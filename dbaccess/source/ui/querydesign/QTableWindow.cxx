/*************************************************************************
 *
 *  $RCSfile: QTableWindow.cxx,v $
 *
 *  $Revision: 1.14 $
 *
 *  last change: $Author: rt $ $Date: 2003-12-01 10:38:18 $
 *
 *  The Contents of this file are made available subject to the terms of
 *  either of the following licenses
 *
 *         - GNU Lesser General Public License Version 2.1
 *         - Sun Industry Standards Source License Version 1.1
 *
 *  Sun Microsystems Inc., October, 2000
 *
 *  GNU Lesser General Public License Version 2.1
 *  =============================================
 *  Copyright 2000 by Sun Microsystems, Inc.
 *  901 San Antonio Road, Palo Alto, CA 94303, USA
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License version 2.1, as published by the Free Software Foundation.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 *  MA  02111-1307  USA
 *
 *
 *  Sun Industry Standards Source License Version 1.1
 *  =================================================
 *  The contents of this file are subject to the Sun Industry Standards
 *  Source License Version 1.1 (the License); You may not use this file
 *  except in compliance with the License. You may obtain a copy of the
 *  License at http://www.openoffice.org/license.html.
 *
 *  Software provided under this License is provided on an AS IS basis,
 *  WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING,
 *  WITHOUT LIMITATION, WARRANTIES THAT THE SOFTWARE IS FREE OF DEFECTS,
 *  MERCHANTABLE, FIT FOR A PARTICULAR PURPOSE, OR NON-INFRINGING.
 *  See the License for the specific provisions governing your rights and
 *  obligations concerning the Software.
 *
 *  The Initial Developer of the Original Code is: Sun Microsystems, Inc.
 *
 *  Copyright: 2000 by Sun Microsystems, Inc.
 *
 *  All Rights Reserved.
 *
 *  Contributor(s): _______________________________________
 *
 *
 ************************************************************************/
#ifndef DBAUI_QUERY_TABLEWINDOWDATA_HXX
#include "QTableWindow.hxx"
#endif
#ifndef DBAUI_QUERYTABLEVIEW_HXX
#include "QueryTableView.hxx"
#endif
#ifndef DBACCESS_SHARED_DBUSTRINGS_HRC
#include "dbustrings.hrc"
#endif
#ifndef _TOOLS_DEBUG_HXX
#include <tools/debug.hxx>
#endif
#include "dbaccess_helpid.hrc"
#ifndef DBAUI_QUERYDESIGNVIEW_HXX
#include "QueryDesignView.hxx"
#endif
#ifndef DBACCESS_UI_BROWSER_ID_HXX
#include "browserids.hxx"
#endif
#ifndef DBAUI_QUERYCONTROLLER_HXX
#include "querycontroller.hxx"
#endif
#ifndef _SV_IMAGE_HXX
#include <vcl/image.hxx>
#endif
#ifndef DBAUI_TABLEWINDOWLISTBOX_HXX
#include "TableWindowListBox.hxx"
#endif
#ifndef _DBU_QRY_HRC_
#include "dbu_qry.hrc"
#endif
#ifndef _DBAUI_MODULE_DBU_HXX_
#include "moduledbu.hxx"
#endif
#ifndef DBAUI_QUERY_HRC
#include "Query.hrc"
#endif
#ifndef _COM_SUN_STAR_SDBCX_XKEYSSUPPLIER_HPP_
#include <com/sun/star/sdbcx/XKeysSupplier.hpp>
#endif
#ifndef _COM_SUN_STAR_CONTAINER_XNAMEACCESS_HPP_
#include <com/sun/star/container/XNameAccess.hpp>
#endif
#ifndef _COM_SUN_STAR_CONTAINER_XINDEXACCESS_HPP_
#include <com/sun/star/container/XIndexAccess.hpp>
#endif
#ifndef _COM_SUN_STAR_BEANS_XPROPERTYSET_HPP_
#include <com/sun/star/beans/XPropertySet.hpp>
#endif
#ifndef _COM_SUN_STAR_SDBCX_KEYTYPE_HPP_
#include <com/sun/star/sdbcx/KeyType.hpp>
#endif
#ifndef _COM_SUN_STAR_SDBCX_XCOLUMNSSUPPLIER_HPP_
#include <com/sun/star/sdbcx/XColumnsSupplier.hpp>
#endif
#ifndef DBAUI_TABLEFIELDINFO_HXX
#include "TableFieldInfo.hxx"
#endif
#ifndef _COMPHELPER_UNO3_HXX_
#include <comphelper/uno3.hxx>
#endif
#ifndef _COMPHELPER_EXTRACT_HXX_
#include <comphelper/extract.hxx>
#endif
#ifndef DBAUI_TOOLS_HXX
#include "UITools.hxx"
#endif


using namespace ::com::sun::star::sdbc;
using namespace ::com::sun::star::sdbcx;
using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::container;
using namespace ::com::sun::star::beans;
using namespace dbaui;
TYPEINIT1(OQueryTableWindow, OTableWindow);
//========================================================================
// class OQueryTableWindow
//========================================================================
DBG_NAME(OQueryTableWindow);
//------------------------------------------------------------------------------
OQueryTableWindow::OQueryTableWindow( Window* pParent, OQueryTableWindowData* pTabWinData, sal_Unicode* pszInitialAlias)
    :OTableWindow( pParent, pTabWinData )
    ,m_nAliasNum(0)
{
    DBG_CTOR(OQueryTableWindow,NULL);
    if (pszInitialAlias != NULL)
        m_strInitialAlias = ::rtl::OUString(pszInitialAlias);
    else
        m_strInitialAlias = pTabWinData->GetAliasName();

    // wenn der Tabellen- gleich dem Aliasnamen ist, dann darf ich das nicht an InitialAlias weiterreichen, denn das Anhaengen
    // eines eventuelle Tokens nicht klappen ...
    if (m_strInitialAlias == pTabWinData->GetTableName())
        m_strInitialAlias = ::rtl::OUString();

    SetHelpId(HID_CTL_QRYDGNTAB);
}

//------------------------------------------------------------------------------
OQueryTableWindow::~OQueryTableWindow()
{
    DBG_DTOR(OQueryTableWindow,NULL);
}

//------------------------------------------------------------------------------
sal_Bool OQueryTableWindow::Init()
{
    sal_Bool bSuccess = OTableWindow::Init();
    if(!bSuccess)
        return bSuccess;

    OQueryTableView* pContainer = static_cast<OQueryTableView*>(getTableView());

    // zuerst Alias bestimmen
    ::rtl::OUString strAliasName;

    OTableWindowData* pWinData = GetData();
    DBG_ASSERT(pWinData->ISA(OQueryTableWindowData), "OQueryTableWindow::Init() : habe keine OQueryTableWindowData");

    if (m_strInitialAlias.getLength() )
        // Der Alias wurde explizit mit angegeben
        strAliasName = m_strInitialAlias;
    else
    {
        ::rtl::OUString aInitialTitle = pWinData->GetTableName();
        sal_Bool bOwner	=  sal_False;
        if(GetTable().is())
        {
            ::rtl::OUString sName;
            GetTable()->getPropertyValue(PROPERTY_NAME) >>= sName;
            strAliasName = sName.getStr();
        }
    }

    // Alias mit fortlaufender Nummer versehen
    if (pContainer->CountTableAlias(strAliasName, m_nAliasNum))
    {
        strAliasName += ::rtl::OUString('_');
        strAliasName += ::rtl::OUString::valueOf(m_nAliasNum);
    }


    strAliasName = String(strAliasName).EraseAllChars('"');
    SetAliasName(strAliasName);
        // SetAliasName reicht das als WinName weiter, dadurch benutzt es die Basisklasse
    // reset the titel
    m_aTitle.SetText( pWinData->GetWinName() );
    m_aTitle.Show();

    //	sal_Bool bSuccess(sal_True);
    if (!bSuccess)
    {	// es soll nur ein Dummy-Window aufgemacht werden ...
        DBG_ASSERT(GetAliasName().getLength(), "OQueryTableWindow::Init : kein Alias- UND kein Tabellenname geht nicht !");
            // .. aber das braucht wenigstens einen Alias

        // ::com::sun::star::form::ListBox anlegen
        if (!m_pListBox)
            m_pListBox = CreateListBox();

        // Titel setzen
        m_aTitle.SetText(GetAliasName());
        m_aTitle.Show();

        clearListBox();
            // neu zu fuellen brauche ich die nicht, da ich ja keine Tabelle habe
        m_pListBox->Show();
    }

    getTableView()->getDesignView()->getController()->InvalidateFeature(ID_BROWSER_QUERY_EXECUTE);
    return bSuccess;
}
// -----------------------------------------------------------------------------
void* OQueryTableWindow::createUserData(const Reference< XPropertySet>& _xColumn,bool _bPrimaryKey)
{
    OTableFieldInfo* pInfo = new OTableFieldInfo();
    pInfo->SetKey(_bPrimaryKey ? TAB_PRIMARY_FIELD : TAB_NORMAL_FIELD);
    if ( _xColumn.is() )
        pInfo->SetDataType(::comphelper::getINT32(_xColumn->getPropertyValue(PROPERTY_TYPE)));
    return pInfo;
}
// -----------------------------------------------------------------------------
void OQueryTableWindow::deleteUserData(void*& _pUserData)
{
    delete static_cast<OTableFieldInfo*>(_pUserData);
    _pUserData = NULL;
}
//------------------------------------------------------------------------------
void OQueryTableWindow::OnEntryDoubleClicked(SvLBoxEntry* pEntry)
{
    DBG_ASSERT(pEntry != NULL, "OQueryTableWindow::OnEntryDoubleClicked : pEntry darf nicht NULL sein !");
        // man koennte das auch abfragen und dann ein return hinsetzen, aber so weist es vielleicht auf Fehler bei Aufrufer hin

    if (getTableView()->getDesignView()->getController()->isReadOnly())
        return;

    OTableFieldInfo* pInf = static_cast<OTableFieldInfo*>(pEntry->GetUserData());
    DBG_ASSERT(pInf != NULL, "OQueryTableWindow::OnEntryDoubleClicked : Feld hat keine FieldInfo !");

    // eine DragInfo aufbauen
    OTableFieldDescRef aInfo = new OTableFieldDesc(GetTableName(),m_pListBox->GetEntryText(pEntry));
    aInfo->SetTabWindow(this);
    aInfo->SetAlias(GetAliasName());
    aInfo->SetDatabase(GetComposedName());
    aInfo->SetFieldIndex(m_pListBox->GetModel()->GetAbsPos(pEntry));
    aInfo->SetDataType(pInf->GetDataType());

    // und das entsprechende Feld einfuegen
    static_cast<OQueryTableView*>(getTableView())->InsertField(aInfo);
}

//------------------------------------------------------------------------------
sal_Bool OQueryTableWindow::ExistsField(const ::rtl::OUString& strFieldName, OTableFieldDescRef& rInfo)
{
    DBG_ASSERT(m_pListBox != NULL, "OQueryTableWindow::ExistsField : habe keine ::com::sun::star::form::ListBox !");
    OSL_ENSURE(rInfo.isValid(),"OQueryTableWindow::ExistsField: invlid argument for OTableFieldDescRef!");
    Reference< XConnection> xConnection = getTableView()->getDesignView()->getController()->getConnection();
    sal_Bool bExists = sal_False;
    if(xConnection.is())
    {
        SvLBoxEntry* pEntry = m_pListBox->First();
        try
        {
            Reference<XDatabaseMetaData> xMeta = xConnection->getMetaData();
            ::comphelper::UStringMixEqual bCase(xMeta.is() && xMeta->storesMixedCaseQuotedIdentifiers());

            while (pEntry)
            {
                if (bCase(strFieldName,::rtl::OUString(m_pListBox->GetEntryText(pEntry))))
                {
                    OTableFieldInfo* pInf = static_cast<OTableFieldInfo*>(pEntry->GetUserData());
                    DBG_ASSERT(pInf != NULL, "OQueryTableWindow::ExistsField : Feld hat keine FieldInfo !");

                    rInfo->SetTabWindow(this);
                    rInfo->SetField(strFieldName);
                    rInfo->SetTable(GetTableName());
                    rInfo->SetAlias(GetAliasName());
                    rInfo->SetDatabase(GetComposedName());
                    rInfo->SetFieldIndex(m_pListBox->GetModel()->GetAbsPos(pEntry));
                    rInfo->SetDataType(pInf->GetDataType());
                    bExists = sal_True;
                    break;
                }
                pEntry = m_pListBox->Next(pEntry);
            }
        }
        catch(SQLException&)
        {
        }
    }

    return bExists;
}

//------------------------------------------------------------------------------
sal_Bool OQueryTableWindow::ExistsAVisitedConn() const
{
    return static_cast<const OQueryTableView*>(getTableView())->ExistsAVisitedConn(this);
}

//------------------------------------------------------------------------------
void OQueryTableWindow::KeyInput( const KeyEvent& rEvt )
{
    OTableWindow::KeyInput( rEvt );
}
// -----------------------------------------------------------------------------



