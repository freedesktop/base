/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 * 
 * Copyright 2008 by Sun Microsystems, Inc.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * $RCSfile: QTableConnection.hxx,v $
 * $Revision: 1.6 $
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
#ifndef DBAUI_QUERYTABLECONNECTION_HXX
#define DBAUI_QUERYTABLECONNECTION_HXX

#ifndef DBAUI_TABLECONNECTION_HXX
#include "TableConnection.hxx"
#endif
#ifndef DBAUI_QTABLECONNECTIONDATA_HXX
#include "QTableConnectionData.hxx"
#endif
#ifndef DBAUI_ENUMTYPES_HXX
#include "QEnumTypes.hxx"
#endif

namespace dbaui
{
    //==================================================================
    class OQueryTableView;
    class OQueryTableConnection : public OTableConnection
    {
        sal_Bool m_bVisited;	// is true if the conn was already visited through the join algorithm
    public:
        OQueryTableConnection(OQueryTableView* pContainer, const TTableConnectionData::value_type& pTabConnData);
        OQueryTableConnection(const OQueryTableConnection& rConn);
        virtual ~OQueryTableConnection();

        OQueryTableConnection& operator=(const OQueryTableConnection& rConn);
        sal_Bool operator==(const OQueryTableConnection& rCompare);

        inline ::rtl::OUString	GetAliasName(EConnectionSide nWhich) const { return static_cast<OQueryTableConnectionData*>(GetData().get())->GetAliasName(nWhich); }

        inline sal_Bool	IsVisited() const				{ return m_bVisited; }
        inline void		SetVisited(sal_Bool bVisited)	{ m_bVisited = bVisited; }

    };
}
#endif // DBAUI_QUERYTABLECONNECTION_HXX
