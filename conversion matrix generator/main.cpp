// Conversion matrix generator for binary and ternary
// Author: Halvor Nybø Risto
// Date: 4. Dec 2019
// This program uses two different methods for generating the conversion matrices.
// For binary to ternary, a method nicknamed the "input bit-flipping method" is implemented.
// This method was use to demonstrate that it can be done in this way.
// For the ternary to binary method, an arguably much simpler method is used, nicknamed the Digit Relation method
// NOTE: This program only works up to 64 bits

#include <iostream>
#include <string>
#include <vector>
#include <math.h>
#include <cstdint>
using namespace std;
vector<int> input; //binary inputs 
vector<int> all_one_ternary;
vector<int> output; // ternary outputs
					//vector<int> matrix; //2D vector
// matrices are larger than 64 bit / 41 trit and therefore do not need a dynamic size
int binToTerMatrix[128][128]; // binary to ternary 
int terToBinMatrix[128][128]; // ternary to binary
int bits = 0;
int trits = 0;
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




uint64_t pow64_t(int number, int exponent) {
	uint64_t result = 1;

	for (int i = 0; i < exponent; i++) {
		result *= number;
	}

	return result;
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
		if (getValue("Select a converter\n1. Binary to ternary\n2. Ternary to binary\n>", 1, 2) == 1) { // binary to ternary
			

			// overcomplicated method (stops working after 31 bits)
			/*
			bits = getValue("enter number of binary inputs (0 - 64): ", 0, 64);
			trits = ceil(bits / 1.585); //a trit can replace 1.58496 bits

			cout << "\n";

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
					binToTerMatrix[i][j] = all_one_ternary[j] - output[j];
					//cout << "all_one_ternary["<<j<<"] = " << all_one_ternary[j] << "\n";
					//cout << "output[" << j << "] = " << output[j] << "\n";

				}

				for (int k = bits - 1; k > 0; k--) input[k] = input[k - 1];
				input[0] = 0;

				//cout << "\n";
			}

			for (int j = 0; j < trits; j++) {
				for (int i = bits - 1; i > -1; i--) {
					if (binToTerMatrix[i][j] == -2) {
						binToTerMatrix[i][j] = 1;
						binToTerMatrix[i][j + 1] += -1;
					}
					else if (binToTerMatrix[i][j] == 2) {
						binToTerMatrix[i][j] = -1;
						binToTerMatrix[i][j + 1] += +1;
					}
					else if (binToTerMatrix[i][j] == 3) {
						binToTerMatrix[i][j] = 0;
						binToTerMatrix[i][j + 1] += +1;
					}
					else if (binToTerMatrix[i][j] == -3) {
						binToTerMatrix[i][j] = 0;
						binToTerMatrix[i][j + 1] += -1;
					}

				}
			}

			cout << "    ";
			for (int i = 0; i < bits; i++) {
				cout << "b" << i << " ";
				if (i < 10) cout << " ";
			}
			cout << "\n";
			for (int j = 0; j < trits; j++) {
				cout << "\nt" << j << "= ";
				if (j < 10) cout << " ";
				for (int i = bits - 1; i > -1; i--) {
					if (binToTerMatrix[i][j] == -1) cout << "-   ";
					if (binToTerMatrix[i][j] == +1) cout << "+   ";
					if (binToTerMatrix[i][j] == 0) cout << "0   ";
				}
				cout << "\n";
			}



			
			//cout << "all_one_ternary: " << "\n";
			//for (int i = 0 ; i < trits; ++i) {
			//int & foobar = all_one_ternary[i];
			//cout << foobar << "\n";
			//}
			//cout << "\n\n";
			

			cout << "\n\n\n";

			output.clear();
			input.clear();
			all_one_ternary.clear();
			*/

			
			bits = getValue("enter number of binary outputs (0 - 64): ", 0, 64);
			trits = ceil(bits / 1.585); //a trit can replace 1.58496 bits


			// step one: Convert the decimal value of the binary exponents to unbalanced ternary
			// step two: Convert the unbalanced ternary to balanced ternary

			
			vector<uint64_t> binaryExponents;
			binaryExponents.reserve(bits);
			for (int i = 0; i < bits + 1; i++) {
				binaryExponents.push_back(pow64_t(2, i));
			}
			cout << "\n\n";


			for (int n = 0; n < bits; n++) {		// fill the matrix with unsigned ternary
				//cout << "\nbinary exponent: " << binaryExponents[n] << endl;
				for (int m = 0; m < trits; m++) {
					//cout << binaryExponents[n] % 3;
					binToTerMatrix[n][trits - 1 - m] = binaryExponents[n] % 3;
					binaryExponents[n] = binaryExponents[n] / 3;
				}
			}

			cout << "\n\nunsigned: \n";
			for (int n = 0; n < bits; n++) {		// print the content of matrix
				cout << "\n";
				for (int m = 0; m < trits; m++) {
					cout << binToTerMatrix[n][m];

				}
			}
			cout << "\n\n\n";
/*
			for (int n = 0; n < bits; n++) {
				for (int m = trits-1; m > -1; m--) {
					while (binToTerMatrix[n][m] > 1) {
						binToTerMatrix[n][m] -= 1;
						binToTerMatrix[n][m - 1] += 1;
						if (binToTerMatrix[n][m] == 1) {
							binToTerMatrix[n][m] = -1;
						}
					}
				}
			}
			
*/			//converting from unsigned to balanced
			for (int i = 0; i < bits; i++) { // repeat to ensure there are no leftover 2's
				for (int n = 0; n < bits; n++) {
					for (int m = 0; m < trits; m++) {
						while (binToTerMatrix[n][m] > 1) {
							binToTerMatrix[n][m] -= 1;
							binToTerMatrix[n][m - 1] += 1;
							if (binToTerMatrix[n][m] == 1) {
								binToTerMatrix[n][m] = -1;
							}
						}
					}
				}
			}
			


			cout << "\n\nBalanced: \n";
			
			
			for (int n = 0; n < bits; n++) {		// print the content of matrix
				cout << "\n";
				for (int m = 0; m < trits; m++) {
					if (binToTerMatrix[n][m] == -1) cout << "-   ";
					else if (binToTerMatrix[n][m] == +1) cout << "+   ";
					else if (binToTerMatrix[n][m] == 0) cout << "0   ";
					else cout << binToTerMatrix[n][m] << "   ";
				}
			}
			cout << "\n\n\n";
			
			


			cout << "    ";
			for (int i = 0; i < bits; i++) {
				cout << "b" << bits - 1 - i << " ";
				if (i < 10) cout << " ";
			}
			cout << "\n";
			for (int j = trits-1; j > -1; j--) {
				cout << "\nt" << trits - 1 - j << "= ";
				if (trits - 1 - j < 10) cout << " ";
				for (int i = bits - 1; i > -1; i--) {
					if (binToTerMatrix[i][j] == -1) cout << "-   ";
					if (binToTerMatrix[i][j] == +1) cout << "+   ";
					if (binToTerMatrix[i][j] == 0) cout << "0   ";
				}
				cout << "\n";
			}


		}
		else {	// ternary to binary ======================================================

			bits = getValue("enter number of binary outputs (0 - 64): ", 0, 64);
			trits = ceil(bits / 1.585); //a trit can replace 1.58496 bits
			vector<uint64_t> ternaryExponents;
			ternaryExponents.reserve(trits);
			for (int i = 0; i < trits + 1; i++) {
				ternaryExponents.push_back(pow64_t(3, i));
			}
			cout << "\n\n";



			for (int m = 0; m < trits; m++) {
				for (int n = 0; n < bits; n++) {
					terToBinMatrix[trits - m - 1][bits - n - 1] = ternaryExponents[m] % 2;
					ternaryExponents[m] = ternaryExponents[m] / 2;
				}
			}

			cout << "    ";
			for (int m = 0; m < trits; m++) {
				cout << "t" << m << " ";
				if (m < 10) cout << " ";
			}
			cout << "\n";
			for (int n = bits - 1; n > -1; n--) {
				cout << "b" << bits - 1 - n << "= ";
				if ((bits - 1 - n) < 10) cout << " ";
				for (int m = 0; m < trits; m++) {
					cout << terToBinMatrix[m][n];
					if (m < trits - 1) cout << " + ";
				}
				cout << "\n";
			}
			cout << "\n\n\n";
		}



	}
	return 0;
}