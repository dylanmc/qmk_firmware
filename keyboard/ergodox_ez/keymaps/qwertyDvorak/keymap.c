// Notable differences vs. the default firmware for the ErgoDox EZ:
// Kinesis-inspired layout which makes a software QWERTY->Dvorak remapping work out right.
// Layer 4 is an un-optimized firmware Dvorak remapping.
//  (for plugging in to devices that don't do soft remapping)
#include "ergodox_ez.h"
#include "debug.h"
#include "action_layer.h"

#define BASE 0     // default layer
#define FKEYS 1    // FnKeys
#define MCFT 2     // jump (space) with left thumb
#define DVORAK 4   // firmware-mapped Dvorak
#define DFKEYS 5   // function keys for firmware-mapped Dvorak

/* Macro definitions */
enum macro_id {
    LPAREN_NO, RPAREN_NO, LCURLY_NO, RCURLY_NO, LCQW_NO, RCQW_NO
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Basic layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |   `    |   1  |   2  |   3  |   4  |   5  |  6   |           |  5   |   6  |   7  |   8  |   9  |   0  |   \    |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * | Tab    |   Q  |   W  |   E  |   R  |   T  | ESC  |           | ESC  |   Y  |   U  |   I  |   O  |   P  |  [     |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | Ctrl   |   A  |   S  |   D  |   F  |   G  |------|           |------|   H  |   J  |   K  |   L  |  ;   |  '     |
 * |--------+------+------+------+------+------| LGui |           | RGui |------+------+------+------+------+--------|
 * | LShift |   Z  |   X  |   C  |   V  |   B  |      |           |      |   N  |   M  |   ,  |   .  |  /   | RShift |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   | L1   |  L2  |  L4  | Opt  | LGui |                                       | Left | Down | Up   | Right|      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,---------------.
 *                                        | Ctrl | LAlt |       | RAlt | Ctrl   |
 *                                 ,------|------|------|       |------+--------+------.
 *                                 |      |      | Home |       | PgUp |        |      |
 *                                 | BKSP | DEL  |------|       |------|  Enter |Space |
 *                                 |      |      | End  |       | PgDn |        |      |
 *                                 `--------------------'       `----------------------'
 */
// If it accepts an argument (i.e, is a function), it doesn't need KC_.
// Otherwise, it needs KC_*
[BASE] = KEYMAP(  // layer 0 : default
        // left hand
        KC_GRV,         KC_1,      KC_2,      KC_3,    KC_4,    KC_5,     KC_6,
        KC_TAB,         KC_Q,      KC_W,      KC_E,    KC_R,    KC_T,     KC_ESC,
        KC_LCTL,        KC_A,      KC_S,      KC_D,    KC_F,    KC_G,
        KC_LSFT,        KC_Z,      KC_X,      KC_C,    KC_V,    KC_B,     KC_LGUI,
        MO(FKEYS),      MO(FKEYS), TG(MCFT),  KC_LALT, KC_LGUI,
                                                       KC_LCTL, KC_LGUI,
                                                                KC_HOME,
                                              KC_BSPC, KC_DEL,  KC_END,
        // right hand
             KC_5,      KC_6,      KC_7,      KC_8,    KC_9,    KC_0,     KC_BSLS,
             KC_ESC,    KC_Y,      KC_U,      KC_I,    KC_O,    KC_P,     KC_LBRC,
                        KC_H,      KC_J,      KC_K,    KC_L,    KC_SCLN,  KC_QUOT,
             KC_RGUI,   KC_N,      KC_M,      KC_COMM, KC_DOT,  KC_SLSH,  KC_RSFT,
                                   KC_LEFT,   KC_DOWN, KC_UP,   KC_RIGHT, MO(FKEYS),
             KC_RALT,  KC_RCTL,
             KC_PGUP,
             KC_PGDN,  KC_ENT, KC_SPC
    ),
/* Keymap 1: Function keys Layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |           |  F7  |  F8  |  F9  | F10  | F11  |  F12 |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      |      |      |      |      |Dvorak|           |      |      |  (   |  )   |      |      |        |
 * |--------+------+------+------+------+------| Layer|           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |------|           |------|      |  [   |  ]   |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |  {   |  }   |  ^   |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |      |  <-  |  V   |  ->  |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
// Function keys (and programming braces) layer
[FKEYS] = KEYMAP(
       // left hand
       KC_TRNS, KC_F1,   KC_F2,    KC_F3,      KC_F4,       KC_F5,    KC_F6,
       KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,    KC_TRNS,     KC_TRNS,  TG(DVORAK),
       KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,    KC_TRNS,     KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,    KC_TRNS,     KC_TRNS,  KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,    KC_TRNS,
                                       KC_TRNS,KC_TRNS,
                                               KC_TRNS,
                               KC_TRNS,KC_TRNS,KC_TRNS,
       // right hand
       KC_F7,   KC_F8,        KC_F9,        KC_F10,       KC_F11,     KC_F12,     KC_RBRC,
       KC_TRNS, KC_TRNS,      M(LPAREN_NO), M(RPAREN_NO), KC_TRNS,    KC_TRNS,    KC_RBRC,
                KC_TRNS,      KC_MINS,      KC_EQL,       KC_TRNS,    KC_TRNS,    KC_RBRC,
       KC_TRNS, KC_TRNS,      M(LCURLY_NO), M(RCURLY_NO), KC_TRNS,    KC_UP,      KC_TRNS,
                              KC_TRNS,      KC_LEFT,      KC_DOWN,    KC_RIGHT,   KC_RIGHT,
       KC_TRNS, KC_TRNS,
       KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS
),
/* Keymap 2: Minecraft Layer (left-thumb jumps)
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      |      |      |      |      | ESC  |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |------|           |------|      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |      |      |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |Space |      |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
// Minecraft layer (left-thumb jumps)
[MCFT] = KEYMAP(
       // left hand
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_ESC,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                       KC_TRNS,KC_TRNS,
                                               KC_TRNS,
                               KC_SPC, KC_TRNS,KC_TRNS,
       // right hand
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_AMPR, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                         KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS,
       KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS
),
/* Keymap 4: Dvorak layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |   '  |   ,  |   .  |   P  |   Y  |      |           |      |   F  |   G  |   C  |   R  |   L  |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |   A  |   O  |   E  |   U  |   I  |------|           |------|   D  |   H  |   T  |   N  |  S   |   -    |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |  ;   |   Q  |   J  |   K  |   X  |      |           |      |   B  |   M  |   W  |   V  |  Z   |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |      |      |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 | BKSP |      |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
// If it accepts an argument (i.e, is a function), it doesn't need KC_.
// Otherwise, it needs KC_*
[DVORAK] = KEYMAP(  // layer 4 : Dvorak
        // left hand
        KC_TRNS,   KC_1,      KC_2,      KC_3,    KC_4,    KC_5,     KC_6,
        KC_TRNS,   KC_QUOT,   KC_COMM,  KC_DOT,   KC_P,      KC_Y,      KC_TRNS,
        KC_TRNS,   KC_A,      KC_O,     KC_E,     KC_U,      KC_I,
        KC_LSFT,   KC_SCLN,   KC_Q,     KC_J,     KC_K,      KC_X,      KC_TRNS,
        MO(DFKEYS),KC_TRNS,   KC_TRNS,  KC_TRNS,  KC_TRNS,
                                                             KC_TRNS,   KC_TRNS,
                                                                        KC_TRNS,
                                                    KC_BSPC, KC_TRNS,   KC_TRNS,
        // right hand
        KC_5,       KC_6,     KC_7,      KC_8,      KC_9,      KC_0,      KC_BSLS,
        KC_TRNS,    KC_F,     KC_G,      KC_C,      KC_R,      KC_L,      KC_SLSH,
                    KC_D,     KC_H,      KC_T,      KC_N,      KC_S,      KC_MINS,
        KC_TRNS,    KC_B,     KC_M,      KC_W,      KC_V,      KC_Z,      KC_RSFT,
                              KC_TRNS,  KC_TRNS,    KC_TRNS,   KC_TRNS,   KC_TRNS,
        KC_TRNS, KC_TRNS,
        KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS
    ),
/* Keymap 5: Dvorak layer's Function keys Layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |           |  F7  |  F8  |  F9  | F10  | F11  |  F12 |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      |      |      |      |      |Dvorak|           |      |      |  (   |  )   |      |      |        |
 * |--------+------+------+------+------+------| Layer|           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |------|           |------|      |  [   |  ]   |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |  {   |  }   |  ^   |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |      |  <-  |  V   |  ->  |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
// Function keys (and programming braces) layer
[DFKEYS] = KEYMAP(
       // left hand
       KC_TRNS, KC_F1,   KC_F2,    KC_F3,      KC_F4,       KC_F5,    KC_F6,
       KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,    KC_TRNS,     KC_TRNS,  KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,    KC_TRNS,     KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,    KC_TRNS,     KC_TRNS,  KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,    KC_TRNS,
                                       KC_TRNS,KC_TRNS,
                                               KC_TRNS,
                               KC_TRNS,KC_TRNS,KC_TRNS,
       // right hand
       KC_F7,   KC_F8,        KC_F9,        KC_F10,       KC_F11,     KC_F12,     KC_RBRC,
       KC_TRNS, KC_TRNS,      M(LPAREN_NO), M(RPAREN_NO), KC_TRNS,    KC_TRNS,    KC_RBRC,
                KC_TRNS,      KC_LBRC,      KC_RBRC,      KC_TRNS,    KC_TRNS,    KC_RBRC,
       KC_TRNS, KC_TRNS,      M(LCQW_NO),   M(RCQW_NO),   KC_TRNS,    KC_UP,      KC_TRNS,
                              KC_TRNS,      KC_LEFT,      KC_DOWN,    KC_RIGHT,   KC_RIGHT,
       KC_TRNS, KC_TRNS,
       KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS
)
};

const uint16_t PROGMEM fn_actions[] = {
    [1] = ACTION_MACRO(LPAREN_NO),
    [2] = ACTION_MACRO(RPAREN_NO),
    [3] = ACTION_MACRO(LCURLY_NO), // curlies for Software-remapped Dvorak
    [4] = ACTION_MACRO(RCURLY_NO),
    [5] = ACTION_MACRO(LCQW_NO), // curlies for Firmware-remapped Dvorak
    [6] = ACTION_MACRO(RCQW_NO)
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
    keyevent_t event = record->event;

    switch(id) {
        case LPAREN_NO:
            return (event.pressed ? MACRO ( D(LSFT), T(9), U(LSFT), END ) : MACRO_NONE);
        case RPAREN_NO:
            return (event.pressed ? MACRO ( D(LSFT), T(0), U(LSFT), END ) : MACRO_NONE);
        case LCURLY_NO:
            return (event.pressed ? MACRO ( D(LSFT), T(MINUS), U(LSFT), END ) : MACRO_NONE);
        case RCURLY_NO:
            return (event.pressed ? MACRO ( D(LSFT), T(EQL), U(LSFT), END ) : MACRO_NONE);
        case LCQW_NO:
            return (event.pressed ? MACRO ( D(LSFT), T(LBRC), U(LSFT), END ) : MACRO_NONE);
        case RCQW_NO:
            return (event.pressed ? MACRO ( D(LSFT), T(RBRC), U(LSFT), END ) : MACRO_NONE);
    }
    return MACRO_NONE;
}

// Runs just one time when the keyboard initializes.
void * matrix_init_user(void) {
    return NULL;
}

// Runs constantly in the background, in a loop.
void * matrix_scan_user(void) {

    uint8_t layer = biton32(layer_state);

    ergodox_board_led_off();
    if (layer & 1)
            ergodox_right_led_1_on();
    else
            ergodox_right_led_1_off();
    if (layer & 2)
            ergodox_right_led_2_on();
    else
            ergodox_right_led_2_off();
    if (layer & 4)
            ergodox_right_led_3_on();
    else
            ergodox_right_led_3_off();
    return NULL;
};
