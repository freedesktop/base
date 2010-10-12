/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
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

#include "opendoccontrols.hxx"

/** === begin UNO includes === **/
#include <com/sun/star/uno/Sequence.hxx>
#include <com/sun/star/beans/PropertyValue.hpp>
#include <com/sun/star/lang/XMultiServiceFactory.hpp>
#include <com/sun/star/container/XNameAccess.hpp>
#include <com/sun/star/ui/XModuleUIConfigurationManagerSupplier.hpp>
#include <com/sun/star/ui/XUIConfigurationManager.hpp>
#include <com/sun/star/graphic/XGraphic.hpp>
#include <com/sun/star/ui/XImageManager.hpp>
/** === end UNO includes === **/

#include <comphelper/processfactory.hxx>
#include <vcl/graph.hxx>
#include <vcl/help.hxx>
#include <unotools/historyoptions.hxx>
#include <comphelper/sequenceashashmap.hxx>
#include <tools/urlobj.hxx>
#include <svl/filenotation.hxx>

//........................................................................
namespace dbaui
{
//........................................................................

    namespace
    {
        using ::com::sun::star::uno::Reference;
        using ::com::sun::star::uno::Exception;
        using ::com::sun::star::uno::Sequence;
        using ::com::sun::star::uno::UNO_QUERY_THROW;
        using ::com::sun::star::container::XNameAccess;
        using ::com::sun::star::lang::XMultiServiceFactory;
        using ::com::sun::star::beans::PropertyValue;
        using ::com::sun::star::ui::XModuleUIConfigurationManagerSupplier;
        using ::com::sun::star::ui::XUIConfigurationManager;
        using ::com::sun::star::ui::XImageManager;
        using ::com::sun::star::graphic::XGraphic;

        String GetCommandText( const sal_Char* _pCommandURL, const ::rtl::OUString& _rModuleName )
        {
            ::rtl::OUString sLabel;
            if ( !_pCommandURL || !*_pCommandURL )
                return sLabel;

            Reference< XNameAccess > xUICommandLabels;
            ::rtl::OUString sCommandURL = ::rtl::OUString::createFromAscii( _pCommandURL );

            try
            {
                do
                {
                    // Retrieve popup menu labels
                    Reference< XMultiServiceFactory > xFactory( ::comphelper::getProcessServiceFactory() );
                    if ( !xFactory.is() )
                        break;

                    Reference< XNameAccess> xNameAccess;
                    xNameAccess = xNameAccess.query( xFactory->createInstance(
                        ::rtl::OUString( RTL_CONSTASCII_USTRINGPARAM( "com.sun.star.frame.UICommandDescription" ) )
                    ) );
                    if ( !xNameAccess.is() )
                        break;

                    xNameAccess->getByName( _rModuleName ) >>= xUICommandLabels;
                    if ( !xUICommandLabels.is() )
                        break;

                    Sequence< PropertyValue > aProperties;
                    if ( !( xUICommandLabels->getByName(sCommandURL) >>= aProperties ) )
                        break;

                    sal_Int32 nCount( aProperties.getLength() );
                    for ( sal_Int32 i=0; i<nCount; ++i )
                    {
                        ::rtl::OUString sPropertyName( aProperties[i].Name );
                        if ( sPropertyName.equalsAscii("Label" ) )
                        {
                            aProperties[i].Value >>= sLabel;
                            break;
                        }
                    }
                }
                while ( false );
            }
            catch( Exception& rException )
            {
                (void)rException;
            }

            return sLabel;
        }

        Image GetCommandIcon( const sal_Char* _pCommandURL, const ::rtl::OUString& _rModuleName )
        {
            Image aIcon;
            if ( !_pCommandURL || !*_pCommandURL )
                return aIcon;

            Reference< XNameAccess > xUICommandLabels;
            ::rtl::OUString sCommandURL = ::rtl::OUString::createFromAscii( _pCommandURL );
            try
            {
                do
                {
                    // Retrieve popup menu labels
                    Reference< XMultiServiceFactory> xFactory( ::comphelper::getProcessServiceFactory() );
                    if ( !xFactory.is() )
                        break;

                    Reference< XModuleUIConfigurationManagerSupplier > xSupplier(
                        xFactory->createInstance( ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM(
                            "com.sun.star.ui.ModuleUIConfigurationManagerSupplier" ) ) ),
                        UNO_QUERY_THROW );

                    Reference< XUIConfigurationManager > xManager( xSupplier->getUIConfigurationManager( _rModuleName ) );
                    Reference< XImageManager > xImageManager;
                    if ( xManager.is() )
                        xImageManager = xImageManager.query( xManager->getImageManager() );
                    if ( !xImageManager.is() )
                        break;

                    Sequence< ::rtl::OUString > aCommandList( &sCommandURL, 1 );
                    Sequence<Reference< XGraphic> > xIconList( xImageManager->getImages( 0, aCommandList ) );
                    if ( !xIconList.hasElements() )
                        break;

                    aIcon = Graphic( xIconList[0] ).GetBitmapEx();
                }
                while ( false );
            }
            catch ( Exception& rException )
            {
                (void)rException;
            }

            return aIcon;
        }


    }

    //====================================================================
    //= OpenButton
    //====================================================================
    //--------------------------------------------------------------------
    OpenDocumentButton::OpenDocumentButton( Window* _pParent, const sal_Char* _pAsciiModuleName, const ResId& _rResId )
        :PushButton( _pParent, _rResId )
    {
        impl_init( _pAsciiModuleName );
    }

    //--------------------------------------------------------------------
    void OpenDocumentButton::impl_init( const sal_Char* _pAsciiModuleName )
    {
        DBG_ASSERT( _pAsciiModuleName, "OpenDocumentButton::impl_init: invalid module name!" );
        m_sModule = ::rtl::OUString::createFromAscii( _pAsciiModuleName );

        // our label should equal the UI text of the "Open" command
        String sLabel( GetCommandText( ".uno:Open", m_sModule ) );
        sLabel.SearchAndReplaceAllAscii( "~", String() );
        sLabel.Insert( (sal_Unicode)' ', 0 );
        SetText( sLabel );

        // Place icon left of text and both centered in the button.
        SetModeImage( GetCommandIcon( ".uno:Open", m_sModule ), BMP_COLOR_NORMAL );
        EnableImageDisplay( TRUE );
        EnableTextDisplay( TRUE );
        SetImageAlign( IMAGEALIGN_LEFT );
        SetStyle( GetStyle() | WB_CENTER );
    }

    //====================================================================
    //= OpenDocumentListBox
    //====================================================================
    //--------------------------------------------------------------------
    OpenDocumentListBox::OpenDocumentListBox( Window* _pParent, const sal_Char* _pAsciiModuleName, const ResId& _rResId )
        :ListBox( _pParent, _rResId )
    {
        impl_init( _pAsciiModuleName );
    }

    //--------------------------------------------------------------------
    void OpenDocumentListBox::impl_init( const sal_Char* _pAsciiModuleName )
    {
        DBG_ASSERT( _pAsciiModuleName, "OpenDocumentListBox::impl_init: invalid module name!" );

        Sequence< Sequence< PropertyValue> > aHistory = SvtHistoryOptions().GetList( ePICKLIST );
        Reference< XNameAccess > xFilterFactory;
        xFilterFactory = xFilterFactory.query( ::comphelper::getProcessServiceFactory()->createInstance(
            ::rtl::OUString( RTL_CONSTASCII_USTRINGPARAM( "com.sun.star.document.FilterFactory" ) ) ) );

        sal_uInt32 nCount = aHistory.getLength();
        for ( sal_uInt32 nItem = 0; nItem < nCount; ++nItem )
        {
            try
            {
                //  Get the current history item's properties.
                ::comphelper::SequenceAsHashMap aItemProperties( aHistory[ nItem ] );
                ::rtl::OUString sURL = aItemProperties.getUnpackedValueOrDefault( HISTORY_PROPERTYNAME_URL, ::rtl::OUString() );
                ::rtl::OUString sFilter = aItemProperties.getUnpackedValueOrDefault( HISTORY_PROPERTYNAME_FILTER, ::rtl::OUString() );
                String          sTitle = aItemProperties.getUnpackedValueOrDefault( HISTORY_PROPERTYNAME_TITLE, ::rtl::OUString() );
                ::rtl::OUString sPassword = aItemProperties.getUnpackedValueOrDefault( HISTORY_PROPERTYNAME_PASSWORD, ::rtl::OUString() );

                //  If the entry is an impress file then insert it into the
                //  history list and the list box.
                Sequence< PropertyValue > aProps;
                xFilterFactory->getByName( sFilter ) >>= aProps;

                ::comphelper::SequenceAsHashMap aFilterProperties( aProps );
                ::rtl::OUString sDocumentService = aFilterProperties.getUnpackedValueOrDefault(
                    ::rtl::OUString( RTL_CONSTASCII_USTRINGPARAM( "DocumentService" ) ), ::rtl::OUString() );
                if ( sDocumentService.equalsAscii( _pAsciiModuleName ) )
                {
                    // yes, it's a Base document
                    INetURLObject aURL;
                    aURL.SetSmartURL( sURL );
                    // The password is set only when it is not empty.
                    if ( sPassword.getLength() > 0 )
                        aURL.SetPass( sPassword );

                    if ( !sTitle.Len() )
                        sTitle = aURL.getBase( INetURLObject::LAST_SEGMENT, true, INetURLObject::DECODE_UNAMBIGUOUS );

                    String sDecodedURL = aURL.GetMainURL( INetURLObject::NO_DECODE );

                    USHORT nPos = InsertEntry( sTitle );
                    m_aURLs.insert( MapIndexToStringPair::value_type( nPos, StringPair( sDecodedURL, sFilter ) ) );
                }
            }
            catch( Exception& rException )
            {
                (void)rException;
            }
        }
    }

    //--------------------------------------------------------------------
    String OpenDocumentListBox::GetSelectedDocumentURL() const
    {
        String sURL;
        USHORT nSelected = GetSelectEntryPos();
        if ( LISTBOX_ENTRY_NOTFOUND != GetSelectEntryPos() )
            sURL = impl_getDocumentAtIndex( nSelected ).first;
        return sURL;
    }

    //--------------------------------------------------------------------
    String OpenDocumentListBox::GetSelectedDocumentFilter() const
    {
        String sFilter;
        USHORT nSelected = GetSelectEntryPos();
        if ( LISTBOX_ENTRY_NOTFOUND != GetSelectEntryPos() )
            sFilter = impl_getDocumentAtIndex( nSelected ).second;
        return sFilter;
    }

    //--------------------------------------------------------------------
    OpenDocumentListBox::StringPair OpenDocumentListBox::impl_getDocumentAtIndex( USHORT _nListIndex, bool _bSystemNotation ) const
    {
        MapIndexToStringPair::const_iterator pos = m_aURLs.find( _nListIndex );
        DBG_ASSERT( pos != m_aURLs.end(), "OpenDocumentListBox::impl_getDocumentAtIndex: invalid index!" );

        StringPair aDocumentDescriptor;
        if ( pos != m_aURLs.end() )
        {
            aDocumentDescriptor = pos->second;
            if ( _bSystemNotation && aDocumentDescriptor.first.Len() )
            {
                ::svt::OFileNotation aNotation( aDocumentDescriptor.first );
                aDocumentDescriptor.first = aNotation.get( ::svt::OFileNotation::N_SYSTEM );
            }
        }
        return aDocumentDescriptor;
    }

    //--------------------------------------------------------------------
    void  OpenDocumentListBox::RequestHelp( const HelpEvent& _rHEvt )
    {
        if( !( _rHEvt.GetMode() & HELPMODE_QUICK ) )
            return;
        if ( !IsEnabled() )
            return;

        Point aRequestPos( ScreenToOutputPixel( _rHEvt.GetMousePosPixel() ) );
        USHORT nItemIndex = LISTBOX_ENTRY_NOTFOUND;
        if ( GetIndexForPoint( aRequestPos, nItemIndex ) != -1 )
        {
            Rectangle aItemRect( GetBoundingRectangle( nItemIndex ) );
            aItemRect = Rectangle(
                OutputToScreenPixel( aItemRect.TopLeft() ),
                OutputToScreenPixel( aItemRect.BottomRight() ) );
            String sHelpText = impl_getDocumentAtIndex( nItemIndex, true ).first;
            Help::ShowQuickHelp( this, aItemRect, sHelpText, QUICKHELP_LEFT | QUICKHELP_VCENTER );
        }
    }

//........................................................................
} // namespace dbaui
//........................................................................

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
