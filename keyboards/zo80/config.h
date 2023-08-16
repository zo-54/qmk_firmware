#pragma once

#define MATRIX_ROW_PINS { D0, D1, D2, D3, D5, D4, D6, D7, B4 }
#define MATRIX_COL_PINS { B7, B3, B2, B1, B0, E6, F1, F4, F5, F6, F7 }

#define DIODE_DIRECTION COL2ROW

#define RGB_DI_PIN E2
#ifdef RGB_DI_PIN
    #define RGBLED_NUM 20
    #define RGBLIGHT_SLEEP
    #define RGBLIGHT_LAYERS
    #define RGBLIGHT_LAYER_BLINK

    #define RGBLIGHT_EFFECT_BREATHING
    #define RGBLIGHT_EFFECT_RAINBOW_MOOD
    #define RGBLIGHT_EFFECT_RAINBOW_SWIRL
    #define RGBLIGHT_EFFECT_RGB_TEST
#endif
