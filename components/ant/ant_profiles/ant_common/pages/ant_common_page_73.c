/**
 * Copyright (c) 2015 - 2020, Nordic Semiconductor ASA
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form, except as embedded into a Nordic
 *    Semiconductor ASA integrated circuit in a product or a software update for
 *    such product, must reproduce the above copyright notice, this list of
 *    conditions and the following disclaimer in the documentation and/or other
 *    materials provided with the distribution.
 *
 * 3. Neither the name of Nordic Semiconductor ASA nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * 4. This software, with or without modification, must only be used with a
 *    Nordic Semiconductor ASA integrated circuit.
 *
 * 5. Any software provided in binary form under this license must not be reverse
 *    engineered, decompiled, modified and/or disassembled.
 *
 * THIS SOFTWARE IS PROVIDED BY NORDIC SEMICONDUCTOR ASA "AS IS" AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY, NONINFRINGEMENT, AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL NORDIC SEMICONDUCTOR ASA OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */
#include "sdk_common.h"
#if NRF_MODULE_ENABLED(ANT_COMMON_PAGE_73)

#include <string.h>
#include "ant_common_page_73.h"

#define NRF_LOG_MODULE_NAME ant_common_page_73
#if ANT_COMMON_PAGE_73_LOG_ENABLED
#define NRF_LOG_LEVEL       ANT_COMMON_PAGE_73_LOG_LEVEL
#define NRF_LOG_INFO_COLOR  ANT_COMMON_PAGE_73_INFO_COLOR
#else // ANT_COMMON_PAGE_73_LOG_ENABLED
#define NRF_LOG_LEVEL       0
#endif // ANT_COMMON_PAGE_73_LOG_ENABLED
#include "nrf_log.h"
NRF_LOG_MODULE_REGISTER();

/**@brief ANT+ common page 73 data layout structure. */
typedef struct
{
    uint8_t slave_serial_number[2];
    uint8_t manufacturer_id[2];
    uint8_t sequence;
    uint8_t command_number[2];       
}ant_common_page73_data_layout_t;

/**@brief Function for tracing page 73 data.
 *
 * @param[in]  p_page_data      Pointer to the page 73 data.
 */
static void page73_data_log(volatile ant_common_page73_data_t const * p_page_data)
{
    NRF_LOG_INFO("Device %u, Manufucturer ID: %u", p_page_data->slave_serial_number, p_page_data->manufacturer_id);
    NRF_LOG_INFO("Sequence #%u", p_page_data->sequence);
    NRF_LOG_INFO("Command Number: %u", p_page_data->command_number);
}


void ant_common_page_73_encode(uint8_t                                 * p_page_buffer,
                               volatile ant_common_page73_data_t const * p_page_data)
{
    // TODO: ...

    page73_data_log(p_page_data);
}


void ant_common_page_73_decode(uint8_t const                     * p_page_buffer,
                               volatile ant_common_page73_data_t * p_page_data)
{
    ant_common_page73_data_layout_t const * p_incoming_data =
        (ant_common_page73_data_layout_t *)p_page_buffer;

    p_page_data->slave_serial_number = uint16_decode(p_incoming_data->slave_serial_number);
    p_page_data->manufacturer_id     = uint16_decode(p_incoming_data->manufacturer_id);
    p_page_data->sequence            = p_incoming_data->sequence;
    p_page_data->command_number      = uint16_decode(p_incoming_data->command_number);

    page73_data_log(p_page_data);
}

#endif // NRF_MODULE_ENABLED(ANT_COMMON_PAGE_73)
