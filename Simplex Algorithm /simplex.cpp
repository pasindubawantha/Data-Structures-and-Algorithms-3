#include <iostream>
using namespace std;

// DO NOT COPY THESE COMMENTS !!!!!!
// OF COURSE DO NOT COPY IT AS IT IS ANYWAY !!!!!!
/*
Compiler data:
Configured with: --prefix=/Applications/Xcode.app/Contents/Developer/usr --with-gxx-include-dir=/usr/include/c++/4.2.1
Apple LLVM version 8.0.0 (clang-800.0.42.1)
Target: x86_64-apple-darwin16.4.0
Thread model: posix
InstalledDir: /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin

c++ version : 4.2.1
with no flags

How to use: 
define M as number of constraints,
define N as number of variables
build an MxN 2D array as the constraint matrix
build a array of size M for constraints
build a coefiecnt array for objective function of size N
build a solution array of size N to recive solutions 
and pass these variables to simplex function matching it's signature
solutions will be recived from solution array of size N you passed to the function

Here I have demonstrated an exmple with:
objective function : P = 6x + 5y + 4z
where P has to be maximized under constraints :
2x + y + z <= 180 ,
x + 3y + 2z <= 300,
2x + y + 2z <= 240 
and x, y, z >= 0 

where 
m = 3
n = 3 
A = | 2 | 1 | 1 |
    | 1 | 3 | 2 | 
    | 2 | 1 | 2 |

b = | 180 |
    | 300 |
    | 240 |

c = | 6 |
    | 5 |
    | 4 |
x = empty array of size N

function call :  simplex(A, b, c, x, m, n)
*/


#define M 3 // 3 constrains
#define N 4 // 3 variables 

float* simplex(float A[M][N], float b[], float c[], float x[], int m, int n);// simplex(constraintArray, constraintValues, objectiveFunctionCoefficents, arrayToReciveSolutionSet, noOfConstraints, noOfVariables)
//in c you can't return an array by value therfore we have to send the solution set array from the main() function othervise we recive an empty array as simplex() function releases it's memory to the system after executing and there by losing all local variable data(variables created inside the function)
//no point of returning the solution set but since the quection asks I'm returning a float array pointer without having 'void'
void printTable(float table[M+1][M+N+2], int m, int n);//for debugging
void sort(float valueArray[], int indexArray[], int size);

int main(){//example
	float A[M][N];//constraint matrix
	float b[M];// Ax = b are the constraints 
	float c[N];//coefiecients of the objective function
	c[0] = 6; c[1] = 5; c[2] = 4;//objective function P = 6x + 5y + 4z
	A[0][0] = 2; A[0][1] = 1; A[0][2] = 1; b[0] = 180;//constrain 1  2x + y + z <= 180 
	A[1][0] = 1; A[1][1] = 3; A[1][2] = 2; b[1] = 300;//constrain 1  x + 3y + 2z <= 300 
	A[2][0] = 2; A[2][1] = 1; A[2][2] = 2; b[2] = 240;//constrain 1  2x + y + 2z <= 240 

	float x[N];//solution set 
	simplex(A, b, c, x, M, N);// solutions are in the x[N] array
	cout << "##Solution" << endl;
	for(int i = 0; i < N ; i++){// to printout solutions
		cout << "x" << i << " = " << x[i] << endl;// x1 = x , x2 = y , x3 = z
	}
	cout << "-------------------------------" << endl;
	return 0;
}

float* simplex(float A[M][N], float b[], float c[], float x[],int m, int n){
	int m1 = m + 1; //no of constraints plus one for objective
	int n1 = n + m + 2; //variables + slack variables + 2 (for colomb P and b) 
	float table[M+1][M+N+2];

	for(int i = 0;i < m; i++){// putting data to Table
		table[i][n1 -1] = b[i];// putting b data to Table 
		for(int j = 0;j < n; j++){// putting  A data to Table
			table[i][j] = A[i][j];
		}
		
		for(int j = n; j < n1 - 1; j++){// filling up slack variable data
			if(i == (j - n)){
				table[i][j] = 1;
			}
			else{
				table[i][j] = 0;
			}
			if(i == m-1){//filling the last row of slack variables
				table[i+1][j] = 0;
				if(j == n1 - 2){// filling p colomn
					table[i+1][j] = 1;
				}
			}
			if(j == n1 - 2){// filling p colomn
				table[i][j] = 0;
			}
		}
	}
	for(int i = 0;i < n;i++){// adding objective coefecient data to table
		table[m][i] = -c[i];
	}
	table[m1 - 1][n1 - 1] = 0;
	cout << "--------------Table------------" << endl;
	printTable(table, m1, n1);
	cout << "-------------------------------" << endl;
	// Table has been filled
	
	bool foundNegative, foundValidPivot;
	int row, colomn, minimumIndex, minimumRowIndex, colomnArraySize;
	float minimum, divisor, multiplier;
	int colomnsInDecendingOrder[n1-1], rowsInDecendingOrder[m1-1];
	float colomnsValuesInDecendingOrder[n1-1], rowsValuesInDecendingOrder[m1-1];
	cout << "### Starting Simplex algorithm" << endl;
	cout << "-------------------------------" << endl;
	do{//executing simplex
		foundNegative = false;
		minimumIndex = 0;
		for(int j = 0; j < n1 - 1; j++){//looking for minimum negatove colomn
			if(table[m1-1][j] < 0){
				colomnsValuesInDecendingOrder[minimumIndex] = table[m1-1][j];
				colomnsInDecendingOrder[minimumIndex] = j;
				minimumIndex++;
				foundNegative = true;
			}
		}
		colomnArraySize = minimumIndex;
		sort(colomnsValuesInDecendingOrder, colomnsInDecendingOrder, colomnArraySize);
		foundValidPivot = false; 
		minimumIndex = 0;
		minimumRowIndex = 0;
		while(!foundValidPivot && (minimumIndex < colomnArraySize) && foundNegative){
			for(int i = 0; i < m1 - 1; i++){//looking for minimum row
				rowsInDecendingOrder[i] = i;
				rowsValuesInDecendingOrder[i] = (table[i][n1-1] / table[i][colomnsInDecendingOrder[minimumIndex]]);
			}
			sort(rowsValuesInDecendingOrder, rowsInDecendingOrder, m1-1);
			while(!foundValidPivot && (minimumRowIndex < m1-1)){
				if(table[rowsInDecendingOrder[minimumRowIndex]][colomnsInDecendingOrder[minimumIndex]] > 0){
					foundValidPivot = true;					
				}else{
					minimumRowIndex++;
				}
			}
			if(!foundValidPivot){
				minimumIndex++;				
			}
		}

		row = rowsInDecendingOrder[minimumRowIndex];
		colomn = colomnsInDecendingOrder[minimumIndex];

		if(foundNegative && foundValidPivot){
			divisor = table[row][colomn];
			for(int j = 0; j < n1; j++){//normalisiong row with leading variable
				table[row][j] = table[row][j] / divisor; 
			}
			for(int i = 0; i < m1; i++){//subtracting all rows by selected row
				if(i != row){
					multiplier = -(table[i][colomn]);
					for(int j = 0; j < n1; j++){
						table[i][j] = (table[i][j] + (table[row][j] * multiplier));
					}
				}
			}
		}
		
	printTable(table, m1, n1);
	if (foundNegative && foundValidPivot) cout << "Found Negatives did operations" << endl;
	else cout << "Didn't found Negatives no operations done" << endl;
	cout << "-------------------------------" << endl;
	}while(foundNegative && foundValidPivot);
	//Simplex has been executed, extracting solution
	cout << "### Extrating solutions from the table" << endl;
	cout << "-------------------------------" << endl;
	bool isZero;
	bool foundLeadingOne;
	int leadingOneAt;
	for(int j = 0; j < n; j++){//extraction solutions, traversing colomns
		isZero = false;
		foundLeadingOne = false;
		for(int i = 0; i < m1; i++){//traversing rows
			if(foundLeadingOne){
				if(table[i][j] != 0) isZero = true;
			}else{
				if(table[i][j] == 1){
					foundLeadingOne = true;
					leadingOneAt = i;
				}else if(table[i][j] != 0){
					isZero = true;
				}
			}
		}
		if(isZero) x[j] = 0;
		else if(foundLeadingOne) x[j] = table[leadingOneAt][n1-1]; // i = j at the corresponding variable
		else x[j] = 0;
	}

	return x;

}

void printTable(float table[M+1][M+N+2], int m, int n){
	for(int i = 0; i < m; i++){
		for(int j = 0; j < n; j++){
			cout << table[i][j] << " | ";
		}
		cout << endl;
	}
}

void sort(float valueArray[], int indexArray[], int size){
	int traversIndex, minimumIndex, tmpIndex;
	float tmpValue;
	for(int currentIndex = 0; currentIndex < size; currentIndex++){
		traversIndex = currentIndex;
		minimumIndex = traversIndex;
		while(traversIndex < size){
			if(valueArray[traversIndex] < valueArray[minimumIndex]) minimumIndex = traversIndex;
			traversIndex++;
		}
		tmpValue = valueArray[currentIndex];
		tmpIndex = indexArray[currentIndex];
		valueArray[currentIndex] = valueArray[minimumIndex];
		indexArray[currentIndex] = indexArray[minimumIndex];
		valueArray[minimumIndex] = tmpValue;
		indexArray[minimumIndex] = tmpIndex;
	}

}