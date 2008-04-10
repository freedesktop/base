/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 * 
 * Copyright 2008 by Sun Microsystems, Inc.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * $RCSfile: ConnectionPage.hxx,v $
 * $Revision: 1.7 $
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

#ifndef DBAUI_CONNECTIONPAGE_HXX
#define DBAUI_CONNECTIONPAGE_HXX

#ifndef DBAUI_CONNECTIONHELPER_HXX
#include "ConnectionHelper.hxx"
#endif
#ifndef _DBAUI_ADMINPAGES_HXX_
#include "adminpages.hxx"
#endif
#ifndef _UCBHELPER_CONTENT_HXX
#include <ucbhelper/content.hxx>
#endif
#ifndef _DBAUI_CURLEDIT_HXX_
#include "curledit.hxx"
#endif

//.........................................................................
namespace dbaui
{
//.........................................................................

    class IDatabaseSettingsDialog;
    //=========================================================================
    //= OConnectionTabPage
    //=========================================================================

    /** implements the connection page of teh data source properties dialog.
    */
    class OConnectionTabPage : public OConnectionHelper
    {
        ODsnTypeCollection*	m_pCollection;	/// the DSN type collection instance
        sal_Bool			m_bUserGrabFocus : 1;
    protected:
        // connection 
        FixedLine			m_aFL1;
        // user authentification
        FixedLine			m_aFL2;
        FixedText			m_aUserNameLabel;
        Edit				m_aUserName;
        CheckBox			m_aPasswordRequired;

        // jdbc driver
        FixedLine			m_aFL3;
        FixedText			m_aJavaDriverLabel;
        Edit				m_aJavaDriver;
        PushButton			m_aTestJavaDriver;

        // connection test
        PushButton			m_aTestConnection;


        // called when the test connection button was clicked
        DECL_LINK(OnBrowseConnections, PushButton*);
        DECL_LINK(OnTestJavaClickHdl,PushButton*);
        DECL_LINK(OnEditModified,Edit*);

    public:
        static	SfxTabPage*	Create( Window* pParent, const SfxItemSet& _rAttrSet );
        virtual	BOOL		FillItemSet	(SfxItemSet& _rCoreAttrs);

        virtual void		implInitControls(const SfxItemSet& _rSet, sal_Bool _bSaveValue);

        virtual void SetServiceFactory(const ::com::sun::star::uno::Reference< ::com::sun::star::lang::XMultiServiceFactory > _rxORB)
        { 
            OGenericAdministrationPage::SetServiceFactory(_rxORB);
            m_aET_Connection.initializeTypeCollection(m_xORB);
        }

        inline void enableConnectionURL() { m_aET_Connection.SetReadOnly(sal_False); }
        inline void disableConnectionURL() { m_aET_Connection.SetReadOnly(); }

        /** changes the connection URL.
            <p>The new URL must be of the type which is currently selected, only the parts which do not
            affect the type may be changed (compared to the previous URL).</p>
        */
    private:
        OConnectionTabPage(Window* pParent, const SfxItemSet& _rCoreAttrs);
            // nControlFlags ist eine Kombination der CBTP_xxx-Konstanten
        virtual ~OConnectionTabPage();

        // <method>OGenericAdministrationPage::fillControls</method>
        virtual void fillControls(::std::vector< ISaveValueWrapper* >& _rControlList);
        // <method>OGenericAdministrationPage::fillWindows</method>
        virtual void fillWindows(::std::vector< ISaveValueWrapper* >& _rControlList);

    private:
        /** enables the test connection button, if allowed
        */
        virtual bool checkTestConnection();
    };
//.........................................................................
}	// namespace dbaui
//.........................................................................

#endif // _DBAUI_DETAILPAGES_HXX_
