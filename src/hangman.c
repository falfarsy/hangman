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

char *randomWord() { //generates a random word from txt file

	FILE *word_list;
	size_t line_no = 0;
	char chosen_word[maxLen] = "";
	char current_word[maxLen] = "";
	int max = 1.0;

	//reading in file with words to choose from
	word_list = fopen("10000-most-common-eng-words.txt", "r");
    if (word_list == NULL) {
        perror("10000-most-common-eng-words.txt");
        exit(EXIT_FAILURE);
    }

    while(fgets(current_word, sizeof(current_word), word_list)) { //while there are still lines to read
    	if( (double)rand()/ ((RAND_MAX) / max) < 1.0 / ++line_no) { // odds of word being replaced given a random double
    		strcpy(chosen_word, current_word); //replace with new word
    	}
    }

    fclose(word_list); //close file
    chosen_word[strcspn(chosen_word, "\n")] = 0;//remove newline

    //printf ( "%s\n", chosen_word);
    //printf ( "\n");

    return strdup(chosen_word);
}

int runGame() {
	int game_over = 0;
	int man_hung = 0;
	char guesses_made[maxLen] = "";
	char player_guess = 0;
	char rand_word[maxLen] = "";
	char *word_copy = NULL;
	char correct_guesses[15] = "";
	char wrong_guesses[11] = "";
	int w = 0;
	int r = 0;


	printf("Lets play Hangman!\n");
	fflush(stdout);
	printf("You have 10 lives which wil1 decrease each time you guess incorrectly.\n\n");
	fflush(stdout);

	while(!game_over) {
		word_copy = randomWord(); //assign memory allocation
		strcpy(rand_word, word_copy);
		while(man_hung < 10) {
			printf("You have correctly guessed: ");
		    for (int i = 0; i < 15; ++i) {
		        printf("%c, ", correct_guesses[i]);
		    }
		    printf("\n");
			printf("You have incorrectly guessed: ");
		    for (int i = 0; i < 10; ++i) {
		        printf("%c, ", wrong_guesses[i]);
		    }
		    printf("\n");


			printf("Enter your guess (single letters only):\n");
			fflush(stdout);
			scanf(" %c", &player_guess); // avoids reading in new lines
			printf("\n");
			int a = 0;
			int match = 0;
			while(guesses_made[a]) { //for every value in array
				if(guesses_made[a] == player_guess) { //see if guess has already been made
					match = 3;
					printf("You've already made that guess. Try something different...\n");
					fflush(stdout);
					break;
				}
				++a;
			}
			if(!guesses_made[a]) { //terminating zero
				guesses_made[a] = player_guess; //add player guess
				guesses_made[a+1] = 0; //terminate
			}

			//iterate through random word array to see if letter exists in word
			int b = 0;
			while(rand_word[b]) { //not terminating zero
				if(rand_word[b] == player_guess) {
					match = 1; //found
					int c = b;
					// delete letter from random word array
					while(rand_word[c]) {
						rand_word[c] = rand_word[c+1];
						++c;
					}
					--b; //for consecutive matching letters
				}
				++b;
			} //end of while

			if(match == 0) {
				printf("Sorry wrong guess, try again!\n\n");
				fflush(stdout);
				if(!wrong_guesses[w]) { //terminating zero
					wrong_guesses[w] = player_guess; //add player guess
					wrong_guesses[w+1] = 0; //terminate
				}
				++w;
				man_hung += 1;
			}
			else if(match == 1) {
				printf("Correct guess!\n\n");
				fflush(stdout);
				if(!correct_guesses[r]) { //terminating zero
					correct_guesses[r] = player_guess; //add player guess
					correct_guesses[r+1] = 0; //terminate
				}
				++r;
			}

			if(rand_word[0] != 0) { //if element is not 'empty'
				if(10 > man_hung) {
					match = 0;
					continue; //ask for another input
				}
			}
			else {
				printf("Well done,you won!\n");
				fflush(stdout);
			}
            printf("The word was %s \n", word_copy);
            fflush(stdout);
            free(word_copy);

          	game_over = 1;
           	break;


		}//end of man hung while
	}//end of game_over while

	return 0;
}//end of run_game

int main(void) {
	srand(time(NULL)); //SEEDING RAND FUNCTION WIT A UNIQUE NO, IF YOU TAKE THIS OUT YOU WILL SPEND ANOTHER 2 HOURS WONDERING WHY YOURE GETTING THE SAME WORD EVERY TIME

	runGame();

	return 0;
}
