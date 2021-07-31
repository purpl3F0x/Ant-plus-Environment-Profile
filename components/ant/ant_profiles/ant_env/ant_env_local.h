/**
 * @file ant_env_local.h
 * @author Stavros Avramidis (stavros9899@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2020-09-29
 * 
 * @copyright Copyright (c) 2020
 * 
 */


#ifndef ANT_ENV_LOCAL_H__
#define ANT_ENV_LOCAL_H__

#include <stdint.h>
#include <stdbool.h>
#include "ant_env.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup ant_env
 * @{
 */

/** @brief ENV Sensor control block. */
typedef struct
{
    ant_env_page_t main_page_number;
    ant_env_page_t ext_page_number;
    uint8_t        message_counter;
    ant_request_controller_t req_controller;

} ant_env_sens_cb_t;

/**
 * @}
 */


#ifdef __cplusplus
}
#endif

#endif // ANT_ENV_LOCAL_H__
