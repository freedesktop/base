/*************************************************************************
 *
 *  $RCSfile: TableConnectionData.cxx,v $
 *
 *  $Revision: 1.1 $
 *
 *  last change: $Author: oj $ $Date: 2001-02-05 09:34:41 $
 *
 *  The Contents of this file are made available subject to the terms of
 *  either of the following licenses
 *
 *         - GNU Lesser General Public License Version 2.1
 *         - Sun Industry Standards Source License Version 1.1
 *
 *  Sun Microsystems Inc., October, 2000
 *
 *  GNU Lesser General Public License Version 2.1
 *  =============================================
 *  Copyright 2000 by Sun Microsystems, Inc.
 *  901 San Antonio Road, Palo Alto, CA 94303, USA
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License version 2.1, as published by the Free Software Foundation.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 *  MA  02111-1307  USA
 *
 *
 *  Sun Industry Standards Source License Version 1.1
 *  =================================================
 *  The contents of this file are subject to the Sun Industry Standards
 *  Source License Version 1.1 (the License); You may not use this file
 *  except in compliance with the License. You may obtain a copy of the
 *  License at http://www.openoffice.org/license.html.
 *
 *  Software provided under this License is provided on an AS IS basis,
 *  WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING,
 *  WITHOUT LIMITATION, WARRANTIES THAT THE SOFTWARE IS FREE OF DEFECTS,
 *  MERCHANTABLE, FIT FOR A PARTICULAR PURPOSE, OR NON-INFRINGING.
 *  See the License for the specific provisions governing your rights and
 *  obligations concerning the Software.
 *
 *  The Initial Developer of the Original Code is: Sun Microsystems, Inc.
 *
 *  Copyright: 2000 by Sun Microsystems, Inc.
 *
 *  All Rights Reserved.
 *
 *  Contributor(s): _______________________________________
 *
 *
 ************************************************************************/
#ifndef DBAUI_TABLECONNECTIONDATA_HXX
#include "TableConnectionData.hxx"
#endif
#ifndef _TOOLS_DEBUG_HXX
#include <tools/debug.hxx>
#endif
#ifndef _COMPHELPER_STLTYPES_HXX_
#include <comphelper/stl_types.hxx>
#endif

using namespace dbaui;
using namespace comphelper;
//==================================================================
// class OTableConnectionData
//==================================================================
DBG_NAME(OTableConnectionData);
TYPEINIT0(OTableConnectionData);
//------------------------------------------------------------------------
OTableConnectionData::OTableConnectionData()
{
    DBG_CTOR(OTableConnectionData,NULL);
    Init();
}

//------------------------------------------------------------------------
OTableConnectionData::OTableConnectionData( const String& rSourceWinName, const String& rDestWinName, const String& rConnName )
    :m_aSourceWinName( rSourceWinName )
    ,m_aDestWinName( rDestWinName )
    ,m_aConnName( rConnName )
{
    DBG_CTOR(OTableConnectionData,NULL);
    Init();
}

//------------------------------------------------------------------------
void OTableConnectionData::Init()
{
    //////////////////////////////////////////////////////////////////////
    // LineDataList mit Defaults initialisieren
    DBG_ASSERT(m_vConnLineData.size() == 0, "OTableConnectionData::Init() : nur mit leere Linienliste aufzurufen !");
    ResetConnLines(TRUE);
        // das legt Defaults an
}

//------------------------------------------------------------------------
void OTableConnectionData::Init(const String& rSourceWinName, const String& rDestWinName, const String& rConnName)
{
    // erst mal alle LineDatas loeschen
    for(::std::vector<OConnectionLineData*>::iterator aIter = m_vConnLineData.begin();aIter != m_vConnLineData.end();++aIter)
        delete *aIter;

    m_vConnLineData.clear();
    // dann die Strings
    m_aSourceWinName = rSourceWinName;
    m_aDestWinName = rDestWinName;
    m_aConnName = rConnName;

    // den Rest erledigt das andere Init
    Init();
}

//------------------------------------------------------------------------
OTableConnectionData::OTableConnectionData( const OTableConnectionData& rConnData )
{
    DBG_CTOR(OTableConnectionData,NULL);
    *this = rConnData;
}

//------------------------------------------------------------------------
void OTableConnectionData::CopyFrom(const OTableConnectionData& rSource)
{
    *this = rSource;
    // hier ziehe ich mich auf das (nicht-virtuelle) operator= zurueck, das nur meine Members kopiert
}

//------------------------------------------------------------------------
OTableConnectionData::~OTableConnectionData()
{
    // LineDataList loeschen
    ResetConnLines(FALSE);
    DBG_DTOR(OTableConnectionData,NULL);
}

//------------------------------------------------------------------------
OTableConnectionData& OTableConnectionData::operator=( const OTableConnectionData& rConnData )
{
    if (&rConnData == this)
        return *this;

    m_aSourceWinName = rConnData.GetSourceWinName();
    m_aDestWinName = rConnData.GetDestWinName();
    m_aConnName = rConnData.GetConnName();

    // clear line list
    ResetConnLines(FALSE);

    // und kopieren
    ::std::vector<OConnectionLineData*>* pLineData = const_cast<OTableConnectionData*>(&rConnData)->GetConnLineDataList();
    
    ::std::vector<OConnectionLineData*>::const_iterator aIter = pLineData->begin();
    for(;aIter != pLineData->end();++aIter)
        m_vConnLineData.push_back(new OConnectionLineData(**aIter));

    return *this;
}

//------------------------------------------------------------------------
BOOL OTableConnectionData::SetConnLine( USHORT nIndex, const String& rSourceFieldName, const String& rDestFieldName )
{
    if (USHORT(m_vConnLineData.size()) < nIndex)
        return FALSE;
        // == ist noch erlaubt, das entspricht einem Append

    if (m_vConnLineData.size() == nIndex)
        return AppendConnLine(rSourceFieldName, rDestFieldName);

    OConnectionLineData* pConnLineData = m_vConnLineData[nIndex];
    DBG_ASSERT(pConnLineData != NULL, "OTableConnectionData::SetConnLine : habe ungueltiges LineData-Objekt");

    pConnLineData->SetSourceFieldName( rSourceFieldName );
    pConnLineData->SetDestFieldName( rDestFieldName );

    return TRUE;
}

//------------------------------------------------------------------------
BOOL OTableConnectionData::AppendConnLine( const String& rSourceFieldName, const String& rDestFieldName )
{
    OConnectionLineData* pNew = new OConnectionLineData(rSourceFieldName, rDestFieldName);
    if (!pNew)
        return FALSE;

    m_vConnLineData.push_back(pNew);
    return TRUE;
}

//------------------------------------------------------------------------
void OTableConnectionData::ResetConnLines( BOOL bUseDefaults )
{
    for(::std::vector<OConnectionLineData*>::iterator aIter = m_vConnLineData.begin();aIter != m_vConnLineData.end();++aIter)
        delete *aIter;
    m_vConnLineData.clear();

    if (bUseDefaults)
    {
        for (USHORT i=0; i<MAX_CONN_COUNT; i++)
            m_vConnLineData.push_back( new OConnectionLineData());
    }
}

//------------------------------------------------------------------------
OConnectionLineData* OTableConnectionData::CreateLineDataObj()
{
    return new OConnectionLineData();
}

//------------------------------------------------------------------------
OConnectionLineData* OTableConnectionData::CreateLineDataObj( const OConnectionLineData& rConnLineData )
{
    return new OConnectionLineData( rConnLineData );
}
// -----------------------------------------------------------------------------
OTableConnectionData* OTableConnectionData::NewInstance() const 
{ 
    return new OTableConnectionData(); 
}
// -----------------------------------------------------------------------------




