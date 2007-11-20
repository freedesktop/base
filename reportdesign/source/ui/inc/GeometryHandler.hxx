/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: GeometryHandler.hxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: ihi $ $Date: 2007-11-20 19:10:00 $
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

#ifndef RPT_GEOMETRYHANDLER_HXX
#define RPT_GEOMETRYHANDLER_HXX

#ifndef _SAL_CONFIG_H_
#include "sal/config.h"
#endif
#ifndef _COM_SUN_STAR_UNO_XCOMPONENTCONTEXT_HPP_
#include "com/sun/star/uno/XComponentContext.hpp"
#endif
#ifndef _CPPUHELPER_COMPBASE3_HXX_
#include "cppuhelper/compbase3.hxx"
#endif
#ifndef _CPPUHELPER_BASEMUTEX_HXX_
#include "cppuhelper/basemutex.hxx"
#endif
#ifndef _COM_SUN_STAR_INSPECTION_XPROPERTYHANDLER_HPP_
#include "com/sun/star/inspection/XPropertyHandler.hpp"
#endif
#ifndef _COM_SUN_STAR_SCRIPT_XTYPECONVERTER_HPP_
#include "com/sun/star/script/XTypeConverter.hpp"
#endif
#ifndef _COM_SUN_STAR_BEANS_XPROPERTYSET_HPP_
#include "com/sun/star/beans/XPropertySet.hpp"
#endif
#ifndef _COM_SUN_STAR_LANG_XSERVICEINFO_HPP_
#include "com/sun/star/lang/XServiceInfo.hpp"
#endif
#include "com/sun/star/report/XReportComponent.hpp"
#include "com/sun/star/report/XFunction.hpp"
#include <com/sun/star/beans/XPropertyChangeListener.hpp>
#ifndef _COM_SUN_STAR_SDBC_XROWSET_HPP_
#include <com/sun/star/sdbc/XRowSet.hpp>
#endif
#include <memory>
#include <comphelper/stl_types.hxx>
#include <comphelper/listenernotification.hxx>
#ifndef RPTUI_METADATA_HXX_
#include "metadata.hxx"
#endif

//........................................................................
namespace rptui
{
//........................................................................

    struct DefaultFunction
    {
        com::sun::star::beans::Optional< ::rtl::OUString>   m_sInitialFormula;
        ::rtl::OUString                                     m_sName;
        ::rtl::OUString                                     m_sSearchString;
        ::rtl::OUString                                     m_sFormula;
        ::sal_Bool                                          m_bPreEvaluated;
        ::sal_Bool                                          m_bDeepTraversing;

        inline ::rtl::OUString getName() const { return m_sName; }
    } ;

    class OPropertyInfoService;
    typedef ::std::pair< ::com::sun::star::uno::Reference< ::com::sun::star::report::XFunction>, ::com::sun::star::uno::Reference< ::com::sun::star::report::XFunctionsSupplier> > TFunctionPair;
    typedef ::std::multimap< ::rtl::OUString,TFunctionPair, ::comphelper::UStringMixLess > TFunctions;
    typedef ::comphelper::OSimpleListenerContainer  <   ::com::sun::star::beans::XPropertyChangeListener
                                                    ,   ::com::sun::star::beans::PropertyChangeEvent
                                                    >   PropertyChangeListeners;
    typedef ::cppu::WeakComponentImplHelper3<   ::com::sun::star::inspection::XPropertyHandler
                                            ,   ::com::sun::star::beans::XPropertyChangeListener
                                            ,   ::com::sun::star::lang::XServiceInfo> GeometryHandler_Base;

    class GeometryHandler:
        private ::cppu::BaseMutex,
        public GeometryHandler_Base
    {
        /** sets the counter function at the data field.
        *   If the counter function doesn't exist it will be created.
        */
        void impl_setCounterFunction_throw();

        /** executes a dialog for chosing a filter criterion for a database report
            @param _out_rSelectedClause
                the filter or order clause as chosen by the user
            @precond
                we're really inspecting a database form (well, a RowSet at least)
            @return
                <TRUE/> if and only if the user successfully chose a clause
        */
        bool impl_dialogFilter_nothrow( ::rtl::OUString& _out_rSelectedClause, ::osl::ClearableMutexGuard& _rClearBeforeDialog ) const;

        /** returns the data field type depending on the data field of the report control
        *
        * \param _sDataField if the data field is not empty it will be used as data field, otherwise the data field will be used.
        * \return the data field type
        */
        sal_uInt32 impl_getDataFieldType_throw(const ::rtl::OUString& _sDataField = ::rtl::OUString()) const;

        ::com::sun::star::uno::Any getConstantValue(sal_Bool bToControlValue,sal_uInt16 nResId,const ::com::sun::star::uno::Any& _aValue,const ::rtl::OUString& _sConstantName,const ::rtl::OUString & PropertyName );
        ::com::sun::star::beans::Property getProperty(const ::rtl::OUString & PropertyName);
        void implCreateListLikeControl(
                const ::com::sun::star::uno::Reference< ::com::sun::star::inspection::XPropertyControlFactory >& _rxControlFactory
                ,::com::sun::star::inspection::LineDescriptor & out_Descriptor
                ,sal_uInt16 _nResId
                ,sal_Bool _bReadOnlyControl
                ,sal_Bool _bTrueIfListBoxFalseIfComboBox
            );
        void implCreateListLikeControl(
                const ::com::sun::star::uno::Reference< ::com::sun::star::inspection::XPropertyControlFactory >& _rxControlFactory
                ,::com::sun::star::inspection::LineDescriptor & out_Descriptor
                ,const ::std::vector< ::rtl::OUString>& _aEntries
                ,sal_Bool _bReadOnlyControl
                ,sal_Bool _bTrueIfListBoxFalseIfComboBox
            );
        void checkPosAndSize(   const ::com::sun::star::awt::Point& _aNewPos,
                                const ::com::sun::star::awt::Size& _aSize);

        ::rtl::OUString impl_convertToFormula( const ::com::sun::star::uno::Any& _rControlValue );

        void impl_initFieldList_nothrow( ::com::sun::star::uno::Sequence< ::rtl::OUString >& _rFieldNames ) const;

        /** Creates the function defined by the function template
        *
        * \param _sFunctionName the function name
        * \param _sDataField the data field
        * \param _aFunction the function template
        */
        void impl_createFunction(const ::rtl::OUString& _sFunctionName,const ::rtl::OUString& _sDataField,const DefaultFunction& _aFunction);

        /** check whether the given function name is a countr function.
        *
        * \param _sQuotedFunctionName the quoted function name to check
        * \param _Out_sScope the scope of the function
        * \return When true it is a counter functions otherwise false.
        */
        bool impl_isCounterFunction_throw(const ::rtl::OUString& _sQuotedFunctionName,::rtl::OUString& _Out_sScope) const;

        /** clear the own properties like function and scope and send a notification
        *
        * \param _aGuard 
        * \param _sOldFunctionName 
        * \param _sOldScope 
        * \param _nOldDataFieldType
        */
       void resetOwnProperties(::osl::ResettableMutexGuard& _aGuard,const ::rtl::OUString& _sOldFunctionName,const ::rtl::OUString& _sOldScope,const sal_uInt32 _nOldDataFieldType);

        /** checks whether the name is a field or a parameter
        *
        * \param _sName the name to check
        * \return true when it is a field or parameter otherwise false
        */
        bool impl_isDataField(const ::rtl::OUString& _sName) const;

        /**return all formula in a semicolon seperated list
        *
        * \param _rList the localized function names
        */
        void impl_fillFormulaList_nothrow(::std::vector< ::rtl::OUString >& _out_rList) const;

        /**return all group names in a semicolon seperated list starting with the group where this control is contained in.
        *
        * \param _rList fills the list with all scope names.
        */
        void impl_fillScopeList_nothrow(::std::vector< ::rtl::OUString >& _out_rList) const;

        /** get the functions supplier for the set scope, default is the surrounding group.
        *
        * \param _rsNamePostFix the name post fix which canbe used when the scope as name part is needed
        * \return the function supplier
        */
        ::com::sun::star::uno::Reference< ::com::sun::star::report::XFunctionsSupplier> fillScope_throw(::rtl::OUString& _rsNamePostFix);
        ::rtl::OUString getFormula() const;

        /** checks if the given function is a default function we know.
        *
        * \param _sQuotedFunction the quoted function name
        * \param _Out_rDataField the data field which is used in the function
        * \param _xFunctionsSupplier teh function supplier to search or empty if not used
        * \param _bSet If set to TRUE than the m_sDefaultFunction and m_sScope vars will be set if successful.
        * \return sal_True with known otherwise sal_False
        */
        sal_Bool isDefaultFunction(const ::rtl::OUString& _sQuotedFunction
                                    ,::rtl::OUString& _Out_rDataField
                                    ,const ::com::sun::star::uno::Reference< ::com::sun::star::report::XFunctionsSupplier>& _xFunctionsSupplier = ::com::sun::star::uno::Reference< ::com::sun::star::report::XFunctionsSupplier>()
                                    ,bool _bSet = false) const;

        /** checks if the given function is a default function we know.
        *
        * \param _xFunction 
        * \param _rDataField 
        * \param _rsDefaultFunctionName 
        * \return 
        */
        sal_Bool impl_isDefaultFunction_nothrow( const ::com::sun::star::uno::Reference< ::com::sun::star::report::XFunction>& _xFunction
                                            ,::rtl::OUString& _rDataField
                                            ,::rtl::OUString& _rsDefaultFunctionName) const;

        /** fills the memeber m_aDefaultFunctions
        *
        */
        void loadDefaultFunctions();

        /** creates a default functionof the _sFunction for the data field _sDataField
        *   The new function will only be created if it didn't exist.
        *   
        * \param _aGuard        Will be cleared, when a new function was created.
        * \param _sFunction     The name of the function.
        * \param _sDataField    The name of the data field.
        */
        void createDefaultFunction(::osl::ResettableMutexGuard& _aGuard ,const ::rtl::OUString& _sFunction,const ::rtl::OUString& _sDataField);

        void removeFunction();

        class OBlocker
        {
            bool& m_bIn;
        public:
            OBlocker(bool& _bIn) : m_bIn(_bIn){ m_bIn = true; }
            ~OBlocker() { m_bIn = false; }
        };


        // XEventListener
        virtual void SAL_CALL disposing(const ::com::sun::star::lang::EventObject& Source) throw( ::com::sun::star::uno::RuntimeException );
        // XPropertyChangeListener
        virtual void SAL_CALL propertyChange(const ::com::sun::star::beans::PropertyChangeEvent& evt) throw(::com::sun::star::uno::RuntimeException);

    public:
        // XServiceInfo - static versions
        static ::rtl::OUString getImplementationName_Static(  ) throw(::com::sun::star::uno::RuntimeException);
        static ::com::sun::star::uno::Sequence< ::rtl::OUString > getSupportedServiceNames_static(  ) throw(::com::sun::star::uno::RuntimeException);
        static ::com::sun::star::uno::Reference< ::com::sun::star::uno::XInterface > SAL_CALL
                        create(const ::com::sun::star::uno::Reference< ::com::sun::star::uno::XComponentContext >&);

    public:
        explicit GeometryHandler(::com::sun::star::uno::Reference< ::com::sun::star::uno::XComponentContext > const & context);

        // XServiceInfo
        virtual ::rtl::OUString SAL_CALL getImplementationName(  ) throw(::com::sun::star::uno::RuntimeException);
        virtual sal_Bool SAL_CALL supportsService( const ::rtl::OUString& ServiceName ) throw(::com::sun::star::uno::RuntimeException);
        virtual ::com::sun::star::uno::Sequence< ::rtl::OUString > SAL_CALL getSupportedServiceNames(  ) throw(::com::sun::star::uno::RuntimeException);

        // ::com::sun::star::lang::XComponent:
        virtual void SAL_CALL addEventListener(const ::com::sun::star::uno::Reference< ::com::sun::star::lang::XEventListener > & xListener)   throw (::com::sun::star::uno::RuntimeException);
        virtual void SAL_CALL removeEventListener(const ::com::sun::star::uno::Reference< ::com::sun::star::lang::XEventListener > & aListener) throw (::com::sun::star::uno::RuntimeException);

        // ::com::sun::star::inspection::XPropertyHandler:
        virtual void SAL_CALL inspect(const ::com::sun::star::uno::Reference< ::com::sun::star::uno::XInterface > & Component) throw (::com::sun::star::uno::RuntimeException, ::com::sun::star::lang::NullPointerException);
        virtual ::com::sun::star::uno::Any SAL_CALL getPropertyValue(const ::rtl::OUString & PropertyName) throw (::com::sun::star::uno::RuntimeException, ::com::sun::star::beans::UnknownPropertyException);
        virtual void SAL_CALL setPropertyValue(const ::rtl::OUString & PropertyName, const ::com::sun::star::uno::Any & Value) throw (::com::sun::star::uno::RuntimeException, ::com::sun::star::beans::UnknownPropertyException);
        virtual ::com::sun::star::beans::PropertyState SAL_CALL getPropertyState(const ::rtl::OUString & PropertyName) throw (::com::sun::star::uno::RuntimeException, ::com::sun::star::beans::UnknownPropertyException);
        virtual ::com::sun::star::inspection::LineDescriptor SAL_CALL describePropertyLine(const ::rtl::OUString& PropertyName, const ::com::sun::star::uno::Reference< ::com::sun::star::inspection::XPropertyControlFactory >& ControlFactory ) throw (::com::sun::star::beans::UnknownPropertyException, ::com::sun::star::lang::NullPointerException, ::com::sun::star::uno::RuntimeException);
        virtual ::com::sun::star::uno::Any SAL_CALL convertToPropertyValue(const ::rtl::OUString & PropertyName, const ::com::sun::star::uno::Any & ControlValue) throw (::com::sun::star::uno::RuntimeException, ::com::sun::star::beans::UnknownPropertyException);
        virtual ::com::sun::star::uno::Any SAL_CALL convertToControlValue(const ::rtl::OUString & PropertyName, const ::com::sun::star::uno::Any & PropertyValue, const ::com::sun::star::uno::Type & ControlValueType) throw (::com::sun::star::uno::RuntimeException, ::com::sun::star::beans::UnknownPropertyException);
        virtual void SAL_CALL addPropertyChangeListener(const ::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertyChangeListener > & Listener) throw (::com::sun::star::uno::RuntimeException, ::com::sun::star::lang::NullPointerException);
        virtual void SAL_CALL removePropertyChangeListener(const ::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertyChangeListener > & _rxListener) throw (::com::sun::star::uno::RuntimeException);
        virtual ::com::sun::star::uno::Sequence< ::com::sun::star::beans::Property > SAL_CALL getSupportedProperties() throw (::com::sun::star::uno::RuntimeException);
        virtual ::com::sun::star::uno::Sequence< ::rtl::OUString > SAL_CALL getSupersededProperties() throw (::com::sun::star::uno::RuntimeException);
        virtual ::com::sun::star::uno::Sequence< ::rtl::OUString > SAL_CALL getActuatingProperties() throw (::com::sun::star::uno::RuntimeException);
        virtual ::sal_Bool SAL_CALL isComposable(const ::rtl::OUString & PropertyName) throw (::com::sun::star::uno::RuntimeException, ::com::sun::star::beans::UnknownPropertyException);
        virtual ::com::sun::star::inspection::InteractiveSelectionResult SAL_CALL onInteractivePropertySelection(const ::rtl::OUString & PropertyName, ::sal_Bool Primary, ::com::sun::star::uno::Any & out_Data, const ::com::sun::star::uno::Reference< ::com::sun::star::inspection::XObjectInspectorUI > & InspectorUI) throw (::com::sun::star::uno::RuntimeException, ::com::sun::star::beans::UnknownPropertyException, ::com::sun::star::lang::NullPointerException);
        virtual void SAL_CALL actuatingPropertyChanged(const ::rtl::OUString & ActuatingPropertyName, const ::com::sun::star::uno::Any & NewValue, const ::com::sun::star::uno::Any & OldValue, const ::com::sun::star::uno::Reference< ::com::sun::star::inspection::XObjectInspectorUI > & InspectorUI, ::sal_Bool FirstTimeInit) throw (::com::sun::star::uno::RuntimeException, ::com::sun::star::lang::NullPointerException);
        virtual ::sal_Bool SAL_CALL suspend(::sal_Bool Suspend) throw (::com::sun::star::uno::RuntimeException);

    protected:
        virtual ~GeometryHandler();
    private:
        GeometryHandler(GeometryHandler &); // not defined
        void operator =(GeometryHandler &); // not defined

        // overload WeakComponentImplHelperBase::disposing()
        // This function is called upon disposing the component,
        // if your component needs special work when it becomes
        // disposed, do it here.
        virtual void SAL_CALL disposing();

        PropertyChangeListeners                                                             m_aPropertyListeners;
        ::com::sun::star::uno::Sequence< ::rtl::OUString >                                  m_aFieldNames;
        ::com::sun::star::uno::Sequence< ::rtl::OUString >                                  m_aParamNames;
        TFunctions                                                                          m_aFunctionNames;
        ::std::vector< DefaultFunction >                                                    m_aDefaultFunctions;
        DefaultFunction                                                                     m_aCounterFunction;
        ::com::sun::star::uno::Reference< ::com::sun::star::uno::XComponentContext >        m_xContext;
        mutable ::com::sun::star::uno::Reference< ::com::sun::star::report::XFunction>      m_xFunction;
        ::com::sun::star::uno::Reference< ::com::sun::star::inspection::XPropertyHandler >  m_xFormComponentHandler; /// delegatee
        ::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertySet >           m_xReportComponent; /// inspectee
        mutable ::com::sun::star::uno::Reference< ::com::sun::star::sdbc::XRowSet >         m_xRowSet;
        /// type converter, needed on various occasions
        ::com::sun::star::uno::Reference< ::com::sun::star::script::XTypeConverter >        m_xTypeConverter;
        /// access to property meta data
        ::std::auto_ptr< OPropertyInfoService >                                             m_pInfoService;
        mutable ::rtl::OUString                                                             m_sDefaultFunction;
        mutable ::rtl::OUString                                                             m_sScope;
        sal_uInt32                                                                          m_nDataFieldType;
        mutable bool                                                                        m_bNewFunction;
        bool                                                                                m_bIn;
    };
//........................................................................
} // namespace rptui
//........................................................................

#endif // RPT_GeometryHandler_HXX
