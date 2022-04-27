#include<iostream>
#include<vector>
#include<algorithm>
#include <cmath>
#include <tuple>
#include <fstream>
#include <bits/stdc++.h>

using namespace std;
vector<string> sub_A, sub_B;
typedef vector<vector<int>> matrix;

void genSubSeqA(string input, string output){

    if (input.empty()) {
        if(output.empty()){
            return;
        }
        sub_A.push_back(output);
        return;
    }
 
    genSubSeqA(input.substr(1), output + input[0]);
    genSubSeqA(input.substr(1), output);
}

void genSubSeqB(string input, string output){

    if (input.empty()) {
        if(output.empty()){
            return;
        }
        sub_B.push_back(output);
        return;
    }
 
    genSubSeqB(input.substr(1), output + input[0]);
    genSubSeqB(input.substr(1), output);
}

int calculate_score(char a, char b){
    if(a == b){
        return 2;
    }else{
        return -1;
    }
}

matrix max_score(matrix H, string first_seq, string second_seq, int n, int m, int w){
    int diagonal, deletion, insertion;
    string seq_max;

    for (int i = 1; i <= n; i++){
        for (int j = 1; j <= m; j++){
            w = calculate_score(first_seq[i], second_seq[j]);

            diagonal = H[i-1][j-1] + w;
            deletion = H[i-1][j] - 1;
            insertion = H[i][j-1] - 1;

            H[i][j] = max({0, diagonal, deletion, insertion});
            // cout << H[i][j] << endl;
        }
    }



    return H;
}


int main(){

    int n, m;
    string seqA, seqB;
    string outputA = "";
    string outputB = "";
    int w = 0;
    int max = 0;
    string seqA_utilizada, seqB_utilizada;

    cin >> n >> m;
    cin >> seqA >> seqB;

    matrix H;
    H.resize(n+1);
    for(int e=0; e<=n; e++){
        H[e].resize(m+1);
    }

    //  Gerar todas as subsequencias a´ e b´ não-nulas de a e b
    genSubSeqA(seqA, outputA);
    genSubSeqB(seqB, outputB);

    
    // gera os possiveis pares entre as subsequencias
    for (auto&& e1 : sub_A) {
        for (auto&& e2 : sub_B) {
            cout << e1 << " , " << e2 << endl;

            int tamanho_e1 = e1.size();
            int tamanho_e2 = e2.size();

            H = max_score(H, "-"+e1, "-"+e2, tamanho_e1, tamanho_e2, w);
 
            // descobrindo os maiores scores
            for (int i = 1; i <= tamanho_e1; i++){
                for (int j = 1; j <= tamanho_e2; j++){
                    if(H[i][j] > max){
                        max = H[i][j];
                        seqA_utilizada = e1;
                        seqB_utilizada = e2;

                    }
                }
            }
        }
    }

    cout << max << endl;
    cout << seqA_utilizada << endl;
    cout << seqB_utilizada << endl;

    

   
    return 0;
}