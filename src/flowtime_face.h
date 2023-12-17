#ifndef FLOWTIME_FACE_H_
#define FLOWTIME_FACE_H_

#include "movement.h"

typedef struct
{
    uint32_t previous_date_time;
    uint8_t last_battery_check;
    uint8_t watch_face_index;
    bool battery_low;
    bool reality_check;
} flowtime_state_t;

void flowtime_face_setup(movement_settings_t *settings, uint8_t watch_face_index, void **context_ptr);
void flowtime_face_activate(movement_settings_t *settings, void *context);
bool flowtime_face_loop(movement_event_t event, movement_settings_t *settings, void *context);
void flowtime_face_resign(movement_settings_t *settings, void *context);
bool flowtime_face_wants_background_task(movement_settings_t *settings, void *context);

#define flowtime_face ((const watch_face_t){ \
    flowtime_face_setup,                     \
    flowtime_face_activate,                  \
    flowtime_face_loop,                      \
    flowtime_face_resign,                    \
    flowtime_face_wants_background_task,     \
})

#endif // FLOWTIME_FACE_H_
