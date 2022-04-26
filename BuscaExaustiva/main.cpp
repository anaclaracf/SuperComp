#include<iostream>
#include<vector>
#include<algorithm>
#include <cmath>
#include <tuple>
#include <fstream>
#include <bits/stdc++.h>

using namespace std;

void printSubsequence(string input, string output){

    if (input.empty()) {
        cout << output << endl;
        return;
    }
 
    printSubsequence(input.substr(1), output + input[0]);
    printSubsequence(input.substr(1), output);
}

int main(){

    int n, m;
    string seqA, seqB;
    string output = "";

    cin >> n >> m;
    cin >> seqA >> seqB;
    printSubsequence(seqA, output);

    return 0;
}