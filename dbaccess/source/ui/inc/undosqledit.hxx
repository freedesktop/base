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
#ifndef DBAUI_UNDOSQLEDIT_HXX
#define DBAUI_UNDOSQLEDIT_HXX

#ifndef DBAUI_GENERALUNDO_HXX
#include "GeneralUndo.hxx"
#endif
#ifndef _DBU_CONTROL_HRC_
#include "dbu_control.hrc"
#endif

namespace dbaui
{
    class OSqlEdit;
    // ================================================================================================
    // OSqlEditUndoAct - Undo-class for changing sql text
    //------------------------------------------------------------------------
    class OSqlEditUndoAct : public OCommentUndoAction
    {
    protected:
        OSqlEdit*	m_pOwner;
        String		m_strNextText;

        virtual void	Undo() { ToggleText(); }
        virtual void	Redo() { ToggleText(); }

        void ToggleText();
    public:
        OSqlEditUndoAct(OSqlEdit* pEdit) : OCommentUndoAction(STR_QUERY_UNDO_MODIFYSQLEDIT), m_pOwner(pEdit) { }

        void SetOriginalText(const String& strText) { m_strNextText =strText; }
    };
}
#endif // DBAUI_UNDOSQLEDIT_HXX


