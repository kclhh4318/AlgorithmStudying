#include <vector>
#include <iostream>

const int INF = 987654321;

bool canEverybodyEat(const vector<int>& menu);

int M;

int selectMenu(vector<int>& menu, int food){
    if(food == M){
        if(canEverybodyEat(menu)) return menu.size();
        return INF;
    }

    int ret = selectMenu(menu, food + 1);
    menu.push_back(food);
    ret = min(ret, selecetMenu(menu, food + 1));
    menu.pop_back();
    return ret;
}