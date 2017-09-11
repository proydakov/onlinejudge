#include <queue>
#include <vector>
#include <iostream>

std::vector<int> read_vec4()
{
    std::vector<int> vec(4, 0);
    for(int i = 0; i < 4; i++) {
        std::cin >> vec[i];
    }
    return vec;
}

int vec2num(const std::vector<int>& vec)
{
    int num = 0;
    for(int i = 3, k = 1; i > -1; i--, k *= 10) {
        num += k * vec[i];
    }
    return num;
}

void solve()
{
    std::vector<int> from = read_vec4();
    std::vector<int> to   = read_vec4();

    const int from_num = vec2num(from);
    const int to_num = vec2num(to);

    int n;
    std::cin >> n;

    std::vector<int> cache(10000, 0);
    for(int i = 0; i < n; i++) {
        std::vector<int> vec = read_vec4();
        int num = vec2num(vec);
        cache[num] = -1;
    }
    cache[from_num] = 0;

    int solution = -1;

    std::queue< std::pair<std::vector<int>, int> > queue;
    queue.push( std::make_pair( from, 0 ) );

    while(!queue.empty()) {
        std::pair<std::vector<int>, int> item = queue.front();
        queue.pop();

        int item_num = vec2num(item.first);
        if(cache[item_num] != 0) {
            continue;
        }

        cache[item_num] = 1;

        const int curr = item.second;
        const int next = item.second + 1;

        if(item_num == to_num) {
            solution = curr;
            break;
        }

        for(int i = 0; i < 4; i++) {
            auto copy(item.first);
            copy[i] = (copy[i] + 1) % 10;
            queue.push(std::make_pair(copy, next));
        }

        for(int i = 0; i < 4; i++) {
            auto copy(item.first);
            copy[i] = (copy[i] - 1 + 10) % 10;
            queue.push(std::make_pair(copy, next));
        }
    }

    std::cout << solution << std::endl;
}

int main()
{
    std::ios::sync_with_stdio(false);

    int n;
    std::cin >> n;

    for(int i = 0; i < n; i++) {
        solve();
    }

    return 0;
}
