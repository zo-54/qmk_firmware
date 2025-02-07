#include QMK_KEYBOARD_H

enum layer_names {
    _MAC_BASE,
    _WIN_BASE,
    _FN_LAYER,
};

enum custom_keycodes {
    LOCK = SAFE_RANGE,
    ILY,
    SWAP_OS,
    FOR_OS,
};

const rgblight_segment_t PROGMEM _mac_layer[] = RGBLIGHT_LAYER_SEGMENTS( {0, 20, HSV_WHITE} );
const rgblight_segment_t PROGMEM _win_layer[] = RGBLIGHT_LAYER_SEGMENTS( {0, 20, HSV_BLUE} );
const rgblight_segment_t PROGMEM _warn_layer[] = RGBLIGHT_LAYER_SEGMENTS( {0, 20, HSV_RED} );
const rgblight_segment_t PROGMEM _ily_layer[] = RGBLIGHT_LAYER_SEGMENTS( {0, 20, HSV_PINK} );

const rgblight_segment_t* const PROGMEM _rgb_layers[] =
    RGBLIGHT_LAYERS_LIST( _mac_layer, _win_layer, _warn_layer, _ily_layer );

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_MAC_BASE] = LAYOUT_ansi(
        KC_ESC,    KC_F1,   KC_F2,   KC_F3,   KC_F4,     KC_F5,   KC_F6,   KC_F7,   KC_F8,     KC_F9,   KC_F10,  KC_F11,  KC_F12,     MO(2),     KC_DEL,
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,            KC_HOME,
        KC_TAB,      KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,        KC_END,
        KC_CAPS,       KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,
        KC_LSFT,            KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,          KC_UP,
        KC_LCTL,   KC_LOPT,   KC_LCMD,                       KC_SPC,                              C(KC_UP),     C(KC_DOWN),    KC_LEFT, KC_DOWN, KC_RGHT
    ),
    [_WIN_BASE] = LAYOUT_ansi(
        KC_ESC,    KC_F1,   KC_F2,   KC_F3,   KC_F4,     KC_F5,   KC_F6,   KC_F7,   KC_F8,     KC_F9,   KC_F10,  KC_F11,  KC_F12,     MO(2),     KC_DEL,
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,            KC_HOME,
        KC_TAB,      KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,        KC_END,
        KC_CAPS,       KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,
        KC_LSFT,            KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,          KC_UP,
        KC_LCTL,   KC_LWIN,   KC_LALT,                       KC_SPC,                              KC_RALT,     KC_RCTL,        KC_LEFT, KC_DOWN, KC_RGHT
    ),
    [_FN_LAYER] = LAYOUT_ansi(
        QK_BOOT,   _______, _______, _______, _______,   _______, _______, _______, _______,   _______, _______, _______, _______,    _______,   LOCK,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_VOLD, KC_VOLU, KC_MUTE,            KC_PGUP,
        _______,     RGB_TOG, RGB_MOD, _______, RGB_M_R, RGB_M_T, _______, _______, _______, _______, KC_MPRV, KC_MPLY, KC_MNXT, _______,        KC_PGDN,
        _______,       RGB_HUI, RGB_SAI, RGB_VAI, _______, _______, _______, _______, _______, ILY,     _______, _______, _______,
        _______,            RGB_HUD, RGB_SAD, RGB_VAD, _______, RGB_M_B, NK_TOGG, _______, _______, _______, FOR_OS,  _______,          _______,
        _______,   _______,   _______,                       SWAP_OS,                             _______,     _______,        _______, _______, _______
    ),
};

void keyboard_post_init_user(void) {
    rgblight_layers = _rgb_layers;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LOCK:
            if (record->event.pressed) {
                if (layer_state_cmp(default_layer_state, _WIN_BASE)) {
                    // WINDOWS
                    register_code16(G(KC_L));
                } else {
                    // MAC
                    register_code16(C(G(KC_Q)));
                };
            } else {
                unregister_code16(C(G(KC_Q)));
                unregister_code16(G(KC_L));
            };
            return false;
        case SWAP_OS:
            if (record->event.pressed) {
                if (layer_state_cmp(default_layer_state, _WIN_BASE)) {
                    set_single_persistent_default_layer(_MAC_BASE);
                    rgblight_blink_layer(0, 250);
                } else {
                    set_single_persistent_default_layer(_WIN_BASE);
                    rgblight_blink_layer(1, 250);
                };
            };
            return false;
        case FOR_OS:
            if (record->event.pressed) {
                if (layer_state_cmp(default_layer_state, _WIN_BASE)) {
                    rgblight_blink_layer(1, 250);
                } else {
                    rgblight_blink_layer(0, 250);
                };
            };
            return false;
        case ILY:
            if (record->event.pressed) {
                SEND_STRING("I love you!\n");
                rgblight_blink_layer(3, 250);
            };
            return false;
        default:
            return true;
    };
}
