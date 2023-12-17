#ifndef MOVEMENT_CONFIG_H_
#define MOVEMENT_CONFIG_H_

#include "movement_faces.h"

const watch_face_t watch_faces[] = {
    flowtime_face,
    simple_clock_face,
    stopwatch_face,
    preferences_face,
    set_time_face,
};

#define MOVEMENT_NUM_FACES (sizeof(watch_faces) / sizeof(watch_face_t))

/* Determines what face to go to from the first face on long press of the Mode button.
 * Also excludes these faces from the normal rotation.
 * In the default firmware, this lets you access temperature and battery voltage with a long press of Mode.
 * Some folks also like to use this to hide the preferences and time set faces from the normal rotation.
 * If you don't want any faces to be excluded, set this to 0 and a long Mode press will have no effect.
 */
#define MOVEMENT_SECONDARY_FACE_INDEX (MOVEMENT_NUM_FACES - 2) // or (0)

/* Custom hourly chime tune. Check movement_custom_signal_tunes.h for options */
#define SIGNAL_TUNE_DEFAULT

#endif // MOVEMENT_CONFIG_H_
