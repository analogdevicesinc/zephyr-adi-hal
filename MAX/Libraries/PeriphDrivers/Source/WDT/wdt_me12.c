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
#include "mxc_device.h"
#include "mxc_errors.h"
#include "mxc_assert.h"
#include "mxc_sys.h"
#include "wdt.h"
#include "wdt_revb.h"

/* **** Functions **** */

int MXC_WDT_Init(mxc_wdt_regs_t *wdt, mxc_wdt_cfg_t *cfg)
{
#ifndef MSDK_NO_GPIO_CLK_INIT
    if (wdt == MXC_WDT) {
        MXC_SYS_ClockEnable(MXC_SYS_PERIPH_CLOCK_WDT);
    } else {
        return E_BAD_PARAM;
    }
#endif

    MXC_WDT_RevB_Init((mxc_wdt_revb_regs_t *)wdt, (mxc_wdt_revb_cfg_t *)cfg);

    return E_NO_ERROR;
}

int MXC_WDT_Shutdown(mxc_wdt_regs_t *wdt)
{
    if (wdt == MXC_WDT) {
        MXC_SYS_ClockDisable(MXC_SYS_PERIPH_CLOCK_WDT);
    } else {
        return E_BAD_PARAM;
    }

    return E_NO_ERROR;
}

void MXC_WDT_SetIntPeriod(mxc_wdt_regs_t *wdt, mxc_wdt_cfg_t *cfg)
{
    MXC_WDT_RevB_SetIntPeriod((mxc_wdt_revb_regs_t *)wdt, (mxc_wdt_revb_cfg_t *)cfg);
}

void MXC_WDT_SetResetPeriod(mxc_wdt_regs_t *wdt, mxc_wdt_cfg_t *cfg)
{
    MXC_WDT_RevB_SetResetPeriod((mxc_wdt_revb_regs_t *)wdt, (mxc_wdt_revb_cfg_t *)cfg);
}

void MXC_WDT_Enable(mxc_wdt_regs_t *wdt)
{
    // ME12 requires the special sequence below
    // to set the MXC_F_WDT_CTRL_EN bit.  The
    // bit cannot be set directly.
    __disable_irq();
    wdt->rst = 0xFE;
    wdt->rst = 0XED;
    __enable_irq();
}

void MXC_WDT_Disable(mxc_wdt_regs_t *wdt)
{
    // ME12 requires the special sequence below
    // to unset the MXC_F_WDT_CTRL_EN bit.  The
    // bit cannot be unset directly.
    __disable_irq();
    wdt->rst = 0xDE;
    wdt->rst = 0XAD;
    __enable_irq();
}

void MXC_WDT_EnableInt(mxc_wdt_regs_t *wdt)
{
    MXC_WDT_RevB_EnableInt((mxc_wdt_revb_regs_t *)wdt, MXC_WDT_REVB_ENABLE);
}

void MXC_WDT_DisableInt(mxc_wdt_regs_t *wdt)
{
    MXC_WDT_RevB_EnableInt((mxc_wdt_revb_regs_t *)wdt, MXC_WDT_REVB_DISABLE);
}

void MXC_WDT_EnableReset(mxc_wdt_regs_t *wdt)
{
    MXC_WDT_RevB_EnableReset((mxc_wdt_revb_regs_t *)wdt, MXC_WDT_REVB_ENABLE);
}

void MXC_WDT_DisableReset(mxc_wdt_regs_t *wdt)
{
    MXC_WDT_RevB_EnableReset((mxc_wdt_revb_regs_t *)wdt, MXC_WDT_REVB_DISABLE);
}

void MXC_WDT_ResetTimer(mxc_wdt_regs_t *wdt)
{
    __disable_irq();
    MXC_WDT_RevB_ResetTimer((mxc_wdt_revb_regs_t *)wdt);
    __enable_irq();
}

int MXC_WDT_GetResetFlag(mxc_wdt_regs_t *wdt)
{
    return MXC_WDT_RevB_GetResetFlag((mxc_wdt_revb_regs_t *)wdt);
}

void MXC_WDT_ClearResetFlag(mxc_wdt_regs_t *wdt)
{
    MXC_WDT_RevB_ClearResetFlag((mxc_wdt_revb_regs_t *)wdt);
}

int MXC_WDT_GetIntFlag(mxc_wdt_regs_t *wdt)
{
    return MXC_WDT_RevB_GetIntFlag((mxc_wdt_revb_regs_t *)wdt);
}

void MXC_WDT_ClearIntFlag(mxc_wdt_regs_t *wdt)
{
    MXC_WDT_RevB_ClearIntFlag((mxc_wdt_revb_regs_t *)wdt);
}
