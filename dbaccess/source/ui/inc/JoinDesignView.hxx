/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: JoinDesignView.hxx,v $
 *
 *  $Revision: 1.7 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-08 15:29:02 $
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

#ifndef DBAUI_JOINDESIGNVIEW_HXX
#define DBAUI_JOINDESIGNVIEW_HXX

#ifndef DBAUI_DATAVIEW_HXX
#include "dataview.hxx"
#endif
#ifndef _VECTOR_
#include <vector>
#endif
#ifndef _STRING_HXX
#include <tools/string.hxx>
#endif
#ifndef DBAUI_ENUMTYPES_HXX
#include "QEnumTypes.hxx"
#endif
//#ifndef DBAUI_JOINTABLEVIEW_HXX
//#include "JoinTableView.hxx"
//#endif

namespace dbaui
{
    class OAddTableDlg;
    class OTableConnection;
    class OConnectionLineData;
    class OJoinController;
    class OScrollWindowHelper;
    class OJoinTableView;
    class OTableWindow;
    
    class OJoinDesignView : public ODataView
    {
    protected:
        OScrollWindowHelper*	m_pScrollWindow;	// contains only the scrollbars
        OJoinTableView*			m_pTableView;		// presents the upper window
        OAddTableDlg*			m_pAddTabDlg;		// create by the first execute of the add table slot
        OJoinController*		m_pController;

    public:
        OJoinDesignView(Window* pParent, 
                        OJoinController* _pController,
                        const ::com::sun::star::uno::Reference< ::com::sun::star::lang::XMultiServiceFactory >& );
        virtual ~OJoinDesignView();

        // set the view readonly or not
        virtual void setReadOnly(sal_Bool _bReadOnly);
        // set the statement for representation
        /// late construction
        virtual void Construct();
        virtual void initialize();
        virtual void KeyInput( const KeyEvent& rEvt );

        virtual void SaveTabWinUIConfig(OTableWindow* pWin);
        OJoinController* getController() const { return m_pController; }
        // returs the add table dialog from the design view
        OAddTableDlg* getAddTableDialog() { return m_pAddTabDlg; }
        // called when fields are deleted
        // called when a table from tabeview was deleted
        void TableDeleted(const ::rtl::OUString& rAliasName);

        OJoinTableView* getTableView() const { return m_pTableView; }
        void zoomTableView(const Fraction& _rFraction);
        void SaveUIConfig();
    protected:
        // return the Rectangle where I can paint myself
        virtual void resizeDocumentView(Rectangle& rRect);
        DECL_LINK( SplitHdl, void* );
    };
}
#endif // DBAUI_JOINDESIGNVIEW_HXX



