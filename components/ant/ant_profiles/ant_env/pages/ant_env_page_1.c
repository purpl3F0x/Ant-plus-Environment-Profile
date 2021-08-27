/**
 * @file ant_env_page_1.c
 * @author Stavros Avramidis (stavros9899@gmail.com)
 * @brief 
 * @version 1.0
 * @date 2021-27-8
 * 
 * @copyright Copyright (c) 2021
 * 
 */


#include "sdk_common.h"
#if NRF_MODULE_ENABLED(ANT_ENV)

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
    uint8_t _24_hour_high_lsn:4;
       uint8_t _24_hour_low_msn:4;
    uint8_t _24_hour_high_msb;
    uint8_t current_temp[2];
}ant_env_page1_data_layout_t;

/**@brief Function for tracing page 1 and common data.
 *
 * @param[in]  p_common_data    Pointer to the common data.
 * @param[in]  p_page_data      Pointer to the page 1 data.
 */
static void page1_data_log(ant_env_page1_data_t const * p_page_data)
{
    NRF_LOG_INFO("Event Count  :                %u", (unsigned int)p_page_data->event_count);
    NRF_LOG_INFO("24-Hour Low  :                " NRF_LOG_FLOAT_MARKER , p_page_data->_24_hour_low * .1f);
    NRF_LOG_INFO("24-Hour High :                " NRF_LOG_FLOAT_MARKER , p_page_data->_24_hour_high* .1f);
    NRF_LOG_INFO("Current Temp :                " NRF_LOG_FLOAT_MARKER "\n\r", p_page_data->current_temp * 0.01f);
}


void ant_env_page_1_encode(uint8_t                    * p_page_buffer,
                           ant_env_page1_data_t const * p_page_data)
{
    ant_env_page1_data_layout_t * p_outcoming_data = (ant_env_page1_data_layout_t *)p_page_buffer;

    p_outcoming_data->reserved                          = UINT8_MAX;
    p_outcoming_data->event_count                       = (uint8_t)(p_page_data->event_count);
    p_outcoming_data->_24_hour_low_lsb                  = (uint8_t)(p_page_data->_24_hour_low & 0xFFu);
    p_outcoming_data->_24_hour_low_msn                  = (uint8_t)((p_page_data->_24_hour_low >> 8u) & 0xFu);          
    p_outcoming_data->_24_hour_high_lsn                 = (uint8_t)(p_page_data->_24_hour_high & 0xFu);
    p_outcoming_data->_24_hour_high_msb                 = (uint8_t)((p_page_data->_24_hour_high >> 4u) & 0xFFu);

    UNUSED_PARAMETER(uint16_encode(p_page_data->current_temp, p_outcoming_data->current_temp));

    page1_data_log(p_page_data);
}


 void ant_env_page_1_decode(uint8_t const        * p_page_buffer,
                            ant_env_page1_data_t * p_page_data)
{
     ant_env_page1_data_layout_t const * p_incoming_data = (ant_env_page1_data_layout_t *)p_page_buffer;

     p_page_data->event_count  = p_incoming_data->event_count;
     p_page_data->current_temp = (int16_t)uint16_decode(p_incoming_data->current_temp);

     p_page_data->_24_hour_low =  (int16_t) (((uint16_t)p_incoming_data->_24_hour_low_msn  << 8u) | p_incoming_data->_24_hour_low_lsb);
     p_page_data->_24_hour_high =  (int16_t) (((uint16_t)p_incoming_data->_24_hour_high_msb << 4u) |  p_incoming_data->_24_hour_high_lsn);


     page1_data_log(p_page_data);
}

#endif // NRF_MODULE_ENABLED(ANT_ENV)
