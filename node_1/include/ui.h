#ifndef UI_H
#define UI_H

#include "ui_internal.h"

void ui_update();
void ui_init();
void ui_enable();
void ui_disable();
void update_backlist(menu_item_t*);
void ui_enable();
void ui_disable();
void ui_display();
void ui_go_back();
void ui_goto_silent(menu_item_t*);
void ui_goto(menu_item_t*);
void ui_select();
#endif
