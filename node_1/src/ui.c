#include "oled.h"
#include "joystick.h"
#include "stdio.h"
#include "ui_internal.h"
#include "ui_entrypoints.h"
#include "highscore.h"
#include <string.h>
#include "ui.h"

#define BACKLIST_SIZE 3
int disabled = 0;
//Keep track of previous locations
menu_item_t* backlist[BACKLIST_SIZE] = { NULL, NULL, NULL };

menu_item_t* on_back_selected(menu_item_t* caller) {
    ui_enable();
    for (int i = BACKLIST_SIZE-1; i >= 0; i--){
        if (backlist[i] != NULL){
            menu_item_t* temp = backlist[i];
            backlist[i] = NULL;
            return temp;
        }
    }
    return caller;
/*
    if(backlist[0] != NULL) {
        menu_item_t* next = backlist[0];
        for(int i = 1; i < BACKLIST_SIZE; ++i) {
            backlist[i-1] = backlist[i];
        }
        return next;
    }
    return caller;
*/
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
	menu_item_t* temp = current_item_p; 
    current_item_p = current_item_p->on_select(current_item_p);
	if (current_item_p != temp){
        ui_display();
		for (int i = 0; i < BACKLIST_SIZE; ++i){
			if (backlist[i] == NULL){
                backlist[i] = temp;
            }
		}
	}
}


/*---Exposed functions---------------------------*/


void ui_init() {
    current_item_p = UI_MAIN_MENU_ENTRYPOINT;
    init_joystick();
    ui_display();
}

void ui_update() {
    static int lst_back_butt = 0;
    int back_butt = read_left_button_select();

    if (back_butt && !lst_back_butt){
        current_item_p = on_back_selected(current_item_p);
        ui_display();
    }
    lst_back_butt = back_butt;
    if (disabled){
        return;
    }
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

void ui_disable(){
    disabled = 1;
}

void ui_enable(){
    disabled = 0;
}

void print_backlist(){
    printf("\n");
    for (int i = 0; i < BACKLIST_SIZE; i++){
        printf("%s\n\r",backlist[i]->item_text);
    }
    printf("\n");
}

void update_backlist(menu_item_t* caller){
    for (int i = 0; i < BACKLIST_SIZE; i++){
        if (backlist[i] == NULL){
            backlist[i] = caller;
            return;
        }
        
    }
}