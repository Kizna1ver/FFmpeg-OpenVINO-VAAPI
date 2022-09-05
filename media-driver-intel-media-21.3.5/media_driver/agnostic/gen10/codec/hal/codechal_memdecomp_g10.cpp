/*
* Copyright (c) 2017, Intel Corporation
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
//! \file     codechal_memdecomp_g10.cpp
//! \brief    This module sets up a kernel for Gen10 media memory decompression.

#include "codechal_memdecomp_g10.h"
#ifndef _FULL_OPEN_SOURCE
#include "igcodeckrn_g10.h"
#endif

MediaMemDecompStateG10::MediaMemDecompStateG10():
    MediaMemDecompState()
{
     MHW_FUNCTION_ENTER;

#ifndef _FULL_OPEN_SOURCE
     m_kernelBase = (uint8_t *)IGCODECKRN_G10;
#else
     m_kernelBase = nullptr;
#endif
}

