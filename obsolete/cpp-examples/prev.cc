// g++ -std=c++11 prev.cc 

#include <iostream>
#include <iterator>
#include <vector>
 
int main() 
{
    // std::vector<int> v{ 3, 1, 4 };
    std::vector<int> v{};
 
    auto it = v.end();
 
    auto last =  std::prev(v.end());

    std::cout << "START" << '\n';
    if (last) {
        std::cout << "EQUAL" << '\n';
    }
    for (auto it = v.begin(); it != last; ++it) {
        std::cout << *it << "|";
    }
 
    std::cout << "TOTO" << '\n';
}
