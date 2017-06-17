#include <iostream> 
/*
ON TESTING:
To test this code compile TestCases.cpp and run, do not compile this file.

ON USAGE:
include this file to your main source code file by #include "lastFunction.cpp"
Run CalculateLast(string pattern) function first before using last(char character) function

TESTED COMPILER INFORMATION: 
compiled using g++ 
g++ version details :
Apple LLVM version 8.0.0 (clang-800.0.42.1)
Target: x86_64-apple-darwin16.4.0
Thread model: posix
*/

#define ALPHABET_SIZE 256 // 256 is the number of unique values that can be represented by 1 byte. and c++ char type has size 1 byte
using namespace std;

//function prototypes 
void CalculateLast(string pattern);
int last(char character);

int alphabet[ALPHABET_SIZE];//defining global variable integer array(used as a dictinary)

void CalculateLast(string pattern){
	//Initialize array(dictionary)
	for(int j = 0; j < ALPHABET_SIZE; j++){
		alphabet[j] = -1;
	}
	//Assigning dictionary values
	for(int i = (pattern.length() - 1); i >= 0; i--){
		if(alphabet[ (int) pattern[i] ] == -1){
			alphabet[ (int) pattern[i] ] = i;
		}
	}
}

int last(char character){
	return alphabet[ (int) character ];
}
