/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 * 
 * Copyright 2008 by Sun Microsystems, Inc.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * $RCSfile: reportformula.hxx,v $
 * $Revision: 1.3 $
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

#ifndef REPORTFORMULA_HXX
#define REPORTFORMULA_HXX

#include "dllapi.h"

/** === begin UNO includes === **/
#include <com/sun/star/uno/Any.hxx>
/** === end UNO includes === **/

#include <osl/diagnose.h>

//........................................................................
namespace rptui
{
//........................................................................

    //====================================================================
    //= ReportFormula
    //====================================================================
    class REPORTDESIGN_DLLPUBLIC ReportFormula
    {
    public:
        enum BindType
        {
            Expression,
            Field,

            Invalid
        };

    private:
        BindType            m_eType;
        ::rtl::OUString     m_sCompleteFormula;
        ::rtl::OUString     m_sUndecoratedContent;

    public:
        // constructs a ReportFormula instance which is initially invalid.
        ReportFormula();

        /// constructs a ReportFormula object from a string
        ReportFormula( const ::rtl::OUString& _rFormula );

        /// constructs a ReportFormula object from a string
        ReportFormula( const ::com::sun::star::uno::Any& _rWrappedFormula );

        /// constructs a ReportFormula by BindType
        ReportFormula( const BindType _eType, const ::rtl::OUString& _rFieldOrExpression );

        /// returns whether the object denotes a valid formula
        bool        isValid() const { return getType() != Invalid; }

        /// returns the type of the binding represented by the formula
        BindType    getType() const { return m_eType; }

        /// returns the complete formula represented by the object
        const ::rtl::OUString&
                    getCompleteFormula() const { return m_sCompleteFormula; }

        /** gets the <em>undecorated formula</em> content

            If the formula denotes a field binding, the <em>undecorated content</em> is the
            field name.

            If the formula denotes an expression, then the <em>undecorated content</em> is the expression
            itself.
        */
        const ::rtl::OUString& getUndecoratedContent() const { return m_sUndecoratedContent; }

        /// convenience alias for <code>getUndecoratedContent</code>, which asserts (in a non-product build) when used on an expression
        inline ::rtl::OUString  getFieldName() const;

        /// convenience alias for <code>getUndecoratedContent</code>, which asserts (in a non-product build) when used on a field
        inline ::rtl::OUString  getExpression() const;

        /** returns a bracketed field name of the formula denotes a field reference,
            or the undecorated expression if the formula denotes an expression.

            Effectively, this means the method returns the complete formular, stripped by the prefix
            which indicates a field or a expression.
        */
        ::rtl::OUString getBracketedFieldOrExpression() const;

    private:
        void    impl_construct( const ::rtl::OUString& _rFormula );
    };

    //--------------------------------------------------------------------
    inline ::rtl::OUString ReportFormula::getFieldName() const
    {
        OSL_PRECOND( getType() == Field, "ReportFormula::getFieldName: not bound to a field!" );
        return getUndecoratedContent();
    }

    //--------------------------------------------------------------------
    inline ::rtl::OUString ReportFormula::getExpression() const
    {
        OSL_PRECOND( getType() == Expression, "ReportFormula::getExpression: not bound to an expression!" );
        return getUndecoratedContent();
    }

//........................................................................
} // namespace rptui
//........................................................................

#endif // REPORTFORMULA_HXX
