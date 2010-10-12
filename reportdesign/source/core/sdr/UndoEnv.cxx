/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 * 
 * Copyright 2000, 2010 Oracle and/or its affiliates.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * This file is part of OpenOffice.org.
 *
 * OpenOffice.org is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License version 3
 * only, as published by the Free Software Foundation.
 *
 * OpenOffice.org is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License version 3 for more details
 * (a copy is included in the LICENSE file that accompanied this code).
 *
 * You should have received a copy of the GNU Lesser General Public License
 * version 3 along with OpenOffice.org.  If not, see
 * <http://www.openoffice.org/license.html>
 * for a copy of the LGPLv3 License.
 *
 ************************************************************************/

#include "UndoActions.hxx"
#include "UndoEnv.hxx"
#include "formatnormalizer.hxx"
#include "conditionupdater.hxx"
#include "corestrings.hrc"
#include "rptui_slotid.hrc"
#include "RptDef.hxx"
#include "ModuleHelper.hxx"
#include "RptObject.hxx"
#include "RptPage.hxx"
#include "RptResId.hrc"
#include "RptModel.hxx"

/** === begin UNO includes === **/
#include <com/sun/star/script/XEventAttacherManager.hpp>
#include <com/sun/star/container/XChild.hpp>
#include <com/sun/star/container/XNameContainer.hpp>
#include <com/sun/star/beans/PropertyAttribute.hpp>
#include <com/sun/star/util/XModifyBroadcaster.hpp>
/** === end UNO includes === **/

#include <connectivity/dbtools.hxx>
#include <svl/smplhint.hxx>
#include <tools/diagnose_ex.h>
#include <comphelper/stl_types.hxx>
#include <vcl/svapp.hxx>
#include <dbaccess/singledoccontroller.hxx>
#include <svx/unoshape.hxx>
#include <vos/mutex.hxx>

namespace rptui
{
    using namespace ::com::sun::star;
    using namespace uno;
    using namespace lang;
    using namespace script;
    using namespace beans;
    using namespace awt;
    using namespace util;
    using namespace container;
    using namespace report;
//----------------------------------------------------------------------------


DECLARE_STL_USTRINGACCESS_MAP(bool, AllProperties);
DECLARE_STL_STDKEY_MAP(uno::Reference< beans::XPropertySet >, AllProperties, PropertySetInfoCache);

// -----------------------------------------------------------------------------

class OXUndoEnvironmentImpl
{
    OXUndoEnvironmentImpl(OXUndoEnvironmentImpl&);
    void operator =(OXUndoEnvironmentImpl&);
public:
    OReportModel&                                       m_rModel;
    PropertySetInfoCache                                m_aPropertySetCache;
    FormatNormalizer                                    m_aFormatNormalizer;
    ConditionUpdater                                    m_aConditionUpdater;
    ::osl::Mutex                                        m_aMutex;
    ::std::vector< uno::Reference< container::XChild> > m_aSections;
    oslInterlockedCount                                 m_nLocks;
    sal_Bool	                                        m_bReadOnly;
    sal_Bool                                            m_bIsUndo;

    OXUndoEnvironmentImpl(OReportModel& _rModel);
};

OXUndoEnvironmentImpl::OXUndoEnvironmentImpl(OReportModel& _rModel) : m_rModel(_rModel)
        ,m_aFormatNormalizer( _rModel )
        ,m_aConditionUpdater()
        ,m_nLocks(0)
        ,m_bReadOnly(sal_False)
        ,m_bIsUndo(sal_False)
{
}

//------------------------------------------------------------------------------
DBG_NAME( rpt_OXUndoEnvironment );
//------------------------------------------------------------------------------
OXUndoEnvironment::OXUndoEnvironment(OReportModel& _rModel)
                   :m_pImpl(new OXUndoEnvironmentImpl(_rModel) )
{
    DBG_CTOR( rpt_OXUndoEnvironment,NULL);
    StartListening(m_pImpl->m_rModel);
}

//------------------------------------------------------------------------------
OXUndoEnvironment::~OXUndoEnvironment()
{
    DBG_DTOR( rpt_OXUndoEnvironment,NULL);
}
// -----------------------------------------------------------------------------
void OXUndoEnvironment::Lock() 
{ 
    OSL_ENSURE(m_refCount,"Illegal call to dead object!");
    osl_incrementInterlockedCount( &m_pImpl->m_nLocks ); 
}
void OXUndoEnvironment::UnLock() 
{ 
    OSL_ENSURE(m_refCount,"Illegal call to dead object!");

    osl_decrementInterlockedCount( &m_pImpl->m_nLocks ); 
}
sal_Bool OXUndoEnvironment::IsLocked() const { return m_pImpl->m_nLocks != 0; }
// -----------------------------------------------------------------------------
void OXUndoEnvironment::RemoveSection(OReportPage* _pPage)
{
    if ( _pPage )
    {
        Reference< XInterface > xSection(_pPage->getSection());
        if ( xSection.is() )
            RemoveElement( xSection );
    }
}
//------------------------------------------------------------------------------
void OXUndoEnvironment::Clear(const Accessor& /*_r*/)
{
    OUndoEnvLock aLock(*this);

#if OSL_DEBUG_LEVEL > 0
    // TODO: LLA->OJ please describe what you are doing in this code fragment.
    PropertySetInfoCache::iterator aIter = m_pImpl->m_aPropertySetCache.begin();
    PropertySetInfoCache::iterator aEnd = m_pImpl->m_aPropertySetCache.end();
    int ndbg_len = m_pImpl->m_aPropertySetCache.size();
    ndbg_len = ndbg_len;
    for (int idbg_ = 0; aIter != aEnd; ++aIter,++idbg_)
    {
        uno::Reference<beans::XPropertySet> xProp(aIter->first,uno::UNO_QUERY);
        xProp->getPropertySetInfo();
        int nlen = aIter->second.size();
        nlen = nlen;
    }
#endif
    m_pImpl->m_aPropertySetCache.clear();

    sal_uInt16 nCount = m_pImpl->m_rModel.GetPageCount();
    sal_uInt16 i;
    for (i = 0; i < nCount; i++)
    {
        OReportPage* pPage = PTR_CAST( OReportPage, m_pImpl->m_rModel.GetPage(i) );
        RemoveSection(pPage);
    }

    nCount = m_pImpl->m_rModel.GetMasterPageCount();
    for (i = 0; i < nCount; i++)
    {
        OReportPage* pPage = PTR_CAST( OReportPage, m_pImpl->m_rModel.GetMasterPage(i) );
        RemoveSection(pPage);
    }    

    m_pImpl->m_aSections.clear();

    if (IsListening(m_pImpl->m_rModel))
        EndListening(m_pImpl->m_rModel);
}

//------------------------------------------------------------------------------
void OXUndoEnvironment::ModeChanged()
{
    m_pImpl->m_bReadOnly = !m_pImpl->m_bReadOnly;

    if (!m_pImpl->m_bReadOnly)
        StartListening(m_pImpl->m_rModel);
    else
        EndListening(m_pImpl->m_rModel);
}

//------------------------------------------------------------------------------
void OXUndoEnvironment::Notify( SfxBroadcaster& /*rBC*/, const SfxHint& rHint )
{
    if (rHint.ISA(SfxSimpleHint) && ((SfxSimpleHint&)rHint).GetId() == SFX_HINT_MODECHANGED )
        ModeChanged();
}
// -----------------------------------------------------------------------------
//	XEventListener
//------------------------------------------------------------------------------
void SAL_CALL OXUndoEnvironment::disposing(const EventObject& e) throw( RuntimeException )
{
    // check if it's an object we have cached informations about
    Reference< XPropertySet > xSourceSet(e.Source, UNO_QUERY);
    if ( xSourceSet.is() )
    {
        uno::Reference< report::XSection> xSection(xSourceSet,uno::UNO_QUERY);
        if ( xSection.is() )
            RemoveSection(xSection);
        else
            RemoveElement(xSourceSet);
        /*if (!m_pImpl->m_aPropertySetCache.empty())
            m_pImpl->m_aPropertySetCache.erase(xSourceSet);*/
    }
}

// XPropertyChangeListener
//------------------------------------------------------------------------------
void SAL_CALL OXUndoEnvironment::propertyChange( const PropertyChangeEvent& _rEvent ) throw(uno::RuntimeException)
{
    ::osl::ClearableMutexGuard aGuard( m_pImpl->m_aMutex );

    if ( IsLocked() )
        return;

    Reference< XPropertySet >  xSet( _rEvent.Source, UNO_QUERY );
    if (!xSet.is())
        return;

    dbaui::OSingleDocumentController* pController = m_pImpl->m_rModel.getController();
    if ( !pController )
        return;

    // no Undo for transient and readonly props. 
    // let's see if we know something about the set
#if OSL_DEBUG_LEVEL > 0
    int nlen = m_pImpl->m_aPropertySetCache.size();
    nlen = nlen;
#endif
    PropertySetInfoCache::iterator aSetPos = m_pImpl->m_aPropertySetCache.find(xSet);
    if (aSetPos == m_pImpl->m_aPropertySetCache.end())
    {
        AllProperties aNewEntry;
        aSetPos = m_pImpl->m_aPropertySetCache.insert(PropertySetInfoCache::value_type(xSet,aNewEntry)).first;
        DBG_ASSERT(aSetPos != m_pImpl->m_aPropertySetCache.end(), "OXUndoEnvironment::propertyChange : just inserted it ... why it's not there ?");
    }
    if ( aSetPos == m_pImpl->m_aPropertySetCache.end() )
        return;

    // now we have access to the cached info about the set
    // let's see what we know about the property
    AllProperties& rPropInfos = aSetPos->second;
    AllPropertiesIterator aPropertyPos = rPropInfos.find( _rEvent.PropertyName );
    if (aPropertyPos == rPropInfos.end())
    {	// nothing 'til now ... have to change this ....
        // the attributes
        INT32 nAttributes = xSet->getPropertySetInfo()->getPropertyByName( _rEvent.PropertyName ).Attributes;
        bool bTransReadOnly = ((nAttributes & PropertyAttribute::READONLY) != 0) || ((nAttributes & PropertyAttribute::TRANSIENT) != 0);

        // insert the new entry
        aPropertyPos = rPropInfos.insert( AllProperties::value_type( _rEvent.PropertyName, bTransReadOnly ) ).first;
        DBG_ASSERT(aPropertyPos != rPropInfos.end(), "OXUndoEnvironment::propertyChange : just inserted it ... why it's not there ?");
    }

    implSetModified();

    // now we have access to the cached info about the property affected
    // and are able to decide wether or not we need an undo action

    // no UNDO for transient/readonly properties
    if ( aPropertyPos->second )
        return;

    // give components with sub responsibilities a chance
    m_pImpl->m_aFormatNormalizer.notifyPropertyChange( _rEvent );
    m_pImpl->m_aConditionUpdater.notifyPropertyChange( _rEvent );

    aGuard.clear();
    // TODO: this is a potential race condition: two threads here could in theory
    // add their undo actions out-of-order

    ::vos::OClearableGuard aSolarGuard( Application::GetSolarMutex() );
    ORptUndoPropertyAction* pUndo = NULL;
    try
    {
        uno::Reference< report::XSection> xSection( xSet, uno::UNO_QUERY );
        if ( xSection.is() )
        {
            uno::Reference< report::XGroup> xGroup = xSection->getGroup();
            if ( xGroup.is() )
                pUndo = new OUndoPropertyGroupSectionAction( m_pImpl->m_rModel, _rEvent, OGroupHelper::getMemberFunction( xSection ), xGroup );
            else
                pUndo = new OUndoPropertyReportSectionAction( m_pImpl->m_rModel, _rEvent, OReportHelper::getMemberFunction( xSection ), xSection->getReportDefinition() );
        }
    }
    catch(const Exception&)
    {
        DBG_UNHANDLED_EXCEPTION();
    }

    if ( pUndo == NULL )
        pUndo = new ORptUndoPropertyAction( m_pImpl->m_rModel, _rEvent );

    pController->addUndoActionAndInvalidate(pUndo);
    pController->InvalidateAll();
}
// -----------------------------------------------------------------------------
::std::vector< uno::Reference< container::XChild> >::const_iterator OXUndoEnvironment::getSection(const Reference<container::XChild>& _xContainer) const
{
    ::std::vector< uno::Reference< container::XChild> >::const_iterator aFind = m_pImpl->m_aSections.end();
    if ( _xContainer.is() )
    {
        aFind = ::std::find(m_pImpl->m_aSections.begin(),m_pImpl->m_aSections.end(),_xContainer);
            
        if ( aFind == m_pImpl->m_aSections.end() )
        {
            Reference<container::XChild> xParent(_xContainer->getParent(),uno::UNO_QUERY);
            aFind = getSection(xParent);
        }
    }
    return aFind;
}
// XContainerListener
//------------------------------------------------------------------------------
void SAL_CALL OXUndoEnvironment::elementInserted(const ContainerEvent& evt) throw(uno::RuntimeException)
{
    ::vos::OClearableGuard aSolarGuard( Application::GetSolarMutex() );
    ::osl::MutexGuard aGuard( m_pImpl->m_aMutex );

    // neues Object zum lauschen
    Reference< uno::XInterface >  xIface( evt.Element, UNO_QUERY );
    if ( !IsLocked() )
    {
        Reference< report::XReportComponent >  xReportComponent( xIface, UNO_QUERY );
        if ( xReportComponent.is() )
        {
            Reference< report::XSection > xContainer(evt.Source,uno::UNO_QUERY);

            ::std::vector< uno::Reference< container::XChild> >::const_iterator aFind = getSection(xContainer.get());
            
            if ( aFind != m_pImpl->m_aSections.end() )
            {
                OUndoEnvLock aLock(*this);
                try
                {
                    OReportPage* pPage = m_pImpl->m_rModel.getPage(uno::Reference< report::XSection>(*aFind,uno::UNO_QUERY));
                    OSL_ENSURE(pPage,"No page could be found for section!");
                    if ( pPage )
                        pPage->insertObject(xReportComponent);
                }
                catch(uno::Exception&)
                {
                    DBG_UNHANDLED_EXCEPTION();
                }
             
            }
        }
        else
        {
            uno::Reference< report::XFunctions> xContainer(evt.Source,uno::UNO_QUERY);
            if ( xContainer.is() )
            {
                dbaui::OSingleDocumentController* pController = m_pImpl->m_rModel.getController();
                pController->addUndoActionAndInvalidate(new OUndoContainerAction(m_pImpl->m_rModel
                                                                                ,rptui::Inserted
                                                                                ,xContainer.get()
                                                                                ,xIface
                                                                                ,RID_STR_UNDO_ADDFUNCTION));
            }
        }
    }

    AddElement(xIface);

    implSetModified();
}

//------------------------------------------------------------------------------
void OXUndoEnvironment::implSetModified()
{
    //if ( !IsLocked() )
    m_pImpl->m_rModel.SetModified( sal_True );
}

//------------------------------------------------------------------------------
void SAL_CALL OXUndoEnvironment::elementReplaced(const ContainerEvent& evt) throw(uno::RuntimeException)
{
    ::vos::OClearableGuard aSolarGuard( Application::GetSolarMutex() );
    ::osl::MutexGuard aGuard( m_pImpl->m_aMutex );

    Reference< XInterface >  xIface(evt.ReplacedElement,uno::UNO_QUERY);
    OSL_ENSURE(xIface.is(), "OXUndoEnvironment::elementReplaced: invalid container notification!");
    RemoveElement(xIface);

    xIface.set(evt.Element,uno::UNO_QUERY);
    AddElement(xIface);

    implSetModified();
}

//------------------------------------------------------------------------------
void SAL_CALL OXUndoEnvironment::elementRemoved(const ContainerEvent& evt) throw(uno::RuntimeException)
{
    ::vos::OClearableGuard aSolarGuard( Application::GetSolarMutex() );
    ::osl::MutexGuard aGuard( m_pImpl->m_aMutex );

    Reference< uno::XInterface >  xIface( evt.Element, UNO_QUERY );
    if ( !IsLocked() )
    {
        Reference< report::XSection > xContainer(evt.Source,uno::UNO_QUERY);
        ::std::vector< uno::Reference< container::XChild> >::const_iterator aFind = getSection(xContainer.get());
        
        Reference< report::XReportComponent >  xReportComponent( xIface, UNO_QUERY );
        if ( aFind != m_pImpl->m_aSections.end() && xReportComponent.is() )
        {
            OXUndoEnvironment::OUndoEnvLock aLock(*this);
            try
            {
                OReportPage* pPage = m_pImpl->m_rModel.getPage(uno::Reference< report::XSection >( *aFind, uno::UNO_QUERY_THROW ) );
                OSL_ENSURE( pPage, "OXUndoEnvironment::elementRemoved: no page for the section!" );
                if ( pPage )
                    pPage->removeSdrObject(xReportComponent);
            }
            catch(const uno::Exception&)
            {
                DBG_UNHANDLED_EXCEPTION();
            }
        }
        else
        {
            uno::Reference< report::XFunctions> xFunctions(evt.Source,uno::UNO_QUERY);
            if ( xFunctions.is() )
            {
                dbaui::OSingleDocumentController* pController = m_pImpl->m_rModel.getController();
                pController->addUndoActionAndInvalidate(new OUndoContainerAction(m_pImpl->m_rModel
                                                                                ,rptui::Removed
                                                                                ,xFunctions.get()
                                                                                ,xIface
                                                                                ,RID_STR_UNDO_ADDFUNCTION));
            }
        }
    }
    
    if ( xIface.is() )
        RemoveElement(xIface);

    implSetModified();
}

//------------------------------------------------------------------------------
void SAL_CALL OXUndoEnvironment::modified( const EventObject& /*aEvent*/ ) throw (RuntimeException)
{
    implSetModified();
}

//------------------------------------------------------------------------------
void OXUndoEnvironment::AddSection(const Reference< report::XSection > & _xSection)
{
    OUndoEnvLock aLock(*this);
    try
    {
        uno::Reference<container::XChild> xChild = _xSection.get();
        uno::Reference<report::XGroup> xGroup(xChild->getParent(),uno::UNO_QUERY);
        m_pImpl->m_aSections.push_back(xChild);
        Reference< XInterface >  xInt(_xSection);
        AddElement(xInt);
    }
    catch(const uno::Exception&)
    {
        DBG_UNHANDLED_EXCEPTION();
    }
}

//------------------------------------------------------------------------------
void OXUndoEnvironment::RemoveSection(const Reference< report::XSection > & _xSection)
{
    OUndoEnvLock aLock(*this);
    try
    {
        uno::Reference<container::XChild> xChild(_xSection.get());
        m_pImpl->m_aSections.erase(::std::remove(m_pImpl->m_aSections.begin(),m_pImpl->m_aSections.end(),
            xChild), m_pImpl->m_aSections.end());
        Reference< XInterface >  xInt(_xSection);
        RemoveElement(xInt);
    }
    catch(uno::Exception&){}
}

//------------------------------------------------------------------------------
void OXUndoEnvironment::TogglePropertyListening(const Reference< XInterface > & Element)
{
    // am Container horchen
    Reference< XIndexAccess >  xContainer(Element, UNO_QUERY);
    if (xContainer.is())
    {
        Reference< XInterface > xInterface;
        sal_Int32 nCount = xContainer->getCount();
        for(sal_Int32 i = 0;i != nCount;++i)
        {
            xInterface.set(xContainer->getByIndex( i ),uno::UNO_QUERY);
            TogglePropertyListening(xInterface);
        }
    }

    Reference< XPropertySet >  xSet(Element, UNO_QUERY);
    if (xSet.is())
    {
        if (!m_pImpl->m_bReadOnly)
            xSet->addPropertyChangeListener( ::rtl::OUString(), this );
        else
            xSet->removePropertyChangeListener( ::rtl::OUString(), this );
    }
}


//------------------------------------------------------------------------------
void OXUndoEnvironment::switchListening( const Reference< XIndexAccess >& _rxContainer, bool _bStartListening ) SAL_THROW(())
{
    OSL_PRECOND( _rxContainer.is(), "OXUndoEnvironment::switchListening: invalid container!" );
    if ( !_rxContainer.is() )
        return;

    try
    {
        // also handle all children of this element
        Reference< XInterface > xInterface;
        sal_Int32 nCount = _rxContainer->getCount();
        for(sal_Int32 i = 0;i != nCount;++i)
        {
            xInterface.set(_rxContainer->getByIndex( i ),uno::UNO_QUERY);
            if ( _bStartListening )
                AddElement( xInterface );
            else
                RemoveElement( xInterface );
        }

        // be notified of any changes in the container elements
        Reference< XContainer > xSimpleContainer( _rxContainer, UNO_QUERY );
        // OSL_ENSURE( xSimpleContainer.is(), "OXUndoEnvironment::switchListening: how are we expected to be notified of changes in the container?" );
        if ( xSimpleContainer.is() )
        {
            if ( _bStartListening )
                xSimpleContainer->addContainerListener( this );
            else
                xSimpleContainer->removeContainerListener( this );
        }
    }
    catch( const Exception& )
    {
        DBG_UNHANDLED_EXCEPTION();
    }
}

//------------------------------------------------------------------------------
void OXUndoEnvironment::switchListening( const Reference< XInterface >& _rxObject, bool _bStartListening ) SAL_THROW(())
{
    OSL_PRECOND( _rxObject.is(), "OXUndoEnvironment::switchListening: how should I listen at a NULL object?" );

    try
    {
        if ( !m_pImpl->m_bReadOnly )
        {
            Reference< XPropertySet > xProps( _rxObject, UNO_QUERY );
            if ( xProps.is() )
            {
                if ( _bStartListening )
                    xProps->addPropertyChangeListener( ::rtl::OUString(), this );
                else
                    xProps->removePropertyChangeListener( ::rtl::OUString(), this );
            }
        }

        Reference< XModifyBroadcaster > xBroadcaster( _rxObject, UNO_QUERY );
        if ( xBroadcaster.is() )
        {
            if ( _bStartListening )
                xBroadcaster->addModifyListener( this );
            else
                xBroadcaster->removeModifyListener( this );
        }
    }
    catch( const Exception& )
    {
        //OSL_ENSURE( sal_False, "OXUndoEnvironment::switchListening: caught an exception!" );
    }
}

//------------------------------------------------------------------------------
void OXUndoEnvironment::AddElement(const Reference< XInterface >& _rxElement )
{
    if ( !IsLocked() )
        m_pImpl->m_aFormatNormalizer.notifyElementInserted( _rxElement );

    // if it's a container, start listening at all elements
    Reference< XIndexAccess > xContainer( _rxElement, UNO_QUERY );
    if ( xContainer.is() )
        switchListening( xContainer, true );

    switchListening( _rxElement, true );
}

//------------------------------------------------------------------------------
void OXUndoEnvironment::RemoveElement(const Reference< XInterface >& _rxElement)
{
    uno::Reference<beans::XPropertySet> xProp(_rxElement,uno::UNO_QUERY);
    if (!m_pImpl->m_aPropertySetCache.empty())
        m_pImpl->m_aPropertySetCache.erase(xProp);
    switchListening( _rxElement, false );

    Reference< XIndexAccess > xContainer( _rxElement, UNO_QUERY );
    if ( xContainer.is() )
        switchListening( xContainer, false );
}

void OXUndoEnvironment::SetUndoMode(sal_Bool _bUndo)
{
    m_pImpl->m_bIsUndo = _bUndo;
}

sal_Bool OXUndoEnvironment::IsUndoMode() const
{
    return m_pImpl->m_bIsUndo;
}
//============================================================================
} // rptui
//============================================================================

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
