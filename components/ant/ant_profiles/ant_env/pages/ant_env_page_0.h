/**
 * @file ant_env_page_0.h
 * @author Stavros Avramidis (stavros9899@gmail.com)
 * @version 0.1
 * @date 2020-09-29
 * 
 * @copyright Copyright (c) 2020
 *
 * @defgroup ant_sdk_profiles_env_page0 ENV profile page 0
 * @{
 * @ingroup ant_sdk_profiles_env_pages
 */

#ifndef ANT_ENV_PAGE_0_H__
#define ANT_ENV_PAGE_0_H__



#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**@brief Common Page 0 Default Transmission Rate/
 *
 * This enum represents possible default transmission rate values for the common page 82.
 */
typedef enum
{
    ANT_ENV_PAGE_0_TRANS_RATE_0_5_HZ    = 0b00,    ///< default transmission rate of 0.5 Hz.
    ANT_ENV_PAGE_0_TRANS_RATE_4_HZ      = 0b01,    ///< default transmission rate of 4 Hz.
    ANT_ENV_PAGE_0_TRANS_RATE_RESERVED0 = 0b10,    ///< Reserved.
    ANT_ENV_PAGE_0_TRANS_RATE_RESERVED1 = 0b11,    ///< Reserved.
} ant_env_page0_default_trans_rate_t;

/**@brief Data structure for ENV data page 0.
 *
 * This structure is used as a common page.
 */
typedef struct
{
    uint32_t supported_pages;
    uint8_t local_time:2;
    uint8_t utc_time:2;
    uint8_t default_trans_rate:2;    
} ant_env_page0_data_t;


/**@brief Initialize page 0.
 */
#define DEFAULT_ANT_ENV_PAGE0()   \
    (ant_env_page0_data_t)        \
    {                             \
        .supported_pages  = 0b11, \
        .local_time = 0,          \
        .utc_time = 0,            \
        .default_trans_rate = ANT_ENV_PAGE_0_TRANS_RATE_4_HZ\
    }

/**@brief Function for encoding page 0.
 *
 * @param[in]  p_page_data      Pointer to the page data.
 * @param[out] p_page_buffer    Pointer to the data buffer.
 */
void ant_env_page_0_encode(uint8_t                    * p_page_buffer,
                           ant_env_page0_data_t const * p_page_data);

/**@brief Function for decoding page 0.
 *
 * @param[in]  p_page_buffer    Pointer to the data buffer.
 * @param[out] p_page_data      Pointer to the page data.
 */
void ant_env_page_0_decode(uint8_t const        * p_page_buffer,
                           ant_env_page0_data_t * p_page_data);


#ifdef __cplusplus
}
#endif

#endif // ANT_ENV_PAGE_0_H__
/** @} */
