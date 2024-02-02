#include <vector>
#include <iostream>
#include <limits>

//필수 조선: n >= 1
//결과: 1부터 n까지의 합을 반환한다.
int sum(int n){
    int ret = 0;
    for(int i = 1; i <= n; ++i){
        ret += i;
    }
    return ret;
}

//필수 조건: n <>= 1
//결과: 1부터 n까지의 합을 반환한다.
int recursiveSum(int n){
    if(n == 1) return 1;
    return n + recursiveSum(n - 1);
}

//n: 전체 원소의 수
//picked: 지금까지 고른 원소들의 번호
//toPick: 더 고를 원소의 수
//일 때, 앞으로 toPick개의 원소를 고르는 모든 방법을 출력한다.
void pick(int n, vector<int>& picked, int toPick){
    //기저 사례: 더 고를 원소가 없을 때 고른 원소들을 출력한다.
    if(toPick == 0) {printPicked(picked); return;}
    //고를 수 있는 가장 작은 번호를 계산한다.
    int smallest = picked.empty() ? 0 : picked.back() + 1;
    //이 단계에서 원소 하나를 고른다.
    for(int next = smallest; next < n; ++next){
        picked.push_back(next);
        pick(n, picked, toPick - 1);
        picked.pop_back();
    }
}

const int dx[8] = {-1, -1, -1, 1, 1, 1, 0, 0};
const int dx[8] = {-1, 0, 1, -1, 0, 1, -1, 1};
// 5x5의 보글 게임 판의 해당 위치에서 주어진 단어가 시작하는지를 반환.
bool hasWord(int y, int x, const string& word){
    //기저 사례1: 시작 위치가 범위 밖이면 무조건 실패
    if(!inRange(y, x)) return false;
    //기저 사례2: 첫 글자가 일치하지 않으면 실패
    if(board[y][x] != word[0]) return false;
    //기저 사례3: 단어 길이가 1이면 성공
    if(word.size() == 1) return true;
    //인접한 8칸을 검사한다.
    for(int direction = 0; direction < 8; ++direction){
        int nextY = y + dy[direction], nextX = x + dx[direction];
        //다음 칸이 범위 안에 있는지, 첫 글자는 일치하는지 확인할 필요가 없다.
        if(hasWord(nextY, nextX, word.substr(1)))
            return true;
    }
    return false;
}

//잘못된 재귀 호출의 예
int n;
bool areFriends[10][10];
//taken[i] = i번째 학생이 짝을 이미 찾았으면 true, 아니면 false
int countPairings(bool taken[10]){
    //기저 사례: 모든 학생이 짝을 찾았으면 한 가지 방법을 찾았으니 종료한다.
    bool finished = true;
    for(int i = 0; i < n; ++i) if(!taken[i]) finished = false;
    if(finished) return 1;
    int ret = 0;
    // 서로 친구인 두 학생을 찾아 짝을 지어 준다.
    for(int i = 0; i < n; ++i)
        for(int j = 0; j < n; ++j)
            if(!taken[i] && !taken[j] && areFriends[i][j]){
                taken[i] = taken[j] = true;
                ret += countPairings(taken);
                taken[i] = taken[j] = false;
            }
    return ret;
}

//소풍 문제를 해결하는 재귀 호출 코드

int n;
bool areFriends[10][10];
//taken[i] = i번째 학생이 짝을 이미 찾았으면 true, 아니면 false
int countPairings(bool taken[10]){
    //남은 학생 중 가장 번호가 빠른 학생을 찾는다.
    int firstFree = -1;
    for(int i = 0; i < n; ++i){
        if(!taken[i]){
            firstFree = i;
            break;
        }
    }
    //기저 사례: 모든 학생이 짝을 찾았으면 한 가지 방법을 찾았으니 종료한다.
    if(firstFree == -1) return 1;
    int ret = 0;
    //이 학생과 짝지을 학생을 결정한다.
    for(int pairWith = firstFree + 1; pairWith < n; ++pairWith){
        if(!taken[pairWith] && areFriends[firstFree][pairWith]){
            taken[firstFree] = taken[pairWith] = true;
            ret += countPairings(taken);
            taken[firstFree] = taken[pairWith] = false;
        }
    }
}

//주어진 칸을 덮을 수 있는 네 가지 방법
//블록을 구성하는 세 칸의 상대적 위치 (dy, dx)의 목록(그림 6.3 참조)
const int coverType[4][3][2] = {
    {{0, 0}, {1, 0}, {0, 1}}; // ㄱ의 y축 대칭
    {{0, 0}, {0, 1}, {1, 1}}; // ㄱ
    {{0, 0}, {1, 0}, {1, 1}}; //ㄴ
    {{0, 0}, {1, 0}, {1, -1}}; //ㄴ의 y축 대칭
}

//board의 (y, x)를 type번 방법으로 덮거나, 덮었던 블록을 없앤다.
//delta = 1이면 덮고, -1이면 덮었던 블록을 없앤다.
//만약 블록이 제대로 덮이지 않은 경우 (게임판 밖으로 나가거나, 겹치거나, 검은 칸을 덮을 때) false를 반환한다.
bool set(vector<vector<int>>& board, int y, int x, int type, int delta){
    bool ok = true;
    for(int i = 0; i < 3; ++i){
        const int ny = y + coverType[type][i][0];
        const int nx = x + coverType[type][i][1];
        if(ny < 0 || ny >= board.size() || nx < 0 || nx >= board[0].size()) //게임판 범위를 넘어섰을때
            ok = false;
        else if((board[ny][nx] += delta) > 1) // 겹칠때
            ok = false;
    }
    return ok;
}

//board의 모든 빈 칸을 덮을 수 있는 방법의 수를 반환한다.
//board[i][j] = 1 이미 덮인 칸 혹은 검은 칸
//board[i][j] = 0 아직 덮이지 않은 칸
int cover(vector<vector<int>>& board){
    //아직 채우지 못한 칸 중 가장 윗줄 왼쪽에 있는 칸을 찾는다.
    int y = -1, x = -1;
    for(int i = 0; i < board.size(); ++i){
        for(int j = 0; j < board[i].size(); ++j)
            if(board[i][j] == 0){
                y = i;
                x = j;
                break;
            }
        if(y != -1) break;
    }
    //기저 사례: 모든 칸을 채웠으면 1을 반환한다.
    if(y == -1) return 1;
    int ret = 0;
    for(int type = 0; type < 4; ++type){
        //만약 board[y][x]를 type 형태롤 덮을 수 있으면 재귀 호출한다.
        if(set(board, y, x, type, 1))
            ret += cover(board);
        //덮었던 블록을 치운다.
        set(board, y, x, type, -1);
    }
    return ret;
}

int n; // 도시의 수
double dist[MAX][MAX]; // 두 도시간의 거리를 저장하는 배열
//path: 지금까지 만든 경로
//visited: 각 도시의 방문 여부
//currentLength: 지금까지 만든 경로의 길이
//나머지 도시들을 모두 방문하는 경로들 중 가장 짧은 것의 길이를 반환한다.
int shortestPath(vector<int>& path, vector<bool>& visited, double currentLength){
    //기저 사례: 모든 도시를 다 방문했을 때는 시작 도시로 돌아가고 종료한다.
    if(path.size() == n)
        return currentLength + dist[path[0]][path.back()];
    double ret = INF; // 매우 큰 값으로 초기화
    //다음 방문할 도시를 전부 시도해 본다.
    for(int next = 0; next < n; ++next){
        if(visited[next]) continue;
        int here = path.back();
        path.push_back(next);
        visited[next] = true;
        //나머지 경로를 재귀 호출을 통해 완성하고 가장 짧은 경로의 길이를 얻는다.
        double cand = shortestPath(path, visited, currentLength + dist[here][next]);
        ret = min(ret, cand);
        visited[next] = false;
        path.pop_back();
    }
    return ret;
}

const int INF = 9999, SWITCHES = 10, CLOCKS = 16;
//linked[i][j] = 'x': i번 스위치와 j번 시계가 연결되어 있다.
//linked[i][j] = '.': i번 스위치와 j번 시계가 연결되어 있지 않다.
const char linked[SWITCHES][CLOCKS + 1] = {
    "xxx.............",
    "...x...x.x.x....",
    "....x.....x...xx",
    "x...xxxx........",
    "......xxx.x.x...",
    "x.x...........xx",
    "...x..........xx",
    "....xx.x......xx",
    "xxxxx...........",
    "...xxx...x...x.."
};
//모든 시계가 12시를 가리키고 있는지 확인
bool areAligned(const vector<int>& clocks);
//swtch번 스위치를 누른다.
void push(vector<int>& clocks, int swtch){
    for(int clock = 0; clock < CLOCKS; ++clock)
        if(linked[swtch][clock] == 'x'){
            clocks[clock] += 3;
            if(clocks[clock] == 15) clocks[clock] = 3;
        }
}
//clocks. 현재 시계들의 상태
//swtch: 이번에 누를 스위치의 번호
//가 주어질 때, 남은 스위치들을 눌러서 clocks를 12시로 맞출 수 있는 최소 횟수를 반환한다.
//만약 불가능하다면 INF 이상의 큰 수를 반환한다.
int solve(vector<int>& clocks, int swtch){
    if(swtch == SWITCHES) return areAligned(clocks) ? 0 : INF;
    //이 스위치를 0번 누르는 경우부터 세 번 누르는 경우까지를 모두 시도한다.
    int ret = INF;
    for(int cnt = 0; cnt < 4; ++cnt){
        ret = min(ret, cnt + solve(clocks, swtch + 1));
        push(clocks, swtch);
    }
    //push(clocks, swtch)가 네 번 호출되었으니 clocks는 원래와 같은 상태가 된다.
    return ret;
}