/**
 * @file ant_env_page_0.c
 * @author Stavros Avramidis (stavros9899@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2020-09-29
 * 
 * @copyright Copyright (c) 2020
 * 
 */


#include "sdk_common.h"
#if NRF_MODULE_ENABLED(ANT_ENV)

#include "ant_env_page_0.h"
#include "ant_env_utils.h"

#define NRF_LOG_MODULE_NAME ant_env_page_0
#if ANT_ENV_PAGE_0_LOG_ENABLED
#define NRF_LOG_LEVEL       ANT_ENV_PAGE_0_LOG_LEVEL
#define NRF_LOG_INFO_COLOR  ANT_ENV_PAGE_0_INFO_COLOR
#else // ANT_ENV_PAGE_0_LOG_ENABLED
#define NRF_LOG_LEVEL       0
#endif // ANT_ENV_PAGE_0_LOG_ENABLED
#include "nrf_log.h"
NRF_LOG_MODULE_REGISTER();

/**@brief ENV page 0 data layout structure. */
typedef struct
{
    uint8_t reserved[2];
    uint8_t transmission_info;
    uint8_t supported_pages_bit0;
    uint8_t supported_pages_bit1;
    uint8_t supported_pages_bit2;
    uint8_t supported_pages_bit3;

}ant_env_page0_data_layout_t;

/**@brief Function for tracing page 0 and common data.
 *
 * @param[in]  p_common_data    Pointer to the common data.
 * @param[in]  p_page_data      Pointer to the page 0 data.
 */
static void page0_data_log(ant_env_page0_data_t const * p_page_data)
{
    //NRF_LOG_INFO("Transmission Info:                %u", (unsigned int)p_page_data->transmission_info);

    //NRF_LOG_INFO("Supported Pages:                %u", (unsigned int)p_page_data->supported_pages);
    if (p_page_data->default_trans_rate == 0 )
    {
      NRF_LOG_INFO("Default Transmition Rate:      0.5Hz");
    }
    else if (p_page_data->default_trans_rate == 1)
    {
      NRF_LOG_INFO("Default Transmition Rate:        4Hz");
    }

    NRF_LOG_INFO("\n\r");
}


void ant_env_page_0_encode(uint8_t                    * p_page_buffer,
                           ant_env_page0_data_t const * p_page_data)
{
    ant_env_page0_data_layout_t * p_outcoming_data = (ant_env_page0_data_layout_t *)p_page_buffer;

    p_outcoming_data->reserved[0]           = UINT8_MAX;
    p_outcoming_data->reserved[1]           = UINT8_MAX;
    p_outcoming_data->transmission_info     = (p_page_data->local_time << 4u) || (p_page_data->utc_time << 2u) || (p_page_data->default_trans_rate);
    p_outcoming_data->supported_pages_bit0  = (uint8_t)0b11u;
    p_outcoming_data->supported_pages_bit1  = (uint8_t)0u;
    p_outcoming_data->supported_pages_bit2  = (uint8_t)0u;
    p_outcoming_data->supported_pages_bit3  = (uint8_t)0u;

    page0_data_log(p_page_data);
}


// void ant_env_page_0_decode(uint8_t const        * p_page_buffer,
//                            ant_env_page0_data_t * p_page_data)
// {
//     ant_env_page0_data_layout_t const * p_incoming_data = (ant_env_page0_data_layout_t *)p_page_buffer;

//     p_page_data->transmission_info  = (uint32_t)p_incoming_data->transmission_info;

//     p_page_data->supported_pages    = (uint32_t)(p_incoming_data->supported_pages_bit0 +
//                                       (p_incoming_data->supported_pages_bit1 << 8) +
//                                       (p_incoming_data->supported_pages_bit2 << 16) + 
//                                       (p_incoming_data->supported_pages_bit3 << 24));

//     page0_data_log(p_page_data);
// }

#endif // NRF_MODULE_ENABLED(ANT_ENV)
