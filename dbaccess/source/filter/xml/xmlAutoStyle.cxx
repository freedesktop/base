/*************************************************************************
 *
 *  $RCSfile: xmlAutoStyle.cxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: obo $ $Date: 2005-01-05 12:30:17 $
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
#ifndef DBA_XMLAUTOSTYLE_HXX 
#include "xmlAutoStyle.hxx"
#endif
#ifndef DBA_XMLHELPER_HXX
#include "xmlHelper.hxx"
#endif
#ifndef DBA_XMLEXPORT_HXX
#include "xmlExport.hxx"
#endif
#ifndef _XMLOFF_FAMILIES_HXX_
#include <xmloff/families.hxx>
#endif

namespace dbaxml
{
    using namespace ::com::sun::star::uno;
    using namespace ::com::sun::star::xml::sax;

void OXMLAutoStylePoolP::exportStyleAttributes(
            SvXMLAttributeList& rAttrList,
            sal_Int32 nFamily,
            const ::std::vector< XMLPropertyState >& rProperties,
            const SvXMLExportPropertyMapper& rPropExp
            , const SvXMLUnitConverter& rUnitConverter,
            const SvXMLNamespaceMap& rNamespaceMap
            ) const
{
    SvXMLAutoStylePoolP::exportStyleAttributes( rAttrList, nFamily, rProperties, rPropExp, rUnitConverter, rNamespaceMap );
    if ( nFamily == XML_STYLE_FAMILY_TABLE_COLUMN )
    {
        UniReference< XMLPropertySetMapper > aPropMapper = rODBExport.GetColumnStylesPropertySetMapper();
        ::std::vector< XMLPropertyState >::const_iterator i = rProperties.begin();
        ::std::vector< XMLPropertyState >::const_iterator aEnd = rProperties.end();
        for (i; i != aEnd ; ++i)
        {			
            sal_Int16 nContextID = aPropMapper->GetEntryContextId(i->mnIndex);
            switch (nContextID)
            {
                case CTF_DB_NUMBERFORMAT :
                {
                    sal_Int32 nNumberFormat;
                    if ( i->maValue >>= nNumberFormat )
                    {
                        rtl::OUString sAttrValue = rODBExport.getDataStyleName(nNumberFormat);
                        if ( sAttrValue.getLength() )
                        {
                            GetExport().AddAttribute(
                                aPropMapper->GetEntryNameSpace(i->mnIndex),
                                aPropMapper->GetEntryXMLName(i->mnIndex),
                                sAttrValue );
                        }
                    }
                    break;
                }					
            }
        }
    }
}
// -----------------------------------------------------------------------------
OXMLAutoStylePoolP::OXMLAutoStylePoolP(ODBExport& rTempODBExport):
    SvXMLAutoStylePoolP(rTempODBExport),
    rODBExport(rTempODBExport)
{
}
// -----------------------------------------------------------------------------
OXMLAutoStylePoolP::~OXMLAutoStylePoolP()
{
}
// -----------------------------------------------------------------------------

//----------------------------------------------------------------------------
} // namespace dbaxml
// -----------------------------------------------------------------------------
