#include <iostream>
#include <string.h>
#include <iterator> 
#include <map>
using namespace std;

map<string, string> codones;

int main()
{
    codones.insert(pair<string, string>("TTT","Phe"));
    codones.insert(pair<string, string>("TTC", "Phe"));
    codones.insert(pair<string, string>("TTA", "Leu"));
    codones.insert(pair<string, string>("TTG", "Leu"));
    codones.insert(pair<string, string>("TCT", "Ser"));
    codones.insert(pair<string, string>("TCC", "Ser"));
    codones.insert(pair<string, string>("TCA", "Ser"));
    codones.insert(pair<string, string>("TCG", "Ser"));
    string y;
    cin >> y;
    string x = codones.find(y);
    cout <<x;
}


