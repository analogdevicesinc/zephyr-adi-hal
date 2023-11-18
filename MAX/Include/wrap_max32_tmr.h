/******************************************************************************
 *
 * Copyright (C) 2023 Analog Devices, Inc.
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

#ifndef _WRAP_MAX32_TMR_H_
#define _WRAP_MAX32_TMR_H_

/***** Includes *****/
#include <tmr.h>

#ifdef __cplusplus
extern "C" {
#endif


typedef struct {
    mxc_tmr_pres_t pres; 
    mxc_tmr_mode_t mode; 
    int bitMode; /* Some PN does not support it, check mxc_tmr_bit_mode_t in tmr.h file */
    int clock; /* Some PN does not support it, check mxc_tmr_clock_t in tmr.h file */
    uint32_t cmp_cnt; /**< Compare register value in timer ticks */
    unsigned pol; /**< Polarity (0 or 1) */
} wrap_mxc_tmr_cfg_t;

/*
 *  MAX32665, MAX32666 related mapping
 */
#if defined(CONFIG_SOC_MAX32665) || (CONFIG_SOC_MAX32666)

static inline int Wrap_MXC_TMR_Init(mxc_tmr_regs_t *tmr, wrap_mxc_tmr_cfg_t *cfg)
{
    mxc_tmr_cfg_t mxc_cfg;

    mxc_cfg.pres = cfg->pres;
    mxc_cfg.mode = cfg->mode;
    mxc_cfg.cmp_cnt = cfg->cmp_cnt;
    mxc_cfg.pol = cfg->pol;

    MXC_TMR_Init(tmr, &mxc_cfg);
    return 0;
}

static inline int Wrap_MXC_TMR_GetClockIndex(int z_clock)
{
    if (z_clock == 0) {
        /* Only peripheral clock is supported, just retunr 0 */
        return 0;
    } else {
        return -1; /* Not supported */
    }
}

/*
 *  MAX32690, MAX32655 related mapping
 */
#elif defined(CONFIG_SOC_MAX32690) || (CONFIG_SOC_MAX32655)

static inline int Wrap_MXC_TMR_Init(mxc_tmr_regs_t *tmr, wrap_mxc_tmr_cfg_t *cfg)
{
    mxc_tmr_cfg_t mxc_cfg;

    mxc_cfg.pres = cfg->pres;
    mxc_cfg.mode = cfg->mode;
    mxc_cfg.cmp_cnt = cfg->cmp_cnt;
    mxc_cfg.pol = cfg->pol;
    mxc_cfg.bitMode = (mxc_tmr_bit_mode_t) cfg->bitMode;
    mxc_cfg.clock = (mxc_tmr_clock_t) cfg->clock;
    
    return  MXC_TMR_Init(tmr, &mxc_cfg, 0); // init_pins not used
}

static inline int Wrap_MXC_TMR_GetClockIndex(int z_clock)
{
    switch (z_clock) {
    case 0: // ADI_MAX32_PRPH_CLK_SRC_PCLK
        return MXC_TMR_APB_CLK;
    case 1: // ADI_MAX32_PRPH_CLK_SRC_EXTCLK
        return MXC_TMR_EXT_CLK;
    case 2: // ADI_MAX32_PRPH_CLK_SRC_IBRO
        return MXC_TMR_8M_CLK;
    case 3: //ADI_MAX32_PRPH_CLK_SRC_ERFO
        return MXC_TMR_32M_CLK;
    case 4: //ADI_MAX32_PRPH_CLK_SRC_ERTCO
        return MXC_TMR_32K_CLK;
    case 5: //ADI_MAX32_PRPH_CLK_SRC_INRO
        return MXC_TMR_8K_CLK;
#if defined(CONFIG_SOC_MAX32690)
    case 6: //ADI_MAX32_PRPH_CLK_SRC_ISO
        return MXC_TMR_60M_CLK;
#endif
    }

    return -1; /* Not supported */
}

#endif  // part number


#ifdef __cplusplus
}
#endif

#endif // _WRAP_MAX32_TMR_H_
