/**
 * @file ant_env_page_1.c
 * @author Stavros Avramidis (stavros9899@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2020-09-29
 * 
 * @copyright Copyright (c) 2020
 * 
 */


#include "sdk_common.h"
// #if NRF_MODULE_ENABLED(ANT_ENV)

#include "ant_env_page_1.h"
#include "ant_env_utils.h"

#define NRF_LOG_MODULE_NAME ant_env_page_1
#if ANT_ENV_PAGE_1_LOG_ENABLED
#define NRF_LOG_LEVEL       ANT_ENV_PAGE_1_LOG_LEVEL
#define NRF_LOG_INFO_COLOR  ANT_ENV_PAGE_1_INFO_COLOR
#else // ANT_ENV_PAGE_1_LOG_ENABLED
#define NRF_LOG_LEVEL       0
#endif // ANT_ENV_PAGE_1_LOG_ENABLED
#include "nrf_log.h"
NRF_LOG_MODULE_REGISTER();

/**@brief ENV page 1 data layout structure. */
typedef struct
{
    uint8_t reserved;
    uint8_t event_count;
    uint8_t _24_hour_low_lsb;
    uint8_t _24_hour_low_msn:4;
    uint8_t _24_hour_high_lsn:4;
    uint8_t _24_hour_high_msb;
    uint8_t current_temp_lsb;
    uint8_t current_temp_msb;


}ant_env_page1_data_layout_t;

/**@brief Function for tracing page 1 and common data.
 *
 * @param[in]  p_common_data    Pointer to the common data.
 * @param[in]  p_page_data      Pointer to the page 1 data.
 */
static void page1_data_log(ant_env_page1_data_t const * p_page_data)
{
    NRF_LOG_INFO("Event Count  :                %u", (unsigned int)p_page_data->event_count);
    NRF_LOG_INFO("24-Hour Low  :                %i", (int)p_page_data->_24_hour_low);
    NRF_LOG_INFO("24-Hour High :                %i", (int)p_page_data->_24_hour_high);
    NRF_LOG_INFO("Current Temp :                %i\n\r", (int)p_page_data->current_temp);
}


void ant_env_page_1_encode(uint8_t                    * p_page_buffer,
                           ant_env_page1_data_t const * p_page_data)
{
    ant_env_page1_data_layout_t * p_outcoming_data = (ant_env_page1_data_layout_t *)p_page_buffer;

    p_outcoming_data->reserved                          = UINT8_MAX;
    p_outcoming_data->event_count                       = (uint8_t)(p_page_data->event_count);
    p_outcoming_data->_24_hour_low_lsb                  = (uint8_t)(p_page_data->_24_hour_low & 0xFFu);
    p_outcoming_data->_24_hour_low_msn                  = (uint8_t)((p_page_data->_24_hour_low >> 4u) & 0xFu);          
    p_outcoming_data->_24_hour_high_lsn                 = (uint8_t)(p_page_data->_24_hour_high & 0xFu);
    p_outcoming_data->_24_hour_high_msb                 = (uint8_t)((p_page_data->_24_hour_high >> 4u) & 0xFFu);
    p_outcoming_data->current_temp_lsb                  = (uint8_t)(p_page_data->current_temp & 0xFF);
    p_outcoming_data->current_temp_msb                  = (uint8_t)((p_page_data->current_temp >> 8u) & 0xFF);

    page1_data_log(p_page_data);
}


// void ant_env_page_1_decode(uint8_t const        * p_page_buffer,
//                            ant_env_page1_data_t * p_page_data)
// {
//     ant_env_page1_data_layout_t const * p_incoming_data = (ant_env_page1_data_layout_t *)p_page_buffer;

//     p_page_data->transmission_info  = (uint32_t)p_incoming_data->transmission_info;

//     p_page_data->supported_pages    = (uint32_t)(p_incoming_data->supported_pages_bit0 +
//                                       (p_incoming_data->supported_pages_bit1 << 8) +
//                                       (p_incoming_data->supported_pages_bit2 << 16) + 
//                                       (p_incoming_data->supported_pages_bit3 << 24));

//     page1_data_log(p_page_data);
// }

// #endif // NRF_MODULE_ENABLED(ANT_ENV)
