/*
* Copyright (c) 2019, Intel Corporation
*
* Permission is hereby granted, free of charge, to any person obtaining a
* copy of this software and associated documentation files (the "Software"),
* to deal in the Software without restriction, including without limitation
* the rights to use, copy, modify, merge, publish, distribute, sublicense,
* and/or sell copies of the Software, and to permit persons to whom the
* Software is furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included
* in all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
* OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
* THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR
* OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
* ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
* OTHER DEALINGS IN THE SOFTWARE.
*/
//!
//! \file      decodecp_interface.cpp
//! \brief     Stub file for decodecp interface
//!

#include "decodecp_interface.h"
#include "cp_interfaces.h"

static void DecodeCpStubMessage()
{
    MOS_NORMALMESSAGE(MOS_COMPONENT_CP, MOS_CP_SUBCOMP_CODEC, "This function is stubbed as CP is not enabled.");
}

DecodeCpInterface *Create_DecodeCpInterface(
    CodechalSetting *    codechalSettings,
    CodechalHwInterface *hwInterfaceInput)
{
    if (nullptr == codechalSettings || nullptr == hwInterfaceInput)
    {
        MOS_NORMALMESSAGE(MOS_COMPONENT_CP, MOS_CP_SUBCOMP_CODEC, "NULL pointer parameters");
        return nullptr;
    }

    DecodeCpInterface *pInterface = nullptr;
    CpInterfaces *cp_interface = CpInterfacesFactory::Create(CP_INTERFACE);
    if (cp_interface)
    {
        pInterface = cp_interface->Create_DecodeCpInterface(codechalSettings, hwInterfaceInput);
        MOS_Delete(cp_interface);
    }

    if (nullptr == pInterface) DecodeCpStubMessage();

    return pInterface;
}

void Delete_DecodeCpInterface(DecodeCpInterface *pInterface)
{
    CpInterfaces *cp_interface = CpInterfacesFactory::Create(CP_INTERFACE);
    if (pInterface != nullptr && cp_interface != nullptr)
    {
        cp_interface->Delete_DecodeCpInterface(pInterface);
        pInterface = nullptr;
    }
    MOS_Delete(pInterface);
    MOS_Delete(cp_interface);
}
