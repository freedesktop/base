/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 * 
 * Copyright 2008 by Sun Microsystems, Inc.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * $RCSfile: dbtreelistbox.cxx,v $
 * $Revision: 1.20 $
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

#ifndef DBAUI_DBTREELISTBOX_HXX
#include "dbtreelistbox.hxx"
#endif
#ifndef _DBU_RESOURCE_HRC_
#include "dbu_resource.hrc"
#endif
#ifndef DBACCESS_UI_BROWSER_ID_HXX
#include "browserids.hxx"
#endif
#ifndef _DBAUI_LISTVIEWITEMS_HXX_
#include "listviewitems.hxx"
#endif
#ifndef _DBACCESS_UI_CALLBACKS_HXX_
#include "callbacks.hxx"
#endif

#ifndef _COM_SUN_STAR_DATATRANSFER_DND_XDRAGGESTURELISTENER_HDL_
#include <com/sun/star/datatransfer/dnd/XDragGestureListener.hdl>
#endif
#ifndef _COM_SUN_STAR_DATATRANSFER_DND_XDRAGGESTURERECOGNIZER_HPP_ 
#include <com/sun/star/datatransfer/dnd/XDragGestureRecognizer.hpp>
#endif
#ifndef _COM_SUN_STAR_UI_XCONTEXTMENUINTERCEPTOR_HPP_
#include <com/sun/star/ui/XContextMenuInterceptor.hpp>
#endif
#ifndef _COM_SUN_STAR_UTIL_URL_HPP_
#include <com/sun/star/util/URL.hpp>
#endif
#ifndef _CPPUHELPER_IMPLBASE1_HXX_
#include <cppuhelper/implbase1.hxx>
#endif
#ifndef _CPPUHELPER_INTERFACECONTAINER_HXX_
#include <cppuhelper/interfacecontainer.hxx>
#endif
#ifndef _SV_HELP_HXX
#include <vcl/help.hxx>
#endif
#ifndef _DBAUI_TABLETREE_HRC_
#include "tabletree.hrc"
#endif
#ifndef DBAUI_ICONTROLLER_HXX
#include "IController.hxx"
#endif
#ifndef __FRAMEWORK_HELPER_ACTIONTRIGGERHELPER_HXX_
#include <framework/actiontriggerhelper.hxx>
#endif
#ifndef _TOOLKIT_HELPER_VCLUNOHELPER_HXX_
#include <toolkit/helper/vclunohelper.hxx>
#endif

#include <memory>

// .........................................................................
namespace dbaui
{
// .........................................................................

using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::beans;
using namespace ::com::sun::star::lang;
using namespace ::com::sun::star::datatransfer;
using namespace ::com::sun::star::frame;
using namespace ::com::sun::star::ui;
using namespace ::com::sun::star::view;

DBG_NAME(DBTreeListBox)
#define SPACEBETWEENENTRIES		4
//========================================================================
// class DBTreeListBox
//========================================================================
//------------------------------------------------------------------------
DBTreeListBox::DBTreeListBox( Window* pParent, const Reference< XMultiServiceFactory >& _rxORB, WinBits nWinStyle ,sal_Bool _bHandleEnterKey)
    :SvTreeListBox(pParent,nWinStyle)
    ,m_pSelectedEntry(NULL)
    ,m_pDragedEntry(NULL)
    ,m_pActionListener(NULL)
    ,m_pContextMenuProvider( NULL )
    ,m_nSelectLock(0)
    ,m_bHandleEnterKey(_bHandleEnterKey)
    ,m_xORB(_rxORB)
{
    DBG_CTOR(DBTreeListBox,NULL);
    init();
}
// -----------------------------------------------------------------------------
DBTreeListBox::DBTreeListBox( Window* pParent, const Reference< XMultiServiceFactory >& _rxORB, const ResId& rResId,sal_Bool _bHandleEnterKey)
    :SvTreeListBox(pParent,rResId)
    ,m_pSelectedEntry(NULL)
    ,m_pDragedEntry(NULL)
    ,m_pActionListener(NULL)
    ,m_pContextMenuProvider( NULL )
    ,m_nSelectLock(0)
    ,m_bHandleEnterKey(_bHandleEnterKey)
    ,m_xORB(_rxORB)
{
    DBG_CTOR(DBTreeListBox,NULL);
    init();	
}
// -----------------------------------------------------------------------------
void DBTreeListBox::init()
{
    USHORT nSize = SPACEBETWEENENTRIES;
    SetSpaceBetweenEntries(nSize);

    m_aTimer.SetTimeout(900);
    m_aTimer.SetTimeoutHdl(LINK(this, DBTreeListBox, OnTimeOut));

    m_aScrollHelper.setUpScrollMethod( LINK(this, DBTreeListBox, ScrollUpHdl) );
    m_aScrollHelper.setDownScrollMethod( LINK(this, DBTreeListBox, ScrollDownHdl) );

    SetNodeDefaultImages( );

    EnableContextMenuHandling();
}
//------------------------------------------------------------------------
DBTreeListBox::~DBTreeListBox()
{
    DBG_DTOR(DBTreeListBox,NULL);
    if(m_aTimer.IsActive())
        m_aTimer.Stop();	
}
//------------------------------------------------------------------------
SvLBoxEntry* DBTreeListBox::GetEntryPosByName( const String& aName, SvLBoxEntry* pStart, const IEntryFilter* _pFilter ) const
{
    SvLBoxTreeList*	myModel = GetModel();
    SvTreeEntryList* pChilds = myModel->GetChildList(pStart);
    SvLBoxEntry* pEntry = NULL;
    if ( pChilds )
    {
        ULONG nCount = pChilds->Count();
        for (ULONG i=0; i < nCount; ++i)
        {
            pEntry = static_cast<SvLBoxEntry*>(pChilds->GetObject(i));
            SvLBoxString* pItem = (SvLBoxString*)(pEntry->GetFirstItem(SV_ITEM_ID_LBOXSTRING));
            if ( pItem->GetText().Equals(aName) )
            {
                if ( !_pFilter || _pFilter->includeEntry( pEntry ) )
                    // found
                    break;
            }
            pEntry = NULL;
        }
    }

    return pEntry;
}

// -------------------------------------------------------------------------
void DBTreeListBox::EnableExpandHandler(SvLBoxEntry* _pEntry)
{
    LINK(this, DBTreeListBox, OnResetEntry).Call(_pEntry);
}

// -------------------------------------------------------------------------
void DBTreeListBox::RequestingChilds( SvLBoxEntry* pParent )
{
    if (m_aPreExpandHandler.IsSet())
    {
        if (!m_aPreExpandHandler.Call(pParent))
        {
            // an error occured. The method calling us will reset the entry flags, so it can't be expanded again.
            // But we want that the user may do a second try (i.e. because he misstypes a password in this try), so
            // we have to reset these flags controlling the expand ability
            PostUserEvent(LINK(this, DBTreeListBox, OnResetEntry), pParent);
        }
    }
}

// -------------------------------------------------------------------------
void DBTreeListBox::SelectEntry(SvLBoxEntry* _pEntry)
{
    OSL_ENSURE(_pEntry,"Who called me with NULL!");
    if ( _pEntry )
    {
        if ( GetCurEntry() )
            Select(GetCurEntry(), sal_False);
        Select(_pEntry, sal_True);
        SetCurEntry(_pEntry);
        implSelected(_pEntry);
    }
}

// -------------------------------------------------------------------------
void DBTreeListBox::InitEntry( SvLBoxEntry* _pEntry, const XubString& aStr, const Image& _rCollEntryBmp, const Image& _rExpEntryBmp, SvLBoxButtonKind eButtonKind)
{
    SvTreeListBox::InitEntry( _pEntry, aStr, _rCollEntryBmp,_rExpEntryBmp, eButtonKind);
    SvLBoxItem* pTextItem(_pEntry->GetFirstItem(SV_ITEM_ID_LBOXSTRING));
    SvLBoxString* pString = new OBoldListboxString( _pEntry, 0, aStr );
    _pEntry->ReplaceItem( pString,_pEntry->GetPos(pTextItem));
}

// -------------------------------------------------------------------------
void DBTreeListBox::implSelected(SvLBoxEntry* _pSelected)
{
    if(!m_nSelectLock && _pSelected && m_pSelectedEntry != _pSelected)
    {
        // re-start the timer
        if(m_aTimer.IsActive())
            m_aTimer.Stop();
        m_pSelectedEntry = _pSelected;
        m_aTimer.Start();
    }
}

// -------------------------------------------------------------------------
sal_Int32 DBTreeListBox::lockAutoSelect()
{
    return ++m_nSelectLock;
}

// -------------------------------------------------------------------------
sal_Int32 DBTreeListBox::unlockAutoSelect()
{
    DBG_ASSERT(m_nSelectLock, "DBTreeListBox::unlockAutoSelect: not locked!");
    return --m_nSelectLock;
}
// -----------------------------------------------------------------------------

void DBTreeListBox::DeselectHdl()
{
    SvTreeListBox::DeselectHdl();
}
// -------------------------------------------------------------------------
void DBTreeListBox::SelectHdl()
{
    implSelected(GetHdlEntry());
}

// -------------------------------------------------------------------------
void DBTreeListBox::MouseButtonDown( const MouseEvent& rMEvt )
{
    sal_Bool bHitEmptySpace = (NULL == GetEntry(rMEvt.GetPosPixel(), sal_True));
    if (bHitEmptySpace && (rMEvt.GetClicks() == 2) && rMEvt.IsMod1())
        Control::MouseButtonDown(rMEvt);
    else
        SvTreeListBox::MouseButtonDown(rMEvt);
}

// -------------------------------------------------------------------------
IMPL_LINK(DBTreeListBox, OnResetEntry, SvLBoxEntry*, pEntry)
{
    // set the flag which allows if the entry can be expanded
    pEntry->SetFlags( (pEntry->GetFlags() & ~(SV_ENTRYFLAG_NO_NODEBMP | SV_ENTRYFLAG_HAD_CHILDREN)) | SV_ENTRYFLAG_CHILDS_ON_DEMAND );
    // redraw the entry
    GetModel()->InvalidateEntry( pEntry );
    return 0L;
}
// -----------------------------------------------------------------------------
void DBTreeListBox::ModelHasEntryInvalidated( SvListEntry* _pEntry )
{
    SvTreeListBox::ModelHasEntryInvalidated(_pEntry);
    if ( _pEntry == m_pSelectedEntry && m_pSelectedEntry )
    {
        SvLBoxItem* pTextItem = m_pSelectedEntry->GetFirstItem(SV_ITEM_ID_BOLDLBSTRING);
        if ( pTextItem && !static_cast<OBoldListboxString*>(pTextItem)->isEmphasized() )
        {
            if(m_aTimer.IsActive())
                m_aTimer.Stop();
            m_pSelectedEntry = NULL;
        }
    }
}
// -------------------------------------------------------------------------
void DBTreeListBox::ModelHasRemoved( SvListEntry* _pEntry )
{
    SvTreeListBox::ModelHasRemoved(_pEntry);
    if (_pEntry == m_pSelectedEntry)
    {
        if(m_aTimer.IsActive())
            m_aTimer.Stop();
        m_pSelectedEntry = NULL;
    }
}

// -------------------------------------------------------------------------
sal_Int8 DBTreeListBox::AcceptDrop( const AcceptDropEvent& _rEvt )
{
    sal_Int8 nDropOption = DND_ACTION_NONE;
    if ( m_pActionListener )
    {
        SvLBoxEntry* pDroppedEntry = GetEntry(_rEvt.maPosPixel);
        // check if drag is on child entry, which is not allowed
        SvLBoxEntry* pParent = NULL;
        if ( _rEvt.mnAction & DND_ACTION_MOVE )
        {
            if ( !m_pDragedEntry ) // no entry to move
            {
                nDropOption = m_pActionListener->queryDrop( _rEvt, GetDataFlavorExVector() );
                m_aMousePos = _rEvt.maPosPixel;
                m_aScrollHelper.scroll(m_aMousePos,GetOutputSizePixel());
                return nDropOption;
            }

            pParent = pDroppedEntry ? GetParent(pDroppedEntry) : NULL;
            while ( pParent && pParent != m_pDragedEntry )
                pParent = GetParent(pParent);
        }

        if ( !pParent )
        {
            nDropOption = m_pActionListener->queryDrop( _rEvt, GetDataFlavorExVector() );
            // check if move is allowed
            if ( nDropOption & DND_ACTION_MOVE )
            {
                if ( m_pDragedEntry == pDroppedEntry || GetEntryPosByName(GetEntryText(m_pDragedEntry),pDroppedEntry) )
                    nDropOption = nDropOption & ~DND_ACTION_MOVE;//DND_ACTION_NONE;
            }
            m_aMousePos = _rEvt.maPosPixel;
            m_aScrollHelper.scroll(m_aMousePos,GetOutputSizePixel());
        }
    }

    return nDropOption;
}

// -------------------------------------------------------------------------
sal_Int8 DBTreeListBox::ExecuteDrop( const ExecuteDropEvent& _rEvt )
{
    if ( m_pActionListener )
        return m_pActionListener->executeDrop( _rEvt );

    return DND_ACTION_NONE;
}

// -------------------------------------------------------------------------
void DBTreeListBox::StartDrag( sal_Int8 _nAction, const Point& _rPosPixel )
{
    if ( m_pActionListener )
    {
        m_pDragedEntry = GetEntry(_rPosPixel);
        if ( m_pDragedEntry && m_pActionListener->requestDrag( _nAction, _rPosPixel ) )
        {
            // if the (asynchronous) drag started, stop the selection timer
            m_aTimer.Stop();
            // and stop selecting entries by simply moving the mouse
            EndSelection();
        }
    }
}

// -------------------------------------------------------------------------
void DBTreeListBox::RequestHelp( const HelpEvent& rHEvt )
{
    if ( !m_pActionListener )
    {
        SvTreeListBox::RequestHelp( rHEvt );
        return;
    }

    if( rHEvt.GetMode() & HELPMODE_QUICK )
    {
        Point aPos( ScreenToOutputPixel( rHEvt.GetMousePosPixel() ));
        SvLBoxEntry* pEntry = GetEntry( aPos );
        if( pEntry )
        {
            String sQuickHelpText;
            if ( m_pActionListener->requestQuickHelp( pEntry, sQuickHelpText ) )
            {
                Size aSize( GetOutputSizePixel().Width(), GetEntryHeight() );
                Rectangle aScreenRect( OutputToScreenPixel( GetEntryPosition( pEntry ) ), aSize );

                Help::ShowQuickHelp( this, aScreenRect,
                                     sQuickHelpText, QUICKHELP_LEFT | QUICKHELP_VCENTER );
                return;
            }
        }
    }

    SvTreeListBox::RequestHelp( rHEvt );
}

// -----------------------------------------------------------------------------
void DBTreeListBox::KeyInput( const KeyEvent& rKEvt )
{
    KeyFuncType eFunc = rKEvt.GetKeyCode().GetFunction();
    USHORT		nCode = rKEvt.GetKeyCode().GetCode();
    sal_Bool bHandled = sal_False;

    if(eFunc != KEYFUNC_DONTKNOW)
    {
        switch(eFunc)
        {
            case KEYFUNC_CUT:
                bHandled = (m_aCutHandler.IsSet() && m_pSelectedEntry);
                if ( bHandled )
                    m_aCutHandler.Call(m_pSelectedEntry);
                break;
            case KEYFUNC_COPY:
                bHandled = (m_aCopyHandler.IsSet() && m_pSelectedEntry);
                if ( bHandled )
                    m_aCopyHandler.Call(m_pSelectedEntry);
                break;
            case KEYFUNC_PASTE:
                bHandled = (m_aPasteHandler.IsSet() && m_pSelectedEntry);
                if ( bHandled )
                    m_aPasteHandler.Call(m_pSelectedEntry);
                break;
            case KEYFUNC_DELETE:
                bHandled = (m_aDeleteHandler.IsSet() && m_pSelectedEntry);
                if ( bHandled )
                    m_aDeleteHandler.Call(m_pSelectedEntry);
                break;
            default:
                break;
        }
    }

    if ( KEY_RETURN == nCode )
    {
        bHandled = m_bHandleEnterKey;
        if ( m_aEnterKeyHdl.IsSet() )
            m_aEnterKeyHdl.Call(this);
        // this is a HACK. If the data source browser is opened in the "beamer", while the main frame
        // contains a writer document, then pressing enter in the DSB would be rerouted to the writer
        // document if we would not do this hack here.
        // The problem is that the Writer uses RETURN as _accelerator_ (which is quite weird itself),
        // so the SFX framework is _obligated_ to pass it to the Writer if nobody else handled it. There
        // is no chance to distinguish between
        //   "accelerators which are to be executed if the main document has the focus"
        // and
        //   "accelerators which are always to be executed"
        //
        // Thus we cannot prevent the handling of this key in the writer without declaring the key event
        // as "handled" herein.
        //
        // The bad thing about this approach is that it does not scale. Every other accelerator which
        // is used by the document will raise a similar bug once somebody discovers it.
        // If this is the case, we should discuss a real solution with the framework (SFX) and the
        // applications.
        //
        // 2002-12-02 - 105831 - fs@openoffice.org
    }

    if ( !bHandled ) 
        SvTreeListBox::KeyInput(rKEvt);
}
// -----------------------------------------------------------------------------
BOOL DBTreeListBox::EditingEntry( SvLBoxEntry* pEntry, Selection& /*_aSelection*/)
{
    return m_aEditingHandler.Call(pEntry) != 0;
}
// -----------------------------------------------------------------------------
BOOL DBTreeListBox::EditedEntry( SvLBoxEntry* pEntry, const XubString& rNewText )
{
    DBTreeEditedEntry aEntry;
    aEntry.pEntry = pEntry;
    aEntry.aNewText  =rNewText;
    if(m_aEditedHandler.Call(&aEntry) != 0)
    {
        if(m_aTimer.IsActive())
            m_aTimer.Stop();
        m_pSelectedEntry = NULL; // to force that the renamed selection will be reselected
    }
    SetEntryText(pEntry,aEntry.aNewText);
    
    return FALSE;  // we never want that the base change our text
}

// -----------------------------------------------------------------------------
BOOL DBTreeListBox::DoubleClickHdl()
{
    long nResult = aDoubleClickHdl.Call( this );
    // continue default processing if the DoubleClickHandler didn't handle it
    return nResult == 0;
}

// -----------------------------------------------------------------------------
void scrollWindow(DBTreeListBox* _pListBox, const Point& _rPos,sal_Bool _bUp)
{
    SvLBoxEntry* pEntry = _pListBox->GetEntry( _rPos );
    if( pEntry && pEntry != _pListBox->Last() )
    {
        _pListBox->ScrollOutputArea( _bUp ? -1 : 1 );
    }
}
// -----------------------------------------------------------------------------
IMPL_LINK( DBTreeListBox, ScrollUpHdl, SvTreeListBox*, /*pBox*/ )
{
    scrollWindow(this,m_aMousePos,sal_True);
    return 0;
}

//------------------------------------------------------------------------------
IMPL_LINK( DBTreeListBox, ScrollDownHdl, SvTreeListBox*, /*pBox*/ )
{
    scrollWindow(this,m_aMousePos,sal_False);
    return 0;
}
// -----------------------------------------------------------------------------
namespace
{
    void lcl_enableEntries( PopupMenu* _pPopup, IController& _rController )
    {
        if ( !_pPopup )
            return;

        USHORT nCount = _pPopup->GetItemCount();
        for (USHORT i=0; i < nCount; ++i)
        {
            if ( _pPopup->GetItemType(i) != MENUITEM_SEPARATOR )
            {
                USHORT nId = _pPopup->GetItemId(i);
                PopupMenu* pSubPopUp = _pPopup->GetPopupMenu(nId);
                if ( pSubPopUp )
                {
                    lcl_enableEntries( pSubPopUp, _rController );
                    _pPopup->EnableItem(nId,pSubPopUp->HasValidEntries());
                }
                else
                {
                    ::rtl::OUString sCommandURL( _pPopup->GetItemCommand( nId ) );
                    bool bEnabled = ( sCommandURL.getLength() )
                                  ? _rController.isCommandEnabled( sCommandURL )
                                  : _rController.isCommandEnabled( nId );
                    _pPopup->EnableItem( nId, bEnabled );
                }
            }
        }

        _pPopup->RemoveDisabledEntries();
    }
}

// -----------------------------------------------------------------------------
namespace
{
    void lcl_adjustMenuItemIDs( Menu& _rMenu, IController& _rCommandController )
    {
        USHORT nCount = _rMenu.GetItemCount();
        for ( USHORT pos = 0; pos < nCount; ++pos )
        {
            USHORT nId = _rMenu.GetItemId(pos);
            String aCommand = _rMenu.GetItemCommand( nId );
            PopupMenu* pPopup = _rMenu.GetPopupMenu( nId );
            if ( pPopup )
            {
                lcl_adjustMenuItemIDs( *pPopup, _rCommandController );
                continue;
            }

            USHORT nCommandId = _rCommandController.registerCommandURL( aCommand );
            _rMenu.InsertItem( nCommandId, _rMenu.GetItemText( nId ), _rMenu.GetItemBits( nId ), pos );
            _rMenu.RemoveItem( pos+1 );
        }
    }
    // =========================================================================
    // = SelectionSupplier
    // =========================================================================
    typedef ::cppu::WeakImplHelper1 <   XSelectionSupplier
                                    >   SelectionSupplier_Base;
    class SelectionSupplier : public SelectionSupplier_Base
    {
    public:
        SelectionSupplier( const Any& _rSelection )
            :m_aSelection( _rSelection )
        {
        }

        virtual ::sal_Bool SAL_CALL select( const Any& xSelection ) throw (IllegalArgumentException, RuntimeException);
        virtual Any SAL_CALL getSelection(  ) throw (RuntimeException);
        virtual void SAL_CALL addSelectionChangeListener( const Reference< XSelectionChangeListener >& xListener ) throw (RuntimeException);
        virtual void SAL_CALL removeSelectionChangeListener( const Reference< XSelectionChangeListener >& xListener ) throw (RuntimeException);

    protected:
        virtual ~SelectionSupplier()
        {
        }

    private:
        Any m_aSelection;
    };

    //--------------------------------------------------------------------
    ::sal_Bool SAL_CALL SelectionSupplier::select( const Any& /*_Selection*/ ) throw (IllegalArgumentException, RuntimeException)
    {
        throw IllegalArgumentException();
        // API bug: this should be a NoSupportException
    }
    
    //--------------------------------------------------------------------
    Any SAL_CALL SelectionSupplier::getSelection(  ) throw (RuntimeException)
    {
        return m_aSelection;
    }
    
    //--------------------------------------------------------------------
    void SAL_CALL SelectionSupplier::addSelectionChangeListener( const Reference< XSelectionChangeListener >& /*_Listener*/ ) throw (RuntimeException)
    {
        OSL_ENSURE( false, "SelectionSupplier::removeSelectionChangeListener: no support!" );
        // API bug: this should be a NoSupportException
    }
    
    //--------------------------------------------------------------------
    void SAL_CALL SelectionSupplier::removeSelectionChangeListener( const Reference< XSelectionChangeListener >& /*_Listener*/ ) throw (RuntimeException)
    {
        OSL_ENSURE( false, "SelectionSupplier::removeSelectionChangeListener: no support!" );
        // API bug: this should be a NoSupportException
    }
}

// -----------------------------------------------------------------------------
PopupMenu* DBTreeListBox::CreateContextMenu( void )
{
    ::std::auto_ptr< PopupMenu > pContextMenu;

    if ( !m_pContextMenuProvider )
        return pContextMenu.release();

    // the basic context menu
    pContextMenu.reset( m_pContextMenuProvider->getContextMenu( *this ) );
    // disable what is not available currently
    lcl_enableEntries( pContextMenu.get(), m_pContextMenuProvider->getCommandController() );
    // allow context menu interception
    ::cppu::OInterfaceContainerHelper* pInterceptors = m_pContextMenuProvider->getContextMenuInterceptors();
    if ( !pInterceptors || !pInterceptors->getLength() )
        return pContextMenu.release();

    ContextMenuExecuteEvent aEvent;
    aEvent.SourceWindow = VCLUnoHelper::GetInterface( this );
    aEvent.ExecutePosition.X = -1;
    aEvent.ExecutePosition.Y = -1;
    aEvent.ActionTriggerContainer = ::framework::ActionTriggerHelper::CreateActionTriggerContainerFromMenu(
        m_xORB, pContextMenu.get() );
    aEvent.Selection = new SelectionSupplier( m_pContextMenuProvider->getCurrentSelection( *this ) );

    ::cppu::OInterfaceIteratorHelper aIter( *pInterceptors );
    bool bModifiedMenu = false;
    bool bAskInterceptors = true;
    while ( aIter.hasMoreElements() && bAskInterceptors )
    {
        Reference< XContextMenuInterceptor > xInterceptor( aIter.next(), UNO_QUERY );
        if ( !xInterceptor.is() )
            continue;

        try
        {
            ContextMenuInterceptorAction eAction = xInterceptor->notifyContextMenuExecute( aEvent );
            switch ( eAction )
            {
                case ContextMenuInterceptorAction_CANCELLED:
                    return NULL;

                case ContextMenuInterceptorAction_EXECUTE_MODIFIED:
                    bModifiedMenu = true;
                    bAskInterceptors = false;
                    break;

                case ContextMenuInterceptorAction_CONTINUE_MODIFIED:
                    bModifiedMenu = true;
                    bAskInterceptors = true;
                    break;

                default:
                    DBG_ERROR( "DBTreeListBox::CreateContextMenu: unexpected return value of the interceptor call!" );

                case ContextMenuInterceptorAction_IGNORED:
                    break;
            }
        }
        catch( const DisposedException& e )
        {
            if ( e.Context == xInterceptor )
                aIter.remove();
        }
    }

    if ( bModifiedMenu )
    {
        // the interceptor(s) modified the menu description => create a new PopupMenu
        PopupMenu* pModifiedMenu = new PopupMenu;
        ::framework::ActionTriggerHelper::CreateMenuFromActionTriggerContainer(
            pModifiedMenu, aEvent.ActionTriggerContainer );
        aEvent.ActionTriggerContainer.clear();
        pContextMenu.reset( pModifiedMenu );

        // the interceptors only know command URLs, but our menus primarily work
        // with IDs -> we need to translate the commands to IDs
        lcl_adjustMenuItemIDs( *pModifiedMenu, m_pContextMenuProvider->getCommandController() );
    }

    return pContextMenu.release();
}

// -----------------------------------------------------------------------------
void DBTreeListBox::ExcecuteContextMenuAction( USHORT _nSelectedPopupEntry )
{
    if ( m_pContextMenuProvider )
        m_pContextMenuProvider->getCommandController().executeChecked( _nSelectedPopupEntry, Sequence< PropertyValue >() );
}

// -----------------------------------------------------------------------------
IMPL_LINK(DBTreeListBox, OnTimeOut, void*, /*EMPTY_ARG*/)
{
    if(m_aTimer.IsActive())
        m_aTimer.Stop();
    if (m_pSelectedEntry)
        aSelectHdl.Call( m_pSelectedEntry );	
    return 0L;
}
// -----------------------------------------------------------------------------
void DBTreeListBox::StateChanged( StateChangedType nStateChange )
{
    if ( nStateChange == STATE_CHANGE_VISIBLE && m_aTimer.IsActive() )
        m_aTimer.Stop();
}
// .........................................................................
}	// namespace dbaui
// .........................................................................
