#include<iostream>
#include<vector>
#include<algorithm>
#include <cmath>

using namespace std;

struct alignment{
    string jump;
};


typedef vector<vector<int>> matrix;
typedef vector<vector<alignment>> matrix_align;


int calculate_score(char a, char b);
matrix smithWaterman_Algorithm(matrix H, string first_seq, string second_seq, int n, int m, int w, matrix_align direction);
matrix_align calculate_direction(int diagonal, int deletion, int insertion, matrix H, int i, int j, matrix_align direction);

int calculate_score(char a, char b){
    if(a == b){
        return 2;
    }else{
        return -1;
    }
}

matrix smithWaterman_Algorithm(matrix H, string first_seq, string second_seq, int n, int m, int w, matrix_align direction){
    int diagonal, deletion, insertion;

    for (int i = 1; i <= n; i++){
        for (int j = 1; j <= m; j++){
            w = calculate_score(first_seq[i], second_seq[j]);
            diagonal = H[i-1][j-1] + w;
            deletion = H[i-1][j] - 1;
            insertion = H[i][j-1] - 1;

            H[i][j] = max({0, diagonal, deletion, insertion});
            calculate_direction(diagonal, deletion, insertion, H, i, j, direction);
        }
    }

    return H;
}

matrix_align calculate_direction(int diagonal, int deletion, int insertion, matrix H, int i, int j, matrix_align direction){
    
    if(H[i][j] == diagonal){
        direction[i][j].jump = "diagonal";
    }
    else if(H[i][j] == deletion){
        direction[i][j].jump = "up";
    }
    else if(H[i][j] == insertion){
        direction[i][j].jump = "left";
    }
    return direction;
}


int main(){

    int n, m;
    int w = 0;
    string first_seq, second_seq;
    char first_signal = '-';
    int max_value = 0;
    int max_x = 0; 
    int max_y = 0;

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
    
    // matrix_align movement;
    H.resize(n+1);
    for(int e=0; e<=n; e++){
        H[e].resize(m+1);
    }

    // criando matriz que guarda as direções dos movimentos
    matrix_align direction(n+1, vector<alignment>(m+1));
    direction.reserve(n*m);

    // aplicando o algoritmo de smith waterman
    H = smithWaterman_Algorithm(H, first_seq, second_seq, n, m, w, direction);

    // visualizando a matriz com o algoritmo aplicado
    for (int i = 0; i <= n; i++){
        for (int j = 0; j <= m; j++){
            if(H[i][j] > max_value){
                max_value = H[i][j];
                max_x = i;
                max_y = j;
            }

            cout << H[i][j] << "  ";
        }
        cout << endl;
    }

    // encontrando o maior valor da matriz
    cout << "Valor máximo: " << max_value << endl;
    cout << "Posição X do valor máximo: " << max_x << endl;
    cout << "Posição Y do valor máximo: " << max_y << endl;

    



    return 0;
}