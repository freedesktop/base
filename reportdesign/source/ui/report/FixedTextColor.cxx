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
#include "precompiled_reportdesign.hxx"

#include <FixedTextColor.hxx>
#include <com/sun/star/report/XFixedText.hpp>
#include <com/sun/star/awt/XVclWindowPeer.hpp>
#include <com/sun/star/awt/InvalidateStyle.hpp>

#include <RptObject.hxx>
#include <RptModel.hxx>
#include <RptPage.hxx>
#include <ViewsWindow.hxx>
#include <ReportSection.hxx>
#include <ReportController.hxx>
#include <uistrings.hrc>
#include <reportformula.hxx>
#include <toolkit/helper/property.hxx>

#include <tools/color.hxx> // COL_TRANSPARENT
#include <svtools/extcolorcfg.hxx>
#include <unotools/confignode.hxx>

// DBG_*
#include <tools/debug.hxx>
// DBG_UNHANDLED_EXCEPTION
#include <tools/diagnose_ex.h>

#include <vcl/svapp.hxx>
#include <vcl/settings.hxx>

namespace rptui
{
    using namespace ::com::sun::star;

    DBG_NAME(rpt_FixedTextColor)

    FixedTextColor::FixedTextColor(const OReportController& _aController)
            :m_rReportController(_aController)
    {
        DBG_CTOR(rpt_FixedTextColor, NULL);
    }

    //--------------------------------------------------------------------
    // sal_Int32 FixedTextColor::getTextColor()
    // {
    //     const StyleSettings& aStyleSettings = Application::GetSettings().GetStyleSettings();
    //     BOOL bHighContrast = aStyleSettings.GetHighContrastMode();
    //     
    //     Color aGetFaceColor = aStyleSettings.GetFaceColor();
    //     Color aGetCheckedColor = aStyleSettings.GetCheckedColor();
    //     Color aGetLightColor = aStyleSettings.GetLightColor();
    //     Color aGetLightBorderColor = aStyleSettings.GetLightBorderColor();
    //     Color aGetShadowColor = aStyleSettings.GetShadowColor();
    //     Color aGetDarkShadowColor = aStyleSettings.GetDarkShadowColor();
    //     Color aGetButtonTextColor = aStyleSettings.GetButtonTextColor();
    //     Color aGetButtonRolloverTextColor = aStyleSettings.GetButtonRolloverTextColor();
    //     Color aGetRadioCheckTextColor = aStyleSettings.GetRadioCheckTextColor();
    //     Color aGetGroupTextColor = aStyleSettings.GetGroupTextColor();
    //     Color aGetLabelTextColor = aStyleSettings.GetLabelTextColor();
    //     Color aGetInfoTextColor = aStyleSettings.GetInfoTextColor();
    //     Color aGetWindowColor = aStyleSettings.GetWindowColor();
    //     Color aGetWindowTextColor = aStyleSettings.GetWindowTextColor();
    //     Color aGetDialogColor = aStyleSettings.GetDialogColor();
    //     Color aGetDialogTextColor = aStyleSettings.GetDialogTextColor();
    //     Color aGetWorkspaceColor = aStyleSettings.GetWorkspaceColor();
    //     Color aGetFieldColor = aStyleSettings.GetFieldColor();
    //     Color aGetFieldTextColor = aStyleSettings.GetFieldTextColor();
    //     Color aGetFieldRolloverTextColor = aStyleSettings.GetFieldRolloverTextColor();
    //     Color aGetActiveColor = aStyleSettings.GetActiveColor();
    //     Color aGetActiveColor2 = aStyleSettings.GetActiveColor2();
    //     Color aGetActiveTextColor = aStyleSettings.GetActiveTextColor();
    //     Color aGetActiveBorderColor = aStyleSettings.GetActiveBorderColor();
    //     Color aGetDeactiveColor = aStyleSettings.GetDeactiveColor();
    //     Color aGetDeactiveColor2 = aStyleSettings.GetDeactiveColor2();
    //     Color aGetDeactiveTextColor = aStyleSettings.GetDeactiveTextColor();
    //     Color aGetDeactiveBorderColor = aStyleSettings.GetDeactiveBorderColor();
    //     Color aGetHighlightColor = aStyleSettings.GetHighlightColor();
    //     Color aGetHighlightTextColor = aStyleSettings.GetHighlightTextColor();
    //     Color aGetDisableColor = aStyleSettings.GetDisableColor();
    //     Color aGetHelpColor = aStyleSettings.GetHelpColor();
    //     Color aGetHelpTextColor = aStyleSettings.GetHelpTextColor();
    //     Color aGetMenuColor = aStyleSettings.GetMenuColor();
    //     Color aGetMenuBarColor = aStyleSettings.GetMenuBarColor();
    //     Color aGetMenuBorderColor = aStyleSettings.GetMenuBorderColor();
    //     Color aGetMenuTextColor = aStyleSettings.GetMenuTextColor();
    //     Color aGetMenuHighlightColor = aStyleSettings.GetMenuHighlightColor();
    //     Color aGetMenuHighlightTextColor = aStyleSettings.GetMenuHighlightTextColor();
    //     Color aGetLinkColor = aStyleSettings.GetLinkColor();
    //     Color aGetVisitedLinkColor = aStyleSettings.GetVisitedLinkColor();
    //     Color aGetHighlightLinkColor = aStyleSettings.GetHighlightLinkColor();
    //     Color aGetMonoColor = aStyleSettings.GetMonoColor();
    //     Color aGetActiveTabColor = aStyleSettings.GetActiveTabColor();
    //     Color aGetInactiveTabColor = aStyleSettings.GetInactiveTabColor();            
    // 
    //     Color aWindowColor = aStyleSettings.GetWindowColor();
    //     Color aLabelColor  = aStyleSettings.GetLabelTextColor();
    //     
    //     // if (m_nTextColor == -1)
    //     // {
    //     //    svtools::ExtendedColorConfig aConfig;
    //     //    m_nTextColor = aConfig.GetColorValue(CFG_REPORTDESIGNER, DBTEXTBOXBOUNDCONTENT).getColor();
    //     // }
    //     return aLabelColor.GetColor();
    // }
    
    //--------------------------------------------------------------------
    FixedTextColor::~FixedTextColor()
    {
        DBG_DTOR(rpt_FixedTextColor,NULL);
    }
    // -----------------------------------------------------------------------------
    
    void FixedTextColor::notifyPropertyChange( const beans::PropertyChangeEvent& _rEvent )
    {
        // (void)_rEvent;
        uno::Reference< report::XFixedText > xFixedText( _rEvent.Source, uno::UNO_QUERY );
        if ( ! xFixedText.is() )
        {
            return;
        }

        try
        {
            uno::Reference< lang::XComponent > xComponent( xFixedText, uno::UNO_QUERY_THROW );
            handle(xComponent);
            // uno::Reference<awt::XVclWindowPeer> xVclWindowPeer = getVclWindowPeer(xComponent);

            //     setPropertyTextColor(xVclWindowPeer, getTextColor());
        }
        catch (uno::Exception e)
        {
            DBG_UNHANDLED_EXCEPTION();
        }
    }
    
    // -----------------------------------------------------------------------------
    void FixedTextColor::setPropertyTextColor(const uno::Reference< awt::XVclWindowPeer >& _xVclWindowPeer, sal_Int32 _nTextColor)
    {
        _xVclWindowPeer->setProperty(PROPERTY_TEXTCOLOR, uno::makeAny(sal_Int32(_nTextColor)));
    }

    // -----------------------------------------------------------------------------
    void FixedTextColor::notifyElementInserted( const uno::Reference< uno::XInterface >& _rxElement )
    {
        handle(_rxElement);
    }
    
// -----------------------------------------------------------------------------
    void FixedTextColor::handle( const uno::Reference< uno::XInterface >& _rxElement )
    {
        // (void) _rxElement;
        uno::Reference< report::XFixedText > xFixedText( _rxElement, uno::UNO_QUERY );
        if ( ! xFixedText.is() )
        {
            return;
        }

        try
        {
            sal_Bool bIsDark = sal_False;
            const sal_Int32 nBackColor( xFixedText->getControlBackground() );
            if ((sal_uInt32)nBackColor == COL_TRANSPARENT)
            {                
                uno::Reference <report::XSection> xSection(xFixedText->getParent(), uno::UNO_QUERY_THROW);
                
                sal_Bool bSectionBackColorIsTransparent = xSection->getBackTransparent();
                if (bSectionBackColorIsTransparent)
                {
                    // Label Transparent, Section Transparent set LabelTextColor
                    const StyleSettings& aStyleSettings = Application::GetSettings().GetStyleSettings();
                    Color aWindowColor  = aStyleSettings.GetWindowColor();
                    bIsDark = aWindowColor.IsDark();
                }
                else
                {
                    com::sun::star::util::Color aColor2 = xSection->getBackColor();
                    Color aBackColor(aColor2);
                    bIsDark = aBackColor.IsDark();
                }
            }
            else
            {
                Color aLabelBackColor(nBackColor);
                bIsDark = aLabelBackColor.IsDark();
            }            
            
            uno::Reference<awt::XVclWindowPeer> xVclWindowPeer = getVclWindowPeer(xFixedText);
            if (bIsDark)
            {
                const StyleSettings& aStyleSettings = Application::GetSettings().GetStyleSettings();
                Color aLabelTextColor  = aStyleSettings.GetLabelTextColor();
                setPropertyTextColor(xVclWindowPeer, aLabelTextColor.GetColor());
            }
            else
            {
                util::Color aLabelColor = xFixedText->getCharColor();
                setPropertyTextColor(xVclWindowPeer, aLabelColor);
            }
            
        }
        catch( const uno::Exception& )
        {
            DBG_UNHANDLED_EXCEPTION();
        }
    }
    

// -----------------------------------------------------------------------------
    // XPropertyChangeListener
    uno::Reference<awt::XControl> FixedTextColor::getXControl(const uno::Reference< report::XFixedText >& _xFixedText) throw(uno::RuntimeException)
    {
            
        uno::Reference<awt::XControl> xControl;
        OReportController *pController = (OReportController *)&m_rReportController;
            
        ::boost::shared_ptr<OReportModel> pModel = pController->getSdrModel();
            
            uno::Reference<report::XSection> xSection(_xFixedText->getSection());
            if ( xSection.is() )
            {
                OReportPage *pPage = pModel->getPage(xSection);
                ULONG nIndex = pPage->getIndexOf(_xFixedText.get());
                if (nIndex < pPage->GetObjCount() )
                {
                    SdrObject *pObject = pPage->GetObj(nIndex);
                    OUnoObject* pUnoObj = dynamic_cast<OUnoObject*>(pObject);
                    if ( pUnoObj ) // this doesn't need to be done for shapes
                    {
                        ::boost::shared_ptr<OSectionWindow> pSectionWindow = pController->getSectionWindow(xSection);
                        if (pSectionWindow != NULL)
                        {
                            OReportSection& aOutputDevice = pSectionWindow->getReportSection(); // OutputDevice
                            OSectionView& aSdrView = aOutputDevice.getSectionView(); // SdrView
                            xControl = pUnoObj->GetUnoControl(aSdrView, aOutputDevice);
                        }
                    }
                }
            }
        return xControl;
    }
    
// -----------------------------------------------------------------------------
    uno::Reference<awt::XVclWindowPeer> FixedTextColor::getVclWindowPeer(const uno::Reference< report::XFixedText >& _xComponent) throw(uno::RuntimeException)
    {
        uno::Reference<awt::XVclWindowPeer> xVclWindowPeer;
        uno::Reference<awt::XControl> xControl = getXControl(_xComponent);

        xVclWindowPeer = uno::Reference<awt::XVclWindowPeer>( xControl->getPeer(), uno::UNO_QUERY);

        return xVclWindowPeer;
    }



    
}
