/******************************************************************************
 *
 * Copyright (C) 2022-2023 Maxim Integrated Products, Inc., All Rights Reserved.
 * (now owned by Analog Devices, Inc.)
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
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL MAXIM INTEGRATED BE LIABLE FOR ANY CLAIM, DAMAGES
 * OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * Except as contained in this notice, the name of Maxim Integrated
 * Products, Inc. shall not be used except as stated in the Maxim Integrated
 * Products, Inc. Branding Policy.
 *
 * The mere transfer of this software does not imply any licenses
 * of trade secrets, proprietary technology, copyrights, patents,
 * trademarks, maskwork rights, or any other form of intellectual
 * property whatsoever. Maxim Integrated Products, Inc. retains all
 * ownership rights.
 *
 ******************************************************************************
 *
 * Copyright 2023 Analog Devices, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 ******************************************************************************/

/* **** Includes **** */
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "mxc_errors.h"
#include "mxc_sys.h"
#include "trng.h"
#include "trng_reva.h"

/* **** MACROS **** */
#define WORD 3
#define BYTE 4

/* **** Functions **** */

// *********************************************************************
int MXC_TRNG_Init(void)
{
    MXC_SYS_ClockEnable(MXC_SYS_PERIPH_CLOCK_TRNG);

    return MXC_TRNG_RevA_Init();
}

// *********************************************************************
void MXC_TRNG_EnableInt(void)
{
    MXC_TRNG_RevA_EnableInt((mxc_trng_reva_regs_t *)MXC_TRNG);
}

// *********************************************************************
void MXC_TRNG_DisableInt(void)
{
    MXC_TRNG_RevA_DisableInt((mxc_trng_reva_regs_t *)MXC_TRNG);
}

// *********************************************************************
int MXC_TRNG_Shutdown(void)
{
    MXC_SYS_ClockEnable(MXC_SYS_PERIPH_CLOCK_TRNG);

    return MXC_TRNG_RevA_Shutdown();
}

// *********************************************************************
void MXC_TRNG_Handler(void)
{
    MXC_TRNG_RevA_Handler((mxc_trng_reva_regs_t *)MXC_TRNG);
}

// *********************************************************************
int MXC_TRNG_RandomInt(void)
{
    return MXC_TRNG_RevA_RandomInt((mxc_trng_reva_regs_t *)MXC_TRNG);
}

// *********************************************************************
int MXC_TRNG_Random(uint8_t *data, uint32_t len)
{
    return MXC_TRNG_RevA_Random(data, len);
}

// *********************************************************************
void MXC_TRNG_RandomAsync(uint8_t *data, uint32_t len, mxc_trng_complete_t callback)
{
    MXC_TRNG_RevA_RandomAsync((mxc_trng_reva_regs_t *)MXC_TRNG, data, len, callback);
}

// *********************************************************************
void MXC_TRNG_GenerateKey(void)
{
    MXC_TRNG_RevA_GenerateKey((mxc_trng_reva_regs_t *)MXC_TRNG);
}
