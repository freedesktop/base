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

#ifndef DBAUI_TOOLBOXHELPER_HXX
#define DBAUI_TOOLBOXHELPER_HXX

#ifndef _SAL_TYPES_H_ 
#include <sal/types.h>
#endif
#ifndef _LINK_HXX 
#include <tools/link.hxx>
#endif
#ifndef _SV_GEN_HXX 
#include <tools/gen.hxx>
#endif
#ifndef _SV_IMAGE_HXX
#include <vcl/image.hxx>
#endif
#include "dbaccessdllapi.h"

class SvtMiscOptions;
class ToolBox;
class VclWindowEvent;

namespace dbaui
{
    class DBACCESS_DLLPUBLIC OToolBoxHelper
    {
        sal_Bool		m_bIsHiContrast;// true when the toolbox is in hi contrast mode
        sal_Int16		m_nSymbolsSize;	// shows the toolbox large or small bitmaps
        ToolBox*		m_pToolBox;		// our toolbox (may be NULL)
    public:
        OToolBoxHelper();
        virtual ~OToolBoxHelper();

        /** will be called when the controls need to be resized.
            @param	_rDiff
                Contains the difference of the old and new toolbox size.
        */
        virtual void resizeControls(const Size& _rDiff) = 0;

        /** will be called when the image list is needed.
            @param	_eSymbolsSize
                <svtools/imgdef.hxx>
            @param	_bHiContast
                <TRUE/> when in high contrast mode.
        */
        virtual ImageList getImageList(sal_Int16 _eSymbolsSize,sal_Bool _bHiContast) const = 0;

        /** only the member will be set, derived classes can overload this function and do what need to be done.
            @param	_pTB
                The new ToolBox.
            @attention
                Must be called after a FreeResource() call.
        */
        virtual void	setToolBox(ToolBox* _pTB);

        inline ToolBox* getToolBox() const			{ return m_pToolBox; }

        /** checks if the toolbox needs a new imagelist.
        */
        void checkImageList();
        
        inline sal_Bool isToolBoxHiContrast() const { return m_bIsHiContrast; }
    protected:
        DECL_LINK(ConfigOptionsChanged, SvtMiscOptions*);
        DECL_LINK(SettingsChanged, VclWindowEvent* );
    };
}
#endif // DBAUI_TOOLBOXHELPER_HXX

