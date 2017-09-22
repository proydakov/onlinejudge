#include <set>
#include <vector>
#include <sstream>
#include <iostream>
#include <algorithm>

void solve(const std::string& buffer)
{
    std::stringstream sstream;
    sstream << buffer;

    std::vector<int> vec;
    vec.reserve(1024);

    bool skip = 0;
    while(!sstream.eof()) {
        int num;
        sstream >> num;

        if(!skip) {
            skip = true;
            continue;
        }

        vec.push_back(num);
    }

    std::set<int> set;
    for(int i = 1; i < vec.size(); i++) {
        int diff = std::abs(vec[i] - vec[i - 1]);
        set.insert(diff);
    }

    for(int i = 1; i < vec.size(); i++) {
        int count = set.count(i);
        if(0 == count) {
            std::cout << "Not jolly" << std::endl;
            return;
        }
    }

    std::cout << "Jolly" << std::endl;
}

int main()
{
    std::ios::sync_with_stdio(false);

    for (int i = 0; !std::cin.eof(); i++) {
        std::string buffer;
        std::getline(std::cin, buffer);
        if(buffer.empty()) {
            break;
        }
        solve(buffer);
    }

    return 0;
}
