#include "iostream"

int main() {
    int x = 0;
    while(std::cin >> x){
        std::cin >> x;
    }

    if(std::cin.eof()){//this is true
        std::cin.clear();
        std::cout << "end of if" << std::endl;//is not visible.
        std::cin >> x;//cin is not working
        return 2;
    }
    std::cout << "end of main" << std::endl;//not researching
    return 1;
}