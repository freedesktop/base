/*************************************************************************
 *
 *  $RCSfile: DBSetupConnectionPages.cxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: vg $ $Date: 2005-03-10 16:47:54 $
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
 *  Source License Version 1.1 (the "License"); You may not use this file
 *  except in compliance with the License. You may obtain a copy of the
 *  License at http://www.openoffice.org/license.html.
 *
 *  Software provided under this License is provided on an "AS IS" basis,
 *  WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING,
 *  WITHOUT LIMITATION, WARRANTIES THAT THE SOFTWARE IS FREE OF DEFECTS,
 *  MERCHANTABLE, FIT FOR A PARTICULAR PURPOSE, OR NON-INFRINGING.
 *  See the License for the specific provisions governing your rights and
 *  obligations concerning the Software.
 *
 *  The Initial Developer of the Original Code is: Sun Microsystems, Inc..
 *
 *  Copyright: 2000 by Sun Microsystems, Inc.
 *
 *  All Rights Reserved.
 *
 *  Contributor(s): Ocke Janssen
 *
 *
 ************************************************************************/
#ifndef DBAUI_DBSETUPCONNECTIONPAGES_HXX
#include "DBSetupConnectionPages.hxx"
#endif
#ifndef _DBAUI_MODULE_DBU_HXX_
#include "moduledbu.hxx"
#endif
#ifndef _DBAUI_SQLMESSAGE_HXX_
#include "sqlmessage.hxx"
#endif
#ifndef _DBU_RESOURCE_HRC_
#include "dbu_resource.hrc"
#endif
#ifndef _DBAUI_AUTOCONTROLS_HRC_
#include "AutoControls.hrc"
#endif
#ifndef _DBAUI_DBADMINSETUP_HRC_
#include "dbadminsetup.hrc"
#endif
#ifndef _SFXITEMSET_HXX 
#include <svtools/itemset.hxx>
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
#ifndef _DBAUI_DATASOURCEITEMS_HXX_
#include "dsitems.hxx"
#endif
#ifndef _DBA_DBACCESS_HELPID_HRC_
#include "dbaccess_helpid.hrc"
#endif
#ifndef _DBAUI_LOCALRESACCESS_HXX_
#include "localresaccess.hxx"
#endif
#ifndef _SV_MSGBOX_HXX
#include <vcl/msgbox.hxx>
#endif
#ifndef _SV_MNEMONIC_HXX
#include <vcl/mnemonic.hxx>
#endif
#ifndef _SVTOOLS_CJKOPTIONS_HXX
#include <svtools/cjkoptions.hxx>
#endif
#include <jvmaccess/virtualmachine.hxx>
#ifndef _CONNECTIVITY_COMMONTOOLS_HXX_
#include <connectivity/CommonTools.hxx>
#endif
#ifndef DBAUI_DRIVERSETTINGS_HXX
#include "DriverSettings.hxx"
#endif
#ifndef _DBAUI_DBADMIN_HXX_
#include "dbadmin.hxx"
#endif
#ifndef _COMPHELPER_TYPES_HXX_
#include <comphelper/types.hxx>
#endif

#ifndef _COM_SUN_STAR_UI_DIALOGS_XFOLDERPICKER_HPP_
#include <com/sun/star/ui/dialogs/XFolderPicker.hpp>
#endif
// #106016# ------------------------------------
#ifndef _COM_SUN_STAR_TASK_XINTERACTIONHANDLER_HPP_
#include <com/sun/star/task/XInteractionHandler.hpp>
#endif

#ifndef SVTOOLS_FILENOTATION_HXX_
#include <svtools/filenotation.hxx>
#endif

#ifndef _UNOTOOLS_LOCALFILEHELPER_HXX
#include <unotools/localfilehelper.hxx>
#endif
#ifndef _UNOTOOLS_UCBHELPER_HXX
#include <unotools/ucbhelper.hxx>
#endif
#ifndef _UCBHELPER_COMMANDENVIRONMENT_HXX
#include <ucbhelper/commandenvironment.hxx>
#endif
#ifndef DBAUI_FILEPICKER_INTERACTION_HXX
#include "finteraction.hxx"
#endif
#ifndef _CONNECTIVITY_COMMONTOOLS_HXX_
#include <connectivity/CommonTools.hxx>
#endif

#ifndef _DBA_DBACCESS_HELPID_HRC_
#include "dbaccess_helpid.hrc"
#endif

#ifndef INCLUDED_SVTOOLS_PATHOPTIONS_HXX
#include <svtools/pathoptions.hxx>
#endif

#ifndef SVTOOLS_INC_ROADMAPWIZARD_HXX
#include <svtools/roadmapwizard.hxx>
#endif

#ifndef DBAUI_TEXTCONNECTIONHELPER_HXX
#include "TextConnectionHelper.hxx"
#endif


//.........................................................................
namespace dbaui
{
//.........................................................................
//	using namespace ::com::sun::star::uno;
//	using namespace ::com::sun::star::ucb;
//	using namespace ::com::sun::star::ui::dialogs;
//	using namespace ::com::sun::star::sdbc;
//	using namespace ::com::sun::star::beans;
//	using namespace ::com::sun::star::lang;
//	using namespace ::com::sun::star::container;
//	using namespace ::dbtools;
//	using namespace ::svt;

    OGenericAdministrationPage*	OTextConnectionPageSetup::CreateTextTabPage( Window* pParent, const SfxItemSet& _rAttrSet )
    {
        return ( new OTextConnectionPageSetup( pParent, _rAttrSet ) );
    }


    //========================================================================
    //= OTextConnectionPageSetup
    //========================================================================
    //------------------------------------------------------------------------
    OTextConnectionPageSetup::OTextConnectionPageSetup( Window* pParent, const SfxItemSet& _rCoreAttrs )
        :OConnectionTabPageSetup(pParent, PAGE_DBWIZARD_TEXT, _rCoreAttrs, STR_TEXT_HELPTEXT, STR_TEXT_HEADERTEXT, STR_TEXT_PATH_OR_FILE)
    {
        m_pTextConnectionHelper = new OTextConnectionHelper(this, PAGE_DBWIZARD_TEXT, sal_True);
        m_pTextConnectionHelper->SetClickHandler(LINK( this, OTextConnectionPageSetup, ImplGetExtensionHdl ) );

        m_pTextConnectionHelper->m_aDecimalSeparator.SetPosPixel( MovePoint( m_pTextConnectionHelper->m_aDecimalSeparator.GetPosPixel(), 0, -14 ) );
        m_pTextConnectionHelper->m_aDecimalSeparatorLabel.SetPosPixel( MovePoint( m_pTextConnectionHelper->m_aDecimalSeparatorLabel.GetPosPixel(), 0, -14 ) );
        m_pTextConnectionHelper->m_aFieldSeparator.SetPosPixel( MovePoint( m_pTextConnectionHelper->m_aFieldSeparator.GetPosPixel(), 0, -14 ) );
        m_pTextConnectionHelper->m_aFieldSeparatorLabel.SetPosPixel( MovePoint( m_pTextConnectionHelper->m_aFieldSeparatorLabel.GetPosPixel(), 0, -14 ) );
        m_pTextConnectionHelper->m_aTextSeparator.SetPosPixel( MovePoint( m_pTextConnectionHelper->m_aTextSeparator.GetPosPixel(), 0, -14 ) );
        m_pTextConnectionHelper->m_aTextSeparatorLabel.SetPosPixel( MovePoint( m_pTextConnectionHelper->m_aTextSeparatorLabel.GetPosPixel(), 0, -14 ) );
        m_pTextConnectionHelper->m_aThousandsSeparator.SetPosPixel( MovePoint( m_pTextConnectionHelper->m_aThousandsSeparator.GetPosPixel(), 0, -14 ) );
        m_pTextConnectionHelper->m_aThousandsSeparatorLabel.SetPosPixel( MovePoint( m_pTextConnectionHelper->m_aThousandsSeparatorLabel.GetPosPixel(), 0, -14 ) );
        FreeResource();
    }


    // -----------------------------------------------------------------------
    OTextConnectionPageSetup::~OTextConnectionPageSetup()
    {
        DELETEZ(m_pTextConnectionHelper);
    }   

    IMPL_LINK(OTextConnectionPageSetup, ImplGetExtensionHdl, OTextConnectionHelper*, _pTextConnectionHelper)
    {                            
        sal_Bool bRoadmapState = GetRoadmapStateValue();
        SetRoadmapStateValue((m_pTextConnectionHelper->GetExtension().Len() > 0) && OConnectionTabPageSetup::checkTestConnection());
        callModifiedHdl();
        return sal_True;
    }


    bool OTextConnectionPageSetup::checkTestConnection()
    {
        bool bDoEnable = OConnectionTabPageSetup::checkTestConnection();
        bDoEnable = (m_pTextConnectionHelper->GetExtension().Len() > 0) && bDoEnable;
        return bDoEnable;
    }

    // -----------------------------------------------------------------------
    void OTextConnectionPageSetup::fillControls(::std::vector< ISaveValueWrapper* >& _rControlList)
    {
        OConnectionTabPageSetup::fillControls(_rControlList);
        m_pTextConnectionHelper->fillControls(_rControlList);
    }
    // -----------------------------------------------------------------------
    void OTextConnectionPageSetup::fillWindows(::std::vector< ISaveValueWrapper* >& _rControlList)
    {
        OConnectionTabPageSetup::fillWindows(_rControlList);
        m_pTextConnectionHelper->fillWindows(_rControlList);
    }
    // -----------------------------------------------------------------------
    void OTextConnectionPageSetup::implInitControls(const SfxItemSet& _rSet, sal_Bool _bSaveValue)
    {
        // first check whether or not the selection is invalid or readonly (invalid implies readonly, but not vice versa)
        sal_Bool bValid, bReadonly;
        getFlags(_rSet, bValid, bReadonly);
        OConnectionTabPageSetup::implInitControls( _rSet, _bSaveValue);
        m_pTextConnectionHelper->implInitControls(_rSet, _bSaveValue, bValid);
    }


    // -----------------------------------------------------------------------
    sal_Bool OTextConnectionPageSetup::FillItemSet( SfxItemSet& _rSet )
    {
        sal_Bool bChangedSomething = OConnectionTabPageSetup::FillItemSet(_rSet);
        bChangedSomething = m_pTextConnectionHelper->FillItemSet(_rSet, bChangedSomething);
        return bChangedSomething;
    }

    
    sal_Bool OTextConnectionPageSetup::checkItems(){
        return m_pTextConnectionHelper->checkItems();
    }


    OGenericAdministrationPage*	OLDAPConnectionPageSetup::CreateLDAPTabPage( Window* pParent, const SfxItemSet& _rAttrSet )
    {
        return ( new OLDAPConnectionPageSetup( pParent, _rAttrSet ) );
    }


    //========================================================================
    //= OLDAPPageSetup
    //========================================================================
    OLDAPConnectionPageSetup::OLDAPConnectionPageSetup( Window* pParent, const SfxItemSet& _rCoreAttrs )
        :OGenericAdministrationPage(pParent, ModuleRes(PAGE_DBWIZARD_LDAP), _rCoreAttrs)
        ,m_aFTHeaderText        (this, ResId(FT_LDAP_HEADERTEXT))
        ,m_aFTHelpText          (this, ResId(FT_LDAP_HELPTEXT))
        ,m_aFTHostServer	    (this, ResId(FT_AUTOHOSTNAME))
        ,m_aETHostServer	    (this, ResId(ET_AUTOHOSTNAME))
        ,m_aFTBaseDN			(this, ResId(FT_AUTOBASEDN))
        ,m_aETBaseDN		    (this, ResId(ET_AUTOBASEDN))
        ,m_aFTPortNumber		(this, ResId(FT_AUTOPORTNUMBER))
        ,m_aNFPortNumber	    (this, ResId(NF_AUTOPORTNUMBER))
        ,m_aFTDefaultPortNumber (this, ResId(FT_AUTOPORTNUMBERDEFAULT))
        ,m_aCBUseSSL            (this, ResId(CB_USESSL))

    {
        SetControlFontWeight(&m_aFTHeaderText);
        m_aFTDefaultPortNumber.SetText(String(ModuleRes(STR_LDAP_DEFAULT)));
        m_aETHostServer.SetModifyHdl(getControlModifiedLink());
        m_aETBaseDN.SetModifyHdl(getControlModifiedLink());
        m_aNFPortNumber.SetModifyHdl(getControlModifiedLink());
        m_aCBUseSSL.SetToggleHdl(getControlModifiedLink());
        // #98982# OJ
        m_aNFPortNumber.SetUseThousandSep(sal_False);
        SetRoadmapStateValue(sal_False);
        FreeResource();
    }

    // -----------------------------------------------------------------------
    /* OGenericAdministrationPage*	ODriversSettings::CreateLDAP( Window* pParent, const SfxItemSet& _rAttrSet )
    {
        return ( new OLDAPConnectionPageSetup( pParent, _rAttrSet ) );
    }*/

    // -----------------------------------------------------------------------
    sal_Bool OLDAPConnectionPageSetup::FillItemSet( SfxItemSet& _rSet )
    {
           sal_Bool bChangedSomething = sal_False;
        fillString(_rSet,&m_aETBaseDN,DSID_CONN_LDAP_BASEDN, bChangedSomething);
        fillInt32(_rSet,&m_aNFPortNumber,DSID_CONN_LDAP_PORTNUMBER,bChangedSomething);

        if ( m_aETHostServer.GetText() != m_aETHostServer.GetSavedValue() )
        {
            DbuTypeCollectionItem* pCollectionItem = PTR_CAST(DbuTypeCollectionItem, _rSet.GetItem(DSID_TYPECOLLECTION));
            ODsnTypeCollection* pCollection = NULL;
            if (pCollectionItem)
                pCollection = pCollectionItem->getCollection();
            DBG_ASSERT(pCollection, "OLDAPConnectionPageSetup::FillItemSet : really need a DSN type collection !");

            String sUrl = pCollection->getDatasourcePrefix(DST_LDAP);
            sUrl += m_aETHostServer.GetText();
            _rSet.Put(SfxStringItem(DSID_CONNECTURL, sUrl));
            bChangedSomething = sal_True;
        }

        // fillString(_rSet,&m_aETHostServer, DSID_CONNECTURL, bChangedSomething);
        fillBool(_rSet,&m_aCBUseSSL,DSID_CONN_LDAP_USESSL,bChangedSomething);
        return bChangedSomething;
    }
    // -----------------------------------------------------------------------
    void OLDAPConnectionPageSetup::fillControls(::std::vector< ISaveValueWrapper* >& _rControlList)
    {
        _rControlList.push_back(new OSaveValueWrapper<Edit>(&m_aETHostServer));
        _rControlList.push_back(new OSaveValueWrapper<Edit>(&m_aETBaseDN));
        _rControlList.push_back(new OSaveValueWrapper<NumericField>(&m_aNFPortNumber));
        _rControlList.push_back(new OSaveValueWrapper<CheckBox>(&m_aCBUseSSL));
    }
    // -----------------------------------------------------------------------
    void OLDAPConnectionPageSetup::fillWindows(::std::vector< ISaveValueWrapper* >& _rControlList)
    {
        _rControlList.push_back(new ODisableWrapper<FixedText>(&m_aFTHelpText));
        _rControlList.push_back(new ODisableWrapper<FixedText>(&m_aFTHostServer));
        _rControlList.push_back(new ODisableWrapper<FixedText>(&m_aFTBaseDN));
        _rControlList.push_back(new ODisableWrapper<FixedText>(&m_aFTPortNumber));
        _rControlList.push_back(new ODisableWrapper<FixedText>(&m_aFTDefaultPortNumber));
    }
    // -----------------------------------------------------------------------
    void OLDAPConnectionPageSetup::implInitControls(const SfxItemSet& _rSet, sal_Bool _bSaveValue)
    {
        // check whether or not the selection is invalid or readonly (invalid implies readonly, but not vice versa)
        sal_Bool bValid, bReadonly;
        getFlags(_rSet, bValid, bReadonly);


        SFX_ITEMSET_GET(_rSet, pBaseDN, SfxStringItem, DSID_CONN_LDAP_BASEDN, sal_True);
        SFX_ITEMSET_GET(_rSet, pPortNumber, SfxInt32Item, DSID_CONN_LDAP_PORTNUMBER, sal_True);

        if ( bValid ) 
        {
            m_aETBaseDN.SetText(pBaseDN->GetValue());
            m_aNFPortNumber.SetValue(pPortNumber->GetValue());
        }
           OGenericAdministrationPage::implInitControls(_rSet, _bSaveValue);	
        callModifiedHdl();
    }

    // -----------------------------------------------------------------------
    IMPL_LINK(OLDAPConnectionPageSetup, OnEditModified, Edit*, _pEdit)
    {
        sal_Bool bRoadmapState = ((m_aETHostServer.GetText().Len() != 0 ) && ( m_aETBaseDN.GetText().Len() != 0 ) && (m_aFTPortNumber.GetText().Len() != 0 ));
        SetRoadmapStateValue(bRoadmapState);
        callModifiedHdl();
        return 0L;
    }


    // ----------------------------------------------------------------------- //OGenericAdministrationPage*
    OMySQLIntroPageSetup* OMySQLIntroPageSetup::CreateMySQLIntroTabPage( Window* _pParent, const SfxItemSet& _rAttrSet )
    {
        return ( new OMySQLIntroPageSetup( _pParent, _rAttrSet) );
    }

    
    OMySQLIntroPageSetup::OMySQLIntroPageSetup( Window* pParent, const SfxItemSet& _rCoreAttrs )
            :OGenericAdministrationPage(pParent, ModuleRes(PAGE_DBWIZARD_MYSQL_INTRO), _rCoreAttrs)
            , m_aFT_Headertext(this, ResId(FT_MYSQL_HEADERTEXT))
            , m_aFT_Helptext(this, ResId(FT_MYSQL_HELPTEXT))
            , m_aFT_ConnectionMode(this, ResId(FT_MYSQLCONNECTIONMODE))
            , m_aRB_ODBCDatabase(this, ResId(RB_CONNECTVIAODBC))
            , m_aRB_JDBCDatabase(this, ResId(RB_CONNECTVIAJDBC))
    {
        SetControlFontWeight(&m_aFT_Headertext);
           m_aRB_JDBCDatabase.SetToggleHdl(LINK(this, OMySQLIntroPageSetup, OnSetupModeSelected));
        m_aRB_JDBCDatabase.SetState(sal_True);
        FreeResource();
    }

    IMPL_LINK(OMySQLIntroPageSetup, OnSetupModeSelected, RadioButton*, _pBox){
        maClickHdl.Call( this );
        return true;
    }

    // -----------------------------------------------------------------------
    OMySQLIntroPageSetup::~OMySQLIntroPageSetup()
    {
    }


    // -----------------------------------------------------------------------
    void OMySQLIntroPageSetup::implInitControls(const SfxItemSet& _rSet, sal_Bool _bSaveValue)
    {
        
    }


    // -----------------------------------------------------------------------
    void OMySQLIntroPageSetup::fillControls(::std::vector< ISaveValueWrapper* >& _rControlList)
    {
    }

    // -----------------------------------------------------------------------
    void OMySQLIntroPageSetup::fillWindows(::std::vector< ISaveValueWrapper* >& _rControlList)
    {
    }


    BOOL OMySQLIntroPageSetup::FillItemSet(SfxItemSet& _rSet)
    {
        OSL_ENSURE(sal_False,"Who called me?! Please ask oj for more information.");
        return sal_True;
    }


    int OMySQLIntroPageSetup::getMySQLMode()
    {
        if (m_aRB_JDBCDatabase.IsChecked())
            return 1;
        else
            return 0;
    }


    // -----------------------------------------------------------------------
    OGenericAdministrationPage*	OGeneralSpecialJDBCConnectionPageSetup::CreateMySQLJDBCTabPage( Window* pParent, const SfxItemSet& _rAttrSet )
    {
        return ( new OGeneralSpecialJDBCConnectionPageSetup( pParent, 
                                                         PAGE_DBWIZARD_MYSQL_JDBC, 
                                                         _rAttrSet,
                                                         DSID_MYSQL_PORTNUMBER ,
                                                         STR_MYSQL_DEFAULT,
                                                         "com.mysql.jdbc.Driver", 
                                                         STR_MYSQLJDBC_HELPTEXT, 
                                                         STR_MYSQLJDBC_HEADERTEXT,
                                                         STR_MYSQL_DRIVERCLASSTEXT) );
    }


    // -----------------------------------------------------------------------
    OGenericAdministrationPage*	OGeneralSpecialJDBCConnectionPageSetup::CreateOracleJDBCTabPage( Window* pParent, const SfxItemSet& _rAttrSet )
    {
        return ( new OGeneralSpecialJDBCConnectionPageSetup( pParent, 
                                                          PAGE_DBWIZARD_ORACLE, 
                                                          _rAttrSet, 
                                                          DSID_ORACLE_PORTNUMBER,
                                                          STR_ORACLE_DEFAULT, 
                                                          "oracle.jdbc.driver.OracleDriver", 
                                                          STR_ORACLE_HELPTEXT, 
                                                          STR_ORACLE_HEADERTEXT,
                                                          STR_ORACLE_DRIVERCLASSTEXT) );
    }


    //========================================================================
    //= OMySQLJDBCConnectionPageSetup
    //========================================================================
    OGeneralSpecialJDBCConnectionPageSetup::OGeneralSpecialJDBCConnectionPageSetup( Window* pParent,USHORT _nResId, const SfxItemSet& _rCoreAttrs ,USHORT _nPortId, USHORT _nDefaultPortResId, char* _pDriverName, USHORT _nHelpTextResId, USHORT _nHeaderTextResId, USHORT _nDriverClassId)
        :OGenericAdministrationPage(pParent, ModuleRes(_nResId), _rCoreAttrs)
        ,m_pFTHeaderText        (NULL)
        ,m_aFTHelpText          (this, ResId(FT_AUTOWIZARDHELPTEXT))
        ,m_aFTDatabasename	    (this, ResId(FT_AUTODATABASENAME))
        ,m_aETDatabasename	    (this, ResId(ET_AUTODATABASENAME))
        ,m_aFTHostname		    (this, ResId(FT_AUTOHOSTNAME))
        ,m_aETHostname		    (this, ResId(ET_AUTOHOSTNAME))
        ,m_aFTPortNumber	    (this, ResId(FT_AUTOPORTNUMBER))
        ,m_aNFPortNumber	    (this, ResId(NF_AUTOPORTNUMBER))
        ,m_aFTDriverClass	    (this, ResId(FT_AUTOJDBCDRIVERCLASS))
        ,m_aETDriverClass	    (this, ResId(ET_AUTOJDBCDRIVERCLASS))
        ,m_aPBTestJavaDriver	(this, ResId(PB_AUTOTESTDRIVERCLASS))
        ,m_aFTDefaultPortNumber (this, ResId(FT_AUTOPORTNUMBERDEFAULT))
        ,m_nPortId(_nPortId)
    {
        if (_nDriverClassId != -1)
            m_aFTDriverClass.SetText(String(ModuleRes(_nDriverClassId)));
        m_aFTDefaultPortNumber.SetText(String(ModuleRes(_nDefaultPortResId)));
        String sHelpText = String(ModuleRes(_nHelpTextResId));
        m_aFTHelpText.SetText(sHelpText);
        //TODO this code snippet is redundant
        SetHeaderText(this, FT_AUTOWIZARDHEADER, _nHeaderTextResId); 

        m_aETDatabasename.SetModifyHdl(getControlModifiedLink());
        m_aETHostname.SetModifyHdl(getControlModifiedLink());
        m_aNFPortNumber.SetModifyHdl(getControlModifiedLink());

        m_aETDriverClass.SetModifyHdl(LINK(this, OGeneralSpecialJDBCConnectionPageSetup, OnEditModified));
        m_aPBTestJavaDriver.SetClickHdl(LINK(this,OGeneralSpecialJDBCConnectionPageSetup,OnTestJavaClickHdl));
        
        m_aNFPortNumber.SetUseThousandSep(sal_False);
        m_sDefaultJdbcDriverName = String::CreateFromAscii(_pDriverName);
        SetRoadmapStateValue(sal_False);
        FreeResource();
    }


    // -----------------------------------------------------------------------
    void OGeneralSpecialJDBCConnectionPageSetup::fillControls(::std::vector< ISaveValueWrapper* >& _rControlList)
    {
        _rControlList.push_back(new OSaveValueWrapper<Edit>(&m_aETDatabasename));
        _rControlList.push_back(new OSaveValueWrapper<Edit>(&m_aETDriverClass));
        _rControlList.push_back(new OSaveValueWrapper<Edit>(&m_aETHostname));
        _rControlList.push_back(new OSaveValueWrapper<NumericField>(&m_aNFPortNumber));
    }
    // -----------------------------------------------------------------------
    void OGeneralSpecialJDBCConnectionPageSetup::fillWindows(::std::vector< ISaveValueWrapper* >& _rControlList)
    {
        _rControlList.push_back(new ODisableWrapper<FixedText>(&m_aFTHelpText));
        _rControlList.push_back(new ODisableWrapper<FixedText>(&m_aFTDatabasename));
        _rControlList.push_back(new ODisableWrapper<FixedText>(&m_aFTHostname));
        _rControlList.push_back(new ODisableWrapper<FixedText>(&m_aFTPortNumber));
        _rControlList.push_back(new ODisableWrapper<FixedText>(&m_aFTDefaultPortNumber));
        _rControlList.push_back(new ODisableWrapper<FixedText>(&m_aFTDriverClass));
    }

    // -----------------------------------------------------------------------
    sal_Bool OGeneralSpecialJDBCConnectionPageSetup::FillItemSet( SfxItemSet& _rSet )
    {
        sal_Bool bChangedSomething = sal_False;
        fillString(_rSet,&m_aETDriverClass,DSID_JDBCDRIVERCLASS,bChangedSomething);
        fillString(_rSet,&m_aETHostname,DSID_CONN_HOSTNAME,bChangedSomething);
        fillString(_rSet,&m_aETDatabasename,DSID_DATABASENAME,bChangedSomething);
        fillInt32(_rSet,&m_aNFPortNumber,m_nPortId,bChangedSomething );
        return bChangedSomething;
    }

    // -----------------------------------------------------------------------
    void OGeneralSpecialJDBCConnectionPageSetup::implInitControls(const SfxItemSet& _rSet, sal_Bool _bSaveValue)
    {
        // check whether or not the selection is invalid or readonly (invalid implies readonly, but not vice versa)
        sal_Bool bValid, bReadonly;
        getFlags(_rSet, bValid, bReadonly);

        SFX_ITEMSET_GET(_rSet, pDrvItem, SfxStringItem, DSID_JDBCDRIVERCLASS, sal_True);
        SFX_ITEMSET_GET(_rSet, pHostName, SfxStringItem, DSID_CONN_HOSTNAME, sal_True);
        SFX_ITEMSET_GET(_rSet, pPortNumber, SfxInt32Item, m_nPortId, sal_True);

        if ( bValid )
        {
            m_aETDriverClass.SetText(pDrvItem->GetValue());
            m_aETDriverClass.ClearModifyFlag();

            m_aETHostname.SetText(pHostName->GetValue());
            m_aETHostname.ClearModifyFlag();

            m_aNFPortNumber.SetValue(pPortNumber->GetValue());
            m_aNFPortNumber.ClearModifyFlag();
        }
        OGenericAdministrationPage::implInitControls(_rSet, _bSaveValue);

        // to get the correcxt value when saveValue was called by base class
        if ( !m_aETDriverClass.GetText().Len() )
        {
            m_aETDriverClass.SetText(m_sDefaultJdbcDriverName);
            m_aETDriverClass.SetModifyFlag();
        }
        callModifiedHdl();

        sal_Bool bRoadmapState = ((m_aETDatabasename.GetText().Len() != 0 ) && ( m_aETHostname.GetText().Len() != 0 ) && (m_aNFPortNumber.GetText().Len() != 0 ) && ( m_aETDriverClass.GetText().Len() != 0 ));
        SetRoadmapStateValue(bRoadmapState);
    }

    // -----------------------------------------------------------------------
    IMPL_LINK(OGeneralSpecialJDBCConnectionPageSetup, OnTestJavaClickHdl, PushButton*, _pButton)
    {
        OSL_ENSURE(m_pAdminDialog,"No Admin dialog set! ->GPF");
        sal_Bool bSuccess = sal_False;
        try
        {
            if ( m_aETDriverClass.GetText().Len() )
            {
// TODO chage jvmaccess
                ::rtl::Reference< jvmaccess::VirtualMachine > xJVM = ::connectivity::getJavaVM(m_pAdminDialog->getORB());
                bSuccess = ::connectivity::existsJavaClassByName(xJVM,m_aETDriverClass.GetText());
            }
        }
        catch(::com::sun::star::uno::Exception&)
        {
        }

        USHORT nMessage = bSuccess ? STR_JDBCDRIVER_SUCCESS : STR_JDBCDRIVER_NO_SUCCESS;
        String aMessage = String(ModuleRes(nMessage));
        String sTitle(ModuleRes(STR_JDBCDRIVER_TEST));
        OSQLMessageBox aMsg(this,sTitle,aMessage);
        aMsg.Execute();
        return 0L;
    }
    
    // -----------------------------------------------------------------------
    IMPL_LINK(OGeneralSpecialJDBCConnectionPageSetup, OnEditModified, Edit*, _pEdit)
    {
        if ( _pEdit == &m_aETDriverClass )
            m_aPBTestJavaDriver.Enable( m_aETDriverClass.GetText().Len() != 0 );
        sal_Bool bRoadmapState = ((m_aETDatabasename.GetText().Len() != 0 ) && ( m_aETHostname.GetText().Len() != 0 ) && (m_aNFPortNumber.GetText().Len() != 0 ) && ( m_aETDriverClass.GetText().Len() != 0 ));
        SetRoadmapStateValue(bRoadmapState);
        callModifiedHdl();
        return 0L;
    }


    // -----------------------------------------------------------------------
    OGenericAdministrationPage*	OJDBCConnectionPageSetup::CreateJDBCTabPage( Window* pParent, const SfxItemSet& _rAttrSet )
    {
        return ( new OJDBCConnectionPageSetup( pParent, PAGE_DBWIZARD_JDBC, _rAttrSet));
    }


    //========================================================================
    //= OMySQLJDBCConnectionPageSetup
    //========================================================================
    OJDBCConnectionPageSetup::OJDBCConnectionPageSetup( Window* pParent, USHORT _nResId, const SfxItemSet& _rCoreAttrs)
        :OConnectionTabPageSetup(pParent, PAGE_DBWIZARD_JDBC, _rCoreAttrs, STR_JDBC_HELPTEXT, STR_JDBC_HEADERTEXT, STR_COMMONURL)
        ,m_aFTDriverClass	    (this, ResId(FT_AUTOJDBCDRIVERCLASS))
        ,m_aETDriverClass	    (this, ResId(ET_AUTOJDBCDRIVERCLASS))
        ,m_aPBTestJavaDriver	(this, ResId(PB_AUTOTESTDRIVERCLASS))
    {
        m_aETDriverClass.SetModifyHdl(LINK(this, OJDBCConnectionPageSetup, OnEditModified));
        m_aPBTestJavaDriver.SetClickHdl(LINK(this,OJDBCConnectionPageSetup,OnTestJavaClickHdl));
        FreeResource();
    }

    // -----------------------------------------------------------------------
    void OJDBCConnectionPageSetup::fillControls(::std::vector< ISaveValueWrapper* >& _rControlList)
    {
        _rControlList.push_back(new OSaveValueWrapper<Edit>(&m_aETDriverClass));
    }

    // -----------------------------------------------------------------------
    void OJDBCConnectionPageSetup::fillWindows(::std::vector< ISaveValueWrapper* >& _rControlList)
    {
        _rControlList.push_back(new ODisableWrapper<FixedText>(&m_aFTDriverClass));
    }

    // -----------------------------------------------------------------------
    sal_Bool OJDBCConnectionPageSetup::FillItemSet( SfxItemSet& _rSet )
    {
        sal_Bool bChangedSomething = OConnectionTabPageSetup::FillItemSet(_rSet);
        fillString(_rSet,&m_aETDriverClass,DSID_JDBCDRIVERCLASS,bChangedSomething);
        return bChangedSomething;
    }

    // -----------------------------------------------------------------------
    void OJDBCConnectionPageSetup::implInitControls(const SfxItemSet& _rSet, sal_Bool _bSaveValue)
    {
        // check whether or not the selection is invalid or readonly (invalid implies readonly, but not vice versa)
        sal_Bool bValid, bReadonly;
        getFlags(_rSet, bValid, bReadonly);

        SFX_ITEMSET_GET(_rSet, pDrvItem, SfxStringItem, DSID_JDBCDRIVERCLASS, sal_True);

        if ( bValid )
        {
            m_aETDriverClass.SetText(pDrvItem->GetValue());
            m_aETDriverClass.ClearModifyFlag();
        }
        sal_Bool bEnable = pDrvItem->GetValue().Len() != 0;
        m_aPBTestJavaDriver.Enable(bEnable);
        OConnectionTabPageSetup::implInitControls(_rSet, _bSaveValue);

        SetRoadmapStateValue(checkTestConnection());
    }


    bool OJDBCConnectionPageSetup::checkTestConnection()
    {
        OSL_ENSURE(m_pAdminDialog,"No Admin dialog set! ->GPF");
        BOOL bEnableTestConnection = !m_aET_Connection.IsVisible() || (m_aET_Connection.GetTextNoPrefix().Len() != 0);
        bEnableTestConnection = bEnableTestConnection && (m_aETDriverClass.GetText().Len() != 0);
        return bEnableTestConnection;
//		m_aTestConnection.Enable(bEnableTestConnection);
    }


    // -----------------------------------------------------------------------
    IMPL_LINK(OJDBCConnectionPageSetup, OnTestJavaClickHdl, PushButton*, _pButton)
    {
        OSL_ENSURE(m_pAdminDialog,"No Admin dialog set! ->GPF");
        sal_Bool bSuccess = sal_False;
        try
        {
            if ( m_aETDriverClass.GetText().Len() )
            {
// TODO chage jvmaccess
                ::rtl::Reference< jvmaccess::VirtualMachine > xJVM = ::connectivity::getJavaVM(m_pAdminDialog->getORB());
                bSuccess = ::connectivity::existsJavaClassByName(xJVM,m_aETDriverClass.GetText());
            }
        }
        catch(::com::sun::star::uno::Exception&)
        {
        }

        USHORT nMessage = bSuccess ? STR_JDBCDRIVER_SUCCESS : STR_JDBCDRIVER_NO_SUCCESS;

        String aMessage = String(ModuleRes(nMessage));
        String sTitle(ModuleRes(STR_JDBCDRIVER_TEST));
        OSQLMessageBox aMsg(this,sTitle,aMessage);
        aMsg.Execute();
        return 0L;
    }

    // -----------------------------------------------------------------------
    IMPL_LINK(OJDBCConnectionPageSetup, OnEditModified, Edit*, _pEdit)
    {
        if ( _pEdit == &m_aETDriverClass )
            m_aPBTestJavaDriver.Enable( m_aETDriverClass.GetText().Len() != 0 );
        SetRoadmapStateValue(checkTestConnection());
        // tell the listener we were modified
        callModifiedHdl();
        return 0L;
    }


    OGenericAdministrationPage*	OSpreadSheetConnectionPageSetup::CreateSpreadSheetTabPage( Window* pParent, const SfxItemSet& _rAttrSet )
    {
        return ( new OSpreadSheetConnectionPageSetup( pParent, _rAttrSet ) );
    }


    OSpreadSheetConnectionPageSetup::OSpreadSheetConnectionPageSetup( Window* pParent, const SfxItemSet& _rCoreAttrs )
        :OConnectionTabPageSetup(pParent, PAGE_DBWIZARD_SPREADSHEET, _rCoreAttrs, STR_SPREADSHEET_HELPTEXT, STR_SPREADSHEET_HEADERTEXT, STR_SPREADSHEETPATH)
            , m_aCBPasswordrequired(this, ResId(CB_SPREADSHEETPASSWORDREQUIRED))
    {
           m_aCBPasswordrequired.SetToggleHdl(getControlModifiedLink());
        FreeResource();
    }


    // -----------------------------------------------------------------------
    OSpreadSheetConnectionPageSetup::~OSpreadSheetConnectionPageSetup()
    {
    }


    void OSpreadSheetConnectionPageSetup::fillWindows(::std::vector< ISaveValueWrapper* >& _rControlList)
    {
    }

    // -----------------------------------------------------------------------
    void OSpreadSheetConnectionPageSetup::fillControls(::std::vector< ISaveValueWrapper* >& _rControlList)
    {
        OConnectionTabPageSetup::fillControls(_rControlList);
        _rControlList.push_back(new OSaveValueWrapper<CheckBox>(&m_aCBPasswordrequired));

    }

    // -----------------------------------------------------------------------
    void OSpreadSheetConnectionPageSetup::implInitControls(const SfxItemSet& _rSet, sal_Bool _bSaveValue)
    {
        OConnectionTabPageSetup::implInitControls(_rSet, _bSaveValue);
    }

    // -----------------------------------------------------------------------
    sal_Bool OSpreadSheetConnectionPageSetup::FillItemSet( SfxItemSet& _rSet )
    {
        sal_Bool bChangedSomething = OConnectionTabPageSetup::FillItemSet(_rSet);
        fillBool(_rSet,&m_aCBPasswordrequired,DSID_PASSWORDREQUIRED,bChangedSomething);
        return bChangedSomething;
    }

    OGenericAdministrationPage*	OAuthentificationPageSetup::CreateAuthentificationTabPage( Window* pParent, const SfxItemSet& _rAttrSet )
    {
        return ( new OAuthentificationPageSetup( pParent, _rAttrSet) );
    }


    OAuthentificationPageSetup::OAuthentificationPageSetup( Window* pParent, const SfxItemSet& _rCoreAttrs )
        :OGenericAdministrationPage(pParent, ModuleRes(PAGE_DBWIZARD_AUTHENTIFICATION), _rCoreAttrs )
        , m_aFTHeaderText           (this, ResId(FT_AUTHENTIFICATIONHEADERTEXT))
        , m_aFTHelpText             (this, ResId(FT_AUTHENTIFICATIONHELPTEXT))
        , m_aFTUserName             (this, ResId(FT_GENERALUSERNAME))
        , m_aETUserName             (this, ResId(ET_GENERALUSERNAME))
        , m_aCBPasswordRequired     (this, ResId(CB_GENERALPASSWORDREQUIRED))
        , m_aPBTestConnection       (this, ResId(PB_TESTCONNECTION))
    {
        SetControlFontWeight(&m_aFTHeaderText);
        m_aETUserName.SetModifyHdl(getControlModifiedLink());
        m_aCBPasswordRequired.SetClickHdl(getControlModifiedLink());
           m_aPBTestConnection.SetClickHdl(LINK(this,OGenericAdministrationPage,OnTestConnectionClickHdl));
        FreeResource();
    }


    // -----------------------------------------------------------------------
    OAuthentificationPageSetup::~OAuthentificationPageSetup()
    {
    }


    void OAuthentificationPageSetup::fillWindows(::std::vector< ISaveValueWrapper* >& _rControlList)
    {
        _rControlList.push_back(new ODisableWrapper<FixedText>(&m_aFTHelpText));
        _rControlList.push_back(new ODisableWrapper<FixedText>(&m_aFTUserName));
        _rControlList.push_back(new ODisableWrapper<PushButton>(&m_aPBTestConnection));
    }

    // -----------------------------------------------------------------------
    void OAuthentificationPageSetup::fillControls(::std::vector< ISaveValueWrapper* >& _rControlList)
    {
        _rControlList.push_back(new OSaveValueWrapper<Edit>(&m_aETUserName));
        _rControlList.push_back(new OSaveValueWrapper<CheckBox>(&m_aCBPasswordRequired));
    }

    // -----------------------------------------------------------------------
    void OAuthentificationPageSetup::implInitControls(const SfxItemSet& _rSet, sal_Bool _bSaveValue)
    {
        // check whether or not the selection is invalid or readonly (invalid implies readonly, but not vice versa)
        sal_Bool bValid, bReadonly;
        getFlags(_rSet, bValid, bReadonly);
        SFX_ITEMSET_GET(_rSet, pUidItem, SfxStringItem, DSID_USER, sal_True);
        SFX_ITEMSET_GET(_rSet, pAllowEmptyPwd, SfxBoolItem, DSID_PASSWORDREQUIRED, sal_True);

        m_aETUserName.SetText(pUidItem->GetValue());
        m_aCBPasswordRequired.Check(pAllowEmptyPwd->GetValue());

        m_aETUserName.ClearModifyFlag();
    }

    // -----------------------------------------------------------------------
    sal_Bool OAuthentificationPageSetup::FillItemSet( SfxItemSet& _rSet )
    {
        sal_Bool bChangedSomething = sal_False;

        if (m_aETUserName.GetText() != m_aETUserName.GetSavedValue())
        {
            _rSet.Put(SfxStringItem(DSID_USER, m_aETUserName.GetText()));
            _rSet.Put(SfxStringItem(DSID_PASSWORD, String()));
            bChangedSomething = sal_True;
        }
        fillBool(_rSet,&m_aCBPasswordRequired,DSID_PASSWORDREQUIRED,bChangedSomething);
        return bChangedSomething;
    }


    OGenericAdministrationPage*	OFinalDBPageSetup::CreateFinalDBTabPageSetup( Window* pParent, const SfxItemSet& _rAttrSet)
    {
        return ( new OFinalDBPageSetup( pParent, _rAttrSet) );
    }


    OFinalDBPageSetup::OFinalDBPageSetup( Window* pParent, const SfxItemSet& _rCoreAttrs )
    :OGenericAdministrationPage(pParent, ModuleRes(PAGE_DBWIZARD_FINAL), _rCoreAttrs )
    , m_aFTFinalHeader              (this, ResId(FT_FINALHEADER))
    , m_aFTFinalHelpText            (this, ResId(FT_FINALHELPTEXT))
    , m_aRBRegisterDataSource       (this, ResId(RB_REGISTERDATASOURCE))
    , m_aRBDontregisterDataSource   (this, ResId(RB_DONTREGISTERDATASOURCE))
    , m_aFTAdditionalSettings       (this, ResId(FT_ADDITIONALSETTINGS))
    , m_aCBOpenAfterwards           (this, ResId(CB_OPENAFTERWARDS))
    , m_aCBStartTableWizard         (this, ResId(CB_STARTTABLEWIZARD))
    , m_aFTFinalText                (this, ResId(FT_FINALTEXT))        
    {
        String stext = m_aFTFinalHeader.GetText();
        SetControlFontWeight(&m_aFTFinalHeader);
        m_aCBOpenAfterwards.SetClickHdl(getControlModifiedLink());
        m_aCBStartTableWizard.SetClickHdl(getControlModifiedLink());
        FreeResource();
    }


    // -----------------------------------------------------------------------
    OFinalDBPageSetup::~OFinalDBPageSetup()
    {
    }

    sal_Bool OFinalDBPageSetup::IsDatabaseDocumentToBeRegistered()
    {   
        return m_aRBRegisterDataSource.IsChecked() && m_aRBRegisterDataSource.IsEnabled();
    }

    sal_Bool OFinalDBPageSetup::IsDatabaseDocumentToBeOpened()
    {          
        return m_aCBOpenAfterwards.IsChecked() && m_aCBOpenAfterwards.IsEnabled();
    }

    sal_Bool OFinalDBPageSetup::IsTableWizardToBeStarted()
    {
        return m_aCBStartTableWizard.IsChecked() && m_aCBStartTableWizard.IsEnabled();
    }


    void OFinalDBPageSetup::fillWindows(::std::vector< ISaveValueWrapper* >& _rControlList)
    {
        _rControlList.push_back(new ODisableWrapper<FixedText>(&m_aFTFinalHeader));
        _rControlList.push_back(new ODisableWrapper<FixedText>(&m_aFTFinalHelpText));
        _rControlList.push_back(new ODisableWrapper<FixedText>(&m_aFTAdditionalSettings));
        _rControlList.push_back(new ODisableWrapper<FixedText>(&m_aFTFinalText));
    }

    // -----------------------------------------------------------------------
    void OFinalDBPageSetup::fillControls(::std::vector< ISaveValueWrapper* >& _rControlList)
    {
        _rControlList.push_back(new OSaveValueWrapper<CheckBox>(&m_aCBOpenAfterwards));
        _rControlList.push_back(new OSaveValueWrapper<CheckBox>(&m_aCBStartTableWizard));
        _rControlList.push_back(new OSaveValueWrapper<RadioButton>(&m_aRBRegisterDataSource));
        _rControlList.push_back(new OSaveValueWrapper<RadioButton>(&m_aRBDontregisterDataSource));
    }

    // -----------------------------------------------------------------------
    void OFinalDBPageSetup::implInitControls(const SfxItemSet& _rSet, sal_Bool _bSaveValue)
    {
        m_aCBOpenAfterwards.Check();
        m_aRBRegisterDataSource.SetState(sal_True);
    }

    void OFinalDBPageSetup::enableTableWizardCheckBox( sal_Bool _bSupportsTableCreation)
    {
        m_aCBStartTableWizard.Enable(_bSupportsTableCreation);
    }

    // -----------------------------------------------------------------------
    sal_Bool OFinalDBPageSetup::FillItemSet( SfxItemSet& _rSet )
    {
        sal_Bool bChangedSomething = sal_True;
        return bChangedSomething;
    }
//.........................................................................
}	// namespace dbaui
//.........................................................................
