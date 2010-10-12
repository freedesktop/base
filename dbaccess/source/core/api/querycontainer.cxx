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

// MARKER(update_precomp.py): autogen include statement, do not remove
#include "precompiled_dbaccess.hxx"

#include "querycontainer.hxx"
#include "dbastrings.hrc"
#include "query.hxx"
#include "objectnameapproval.hxx"
#include "ContainerListener.hxx"
#include "veto.hxx"

/** === begin UNO includes === **/
#include <com/sun/star/beans/XPropertySet.hpp>
#include <com/sun/star/container/XContainer.hpp>
#include <com/sun/star/sdbc/XConnection.hpp>
#include <com/sun/star/container/XContainerApproveBroadcaster.hpp>
/** === end UNO includes === **/

#include <connectivity/dbexception.hxx>

#include <tools/debug.hxx>
#include <comphelper/enumhelper.hxx>
#include <comphelper/uno3.hxx>
#include <comphelper/property.hxx>
#include <comphelper/sequence.hxx>
#include <comphelper/extract.hxx>
#include <cppuhelper/exc_hlp.hxx>

using namespace dbtools;
using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::ucb;
using namespace ::com::sun::star::lang;
using namespace ::com::sun::star::beans;
using namespace ::com::sun::star::sdb;
using namespace ::com::sun::star::sdbc;
using namespace ::com::sun::star::sdbcx;
using namespace ::com::sun::star::container;
using namespace ::com::sun::star::util;
using namespace ::osl;
using namespace ::comphelper;
using namespace ::cppu;

//........................................................................
namespace dbaccess
{
//........................................................................

//==========================================================================
//= OQueryContainer
//==========================================================================
DBG_NAME(OQueryContainer)
//------------------------------------------------------------------------------
OQueryContainer::OQueryContainer(
                  const Reference< XNameContainer >& _rxCommandDefinitions
                , const Reference< XConnection >& _rxConn
                , const Reference< XMultiServiceFactory >& _rxORB,
                ::dbtools::IWarningsContainer* _pWarnings)
    :ODefinitionContainer(_rxORB,NULL,TContentPtr(new ODefinitionContainer_Impl))
    ,m_pWarnings( _pWarnings )
    ,m_xCommandDefinitions(_rxCommandDefinitions)
    ,m_xConnection(_rxConn)
{
    DBG_CTOR(OQueryContainer, NULL);

    increment(m_refCount);
    {
        m_pCommandsListener = new OContainerListener( *this, m_aMutex );
        m_pCommandsListener->acquire();
        
        Reference< XContainer >	xContainer( m_xCommandDefinitions, UNO_QUERY_THROW );
        xContainer->addContainerListener( m_pCommandsListener );

        Reference< XContainerApproveBroadcaster > xContainerApprove( m_xCommandDefinitions, UNO_QUERY_THROW );
        xContainerApprove->addContainerApproveListener( m_pCommandsListener );

        // fill my structures
        ODefinitionContainer_Impl& rDefinitions( getDefinitions() );
        Sequence< ::rtl::OUString > sDefinitionNames = m_xCommandDefinitions->getElementNames();
        const ::rtl::OUString* pDefinitionName = sDefinitionNames.getConstArray();
        const ::rtl::OUString* pEnd = pDefinitionName + sDefinitionNames.getLength();
        for ( ; pDefinitionName != pEnd; ++pDefinitionName )
        {
            rDefinitions.insert( *pDefinitionName, TContentPtr() );
            m_aDocuments.push_back(m_aDocumentMap.insert(Documents::value_type(*pDefinitionName,Documents::mapped_type())).first);
        }
    }
    decrement(m_refCount);

    setElementApproval( PContainerApprove( new ObjectNameApproval( _rxConn, ObjectNameApproval::TypeQuery ) ) );
}

//------------------------------------------------------------------------------
OQueryContainer::~OQueryContainer()
{
    DBG_DTOR(OQueryContainer, NULL);
    //	dispose();
        //	maybe we're already disposed, but this should be uncritical
}
// -----------------------------------------------------------------------------
IMPLEMENT_FORWARD_XINTERFACE2( OQueryContainer,ODefinitionContainer,OQueryContainer_Base)

//------------------------------------------------------------------------------
IMPLEMENT_FORWARD_XTYPEPROVIDER2( OQueryContainer,ODefinitionContainer,OQueryContainer_Base)

//------------------------------------------------------------------------------
void OQueryContainer::disposing()
{
    ODefinitionContainer::disposing();
    MutexGuard aGuard(m_aMutex);
    if ( !m_xCommandDefinitions.is() )
        // already disposed
        return;

    if ( m_pCommandsListener )
    {
        Reference< XContainer >	xContainer( m_xCommandDefinitions, UNO_QUERY );
        xContainer->removeContainerListener( m_pCommandsListener );
        Reference< XContainerApproveBroadcaster > xContainerApprove( m_xCommandDefinitions, UNO_QUERY );
        xContainerApprove->removeContainerApproveListener( m_pCommandsListener );

        m_pCommandsListener->dispose();
        m_pCommandsListener->release();
        m_pCommandsListener = NULL;
    }

    m_xCommandDefinitions	= NULL;
    m_xConnection			= NULL;
}

// XServiceInfo
//------------------------------------------------------------------------------
IMPLEMENT_SERVICE_INFO2(OQueryContainer, "com.sun.star.sdb.dbaccess.OQueryContainer", SERVICE_SDBCX_CONTAINER, SERVICE_SDB_QUERIES)

// XDataDescriptorFactory
//--------------------------------------------------------------------------
Reference< XPropertySet > SAL_CALL OQueryContainer::createDataDescriptor(  ) throw(RuntimeException)
{
    return new OQueryDescriptor();
}

// XAppend
//------------------------------------------------------------------------------
void SAL_CALL OQueryContainer::appendByDescriptor( const Reference< XPropertySet >& _rxDesc ) throw(SQLException, ElementExistException, RuntimeException)
{
    ResettableMutexGuard aGuard(m_aMutex);
    if ( !m_xCommandDefinitions.is() )
        throw DisposedException( ::rtl::OUString(), *this );

    // first clone this object's CommandDefinition part
    Reference< XPropertySet > xCommandDefinitionPart( m_aContext.createComponent( (::rtl::OUString)SERVICE_SDB_QUERYDEFINITION ), UNO_QUERY_THROW );
    ::comphelper::copyProperties( _rxDesc, xCommandDefinitionPart );
    // TODO : the columns part of the descriptor has to be copied

    // create a wrapper for the object (*before* inserting into our command definition container)
    Reference< XContent > xNewObject( implCreateWrapper( Reference< XContent>( xCommandDefinitionPart, UNO_QUERY_THROW ) ) );

    ::rtl::OUString sNewObjectName;
    _rxDesc->getPropertyValue(PROPERTY_NAME) >>= sNewObjectName;

    try
    {
        notifyByName( aGuard, sNewObjectName, xNewObject, NULL, E_INSERTED, ApproveListeners );
    }
    catch( const Exception& )
    {
        disposeComponent( xNewObject );
        disposeComponent( xCommandDefinitionPart );
        throw;
    }

    // insert the basic object into the definition container
    {
        m_eDoingCurrently =	INSERTING;
        OAutoActionReset aAutoReset(this);
        m_xCommandDefinitions->insertByName(sNewObjectName, makeAny(xCommandDefinitionPart));
    }

    implAppend( sNewObjectName, xNewObject );
    notifyByName( aGuard, sNewObjectName, xNewObject, NULL, E_INSERTED, ContainerListemers );
}

// XDrop
//------------------------------------------------------------------------------
void SAL_CALL OQueryContainer::dropByName( const ::rtl::OUString& _rName ) throw(SQLException, NoSuchElementException, RuntimeException)
{
    MutexGuard aGuard(m_aMutex);
    if ( !checkExistence(_rName) )
        throw NoSuchElementException(_rName,*this);

    if ( !m_xCommandDefinitions.is() )
        throw DisposedException( ::rtl::OUString(), *this );

    // now simply forward the remove request to the CommandDefinition container, we're a listener for the removal
    // and thus we do everything neccessary in ::elementRemoved
    m_xCommandDefinitions->removeByName(_rName);
}

//------------------------------------------------------------------------------
void SAL_CALL OQueryContainer::dropByIndex( sal_Int32 _nIndex ) throw(SQLException, IndexOutOfBoundsException, RuntimeException)
{
    MutexGuard aGuard(m_aMutex);
    if ((_nIndex<0) || (_nIndex>getCount()))
        throw IndexOutOfBoundsException();

    if ( !m_xCommandDefinitions.is() )
        throw DisposedException( ::rtl::OUString(), *this );

    ::rtl::OUString sName;
    Reference<XPropertySet> xProp(Reference<XIndexAccess>(m_xCommandDefinitions,UNO_QUERY)->getByIndex(_nIndex),UNO_QUERY);
    if ( xProp.is() )
        xProp->getPropertyValue(PROPERTY_NAME) >>= sName;

    dropByName(sName);
}
//------------------------------------------------------------------------------
void SAL_CALL OQueryContainer::elementInserted( const ::com::sun::star::container::ContainerEvent& _rEvent ) throw(::com::sun::star::uno::RuntimeException)
{
    Reference< XContent > xNewElement;
    ::rtl::OUString sElementName;
    _rEvent.Accessor >>= sElementName;
    {
        MutexGuard aGuard(m_aMutex);
        if (INSERTING == m_eDoingCurrently)
            // nothing to do, we're inserting via an "appendByDescriptor"
            return;

        DBG_ASSERT(sElementName.getLength(), "OQueryContainer::elementInserted : invalid name !");
        DBG_ASSERT(m_aDocumentMap.find(sElementName) == m_aDocumentMap.end(), "OQueryContainer::elementInserted         : oops .... we're inconsistent with our master container !");
        if (!sElementName.getLength() || hasByName(sElementName))
            return;

        // insert an own new element
        xNewElement = implCreateWrapper(sElementName);
    }
    insertByName(sElementName,makeAny(xNewElement));
}

//------------------------------------------------------------------------------
void SAL_CALL OQueryContainer::elementRemoved( const ::com::sun::star::container::ContainerEvent& _rEvent ) throw(::com::sun::star::uno::RuntimeException)
{
    ::rtl::OUString sAccessor;
    _rEvent.Accessor >>= sAccessor;
    {
        DBG_ASSERT(sAccessor.getLength(), "OQueryContainer::elementRemoved : invalid name !");
        DBG_ASSERT(m_aDocumentMap.find(sAccessor) != m_aDocumentMap.end(), "OQueryContainer::elementRemoved : oops .... we're inconsistent with our master container !");
        if ( !sAccessor.getLength() || !hasByName(sAccessor) )
            return;
    }
    removeByName(sAccessor);
}

//------------------------------------------------------------------------------
void SAL_CALL OQueryContainer::elementReplaced( const ::com::sun::star::container::ContainerEvent& _rEvent ) throw(::com::sun::star::uno::RuntimeException)
{
    Reference< XPropertySet > xReplacedElement;
    Reference< XContent > xNewElement;
    ::rtl::OUString sAccessor;
    _rEvent.Accessor >>= sAccessor;

    {
        MutexGuard aGuard(m_aMutex);
        DBG_ASSERT(sAccessor.getLength(), "OQueryContainer::elementReplaced : invalid name !");
        DBG_ASSERT(m_aDocumentMap.find(sAccessor) != m_aDocumentMap.end(), "OQueryContainer::elementReplaced         : oops .... we're inconsistent with our master container !");
        if (!sAccessor.getLength() || !hasByName(sAccessor))
            return;
        
        xNewElement = implCreateWrapper(sAccessor);
    }

    replaceByName(sAccessor,makeAny(xNewElement));
}

//------------------------------------------------------------------------------
Reference< XVeto > SAL_CALL OQueryContainer::approveInsertElement( const ContainerEvent& Event ) throw (WrappedTargetException, RuntimeException)
{
    ::rtl::OUString sName;
    OSL_VERIFY( Event.Accessor >>= sName );
    Reference< XContent > xElement( Event.Element, UNO_QUERY_THROW );

    Reference< XVeto > xReturn;
    try
    {
        getElementApproval()->approveElement( sName, xElement.get() );
    }
    catch( const Exception& )
    {
        xReturn = new Veto( ::rtl::OUString(), ::cppu::getCaughtException() );
    }
    return xReturn;
}

//------------------------------------------------------------------------------
Reference< XVeto > SAL_CALL OQueryContainer::approveReplaceElement( const ContainerEvent& /*Event*/ ) throw (WrappedTargetException, RuntimeException)
{
    return NULL;
}

//------------------------------------------------------------------------------
Reference< XVeto > SAL_CALL OQueryContainer::approveRemoveElement( const ContainerEvent& /*Event*/ ) throw (WrappedTargetException, RuntimeException)
{
    return NULL;
}

//------------------------------------------------------------------------------
void SAL_CALL OQueryContainer::disposing( const ::com::sun::star::lang::EventObject& _rSource ) throw(::com::sun::star::uno::RuntimeException)
{
    if (_rSource.Source.get() == Reference< XInterface >(m_xCommandDefinitions, UNO_QUERY).get())
    {	// our "master container" (with the command definitions) is beeing disposed
        DBG_ERROR("OQueryContainer::disposing : nobody should dispose the CommandDefinition container before disposing my connection !");
        dispose();
    }
    else 
    {
        Reference< XContent > xSource(_rSource.Source, UNO_QUERY);
        // it's one of our documents ....
        Documents::iterator aIter = m_aDocumentMap.begin();
        Documents::iterator aEnd = m_aDocumentMap.end();
        for	(;aIter != aEnd;++aIter )
        {
            if ( xSource == aIter->second.get() )
            {
                m_xCommandDefinitions->removeByName(aIter->first);
                break;
            }
        }
        ODefinitionContainer::disposing(_rSource);
    }
}

// -----------------------------------------------------------------------------
::rtl::OUString OQueryContainer::determineContentType() const
{
    return ::rtl::OUString( RTL_CONSTASCII_USTRINGPARAM( "application/vnd.org.openoffice.DatabaseQueryContainer" ) );
}

// -----------------------------------------------------------------------------
Reference< XContent > OQueryContainer::implCreateWrapper(const ::rtl::OUString& _rName)
{
    Reference< XContent > xObject(m_xCommandDefinitions->getByName(_rName),UNO_QUERY);
    return implCreateWrapper(xObject);
}

//--------------------------------------------------------------------------
Reference< XContent > OQueryContainer::implCreateWrapper(const Reference< XContent >& _rxCommandDesc)
{
    Reference<XNameContainer> xContainer(_rxCommandDesc,UNO_QUERY);
    Reference< XContent > xReturn;
    if ( xContainer .is() )
    {
        xReturn = new OQueryContainer( xContainer, m_xConnection, m_aContext.getLegacyServiceFactory(), m_pWarnings );
    }
    else
    {
        OQuery* pNewObject = new OQuery( Reference< XPropertySet >( _rxCommandDesc, UNO_QUERY ), m_xConnection, m_aContext.getLegacyServiceFactory() );
        xReturn = pNewObject;

        pNewObject->setWarningsContainer( m_pWarnings );
//		pNewObject->getColumns();
        // Why? This is expensive. If you comment this in 'cause you really need it, be sure to run the
        // QueryInQuery test in dbaccess/qa/complex/dbaccess ...
    }

    return xReturn;
}
//--------------------------------------------------------------------------
Reference< XContent > OQueryContainer::createObject( const ::rtl::OUString& _rName)
{
    return implCreateWrapper(_rName);
}
// -----------------------------------------------------------------------------
sal_Bool OQueryContainer::checkExistence(const ::rtl::OUString& _rName)
{
    sal_Bool bRet = sal_False;
    if ( !m_bInPropertyChange )
    {
        bRet = m_xCommandDefinitions->hasByName(_rName);
        Documents::iterator aFind = m_aDocumentMap.find(_rName);
        if ( !bRet && aFind != m_aDocumentMap.end() )
        {
            m_aDocuments.erase( ::std::find(m_aDocuments.begin(),m_aDocuments.end(),aFind));
            m_aDocumentMap.erase(aFind);
        }
        else if ( bRet && aFind == m_aDocumentMap.end() )
        {
            implAppend(_rName,NULL);
        }
    }
    return bRet;
}
//--------------------------------------------------------------------------
sal_Bool SAL_CALL OQueryContainer::hasElements( ) throw (RuntimeException)
{
    MutexGuard aGuard(m_aMutex);
    return m_xCommandDefinitions->hasElements();
}
// -----------------------------------------------------------------------------
sal_Int32 SAL_CALL OQueryContainer::getCount(  ) throw(RuntimeException)
{
    MutexGuard aGuard(m_aMutex);
    return Reference<XIndexAccess>(m_xCommandDefinitions,UNO_QUERY)->getCount();
}
// -----------------------------------------------------------------------------
Sequence< ::rtl::OUString > SAL_CALL OQueryContainer::getElementNames(  ) throw(RuntimeException)
{
    MutexGuard aGuard(m_aMutex);

    return m_xCommandDefinitions->getElementNames();
}

//........................................................................
}	// namespace dbaccess
//........................................................................

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
