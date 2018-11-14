#include "ui_internal.h"
#include "can_msg_defines.h"
#include "can.h"
#include "oled.h"
#include <stdio.h>


extern menu_item_t play_item;
extern menu_item_t highscore_item;
extern menu_item_t settings_item;
extern menu_item_t about_item;
extern menu_item_t back_item;

menu_item_t* UI_MAIN_MENU_ENTRYPOINT = &play_item;

menu_item_t* on_play_select(menu_item_t* caller) {
    ui_disable();
    oled_clear();
    
    oled_write_string_inverse("                ", 0, 0);
    oled_write_string_inverse("### #   ## #   #", 1, 0);
    oled_write_string_inverse("#  ##  #  # # # ", 2, 0);
    oled_write_string_inverse("### #  ####  #  ", 3, 0);
    oled_write_string_inverse("#   #  #  #  #  ", 4, 0);
    oled_write_string_inverse("#   #  #  #  #  ", 5, 0);
    oled_write_string_inverse("#   ####  #  #  ", 6, 0);
    oled_write_string_inverse("                ", 7, 0);
    
/*
    //----LINE 0-----
    oled_write_string_inverse("                ", 0, 0);

    //----LINE 1-----
    oled_write_string("   ",1,0);
    oled_write_string_inverse(" ",1,3);
    oled_write_string(" ",1,4);
    oled_write_string_inverse("   ",1,5);
    oled_write_string("  ",1,8);
    oled_write_string_inverse(" ",1,10);
    oled_write_string(" ",1,11);
    oled_write_string_inverse("   ",1,12);
    oled_write_string(" ",1,15);

    //----LINE 2-----
    oled_write_string(" ",2,0);
    oled_write_string_inverse("  ",2,1);
    oled_write_string("  ",2,3);
    oled_write_string_inverse("  ",2,5);
    oled_write_string(" ",2,7);
    oled_write_string_inverse("  ",2,8);
    oled_write_string(" ",2,10);
    oled_write_string_inverse(" ",2,11);
    oled_write_string(" ",2,12);
    oled_write_string_inverse(" ",2,13);
    oled_write_string(" ",2,14);
    oled_write_string_inverse(" ",2,15);

    //----LINE 3-----
    oled_write_string("   ",3,0);
    oled_write_string_inverse(" ",3,3);
    oled_write_string(" ",3,4);
    oled_write_string_inverse("  ",3,5);
    oled_write_string("    ",3,7);
    oled_write_string_inverse("  ",3,11);
    oled_write_string(" ",3,13);
    oled_write_string_inverse("  ",3,14);

    //----LINE 4-----
    oled_write_string(" ",4,0);
    oled_write_string_inverse("   ",4,1);
    oled_write_string(" ",4,4);
    oled_write_string_inverse("  ",4,5);
    oled_write_string(" ",4,7);
    oled_write_string_inverse("  ",4,8);
    oled_write_string(" ",4,10);
    oled_write_string_inverse("  ",4,11);
    oled_write_string(" ",4,13);
    oled_write_string_inverse("  ",4,14);

    //----LINE 5-----
    oled_write_string(" ",5,0);
    oled_write_string_inverse("   ",5,1);
    oled_write_string(" ",5,4);
    oled_write_string_inverse("  ",5,5);
    oled_write_string(" ",5,7);
    oled_write_string_inverse("  ",5,8);
    oled_write_string(" ",5,10);
    oled_write_string_inverse("  ",5,11);
    oled_write_string(" ",5,13);
    oled_write_string_inverse("  ",5,14);

    //----LINE 6-----
    oled_write_string(" ",6,0);
    oled_write_string_inverse("   ",6,1);
    oled_write_string("    ",6,4);
    oled_write_string_inverse("  ",6,8);
    oled_write_string(" ",6,10);
    oled_write_string_inverse("  ",6,11);
    oled_write_string(" ",6,13);
    oled_write_string_inverse("  ",6,14);

    //----LINE 7-----
    oled_write_string_inverse("                ", 0, 0);
*/
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
    oled_write_string("NO. 1: Sara", 0, 0);
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
    ui_disable();
    oled_clear();
    oled_clear();
    oled_write_string_inverse("   ##      ##   ", 0, 0);
    oled_write_string_inverse("  ####    ####  ", 1, 0);
    oled_write_string_inverse(" ######  ###### ", 2, 0);
    oled_write_string_inverse("  ############  ", 3, 0);
    oled_write_string_inverse("   ##########   ", 4, 0);
    oled_write_string_inverse("    ########    ", 5, 0);
    oled_write_string_inverse("     ######     ", 6, 0);
    oled_write_string_inverse("      ###       ", 7, 0);
    printf("Vakkert bilde laget av Sara: \n\r");
    return caller;
}

menu_item_t about_item = {
    "About",
    on_about_selected, 
    &settings_item,
    &play_item
};

