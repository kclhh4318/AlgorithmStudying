#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <limits>

//MAX_NUMBER: 한 칸에 들어갈 숫자의 최대치
int n, triangle[100][100];
int cache[100][100][MAX_NUMBER * 100 + 1];
//(y, x) 위치까지 내려오기 전에 만난 숫자들의 합이 sum 일때
//맨 아래줄까지 내려가면서 얻을 수 있는 최대 경로를 반환한다.
int path1(int y, int x, int sum){
    //기저 사례: 맨 아래 줄까지 도달했을 경우
    if(y == n - 1) return sum + triangle[y][x];
    //메모이제이션
    int& ret = cache[y][x][sum];
    if(ret != -1) return ret;
    sum += triangle[y][x];
    return ret = max(path1(y + 1, x + 1, sum), path1(y + 1, x, sum));
} // 특정 입력에 대해서는 완전 탐색처럼 동작한다.

int n, triangle[100][100];
int cache2[100][100];
//(y, x) 위부터 맨 아래줄까지 내려가면서 얻을 수 있는 최대 경로의 합을 반환한다.
int path2(int y, int x){
    //기저 사례
    if(y == n - 1) return triangle[y][x];
    //메모이제이션
    int& ret = cache2[y][x];
    if(ret != -1) return ret;
    return ret = max(path2(y + 1, x), path2(y + 1, x + 1)) + triangle[y][x];
}

int lis(const vector<int>& A){
    //기저 사례: A가 텅 비어 있을 때
    if(A.empty()) return 0;
    int ret = 0;
    for(int i = 0; i < A.size(); ++i){
        vector<int> B;
        for(int j = i + 1; j < A.size(); ++j)
            if(A[i] < A[j])
                B.push_back(A[j]);
        ret = max(ret, 1 + lis(B));
    }
    return ret;
}

 int n;
 int cache[100], S[100];
 //S[start]에서 시작하는 증가 부분 수열 중 최대 길이를 반환한다.
 int list2(int start){
    int& ret = cache[start];
    if(ret != -1) return ret;
    //항상 S[start]는 있기 때문에 길이는 최하 1
    ret = 1;
    for(int next = start + 1; next < n; ++next)
        if(S[start] < S[next])
            ret = max(ret, lis2(next) + 1);
    return ret;
}

 int n;
 int cache[101], S[100];
 //S[start]에서 시작하는 증가 부분 수열 중 최대 길이를 반환한다.
 int lis3(int start){
    int& ret = cache[start + 1];
    if(ret != -1) return ret;
    //항상 S[start]는 있기 때문에 길이는 최하 1
    ret = 1;
    for(int next = start + 1; next < n; ++next)
        if(start == -1 || S[start] < S[next])
            ret = max(ret, lis3(next) + 1);
    return ret;
}

//입력이 32비트 부호 있는 정수의 모든 값을 가질 수 있으므로
//인위적인 최소치는 64비트여야 한다.
const long long NEGINF = numeric_limits<long long>::min();
int n, m, A[100], B[100];
int cache[101][101];
//min(A[indexA], B[indexB]), max(A[indexA], B[indexB])로 시작하는
//합친 증가 부분 수열의 최대 길이를 반환한다.
//단 indexA == indexB == -1 혹은 A[indexA] != B[indexB]라고 가정한다.
int jlis(int indexA, int indexB){
    //memoization
    int& ret = cache[indexA + 1][indexB + 1];
    if(ret != -1) return ret;
    //A[indexA], B[indexB]가 이미 존재하므로 2개는 항상 있다.
    ret = 2;
    long long a = (indexA == -1 ? NEGINF : A[indexA]);
    long long b = (indexB -- -1 ? NEGINF : B[indexB]);
    long long maxElement = max(a, b);
    //다음 원소를 찾는다.
    for(int nextA = indexA + 1; nextA < n; ++nextA)
        if(maxElement < A[nextA])
            ret = max(ret, jlis(nextA, indexB) + 1);
    for(int nextB = indexB + 1; nextB < n; ++nextB)
        if(maxElement < B[nextB])
            ret = max(ret, jlis(indexA, nextB) + 1);
    return ret;
}