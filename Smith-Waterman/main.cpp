#include<iostream>
#include<vector>
#include<algorithm>
#include <cmath>
#include <tuple>
#include <fstream>

using namespace std;

struct alignment{
    string jump;
};


typedef vector<vector<int>> matrix;
typedef vector<vector<alignment>> matrix_align;

int calculate_score(char a, char b){
    if(a == b){
        return 2;
    }else{
        return -1;
    }
}

tuple<matrix, matrix_align> smithWaterman_Algorithm(matrix H, string first_seq, string second_seq, int n, int m, int w, matrix_align direction){
    int diagonal, deletion, insertion;

    for (int i = 1; i <= n; i++){
        for (int j = 1; j <= m; j++){
            w = calculate_score(first_seq[i], second_seq[j]);
            diagonal = H[i-1][j-1] + w;
            deletion = H[i-1][j] - 1;
            insertion = H[i][j-1] - 1;

            H[i][j] = max({0, diagonal, deletion, insertion});

            if(H[i][j] == diagonal){
                direction[i][j].jump = "diagonal";
            }
            else if(H[i][j] == deletion){
                direction[i][j].jump = "up";
            }
            else if(H[i][j] == insertion){
                direction[i][j].jump = "left";
            }
        }
    }

    return make_tuple(H, direction);
}

tuple<string, string> trace_path(int max_x, int max_y, matrix_align direction, string first_seq, string second_seq, string new_first_seq, string new_second_seq, matrix H){

    int i = max_x;
    int j = max_y;

    while(((i != 0) || (j != 0)) && H[i][j]){
    
        if(direction[i][j].jump == "diagonal"){
            new_first_seq += first_seq[i];
            i--;
            new_second_seq += second_seq[j];
            j--;
        }
        else if(direction[i][j].jump == "up"){
            new_first_seq += first_seq[i];
            i--;
            new_second_seq += "-";
        }
        else if(direction[i][j].jump == "left"){
            new_first_seq += "-";
            new_second_seq += second_seq[j];
            j--;
        }
    }
    
    return make_tuple(new_first_seq, new_second_seq);

}

int main(){

    int n, m;
    int w = 0;
    string first_seq, second_seq;
    string new_first_seq, new_second_seq;
    char first_signal = '-';
    int max_value = 0;
    int max_x = 0; 
    int max_y = 0;

    cin >> n >> m;
    cin >> first_seq >> second_seq;


    // fromatando as sequencias de DNA
    first_seq = first_signal + first_seq;
    second_seq = first_signal + second_seq;

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
    tie(H, direction) = smithWaterman_Algorithm(H, first_seq, second_seq, n, m, w, direction);

    // visualizando a matriz com o algoritmo aplicado e encontra o maior vvalor da matriz
    for (int i = 0; i <= n; i++){
        for (int j = 0; j <= m; j++){
            if(H[i][j] > max_value){
                max_value = H[i][j];
                max_x = i;
                max_y = j;
            }

            // cout << H[i][j] << "  ";
        }
        // cout << endl;
    }

    // realizando o alinhamento local a partir do maior valor
    // tem que parar ou quando achar um zero ou quando a posicao for (0,0)

    tie(new_first_seq, new_second_seq) = trace_path(max_x, max_y, direction, first_seq, second_seq, new_first_seq, new_second_seq, H);

    reverse(new_first_seq.begin(), new_first_seq.end());
    reverse(new_second_seq.begin(), new_second_seq.end());

    ofstream output_file;
    output_file.open ("output");

    output_file << max_value << '\n';
    output_file << new_first_seq << '\n';
    output_file << new_second_seq;

    output_file.close();

    return 0;
}