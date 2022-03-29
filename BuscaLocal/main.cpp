#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <fstream>
#include <random>
#include <string>
#include <tuple>

using namespace std;
typedef vector<vector<int>> matrix;

struct max_value{
    string seq;
    int score_max;
};

int calculate_score(char a, char b){
    if(a == b){
        return 2;
    }else{
        return -1;
    }
}

matrix max_score(matrix H, string first_seq, string second_seq, int k, int w){
    int diagonal, deletion, insertion;
    int valor_max = 0;
    string seq_max;
    int numero = 0;

    for (int i = 1; i <= k; i++){
        for (int j = 1; j <= k; j++){
            w = calculate_score(first_seq[i], second_seq[j]);

            diagonal = H[i-1][j-1] + w;
            deletion = H[i-1][j] - 1;
            insertion = H[i][j-1] - 1;

            H[i][j] = max({0, diagonal, deletion, insertion});
        }
    }

    return H;
}

int main(){

    int n, m;
    int max_k, k;
    int i, j , p;
    int w = 0;
    string seqA, seqB;
    string new_seqA, new_seqB;
    string sub_seqA, sub_seqB;

    vector<max_value> valores_max;
    
    char first_signal = '-';

    cin >> n >> m;
    cin >> seqA >> seqB;

    // descobrindo qual o maior valor possível para poder aleatoriazar o k
    // escolhendo o tamanho da menor sequencia 
    if(n>=m){
        max_k = m;
    }else{
        max_k = n;
    }

    default_random_engine generator;

    // calculando o k aleatório
    uniform_int_distribution<int> k_aleatorio(1, max_k);
    // k = k_aleatorio(generator);
    k = 6;

    // calculando o j aleatorio
    uniform_int_distribution<int> j_aleatorio(0, m - k);
    j = j_aleatorio(generator);

    // calculando o i aleatorio 
    uniform_int_distribution<int> i_aleatorio(0, n - k);
    
    cout << "k = " << k << endl;
    cout << "j = " << j << endl;
    
    // gerando a subsequencia de b
    sub_seqB = seqB.substr(j, k);

    // cout << seqB << endl;
    // cout << sub_seqB << endl;

    // gerando um número aleatorio para p
    uniform_int_distribution<int> p_aleatorio(1, 100);
    p = p_aleatorio(generator);

    cout << "p = " << p << endl;

    // criando matriz para calculo do max score
    new_seqB = first_signal + sub_seqB;
    matrix H;
    H.resize(k+1);
    for(int e=0; e<=k; e++){
        H[e].resize(k+1);
    }

    // gerando a subsequencia de a
    for(int e = 0; e < 5; e++){
        
        max_value highScore;

        i = i_aleatorio(generator);
        sub_seqA = seqA.substr(i, k);
        new_seqA = first_signal + sub_seqA;

        // tie(highScore.score_max, highScore.seq) = max_score(H, new_seqA, new_seqB, k, w);
        H = max_score(H, new_seqA, new_seqB, k, w);
        int max = 0;


        for (i = 0; i < k; i++){
            for (j = 0; j < k; j++){
                cout << H[i][j] << "  ";
                if(H[i][j] > max){
                    max = H[i][j];
                }
            }
            cout << "\n ";
        }
        
        cout << max << endl;
        cout << sub_seqA << endl;
        cout << "\n ";



        // cout << highScore.score_max << endl;
        // cout << highScore.seq << endl;
        // valores_max.push_back(highScore);
    }

    // for (int i = 0; i < sizeof(valores_max); i++){
    //     cout << valores_max[i].score_max << endl;
    //     cout << valores_max[i].seq << endl;
    // } 



    return 0;
}
