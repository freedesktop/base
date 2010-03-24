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
#include "precompiled_reportdesign.hxx"
#include "xmlGroup.hxx"
#include "xmlSection.hxx"
#include "xmlFunction.hxx"
#include "xmlfilter.hxx"
#include <xmloff/xmltoken.hxx>
#include <xmloff/xmlnmspe.hxx>
#include <xmloff/nmspmap.hxx>
#include <xmloff/xmluconv.hxx>
#include "xmlHelper.hxx"
#include "xmlEnums.hxx"
#include <ucbhelper/content.hxx>
#include <comphelper/namecontainer.hxx>
#include <com/sun/star/report/GroupOn.hpp>
#include <com/sun/star/report/KeepTogether.hpp>
#include <tools/debug.hxx>

namespace rptxml
{
    using namespace ::com::sun::star;
    using namespace ::com::sun::star::uno;
    using namespace ::com::sun::star::report;
    using namespace ::com::sun::star::xml::sax;

    sal_uInt16 lcl_getKeepTogetherOption(const ::rtl::OUString& _sValue)
    {
        sal_uInt16 nRet = report::KeepTogether::NO;
        const SvXMLEnumMapEntry* aXML_EnumMap = OXMLHelper::GetKeepTogetherOptions();
        SvXMLUnitConverter::convertEnum( nRet, _sValue, aXML_EnumMap );
        return nRet;
    }
DBG_NAME( rpt_OXMLGroup )

OXMLGroup::OXMLGroup( ORptFilter& _rImport
                ,sal_uInt16 nPrfx
                ,const ::rtl::OUString& _sLocalName
                ,const Reference< XAttributeList > & _xAttrList 
                ) :
    SvXMLImportContext( _rImport, nPrfx, _sLocalName )
{
    DBG_CTOR( rpt_OXMLGroup,NULL);

    m_xGroups = _rImport.getReportDefinition()->getGroups();
    OSL_ENSURE(m_xGroups.is(),"Groups is NULL!");
    m_xGroup = m_xGroups->createGroup();
    
    OSL_ENSURE(_xAttrList.is(),"Attribute list is NULL!");

    const SvXMLNamespaceMap& rMap = _rImport.GetNamespaceMap();
    const SvXMLTokenMap& rTokenMap = _rImport.GetGroupElemTokenMap();
    m_xGroup->setSortAscending(sal_False);// the default value has to be set
    const sal_Int16 nLength = (_xAttrList.is()) ? _xAttrList->getLength() : 0;
    static const ::rtl::OUString s_sTRUE = ::xmloff::token::GetXMLToken(XML_TRUE);
    for(sal_Int16 i = 0; i < nLength; ++i)
    {
        ::rtl::OUString sLocalName;
        const ::rtl::OUString sAttrName = _xAttrList->getNameByIndex( i );
        const sal_uInt16 nPrefix = rMap.GetKeyByAttrName( sAttrName,&sLocalName );
        ::rtl::OUString sValue = _xAttrList->getValueByIndex( i );

        try
        {
            switch( rTokenMap.Get( nPrefix, sLocalName ) )
            {
                case XML_TOK_START_NEW_COLUMN:
                    m_xGroup->setStartNewColumn(sValue == s_sTRUE);
                    break;
                case XML_TOK_RESET_PAGE_NUMBER:
                    m_xGroup->setResetPageNumber(sValue == s_sTRUE);
                    break;
                case XML_TOK_SORT_ASCENDING:
                    m_xGroup->setSortAscending(sValue == s_sTRUE);
                    break;
                case XML_TOK_GROUP_EXPRESSION:
                    {
                        sal_Int32 nLen = sValue.getLength();
                        if ( nLen )
                        {
                            const static ::rtl::OUString s_sChanged(RTL_CONSTASCII_USTRINGPARAM("rpt:HASCHANGED(\""));
                            sal_Int32 nPos = sValue.indexOf(s_sChanged);
                            if ( nPos == -1 )
                                nPos = 5;
                            else
                            {
                                nPos = s_sChanged.getLength();
                                --nLen;
                            }
                            sValue = sValue.copy(nPos,nLen-nPos-1);
                            const ORptFilter::TGroupFunctionMap& aFunctions = _rImport.getFunctions();
                            ORptFilter::TGroupFunctionMap::const_iterator aFind = aFunctions.find(sValue);
                            if ( aFind != aFunctions.end() )
                            {
                                sal_Int32 nIndex = 0;
                                const ::rtl::OUString sCompleteFormula = aFind->second->getFormula();
                                ::rtl::OUString sExpression = sCompleteFormula.getToken(1,'[',nIndex);
                                nIndex = 0;
                                sExpression = sExpression.getToken(0,']',nIndex);
                                nIndex = 0;
                                const ::rtl::OUString sFormula = sCompleteFormula.getToken(0,'(',nIndex);
                                ::sal_Int16 nGroupOn = report::GroupOn::DEFAULT;

                                if ( sFormula ==::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("rpt:LEFT")))
                                {
                                    nGroupOn = report::GroupOn::PREFIX_CHARACTERS;
                                    ::rtl::OUString sInterval = sCompleteFormula.getToken(1,';',nIndex);
                                    nIndex = 0;
                                    sInterval = sInterval.getToken(0,')',nIndex);
                                    m_xGroup->setGroupInterval(sInterval.toInt32());
                                }
                                else if ( sFormula ==::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("rpt:YEAR")))
                                    nGroupOn = report::GroupOn::YEAR;
                                else if ( sFormula ==::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("rpt:MONTH")))
                                {
                                    if ( sCompleteFormula.endsWithIgnoreAsciiCaseAsciiL("\4",2) )
                                        nGroupOn = report::GroupOn::QUARTAL;
                                    else
                                        nGroupOn = report::GroupOn::MONTH;
                                }
                                else if ( sFormula ==::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("rpt:WEEK")))
                                    nGroupOn = report::GroupOn::WEEK;
                                else if ( sFormula ==::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("rpt:DAY")))
                                    nGroupOn = report::GroupOn::DAY;
                                else if ( sFormula ==::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("rpt:HOUR")))
                                    nGroupOn = report::GroupOn::HOUR;
                                else if ( sFormula ==::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("rpt:MINUTE")))
                                    nGroupOn = report::GroupOn::MINUTE;
                                else if ( sFormula ==::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("rpt:INT")))
                                {
                                    nGroupOn = report::GroupOn::INTERVAL;
                                    _rImport.removeFunction(sExpression);
                                    sExpression = sExpression.copy(::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("INT_count_")).getLength());
                                    
                                    nIndex = 0;
                                    ::rtl::OUString sInterval = sCompleteFormula.getToken(1,'/',nIndex);
                                    nIndex = 0;
                                    sInterval = sInterval.getToken(0,')',nIndex);
                                    m_xGroup->setGroupInterval(sInterval.toInt32());
                                }

                                m_xGroup->setGroupOn(nGroupOn);
    
                                _rImport.removeFunction(sValue);
                                sValue = sExpression;
                            }
                            m_xGroup->setExpression(sValue);
                        }
                    }
                    break;
                case XML_TOK_GROUP_KEEP_TOGETHER:
                    m_xGroup->setKeepTogether(lcl_getKeepTogetherOption(sValue));
                    break;
                default:
                    break;
            }
        }
        catch(const Exception&)
        {
            OSL_ENSURE(0,"Exception catched while putting group props!");
        }
    }
}
// -----------------------------------------------------------------------------

OXMLGroup::~OXMLGroup()
{

    DBG_DTOR( rpt_OXMLGroup,NULL);
}
// -----------------------------------------------------------------------------
SvXMLImportContext* OXMLGroup::CreateChildContext(
        sal_uInt16 nPrefix,
        const ::rtl::OUString& rLocalName,
        const Reference< XAttributeList > & xAttrList )
{
    SvXMLImportContext *pContext = 0;
    ORptFilter& rImport = GetOwnImport();
    const SvXMLTokenMap&	rTokenMap	= rImport.GetGroupElemTokenMap();

    switch( rTokenMap.Get( nPrefix, rLocalName ) )
    {
        case XML_TOK_GROUP_FUNCTION:
            {
                rImport.GetProgressBarHelper()->Increment( PROGRESS_BAR_STEP );
                pContext = new OXMLFunction( rImport, nPrefix, rLocalName,xAttrList,m_xGroup.get());
            }
            break;
        case XML_TOK_GROUP_HEADER:
            {
                rImport.GetProgressBarHelper()->Increment( PROGRESS_BAR_STEP );
                m_xGroup->setHeaderOn(sal_True);
                pContext = new OXMLSection( rImport, nPrefix, rLocalName,xAttrList,m_xGroup->getHeader());
            }
            break;
        case XML_TOK_GROUP_GROUP:
            rImport.GetProgressBarHelper()->Increment( PROGRESS_BAR_STEP );
            pContext = new OXMLGroup( rImport, nPrefix, rLocalName,xAttrList);
            break;
        case XML_TOK_GROUP_DETAIL:
            {
                rImport.GetProgressBarHelper()->Increment( PROGRESS_BAR_STEP );
                Reference<XReportDefinition> m_xComponent = rImport.getReportDefinition();
                pContext = new OXMLSection( rImport, nPrefix, rLocalName,xAttrList ,m_xComponent->getDetail());
            }
            break;

        case XML_TOK_GROUP_FOOTER:
            {
                rImport.GetProgressBarHelper()->Increment( PROGRESS_BAR_STEP );
                m_xGroup->setFooterOn(sal_True);
                pContext = new OXMLSection( rImport, nPrefix, rLocalName,xAttrList,m_xGroup->getFooter());
            }
            break;
        default:
            break;
    }

    if( !pContext )
        pContext = new SvXMLImportContext( GetImport(), nPrefix, rLocalName );

    return pContext;
}
// -----------------------------------------------------------------------------
ORptFilter& OXMLGroup::GetOwnImport()
{
    return static_cast<ORptFilter&>(GetImport());
}
// -----------------------------------------------------------------------------
void OXMLGroup::EndElement()
{
    try
    {
        // the group elements end in the reverse order
        m_xGroups->insertByIndex(0,uno::makeAny(m_xGroup));
    }catch(uno::Exception&)
    {
        OSL_ENSURE(0,"Exception catched!");
    }
}
// -----------------------------------------------------------------------------
//----------------------------------------------------------------------------
} // namespace rptxml
// -----------------------------------------------------------------------------
