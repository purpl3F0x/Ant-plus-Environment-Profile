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
#if NRF_MODULE_ENABLED(ANT_COMMON_PAGE_84)

#include <string.h>
#include "ant_common_page_84.h"

#define NRF_LOG_MODULE_NAME ant_common_page_84
#if ANT_COMMON_PAGE_84_LOG_ENABLED
#define NRF_LOG_LEVEL       ANT_COMMON_PAGE_84_LOG_LEVEL
#define NRF_LOG_INFO_COLOR  ANT_COMMON_PAGE_84_INFO_COLOR
#else // ANT_COMMON_PAGE_84_LOG_ENABLED
#define NRF_LOG_LEVEL       0
#endif // ANT_COMMON_PAGE_84_LOG_ENABLED
#include "nrf_log.h"
NRF_LOG_MODULE_REGISTER();

/**@brief ant+ common page 84 data layout structure. */
typedef struct
{
    uint8_t  reserved;
    uint8_t  subpage_1;
    uint8_t  subpage_2;
    uint8_t data_field_1[2];      
    uint8_t data_field_2[2];
}ant_common_page84_data_layout_t;


/**@brief Function for tracing page 84 data.
 *
 * @param[in]  p_page_data      Pointer to the page 84 data.
 */
static void page84_data_log(volatile ant_common_page84_data_t const * p_page_data)
{   
    switch (p_page_data->subpage_1) {
        case COMMON_PAGE_84_SUBFIELD_TEMPERATURE:
            NRF_LOG_INFO("System Temperature:      " NRF_LOG_FLOAT_MARKER "ºC", NRF_LOG_FLOAT(p_page_data->data_field_1 / 100.0));
            break;
        case COMMON_PAGE_84_SUBFIELD_BAROMETRIC_PRESSURE:
            NRF_LOG_INFO("Barometric Pressure:      " NRF_LOG_FLOAT_MARKER "kPa", NRF_LOG_FLOAT(p_page_data->data_field_1 / 100.0));
            break;
        case COMMON_PAGE_84_SUBFIELD_HUMIDITY:
            NRF_LOG_INFO("Hummidity:                " NRF_LOG_FLOAT_MARKER "%%", NRF_LOG_FLOAT(p_page_data->data_field_1 / 100.0));
            break;
        case COMMON_PAGE_84_SUBFIELD_WIND_DIRECTION:
            NRF_LOG_INFO("Wind Speed:               " NRF_LOG_FLOAT_MARKER "km/h", NRF_LOG_FLOAT(p_page_data->data_field_1 / 20));
            break;
        case COMMON_PAGE_84_SUBFIELD_WIND_SPEED:
            NRF_LOG_INFO("Wind Direction:           " NRF_LOG_FLOAT_MARKER "º", NRF_LOG_FLOAT(p_page_data->data_field_1 / 100.0));
            break;
        case COMMON_PAGE_84_SUBFIELD_CHARGING_CYCLES:
            NRF_LOG_INFO("Charging Cycles:          %u cycles", (unsigned int) p_page_data->data_field_1);
            break;
        case COMMON_PAGE_84_SUBFIELD_MAX_TEMPERATURE:
            NRF_LOG_INFO("Max System Temperature:   " NRF_LOG_FLOAT_MARKER "ºC", NRF_LOG_FLOAT(p_page_data->data_field_1 / 100.0));
            break;
        case COMMON_PAGE_84_SUBFIELD_MIN_TEMPERATURE:
            NRF_LOG_INFO("Min System Temperature:   " NRF_LOG_FLOAT_MARKER "ºC", NRF_LOG_FLOAT(p_page_data->data_field_1 / 100.0));
            break;
    }

    switch (p_page_data->subpage_2) {
        case COMMON_PAGE_84_SUBFIELD_TEMPERATURE:
            NRF_LOG_INFO("System Temperature:       " NRF_LOG_FLOAT_MARKER "ºC\r\n\n", NRF_LOG_FLOAT(p_page_data->data_field_2 / 100.0));
            break;
        case COMMON_PAGE_84_SUBFIELD_BAROMETRIC_PRESSURE:
            NRF_LOG_INFO("Barometric Pressure:      " NRF_LOG_FLOAT_MARKER "kPa\r\n\n", NRF_LOG_FLOAT(p_page_data->data_field_2 / 100.0));
            break;
        case COMMON_PAGE_84_SUBFIELD_HUMIDITY:
            NRF_LOG_INFO("Hummidity:                " NRF_LOG_FLOAT_MARKER "%%\r\n\n", NRF_LOG_FLOAT(p_page_data->data_field_2 / 100.0));
            break;
        case COMMON_PAGE_84_SUBFIELD_WIND_DIRECTION:
            NRF_LOG_INFO("Wind Speed:               " NRF_LOG_FLOAT_MARKER "km/h\r\n\n", NRF_LOG_FLOAT(p_page_data->data_field_2 / 20));
            break;
        case COMMON_PAGE_84_SUBFIELD_WIND_SPEED:
            NRF_LOG_INFO("Wind Direction:           " NRF_LOG_FLOAT_MARKER "º\r\n\n", NRF_LOG_FLOAT(p_page_data->data_field_2 / 100.0));
            break;
        case COMMON_PAGE_84_SUBFIELD_CHARGING_CYCLES:
            NRF_LOG_INFO("Charging Cycles:          %u cycles\r\n\n", (unsigned int) p_page_data->data_field_2);
            break;
        case COMMON_PAGE_84_SUBFIELD_MAX_TEMPERATURE:
            NRF_LOG_INFO("Max System Temperature:   " NRF_LOG_FLOAT_MARKER "ºC\r\n\n", NRF_LOG_FLOAT(p_page_data->data_field_2 / 100.0));
            break;
        case COMMON_PAGE_84_SUBFIELD_MIN_TEMPERATURE:
            NRF_LOG_INFO("Min System Temperature:   " NRF_LOG_FLOAT_MARKER "ºC\r\n\n", NRF_LOG_FLOAT(p_page_data->data_field_2 / 100.0));
            break;
    }
}


void ant_common_page_84_encode(uint8_t                                 * p_page_buffer,
                               volatile ant_common_page84_data_t const * p_page_data)
{
    ant_common_page84_data_layout_t * p_outcoming_data =
        (ant_common_page84_data_layout_t *)p_page_buffer;

    p_outcoming_data->reserved = UINT8_MAX;
    p_outcoming_data->subpage_1 = p_page_data->subpage_1;
    p_outcoming_data->subpage_2 = p_page_data->subpage_2;

    UNUSED_PARAMETER(uint16_encode(p_page_data->data_field_1, p_outcoming_data->data_field_1));
    UNUSED_PARAMETER(uint16_encode(p_page_data->data_field_2, p_outcoming_data->data_field_2));

    page84_data_log(p_page_data);
}


//void ant_common_page_84_decode(uint8_t const                     * p_page_buffer,
//                               volatile ant_common_page84_data_t * p_page_data)
//{
//    ant_common_page84_data_layout_t const * p_incoming_data =
//        (ant_common_page84_data_layout_t *)p_page_buffer;

//    p_page_data->hw_revision = p_incoming_data->hw_revision;

//    p_page_data->manufacturer_id = uint16_decode(p_incoming_data->manufacturer_id);
//    p_page_data->model_number    = uint16_decode(p_incoming_data->model_number);

//    page84_data_log(p_page_data);
//}

#endif // NRF_MODULE_ENABLED(ANT_COMMON_PAGE_84)
