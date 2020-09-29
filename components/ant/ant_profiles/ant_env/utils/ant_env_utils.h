/**
 * @file ant_env_utils.h
 * @author Stavros Avramidis (stavros9899@gmail.com)
 * @version 0.1
 * @date 2020-09-29
 * 
 * @copyright Copyright (c) 2020
 * 
 * @defgroup ant_sdk_profiles_env_utils Enviroment profile utilities
 * @{
 * @ingroup ant_env
 * @brief This module implements utilities for the Enviroment profile.
 * 
 */
#ifndef ANT_ENV_UTILS_H__
#define ANT_ENV_UTILS_H__

#include "app_util.h"
#include "nrf_assert.h"
#include "nrf.h"

#ifdef __cplusplus
extern "C" {
#endif


/**@brief Unit for ENV operating time.
 *
 * @details According to the ANT ENV specification, the operating time unit is 2 seconds.
 */
#define ANT_ENV_OPERATING_TIME_UNIT                 2u

/**@brief This macro should be used to get the seconds part of the operating time.
 */
#define ANT_ENV_OPERATING_SECONDS(OPERATING_TIME)   (((OPERATING_TIME) * ANT_ENV_OPERATING_TIME_UNIT) % 60)

/**@brief This macro should be used to get the minutes part of the operating time.
 */
#define ANT_ENV_OPERATING_MINUTES(OPERATING_TIME)   ((((OPERATING_TIME) * ANT_ENV_OPERATING_TIME_UNIT) / 60) % 60)

/**@brief This macro should be used to get the hours part of the operating time.
 */
#define ANT_ENV_OPERATING_HOURS(OPERATING_TIME)     ((((OPERATING_TIME) * ANT_ENV_OPERATING_TIME_UNIT) / (60 * 60)) % 24)

/**@brief This macro should be used to get the days part of the operating time.
 */
#define ANT_ENV_OPERATING_DAYS(OPERATING_TIME)      ((((OPERATING_TIME) * ANT_ENV_OPERATING_TIME_UNIT) / (60 * 60)) / 24)


// #define ANT_ENV_TRANSMISTION_INFO_LOCAL_TIME_NOT_SUPPORTED      0x00000000u
// #define ANT_ENV_TRANSMISTION_INFO_LOCAL_TIME_SUPPORTED_NOT_SET  0x00010000u
// #define ANT_ENV_TRANSMISTION_INFO_LOCAL_TIME_SUPPORTED_SET      0x00100000u

// #define ANT_ENV_TRANSMISTION_INFO_UTC_LOCAL_TIME_NOT_SUPPORTED      0x00000000u
// #define ANT_ENV_TRANSMISTION_INFO_UTC_LOCAL_TIME_SUPPORTED_NOT_SET  0x00000100u
// #define ANT_ENV_TRANSMISTION_INFO_UTC_LOCAL_TIME_NOT_SUPPORTED      0x00001000u



#ifndef ANT_ENV_ANT_OBSERVER_PRIO
#define ANT_ENV_ANT_OBSERVER_PRIO 1
#endif


#ifdef __cplusplus
}
#endif

#endif // ANT_ENV_UTILS_H__

