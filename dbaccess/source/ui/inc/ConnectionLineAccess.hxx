/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: ConnectionLineAccess.hxx,v $
 *
 *  $Revision: 1.5 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-08 15:15:52 $
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
#ifndef DBACCESS_CONNECTIONLINEACCESS_HXX
#define DBACCESS_CONNECTIONLINEACCESS_HXX

#ifndef _COM_SUN_STAR_ACCESSIBILITY_XACCESSIBLERELATIONSET_HPP_
#include <com/sun/star/accessibility/XAccessibleRelationSet.hpp>
#endif
#ifndef _CPPUHELPER_IMPLBASE2_HXX_
#include <cppuhelper/implbase2.hxx>
#endif
#ifndef _TOOLKIT_AWT_VCLXACCESSIBLECOMPONENT_HXX_
#include <toolkit/awt/vclxaccessiblecomponent.hxx>
#endif

namespace dbaui
{
    typedef ::cppu::ImplHelper2< ::com::sun::star::accessibility::XAccessibleRelationSet,
                                 ::com::sun::star::accessibility::XAccessible
                                            > OConnectionLineAccess_BASE;
    class OTableConnection;
    /** the class OConnectionLineAccess represents the accessible object for the connection between two table windows
        like they are used in the QueryDesign and the RelationDesign
    */
    class OConnectionLineAccess		:	public VCLXAccessibleComponent
                                    ,	public OConnectionLineAccess_BASE
    {
        const OTableConnection*				m_pLine; // the window which I should give accessibility to
    protected:
        /** this function is called upon disposing the component
        */
        virtual void SAL_CALL disposing();

        /** isEditable returns the current editable state
            @return	true if it is editable otherwise false				
        */
        virtual sal_Bool isEditable() const;
    public:
        OConnectionLineAccess(OTableConnection* _pLine);

        // XInterface
        virtual ::com::sun::star::uno::Any SAL_CALL queryInterface( const ::com::sun::star::uno::Type& aType ) throw (::com::sun::star::uno::RuntimeException);
        virtual void SAL_CALL acquire(  ) throw ()
        { // here inline is allowed because we do not use this class outside this dll
            VCLXAccessibleComponent::acquire(  );
        }
        virtual void SAL_CALL release(  ) throw ()
        { // here inline is allowed because we do not use this class outside this dll
            VCLXAccessibleComponent::release(  );
        }

        // XTypeProvider
        virtual ::com::sun::star::uno::Sequence< ::com::sun::star::uno::Type > SAL_CALL getTypes(  ) throw (::com::sun::star::uno::RuntimeException);

        // XServiceInfo - static methods
        static ::rtl::OUString getImplementationName_Static(void) throw( com::sun::star::uno::RuntimeException );
        // XServiceInfo
        virtual ::rtl::OUString SAL_CALL getImplementationName() throw(com::sun::star::uno::RuntimeException);
        
        // XAccessible
        virtual ::com::sun::star::uno::Reference< ::com::sun::star::accessibility::XAccessibleContext > SAL_CALL getAccessibleContext(  ) throw (::com::sun::star::uno::RuntimeException);

        // XAccessibleContext
        virtual sal_Int32 SAL_CALL getAccessibleChildCount(  ) throw (::com::sun::star::uno::RuntimeException);
        virtual ::com::sun::star::uno::Reference< ::com::sun::star::accessibility::XAccessible > SAL_CALL getAccessibleChild( sal_Int32 i ) throw (::com::sun::star::uno::RuntimeException);
        virtual sal_Int32 SAL_CALL getAccessibleIndexInParent(  ) throw (::com::sun::star::uno::RuntimeException);
        virtual sal_Int16 SAL_CALL getAccessibleRole(  ) throw (::com::sun::star::uno::RuntimeException);
        virtual ::rtl::OUString SAL_CALL getAccessibleDescription(  ) throw (::com::sun::star::uno::RuntimeException);
        virtual ::com::sun::star::uno::Reference< ::com::sun::star::accessibility::XAccessibleRelationSet > SAL_CALL getAccessibleRelationSet(  ) throw (::com::sun::star::uno::RuntimeException);

        // XAccessibleComponent
        virtual sal_Bool SAL_CALL contains( const ::com::sun::star::awt::Point& aPoint ) throw (::com::sun::star::uno::RuntimeException);
        virtual ::com::sun::star::uno::Reference< ::com::sun::star::accessibility::XAccessible > SAL_CALL getAccessibleAtPoint( const ::com::sun::star::awt::Point& aPoint ) throw (::com::sun::star::uno::RuntimeException);
        virtual ::com::sun::star::awt::Rectangle SAL_CALL getBounds(  ) throw (::com::sun::star::uno::RuntimeException);
        virtual ::com::sun::star::awt::Point SAL_CALL getLocation(  ) throw (::com::sun::star::uno::RuntimeException);
        virtual ::com::sun::star::awt::Point SAL_CALL getLocationOnScreen(  ) throw (::com::sun::star::uno::RuntimeException);
        virtual ::com::sun::star::awt::Size SAL_CALL getSize(  ) throw (::com::sun::star::uno::RuntimeException);
        virtual sal_Bool SAL_CALL isShowing(  ) throw (::com::sun::star::uno::RuntimeException);
        virtual sal_Bool SAL_CALL isVisible(  ) throw (::com::sun::star::uno::RuntimeException);
        virtual sal_Bool SAL_CALL isFocusTraversable(  ) throw (::com::sun::star::uno::RuntimeException);

        // XAccessibleRelationSet
        virtual sal_Int32 SAL_CALL getRelationCount(  ) throw (::com::sun::star::uno::RuntimeException);
        virtual ::com::sun::star::accessibility::AccessibleRelation SAL_CALL getRelation( sal_Int32 nIndex ) throw (::com::sun::star::lang::IndexOutOfBoundsException, ::com::sun::star::uno::RuntimeException);
        virtual sal_Bool SAL_CALL containsRelation( sal_Int16 aRelationType ) throw (::com::sun::star::uno::RuntimeException);
        virtual ::com::sun::star::accessibility::AccessibleRelation SAL_CALL getRelationByType( sal_Int16 aRelationType ) throw (::com::sun::star::uno::RuntimeException);
    };
}
#endif // DBACCESS_CONNECTIONLINEACCESS_HXX
