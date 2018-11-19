#include "ui_settings_menu.h"
#include <stdint.h>
#include <stdio.h>

#define LENGTH 5
int highscores[LENGTH] = {0,0,0,0,0};
char *names[LENGTH];

void update_highscore(uint8_t high, uint8_t low){
	uint16_t score = ((uint16_t)high << 8) | low;
	printf("BAAAM\n");
	printf("Score %d\n\r", score);
	menu_item_t* player = get_player();
	//char *player = get_player();
	for (int i = 0 ; i < LENGTH; i++){
		if(score > highscores[i]){
			for (int j = LENGTH-1; j > i; j--){
				highscores[j] = highscores[j-1];
				names[j] = names[j-1];
			}
			highscores[i] = score;	
			names[i] = player->item_text;
			break;
		}
	}
}

int get_highscore(int i){
	return highscores[i];
}

char* get_name(int i){
	return names[i];
}
