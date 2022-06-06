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
#include <tuple>


using namespace std;

struct index_seq {
    int begin_seq;
    int size_seq;
};

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

struct temp_calculator {

    thrust::device_ptr<char> a_sub;
    thrust::device_ptr<index_seq> index_B;
    thrust::device_ptr<char> sequence_B;

    temp_calculator(thrust::device_ptr<char> a_sub_, thrust::device_ptr<index_seq> index_B_, thrust::device_ptr<char> sequence_B_):
    a_sub(a_sub_),
    index_B(index_B_),
    sequence_B(sequence_B_){};

    __host__ __device__
    int operator()(const int& i){

        return 0;
    }

};



struct score_calculator {

    thrust::device_ptr<index_seq> index_A;
    thrust::device_ptr<index_seq> index_B;
    thrust::device_ptr<char> sequence_A;
    thrust::device_ptr<char> sequence_B;
    int size_idxB;
    

    score_calculator(thrust::device_ptr<index_seq> index_A_, thrust::device_ptr<index_seq> index_B_, thrust::device_ptr<char> sequence_A_, thrust::device_ptr<char> sequence_B_, int size_idxB_):
    index_A(index_A_),
    index_B(index_B_),
    sequence_A(sequence_A_),
    sequence_B(sequence_B_),
    size_idxB(size_idxB_){};

    __host__ __device__
    int operator()(const int& x){

        index_seq ind;
        ind = index_A[x];
        thrust::device_ptr<char> a_sub;

        int i = 0;
        for(int e = ind.begin_seq; e < (ind.begin_seq + ind.size_seq); e++){
            a_sub[i] = sequence_A[e];
            i++;
        }

        for(int w = 0; w < size_idxB; w++){
            index_seq ind_B;
            ind_B = index_B[w];
            thrust::device_ptr<char> b_sub;

            int f = 0;
            for(int g = ind_B.begin_seq; g < (ind_B.begin_seq + ind_B.size_seq); g++){
                b_sub[f] = sequence_B[g];
                f++;
            }
        }

        // thrust::counting_iterator<int> c0(0);
        // thrust::counting_iterator<int> c1(size_idxB);
        // thrust::device_ptr<int> result;

        // thrust::transform(c0, c1, result, temp_calculator(a_sub, index_B, sequence_B));

        return 0;

    }

};


thrust::device_vector<char> sequence_generator(int size, vector<string> sub, thrust::device_vector<char> sequence){

    // todas as sequencias
    for(int i = 0; i < size; i++){

        int size_sequencia = int(sub[i].size());

        // todas letras de cada sequencia
        for(int e = 0; e < size_sequencia; e++){
            sequence.push_back(sub[i][e]);
        }
    }

    return sequence;
}

thrust::device_vector<index_seq> index_generator(int size, vector<string> sub, thrust::device_vector<index_seq> indexes){

    int start = 0;
    // todas as sequencias
    for(int i = 0; i < size; i++){

        index_seq indices;

        int size_sequencia = int(sub[i].size());

        indices.size_seq = size_sequencia;
        indices.begin_seq = start;
        indexes.push_back(indices);

        start += size_sequencia;
    }

    return indexes;
}


int main(){

    int n, m;
    string seq_A, seq_B;
    vector<string> sub_A, sub_B;
    
    thrust::device_vector<index_seq> index_A_final,index_A, index_B, index_B_final;
    thrust::device_vector<char> sequence_A, sequence_A_final, sequence_B_final, sequence_B;

    cin >> n >> m;
    cin >> seq_A >> seq_B;

    //  Gerar todas as subsequencias a´ e b´ não-nulas de a e b
    sub_A = genSub(n, seq_A);
    sub_B = genSub(m, seq_B);

    int size_A = sub_A.size();
    int size_B = sub_B.size();

    int cont = 0;
    for (int a = 0; a < size_A; a++){
        for (int b = 0; b < size_B; b++){
            cont ++;
        }
    }


    sequence_A_final = sequence_generator(size_A, sub_A, sequence_A);
    index_A_final = index_generator(size_A, sub_A, index_A);

    sequence_B_final = sequence_generator(size_B, sub_B, sequence_B);
    index_B_final = index_generator(size_B, sub_B, index_B);

    thrust::counting_iterator<int> c0(0);
    thrust::counting_iterator<int> c1(int(index_A_final.size()));
    thrust::device_vector<int> result(cont);

    int size_idx_B = int(index_B_final.size());

    thrust::transform(c0, c1, result.begin() + 1, score_calculator(index_A_final.data(), index_B_final.data(), sequence_A_final.data(), sequence_B_final.data(), size_idx_B));
    // int max_value = thrust::reduce(result.begin(), result.end(),0,thrust::maximum<int>());

    // cout << max_value << endl;

    // for(int i = 0 ; i < int(index_A_final.size()); i++){
    //     index_seq ind;
    //     ind = index_A_final[i];
    //     cout << ind.begin_seq << endl;
    // }
    
    return 0;

}