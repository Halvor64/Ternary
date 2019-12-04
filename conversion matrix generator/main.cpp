// Conversion matrix generator for binary and ternary
// Author: Halvor Nybø Risto
// Date: 4. Dec 2019
// NOTE: This program only works up to 64 bits

#include <iostream>
#include <string>
#include <vector>
#include <math.h>
#include <cstdint>
using namespace std;

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



int main() {
	while (true) {
		if (getValue("Select a converter\n1. Binary to ternary\n2. Ternary to binary\n>", 1, 2) == 1) { // binary to ternary

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


			
			//converting from unsigned to balanced
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

			//printing the matrix
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

			//convert ternary exponents to binary

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