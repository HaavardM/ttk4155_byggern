#include "oled.h"
#include "joystick.h"
#include "stdio.h"

typedef void (* const callback_func)(void);

typedef struct menu_item_t menu_item_t;

struct menu_item_t {
    char* item_text;
    callback_func on_select;
    menu_item_t* prev;
    menu_item_t* next;
};


extern menu_item_t play_item;
extern menu_item_t highscore_item;
extern menu_item_t settings_item;
extern menu_item_t about_item;
extern menu_item_t back_item;

menu_item_t* current_item_p = &play_item;
char* menu_header_p = "Menu";

char* empty_string = "               ";

#define BACKLIST_SIZE 3
//Keep track of previous locations
menu_item_t* backlist[BACKLIST_SIZE] = { NULL, NULL, NULL };

void on_play_select() {
    printf("Play\n\r");
}

menu_item_t play_item = {
    "Play",
    on_play_select,
    &about_item,
    &highscore_item
};


void on_highscore_selected() {
    printf("Sara vinner alltid...\n\r");
    printf("Emma kommer alltid sist... \n\r");
    printf("H-Bird er for kul\n\r");
}

menu_item_t highscore_item = {
    "Highscore",
    on_highscore_selected,
    &play_item,
    &settings_item
};

void on_settings_selected() {
    printf("Settings menu\n\r");
}

menu_item_t settings_item = {
    "Settings",
    on_settings_selected,
    &highscore_item,
    &about_item
};

void on_about_selected() {
    printf("Vakkert bilde laget av Sara: \n\r");
}

menu_item_t about_item = {
    "About",
    on_about_selected, 
    &settings_item,
    &play_item
};

void on_back_selected() {
    if(backlist[0] != NULL) {
        current_item_p = backlist[0];
        for(int i = 1; i < BACKLIST_SIZE; ++i) {
            backlist[i-1] = backlist[i];
        }
    }
}

menu_item_t back_item = {
    "Back",
    on_back_selected,
    &back_item,
    &back_item
};



void print_menu_item(const menu_item_t* item, uint8_t page) {
    if (item != NULL) {
        oled_write_string(item->item_text, page);
    }
}

void print_selection(const menu_item_t* item, uint8_t page) {
    if(item != NULL) {
        oled_write_string_inverse(item->item_text, page);
    }
}

void ui_display() {
    oled_clear();
    oled_write_string(menu_header_p, 0);
    print_menu_item(current_item_p->prev, 2);
    print_selection(current_item_p, 3);
    print_menu_item(current_item_p->next, 4);
    if(backlist[0] != NULL) {
        print_menu_item(&back_item, 5);
    }
}

int validate_ui() {
    if(current_item_p == NULL) {
        return 0;
    }
    if(current_item_p->next == NULL) {
        return 0;
    }
    if(current_item_p->prev == NULL) {
        return 0;
    }
    return 1;

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
    current_item_p->on_select();
}

void ui_update() {
    

}




