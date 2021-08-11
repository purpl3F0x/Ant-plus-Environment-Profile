/**@file
 * @defgroup ant_env_tx_main ANT Enviroment TX example
 * @{
 * @ingroup nrf_ant_env
 *
 * @brief Example of ANT Enviroment TX profile.
 *
 * Before compiling this example for NRF52, complete the following steps:
 * - Download the S212 SoftDevice from <a href="https://www.thisisant.com/developer/components/nrf52832" target="_blank">thisisant.com</a>.
 * - Extract the downloaded zip file and copy the S212 SoftDevice headers to <tt>\<InstallFolder\>/components/softdevice/s212/headers</tt>.
 * If you are using Keil packs, copy the files into a @c headers folder in your example folder.
 * - Make sure that @ref ANT_LICENSE_KEY in @c nrf_sdm.h is uncommented.
 */


#include <stdio.h>
#include "nrf.h"
#include "bsp.h"
#include "hardfault.h"
#include "app_error.h"
#include "app_timer.h"
#include "nrf_pwr_mgmt.h"
#include "nrf_sdh.h"
#include "nrf_sdh_ant.h"
#include "ant_key_manager.h"
#include "ant_env.h"
#include "ant_env_utils.h"

#include "ant_state_indicator.h"

#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "nrf_log_default_backends.h"

#define MODIFICATION_TYPE_BUTTON 0 /* predefined value, MUST REMAIN UNCHANGED */
#define MODIFICATION_TYPE_AUTO   1 /* predefined value, MUST REMAIN UNCHANGED */

#if (MODIFICATION_TYPE != MODIFICATION_TYPE_BUTTON) \
    && (MODIFICATION_TYPE != MODIFICATION_TYPE_AUTO)

    #error Unsupported value of MODIFICATION_TYPE.
#endif

#define APP_TICK_EVENT_INTERVAL  APP_TIMER_TICKS(500) /**< 0.25(4Hz) second's tick event interval in timer tick units. */
#define ENV_CHANNEL_NUMBER       0x00 /**< Channel number assigned to Enviroment profile. */
#define ANTPLUS_NETWORK_NUMBER   0    /**< Network number. */

/** @snippet [ANT ENV TX Instance] */
void ant_env_evt_handler(ant_env_profile_t * p_profile, ant_env_evt_t event);

ENV_SENS_CHANNEL_CONFIG_DEF(m_ant_env,
                            ENV_CHANNEL_NUMBER,
                            CHAN_ID_TRANS_TYPE,
                            CHAN_ID_DEV_NUM,
                            ANTPLUS_NETWORK_NUM);
ENV_SENS_PROFILE_CONFIG_DEF(m_ant_env,
                            ANT_ENV_PAGE_1,
                            ant_env_evt_handler);

static ant_env_profile_t m_ant_env;
/** @snippet [ANT Enviroment TX Instance] */


NRF_SDH_ANT_OBSERVER(m_ant_observer, ANT_ENV_ANT_OBSERVER_PRIO,
                     ant_env_sens_evt_handler, &m_ant_env);


APP_TIMER_DEF(m_tick_timer);                        /**< Timer used to update cumulative operating time. */

#if MODIFICATION_TYPE == MODIFICATION_TYPE_BUTTON
/**@brief Function for handling bsp events.
 */
/** @snippet [ANT Enviroment simulator button] */
void bsp_evt_handler(bsp_event_t evt)
{
    switch (evt)
    {
        case BSP_EVENT_KEY_0:
            break;

        case BSP_EVENT_KEY_1:
            break;

        default:
            return; // no implementation needed
    }
}

/** @snippet [ANT Enviroment simulator button] */
#endif // MODIFICATION_TYPE == MODIFICATION_TYPE_BUTTON

/**
 * @brief 0.5 seconds tick handler for updataing cumulative operating time. 
 */
static void app_tick_handler(void * p_context)
{
    uint32_t temp;
    sd_temp_get(&temp);
    temp = (temp * 25);

    m_ant_env.page_1.current_temp = (uint16_t)temp;
    m_ant_env.page_1.event_count++;


}

/**@brief Function for setup all things not directly associated with ANT stack/protocol.
 *
 * @desc Initialization of: @n
 *         - app_timer, presetup for bsp and ant pulse simulation.
 *         - bsp for signaling leds and user buttons (if use button is enabled in example).
 */
static void utils_setup(void)
{
    // Initialize and start a single continuous mode timer, which is used to update the event time
    // on the main data page.
    ret_code_t err_code = app_timer_init();
    APP_ERROR_CHECK(err_code);

    err_code = nrf_pwr_mgmt_init();
    APP_ERROR_CHECK(err_code);

#if (MODIFICATION_TYPE == MODIFICATION_TYPE_BUTTON)
    /** @snippet [ANT Pulse simulator button init] */
    err_code = bsp_init(BSP_INIT_LEDS | BSP_INIT_BUTTONS,
                        bsp_evt_handler);
    /** @snippet [ANT Pulse simulator button init] */
#else
    err_code = bsp_init(BSP_INIT_LEDS, NULL);
#endif
    APP_ERROR_CHECK(err_code);

    err_code = ant_state_indicator_init(m_ant_env.channel_number, ENV_SENS_CHANNEL_TYPE);
    APP_ERROR_CHECK(err_code);

    err_code = app_timer_create(&m_tick_timer,
                                APP_TIMER_MODE_REPEATED,
                                app_tick_handler);
    APP_ERROR_CHECK(err_code);

    err_code = app_timer_start(m_tick_timer, APP_TICK_EVENT_INTERVAL, NULL);
    APP_ERROR_CHECK(err_code);
}


/**@brief Function for ANT stack initialization.
 *
 * @details Initializes the SoftDevice and the ANT event interrupt.
 */
static void softdevice_setup(void)
{
    ret_code_t err_code = nrf_sdh_enable_request();
    APP_ERROR_CHECK(err_code);

    ASSERT(nrf_sdh_is_enabled());

    err_code = nrf_sdh_ant_enable();
    APP_ERROR_CHECK(err_code);

    err_code = ant_plus_key_set(ANTPLUS_NETWORK_NUM);
    APP_ERROR_CHECK(err_code);
}

/**@brief Function for handling ANT ENV events.
 */
/** @snippet [ANT ENV simulator call] */
void ant_env_evt_handler(ant_env_profile_t * p_profile, ant_env_evt_t event)
{
    nrf_pwr_mgmt_feed();

    switch (event)
    {
        case ANT_ENV_PAGE_0_UPDATED:
            /* fall through */
        case ANT_ENV_PAGE_1_UPDATED:
            //{
            //    uint32_t temp;
            //    sd_temp_get(&temp);
            //    temp = (temp * 25);

            //    m_ant_env.page_1.current_temp = (uint16_t)temp;
            //    m_ant_env.page_1.event_count++;
            //}
            break;

        default:
            break;
    }
}

/**
 * @brief Function for ENV profile initialization.
 *
 * @details Initializes the ENV profile and open ANT channel.
 */
static void profile_setup(void)
{
/** @snippet [ANT ENV TX Profile Setup] */
    ret_code_t err_code;

    err_code = ant_env_sens_init(&m_ant_env,
                                 ENV_SENS_CHANNEL_CONFIG(m_ant_env),
                                 ENV_SENS_PROFILE_CONFIG(m_ant_env));
    APP_ERROR_CHECK(err_code);
    

    m_ant_env.page_0.supported_pages = 0b0011;
    m_ant_env.page_80.manufacturer_id = ENV_MFG_ID;
    m_ant_env.page_81.serial_number = ENV_SERIAL_NUMBER;
    m_ant_env.page_80.hw_revision = ENV_HW_VERSION;
    m_ant_env.page_81.sw_revision_major = ENV_SW_VERSION;
    m_ant_env.page_81.sw_revision_major = 0xFF;
    m_ant_env.page_80.model_number = ENV_MODEL_NUMBER;


    err_code = ant_env_sens_open(&m_ant_env);
    APP_ERROR_CHECK(err_code);

    err_code = ant_state_indicator_channel_opened();
    APP_ERROR_CHECK(err_code);
/** @snippet [ANT ENV TX Profile Setup] */
}

/**
 *@brief Function for initializing logging.
 */
static void log_init(void)
{
    ret_code_t err_code = NRF_LOG_INIT(NULL);
    APP_ERROR_CHECK(err_code);

    NRF_LOG_DEFAULT_BACKENDS_INIT();
}



/**@brief Function for application main entry, does not return.
 */
int main(void)
{
    log_init();
    utils_setup();
    softdevice_setup();
    profile_setup();

    NRF_LOG_INFO("ANT+ Enviroment TX example started.");

//    bsp_board_led_on(1);
//    bsp_board_led_on(3);
   

    for (;;)
    {
        NRF_LOG_FLUSH();
        nrf_pwr_mgmt_run();
    }
}


/**
 *@}
 **/
