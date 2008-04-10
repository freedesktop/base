/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 * 
 * Copyright 2008 by Sun Microsystems, Inc.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * $RCSfile: core_resource.hxx,v $
 * $Revision: 1.5 $
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

#ifndef _DBA_CORE_RESOURCE_HXX_
#define _DBA_CORE_RESOURCE_HXX_

#ifndef _RTL_USTRING_HXX_
#include <rtl/ustring.hxx>
#endif

class SimpleResMgr;
//.........................................................................
namespace dbaccess
{

#define DBA_RES( id )                       ResourceManager::loadString( id )
#define DBA_RES_PARAM( id, ascii, replace ) ResourceManager::loadString( id, ascii, replace )

#define DBACORE_RESSTRING( id ) DBA_RES( id )
        // (compatibility)

    //==================================================================
    //= ResourceManager
    //= handling ressources within the DBA-Core library
    //==================================================================
    class ResourceManager
    {
        static SimpleResMgr*	m_pImpl;

    private:
        // no instantiation allowed
        ResourceManager() { }
        ~ResourceManager() { }

        // we'll instantiate one static member of the following class, which, in it's dtor,
        // ensures that m_pImpl will be deleted
        class EnsureDelete
        {
        public:
            EnsureDelete() { }
            ~EnsureDelete();
        };
        friend class EnsureDelete;

    protected:
        static void ensureImplExists();

    public:
        /** loads the string with the specified resource id
        */
        static ::rtl::OUString  loadString(sal_uInt16 _nResId);

        /** loads a string from the resource file, substituting a placeholder with a given string

            @param  _nResId
                the resource ID of the string to loAD
            @param  _pPlaceholderAscii
                the ASCII representation of the placeholder string
            @param  _rReplace
                the string which should substutite the placeholder
        */
        static ::rtl::OUString  loadString(
                sal_uInt16              _nResId,
                const sal_Char*         _pPlaceholderAscii,
                const ::rtl::OUString&  _rReplace
        );
    };

//.........................................................................
}
//.........................................................................

#endif // _DBA_CORE_RESOURCE_HXX_

