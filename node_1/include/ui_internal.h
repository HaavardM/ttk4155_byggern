#ifndef UI_INTERNAL_H
#define UI_INTERNAL_H

typedef struct menu_item_t menu_item_t;

typedef menu_item_t* (* const callback_func)(menu_item_t* caller);

struct menu_item_t {
    char* item_text;
    callback_func on_select;
    menu_item_t* prev;
    menu_item_t* next;
};


#endif
