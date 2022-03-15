#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int calculate_score(char a, char b);

int calculate_score(char a, char b){
    if(a == b){
        return 2;
    }else{
        return -1;
    }
}


int main(){

    int n, m;
    string first_sequence, second_sequence;
    char first_signal = '-';

    cin >> n >> m;
    cin >> first_sequence >> second_sequence;

    first_sequence = first_signal + first_sequence;
    second_sequence = first_signal + second_sequence;

    // cout << n << endl << m << endl;
    // cout << first_sequence << endl << second_sequence << endl;

    int matriz[n+1][m+1] = {};

    // for (int i = 0; i < n; i++){
    //     for (int j = 0; j < m; j++){
    //         cout << matriz[i][j] << "  ";
    //     }
    //     cout << "\n ";
    // }

    for (int i = 1; i < n+1; i++){
        for (int j = 1; j < m+1; j++){

            // vendo se é match
            // if()

        }
    }

    return 0;
}