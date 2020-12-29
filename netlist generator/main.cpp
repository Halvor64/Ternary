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
    bool inverters[6];
    string index;
    int arity;
public:
    void setConnection(int, string);
    void setInverters(int, bool);
    void setIndex(string indx) { index = indx; };
    void setArity(int arty) { arity = arty; }
    string getConnection(int i) { return connections[i]; }
    bool getInverter(int i) {return inverters[i]; }
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
    {"in0", "in1", "", "out_ckt0"}  ,    //sum 2 inputs
    {"out_ckt0", "in2", "", "out0"},    //sum 2 inputs
    {"in0", "in1", "in2", "out1"}, //carry 3 inputs
};

vector<vector<bool>> inv = {
    {true,true,true,true,true,true,false,false,false},
    {true,true,true,true,true,true,false,false,false},
    {true,true,true,true,true,true,true,true,true}

};

vector<string> index = {
    "7PB", "7PB", "XRDRDCDC9"
};

vector<int> arity = { 2,2,3 };
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
        for (int j = 0; j < 6; j++) {
            netlists[i].setInverters(j, inv[i][j]);
        }
    }
}


void printData() {
    for (int i = 0; i < connections.size(); i++) {


        cout << "\nobject nr " << i << endl;
        cout << "subcircuit interface: \n";

        for (int j = 0; j < 6; j++) {
            cout << netlists[i].getInverter(j);
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

    for (int i = 0; i < netlists.size(); i++) {
        myfile << ".include \"f_" << netlists[i].getIndex() <<".sp\"" << endl;
    }
    myfile << ".include \"nti.sp\" \n.include \"pti.sp\"\n\n";

    vector<string> usedInverters;

    for (int i = 0; i < netlists.size(); i++) {
        
        for (int j = 0; j < (netlists[i].getArity() * 2); j++) {
            if (netlists[i].getInverter(j)) {
                if (j % 2 == 0) {

                    string addInverter = connections[i][j / 2] + "_p";
                    if (!(find(usedInverters.begin(), usedInverters.end(), addInverter) != usedInverters.end())) {
                        myfile << "xpti " << connections[i][j / 2] << " " <<
                            addInverter << " vdd pti" << endl;
                        usedInverters.push_back(addInverter);
                    }
                }
                else {
                    string addInverter = connections[i][(j - 1) / 2] + "_n";
                    if (!(find(usedInverters.begin(), usedInverters.end(), addInverter) != usedInverters.end())) {
                        myfile << "xnti " << connections[i][(j - 1) / 2] << " " <<
                            addInverter << " vdd nti" << endl;
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
                if (netlists[i].getInverter(j * 3 + 1)) {
                    myfile << connections[i][j] << "_p ";
                }
                if (netlists[i].getInverter(j * 3 + 2)) {
                    myfile << connections[i][j] << "_n ";
                }
            }
        }
        myfile << "vdd "<< "f_" << netlists[i].getIndex() <<"\n\n";

    }





    myfile << "\n\n.ends\n\n";
    myfile.close();

    return 0;
}































