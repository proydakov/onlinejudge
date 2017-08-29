#include <cstdint>
#include <iostream>

int main()
{
    std::ios::sync_with_stdio(false);

    size_t n;
    std::cin >> n;

    for(size_t i = 0; i < n; i++) {
        int64_t a; int64_t b;
        std::cin >> a;
        std::cin >> b;

        if(a < b) {
            std::cout << '<' << std::endl;
        }
        else if(a > b) {
            std::cout << '>' << std::endl;
        }
        else {
            std::cout << '=' << std::endl;
        }
    }

    return 0;
}
