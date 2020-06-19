
using namespace std;
#include <iostream>;
#include <vector>;
#include <math.h>;

vector<char> truthtable;
vector<vector<char>> networks; 

vector<char> upvddgnd;		//network[0][x]
vector<char> downvddgnd;	//network[1][x]
vector<char> uphalfvdd;		//network[2][x]
vector<char> downhalfvdd;	//network[3][x]



vector<vector<char>> groups;
vector<char> mask;

int dimensions = -1;
int maskIndex = 0;

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
		networks.resize(4);
		networks[0].push_back('0');
		networks[1].push_back('0');
		networks[2].push_back('0');
		networks[3].push_back('0');
		mask.push_back('0');





		groups.resize(int(pow(pow(3, dimensions), 1.64))); // this is a bit of a problem. for high number of dimensions it becomes massive.. 
														 //THIS IS A PROBLEM!! IT BECOMES A PROBLEM VERY QUICKLY.. 
		for (int j = 0; j < int(pow(pow(3, dimensions), 1.64)); j++) {	// is a vector of vectors fine? each subvector still has the maxsize of a normal vector?
			groups[j].push_back('0');
		}

	}
	

	




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
		system("pause");
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

								fill(truthtable.begin(), truthtable.end(), '0');			// checks if the sum of the preexisting groups would cover the mask
								for (int g = 0; g < groupNr; g++) {
									for (int j = 0; j < truthtable.size(); j++) {
										if (groups[g][j] == '1') {
											truthtable[j] = '1';	// TRUTHTABLE IS REPURPOSED 
										}
									}
								}


								covered = true;
								for (int j = 0; j < truthtable.size(); j++) {
									if (mask[j] == '1') {
										if (truthtable[j] == '0') {
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
			fill(truthtable.begin(), truthtable.end(), '0');
			for (int j = 0; j < groupNr; j++) {
				if (i != j) {
					for (int k = 0; k < truthtable.size(); k++) {
						if (groups[j][k] == '1') {
							truthtable[k] = '1';

						}
					}

					
				}
			}

			bool covered = true;
			for (int k = 0; k < truthtable.size(); k++) {
				if ((networks[n][k] == '1') && (truthtable[k] != '1')) {
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

		//system("pause");

		// for each 1 (OR x), draw every rectangle with it in the "top-left" corner. (maybe not every rectangle. can definitely be optimised)
		// store every rectangle with no 0s, in  groups[n][3^dimensions]
		// erase every stored rectangle which is entirely covered by a bigger stored rectangle (this is where optimisation for step 1 would be useful)
		// sort all rectangles in groups[][] by how many 1s they contain (NOT x!)
		// from the top, only keep the ones required to cover all 1s (not x)
		// erase the stored rectangles which are covered by a combination of bigger rectangles
		// for each group, go through each dimension and cut off the zeros to make a transistor path.
	}



	system("pause");
	return 0;
}


