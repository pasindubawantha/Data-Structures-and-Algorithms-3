#include <iostream>
using namespace std;

void makeTable(char pattern[], int table[], int tableSize);

void main(int cout[], char* args[]){
	char* text;
	char* pattern;
	int table[256] = {-1};
	pattern = args[1];
	text = args[2];
	makeTable(pattern, table, 256);

	return 0;
}

makeTable(char pattern[], int table[], int tableSize){
	for(int i = 0; i < tableSize; i++){
		if([(int) pattern[i]])
	}
}