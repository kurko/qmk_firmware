/* Copyright 2022 Alex Oliveira <@kurko>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H

enum layers {
    _NORMAL = 0,
    _SYM_NUM,
    _FUNCTION,
    _ADJUST,
};


// Aliases for readability
#define NORMAL   DF(_NORMAL)
#define SYM_NUM  DF(_SYM_NUM)
#define FKEYS    MO(_FUNCTION)
#define ADJUST   MO(_ADJUST)

#define CTL_ESC  MT(MOD_LCTL, KC_ESC)
#define CTL_QUOT MT(MOD_RCTL, KC_QUOTE)
#define CTL_MINS MT(MOD_RCTL, KC_MINUS)
/*
 * This shortcut is using for toggling input sources from e.g US to US
 * International. It's using HYPR because it's very unlikely that that would be
 * set in a new system, so there are less chances that this would cause trouble
 * in new computers.
 */
#define CHANGE_SOURCE HYPR(KC_S)
/*
 * Note: LAlt/Enter (ALT_ENT) is not the same thing as the keyboard shortcut Alt+Enter.
 * The notation `mod/tap` denotes a key that activates the modifier `mod` when held down, and
 * produces the key `tap` when tapped (i.e. pressed and released).
 */
#define ALT_ENT  MT(MOD_LALT, KC_ENT)

#ifdef RGBLIGHT_ENABLE
void keyboard_post_init_user(void) {
  rgblight_enable_noeeprom(); // Enables RGB, without saving settings
  /*
   * Starts out with a dark green color.
   */
  rgblight_sethsv_noeeprom(85, 255, 60);
  rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
}
#endif

/*
 * Sets the RGB colors for each layer.
 */
layer_state_t layer_state_set_user(layer_state_t state) {
#ifdef RGBLIGHT_ENABLE
    switch (get_highest_layer(state)) {
      case _NORMAL:
          rgblight_sethsv_noeeprom(85, 255, 60);
          break;
      case _SYM_NUM:
          //rgb_matrix_set_color_all(0,0,0);
          rgblight_sethsv_noeeprom(85, 255, 100);
          break;
      case _FUNCTION:
          rgblight_sethsv_noeeprom(148, 255, 100);
          break;
      case _ADJUST:
          rgblight_sethsv_noeeprom(148, 255, 130);
          break;
      default:
          rgblight_sethsv_noeeprom(0, 255, 100);
          break;
    }
#endif
    return state;
}

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
 * Normal Layer: this is the layer used for writing. The keyboard always gets
 * back to this layer (usually automatically).
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |  Tab   |   Q  |   W  |   E  |   R  |   T  |                              |   Y  |   U  |   I  |   O  |   P  |  Bksp  |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |Ctrl/Esc|   A  |   S  |   D  |   F  |   G  |                              |   H  |   J  |   K  |   L  | ;  : |  ' "   |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * | LShift |   Z  |   X  |   C  |   V  |   B  |      |      |  |  L1  |      |   N  |   M  | ,  < | . >  | /  ? |   \    |
 * `----------------------+------+------+------+--  --+------|  |------+--  --+------+------+------+----------------------'
 *                        |      | LAlt | LGUI | Space|      |  | Temp | Enter| RGUI | RAlt | Menu |
 *                        |      |      |      |      |      |  |  L1  |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_NORMAL] = LAYOUT(
        KC_TAB,  KC_Q, KC_W, KC_E, KC_R, KC_T,                                     KC_Y, KC_U, KC_I,    KC_O,   KC_P,    KC_BSPC,
        CTL_ESC, KC_A, KC_S, KC_D, KC_F, KC_G,                                     KC_H, KC_J, KC_K,    KC_L,   KC_SCLN, KC_QUOT,
        KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B,       KC_NO,  KC_NO, TO(1), KC_NO,  KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_BSLS,
                    CHANGE_SOURCE, KC_LALT, KC_LGUI, KC_SPC, KC_NO, TT(1), KC_ENT, KC_RGUI, KC_RALT, KC_NO
    ),

/*
 * Symbols and Numbers Layer: this is used usually in temporary mode, as in,
 * thumb is clicking TT(1) while index or middle fingers accessing some other
 * key.
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |  ` ~   |  1 ! |  2 @ |  3 # |  4 $ |  5 % |                              |  6 ^ |  7 & |  8 * |  9 ( |  0 ) |  Bksp  |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |Ctrl/Esc|      |      |      |      |      |                              |  - _ |  = + |UArrow|  [ { |  ] } |  -  _  |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * | LShift |      |      |      |      |      |      |      |  |  L2  |      |      |LArrow|DArrow|RArrow|      |        |
 * `----------------------+------+------+------+--  --+------|  |------+------+------+------+------+----------------------'
 *                        |      | LAlt | LGUI | Space|  L1  |  | Temp | Enter| RGUI | RAlt |      |
 *                        |      |      |      |      |      |  |  L2  |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_SYM_NUM] = LAYOUT(
        KC_GRV,  KC_1,  KC_2,  KC_3,  KC_4,  KC_5,                                       KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
        CTL_ESC, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                                      KC_MINS, KC_EQL,  KC_UP,   KC_LBRC, KC_RBRC, CTL_MINS,
        KC_LSFT, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,     KC_NO,  KC_NO,  TO(2),  KC_NO,   KC_NO,   KC_LEFT, KC_DOWN, KC_RGHT, KC_NO,   KC_NO,
                               KC_NO, KC_LALT, KC_LGUI, KC_SPC, TO(0),  TT(2),  KC_ENT,  KC_RGUI, KC_RALT, KC_NO
    ),

/*
 * Functions Layer: this focused on function keys and less used keys
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |  F1  |  F2  |  F3  |  F4  |  F5  |                              |  F6  |  F7  |  F8  |  F9  |  F10 |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |Ctrl/Esc|      |      |      |      |      |                              |      |      |      |      |  F11 |        |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * | LShift |      |      |      |      |      |      |      |  |  L3  |      |      |      |      |      |  F12 |        |
 * `----------------------+------+------+------+--  --+------|  |------+------+------+------+------+----------------------'
 *                        |      | LAlt | LGUI | Space|  L0  |  | Temp | Enter| RGUI | RAlt |      |
 *                        |      |      |      |      |      |  |  L3  |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_FUNCTION] = LAYOUT(
        KC_NO,   KC_F1, KC_F2, KC_F3, KC_F4, KC_F5,                                      KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_NO,
        CTL_ESC, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                                      KC_NO, KC_NO, KC_NO, KC_NO, KC_F11, KC_NO,
        KC_LSFT, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,      KC_NO,  KC_NO, TO(3), KC_NO,    KC_NO, KC_NO, KC_NO, KC_NO, KC_F12, KC_NO,
                               KC_NO, KC_LALT, KC_LGUI,  KC_SPC, TO(0), TT(3), KC_ENT,   KC_LGUI, KC_RALT, KC_NO
    ),

    [_ADJUST] = LAYOUT(
      _______, _______, _______, NORMAL , _______, _______,                                    _______, _______, _______, _______,  _______, _______,
      _______, _______, _______, SYM_NUM, _______, _______,                                    RGB_TOG, RGB_SAI, RGB_HUI, RGB_VAI,  RGB_MOD, _______,
      _______, _______, _______, _______, _______, _______,_______, _______, TO(0),   _______, _______, RGB_SAD, RGB_HUD, RGB_VAD, RGB_RMOD, _______,
                                 _______, _______, _______,_______, _______, _______, _______, _______, _______, _______
    ),

 /*
  * Layer template
  *
  * ,-------------------------------------------.                              ,-------------------------------------------.
  * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
  * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
  * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
  * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
  * |        |      |      |      |      |      |      |      |  |      |      |      |      |      |      |      |        |
  * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
  *                        |      |      |      |      |      |  |      |      |      |      |      |
  *                        |      |      |      |      |      |  |      |      |      |      |      |
  *                        `----------------------------------'  `----------------------------------'
  */
  /* [_LAYERINDEX] = LAYOUT(
   *   _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
   *   _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
   *   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
   *                              _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
   * ),
   */
};

#ifdef ENCODER_ENABLE
bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        if (get_highest_layer(layer_state) == 0) {
            // L/R arrows
            if (clockwise) {
                tap_code(KC_DOWN);
            } else {
                tap_code(KC_UP);
            }
        } else if (get_highest_layer(layer_state) == 1) {
            // U/D arrows
            if (clockwise) {
                tap_code(KC_RIGHT);
            } else {
                tap_code(KC_LEFT);
            }
        } else if (get_highest_layer(layer_state) == 2) {
            // Page up/Page down
            if (clockwise) {
                tap_code(KC_PGDN);
            } else {
                tap_code(KC_PGUP);
            }
        }
    } else if (index == 1) {
        // Volume control
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    }
    return false;
}
#endif
