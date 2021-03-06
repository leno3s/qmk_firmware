#include QMK_KEYBOARD_H


#define _QWERTY 0
#define _LOWER 1
#define _RAISE 2
#define _ADJUST 16

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST,
};

#define EISU LALT(KC_GRV)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /* Qwerty
   * ,----------------------------------------------------------------------------------------------------------------------.
   * | ESC  |   1  |   2  |   3  |   4  |   5  |LClick|                    |RClick|   6  |   7  |   8  |   9  |   0  |  =   |
   * |------+------+------+------+------+------+------+--------------------+------+------+------+------+------+------+------|
   * | Tab  |   Q  |   W  |   E  |   R  |   T  |   `  |                    |   -  |   Y  |   U  |   I  |   O  |   P  |  \   |
   * |------+------+------+------+------+------+------+--------------------+------+------+------+------+------+------+------|
   * | EISU |   A  |   S  |   D  |   F  |   G  |   [  |                    |   ]  |   H  |   J  |   K  |   L  |   ;  | Enter|
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |LShift|   Z  |   X  |   C  |   V  |   B  |      |Insert|      | Menu |      |   N  |   M  |   ,  |   .  |   /  |  '  '|
   * |-------------+------+------+------+------| Space|------+------+------| Space|------+------+------+------+-------------|
   * | Ctrl |  GUI |   X  | Lower||||||||  Alt |      |  Del |||||||| Bksp |      |   .  |||||||| Lower| Home |  End |RShift|
   * ,----------------------------------------------------------------------------------------------------------------------.
   */
  [_QWERTY] = LAYOUT( \
    KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_BTN1,                        KC_BTN2, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_EQUAL, \
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_GRV ,                        KC_MINS, KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSLS, \
    EISU,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_LBRC,                        KC_RBRC, KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_ENT, \
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,             KC_INS ,       KC_APP,          KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_QUOT, \
    KC_LCTL, KC_LGUI, KC_X,    LOWER,          KC_LALT,   KC_SPC , KC_DEL,        KC_BSPC, KC_SPC, KC_DOT,           LOWER,   KC_HOME, KC_END,  KC_RSFT \
  ),

  /* Lower
   * ,----------------------------------------------------------------------------------------------------------------------.
   * |      |  F1  |  F2  |  F3  |  F4  |  F5  |  F11 |                    |  F11 |  F6  |  F7  |  F8  |  F9  |  F10 |      |
   * |------+------+------+------+------+------+------+--------------------+------+------+------+------+------+------+------|
   * |      |      |  Up  |      |      |      |  F12 |                    |  F12 |      |RClick|  MUp |LClick|      |      |
   * |------+------+------+------+------+------+------+--------------------+------+------+------+------+------+------+------|
   * |      | Left | Down | Right|      |      |      |                    |      |      | MLeft|MDown |MRight|      |      |
   * |------+------+------+------+------+------+---------------------------+------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |                    |      | HLeft|  HUp |  [   |   ]  |      |      |
   * |-------------+------+------+------+------+------+------+------+------+------+------+------+------+------+-------------|
   * |      |      | PSCR |      ||||||||      |      |      ||||||||      |      |      ||||||||      | PGUP | PGDN |      |
   * ,----------------------------------------------------------------------------------------------------------------------.
   */
  [_LOWER] = LAYOUT(
    _______,  KC_F1,  KC_F2,   KC_F3,    KC_F4,   KC_F5,   KC_F11,                          KC_F11,  KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F12,  \
    _______, _______, KC_UP,   _______,  _______, _______, KC_F12,                          KC_F12,  _______, KC_BTN1, KC_MS_U, KC_BTN2, _______, _______, \
    _______, KC_LEFT, KC_DOWN, KC_RIGHT, _______, _______, _______,                         _______, _______, KC_MS_L, KC_MS_D, KC_MS_R, _______, _______, \
    _______, _______, _______, _______,  _______, _______,          _______,       _______,          KC_WH_L, KC_WH_D, KC_LBRC, KC_RBRC, _______, _______, \
    _______, _______, KC_PSCR, _______,           _______, _______, _______,       _______, _______, _______,          _______, KC_PGUP , KC_PGDN, _______  \
  )
};

#ifdef AUDIO_ENABLE
float tone_qwerty[][2]     = SONG(QWERTY_SOUND);
#endif

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
         print("mode just switched to qwerty and this is a huge string\n");
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
      break;
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
  }
  return true;
}
