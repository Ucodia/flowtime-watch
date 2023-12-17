#include <stdlib.h>
#include "flowtime_face.h"
#include "watch.h"
#include "watch_utility.h"
#include "watch_private_display.h"
#include "flowtime.h"

void flowtime_face_setup(movement_settings_t *settings, uint8_t watch_face_index, void **context_ptr)
{
    (void)settings;
    (void)watch_face_index;

    if (*context_ptr == NULL)
    {
        *context_ptr = malloc(sizeof(flowtime_state_t));
        flowtime_state_t *state = (flowtime_state_t *)*context_ptr;
        state->watch_face_index = watch_face_index;
        state->reality_check = false;
    }
}

void flowtime_face_activate(movement_settings_t *settings, void *context)
{
    flowtime_state_t *state = (flowtime_state_t *)context;

    if (watch_tick_animation_is_running())
        watch_stop_tick_animation();

    if (settings->bit.clock_mode_24h)
        watch_set_indicator(WATCH_INDICATOR_24H);

    if (state->reality_check)
        watch_set_indicator(WATCH_INDICATOR_BELL);
    else
        watch_clear_indicator(WATCH_INDICATOR_BELL);

    watch_set_colon();

    // this ensures that none of the timestamp fields will match, so we can re-render them all.
    state->previous_date_time = 0xFFFFFFFF;
}

bool flowtime_face_loop(movement_event_t event, movement_settings_t *settings, void *context)
{
    flowtime_state_t *state = (flowtime_state_t *)context;
    char buf[11];
    uint8_t pos;

    watch_date_time date_time;
    Time flow_time;
    bool alarm_button_down;
    uint32_t previous_date_time;
    switch (event.event_type)
    {
    case EVENT_ACTIVATE:
    case EVENT_TICK:
    case EVENT_LOW_ENERGY_UPDATE:
        date_time = watch_rtc_get_date_time();
        flow_time = date_to_flowtime(date_time);
        alarm_button_down = watch_get_pin_level(2);
        previous_date_time = state->previous_date_time;
        state->previous_date_time = date_time.reg;

        // check the battery voltage once a day...
        if (date_time.unit.day != state->last_battery_check)
        {
            state->last_battery_check = date_time.unit.day;
            watch_enable_adc();
            uint16_t voltage = watch_get_vcc_voltage();
            watch_disable_adc();
            // 2.2 volts will happen when the battery has maybe 5-10% remaining?
            // we can refine this later.
            state->battery_low = (voltage < 2200);
        }

        // ...and set the LAP indicator if low.
        if (state->battery_low)
            watch_set_indicator(WATCH_INDICATOR_LAP);

        pos = 0;
        if (event.event_type == EVENT_LOW_ENERGY_UPDATE)
        {
            if (!watch_tick_animation_is_running())
                watch_start_tick_animation(500);
            sprintf(buf, "%s%2d%2d%02d  ", watch_utility_get_weekday(date_time), date_time.unit.day, alarm_button_down ? date_time.unit.hour : flow_time.hour, alarm_button_down ? date_time.unit.minute : flow_time.minute);
        }
        else
        {
            sprintf(buf, "%s%2d%2d%02d%02d", watch_utility_get_weekday(date_time), date_time.unit.day, alarm_button_down ? date_time.unit.hour : flow_time.hour, alarm_button_down ? date_time.unit.minute : flow_time.minute, date_time.unit.second);
        }

        watch_display_string(buf, pos);
        break;
    default:
        return movement_default_loop_handler(event, settings);
    }

    return true;
}

void flowtime_face_resign(movement_settings_t *settings, void *context)
{
    (void)settings;
    (void)context;
}

bool flowtime_face_wants_background_task(movement_settings_t *settings, void *context)
{
    return false;
}
