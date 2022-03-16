#include<iostream>
#include<vector>
#include<algorithm>
#include <cmath>

using namespace std;
typedef vector<vector<int>> matrix;

int calculate_score(char a, char b);
matrix smithWaterman_Algorithm(matrix H, string first_seq, string second_seq, int n, int m, int w);

int calculate_score(char a, char b){
    if(a == b){
        return 2;
    }else{
        return -1;
    }
}

matrix smithWaterman_Algorithm(matrix H, string first_seq, string second_seq, int n, int m, int w){
    int diagonal, deletion, insertion;

    for (int i = 1; i <= n; i++){
        for (int j = 1; j <= m; j++){
            w = calculate_score(first_seq[i], second_seq[j]);
            diagonal = H[i-1][j-1] + w;
            deletion = H[i-1][j] - 1;
            insertion = H[i][j-1] - 1;

            // cout << diagonal << endl;
            // cout << deletion << endl;
            // cout << insertion << endl;

            // cout << max({0, diagonal, deletion, insertion}) << endl;

            H[i][j] = max({0, diagonal, deletion, insertion});
        }
    }

    return H;
}


int main(){

    int n, m;
    int w = 0;
    string first_seq, second_seq;
    char first_signal = '-';

    cin >> n >> m;
    cin >> first_seq >> second_seq;


    // fromatando as sequencias de DNA
    first_seq = first_signal + first_seq;
    second_seq = first_signal + second_seq;

    // printando as entradas geradas pelo arquivo de entrada
    cout << n << endl << m << endl;
    cout << first_seq << endl << second_seq << endl;

    // criando a matriz e iniciando ela com zeros
    matrix H;
    H.resize(n+1);
    for(int e=0; e<=n; e++){
        H[e].resize(m+1);
    }

    // vizualizando a matriz preenchida com zeros
    // for (int i = 0; i <= n; i++){
    //     for (int j = 0; j <= m; j++){
    //         cout << H[i][j] << "  ";
    //     }
    //     cout << "\n ";
    // }

    // aplicando o algoritmo de smith waterman
    H = smithWaterman_Algorithm(H, first_seq, second_seq, n, m, w);

    // visualizando a matriz com o algoritmo aplicado
    for (int i = 0; i <= n; i++){
        for (int j = 0; j <= m; j++){
            cout << H[i][j] << "  ";
        }
        cout << "\n ";
    }

    return 0;
}