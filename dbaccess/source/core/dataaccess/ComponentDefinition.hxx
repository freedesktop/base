/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: ComponentDefinition.hxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-08 10:13:40 $
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

#ifndef DBA_COREDATAACESS_COMPONENTDEFINITION_HXX
#define DBA_COREDATAACESS_COMPONENTDEFINITION_HXX

#ifndef _DBA_CORE_COMMANDBASE_HXX_
#include "commandbase.hxx"
#endif
#ifndef _COMPHELPER_PROPERTYCONTAINER_HXX_
#include <comphelper/propertycontainer.hxx>
#endif
#ifndef _DBA_REGHELPER_HXX_
#include "dba_reghelper.hxx"
#endif
#ifndef _COM_SUN_STAR_SDBCX_XRENAME_HPP_
#include <com/sun/star/sdbcx/XRename.hpp>
#endif
#ifndef _CPPUHELPER_IMPLBASE1_HXX_
#include <cppuhelper/implbase1.hxx>
#endif
#ifndef _COMPHELPER_PROPERTY_ARRAY_HELPER_HXX_
#include <comphelper/proparrhlp.hxx>
#endif
#ifndef _DBA_CORE_DATASETTINGS_HXX_
#include "datasettings.hxx"
#endif
#ifndef _COM_SUN_STAR_CONTAINER_XNAMEACCESS_HPP_
#include <com/sun/star/container/XNameAccess.hpp>
#endif
#ifndef _COM_SUN_STAR_SDBCX_XCOLUMNSSUPPLIER_HPP_
#include <com/sun/star/sdbcx/XColumnsSupplier.hpp>
#endif
#ifndef DBA_CONTENTHELPER_HXX
#include "ContentHelper.hxx"
#endif
#ifndef _DBA_COREAPI_COLUMN_HXX_
#include <column.hxx>
#endif
#include <memory>
//........................................................................
namespace dbaccess
{
//........................................................................

    typedef ::cppu::ImplHelper1< ::com::sun::star::sdbcx::XColumnsSupplier > OComponentDefinition_BASE;

    class OComponentDefinition_Impl : public OContentHelper_Impl
                                     ,public ODataSettings_Base
    {
    public:
        DECLARE_STL_USTRINGACCESS_MAP(::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertySet> , TColumns);
        DECLARE_STL_VECTOR(TColumns::iterator, TColumnsIndexAccess);

        TColumnsIndexAccess	m_aColumns;				// for a efficient index access
        TColumns			m_aColumnNames;				// for a efficient name access
        ::rtl::OUString		m_sSchemaName;
        ::rtl::OUString		m_sCatalogName;
    };

//=========================================================================
//= OComponentDefinition - a database "document" which describes a query
//=========================================================================

class OComponentDefinition	:public OContentHelper
                            ,public ODataSettings
                            ,public IColumnFactory
                            ,public OComponentDefinition_BASE
                            ,public ::comphelper::OPropertyArrayUsageHelper< OComponentDefinition >
{
    OComponentDefinition();
    
protected:
    ::std::auto_ptr<OColumns>	m_pColumns;
    
    sal_Bool					m_bTable;

    virtual ~OComponentDefinition(); 
    virtual void SAL_CALL disposing();
protected:
    OComponentDefinition(const ::com::sun::star::uno::Reference< ::com::sun::star::lang::XMultiServiceFactory >&
        ,const ::com::sun::star::uno::Reference< ::com::sun::star::uno::XInterface >&	_xParentContainer
        ,const TContentPtr& _pImpl
        ,sal_Bool _bTable = sal_True);

    
public:

    OComponentDefinition(
             const ::com::sun::star::uno::Reference< ::com::sun::star::uno::XInterface >& _rxContainer
            ,const ::rtl::OUString& _rElementName
            ,const ::com::sun::star::uno::Reference< ::com::sun::star::lang::XMultiServiceFactory >&
            ,const TContentPtr& _pImpl
            ,sal_Bool _bTable = sal_True
        );

// com::sun::star::lang::XTypeProvider
    DECLARE_TYPEPROVIDER( );

// ::com::sun::star::uno::XInterface
    DECLARE_XINTERFACE( )

// ::com::sun::star::lang::XServiceInfo
    virtual ::rtl::OUString SAL_CALL getImplementationName(  ) throw(::com::sun::star::uno::RuntimeException);
    virtual ::com::sun::star::uno::Sequence< ::rtl::OUString > SAL_CALL getSupportedServiceNames(  ) throw(::com::sun::star::uno::RuntimeException);

    static ::com::sun::star::uno::Sequence< ::rtl::OUString > getSupportedServiceNames_Static(void) throw( ::com::sun::star::uno::RuntimeException );
    static ::rtl::OUString getImplementationName_Static(void) throw( ::com::sun::star::uno::RuntimeException );
    static ::com::sun::star::uno::Reference< ::com::sun::star::uno::XInterface > SAL_CALL
        Create(const ::com::sun::star::uno::Reference< ::com::sun::star::lang::XMultiServiceFactory >&);

// ::com::sun::star::beans::XPropertySet
    virtual ::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertySetInfo > SAL_CALL getPropertySetInfo(  ) throw(::com::sun::star::uno::RuntimeException);

    // XColumnsSupplier
    virtual ::com::sun::star::uno::Reference< ::com::sun::star::container::XNameAccess > SAL_CALL getColumns(  ) throw (::com::sun::star::uno::RuntimeException);

    // OPropertySetHelper
    virtual ::cppu::IPropertyArrayHelper& SAL_CALL getInfoHelper();

    // IColumnFactory
    virtual OColumn*	createColumn(const ::rtl::OUString& _rName) const;
    virtual ::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertySet > createEmptyObject();
    virtual void columnDropped(const ::rtl::OUString& _sName);
    virtual void columnCloned(const ::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertySet >& _xClone);

protected:
// OPropertyArrayUsageHelper
    virtual ::cppu::IPropertyArrayHelper* createArrayHelper( ) const;

    virtual void SAL_CALL setFastPropertyValue_NoBroadcast(
                                    sal_Int32 nHandle,
                                    const ::com::sun::star::uno::Any& rValue) throw (::com::sun::star::uno::Exception);
private:
    void registerProperties();

};

//........................................................................
}	// namespace dbaccess
//........................................................................

#endif // DBA_COREDATAACESS_COMPONENTDEFINITION_HXX


