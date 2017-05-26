#include <iostream>

using namespace std;

void prefixFucntion(char pattern[], int table[]);
void Kmp(char* text,char* pattern, int* table);

int main(int count, char* args[]){
	char* text;
	char* pattern;
	pattern = args[1];
	text = args[2];
	int table[strlen(pattern)]; 
	prefixFucntion(pattern, table);

	for(int i=0; i < strlen(pattern); i++){
		cout << table[i] << " | " ;
	}
	cout << endl;
	cout << text << endl;
	cout << pattern << endl;
	Kmp(text, pattern, table);
	return 0;
}

void prefixFucntion(char pattern[] , int table[]){
	int i = 1;
	int j = 0;
	table[0] = 0; 
	while(i < strlen(pattern)){
		if(pattern[i] == pattern[j]){
			table[i] = j + 1;
			i++;
			j++;
		}else if(j == 0){
			table[i] = 0;
			i++;
		}else{
			j--;
			j = table[j];
		}
	}
}

void Kmp(char* text,char* pattern, int* table){
	int i = 0;
	int j = 0;
	while(i < strlen(text)){
		if(j == strlen(pattern)){
			cout << i - j << endl;
			j = 0;
			i = i - j + 1;
		}
		else if(text[i] == pattern[j]){
			i++;
			j++;
		}else if(j == 0){
			i++;
		}else{
			j = table[j-1];
		} 
	}
}