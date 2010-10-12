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

#include <cppuhelper/factory.hxx>
#include <osl/diagnose.h>
#include "Acomponentmodule.hxx"


/********************************************************************************************/

using namespace ::rtl;
using namespace ::adabasui;
using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::lang;
using namespace ::com::sun::star::registry;

//***************************************************************************************
//
// registry functions
extern "C" void SAL_CALL createRegistryInfo_OAdabasCreateDialog();

//***************************************************************************************
extern "C" void SAL_CALL createRegistryInfo_adabasui()
{
    static sal_Bool bInit = sal_False;
    if (!bInit)
    {
        createRegistryInfo_OAdabasCreateDialog();
        ::adabasui::OModule::setResourceFilePrefix("adabasui");
        bInit = sal_True;
    }
}

//---------------------------------------------------------------------------------------

extern "C" SAL_DLLPUBLIC_EXPORT void SAL_CALL
component_getImplementationEnvironment(
                const sal_Char	**ppEnvTypeName,
                uno_Environment	**
            )
{
    createRegistryInfo_adabasui();
    *ppEnvTypeName = CPPU_CURRENT_LANGUAGE_BINDING_NAME;
}

//---------------------------------------------------------------------------------------
extern "C" SAL_DLLPUBLIC_EXPORT sal_Bool SAL_CALL component_writeInfo(
                void* pServiceManager,
                void* pRegistryKey
            )
{
    if (pRegistryKey) 
    try 
    {
        return OModule::writeComponentInfos(
            static_cast<XMultiServiceFactory*>(pServiceManager),
            static_cast<XRegistryKey*>(pRegistryKey));
    }
    catch (InvalidRegistryException& )
    {
        OSL_ASSERT("DBA::component_writeInfo : could not create a registry key ! ## InvalidRegistryException !");
    }

    return sal_False;
}

//---------------------------------------------------------------------------------------
extern "C" SAL_DLLPUBLIC_EXPORT void* SAL_CALL component_getFactory(
                    const sal_Char* pImplementationName,
                    void* pServiceManager,
                    void* /*pRegistryKey*/)
{
    Reference< XInterface > xRet;
    if (pServiceManager && pImplementationName)
    {
        xRet = OModule::getComponentFactory(
            ::rtl::OUString::createFromAscii(pImplementationName),
            static_cast< XMultiServiceFactory* >(pServiceManager));
    }

    if (xRet.is())
        xRet->acquire();
    return xRet.get();
};

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
