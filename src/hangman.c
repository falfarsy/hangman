/*
 ============================================================================
 Name        : hangman.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hangman game
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define maxLen 100

//double rand_0_1() { //function to generate a random double between 0 and 1
//	//double max;
//	//max = 1.0;
//	return ( );
//}

char *randomWord() { //generates a random word from txt file

	FILE *word_list;
	size_t line_no = 0;
	size_t select_len;
	//double drand48();
	char chosen_word[9895]; //size represents total number of lines
	char current_word[9895];
	chosen_word[0] = '\0'; //if no lines then prevents crashing
	int max = 1.0;

	//reading in file with words to choose from
	word_list = fopen("10000-most-common-eng-words.txt", "r");
    if (word_list == NULL) {
        printf("file not found\n");
        exit(EXIT_FAILURE);
    }

    while(fgets(current_word, sizeof(current_word), word_list)) { //while there are still lines to read
    	if( (double)rand()/ ((RAND_MAX) / max) < 1.0 / ++line_no) { // odds of word being replaced given a random double
    		strcpy(chosen_word, current_word); //replace with new word
    	}
    }

    fclose(word_list); //close file
    select_len = strlen(chosen_word); //get word length of random chosen word
    if(select_len > 0 && chosen_word[select_len - 1] == '\n') { //if chosen word if a new line
    	chosen_word[select_len - 1] = '\0'; //then replace with null value
    }

    printf(chosen_word);
    printf("\n");

    return strdup(chosen_word);
}

void run_game() {
	int game_over = 0;
	int man_hung = 0;
	int rand_word_len;
	//char player_guess[1];
	char guesses_made[10];
	char player_guess;
	char rand_word[maxLen];

	printf("running game...\n");

	while(!game_over) {
		strcpy(rand_word, randomWord());
		//rand_word = randomWord(); //get random word
		rand_word_len = strlen(randomWord());
		printf("Enter your guess (single letters only): \n");
		player_guess = getchar(); //get length of random word
		while(man_hung != 10) {
			for(int a = 0; a < sizeof(guesses_made) / sizeof(guesses_made[0]); a++) { //for every value in array
				if(guesses_made[a] == player_guess) { //see if guess has already been made
					printf("You've already made that guess. Try something different...\n");
					continue; //go back to second while loop (man_hung)
				} else { //else append guess to array
					strcat(guesses_made, &player_guess);
				}
			}

			//iterate through random word array to see if letter exists in word
			for(int b = 0; b < sizeof(rand_word) / sizeof(rand_word[0]); b++) {
				if(rand_word[b] != player_guess) {
					man_hung += 1;
					printf("Sorry wrong guess, try again\n");
					continue;
				}
				else { // delete letter from random word array
					for(int c = b-1; c < rand_word_len; c++) {
						rand_word[c] = rand_word[c+1];
					}
				}
			} //end of for

			printf("Correct guess!");
			for(size_t i = 0; i < rand_word_len; ++i){
				if(rand_word[i] != 0) { //if element is not 'empty'
					continue; //ask for another input
				}
			}

            printf("Well done,you won! The word was %s \n", rand_word);
          	game_over = 1;
           	break;


		}//end of man hung while
	}//end of game_over while
}//end of run_game

int main() {

	srand(time(NULL)); //SEEDING RAND FUNCTION WIT A UNIQUE NO, IF YOU TAKE THIS OUT YOU WILL SPEND ANOTHER 2 HOURS WONDERING WHY YOURE GETTING THE SAME WORD EVERY TIME
	randomWord();

	return 0;
}
