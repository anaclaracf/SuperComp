#include<iostream>
#include<vector>
#include<algorithm>
#include <cmath>
#include <tuple>
#include <fstream>

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
            
            w=0;

            int tamanho_e1 = e1.size();
            int tamanho_e2 = e2.size();
            if(tamanho_e1 >= tamanho_e2){
                e1.resize(tamanho_e2);
            }else{
                e2.resize(tamanho_e1);
            }

            int tamanha_final = e1.size();

            for(int e=0; e < tamanha_final; e++){
                w += (e1[e] == e2[e] ? 2 : -1);
            }

            if(w >= max){
                max = w;
                seqA_utilizada = e1;
                seqB_utilizada = e2;
            }

            // cout << e1 << "," << e2 << endl;
        }
    }

    cout << "Score maximo: " << max << endl;
    cout << "Primeira sequencia utilizada: " << seqA_utilizada << endl;
    cout << "Segunda sequencia utilizada: " << seqB_utilizada << endl;

    return 0;
}