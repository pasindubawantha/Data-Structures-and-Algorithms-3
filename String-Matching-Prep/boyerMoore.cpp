#include <iostream>
using namespace std;

void makeTable(char pattern[], int table[], int tableSize);
void boyerMoore(char text[], char pattern[], int table[]);
int main(int count, char* args[]){
	char* text;
	char* pattern;
	int table[256];
	pattern = args[1];
	text = args[2];
	makeTable(pattern, table, 256);
	boyerMoore(text, pattern, table);
	return 0;
}

void makeTable(char pattern[], int table[], int tableSize){
	for(int i = 0; i < tableSize; i++){
		table[i] = -1;
	}
	for(int i = 0; i < strlen(pattern); i++){
		table[(int) pattern[i]] = i;
	}
}

void boyerMoore(char text[], char pattern[], int table[]){
	int patternSize = strlen(pattern) - 1;
	int j = patternSize;
	int i = patternSize;
	int last;
	while(i <= 26){

		if(j == -1){
			i++;
			cout << i << endl;
			i += patternSize + 1;
			j = patternSize; 
		}else if(text[i] == pattern[j]){
			i--;
			j--;
			
		}else{

			last = table[(int) text[i]];
			if(last < j){
				j = last;
			}else{
				j = patternSize;
				i++;
			}

		}
	}
}