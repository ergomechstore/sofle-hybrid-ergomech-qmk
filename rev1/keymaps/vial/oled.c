 /* Copyright 2020 Josef Adamcik
  * Modification for VIA support and RGB underglow by Jens Bonk-Wiltfang
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

//Sets up what the OLED screens display.

#ifdef OLED_ENABLE

static void render_logo(void) {
    static const char PROGMEM raw_logo[] = {
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,128,192,192,192,192,128,224,248,248,248,  8,252,252,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,248,252,204,204,  8,  0,  0,  0,248,188,140,136,248,240,  0,  0,  0,248, 24, 12,204,204,200,  0,  0,224,248, 24, 12, 24,248,240,  0,  0,248,248,112,224,224,112,248,248,  0,  0,248,252,204,204, 12,  0,  0,  0,240,248, 12, 12, 12,  0,  0,  0,248,248,192,192,192,248,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 62,254,252,252, 12, 62,238, 62, 31, 15, 25,237, 13, 13, 31, 31, 30,127, 63, 56, 59,255,120,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 31, 31, 24, 24, 24,  0,  0,  0, 31,  5,  1,  3, 15, 28,  0,  0,  0, 15, 28, 24, 24, 31, 31,  0,  0,  3, 15, 28, 24, 24, 15,  7,  0,  0, 15, 31,  0,  0,  0,  0, 31, 15,  0,  0, 15, 31, 24, 24, 24,  0,  0,  0, 15, 15, 24, 24, 24,  0,  0,  0, 31, 15,  0,  0,  0, 31,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  7,  7,  4, 15, 29,255,255,142,167,179,176,216,248,248,252,252,252, 24,254,253,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,120,252,204,140,136,  0,  0,  0,  0, 12, 12,252,252, 12,  8,  0,  0,224,248, 28, 12, 12,248,240,  0,  0,248,252,140,140,220,248,112,  0,  0,248,252,204,204, 12,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,  1,  1,  7, 31, 31, 31, 16, 63, 63,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 12, 12, 24, 25, 15,  7,  0,  0,  0,  0,  0, 15, 15,  0,  0,  0,  0,  3, 15, 12, 24, 12, 15,  7,  0,  0, 15, 15,  1,  1,  7, 14,  8,  0,  0, 15, 31, 24, 24, 24,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    };
    oled_write_raw_P(raw_logo, sizeof(raw_logo));
}

static void print_status_narrow(void) {
    // Print current mode
    oled_write_P(PSTR("\n\n"), false);

    switch (get_highest_layer(layer_state)) {
        case 0:
            oled_write_ln_P(PSTR("Qwrt"), false);
            break;
        case 1:
            oled_write_ln_P(PSTR("Clmk"), false);
            break;
        default:
            oled_write_P(PSTR("Mod\n"), false);
            break;
    }
    oled_write_P(PSTR("\n\n"), false);
    // Print current layer
    oled_write_ln_P(PSTR("LAYER"), false);
    switch (get_highest_layer(layer_state)) {
        case 0:
        case 1:
            oled_write_P(PSTR("Base\n"), false);
            break;
        case 2:
            oled_write_P(PSTR("Raise"), false);
            break;
        case 3:
            oled_write_P(PSTR("Lower"), false);
            break;
        default:
            oled_write_ln_P(PSTR("Undef"), false);
    }
    oled_write_P(PSTR("\n\n"), false);
    led_t led_usb_state = host_keyboard_led_state();
    oled_write_ln_P(PSTR("CPSLK"), led_usb_state.caps_lock);
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (is_keyboard_master()) {
        return OLED_ROTATION_270;
    } else {
        return OLED_ROTATION_180;
    }
    return rotation;
}

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        print_status_narrow();
    } else {
        render_logo();
    }
	return false;
}

#endif
