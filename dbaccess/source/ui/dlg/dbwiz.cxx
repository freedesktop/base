/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: dbwiz.cxx,v $
 *
 *  $Revision: 1.13 $
 *
 *  last change: $Author: rt $ $Date: 2007-04-26 07:58:29 $
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

// MARKER(update_precomp.py): autogen include statement, do not remove
#include "precompiled_dbaccess.hxx"

#ifndef DBAUI_DBWIZ_HXX
#include "dbwiz.hxx"
#endif
#ifndef _DBAUI_DBADMIN_HRC_
#include "dbadmin.hrc"
#endif
#ifndef _DBU_DLG_HRC_
#include "dbu_dlg.hrc"
#endif
#ifndef _DBAUI_MODULE_DBU_HXX_
#include "moduledbu.hxx"
#endif
#ifndef _DBAUI_DATASOURCEITEMS_HXX_
#include "dsitems.hxx"
#endif
#ifndef _SFXSTRITEM_HXX
#include <svtools/stritem.hxx>
#endif
#ifndef _SFXENUMITEM_HXX
#include <svtools/eitem.hxx>
#endif
#ifndef _SFXINTITEM_HXX
#include <svtools/intitem.hxx>
#endif
#ifndef _SV_MSGBOX_HXX
#include <vcl/msgbox.hxx>
#endif
#ifndef DBACCESS_SHARED_DBUSTRINGS_HRC
#include "dbustrings.hrc"
#endif
#ifndef _DBAUI_ADMINPAGES_HXX_
#include "adminpages.hxx"
#endif
#ifndef _DBAUI_GENERALPAGE_HXX_
#include "generalpage.hxx"
#endif
#ifndef _DBAUI_LOCALRESACCESS_HXX_
#include "localresaccess.hxx"
#endif
#ifndef _DBAUI_STRINGLISTITEM_HXX_
#include "stringlistitem.hxx"
#endif
#ifndef _DBAUI_PROPERTYSETITEM_HXX_
#include "propertysetitem.hxx"
#endif
#ifndef _UNOTOOLS_CONFIGNODE_HXX_
#include <unotools/confignode.hxx>
#endif
#ifndef DBAUI_CONNECTIONPAGE_HXX
#include "ConnectionPage.hxx"
#endif
#ifndef DBAUI_ADVANCEDPAGEDLG_HXX
#include "AdvancedPageDlg.hxx"
#endif
#ifndef DBAUI_DRIVERSETTINGS_HXX
#include "DriverSettings.hxx"
#endif
#ifndef _DBAUI_DBADMINIMPL_HXX_
#include "DbAdminImpl.hxx"
#endif
#ifndef _DBA_DBACCESS_HELPID_HRC_
#include "dbaccess_helpid.hrc"
#endif

//.........................................................................
namespace dbaui
{
//.........................................................................
using namespace svt;
using namespace com::sun::star::uno;
using namespace com::sun::star::sdbc;
using namespace com::sun::star::lang;
using namespace com::sun::star::util;
using namespace com::sun::star::beans;
using namespace com::sun::star::container;

#define START_PAGE			            0
#define CONNECTION_PAGE		            1
#define ADDITIONAL_PAGE_DBASE     		2
#define ADDITIONAL_PAGE_FLAT            3
#define ADDITIONAL_PAGE_LDAP            4
#define ADDITIONAL_PAGE_ADABAS          5
#define ADDITIONAL_PAGE_MYSQL_JDBC      6
#define ADDITIONAL_PAGE_MYSQL_ODBC	    7
#define ADDITIONAL_PAGE_ORACLE_JDBC     8
#define ADDITIONAL_PAGE_ADO             9
#define ADDITIONAL_PAGE_ODBC           10
#define ADDITIONAL_USERDEFINED         11


DBG_NAME(ODbTypeWizDialog)
//=========================================================================
//= ODbTypeWizDialog
//=========================================================================
//-------------------------------------------------------------------------
ODbTypeWizDialog::ODbTypeWizDialog(Window* _pParent
                               ,SfxItemSet* _pItems
                               ,const Reference< XMultiServiceFactory >& _rxORB
                               ,const ::com::sun::star::uno::Any& _aDataSourceName
                               )
    :OWizardMachine(_pParent, ModuleRes(DLG_DATABASE_TYPE_CHANGE), WZB_NEXT | WZB_PREVIOUS | WZB_FINISH | WZB_CANCEL | WZB_HELP, sal_True)
    ,m_pOutSet(NULL)
    ,m_bResetting(sal_False)
    ,m_bApplied(sal_False)
    ,m_bUIEnabled( sal_True )
{
    DBG_CTOR(ODbTypeWizDialog,NULL);	
    m_pImpl = ::std::auto_ptr<ODbDataSourceAdministrationHelper>(new ODbDataSourceAdministrationHelper(_rxORB,this,this));
    m_pImpl->setDataSourceOrName(_aDataSourceName);
    Reference< XPropertySet > xDatasource = m_pImpl->getCurrentDataSource();
    m_pOutSet = new SfxItemSet( *_pItems->GetPool(), _pItems->GetRanges() );

    m_pImpl->translateProperties(xDatasource, *m_pOutSet);
    m_eType = m_pImpl->getDatasourceType(*m_pOutSet);

    SetPageSizePixel(LogicToPixel(::Size(PAGE_X, PAGE_Y), MAP_APPFONT));
    ShowButtonFixedLine(sal_True);
    defaultButton(WZB_NEXT);
    enableButtons(WZB_FINISH, sal_False);
    
    m_pPrevPage->SetHelpId(HID_DBWIZ_PREVIOUS);
    m_pNextPage->SetHelpId(HID_DBWIZ_NEXT);
    m_pCancel->SetHelpId(HID_DBWIZ_CANCEL);
    m_pFinish->SetHelpId(HID_DBWIZ_FINISH);
    m_pHelp->SetUniqueId(UID_DBWIZ_HELP);
    // no local resources needed anymore
    FreeResource();
    ActivatePage();
}

//-------------------------------------------------------------------------
ODbTypeWizDialog::~ODbTypeWizDialog()
{
    DBG_DTOR(ODbTypeWizDialog,NULL);	
    delete m_pOutSet;	
}
//-------------------------------------------------------------------------
IMPL_LINK(ODbTypeWizDialog, OnTypeSelected, OGeneralPage*, _pTabPage)
{
    m_eType = _pTabPage->GetSelectedType();
    switch(m_eType)
    {
        case DST_MOZILLA:
        case DST_OUTLOOK:
        case DST_OUTLOOKEXP:
        case DST_EVOLUTION:
        case DST_KAB:
            enableButtons(WZB_NEXT,sal_False);
            enableButtons(WZB_FINISH,sal_True);
            break;
        default:
            enableButtons(WZB_NEXT,sal_True);
            enableButtons(WZB_FINISH,sal_False);
            break;
    }
    return 1L;
}
//-------------------------------------------------------------------------
WizardTypes::WizardState ODbTypeWizDialog::determineNextState(WizardState _nCurrentState)
{
    WizardTypes::WizardState nNextState = WZS_INVALID_STATE;
    switch(_nCurrentState)
    {
        case START_PAGE:
            switch(m_eType)
            {
                case DST_MOZILLA:
                case DST_OUTLOOK:
                case DST_OUTLOOKEXP:
                case DST_EVOLUTION:
                case DST_KAB:
                    nNextState = WZS_INVALID_STATE;
                    break;
                default:
                    nNextState = CONNECTION_PAGE;
                    break;
            }
            break;
        case CONNECTION_PAGE:
            switch(m_eType)
            {
                case DST_MOZILLA:
                case DST_THUNDERBIRD:
                case DST_OUTLOOK:
                case DST_OUTLOOKEXP:
                case DST_EVOLUTION:
                case DST_KAB:
                case DST_MSACCESS:
                case DST_JDBC:
                case DST_CALC:
                    nNextState = WZS_INVALID_STATE;
                    break;
                case DST_DBASE:
                    nNextState = ADDITIONAL_PAGE_DBASE;
                    break;
                case DST_FLAT:
                    nNextState = ADDITIONAL_PAGE_FLAT;
                    break;
                case DST_LDAP:
                    nNextState = ADDITIONAL_PAGE_LDAP;
                    break;
                case DST_ADABAS:
                    nNextState = ADDITIONAL_PAGE_ADABAS;
                    break;
                case DST_MYSQL_JDBC:
                    nNextState = ADDITIONAL_PAGE_MYSQL_JDBC;
                    break;
                case DST_MYSQL_ODBC:
                    nNextState = ADDITIONAL_PAGE_MYSQL_ODBC;
                    break;
                case DST_ORACLE_JDBC:
                    nNextState = ADDITIONAL_PAGE_ORACLE_JDBC;
                    break;
                case DST_ADO:
                    nNextState = ADDITIONAL_PAGE_ADO;
                    break;
                case DST_ODBC:
                    nNextState = ADDITIONAL_PAGE_ODBC;
                    break;
                default:
                    nNextState = WZS_INVALID_STATE;
                    break;
            }
            break;
    }

    return nNextState;
}

//-------------------------------------------------------------------------
void ODbTypeWizDialog::resetPages(const Reference< XPropertySet >& _rxDatasource)
{
    // remove all items which relate to indirect properties from the input set
    // (without this, the following may happen: select an arbitrary data source where some indirect properties
    // are set. Select another data source of the same type, where the indirect props are not set (yet). Then,
    // the indirect property values of the first ds are shown in the second ds ...)
    const ODbDataSourceAdministrationHelper::MapInt2String& rMap = m_pImpl->getIndirectProperties();
    for	(	ODbDataSourceAdministrationHelper::ConstMapInt2StringIterator aIndirect = rMap.begin();
            aIndirect != rMap.end();
            ++aIndirect
        )
        getWriteOutputSet()->ClearItem( (sal_uInt16)aIndirect->first );

    // extract all relevant data from the property set of the data source
    m_pImpl->translateProperties(_rxDatasource, *getWriteOutputSet());
}
//-------------------------------------------------------------------------
ODbTypeWizDialog::ApplyResult ODbTypeWizDialog::implApplyChanges()
{
    if ( !m_pImpl->saveChanges(*m_pOutSet) )
        return AR_KEEP;

    m_bApplied = sal_True;

    return AR_LEAVE_MODIFIED;
}
// -----------------------------------------------------------------------------
const SfxItemSet* ODbTypeWizDialog::getOutputSet() const
{
    return m_pOutSet;
}
// -----------------------------------------------------------------------------
SfxItemSet* ODbTypeWizDialog::getWriteOutputSet()
{
    return m_pOutSet;
}
// -----------------------------------------------------------------------------
::std::pair< Reference<XConnection>,sal_Bool> ODbTypeWizDialog::createConnection()
{
    return m_pImpl->createConnection();
}
// -----------------------------------------------------------------------------
Reference< XMultiServiceFactory > ODbTypeWizDialog::getORB()
{
    return m_pImpl->getORB();
}
// -----------------------------------------------------------------------------
Reference< XDriver > ODbTypeWizDialog::getDriver()
{
    return m_pImpl->getDriver();
}
// -----------------------------------------------------------------------------
DATASOURCE_TYPE	ODbTypeWizDialog::getDatasourceType(const SfxItemSet& _rSet) const
{
    return m_pImpl->getDatasourceType(_rSet);
}
// -----------------------------------------------------------------------------
void ODbTypeWizDialog::clearPassword()
{
    m_pImpl->clearPassword();
}

// -----------------------------------------------------------------------------
TabPage* ODbTypeWizDialog::createPage(WizardState _nState)
{
    USHORT nStringId = STR_PAGETITLE_ADVANCED;
    TabPage* pPage = NULL;
    switch(_nState)
    {
        case START_PAGE: // start state
        {
            pPage = OGeneralPage::Create(this,*m_pOutSet);
            OGeneralPage* pGeneralPage = static_cast< OGeneralPage* >( pPage );
            pGeneralPage->SetTypeSelectHandler( LINK( this, ODbTypeWizDialog, OnTypeSelected));
//            pGeneralPage->SetCreationModeHandler( LINK( this, ODbTypeWizDialog, TODO ) );
            nStringId = STR_PAGETITLE_GENERAL;
        }
        break;
        case CONNECTION_PAGE:
            pPage = OConnectionTabPage::Create(this,*m_pOutSet);
            nStringId = STR_PAGETITLE_CONNECTION;
            break;

        case ADDITIONAL_PAGE_DBASE:
            pPage = ODriversSettings::CreateDbase(this,*m_pOutSet);
            break;
        case ADDITIONAL_PAGE_FLAT:
            pPage = ODriversSettings::CreateText(this,*m_pOutSet);
            break;
        case ADDITIONAL_PAGE_LDAP:
            pPage = ODriversSettings::CreateLDAP(this,*m_pOutSet);
            break;
        case ADDITIONAL_PAGE_ADABAS:
            pPage = ODriversSettings::CreateAdabas(this,*m_pOutSet);
            break;
        case ADDITIONAL_PAGE_MYSQL_JDBC:
            pPage = ODriversSettings::CreateMySQLJDBC(this,*m_pOutSet);
            break;
        case ADDITIONAL_PAGE_MYSQL_ODBC:
            pPage = ODriversSettings::CreateMySQLODBC(this,*m_pOutSet);
            break;
        case ADDITIONAL_PAGE_ORACLE_JDBC:
            pPage = ODriversSettings::CreateOracleJDBC(this,*m_pOutSet);
            break;
        case ADDITIONAL_PAGE_ADO:
            pPage = ODriversSettings::CreateAdo(this,*m_pOutSet);
            break;
        case ADDITIONAL_PAGE_ODBC:
            pPage = ODriversSettings::CreateODBC(this,*m_pOutSet);
            break;
        case ADDITIONAL_USERDEFINED:
            pPage = ODriversSettings::CreateUser(this,*m_pOutSet);
            break;
        default:
            OSL_ENSURE(0,"Wrong state!");
            break;
    }

    // register ourself as modified listener
    if ( pPage )
    {		
        static_cast<OGenericAdministrationPage*>(pPage)->SetServiceFactory(m_pImpl->getORB());
        static_cast<OGenericAdministrationPage*>(pPage)->SetAdminDialog(this,this);
        // open our own resource block, as the page titles are strings local to this block
        LocalResourceAccess aDummy(DLG_DATABASE_ADMINISTRATION, RSC_TABDIALOG);

        pPage->SetText(String(ModuleRes(nStringId)));
        defaultButton( _nState == START_PAGE ? WZB_NEXT : WZB_FINISH );
        enableButtons( WZB_FINISH, _nState == START_PAGE ? sal_False : sal_True);
        pPage->Show();
    }
    return pPage;
}
// -----------------------------------------------------------------------------
sal_Bool ODbTypeWizDialog::leaveState(WizardState _nState)
{
    SfxTabPage* pPage = static_cast<SfxTabPage*>(WizardDialog::GetPage(_nState));
    if ( pPage )
        pPage->FillItemSet(*m_pOutSet);
    return sal_True;
}
// -----------------------------------------------------------------------------
void ODbTypeWizDialog::setTitle(const ::rtl::OUString& _sTitle)
{
    SetText(_sTitle);
}
//-------------------------------------------------------------------------
sal_Bool ODbTypeWizDialog::saveDatasource()
{
    SfxTabPage* pPage = static_cast<SfxTabPage*>(WizardDialog::GetPage(getCurrentState()));
    if ( pPage )
        pPage->FillItemSet(*m_pOutSet);
    return sal_True;
}
// -----------------------------------------------------------------------------
IWizardPage* ODbTypeWizDialog::getWizardPage(TabPage* _pCurrentPage) const
{
    OGenericAdministrationPage* pPage = static_cast<OGenericAdministrationPage*>(_pCurrentPage);
    return pPage;
}
// -----------------------------------------------------------------------------
sal_Bool ODbTypeWizDialog::onFinish(sal_Int32 _nResult)
{
    saveDatasource();
    return m_pImpl->saveChanges(*m_pOutSet) ? OWizardMachine::onFinish(_nResult) : sal_False;
}
//.........................................................................
}	// namespace dbaui
//.........................................................................

