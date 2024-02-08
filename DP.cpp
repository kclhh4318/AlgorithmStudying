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

int n;
int cache[101], S[100], choices[101];
//S[start]에서 시작하는 증가 부분 수열 중 최대 길이를 반환한다.
int lis4(int start){
    int& ret = cache[start + 1];
    if(ret != -1) return ret;
    //항상 S[start]는 있기 때문에 길이는 최하 1
    ret = 1;
    int bestNext = -1;
    for(int next = start + 1; next < n; ++next)
        if(start == -1 || S[start] < S[next]){
            int cand = lis4(next) + 1;
            if(cand > ret){
                ret = cand;
                bestNext = next;
            }
        }
    choices[start + 1] = bestNext;
    return ret;
}
//S[start]에서 시작하는 LIS 를 seq에 저장한다.
void reconstruct(int start, vector<int>& seq){
    if(start != -1) seq.push_back(S[start]);
    int next = choices[start + 1];
    if(next != -1) reconstruct(next, seq);
}

int n, capacity;
int volume[100], need[100];
int cache[1001][100];
string name[100];
//캐리어에 남은 용량이 capacity일 때, item 이후의 물건들을
//담아 얻을 수 있는 최대 절박도의 합을 반환한다.
int pack(int capacity, int item){
    //기저 사례: 더 담을 물건이 없을 때
    if(item == n) return 0;
    int& ret = cache[capacity][item];
    if(ret != -1) return ret;
    //이 물건을 담지 않을 경우
    ret = pack(capacity, item + 1);
    //이 물건을 담을 경우
    if(capacity >= volume[item])
        ret = max(ret, pack(capacity - volume[item], item + 1) + need[item]);
    return ret;
}

//pack(capacity, item)이 선택한 물건들의 목록을 picked에 저장한다.
void reconstruct(int capacity, int item, vector<string>& picked){
    //기저 사례: 모든 물건을 다 고려했음
    if(item == n) return;
    if(pack(capacity, item) == pack(capacity, item + 1)){
        reconstruct(capacity, item + 1, picked);
    }
    else{
        picked.push_back(name[item]);
        reconstruct(capacity - volume[item], item + 1, picked);
    }
}

int n, m;
//분류기가 반환한 문장. 단어 번호로 변환되어 있음
int R[100];
//T[i][j] = i 단어 이후에 j단어가 나올 확률의 로그 값
double T[501][501];
//M[i][j] = i 단어가 j단어로 분류될 확률의 로그 값
double M[501][501];
int choice[102][502];
double cache[102][502]; // 1로 초기화한다.

//Q[segment] 이후를 채워서 얻을 수 있는 최대 g() 곱의 로그 값을 반환한다.
//Q[segment - 1] == previousMatch라고 가정한다.
double recognize(int segment; int previousMatch){
    if(segment == n) return 0;
    doublt& ret = cache[segment][previousMatch];
    if(ret != 1.0) return ret;
    ret = -1e200; //log(0) = 음의 무한대에 해당하는 값
    int& choose = choice[segment][previousMatch];
    //R[segment]에 대응되는 단어를 찾는다.
    for(int thisMatch = 0; thisMatch < m; ++thisMatch){
        //g(thisMatch) = T(previoiusMatch, thisMatch) * M(thisMatch, R[segment])
        double cand = T[previousMatch][thisMatch]; + M[thisMatch][R[segment]] + recognize(segment + 1, thisMatch);
        if(cand > ret){
            ret = cand;
            choose = thisMatch;
        }
    }
    return ret;
}

//입력받은 단어들의 목록
string corpus[501];
string reconstruct(int segment, int previousMatch){
    int choose = choice[segment][previousMatch];
    string ret = corpus[choose];
    if(segment < n - 1)
        ret = ret + " " + reconstruct(segment + 1, choose);
    return ret;
}

//s: 지금까지 만든 신호
//n: 더 필요한 -의 개수
//m: 더 피룡한 o의 개수
void generate(int n, int m, string s){
    //기저 사레: n = m = 0
    if(n == 0 && m == 0){
        cout << s << endl;
        return;
    }
    if(n > 0) generate(n - 1, m, s + "-");
    if(m > 0) generate(n, m - 1, s + "o");
}

int skip; //k - 1로 초기화
//skip개를 건너뛰고 출력한다.
void generate2(int n, int m, string s){
    //기저 사례: skip < 0
    if(skip < 0) return;
    //기저 사레: n = m = 0
    if(n == 0 && m == 0){
        //더 건너뛸 신호가 없는 경우
        if(skip == 0) cout << s << endl;
        --skip;
        return;
    }
    if(n > 0) generate2(n - 1, m, s + "-");
    if(m > 0) generate2(n, m - 1, s + "o");
}

//K의 최대값 + 100. 오버플로를 막기 위해 이보다 큰 값은 구하지 않는다.
const int M = 1000000000000 + 100;
int bino[201][201];
//필요한 모든 이항계수를 미리 계산해 둔다.
void calcBino(){
    memset(bino, 0, sizeof(bino));
    for(int i = 0; i <= 200; ++i){
        bino[i][0] = bino[i][i] = 1;
        for(int j = 1; j < i; ++j)
            bino[i][j] = min(M, bino[i - 1][j - 1] + bino[i - 1][j]);
    }
}
//skip개를 건너뛰고 출력한다.
void generate3(int n, int m, string s){
    //기저 사레: skip < 0
    if(skip < 0) return;
    //기저 사례: n = m = 0
    if(n == 0 && m == 0){
        if(skip == 0) cout << s << endl;
        --skip;
        return;
    }
    if(bino[n + m][n] <= skip){
        skip -= bino[n + m][n];
        return;
    }
    if(n > 0) generate3(n - 1, m, s + "-");
    if(m > 0) generate3(n, m - 1, s + "o");
}

//n개의 -, m개의 o으로 구성된 신호 중 skip개를 건너뛰고
//만들어지는 신호를 반환한다.
string kth(int n, int m, int skip){
    //n == 0인 경우 나머지 부분은 전부 o일 수밖에 없다.
    if(n == 0) return string(m, 'o');
    if(skip < bino[n + m - 1][n - 1])
        return "-" + kth(n - 1, m, skip);
    return "o" + kth(n, m - 1, skip - bino[n + m - 1][n - 1]);
}

const int MAX = 2000000000000 + 1;
int n;
int cacheLen[501], cacheCnt[501], S[500];
//S[start]에서 시작하는 증가 부분 수열 중 최대 길이를 반환한다.
int lis(int start){
    //메모이제이션
    int& ret = cacheLen[start + 1];
    if(ret != -1) return ret;
    //항상 S[start]는 있기 때문에 길이는 최하 1
    ret = 1;
    for(int next = start + 1; next < n; ++next)
        if(start == -1 || S[start] < S[next])
            ret = max(ret, lis(next) + 1);
    return ret;
}
//S[start]에서 시작하는 최대 증가 부분 수열의 수를 반환한다
int count(int start){
    //기저 사례: LIS의 길이가 1인 경우
    if(lis(start) == 1) return 1;
    //메모이제이션
    int& ret = cacheCnt[start + 1];
    if(ret != -1) return ret;
    ret = 0;
    for(int next = start + 1; next < n; ++next){
        if((start == -1 || S[start] < S[next]) && lis(start) == lis(next) + 1)
        ret = min <long long>(MAX, (long long)ret + count(next));
    }
    return ret;
}