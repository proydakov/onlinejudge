#include <limits>
#include <vector>
#include <iostream>
#include <algorithm>

class solver
{
private:
    struct node
    {
        int to;
        int cost;
    };

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

        rec_solve(from_, std::numeric_limits<int>::max(), cache);

        min_length_ = min_length_ - 1;

        int solution = count_ / min_length_;
        if(count_ % min_length_ > 0) {
            solution++;
        }

        return solution;
    }

private:
    void rec_solve(int vertex, int cost, std::vector<int> cache)
    {
        if(cache[vertex] != 0 || cost <= min_length_) {
            return;
        }

        cache[vertex] = 1;

        if(vertex == to_) {
            min_length_ = std::max(min_length_, cost);
            return;
        }

        for(const auto item : graph_[vertex]) {
            rec_solve(item.to, std::min(item.cost, cost), cache);
        }
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
