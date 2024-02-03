#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>
#include <string>
#include <cmath>

//필수 조건: n은 자연수
//1 + 2 + ... + n을 반환한다.
int fastSum(int n){
    //기저 사례
    if(n == 1) return 1;
    if(n % 2 == 1) return fastSum(n - 1) + n;
    return 2 * fastSum(n / 2) + (n / 2) * (n / 2);
}

//정방행렬을 표현하는 SquareMatrix 클래스가 있다고 가정하자.
class SquareMatrix;
//n * n 크기의 항등 행렬(identity matrix)을 반환하는 함수
SquareMatrix identity(int n);
//A ^ m 을 반환한다.
SquareMatrix pow(const SquareMatrix& A, int m){
    //기저 사례: A ^ 0 = I;
    if(m == 0) return identity(A.size());
    if(m % 2 > 0) return pow(A, m - 1) * A;
    SquareMatrix half = pow(A, m / 2);
    //A ^ m = (A ^ (m / 2) * (A ^ (m / 2))
    return half * half;
}

//num[]의 자릿수 올림을 처리한다.
void normalize(vector<int>& num){
    num.push_back(0);
    //자릿수 올림을 처리한다.
    for(int i = 0; i + 1 < num.size(); ++i){
        if(num[i] < 0){
            int borrow = (abs(num[i]) + 9) / 10;
            num[i + 1] -= borrow;
            num[i] += borrow * 10;
        }
        else{
            num[i + 1] += num[i] / 10;
            num[i] %= 10;
        }
    }
    while(num.size() > 1 && num.back() == 0) num.pop_back();
}
//두 긴 자연수의 곱을 반환한다.
//각 배열에는 각 수의 자릿수가 1의 자리에서부터 시작해 저장되어 있다.
//예: multiply({3, 2, 1}, {6, 5, 4}) = 123 * 456 = 56088 = {8, 8, 0, 6, 5}
vector<int> multiply(const vector<int>& a, const vector<int>& b){
    vector<int> c(a.size() + b.size() + 1, 0);
    for(int i = 0; i < a.size(); ++i)
        for(int j = 0; j < b.size(); ++j)
            c[i + j] += a[i] * b[j];
    normalize(c);
    return c;
}

//카라츠바 알고리즘
//a += b * (10 ^ k);를 구현한다.
void addTo(vector<int>& a, const vector<int>& b, int k);
//a -= b;를 구현한다. a >= b를 가정한다.
void subFrom(vector<int>& a, const vector<int>& b);
//두 긴 정수의 곱을 반환한다.
vector<int> karatsuba(const vector<int>& a, const vector<int>& b){
    int an = a.size(), bn = b.size();
    //a가 b보다 짧을 경우 둘을 바꾼다.
    if(an < bn) return karatsuba(b, a);
    //기저 사례: a나 b가 비어 있는 경우
    if(an == 0 || bn == 0) return vector<int>();
    //기저 사례: a가 비교적 짧은 경우 O(n ^ 2)곱셈으로 변경한다.
    if(an <= 50) return multiply(a, b);
    int half = an / 2;
    //a와 b를 밑에서 half 자리와 나머지로 분리한다.
    vector<int> a0(a.begin(), a.begin() + half);
    vector<int> a1(a.begin() + half, a.end());
    vector<int> b0(b.begin(), b.begin() + min<int>(b.size(), half));
    vector<int> b1(b.begin() + min<int>(b.size(), half), b.end());
    //z2 = a1 * b1
    vector<int> z2 = karatsuba(a1, b1);
    //z0 = a0 * b0
    vector<int> z2 = karatsuba(a0, b0);
    //a0 = a0 + a1; b0 = b0 + b1
    addTo(a0, a1, 0); addTo(b0, b1, 0);
    //z1 = (a0 * b0) - z0 - z2;
    vector<int> z1 = karatsuba(a0, b0);
    subFrom(z1, z0);
    subFrom(z1, z2);
    //ret = z0 + z1 * 10 ^ half + z2 * 10 ^ (half * 2)
    vector<int> ret;
    addTo(ret, z0, 0);
    addTo(ret, z1, half);
    addTo(ret, z2, half + half);
    return ret;
}

char decompressed[MAX_SIZE][MAX_SIZE];
//s를 압축 해제해서 decompressed[y..y + size - 1][x..x + size - 1] 구간에 쓴다.
void decompress(const string::iterator& it, int y, int x, int size){
    //한 글자를 검사할 때마다 반복자를 한 칸 앞으로 옮긴다.
    char head = *(it++);
    //기저 사례: 첫 글자가 'b' 혹은 'w'인 경우
    if(head == 'b' || head == 'w'){
        for(int dy = 0; dy < size; ++dy)
            for(int dx = 0; dx < size; ++dx)
                decompressed[y + dy][x + dx] = head;
    }
    else{
        //네 부분을 각각 순서대로 압축 해제한다.
        int half = size / 2;
        decompress(it, y, x, half);
        decompress(it, y, x + half, half);
        decompress(it, y + half, x, half);
        decompress(it, y + half, x + half, half);
    }
}

string reverse(string::iterator& it){
    char head = *it;
    ++it;
    if(head == 'b' || head == 'w')
        return string(1, head);
    string upperLeft = reverse(it);
    string upperRight = reverse(it);
    string lowerLeft = reverse(it);
    string lowerRight = reverse(it);
    //각각 위와 아래 조각들의 위치를 바꾼다.
    return string("x") + lowerLeft + lowerRight + upperLeft + upperRight;
}

//판자의 높이를 담은 배열 h[]가 주어질 때 사각형의 넓이의 최대 너비를 반환한다.
int bruteForce(const vector<int>& h){
    int ret = 0;
    int N = h.size();
    for(int left = 0; left < N; ++left){
        int minHeight = h[left];
        for(int right = left; right < N; ++right){
            minHeight = min(minHeight, h[right]);
            ret = max(ret, (right - left + 1) * minHeight);
        }
    }
    return ret;
}

