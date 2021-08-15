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
#ifndef ANT_COMMON_PAGE_73_H__
#define ANT_COMMON_PAGE_73_H__

/** @file
 *
 * @defgroup ant_common_page_73 ANT+ common page 73
 * @{
 * @ingroup ant_sdk_common_pages
 */

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define ANT_COMMON_PAGE_73              (73)        ///< @brief ID value of common page 73.


/**@brief Data structure for ANT+ common data page 73.
 */
typedef struct
{
    uint16_t slave_serial_number;        ///< The serial number of the remote control device. .
    uint16_t manufacturer_id;            ///< ///< Manufacturer ID..
    uint8_t  sequence;                   ///< Sequence that increments for each new command.
    uint16_t command_number;              ///< Command Number.

} ant_common_page73_data_t;

/**@brief Initialize page 73 with default values.
 */
#define DEFAULT_ANT_COMMON_PAGE73()                                             \
    (ant_common_page73_data_t)                                                  \
    {                                                                           \
        .slave_serial_number                 = 0xFFFF,                          \
        .manufacturer_id                     = 0x00FF,                          \
        .sequence                            = 0x00,                            \
        .command_number                      = 0,                               \
    }

/**@brief Initialize page 73 with the page request.
 */
#define ANT_COMMON_PAGE73(page_num, man_id, seq, cmd_num) \
    (ant_common_page73_data_t)                                                  \                                                                         \
    {                                                                           \
        .slave_serial_number                 = page_num,                        \
        .manufacturer_id                     = man_id,                          \
        .sequence                            = sqe,                             \
        .command_number                      = cmd_num,                         \
    }

/**@brief Function for encoding page 73.
 *
 * @param[in]  p_page_data      Pointer to the page data.
 * @param[out] p_page_buffer    Pointer to the data buffer.
 */
void ant_common_page_73_encode(uint8_t                                 * p_page_buffer,
                               volatile ant_common_page73_data_t const * p_page_data);

/**@brief Function for decoding page 73.
 *
 * @param[in]  p_page_buffer    Pointer to the data buffer.
 * @param[out] p_page_data      Pointer to the page data.
 */
void ant_common_page_73_decode(uint8_t const                     * p_page_buffer,
                               volatile ant_common_page73_data_t * p_page_data);


#ifdef __cplusplus
}
#endif

#endif // ANT_COMMON_PAGE_73_H__
/** @} */
