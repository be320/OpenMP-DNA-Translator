#include <iostream>
#include <string.h>
#include <iterator>
#include <sstream>
#include <fstream>
#include <map>
#include <string>
#include <omp.h>
using namespace std;
//HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
//SetConsoleTextAttribute(hConsole, k);

void read_map(map<string, int> &m, ifstream &is){
    string key;
    int value;
    while ( is >> key >> value ) {
    m[key] = value;
    }
}

void print_map(map<string, int> m){
    map<string, int>::iterator itr;
    for (itr = m.begin(); itr != m.end(); ++itr) {
        cout << itr->first << '\t' << itr->second << '\n';
    }
}

int main(){
    map<string, int> codons;

    ifstream myfile;
    myfile.open("codon.txt");
    read_map(codons, myfile);
    myfile.close();

    myfile.open("InputSeq.dat.txt");
    string str;
    if (myfile) {
        ostringstream ss;
        ss << myfile.rdbuf(); // reading data
        str = ss.str();
    }
    str.erase(remove_if(str.begin(), str.end(), [](char c) { return !isalpha(c); }), str.end());

    string temp;

    omp_set_num_threads(50);

    double start = omp_get_wtime();


    //   Sequential Part

    //for (int i = 0; i < str.length(); i += 3) {
    //    temp = str.substr(i, 3);
    //    //cout << temp << endl;
    //    codons[temp]++;
    //}


#pragma omp parallel for schedule (dynamic) private(temp)
    for (int i = 0;i < str.length();i+=3) {
       // printf("thread [%d] \n", omp_get_thread_num());
        temp = str.substr(i, 3);
       #pragma omp critical 
        codons[temp]++;
    }

    double end = omp_get_wtime();

    printf("Time Consumed : %f  seconds\n",end-start);

    //print_map(codons);
}


