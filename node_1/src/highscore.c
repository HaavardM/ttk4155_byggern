#include "ui_settings_menu.h"
#include <stdint.h>
#include <stdio.h>
#include <avr/io.h>
#include <avr/eeprom.h>

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
	highscore_save();
}

int get_highscore(int i){
	return highscores[i];
}

char* get_name(int i){
	return names[i];
}

#define INITIAL_EEPROM 1
void highscore_save() {
	EEAR = INITIAL_EEPROM;
	EEAD = '\r';
	for(uint8_t i = 0; i < LENGTH; ++i) {
		EEAR += 1;
		EEAD = highscores[i] / 256; 
		EEAR += 1;
		EEAD = highscores[i] % 256;
		char* c = names[i];
		while(*c != '\0') {
			EEAR += 1;
			EEAD = *c;
		}
		EEAR += 1;
		EEAD = '\0';
	}
	EEAR += 1;
	EEAD = '\n';
}

char* players[LENGTH][10];

void highscore_load() {
	EEAR = INITIAL_EEPROM;
	uint8_t data = EEAD;
	//No highscore data to read
	if(data != '\r') {
		return;
	}
	uint8_t i = 0;
	do {
		EEAR += 1;
		data = EEAD;
		uint8_t high = data;
		EEAR += 1;
		data = EEAD;
		uint16_t score = high * 256 + data;
		EEAR += 1;
		data = EEAD;
		uint8_t ci = 0;
		while(data != '\0') {
			players[i][ci] = data;
			ci++;
			EEAR += 1;
			data = EEAD;
		}
		players[i][ci] = '\0';
		highscores[i] = score;
		names[i] = players[i];
		EEAR += 1;
		data = EEAD;
	} while(data != '\n');
}
