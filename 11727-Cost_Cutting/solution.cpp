#include <vector>
#include <iostream>
#include <algorithm>

int main()
{
    std::ios::sync_with_stdio(false);

    size_t n;
    std::cin >> n;

    for(size_t i = 0; i < n; i++) {
        std::vector<int> array(3, 0);
        std::cin >> array[0];
        std::cin >> array[1];
        std::cin >> array[2];

        std::sort(array.begin(), array.end());

        std::cout << "Case " << (i + 1) << ": " << array[1] << std::endl;
    }

    return 0;
}
