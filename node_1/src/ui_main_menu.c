#include "ui_internal.h"
#include "ui_entrypoints.h"
#include "can_msg_defines.h"
#include "can.h"
#include "oled.h"
#include "functions.h"
#include "highscore.h"
#include <stdio.h>



extern menu_item_t play_item;
extern menu_item_t highscore_item;
extern menu_item_t settings_item;
extern menu_item_t about_item;
extern menu_item_t back_item;

menu_item_t* UI_MAIN_MENU_ENTRYPOINT = &play_item;


menu_item_t* on_play_select(menu_item_t* caller) {
    update_backlist(caller);
    ui_disable();
    oled_clear();
    draw_play(); 

    printf("Play\n\r");
	can_message_t msg;
	msg.id = MSG_START_GAME;
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
    update_backlist(caller);
    ui_disable();
	oled_clear();
    //draw_header();
    oled_write_string("HIGHSCORE", 0, 0);
    oled_write_string_inverse("   Name   Score ",1,0);
    for (int i = 0; i < 5; i++){
        int score = get_highscore(i);//get_highscore(i);
        char* name = get_name(i);
        char buffer[10];
        itoa(i+1, buffer, 10);
        oled_write_string(buffer, i+2, 0);
        oled_write_string("  ", i+2, 8);
        oled_write_string(name, i+2, 24);
        itoa(score, buffer, 10);
        oled_write_string(buffer, i+2, 80);
        
    }
    
    return caller;
}


menu_item_t highscore_item = {
    "Highscore",
    on_highscore_selected,
    &play_item,
    &settings_item
};

menu_item_t* on_settings_selected(menu_item_t* caller) {
    update_backlist(caller);
    printf("Settings menu\n\r");
    return UI_SETTINGS_MENU_ENTRYPOINT;
}

menu_item_t settings_item = {
    "Settings",
    on_settings_selected,
    &highscore_item,
    &about_item
};

menu_item_t* on_about_selected(menu_item_t* caller) {
    update_backlist(caller);
    ui_disable();
    oled_clear();
    oled_clear();
    draw_heart();
    return caller;
}

menu_item_t about_item = {
    "About",
    on_about_selected, 
    &settings_item,
    &play_item
};

