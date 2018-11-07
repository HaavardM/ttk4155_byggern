#include "ui_internal.h"
#include "can_msg_defines.h"
#include "can.h"
#include <stdio.h>


extern menu_item_t play_item;
extern menu_item_t highscore_item;
extern menu_item_t settings_item;
extern menu_item_t about_item;
extern menu_item_t back_item;

menu_item_t* UI_MAIN_MENU_ENTRYPOINT = &play_item;

menu_item_t* on_play_select(menu_item_t* caller) {
    printf("Play\n\r");
	can_message_t msg;
	msg.id = start_game;
	can_msg_send(&msg); 
    return caller;
}

menu_item_t play_item = {
    "Play",
    on_play_select,
    &about_item,
    &highscore_item
};


menu_item_t* on_highscore_selected(menu_item_t* caller) {
    printf("Sara er en taper...\n\r");
    printf("Emma vinner!! \n\r");
    printf("H-Bird er for kul\n\r");
	
    return caller;
}

menu_item_t highscore_item = {
    "Highscore",
    on_highscore_selected,
    &play_item,
    &settings_item
};

menu_item_t* on_settings_selected(menu_item_t* caller) {
    printf("Settings menu\n\r");
    return caller;
}

menu_item_t settings_item = {
    "Settings",
    on_settings_selected,
    &highscore_item,
    &about_item
};

menu_item_t* on_about_selected(menu_item_t* caller) {
    printf("Vakkert bilde laget av Sara: \n\r");
    return caller;
}

menu_item_t about_item = {
    "About",
    on_about_selected, 
    &settings_item,
    &play_item
};

