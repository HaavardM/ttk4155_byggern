#include "ui_internal.h"
#include "can_msg_defines.h"
#include "can.h"
#include "oled.h"
#include "functions.h"
#include "highscore.h"
#include <stdio.h>
#include <string.h>


extern menu_item_t play_item;
extern menu_item_t highscore_item;
extern menu_item_t settings_item;
extern menu_item_t about_item;
extern menu_item_t back_item;

menu_item_t* UI_MAIN_MENU_ENTRYPOINT = &play_item;

menu_item_t* on_play_select(menu_item_t* caller) {
    ui_disable();
    oled_clear();
  
    //----LINE 0-----
    oled_write_string_inverse("                ", 0, 0);

    //----LINE 1-----
    oled_write_string("   ",1,0);
    oled_write_string_inverse(" ",1,8*3);
    oled_write_string(" ",1,8*4);
    oled_write_string_inverse("   ",1,8*5);
    oled_write_string("  ",1,8*8);
    oled_write_string_inverse(" ",1,8*10);
    oled_write_string(" ",1,8*11);
    oled_write_string_inverse("   ",1,8*12);
    oled_write_string(" ",1,8*15);

    //----LINE 2-----
    oled_write_string(" ",2,0);
    oled_write_string_inverse("  ",2,8*1);
    oled_write_string(" ",2,8*3-4);
    oled_write_string_inverse(" ",2,8*4-4);
    oled_write_string(" ",2,8*4);
    oled_write_string_inverse("  ",2,8*5);
    oled_write_string(" ",2,8*7);
    oled_write_string_inverse("  ",2,8*8);
    oled_write_string(" ",2,8*10);
    oled_write_string_inverse(" ",2,8*11);
    oled_write_string(" ",2,8*12);
    oled_write_string_inverse(" ",2,8*13);
    oled_write_string(" ",2,8*14);
    oled_write_string_inverse(" ",2,8*15);

    //----LINE 3-----
    oled_write_string("   ",3,0);
    oled_write_string_inverse(" ",3,8*3);
    oled_write_string(" ",3,8*4);
    oled_write_string_inverse("  ",3,8*5);
    oled_write_string("    ",3,8*7);
    oled_write_string_inverse("  ",3,8*11);
    oled_write_string(" ",3,8*13);
    oled_write_string_inverse("  ",3,8*14);

    //----LINE 4-----
    oled_write_string(" ",4,0);
    oled_write_string_inverse("   ",4,8*1);
    oled_write_string(" ",4,8*4);
    oled_write_string_inverse("  ",4,8*5);
    oled_write_string(" ",4,8*7);
    oled_write_string_inverse("  ",4,8*8);
    oled_write_string(" ",4,8*10);
    oled_write_string_inverse("  ",4,8*11);
    oled_write_string(" ",4,8*13);
    oled_write_string_inverse("  ",4,8*14);

    //----LINE 5-----
    oled_write_string(" ",5,0);
    oled_write_string_inverse("   ",5,8*1);
    oled_write_string(" ",5,8*4);
    oled_write_string_inverse("  ",5,8*5);
    oled_write_string(" ",5,8*7);
    oled_write_string_inverse("  ",5,8*8);
    oled_write_string(" ",5,8*10);
    oled_write_string_inverse("  ",5,8*11);
    oled_write_string(" ",5,8*13);
    oled_write_string_inverse("  ",5,8*14);

    //----LINE 6-----
    oled_write_string(" ",6,0);
    oled_write_string_inverse("   ",6,8*1);
    oled_write_string("   ",6,8*4);
    oled_write_string_inverse(" ",6,8*6+6);
    oled_write_string(" ",6,8*7);
    oled_write_string_inverse("  ",6,8*8);
    oled_write_string(" ",6,8*10);
    oled_write_string_inverse("  ",6,8*11);
    oled_write_string(" ",6,8*13);
    oled_write_string_inverse("  ",6,8*14);

    //----LINE 7-----
    oled_write_string_inverse("                ", 7, 0);

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
    ui_disable();
	oled_clear();

    for (int i = 0; i < 5; ++i){
        int a = get_highscore(i);//get_highscore(i);
        char buffer[10];
        itoa(i+1, buffer, 10);
        oled_write_string(buffer, i+1, 0);
        oled_write_string(":", i+1, 8);
        itoa(a, buffer, 10);
        oled_write_string(buffer, i+1, 16);
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
    ui_disable();
    oled_clear();
    oled_clear();
    oled_write_string_inverse("   ###     ###  ", 0, 0);
    oled_write_string_inverse(" ######   ######", 1, 0);
    oled_write_string_inverse(" ####### #######", 2, 0);
    oled_write_string_inverse("  ############# ", 3, 0);
    oled_write_string_inverse("   ###########  ", 4, 0);
    oled_write_string_inverse("     #######    ", 5, 0);
    oled_write_string_inverse("       ###      ", 6, 0);
    oled_write_string_inverse("        #       ", 7, 0);
    printf("Vakkert bilde laget av Sara: \n\r");
    return caller;
}

menu_item_t about_item = {
    "About",
    on_about_selected, 
    &settings_item,
    &play_item
};

