#include <queue>
#include <limits>
#include <vector>
#include <iostream>
#include <algorithm>

struct node
{
    int vertex;
    int cost;
};

bool operator<(const node& n1, const node& n2)
{
    return n1.cost < n2.cost;
}

class solver
{
public:
    solver(int n, int r) :
        graph_( std::vector<std::vector<node>>(n + 1) )
    {
        for(int i = 0; i < r; i++) {
            int v1; int v2; int c;
            std::cin >> v1;
            std::cin >> v2;
            std::cin >> c;

            graph_[v1].push_back(node{v2, c});
            graph_[v2].push_back(node{v1, c});
        }

        std::cin >> from_;
        std::cin >> to_;
        std::cin >> count_;
    }

    int solve()
    {
        std::vector<int> cache(graph_.size(), 0);

        std::priority_queue<node, std::vector<node>> heap;
        heap.push(node{from_, std::numeric_limits<int>::max()});

        while(!heap.empty()) {
            auto item = heap.top();
            heap.pop();

            if(cache[item.vertex]) {
                continue;
            }

            if(item.vertex == to_) {
                min_length_ = item.cost;
                break;
            }

            cache[item.vertex] = 1;

            for(const auto& edge : graph_[item.vertex]) {
                heap.push(node{edge.vertex, std::min(edge.cost, item.cost)});
            }
        }

        min_length_ = min_length_ - 1;
        int solution = count_ / min_length_;
        if(count_ % min_length_ > 0) {
            solution++;
        }

        return solution;
    }

private:
    std::vector<std::vector<node>> graph_;
    int from_;
    int to_;
    int count_;
    int min_length_ = 0;
};

int main()
{
    std::ios::sync_with_stdio(false);

    int n; int r;
    std::cin >> n;
    std::cin >> r;

    for(int i = 1; n != 0; i++) {
        solver s(n, r);
        int result = s.solve();

        std::cout << "Scenario #" << i << std::endl;
        std::cout << "Minimum Number of Trips = " << result << std::endl;
        std::cout << std::endl;

        std::cin >> n;
        std::cin >> r;
    }

    return 0;
}
