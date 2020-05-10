#include <iostream>
#include <string.h>
#include <iterator>
#include <sstream>
#include <fstream>
#include <map>
#include <string>
#include <omp.h>
using namespace std;
map<string, int> codons;

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

void sequential (string str){
    double start = omp_get_wtime();
    string temp;
    for (int i = 0; i < str.length(); i += 3) {
        temp = str.substr(i, 3);
        codons[temp]++;
    }
    double end = omp_get_wtime();
    print_map(codons);
    printf("Time Consumed : %f  seconds\n", end - start);
}

void loopParallelism(int nThreads, string str) {
    string temp;
    omp_set_num_threads(nThreads);
    double start = omp_get_wtime();
    #pragma omp parallel for schedule (dynamic) private(temp)
    for (int i = 0;i < str.length();i+=3) {
       // printf("thread [%d] \n", omp_get_thread_num());
        temp = str.substr(i, 3);
       #pragma omp critical 
        codons[temp]++;
    }
    double end = omp_get_wtime();
    print_map(codons);
    printf("Time Consumed : %f  seconds\n", end - start);
   
}

string readFile() {

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

    return str;
}

void sectionParallelism(int nThreads, string str) {
    string temp;
    int id, i;
    string str1;
    int counter = 0;
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
                }
                printf("Section %d executed by thread number %d \n", ++counter, id);
            }

#pragma omp section
            {
                str1 = str.substr(5112, 5112);
                id = omp_get_thread_num();
                for (i = 0; i < str1.length(); i += 3)
                {
                    temp = str1.substr(i, 3);
                    codons[temp]++;
                }
                printf("Section %d executed by thread number %d \n", ++counter, id);
            }

#pragma omp section
            {
                str1 = str.substr(10224, 5112);
                id = omp_get_thread_num();
                for (i = 0; i < str1.length(); i += 3)
                {
                    temp = str1.substr(i, 3);
                    codons[temp]++;
                }
                printf("Section %d executed by thread number %d \n", ++counter, id);
            }
#pragma omp section
            {
                str1 = str.substr(15336, 5112);
                id = omp_get_thread_num();
                for (i = 0; i < str1.length(); i += 3)
                {
                    temp = str1.substr(i, 3);
                    codons[temp]++;
                }
                printf("Section %d executed by thread number %d \n", ++counter, id);
            }

#pragma omp section
            {
                str1 = str.substr(20448, 5112);
                id = omp_get_thread_num();
                for (i = 0; i < str1.length(); i += 3)
                {
                    temp = str1.substr(i, 3);
                    codons[temp]++;
                }
                printf("Section %d executed by thread number %d \n", ++counter, id);
            }

#pragma omp section
            {
                str1 = str.substr(25560, 5112);
                id = omp_get_thread_num();
                for (i = 0; i < str1.length(); i += 3)
                {
                    temp = str1.substr(i, 3);
                    codons[temp]++;
                }
                printf("Section %d executed by thread number %d \n", ++counter, id);
            }
#pragma omp section
            {
                str1 = str.substr(30672, 5112);
                id = omp_get_thread_num();
                for (i = 0; i < str1.length(); i += 3)
                {
                    temp = str1.substr(i, 3);
                    codons[temp]++;
                }
                printf("Section %d executed by thread number %d \n", ++counter, id);
            }
#pragma omp section
            {
                str1 = str.substr(35784, 5112);
                id = omp_get_thread_num();
                for (i = 0; i < str1.length(); i += 3)
                {
                    temp = str1.substr(i, 3);
                    codons[temp]++;
                }
                printf("Section %d executed by thread number %d \n", ++counter, id);
            }
#pragma omp section
            {
                str1 = str.substr(40896, 5112);
                id = omp_get_thread_num();
                for (i = 0; i < str1.length(); i += 3)
                {
                    temp = str1.substr(i, 3);
                    codons[temp]++;
                }
                printf("Section %d executed by thread number %d \n", ++counter, id);
            }
#pragma omp section
            {
                str1 = str.substr(46008, 5112);
                id = omp_get_thread_num();
                for (i = 0; i < str1.length(); i += 3)
                {
                    temp = str1.substr(i, 3);
                    codons[temp]++;
                }
                printf("Section %d executed by thread number %d \n", ++counter, id);

            }
#pragma omp section
            {
                str1 = str.substr(51120, 5112);
                id = omp_get_thread_num();
                for (i = 0; i < str1.length(); i += 3)
                {
                    temp = str1.substr(i, 3);
                    codons[temp]++;
                }
                printf("Section %d executed by thread number %d \n", ++counter, id);
            }
#pragma omp section
            {
                str1 = str.substr(56232, 5112);
                id = omp_get_thread_num();
                for (i = 0; i < str1.length(); i += 3)
                {
                    temp = str1.substr(i, 3);
                    codons[temp]++;
                }
                printf("Section %d executed by thread number %d \n", ++counter, id);
            }
#pragma omp section
            {
                str1 = str.substr(61344, 5112);
                id = omp_get_thread_num();
                for (i = 0; i < str1.length(); i += 3)
                {
                    temp = str1.substr(i, 3);
                    codons[temp]++;
                }
                printf("Section %d executed by thread number %d \n", ++counter, id);
            }
#pragma omp section
            {
                str1 = str.substr(66456, 5112);
                id = omp_get_thread_num();
                for (i = 0; i < str1.length(); i += 3)
                {
                    temp = str1.substr(i, 3);
                    codons[temp]++;
                }
                printf("Section %d executed by thread number %d \n", ++counter, id);
            }
#pragma omp section
            {
                str1 = str.substr(71568, 5112);
                id = omp_get_thread_num();
                for (i = 0; i < str1.length(); i += 3)
                {
                    temp = str1.substr(i, 3);
                    codons[temp]++;
                }
                printf("Section %d executed by thread number %d \n", ++counter, id);
            }
#pragma omp section
            {
                str1 = str.substr(76680, 5106);
                id = omp_get_thread_num();
                for (i = 0; i < str1.length(); i += 3)
                {
                    temp = str1.substr(i, 3);
                    codons[temp]++;
                }
                printf("Section %d executed by thread number %d \n", ++counter, id);
            }

        }

    }
    double end = omp_get_wtime();
    print_map(codons);
    printf("Time Consumed : %f  seconds\n", end - start);
}

int main(){
    string str = readFile();
    int choice;
    int nthreads;
    cout << "Enter Method: \n Sequential : 1\n LoopLevel Parallism : 2\n SectionLevel Parallism : 3" << endl;
    cin >> choice;
    switch (choice) {
        case 1:
             sequential(str);
             break;

        case 2:
            cout << "enter number of threads:" << endl;
            cin >> nthreads;
            loopParallelism(nthreads,str);
            break;

        case 3:
            cout << "enter number of threads:" << endl;
            cin >> nthreads;
            sectionParallelism(nthreads,str);
            break;

        default:
            break;
    }
}


