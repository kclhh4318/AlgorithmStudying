#include <iostream>

int main(){

    std::cin.tie(0);
    std::ios_base::sync_with_stdio(false);

    std::string str = "Hello world~";

    std::cout << str.substr(1) << std::endl;

    return 0;
}