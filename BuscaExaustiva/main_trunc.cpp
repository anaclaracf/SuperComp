#include<iostream>
#include<vector>
#include<algorithm>
#include <cmath>
#include <tuple>
#include <fstream>

using namespace std;
vector<string> sub_A, sub_B;


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
    string seqA_utilizada, seqB_utilizada;

    cin >> n >> m;
    cin >> seqA >> seqB;


    //  Gerar todas as subsequencias a´ e b´ não-nulas de a e b
    sub_A = genSub(n, seqA);
    sub_B = genSub(m, seqB);


    // gera os possiveis pares entre as subsequencias
    for (int i=0; i< int(sub_A.size());i++) {
        for (int j=0; j< int(sub_B.size());j++) {
            
            w=0;
            
            string e1 = sub_A[i];
            string e2 = sub_B[j];

            // realizando o truncamento
            if(int(e1.size()) >= int(e2.size())){
                e1.resize(int(e2.size()));
            }else{
                e2.resize(int(e1.size()));
            }

            // calculando o score
            for(int e=0; e < int(e1.size()); e++){
                w += (e1[e] == e2[e] ? 2 : -1);
            }

            // definindo o score maximo e as sequencias utilizadas
            if(w >= max){
                max = w;
                seqA_utilizada = e1;
                seqB_utilizada = e2;
            }

        }
    }

    cout << "Score maximo: " << max << endl;
    cout << "Primeira sequencia utilizada: " << seqA_utilizada << endl;
    cout << "Segunda sequencia utilizada: " << seqB_utilizada << endl;

    return 0;
}