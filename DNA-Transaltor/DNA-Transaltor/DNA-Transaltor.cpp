#include <iostream>
#include <string.h>
#include <iterator>
#include <sstream>
#include <fstream>
#include <map>
#include <string>
#include <numeric>
#include <iomanip>
#include <omp.h>
using namespace std;

void read_map(map<string, int>& m1, map<string, string>& m2, map<string, int>& m3, ifstream& is1, ifstream& is2, ifstream& is3);
void print_map(map<string, int> m1, map<string, int> m2);
void sequential(string str, map<string, int> &codons, map<string, string> &amino, map<string, int> &result);
void loopParallelism(int nThreads, string str, map<string, int>& codons, map<string, string>& amino, map<string, int>& result);
string readFile(map<string, int>& codons, map<string, string>& amino, map<string, int>& result);
void sectionParallelism(int nThreads, string str, map<string, int>& codons, map<string, string>& amino, map<string, int>&result);

int main(){
    map<string, int> codons;
    map<string, string> amino;
    map<string, int> result;
    string str = readFile(codons, amino, result);
    int choice;
    int nthreads;

    cout << "Enter Method: \n Sequential : 1\n LoopLevel Parallism : 2\n SectionLevel Parallism : 3" << endl;
    cin >> choice;
    switch (choice) {
    case 1:
        sequential(str, codons, amino, result);
        break;

    case 2:
        cout << "enter number of threads:" << endl;
        cin >> nthreads;
        loopParallelism(nthreads, str, codons, amino, result);
        break;

    case 3:
        cout << "enter number of threads:" << endl;
        cin >> nthreads;
        sectionParallelism(nthreads, str, codons, amino, result);
        break;

    default:
        break;
    }
}

void read_map(map<string, int>& m1, map<string, string>& m2, map<string, int>& m3, ifstream& is1, ifstream& is2, ifstream& is3) {
    string key, value2;
    int value;
    for (int i = 0; i < 64; i++) {
        is1 >> key >> value;
        m1[key] = value;
        is2 >> key >> value2;
        m2[key] = value2;
    }
}

void print_map(map<string, int> m1, map<string, int> m2) {
    map<string, int>::iterator itr1;
    map<string, int>::iterator itr2;
    const size_t sum = accumulate(begin(m1), end(m1), 0, [](const size_t previous, const pair<const string, size_t>& p)
        { return previous + p.second; });
    const size_t sum1 = accumulate(begin(m2), end(m2), 0, [](const size_t previous, const pair<const string, size_t>& p)
        { return previous + p.second; });

    cout << "Codons \t" << "Number\t" << "Percentage\n";
    for (itr1 = m1.begin(); itr1 != m1.end(); ++itr1)
        cout << itr1->first << '\t' << itr1->second << '\t'<< fixed << setprecision(3) << (float(itr1->second) / float(sum)) * 100 << '%' << '\n';
    cout << "\nAmino Acids \t" << "Number\t" << "Percentage\n";
    for (itr2 = m2.begin(); itr2 != m2.end(); ++itr2)
        cout << itr2->first << "\t\t" << itr2->second << '\t' << fixed << setprecision(3) << (float(itr2->second) / float(sum1)) * 100 << '%' << '\n';
}

void sequential(string str, map<string, int> &codons, map<string, string> &amino, map<string, int> &result) {
    double start = omp_get_wtime();
    string temp;
    for (int i = 0; i < str.length(); i += 3) {
        temp = str.substr(i, 3);
        codons[temp]++;
        result[amino[temp]]++;
    }
    double end = omp_get_wtime();
    print_map(codons, result);
    printf("Time Consumed : %f  seconds\n", end - start);
}

void loopParallelism(int nThreads, string str, map<string, int>&codons, map<string, string>& amino, map<string, int>& result) {
    string temp;
    omp_set_num_threads(nThreads);
    double start = omp_get_wtime();
#pragma omp parallel for schedule (dynamic) private(temp)
    for (int i = 0;i < str.length();i += 3) {
        temp = str.substr(i, 3);
        codons[temp]++;
        result[amino[temp]]++;
    }
    double end = omp_get_wtime();
    print_map(codons, result);
    printf("Time Consumed : %f  seconds\n", end - start);
}

string readFile(map<string, int>&codons, map<string, string>&amino, map<string, int>&result) {
    ifstream myfile1, myfile2, myfile3;
    myfile1.open("codon.txt");
    myfile2.open("aminoAcid.txt");
    myfile3.open("result.txt");
    read_map(codons, amino, result, myfile1, myfile2, myfile3);
    myfile1.close();
    myfile2.close();
    myfile3.close();
    myfile1.open("InputSeq.dat.txt");
    string str;
    if (myfile1) {
        ostringstream ss;
        ss << myfile1.rdbuf(); // reading data
        str = ss.str();
    }
    str.erase(remove_if(str.begin(), str.end(), [](char c) { return !isalpha(c); }), str.end());
    return str;
}

void sectionParallelism(int nThreads, string str, map<string, int>&codons, map<string, string>&amino, map<string, int>&result) {
    string temp;
    int id, i;
    string str1;
    omp_set_num_threads(nThreads);
    double start = omp_get_wtime();
#pragma omp parallel shared(str,counter) 
    {

#pragma omp sections private(i,id,temp,str1)
        {
#pragma omp section
            {
                str1 = str.substr(0, 5112);
                id = omp_get_thread_num();
                for (i = 0; i < str1.length(); i += 3)
                {
                    temp = str1.substr(i, 3);
                    codons[temp]++;
                    result[amino[temp]]++;
                }
            }

#pragma omp section
            {
                str1 = str.substr(5112, 5112);
                id = omp_get_thread_num();
                for (i = 0; i < str1.length(); i += 3)
                {
                    temp = str1.substr(i, 3);
                    codons[temp]++;
                    result[amino[temp]]++;
                }
            }

#pragma omp section
            {
                str1 = str.substr(10224, 5112);
                id = omp_get_thread_num();
                for (i = 0; i < str1.length(); i += 3)
                {
                    temp = str1.substr(i, 3);
                    codons[temp]++;
                    result[amino[temp]]++;
                }
            }
#pragma omp section
            {
                str1 = str.substr(15336, 5112);
                id = omp_get_thread_num();
                for (i = 0; i < str1.length(); i += 3)
                {
                    temp = str1.substr(i, 3);
                    codons[temp]++;
                    result[amino[temp]]++;
                }
            }

#pragma omp section
            {
                str1 = str.substr(20448, 5112);
                id = omp_get_thread_num();
                for (i = 0; i < str1.length(); i += 3)
                {
                    temp = str1.substr(i, 3);
                    codons[temp]++;
                    result[amino[temp]]++;
                }
            }

#pragma omp section
            {
                str1 = str.substr(25560, 5112);
                id = omp_get_thread_num();
                for (i = 0; i < str1.length(); i += 3)
                {
                    temp = str1.substr(i, 3);
                    codons[temp]++;
                    result[amino[temp]]++;
                }
            }
#pragma omp section
            {
                str1 = str.substr(30672, 5112);
                id = omp_get_thread_num();
                for (i = 0; i < str1.length(); i += 3)
                {
                    temp = str1.substr(i, 3);
                    codons[temp]++;
                    result[amino[temp]]++;
                }
            }
#pragma omp section
            {
                str1 = str.substr(35784, 5112);
                id = omp_get_thread_num();
                for (i = 0; i < str1.length(); i += 3)
                {
                    temp = str1.substr(i, 3);
                    codons[temp]++;
                    result[amino[temp]]++;
                }
            }
#pragma omp section
            {
                str1 = str.substr(40896, 5112);
                id = omp_get_thread_num();
                for (i = 0; i < str1.length(); i += 3)
                {
                    temp = str1.substr(i, 3);
                    codons[temp]++;
                    result[amino[temp]]++;
                }
            }
#pragma omp section
            {
                str1 = str.substr(46008, 5112);
                id = omp_get_thread_num();
                for (i = 0; i < str1.length(); i += 3)
                {
                    temp = str1.substr(i, 3);
                    codons[temp]++;
                    result[amino[temp]]++;
                }
            }
#pragma omp section
            {
                str1 = str.substr(51120, 5112);
                id = omp_get_thread_num();
                for (i = 0; i < str1.length(); i += 3)
                {
                    temp = str1.substr(i, 3);
                    codons[temp]++;
                    result[amino[temp]]++;
                }
            }
#pragma omp section
            {
                str1 = str.substr(56232, 5112);
                id = omp_get_thread_num();
                for (i = 0; i < str1.length(); i += 3)
                {
                    temp = str1.substr(i, 3);
                    codons[temp]++;
                    result[amino[temp]]++;
                }
            }
#pragma omp section
            {
                str1 = str.substr(61344, 5112);
                id = omp_get_thread_num();
                for (i = 0; i < str1.length(); i += 3)
                {
                    temp = str1.substr(i, 3);
                    codons[temp]++;
                    result[amino[temp]]++;
                }
            }
#pragma omp section
            {
                str1 = str.substr(66456, 5112);
                id = omp_get_thread_num();
                for (i = 0; i < str1.length(); i += 3){
                    temp = str1.substr(i, 3);
                    codons[temp]++;
                    result[amino[temp]]++;
                }
            }
#pragma omp section
            {
                str1 = str.substr(71568, 5112);
                id = omp_get_thread_num();
                for (i = 0; i < str1.length(); i += 3){
                    temp = str1.substr(i, 3);
                    codons[temp]++;
                    result[amino[temp]]++;
                }
            }
#pragma omp section
            {
                str1 = str.substr(76680, 5106);
                id = omp_get_thread_num();
                for (i = 0; i < str1.length(); i += 3){
                    temp = str1.substr(i, 3);
                    codons[temp]++;
                    result[amino[temp]]++;
                }
            }
        }
    }
    double end = omp_get_wtime();
    print_map(codons, result);
    printf("Time Consumed : %f  seconds\n", end - start);
}


