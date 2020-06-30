
using namespace std;
#include <iostream>;
#include <vector>;
#include <math.h>;
#include <fstream>
#include <string>

vector<char> truthtable;
vector<char> tempVect;
vector<vector<char>> networks; 

vector<char> upvddgnd;		//network[0][x]
vector<char> downvddgnd;	//network[1][x]
vector<char> uphalfvdd;		//network[2][x]
vector<char> downhalfvdd;	//network[3][x]


vector<vector<vector<string>>> circuit;	//network, group, series

vector<vector<char>> groups;
vector<char> mask;

int dimensions = -1;
int maskIndex = 0;
int transistors = 0;
bool foobarmode = false;



int dimensionLevel(int index, int dimension) {	//returns the level a specific dimension is for a given index (not its value) NOT ZERO INDEXED
	return ((index%int((pow(3, dimension)))) / int(pow(3, (dimension - 1))));
}

void maskRecurs(int n,int p1,int p2) { 
	//recursivly goes through all the dimensions an fills in the mask vector between the two opposing corner points
	for (int i = 0; i < 3; i++) {	
		if (n == 1) {
			maskIndex += 1;
		}
		if (!(i > dimensionLevel(p2, n)) && !(i < dimensionLevel(p1, n))) {	//"current point" not smaller than p1,  
			if (n > 1) {													//not bigger than p2 in the current dimension
				maskRecurs(n - 1, p1, p2);
			}
			else {
				mask[maskIndex -1] = '1'; 
			}
		} else {
			if (n > 1) maskIndex += int(pow(3,n-1));

		}
		
	}
}

void drawMask(int p1, int p2) {
	fill(mask.begin(), mask.end(), '0');
	maskIndex = 0;
	bool error = false;
	for (int i = 1; i < dimensions+1; i++) {
		if (dimensionLevel(p2,i) < dimensionLevel(p1,i)) {
			error = true;
		}
	}

	if (error) {
		//WRITE CODE WHICH CAN DO WRAPPING
		cout << "\nError: one of p2's dimensions is lower than p1's.\n"; // \n(this means either edge wrapping, or reduntant rectangle)\n(edge wrapping to be implemented, somehow...)";
	}
	else {
		maskRecurs(dimensions, p1, p2);
	}
}

int main() {



	while (!((dimensions < truthtable.max_size()) && (dimensions > 0))) {
		cout << "\nEnter the function arity(number of dimensions): ";
		cin >> dimensions;
	}


	

	for (int i = 0; i < pow(3, dimensions); i++) {
		truthtable.push_back('0');
		tempVect.push_back('0');
		networks.resize(4);
		networks[0].push_back('0');
		networks[1].push_back('0');
		networks[2].push_back('0');
		networks[3].push_back('0');
		mask.push_back('0');


		
		circuit.resize(4, vector<vector<string> >(dimensions * 10, vector<string>(dimensions))); //why here??


		groups.resize(int(pow(pow(3, dimensions), 1.64))); // this is a bit of a problem. for high number of dimensions it becomes massive.. 
														 //THIS IS A PROBLEM!! IT BECOMES A PROBLEM VERY QUICKLY.. 
		for (int j = 0; j < int(pow(pow(3, dimensions), 1.64)); j++) {	
			groups[j].push_back('0');
		}

	}
	

	// MAYBE MOVE SOME THINGS FROM HERE TO WHERE IT IS ACTUALLY BEING USED.
	// THAT WAY MAYBE IT IS EASIER TO GIVE IT THE PROPER SIZE




	/*
	//testing
	int p1 = 0;
	int p2 = 0;
	while (true) {            //////////////////////////// WHILE TRUE TEST LOOP
		cout << "\n========\np1: ";
		cin >> p1;
		
		cout << "\n========\np2: ";
		cin >> p2;

		drawMask(p1, p2);
		cout << "\n\n";
		//cout << "p2 = " << p2 << endl;
		for (int i = 0; i < truthtable.size(); i++) {
			if (i % 3 == 0) cout << "\n";
			if (i % 9 == 0) cout << "\n";
			if (i % 27 == 0) cout << "\n";
			cout << mask[i];

		}
		cout << "\n\n";

	}
	/////////////////////////////////////////////////
	*/
	

	for (int i = 0; i < pow(3,dimensions); i++) {
		cout << "Enter the truthtable output when ";
		for (int j = 1; j < dimensions + 1; j++) {
			cout << "i" << j << " = " << dimensionLevel(i, j) << " ";
		}
		cin >> truthtable[i];
	}

	for (int i = 0; i < truthtable.size(); i++) {
		
		if (truthtable[i] == 'x') {
			networks[0][i] = 'x';
			networks[1][i] = 'x';
			networks[2][i] = 'x';
			networks[3][i] = 'x';
		}
		if (truthtable[i] == '0') {
			networks[0][i] = '0';
			networks[1][i] = '1';
			networks[2][i] = '0';
			networks[3][i]= 'x';
		}
		if (truthtable[i] == '1') {
			networks[0][i] = '0';
			networks[1][i] = '0';
			networks[2][i] = '1';
			networks[3][i] = '1';
		}
		if (truthtable[i] == '2') {
			networks[0][i] = '1';
			networks[1][i] = '0';
			networks[2][i] = 'x';
			networks[3][i] = '0';
		}
	}


	fill(truthtable.begin(), truthtable.end(), '0');


	for (int n = 0; n < 4; n++) {
		cout << "\n\nNETWORK " << n << ": \n";
		for (int i = 0; i < truthtable.size(); i++) {
			if (i % 3 == 0) cout << "\n";
			if (i % 9 == 0) cout << "\n\n";
			cout << networks[n][i];
			
		}
		
	}



	int groupNr = 0;
	bool lessthan = false;

	for (int n = 0; n < 4; n++) { //for each of the four transistor networks
		cout << "\n\n";
		//system("pause");
		cout << "\n\n Network " << n << "...\n\n";
		groupNr = 0;
		for (int f = 0; f < truthtable.size(); f++) {
			fill(groups[f].begin(), groups[f].end(), '0');
		}
		for (int p1 = 0; p1 < truthtable.size(); p1++) { //for each point in the network which is 1 or x
			
			if ((networks[n][p1] == '1') || (networks[n][p1] == 'x')) {
				for (int p2 = p1; p2 < truthtable.size(); p2++){ //  for each point after the 1 or x                 p = 0 for warping (it's not implemented)
					lessthan = false;
					
					for (int j = 1; j < dimensions + 1; j++) {					// check if it's lower in any dimension (it would result in a 0-mask)
						if (dimensionLevel(p2, j) < dimensionLevel(p1, j)) {
							lessthan = true;
						}
					}
					
					if (!lessthan) {			// if it is a valid rectangle, compare it with the truthtable of the network
						
						drawMask(p1, p2);
						
						bool equalMask = true;
						for (int j = p1; j < p2 +1; j++) {		// for every point, see if a 1 in the mask is a 0 in the network truth table
							if (mask[j] == '1') {
								if (networks[n][j] == '0') {
									equalMask = false;
								}
							}
						}
						
						if (equalMask == true) {				// if there are no 0s compared to the mask

							bool written = false;
							bool covered = true;

							for (int g = 0; g < groupNr; g++) {				// check if a group would be covered by the next group, and overwrite it if it does 
								//NOTE: This can overwrite multiple groups, resulting in duplicate groups
								covered = true;
								for (int c = 0; c < p2; c++) { // is p2 fine?
									if ((groups[g][c] == '1') && (mask[c] == '0')) {
										covered = false;
									}
								}
								if (covered) {
									for (int j = p1; j < p2 + 1; j++) {
										//cout << "\ngroupNr: " << g  << " overwritten" << "\nj: " << j;
										groups[g][j] = mask[j];
									}
									written = true;
								}
							}
							
							if (!written) {

								fill(tempVect.begin(), tempVect.end(), '0');			// checks if the sum of the preexisting groups would cover the mask
								for (int g = 0; g < groupNr; g++) {
									for (int j = 0; j < truthtable.size(); j++) {
										if (groups[g][j] == '1') {
											tempVect[j] = '1';	
										}
									}
								}


								covered = true;
								for (int j = 0; j < truthtable.size(); j++) {
									if (mask[j] == '1') {
										if (tempVect[j] == '0') {
											covered = false;
										}
									}
								}
								if (!covered) {
									for (int j = p1; j < p2 + 1; j++) {
										//cout << "\ngroupNr: " << groupNr << "\nj: " << j;
										groups[groupNr][j] = mask[j];
									}
									groupNr += 1;
								}
							}	

						}
						
					}
				}
			}
		}

		bool duplicate = false;

		for (int g = groupNr - 1; g > 0; g--) {				// checks for duplicate groups
			for (int g2 = 0; g2 < g; g2++) {
				duplicate = true;
				for (int c = 0; c < truthtable.size(); c++) {
					if ((groups[g2][c] == '1') && (groups[g][c] == '0')) {
						duplicate = false;
					}
				}
			}

			if (duplicate) {
				for (int j = 0; j < truthtable.size(); j++) {
					groups[g][j] = '0';
				}

				//for () // shift all groups above this one down and subtract groupNr	maybe not important


			}

		}



		// REMOVE GROUPS WHICH ARE ONLY THERE BECAUSE OF x
		// EXAMPLE:
		// 010
		// x1x
		// 010
		// only needs ONE group!


		//for each group, see if the sum of the other groups would cover all the 1s (WITHOUT x)
		for (int i = 0; i < groupNr; i++) {
			fill(tempVect.begin(), tempVect.end(), '0');
			for (int j = 0; j < groupNr; j++) {
				if (i != j) {
					for (int k = 0; k < truthtable.size(); k++) {
						if (groups[j][k] == '1') {
							tempVect[k] = '1';

						}
					}

					
				}
			}

			bool covered = true;
			for (int k = 0; k < truthtable.size(); k++) {
				if ((networks[n][k] == '1') && (tempVect[k] != '1')) {
					covered = false;
				}
			}
			if (covered) {	// if the group is not needed, set it to 0
				for (int k = 0; k < truthtable.size(); k++) {
					groups[i][k] = '0'; 
				}
			}
		}




		for (int i = 0; i < groupNr; i++) {
			cout << "\n\ngroup " << i;
			for (int j = 0; j < truthtable.size(); j++) {
				if (j % 3 == 0) cout << "\n";
				if (j % 9 == 0) cout << "\n\n";
				cout << groups[i][j];
			}
		}


		fill(tempVect.begin(), tempVect.end(), '0');
		for (int j = 0; j < groupNr; j++) {
			
			for (int k = 0; k < truthtable.size(); k++) {
				if (groups[j][k] == '1') {
					tempVect[k] = '1';

				}
			}

		}


		// reconstructing the truthtable (if it had x's in it to begin with, it don't anymore!)
		for (int i = 0; i < truthtable.size(); i++) {
			if (tempVect[i] == '1') {
				if (n == 0) {
					truthtable[i] = '2';
				}
				else if (n == 1) {
					truthtable[i] = '0';
				}
				else if (n == 2) {
					truthtable[i] = '1';
				}
				//else if (n == 3) {
					// don't need this one
				//}
			}
		}

		


		

		// build the circuit
	
		for (int g = 0; g < groupNr; g++) {
			for (int d = 0; d < dimensions; d++) {

				bool cut = true;
				string transType = "111";
				

				for (int L = 0; L < 3; L++) {
					for (int i = 0; i < truthtable.size(); i++) {
						if (dimensionLevel(i, d+1) == L) {
							if (groups[g][i] != '0') {
								cut = false;
							}
						}
					}
					if (cut) {
						transType[L] = '0';
					}
					else cut = true;
				}
				cout << "\n\nGroup: " << g << "\nDimension: " << d << "\ntrans: " << transType;
				circuit[n][g][d] = transType;
				cout << "\ncircuit[n][g][d]: " << circuit[n][g][d];
				//system("pause");
			}
		}



		// for each 1 (OR x), draw every rectangle with it in the "top-left" corner. (maybe not every rectangle. can definitely be optimised)
		// store every rectangle with no 0s, in  groups[n][3^dimensions]
		// erase every stored rectangle which is entirely covered by a bigger stored rectangle (this is where optimisation for step 1 would be useful)
		// sort all rectangles in groups[][] by how many 1s they contain (NOT x!)
		// from the top, only keep the ones required to cover all 1s (not x)
		// erase the stored rectangles which are covered by a combination of bigger rectangles
		// for each group, go through each dimension and cut off the zeros to make a transistor path.
	}







	// cout STUFF 
	// find the function index, for N DIMENSIONS (??)
	//if this or that network, gnd or vdd
	//for groups
	//for each dimension
	//if so and so is 0, this transistor
	// if it's not finished, add a point
	// repeat until its finished
	// out or up/down
	//next group




	cout << "\n\n true circuit truthtable: \n";

	uint64_t function_index = 0;
	// The true circuit truthtable is reconstructed (with no x)

	
	for (int i = 0; i < truthtable.size(); i++) {
		if (i % 3 == 0) cout << "\n";
		if (i % 9 == 0) cout << "\n\n";
		if (i % 27 == 0) cout << "\n\n\n";
		cout << truthtable[i];

		// WILL OVERFLOW FOR n>3!!!!!!!!
		//3^(3^3) < 2^64
		//3^(3^4) > 2^64
		// USE HEPT NAMES INSTEAD!!!
		if (truthtable[i] == '1') function_index += uint64_t(pow(3, i));
		if (truthtable[i] == '2') function_index += 2 * uint64_t(pow(3, i));
	}



	cout << "\nfunction index: " << function_index;
	cout << "\n\n";


	cout << "\nCIRCUIT VECTOR:\n";
	for (int n = 0; n < 4; n++) {
		cout << "\nnetwork "<< n <<"\n";
		for (int g = 0; g < dimensions * 10; g++) {
			cout << "\ngroup " << g << endl;
			for (int d = 0; d < dimensions; d++) {
				cout << "dimension: " << d << endl;
				cout << circuit[n][g][d] << endl;
			}
		}
	}

	cout << "\n\n" << endl;
	


	/* TO OPTIMIZE THE CIRCUIT BY SHARING TRANSISTORS:
	you first find the letter which is the most common
	(a letter can only appear once per column)
	and you put that on top (like with A in the example)
	then you find the letter that's 2nd most common
	and you put that on the bottom
	and THEN amongst the ones with an A (or without A if they are more common), find the 3rd most common letter, and do another branching under A,
	then the same for above B
	repeat until all the letters are covered
	*/




	//system("pause");


	
	string filename = "f_";
	for (int i = 0; i < 5 - to_string(function_index).length(); i++) { filename += "0"; }
	filename += to_string(function_index);
	filename += ".sp";
	ofstream myfile;
	string path = "functions/";
	path += filename;
	myfile.open(path);


	//red = 0.783nm, covers one from the side
	//blue = 1.487nm, covers two from the side
	// p-type from left and top
	// n-type from right and bottom



	// SPECIFY TRANSISTOR MODEL AND PARAMETERS HERE (don't forget the sub input if there is one)
	string p0 = " gnd PCNFET Lch=Lg  Lgeff='Lgef' Lss=32e-9  Ldd=32e-9 \n+Kgate = 'Kox' Tox = 'Hox' Csub = 'Cb' Vfbp = 'Vfp' Dout = 0  Sout = 0  Pitch = 20e-9 tubes = 3  n2 = n  n1 = 13 "; //" ptype 1.018nm";
	string n0 = " gnd NCNFET Lch=Lg  Lgeff='Lgef' Lss=32e-9  Ldd=32e-9 \n+ Kgate = 'Kox' Tox = 'Hox' Csub = 'Cb' Vfbn = 'Vfn' Dout = 0  Sout = 0  Pitch = 20e-9 tubes = 3  n2 = n  n1 = 13 "; //" ntype 1.018nm";

	string n1 = " gnd NCNFET Lch=Lg  Lgeff='Lgef' Lss=32e-9  Ldd=32e-9 \n+ Kgate = 'Kox' Tox = 'Hox' Csub = 'Cb' Vfbn = 'Vfn' Dout = 0  Sout = 0  Pitch = 20e-9 tubes = 3  n2 = n  n1 = 10 "; //" ntype 0.783nm";
	string n2 = " gnd NCNFET Lch=Lg  Lgeff='Lgef' Lss=32e-9  Ldd=32e-9 \n+ Kgate = 'Kox' Tox = 'Hox' Csub = 'Cb' Vfbn = 'Vfn' Dout = 0  Sout = 0  Pitch = 20e-9 tubes = 3  n2 = n  n1 = 19 "; //" ntype 1.487nm";

	string p1 = " gnd PCNFET Lch=Lg  Lgeff='Lgef' Lss=32e-9  Ldd=32e-9 \n+Kgate = 'Kox' Tox = 'Hox' Csub = 'Cb' Vfbp = 'Vfp' Dout = 0  Sout = 0  Pitch = 20e-9 tubes = 3  n2 = n  n1 = 10  "; //" ptype 0.783nm";
	string p2 = " gnd PCNFET Lch=Lg  Lgeff='Lgef' Lss=32e-9  Ldd=32e-9 \n+Kgate = 'Kox' Tox = 'Hox' Csub = 'Cb' Vfbp = 'Vfp' Dout = 0  Sout = 0  Pitch = 20e-9 tubes = 3  n2 = n  n1 = 19  "; //" ptype 1.487nm";
	





	filename.erase(7, 3);
	myfile << ".subckt " << filename << " a a_p a_n b b_p b_n out vdd\n"; // make internal PTI and NTI? NO! multiple subcircuits might share! sum and carry for example!
	myfile << "\n\nxp0 up out out" << p0;
	myfile << "\nxn1 out out down" << n0<<"\n\n\n";
	int connections = 0;
	int transistors = 2;


	string connect1 = "foobar";
	string connect2 = "foobar";
	string out = "out";
	string vsource = "vdd";
	// PRINT
	for (int n = 0; n < 4; n++) {
		if (n == 0) {
			out = "out";
			vsource = "vdd";
		}
		if (n == 1) {
			out = "out";
			vsource = "gnd";
		}
		if (n == 2) {
			out = "up";
			vsource = "vdd";
		}
			
		if (n == 3) {
			out = "down";
			vsource = "gnd";
		}
		

		for (int g = 0; g < dimensions * 10; g++) {
			for (int d = 0; d < dimensions; d++) {
				if (!circuit[n][g][d].empty() && circuit[n][g][d] != "000") {


					if (d == 0) {
						connect1 = vsource;
						connect2 = 'p' + to_string(connections);
					}
					if (d == 1) {
						connect1 = 'p' + to_string(connections);
						connect2 = 'p' + to_string(connections+1);
					}
					if (d == 2) {
						connect1 = 'p' + to_string(connections);
						connect2 = out;
					}


					if (circuit[n][g][d].empty()) { // THIS ONLY REALLY WORKS IF THERE ARE NO 0-GROUPS
						connect1 = connections;
						connect2 = out;				// if the last group is a 0-group, this will never be outputted
					}
					connections += 1;


					if (n % 2 == 0) {
						if (circuit[n][g][d] == "100") {	// small ptype I
							myfile << "\nxp"<<transistors<<" "<<connect1 << "i"<<d << " " << connect2 << p1; 
							transistors += 1;
						}
						if (circuit[n][g][d] == "110") {	// big ptype I
							myfile << "\nxp" << transistors << " " << connect1 << "i" << d << " " << connect2 << p2;
							transistors += 1;
						}
						if (circuit[n][g][d] == "001") {	// big ptype I_N
							myfile << "\nxp" << transistors << " " << connect1 << "i" << d << "_n " << connect2 << p2;
							transistors += 1;
						}
						if (circuit[n][g][d] == "011") {	// big ptype I_P
							myfile << "\nxp" << transistors << " " << connect1 << "i" << d << "_p " << connect2 << p2;
							transistors += 1;
						}
					}
					else {
						if (circuit[n][g][d] == "100") {	// big ntype I_N
							myfile << "\nxn" << transistors << " " << connect1 << "i" << d << "_n " << connect2 << p2;
							transistors += 1;
						}
						if (circuit[n][g][d] == "110") {	// big ntype I_P
							myfile << "\nxn" << transistors << " " << connect1 << "i" << d << "_p " << connect2 << p2;
							transistors += 1;
						}
						if (circuit[n][g][d] == "001") {	// small ntype I
							myfile << "\nxn" << transistors << " " << connect1 << "i" << d << " " << connect2 << p1;
							transistors += 1;
						}
						if (circuit[n][g][d] == "011") {	// big ntype I
							myfile << "\nxn" << transistors << " " << connect1 << "i" << d << " " << connect2 << p2;
							transistors += 1;
						}
					}


					///// These two might be unnecessary if it's optimized anyway
					/*
					if (circuit[n][g][d] == "010") {

					}
					if (circuit[n][g][d] == "101") {

					}
					*/
					////




					//if d is 0, connect to top/bottom
					//if d is 1, use a point
					// connection +=1 when points are used
					// transistors +=1 for every transistor
					// if pull-up
					//  each value gives a different transistor (or transistors!)
					// if pull-down
					//  same but different transistors
				}
			}
		}
	}
	



	// THE FILE INDEX BECOMES TOO HIGH WHEN n>3!!
	// CIN FILENAME INSTEAD!!
	// no, hept
	// also, call by index



	//system("pause");
	return 0;
}


