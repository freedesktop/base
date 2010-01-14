/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 *
 * Copyright 2008 by Sun Microsystems, Inc.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * $RCSfile: precompiled_dbaccess.hxx,v $
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

// MARKER(update_precomp.py): Generated on 2006-09-01 17:49:38.561560

#ifdef PRECOMPILED_HEADERS

//---MARKER---
#include "sal/types.h"


#include "boost/mem_fn.hpp"
#include "boost/noncopyable.hpp"
#include "boost/optional.hpp"
#include "boost/shared_ptr.hpp"

#include "com/sun/star/accessibility/AccessibleEventId.hpp"
#include "com/sun/star/accessibility/AccessibleRelationType.hpp"
#include "com/sun/star/accessibility/AccessibleRole.hpp"
#include "com/sun/star/accessibility/AccessibleStateType.hpp"
#include "com/sun/star/accessibility/XAccessible.hpp"
#include "com/sun/star/accessibility/XAccessibleRelationSet.hpp"
#include "com/sun/star/awt/FontDescriptor.hpp"
#include "com/sun/star/awt/FontEmphasisMark.hpp"
#include "com/sun/star/awt/FontRelief.hpp"
#include "com/sun/star/awt/FontSlant.hpp"
#include "com/sun/star/awt/FontStrikeout.hpp"
#include "com/sun/star/awt/FontUnderline.hpp"
#include "com/sun/star/awt/FontWeight.hpp"
#include "com/sun/star/awt/FontWidth.hpp"
#include "com/sun/star/awt/LineEndFormat.hpp"
#include "com/sun/star/awt/PosSize.hpp"
#include "com/sun/star/awt/Size.hpp"
#include "com/sun/star/awt/TextAlign.hpp"
#include "com/sun/star/awt/VisualEffect.hpp"
#include "com/sun/star/awt/XControlModel.hpp"
#include "com/sun/star/awt/XFocusListener.hpp"
#include "com/sun/star/awt/XTabControllerModel.hpp"
#include "com/sun/star/awt/XTextComponent.hpp"
#include "com/sun/star/awt/XWindow.hpp"
#include "com/sun/star/beans/NamedValue.hpp"
#include "com/sun/star/beans/Property.hpp"
#include "com/sun/star/beans/PropertyAttribute.hpp"
#include "com/sun/star/beans/PropertyState.hpp"
#include "com/sun/star/beans/PropertyValue.hpp"
#include "com/sun/star/beans/XFastPropertySet.hpp"
#include "com/sun/star/beans/XMultiPropertySet.hpp"
#include "com/sun/star/beans/XPropertiesChangeListener.hpp"
#include "com/sun/star/beans/XPropertiesChangeNotifier.hpp"
#include "com/sun/star/beans/XPropertyAccess.hpp"
#include "com/sun/star/beans/XPropertyChangeListener.hpp"
#include "com/sun/star/beans/XPropertyContainer.hpp"
#include "com/sun/star/beans/XPropertySet.hpp"
#include "com/sun/star/beans/XPropertySetInfo.hpp"
#include "com/sun/star/beans/XPropertyState.hpp"
#include "com/sun/star/beans/XPropertyStateChangeListener.hpp"
#include "com/sun/star/beans/XVetoableChangeListener.hpp"
#include "com/sun/star/chart/ChartDataRowSource.hpp"
#include "com/sun/star/configuration/backend/XLayer.hpp"
#include "com/sun/star/configuration/backend/XLayerHandler.hpp"
#include "com/sun/star/connection/XConnection.hpp"
#include "com/sun/star/container/ElementExistException.hpp"
#include "com/sun/star/container/XChild.hpp"
#include "com/sun/star/container/XContainer.hpp"
#include "com/sun/star/container/XContainerApproveBroadcaster.hpp"
#include "com/sun/star/container/XContainerApproveListener.hpp"
#include "com/sun/star/container/XContainerListener.hpp"
#include "com/sun/star/container/XEnumerationAccess.hpp"
#include "com/sun/star/container/XHierarchicalNameAccess.hpp"
#include "com/sun/star/container/XHierarchicalNameContainer.hpp"
#include "com/sun/star/container/XIndexAccess.hpp"
#include "com/sun/star/container/XIndexContainer.hpp"
#include "com/sun/star/container/XNameAccess.hpp"
#include "com/sun/star/container/XNameContainer.hpp"
#include "com/sun/star/container/XNameReplace.hpp"
#include "com/sun/star/container/XNamed.hpp"
#include "com/sun/star/container/XSet.hpp"
#include "com/sun/star/datatransfer/DataFlavor.hpp"
#include "com/sun/star/datatransfer/XTransferable.hpp"
#include "com/sun/star/datatransfer/clipboard/XClipboard.hpp"
#include "com/sun/star/datatransfer/dnd/XDragGestureListener.hdl"
#include "com/sun/star/datatransfer/dnd/XDragGestureRecognizer.hpp"
#include "com/sun/star/document/MacroExecMode.hpp"
#include "com/sun/star/document/XDocumentInfoSupplier.hpp"
#include "com/sun/star/document/XDocumentSubStorageSupplier.hpp"
#include "com/sun/star/document/XEventBroadcaster.hpp"
#include "com/sun/star/document/XEventListener.hpp"
#include "com/sun/star/document/XEventsSupplier.hpp"
#include "com/sun/star/document/XExporter.hpp"
#include "com/sun/star/document/XExtendedFilterDetection.hpp"
#include "com/sun/star/document/XFilter.hpp"
#include "com/sun/star/document/XImporter.hpp"
#include "com/sun/star/document/XStorageBasedDocument.hpp"
#include "com/sun/star/document/XTypeDetection.hpp"
#include "com/sun/star/drawing/XDrawPageSupplier.hpp"
#include "com/sun/star/embed/Aspects.hpp"
#include "com/sun/star/embed/ElementModes.hpp"
#include "com/sun/star/embed/EmbedStates.hpp"
#include "com/sun/star/embed/EntryInitModes.hpp"
#include "com/sun/star/embed/XCommonEmbedPersist.hpp"
#include "com/sun/star/embed/XComponentSupplier.hpp"
#include "com/sun/star/embed/XEmbedObjectCreator.hpp"
#include "com/sun/star/embed/XEmbedObjectFactory.hpp"
#include "com/sun/star/embed/XEmbedPersist.hpp"
#include "com/sun/star/embed/XEmbeddedObject.hpp"
#include "com/sun/star/embed/XStateChangeBroadcaster.hpp"
#include "com/sun/star/embed/XStateChangeListener.hpp"
#include "com/sun/star/embed/XStorage.hpp"
#include "com/sun/star/embed/XTransactedObject.hpp"
#include "com/sun/star/embed/XTransactionBroadcaster.hpp"
#include "com/sun/star/embed/XTransactionListener.hpp"
#include "com/sun/star/form/DataSelectionType.hpp"
#include "com/sun/star/form/FormButtonType.hpp"
#include "com/sun/star/form/FormComponentType.hpp"
#include "com/sun/star/form/FormSubmitEncoding.hpp"
#include "com/sun/star/form/FormSubmitMethod.hpp"
#include "com/sun/star/form/XApproveActionBroadcaster.hpp"
#include "com/sun/star/form/XBoundControl.hpp"
#include "com/sun/star/form/XChangeBroadcaster.hpp"
#include "com/sun/star/form/XChangeListener.hpp"
#include "com/sun/star/form/XConfirmDeleteListener.hpp"
#include "com/sun/star/form/XDatabaseParameterBroadcaster.hpp"
#include "com/sun/star/form/XDatabaseParameterListener.hpp"
#include "com/sun/star/form/XDeleteListener.hpp"
#include "com/sun/star/form/XErrorListener.hpp"
#include "com/sun/star/form/XForm.hpp"
#include "com/sun/star/form/XFormComponent.hpp"
#include "com/sun/star/form/XFormsSupplier.hpp"
#include "com/sun/star/form/XGridColumnFactory.hpp"
#include "com/sun/star/form/XInsertListener.hpp"
#include "com/sun/star/form/XLoadListener.hpp"
#include "com/sun/star/form/XPositioningListener.hpp"
#include "com/sun/star/form/XReset.hpp"
#include "com/sun/star/form/XResetListener.hpp"
#include "com/sun/star/form/XRestoreListener.hpp"
#include "com/sun/star/form/XSubmitListener.hpp"
#include "com/sun/star/form/XUpdateListener.hpp"
#include "com/sun/star/frame/CommandGroup.hpp"
#include "com/sun/star/frame/FrameSearchFlag.hpp"
#include "com/sun/star/frame/XComponentLoader.hpp"
#include "com/sun/star/frame/XController.hpp"
#include "com/sun/star/frame/XDispatch.hpp"
#include "com/sun/star/frame/XDispatchInformationProvider.hpp"
#include "com/sun/star/frame/XDispatchProvider.hpp"
#include "com/sun/star/frame/XDispatchProviderInterception.hpp"
#include "com/sun/star/frame/XDispatchProviderInterceptor.hpp"
#include "com/sun/star/frame/XFrame.hpp"
#include "com/sun/star/frame/XFrameActionListener.hpp"
#include "com/sun/star/frame/XFrameLoader.hpp"
#include "com/sun/star/frame/XFrames.hpp"
#include "com/sun/star/frame/XFramesSupplier.hpp"
#include "com/sun/star/frame/XInterceptorInfo.hpp"
#include "com/sun/star/frame/XLayoutManager.hpp"
#include "com/sun/star/frame/XLoadEventListener.hpp"
#include "com/sun/star/frame/XModel.hpp"
#include "com/sun/star/frame/XStatusListener.hpp"
#include "com/sun/star/frame/XStorable.hpp"
#include "com/sun/star/graphic/GraphicColorMode.hpp"
#include "com/sun/star/graphic/XGraphic.hpp"
#include "com/sun/star/i18n/XCollator.hpp"
#include "com/sun/star/i18n/XLocaleData.hpp"
#include "com/sun/star/io/IOException.hpp"
#include "com/sun/star/io/XActiveDataSink.hpp"
#include "com/sun/star/io/XActiveDataSource.hpp"
#include "com/sun/star/io/XInputStream.hpp"
#include "com/sun/star/io/XObjectInputStream.hpp"
#include "com/sun/star/io/XObjectOutputStream.hpp"
#include "com/sun/star/io/XOutputStream.hpp"
#include "com/sun/star/io/XPersistObject.hpp"
#include "com/sun/star/io/XSeekable.hpp"
#include "com/sun/star/lang/DisposedException.hpp"
#include "com/sun/star/lang/IllegalAccessException.hpp"
#include "com/sun/star/lang/IllegalArgumentException.hpp"
#include "com/sun/star/lang/Locale.hpp"
#include "com/sun/star/lang/NullPointerException.hpp"
#include "com/sun/star/lang/ServiceNotRegisteredException.hpp"
#include "com/sun/star/lang/WrappedTargetException.hpp"
#include "com/sun/star/lang/XComponent.hpp"
#include "com/sun/star/lang/XEventListener.hpp"
#include "com/sun/star/lang/XInitialization.hpp"
#include "com/sun/star/lang/XMultiServiceFactory.hpp"
#include "com/sun/star/lang/XServiceInfo.hpp"
#include "com/sun/star/lang/XSingleServiceFactory.hpp"
#include "com/sun/star/lang/XUnoTunnel.hpp"
#include "com/sun/star/mozilla/XMozillaBootstrap.hpp"
#include "com/sun/star/packages/zip/ZipIOException.hpp"
#include "com/sun/star/reflection/XProxyFactory.hpp"
#include "com/sun/star/registry/InvalidRegistryException.hpp"
#include "com/sun/star/registry/XRegistryKey.hpp"
#include "com/sun/star/script/XTypeConverter.hpp"
#include "com/sun/star/sdb/CommandType.hpp"
#include "com/sun/star/sdb/DocumentSaveRequest.hpp"
#include "com/sun/star/sdb/ParametersRequest.hpp"
#include "com/sun/star/sdb/RowChangeAction.hpp"
#include "com/sun/star/sdb/RowSetVetoException.hpp"
#include "com/sun/star/sdb/SQLContext.hpp"
#include "com/sun/star/sdb/SQLFilterOperator.hpp"
#include "com/sun/star/sdb/XBookmarksSupplier.hpp"
#include "com/sun/star/sdb/XColumn.hpp"
#include "com/sun/star/sdb/XColumnUpdate.hpp"
#include "com/sun/star/sdb/XCommandPreparation.hpp"
#include "com/sun/star/sdb/XCompletedConnection.hpp"
#include "com/sun/star/sdb/XCompletedExecution.hpp"
#include "com/sun/star/sdb/XDatabaseEnvironment.hpp"
#include "com/sun/star/sdb/XDocumentDataSource.hpp"
#include "com/sun/star/sdb/XFormDocumentsSupplier.hpp"
#include "com/sun/star/sdb/XInteractionDocumentSave.hpp"
#include "com/sun/star/sdb/XInteractionSupplyParameters.hpp"
#include "com/sun/star/sdb/XOfficeDatabaseDocument.hpp"
#include "com/sun/star/sdb/XParametersSupplier.hpp"
#include "com/sun/star/sdb/XQueriesSupplier.hpp"
#include "com/sun/star/sdb/XQueryDefinitionsSupplier.hpp"
#include "com/sun/star/sdb/XReportDocumentsSupplier.hpp"
#include "com/sun/star/sdb/XResultSetAccess.hpp"
#include "com/sun/star/sdb/XRowSetApproveBroadcaster.hpp"
#include "com/sun/star/sdb/XRowSetApproveListener.hpp"
#include "com/sun/star/sdb/XSQLErrorBroadcaster.hpp"
#include "com/sun/star/sdb/XSQLErrorListener.hpp"
#include "com/sun/star/sdb/XSQLQueryComposer.hpp"
#include "com/sun/star/sdb/XSQLQueryComposerFactory.hpp"
#include "com/sun/star/sdb/XSingleSelectQueryAnalyzer.hpp"
#include "com/sun/star/sdb/XSingleSelectQueryComposer.hpp"
#include "com/sun/star/sdb/application/DatabaseObject.hpp"
#include "com/sun/star/sdb/application/XDatabaseDocumentUI.hpp"
#include "com/sun/star/sdb/application/XTableUIProvider.hpp"
#include "com/sun/star/sdb/tools/CompositionType.hpp"
#include "com/sun/star/sdb/tools/XConnectionTools.hpp"
#include "com/sun/star/sdb/tools/XDataSourceMetaData.hpp"
#include "com/sun/star/sdb/tools/XObjectNames.hpp"
#include "com/sun/star/sdb/tools/XTableName.hpp"
#include "com/sun/star/sdbc/ColumnSearch.hpp"
#include "com/sun/star/sdbc/ColumnValue.hpp"
#include "com/sun/star/sdbc/DataType.hpp"
#include "com/sun/star/sdbc/FetchDirection.hpp"
#include "com/sun/star/sdbc/IndexType.hpp"
#include "com/sun/star/sdbc/KeyRule.hpp"
#include "com/sun/star/sdbc/ResultSetConcurrency.hpp"
#include "com/sun/star/sdbc/ResultSetType.hpp"
#include "com/sun/star/sdbc/SQLException.hpp"
#include "com/sun/star/sdbc/SQLWarning.hpp"
#include "com/sun/star/sdbc/XCloseable.hpp"
#include "com/sun/star/sdbc/XColumnLocate.hpp"
#include "com/sun/star/sdbc/XConnection.hpp"
#include "com/sun/star/sdbc/XDataSource.hpp"
#include "com/sun/star/sdbc/XDatabaseMetaData.hpp"
#include "com/sun/star/sdbc/XDriver.hpp"
#include "com/sun/star/sdbc/XDriverAccess.hpp"
#include "com/sun/star/sdbc/XDriverManager.hpp"
#include "com/sun/star/sdbc/XGeneratedResultSet.hpp"
#include "com/sun/star/sdbc/XIsolatedConnection.hpp"
#include "com/sun/star/sdbc/XMultipleResults.hpp"
#include "com/sun/star/sdbc/XOutParameters.hpp"
#include "com/sun/star/sdbc/XParameters.hpp"
#include "com/sun/star/sdbc/XPreparedBatchExecution.hpp"
#include "com/sun/star/sdbc/XPreparedStatement.hpp"
#include "com/sun/star/sdbc/XResultSet.hpp"
#include "com/sun/star/sdbc/XResultSetMetaData.hdl"
#include "com/sun/star/sdbc/XResultSetMetaData.hpp"
#include "com/sun/star/sdbc/XResultSetMetaDataSupplier.hpp"
#include "com/sun/star/sdbc/XResultSetUpdate.hpp"
#include "com/sun/star/sdbc/XRow.hpp"
#include "com/sun/star/sdbc/XRowSet.hpp"
#include "com/sun/star/sdbc/XRowSetListener.hpp"
#include "com/sun/star/sdbc/XRowUpdate.hpp"
#include "com/sun/star/sdbc/XStatement.hpp"
#include "com/sun/star/sdbc/XWarningsSupplier.hpp"
#include "com/sun/star/sdbcx/CompareBookmark.hpp"
#include "com/sun/star/sdbcx/KeyType.hpp"
#include "com/sun/star/sdbcx/Privilege.hpp"
#include "com/sun/star/sdbcx/PrivilegeObject.hpp"
#include "com/sun/star/sdbcx/XAlterTable.hpp"
#include "com/sun/star/sdbcx/XAppend.hpp"
#include "com/sun/star/sdbcx/XAuthorizable.hpp"
#include "com/sun/star/sdbcx/XColumnsSupplier.hpp"
#include "com/sun/star/sdbcx/XCreateCatalog.hpp"
#include "com/sun/star/sdbcx/XDataDefinitionSupplier.hpp"
#include "com/sun/star/sdbcx/XDataDescriptorFactory.hpp"
#include "com/sun/star/sdbcx/XDeleteRows.hpp"
#include "com/sun/star/sdbcx/XDrop.hpp"
#include "com/sun/star/sdbcx/XGroupsSupplier.hpp"
#include "com/sun/star/sdbcx/XIndexesSupplier.hpp"
#include "com/sun/star/sdbcx/XKeysSupplier.hpp"
#include "com/sun/star/sdbcx/XRename.hpp"
#include "com/sun/star/sdbcx/XRowLocate.hpp"
#include "com/sun/star/sdbcx/XTablesSupplier.hpp"
#include "com/sun/star/sdbcx/XUser.hpp"
#include "com/sun/star/sdbcx/XUsersSupplier.hpp"
#include "com/sun/star/sdbcx/XViewsSupplier.hpp"
#include "com/sun/star/style/XStyleFamiliesSupplier.hpp"
#include "com/sun/star/task/ErrorCodeIOException.hpp"
#include "com/sun/star/task/InteractionClassification.hpp"
#include "com/sun/star/task/XInteractionAbort.hpp"
#include "com/sun/star/task/XInteractionApprove.hpp"
#include "com/sun/star/task/XInteractionDisapprove.hpp"
#include "com/sun/star/task/XInteractionHandler.hpp"
#include "com/sun/star/task/XInteractionRetry.hpp"
#include "com/sun/star/task/XJob.hpp"
#include "com/sun/star/task/XJobExecutor.hpp"
#include "com/sun/star/task/XStatusIndicator.hpp"
#include "com/sun/star/task/XStatusIndicatorFactory.hpp"
#include "com/sun/star/ucb/AuthenticationRequest.hpp"
#include "com/sun/star/ucb/Command.hpp"
#include "com/sun/star/ucb/CommandInfo.hpp"
#include "com/sun/star/ucb/IOErrorCode.hpp"
#include "com/sun/star/ucb/InsertCommandArgument.hpp"
#include "com/sun/star/ucb/InteractiveAugmentedIOException.hpp"
#include "com/sun/star/ucb/InteractiveIOException.hpp"
#include "com/sun/star/ucb/MissingInputStreamException.hpp"
#include "com/sun/star/ucb/MissingPropertiesException.hpp"
#include "com/sun/star/ucb/OpenCommandArgument2.hpp"
#include "com/sun/star/ucb/OpenMode.hpp"
#include "com/sun/star/ucb/UnsupportedCommandException.hpp"
#include "com/sun/star/ucb/UnsupportedDataSinkException.hpp"
#include "com/sun/star/ucb/UnsupportedOpenModeException.hpp"
#include "com/sun/star/ucb/XCommandEnvironment.hpp"
#include "com/sun/star/ucb/XCommandProcessor.hpp"
#include "com/sun/star/ucb/XContent.hpp"
#include "com/sun/star/ucb/XContentCreator.hpp"
#include "com/sun/star/ucb/XInteractionSupplyAuthentication.hpp"
#include "com/sun/star/ucb/XProgressHandler.hpp"
#include "com/sun/star/ucb/XSimpleFileAccess.hpp"
#include "com/sun/star/ui/ImageType.hpp"
#include "com/sun/star/ui/XImageManager.hpp"
#include "com/sun/star/ui/XModuleUIConfigurationManagerSupplier.hpp"
#include "com/sun/star/ui/XUIConfigurationManager.hpp"
#include "com/sun/star/ui/XUIConfigurationManagerSupplier.hpp"
#include "com/sun/star/ui/XUIConfigurationStorage.hpp"
#include "com/sun/star/ui/dialogs/ExtendedFilePickerElementIds.hpp"
#include "com/sun/star/ui/dialogs/TemplateDescription.hpp"
#include "com/sun/star/ui/dialogs/XExecutableDialog.hpp"
#include "com/sun/star/ui/dialogs/XFilePicker.hpp"
#include "com/sun/star/ui/dialogs/XFilePickerControlAccess.hpp"
#include "com/sun/star/ui/dialogs/XFolderPicker.hpp"
#include "com/sun/star/uno/Any.h"
#include "com/sun/star/uno/Reference.h"
#include "com/sun/star/uno/Sequence.hxx"
#include "com/sun/star/uno/TypeClass.hpp"
#include "com/sun/star/uno/XAggregation.hpp"
#include "com/sun/star/uno/XComponentContext.hpp"
#include "com/sun/star/uno/XInterface.hpp"
#include "com/sun/star/uno/XNamingService.hpp"
#include "com/sun/star/util/Date.hpp"
#include "com/sun/star/util/DateTime.hpp"
#include "com/sun/star/util/NumberFormat.hpp"
#include "com/sun/star/util/Time.hpp"
#include "com/sun/star/util/URL.hpp"
#include "com/sun/star/util/XCancellable.hpp"
#include "com/sun/star/util/XCloneable.hpp"
#include "com/sun/star/util/XCloseBroadcaster.hpp"
#include "com/sun/star/util/XCloseable.hpp"
#include "com/sun/star/util/XFlushable.hpp"
#include "com/sun/star/util/XModifiable.hpp"
#include "com/sun/star/util/XModifyBroadcaster.hpp"
#include "com/sun/star/util/XModifyListener.hpp"
#include "com/sun/star/util/XNumberFormatTypes.hpp"
#include "com/sun/star/util/XNumberFormatsSupplier.hpp"
#include "com/sun/star/util/XRefreshListener.hpp"
#include "com/sun/star/util/XRefreshable.hpp"
#include "com/sun/star/util/XURLTransformer.hpp"
#include "com/sun/star/util/XVeto.hpp"
#include "com/sun/star/view/XPrintable.hpp"
#include "com/sun/star/view/XSelectionSupplier.hpp"
#include "com/sun/star/view/XViewSettingsSupplier.hpp"
#include "com/sun/star/xml/sax/InputSource.hpp"
#include "com/sun/star/xml/sax/XDocumentHandler.hpp"
#include "com/sun/star/xml/sax/XParser.hpp"

#include "comphelper/basicio.hxx"
#include "comphelper/broadcasthelper.hxx"
#include "comphelper/componentcontext.hxx"
#include "comphelper/container.hxx"
#include "comphelper/documentconstants.hxx"
#include "comphelper/guarding.hxx"
#include "comphelper/mediadescriptor.hxx"
#include "comphelper/namecontainer.hxx"
#include "comphelper/namedvaluecollection.hxx"
#include "comphelper/processfactory.hxx"
#include "comphelper/propertycontainer.hxx"
#include "comphelper/sequence.hxx"
#include "comphelper/sequenceashashmap.hxx"
#include "comphelper/stl_types.hxx"
#include "comphelper/storagehelper.hxx"
#include "comphelper/streamsection.hxx"
#include "comphelper/types.hxx"

#include "connectivity/FValue.hxx"
#include <connectivity/DriversConfig.hxx>
#include "connectivity/dbcharset.hxx"
#include "connectivity/dbconversion.hxx"
#include "connectivity/dbexception.hxx"
#include "connectivity/dbmetadata.hxx"
#include "connectivity/sqlnode.hxx"
#include "connectivity/sqlparse.hxx"

#include "cppuhelper/exc_hlp.hxx"
#include "cppuhelper/factory.hxx"
#include "cppuhelper/implbase1.hxx"
#include "cppuhelper/interfacecontainer.h"
#include "cppuhelper/interfacecontainer.hxx"
#include "cppuhelper/propshlp.hxx"
#include "cppuhelper/queryinterface.hxx"
#include "cppuhelper/typeprovider.hxx"
#include "cppuhelper/weak.hxx"
#include "cppuhelper/weakref.hxx"


#include "i18npool/mslangid.hxx"

#include "osl/diagnose.h"
#include "osl/file.hxx"
#include "osl/getglobalmutex.hxx"
#include "osl/module.h"
#include "osl/mutex.hxx"
#include "osl/process.h"
#include "osl/thread.h"

#include "rtl/digest.h"
#include "rtl/logfile.hxx"
#include "rtl/memory.h"
#include "rtl/tencinfo.h"
#include "rtl/ustrbuf.hxx"
#include "rtl/ustring.hxx"
#include "rtl/uuid.h"

#include "sfx2/QuerySaveDocument.hxx"
#include "sfx2/cntids.hrc"
#include "sfx2/sfx.hrc"
#include "sfx2/sfxsids.hrc"
#include "sfx2/sfxuno.hxx"

#include "comphelper/classids.hxx"


#include "svl/cjkoptions.hxx"
#include "svl/filenotation.hxx"
#include "unotools/historyoptions.hxx"
#include "svtools/htmlkywd.hxx"
#include "svtools/imgdef.hxx"
#include "unotools/internaloptions.hxx"
#include "svtools/menuoptions.hxx"
#include "svtools/miscopt.hxx"
#include "svtools/rtfkeywd.hxx"
#include "svtools/rtftoken.h"
#include "vcl/solar.hrc"
#include "svtools/toolboxcontroller.hxx"
#include "unotools/viewoptions.hxx"

#include "svx/dataaccessdescriptor.hxx"
#include "svx/dbexch.hrc"
#include "svx/dialogs.hrc"
#include "svx/globlmn.hrc"
#include "svx/svxenum.hxx"
#include "svx/svxids.hrc"


#include "tools/diagnose_ex.h"

#include "typelib/typedescription.hxx"

#include "ucbhelper/cancelcommandexecution.hxx"
#include "ucbhelper/commandenvironment.hxx"
#include "ucbhelper/content.hxx"
#include "ucbhelper/contentbroker.hxx"
#include "ucbhelper/contentidentifier.hxx"
#include "ucbhelper/propertyvalueset.hxx"
#include "ucbhelper/providerhelper.hxx"
#include "ucbhelper/resultset.hxx"
#include "ucbhelper/resultsethelper.hxx"

#include "unotools/bootstrap.hxx"
#include "unotools/configmgr.hxx"
#include "unotools/confignode.hxx"
#include "unotools/eventlisteneradapter.hxx"
#include "unotools/processfactory.hxx"


#include "vos/mutex.hxx"
#include "vos/ref.hxx"
#include "vos/refernce.hxx"
#include "vos/thread.hxx"

#include "xmloff/ProgressBarHelper.hxx"
#include "xmloff/XMLConstantsPropertyHandler.hxx"
#include "xmloff/contextid.hxx"
#include "xmloff/families.hxx"
#include "xmloff/nmspmap.hxx"
#include "xmloff/xmlement.hxx"
#include "xmloff/xmlnmspe.hxx"
#include "xmloff/xmltoken.hxx"
#include "xmloff/xmltypes.hxx"

//---MARKER---

#endif


