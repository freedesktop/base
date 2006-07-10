/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: DExport.cxx,v $
 *
 *  $Revision: 1.33 $
 *
 *  last change: $Author: obo $ $Date: 2006-07-10 15:35:09 $
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
#ifndef DBAUI_DATABASEEXPORT_HXX
#include "DExport.hxx"
#endif
#ifndef _COM_SUN_STAR_SDBCX_XTABLESSUPPLIER_HPP_
#include <com/sun/star/sdbcx/XTablesSupplier.hpp>
#endif
#ifndef _COM_SUN_STAR_SDBCX_XDATADESCRIPTORFACTORY_HPP_ 
#include <com/sun/star/sdbcx/XDataDescriptorFactory.hpp>
#endif
#ifndef _COM_SUN_STAR_SDBCX_XCOLUMNSSUPPLIER_HPP_
#include <com/sun/star/sdbcx/XColumnsSupplier.hpp>
#endif
#ifndef _COM_SUN_STAR_SDBCX_XAPPEND_HPP_
#include <com/sun/star/sdbcx/XAppend.hpp>
#endif
#ifndef _COM_SUN_STAR_SDBCX_KEYTYPE_HPP_
#include <com/sun/star/sdbcx/KeyType.hpp>
#endif
#ifndef _COM_SUN_STAR_SDBC_DATATYPE_HPP_
#include <com/sun/star/sdbc/DataType.hpp>
#endif
#ifndef _COM_SUN_STAR_SDBC_COLUMNVALUE_HPP_
#include <com/sun/star/sdbc/ColumnValue.hpp>
#endif
#ifndef _COM_SUN_STAR_SDB_COMMANDTYPE_HPP_
#include <com/sun/star/sdb/CommandType.hpp>
#endif
#ifndef _COM_SUN_STAR_SDBC_XRESULTSETMETADATASUPPLIER_HPP_
#include <com/sun/star/sdbc/XResultSetMetaDataSupplier.hpp>
#endif
#ifndef _COM_SUN_STAR_SDBC_XROW_HPP_
#include <com/sun/star/sdbc/XRow.hpp>
#endif
#ifndef _COM_SUN_STAR_UTIL_NUMBERFORMAT_HPP_
#include <com/sun/star/util/NumberFormat.hpp>
#endif
#ifndef _COM_SUN_STAR_UTIL_XNUMBERFORMATTYPES_HPP_
#include <com/sun/star/util/XNumberFormatTypes.hpp>
#endif
#ifndef DBACCESS_SHARED_DBUSTRINGS_HRC
#include "dbustrings.hrc"
#endif
#ifndef _DBU_MISC_HRC_
#include "dbu_misc.hrc"
#endif
#ifndef _DBHELPER_DBCONVERSION_HXX_
#include <connectivity/dbconversion.hxx>
#endif
#ifndef _SFXHTML_HXX
#include <sfx2/sfxhtml.hxx>
#endif
#ifndef _NUMUNO_HXX
#include <svtools/numuno.hxx>
#endif
#ifndef _CONNECTIVITY_DBTOOLS_HXX_
#include <connectivity/dbtools.hxx>
#endif
#ifndef _COMPHELPER_EXTRACT_HXX_
#include <comphelper/extract.hxx>
#endif
#ifndef DBAUI_TYPEINFO_HXX
#include "TypeInfo.hxx"
#endif
#ifndef DBAUI_FIELDDESCRIPTIONS_HXX
#include "FieldDescriptions.hxx"
#endif
#ifndef DBAUI_TOOLS_HXX
#include "UITools.hxx"
#endif
#ifndef _UTL_CONFIGMGR_HXX_
#include <unotools/configmgr.hxx>
#endif
#include <memory>
#ifndef _TOOLS_DEBUG_HXX
#include <tools/debug.hxx>
#endif
#ifndef INCLUDED_I18NPOOL_MSLANGID_HXX
#include <i18npool/mslangid.hxx>
#endif
#ifndef _COM_SUN_STAR_AWT_FONTDESCRIPTOR_HPP_
#include <com/sun/star/awt/FontDescriptor.hpp>
#endif
#ifndef DBAUI_WIZ_COPYTABLEDIALOG_HXX
#include "WCopyTable.hxx"
#endif
#ifndef DBAUI_WIZ_EXTENDPAGES_HXX
#include "WExtendPages.hxx"
#endif
#ifndef DBAUI_WIZ_NAMEMATCHING_HXX
#include "WNameMatch.hxx"
#endif
#ifndef DBAUI_WIZ_COLUMNSELECT_HXX
#include "WColumnSelect.hxx"
#endif
#ifndef DBAUI_WIZARD_CPAGE_HXX
#include "WCPage.hxx"
#endif
#ifndef INCLUDED_SVTOOLS_SYSLOCALE_HXX
#include <svtools/syslocale.hxx>
#endif
#ifndef _DBHELPER_DBEXCEPTION_HXX_
#include <connectivity/dbexception.hxx>
#endif
#ifndef _CONNECTIVITY_FILE_VALUE_HXX_
#include <connectivity/FValue.hxx>
#endif
#ifndef _COM_SUN_STAR_SDBC_SQLWARNING_HPP_
#include <com/sun/star/sdbc/SQLWarning.hpp>
#endif
#ifndef _COM_SUN_STAR_SDB_SQLCONTEXT_HPP_
#include <com/sun/star/sdb/SQLContext.hpp>
#endif
#ifndef _DBAUI_SQLMESSAGE_HXX_
#include "sqlmessage.hxx"
#endif
#ifndef DBAUI_UPDATEHELPERIMPL_HXX
#include "UpdateHelperImpl.hxx"
#endif
#ifndef _SV_MSGBOX_HXX
#include <vcl/msgbox.hxx>
#endif


using namespace dbaui;
using namespace utl;
using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::beans;
using namespace ::com::sun::star::container;
using namespace ::com::sun::star::util;
using namespace ::com::sun::star::sdbc;
using namespace ::com::sun::star::sdbcx;
using namespace ::com::sun::star::sdb;
using namespace ::com::sun::star::lang;
using namespace ::com::sun::star::awt;

// ==========================================================================
// ==========================================================================
// ODatabaseExport
// ==========================================================================
DBG_NAME(ODatabaseExport)
ODatabaseExport::ODatabaseExport(sal_Int32 nRows,
                                 const TPositions &_rColumnPositions,
                                 const Reference< XNumberFormatter >& _rxNumberF,
                                 const Reference< ::com::sun::star::lang::XMultiServiceFactory >& _rM,
                                 const TColumnVector* pList,
                                 const OTypeInfoMap* _pInfoMap,
                                 sal_Bool _bAutoIncrementEnabled)
    :m_vColumns(_rColumnPositions)
    ,m_aDestColumns(sal_True)
    ,m_xFormatter(_rxNumberF)
    ,m_xFactory(_rM)
    ,m_pFormatter(NULL)
    ,m_pTypeInfo()
    ,m_pColumnList(pList)
    ,m_pInfoMap(_pInfoMap)
    ,m_nColumnPos(0)
    ,m_nRows(1)
    ,m_nRowCount(0)
    ,m_nDefToken( gsl_getSystemTextEncoding() )
    ,m_bError(FALSE)
    ,m_bInTbl(FALSE)
    ,m_bHead(TRUE)
    ,m_bDontAskAgain(FALSE)
    ,m_bIsAutoIncrement(_bAutoIncrementEnabled)
    ,m_bFoundTable(sal_False)
    ,m_bCheckOnly(sal_False)
{
    DBG_CTOR(ODatabaseExport,NULL); 

    m_nRows += nRows;
    sal_Int32 nCount = 0;
    for(sal_Int32 j=0;j < (sal_Int32)m_vColumns.size();++j)
        if ( m_vColumns[j].first != COLUMN_POSITION_NOT_FOUND )
            ++nCount;

    m_vColumnSize.resize(nCount);
    m_vFormatKey.resize(nCount);
    for(sal_Int32 i=0;i<nCount;++i)
    {
        m_vColumnSize[i] = 0;
        m_vFormatKey[i] = 0;
    }

    try
    {
        SvtSysLocale aSysLocale;
        m_aLocale = aSysLocale.GetLocaleData().getLocale();
    }
    catch(Exception&)
    {
    }

    SetColumnTypes(pList,_pInfoMap);
}
//---------------------------------------------------------------------------
ODatabaseExport::ODatabaseExport(const SharedConnection& _rxConnection,
                                 const Reference< XNumberFormatter >& _rxNumberF,
                                 const Reference< ::com::sun::star::lang::XMultiServiceFactory >& _rM,
                                 const TColumnVector* pList,
                                 const OTypeInfoMap* _pInfoMap)
    :m_aDestColumns(_rxConnection->getMetaData().is() && _rxConnection->getMetaData()->supportsMixedCaseQuotedIdentifiers() == sal_True)
    ,m_xConnection(_rxConnection)
    ,m_xFormatter(_rxNumberF)
    ,m_xFactory(_rM)
    ,m_pFormatter(NULL)
    ,m_pTypeInfo()
    ,m_pColumnList(NULL)
    ,m_pInfoMap(NULL)
    ,m_nColumnPos(0)
    ,m_nRows(1)
    ,m_nRowCount(0)
    ,m_nDefToken( gsl_getSystemTextEncoding() )
    ,m_bError(sal_False)
    ,m_bInTbl(sal_False)
    ,m_bHead(TRUE)
    ,m_bDontAskAgain(sal_False)
    ,m_bIsAutoIncrement(sal_False)
    ,m_bFoundTable(sal_False)
    ,m_bCheckOnly(sal_False)
{
    DBG_CTOR(ODatabaseExport,NULL); 
    try
    {
        SvtSysLocale aSysLocale;
        m_aLocale = aSysLocale.GetLocaleData().getLocale();
    }
    catch(Exception&)
    {
    }

    Reference<XTablesSupplier> xTablesSup(m_xConnection,UNO_QUERY);
    if(xTablesSup.is())
        m_xTables = xTablesSup->getTables();

    Reference<XDatabaseMetaData> xMeta = m_xConnection->getMetaData();
    Reference<XResultSet> xSet = xMeta.is() ? xMeta->getTypeInfo() : Reference<XResultSet>();
    if(xSet.is())
    {
        ::connectivity::ORowSetValue aValue;
        ::std::vector<sal_Int32> aTypes;
        Reference<XResultSetMetaData> xResultSetMetaData = Reference<XResultSetMetaDataSupplier>(xSet,UNO_QUERY)->getMetaData();
        Reference<XRow> xRow(xSet,UNO_QUERY);
        while(xSet->next())
        {
            if ( aTypes.empty() )
            {
                sal_Int32 nCount = xResultSetMetaData->getColumnCount();
                if ( nCount < 1 )
                    nCount = 18;
                aTypes.reserve(nCount+1);
                aTypes.push_back(-1);
                for (sal_Int32 j = 1; j <= nCount ; ++j)
                    aTypes.push_back(xResultSetMetaData->getColumnType(j));
            }

            sal_Int32 nPos = 1;
            aValue.fill(nPos,aTypes[nPos],xRow);
            ::rtl::OUString sTypeName = aValue;
            ++nPos;
            aValue.fill(nPos,aTypes[nPos],xRow);
            sal_Int32 nType = aValue;
            ++nPos;
            
            if( nType == DataType::VARCHAR)
            {
                m_pTypeInfo					= TOTypeInfoSP(new OTypeInfo());
                
                m_pTypeInfo->aTypeName		= sTypeName;
                m_pTypeInfo->nType			= nType;
                
                aValue.fill(nPos,aTypes[nPos],xRow);
                m_pTypeInfo->nPrecision		= aValue;
                ++nPos;
                aValue.fill(nPos,aTypes[nPos],xRow);
                m_pTypeInfo->aLiteralPrefix	= aValue;
                ++nPos;
                aValue.fill(nPos,aTypes[nPos],xRow);
                m_pTypeInfo->aLiteralSuffix	= aValue;
                ++nPos;
                aValue.fill(nPos,aTypes[nPos],xRow);
                m_pTypeInfo->aCreateParams	= aValue;
                ++nPos;
                aValue.fill(nPos,aTypes[nPos],xRow);
                m_pTypeInfo->bNullable		= (sal_Int32)aValue == ColumnValue::NULLABLE;
                ++nPos;
                aValue.fill(nPos,aTypes[nPos],xRow);
                m_pTypeInfo->bCaseSensitive	= aValue;
                ++nPos;
                aValue.fill(nPos,aTypes[nPos],xRow);
                m_pTypeInfo->nSearchType		= aValue;
                ++nPos;
                aValue.fill(nPos,aTypes[nPos],xRow);
                m_pTypeInfo->bUnsigned		= aValue;
                ++nPos;
                aValue.fill(nPos,aTypes[nPos],xRow);
                m_pTypeInfo->bCurrency		= aValue;
                ++nPos;
                aValue.fill(nPos,aTypes[nPos],xRow);
                m_pTypeInfo->bAutoIncrement	= aValue;
                ++nPos;
                aValue.fill(nPos,aTypes[nPos],xRow);
                m_pTypeInfo->aLocalTypeName	= aValue;
                ++nPos;
                aValue.fill(nPos,aTypes[nPos],xRow);
                m_pTypeInfo->nMinimumScale	= aValue;
                ++nPos;
                aValue.fill(nPos,aTypes[nPos],xRow);
                m_pTypeInfo->nMaximumScale	= aValue;

                // check if values are less than zero like it happens in a oracle jdbc driver
                if( m_pTypeInfo->nPrecision < 0)
                    m_pTypeInfo->nPrecision = 0;
                if( m_pTypeInfo->nMinimumScale < 0)
                    m_pTypeInfo->nMinimumScale = 0;
                if( m_pTypeInfo->nMaximumScale < 0)
                    m_pTypeInfo->nMaximumScale = 0;
                break;
            }
        }
    }
    SetColumnTypes(pList,_pInfoMap);
}
//---------------------------------------------------------------------------
ODatabaseExport::~ODatabaseExport()
{
    DBG_DTOR(ODatabaseExport,NULL); 
    m_pFormatter = NULL;
    ODatabaseExport::TColumns::iterator aIter = m_aDestColumns.begin();
    ODatabaseExport::TColumns::iterator aEnd  = m_aDestColumns.end();

    for(;aIter != aEnd;++aIter)
        delete aIter->second;
    m_vDestVector.clear();
    m_aDestColumns.clear();	
}
// -----------------------------------------------------------------------------
void ODatabaseExport::insertValueIntoColumn()
{
    DBG_CHKTHIS(ODatabaseExport,NULL);
    if(m_nColumnPos < sal_Int32(m_vDestVector.size()))
    {
        OFieldDescription* pField = m_vDestVector[m_nColumnPos]->second;
        if(pField)
        {
            sal_Int32 nNewPos = m_bIsAutoIncrement ? m_nColumnPos+1 : m_nColumnPos;
            OSL_ENSURE((nNewPos) < static_cast<sal_Int32>(m_vColumns.size()),"Illegal index for vector");
            
            sal_Int32 nPos = m_vColumns[nNewPos].first;
            if ( nPos != COLUMN_POSITION_NOT_FOUND )
            {
//                  if(m_nDefToken != LANGUAGE_DONTKNOW) // falls Sprache anders als Systemsprache
//                      m_pNF->ChangeIntl((LanguageType)m_nDefToken);

                if(!m_sTextToken.Len() && m_xResultSetMetaData->isNullable(nPos))
                    m_pUpdateHelper->updateNull(nPos,pField->GetType());
                else
                {
                    sal_Int32 nNumberFormat = 0;
                    double fOutNumber = 0.0;
                    OSL_ENSURE((nNewPos) < static_cast<sal_Int32>(m_vColumnTypes.size()),"Illegal index for vector");
                    if (m_vColumnTypes[nNewPos] != DataType::VARCHAR)
                    {
                        Reference< XNumberFormatsSupplier >  xSupplier = m_xFormatter->getNumberFormatsSupplier();
                        Reference<XPropertySet> xNumberFormatSettings = xSupplier->getNumberFormatSettings();
                        com::sun::star::util::Date aNullDate;
                        xNumberFormatSettings->getPropertyValue(::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("NullDate"))) >>= aNullDate;

                        ensureFormatter();
                        if ( m_pFormatter && m_sNumToken.Len() )
                        {
                            LanguageType eNumLang;
                            sal_uInt32 nNumberFormat2;
                            fOutNumber = SfxHTMLParser::GetTableDataOptionsValNum(nNumberFormat2,eNumLang,m_sTextToken,m_sNumToken,*m_pFormatter);
                            nNumberFormat = static_cast<sal_Int32>(nNumberFormat2);
                        }
                        else
                        {
                            Reference<XNumberFormatTypes> xNumType(xSupplier->getNumberFormats(),UNO_QUERY);

                            try
                            {
                                nNumberFormat = m_xFormatter->detectNumberFormat(xNumType->getStandardFormat(NumberFormat::DATETIME,m_aLocale),m_sTextToken);
                            }
                            catch(Exception&)
                            {
                                try
                                {
                                    nNumberFormat = m_xFormatter->detectNumberFormat(xNumType->getStandardFormat(NumberFormat::DATE,m_aLocale),m_sTextToken);
                                }
                                catch(Exception&)
                                {
                                    try
                                    {
                                        nNumberFormat = m_xFormatter->detectNumberFormat(xNumType->getStandardFormat(NumberFormat::TIME,m_aLocale),m_sTextToken);
                                    }
                                    catch(Exception&)
                                    {
                                        try
                                        {
                                            nNumberFormat = m_xFormatter->detectNumberFormat(xNumType->getStandardFormat(NumberFormat::NUMBER,m_aLocale),m_sTextToken);
                                        }
                                        catch(Exception&)
                                        {
                                        }
                                    }
                                }
                            }
                            fOutNumber = m_xFormatter->convertStringToNumber(nNumberFormat,m_sTextToken);
                        }
                        try
                        {
                            Reference< XNumberFormats >         xFormats = xSupplier->getNumberFormats();
                            Reference<XPropertySet> xProp = xFormats->getByKey(nNumberFormat);
                            sal_Int16 nType = 0;
                            xProp->getPropertyValue(PROPERTY_TYPE) >>= nType;
                            switch(nType)
                            {
                                case NumberFormat::DATE:
                                case NumberFormat::DATETIME:
                                    fOutNumber = ::dbtools::DBTypeConversion::toStandardDbDate(aNullDate,fOutNumber);
                                    break;
                                default:
                                    ;
                            }
                            m_pUpdateHelper->updateDouble(nPos,fOutNumber);//::dbtools::DBTypeConversion::getStandardDate()
                        }
                        catch(Exception&)
                        {
                            m_pUpdateHelper->updateString(nPos,m_sTextToken);
                        }

                    }
                    else
                        m_pUpdateHelper->updateString(nPos,m_sTextToken);
                }
            }
            eraseTokens();
        }
    }
}
// -----------------------------------------------------------------------------
sal_Int32 ODatabaseExport::CheckString(const String& aCheckToken, sal_Int32 _nOldFormat)
{
    DBG_CHKTHIS(ODatabaseExport,NULL);
    double fOutNumber = 0.0;
    sal_Int32 nFormat = 0;

    try
    {
        Reference< XNumberFormatsSupplier > xSupplier = m_xFormatter->getNumberFormatsSupplier();
        Reference< XNumberFormats >         xFormats = xSupplier->getNumberFormats();

        ensureFormatter();
        if ( m_pFormatter && m_sNumToken.Len() )
        {
            LanguageType eNumLang;
            sal_uInt32 nNumberFormat2;
            fOutNumber = SfxHTMLParser::GetTableDataOptionsValNum(nNumberFormat2,eNumLang,m_sTextToken,m_sNumToken,*m_pFormatter);
            //double fOutNumber2 = SfxHTMLParser::GetTableDataOptionsValNum(nNumberFormat2,eNumLang,m_sValToken,m_sNumToken,*m_pFormatter);
            nFormat = static_cast<sal_Int32>(nNumberFormat2);
        }
        else
        {           
            Reference<XNumberFormatTypes> xNumType(xFormats,UNO_QUERY);
            nFormat = m_xFormatter->detectNumberFormat(xNumType->getStandardFormat(NumberFormat::ALL,m_aLocale),aCheckToken);
            fOutNumber = m_xFormatter->convertStringToNumber(nFormat,aCheckToken);

            Reference<XPropertySet> xProp = xFormats->getByKey(nFormat);
            sal_Int16 nType = 0;
            xProp->getPropertyValue(PROPERTY_TYPE) >>= nType;
            
            switch(nType)
            {
                case NumberFormat::ALL:
                    nFormat = NumberFormat::ALL;
                    break;
                case NumberFormat::DEFINED:
                    nFormat = NumberFormat::TEXT;
                    break;
                case NumberFormat::DATE:
                    switch(_nOldFormat)
                    {
                        case NumberFormat::DATETIME:
                        case NumberFormat::TEXT:
                        case NumberFormat::DATE:
                            break;
                        case NumberFormat::ALL:
                            nFormat = NumberFormat::DATE;
                            break;
                        default:
                            nFormat = NumberFormat::TEXT;

                    }
                    break;
                case NumberFormat::TIME:
                    switch(_nOldFormat)
                    {
                        case NumberFormat::DATETIME:
                        case NumberFormat::TEXT:
                        case NumberFormat::TIME:
                            break;
                        case NumberFormat::ALL:
                            nFormat = NumberFormat::TIME;
                            break;
                        default:
                            nFormat = NumberFormat::TEXT;
                            break;
                    }
                    break;
                case NumberFormat::CURRENCY:
                    switch(_nOldFormat)
                    {
                        case NumberFormat::NUMBER:
                            nFormat = NumberFormat::CURRENCY;
                            break;
                        case NumberFormat::CURRENCY:
                            break;
                        case NumberFormat::ALL:
                            nFormat = NumberFormat::CURRENCY;
                            break;
                        default:
                            nFormat = NumberFormat::TEXT;
                            break;
                    }
                    break;
                case NumberFormat::NUMBER:
                case NumberFormat::SCIENTIFIC:
                case NumberFormat::FRACTION:
                case NumberFormat::PERCENT:
                    switch(_nOldFormat)
                    {
                        case NumberFormat::NUMBER:
                            break;
                        case NumberFormat::CURRENCY:
                            nFormat = NumberFormat::CURRENCY;
                            break;
                        case NumberFormat::ALL:
                            nFormat = nType;
                            break;
                        default:
                            nFormat = NumberFormat::TEXT;
                            break;
                    }
                    break;
                case NumberFormat::TEXT:
                case NumberFormat::UNDEFINED:
                case NumberFormat::LOGICAL:
                    nFormat = NumberFormat::TEXT; // Text "uberschreibt alles
                    break;
                case NumberFormat::DATETIME:
                    switch(_nOldFormat)
                    {
                        case NumberFormat::DATETIME:
                        case NumberFormat::TEXT:
                        case NumberFormat::TIME:
                            break;
                        case NumberFormat::ALL:
                            nFormat = NumberFormat::DATETIME;
                            break;
                        default:
                            nFormat = NumberFormat::TEXT;
                            break;
                    }
                    break;
                default:
                    OSL_ENSURE(0,"ODatabaseExport: Unbekanntes Format");
            }
        }
    }
    catch(Exception&)
    {
        nFormat = NumberFormat::TEXT; // Text "uberschreibt alles
    }

    return nFormat;
}
// -----------------------------------------------------------------------------
void ODatabaseExport::SetColumnTypes(const TColumnVector* _pList,const OTypeInfoMap* _pInfoMap)
{
    DBG_CHKTHIS(ODatabaseExport,NULL);
    if(_pList && _pInfoMap)
    {
        Reference< XNumberFormatsSupplier > xSupplier = m_xFormatter->getNumberFormatsSupplier();
        Reference< XNumberFormats >         xFormats = xSupplier->getNumberFormats();
        TColumnVector::const_iterator aIter = _pList->begin();
        TColumnVector::const_iterator aEnd = _pList->end();
        for(sal_Int32 i= 0;aIter != aEnd;++aIter,++i)
        {
            sal_Int32 nDataType;
            sal_Int32 nLength(0),nScale(0);
            Reference<XPropertySet> xProp = xFormats->getByKey(m_vFormatKey[i]);
            sal_Int16 nType = 0;
            xProp->getPropertyValue(PROPERTY_TYPE) >>= nType;
            switch ( nType )
            {
                case NumberFormat::ALL:
                    nDataType  = DataType::DOUBLE;
                    break;
                case NumberFormat::DEFINED:
                    nDataType	= DataType::VARCHAR;
                    nLength		= ((m_vColumnSize[i] % 10 ) ? m_vColumnSize[i]/ 10 + 1: m_vColumnSize[i]/ 10) * 10;
                    break;
                case NumberFormat::DATE:
                    nDataType  = DataType::DATE;
                    break;
                case NumberFormat::TIME:
                    nDataType  = DataType::TIME;
                    break;
                case NumberFormat::DATETIME:
                    nDataType  = DataType::TIMESTAMP;
                    break;
                case NumberFormat::CURRENCY:
                    nDataType  = DataType::NUMERIC;
                    nScale		= 4;
                    nLength		= 19;
                    break;
                case NumberFormat::NUMBER:
                case NumberFormat::SCIENTIFIC:
                case NumberFormat::FRACTION:
                case NumberFormat::PERCENT:
                    nDataType  = DataType::DOUBLE;
                    break;
                case NumberFormat::TEXT:
                case NumberFormat::UNDEFINED:
                case NumberFormat::LOGICAL:
                default:
                    nDataType  = DataType::VARCHAR;
                    nLength		= ((m_vColumnSize[i] % 10 ) ? m_vColumnSize[i]/ 10 + 1: m_vColumnSize[i]/ 10) * 10;
                    break;
            }
            OTypeInfoMap::const_iterator aFind = _pInfoMap->find(nDataType);
            if(aFind != _pInfoMap->end())
            {
                (*aIter)->second->SetType(aFind->second);
                (*aIter)->second->SetPrecision(::std::min<sal_Int32>(aFind->second->nPrecision,nLength));
                (*aIter)->second->SetScale(::std::min<sal_Int32>(aFind->second->nMaximumScale,nScale));
            }
            (*aIter)->second->SetFormatKey(m_vFormatKey[i]);
        }
    }
}
// -----------------------------------------------------------------------------
void ODatabaseExport::CreateDefaultColumn(const ::rtl::OUString& _rColumnName)
{
    DBG_CHKTHIS(ODatabaseExport,NULL);
    Reference< XDatabaseMetaData>  xDestMetaData(m_xConnection->getMetaData());	
    sal_Int32 nMaxNameLen(xDestMetaData->getMaxColumnNameLength());
    ::rtl::OUString aAlias = _rColumnName;
    if ( isSQL92CheckEnabled(m_xConnection) )
        aAlias = ::dbtools::convertName2SQLName(_rColumnName,xDestMetaData->getExtraNameCharacters());

    if(nMaxNameLen && aAlias.getLength() > nMaxNameLen)
        aAlias = aAlias.copy(0, ::std::min<sal_Int32>( nMaxNameLen, aAlias.getLength() ) );
    
    ::rtl::OUString sName(aAlias);
    if(m_aDestColumns.find(sName) != m_aDestColumns.end())
    {
        aAlias = aAlias.copy(0,::std::min<sal_Int32>( nMaxNameLen-1, aAlias.getLength() ));
    
        sal_Int32 nPos = 0;
        sal_Int32 nCount = 2;
        while(m_aDestColumns.find(sName) != m_aDestColumns.end())
        {
            sName = aAlias;
            sName += ::rtl::OUString::valueOf(++nPos);
            if(nMaxNameLen && sName.getLength() > nMaxNameLen)
            {
                aAlias = aAlias.copy(0,::std::min<sal_Int32>( nMaxNameLen-nCount, aAlias.getLength() ));
                sName = aAlias;
                sName += ::rtl::OUString::valueOf(nPos);
                ++nCount;
            }
        }
    }
    aAlias = sName;
    // now create a column
    OFieldDescription* pField = new OFieldDescription();
    pField->SetType(m_pTypeInfo);
    pField->SetName(aAlias);
    pField->SetPrecision(::std::min<sal_Int32>((sal_Int32)255,m_pTypeInfo->nPrecision));
    pField->SetScale(0);
    pField->SetIsNullable(ColumnValue::NULLABLE);
    pField->SetAutoIncrement(sal_False);
    pField->SetPrimaryKey(sal_False);
    pField->SetCurrency(sal_False);

    TColumns::iterator aFind = m_aDestColumns.find( aAlias );
    if ( aFind != m_aDestColumns.end() )
    {
        delete aFind->second;
        m_aDestColumns.erase(aFind);
    }

    m_vDestVector.push_back(m_aDestColumns.insert(TColumns::value_type(aAlias,pField)).first);
}
// -----------------------------------------------------------------------------
sal_Bool ODatabaseExport::createRowSet()
{
    DBG_CHKTHIS(ODatabaseExport,NULL);
    Reference<XResultSet> xDestSet(m_xFactory->createInstance(::rtl::OUString::createFromAscii("com.sun.star.sdb.RowSet")),UNO_QUERY);
    Reference<XPropertySet > xProp(xDestSet,UNO_QUERY);
    if(xProp.is())
    {
        ::rtl::OUString sDestName = ::dbtools::composeTableName(
            m_xConnection->getMetaData(), m_xTable, ::dbtools::eInDataManipulation, false, false, false );

        xProp->setPropertyValue(PROPERTY_ACTIVECONNECTION,makeAny(m_xConnection.getTyped()));
        xProp->setPropertyValue(PROPERTY_COMMANDTYPE,makeAny(CommandType::TABLE));
        xProp->setPropertyValue(PROPERTY_COMMAND,makeAny(sDestName));
        xProp->setPropertyValue(PROPERTY_IGNORERESULT,::cppu::bool2any(sal_True));
        Reference<XRowSet> xRowSet(xProp,UNO_QUERY);
        xRowSet->execute();

        Reference< XResultSetMetaDataSupplier> xSrcMetaSup(xRowSet,UNO_QUERY_THROW);
        m_xResultSetMetaData = xSrcMetaSup->getMetaData();

        if ( ::dbtools::canInsert(xProp) )
        {
            m_pUpdateHelper.reset(new ORowUpdateHelper(xRowSet));
        OSL_ENSURE(m_xResultSetMetaData.is(),"No ResultSetMetaData!");
    }
        else
            m_pUpdateHelper.reset(new OParameterUpdateHelper(createPreparedStatment(m_xConnection->getMetaData(),m_xTable,m_vColumns)));
    }

    return m_pUpdateHelper.get() != NULL;
}
// -----------------------------------------------------------------------------
sal_Bool ODatabaseExport::executeWizard(const ::rtl::OUString& _sTableName,const Any& _aTextColor,const FontDescriptor& _rFont)
{
    DBG_CHKTHIS(ODatabaseExport,NULL);
    OCopyTableWizard aWizard(NULL,_sTableName,m_aDestColumns,m_vDestVector,m_xConnection,m_xFormatter,m_xFactory);
    
    sal_Bool bError = sal_False;
    try
    {
        aWizard.fillTypeInfo();

        OCopyTable*			pPage1 = new OCopyTable(&aWizard,COPY, sal_False,OCopyTableWizard::WIZARD_DEF_DATA);
        OWizNameMatching*	pPage2 = new OWizNameMatching(&aWizard);
        OWizColumnSelect*	pPage3 = new OWizColumnSelect(&aWizard);		
        OWizTypeSelect*		pPage4 = createPage(&aWizard);

        aWizard.AddWizardPage(pPage1);
        aWizard.AddWizardPage(pPage2);
        aWizard.AddWizardPage(pPage3);
        aWizard.AddWizardPage(pPage4);

        aWizard.ActivatePage();

        if (aWizard.Execute())
        {
            switch(aWizard.getCreateStyle())
            {
                case OCopyTableWizard::WIZARD_DEF_DATA:
                case OCopyTableWizard::WIZARD_APPEND_DATA:
                    {
                        m_xTable = aWizard.createTable();
                        bError = !m_xTable.is();
                        if(m_xTable.is())
                        {
                            m_xTable->setPropertyValue(PROPERTY_FONT,makeAny(_rFont));
                            if(_aTextColor.hasValue())
                                m_xTable->setPropertyValue(PROPERTY_TEXTCOLOR,_aTextColor);
                        }
                        m_bIsAutoIncrement	= aWizard.isAutoincrementEnabled();
                        m_vColumns			= aWizard.GetColumnPositions();
                        m_vColumnTypes		= aWizard.GetColumnTypes();
                    }
                    break;
                default:
                    bError = sal_True; // there is no error but I have nothing more to do
            }
        }
        else
            bError = sal_True;

        if(!bError)
            bError = !createRowSet();
    }
    catch(SQLContext& e) 
    { 
        ::dbaui::showError(::dbtools::SQLExceptionInfo(e),&aWizard,m_xFactory); 
        bError = sal_True;
    }
    catch(SQLWarning& e) 
    { 

        ::dbaui::showError(::dbtools::SQLExceptionInfo(e),&aWizard,m_xFactory); 
        bError = sal_True;
    }
    catch(SQLException& e) 
    {


        ::dbaui::showError(::dbtools::SQLExceptionInfo(e),&aWizard,m_xFactory); 
        bError = sal_True;
    }
    catch(Exception& )
    {
        OSL_ENSURE(sal_False, "ODatabaseExport::executeWizard: caught a generic exception!");
    }

    return bError;
}
//---------------------------------------------------------------------------------
void ODatabaseExport::showErrorDialog(const ::com::sun::star::sdbc::SQLException& e)
{
    if(!m_bDontAskAgain)
    {
        String aMsg(e.Message);
        aMsg += '\n';
        aMsg += String(ModuleRes(STR_QRY_CONTINUE));
        OSQLMessageBox aBox(NULL, String(ModuleRes(STR_STAT_WARNING)),
            aMsg, WB_YES_NO | WB_DEF_NO, OSQLMessageBox::Warning);

        if (aBox.Execute() == RET_YES)
            m_bDontAskAgain = TRUE;
        else
            m_bError = TRUE;
    } // if(!m_bDontAskAgain)
}
// -----------------------------------------------------------------------------
void ODatabaseExport::adjustFormat()
{
    if ( m_sTextToken.Len() )
    {
        sal_Int32 nColPos = m_vColumns[m_bIsAutoIncrement ? m_nColumnPos+1 : m_nColumnPos].first;
        if( nColPos != sal::static_int_cast< long >(CONTAINER_ENTRY_NOTFOUND))
        {
            --nColPos;
            m_vFormatKey[nColPos] = CheckString(m_sTextToken,m_vFormatKey[nColPos]);
            m_vColumnSize[nColPos] = ::std::max<sal_Int32>((sal_Int32)m_vColumnSize[nColPos],(sal_Int32)m_sTextToken.Len());
        }
        eraseTokens();
    }
}
// -----------------------------------------------------------------------------
void ODatabaseExport::eraseTokens()
{
    m_sTextToken.Erase();
    m_sNumToken.Erase();
    m_sValToken.Erase();
}
// -----------------------------------------------------------------------------
void ODatabaseExport::ensureFormatter()
{
    if ( !m_pFormatter )
    {
        Reference< XNumberFormatsSupplier >  xSupplier = m_xFormatter->getNumberFormatsSupplier();
        Reference< XUnoTunnel > xTunnel(xSupplier,UNO_QUERY);
        SvNumberFormatsSupplierObj* pSupplierImpl = (SvNumberFormatsSupplierObj*)sal::static_int_cast< sal_IntPtr >(xTunnel->getSomething(SvNumberFormatsSupplierObj::getUnoTunnelId()));
        m_pFormatter = pSupplierImpl ? pSupplierImpl->GetNumberFormatter() : NULL;
    }
}
// -----------------------------------------------------------------------------
Reference< XPreparedStatement > ODatabaseExport::createPreparedStatment( const Reference<XDatabaseMetaData>& _xMetaData
                                                       ,const Reference<XPropertySet>& _xDestTable
                                                       ,const TPositions& _rvColumns)
{
    ::rtl::OUString aSql(::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("INSERT INTO ")));
    ::rtl::OUString sComposedTableName = ::dbtools::composeTableName( _xMetaData, _xDestTable, ::dbtools::eInDataManipulation, false, false, true );

    aSql += sComposedTableName;
    aSql += ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM(" ( "));
    // set values and column names
    ::rtl::OUString aValues(RTL_CONSTASCII_USTRINGPARAM(" VALUES ( "));
    static ::rtl::OUString aPara(RTL_CONSTASCII_USTRINGPARAM("?,"));
    static ::rtl::OUString aComma(RTL_CONSTASCII_USTRINGPARAM(","));

    ::rtl::OUString aQuote;
    if ( _xMetaData.is() )
        aQuote = _xMetaData->getIdentifierQuoteString();

    Reference<XColumnsSupplier> xDestColsSup(_xDestTable,UNO_QUERY_THROW);

    // create sql string and set column types
    Sequence< ::rtl::OUString> aDestColumnNames = xDestColsSup->getColumns()->getElementNames();
    if ( aDestColumnNames.getLength() == 0 )
    {
        return Reference< XPreparedStatement > ();
    }
    const ::rtl::OUString* pIter = aDestColumnNames.getConstArray();
    ::std::vector< ::rtl::OUString> aInsertList;
    aInsertList.resize(aDestColumnNames.getLength()+1);
    sal_Int32 i = 0;
    for(sal_uInt32 j=0; j < aInsertList.size() ;++i,++j)
    {
        ODatabaseExport::TPositions::const_iterator aFind = ::std::find_if(_rvColumns.begin(),_rvColumns.end(),
            ::std::compose1(::std::bind2nd(::std::equal_to<sal_Int32>(),i+1),::std::select2nd<ODatabaseExport::TPositions::value_type>()));
        if ( _rvColumns.end() != aFind && aFind->second != sal::static_int_cast< long >(CONTAINER_ENTRY_NOTFOUND) && aFind->first != sal::static_int_cast< long >(CONTAINER_ENTRY_NOTFOUND) )
        {
            aInsertList[aFind->first] = ::dbtools::quoteName( aQuote,*(pIter+i));
        }
    }

    i = 1;
    // create the sql string
    for (::std::vector< ::rtl::OUString>::iterator aInsertIter = aInsertList.begin(); aInsertIter != aInsertList.end(); ++aInsertIter)
    {
        if ( aInsertIter->getLength() )
        {
            aSql += *aInsertIter;
            aSql += aComma;
            aValues += aPara;
        }
    }

    aSql = aSql.replaceAt(aSql.getLength()-1,1,::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM(")")));
    aValues = aValues.replaceAt(aValues.getLength()-1,1,::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM(")")));

    aSql += aValues;
    // now create,fill and execute the prepared statement
    return Reference< XPreparedStatement >(_xMetaData->getConnection()->prepareStatement(aSql));
}
// -----------------------------------------------------------------------------


