#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <unistd.h>
#define numLetter 6
#define Num_Of_Letter_In_The_File 488

int random_number(int low, int high);
void read_word(char* corrct_word);
void compare_words(char* user_word, char* corrct_word, char* word);
void clean_stdin();

// we use this function after using the scanf function to clean the stdin
void clean_stdin(){
	while(getc(stdin) != '\n');
}

// This function will take two numbers and generate a random number between them
int random_number(int low, int high) {
    srand(time(0));  // Seed the random number generator
    return low + rand() % (high - low + 1);
}

// This function will read a random word from the file
void read_word(char* correct_word){
	int i;
	FILE *file;
	file = fopen("words.txt", "r");
	if(file == NULL){
		printf("There is a problem with reading from the file\n");
		exit(1);
	}
	int randnum = (random_number(1, Num_Of_Letter_In_The_File))-1;//get the random number
	fseek(file, 0, SEEK_SET);
	for(i=0; i<randnum; i++){
		fseek(file, 6, SEEK_CUR);
	}
	fgets(correct_word, numLetter, file);
	fclose(file);
}

// This function will compare between the word from the user and the word from the file
void compare_words(char* user_word, char* correct_word, char* word){
	int i;
	for(i=0; i<5; i++){
		if(user_word[i] == correct_word[i]){
			word[i] = correct_word[i];
		}
	}
}

int main(){
	char* correct_word = malloc(5 * sizeof(char)); // To store the word from the file
	char *user_word = NULL; // To store the word from the user
	// To store similar letters between correct_word and user_word
	char *word = malloc(5 * sizeof(char));  
	int try;
	int i;
	char ch;
	size_t num;
	bool isWord;

	repeate: // If the user want to play again
	memset(word, '?', numLetter);// To initialize all the letters by '?'
	memset(correct_word, 0, numLetter);// To initialize all the letters by 0
	read_word(correct_word);
	try =5;
	num = 0;
	isWord = false;
	for( ; try>0; try--){
		system("clear");
		printf("\n");
		printf("\t\t\t*********************\n");
		printf("\t\t\t*   |   |   |   |   *\n");
		printf("\t\t\t* %c | %c | %c | %c | %c *\n", word[0], word[1], word[2], word[3], word[4]);
		printf("\t\t\t*   |   |   |   |   *\n");
		printf("\t\t\t*********************\n\n\n");
		printf("The number of attempts remaining : %d\n\n", try);
		printf("Enter a word of five letters : ");
		getline(&user_word, &num, stdin);
		// To make the letters uppercase
		for(i=0; i<5; i++){
			if(user_word[i]>96 && user_word[i]<122){
				user_word[i] = user_word[i] - 32;
			}
		}
		compare_words(user_word, correct_word, word);
		memset(&user_word, 0, numLetter);
		for(i=0; i<5; i++){
			if(word[i] == '?'){
				isWord = false;
				break;
			}
			if(i == 4){
				isWord = true;
			}
		}
		if(isWord == true){
			break;
		}
	}
	// Giving the result to the user
	if(isWord == true){
		system("clear");
		printf("\t\t\t  Congratulation !\n");
		printf("\t\t\t      You Win\n\n");
		
	}else{
		system("clear");
		printf("\t\t\t   You Lose !\n\n");
		printf("The correct word is :\n");
	}
	// Giving the user the correct word
	printf("\t\t\t********************\n");
	printf("\t\t\t*%c * %c * %c * %c * %c *\n", correct_word[0], correct_word[1], correct_word[2], correct_word[3], correct_word[4]);
	printf("\t\t\t********************\n");
	// Asking the user for another game
	do{
		printf("\nDo you want to play again [Y/N] : ");
		scanf("%c", &ch);
		clean_stdin();
		if(ch == 'y' || ch == 'Y'){
			goto repeate; 
		}else if(ch == 'n' || ch == 'N'){
			printf("\n\t\t\t\t Thank you !\n");
			sleep(1);
			exit(1); 
		}
	}while(ch != 'Y' && ch != 'y' && ch != 'N' && ch != 'n');
		

	return 0;
}