#include <vector>
#include <cstdint>
#include <iostream>
#include <algorithm>

void solve()
{
    size_t n;
    std::cin >> n;

    std::vector<int64_t> data(n, 0);
    for(size_t i = 0; i < n; i++) {
        std::cin >> data[i];
    }
    std::sort(data.begin(), data.end());

    int64_t nth_element = 0;
    if(n % 2 == 1) {
        nth_element = data[n / 2];
    }
    else {
        size_t index_2 = n / 2;
        size_t index_1 = index_2 - 1;
        nth_element = (data[index_2] + data[index_1]) / 2;
    }

    int64_t acc = 0;
    for(size_t i = 0; i < n; i++) {
        acc += std::abs(nth_element - data[i]);
    }
    std::cout << acc << std::endl;
}

int main()
{
    std::ios::sync_with_stdio(false);

    size_t n;
    std::cin >> n;

    for(size_t i = 0; i < n; i++) {
        solve();
    }

    return 0;
}
