#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <limits>
using namespace std;

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
    long long b = (indexB == -1 ? NEGINF : B[indexB]);
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

const int INF = 987654321;
string N;
//N[a..b] 구간의 난이도를 반환한다.
int classify(int a, int b){
    //숫자 조각을 가져온다.
    string M = N.substr(a, b - a + 1);
    //첫 글자만으로 이루어진 문자열과 같으면 난이도는 1
    if(M == string(M.size(), M[0])) return 1;
    //등차수열인지 검사한다.
    bool progressive = true;
    for(int i = 0; i < M.size() - 1; ++i)
        if(M[i + 1] - M[i] != M[1] - M[0])
            progressive = false;
    //등차수열이고 공차가 1 혹은 -1이면 난이도는 2
    if(progressive && abs(M[1] - M[0]) == 1)
        return 2;
    //두 수가 번갈아 등장하는지 확인한다.
    bool alternating = true;
    for(int i = 0; i < M.size(); ++i)
        if(M[i] != M[i % 2])
            alternating = false;
    if(progressive) return 4;
    if(alternating) return 5;
    return 10;
}

int cache[10002];
//수열 N[begin..]를 외우는 방법 중 난이도의 최소 합을 출력한다.
int memorize(int begin){
    //기저 사례: 수열의 끝에 도달했을 경우
    if(begin == N.size()) return 0;
    //메모이제이션
    int& ret = cache[begin];
    if(ret != -1) return ret;
    ret = INF;
    for(int L = 3; L <= 5; ++L)
        if(begin + L <= N.size())
            ret = min(ret, memorize(begin + L) + classify(begin, begin + L - 1));
    return ret;
}

const int INF = 987654321;
//A[]: 양자화해야 할 수열, 정렬한 상태
//pSum[]: A[]의 부분합을 저장한다. pSum[i]는 A[0] .. A[i] 의 합
//pSqSum[]: A[] 제곱의 부분합을 저장한다. pSqSum[i]는 A[0]^2 .. A[i]^2의 합
int n;
int A[101], pSum[101], pSqSum[101];
//A를 정렬하고 각 부분합을 계산한다.
void precalc(){
    sort(A, A + n);
    pSum[0] = A[0];
    pSqSum[0] = A[0] * A[0];
    for(int i = 1; i < n; ++i){
        pSum[i] = pSum[i - 1] + A[i];
        pSqSum[i] = pSqSum[i - 1] + A[i] * A[i];
    }
}
//A[lo] .. A[hi] 구간을 하나의 숫자로 표현할 때 최소 오차 합을 계산한다.
int minError(int lo, int hi){
    //부분합을 이용해 A[lo] ~ A[hi]까지의 합을 구한다.
    int sum = pSum[hi] - (lo == 0 ? 0 : pSum[lo - 1]);
    int sqSum = pSqSum[hi] - (lo == 0 ? 0 : pSqSum[lo - 1]);
    //평균을 반올림한 값으로 이 수들을 표현한다.
    int m = int(0.5 + (double)sum / (hi - lo + 1));
    //sum(A[i] - m) ^ 2 를 전개한 결과를 부분 합으로 표현
    int ret = sqSum - 2 * m * sum + m * m * (hi - lo + 1);
    return ret;
}
int cache[101][11];
int quantize(int from, int parts){
    //기저 사례: 모든 숫자들을 다 양자화했을 때
    if(from == n) return 0;
    //기저 사례: 숫자는 아직 남았는데 더 묶을 수 없을 때 아주 큰 값을 반환한다.
    if(parts == 0) return INF;
    int& ret = cache[from][parts];
    if(ret != -1) return ret;
    ret = INF;
    //조각의 길이를 변화시켜 가며 최소치를 찾는다.
    for(int partSize = 1; from + partSize <= n; ++partSize)
        ret = min(ret, minError(from, from + partSize - 1) + quantize(from + partSize, parts - 1));
    return ret;
}

const int MOD = 1000000007;
int cache[101];
//2*width 크기의 사각형을 채우는 방법의 수를 MOD로 나눈 나머지를 반환한다.
int tiling(int width){
    //기저 사례: witdh가 1 이하일때
    if(width <= 1) return 1;
    //메모이제이션
    int& ret = cache[width];
    if(ret != -1) return ret;
    return ret = (tiling(width - 2) + tiling(width - 1) % MOD);
}

int n, m;
int cache[MAX_N][2 * MAX_ + 1];
//달팽이가 days일 동안 climbed미터를 기어올라 왔다고 할때,
//m일 전까지 n미터를 기어올라갈 수 있는 경우의 수
int climb(int days, int climbed){
    //기저 사례: m일이 모두 지난 경우
    if(days == m) return climbed >= n ? 1 : 0;
    //메모이제이션
    int& ret = cache[days][climbed];
    if(ret != -1) return ret;
    return ret = climb(days + 1, climbed + 1) + climb(days + 1, climbed + 2);
}

//2*width 크기의 사각형을 채우는 비대칭 방법의 수를 반환한다.
int asymmetric(int width){
    if(width % 2 == 1)
        return (tiling(width) - tiling(width / 2) + MOD) % MOD;
    int ret = tiling(width);
    ret = (ret - tiling(width / 2) + MOD) % MOD;
    ret = (ret - tiling(width / 2 - 1) + MOD) % MOD;
    return ret;
}

int cache2[101];
//2 * width 크기의 사각형을 채우는 비대칭 방법의 수를 반환한다.
int asymmetric2(int width){
    //기저 사례: 너비가 2 이하인 경우
    if(width <= 2) return 0;
    //메모이제이션
    int& ret = cache2[width];
    if(ret != -1) return ret;
    ret = asymmetric2(width - 2) % MOD; // (a)
    ret = (ret + asymmetric2(width - 4)) & MOD; //(b)
    ret = (ret + tiling(width - 3)) % MOD; //(c)
    ret = (ret + tiling(width - 3)) % MOD; //(d)
    return ret;
}

const int MOD = 10 * 1000 * 1000;
int cache[101][101];
//n개의 정사각형으로 이루어졌고, 맨 위 가로줄에 first개의
//정사각형을 포함하는 폴리오미노의 수를 반환한다.
int poly(int n, int first){
    //기저 사례: n == first
    if(n == first) return 1;
    //메모이제이션
    int& ret = cache[n][first];
    if(ret != -1) return ret;
    ret = 0;
    for(int second = 1; second <= n - first; ++second){
        int add = second + first - 1;
        add *= poly(n - first, second);
        add %= MOD;
        ret += add;
        ret %= MOD;
    }
    return ret;
} // 시간복잡도: 가능한 n과 first 의 조합 O(n ^ 2) + poly 한 번 실행하는데 걸리는 시간 O(n) = O(n ^ 3)

int n, d, p, q;
//connected[i][j] = 마을 i, j가 연결되어 있나 여부
//deg[i] = 마을 i와 연결된 마을의 개수
int connected[51][51], deg[51];
double search(vector<int>& path){
    //기저 사례: d일이 지난 경우
    if(path.size() == d + 1){
        //이 시나리오가 q에서 끝나지 않는다면 무효
        if(path.back() != q) return 0.0;
        //path의 출현 확률을 계산한다.
        double ret = 1.0;
        for(int i = 0; i + 1 < path.size(); ++i)
            ret /= deg[path[i]];
        return ret;
    }
    double ret = 0;
    //경로의 다음 위치를 결정한다.
    for(int there = 0; there < n; ++there)
        if(connected[path.back()][there]){
            path.push_back(there);
            ret += search(path);
            path.pop_back();
        }
    return ret;
}

int n, d, p, q;
//cache[][]는 -1로 초기화 해둔다.
double cache[51][101];
//connected[i][j] = 마을 i, j가 연결되어 있나 여부
//deg[i] = 마을 i와 연결된 마을의 개수
int connected[51][51], deg[51];
//days일째에 here번 마을에 숨어있다고 가정하고,
//마지막 날에 q번 마을에 숨어 있을 조건부 확률을 반환한다.
double search2(int here, int days){
    //기저 사례: d일이 지난 경우
    if(days == d) return (here == q ? 1.0 : 0.0);
    //메모이제이션
    double& ret = cache[here][days];
    if(ret > -0.5) return ret;
    ret = 0.0;
    for(int there = 0; there < n; ++there)
        if(connected[here][there])
            ret += search2(there, days + 1) / deg[here];
    return ret;
}

double search3(int here, int days){
    //기저 사례: 0일 째
    if(days == 0) return (here == p ? 1.0 : 0.0);
    //메모이제이션
    double& ret = cache[here][days];
    if(ret > -0.5) return ret;
    ret = 0.0;
    for(int there = 0; there < n; ++there)
        if(connected[here][there])
            ret += search3(there, days - 1) / deg[there];
    return ret;
}