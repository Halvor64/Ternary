// classes example
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

class IO {
    int nr;
    vector<string> connections;
public:
    int getNr() { return nr; }
    void setNr(int i) { nr = i; }
};

class Connection {
    //hmmm...
};

class Subcircuit {
    string connections[4];    //interface connections i0, i1, i2, out
    //bool ap, an, bp, bn, cp, cn; //subcircuit interface
    bool inverters[9];
    string index;
    int arity;
public:
    void setConnection(int, string);
    void setInverters(int, bool);
    void setIndex(string indx) { index = indx; };
    void setArity(int arty) { arity = arty; }
    string getConnection(int i) { return connections[i]; }
    bool getInverter(int i) { return inverters[i]; }
    string getIndex() { return index; }
    int getArity() { return arity; }
};

void Subcircuit::setConnection(int i, string id) {
    connections[i] = id;     //i is the nr of the input, id is the id of the connection
}

void::Subcircuit::setInverters(int i, bool x) {
    inverters[i] = x;
}




///////////////////////////////// DATA
vector<vector<string>> connections = {
    {"in0", "in1", "", "out_ckt0"}  ,       //20K
    {"out_ckt0", "in2", "", "out0"}  ,      //20K
    {"in0", "in1", "", "out_ckt2"},         //K00
    {"out_ckt0", "in2", "", "out_ckt3"},    //K00
    {"out_ckt2", "out_ckt3", "", "out2"},   //ZKK
};

vector<vector<bool>> inv = {
    {true,true,false,true,true,false,false,false,false},
    {true,true,false,true,true,false,false,false,false},
    {false,true,false,false,true,false,false,false,false},
    {false,true,false,false,true,false,false,false,false},
    {false,true,false,false,true,false,false,false,false}
};


vector<string> index = {
    "20K", "20K", "K00", "K00", "ZKK"
};

vector<int> arity = { 2,2,2,2,2 };
///////////////////////////////// DATA



vector<Subcircuit> netlists;

void enterData() {
    for (int i = 0; i < connections.size(); i++) {

        netlists[i].setIndex(index[i]);
        netlists[i].setArity(arity[i]);
        // entering connection data
        for (int j = 0; j < connections[i].size(); j++) {
            netlists[i].setConnection(j, connections[i][j]);
        }

        // entering subcircuit interface data
        for (int j = 0; j < 9; j++) {
            netlists[i].setInverters(j, inv[i][j]);
        }
    }
}


void printData() {
    for (int i = 0; i < connections.size(); i++) {


        cout << "\nobject nr " << i << endl;
        cout << "subcircuit interface: \n";

        for (int j = 0; j < 9; j++) {
            cout << netlists[i].getInverter(j) << " ";
        }
        cout << endl;
        for (int j = 0; j < connections[i].size(); j++) {
            cout << "connection " << j << " " << netlists[i].getConnection(j) << endl;
        }

    }

}


int main() {

    IO input;
    input.setNr(3);
    IO output;
    output.setNr(2);

    //vector<Subcircuit> netlists;
    netlists.resize(connections.size());



    enterData();
    printData();



    ofstream myfile;
    //string path = "functions/";
    string filename = "circuit";
    string path = filename;
    path += ".sp";
    myfile.open(path);

    myfile << ".subckt " << filename;
    for (int i = 0; i < input.getNr(); i++) {
        myfile << " in" << i;
    }
    for (int i = 0; i < output.getNr(); i++) {
        myfile << " out" << i;
    }
    myfile << " vdd\n";

    vector<string> includedIndex;

    for (int i = 0; i < netlists.size(); i++) {
        if (find(includedIndex.begin(), includedIndex.end(), netlists[i].getIndex()) == includedIndex.end())   {

            myfile << ".include \"f_" << netlists[i].getIndex() << ".sp\"" << endl;
            includedIndex.push_back(netlists[i].getIndex());
        }
        
    }
    myfile << ".include \"nti.sp\" \n.include \"pti.sp\"\n\n";

    vector<string> usedInverters;
    int inverterCount = 0;
    for (int i = 0; i < netlists.size(); i++) {

        for (int j = 0; j < (netlists[i].getArity() * 3); j++) {
            if (netlists[i].getInverter(j)) {
                if (j % 3 == 1) {

                    string addInverter = connections[i][(j - 1) / 3] + "_p";
                    if (find(usedInverters.begin(), usedInverters.end(), addInverter) == usedInverters.end()) {
                        myfile << "xpti" << inverterCount << " " << connections[i][(j - 1) / 3] << " " <<
                            addInverter << " vdd pti" << endl;
                        inverterCount++;
                        usedInverters.push_back(addInverter);
                    }
                }
                else if (j % 3 == 2) {
                    string addInverter = connections[i][(j - 2) / 3] + "_n";
                    if (find(usedInverters.begin(), usedInverters.end(), addInverter) == usedInverters.end()) {
                        myfile << "xnti" << inverterCount << " " << connections[i][(j - 2) / 3] << " " <<
                            addInverter << " vdd nti" << endl;
                        inverterCount++;
                        usedInverters.push_back(addInverter);
                    }
                }
            }
        }

        myfile << "\nxckt" << i << " ";
        for (int j = 0; j < 4; j++) {
            if (j < 3) {
                if (netlists[i].getInverter(j * 3)) {
                    myfile << connections[i][j] << " ";
                }
                if (netlists[i].getInverter((j * 3) + 1)) {
                    myfile << connections[i][j] << "_p ";
                }
                if (netlists[i].getInverter((j * 3) + 2)) {
                    myfile << connections[i][j] << "_n ";
                }
            }
        }
        myfile << connections[i][3]<<" vdd " << "f_" << netlists[i].getIndex() << "\n\n";

    }





    myfile << "\n\n.ends\n\n";
    myfile.close();

    return 0;
}


