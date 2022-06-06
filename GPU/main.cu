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
#include<omp.h>

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

        int diagonal = line[x-1] + (letter_B == sequence_A[x-1] ? 2 : -1);
        int deletion = line[x] - 1;

        int max = 0;

        if (deletion >= diagonal && deletion > max){
            return deletion;
        }
        else if (diagonal > max){
            return diagonal;
        }
        else{
            return max;
        }

    }

};

struct lateral {

    __host__ __device__
    int operator()(const int& i, const int& j){

        int max = 0;
        int actual = j;        
        int left = i-1;

        max = (left < actual ? actual : left);

        if(max < 0){
            max =  0;
        }

        return max;
    }

};


int main(){

    int n, m;
    string seq_A, seq_B;
    vector<string> sub_A, sub_B;
    thrust::device_vector<int> results[2], maximos;

    cin >> n >> m;
    cin >> seq_A >> seq_B;

    //  Gerar todas as subsequencias a´ e b´ não-nulas de a e b
    sub_A = genSub(n, seq_A);
    sub_B = genSub(m, seq_B);

    int size_A = sub_A.size();
    int size_B = sub_B.size();

    // criando contador inicial para percorrer a sequencia A
    thrust::counting_iterator<int> counter_initial(1);

    // utilizando openmp para paralelizar o processo
    #pragma omp for collapse(2)

    // percorre o tamanho das possíveis sequencias de A
    for (int i=0; i < size_A; i++) {
        // percorre o tamanho das possíveis sequencias de B
        for (int j=0; j < size_B; j++) {

            // transforma a sub sequencia em um device vector para utilização da GPU
            thrust::device_vector<char> subseq_A(sub_A[i].begin(), sub_A[i].end());
            thrust::device_vector<char> subseq_B(sub_B[j].begin(), sub_B[j].end());
                        
            int size_subB = int(subseq_B.size());
            int size_subA = int(subseq_A.size());

            thrust::counting_iterator<int> counter_final(size_subA+1);

            results[0].resize(size_subA+1);
            results[1].resize(size_subA+1);

            thrust::fill(results[0].begin(), results[0].end(),0);


            for(int e = 0; e < size_subB; e++){
                char letter_B = subseq_B[e];
                thrust::transform(counter_initial, counter_final, results[1].begin() + 1, temp(subseq_A.data(), letter_B, results[0].data()));
                thrust::inclusive_scan(results[1].begin()+1, results[1].end(), results[0].begin()+1, lateral());
            }

            maximos.push_back(results[0].back());

            // cout << results[0].back() << endl;
            
        }
        
    }

    int max_value = thrust::reduce(maximos.begin(), maximos.end(),0,thrust::maximum<int>());

    cout << max_value << endl;

    return 0;

}