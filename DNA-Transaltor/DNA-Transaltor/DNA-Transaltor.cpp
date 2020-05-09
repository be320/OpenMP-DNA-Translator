#include <iostream>
#include <string.h>
#include <iterator>
#include <sstream>
#include <fstream>
#include <map>
using namespace std;


void read_map(map<string, string> &m, ifstream &is){
    string key, value;
    while ( is >> key >> value ) {
    m[key] = value;
    }
}

void print_map(map<string, string> m){
    map<string, string>::iterator itr;
    for (itr = m.begin(); itr != m.end(); ++itr) {
        cout << itr->first << '\t' << itr->second << '\n';
    }
}

int main(){
    map<string, string> codons;

    ifstream myfile;
    myfile.open("codon.txt");
    read_map(codons, myfile);
    print_map(codons);
}


