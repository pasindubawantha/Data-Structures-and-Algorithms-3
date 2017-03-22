#include "lastFunction.cpp"
/*
ON USAGE:
Compile and run this file. Add your own test cases as functions check testcases using test(char character. int correctAnswer) function 

TESTED COMPILER INFORMATION: 
compiled using g++ 
g++ version details :
Apple LLVM version 8.0.0 (clang-800.0.42.1)
Target: x86_64-apple-darwin16.4.0
Thread model: posix
*/

void test(char character, int correct);
void testCase1(void);//Empty string pattern = "" 
void testCase2(void);//pattern = "zyxwvutsrqponmlkjihgfedcba"
void testCase3(void);//pattern = "abcdefghijklmnopqrstuvwxyz"
void testCase4(void);//pattern = "1234567890`!@#$%^&*()-="

int totalPassed = 0;
int totalFailed = 0;

int main(void){
	cout << "Running test cases :" << endl;
	//add testcasess here
	testCase1();
	testCase2();
	testCase3();
	testCase4();
	cout << "Total passed = " << totalPassed << " | Total failed = " << totalFailed << endl;
	char a = 'a';
	cout << sizeof(a);
	return 0;
}

void test(char character, int correct){
	int answer = last(character);
	cout << "character '" << character << "' : returned = " << answer << " | correct = " << correct << " | ";
	if(answer == correct){
		cout << "PASSED" << endl;
		totalPassed++;
	}
	else{
		cout << "FAILED" << endl;
		totalFailed++;
	}
}

void testCase1(void){
	string pattern = "";
	CalculateLast(pattern);
	cout << "Test case 01 : pattern = " << pattern << endl;
	cout << "----------------------------------------------" << endl;
	test('0',-1);
	test('1',-1);
	test('2',-1);
	test('3',-1);
	test('4',-1);
	test('5',-1);
	test('6',-1);
	test('7',-1);
	test('8',-1);
	test('9',-1);
	test('q',-1);
	test('w',-1);
	test('e',-1);
	test('r',-1);
	test('t',-1);
	test('y',-1);
	test('u',-1);
	test('i',-1);
	test('o',-1);
	test('p',-1);
	test('a',-1);
	test('s',-1);
	test('d',-1);
	test('f',-1);
	test('g',-1);
	test('h',-1);
	test('j',-1);
	test('k',-1);
	test('l',-1);
	test('z',-1);
	test('x',-1);
	test('c',-1);
	test('v',-1);
	test('b',-1);
	test('n',-1);
	test('m',-1);
	test('`',-1);
	test('!',-1);
	test('@',-1);
	test('#',-1);
	test('$',-1);
	test('%',-1);
	test('^',-1);
	test('&',-1);
	test('*',-1);
	test('(',-1);
	test(')',-1);
	test('-',-1);
	test('=',-1);
}

void testCase2(void){
	string pattern = "zyxwvutsrqponmlkjihgfedcba";
	CalculateLast(pattern);
	cout << "Test case 02 : pattern = " << pattern << endl;
	cout << "----------------------------------------------" << endl;
	test('0',-1);
	test('1',-1);
	test('2',-1);
	test('3',-1);
	test('4',-1);
	test('5',-1);
	test('6',-1);
	test('7',-1);
	test('8',-1);
	test('9',-1);
	test('a',25);
	test('b',24);
	test('c',23);
	test('d',22);
	test('e',21);
	test('f',20);
	test('g',19);
	test('h',18);
	test('i',17);
	test('j',16);
	test('k',15);
	test('l',14);
	test('m',13);
	test('n',12);
	test('o',11);
	test('p',10);
	test('q',9);
	test('r',8);
	test('s',7);
	test('t',6);
	test('u',5);
	test('v',4);
	test('w',3);
	test('x',2);
	test('y',1);
	test('z',0);
	test('`',-1);
	test('!',-1);
	test('@',-1);
	test('#',-1);
	test('$',-1);
	test('%',-1);
	test('^',-1);
	test('&',-1);
	test('*',-1);
	test('(',-1);
	test(')',-1);
	test('-',-1);
	test('=',-1);
}

void testCase3(void){
	string pattern = "abcdefghijklmnopqrstuvwxyz";
	CalculateLast(pattern);
	cout << "Test case 03 : pattern = " << pattern << endl;
	cout << "----------------------------------------------" << endl;
	test('0',-1);
	test('1',-1);
	test('2',-1);
	test('3',-1);
	test('4',-1);
	test('5',-1);
	test('6',-1);
	test('7',-1);
	test('8',-1);
	test('9',-1);
	test('a',0);
	test('b',1);
	test('c',2);
	test('d',3);
	test('e',4);
	test('f',5);
	test('g',6);
	test('h',7);
	test('i',8);
	test('j',9);
	test('k',10);
	test('l',11);
	test('m',12);
	test('n',13);
	test('o',14);
	test('p',15);
	test('q',16);
	test('r',17);
	test('s',18);
	test('t',19);
	test('u',20);
	test('v',21);
	test('w',22);
	test('x',23);
	test('y',24);
	test('z',25);
	test('`',-1);
	test('!',-1);
	test('@',-1);
	test('#',-1);
	test('$',-1);
	test('%',-1);
	test('^',-1);
	test('&',-1);
	test('*',-1);
	test('(',-1);
	test(')',-1);
	test('-',-1);
	test('=',-1);
}

void testCase4(void){
	string pattern = "1234567890`!@#$%^&*()-=";
	CalculateLast(pattern);
	cout << "Test case 04 : pattern = " << pattern << endl;
	cout << "----------------------------------------------" << endl;
	test('0',9);
	test('1',0);
	test('2',1);
	test('3',2);
	test('4',3);
	test('5',4);
	test('6',5);
	test('7',6);
	test('8',7);
	test('9',8);
	test('q',-1);
	test('w',-1);
	test('e',-1);
	test('r',-1);
	test('t',-1);
	test('y',-1);
	test('u',-1);
	test('i',-1);
	test('o',-1);
	test('p',-1);
	test('a',-1);
	test('s',-1);
	test('d',-1);
	test('f',-1);
	test('g',-1);
	test('h',-1);
	test('j',-1);
	test('k',-1);
	test('l',-1);
	test('z',-1);
	test('x',-1);
	test('c',-1);
	test('v',-1);
	test('b',-1);
	test('n',-1);
	test('m',-1);
	test('`',10);
	test('!',11);
	test('@',12);
	test('#',13);
	test('$',14);
	test('%',15);
	test('^',16);
	test('&',17);
	test('*',18);
	test('(',19);
	test(')',20);
	test('-',21);
	test('=',22);
}