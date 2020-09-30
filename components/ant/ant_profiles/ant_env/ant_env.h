/**
 * @file ant_env.h
 * @author Stavros Avramidis (stavros9899@gmail.com)
 * @version 0.1
 * @date 2020-09-29
 * 
 * @copyright Copyright (c) 2020
 * 
 * @defgroup ant_env Enviroment profile
 * @{
 * @ingroup ant_sdk_profiles
 * @brief This module implements the Enviroment profile.
 * 
 */


#ifndef ANT_ENV_H__
#define ANT_ENV_H__

#include <stdint.h>
#include <stdbool.h>
#include "app_util.h"
#include "ant_parameters.h"
#include "nrf_sdh_ant.h"
#include "ant_channel_config.h"
#include "ant_env_pages.h"
#include "sdk_errors.h"

#define ENV_DEVICE_TYPE       0x19u     ///< Device type reserved for ANT+ enviroment
#define ENV_ANTPLUS_RF_FREQ   0x39u     ///< Frequency, decimal 57 (2457 MHz).

#define ENV_MSG_PERIOD_4Hz    0x2000u   ///< Message period, decimal 8070 (4.06 Hz).
#define ENV_MSG_PERIOD_05Hz   0xFFFFu   ///< Message period, decimal 65535 (0.5 Hz).



#define ENV_EXT_ASSIGN        0x00                  ///< ANT ext assign.
// #define ENV_DISP_CHANNEL_TYPE CHANNEL_TYPE_SLAVE    ///< Display ENV channel type.
#define ENV_SENS_CHANNEL_TYPE CHANNEL_TYPE_MASTER   ///< Sensor ENV channel type.

// /**@brief Initialize an ANT channel configuration structure for the ENV profile (Display).
//  *
//  * @param[in]  NAME                 Name of related instance.
//  * @param[in]  CHANNEL_NUMBER       Number of the channel assigned to the profile instance.
//  * @param[in]  TRANSMISSION_TYPE    Type of transmission assigned to the profile instance.
//  * @param[in]  DEVICE_NUMBER        Number of the device assigned to the profile instance.
//  * @param[in]  NETWORK_NUMBER       Number of the network assigned to the profile instance.
//  * @param[in]  ENV_MSG_PERIOD       Channel period in 32 kHz counts. The ENV profile supports only the following periods:
//  *                                  @ref ENV_MSG_PERIOD_4Hz, @ref ENV_MSG_PERIOD_2Hz, @ref ENV_MSG_PERIOD_1Hz.
//  */
// #define ENV_DISP_CHANNEL_CONFIG_DEF(NAME,                                       \
//                                     CHANNEL_NUMBER,                             \
//                                     TRANSMISSION_TYPE,                          \
//                                     DEVICE_NUMBER,                              \
//                                     NETWORK_NUMBER,                             \
//                                     ENV_MSG_PERIOD)                             \
// static const ant_channel_config_t   CONCAT_2(NAME,_channel_env_disp_config) =   \
//     {                                                                           \
//         .channel_number    = (CHANNEL_NUMBER),                                  \
//         .channel_type      = ENV_DISP_CHANNEL_TYPE,                             \
//         .ext_assign        = ENV_EXT_ASSIGN,                                    \
//         .rf_freq           = ENV_ANTPLUS_RF_FREQ,                               \
//         .transmission_type = (TRANSMISSION_TYPE),                               \
//         .device_type       = ENV_DEVICE_TYPE,                                   \
//         .device_number     = (DEVICE_NUMBER),                                   \
//         .channel_period    = (ENV_MSG_PERIOD),                                  \
//         .network_number    = (NETWORK_NUMBER),                                  \
//     }
// #define ENV_DISP_CHANNEL_CONFIG(NAME) &CONCAT_2(NAME,_channel_env_disp_config)


/**@brief Initialize an ANT channel configuration structure for the ENV profile (Sensor).
 *
 * @param[in]  NAME                 Name of related instance.
 * @param[in]  CHANNEL_NUMBER       Number of the channel assigned to the profile instance.
 * @param[in]  TRANSMISSION_TYPE    Type of transmission assigned to the profile instance.
 * @param[in]  DEVICE_NUMBER        Number of the device assigned to the profile instance.
 * @param[in]  NETWORK_NUMBER       Number of the network assigned to the profile instance.
 */
#define ENV_SENS_CHANNEL_CONFIG_DEF(NAME,                                       \
                                    CHANNEL_NUMBER,                             \
                                    TRANSMISSION_TYPE,                          \
                                    DEVICE_NUMBER,                              \
                                    NETWORK_NUMBER)                             \
static const ant_channel_config_t   CONCAT_2(NAME,_channel_env_sens_config) =   \
    {                                                                           \
        .channel_number    = (CHANNEL_NUMBER),                                  \
        .channel_type      = ENV_SENS_CHANNEL_TYPE,                             \
        .ext_assign        = ENV_EXT_ASSIGN,                                    \
        .rf_freq           = ENV_ANTPLUS_RF_FREQ,                               \
        .transmission_type = (TRANSMISSION_TYPE),                               \
        .device_type       = ENV_DEVICE_TYPE,                                   \
        .device_number     = (DEVICE_NUMBER),                                   \
        .channel_period    = ENV_MSG_PERIOD_4Hz,                                \
        .network_number    = (NETWORK_NUMBER),                                  \
    }
#define ENV_SENS_CHANNEL_CONFIG(NAME) &CONCAT_2(NAME,_channel_env_sens_config)

/**@brief Initialize an ANT profile configuration structure for the ENV profile (Sensor).
 *
 * @param[in]  NAME                 Name of related instance.
 * @param[in]  MAIN_PAGE_NUMBER     Determines the main data page (@ref ANT_ENV_PAGE_0 or @ref ANT_ENV_PAGE_4).
 * @param[in]  EVT_HANDLER          Event handler to be called for handling events in the ENV profile.
 */
#define ENV_SENS_PROFILE_CONFIG_DEF(NAME,                                       \
                                    MAIN_PAGE_NUMBER,                           \
                                    EVT_HANDLER)                                \
static ant_env_sens_cb_t            CONCAT_2(NAME,_env_sens_cb);                \
static const ant_env_sens_config_t  CONCAT_2(NAME,_profile_env_sens_config) =   \
    {                                                                           \
        .main_page_number   = (MAIN_PAGE_NUMBER),                               \
        .p_cb               = &CONCAT_2(NAME,_env_sens_cb),                     \
        .evt_handler        = (EVT_HANDLER),                                    \
    }
#define ENV_SENS_PROFILE_CONFIG(NAME) &CONCAT_2(NAME,_profile_env_sens_config)


/**@brief ENV page number type. */
typedef enum
{
    ANT_ENV_PAGE_0, ///< Main data page number 0.
    ANT_ENV_PAGE_1, ///< Main data page number 1.
} ant_env_page_t;

/**@brief ENV profile event type. */
typedef enum
{
    ANT_ENV_PAGE_0_UPDATED = ANT_ENV_PAGE_0, ///< Data page 0 has been updated (Display) or sent (Sensor).
    ANT_ENV_PAGE_1_UPDATED = ANT_ENV_PAGE_1, ///< Data page 0 and page 1 have been updated (Display) or sent (Sensor).
} ant_env_evt_t;

// Forward declaration of the ant_env_profile_t type.
typedef struct ant_env_profile_s ant_env_profile_t;

/**@brief ENV event handler type. */
typedef void (* ant_env_evt_handler_t) (ant_env_profile_t *, ant_env_evt_t);

#include "ant_env_local.h"

#ifdef __cplusplus
extern "C" {
#endif

/**@brief ENV sensor configuration structure. */
typedef struct
{
    ant_env_page_t          main_page_number; ///< Determines the main data page (@ref ANT_ENV_PAGE_0 or @ref ANT_ENV_PAGE_4).
    ant_env_sens_cb_t     * p_cb;             ///< Pointer to the data buffer for internal use.
    ant_env_evt_handler_t   evt_handler;      ///< Event handler to be called for handling events in the ENV profile.
} ant_env_sens_config_t;

/**@brief ENV profile structure. */
struct ant_env_profile_s
{
    uint8_t               channel_number; ///< Channel number assigned to the profile.
    union {
        void              * p_none;
        ant_env_sens_cb_t * p_sens_cb;
    } _cb;                                ///< Pointer to internal control block.
    ant_env_evt_handler_t evt_handler;    ///< Event handler to be called for handling events in the ENV profile.
    ant_env_page0_data_t  page_0;         ///< Page 0.
    ant_env_page1_data_t  page_1;         ///< Page 1.
};



/**@brief Function for initializing the ANT ENV Display profile instance.
 *
 * @param[in]  p_profile        Pointer to the profile instance.
 * @param[in]  p_channel_config Pointer to the ANT channel configuration structure.
 * @param[in]  evt_handler      Event handler to be called for handling events in the ENV profile.
 *
 * @retval     NRF_SUCCESS      If initialization was successful. Otherwise, an error code is returned.
 */
// ret_code_t ant_env_disp_init(ant_env_profile_t          * p_profile,
//                              ant_channel_config_t const * p_channel_config,
//                              ant_env_evt_handler_t        evt_handler);

/**@brief Function for initializing the ANT ENV Sensor profile instance.
 *
 * @param[in]  p_profile        Pointer to the profile instance.
 * @param[in]  p_channel_config Pointer to the ANT channel configuration structure.
 * @param[in]  p_sens_config    Pointer to the ENV sensor configuration structure.
 *
 * @retval     NRF_SUCCESS      If initialization was successful. Otherwise, an error code is returned.
 */
 ret_code_t ant_env_sens_init(ant_env_profile_t           * p_profile,
                              ant_channel_config_t const  * p_channel_config,
                              ant_env_sens_config_t const * p_sens_config);

/**@brief Function for opening the profile instance channel for ANT ENV Display.
 *
 * Before calling this function, pages should be configured.
 *
 * @param[in]  p_profile        Pointer to the profile instance.
 *
 * @retval     NRF_SUCCESS      If the channel was successfully opened. Otherwise, an error code is returned.
 */
// ret_code_t ant_env_disp_open(ant_env_profile_t * p_profile);

/**@brief Function for opening the profile instance channel for ANT ENV Sensor.
 *
 * Before calling this function, pages should be configured.
 *
 * @param[in]  p_profile        Pointer to the profile instance.
 *
 * @retval     NRF_SUCCESS      If the channel was successfully opened. Otherwise, an error code is returned.
 */
ret_code_t ant_env_sens_open(ant_env_profile_t * p_profile);

/**@brief Function for handling the sensor ANT events.
 *
 * @details This function handles all events from the ANT stack that are of interest to the Enviroment Sensor profile.
 *
 * @param[in]   p_ant_evt       Event received from the ANT stack.
 * @param[in]   p_context       Pointer to the profile instance.
 */
void ant_env_sens_evt_handler(ant_evt_t * p_ant_evt, void * p_context);

/**@brief Function for handling the display ANT events.
 *
 * @details This function handles all events from the ANT stack that are of interest to the Enviroment Display profile.
 *
 * @param[in]   p_ant_evt       Event received from the ANT stack.
 * @param[in]   p_context       Pointer to the profile instance.
 */
// void ant_env_disp_evt_handler(ant_evt_t * p_ant_evt, void * p_context);

#ifdef __cplusplus
}
#endif

#endif // ANT_ENV_H__
/** @} */

