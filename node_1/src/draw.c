#include "draw.h"
#include <string.h>

void draw_play(){
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
}

void draw_heart(){
	oled_write_string_inverse("   ###     ###  ", 0, 0);
    oled_write_string_inverse(" ######   ######", 1, 0);
    oled_write_string_inverse(" ####### #######", 2, 0);
    oled_write_string_inverse("  ############# ", 3, 0);
    oled_write_string_inverse("   ###########  ", 4, 0);
    oled_write_string_inverse("     #######    ", 5, 0);
    oled_write_string_inverse("       ###      ", 6, 0);
    oled_write_string_inverse("        #       ", 7, 0);
}