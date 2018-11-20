#include <stdio.h>
#include "ui_settings_menu.h"
#include "highscore.h"
//#include "ui_internal.h"
#include "ui.h"

extern menu_item_t player_1;
extern menu_item_t player_2;
extern menu_item_t player_3;

menu_item_t* UI_SETTINGS_MENU_ENTRYPOINT = &player_1;

menu_item_t* player = &player_1;

menu_item_t* on_player_select(menu_item_t* caller){
	ui_display();
	player = caller;
	return caller;
}

menu_item_t player_1 = {
    "Sara",
    on_player_select,
    &player_3,
    &player_2
};

menu_item_t player_2 = {
    "H-bird",
    on_player_select,
    &player_1,
    &player_3
};

menu_item_t player_3 = {
    "Emma",
    on_player_select,
    &player_2,
    &player_1
};


menu_item_t* get_player(){
	return player;
}

