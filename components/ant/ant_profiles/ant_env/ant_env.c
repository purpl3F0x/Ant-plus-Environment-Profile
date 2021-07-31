/**
 * @file ant_env.c
 * @author Stavros Avramidis (stavros9899@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2020-09-29
 * 
 * @copyright Copyright (c) 2020
 * 
 */


#include "sdk_config.h"
#if ANT_ENV_ENABLED

#include "nrf_assert.h"
#include "app_error.h"
#include "ant_interface.h"
#include "app_util.h"
#include "ant_env.h"
#include "ant_env_utils.h"
#include "app_error.h"



#define NRF_LOG_MODULE_NAME ant_env
#if ANT_ENV_LOG_ENABLED
#define NRF_LOG_LEVEL       ANT_ENV_LOG_LEVEL
#define NRF_LOG_INFO_COLOR  ANT_ENV_INFO_COLOR
#else // ANT_ENV_LOG_ENABLED
#define NRF_LOG_LEVEL       0
#endif // ANT_ENV_LOG_ENABLED
#include "nrf_log.h"
NRF_LOG_MODULE_REGISTER();

#define BACKGROUND_DATA_INTERVAL 64 /**< The number of main data pages sent between background data page.
                                         Background data page is sent every 65th message. */
#define TX_TOGGLE_DIVISOR        4  /**< The number of messages between changing state of toggle bit. */

/**@brief ENV message data layout structure. */
typedef struct
{
    uint8_t page_number;
    uint8_t page_payload[7];
} ant_env_message_layout_t;

/**@brief Function for initializing the ANT ENV profile instance.
 *
 * @param[in]  p_profile        Pointer to the profile instance.
 * @param[in]  p_channel_config Pointer to the ANT channel configuration structure.
 *
 * @retval     NRF_SUCCESS      If initialization was successful. Otherwise, an error code is returned.
 */
static ret_code_t ant_env_init(ant_env_profile_t          * p_profile,
                             ant_channel_config_t const * p_channel_config)
{
    p_profile->channel_number = p_channel_config->channel_number;

    p_profile->page_0 = DEFAULT_ANT_ENV_PAGE0();
    p_profile->page_1 = DEFAULT_ANT_ENV_PAGE1();

    // p_profile->page_80 = DEFAULT_ANT_COMMON_page80();
    // p_profile->page_81 = DEFAULT_ANT_COMMON_page81();

    NRF_LOG_INFO("ANT ENV channel %u init", p_profile->channel_number);
    return ant_channel_init(p_channel_config);
}


// ret_code_t ant_env_disp_init(ant_env_profile_t          * p_profile,
//                            ant_channel_config_t const * p_channel_config,
//                            ant_env_evt_handler_t        evt_handler)
// {
//     ASSERT(p_profile != NULL);
//     ASSERT(p_channel_config != NULL);
//     ASSERT(evt_handler != NULL);

//     p_profile->evt_handler = evt_handler;

//     return ant_env_init(p_profile, p_channel_config);
// }


ret_code_t ant_env_sens_init(ant_env_profile_t           * p_profile,
                           ant_channel_config_t const  * p_channel_config,
                           ant_env_sens_config_t const * p_sens_config)
{
    ASSERT(p_profile != NULL);
    ASSERT(p_channel_config != NULL);
    ASSERT(p_sens_config != NULL);
    ASSERT(p_sens_config->p_cb != NULL);
    ASSERT(p_sens_config->evt_handler != NULL);

    ASSERT((p_sens_config->main_page_number == ANT_ENV_PAGE_0) || (p_sens_config->main_page_number == ANT_ENV_PAGE_1));

    p_profile->evt_handler       = p_sens_config->evt_handler;
    p_profile->_cb.p_sens_cb     = p_sens_config->p_cb;

    ant_env_sens_cb_t * p_env_cb = p_profile->_cb.p_sens_cb;
    p_env_cb->main_page_number   = p_sens_config->main_page_number;
    p_env_cb->ext_page_number    = (p_sens_config->main_page_number == ANT_ENV_PAGE_1) ? ANT_ENV_PAGE_0 : ANT_ENV_PAGE_1;
    p_env_cb->message_counter    = 0;

    return ant_env_init(p_profile, p_channel_config);
}


/**@brief Function for getting next page number to send.
 *
 * @param[in]  p_profile        Pointer to the profile instance.
 *
 * @return     Next page number.
 */
static ant_env_page_t next_page_number_get(ant_env_profile_t * p_profile)
{   
    static ant_env_page_t page_number = ANT_ENV_PAGE_0;
    ant_env_sens_cb_t * p_env_cb = p_profile->_cb.p_sens_cb;


    if (ant_request_controller_pending_get(&(p_env_cb->req_controller), (uint8_t *)&page_number))
    {
        // No implementation needed
        return page_number;
    }
    else {
        return page_number++ &1;
    }

    return page_number++ & 1;


    // ant_env_sens_cb_t * p_env_cb = p_profile->_cb.p_sens_cb;
    // ant_env_page_t      page_number;

    if (p_env_cb->message_counter == (BACKGROUND_DATA_INTERVAL))
    {
        page_number = p_env_cb->ext_page_number;

        p_env_cb->message_counter = 0;

        p_env_cb->ext_page_number++;

        if (p_env_cb->ext_page_number > ANT_ENV_PAGE_1)
        {
            p_env_cb->ext_page_number = ANT_ENV_PAGE_1;
        }
    }
    else
    {
        page_number = p_env_cb->main_page_number;
    }

    // if (p_env_cb->message_counter % TX_TOGGLE_DIVISOR == 0)
    // {
    //     p_env_cb->toggle_bit ^= 1;
    // }

    p_env_cb->message_counter++;

    return page_number;
}


/**@brief Function for encoding ENV message.
 *
 * @note Assume to be call each time when Tx window will occur.
 */
static void sens_message_encode(ant_env_profile_t * p_profile, uint8_t * p_message_payload)
{
    ant_env_message_layout_t * p_env_message_payload =
        (ant_env_message_layout_t *)p_message_payload;
    ant_env_sens_cb_t * p_env_cb = p_profile->_cb.p_sens_cb;

    p_env_message_payload->page_number = next_page_number_get(p_profile);

    NRF_LOG_INFO("ENV TX Page number: %u", p_env_message_payload->page_number);

    ant_env_page_0_encode(p_env_message_payload->page_payload, &(p_profile->page_0)); // Page 0 is present in each message

    switch (p_env_message_payload->page_number)
    {
        case ANT_ENV_PAGE_0:
            // No implementation needed
            break;

        case ANT_ENV_PAGE_1:
            ant_env_page_1_encode(p_env_message_payload->page_payload, &(p_profile->page_1));
            break;

        case ANT_ENV_PAGE_80:
            ant_common_page_80_encode(p_env_message_payload->page_payload, &(p_profile->page_80));
            break;

        case ANT_ENV_PAGE_81:
            ant_common_page_81_encode(p_env_message_payload->page_payload, &(p_profile->page_81));
            break;

        default:
            return;
    }

    p_profile->evt_handler(p_profile, (ant_env_evt_t)p_env_message_payload->page_number);
}


/**@brief Function for setting payload for ANT message and sending it.
 *
 * @param[in]  p_profile        Pointer to the profile instance.
 */
static void ant_message_send(ant_env_profile_t * p_profile)
{
    uint32_t err_code;
    uint8_t  p_message_payload[ANT_STANDARD_DATA_PAYLOAD_SIZE];

    sens_message_encode(p_profile, p_message_payload);
    err_code =
        sd_ant_broadcast_message_tx(p_profile->channel_number,
                                    sizeof (p_message_payload),
                                    p_message_payload);
    APP_ERROR_CHECK(err_code);
}


void ant_env_sens_evt_handler(ant_evt_t * p_ant_evt, void * p_context)
{
    ASSERT(p_context   != NULL);
    ASSERT(p_ant_evt != NULL);
    ant_env_profile_t * p_profile = (ant_env_profile_t *)p_context;


    if (p_ant_evt->channel == p_profile->channel_number)
    {
        uint32_t err_code;
        uint8_t p_message_payload[ANT_STANDARD_DATA_PAYLOAD_SIZE];
        ant_env_sens_cb_t * p_env_cb = p_profile->_cb.p_sens_cb;
        ant_request_controller_sens_evt_handler(&(p_env_cb->req_controller), p_ant_evt);


        switch (p_ant_evt->event)
        {
            case EVENT_TX:
            case EVENT_TRANSFER_TX_FAILED:
            case EVENT_TRANSFER_TX_COMPLETED:
                // ant_message_send(p_profile);


                sens_message_encode(p_profile, p_message_payload);
                if (ant_request_controller_ack_needed(&(p_env_cb->req_controller)))
                {
                    err_code = sd_ant_acknowledge_message_tx(p_profile->channel_number,
                                                             sizeof(p_message_payload),
                                                             p_message_payload);
                }
                else
                {
                    err_code = sd_ant_broadcast_message_tx(p_profile->channel_number,
                                                           sizeof(p_message_payload),
                                                           p_message_payload);
                }
                APP_ERROR_CHECK(err_code);

                break;
            
            // case EVENT_RX:
            //     if (p_ant_evt->message.ANT_MESSAGE_ucMesgID == MESG_ACKNOWLEDGED_DATA_ID)
            //     {
            //         sens_message_decode(p_profile, p_ant_evt->message.ANT_MESSAGE_aucPayload);
            //     }
            //     break;

            default:
                break;
        }
    }
}


// ret_code_t ant_env_disp_open(ant_env_profile_t * p_profile)
// {
//     ASSERT(p_profile != NULL);

//     NRF_LOG_INFO("ANT ENV channel %u open", p_profile->channel_number);
//     return sd_ant_channel_open(p_profile->channel_number);
// }


ret_code_t ant_env_sens_open(ant_env_profile_t * p_profile)
{
    ASSERT(p_profile != NULL);

    // Fill tx buffer for the first frame
    ant_message_send(p_profile);

    NRF_LOG_INFO("ANT ENV channel %u open", p_profile->channel_number);
    return sd_ant_channel_open(p_profile->channel_number);
}


// /**@brief Function for decoding ENV message.
//  *
//  * @note Assume to be call each time when Rx window will occur.
//  */
// static void disp_message_decode(ant_env_profile_t * p_profile, uint8_t * p_message_payload)
// {
//     const ant_env_message_layout_t * p_env_message_payload =
//         (ant_env_message_layout_t *)p_message_payload;

//     NRF_LOG_INFO("ENV RX Page Number: %u", p_env_message_payload->page_number);

//     ant_env_page_0_decode(p_env_message_payload->page_payload, &(p_profile->page_0)); // Page 0 is present in each message

//     switch (p_env_message_payload->page_number)
//     {
//         case ANT_ENV_PAGE_0:
//             // No implementation needed
//             break;

//         case ANT_ENV_PAGE_1:
//             ant_env_page_1_decode(p_env_message_payload->page_payload, &(p_profile->page_1));
//             break;

//         case ANT_ENV_PAGE_2:
//             ant_env_page_2_decode(p_env_message_payload->page_payload, &(p_profile->page_2));
//             break;

//         case ANT_ENV_PAGE_3:
//             ant_env_page_3_decode(p_env_message_payload->page_payload, &(p_profile->page_3));
//             break;

//         case ANT_ENV_PAGE_4:
//             ant_env_page_4_decode(p_env_message_payload->page_payload, &(p_profile->page_4));
//             break;

//         default:
//             return;
//     }

//     p_profile->evt_handler(p_profile, (ant_env_evt_t)p_env_message_payload->page_number);
// }


// void ant_env_disp_evt_handler(ant_evt_t * p_ant_evt, void * p_context)
// {
//     ant_env_profile_t * p_profile = ( ant_env_profile_t *)p_context;
//     if (p_ant_evt->channel == p_profile->channel_number)
//     {
//         switch (p_ant_evt->event)
//         {
//             case EVENT_RX:
//                 if (p_ant_evt->message.ANT_MESSAGE_ucMesgID == MESG_BROADCAST_DATA_ID
//                  || p_ant_evt->message.ANT_MESSAGE_ucMesgID == MESG_ACKNOWLEDGED_DATA_ID
//                  || p_ant_evt->message.ANT_MESSAGE_ucMesgID == MESG_BURST_DATA_ID)
//                 {
//                     disp_message_decode(p_profile, p_ant_evt->message.ANT_MESSAGE_aucPayload);
//                 }
//                 break;

//             default:
//                 break;
//         }
//     }
// }

#endif // ANT_ENV_ENABLED
