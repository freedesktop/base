/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 *
 * Copyright 2000, 2010 Oracle and/or its affiliates.
 *
 * OpenOffice.org - a multi-platform office productivity suite
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

#ifndef ADABASUI_SQLNAMEEDIT_HXX
#define ADABASUI_SQLNAMEEDIT_HXX

#ifndef _SV_EDIT_HXX 
#include <vcl/edit.hxx>
#endif
#ifndef _SV_COMBOBOX_HXX
#include <vcl/combobox.hxx>
#endif

namespace adabasui
{
    class OSQLNameChecker
    {
    public:
        sal_Bool checkString(const ::rtl::OUString& _sOldValue,const ::rtl::OUString& _sToCheck,::rtl::OUString& _rsCorrected);
    };
    //==================================================================
    class OSQLNameEdit : public Edit
                        ,public OSQLNameChecker
    {
    public:
        OSQLNameEdit(Window* _pParent,const ResId& _rRes) 
            : Edit(_pParent,_rRes)
        {
        }

        // Edit
        virtual void Modify();
    };
}
#endif // DBAUI_SQLNAMEEDIT_HXX


