#include "oled.h"
#include "joystick.h"
#include "stdio.h"
#include "ui_internal.h"
#include "ui_entrypoints.h"

#define BACKLIST_SIZE 3
//Keep track of previous locations
menu_item_t* backlist[BACKLIST_SIZE] = { NULL, NULL, NULL };

menu_item_t* on_back_selected(menu_item_t* caller) {
    if(backlist[0] != NULL) {
        menu_item_t* next = backlist[0];
        for(int i = 1; i < BACKLIST_SIZE; ++i) {
            backlist[i-1] = backlist[i];
        }
        return next;
    }
    return caller;
}

menu_item_t back_item = {
    "Back",
    on_back_selected,
    &back_item,
    &back_item
};


void print_menu_item(const menu_item_t* item, uint8_t page) {
    if (item != NULL) {
        oled_write_string(item->item_text, page, 0);
    }
}

void print_selection(const menu_item_t* item, uint8_t page) {
    if(item != NULL) {
        oled_write_string_inverse(item->item_text, page, 0);
    }
}

menu_item_t* current_item_p = NULL;
char* menu_header_p = "Menu";

void ui_display() {
    oled_clear();
    oled_write_string(menu_header_p, 0, 0);
    print_menu_item(current_item_p->prev, 2);
    print_selection(current_item_p, 3);
    print_menu_item(current_item_p->next, 4);
    if(backlist[0] != NULL) {
        print_menu_item(&back_item, 5);
    }
}

void ui_move_up() {
    current_item_p = current_item_p->prev;
    ui_display();
}


void ui_move_down() {
    current_item_p = current_item_p->next;
    ui_display();
}

void ui_select() {
    current_item_p = current_item_p->on_select(current_item_p);
}


/*---Exposed functions---------------------------*/


void ui_init() {
    current_item_p = UI_MAIN_MENU_ENTRYPOINT;
    init_joystick();
    ui_display();
}

void ui_update() {
    static int last_y = 0;
    static int last_selected = 0;
    int curr_y = read_joystick_y();
    if (last_y < 20 && last_y > -20) {
        if(curr_y >= 20) {
            ui_move_up();
        } else if(curr_y <= -20) {
            ui_move_down();
        }
    }
    last_y = curr_y;
    if (read_joystick_select()) {
        if(!last_selected) {
            ui_select();
            last_selected = 1;
        }
    } else {
        last_selected = 0;
    }
}

