#include<iostream>
#include<vector>
#include<algorithm>
#include <cmath>
#include <tuple>
#include <fstream>
#include <bits/stdc++.h>

using namespace std;
typedef vector<vector<int>> matrix;

// funcao para calcular o sw
matrix max_score(matrix H, string first_seq, string second_seq, int n, int m, int w){
    int diagonal, deletion, insertion;
    string seq_max;

    for (int i = 1; i <= n; i++){
        for (int j = 1; j <= m; j++){
            w = (first_seq[i] == second_seq[j] ? 2 : -1);

            diagonal = H[i-1][j-1] + w;
            deletion = H[i-1][j] - 1;
            insertion = H[i][j-1] - 1;

            H[i][j] = max({0, diagonal, deletion, insertion});
            // cout << H[i][j] << endl;
        }
    }
    return H;
}

// funcao para gerar as sub sequencias
vector<string> genSub(int size, string seq){
    vector<string> sub_seqs;
    for(int i=0; i< size; i++){
        string stg = "";
        for(int j=i; j < size; j++){
            stg += seq[j];
            sub_seqs.push_back(stg);
        }
    }

    return sub_seqs;
}


int main(){

    int n, m;
    string seqA, seqB;
    string outputA = "";
    string outputB = "";
    int w = 0;
    int max = 0;
    vector<string> sub_A, sub_B;
    string seqA_utilizada, seqB_utilizada;

    cin >> n >> m;
    cin >> seqA >> seqB;

    matrix H;
    H.resize(n+1);
    for(int e=0; e<=n; e++){
        H[e].resize(m+1);
    }

    //  Gerar todas as subsequencias a´ e b´ não-nulas de a e b
    sub_A = genSub(n, seqA);
    sub_B = genSub(m, seqB);

    
    // gera os possiveis pares entre as subsequencias
    for (int i=0; i< int(sub_A.size());i++) {
        for (int j=0; j< int(sub_B.size());j++) {

            string e1 = sub_A[i];
            string e2 = sub_B[j];
            
            int tamanho_e1 = e1.size();
            int tamanho_e2 = e2.size();

            // calcula o sw
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

    cout << "Score maximo: " << max << endl;
    cout << "Primeira sequencia utilizada: " << seqA_utilizada << endl;
    cout << "Segunda sequencia utilizada: " << seqB_utilizada << endl;

    

   
    return 0;
}