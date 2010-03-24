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

// MARKER(update_precomp.py): autogen include statement, do not remove
#include "precompiled_dbaccess.hxx"

#ifndef DBAUI_TOOLS_HXX
#include "UITools.hxx"
#endif
#ifndef _SFX_DOCFILT_HACK_HXX
#include <sfx2/docfilt.hxx>
#endif
#ifndef _DBACCESS_UI_CALLBACKS_HXX_
#include "callbacks.hxx"
#endif
#ifndef DBACCESS_SHARED_DBUSTRINGS_HRC
#include "dbustrings.hrc"
#endif
#ifndef _DBU_RESOURCE_HRC_
#include "dbu_resource.hrc"
#endif
#ifndef DBAUI_DLGSAVE_HXX
#include "dlgsave.hxx"
#endif
#ifndef DBAUI_DBTREELISTBOX_HXX
#include "dbtreelistbox.hxx"
#endif
#ifndef DBACCESS_SOURCE_UI_INC_DEFAULTOBJECTNAMECHECK_HXX
#include "defaultobjectnamecheck.hxx"
#endif
#ifndef _COMPHELPER_EXTRACT_HXX_
#include <comphelper/extract.hxx>
#endif
#ifndef _COM_SUN_STAR_SDB_XSINGLESELECTQUERYANALYZER_HPP_
#include <com/sun/star/sdb/XSingleSelectQueryAnalyzer.hpp>
#endif
#ifndef _COM_SUN_STAR_SDB_XCOMPLETEDCONNECTION_HPP_
#include <com/sun/star/sdb/XCompletedConnection.hpp>
#endif
#ifndef _COM_SUN_STAR_SDBC_XDATASOURCE_HPP_
#include <com/sun/star/sdbc/XDataSource.hpp>
#endif
#ifndef _COM_SUN_STAR_SDB_SQLCONTEXT_HPP_
#include <com/sun/star/sdb/SQLContext.hpp>
#endif
#ifndef _COM_SUN_STAR_SDBCX_XKEYSSUPPLIER_HPP_
#include <com/sun/star/sdbcx/XKeysSupplier.hpp>
#endif
#ifndef _COM_SUN_STAR_SDBCX_XCOLUMNSSUPPLIER_HPP_
#include <com/sun/star/sdbcx/XColumnsSupplier.hpp>
#endif
#ifndef _COM_SUN_STAR_SDBCX_XVIEWSSUPPLIER_HPP_
#include <com/sun/star/sdbcx/XViewsSupplier.hpp>
#endif
#ifndef _COM_SUN_STAR_SDBCX_XTABLESSUPPLIER_HPP_
#include <com/sun/star/sdbcx/XTablesSupplier.hpp>
#endif
#ifndef _COM_SUN_STAR_SDBCX_XDATADESCRIPTORFACTORY_HPP_
#include <com/sun/star/sdbcx/XDataDescriptorFactory.hpp>
#endif
#ifndef _COM_SUN_STAR_SDBCX_XAPPEND_HPP_
#include <com/sun/star/sdbcx/XAppend.hpp>
#endif
#ifndef _COM_SUN_STAR_SDBC_XROW_HPP_
#include <com/sun/star/sdbc/XRow.hpp>
#endif
#ifndef _COM_SUN_STAR_SDBC_XRESULTSETMETADATASUPPLIER_HPP_
#include <com/sun/star/sdbc/XResultSetMetaDataSupplier.hpp>
#endif
#ifndef _COM_SUN_STAR_SDBC_XRESULTSETMETADATA_HPP_
#include <com/sun/star/sdbc/XResultSetMetaData.hpp>
#endif
#include <com/sun/star/sdbc/ColumnValue.hpp>
#ifndef _COM_SUN_STAR_TASK_XINTERACTIONHANDLER_HPP_
#include <com/sun/star/task/XInteractionHandler.hpp>
#endif
#ifndef _COM_SUN_STAR_UCB_XCONTENT_HPP_
#include <com/sun/star/ucb/XContent.hpp>
#endif
#ifndef _COM_SUN_STAR_UI_DIALOGS_XEXECUTABLEDIALOG_HPP_
#include <com/sun/star/ui/dialogs/XExecutableDialog.hpp>
#endif
#ifndef _COM_SUN_STAR_BEANS_PROPERTYVALUE_HPP_
#include <com/sun/star/beans/PropertyValue.hpp>
#endif
#ifndef _COM_SUN_STAR_CONTAINER_XINDEXACCESS_HPP_
#include <com/sun/star/container/XIndexAccess.hpp>
#endif
#ifndef _COM_SUN_STAR_CONTAINER_XNAMECONTAINER_HPP_
#include <com/sun/star/container/XNameContainer.hpp>
#endif
#ifndef _COM_SUN_STAR_UCB_INTERACTIVEIOEXCEPTION_HPP_
#include <com/sun/star/ucb/InteractiveIOException.hpp>
#endif
#ifndef _COM_SUN_STAR_SDB_XDOCUMENTDATASOURCE_HPP_
#include <com/sun/star/sdb/XDocumentDataSource.hpp>
#endif
#ifndef _COM_SUN_STAR_UCB_IOERRORCODE_HPP_
#include <com/sun/star/ucb/IOErrorCode.hpp>
#endif
#ifndef _TOOLKIT_HELPER_VCLUNOHELPER_HXX_
#include <toolkit/helper/vclunohelper.hxx>
#endif
#ifndef _TOOLKIT_AWT_VCLXWINDOW_HXX_
#include <toolkit/awt/vclxwindow.hxx>
#endif
#ifndef _VCL_STDTEXT_HXX
#include <vcl/stdtext.hxx>
#endif
#ifndef _COM_SUN_STAR_BEANS_XPROPERTYSETINFO_HPP_
#include <com/sun/star/beans/XPropertySetInfo.hpp>
#endif
#ifndef _COM_SUN_STAR_BEANS_XPROPERTYSET_HPP_
#include <com/sun/star/beans/XPropertySet.hpp>
#endif
#ifndef _COM_SUN_STAR_CONTAINER_XNAMEACCESS_HPP_
#include <com/sun/star/container/XNameAccess.hpp>
#endif
#ifndef _COM_SUN_STAR_CONTAINER_XCONTAINER_HPP_
#include <com/sun/star/container/XContainer.hpp>
#endif
#ifndef _COM_SUN_STAR_CONTAINER_XHIERARCHICALNAMECONTAINER_HPP_
#include <com/sun/star/container/XHierarchicalNameContainer.hpp>
#endif
#ifndef _COM_SUN_STAR_LANG_XMULTISERVICEFACTORY_HPP_
#include <com/sun/star/lang/XMultiServiceFactory.hpp>
#endif
#ifndef _COM_SUN_STAR_AWT_TEXTALIGN_HPP_
#include <com/sun/star/awt/TextAlign.hpp>
#endif
#ifndef _COM_SUN_STAR_AWT_FONTDESCRIPTOR_HPP_
#include <com/sun/star/awt/FontDescriptor.hpp>
#endif
#ifndef _COM_SUN_STAR_AWT_FONTWEIGHT_HPP_
#include <com/sun/star/awt/FontWeight.hpp>
#endif
#ifndef _COM_SUN_STAR_AWT_FONTRELIEF_HPP_
#include <com/sun/star/awt/FontRelief.hpp>
#endif
#ifndef _COM_SUN_STAR_AWT_FONTWIDTH_HPP_
#include <com/sun/star/awt/FontWidth.hpp>
#endif
#ifndef _COM_SUN_STAR_FRAME_XMODEL_HPP_
#include <com/sun/star/frame/XModel.hpp>
#endif
#ifndef DBAUI_SBATTRDLG_HRC
#include "dlgattr.hrc"
#endif
#ifndef DBAUI_TYPEINFO_HXX
#include "TypeInfo.hxx"
#endif
#ifndef DBAUI_FIELDDESCRIPTIONS_HXX
#include "FieldDescriptions.hxx"
#endif
#ifndef _COMPHELPER_STLTYPES_HXX_
#include <comphelper/stl_types.hxx>
#endif
#ifndef COMPHELPER_COMPONENTCONTEXT_HXX
#include <comphelper/componentcontext.hxx>
#endif

#ifndef _SVX_SVXIDS_HRC
#include <svx/svxids.hrc>
#endif

#define ITEMID_HORJUSTIFY		SID_ATTR_ALIGN_HOR_JUSTIFY
#define ITEMID_VERJUSTIFY		SID_ATTR_ALIGN_VER_JUSTIFY
//#define ITEMID_ORIENTATION     SID_ATTR_ALIGN_ORIENTATION
#define ITEMID_LINEBREAK		SID_ATTR_ALIGN_LINEBREAK
#define ITEMID_MARGIN			SID_ATTR_ALIGN_MARGIN
#define ITEMID_NUMBERINFO		SID_ATTR_NUMBERFORMAT_INFO

#ifndef _SFXITEMPOOL_HXX
#include <svtools/itempool.hxx>
#endif
#ifndef _STRING_HXX
#include <tools/string.hxx>
#endif
#ifndef _DBA_DBACCESS_HELPID_HRC_
#include "dbaccess_helpid.hrc"
#endif
#ifndef _SFXITEMSET_HXX //autogen wg. SfxItemSet
#include <svtools/itemset.hxx>
#endif
#ifndef DBACCESS_SBA_GRID_HRC
#include "sbagrid.hrc"
#endif
#ifndef _SFXRNGITEM_HXX
#include <svtools/rngitem.hxx>
#endif
#ifndef _SFXINTITEM_HXX
#include <svtools/intitem.hxx>
#endif
#ifndef _SVX_ALGITEM_HXX
#include <svx/algitem.hxx>
#endif
#ifndef _SVX_NUMINF_HXX
#include <svx/numinf.hxx>
#endif
#define _ZFORLIST_DECLARE_TABLE
#ifndef _SVX_NUMINF_HXX
#include <svx/numinf.hxx>
#endif
#ifndef _ZFORLIST_HXX
#include <svtools/zforlist.hxx>
#endif
#ifndef DBAUI_SBATTRDLG_HXX
#include "dlgattr.hxx"
#endif
#ifndef _SV_MSGBOX_HXX
#include <vcl/msgbox.hxx>
#endif
#ifndef _COM_SUN_STAR_CONTAINER_XCHILD_HPP_
#include <com/sun/star/container/XChild.hpp>
#endif
#ifndef _COM_SUN_STAR_UTIL_XNUMBERFORMATSSUPPLIER_HPP_
#include <com/sun/star/util/XNumberFormatsSupplier.hpp>
#endif
#ifndef _COM_SUN_STAR_UTIL_XNUMBERFORMATTER_HPP_
#include <com/sun/star/util/XNumberFormatter.hpp>
#endif
#ifndef _DBU_MISC_HRC_
#include "dbu_misc.hrc"
#endif
#ifndef _DBAUI_SQLMESSAGE_HXX_
#include "sqlmessage.hxx"
#endif
#ifndef _COM_SUN_STAR_UTIL_NUMBERFORMAT_HPP_
#include <com/sun/star/util/NumberFormat.hpp>
#endif
#ifndef _COM_SUN_STAR_UTIL_URL_HPP_
#include <com/sun/star/util/URL.hpp>
#endif
#ifndef _SV_TOOLBOX_HXX
#include <vcl/toolbox.hxx>
#endif
#ifndef _DBAUI_DLGSIZE_HXX
#include "dlgsize.hxx"
#endif
#ifndef _SVTOOLS_EDITBROWSEBOX_HXX_
#include <svtools/editbrowsebox.hxx>
#endif
#ifndef _UTL_CONFIGMGR_HXX_
#include <unotools/configmgr.hxx>
#endif
#ifndef INCLUDED_SVTOOLS_HELPOPT_HXX
#include <svtools/helpopt.hxx>
#endif
#ifndef _UCBHELPER_CONTENT_HXX
#include <ucbhelper/content.hxx>
#endif
#ifndef _URLOBJ_HXX
#include <tools/urlobj.hxx>
#endif
#ifndef TOOLS_DIAGNOSE_EX_H
#include <tools/diagnose_ex.h>
#endif
#ifndef _NUMUNO_HXX
#include <svtools/numuno.hxx>
#endif
#ifndef INCLUDED_SVTOOLS_PATHOPTIONS_HXX
#include <svtools/pathoptions.hxx>
#endif
#ifndef SVTOOLS_FILENOTATION_HXX_
#include <svtools/filenotation.hxx>
#endif
#ifndef _SVT_FILEVIEW_HXX
#include <svtools/fileview.hxx>
#endif
#ifndef _CONNECTIVITY_FILE_VALUE_HXX_
#include <connectivity/FValue.hxx>
#endif

// .........................................................................
namespace dbaui
{
// .........................................................................
using namespace ::dbtools;
using namespace ::comphelper;
using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::task;
using namespace ::com::sun::star::sdbcx;
using namespace ::com::sun::star::sdbc;
using namespace ::com::sun::star::sdb;
using namespace ::com::sun::star::util;
using namespace ::com::sun::star::ucb;
using namespace ::com::sun::star::beans;
using namespace ::com::sun::star::container;
using namespace ::com::sun::star::lang;
using namespace ::com::sun::star::ui::dialogs;
using namespace ::svt;
using ::com::sun::star::ucb::InteractiveIOException;
using ::com::sun::star::ucb::IOErrorCode_NO_FILE;
using ::com::sun::star::ucb::IOErrorCode_NOT_EXISTING;
using ::com::sun::star::frame::XModel;

// -----------------------------------------------------------------------------
SQLExceptionInfo createConnection(	const ::rtl::OUString& _rsDataSourceName,
                                     const Reference< ::com::sun::star::container::XNameAccess >& _xDatabaseContext,
                                    const Reference< ::com::sun::star::lang::XMultiServiceFactory >& _rMF,
                                    Reference< ::com::sun::star::lang::XEventListener>& _rEvtLst,
                                    Reference< ::com::sun::star::sdbc::XConnection>& _rOUTConnection )
{
    Reference<XPropertySet> xProp;
    try
    {
        xProp.set(_xDatabaseContext->getByName(_rsDataSourceName),UNO_QUERY);
    }
    catch(Exception&)
    {
    }
    SQLExceptionInfo aInfo;

    return createConnection(xProp,_rMF,_rEvtLst,_rOUTConnection);
}
// -----------------------------------------------------------------------------
SQLExceptionInfo createConnection(	const Reference< ::com::sun::star::beans::XPropertySet>& _xDataSource,
                                    const Reference< ::com::sun::star::lang::XMultiServiceFactory >& _rMF,
                                    Reference< ::com::sun::star::lang::XEventListener>& _rEvtLst,
                                    Reference< ::com::sun::star::sdbc::XConnection>& _rOUTConnection )
{
    SQLExceptionInfo aInfo;
    if ( !_xDataSource.is() )
    {
        OSL_ENSURE(0,"createConnection: coult not retrieve the data source!");
        return aInfo;
    }

    ::rtl::OUString sPwd, sUser;
    sal_Bool bPwdReq = sal_False;
    try
    {
        _xDataSource->getPropertyValue(PROPERTY_PASSWORD) >>= sPwd;
        bPwdReq = ::cppu::any2bool(_xDataSource->getPropertyValue(PROPERTY_ISPASSWORDREQUIRED));
        _xDataSource->getPropertyValue(PROPERTY_USER) >>= sUser;
    }
    catch(Exception&)
    {
        OSL_ENSURE(0,"createConnection: error while retrieving data source properties!");
    }


    try
    {
        if(bPwdReq && !sPwd.getLength())
        {	// password required, but empty -> connect using an interaction handler
            Reference<XCompletedConnection> xConnectionCompletion(_xDataSource, UNO_QUERY);
            if (!xConnectionCompletion.is())
            {
                OSL_ENSURE(0,"createConnection: missing an interface ... need an error message here!");
            }
            else
            {	// instantiate the default SDB interaction handler
                Reference< XInteractionHandler > xHandler(_rMF->createInstance(SERVICE_SDB_INTERACTION_HANDLER), UNO_QUERY);
                if (!xHandler.is())
                {
                    OSL_ENSURE(sal_False, "createConnection: could not instantiate an interaction handler!");
                    // ShowServiceNotAvailableError(NULL, String(SERVICE_SDB_INTERACTION_HANDLER), sal_True);
                        // TODO: a real parent!
                }
                else
                    _rOUTConnection = xConnectionCompletion->connectWithCompletion(xHandler);
            }
        }
        else
        {
            Reference<XDataSource> xDataSource(_xDataSource,UNO_QUERY);
            _rOUTConnection = xDataSource->getConnection(sUser, sPwd);
        }
        // be notified when connection is in disposing
        Reference< XComponent >  xComponent(_rOUTConnection, UNO_QUERY);
        if (xComponent.is() && _rEvtLst.is())
            xComponent->addEventListener(_rEvtLst);
    }
    catch(SQLContext& e) { aInfo = SQLExceptionInfo(e); }
    catch(SQLWarning& e) { aInfo = SQLExceptionInfo(e); }
    catch(SQLException& e) { aInfo = SQLExceptionInfo(e); }
    catch(Exception&) { OSL_ENSURE(0,"SbaTableQueryBrowser::OnExpandEntry: could not connect - unknown exception!"); }

    //	showError(aInfo);

    return aInfo;
}
// -----------------------------------------------------------------------------
Reference< XDataSource > getDataSourceByName( const ::rtl::OUString& _rDataSourceName,
    Window* _pErrorMessageParent, Reference< XMultiServiceFactory > _rxORB, ::dbtools::SQLExceptionInfo* _pErrorInfo )
{
    ::comphelper::ComponentContext aContext( _rxORB );
    Reference< XNameAccess > xDatabaseContext( aContext.createComponent( "com.sun.star.sdb.DatabaseContext" ), UNO_QUERY_THROW );

    Reference< XDataSource > xDatasource;
    Any aError;
    SQLExceptionInfo aSQLError;
    try
    {
        xDatabaseContext->getByName( _rDataSourceName ) >>= xDatasource;
    }
    catch(const WrappedTargetException& e)
    {
        InteractiveIOException aIOException;
        if  (   ( e.TargetException >>= aIOException )
            &&  (   ( aIOException.Code == IOErrorCode_NO_FILE )
                ||  ( aIOException.Code == IOErrorCode_NOT_EXISTING )
                )
            )
        {
            String sErrorMessage = String( ModuleRes( STR_FILE_DOES_NOT_EXIST ) );
            OFileNotation aTransformer( e.Message );
            sErrorMessage.SearchAndReplaceAscii( "$file$", aTransformer.get( OFileNotation::N_SYSTEM ) );
            aSQLError = SQLExceptionInfo( sErrorMessage ).get();
        }
        else
        {
            aSQLError = SQLExceptionInfo( e.TargetException );
            if ( !aSQLError.isValid() )
                aError = e.TargetException;
        }
    }
    catch( const Exception& )
    {
        DBG_UNHANDLED_EXCEPTION();
    }

    if ( xDatasource.is() )
        return xDatasource;

    if ( aSQLError.isValid() )
    {
        if ( _pErrorInfo )
        {
            *_pErrorInfo = aSQLError;
        }
        else
        {
            showError( aSQLError, _pErrorMessageParent, _rxORB );
        }
    }

    return Reference<XDataSource>();
}
// -----------------------------------------------------------------------------
Reference< XInterface > getDataSourceOrModel(const Reference< XInterface >& _xObject)
{
    Reference< XInterface > xRet;
    Reference<XDocumentDataSource> xDocumentDataSource(_xObject,UNO_QUERY);
    if ( xDocumentDataSource.is() )
        xRet = xDocumentDataSource->getDatabaseDocument();

    if ( !xRet.is() )
    {
        Reference<XOfficeDatabaseDocument> xOfficeDoc(_xObject,UNO_QUERY);
        if ( xOfficeDoc.is() )
            xRet = xOfficeDoc->getDataSource();
    }

    return xRet;
}
// -----------------------------------------------------------------------------
void showError(const SQLExceptionInfo& _rInfo,Window* _pParent,const Reference< XMultiServiceFactory >& _xFactory)
{
    OSL_ENSURE(_pParent,"showError: Parent window must be NOT NULL!");
    ::dbtools::showError(_rInfo,VCLUnoHelper::GetInterface(_pParent),_xFactory);
}

// -----------------------------------------------------------------------------
::std::vector< Reference<XNameAccess> > getKeyColumns(const Reference<XIndexAccess >& _rxKeys,
                                                      sal_Int32 _nKeyType)
{
    // use keys and indexes for excat postioning
    // first the keys
    ::std::vector< Reference<XNameAccess> > vRet;
    if(_rxKeys.is())
    {
        Reference<XPropertySet> xProp;
        for(sal_Int32 i=0;i< _rxKeys->getCount();++i)
        {
            _rxKeys->getByIndex(i) >>= xProp;
            sal_Int32 nKeyType = 0;
            xProp->getPropertyValue(PROPERTY_TYPE) >>= nKeyType;
            if(_nKeyType == nKeyType)
            {
                Reference<XColumnsSupplier> xKeyColsSup(xProp,UNO_QUERY);
                OSL_ENSURE(xKeyColsSup.is(),"Columnsupplier is null!");
                vRet.push_back(xKeyColsSup->getColumns());
            }
        }
    }

    return vRet;
}
// -----------------------------------------------------------------------------

TOTypeInfoSP getTypeInfoFromType(const OTypeInfoMap& _rTypeInfo,
                               sal_Int32 _nType,
                               const ::rtl::OUString& _sTypeName,
                               const ::rtl::OUString& _sCreateParams,
                               sal_Int32 _nPrecision,
                               sal_Int32 _nScale,
                               sal_Bool _bAutoIncrement,
                               sal_Bool& _brForceToType)
{
    TOTypeInfoSP pTypeInfo;
    _brForceToType = sal_False;
    // search for type
    ::std::pair<OTypeInfoMap::const_iterator, OTypeInfoMap::const_iterator> aPair = _rTypeInfo.equal_range(_nType);
    OTypeInfoMap::const_iterator aIter = aPair.first;
    if(aIter != _rTypeInfo.end()) // compare with end is correct here
    {
        for(;aIter != aPair.second;++aIter)
        {
            // search the best matching type
    #ifdef DBG_UTIL
            ::rtl::OUString sDBTypeName			= aIter->second->aTypeName;         (void)sDBTypeName;
            sal_Int32		nDBTypePrecision	= aIter->second->nPrecision;        (void)nDBTypePrecision;
            sal_Int32		nDBTypeScale		= aIter->second->nMaximumScale;     (void)nDBTypeScale;
            sal_Bool		bDBAutoIncrement	= aIter->second->bAutoIncrement;    (void)bDBAutoIncrement;
    #endif
            if	(	(
                        !_sTypeName.getLength()
                    ||	(aIter->second->aTypeName.equalsIgnoreAsciiCase(_sTypeName))
                    )
                &&	(
                        (
                                !aIter->second->aCreateParams.getLength()
                            &&	!_sCreateParams.getLength()
                        )
                    ||	(
                                (aIter->second->nPrecision		>= _nPrecision)
                            &&	(aIter->second->nMaximumScale	>= _nScale)
                            &&	( (_bAutoIncrement && aIter->second->bAutoIncrement) || !_bAutoIncrement )
                        )
                    )
                )
                break;
        }

        if (aIter == aPair.second)
        {
            for(aIter = aPair.first; aIter != aPair.second; ++aIter)
            {
                sal_Int32 nPrec = aIter->second->nPrecision;
                sal_Int32 nScale = aIter->second->nMaximumScale;
                // search the best matching type (now comparing the local names)
                if	(	(aIter->second->aLocalTypeName.equalsIgnoreAsciiCase(_sTypeName))
                    &&	(nPrec	>= _nPrecision)
                    &&	(nScale	>= _nScale)
                    &&	( (_bAutoIncrement && aIter->second->bAutoIncrement) || !_bAutoIncrement )
                    )
                {
                    OSL_ENSURE(sal_False,
                        (	::rtl::OString("getTypeInfoFromType: assuming column type ")
                        +=	::rtl::OString(aIter->second->aTypeName.getStr(), aIter->second->aTypeName.getLength(), gsl_getSystemTextEncoding())
                        +=	::rtl::OString("\" (expected type name ")
                        +=	::rtl::OString(_sTypeName.getStr(), _sTypeName.getLength(), gsl_getSystemTextEncoding())
                        +=	::rtl::OString(" matches the type's local name).")).getStr());
                    break;
                }
            }
        }

        if (aIter == aPair.second)
        {	// no match for the names, no match for the local names
            // -> drop the precision and the scale restriction, accept any type with the property
            // type id (nType)

            //OSL_ENSURE(sal_False,
            //	(	::rtl::OString("getTypeInfoFromType: did not find a matching type")
            //	+=	::rtl::OString(" (expected type name: ")
            //	+=	::rtl::OString(_sTypeName.getStr(), _sTypeName.getLength(), gsl_getSystemTextEncoding())
            //	+=	::rtl::OString(")! Defaulting to the first matching type.")).getStr());
            for(aIter = aPair.first; aIter != aPair.second; ++aIter)
            {
                // search the best matching type (now comparing the local names)
#ifdef DBG_UTIL
                ::rtl::OUString sDBTypeName = aIter->second->aTypeName;
#endif
                sal_Int32 nPrec = aIter->second->nPrecision;
                sal_Int32 nScale = aIter->second->nMaximumScale;
                if	(	(nPrec	>= _nPrecision)
                    &&	(nScale	>= _nScale)
                    &&	( (_bAutoIncrement && aIter->second->bAutoIncrement) || !_bAutoIncrement )
                    )
                    break;
            }
        }
        if (aIter == aPair.second)
        {
            if ( _bAutoIncrement )
            {
                for(aIter = aPair.first; aIter != aPair.second; ++aIter)
                {
                    // search the best matching type (now comparing the local names)
#ifdef DBG_UTIL
                    ::rtl::OUString sDBTypeName = aIter->second->aTypeName;
#endif
                    sal_Int32 nScale = aIter->second->nMaximumScale;
                    if	(	(nScale	>= _nScale)
                        &&	(aIter->second->bAutoIncrement	== _bAutoIncrement)
                        )
                        break;
                }
                if ( aIter == aPair.second )
                {
                    // try it without the auto increment flag
                    pTypeInfo = getTypeInfoFromType(_rTypeInfo,
                                   _nType,
                                   _sTypeName,
                                   _sCreateParams,
                                   _nPrecision,
                                   _nScale,
                                   sal_False,
                                   _brForceToType);
                }
                else
                    pTypeInfo = aIter->second;
            }
            else
            {
                pTypeInfo = aPair.first->second;
                _brForceToType = sal_True;
            }
        }
        else
            pTypeInfo = aIter->second;
    }
    else
    {
        ::comphelper::TStringMixEqualFunctor aCase(sal_False);
        // search for typeinfo where the typename is equal _sTypeName
        OTypeInfoMap::const_iterator typeInfoLoop = _rTypeInfo.begin();
        OTypeInfoMap::const_iterator typeInfoEnd  = _rTypeInfo.end();
        for (; typeInfoLoop != typeInfoEnd; ++typeInfoLoop)
        {
            if ( aCase( typeInfoLoop->second->getDBName() , _sTypeName ) )
            {
                pTypeInfo = typeInfoLoop->second;
                break;
            }
        }
    }

    OSL_ENSURE(pTypeInfo, "getTypeInfoFromType: no type info found for this type!");
    return pTypeInfo;
}
// -----------------------------------------------------------------------------
void fillTypeInfo(	const Reference< ::com::sun::star::sdbc::XConnection>& _rxConnection,
                    const String& _rsTypeNames,
                    OTypeInfoMap& _rTypeInfoMap,
                    ::std::vector<OTypeInfoMap::iterator>& _rTypeInfoIters)
{
    if(!_rxConnection.is())
        return;
    Reference< XResultSet> xRs = _rxConnection->getMetaData ()->getTypeInfo ();
    Reference< XRow> xRow(xRs,UNO_QUERY);
    // Information for a single SQL type
    if(xRs.is())
    {
        static const ::rtl::OUString aB1 = ::rtl::OUString::createFromAscii(" [ ");
        static const ::rtl::OUString aB2 = ::rtl::OUString::createFromAscii(" ]");
        Reference<XResultSetMetaData> xResultSetMetaData = Reference<XResultSetMetaDataSupplier>(xRs,UNO_QUERY)->getMetaData();
        ::connectivity::ORowSetValue aValue;
        ::std::vector<sal_Int32> aTypes;
        ::std::vector<sal_Bool> aNullable;
        // Loop on the result set until we reach end of file
        while (xRs->next())
        {
            TOTypeInfoSP pInfo(new OTypeInfo());
            sal_Int32 nPos = 1;
            if ( aTypes.empty() )
            {
                sal_Int32 nCount = xResultSetMetaData->getColumnCount();
                if ( nCount < 1 )
                    nCount = 18;
                aTypes.reserve(nCount+1);
                aTypes.push_back(-1);
                aNullable.push_back(sal_False);
                for (sal_Int32 j = 1; j <= nCount ; ++j)
                {
                    aTypes.push_back(xResultSetMetaData->getColumnType(j));
                    aNullable.push_back(xResultSetMetaData->isNullable(j) != ColumnValue::NO_NULLS);
                }
            }

            aValue.fill(nPos,aTypes[nPos],aNullable[nPos],xRow);
            pInfo->aTypeName		= aValue;
            ++nPos;
            aValue.fill(nPos,aTypes[nPos],aNullable[nPos],xRow);
            pInfo->nType			= aValue;
            ++nPos;
            aValue.fill(nPos,aTypes[nPos],aNullable[nPos],xRow);
            pInfo->nPrecision		= aValue;
            ++nPos;
            aValue.fill(nPos,aTypes[nPos],aNullable[nPos],xRow);
            pInfo->aLiteralPrefix	= aValue;
            ++nPos;
            aValue.fill(nPos,aTypes[nPos],aNullable[nPos],xRow);
            pInfo->aLiteralSuffix	= aValue;
            ++nPos;
            aValue.fill(nPos,aTypes[nPos],aNullable[nPos],xRow);
            pInfo->aCreateParams	= aValue;
            ++nPos;
            aValue.fill(nPos,aTypes[nPos],aNullable[nPos],xRow);
            pInfo->bNullable		= (sal_Int32)aValue == ColumnValue::NULLABLE;
            ++nPos;
            aValue.fill(nPos,aTypes[nPos],aNullable[nPos],xRow);
            pInfo->bCaseSensitive	= (sal_Bool)aValue;
            ++nPos;
            aValue.fill(nPos,aTypes[nPos],aNullable[nPos],xRow);
            pInfo->nSearchType		= aValue;
            ++nPos;
            aValue.fill(nPos,aTypes[nPos],aNullable[nPos],xRow);
            pInfo->bUnsigned		= (sal_Bool)aValue;
            ++nPos;
            aValue.fill(nPos,aTypes[nPos],aNullable[nPos],xRow);
            pInfo->bCurrency		= (sal_Bool)aValue;
            ++nPos;
            aValue.fill(nPos,aTypes[nPos],aNullable[nPos],xRow);
            pInfo->bAutoIncrement	= (sal_Bool)aValue;
            ++nPos;
            aValue.fill(nPos,aTypes[nPos],aNullable[nPos],xRow);
            pInfo->aLocalTypeName	= aValue;
            ++nPos;
            aValue.fill(nPos,aTypes[nPos],aNullable[nPos],xRow);
            pInfo->nMinimumScale	= aValue;
            ++nPos;
            aValue.fill(nPos,aTypes[nPos],aNullable[nPos],xRow);
            pInfo->nMaximumScale	= aValue;
            nPos = 18;
            aValue.fill(nPos,aTypes[nPos],aNullable[nPos],xRow);

            // check if values are less than zero like it happens in a oracle jdbc driver
            if( pInfo->nPrecision < 0)
                pInfo->nPrecision = 0;
            if( pInfo->nMinimumScale < 0)
                pInfo->nMinimumScale = 0;
            if( pInfo->nMaximumScale < 0)
                pInfo->nMaximumScale = 0;

            String aName;
            switch(pInfo->nType)
            {
                case DataType::CHAR:
                    aName = _rsTypeNames.GetToken(TYPE_CHAR);
                    break;
                case DataType::VARCHAR:
                    aName = _rsTypeNames.GetToken(TYPE_TEXT);
                    break;
                case DataType::DECIMAL:
                    aName = _rsTypeNames.GetToken(TYPE_DECIMAL);
                    break;
                case DataType::NUMERIC:
                    aName = _rsTypeNames.GetToken(TYPE_NUMERIC);
                    break;
                case DataType::BIGINT:
                    aName = _rsTypeNames.GetToken(TYPE_BIGINT);
                    break;
                case DataType::FLOAT:
                    aName = _rsTypeNames.GetToken(TYPE_FLOAT);
                    break;
                case DataType::DOUBLE:
                    aName = _rsTypeNames.GetToken(TYPE_DOUBLE);
                    break;
                case DataType::LONGVARCHAR:
                    aName = _rsTypeNames.GetToken(TYPE_MEMO);
                    break;
                case DataType::LONGVARBINARY:
                    aName = _rsTypeNames.GetToken(TYPE_IMAGE);
                    break;
                case DataType::DATE:
                    aName = _rsTypeNames.GetToken(TYPE_DATE);
                    break;
                case DataType::TIME:
                    aName = _rsTypeNames.GetToken(TYPE_TIME);
                    break;
                case DataType::TIMESTAMP:
                    aName = _rsTypeNames.GetToken(TYPE_DATETIME);
                    break;
                case DataType::BIT:
                case DataType::BOOLEAN:
                    aName = _rsTypeNames.GetToken(TYPE_BOOL);
                    break;
                case DataType::TINYINT:
                    aName = _rsTypeNames.GetToken(TYPE_TINYINT);
                    break;
                case DataType::SMALLINT:
                    aName = _rsTypeNames.GetToken(TYPE_SMALLINT);
                    break;
                case DataType::INTEGER:
                    aName = _rsTypeNames.GetToken(TYPE_INTEGER);
                    break;
                case DataType::REAL:
                    aName = _rsTypeNames.GetToken(TYPE_REAL);
                    break;
                case DataType::BINARY:
                    aName = _rsTypeNames.GetToken(TYPE_BINARY);
                    break;
                case DataType::VARBINARY:
                    aName = _rsTypeNames.GetToken(TYPE_VARBINARY);
                    break;
                case DataType::SQLNULL:
                    aName = _rsTypeNames.GetToken(TYPE_SQLNULL);
                    break;
                case DataType::OBJECT:
                    aName = _rsTypeNames.GetToken(TYPE_OBJECT);
                    break;
                case DataType::DISTINCT:
                    aName = _rsTypeNames.GetToken(TYPE_DISTINCT);
                    break;
                case DataType::STRUCT:
                    aName = _rsTypeNames.GetToken(TYPE_STRUCT);
                    break;
                case DataType::ARRAY:
                    aName = _rsTypeNames.GetToken(TYPE_ARRAY);
                    break;
                case DataType::BLOB:
                    aName = _rsTypeNames.GetToken(TYPE_BLOB);
                    break;
                case DataType::CLOB:
                    aName = _rsTypeNames.GetToken(TYPE_CLOB);
                    break;
                case DataType::REF:
                    aName = _rsTypeNames.GetToken(TYPE_REF);
                    break;
                case DataType::OTHER:
                    aName = _rsTypeNames.GetToken(TYPE_OTHER);
                    break;
            }
            if ( aName.Len() )
            {
                pInfo->aUIName = aName.GetBuffer();
                pInfo->aUIName += aB1;
            }
            pInfo->aUIName += pInfo->aTypeName;
            if ( aName.Len() )
                pInfo->aUIName += aB2;
            // Now that we have the type info, save it in the multimap
            _rTypeInfoMap.insert(OTypeInfoMap::value_type(pInfo->nType,pInfo));
        }
        // for a faster index access
        _rTypeInfoIters.reserve(_rTypeInfoMap.size());

        OTypeInfoMap::iterator aIter = _rTypeInfoMap.begin();
        OTypeInfoMap::iterator aEnd = _rTypeInfoMap.end();
        for(;aIter != aEnd;++aIter)
            _rTypeInfoIters.push_back(aIter);

        // Close the result set/statement.

        ::comphelper::disposeComponent(xRs);
    }
}
// -----------------------------------------------------------------------------
void setColumnProperties(const Reference<XPropertySet>& _rxColumn,const OFieldDescription* _pFieldDesc)
{
    _rxColumn->setPropertyValue(PROPERTY_NAME,makeAny(_pFieldDesc->GetName()));
    _rxColumn->setPropertyValue(PROPERTY_TYPENAME,makeAny(_pFieldDesc->getTypeInfo()->aTypeName));
    _rxColumn->setPropertyValue(PROPERTY_TYPE,makeAny(_pFieldDesc->GetType()));
    _rxColumn->setPropertyValue(PROPERTY_PRECISION,makeAny(_pFieldDesc->GetPrecision()));
    _rxColumn->setPropertyValue(PROPERTY_SCALE,makeAny(_pFieldDesc->GetScale()));
    _rxColumn->setPropertyValue(PROPERTY_ISNULLABLE, makeAny(_pFieldDesc->GetIsNullable()));
    _rxColumn->setPropertyValue(PROPERTY_ISAUTOINCREMENT,::cppu::bool2any(_pFieldDesc->IsAutoIncrement()));
    if ( _rxColumn->getPropertySetInfo()->hasPropertyByName(PROPERTY_ISCURRENCY) && _pFieldDesc->IsCurrency() )
        _rxColumn->setPropertyValue(PROPERTY_ISCURRENCY,::cppu::bool2any(_pFieldDesc->IsCurrency()));
    // set autoincrement value when available
    // and only set when the entry is not empty, that lets the value in the column untouched
    if ( _pFieldDesc->IsAutoIncrement() && _pFieldDesc->GetAutoIncrementValue().getLength() && _rxColumn->getPropertySetInfo()->hasPropertyByName(PROPERTY_AUTOINCREMENTCREATION) )
        _rxColumn->setPropertyValue(PROPERTY_AUTOINCREMENTCREATION,makeAny(_pFieldDesc->GetAutoIncrementValue()));
}
// -----------------------------------------------------------------------------
::rtl::OUString createDefaultName(const Reference< XDatabaseMetaData>& _xMetaData,const Reference<XNameAccess>& _xTables,const ::rtl::OUString& _sName)
{
    OSL_ENSURE(_xMetaData.is(),"No MetaData!");
    ::rtl::OUString sDefaultName = _sName;
    try
    {
        ::rtl::OUString sCatalog,sSchema,sCompsedName;
        if(_xMetaData->supportsCatalogsInTableDefinitions())
        {
            try
            {
                Reference< XConnection> xCon = _xMetaData->getConnection();
                if ( xCon.is() )
                    sCatalog = xCon->getCatalog();
                if ( !sCatalog.getLength() )
                {
                    Reference<XResultSet> xRes = _xMetaData->getCatalogs();
                    Reference<XRow> xRow(xRes,UNO_QUERY);
                    while(xRes.is() && xRes->next())
                    {
                        sCatalog = xRow->getString(1);
                        if(!xRow->wasNull())
                            break;
                    }
                }
            }
            catch(const SQLException&)
            {
            }
        }
        if(_xMetaData->supportsSchemasInTableDefinitions())
        {
            sSchema = _xMetaData->getUserName();
        }
        sCompsedName = ::dbtools::composeTableName( _xMetaData, sCatalog, sSchema, _sName, sal_False, ::dbtools::eInDataManipulation );
        sDefaultName = ::dbtools::createUniqueName(_xTables,sCompsedName);
    }
    catch(const SQLException&)
    {
    }
    return sDefaultName;
}
// -----------------------------------------------------------------------------
sal_Bool checkDataSourceAvailable(const ::rtl::OUString& _sDataSourceName,const Reference< ::com::sun::star::lang::XMultiServiceFactory >& _xORB)
{
    sal_Bool bRet = sal_False;
    Reference< XNameAccess > xDataBaseContext(_xORB->createInstance(SERVICE_SDB_DATABASECONTEXT), UNO_QUERY);
    if ( xDataBaseContext.is() )
    {
        bRet = xDataBaseContext->hasByName(_sDataSourceName);
        if ( !bRet )
        { // try if this one is a URL
            try
            {
                bRet = xDataBaseContext->getByName(_sDataSourceName).hasValue();
            }
            catch(Exception)
            {
            }
        }
    }
    return bRet;
}
// -----------------------------------------------------------------------------
sal_Int32 mapTextAllign(const SvxCellHorJustify& _eAlignment)
{
    sal_Int32 nAlignment = com::sun::star::awt::TextAlign::LEFT;
    switch (_eAlignment)
    {
        case SVX_HOR_JUSTIFY_STANDARD:
        case SVX_HOR_JUSTIFY_LEFT:		nAlignment = ::com::sun::star::awt::TextAlign::LEFT;	break;
        case SVX_HOR_JUSTIFY_CENTER:	nAlignment = ::com::sun::star::awt::TextAlign::CENTER;	break;
        case SVX_HOR_JUSTIFY_RIGHT:		nAlignment = ::com::sun::star::awt::TextAlign::RIGHT;	break;
        default:
            OSL_ENSURE(0,"Invalid TextAlign!");
    }
    return nAlignment;
}
// -----------------------------------------------------------------------------
SvxCellHorJustify mapTextJustify(const sal_Int32& _nAlignment)
{
    SvxCellHorJustify eJustify = SVX_HOR_JUSTIFY_LEFT;
    switch (_nAlignment)
    {
        case ::com::sun::star::awt::TextAlign::LEFT		: eJustify = SVX_HOR_JUSTIFY_LEFT; break;
        case ::com::sun::star::awt::TextAlign::CENTER	: eJustify = SVX_HOR_JUSTIFY_CENTER; break;
        case ::com::sun::star::awt::TextAlign::RIGHT	: eJustify = SVX_HOR_JUSTIFY_RIGHT; break;
        default:
            OSL_ENSURE(0,"Invalid TextAlign!");
    }
    return eJustify;
}
// -----------------------------------------------------------------------------
float ConvertFontWeight( ::FontWeight eWeight )
{
    if( eWeight == WEIGHT_DONTKNOW )
        return ::com::sun::star::awt::FontWeight::DONTKNOW;
    else if( eWeight == WEIGHT_THIN )
        return ::com::sun::star::awt::FontWeight::THIN;
    else if( eWeight == WEIGHT_ULTRALIGHT )
        return ::com::sun::star::awt::FontWeight::ULTRALIGHT;
    else if( eWeight == WEIGHT_LIGHT )
        return ::com::sun::star::awt::FontWeight::LIGHT;
    else if( eWeight == WEIGHT_SEMILIGHT )
        return ::com::sun::star::awt::FontWeight::SEMILIGHT;
    else if( ( eWeight == WEIGHT_NORMAL ) || ( eWeight == WEIGHT_MEDIUM ) )
        return ::com::sun::star::awt::FontWeight::NORMAL;
    else if( eWeight == WEIGHT_SEMIBOLD )
        return ::com::sun::star::awt::FontWeight::SEMIBOLD;
    else if( eWeight == WEIGHT_BOLD )
        return ::com::sun::star::awt::FontWeight::BOLD;
    else if( eWeight == WEIGHT_ULTRABOLD )
        return ::com::sun::star::awt::FontWeight::ULTRABOLD;
    else if( eWeight == WEIGHT_BLACK )
        return ::com::sun::star::awt::FontWeight::BLACK;

    OSL_ENSURE(0, "Unknown FontWeigth" );
    return ::com::sun::star::awt::FontWeight::DONTKNOW;
}
// -----------------------------------------------------------------------------
float ConvertFontWidth( ::FontWidth eWidth )
{
    if( eWidth == WIDTH_DONTKNOW )
        return ::com::sun::star::awt::FontWidth::DONTKNOW;
    else if( eWidth == WIDTH_ULTRA_CONDENSED )
        return ::com::sun::star::awt::FontWidth::ULTRACONDENSED;
    else if( eWidth == WIDTH_EXTRA_CONDENSED )
        return ::com::sun::star::awt::FontWidth::EXTRACONDENSED;
    else if( eWidth == WIDTH_CONDENSED )
        return ::com::sun::star::awt::FontWidth::CONDENSED;
    else if( eWidth == WIDTH_SEMI_CONDENSED )
        return ::com::sun::star::awt::FontWidth::SEMICONDENSED;
    else if( eWidth == WIDTH_NORMAL )
        return ::com::sun::star::awt::FontWidth::NORMAL;
    else if( eWidth == WIDTH_SEMI_EXPANDED )
        return ::com::sun::star::awt::FontWidth::SEMIEXPANDED;
    else if( eWidth == WIDTH_EXPANDED )
        return ::com::sun::star::awt::FontWidth::EXPANDED;
    else if( eWidth == WIDTH_EXTRA_EXPANDED )
        return ::com::sun::star::awt::FontWidth::EXTRAEXPANDED;
    else if( eWidth == WIDTH_ULTRA_EXPANDED )
        return ::com::sun::star::awt::FontWidth::ULTRAEXPANDED;

    OSL_ENSURE(0, "Unknown FontWidth" );
    return ::com::sun::star::awt::FontWidth::DONTKNOW;
}
// -----------------------------------------------------------------------------
::com::sun::star::awt::FontDescriptor CreateFontDescriptor( const Font& rFont )
{
    ::com::sun::star::awt::FontDescriptor aFD;
    aFD.Name			= rFont.GetName();
    aFD.StyleName		= rFont.GetStyleName();
    aFD.Height			= (sal_Int16)rFont.GetSize().Height();
    aFD.Width			= (sal_Int16)rFont.GetSize().Width();
    aFD.Family			= sal::static_int_cast< sal_Int16 >(rFont.GetFamily());
    aFD.CharSet			= rFont.GetCharSet();
    aFD.Pitch			= sal::static_int_cast< sal_Int16 >(rFont.GetPitch());
    aFD.CharacterWidth	= ConvertFontWidth( rFont.GetWidthType() );
    aFD.Weight			= ConvertFontWeight( rFont.GetWeight() );
    aFD.Slant			= (::com::sun::star::awt::FontSlant)rFont.GetItalic();
    aFD.Underline		= sal::static_int_cast< sal_Int16 >(
        rFont.GetUnderline());
    aFD.Strikeout		= sal::static_int_cast< sal_Int16 >(
        rFont.GetStrikeout());
    aFD.Orientation		= rFont.GetOrientation();
    aFD.Kerning			= rFont.IsKerning();
    aFD.WordLineMode	= rFont.IsWordLineMode();
    aFD.Type			= 0;   // ??? => Nur an Metric...
    return aFD;
}
// -----------------------------------------------------------------------------
void callColumnFormatDialog(const Reference<XPropertySet>& xAffectedCol,
                            const Reference<XPropertySet>& xField,
                            SvNumberFormatter* _pFormatter,
                            Window* _pParent)
{
    if (xAffectedCol.is() && xField.is())
    {
        try
        {
            Reference< XPropertySetInfo >  xInfo = xAffectedCol->getPropertySetInfo();
            sal_Bool bHasFormat = xInfo->hasPropertyByName(PROPERTY_FORMATKEY);
            sal_Int32 nDataType = ::comphelper::getINT32(xField->getPropertyValue(PROPERTY_TYPE));

            SvxCellHorJustify eJustify(SVX_HOR_JUSTIFY_STANDARD);
            Any aAlignment = xAffectedCol->getPropertyValue(PROPERTY_ALIGN);
            if (aAlignment.hasValue())
                eJustify = dbaui::mapTextJustify(::comphelper::getINT16(aAlignment));
            sal_Int32  nFormatKey = 0;
            if ( bHasFormat )
                nFormatKey = ::comphelper::getINT32(xAffectedCol->getPropertyValue(PROPERTY_FORMATKEY));

            sal_uInt16 nFlags = 0;
            if(callColumnFormatDialog(_pParent,_pFormatter,nDataType,nFormatKey,eJustify,nFlags,bHasFormat))
            {
                xAffectedCol->setPropertyValue(PROPERTY_ALIGN, makeAny((sal_Int16)dbaui::mapTextAllign(eJustify)));
                if (nFlags & TP_ATTR_NUMBER)
                    xAffectedCol->setPropertyValue(PROPERTY_FORMATKEY, makeAny(nFormatKey));

            }
        }
        catch( const Exception& )
        {
            DBG_UNHANDLED_EXCEPTION();
        }
    }
}
// -----------------------------------------------------------------------------
sal_Bool callColumnFormatDialog(Window* _pParent,
                                SvNumberFormatter* _pFormatter,
                                sal_Int32 _nDataType,
                                sal_Int32& _nFormatKey,
                                SvxCellHorJustify& _eJustify,
                                sal_uInt16&	_nFlags,
                                sal_Bool  _bHasFormat)
{
    sal_Bool bRet = sal_False;
    // the allowed format changes depend of the type of the field ...
    _nFlags = TP_ATTR_ALIGN;

    if (_bHasFormat)
        _nFlags |= TP_ATTR_NUMBER;

    // ------------
    // UNO->ItemSet
    static SfxItemInfo aItemInfos[] =
    {
        { 0, 0 },
        { SID_ATTR_NUMBERFORMAT_VALUE,		SFX_ITEM_POOLABLE },
        { SID_ATTR_ALIGN_HOR_JUSTIFY,		SFX_ITEM_POOLABLE },
        { SID_ATTR_NUMBERFORMAT_ONE_AREA,	SFX_ITEM_POOLABLE },
        { SID_ATTR_NUMBERFORMAT_INFO,		SFX_ITEM_POOLABLE }
    };
    static sal_uInt16 aAttrMap[] =
    {
        SBA_DEF_RANGEFORMAT, SBA_ATTR_ALIGN_HOR_JUSTIFY,
        SID_ATTR_NUMBERFORMAT_ONE_AREA, SID_ATTR_NUMBERFORMAT_ONE_AREA,
        SID_ATTR_NUMBERFORMAT_INFO, SID_ATTR_NUMBERFORMAT_INFO,
        0
    };

    SfxPoolItem* pDefaults[] =
    {
        new SfxRangeItem(SBA_DEF_RANGEFORMAT, SBA_DEF_FMTVALUE, SBA_ATTR_ALIGN_HOR_JUSTIFY),
        new SfxUInt32Item(SBA_DEF_FMTVALUE),
        new SvxHorJustifyItem(SVX_HOR_JUSTIFY_STANDARD, SBA_ATTR_ALIGN_HOR_JUSTIFY),
        new SfxBoolItem(SID_ATTR_NUMBERFORMAT_ONE_AREA, sal_False),
        new SvxNumberInfoItem(SID_ATTR_NUMBERFORMAT_INFO)
    };

    SfxItemPool* pPool = new SfxItemPool(String::CreateFromAscii("GridBrowserProperties"), SBA_DEF_RANGEFORMAT, SBA_ATTR_ALIGN_HOR_JUSTIFY, aItemInfos, pDefaults);
    pPool->SetDefaultMetric( SFX_MAPUNIT_TWIP );	// ripped, don't understand why
    pPool->FreezeIdRanges();						// the same

    SfxItemSet* pFormatDescriptor = new SfxItemSet(*pPool, aAttrMap);
    // fill it
    pFormatDescriptor->Put(SvxHorJustifyItem(_eJustify, SBA_ATTR_ALIGN_HOR_JUSTIFY));
    sal_Bool bText = sal_False;
    if (_bHasFormat)
    {
        // if the col is bound to a text field we have to disallow all non-text formats
        if ((DataType::CHAR == _nDataType) || (DataType::VARCHAR == _nDataType) || (DataType::LONGVARCHAR == _nDataType))
        {
            bText = sal_True;
            pFormatDescriptor->Put(SfxBoolItem(SID_ATTR_NUMBERFORMAT_ONE_AREA, sal_True));
            if (!_pFormatter->IsTextFormat(_nFormatKey))
                // text fields can only have text formats
                _nFormatKey = _pFormatter->GetStandardFormat(NUMBERFORMAT_TEXT,_pParent->GetSettings().GetLanguage());
        }

        pFormatDescriptor->Put(SfxUInt32Item(SBA_DEF_FMTVALUE, _nFormatKey));
    }

    if (!bText)
    {
        double dPreviewVal = 1234.56789;
        SvxNumberInfoItem aFormatter(_pFormatter, dPreviewVal, SID_ATTR_NUMBERFORMAT_INFO);
        pFormatDescriptor->Put(aFormatter);
    }

    {	// want the dialog to be destroyed before our set
        SbaSbAttrDlg aDlg(_pParent, pFormatDescriptor, _pFormatter, _nFlags);
        if (RET_OK == aDlg.Execute())
        {
            // ------------
            // ItemSet->UNO
            // UNO-properties
            const SfxItemSet* pSet = aDlg.GetExampleSet();
            // (of course we could put the modified items directly into the column, but then the UNO-model
            // won't reflect these changes, and why do we have a model, then ?)

            // horizontal justify
            SFX_ITEMSET_GET(*pSet, pHorJustify, SvxHorJustifyItem, SBA_ATTR_ALIGN_HOR_JUSTIFY, sal_True);

            _eJustify = (SvxCellHorJustify)pHorJustify->GetValue();

            // format key
            if (_nFlags & TP_ATTR_NUMBER)
            {
                SFX_ITEMSET_GET(*pSet, pFormat, SfxUInt32Item, SBA_DEF_FMTVALUE, sal_True);
                _nFormatKey = (sal_Int32)pFormat->GetValue();
            }
            bRet = sal_True;
        }
            // deleted formats
        const SfxItemSet* pResult = aDlg.GetOutputItemSet();
        if (pResult)
        {
            const SfxPoolItem* pItem = pResult->GetItem( SID_ATTR_NUMBERFORMAT_INFO );
            const SvxNumberInfoItem* pInfoItem = static_cast<const SvxNumberInfoItem*>(pItem);
            if (pInfoItem && pInfoItem->GetDelCount())
            {
                const sal_uInt32* pDeletedKeys = pInfoItem->GetDelArray();

                for (sal_uInt16 i=0; i< pInfoItem->GetDelCount(); ++i, ++pDeletedKeys)
                    _pFormatter->DeleteEntry(*pDeletedKeys);
            }
        }
    }

    delete pFormatDescriptor;
    SfxItemPool::Free(pPool);
    for (sal_uInt16 i=0; i<sizeof(pDefaults)/sizeof(pDefaults[0]); ++i)
        delete pDefaults[i];

    return bRet;
}

//------------------------------------------------------------------------------
const SfxFilter* getStandardDatabaseFilter()
{
    static const String s_sDatabaseType = String::CreateFromAscii("StarOffice XML (Base)");
    const SfxFilter* pFilter = SfxFilter::GetFilterByName( s_sDatabaseType);
    OSL_ENSURE(pFilter,"Filter: StarOffice XML (Base) could not be found!");
    return pFilter;
}


// -----------------------------------------------------------------------------
sal_Bool appendToFilter(const Reference<XConnection>& _xConnection,
                        const ::rtl::OUString& _sName,
                        const Reference< XMultiServiceFactory >& _xFactory,
                        Window* _pParent)
{
    sal_Bool bRet = sal_False;
    Reference< XChild> xChild(_xConnection,UNO_QUERY);
    if(xChild.is())
    {
        Reference< XPropertySet> xProp(xChild->getParent(),UNO_QUERY);
        if(xProp.is())
        {
            Sequence< ::rtl::OUString > aFilter;
            xProp->getPropertyValue(PROPERTY_TABLEFILTER) >>= aFilter;
            // first check if we have something like SCHEMA.%
            sal_Bool bHasToInsert = sal_True;
            static ::rtl::OUString sPattern = ::rtl::OUString::createFromAscii("%");
            const ::rtl::OUString* pBegin = aFilter.getConstArray();
            const ::rtl::OUString* pEnd = pBegin + aFilter.getLength();
            for (;pBegin != pEnd; ++pBegin)
            {
                if(pBegin->indexOf('%') != -1)
                {
                    sal_Int32 nLen;
                    if((nLen = pBegin->lastIndexOf('.')) != -1 && !pBegin->compareTo(_sName,nLen))
                        bHasToInsert = sal_False;
                    else if(pBegin->getLength() == 1)
                        bHasToInsert = sal_False;
                }
            }

            bRet = sal_True;
            if(bHasToInsert)
            {
                if(! ::dbaui::checkDataSourceAvailable(::comphelper::getString(xProp->getPropertyValue(PROPERTY_NAME)),_xFactory))
                {
                    String aMessage(ModuleRes(STR_TABLEDESIGN_DATASOURCE_DELETED));
                    OSQLWarningBox( _pParent, aMessage ).Execute();
                    bRet = sal_False;
                }
                else
                {
                    aFilter.realloc(aFilter.getLength()+1);
                    aFilter.getArray()[aFilter.getLength()-1] = _sName;
                    xProp->setPropertyValue(PROPERTY_TABLEFILTER,makeAny(aFilter));
                }
            }
        }
    }
    return bRet;
}
// -----------------------------------------------------------------------------
void notifySystemWindow(Window* _pWindow,Window* _pToRegister, ::comphelper::mem_fun1_t<TaskPaneList,Window*> _rMemFunc)
{
    OSL_ENSURE(_pWindow,"Window can not be null!");
    SystemWindow* pSystemWindow = _pWindow ? _pWindow->GetSystemWindow() : NULL;
    if ( pSystemWindow )
    {
        _rMemFunc( pSystemWindow->GetTaskPaneList(), _pToRegister );
    }
}
// -----------------------------------------------------------------------------
void adjustToolBoxSize(ToolBox* _pToolBox)
{
    // adjust the toolbox size, otherwise large bitmaps don't fit into
    Size aOldSize = _pToolBox->GetSizePixel();
    Size aSize = _pToolBox->CalcWindowSizePixel();
    if ( !aSize.Width() )
        aSize.Width() = aOldSize.Width();
    else if ( !aSize.Height() )
        aSize.Height() = aOldSize.Height();

    Size aTbSize = _pToolBox->GetSizePixel();
    if ( (aSize.Width() && aSize.Width() != aTbSize.Width()) ||
            (aSize.Height() && aSize.Height() != aTbSize.Height()) )
    {
        _pToolBox->SetPosSizePixel( _pToolBox->GetPosPixel(), aSize );
        _pToolBox->Invalidate();
    }
}
// -----------------------------------------------------------------------------
sal_Bool isHiContrast(Window* _pWindow)
{
    OSL_ENSURE(_pWindow,"Window must be not null!");
    Window* pIter = _pWindow;
    //	while( pIter &&  pIter->GetBackground().GetColor().GetColor() == COL_TRANSPARENT )
    while( pIter )
    {
        if ( pIter->GetBackground().GetColor().GetColor() == COL_TRANSPARENT )
            pIter = pIter->GetParent();
        else
            break;
    }
    return pIter && pIter->GetBackground().GetColor().IsDark();
}

// -----------------------------------------------------------------------------
void adjustBrowseBoxColumnWidth( ::svt::EditBrowseBox* _pBox, sal_uInt16 _nColId )
{
    sal_Int32 nColSize = -1;
    sal_uInt32 nDefaultWidth = _pBox->GetDefaultColumnWidth( _pBox->GetColumnTitle( _nColId ) );
    if ( nDefaultWidth != _pBox->GetColumnWidth( _nColId ) )
    {
        Size aSizeMM = _pBox->PixelToLogic( Size( _pBox->GetColumnWidth( _nColId ), 0 ), MapMode( MAP_MM ) );
        nColSize = aSizeMM.Width() * 10;
    }

    Size aDefaultMM = _pBox->PixelToLogic( Size( nDefaultWidth, 0 ), MapMode( MAP_MM ) );

    DlgSize aColumnSizeDlg( _pBox, nColSize, sal_False, aDefaultMM.Width() * 10 );
    if ( aColumnSizeDlg.Execute() )
    {
        sal_Int32 nValue = aColumnSizeDlg.GetValue();
        if ( -1 == nValue )
        {	// default width
            nValue = _pBox->GetDefaultColumnWidth( _pBox->GetColumnTitle( _nColId ) );
        }
        else
        {
            Size aSizeMM( nValue / 10, 0 );
            nValue = _pBox->LogicToPixel( aSizeMM, MapMode( MAP_MM ) ).Width();
        }
        _pBox->SetColumnWidth( _nColId, nValue );
    }
}
// -----------------------------------------------------------------------------
// check if SQL92 name checking is enabled
sal_Bool isSQL92CheckEnabled(const Reference<XConnection>& _xConnection)
{
    return ::dbtools::getBooleanDataSourceSetting( _xConnection, PROPERTY_ENABLESQL92CHECK );
}
// -----------------------------------------------------------------------------
sal_Bool isAppendTableAliasEnabled(const Reference<XConnection>& _xConnection)
{
    return ::dbtools::getBooleanDataSourceSetting( _xConnection, INFO_APPEND_TABLE_ALIAS );
}

// -----------------------------------------------------------------------------
sal_Bool generateAsBeforeTableAlias(const Reference<XConnection>& _xConnection)
{
    return ::dbtools::getBooleanDataSourceSetting( _xConnection, INFO_AS_BEFORE_CORRELATION_NAME );
}

// -----------------------------------------------------------------------------
void fillAutoIncrementValue(const Reference<XPropertySet>& _xDatasource,
                            sal_Bool& _rAutoIncrementValueEnabled,
                            ::rtl::OUString& _rsAutoIncrementValue)
{
    if ( _xDatasource.is() )
    {
        OSL_ENSURE(_xDatasource->getPropertySetInfo()->hasPropertyByName(PROPERTY_INFO),"NO datasource supplied!");
        Sequence<PropertyValue> aInfo;
        _xDatasource->getPropertyValue(PROPERTY_INFO) >>= aInfo;

        // search the right propertyvalue
        const PropertyValue* pValue =::std::find_if(aInfo.getConstArray(),
                                                    aInfo.getConstArray() + aInfo.getLength(),
                                                    ::std::bind2nd(TPropertyValueEqualFunctor(),PROPERTY_AUTOINCREMENTCREATION));
        if ( pValue && pValue != (aInfo.getConstArray() + aInfo.getLength()) )
            pValue->Value >>= _rsAutoIncrementValue;
        pValue =::std::find_if(aInfo.getConstArray(),
                                                    aInfo.getConstArray() + aInfo.getLength(),
                                                    ::std::bind2nd(TPropertyValueEqualFunctor(),::rtl::OUString::createFromAscii("IsAutoRetrievingEnabled") ));
        if ( pValue && pValue != (aInfo.getConstArray() + aInfo.getLength()) )
            pValue->Value >>= _rAutoIncrementValueEnabled;
    }
}
// -----------------------------------------------------------------------------
void fillAutoIncrementValue(const Reference<XConnection>& _xConnection,
                            sal_Bool& _rAutoIncrementValueEnabled,
                            ::rtl::OUString& _rsAutoIncrementValue)
{
    Reference< XChild> xChild(_xConnection,UNO_QUERY);
    if(xChild.is())
    {
        Reference< XPropertySet> xProp(xChild->getParent(),UNO_QUERY);
        fillAutoIncrementValue(xProp,_rAutoIncrementValueEnabled,_rsAutoIncrementValue);
    }
}
// -----------------------------------------------------------------------------
::rtl::OUString getStrippedDatabaseName(const Reference<XPropertySet>& _xDataSource,::rtl::OUString& _rsDatabaseName)
{
    if ( !_rsDatabaseName.getLength() && _xDataSource.is() )
    {
        try
        {
            _xDataSource->getPropertyValue(PROPERTY_NAME) >>= _rsDatabaseName;
        }
        catch(const Exception& )
        {
            DBG_UNHANDLED_EXCEPTION();
        }
    }
    ::rtl::OUString sName = _rsDatabaseName;
    INetURLObject aURL(sName);
    if ( aURL.GetProtocol() != INET_PROT_NOT_VALID )
        sName = aURL.getBase(INetURLObject::LAST_SEGMENT,true,INetURLObject::DECODE_UNAMBIGUOUS);
    return sName;
}
// -----------------------------------------------------------------------------
    void AppendConfigToken( ::rtl::OUString& _rURL, sal_Bool _bQuestionMark )
    {
        Any aLocale =
            ::utl::ConfigManager::GetConfigManager()->GetDirectConfigProperty( ::utl::ConfigManager::LOCALE );
        ::rtl::OUString sLocaleStr;
        if ( !( aLocale >>= sLocaleStr ) )
            // fallback is english
            sLocaleStr = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("en"));

        // query part exists?
        if ( _bQuestionMark )
            // no, so start with '?'
            _rURL += ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("?"));
        else
            // yes, so only append with '&'
            _rURL += ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("&"));

        // set parameters
        _rURL += ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("Language="));
        _rURL += sLocaleStr;
        _rURL += ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("&System="));
        _rURL += SvtHelpOptions().GetSystem();
    }

namespace
{
    // -----------------------------------------------------------------------

    sal_Bool GetHelpAnchor_Impl( const ::rtl::OUString& _rURL, ::rtl::OUString& _rAnchor )
    {
        sal_Bool bRet = sal_False;
        ::rtl::OUString sAnchor;

        try
        {
            ::ucbhelper::Content aCnt( INetURLObject( _rURL ).GetMainURL( INetURLObject::NO_DECODE ),
                                 Reference< ::com::sun::star::ucb::XCommandEnvironment > () );
            if ( ( aCnt.getPropertyValue( ::rtl::OUString::createFromAscii( "AnchorName" ) ) >>= sAnchor ) )
            {

                if ( sAnchor.getLength() > 0 )
                {
                    _rAnchor = sAnchor;
                    bRet = sal_True;
                }
            }
            else
            {
                DBG_ERRORFILE( "Property 'AnchorName' is missing" );
            }
        }
        catch( Exception& )
        {
        }

        return bRet;
    }
// .........................................................................
} // annonymous
// .........................................................................
// -----------------------------------------------------------------------------
::com::sun::star::util::URL	createHelpAgentURL(const ::rtl::OUString& _sModuleName,const sal_Int32 _nHelpId)
{
    ::com::sun::star::util::URL aURL;
    aURL.Complete = ::rtl::OUString( RTL_CONSTASCII_USTRINGPARAM( "vnd.sun.star.help://" ) );
    aURL.Complete += _sModuleName;
    aURL.Complete += ::rtl::OUString( RTL_CONSTASCII_USTRINGPARAM( "/" ) );
    aURL.Complete += ::rtl::OUString::valueOf(_nHelpId);

    ::rtl::OUString sAnchor;
    ::rtl::OUString sTempURL = aURL.Complete;
    AppendConfigToken( sTempURL, sal_True );
    sal_Bool bHasAnchor = GetHelpAnchor_Impl( sTempURL, sAnchor );
    AppendConfigToken(aURL.Complete,sal_True);
    if ( bHasAnchor )
    {
        aURL.Complete += ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("#"));
        aURL.Complete += sAnchor;
    }
    return aURL;
}
// -----------------------------------------------------------------------------
void setEvalDateFormatForFormatter(Reference< ::com::sun::star::util::XNumberFormatter >& _rxFormatter)
{
    OSL_ENSURE( _rxFormatter.is(),"setEvalDateFormatForFormatter: Formatter is NULL!");
    if ( _rxFormatter.is() )
    {
        Reference< ::com::sun::star::util::XNumberFormatsSupplier >  xSupplier = _rxFormatter->getNumberFormatsSupplier();

        Reference< XUnoTunnel > xTunnel(xSupplier,UNO_QUERY);
        SvNumberFormatsSupplierObj* pSupplierImpl = reinterpret_cast<SvNumberFormatsSupplierObj*>(xTunnel->getSomething(SvNumberFormatsSupplierObj::getUnoTunnelId()));
        OSL_ENSURE(pSupplierImpl,"No Supplier!");

        if ( pSupplierImpl )
        {
            SvNumberFormatter* pFormatter = pSupplierImpl->GetNumberFormatter();
            pFormatter->SetEvalDateFormat(NF_EVALDATEFORMAT_FORMAT);
        }
    }
}
// -----------------------------------------------------------------------------
TOTypeInfoSP queryPrimaryKeyType(const OTypeInfoMap& _rTypeInfo)
{
    TOTypeInfoSP pTypeInfo;
    // first we search for a type which supports autoIncrement
    OTypeInfoMap::const_iterator aIter = _rTypeInfo.begin();
    OTypeInfoMap::const_iterator aEnd  = _rTypeInfo.end();
    for(;aIter != aEnd;++aIter)
    {
        // OJ: we don't want to set an autoincrement column to be key
        // because we don't have the possiblity to know how to create
        // such auto increment column later on
        // so until we know how to do it, we create a column without autoincrement
        //	if ( !aIter->second->bAutoIncrement )
        {	// therefor we have searched
            if ( aIter->second->nType == DataType::INTEGER )
            {
                pTypeInfo = aIter->second; // alternative
                break;
            }
            else if ( !pTypeInfo.get() && aIter->second->nType == DataType::DOUBLE )
                pTypeInfo = aIter->second; // alternative
            else if ( !pTypeInfo.get() && aIter->second->nType == DataType::REAL )
                pTypeInfo = aIter->second; // alternative
        }
    }
    if ( !pTypeInfo.get() ) // just a fallback
        pTypeInfo = queryTypeInfoByType(DataType::VARCHAR,_rTypeInfo);

    OSL_ENSURE(pTypeInfo.get(),"checkColumns: cann't find a type which is useable as a key!");
    return pTypeInfo;
}
// -----------------------------------------------------------------------------
TOTypeInfoSP queryTypeInfoByType(sal_Int32 _nDataType,const OTypeInfoMap& _rTypeInfo)
{
    OTypeInfoMap::const_iterator aIter = _rTypeInfo.find(_nDataType);
    if(aIter != _rTypeInfo.end())
        return aIter->second;
    // fall back if the type is unknown
    TOTypeInfoSP pTypeInfo;
    switch(_nDataType)
    {
        case DataType::TINYINT:
            if( pTypeInfo = queryTypeInfoByType(DataType::SMALLINT,_rTypeInfo))
                break;
            // run through
        case DataType::SMALLINT:
            if( pTypeInfo = queryTypeInfoByType(DataType::INTEGER,_rTypeInfo))
                break;
            // run through
        case DataType::INTEGER:
            if( pTypeInfo = queryTypeInfoByType(DataType::FLOAT,_rTypeInfo))
                break;
            // run through
        case DataType::FLOAT:
            if( pTypeInfo = queryTypeInfoByType(DataType::REAL,_rTypeInfo))
                break;
            // run through
        case DataType::DATE:
        case DataType::TIME:
            if( DataType::DATE == _nDataType || DataType::TIME == _nDataType )
            {
                if( pTypeInfo = queryTypeInfoByType(DataType::TIMESTAMP,_rTypeInfo))
                    break;
            }
            // run through
        case DataType::TIMESTAMP:
        case DataType::REAL:
        case DataType::BIGINT:
            if (  pTypeInfo = queryTypeInfoByType(DataType::DOUBLE,_rTypeInfo) )
                break;
            // run through
        case DataType::DOUBLE:
            if (  pTypeInfo = queryTypeInfoByType(DataType::NUMERIC,_rTypeInfo) )
                break;
            // run through
        case DataType::NUMERIC:
             pTypeInfo = queryTypeInfoByType(DataType::DECIMAL,_rTypeInfo);
            break;
        case DataType::DECIMAL:
            if (  pTypeInfo = queryTypeInfoByType(DataType::NUMERIC,_rTypeInfo) )
                break;
            if (  pTypeInfo = queryTypeInfoByType(DataType::DOUBLE,_rTypeInfo) )
                break;
            break;
        case DataType::VARCHAR:
            if (  pTypeInfo = queryTypeInfoByType(DataType::LONGVARCHAR,_rTypeInfo) )
                break;
            break;
        default:
            ;
    } // switch(_nDataType)
    if ( !pTypeInfo )
    {
        ::rtl::OUString sCreate(RTL_CONSTASCII_USTRINGPARAM("x")),sTypeName;
        sal_Bool bForce = sal_True;
        pTypeInfo = ::dbaui::getTypeInfoFromType(_rTypeInfo,DataType::VARCHAR,sTypeName,sCreate,50,0,sal_False,bForce);
    } // if ( !pTypeInfo )
    OSL_ENSURE(pTypeInfo,"Wrong DataType supplied!");
    return pTypeInfo;
}
// -----------------------------------------------------------------------------
sal_Int32 askForUserAction(Window* _pParent,USHORT _nTitle,USHORT _nText,sal_Bool _bAll,const ::rtl::OUString& _sName)
{
    vos::OGuard aGuard( Application::GetSolarMutex() );
    String aMsg = String(ModuleRes(_nText));
    aMsg.SearchAndReplace(String::CreateFromAscii("%1"),String(_sName));
    OSQLMessageBox aAsk(_pParent,String(ModuleRes(_nTitle )),aMsg,WB_YES_NO | WB_DEF_YES,OSQLMessageBox::Query);
    if ( _bAll )
    {
        aAsk.AddButton(String(ModuleRes(STR_BUTTON_TEXT_ALL)), RET_ALL, 0);
        aAsk.GetPushButton(RET_ALL)->SetHelpId(HID_CONFIRM_DROP_BUTTON_ALL);
    }
    return aAsk.Execute();
}

// -----------------------------------------------------------------------------
namespace
{
    static ::rtl::OUString lcl_createSDBCLevelStatement( const ::rtl::OUString& _rStatement, const Reference< XConnection >& _rxConnection )
    {
        ::rtl::OUString sSDBCLevelStatement( _rStatement );
        try
        {
            Reference< XMultiServiceFactory > xAnalyzerFactory( _rxConnection, UNO_QUERY_THROW );
            Reference< XSingleSelectQueryAnalyzer > xAnalyzer( xAnalyzerFactory->createInstance( SERVICE_NAME_SINGLESELECTQUERYCOMPOSER ), UNO_QUERY_THROW );
            xAnalyzer->setQuery( _rStatement );
            sSDBCLevelStatement = xAnalyzer->getQueryWithSubstitution();
        }
        catch( const Exception& )
        {
            DBG_UNHANDLED_EXCEPTION();
        }
        return sSDBCLevelStatement;
    }
}

// -----------------------------------------------------------------------------
Reference< XPropertySet > createView( const ::rtl::OUString& _rName, const Reference< XConnection >& _rxConnection,
                                    const ::rtl::OUString& _rCommand )
{
    Reference<XViewsSupplier> xSup(_rxConnection,UNO_QUERY);
    Reference< XNameAccess > xViews;
    if(xSup.is())
        xViews = xSup->getViews();
    Reference<XDataDescriptorFactory> xFact(xViews,UNO_QUERY);
    OSL_ENSURE(xFact.is(),"No XDataDescriptorFactory available!");
    if(!xFact.is())
        return NULL;

    Reference<XPropertySet> xView = xFact->createDataDescriptor();
    if ( !xView.is() )
        return NULL;

    ::rtl::OUString sCatalog,sSchema,sTable;
    ::dbtools::qualifiedNameComponents(_rxConnection->getMetaData(),
                                        _rName,
                                        sCatalog,
                                        sSchema,
                                        sTable,
                                        ::dbtools::eInDataManipulation);

    xView->setPropertyValue(PROPERTY_CATALOGNAME,makeAny(sCatalog));
    xView->setPropertyValue(PROPERTY_SCHEMANAME,makeAny(sSchema));
    xView->setPropertyValue(PROPERTY_NAME,makeAny(sTable));

    xView->setPropertyValue( PROPERTY_COMMAND, makeAny( _rCommand ) );

    Reference<XAppend> xAppend(xViews,UNO_QUERY);
    if(xAppend.is())
        xAppend->appendByDescriptor(xView);

    xView = NULL;
    // we need to reget the view because after appending it it is no longer valid
    // but this time it isn't a view object it is a table object with type "VIEW"
    Reference<XTablesSupplier> xTabSup(_rxConnection,UNO_QUERY);
    Reference< XNameAccess > xTables;
    if ( xTabSup.is() )
    {
        xTables = xTabSup->getTables();
        if ( xTables.is() && xTables->hasByName( _rName ) )
            xTables->getByName( _rName ) >>= xView;
    }

    return xView;
}

// -----------------------------------------------------------------------------
Reference<XPropertySet> createView( const ::rtl::OUString& _rName, const Reference< XConnection >& _rxConnection
                                   ,const Reference<XPropertySet>& _rxSourceObject)
{
    ::rtl::OUString sCommand;
    Reference< XPropertySetInfo > xPSI( _rxSourceObject->getPropertySetInfo(), UNO_SET_THROW );
    if ( xPSI->hasPropertyByName( PROPERTY_COMMAND ) )
    {
        _rxSourceObject->getPropertyValue( PROPERTY_COMMAND ) >>= sCommand;

        sal_Bool bEscapeProcessing( sal_False );
        OSL_VERIFY( _rxSourceObject->getPropertyValue( PROPERTY_ESCAPE_PROCESSING ) >>= bEscapeProcessing );
        if ( bEscapeProcessing )
            sCommand = lcl_createSDBCLevelStatement( sCommand, _rxConnection );
    }
    else
    {
        sCommand = ::rtl::OUString( RTL_CONSTASCII_USTRINGPARAM( "SELECT * FROM " ) );
        sCommand += composeTableNameForSelect( _rxConnection, _rxSourceObject );
    }
    return createView( _rName, _rxConnection, sCommand );
}

// -----------------------------------------------------------------------------
sal_Bool insertHierachyElement( Window* _pParent, const Reference< XMultiServiceFactory >& _rxORB,
                           const Reference<XHierarchicalNameContainer>& _xNames,
                           const String& _sParentFolder,
                           sal_Bool _bForm,
                           sal_Bool _bCollection,
                           const Reference<XContent>& _xContent,
                           sal_Bool _bMove)
{
    OSL_ENSURE( _xNames.is(), "insertHierachyElement: illegal name container!" );
    if ( !_xNames.is() )
        return sal_False;

    Reference<XNameAccess> xNameAccess( _xNames, UNO_QUERY );
    ::rtl::OUString sName = _sParentFolder;
    if ( _xNames->hasByHierarchicalName(sName) )
    {
        Reference<XChild> xChild(_xNames->getByHierarchicalName(sName),UNO_QUERY);
        xNameAccess.set(xChild,UNO_QUERY);
        if ( !xNameAccess.is() && xChild.is() )
            xNameAccess.set(xChild->getParent(),UNO_QUERY);
    }

    OSL_ENSURE( xNameAccess.is(), "insertHierachyElement: could not find the proper name container!" );
    if ( !xNameAccess.is() )
        return sal_False;

    ::rtl::OUString sNewName;
    Reference<XPropertySet> xProp(_xContent,UNO_QUERY);
    if ( xProp.is() )
        xProp->getPropertyValue(PROPERTY_NAME) >>= sNewName;

    if ( !_bMove || !sNewName.getLength() )
    {
        String sTargetName,sLabel;
        if ( !sNewName.getLength() || xNameAccess->hasByName(sNewName) )
        {
            if ( sNewName.getLength() )
                sTargetName = sNewName;
            else
                sTargetName = String(ModuleRes( _bCollection ? STR_NEW_FOLDER : ((_bForm) ? RID_STR_FORM : RID_STR_REPORT)));
            sLabel = String(ModuleRes( _bCollection ? STR_FOLDER_LABEL  : ((_bForm) ? STR_FRM_LABEL : STR_RPT_LABEL)));
            sTargetName = ::dbtools::createUniqueName(xNameAccess,sTargetName);


            // here we have everything needed to create a new query object ...
            HierarchicalNameCheck aNameChecker( _xNames.get(), sName );
            // ... ehm, except a new name
            OSaveAsDlg aAskForName(	_pParent,
                                    _rxORB,
                                    sTargetName,
                                    sLabel,
                                    aNameChecker,
                                    SAD_ADDITIONAL_DESCRIPTION | SAD_TITLE_PASTE_AS);
            if ( RET_OK != aAskForName.Execute() )
                // cancelled by the user
                return sal_False;

            sNewName = aAskForName.getName();
        }
    }
    else if ( xNameAccess->hasByName(sNewName) )
    {
        String sError(ModuleRes(STR_NAME_ALREADY_EXISTS));
        sError.SearchAndReplaceAscii("#",sNewName);
        throw SQLException(sError,NULL,::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("S1000")) ,0,Any());
    }

    try
    {
        Reference<XMultiServiceFactory> xORB( xNameAccess, UNO_QUERY_THROW );
        Sequence< Any > aArguments(3);
        PropertyValue aValue;
        // set as folder
        aValue.Name = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("Name"));
        aValue.Value <<= sNewName;
        aArguments[0] <<= aValue;
        //parent
        aValue.Name = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("Parent"));
        aValue.Value <<= xNameAccess;
        aArguments[1] <<= aValue;

        aValue.Name = PROPERTY_EMBEDDEDOBJECT;
        aValue.Value <<= _xContent;
        aArguments[2] <<= aValue;

        ::rtl::OUString sServiceName(_bCollection ? ((_bForm) ? SERVICE_NAME_FORM_COLLECTION : SERVICE_NAME_REPORT_COLLECTION) : SERVICE_SDB_DOCUMENTDEFINITION);

        Reference<XContent > xNew( xORB->createInstanceWithArguments( sServiceName, aArguments ), UNO_QUERY_THROW );
        Reference< XNameContainer > xNameContainer( xNameAccess, UNO_QUERY_THROW );
        xNameContainer->insertByName( sNewName, makeAny( xNew ) );
    }
    catch( const IllegalArgumentException& e )
    {
        ::dbtools::throwGenericSQLException( e.Message, e.Context );
    }
    catch( const Exception& )
    {
        DBG_UNHANDLED_EXCEPTION();
        return sal_False;
    }

    return sal_True;
}
// -----------------------------------------------------------------------------
Reference< XNumberFormatter > getNumberFormatter(const Reference< XConnection >& _rxConnection,const Reference< ::com::sun::star::lang::XMultiServiceFactory >& _rMF )
{
    // ---------------------------------------------------------------
    // create a formatter working with the connections format supplier
    Reference< XNumberFormatter > xFormatter;

    try
    {
        Reference< ::com::sun::star::util::XNumberFormatsSupplier >  xSupplier(::dbtools::getNumberFormats(_rxConnection, sal_True,_rMF));

        if ( xSupplier.is() )
        {
            // create a new formatter
            xFormatter = Reference< ::com::sun::star::util::XNumberFormatter > (
                _rMF->createInstance(::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("com.sun.star.util.NumberFormatter"))), UNO_QUERY);
            if ( xFormatter.is() )
                xFormatter->attachNumberFormatsSupplier(xSupplier);
        }
    }
    catch(const Exception&)
    {
        DBG_UNHANDLED_EXCEPTION();
    }
    return xFormatter;
}


// .........................................................................
} // dbaui
// .........................................................................
