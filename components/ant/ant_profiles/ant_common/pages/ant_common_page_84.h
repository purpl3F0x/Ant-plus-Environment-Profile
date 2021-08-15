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
#ifndef ANT_COMMON_PAGE_84_H__
#define ANT_COMMON_PAGE_84_H__

/** @file
 *
 * @defgroup ant_sdk_common_pages ANT+ common pages
 * @{
 * @ingroup ant_sdk_profiles
 * @brief This module implements functions for the ANT+ common pages.
 * @details  ANT+ common data pages define common data formats that can be used by any device on any ANT network. The ability to send and receive these common pages is defined by the transmission type of the ANT channel parameter.
 *
 * Note that all unused pages in this section are not defined and therefore cannot be used.
 * @}
 *
 * @defgroup ant_common_page_84 ANT+ common page 84
 * @{
 * @ingroup ant_sdk_common_pages
 */

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define ANT_COMMON_PAGE_84 (84) ///< @brief ID value of common page 84.

/**@brief Macros for converting to the units of the page 84 data field
 */
// ANT_COMMON_PAGE_84_SUBFIELD_TEMPERATURE (TEMP)      (uint16_t)  TEMP * 100u
// ANT_COMMON_PAGE_84_SUBFIELD_PRESSURE (PRESS)        (uint16_t)  PRESS * 100u
// ANT_COMMON_PAGE_84_SUBFIELD_HUMIDITY (HUM)          (uint16_t) HUM * 100u
// ANT_COMMON_PAGE_84_SUBFIELD_WIND_SPEED (SPEED)      (uint16_t) SPEED * 100u
// ANT_COMMON_PAGE_84_SUBFIELD_WIND_DIRECTION (DEGREES)(uint16_t) DEGREES* 20u
// ANT_COMMON_PAGE_84_SUBFIELD_CHARGE_CYCLES (CYCLES)  (uint16_t) CYCLES


/**@brief Common Page 84 Subfield Types.
 *
 * This enum represents possible subpage values for the common page 84.
 */
typedef enum
{
    COMMON_PAGE_84_SUBFIELD_TEMPERATURE         = 0,
    COMMON_PAGE_84_SUBFIELD_BAROMETRIC_PRESSURE = 1,
    COMMON_PAGE_84_SUBFIELD_HUMIDITY            = 2,
    COMMON_PAGE_84_SUBFIELD_WIND_SPEED          = 3,
    COMMON_PAGE_84_SUBFIELD_WIND_DIRECTION      = 4,
    COMMON_PAGE_84_SUBFIELD_CHARGING_CYCLES     = 5,
    COMMON_PAGE_84_SUBFIELD_MIN_TEMPERATURE     = 6,
    COMMON_PAGE_84_SUBFIELD_MAX_TEMPERATURE     = 7
} ant_common_page84_subpages_t;

/**@brief Data structure for ANT+ common data page 84.
 *
 * @note This structure implements only page 84 specific data.
 */
typedef struct
{
    uint8_t  subpage_1 ;        ///< Indicates the page value for data_field_1
    uint8_t  subpage_2;         ///< Indicates the page value for data_field_2 
    uint16_t data_field_1;      ///< Check docs for description
    uint16_t data_field_2;      ///< Check docs for description
} ant_common_page84_data_t;

/**@brief Initialize page 84.
 */
#define DEFAULT_ANT_COMMON_page84()     \
    (ant_common_page84_data_t)          \
    {                                   \
        .subpage_1     = 0x00,          \
        .subpage_2     = 0x00,          \
        .data_field_1  = 0x00,          \
        .data_field_2  = 0x00,          \
    }

/**@brief Initialize page 84.
 */
#define ANT_COMMON_page84(subpage_1, subpage_2, data_field_1, data_field_2)  \
    (ant_common_page84_data_t)                      \
    {                                               \
        .subpage_1     = (subpage_1),               \
        .subpage_2     = (subpage_2),               \
        .data_field_1  = (data_field_1),            \
        .data_field_2  = (data_field_2),            \
    }

/**@brief Function for encoding page 84.
 *
 * @param[in]  p_page_data      Pointer to the page data.
 * @param[out] p_page_buffer    Pointer to the data buffer.
 */
void ant_common_page_84_encode(uint8_t * p_page_buffer,
                               volatile ant_common_page84_data_t const * p_page_data);

/**@brief Function for decoding page 84.
 *
 * @param[in]  p_page_buffer    Pointer to the data buffer.
 * @param[out] p_page_data      Pointer to the page data.
 */
void ant_common_page_84_decode(uint8_t const * p_page_buffer,
                               volatile ant_common_page84_data_t * p_page_data);


#ifdef __cplusplus
}
#endif

#endif // ANT_COMMON_PAGE_84_H__
/** @} */
