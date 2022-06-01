#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <string>
#include <tuple>
#include <fstream>
#include <thrust/device_vector.h>
#include <thrust/device_ptr.h>
#include <thrust/host_vector.h>
#include <thrust/copy.h>
#include <thrust/fill.h>
#include <thrust/iterator/counting_iterator.h>

using namespace std;

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


struct temp {
    thrust::device_ptr<char> sequence_A;
    char letter_B;
    thrust::device_ptr<int> line;

    temp(thrust::device_ptr<char> sequence_A_, char letter_B_, thrust::device_ptr<int> line_):
    sequence_A(sequence_A_),
    letter_B(letter_B_),
    line(line_){};

    __host__ __device__
    int operator()(const int& x){

        int score = (letter_B == sequence_A[x] ? 2 : -1);
        int diagonal = line[x-1] + score;
        int deletion = line[x] - 1;

        if (diagonal >= deletion && diagonal >0){
            return diagonal;
        }
        else if (deletion > 0){
            return deletion;
        }
        else{
            return 0;
        }

    }

};


int main(){

    int n, m;
    string seq_A, seq_B;
    vector<string> sub_A, sub_B;
    thrust::device_vector<int> calc[2];
    thrust::device_vector<int> maximos;

    cin >> n >> m;
    cin >> seq_A >> seq_B;

    //  Gerar todas as subsequencias a´ e b´ não-nulas de a e b
    sub_A = genSub(n, seq_A);
    sub_B = genSub(m, seq_B);

    int size_A = sub_A.size();
    int size_B = sub_B.size();

    thrust::counting_iterator<int> c0(0);
    

    for (int i=0; i < size_A; i++) {
        for (int j=0; j < size_B; j++) {

            thrust::device_vector<char> subseq_A(sub_A[i].begin(), sub_A[i].end());
            thrust::device_vector<char> subseq_B(sub_B[j].begin(), sub_B[j].end());
            
            int size_subB = int(subseq_B.size());
            int size_subA = int(subseq_A.size());

            thrust::counting_iterator<int> c1(size_subA);

            calc[0].resize(size_subA+1);
            calc[1].resize(size_subA+1);

            thrust::fill(calc[0].begin(), calc[0].end(),0);

            for(int e = 0; e < size_subB; e++){
                char letter_B = subseq_B[e];
                thrust::transform(c0, c1, calc[1].begin() + 1, temp(subseq_A.data(), letter_B, calc[0].data()));
                thrust::inclusive_scan(calc[1].begin()+1, calc[1].end(), calc[0].begin()+1, thrust::maximum<int>());
            }

            maximos.push_back(calc[0].back());
            
        }
        
    }

    int max_value = thrust::reduce(maximos.begin(), maximos.end(),0,thrust::maximum<int>());

    cout << max_value << endl;

    return 0;

}