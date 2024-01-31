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