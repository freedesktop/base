/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: GroupsSorting.cxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: hr $ $Date: 2007-08-02 14:36:30 $
 *
 *  The Contents of this file are made available subject to
 *  the terms of GNU Lesser General Public License Version 2.1.
 *
 *
 *    GNU Lesser General Public License Version 2.1
 *    =============================================
 *    Copyright 2005 by Sun Microsystems, Inc.
 *    901 San Antonio Road, Palo Alto, CA 94303, USA
 *
 *    This library is free software; you can redistribute it and/or
 *    modify it under the terms of the GNU Lesser General Public
 *    License version 2.1, as published by the Free Software Foundation.
 *
 *    This library is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *    Lesser General Public License for more details.
 *
 *    You should have received a copy of the GNU Lesser General Public
 *    License along with this library; if not, write to the Free Software
 *    Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 *    MA  02111-1307  USA
 *
 ************************************************************************/
#include "precompiled_reportdesign.hxx"

#ifndef RPTUI_GROUPS_SORTING_HXX
#include "GroupsSorting.hxx"
#endif
#ifndef RPTUI_GROUPSSORTING_HRC
#include "GroupsSorting.hrc"
#endif
#ifndef _CONNECTIVITY_DBTOOLS_HXX_
#include <connectivity/dbtools.hxx>
#endif
#ifndef _SVTOOLS_EDITBROWSEBOX_HXX_
#include <svtools/editbrowsebox.hxx>
#endif
#ifndef _COM_SUN_STAR_BEANS_XPROPERTYSET_HPP_
#include <com/sun/star/beans/XPropertySet.hpp>
#endif
#ifndef _COM_SUN_STAR_SDBC_DATATYPE_HPP_
#include <com/sun/star/sdbc/DataType.hpp>
#endif
#ifndef _TOOLS_DEBUG_HXX
#include <tools/debug.hxx>
#endif
#ifndef _RPTUI_DLGRESID_HRC
#include "RptResId.hrc"
#endif
#ifndef _RPTUI_SLOTID_HRC_
#include "rptui_slotid.hrc"
#endif
#ifndef _RPTUI_MODULE_HELPER_DBU_HXX_
#include "ModuleHelper.hxx"
#endif
#ifndef RTPUI_REPORTDESIGN_HELPID_HRC
#include "helpids.hrc"
#endif
#ifndef _SV_MSGBOX_HXX
#include <vcl/msgbox.hxx>
#endif
#ifndef _GLOBLMN_HRC
#include <svx/globlmn.hrc>
#endif
#ifndef _SBASLTID_HRC
#include <svx/svxids.hrc>
#endif
#ifndef _COM_SUN_STAR_REPORT_GROUPON_HPP_
#include <com/sun/star/report/GroupOn.hpp>
#endif
#ifndef RPTUI_GROUP_EXCHANGE_HXX
#include "GroupExchange.hxx"
#endif
#ifndef RPTUI_TOOLS_HXX
#include "UITools.hxx"
#endif
#ifndef REPORTDESIGN_SHARED_UISTRINGS_HRC
#include "uistrings.hrc"
#endif
#ifndef RPTUI_REPORTCONTROLLER_HXX
#include "ReportController.hxx"
#endif
#ifndef _COM_SUN_STAR_CONTAINER_XCONTAINERLISTENER_HPP_
#include <com/sun/star/container/XContainerListener.hpp>
#endif
#ifndef _CPPUHELPER_IMPLBASE1_HXX_
#include <cppuhelper/implbase1.hxx>
#endif
#ifndef _COMPHELPER_PROPERTY_HXX_
#include <comphelper/property.hxx>
#endif
#ifndef _SV_MNEMONIC_HXX
#include <vcl/mnemonic.hxx>
#endif
#include <algorithm>
#include <boost/bind.hpp>

#define HANDLE_ID			0
#define FIELD_EXPRESSION	1
#define GROUPS_START_LEN	5
#define NO_GROUP            -1

namespace rptui
{
using namespace ::com::sun::star;
using namespace svt;
using namespace ::comphelper;

typedef ::svt::EditBrowseBox OFieldExpressionControl_Base;
typedef ::cppu::WeakImplHelper1< container::XContainerListener > TContainerListenerBase;
class OFieldExpressionControl : public TContainerListenerBase
                               ,public OFieldExpressionControl_Base
{
    ::osl::Mutex                    m_aMutex;
    ::std::vector<sal_Int32>        m_aGroupPositions;
    ::svt::ComboBoxControl*			m_pComboCell;
    sal_Int32						m_nDataPos;
    sal_Int32						m_nCurrentPos;
    ULONG							m_nPasteEvent;
    ULONG							m_nDeleteEvent;
    OGroupsSortingDialog*			m_pParent;
    bool                            m_bIgnoreEvent;


    void fillListBox(const uno::Reference< beans::XPropertySet>& _xDest,long nRow,USHORT nColumnId);
    BOOL SaveModified(bool _bAppend);

    OFieldExpressionControl(const OFieldExpressionControl&);
    void operator =(const OFieldExpressionControl&);
public:
    OFieldExpressionControl( OGroupsSortingDialog* _pParent,const ResId& _rResId);
    virtual ~OFieldExpressionControl();

    // XEventListener
    virtual void SAL_CALL disposing(const ::com::sun::star::lang::EventObject& Source) throw( ::com::sun::star::uno::RuntimeException );
    // XContainerListener
    virtual void SAL_CALL elementInserted(const ::com::sun::star::container::ContainerEvent& rEvent) throw(::com::sun::star::uno::RuntimeException);
    virtual void SAL_CALL elementReplaced(const ::com::sun::star::container::ContainerEvent& rEvent) throw(::com::sun::star::uno::RuntimeException);
    virtual void SAL_CALL elementRemoved(const ::com::sun::star::container::ContainerEvent& rEvent) throw(::com::sun::star::uno::RuntimeException);

    void		fillColumns(const uno::Reference< container::XNameAccess>& _xColumns);
    void		lateInit();
    sal_Bool	IsDeleteAllowed( );
    void		DeleteRows();
    void		cut();
    void		copy();
    void		paste();

    inline sal_Int32   getGroupPosition(sal_Int32 _nRow) const { return _nRow != BROWSER_ENDOFSELECTION ? m_aGroupPositions[_nRow] : sal_Int32(NO_GROUP); }

    inline ::svt::ComboBoxControl*	getExpressionControl() const { return m_pComboCell; }

    
    /** returns the sequence with the selected groups
    */
    uno::Sequence<uno::Any> fillSelectedGroups();

    /** move groups given by _aGroups
    */
    void moveGroups(const uno::Sequence<uno::Any>& _aGroups,sal_Int32 _nRow,sal_Bool _bSelect = sal_True);

    virtual BOOL CursorMoving(long nNewRow, USHORT nNewCol);
    using OFieldExpressionControl_Base::GetRowCount;
protected:
    virtual BOOL IsTabAllowed(BOOL bForward) const;
    

    virtual void InitController( ::svt::CellControllerRef& rController, long nRow, USHORT nCol );
    virtual ::svt::CellController* GetController( long nRow, USHORT nCol );
    virtual void PaintCell( OutputDevice& rDev, const Rectangle& rRect, USHORT nColId ) const;
    virtual BOOL SeekRow( long nRow );
    virtual BOOL SaveModified();
    virtual String GetCellText( long nRow, USHORT nColId ) const;
    virtual RowStatus GetRowStatus(long nRow) const;

    virtual void KeyInput(const KeyEvent& rEvt);
    virtual void Command( const CommandEvent& rEvt );

    // D&D
    virtual void	 StartDrag( sal_Int8 nAction, const Point& rPosPixel );
    virtual sal_Int8 AcceptDrop( const BrowserAcceptDropEvent& rEvt );
    virtual sal_Int8 ExecuteDrop( const BrowserExecuteDropEvent& rEvt );

    using BrowseBox::AcceptDrop;
    using BrowseBox::ExecuteDrop;

private:

    DECL_LINK( AsynchActivate, void* );
    DECL_LINK( AsynchDeactivate, void* );
    DECL_LINK( DelayedPaste, void* );
    DECL_LINK( DelayedDelete, void* );
    DECL_LINK( CBChangeHdl,ComboBox*);

    void InsertRows( long nRow );
};
//========================================================================
// class OFieldExpressionControl
//========================================================================
DBG_NAME( rpt_OFieldExpressionControl )
//------------------------------------------------------------------------
OFieldExpressionControl::OFieldExpressionControl( OGroupsSortingDialog* _pParent,const ResId& _rResId )
    :EditBrowseBox( _pParent, _rResId,EBBF_NONE, WB_TABSTOP | BROWSER_COLUMNSELECTION | BROWSER_MULTISELECTION | BROWSER_AUTOSIZE_LASTCOL |
                                  BROWSER_KEEPSELECTION | BROWSER_HLINESFULL | BROWSER_VLINESFULL)
    ,m_aGroupPositions(GROUPS_START_LEN,-1)
    ,m_pComboCell(NULL)
    ,m_nDataPos(-1)
    ,m_nCurrentPos(-1)
    ,m_nPasteEvent(0)
    ,m_nDeleteEvent(0)
    ,m_pParent(_pParent)
    ,m_bIgnoreEvent(false)
{
    DBG_CTOR( rpt_OFieldExpressionControl,NULL);
    SetBorderStyle(WINDOW_BORDER_MONO);
}

//------------------------------------------------------------------------
OFieldExpressionControl::~OFieldExpressionControl()
{
    acquire();
    uno::Reference< report::XGroups > xGroups = m_pParent->getGroups();
    xGroups->removeContainerListener(this);
    //////////////////////////////////////////////////////////////////////
    // delete events from queue
    if( m_nPasteEvent )
        Application::RemoveUserEvent( m_nPasteEvent );
    if( m_nDeleteEvent )
        Application::RemoveUserEvent( m_nDeleteEvent );

    delete m_pComboCell;
    DBG_DTOR( rpt_OFieldExpressionControl,NULL);
}
//------------------------------------------------------------------------------
uno::Sequence<uno::Any> OFieldExpressionControl::fillSelectedGroups()
{
    uno::Sequence<uno::Any> aList;
    ::std::vector<uno::Any> vClipboardList;
    vClipboardList.reserve(GetSelectRowCount());

    uno::Reference<report::XGroups> xGroups = m_pParent->getGroups();
    sal_Int32 nCount = xGroups->getCount();
    if ( nCount >= 1 )
    {
        for( long nIndex=FirstSelectedRow(); nIndex >= 0 ; nIndex=NextSelectedRow() )
        {
            try
            {
                if ( m_aGroupPositions[nIndex] != NO_GROUP )
                {
                    uno::Reference< report::XGroup> xOrgGroup(xGroups->getByIndex(m_aGroupPositions[nIndex]),uno::UNO_QUERY);
                    /*uno::Reference< report::XGroup> xCopy = xGroups->createGroup();
                    ::comphelper::copyProperties(xOrgGroup.get(),xCopy.get());*/
                    vClipboardList.push_back( uno::makeAny(xOrgGroup) );
                }
            }
            catch(uno::Exception&)
            {
                OSL_ENSURE(0,"Can not access group!");
            }
        }
        if ( !vClipboardList.empty() )
            aList = uno::Sequence< uno::Any >(&vClipboardList[0], vClipboardList.size());
    } // if ( nCount > 1 )
    return aList;
}
//------------------------------------------------------------------------------
void OFieldExpressionControl::StartDrag( sal_Int8 /*_nAction*/ , const Point& /*_rPosPixel*/ )
{
    DBG_CHKTHIS( rpt_OFieldExpressionControl,NULL);
    if ( m_pParent && !m_pParent->isReadOnly( ) )
    {
        uno::Sequence<uno::Any> aClipboardList = fillSelectedGroups();

        if( aClipboardList.getLength() )
        {
            OGroupExchange* pData = new OGroupExchange(aClipboardList);
            uno::Reference< ::com::sun::star::datatransfer::XTransferable> xRef = pData;
            pData->StartDrag(this, DND_ACTION_MOVE );
        } // if(!vClipboardList.empty())
    }
}
//------------------------------------------------------------------------------
sal_Int8 OFieldExpressionControl::AcceptDrop( const BrowserAcceptDropEvent& rEvt )
{
    DBG_CHKTHIS( rpt_OFieldExpressionControl,NULL);
    sal_Int8 nAction = DND_ACTION_NONE;
    if ( IsDropFormatSupported( OGroupExchange::getReportGroupId() ) && m_pParent->getGroups()->getCount() > 1 && rEvt.GetWindow() == &GetDataWindow() )
    {
        nAction = DND_ACTION_MOVE;
    }
    return nAction;
}
//------------------------------------------------------------------------------
sal_Int8 OFieldExpressionControl::ExecuteDrop( const BrowserExecuteDropEvent& rEvt )
{
    DBG_CHKTHIS( rpt_OFieldExpressionControl,NULL);
    sal_Int8 nAction = DND_ACTION_NONE;
    if ( IsDropFormatSupported( OGroupExchange::getReportGroupId() ) )
    {		
        sal_Int32	nRow = GetRowAtYPosPixel(rEvt.maPosPixel.Y(), sal_False);
        SetNoSelection();

        TransferableDataHelper aDropped( rEvt.maDropEvent.Transferable );
        uno::Any aDrop = aDropped.GetAny(OGroupExchange::getReportGroupId());
        uno::Sequence< uno::Any > aGroups;
        aDrop >>= aGroups;
        if ( aGroups.getLength() )
        {
            moveGroups(aGroups,nRow);
            nAction = DND_ACTION_MOVE;
        }
    }
    return nAction;
}
//------------------------------------------------------------------------------
void OFieldExpressionControl::moveGroups(const uno::Sequence<uno::Any>& _aGroups,sal_Int32 _nRow,sal_Bool _bSelect)
{
    if ( _aGroups.getLength() )
    {
        m_bIgnoreEvent = true;
        sal_Int32 nRow = _nRow;
        String sUndoAction(String(ModuleRes(RID_STR_UNDO_MOVE_GROUP)));
        m_pParent->m_pController->getUndoMgr()->EnterListAction( sUndoAction, String() );

        uno::Reference< report::XGroups> xGroups = m_pParent->getGroups();
        const uno::Any* pIter = _aGroups.getConstArray();
        const uno::Any* pEnd  = pIter + _aGroups.getLength();
        for(;pIter != pEnd;++pIter)
        {
            uno::Reference< report::XGroup> xGroup(*pIter,uno::UNO_QUERY);
            if ( xGroup.is() )
            {					
                uno::Sequence< beans::PropertyValue > aArgs(1);
                aArgs[0].Name = PROPERTY_GROUP;
                aArgs[0].Value <<= xGroup;
                // we use this way to create undo actions
                m_pParent->m_pController->executeChecked(SID_GROUP_REMOVE,aArgs);
                aArgs.realloc(2);
                if ( nRow > xGroups->getCount() )
                    nRow = xGroups->getCount();
                if ( _bSelect )
                    SelectRow(nRow);
                aArgs[1].Name = PROPERTY_POSITIONY;
                aArgs[1].Value <<= nRow;
                m_pParent->m_pController->executeChecked(SID_GROUP_APPEND,aArgs);
                ++nRow;
            }
        } // for(;pIter != pEnd;++pIter)
        m_pParent->m_pController->getUndoMgr()->LeaveListAction();
        m_bIgnoreEvent = false;
        Invalidate();
    } // if ( _aGroups.getLength() )
}
// -----------------------------------------------------------------------------
void OFieldExpressionControl::fillColumns(const uno::Reference< container::XNameAccess>& _xColumns)
{
    m_pComboCell->Clear();
    if ( _xColumns.is() )
    {
        uno::Sequence< ::rtl::OUString> aColumnNames = _xColumns->getElementNames();
        const ::rtl::OUString* pIter = aColumnNames.getConstArray();
        const ::rtl::OUString* pEnd	  = pIter + aColumnNames.getLength();
        for(;pIter != pEnd;++pIter)
            m_pComboCell->InsertEntry(*pIter);
    } // if ( _xColumns.is() )
}
//------------------------------------------------------------------------------
void OFieldExpressionControl::lateInit()
{
    uno::Reference< report::XGroups > xGroups = m_pParent->getGroups();
    sal_Int32 nGroupsCount = xGroups->getCount();
    m_aGroupPositions.resize(::std::max<sal_Int32>(nGroupsCount,sal_Int32(GROUPS_START_LEN)),NO_GROUP);
    ::std::vector<sal_Int32>::iterator aIter = m_aGroupPositions.begin();
    for (sal_Int32 i = 0; i < nGroupsCount; ++i,++aIter)
        *aIter = i;

    if ( ColCount() == 0 )
    {
        Font aFont( GetDataWindow().GetFont() );
        aFont.SetWeight( WEIGHT_NORMAL );
        GetDataWindow().SetFont( aFont );

        // Font fuer die Ueberschriften auf Light setzen
        aFont = GetFont();
        aFont.SetWeight( WEIGHT_LIGHT );
        SetFont(aFont);

        InsertHandleColumn(static_cast<USHORT>(GetTextWidth('0') * 4)/*, TRUE */);
        InsertDataColumn( FIELD_EXPRESSION, String(ModuleRes(STR_RPT_EXPRESSION)), 100);

        m_pComboCell = new ComboBoxControl( &GetDataWindow() );
        m_pComboCell->SetSelectHdl(LINK(this,OFieldExpressionControl,CBChangeHdl));
        m_pComboCell->SetHelpId(HID_FIELDEXPRESSION);

        Control* pControls[] = {m_pComboCell};
        for (size_t i = 0; i < sizeof(pControls)/sizeof(pControls[0]); ++i)
        {
            pControls[i]->SetGetFocusHdl(LINK(m_pParent, OGroupsSortingDialog, OnControlFocusGot));
            pControls[i]->SetLoseFocusHdl(LINK(m_pParent, OGroupsSortingDialog, OnControlFocusLost));
        }

        //////////////////////////////////////////////////////////////////////
        // set browse mode
        BrowserMode nMode(BROWSER_COLUMNSELECTION | BROWSER_MULTISELECTION	| BROWSER_KEEPSELECTION |
                          BROWSER_HLINESFULL | BROWSER_VLINESFULL		| BROWSER_AUTOSIZE_LASTCOL | BROWSER_AUTO_VSCROLL | BROWSER_AUTO_HSCROLL);
        if( m_pParent->isReadOnly() )
            nMode |= BROWSER_HIDECURSOR;
        SetMode(nMode);
        xGroups->addContainerListener(this);
    }
    else
        // not the first call
        RowRemoved(0, GetRowCount());

    RowInserted(0, m_aGroupPositions.size(), TRUE);
}
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
IMPL_LINK( OFieldExpressionControl, CBChangeHdl, ComboBox*, /*pComboBox*/ )
{
    DBG_CHKTHIS( rpt_OFieldExpressionControl,NULL);

    SaveModified();
    return 0L;
}
//------------------------------------------------------------------------------
IMPL_LINK(OFieldExpressionControl, AsynchActivate, void*, EMPTYARG)
{
    ActivateCell();
    return 0L;
}

//------------------------------------------------------------------------------
IMPL_LINK(OFieldExpressionControl, AsynchDeactivate, void*, EMPTYARG)
{
    DeactivateCell();
    return 0L;
}

//------------------------------------------------------------------------------
BOOL OFieldExpressionControl::IsTabAllowed(BOOL /*bForward*/) const
{
    DBG_CHKTHIS( rpt_OFieldExpressionControl,NULL);
    return FALSE;
}

//------------------------------------------------------------------------------
BOOL OFieldExpressionControl::SaveModified()
{
    return SaveModified(true);
}
//------------------------------------------------------------------------------
BOOL OFieldExpressionControl::SaveModified(bool _bAppendRow)
{
    DBG_CHKTHIS( rpt_OFieldExpressionControl,NULL);
    sal_Int32 nRow = GetCurRow();
    if ( nRow != BROWSER_ENDOFSELECTION )
    {
        sal_Bool bAppend = sal_False;
        try
        {
            uno::Reference< report::XGroup> xGroup;
            if ( m_aGroupPositions[nRow] == NO_GROUP )
            {
                bAppend = sal_True;
                String sUndoAction(String(ModuleRes(RID_STR_UNDO_APPEND_GROUP)));
                m_pParent->m_pController->getUndoMgr()->EnterListAction( sUndoAction, String() );
                xGroup = m_pParent->getGroups()->createGroup();
                xGroup->setHeaderOn(sal_True);

                uno::Sequence< beans::PropertyValue > aArgs(2);
                aArgs[0].Name = PROPERTY_GROUP;
                aArgs[0].Value <<= xGroup;
                // find position where to insert the new group
                sal_Int32 nGroupPos = 0;
                ::std::vector<sal_Int32>::iterator aIter = m_aGroupPositions.begin();
                ::std::vector<sal_Int32>::iterator aEnd  = m_aGroupPositions.begin() + nRow;
                for(;aIter != aEnd;++aIter)
                    if ( *aIter != NO_GROUP )
                        nGroupPos = *aIter + 1;
                aArgs[1].Name = PROPERTY_POSITIONY;
                aArgs[1].Value <<= nGroupPos;
                m_bIgnoreEvent = true;
                m_pParent->m_pController->executeChecked(SID_GROUP_APPEND,aArgs);
                m_bIgnoreEvent = false;
                OSL_ENSURE(*aIter == NO_GROUP ,"Illegal iterator!");
                *aIter++ = nGroupPos;

                aEnd  = m_aGroupPositions.end();
                for(;aIter != aEnd;++aIter)
                    if ( *aIter != NO_GROUP )
                        ++*aIter;
            }
            else
                xGroup = m_pParent->getGroup(m_aGroupPositions[nRow]);
            if ( xGroup.is() )
            {			
                USHORT nPos = m_pComboCell->GetSelectEntryPos();
                ::rtl::OUString sExpression;
                if ( COMBOBOX_ENTRY_NOTFOUND == nPos )
                    sExpression = m_pComboCell->GetText();
                else
                {
                    sExpression = m_pComboCell->GetEntry(nPos);
                }
                xGroup->setExpression( sExpression );

                ::rptui::adjustSectionName(xGroup,nPos);
                
                if ( bAppend )
                    m_pParent->m_pController->getUndoMgr()->LeaveListAction();
            }

            if ( Controller() )
                Controller()->ClearModified();
            if ( _bAppendRow && GetRowCount() == m_pParent->getGroups()->getCount() )
            {
                RowInserted( GetRowCount()-1);
                m_aGroupPositions.push_back(NO_GROUP);
            }

            GoToRow(nRow);
            m_pParent->DisplayData(nRow);
        }
        catch(uno::Exception&)
        {
            OSL_ENSURE(0,"OFieldExpressionControl::SaveModified: Exception caught!");
        }
    }

    return TRUE;
}
//------------------------------------------------------------------------------
String OFieldExpressionControl::GetCellText( long nRow, USHORT /*nColId*/ ) const
{
    DBG_CHKTHIS( rpt_OFieldExpressionControl,NULL);
    String sText;
    if ( nRow != BROWSER_ENDOFSELECTION && m_aGroupPositions[nRow] != NO_GROUP )
    {
        try
        {
            uno::Reference< report::XGroup> xGroup = m_pParent->getGroup(m_aGroupPositions[nRow]);
            sText  = xGroup->getExpression();
        }
        catch(uno::Exception&)
        {
            OSL_ENSURE(0,"Exception caught while getting expression value from the group");
        }
    } // if ( nRow != BROWSER_ENDOFSELECTION && nRow < m_pParent->getGroups()->getCount() )
    return sText;
}

//------------------------------------------------------------------------------
void OFieldExpressionControl::InitController( CellControllerRef& /*rController*/, long nRow, USHORT nColumnId )
{
    DBG_CHKTHIS( rpt_OFieldExpressionControl,NULL);

    m_pComboCell->SetText( GetCellText( nRow, nColumnId ) );
}
//------------------------------------------------------------------------------
sal_Bool OFieldExpressionControl::CursorMoving(long nNewRow, sal_uInt16 nNewCol)
{
    DBG_CHKTHIS( rpt_OFieldExpressionControl,NULL);

    if (!EditBrowseBox::CursorMoving(nNewRow, nNewCol))
        return sal_False;
    m_nDataPos = nNewRow;
    long nOldDataPos = GetCurRow();
    InvalidateStatusCell( m_nDataPos );
    InvalidateStatusCell( nOldDataPos );

    m_pParent->SaveData( nOldDataPos );
    m_pParent->DisplayData( m_nDataPos );
    return sal_True;
}
//------------------------------------------------------------------------------
CellController* OFieldExpressionControl::GetController( long /*nRow*/, USHORT /*nColumnId*/ )
{
    DBG_CHKTHIS( rpt_OFieldExpressionControl,NULL);
    ComboBoxCellController* pCellController = new ComboBoxCellController( m_pComboCell );
    pCellController->GetComboBox().SetReadOnly(!m_pParent->m_pController->isEditable());
    return pCellController;
}

//------------------------------------------------------------------------------
BOOL OFieldExpressionControl::SeekRow( long _nRow )
{
    DBG_CHKTHIS( rpt_OFieldExpressionControl,NULL);
    // die Basisklasse braucht den Aufruf, da sie sich dort merkt, welche Zeile gepainted wird
    EditBrowseBox::SeekRow(_nRow);
    m_nCurrentPos = _nRow;
    return TRUE;
}

//------------------------------------------------------------------------------
void OFieldExpressionControl::PaintCell( OutputDevice& rDev, const Rectangle& rRect, USHORT nColumnId ) const
{
    DBG_CHKTHIS( rpt_OFieldExpressionControl,NULL);
    String aText  =const_cast< OFieldExpressionControl*>(this)->GetCellText( m_nCurrentPos, nColumnId );

    Point aPos( rRect.TopLeft() );			
    Size aTextSize( GetDataWindow().GetTextHeight(),GetDataWindow().GetTextWidth( aText ));

    if( aPos.X() < rRect.Right() || aPos.X() + aTextSize.Width() > rRect.Right() ||
        aPos.Y() < rRect.Top() || aPos.Y() + aTextSize.Height() > rRect.Bottom() )
        rDev.SetClipRegion( rRect );

    rDev.DrawText( aPos, aText );

    if( rDev.IsClipRegion() )
        rDev.SetClipRegion();
}
//------------------------------------------------------------------------------
EditBrowseBox::RowStatus OFieldExpressionControl::GetRowStatus(long nRow) const
{
    DBG_CHKTHIS( rpt_OFieldExpressionControl,NULL);
    if (nRow >= 0 && nRow == m_nDataPos)
        return EditBrowseBox::CURRENT;
    if ( nRow != BROWSER_ENDOFSELECTION && nRow < static_cast<long>(m_aGroupPositions.size()) && m_aGroupPositions[nRow] != NO_GROUP )
    {
        try
        {
            uno::Reference< report::XGroup> xGroup = m_pParent->getGroup(m_aGroupPositions[nRow]);
            return (xGroup->getHeaderOn() || xGroup->getFooterOn())? EditBrowseBox::HEADERFOOTER : EditBrowseBox::CLEAN;
        }
        catch(uno::Exception&)
        {
            OSL_ENSURE(0,"Exception cathced while try to get a group!");
        }
    }
    return EditBrowseBox::CLEAN;
}
//	XEventListener
//------------------------------------------------------------------------------
void SAL_CALL OFieldExpressionControl::disposing(const lang::EventObject& /*e*/) throw( uno::RuntimeException )
{
}
//------------------------------------------------------------------------------
// XContainerListener
//------------------------------------------------------------------------------
void SAL_CALL OFieldExpressionControl::elementInserted(const container::ContainerEvent& evt) throw(uno::RuntimeException)
{
    if ( m_bIgnoreEvent )
        return;
    ::vos::OClearableGuard aSolarGuard( Application::GetSolarMutex() );
    ::osl::MutexGuard aGuard( m_aMutex );
    sal_Int32 nGroupPos = 0;
    if ( evt.Accessor >>= nGroupPos )
    {
        if ( nGroupPos >= GetRowCount() )
        {
            sal_Int32 nAddedRows = nGroupPos - GetRowCount();
            RowInserted(nAddedRows);
            for (sal_Int32 i = 0; i < nAddedRows; ++i)
                m_aGroupPositions.push_back(NO_GROUP);
            m_aGroupPositions[nGroupPos] = nGroupPos;
        }
        else
        {
            ::std::vector<sal_Int32>::iterator aFind = m_aGroupPositions.begin()+ nGroupPos;
            if ( aFind == m_aGroupPositions.end() )
                aFind = ::std::find(m_aGroupPositions.begin(),m_aGroupPositions.end(),NO_GROUP);

            if ( aFind != m_aGroupPositions.end() )
            {
                if ( *aFind != NO_GROUP )
                    aFind = m_aGroupPositions.insert(aFind,nGroupPos);
                else
                    *aFind = nGroupPos;
                
                ::std::vector<sal_Int32>::iterator aEnd  = m_aGroupPositions.end();
                for(++aFind;aFind != aEnd;++aFind)
                    if ( *aFind != NO_GROUP )
                        ++*aFind;

                //::std::vector<sal_Int32>::reverse_iterator aRIter = m_aGroupPositions.rbegin();
                //::std::vector<sal_Int32>::reverse_iterator aREnd = m_aGroupPositions.rend();
                //for (; aRIter != aREnd && *aRIter != NO_GROUP; ++aRIter)
                //    continue;
                //if ( aRIter != aREnd )
                //    m_aGroupPositions.erase(m_aGroupPositions.begin() + (m_aGroupPositions.size() - 1 - (aRIter - m_aGroupPositions.rbegin())));
            }
        }
        Invalidate();
    }
}
//------------------------------------------------------------------------------
void SAL_CALL OFieldExpressionControl::elementReplaced(const container::ContainerEvent& /*evt*/) throw(uno::RuntimeException)
{
}
//------------------------------------------------------------------------------
void SAL_CALL OFieldExpressionControl::elementRemoved(const container::ContainerEvent& evt) throw(uno::RuntimeException)
{
    ::vos::OClearableGuard aSolarGuard( Application::GetSolarMutex() );
    ::osl::MutexGuard aGuard( m_aMutex );

    if ( m_bIgnoreEvent )
        return;

    sal_Int32 nGroupPos = 0;
    if ( evt.Accessor >>= nGroupPos )
    {
        ::std::vector<sal_Int32>::iterator aFind = ::std::find(m_aGroupPositions.begin(),m_aGroupPositions.end(),nGroupPos);
        if ( aFind != m_aGroupPositions.end() )
        {
            *aFind = NO_GROUP;
            ::std::vector<sal_Int32>::iterator aEnd  = m_aGroupPositions.end();
            for(++aFind;aFind != aEnd;++aFind)
                if ( *aFind != NO_GROUP )
                    --*aFind;
            //PaintCell(*this,GetFieldRect(FIELD_EXPRESSION),FIELD_EXPRESSION);
            Invalidate();
        }
    }
}
//------------------------------------------------------------------------------
sal_Bool OFieldExpressionControl::IsDeleteAllowed( )
{
    return !m_pParent->isReadOnly() && GetSelectRowCount() > 0;
}
//------------------------------------------------------------------------
void OFieldExpressionControl::KeyInput( const KeyEvent& rEvt )
{
    if (IsDeleteAllowed())
    {
        if (rEvt.GetKeyCode().GetCode() == KEY_DELETE &&	// Delete rows
            !rEvt.GetKeyCode().IsShift() &&
            !rEvt.GetKeyCode().IsMod1())
        {
            DeleteRows();
            return;
        }
    }
    EditBrowseBox::KeyInput(rEvt);
}
//------------------------------------------------------------------------
void OFieldExpressionControl::Command(const CommandEvent& rEvt)
{
    switch (rEvt.GetCommand())
    {
        case COMMAND_CONTEXTMENU:
        {
            if (!rEvt.IsMouseEvent())
            {
                EditBrowseBox::Command(rEvt);
                return;
            }

            USHORT nColId = GetColumnAtXPosPixel(rEvt.GetMousePosPixel().X());

            if ( nColId == HANDLE_ID )
            {
                //long   nRow = GetRowAtYPosPixel(rEvt.GetMousePosPixel().Y());
                PopupMenu aContextMenu(ModuleRes(RID_GROUPSROWPOPUPMENU));
                sal_Bool bEnable = sal_False;
                long nIndex = FirstSelectedRow();
                while( nIndex >= 0 && !bEnable )
                {
                    if ( m_aGroupPositions[nIndex] != NO_GROUP )
                        bEnable = sal_True;
                    nIndex = NextSelectedRow();
                }
                //aContextMenu.EnableItem( SID_CUT, IsDeleteAllowed() && bEnable);
                //aContextMenu.EnableItem( SID_COPY, bEnable);
                //TransferableDataHelper aTransferData(TransferableDataHelper::CreateFromSystemClipboard(GetParent()));
                //aContextMenu.EnableItem( SID_PASTE, aTransferData.HasFormat(SOT_FORMATSTR_ID_RPT_GRPED) );
                aContextMenu.EnableItem( SID_DELETE, IsDeleteAllowed() && bEnable );
                switch (aContextMenu.Execute(this, rEvt.GetMousePosPixel()))
                {
                    case SID_CUT:
                        cut();
                        break;
                    case SID_COPY:
                        copy();
                        break;
                    case SID_PASTE:
                        paste();
                        break;

                    case SID_DELETE:
                        if( m_nDeleteEvent )
                            Application::RemoveUserEvent( m_nDeleteEvent );
                        m_nDeleteEvent = Application::PostUserEvent( LINK(this, OFieldExpressionControl, DelayedDelete) );
                        break;
                    default:
                        break;
                }
            } // if ( nColId == HANDLE_ID )
            // run through
        }
        default:
            EditBrowseBox::Command(rEvt);
    }

}
//------------------------------------------------------------------------------
void OFieldExpressionControl::DeleteRows()
{
    DBG_CHKTHIS( rpt_OFieldExpressionControl,NULL);
    
    long nIndex = FirstSelectedRow();
    bool bFirstTime = true;

    long nOldDataPos = nIndex;
    uno::Sequence< beans::PropertyValue > aArgs(1);
    aArgs[0].Name = PROPERTY_GROUP;
    m_bIgnoreEvent = true;
    while( nIndex >= 0 )
    {
        if ( m_aGroupPositions[nIndex] != NO_GROUP )
        {
            if ( bFirstTime )
            {
                bFirstTime = false;
                String sUndoAction(String(ModuleRes(RID_STR_UNDO_REMOVE_SELECTION)));
                m_pParent->m_pController->getUndoMgr()->EnterListAction( sUndoAction, String() );
            }

            sal_Int32 nGroupPos = m_aGroupPositions[nIndex];
            uno::Reference< report::XGroup> xGroup = m_pParent->getGroup(nGroupPos);
            aArgs[0].Value <<= xGroup;
            // we use this way to create undo actions
            m_pParent->m_pController->executeChecked(SID_GROUP_REMOVE,aArgs);

            ::std::vector<sal_Int32>::iterator aFind = ::std::find(m_aGroupPositions.begin(),m_aGroupPositions.end(),nGroupPos);
            *aFind = NO_GROUP;
            ::std::vector<sal_Int32>::iterator aEnd  = m_aGroupPositions.end();
            for(++aFind;aFind != aEnd;++aFind)
                if ( *aFind != NO_GROUP )
                    --*aFind;
        }
        nIndex = NextSelectedRow();
    } // while( nIndex >= 0 )

    if ( !bFirstTime )
        m_pParent->m_pController->getUndoMgr()->LeaveListAction();

    m_nDataPos = GetCurRow();
    InvalidateStatusCell( nOldDataPos );
    InvalidateStatusCell( m_nDataPos );
    ActivateCell();
    m_pParent->DisplayData( m_nDataPos );
    m_bIgnoreEvent = false;
    Invalidate();
}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void OFieldExpressionControl::cut()
{
    copy();
    DeleteRows();
}

//------------------------------------------------------------------------------
void OFieldExpressionControl::copy()
{
    DBG_CHKTHIS( rpt_OFieldExpressionControl,NULL);
    //////////////////////////////////////////////////////////////////////
    // set to the right row and save it
    m_pParent->SaveData( m_nDataPos );

    uno::Sequence<uno::Any> aClipboardList = fillSelectedGroups();

    if( aClipboardList.getLength() )
    {
        OGroupExchange* pData = new OGroupExchange(aClipboardList);
        uno::Reference< ::com::sun::star::datatransfer::XTransferable> xRef = pData;
        pData->CopyToClipboard(GetParent());
    }
}

//------------------------------------------------------------------------------
void OFieldExpressionControl::paste()
{
    TransferableDataHelper aTransferData(TransferableDataHelper::CreateFromSystemClipboard(GetParent()));
    if(aTransferData.HasFormat(OGroupExchange::getReportGroupId()))
    {
        if( m_nPasteEvent )
            Application::RemoveUserEvent( m_nPasteEvent );
        m_nPasteEvent = Application::PostUserEvent( LINK(this, OFieldExpressionControl, DelayedPaste) );
    }
}
//------------------------------------------------------------------------------
IMPL_LINK( OFieldExpressionControl, DelayedPaste, void*,  )
{
    m_nPasteEvent = 0;

    sal_Int32 nPastePosition = GetSelectRowCount() ? FirstSelectedRow() : GetCurRow();

    InsertRows( nPastePosition );
    SetNoSelection();
    GoToRow( nPastePosition );

    return 0;
}
//------------------------------------------------------------------------------
IMPL_LINK( OFieldExpressionControl, DelayedDelete, void*,  )
{
    m_nDeleteEvent = 0;
    DeleteRows();
    return 0;
}
//------------------------------------------------------------------------------
void OFieldExpressionControl::InsertRows( long nRow )
{
    DBG_CHKTHIS( rpt_OFieldExpressionControl,NULL);

    sal_Int32 nSize = 0;
    //////////////////////////////////////////////////////////////////////
    // get rows from clipboard
    TransferableDataHelper aTransferData(TransferableDataHelper::CreateFromSystemClipboard(GetParent()));
    if(aTransferData.HasFormat(OGroupExchange::getReportGroupId()))
    {
        datatransfer::DataFlavor aFlavor;
        SotExchange::GetFormatDataFlavor(OGroupExchange::getReportGroupId(), aFlavor);
        uno::Sequence< uno::Any > aGroups;
        
        if( (aTransferData.GetAny(aFlavor) >>= aGroups) && aGroups.getLength() )
        {
            m_bIgnoreEvent = false;
            String sUndoAction(String(ModuleRes(RID_STR_UNDO_APPEND_GROUP)));
            m_pParent->m_pController->getUndoMgr()->EnterListAction( sUndoAction, String() );

            uno::Reference<report::XGroups> xGroups = m_pParent->getGroups();
            sal_Int32 nGroupPos = 0;
            ::std::vector<sal_Int32>::iterator aIter = m_aGroupPositions.begin();
            ::std::vector<sal_Int32>::size_type nRowPos = static_cast< ::std::vector<sal_Int32>::size_type >(nRow);
            if ( nRowPos < m_aGroupPositions.size() )
            {
                ::std::vector<sal_Int32>::iterator aEnd  = m_aGroupPositions.begin() + nRowPos;
                for(;aIter != aEnd;++aIter)
                {
                    if ( *aIter != NO_GROUP )
                        nGroupPos = *aIter;
                }
            }
            for(sal_Int32 i=0;i < aGroups.getLength();++i,++nSize)
            {
                uno::Sequence< beans::PropertyValue > aArgs(2);
                aArgs[0].Name = PROPERTY_GROUP;
                aArgs[0].Value = aGroups[i];
                aArgs[1].Name = PROPERTY_POSITIONY;
                aArgs[1].Value <<= nGroupPos;
                m_pParent->m_pController->executeChecked(SID_GROUP_APPEND,aArgs);

                ::std::vector<sal_Int32>::iterator aInsertPos = m_aGroupPositions.insert(aIter,nGroupPos);
                ++aInsertPos;
                aIter = aInsertPos;
                ::std::vector<sal_Int32>::iterator aEnd  = m_aGroupPositions.end();
                for(;aInsertPos != aEnd;++aInsertPos)
                    if ( *aInsertPos != NO_GROUP )
                        ++*aInsertPos;
            }
            m_pParent->m_pController->getUndoMgr()->LeaveListAction();
            m_bIgnoreEvent = true;
        }
    }

    RowInserted( nRow,nSize,sal_True );
}
//------------------------------------------------------------------------------

DBG_NAME( rpt_OGroupsSortingDialog )
//========================================================================
// class OGroupsSortingDialog
//========================================================================
OGroupsSortingDialog::OGroupsSortingDialog( Window* _pParent
                                           ,sal_Bool _bReadOnly
                                           ,OReportController* _pController)
    : FloatingWindow( _pParent, ModuleRes(RID_GROUPS_SORTING) )
    ,OPropertyChangeListener(m_aMutex)
    ,m_aFL2(this, ModuleRes(FL_SEPARATOR2) )
    ,m_aMove(this, ModuleRes(FT_MOVELABEL) )
    ,m_aUp(this, ModuleRes(PB_UP) )
    ,m_aDown(this, ModuleRes(PB_DOWN) )
    ,m_aFL3(this, ModuleRes(FL_SEPARATOR3) )
    ,m_aOrder(this, ModuleRes(FT_ORDER) )
    ,m_aOrderLst(this, ModuleRes(LST_ORDER) )
    ,m_aHeader(this, ModuleRes(FT_HEADER) )
    ,m_aHeaderLst(this, ModuleRes(LST_HEADERLST) )
    ,m_aFooter(this, ModuleRes(FT_FOOTER) )
    ,m_aFooterLst(this, ModuleRes(LST_FOOTERLST) )
    ,m_aGroupOn(this, ModuleRes(FT_GROUPON) )
    ,m_aGroupOnLst(this, ModuleRes(LST_GROUPONLST) )
    ,m_aGroupInterval(this, ModuleRes(FT_GROUPINTERVAL) )
    ,m_aGroupIntervalEd(this, ModuleRes(ED_GROUPINTERVALLST) )
    ,m_aKeepTogether(this, ModuleRes(FT_KEEPTOGETHER) )
    ,m_aKeepTogetherLst(this, ModuleRes(LST_KEEPTOGETHERLST) )
    ,m_aFL(this, ModuleRes(FL_SEPARATOR1) )
    ,m_aHelpWindow(this, ModuleRes(HELP_FIELD) )
    ,m_pFieldExpression( new OFieldExpressionControl(this,ModuleRes(WND_CONTROL)))
    ,m_pController(_pController)
    ,m_pCurrentGroupListener(NULL)
    ,m_xGroups(m_pController->getReportDefinition()->getGroups())
    ,m_bReadOnly(_bReadOnly)
{
    DBG_CTOR( rpt_OGroupsSortingDialog,NULL);	
    

    Control* pControlsLst[] = { &m_aHeaderLst, &m_aFooterLst, &m_aGroupOnLst, &m_aKeepTogetherLst, &m_aOrderLst, &m_aGroupIntervalEd};
    for (size_t i = 0; i < sizeof(pControlsLst)/sizeof(pControlsLst[0]); ++i)
    {
        pControlsLst[i]->SetGetFocusHdl(LINK(this, OGroupsSortingDialog, OnControlFocusGot));
        pControlsLst[i]->SetLoseFocusHdl(LINK(this, OGroupsSortingDialog, OnControlFocusLost));
        pControlsLst[i]->Show(TRUE);
    } // for (int i = 0; i < sizeof(pControls)/sizeof(pControls[0]); ++i)

    for (size_t i = 0; i < (sizeof(pControlsLst)/sizeof(pControlsLst[0]))-1; ++i)
        static_cast<ListBox*>(pControlsLst[i])->SetSelectHdl(LINK(this,OGroupsSortingDialog,LBChangeHdl));

    Control* pControls[]	= { &m_aHeader,	&m_aFooter,	&m_aGroupOn, &m_aGroupInterval,	&m_aKeepTogether, &m_aOrder
                                , &m_aMove,&m_aFL2};
    sal_Int32 nMaxTextWidth = 0;
    MnemonicGenerator aMnemonicGenerator;
    for (size_t i = 0; i < sizeof(pControls)/sizeof(pControls[0]); ++i)
        aMnemonicGenerator.RegisterMnemonic( pControls[i]->GetText() );

    for (size_t i = 0; i < sizeof(pControls)/sizeof(pControls[0]); ++i)
    {
        pControls[i]->Show(TRUE);
        String sText = pControls[i]->GetText();
        if ( aMnemonicGenerator.CreateMnemonic(sText) )
            pControls[i]->SetText(sText);
        sal_Int32 nTextWidth = GetTextWidth(sText);
        nMaxTextWidth = ::std::max<sal_Int32>(nTextWidth,nMaxTextWidth);		
    }

    Size aSpace = LogicToPixel( Size( UNRELATED_CONTROLS, PAGE_HEIGHT), MAP_APPFONT );
    Size aOutSize(nMaxTextWidth + m_aHeader.GetSizePixel().Width() + 3*aSpace.Width(),aSpace.Height());
    SetMinOutputSizePixel(aOutSize);
    SetOutputSizePixel(aOutSize);
    Resize();

    m_pReportListener = new OPropertyChangeMultiplexer(this,m_pController->getReportDefinition().get());
    m_pReportListener->addProperty(PROPERTY_COMMAND);
    m_pReportListener->addProperty(PROPERTY_COMMANDTYPE);

    m_pFieldExpression->lateInit();
    fillColumns();
    m_pFieldExpression->Show();

    //m_aHelpWindow.SetReadOnly();
    m_aHelpWindow.SetControlBackground( GetSettings().GetStyleSettings().GetFaceColor() );
    m_aUp.SetClickHdl(LINK(this,OGroupsSortingDialog,ClickHdl));
    m_aDown.SetClickHdl(LINK(this,OGroupsSortingDialog,ClickHdl));

    m_pFieldExpression->SetZOrder(&m_aFL2, WINDOW_ZORDER_BEHIND);

    m_aMove.SetZOrder(m_pFieldExpression, WINDOW_ZORDER_BEHIND);
    m_aUp.SetZOrder(&m_aMove, WINDOW_ZORDER_BEHIND);
    m_aDown.SetZOrder(&m_aUp, WINDOW_ZORDER_BEHIND);
    // set Hi contrast bitmaps
    m_aUp.SetModeImage(		ModuleRes(IMG_UP_H),BMP_COLOR_HIGHCONTRAST);
    m_aDown.SetModeImage(	ModuleRes(IMG_DOWN_H),BMP_COLOR_HIGHCONTRAST);

    checkButtons(0);

    FreeResource();
}

//------------------------------------------------------------------------
OGroupsSortingDialog::~OGroupsSortingDialog()
{
    DBG_DTOR( rpt_OGroupsSortingDialog,NULL);	
    delete m_pFieldExpression;
    m_xColumns.clear();
    m_pReportListener->dispose();
    if ( m_pCurrentGroupListener.is() )
        m_pCurrentGroupListener->dispose();
}
// -----------------------------------------------------------------------------
sal_Bool OGroupsSortingDialog::isReadOnly( ) const
{
    return m_bReadOnly;
}
//------------------------------------------------------------------------------
void OGroupsSortingDialog::UpdateData( )
{
    m_pFieldExpression->Invalidate();
    long nCurRow = m_pFieldExpression->GetCurRow();
    m_pFieldExpression->DeactivateCell();
    m_pFieldExpression->ActivateCell(nCurRow, m_pFieldExpression->GetCurColumnId());
    DisplayData(nCurRow);
}
//------------------------------------------------------------------------------
void OGroupsSortingDialog::DisplayData( sal_Int32 _nRow )
{
    DBG_CHKTHIS( rpt_OGroupsSortingDialog,NULL);
    sal_Int32 nGroupPos = m_pFieldExpression->getGroupPosition(_nRow);
    sal_Bool bEmpty = nGroupPos == NO_GROUP;
    m_aHeaderLst.Enable(!bEmpty);
    m_aFooterLst.Enable(!bEmpty);
    m_aGroupOnLst.Enable(!bEmpty);
    m_aGroupIntervalEd.Enable(!bEmpty);
    m_aKeepTogetherLst.Enable(!bEmpty);
    m_aOrderLst.Enable(!bEmpty);

    m_aFL3.Enable(!bEmpty);
    m_aHeader.Enable(!bEmpty);
    m_aFooter.Enable(!bEmpty);
    m_aGroupOn.Enable(!bEmpty);
    m_aGroupInterval.Enable(!bEmpty);
    m_aKeepTogether.Enable(!bEmpty);
    m_aOrder.Enable(!bEmpty);

    checkButtons(_nRow);

    if ( m_pCurrentGroupListener.is() )
        m_pCurrentGroupListener->dispose();
    m_pCurrentGroupListener = NULL;
    if ( !bEmpty && nGroupPos != NO_GROUP )
    {
        uno::Reference< report::XGroup> xGroup = getGroup(nGroupPos);
        
        m_pCurrentGroupListener = new OPropertyChangeMultiplexer(this,xGroup.get());
        m_pCurrentGroupListener->addProperty(PROPERTY_HEADERON);
        m_pCurrentGroupListener->addProperty(PROPERTY_FOOTERON);
        
        displayGroup(xGroup);
    }
}
//------------------------------------------------------------------------------
void OGroupsSortingDialog::SaveData( sal_Int32 _nRow)
{
    DBG_CHKTHIS( rpt_OGroupsSortingDialog,NULL);
    sal_Int32 nGroupPos = m_pFieldExpression->getGroupPosition(_nRow);
    if ( nGroupPos == NO_GROUP )
        return;
    
    uno::Reference< report::XGroup> xGroup = getGroup(nGroupPos);
    if ( m_aHeaderLst.GetSavedValue() != m_aHeaderLst.GetSelectEntryPos() )
        xGroup->setHeaderOn( m_aHeaderLst.GetSelectEntryPos() == 0 );
    if ( m_aFooterLst.GetSavedValue() != m_aFooterLst.GetSelectEntryPos() )
        xGroup->setFooterOn( m_aFooterLst.GetSelectEntryPos() == 0 );
    if ( m_aKeepTogetherLst.GetSavedValue() != m_aKeepTogetherLst.GetSelectEntryPos() )
        xGroup->setKeepTogether( m_aKeepTogetherLst.GetSelectEntryPos() );
    if ( m_aGroupOnLst.GetSavedValue() != m_aGroupOnLst.GetSelectEntryPos() )
    {
        sal_Int16 nGroupOn = static_cast<sal_Int16>(reinterpret_cast<sal_IntPtr>(m_aGroupOnLst.GetEntryData(m_aGroupOnLst.GetSelectEntryPos())));
        xGroup->setGroupOn( nGroupOn );
    }
    if ( m_aGroupIntervalEd.GetSavedValue().ToInt32() != m_aGroupIntervalEd.GetValue() )
    {
        xGroup->setGroupInterval( static_cast<sal_Int32>(m_aGroupIntervalEd.GetValue()) );
        m_aGroupIntervalEd.SaveValue();
    }
    if ( m_aOrderLst.GetSavedValue() != m_aOrderLst.GetSelectEntryPos() )
        xGroup->setSortAscending( m_aOrderLst.GetSelectEntryPos() == 0 );

    ListBox* pControls[] = { &m_aHeaderLst,&m_aFooterLst,&m_aGroupOnLst,&m_aKeepTogetherLst,&m_aOrderLst};
    for (size_t i = 0; i < sizeof(pControls)/sizeof(pControls[0]); ++i)
        pControls[i]->SaveValue();
}

// -----------------------------------------------------------------------------
sal_Int32 OGroupsSortingDialog::getColumnDataType(const ::rtl::OUString& _sColumnName)
{
    sal_Int32 nDataType = sdbc::DataType::VARCHAR;
    try
    {
        if ( m_xColumns.is() && m_xColumns->hasByName(_sColumnName) )
        {
            uno::Reference< beans::XPropertySet> xColumn(m_xColumns->getByName(_sColumnName),uno::UNO_QUERY);
            if ( xColumn.is() )
                xColumn->getPropertyValue(PROPERTY_TYPE) >>= nDataType;
        }
    }
    catch(uno::Exception&)
    {
        OSL_ENSURE(0,"Eception caught while getting the type of a column");
    }
    
    return nDataType;
}
//------------------------------------------------------------------------------
IMPL_LINK(OGroupsSortingDialog, OnControlFocusGot, Control*, pControl )
{
    if ( m_pFieldExpression && m_pFieldExpression->getExpressionControl() )
    {
        Control* pControls[] = { m_pFieldExpression->getExpressionControl(),&m_aHeaderLst,&m_aFooterLst,&m_aGroupOnLst,&m_aGroupIntervalEd,&m_aKeepTogetherLst,&m_aOrderLst};
        for (size_t i = 0; i < sizeof(pControls)/sizeof(pControls[0]); ++i)
        {
            if ( pControl == pControls[i] )
            {
                ListBox* pListBox = dynamic_cast< ListBox* >( pControl );
                if ( pListBox )
                    pListBox->SaveValue();
                NumericField* pNumericField = dynamic_cast< NumericField* >( pControl );
                if ( pNumericField )
                    pNumericField->SaveValue();
                showHelpText(static_cast<USHORT>(i+STR_RPT_HELP_FIELD));
                break;
            }
        }
    }
    return 0L;
}
//------------------------------------------------------------------------------
IMPL_LINK(OGroupsSortingDialog, OnControlFocusLost, Control*, pControl )
{
    if ( m_pFieldExpression && pControl == &m_aGroupIntervalEd )
    {
        if ( m_aGroupIntervalEd.IsModified() )
            SaveData(m_pFieldExpression->GetCurRow());
    }
    return 0L;
}
// -----------------------------------------------------------------------------
IMPL_LINK( OGroupsSortingDialog, ClickHdl, ImageButton*, _pButton )
{
    DBG_CHKTHIS( rpt_OGroupsSortingDialog,NULL);
    if ( m_pFieldExpression )
    {
        long nIndex = m_pFieldExpression->GetCurrRow();
        sal_Int32 nGroupPos = m_pFieldExpression->getGroupPosition(nIndex);
        uno::Sequence<uno::Any> aClipboardList;
        if ( nIndex >= 0 && nGroupPos != NO_GROUP )
        {
            aClipboardList.realloc(1);
            aClipboardList[0] = m_xGroups->getByIndex(nGroupPos);
        }
        if ( _pButton == &m_aUp )
            --nIndex;
        else
            ++nIndex;

        if ( nIndex >= 0 && aClipboardList.getLength() )
        {
            m_pFieldExpression->SetNoSelection();
            m_pFieldExpression->moveGroups(aClipboardList,nIndex,sal_False);
            m_pFieldExpression->DeactivateCell();
            m_pFieldExpression->GoToRow(nIndex);
            //long nCurRow = m_pFieldExpression->GetCurRow();
            m_pFieldExpression->ActivateCell(nIndex, m_pFieldExpression->GetCurColumnId());
            DisplayData(nIndex);
        }
    }
    return 1L;
}
// -----------------------------------------------------------------------------
IMPL_LINK( OGroupsSortingDialog, LBChangeHdl, ListBox*, pListBox )
{
    DBG_CHKTHIS( rpt_OGroupsSortingDialog,NULL);
    if ( pListBox->GetSavedValue() != pListBox->GetSelectEntryPos() )
    {
        sal_Int32 nRow = m_pFieldExpression->GetCurRow();
        sal_Int32 nGroupPos = m_pFieldExpression->getGroupPosition(nRow);
        if ( pListBox != &m_aHeaderLst && pListBox != &m_aFooterLst)
        {
            if ( pListBox && pListBox->GetSavedValue() != pListBox->GetSelectEntryPos() )
                SaveData(nRow);
        }
        else if ( nGroupPos != NO_GROUP )
        {
            uno::Reference< report::XGroup> xGroup = getGroup(nGroupPos);
            uno::Sequence< beans::PropertyValue > aArgs(2);
            aArgs[1].Name = PROPERTY_GROUP;
            aArgs[1].Value <<= xGroup;
        
            if ( &m_aHeaderLst  == pListBox )
                aArgs[0].Name = PROPERTY_HEADERON;
            else
                aArgs[0].Name = PROPERTY_FOOTERON;

            aArgs[0].Value <<= pListBox->GetSelectEntryPos() == 0;
            m_pController->executeChecked(&m_aHeaderLst  == pListBox ? SID_GROUPHEADER : SID_GROUPFOOTER,aArgs);
            if ( m_pFieldExpression )
                m_pFieldExpression->InvalidateHandleColumn();
        }
    }
    return 1L;
}
// -----------------------------------------------------------------------------
void OGroupsSortingDialog::showHelpText(USHORT _nResId)
{
    m_aHelpWindow.SetText(String(ModuleRes(_nResId)));
}
// -----------------------------------------------------------------------------
void OGroupsSortingDialog::_propertyChanged(const beans::PropertyChangeEvent& _rEvent) throw( uno::RuntimeException)
{
    uno::Reference< report::XGroup > xGroup(_rEvent.Source,uno::UNO_QUERY);
    if ( xGroup.is() )
        displayGroup(xGroup);
    else
        fillColumns();
}
// -----------------------------------------------------------------------------
void OGroupsSortingDialog::fillColumns()
{
    m_xColumns.clear();
    uno::Reference< report::XReportDefinition> xReport = m_pController->getReportDefinition();
    if ( xReport->getCommand().getLength() )
        m_xColumns = dbtools::getFieldsByCommandDescriptor(m_pController->getConnection(),xReport->getCommandType(),xReport->getCommand(),m_xHoldAlive);
    m_pFieldExpression->fillColumns(m_xColumns);
}
// -----------------------------------------------------------------------------
void OGroupsSortingDialog::displayGroup(const uno::Reference<report::XGroup>& _xGroup)
{
    m_aHeaderLst.SelectEntryPos(_xGroup->getHeaderOn() ? 0 : 1 );
    m_aFooterLst.SelectEntryPos(_xGroup->getFooterOn() ? 0 : 1 );
    sal_Int32 nDataType = getColumnDataType(_xGroup->getExpression());

    // first clear whole group on list
    while(m_aGroupOnLst.GetEntryCount() > 1 )
    {
        m_aGroupOnLst.RemoveEntry(1);
    }
    
    switch(nDataType)
    {
        case sdbc::DataType::LONGVARCHAR:
        case sdbc::DataType::VARCHAR:
        case sdbc::DataType::CHAR:
            m_aGroupOnLst.InsertEntry(String(ModuleRes(STR_RPT_PREFIXCHARS)));
            m_aGroupOnLst.SetEntryData(1,reinterpret_cast<void*>(report::GroupOn::PREFIX_CHARACTERS));
            break;
        case sdbc::DataType::DATE:
        case sdbc::DataType::TIME:
        case sdbc::DataType::TIMESTAMP:
            {
                USHORT nIds[] = { STR_RPT_YEAR, STR_RPT_QUARTER,STR_RPT_MONTH,STR_RPT_WEEK,STR_RPT_DAY,STR_RPT_HOUR,STR_RPT_MINUTE };
                for (USHORT i = 0; i < sizeof(nIds)/sizeof(nIds[0]); ++i)
                {
                    m_aGroupOnLst.InsertEntry(String(ModuleRes(nIds[i])));
                    m_aGroupOnLst.SetEntryData(i+1,reinterpret_cast<void*>(i+2));
                }
            }
            break;
        default:
            m_aGroupOnLst.InsertEntry(String(ModuleRes(STR_RPT_INTERVAL)));
            m_aGroupOnLst.SetEntryData(1,reinterpret_cast<void*>(report::GroupOn::INTERVAL));
            break;
    } // switch(nDataType)
    USHORT nPos = 0;
    switch(_xGroup->getGroupOn())
    {
        case report::GroupOn::DEFAULT:
            nPos = 0;
            break;
        case report::GroupOn::PREFIX_CHARACTERS:
            nPos = 1;
            break;
        case report::GroupOn::YEAR:
            nPos = 1;
            break;
        case report::GroupOn::QUARTAL:
            nPos = 2;
            break;
        case report::GroupOn::MONTH:
            nPos = 3;
            break;
        case report::GroupOn::WEEK:
            nPos = 4;
            break;
        case report::GroupOn::DAY:
            nPos = 5;
            break;
        case report::GroupOn::HOUR:
            nPos = 6;
            break;
        case report::GroupOn::MINUTE:
            nPos = 7;
            break;
        case report::GroupOn::INTERVAL:
            nPos = 1;
            break;
        default:
            nPos = 0;
    }
    m_aGroupOnLst.SelectEntryPos(nPos);
    m_aGroupIntervalEd.SetText(String::CreateFromInt32(_xGroup->getGroupInterval()));
    m_aGroupIntervalEd.SaveValue();
    m_aKeepTogetherLst.SelectEntryPos(_xGroup->getKeepTogether());
    m_aOrderLst.SelectEntryPos(_xGroup->getSortAscending() ? 0 : 1);

    ListBox* pControls[] = { &m_aHeaderLst,&m_aFooterLst,&m_aGroupOnLst,&m_aKeepTogetherLst,&m_aOrderLst};
    for (size_t i = 0; i < sizeof(pControls)/sizeof(pControls[0]); ++i)
        pControls[i]->SaveValue();

    ListBox* pControlsLst2[] = { &m_aHeaderLst,	&m_aFooterLst,	&m_aGroupOnLst,	&m_aKeepTogetherLst,&m_aOrderLst};
    sal_Bool bReadOnly = !m_pController->isEditable();
    for (size_t i = 0; i < sizeof(pControlsLst2)/sizeof(pControlsLst2[0]); ++i)
        pControlsLst2[i]->SetReadOnly(bReadOnly);
    m_aGroupIntervalEd.SetReadOnly(bReadOnly);
}
//------------------------------------------------------------------------------
void OGroupsSortingDialog::Resize()
{
    Window::Resize();
    Size aTotalOutputSize = GetOutputSizePixel();
    Size aSpace = LogicToPixel( Size( UNRELATED_CONTROLS, UNRELATED_CONTROLS ), MAP_APPFONT );
    m_pFieldExpression->SetSizePixel(Size(aTotalOutputSize.Width() - 2*aSpace.Width(),m_pFieldExpression->GetSizePixel().Height()));

    Control* pControlsLst[] = { &m_aHeaderLst,	&m_aFooterLst,	&m_aGroupOnLst,	&m_aGroupIntervalEd,&m_aKeepTogetherLst,&m_aOrderLst};
    Control* pControls[]	= { &m_aHeader,		&m_aFooter,		&m_aGroupOn,	&m_aGroupInterval,	&m_aKeepTogether,	&m_aOrder};
    sal_Int32 nMaxTextWidth = 0;
    for (size_t i = 0; i < sizeof(pControls)/sizeof(pControls[0]); ++i)
    {
        nMaxTextWidth = ::std::max<sal_Int32>(static_cast<sal_Int32>(GetTextWidth(pControls[i]->GetText())),nMaxTextWidth);
    } // for (int i = 0; i < sizeof(pControls)/sizeof(pControls[0]); ++i)

    // aTotalOutputSize.Width() - m_aHeaderLst.GetSizePixel().Width() - 3*aSpace.Width()
    for (size_t i = 0; i < sizeof(pControls)/sizeof(pControls[0]); ++i)
    {
        pControls[i]->SetSizePixel(Size(nMaxTextWidth,pControls[i]->GetSizePixel().Height()));
        Point aPos = pControls[i]->GetPosPixel();
        aPos.X() += nMaxTextWidth + aSpace.Width();
        aPos.Y() = pControlsLst[i]->GetPosPixel().Y();
        
        pControlsLst[i]->SetPosSizePixel(aPos,Size(aTotalOutputSize.Width() - aPos.X() - aSpace.Width(),pControlsLst[i]->GetSizePixel().Height()));
    } // for (int i = 0; i < sizeof(pControls)/sizeof(pControls[0]); ++i)

    m_aFL.SetSizePixel(Size(aTotalOutputSize.Width() - aSpace.Width(),m_aFL.GetSizePixel().Height()));
    m_aFL2.SetSizePixel(Size(aTotalOutputSize.Width() - aSpace.Width(),m_aFL2.GetSizePixel().Height()));
    m_aFL3.SetSizePixel(Size(aTotalOutputSize.Width() - aSpace.Width(),m_aFL3.GetSizePixel().Height()));

    sal_Int32 nPos = aTotalOutputSize.Width() - aSpace.Width() - m_aUp.GetSizePixel().Width();
    m_aDown.SetPosPixel(Point(nPos,m_aDown.GetPosPixel().Y()));
    nPos -= (m_aUp.GetSizePixel().Width() + LogicToPixel( Size( RELATED_CONTROLS, 0 ), MAP_APPFONT ).Width());
    m_aUp.SetPosPixel(Point(nPos,m_aUp.GetPosPixel().Y()));
    Point aHelpPos = m_aHelpWindow.GetPosPixel();
    m_aHelpWindow.SetSizePixel(Size(aTotalOutputSize.Width() - aHelpPos.X(),aTotalOutputSize.Height() - aHelpPos.Y()));
}
//------------------------------------------------------------------------------
void OGroupsSortingDialog::checkButtons(sal_Int32 _nRow)
{
    sal_Int32 nGroupCount = m_xGroups->getCount();
    sal_Bool bEnable = nGroupCount > 1;
    m_aUp.Enable(bEnable && _nRow > 0 );
    m_aDown.Enable(bEnable && _nRow < (m_pFieldExpression->GetRowCount()-1) );
}
// =============================================================================
} // rptui
// =============================================================================
