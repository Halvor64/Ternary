#include <iostream>
#include <string>
#include <vector>
#include <math.h>
#include <cstdint>
using namespace std;

//vectors are used since they have dynamic size
vector<int> input; //binary inputs 
vector<int> all_one_ternary;
vector<int> output; // ternary outputs
//vector<int> matrix; //2D vector
int matrix[128][82];

int getValue(string prompt, int low, int high) {	// gets a value (int) between low and high and returns it
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


void setOutput(int bits) {
	int trits = ceil(bits / 1.585);
	uint64_t decimal = 0;				
	for (int i = 0; i < bits; i++) {
		decimal += ((1 << i) * (!input[i]));
	}
	//cout << "\ndecimal for output: " << decimal << "\n\n";
	uint64_t valueZero = 0;
	for (int i = 0; i < trits; i++) valueZero += pow(3, i);
	decimal = decimal + valueZero; // in balanced ternary, all middle value = 0. Therefore an offset is added

	for (int i = 0; i < trits; i++) {
		output[i] = ((decimal % 3) - 1); // -1 to get the correct balanced ternary notation
		decimal = decimal / 3;
		if (decimal == 0) i = trits;
	}
}


void setAllOneTernary(int bits) {	//sets the all_one_ternary to the balanced ternary value corresponding to all 1s on the input
	int trits = ceil(bits / 1.585);
	uint64_t decimal = 0;
	for (int i = 0; i < bits; i++) decimal += 1 << i;//pow(2, i);
	//cout << "decimal: " << decimal << "\n\n";

	uint64_t valueZero = 0;
	for (int i = 0; i < trits; i++) valueZero += pow(3, i);
	decimal = decimal + valueZero; // in balanced ternary, all middle value = 0. Therefore an offset is added



	for (int i = 0; i < trits; i++) {
		all_one_ternary[i] = ((decimal % 3) - 1); // -1 to get the correct balanced ternary notation
		decimal = decimal / 3;
		if (decimal == 0) i = trits;
	}


}


int main() {
	while (true) {

		int bits = getValue("enter number of binary inputs (0 - 64): ", 0, 64);
		int trits = ceil(bits / 1.585); //a trit can replace 1.58496 bits
		//NOTE: In implementation, it is advisable to use one output trit more than the number of trits in the matrix.
		// The most significant bit can have a positive overflow
		// this is due to the fact that 2 trit balaced ternary can count from -4 to +4, 
		// while 2 trit unsigned can count from 0 to 8.
		// so while the number of trits defined above are enough for the matrix, it might sometimes not be enough for some specific outputs.
		// for some data sizes, the overhead might cause this positive overflow to never happen. 

		// reserving vector space and setting contents to 0
		output.reserve(trits);
		input.reserve(bits);
		all_one_ternary.reserve(trits);
		//matrix.reserve(trits); ///////////////////////////
		for (int i = 0; i < bits; i++) {
			input.push_back(0);
		}
		for (int i = 0; i < trits; i++) {
			output.push_back(0);
			all_one_ternary.push_back(0);
			//	matrix.push_back(0);////////////////////////////
		}



		setAllOneTernary(bits);



		for (int n = 0; n < bits; n++) input[n] = 0;
		input[0] = 1;

		for (int i = 0; i < bits; i++) {
			//cout << "\n\ni: " << i << "\n";
			setOutput(bits);

			for (int j = 0; j < trits; j++) {
				//cout << "\n\nj: " << j << "\n";
				//cout << "input: ";
				//for (int foobar = bits - 1; foobar > -1; foobar--) cout << !input[foobar];
				//cout << "\n\n\n";
				matrix[i][j] = all_one_ternary[j] - output[j];
				//cout << "all_one_ternary["<<j<<"] = " << all_one_ternary[j] << "\n";
				//cout << "output[" << j << "] = " << output[j] << "\n";

			}

			for (int k = bits - 1; k > 0; k--) input[k] = input[k - 1];
			input[0] = 0;

			//cout << "\n";
		}

		for (int j = 0; j < trits; j++) {
			for (int i = bits - 1; i > -1; i--) {
				if (matrix[i][j] == -2) {
					matrix[i][j] = 1;
					matrix[i][j + 1] += -1;
				}
				else if (matrix[i][j] == 2) {
					matrix[i][j] = -1;
					matrix[i][j + 1] += +1;
				}
				else if (matrix[i][j] == 3) {
					matrix[i][j] = 0;
					matrix[i][j + 1] += +1;
				}
				else if (matrix[i][j] == -3) {
					matrix[i][j] = 0;
					matrix[i][j + 1] += -1;
				}

			}
			cout << "\n";
		}


		for (int j = 0; j < trits; j++) {
			cout << "\nt" << j << ": ";
			for (int i = bits - 1; i > -1; i--) {
				cout << matrix[i][j] << "  ";
			}
			cout << "\n";
		}



		/*
		cout << "all_one_ternary: " << "\n";
		for (int i = 0 ; i < trits; ++i) {
			int & foobar = all_one_ternary[i];
			cout << foobar << "\n";
		}
		cout << "\n\n";
		*/

		cout << "\n\n\n";

		output.clear();
		input.clear();
		all_one_ternary.clear();


	}
	return 0;
}