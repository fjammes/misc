// g++ -std=c++11 std_unique.cc

#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

typedef std::vector<std::string> StringVector;

int main() 
{
    std::vector<std::string> v;
    v.push_back("sum(pm_declerr)");
    v.push_back("f1");
    v.push_back("f1");
    v.push_back("avg(pm_declerr)");

    std::cout << "orig\n";
    for (StringVector::iterator it = v.begin(); it!=v.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << "\n";

    //std::vector<std::string> v{ "a", "f", "f", "s"};
    std::sort(v.begin(), v.end());

    std::cout << "orig\n";
    for (StringVector::iterator it = v.begin(); it!=v.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << "\n";

    std::vector<std::string>::iterator last = std::unique(v.begin(), v.end());

    std::cout << "orig\n";
    for (StringVector::iterator it = v.begin(); it!=v.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << "\n";
/*
    for (auto it = last; it!=v.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << "\n";
*/
}
