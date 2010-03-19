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
#ifndef DBAUI_SBATTRDLG_HXX
#define DBAUI_SBATTRDLG_HXX


#ifndef DBAUI_SBATTRDLG_HRC
#include "dlgattr.hrc"
#endif

#ifndef _SFXTABDLG_HXX //autogen
#include <sfx2/tabdlg.hxx>
#endif
#ifndef _SOLAR_H
#include <tools/solar.h>
#endif



class SvxNumberInfoItem;
class SfxItemSet;
class SvNumberFormatter;
//.........................................................................
namespace dbaui
{
//.........................................................................

    class SbaSbAttrDlg : public SfxTabDialog
    {
        String aTitle;
        SvxNumberInfoItem* pNumberInfoItem;

    public:
        SbaSbAttrDlg( Window * pParent, const SfxItemSet*, SvNumberFormatter*, USHORT nFlags = TP_ATTR_CHAR , BOOL bRow = FALSE);
        ~SbaSbAttrDlg();

        virtual void  PageCreated( USHORT nPageId, SfxTabPage& rTabPage );
    };
//.........................................................................
}	// namespace dbaui
//.........................................................................

#endif//DBAUI_SBATTRDLG_HXX

