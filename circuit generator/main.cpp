using namespace std;
#include <iostream>;
#include <math.h>       /* pow */
#include <fstream>
#include <string>
char matrix[3][3] = {
					0, 0, 0,
					0, 0, 0,
					0, 0, 0
};

char upvddgnd[3][3] = {
					0, 0, 0,
					0, 0, 0,
					0, 0, 0
};

char downvddgnd[3][3] = {
					0, 0, 0,
					0, 0, 0,
					0, 0, 0
};

char uphalfvdd[3][3] = {
					0, 0, 0,
					0, 0, 0,
					0, 0, 0
};

char downhalfvdd[3][3] = {
					0, 0, 0,
					0, 0, 0,
					0, 0, 0
};

char backup0[3][3];
char backup1[3][3];
char backup2[3][3];
char backup3[3][3];

bool group[4][48];

bool rwGroup(int index, int array, char c, char rw) { //this function reads or writes to the 3x3 arrays. 
// In read mode, it will look for c in the specified grouping, and return true if it is found.
// In write mode, it will write c to the specified grouping. Write mode returns false.
	bool result = false;

	char m[3][3] = { '0','0','0','0','0','0','0','0','0' };

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (array == 0) {
				m[i][j] = upvddgnd[i][j];
			}
			if (array == 1) {
				m[i][j] = downvddgnd[i][j];
			}
			if (array == 2) {
				m[i][j] = uphalfvdd[i][j];
			}
			if (array == 3) {
				m[i][j] = downhalfvdd[i][j];
			}
			if (array == 9) {
				m[i][j] = matrix[i][j];
			}
		}
	}

	////////////////////////////////////////
	// The indexes are ordered in terms of size.
	// (should they be ordered in terms of transistors per value?)

	if (index == 0) {
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {

				if (rw == 'r') {
					if (m[i][j] == c) result = true;
				}
				else {
					m[i][j] = c;
				}

			}
		}
	}



	// 2x3 grouping: (4)
	if ((index > 0) && (index < 5)) {
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 3; j++) {

				if (index == 1) {
					if (rw == 'r') {
						if (m[i][j] == c) result = true;
					}
					else {
						m[i][j] = c;
					}

				}
				if (index == 2) {
					if (rw == 'r') {
						if (m[i + 1][j] == c) result = true;
					}
					else {
						m[i + 1][j] = c;
					}
				}
				if (index == 3) {
					if (rw == 'r') {
						if (m[j][i] == c) result = true;
					}
					else {
						m[j][i] = c;
					}
				}
				if (index == 4) {
					if (rw == 'r') {
						if (m[j][i + 1] == c) result = true;
					}
					else {
						m[j][i + 1] = c;
					}

				}
			}
		}
	}


	// 2x3 wrapping is pointless
	//2x3 wrapping (2)
	/*
	if (index == 5) {
		for (int i = 0; i < 3; i=i+2) {
			for (int j = 0; j < 3; j++) {

				if (rw == 'r') {
					if (m[i][j] == c) result = true;
				}
				else {
					m[i][j] = c;
				}

			}
		}
	}

	if (index == 6) {
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j=j+2) {

				if (rw == 'r') {
					if (m[i][j] == c) result = true;
				}
				else {
					m[i][j] = c;
				}

			}
		}
	}
	*/

	// 2x2 grouping: (4)
	if ((index > 4) && (index < 9)) {
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++) {

				if (index == 5) {
					if (rw == 'r') {
						if (m[i][j] == c) result = true;
					}
					else {
						m[i][j] = c;
					}

				}
				if (index == 6) {
					if (rw == 'r') {
						if (m[i + 1][j] == c) result = true;
					}
					else {
						m[i + 1][j] = c;
					}

				}
				if (index == 7) {
					if (rw == 'r') {
						if (m[i][j + 1] == c) result = true;
					}
					else {
						m[i][j + 1] = c;
					}

				}
				if (index == 8) {
					if (rw == 'r') {
						if (m[i + 1][j + 1] == c) result = true;
					}
					else {
						m[i + 1][j + 1] = c;
					}
				}
			}
		}
	}


	// 2x2 wrapping (4)


	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 3; j = j + 2) {
			if (index == 9) {
				if (rw == 'r') {
					if (m[i][j] == c) result = true;
				}
				else {
					m[i][j] = c;
				}
			}
			if (index == 10) {
				if (rw == 'r') {
					if (m[i + 1][j] == c) result = true;
				}
				else {
					m[i + 1][j] = c;
				}
			}


		}
	}

	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 3; j = j + 2) {
			if (index == 11) {
				if (rw == 'r') {
					if (m[j][i] == c) result = true;
				}
				else {
					m[j][i] = c;
				}
			}
			if (index == 12) {
				if (rw == 'r') {
					if (m[j][i + 1] == c) result = true;
				}
				else {
					m[j][i + 1] = c;
				}
			}
		}
	}



	// 1x3 grouping: (6)

	if ((index > 12) && (index < 19)) {
		for (int i = 0; i < 3; i++) {

			if (index == 13) {
				if (rw == 'r') {
					if (m[0][i] == c) result = true;
				}
				else {
					m[0][i] = c;
				}
			}
			if (index == 14) {
				if (rw == 'r') {
					if (m[1][i] == c) result = true;
				}
				else {
					m[1][i] = c;
				}
			}
			if (index == 15) {
				if (rw == 'r') {
					if (m[2][i] == c) result = true;
				}
				else {
					m[2][i] = c;
				}

			}
			if (index == 16) {
				if (rw == 'r') {
					if (m[i][0] == c) result = true;
				}
				else {
					m[i][0] = c;
				}
			}
			if (index == 17) {
				if (rw == 'r') {
					if (m[i][1] == c) result = true;
				}
				else {
					m[i][1] = c;
				}
			}
			if (index == 18) {
				if (rw == 'r') {
					if (m[i][2] == c) result = true;
				}
				else {
					m[i][2] = c;
				}
			}
		}
	}


	// 1x3 wrapping (0)
	//there are none

	// 1x2 grouping: (12)
	if ((index > 18) && (index < 31)) {
		for (int i = 0; i < 2; i++) {

			if (index == 19) {
				if (rw == 'r') {
					if (m[0][i] == c) result = true;
				}
				else {
					m[0][i] = c;
				}
			}
			if (index == 20) {
				if (rw == 'r') {
					if (m[1][i] == c) result = true;
				}
				else {
					m[1][i] = c;
				}
			}
			if (index == 21) {
				if (rw == 'r') {
					if (m[2][i] == c) result = true;
				}
				else {
					m[2][i] = c;
				}
			}
			if (index == 22) {
				if (rw == 'r') {
					if (m[i][0] == c) result = true;
				}
				else {
					m[i][0] = c;
				}
			}
			if (index == 23) {
				if (rw == 'r') {
					if (m[i][1] == c) result = true;
				}
				else {
					m[i][1] = c;
				}
			}
			if (index == 24) {
				if (rw == 'r') {
					if (m[i][2] == c) result = true;
				}
				else {
					m[i][2] = c;
				}
			}
			if (index == 25) {
				if (rw == 'r') {
					if (m[0][i + 1] == c) result = true;
				}
				else {
					m[0][i + 1] = c;
				}
			}
			if (index == 26) {
				if (rw == 'r') {
					if (m[1][i + 1] == c) result = true;
				}
				else {
					m[1][i + 1] = c;
				}
			}
			if (index == 27) {
				if (rw == 'r') {
					if (m[2][i + 1] == c) result = true;
				}
				else {
					m[2][i + 1] = c;
				}
			}
			if (index == 28) {
				if (rw == 'r') {
					if (m[i + 1][0] == c) result = true;
				}
				else {
					m[i + 1][0] = c;
				}
			}
			if (index == 29) {
				if (rw == 'r') {
					if (m[i + 1][1] == c) result = true;
				}
				else {
					m[i + 1][1] = c;
				}
			}
			if (index == 30) {
				if (rw == 'r') {
					if (m[i + 1][2] == c) result = true;
				}
				else {
					m[i + 1][2] = c;
				}
			}
		}
	}


	// 1x2 wrapping (6)

	for (int i = 0; i < 3; i = i + 2) {
		if (index == 31) {
			if (rw == 'r') {
				if (m[i][0] == c) result = true;
			}
			else {
				m[i][0] = c;
			}
		}
		if (index == 32) {
			if (rw == 'r') {
				if (m[i][1] == c) result = true;
			}
			else {
				m[i][1] = c;
			}
		}
		if (index == 33) {
			if (rw == 'r') {
				if (m[i][2] == c) result = true;
			}
			else {
				m[i][2] = c;
			}
		}
		if (index == 34) {
			if (rw == 'r') {
				if (m[0][i] == c) result = true;
			}
			else {
				m[0][i] = c;
			}
		}
		if (index == 35) {
			if (rw == 'r') {
				if (m[1][i] == c) result = true;
			}
			else {
				m[1][i] = c;
			}
		}
		if (index == 36) {
			if (rw == 'r') {
				if (m[2][i] == c) result = true;
			}
			else {
				m[2][i] = c;
			}
		}

	}


	// 1x1 (9)

	if (index == 37) {
		if (rw == 'r') {
			if (m[0][0] == c) result = true;
		}
		else {
			m[0][0] = c;
		}
	}
	if (index == 38) {
		if (rw == 'r') {
			if (m[0][1] == c) result = true;
		}
		else {
			m[0][1] = c;
		}
	}
	if (index == 39) {
		if (rw == 'r') {
			if (m[0][2] == c) result = true;
		}
		else {
			m[0][2] = c;
		}
	}
	if (index == 40) {
		if (rw == 'r') {
			if (m[1][0] == c) result = true;
		}
		else {
			m[1][0] = c;
		}
	}
	if (index == 41) {
		if (rw == 'r') {
			if (m[1][1] == c) result = true;
		}
		else {
			m[1][1] = c;
		}
	}
	if (index == 42) {
		if (rw == 'r') {
			if (m[1][2] == c) result = true;
		}
		else {
			m[1][2] = c;
		}
	}
	if (index == 43) {
		if (rw == 'r') {
			if (m[2][0] == c) result = true;
		}
		else {
			m[2][0] = c;
		}
	}
	if (index == 44) {
		if (rw == 'r') {
			if (m[2][1] == c) result = true;
		}
		else {
			m[2][1] = c;
		}
	}
	if (index == 45) {
		if (rw == 'r') {
			if (m[2][2] == c) result = true;
		}
		else {
			m[2][2] = c;
		}
	}

	if (rw == 'w') {
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				if (array == 0) {
					upvddgnd[i][j] = m[i][j];
				}
				if (array == 1) {
					downvddgnd[i][j] = m[i][j];
				}
				if (array == 2) {
					uphalfvdd[i][j] = m[i][j];
				}
				if (array == 3) {
					downhalfvdd[i][j] = m[i][j];
				}
				if (array == 9) {
					matrix[i][j] = m[i][j];
				}
			}
		}
	}



	return result;
}





int main() {
	while (true) {
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				cout << "Enter the value of column " << j << " and row " << i << ": ";
				cin >> matrix[i][j];
			}

		}


		cout << "\n\n\ninput truth table: \n";
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				cout << matrix[i][j] << " ";
			}
			cout << endl;
		}

		


		//magic
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				if (matrix[i][j] == 'x') {
					upvddgnd[i][j] = 'x';
					downvddgnd[i][j] = 'x';
					uphalfvdd[i][j] = 'x';
					downhalfvdd[i][j] = 'x';
				}
				if (matrix[i][j] == '0') {
					upvddgnd[i][j] = '0';
					downvddgnd[i][j] = '1';
					uphalfvdd[i][j] = '0';
					downhalfvdd[i][j] = 'x';
				}
				if (matrix[i][j] == '1') {
					upvddgnd[i][j] = '0';
					downvddgnd[i][j] = '0';
					uphalfvdd[i][j] = '1';
					downhalfvdd[i][j] = '1';
				}
				if (matrix[i][j] == '2') {
					upvddgnd[i][j] = '1';
					downvddgnd[i][j] = '0';
					uphalfvdd[i][j] = 'x';
					downhalfvdd[i][j] = '0';
				}
			}

		}

		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				backup0[i][j] = upvddgnd[i][j];
				backup1[i][j] = downvddgnd[i][j];
				backup2[i][j] = uphalfvdd[i][j];
				backup3[i][j] = downhalfvdd[i][j];
			}
		}


		cout << "upvddgnd: \n";
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				cout << upvddgnd[i][j] << " ";
			}
			cout << endl;
		}

		cout << "downvddgnd: \n";
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				cout << downvddgnd[i][j] << " ";
			}
			cout << endl;
		}

		cout << "uphalfvdd: \n";
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				cout << uphalfvdd[i][j] << " ";
			}
			cout << endl;
		}

		cout << "downhalfvdd: \n";
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				cout << downhalfvdd[i][j] << " ";
			}
			cout << endl;
		}
		cout << "\n\n\n\n";


		// prints all the possible groupings.  (repurposes the first input matrix)
		for (int i = 0; i < 48; i++) {
			rwGroup(0, 9, '0', 'w');
			rwGroup(i, 9, 'Z', 'w');
			cout << i << ": \n";
			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 3; j++) {
					cout << matrix[i][j] << " ";
				}
				cout << endl;
			}


		}


		for (int i = 0; i < 48; i++) {	 // checks for each group in each network if a 0 is found. set group to true if none is.
			for (int j = 0; j < 4; j++) {
				group[j][i] = !rwGroup(i, j, '0', 'r');
				if (!rwGroup(i, j, '1', 'r')) group[j][i] = false; // if a group does not contain a '1' (e.g. only x), set the group to false
			}
		}


		//removes smaller unnecessary groups 
		for (int i = 0; i < 48; i++) {				// for the larger true groups, the array is rewritten with 0s over the group. if a smaller group has no 1s, it can be removed
			for (int j = 0; j < 4; j++) {
				if (rwGroup(0, j, '1', 'r')) {						//if there is a 1 in the group
					if (group[j][i]) rwGroup(i, j, '0', 'w');		//and	if the group is true, set the group in the matrix to '0'
				}
				else group[j][i] = false;							//else, if no 1 was found, set the group to false 		
			}
		}



		//checks that none of the groups are fully covered by the sum of the other groups, for each network
		// (this can happen with groupings of the same dimensions)
		for (int i = 0; i < 4; i++) { // 4 networks
			rwGroup(0, 9, '0', 'w');
			for (int j = 0; j < 48; j++) {
				if (group[i][j] == true) {
					// go through again and mark all the other ones except this one
					rwGroup(0, 9, '0', 'w'); // sets whole array to 0

					for (int k = 0; k < 48; k++) {
						if (group[i][k] == true) {
							if (k != j) {
								rwGroup(k, 9, 'x', 'w');
							}
						}
					}

					if (!rwGroup(j, 9, '0', 'r')) group[i][j] = false; // if there is nothing left to cover by the group, set it to false
				}
			}




		}


		// do the same thing again but with the preexisting x's this time. 

		for (int i = 0; i < 4; i++) { // 4 networks
			rwGroup(0, 9, '0', 'w');
			for (int j = 0; j < 48; j++) {
				if (group[i][j] == true) {
					// go through again and mark all the other ones except this one
					rwGroup(0, 9, '0', 'w'); // sets whole array to 0

					for (int k = 0; k < 48; k++) {
						if (group[i][k] == true) {
							if (k != j) {
								rwGroup(k, 9, 'x', 'w');
							}
						}
					}



					for (int m = 0; m < 3; m++) { // set x's
						for (int n = 0; n < 3; n++) {
							if (i == 2) {
								if (backup2[m][n] == 'x') matrix[m][n] = 'x';
							}
							if (i == 3) {
								if (backup3[m][n] == 'x') matrix[m][n] = 'x';
							}
						}
					}

					if (!rwGroup(j, 9, '0', 'r')) group[i][j] = false; // if there is nothing left to cover by the group, set it to false
				}
			}
		}






		for (int n = 0; n < 4; n++) {
			if (n == 0) cout << "\n\nupvddgnd: \n";
			if (n == 1) cout << "\n\ndownvddgnd: \n";
			if (n == 2) cout << "\n\nuphalfvdd: \n";
			if (n == 3) cout << "\n\ndownhalfvdd: \n";
			for (int i = 0; i < 48; i++) {
				if (group[n][i] == true) {
					rwGroup(0, 9, '0', 'w');
					rwGroup(i, 9, '1', 'w');
					rwGroup(i, n, '1', 'w'); //for reconstruction purposes
					cout << i << ": \n";
					for (int j = 0; j < 3; j++) {
						for (int k = 0; k < 3; k++) {
							cout << matrix[j][k] << " ";
						}
						cout << endl;
					}
				}
			}
		}


		

		cout << "\n\n true circuit truthtable: \n";

		int function_index = 0;
		// The true circuit truthtable is reconstructed (with no x)
		rwGroup(0, 9, '0', 'w');
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				if (uphalfvdd[i][j] == downhalfvdd[i][j]) {
					matrix[i][j] = uphalfvdd[i][i];
				}
				if (upvddgnd[i][j] == '1') {
					matrix[i][j] = '2';
				}
				if (downvddgnd[i][j] == '1') {
					matrix[i][j] = '0';
				}


				cout << matrix[i][j] << " ";
				if (matrix[i][j] == '1'){
					function_index += int(pow(3,(3*i + j)));
				}
				if (matrix[i][j] == '2') {
					function_index += int(2*pow(3, (3 * i + j)));
				}

			}
			cout << endl;
		}
		cout << "function index: " << function_index;
		cout << "\n\n";

		

		/////



		string filename = "f_";
		for (int i = 0; i < 5 - to_string(function_index).length(); i++) { filename += "0"; }
		filename += to_string(function_index);
		filename += ".sp";
		ofstream myfile;
		myfile.open(filename);


		//red = 0.783nm, covers one from the side
		//blue = 1.487nm, covers two from the side
		// p-type from left and top
		// n-type from right and bottom


		

		string n0 = " ntype 1.018nm";
		string n1 = " ntype 0.783nm";
		string n2 = " ntype 1.487nm";
		string p0 = " ptype 1.018nm";
		string p1 = " ptype 0.783nm";
		string p2 = " ptype 1.487nm";
		string out = "";

		
		
		


		cout << ".subckt f" << function_index << " a b out vdd\n";
		cout << "\n\nxp0 up out out" << p0;
		cout << "\nxn0 out out down" << n0;
		int connections = 0;
		int transistors = 2;

		for (int i = 0; i < 4; i++) {

			if (i == 0) {
				cout << "\n******** UpVddGnd ********\n\n";
				out = "out";
			}
			if (i == 1) {
				cout << "\n******** DownVddGnd ********";
				out = "out";
			}
			if (i == 2) {
				cout << "\n******** UpHalfVdd ********";
				out = "up";
			}

			if (i == 3) {
				cout << "\n******** DownHalfVdd ********";
				out = "down";
			}



			if (group[i][0]) {

				cout << "\n *DIRECT CONNECTION \n\n";
				cout << "Vs " << out;
				if (i % 2 == 0) cout << " vdd 0"; else cout << " gnd 0";  
			}
			if (group[i][1]) {

				cout << "\nxp" << transistors;
				if (i % 2 == 0) cout << " vdd"; else cout << " gnd";
				cout << " b " << out << p2 << "\n";
				transistors += 1;

			}
			if (group[i][2]) {


				cout << "\nxn" << transistors;
				if (i % 2 == 0) cout << " vdd"; else cout << " gnd";
				cout << " b " << out << n2 << "\n";
				transistors += 1;
			}
			if (group[i][3]) {


				cout << "\nxp" << transistors;
				if (i % 2 == 0) cout << " vdd"; else cout << " gnd";
				cout << " a " << out << p2 << "\n";
				transistors += 1;
			}
			if (group[i][4]) {


				cout << "\nxn" << transistors;
				if (i % 2 == 0) cout << " vdd"; else cout << " gnd";
				cout << " a " << out << n2 << "\n";
				transistors += 1;
			}
			if (group[i][5]) {


				cout << "\nxp" << transistors;
				if (i % 2 == 0) cout << " vdd"; else cout << " gnd";
				cout << " a p" << connections << p2 << "\n";
				transistors += 1;

				cout << "\nxp" << transistors;
				cout << " p" << connections << " b " << out << p2 << "\n";
				transistors += 1;
				connections += 1;
			}
			if (group[i][6]) {


				cout << "\nxp" << transistors;
				if (i % 2 == 0) cout << " vdd"; else cout << " gnd";
				cout << " a p" << connections << p2 << "\n";
				transistors += 1;

				cout << "\nxn" << transistors;
				cout << " p" << connections << " b " << out << n2 << "\n";
				transistors += 1;
				connections += 1;
			}
			if (group[i][7]) {


				cout << "\nxn" << transistors;
				if (i % 2 == 0) cout << " vdd"; else cout << " gnd";
				cout << " a p" << connections << n2 << "\n";
				transistors += 1;

				cout << "\nxp" << transistors;
				cout << " p" << connections << " b " << out << p2 << "\n";
				transistors += 1;
				connections += 1;
			}
			if (group[i][8]) {


				cout << "\nxn" << transistors;
				if (i % 2 == 0) cout << " vdd"; else cout << " gnd";
				cout << " a p" << connections << n2 << "\n";
				transistors += 1;

				cout << "\nxn" << transistors;
				cout << " p" << connections << " b " << out << n2 << "\n";
				transistors += 1;
				connections += 1;
			}
			if (group[i][9]) {


				cout << "\nxp" << transistors;
				if (i % 2 == 0) cout << " vdd"; else cout << " gnd";
				cout << " b p" << connections << p2 << "\n";
				transistors += 1;

				cout << "\nxp" << transistors;
				cout << " p" << connections << " a " << out << p1 << "\n";
				transistors += 1;

				cout << "\nxn" << transistors;
				cout << " p" << connections << " a " << out << n1 << "\n";
				transistors += 1;
				connections += 1;

			}
			if (group[i][10]) {


				cout << "\nxn" << transistors;
				if (i % 2 == 0) cout << " vdd"; else cout << " gnd";
				cout << " b p" << connections << n2 << "\n";
				transistors += 1;

				cout << "\nxp" << transistors;
				cout << " p" << connections << " a p" << connections + 1 << p1 << "\n";
				transistors += 1;

				cout << "\nxn" << transistors;
				cout << " p" << connections << " a " << out << n1 << "\n";
				transistors += 1;
				connections += 1;
			}
			if (group[i][11]) {


				cout << "\nxp" << transistors;
				if (i % 2 == 0) cout << " vdd"; else cout << " gnd";
				cout << " a p" << connections << p2 << "\n";
				transistors += 1;

				cout << "\nxp" << transistors;
				cout << " p" << connections << " b " << out << p1 << "\n";
				transistors += 1;

				cout << "\nxn" << transistors;
				cout << " p" << connections << " b " << out << n1 << "\n";
				transistors += 1;
				connections += 1;
			}
			if (group[i][12]) {


				cout << "\nxn" << transistors;
				if (i % 2 == 0) cout << " vdd"; else cout << " gnd";
				cout << " a p" << connections << n2 << "\n";
				transistors += 1;

				cout << "\nxp" << transistors;
				cout << " p" << connections << " b " << out << p1 << "\n";
				transistors += 1;

				cout << "\nxn" << transistors;
				cout << " p" << connections << " b " << out << n1 << "\n";
				transistors += 1;
				connections += 1;
			}


			if (group[i][13]) {


				cout << "\nxp" << transistors;
				if (i % 2 == 0) cout << " vdd"; else cout << " gnd";
				cout << " b " << out << p1 << "\n";
				transistors += 1;

			}
			if (group[i][14]) {


				cout << "\nxn" << transistors;
				if (i % 2 == 0) cout << " vdd"; else cout << " gnd";
				cout << " b p" << connections << n2 << "\n";
				transistors += 1;

				cout << "\nxp" << transistors;
				cout << " p" << connections << " b " << out << p2 << "\n";
				transistors += 1;
				connections += 1;
			}
			if (group[i][15]) {


				cout << "\nxn" << transistors;
				if (i % 2 == 0) cout << " vdd"; else cout << " gnd";
				cout << " b " << out << n1 << "\n";
				transistors += 1;
			}
			if (group[i][16]) {


				cout << "\nxp" << transistors;
				if (i % 2 == 0) cout << " vdd"; else cout << " gnd";
				cout << " a " << out << p1 << "\n";
				transistors += 1;
			}
			if (group[i][17]) {


				cout << "\nxn" << transistors;
				if (i % 2 == 0) cout << " vdd"; else cout << " gnd";
				cout << " a p" << connections << n2 << "\n";
				transistors += 1;

				cout << "\nxp" << transistors;
				cout << " p" << connections << " a " << out << p2 << "\n";
				transistors += 1;
				connections += 1;
			}
			if (group[i][18]) {


				cout << "\nxn" << transistors;
				if (i % 2 == 0) cout << " vdd"; else cout << " gnd";
				cout << " a " << out << n1 << "\n";
				transistors += 1;
			}
			if (group[i][19]) {


				cout << "\nxp" << transistors;
				if (i % 2 == 0) cout << " vdd"; else cout << " gnd";
				cout << " a p" << connections << p2 << "\n";
				transistors += 1;

				cout << "\nxp" << transistors;
				cout << " p" << connections << " b " << out << p1 << "\n";
				transistors += 1;


			}
			if (group[i][20]) {


				cout << "\nxn" << transistors;
				if (i % 2 == 0) cout << " vdd"; else cout << " gnd";
				cout << " b p" << connections << n2 << "\n";
				transistors += 1;

				cout << "\nxp" << transistors;
				cout << " p" << connections << " b p" << connections + 1 << p2 << "\n";
				transistors += 1;
				connections += 1;

				cout << "\nxp" << transistors;
				cout << " p" << connections << " a " << out << p2 << "\n";
				transistors += 1;

			}
			if (group[i][21]) {


				cout << "\nxn" << transistors;
				if (i % 2 == 0) cout << " vdd"; else cout << " gnd";
				cout << " b p" << connections << n1 << "\n";
				transistors += 1;

				cout << "\nxp" << transistors;
				cout << " p" << connections << " a " << out << p2 << "\n";
				transistors += 1;


			}
			if (group[i][22]) {


				cout << "\nxp" << transistors;
				if (i % 2 == 0) cout << " vdd"; else cout << " gnd";
				cout << " a p" << connections << p1 << "\n";
				transistors += 1;

				cout << "\nxp" << transistors;
				cout << " p" << connections << " b " << out << p2 << "\n";
				transistors += 1;
				connections += 1;

			}
			if (group[i][23]) {


				cout << "\nxn" << transistors;
				if (i % 2 == 0) cout << " vdd"; else cout << " gnd";
				cout << " a p" << connections << n2 << "\n";
				transistors += 1;

				cout << "\nxp" << transistors;
				cout << " p" << connections << " a p" << connections + 1 << p2 << "\n";
				transistors += 1;
				connections += 1;

				cout << "\nxp" << transistors;
				cout << " p" << connections << " b out" << p2 << "\n";
				transistors += 1;
				connections += 1;
			}
			if (group[i][24]) {


				cout << "\nxn" << transistors;
				if (i % 2 == 0) cout << " vdd"; else cout << " gnd";
				cout << " a p" << connections << n1 << "\n";
				transistors += 1;

				cout << "\nxp" << transistors;
				cout << " p" << connections << " b " << out << p2 << "\n";
				transistors += 1;
				connections += 1;

			}
			if (group[i][25]) {


				cout << "\nxn" << transistors;
				if (i % 2 == 0) cout << " vdd"; else cout << " gnd";
				cout << " a p" << connections << n2 << "\n";
				transistors += 1;

				cout << "\nxp" << transistors;
				cout << " p" << connections << " b " << out << p1 << "\n";
				transistors += 1;
			}
			if (group[i][26]) {


				cout << "\nxn" << transistors;
				if (i % 2 == 0) cout << " vdd"; else cout << " gnd";
				cout << " b p" << connections << n2 << "\n";
				transistors += 1;

				cout << "\nxp" << transistors;
				cout << " p" << connections << " b p" << connections + 1 << p2 << "\n";
				transistors += 1;
				connections += 1;

				cout << "\nxn" << transistors;
				cout << " p" << connections << " a " << out << n2 << "\n";
				transistors += 1;
				connections += 1;
			}
			if (group[i][27]) {


				cout << "\nxn" << transistors;
				if (i % 2 == 0) cout << " vdd"; else cout << " gnd";
				cout << " b p" << connections << n1 << "\n";
				transistors += 1;

				cout << "\nxn" << transistors;
				if (i % 2 == 0) cout << " vdd"; else cout << " gnd";
				cout << " a " << out << n2 << "\n";
				transistors += 1;
			}
			if (group[i][28]) {


				cout << "\nxp" << transistors;
				if (i % 2 == 0) cout << " vdd"; else cout << " gnd";
				cout << " a p" << connections << p1 << "\n";
				transistors += 1;

				cout << "\nxn" << transistors;
				if (i % 2 == 0) cout << " vdd"; else cout << " gnd";
				cout << " b " << out << n2 << "\n";
				transistors += 1;

			}
			if (group[i][29]) {


				cout << "\nxn" << transistors;
				if (i % 2 == 0) cout << " vdd"; else cout << " gnd";
				cout << " a p" << connections << n2 << "\n";
				transistors += 1;

				cout << "\nxp" << transistors;
				cout << " p" << connections << " a p" << connections + 1 << p2 << "\n";
				transistors += 1;
				connections += 1;

				cout << "\nxn" << transistors;
				cout << " p" << connections << " b " << out << n2 << "\n";
				transistors += 1;
				connections += 1;
			}
			if (group[i][30]) {


				cout << "\nxn" << transistors;
				if (i % 2 == 0) cout << " vdd"; else cout << " gnd";
				cout << " a p" << connections << n1 << "\n";
				transistors += 1;

				cout << "\nxn" << transistors;
				cout << " p" << connections << " b " << out << n2 << "\n";
				transistors += 1;
				connections += 1;
			}
			if (group[i][31]) {


				cout << "\nxp" << transistors;
				if (i % 2 == 0) cout << " vdd"; else cout << " gnd";
				cout << " a p" << connections << p1 << "\n";
				transistors += 1;

				cout << "\nxn" << transistors;
				cout << " p" << connections << " b " << out << n1 << "\n";
				transistors += 1;

				cout << "\nxp" << transistors;
				cout << " p" << connections << " b " << out << p1 << "\n";
				transistors += 1;
				connections += 1;
			}
			if (group[i][32]) {


				cout << "\nxp" << transistors;
				if (i % 2 == 0) cout << " vdd"; else cout << " gnd";
				cout << " a p" << connections << p2 << "\n";
				transistors += 1;

				cout << "\nxn" << transistors;
				cout << " p" << connections << " a p" << connections + 1 << n2 << "\n";
				transistors += 1;
				connections += 1;



				cout << "\nxn" << transistors;
				cout << " p" << connections << " b " << out << n1 << "\n";
				transistors += 1;

				cout << "\nxp" << transistors;
				cout << " p" << connections << " b " << out << p1 << "\n";

				transistors += 1;
				connections += 1;
			}
			if (group[i][33]) {


				cout << "\nxn" << transistors;
				if (i % 2 == 0) cout << " vdd"; else cout << " gnd";
				cout << " a p" << connections << n1 << "\n";
				transistors += 1;

				cout << "\nxn" << transistors;
				cout << " p" << connections << " b " << out << n1 << "\n";
				transistors += 1;


				cout << "\nxp" << transistors;
				cout << " p" << connections << " b " << out << p1 << "\n";
				transistors += 1;
				connections += 1;
			}
			if (group[i][34]) {


				cout << "\nxp" << transistors;
				if (i % 2 == 0) cout << " vdd"; else cout << " gnd";
				cout << " b p" << connections << p1 << "\n";
				transistors += 1;

				cout << "\nxn" << transistors;
				cout << " p" << connections << " a " << out << n1 << "\n";
				transistors += 1;

				cout << "\nxp" << transistors;
				cout << " p" << connections << " a " << out << p1 << "\n";
				transistors += 1;
				connections += 1;
			}
			if (group[i][35]) {


				cout << "\nxp" << transistors;
				if (i % 2 == 0) cout << " vdd"; else cout << " gnd";
				cout << " b p" << connections << p2 << "\n";
				transistors += 1;

				cout << "\nxn" << transistors;
				cout << " p" << connections << " b p" << connections + 1 << n2 << "\n";
				transistors += 1;
				connections += 1;



				cout << "\nxn" << transistors;
				cout << " p" << connections << " a " << out << n1 << "\n";
				transistors += 1;

				cout << "\nxp" << transistors;
				cout << " p" << connections << " a " << out << p1 << "\n";

				transistors += 1;
				connections += 1;
			}
			if (group[i][36]) {


				cout << "\nxn" << transistors;
				if (i % 2 == 0) cout << " vdd"; else cout << " gnd";
				cout << " b p" << connections << n1 << "\n";
				transistors += 1;

				cout << "\nxn" << transistors;
				cout << " p" << connections << " a " << out << n1 << "\n";
				transistors += 1;

				cout << "\nxp" << transistors;
				cout << " p" << connections << " a " << out << p1 << "\n";
				transistors += 1;
				connections += 1;
			}
			if (group[i][37]) {


				cout << "\nxp" << transistors;
				if (i % 2 == 0) cout << " vdd"; else cout << " gnd";
				cout << " b p" << connections << p1 << "\n";
				transistors += 1;

				cout << "\nxp" << transistors;
				cout << " p" << connections << " a " << out << p1 << "\n";
				transistors += 1;
				connections += 1;
			}
			if (group[i][38]) {


				cout << "\nxp" << transistors;
				if (i % 2 == 0) cout << " vdd"; else cout << " gnd";
				cout << " b p" << connections << p1 << "\n";
				transistors += 1;

				cout << "\nxn" << transistors;
				cout << " p" << connections << " a p" << connections + 1 << n2 << "\n";
				transistors += 1;
				connections += 1;

				cout << "\nxp" << transistors;
				cout << " p" << connections << " a " << out << p2 << "\n";
				transistors += 1;
				connections += 1;
			}
			if (group[i][39]) {


				cout << "\nxp" << transistors;
				if (i % 2 == 0) cout << " vdd"; else cout << " gnd";
				cout << " b p" << connections << p1 << "\n";
				transistors += 1;

				cout << "\nxn" << transistors;
				cout << " p" << connections << " a " << out << n1 << "\n";
				transistors += 1;
				connections += 1;
			}
			if (group[i][40]) {


				cout << "\nxp" << transistors;
				if (i % 2 == 0) cout << " vdd"; else cout << " gnd";
				cout << " a p" << connections << p1 << "\n";
				transistors += 1;

				cout << "\nxn" << transistors;
				cout << " p" << connections << " b p" << connections + 1 << n2 << "\n";
				transistors += 1;
				connections += 1;

				cout << "\nxp" << transistors;
				cout << " p" << connections << " b " << out << p2 << "\n";
				transistors += 1;
				connections += 1;
			}
			if (group[i][41]) {


				cout << "\nxp" << transistors;
				if (i % 2 == 0) cout << " vdd"; else cout << " gnd";
				cout << " a p" << connections << p2 << "\n";
				transistors += 1;

				cout << "\nxn" << transistors;
				cout << " p" << connections << " a p" << connections + 1 << n2 << "\n";
				transistors += 1;
				connections += 1;

				cout << "\nxn" << transistors;
				cout << " p" << connections << " b p" << connections + 1 << n2 << "\n";
				transistors += 1;
				connections += 1;

				cout << "\nxp" << transistors;
				cout << " p" << connections << " b " << out << p2 << "\n";
				transistors += 1;
				connections += 1;


			}
			if (group[i][42]) {


				cout << "\nxn" << transistors;
				if (i % 2 == 0) cout << " vdd"; else cout << " gnd";
				cout << " a p" << connections << n1 << "\n";
				transistors += 1;

				cout << "\nxn" << transistors;
				cout << " p" << connections << " b p" << connections + 1 << n2 << "\n";
				transistors += 1;
				connections += 1;

				cout << "\nxp" << transistors;
				cout << " p" << connections << " b " << out << p2 << "\n";
				transistors += 1;
				connections += 1;
			}
			if (group[i][43]) {


				cout << "\nxn" << transistors;
				if (i % 2 == 0) cout << " vdd"; else cout << " gnd";
				cout << " b p" << connections << n1 << "\n";
				transistors += 1;

				cout << "\nxp" << transistors;
				cout << " p" << connections << " a " << out << p1 << "\n";
				transistors += 1;
				connections += 1;
			}

			if (group[i][44]) {


				cout << "\nxn" << transistors;
				if (i % 2 == 0) cout << " vdd"; else cout << " gnd";
				cout << " b p" << connections << n1 << "\n";
				transistors += 1;

				cout << "\nxn" << transistors;
				cout << " p" << connections << " a p" << connections + 1 << n2 << "\n";
				transistors += 1;
				connections += 1;

				cout << "\nxp" << transistors;
				cout << " p" << connections << " a " << out << p2 << "\n";
				transistors += 1;
				connections += 1;
			}

			if (group[i][45]) {


				cout << "\nxn" << transistors;
				if (i % 2 == 0) cout << " vdd"; else cout << " gnd";
				cout << " b p" << connections << n1 << "\n";
				transistors += 1;

				cout << "\nxn" << transistors;
				cout << " p" << connections << " a " << out << n1 << "\n";
				transistors += 1;
				connections += 1;
			}

		}
		cout << "\n\n.end\n\n";




		myfile << ".subckt f" << function_index << " a b out vdd\n";
		myfile << "\n\nxp0 up out out" << p0;
		myfile << "\nxn0 out out down" << n0;
		connections = 0;
		transistors = 2;



		for (int i = 0; i < 4; i++) {

			if (i == 0) {
				myfile << "\n******** UpVddGnd ********\n\n";
				out = "out";
			}
			if (i == 1) {
				myfile << "\n******** DownVddGnd ********";
				out = "out";
			}
			if (i == 2) {
				myfile << "\n******** UpHalfVdd ********";
				out = "up";
			}

			if (i == 3) {
				myfile << "\n******** DownHalfVdd ********";
				out = "down";
			}



			if (group[i][0]) {

				myfile << "\n *DIRECT CONNECTION \n\n";
				myfile << "Vs " << out;
				if (i % 2 == 0) myfile << " vdd 0"; else myfile << " gnd 0";
			}
			if (group[i][1]) {

				myfile << "\nxp" << transistors;
				if (i % 2 == 0) myfile << " vdd"; else myfile << " gnd";
				myfile << " b " << out << p2 << "\n";
				transistors += 1;

			}
			if (group[i][2]) {


				myfile << "\nxn" << transistors;
				if (i % 2 == 0) myfile << " vdd"; else myfile << " gnd";
				myfile << " b " << out << n2 << "\n";
				transistors += 1;
			}
			if (group[i][3]) {


				myfile << "\nxp" << transistors;
				if (i % 2 == 0) myfile << " vdd"; else myfile << " gnd";
				myfile << " a " << out << p2 << "\n";
				transistors += 1;
			}
			if (group[i][4]) {


				myfile << "\nxn" << transistors;
				if (i % 2 == 0) myfile << " vdd"; else myfile << " gnd";
				myfile << " a " << out << n2 << "\n";
				transistors += 1;
			}
			if (group[i][5]) {


				myfile << "\nxp" << transistors;
				if (i % 2 == 0) myfile << " vdd"; else myfile << " gnd";
				myfile << " a p" << connections << p2 << "\n";
				transistors += 1;

				myfile << "\nxp" << transistors;
				myfile << " p" << connections << " b " << out << p2 << "\n";
				transistors += 1;
				connections += 1;
			}
			if (group[i][6]) {


				myfile << "\nxp" << transistors;
				if (i % 2 == 0) myfile << " vdd"; else myfile << " gnd";
				myfile << " a p" << connections << p2 << "\n";
				transistors += 1;

				myfile << "\nxn" << transistors;
				myfile << " p" << connections << " b " << out << n2 << "\n";
				transistors += 1;
				connections += 1;
			}
			if (group[i][7]) {


				myfile << "\nxn" << transistors;
				if (i % 2 == 0) myfile << " vdd"; else myfile << " gnd";
				myfile << " a p" << connections << n2 << "\n";
				transistors += 1;

				myfile << "\nxp" << transistors;
				myfile << " p" << connections << " b " << out << p2 << "\n";
				transistors += 1;
				connections += 1;
			}
			if (group[i][8]) {


				myfile << "\nxn" << transistors;
				if (i % 2 == 0) myfile << " vdd"; else myfile << " gnd";
				myfile << " a p" << connections << n2 << "\n";
				transistors += 1;

				myfile << "\nxn" << transistors;
				myfile << " p" << connections << " b " << out << n2 << "\n";
				transistors += 1;
				connections += 1;
			}
			if (group[i][9]) {


				myfile << "\nxp" << transistors;
				if (i % 2 == 0) myfile << " vdd"; else myfile << " gnd";
				myfile << " b p" << connections << p2 << "\n";
				transistors += 1;

				myfile << "\nxp" << transistors;
				myfile << " p" << connections << " a " << out << p1 << "\n";
				transistors += 1;

				myfile << "\nxn" << transistors;
				myfile << " p" << connections << " a " << out << n1 << "\n";
				transistors += 1;
				connections += 1;

			}
			if (group[i][10]) {


				myfile << "\nxn" << transistors;
				if (i % 2 == 0) myfile << " vdd"; else myfile << " gnd";
				myfile << " b p" << connections << n2 << "\n";
				transistors += 1;

				myfile << "\nxp" << transistors;
				myfile << " p" << connections << " a p" << connections + 1 << p1 << "\n";
				transistors += 1;

				myfile << "\nxn" << transistors;
				myfile << " p" << connections << " a " << out << n1 << "\n";
				transistors += 1;
				connections += 1;
			}
			if (group[i][11]) {


				myfile << "\nxp" << transistors;
				if (i % 2 == 0) myfile << " vdd"; else myfile << " gnd";
				myfile << " a p" << connections << p2 << "\n";
				transistors += 1;

				myfile << "\nxp" << transistors;
				myfile << " p" << connections << " b " << out << p1 << "\n";
				transistors += 1;

				myfile << "\nxn" << transistors;
				myfile << " p" << connections << " b " << out << n1 << "\n";
				transistors += 1;
				connections += 1;
			}
			if (group[i][12]) {


				myfile << "\nxn" << transistors;
				if (i % 2 == 0) myfile << " vdd"; else myfile << " gnd";
				myfile << " a p" << connections << n2 << "\n";
				transistors += 1;

				myfile << "\nxp" << transistors;
				myfile << " p" << connections << " b " << out << p1 << "\n";
				transistors += 1;

				myfile << "\nxn" << transistors;
				myfile << " p" << connections << " b " << out << n1 << "\n";
				transistors += 1;
				connections += 1;
			}


			if (group[i][13]) {


				myfile << "\nxp" << transistors;
				if (i % 2 == 0) myfile << " vdd"; else myfile << " gnd";
				myfile << " b " << out << p1 << "\n";
				transistors += 1;

			}
			if (group[i][14]) {


				myfile << "\nxn" << transistors;
				if (i % 2 == 0) myfile << " vdd"; else myfile << " gnd";
				myfile << " b p" << connections << n2 << "\n";
				transistors += 1;

				myfile << "\nxp" << transistors;
				myfile << " p" << connections << " b " << out << p2 << "\n";
				transistors += 1;
				connections += 1;
			}
			if (group[i][15]) {


				myfile << "\nxn" << transistors;
				if (i % 2 == 0) myfile << " vdd"; else myfile << " gnd";
				myfile << " b " << out << n1 << "\n";
				transistors += 1;
			}
			if (group[i][16]) {


				myfile << "\nxp" << transistors;
				if (i % 2 == 0) myfile << " vdd"; else myfile << " gnd";
				myfile << " a " << out << p1 << "\n";
				transistors += 1;
			}
			if (group[i][17]) {


				myfile << "\nxn" << transistors;
				if (i % 2 == 0) myfile << " vdd"; else myfile << " gnd";
				myfile << " a p" << connections << n2 << "\n";
				transistors += 1;

				myfile << "\nxp" << transistors;
				myfile << " p" << connections << " a " << out << p2 << "\n";
				transistors += 1;
				connections += 1;
			}
			if (group[i][18]) {


				myfile << "\nxn" << transistors;
				if (i % 2 == 0) myfile << " vdd"; else myfile << " gnd";
				myfile << " a " << out << n1 << "\n";
				transistors += 1;
			}
			if (group[i][19]) {


				myfile << "\nxp" << transistors;
				if (i % 2 == 0) myfile << " vdd"; else myfile << " gnd";
				myfile << " a p" << connections << p2 << "\n";
				transistors += 1;

				myfile << "\nxp" << transistors;
				myfile << " p" << connections << " b " << out << p1 << "\n";
				transistors += 1;


			}
			if (group[i][20]) {


				myfile << "\nxn" << transistors;
				if (i % 2 == 0) myfile << " vdd"; else myfile << " gnd";
				myfile << " b p" << connections << n2 << "\n";
				transistors += 1;

				myfile << "\nxp" << transistors;
				myfile << " p" << connections << " b p" << connections + 1 << p2 << "\n";
				transistors += 1;
				connections += 1;

				myfile << "\nxp" << transistors;
				myfile << " p" << connections << " a " << out << p2 << "\n";
				transistors += 1;

			}
			if (group[i][21]) {


				myfile << "\nxn" << transistors;
				if (i % 2 == 0) myfile << " vdd"; else myfile << " gnd";
				myfile << " b p" << connections << n1 << "\n";
				transistors += 1;

				myfile << "\nxp" << transistors;
				myfile << " p" << connections << " a " << out << p2 << "\n";
				transistors += 1;


			}
			if (group[i][22]) {


				myfile << "\nxp" << transistors;
				if (i % 2 == 0) myfile << " vdd"; else myfile << " gnd";
				myfile << " a p" << connections << p1 << "\n";
				transistors += 1;

				myfile << "\nxp" << transistors;
				myfile << " p" << connections << " b " << out << p2 << "\n";
				transistors += 1;
				connections += 1;

			}
			if (group[i][23]) {


				myfile << "\nxn" << transistors;
				if (i % 2 == 0) myfile << " vdd"; else myfile << " gnd";
				myfile << " a p" << connections << n2 << "\n";
				transistors += 1;

				myfile << "\nxp" << transistors;
				myfile << " p" << connections << " a p" << connections + 1 << p2 << "\n";
				transistors += 1;
				connections += 1;

				myfile << "\nxp" << transistors;
				myfile << " p" << connections << " b out" << p2 << "\n";
				transistors += 1;
				connections += 1;
			}
			if (group[i][24]) {


				myfile << "\nxn" << transistors;
				if (i % 2 == 0) myfile << " vdd"; else myfile << " gnd";
				myfile << " a p" << connections << n1 << "\n";
				transistors += 1;

				myfile << "\nxp" << transistors;
				myfile << " p" << connections << " b " << out << p2 << "\n";
				transistors += 1;
				connections += 1;

			}
			if (group[i][25]) {


				myfile << "\nxn" << transistors;
				if (i % 2 == 0) myfile << " vdd"; else myfile << " gnd";
				myfile << " a p" << connections << n2 << "\n";
				transistors += 1;

				myfile << "\nxp" << transistors;
				myfile << " p" << connections << " b " << out << p1 << "\n";
				transistors += 1;
			}
			if (group[i][26]) {


				myfile << "\nxn" << transistors;
				if (i % 2 == 0) myfile << " vdd"; else myfile << " gnd";
				myfile << " b p" << connections << n2 << "\n";
				transistors += 1;

				myfile << "\nxp" << transistors;
				myfile << " p" << connections << " b p" << connections + 1 << p2 << "\n";
				transistors += 1;
				connections += 1;

				myfile << "\nxn" << transistors;
				myfile << " p" << connections << " a " << out << n2 << "\n";
				transistors += 1;
				connections += 1;
			}
			if (group[i][27]) {


				myfile << "\nxn" << transistors;
				if (i % 2 == 0) myfile << " vdd"; else myfile << " gnd";
				myfile << " b p" << connections << n1 << "\n";
				transistors += 1;

				myfile << "\nxn" << transistors;
				if (i % 2 == 0) myfile << " vdd"; else myfile << " gnd";
				myfile << " a " << out << n2 << "\n";
				transistors += 1;
			}
			if (group[i][28]) {


				myfile << "\nxp" << transistors;
				if (i % 2 == 0) myfile << " vdd"; else myfile << " gnd";
				myfile << " a p" << connections << p1 << "\n";
				transistors += 1;

				myfile << "\nxn" << transistors;
				if (i % 2 == 0) myfile << " vdd"; else myfile << " gnd";
				myfile << " b " << out << n2 << "\n";
				transistors += 1;

			}
			if (group[i][29]) {


				myfile << "\nxn" << transistors;
				if (i % 2 == 0) myfile << " vdd"; else myfile << " gnd";
				myfile << " a p" << connections << n2 << "\n";
				transistors += 1;

				myfile << "\nxp" << transistors;
				myfile << " p" << connections << " a p" << connections + 1 << p2 << "\n";
				transistors += 1;
				connections += 1;

				myfile << "\nxn" << transistors;
				myfile << " p" << connections << " b " << out << n2 << "\n";
				transistors += 1;
				connections += 1;
			}
			if (group[i][30]) {


				myfile << "\nxn" << transistors;
				if (i % 2 == 0) myfile << " vdd"; else myfile << " gnd";
				myfile << " a p" << connections << n1 << "\n";
				transistors += 1;

				myfile << "\nxn" << transistors;
				myfile << " p" << connections << " b " << out << n2 << "\n";
				transistors += 1;
				connections += 1;
			}
			if (group[i][31]) {


				myfile << "\nxp" << transistors;
				if (i % 2 == 0) myfile << " vdd"; else myfile << " gnd";
				myfile << " a p" << connections << p1 << "\n";
				transistors += 1;

				myfile << "\nxn" << transistors;
				myfile << " p" << connections << " b " << out << n1 << "\n";
				transistors += 1;

				myfile << "\nxp" << transistors;
				myfile << " p" << connections << " b " << out << p1 << "\n";
				transistors += 1;
				connections += 1;
			}
			if (group[i][32]) {


				myfile << "\nxp" << transistors;
				if (i % 2 == 0) myfile << " vdd"; else myfile << " gnd";
				myfile << " a p" << connections << p2 << "\n";
				transistors += 1;

				myfile << "\nxn" << transistors;
				myfile << " p" << connections << " a p" << connections + 1 << n2 << "\n";
				transistors += 1;
				connections += 1;



				myfile << "\nxn" << transistors;
				myfile << " p" << connections << " b " << out << n1 << "\n";
				transistors += 1;

				myfile << "\nxp" << transistors;
				myfile << " p" << connections << " b " << out << p1 << "\n";

				transistors += 1;
				connections += 1;
			}
			if (group[i][33]) {


				myfile << "\nxn" << transistors;
				if (i % 2 == 0) myfile << " vdd"; else myfile << " gnd";
				myfile << " a p" << connections << n1 << "\n";
				transistors += 1;

				myfile << "\nxn" << transistors;
				myfile << " p" << connections << " b " << out << n1 << "\n";
				transistors += 1;


				myfile << "\nxp" << transistors;
				myfile << " p" << connections << " b " << out << p1 << "\n";
				transistors += 1;
				connections += 1;
			}
			if (group[i][34]) {


				myfile << "\nxp" << transistors;
				if (i % 2 == 0) myfile << " vdd"; else myfile << " gnd";
				myfile << " b p" << connections << p1 << "\n";
				transistors += 1;

				myfile << "\nxn" << transistors;
				myfile << " p" << connections << " a " << out << n1 << "\n";
				transistors += 1;

				myfile << "\nxp" << transistors;
				myfile << " p" << connections << " a " << out << p1 << "\n";
				transistors += 1;
				connections += 1;
			}
			if (group[i][35]) {


				myfile << "\nxp" << transistors;
				if (i % 2 == 0) myfile << " vdd"; else myfile << " gnd";
				myfile << " b p" << connections << p2 << "\n";
				transistors += 1;

				myfile << "\nxn" << transistors;
				myfile << " p" << connections << " b p" << connections + 1 << n2 << "\n";
				transistors += 1;
				connections += 1;



				myfile << "\nxn" << transistors;
				myfile << " p" << connections << " a " << out << n1 << "\n";
				transistors += 1;

				myfile << "\nxp" << transistors;
				myfile << " p" << connections << " a " << out << p1 << "\n";

				transistors += 1;
				connections += 1;
			}
			if (group[i][36]) {


				myfile << "\nxn" << transistors;
				if (i % 2 == 0) myfile << " vdd"; else myfile << " gnd";
				myfile << " b p" << connections << n1 << "\n";
				transistors += 1;

				myfile << "\nxn" << transistors;
				myfile << " p" << connections << " a " << out << n1 << "\n";
				transistors += 1;

				myfile << "\nxp" << transistors;
				myfile << " p" << connections << " a " << out << p1 << "\n";
				transistors += 1;
				connections += 1;
			}
			if (group[i][37]) {


				myfile << "\nxp" << transistors;
				if (i % 2 == 0) myfile << " vdd"; else myfile << " gnd";
				myfile << " b p" << connections << p1 << "\n";
				transistors += 1;

				myfile << "\nxp" << transistors;
				myfile << " p" << connections << " a " << out << p1 << "\n";
				transistors += 1;
				connections += 1;
			}
			if (group[i][38]) {


				myfile << "\nxp" << transistors;
				if (i % 2 == 0) myfile << " vdd"; else myfile << " gnd";
				myfile << " b p" << connections << p1 << "\n";
				transistors += 1;

				myfile << "\nxn" << transistors;
				myfile << " p" << connections << " a p" << connections + 1 << n2 << "\n";
				transistors += 1;
				connections += 1;

				myfile << "\nxp" << transistors;
				myfile << " p" << connections << " a " << out << p2 << "\n";
				transistors += 1;
				connections += 1;
			}
			if (group[i][39]) {


				myfile << "\nxp" << transistors;
				if (i % 2 == 0) myfile << " vdd"; else myfile << " gnd";
				myfile << " b p" << connections << p1 << "\n";
				transistors += 1;

				myfile << "\nxn" << transistors;
				myfile << " p" << connections << " a " << out << n1 << "\n";
				transistors += 1;
				connections += 1;
			}
			if (group[i][40]) {


				myfile << "\nxp" << transistors;
				if (i % 2 == 0) myfile << " vdd"; else myfile << " gnd";
				myfile << " a p" << connections << p1 << "\n";
				transistors += 1;

				myfile << "\nxn" << transistors;
				myfile << " p" << connections << " b p" << connections + 1 << n2 << "\n";
				transistors += 1;
				connections += 1;

				myfile << "\nxp" << transistors;
				myfile << " p" << connections << " b " << out << p2 << "\n";
				transistors += 1;
				connections += 1;
			}
			if (group[i][41]) {


				myfile << "\nxp" << transistors;
				if (i % 2 == 0) myfile << " vdd"; else myfile << " gnd";
				myfile << " a p" << connections << p2 << "\n";
				transistors += 1;

				myfile << "\nxn" << transistors;
				myfile << " p" << connections << " a p" << connections + 1 << n2 << "\n";
				transistors += 1;
				connections += 1;

				myfile << "\nxn" << transistors;
				myfile << " p" << connections << " b p" << connections + 1 << n2 << "\n";
				transistors += 1;
				connections += 1;

				myfile << "\nxp" << transistors;
				myfile << " p" << connections << " b " << out << p2 << "\n";
				transistors += 1;
				connections += 1;


			}
			if (group[i][42]) {


				myfile << "\nxn" << transistors;
				if (i % 2 == 0) myfile << " vdd"; else myfile << " gnd";
				myfile << " a p" << connections << n1 << "\n";
				transistors += 1;

				myfile << "\nxn" << transistors;
				myfile << " p" << connections << " b p" << connections + 1 << n2 << "\n";
				transistors += 1;
				connections += 1;

				myfile << "\nxp" << transistors;
				myfile << " p" << connections << " b " << out << p2 << "\n";
				transistors += 1;
				connections += 1;
			}
			if (group[i][43]) {


				myfile << "\nxn" << transistors;
				if (i % 2 == 0) myfile << " vdd"; else myfile << " gnd";
				myfile << " b p" << connections << n1 << "\n";
				transistors += 1;

				myfile << "\nxp" << transistors;
				myfile << " p" << connections << " a " << out << p1 << "\n";
				transistors += 1;
				connections += 1;
			}

			if (group[i][44]) {


				myfile << "\nxn" << transistors;
				if (i % 2 == 0) myfile << " vdd"; else myfile << " gnd";
				myfile << " b p" << connections << n1 << "\n";
				transistors += 1;

				myfile << "\nxn" << transistors;
				myfile << " p" << connections << " a p" << connections + 1 << n2 << "\n";
				transistors += 1;
				connections += 1;

				myfile << "\nxp" << transistors;
				myfile << " p" << connections << " a " << out << p2 << "\n";
				transistors += 1;
				connections += 1;
			}

			if (group[i][45]) {


				myfile << "\nxn" << transistors;
				if (i % 2 == 0) myfile << " vdd"; else myfile << " gnd";
				myfile << " b p" << connections << n1 << "\n";
				transistors += 1;

				myfile << "\nxn" << transistors;
				myfile << " p" << connections << " a " << out << n1 << "\n";
				transistors += 1;
				connections += 1;
			}

		}
		myfile << "\n\n.end\n\n";

		myfile.close();

	}

	// thoughts and notes:
	// Group wrapping does not ensure transistor sharing between networks!
	// Are p-buffers and n-buffers useful? maybe for single middle values.
	// Any n-input 1-output functions can be done with this method, using n-dimensional rectangular grouping
	// ... but is this better than combining two (n-1)-input 1-output functions?
	// .. is it less optimal as n goes up?
	// change int transistors to ntype and ptype counters.. Or don't! Less confusing this way.
	// Think about higher functions. How are they made with 2i 1o functions?
	// How does function indexing relate to subfunctions and their connections?

	return 0;
}





