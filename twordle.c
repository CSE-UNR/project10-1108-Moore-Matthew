//NAME: Matthew Moore
//DATE: 05-04-2026
//PURPOSE: Combine everything + 2d arrays for project 10

#include <stdio.h>
#include <stdbool.h>

#define STR_CAP 100
#define GUESSLIMIT 6
#define WORDLIMIT 6
#define BORDERLENGTH 31
#define INPUTFILE "mystery.txt"

void ReadWordFromFile(FILE *WordPtr, char WordFromFile[]);
void GetUserGuess(int MaxSize, char CurrentUserGuess[][MaxSize], int CurrentGuess);
void InputInLowerCase(int const ColumnSize, int const RowNumber, char Guesses[][ColumnSize]);
_Bool CheckIfCorrect(int const ColumnSize, int const RowNumber, char const PhraseArray[], char const WordArray[][ColumnSize]);
void DisplayBorderLine(int const LineLength, char const Symbol);
void FunctionCompiler(int FinalGuess, int ColCapacity, int RowCapacity, int LineLength, FILE *FilePtr);
void HintChecker(int const ColumnSize, int const RowNumber, char const Answer[], char Guesses[][ColumnSize], char HintsArr[][ColumnSize]);
void DisplayPastGuesses(int const ColumnSize, int const RowNumber, char const Guesses[][ColumnSize], char const HintsArr[][ColumnSize], int SpaceLength);
void EndMessage(int const RowNumber, _Bool const Win, int SpaceLength);

int main(){
	FILE *InputWord;
	InputWord = fopen(INPUTFILE, "r");
	if(InputWord == NULL){
		printf("File could not open.");
		return 0;
	}
	FunctionCompiler(GUESSLIMIT, STR_CAP, WORDLIMIT, BORDERLENGTH, InputWord);
	fclose(InputWord);
	return 0;
}

void ReadWordFromFile(FILE *WordPtr , char Answer[]){
	fscanf(WordPtr, "%5s", Answer);
}

void GetUserGuess(int MaxSize, char CurrentUserGuess[][MaxSize], int CurrentGuess){
	int StringLength = 0;
	_Bool Symbols = false;
	if(CurrentGuess + 1 != 6){
		printf("GUESS %d! ENTER YOUR GUESS: ", CurrentGuess + 1);		
		scanf(" %99s", CurrentUserGuess[CurrentGuess]);
	}
	else{
		printf("FINAL GUESS : ");
		scanf(" %99s", CurrentUserGuess[CurrentGuess]);
	}
	for(int i = 0; CurrentUserGuess[CurrentGuess][i] != '\0' && i < MaxSize; i++){
		StringLength++;
		if(CurrentUserGuess[CurrentGuess][i] < 'A' || (CurrentUserGuess[CurrentGuess][i] > 'Z' && CurrentUserGuess[CurrentGuess][i] < 'a') || CurrentUserGuess[CurrentGuess][i] > 'z'){
		StringLength = 10;
		Symbols = true;
		}
	}
	while(StringLength != 5){
		StringLength = 0;
		printf("Your guess must be 5 letters long.");
		if(Symbols == true){
			printf("Your guess must contain only letters.");
			Symbols = false;
		}
		printf("\nPlease try again: ");
		scanf(" %99s", CurrentUserGuess[CurrentGuess]);
		for(int i = 0; CurrentUserGuess[CurrentGuess][i] != '\0' && i < MaxSize; i++){
			StringLength++;
			if(CurrentUserGuess[CurrentGuess][i] < 'A' || (CurrentUserGuess[CurrentGuess][i] > 'Z' && CurrentUserGuess[CurrentGuess][i] < 'a') || CurrentUserGuess[CurrentGuess][i] > 'z'){
		StringLength = 10;
		Symbols = true;
			}
		}
	}
}
void InputInLowerCase(int const ColumnSize, int const RowNumber, char Guesses[][ColumnSize]){
	for(int i = 0; Guesses[RowNumber][i] != '\0' && i < ColumnSize; i++){
		if(Guesses[RowNumber][i] >= 'A' && Guesses[RowNumber][i] <= 'Z'){
			Guesses[RowNumber][i] += 32;
		}
	}
}
void DisplayBorderLine(int const LineLength, char Symbol){
	for(int i = 0; i <= LineLength; i++){
		printf("%c", Symbol);
	}
}
_Bool CheckIfCorrect(int const ColumnSize, int const RowNumber, char const PhraseArray[], char const WordArray[][ColumnSize]){
	int Id;
	_Bool Match = false;
	for(int Index = 0; PhraseArray[Index] != '\0' && Index < ColumnSize; Index++){
		Id = 0;
		while(WordArray[RowNumber][Id] == PhraseArray[Index + Id] && WordArray[RowNumber][Id] != '\0'){
	    	Id++;
		}
		if(WordArray[RowNumber][Id] == '\0'){
			Match = true;
		}
	}
	return Match;
}
void HintChecker(int const ColumnSize, int const RowNumber, char const Answer[], char Guesses[][ColumnSize], char HintsArr[][ColumnSize]){
	int i;
	char CopyAnswer[ColumnSize];
	for(i = 0; Answer[i] != '\0' && i < ColumnSize; i++){
		CopyAnswer[i] = Answer[i];
	}
	CopyAnswer[i] = '\0';
	for(i = 0; Guesses[RowNumber][i] != '\0' && i < ColumnSize; i++){
		if(Guesses[RowNumber][i] == Answer[i]){
			Guesses[RowNumber][i] -= 32;
			HintsArr[RowNumber][i] = ' ';
			CopyAnswer[i] = ' ';
		}
	}
	for(i = 0; Guesses[RowNumber][i] != '\0' && i < ColumnSize; i++){
		for(int j = 0; CopyAnswer[j] != '\0'; j++){
			if(Guesses[RowNumber][i] == CopyAnswer[j] && HintsArr[RowNumber][i] != '^'){
				HintsArr[RowNumber][i] = '^';
				CopyAnswer[j] = ' ';
			}
			else if(HintsArr[RowNumber][i] != '^'){
				HintsArr[RowNumber][i] = ' ';
			}
		}
	}
	HintsArr[RowNumber][i] = '\0';
}
void DisplayPastGuesses(int const ColumnSize, int const RowNumber, char const Guesses[][ColumnSize], char const HintsArr[][ColumnSize], int SpaceLength){
	DisplayBorderLine(SpaceLength, '=');
	for(int i = 0; i <= RowNumber; i++){
		printf("\n%s\n", Guesses[i]);
		printf("%s", HintsArr[i]);
		if(i == RowNumber){
			printf("\n");
		}
	}
}
void EndMessage(int const RowNumber, _Bool const Win, int SpaceLength){
	if(Win != true){
		printf("you lost, better luck next time!\n");
	}
	else if(Win == true){
		DisplayBorderLine(SpaceLength, '=');
		printf("\n");
		DisplayBorderLine(15, ' ');
		printf("SOUND\n");
		DisplayBorderLine(7, ' ');
		printf("You won in %d guess!\n", RowNumber);
		DisplayBorderLine(15, ' ');
		printf("GOATED!\n");
	}
}
void FunctionCompiler(int FinalGuess, int ColCapacity, int RowCapacity, int LineLength, FILE *FilePtr){
	char HintsArr[RowCapacity][ColCapacity], Answer[ColCapacity], Guesses[RowCapacity][ColCapacity];
	int GuessCounter = 0;
	_Bool correct = false;
	ReadWordFromFile(FilePtr, Answer);
	do{
		GetUserGuess(ColCapacity, Guesses, GuessCounter);
		InputInLowerCase(ColCapacity, GuessCounter, Guesses);
		correct = CheckIfCorrect(ColCapacity, GuessCounter, Answer, Guesses);
		if(correct != true){
			HintChecker(ColCapacity, GuessCounter, Answer, Guesses, HintsArr);
			DisplayPastGuesses(ColCapacity, GuessCounter, Guesses, HintsArr, LineLength);
			GuessCounter++;
		}
	}while(GuessCounter < RowCapacity && correct != true);
	EndMessage(GuessCounter + 1, correct, LineLength);
}
