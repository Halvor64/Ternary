#include <iostream>
#include <string>

using namespace std;

int table[9] = //Logic table outputs. It is also the function index expressed in ternary.
{
//in2   2,1,0	| in1	
		0,0,0 , //2
		0,0,0 , //1
		0,0,0   //0
};


int in1 = 0;
int in2 = 0;
int index = 0;


int getValue(string prompt, int low, int high) {	//prints a prompt, gets a value (int) between low and high, and returns it. The input value is clamped to the limits.
	int value = 0;
	do {
		if (!cin.good()) {
			cin.clear();
			cin.ignore(INT_MAX, '\n');
		}
		cout << prompt;
		cin >> value;
	} while (!cin.good());


	if (value > high) value = high;
	if (value < low) value = low;
	return value;
}

void printFunction(int index) {
	cout << "-------------------\nfunction of index " << index << endl;
	for (int i = 0; i < 9; i++) table[i] = 0;
	int convert = index;
	for (int i = 9; i>0; i--) {
		table[i] = convert % 3;
		convert = convert / 3;
	}
	for (int row = 9; row > 0; row--) {	//prints all possible inputs and the corresponding output of function of index i					
		cout << "(" << (9 - row) / 3 << "," << (9 - row) % 3 << ") => " << table[row] << endl;
	}

	//for (int i = 0; i < 9; i++) table[i] = 0; //functions calling this function might need the content of the table
	cout << "-------------------\n\n";
}

int iterateFunctions() {	//prints all function logic tables iteratively. This is not a useful function other than for demonstrating the indexing.
	for (int i = 0; i < 9; i++) table[i] = 0;
	for (int i = 0; i < 19683; i++) {
		
		printFunction(i);

		/*
		for (int row = 0; row < 9; row++) {	//prints all possible inputs and the corresponding output of function of index i					
			cout << "(" << row / 3 << "," << row % 3 << ") => " << table[row] << endl;
		}
		table[0]++;
		for (int digit = 0; digit < 9; digit++) {	//increments the function index / logic table output
			if (table[digit] > 2) {
				table[digit] = 0;
				table[digit + 1]++;
			}
		}
		*/ //interesting but unnecessary given the printFunction function

		char yn;
		do {
			if (!cin.good()) {
				cin.clear();
				cin.ignore(INT_MAX, '\n');
			}
			
			cout << "continue? y/n: ";
			cin >> yn;
		} while (!cin.good());

		if (yn == 'n') {
			for (int i = 0; i < 9; i++) table[i] = 0;
			return 0;
		}

	}
	for (int i = 0; i < 9; i++) table[i] = 0;
	return 0;
}



void callFunction(int input1, int input2, int index) {
	printFunction(index); //this function will print the table, and set the values of the table array
	int n = input1 * 3 + input2;
	cout <<"("<< input1 << "," << input2 << ") => " << table[9-n] << "\n\n";
}

int main() {						// MONADIC FUNCTIONS CAN BE ACHIEVED BY IGNORING ONE INPUT
	while (true) {
		int input = 0;
		//menu
		cout << "1. call function with inputs and index\n";
		cout << "2. print function with index\n";
		cout << "3. iterate through all functions from index 0\n";
		cout << "4. Useful functions\n";
		input = getValue("(1-4) >", 1, 4);
		switch (input) {
		case 1:
			in1 = getValue("enter first ternary input(0 - 2) : ", 0, 2);
			in2 = getValue("\nenter second ternary input(0 - 2): ", 0, 2);
			index = getValue("\nenter the index(0 - 19682): ", 0, 19682);
			cout << "\n\nin1: " << in1 << "\nin2: " << in2 << "\nIndex: " << index << "\n\n";
			callFunction(in1, in2, index);
			break;
		case 2:
			index = getValue("\nenter the index(0 - 19682): ", 0, 19682);
			printFunction(index);
			break;
		case 3:
			iterateFunctions();
			break;
		case 4:
			cout << "\n\n";
			cout << "Note: Some of these functions may only work in balanced ternary. This program is currently unbalanced ternary.\n";
			cout << "1. Balanced Distance Compare(Engdal): 8119 [102010201]\nGives the distance between the two values. 1 is no distance. 0 is a distance of one. 2 is a distance of two. Designed for use with balanced ternary. \n\n";
			cout << "2. Unbalanced Distance Compare: 3936 [012101210]\nAn altered version of Engdal's compare function. Gives the distance between the two values. In unbalanced ternary, it outputs the distance value.\n\n";
			cout << "3. Size Compare: 7153 [100210221]\nGives which input has the highest value. An output of 0 means the first input has the bigger value, 2 is the second input. Identical values gives 1.\n\n";
			cout << "4. Max or Or: 19569 [222211210]\nOutputs the highest value of the two inputs.\n\n";
			cout << "5. Min or And: 16362 [211110000]\nIf BOTH inputs are 2, output is 2. If ANY input is 0, output is 0. Else, output is 1.\n\n";
			cout << "6. Antimax or Nor: 15633 [210110000]\nOutputs the lowest value of the two inputs.\n\n";
			cout << "7. Antimin or Nand: 4049 [012112222]If BOTH inputs are 2, output is 0. If ANY input is 0, output is 2. Else, output is 1.\n\n";
			cout << "8. Xor: 4017 [012111210]\nExcluding the middle value, this functions the same way as binary XOR. If any input is 1, output is 1. If the inputs are opposites, the output is 2. If they are identical, output is 0.\n\n";
			cout << "9. Balanced Sum: 5681 [021210102]\nAdds the two balanced ternary inputs together.\n\n";
			cout << "10. Unbalanced Sum: 8229 [102021210]\nAdds the two unbalanced ternary inputs together.\n\n";
			cout << "11. Consensus: 16401 [211111110]\nIf both inputs are 0, output is 0. If both are 2, output is 2. Else, the output is 1.\n\n";
			cout << "12. Accept Anything: 18801 [221210100]\n Similar to consensus, except that if one of the outputs are 1, the other will decide the output. If both are 1, output is 1.\n\n";
			cout << "13. Equality comparison: 13286 [200020002]\n If the inputs are equal, output is 2. Else, output is 0.\n\n";

			input = getValue("(1-13) >", 1, 13);
			in1 = getValue("enter first ternary input(0 - 2) : ", 0, 2);
			in2 = getValue("\nenter second ternary input(0 - 2): ", 0, 2);
			switch (input) {
			case 1:
				callFunction(in1, in2, 8119);
				break;
			case 2:
				callFunction(in1, in2, 3936);
				break;
			case 3:
				callFunction(in1, in2, 7153);
				break;
			case 4:
				callFunction(in1, in2, 19569);
				break;
			case 5:
				callFunction(in1, in2, 16362);
				break;
			case 6:
				callFunction(in1, in2, 15633);
				break;
			case 7:
				callFunction(in1, in2, 4049);
				break;
			case 8:
				callFunction(in1, in2, 4017);
				break;
			case 9:
				callFunction(in1, in2, 5681);
				break;
			case 10:
				callFunction(in1, in2, 8229);
				break;
			case 11:
				callFunction(in1, in2, 16401);
				break;
			case 12:
				callFunction(in1, in2, 18801);
				break;
			case 13:
				callFunction(in1, in2, 13286);
				break;
			default:
				break;
			}
			break;
		}
	}
	return 0;
}






