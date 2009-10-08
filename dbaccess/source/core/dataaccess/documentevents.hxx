/*************************************************************************
* DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
* 
* Copyright 2008 by Sun Microsystems, Inc.
*
* OpenOffice.org - a multi-platform office productivity suite
*
* $RCSfile: documentevents.hxx,v $
*
* $Revision: 1.1.2.2 $
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
************************************************************************/

#ifndef DBACCESS_DOCUMENTEVENTS_HXX
#define DBACCESS_DOCUMENTEVENTS_HXX

/** === begin UNO includes === **/
#include <com/sun/star/container/XNameReplace.hpp>
/** === end UNO includes === **/

#include <cppuhelper/implbase1.hxx>

#include <memory>
#include <boost/noncopyable.hpp>

//........................................................................
namespace dbaccess
{
//........................................................................

    //====================================================================
    //= DocumentEvents
    //====================================================================
    struct DocumentEvents_Data;

    typedef ::cppu::WeakImplHelper1 <   ::com::sun::star::container::XNameReplace
                                    >   DocumentEvents_Base;

    class DocumentEvents
                                    :public DocumentEvents_Base
                                    ,public ::boost::noncopyable
    {
    public:
        DocumentEvents( ::cppu::OWeakObject& _rParent, ::osl::Mutex& _rMutex );
        ~DocumentEvents();

        static bool needsSynchronousNotification( const ::rtl::OUString& _rEventName );

        // XInterface
        virtual void SAL_CALL acquire() throw();
        virtual void SAL_CALL release() throw();

        // XNameReplace
        virtual void SAL_CALL replaceByName( const ::rtl::OUString& aName, const ::com::sun::star::uno::Any& aElement ) throw (::com::sun::star::lang::IllegalArgumentException, ::com::sun::star::container::NoSuchElementException, ::com::sun::star::lang::WrappedTargetException, ::com::sun::star::uno::RuntimeException);

        // XNameAccess
        virtual ::com::sun::star::uno::Any SAL_CALL getByName( const ::rtl::OUString& aName ) throw (::com::sun::star::container::NoSuchElementException, ::com::sun::star::lang::WrappedTargetException, ::com::sun::star::uno::RuntimeException);
        virtual ::com::sun::star::uno::Sequence< ::rtl::OUString > SAL_CALL getElementNames(  ) throw (::com::sun::star::uno::RuntimeException);
        virtual ::sal_Bool SAL_CALL hasByName( const ::rtl::OUString& aName ) throw (::com::sun::star::uno::RuntimeException);

        // XElementAccess
        virtual ::com::sun::star::uno::Type SAL_CALL getElementType(  ) throw (::com::sun::star::uno::RuntimeException);
        virtual ::sal_Bool SAL_CALL hasElements(  ) throw (::com::sun::star::uno::RuntimeException);

    private:
        ::std::auto_ptr< DocumentEvents_Data >  m_pData;
    };

//........................................................................
} // namespace dbaccess
//........................................................................

#endif // DBACCESS_DOCUMENTEVENTS_HXX
