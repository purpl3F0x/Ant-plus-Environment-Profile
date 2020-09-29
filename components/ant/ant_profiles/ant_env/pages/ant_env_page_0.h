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

/**@brief Data structure for ENV data page 0.
 *
 * This structure is used as a common page.
 */
typedef struct
{
    uint8_t  transmission_info;          
    uint32_t supported_pages ;         
} ant_env_page0_data_t;


/**@brief Initialize page 0.
 */
#define DEFAULT_ANT_ENV_PAGE0()   \
    (ant_env_page0_data_t)        \
    {                             \
        .transmission_info = 0,   \
        .supported_pages  = 0,    \
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
