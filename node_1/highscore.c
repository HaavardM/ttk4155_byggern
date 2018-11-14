#define LENGTH 5
int highscores[LENGTH] = {0,1,2,3,4};

void update_highscore(int score){
	
	for (int i = 0 ; i < LENGTH; i++){
		if(score > highscores[i]){
			for (int j = i+1 ; j <= LENGTH-i ; j++){
				highscores[j] = highscores[j-1];
			}
			highscores[i] = score;	
		}
	}
}

int get_highscore(int i){
	return highscores[i];
}