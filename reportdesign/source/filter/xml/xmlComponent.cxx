/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 * 
 * Copyright 2008 by Sun Microsystems, Inc.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * $RCSfile: xmlComponent.cxx,v $
 * $Revision: 1.4 $
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
#include "xmlComponent.hxx"
#include "xmlfilter.hxx"
#include <xmloff/xmltoken.hxx>
#include <xmloff/xmlnmspe.hxx>
#include <xmloff/xmluconv.hxx>
#include <xmloff/nmspmap.hxx>
#include "xmlEnums.hxx"
#include "xmlHelper.hxx"
#ifndef RPT_SHARED_XMLSTRINGS_HRC
#include "xmlstrings.hrc"
#endif
#include "xmlStyleImport.hxx"
#include <ucbhelper/content.hxx>
#include <tools/debug.hxx>
#include <comphelper/namecontainer.hxx>
#include <comphelper/genericpropertyset.hxx>
#include <com/sun/star/awt/FontDescriptor.hpp>
#include <com/sun/star/report/XReportControlModel.hpp>
#ifndef _COM_SUN_STAR_BEANS_PROPERTYATTRIBUTE_HXX_
#include <com/sun/star/beans/PropertyAttribute.hpp>
#endif
#include <tools/debug.hxx>

namespace rptxml
{
    using namespace ::comphelper;
    using namespace ::com::sun::star;
    using namespace ::com::sun::star::uno;
    using namespace ::com::sun::star::beans;
    using namespace ::com::sun::star::report;
    using namespace ::com::sun::star::xml::sax;
    DBG_NAME( rpt_OXMLComponent )
OXMLComponent::OXMLComponent( ORptFilter& _rImport
                ,sal_uInt16 nPrfx
                ,const ::rtl::OUString& _sLocalName
                ,const Reference< XAttributeList > & _xAttrList 
                ,const Reference< XReportComponent > & _xComponent 
                ) :
    SvXMLImportContext( _rImport, nPrfx, _sLocalName )
    ,m_xComponent(_xComponent)
{
    DBG_CTOR( rpt_OXMLComponent,NULL);	
    OSL_ENSURE(_xAttrList.is(),"Attribute list is NULL!");
    OSL_ENSURE(m_xComponent.is(),"Component is NULL!");

    const SvXMLNamespaceMap& rMap = _rImport.GetNamespaceMap();
    const SvXMLTokenMap& rTokenMap = _rImport.GetComponentElemTokenMap();

    const sal_Int16 nLength = (_xAttrList.is()) ? _xAttrList->getLength() : 0;
    static const ::rtl::OUString s_sTRUE = ::xmloff::token::GetXMLToken(XML_TRUE);
    
    for(sal_Int16 i = 0; i < nLength; ++i)
    {
        try
        {
            ::rtl::OUString sLocalName;
            const ::rtl::OUString sAttrName = _xAttrList->getNameByIndex( i );
            const sal_uInt16 nPrefix = rMap.GetKeyByAttrName( sAttrName,&sLocalName );
            const ::rtl::OUString sValue = _xAttrList->getValueByIndex( i );

            switch( rTokenMap.Get( nPrefix, sLocalName ) )
            {
                case XML_TOK_NAME: 
                    m_xComponent->setName(sValue);
                    break;
                case XML_TOK_TEXT_STYLE_NAME:
                    m_sTextStyleName = sValue;
                    break;
                case XML_TOK_TRANSFORM:
                    break;
                default:
                    break;
            }
        }
        catch(const Exception&)
        {
            OSL_ENSURE(0,"Exception catched while putting props into report component!");
        }
    }	
}
// -----------------------------------------------------------------------------

OXMLComponent::~OXMLComponent()
{
    DBG_DTOR( rpt_OXMLComponent,NULL);	
}
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
ORptFilter& OXMLComponent::GetOwnImport()
{
    return static_cast<ORptFilter&>(GetImport());
}
// -----------------------------------------------------------------------------
//----------------------------------------------------------------------------
} // namespace rptxml
// -----------------------------------------------------------------------------
