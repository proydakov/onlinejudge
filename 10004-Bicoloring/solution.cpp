#include <queue>
#include <iostream>

struct solver
{
    bool solve()
    {
        int count;
        std::cin >> count;

        if(0 == count) {
            done_ = true;
            return true;
        }

        int n;
        std::cin >> n;

        std::vector<std::vector<int>> graph(count);
        for(int i = 0; i < n; i++) {
            int v1; int v2;
            std::cin >> v1;
            std::cin >> v2;

            graph[v1].push_back(v2);
            graph[v2].push_back(v1);
        }

        std::vector<int> color(count, -1);

        std::queue<std::pair<int, int>> queue;
        queue.push(std::make_pair(0, 0));

        while(!queue.empty()) {
            auto front = queue.front();
            queue.pop();

            if(-1 == color[front.first]) {
                color[front.first] = front.second;

                const int next_color = front.second == 0 ? 1 : 0;
                for(const auto item : graph[front.first]) {
                    queue.push(std::make_pair(item, next_color));
                }
            }
            else {
                if(color[front.first] != front.second) {
                    return false;
                }
            }
        }

        return true;
    }

    bool done_ = false;
};

int main()
{
    std::ios::sync_with_stdio(false);

    solver s;

    while(true) {
        bool result = s.solve();
        if(s.done_) {
            break;
        }
        if(result) {
            std::cout << "BICOLORABLE." << std::endl;
        }
        else {
            std::cout << "NOT BICOLORABLE." << std::endl;
        }
    }

    return 0;
}
