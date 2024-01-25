//moving average

#include <vector>
#include <iostream>
using namespace std;

vector<double> movingAverage1(const vector<double>& A, int M){
    vector<double> ret;
    int N = A.size();
    for(int i = M - 1; i < N; ++i){
        double partialSum = 0;
        for(int j = 0; j < M; ++j)
            partialSum += A[i - j];
        ret.push_back(partialSum / M);
    }
    return ret;
}

vector<double> movingAverage2(const vector<double>& A, int M){
    vector<double> ret;
    int N = A.size();
    double partialSum = 0;
    for(int i = 0; i < M - 1; ++i)
        partialSum += A[i];
    for(int i = M - 1; i < N; ++i){
        partialSum += A[i];
        ret.push_back(partialSum / M);
        partialSum -= A[i - M + 1];
    }
    return ret;
}