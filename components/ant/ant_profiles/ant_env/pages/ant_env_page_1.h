#ifndef ANT_ENV_PAGE_1_H__
#define ANT_ENV_PAGE_1_H__

/** @file
 *
 * @defgroup ant_sdk_profiles_env_page1 ENV profile page 1
 * @{
 * @ingroup ant_sdk_profiles_env_pages
 */

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define INT12_MAX   0x7FFu
#define INT12_MIN   0xFFFu


/**@brief Data structure for ENV data page 1.
 *
 * This structure is used as a common page.
 */
typedef struct
{
    uint8_t  event_count;           ///< event count - increments with each measurement.
    int16_t _24_hour_low;           ///< Signed Integer representing the lowest temperature recorded over the last 24hours (0x800 invalid)
    int16_t _24_hour_high;          ///< Signed Integer representing the highest temperature recorded over the last 24hours (0x800 invalid)
    int16_t current_temp;           ///< Signed Integer representing the current Temperature (0x8000 invalid)

} ant_env_page1_data_t;


/**@brief Initialize page 1.
 */
#define DEFAULT_ANT_ENV_PAGE1()   \
    (ant_env_page1_data_t)        \
    {                             \
        .event_count   = 0,       \
        ._24_hour_low  = 0x800u,       \
        ._24_hour_high = 0x800u,       \
        .current_temp  = 0        \
    }

/**@brief Function for encoding page 1.
 *
 * @param[in]  p_page_data      Pointer to the page data.
 * @param[out] p_page_buffer    Pointer to the data buffer.
 */
void ant_env_page_1_encode(uint8_t                    * p_page_buffer,
                           ant_env_page1_data_t const * p_page_data);

/**@brief Function for decoding page 1.
 *
 * @param[in]  p_page_buffer    Pointer to the data buffer.
 * @param[out] p_page_data      Pointer to the page data.
 */
void ant_env_page_1_decode(uint8_t const        * p_page_buffer,
                           ant_env_page1_data_t * p_page_data);


#ifdef __cplusplus
}
#endif

#endif // ANT_ENV_PAGE_1_H__
/** @} */
