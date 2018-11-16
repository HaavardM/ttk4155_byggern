#include "ui_settings_menu.h"
#define LENGTH 5
int highscores[LENGTH] = {0,0,0,0,0};
const char *names[LENGTH];

void update_highscore(int score){
	printf("BAAAM\n");
	printf(score,"\n\r");
	menu_item_t* player = get_player();
	//char *player = get_player();
	for (int i = 0 ; i < LENGTH; i++){
		if(score > highscores[i]){
			for (int j = i+1; j <= LENGTH-i; j++){
				highscores[j] = highscores[j-1];
			}
			highscores[i] = score;	
			names[i] = player->item_text;
		}
	}
}

int get_highscore(int i){
	return highscores[i];
}

char* get_name(int i){
	return names[i];
}
