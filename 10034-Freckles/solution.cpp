#include <cmath>
#include <vector>
#include <limits>
#include <iomanip>
#include <iostream>

template<class T>
struct point_t
{
    T x;
    T y;
};

template<class T>
T calc_dist(const point_t<T>& p1, const point_t<T>& p2)
{
    const T dx = p1.x - p2.x;
    const T dy = p1.y - p2.y;
    const T result = std::sqrt( dx * dx + dy * dy );
    return result;
}

template<class T>
T solve(const std::vector<std::vector<T>>& adjacency_matrix, int start_node)
{
    const auto INF = std::numeric_limits<int>::max();

    const size_t n = adjacency_matrix.size();

    std::vector<int> used     (n, 0  );
    std::vector<T>   min_dist (n, INF);
    std::vector<int> dest_node(n, -1 );

    min_dist[start_node] = 0;

    T sum = 0;

    for(size_t i = 0; i < n; i++) {
        int v = -1;

        for(int j = 0; j < n; j++) {
            if(!used[j] && (v == -1 || min_dist[j] < min_dist[v])) {
                v = j;
            }
        }

        if(min_dist[v] == INF) {
            throw std::runtime_error("invalid adjacency_matrix");
        }

        used[v] = 1;

        if (dest_node[v] != -1) {
            sum += min_dist[v];
            //std::cout << "link: "  << char('A' + dest_node[v])
            //          << " -> "    << char('A' + v)
            //          << " cost: " << min_dist[v]
            //          << std::endl;
        }

        for(size_t to = 0; to < n; to++) {
            const T test_dist = adjacency_matrix[v][to];
            if (test_dist < min_dist[to]) {
                min_dist [to] = test_dist;
                dest_node[to] = v;
            }
        }
    }

    return sum;
}

void solve()
{
    // read input

    int n;
    std::cin >> n;

    std::vector<point_t<double>> vector;
    vector.reserve(n);

    for(int i = 0; i < n; i++) {
        point_t<double> point;
        std::cin >> point.x;
        std::cin >> point.y;

        vector[i] = point;
    }

    // build adjacency_matrix

    std::vector<std::vector<double>> adjacency_matrix;
    adjacency_matrix.resize(n, std::vector<double>(n, 0));

    for(int i = 0; i < n; i++) {
        for(int j = i; j < n; j++) {
            double dist = calc_dist(vector[i], vector[j]);
            adjacency_matrix[i][j] = dist;
            adjacency_matrix[j][i] = dist;
        }
    }

    // solve

    double solution = solve(adjacency_matrix, 0);
    int int_solution = solution * 100.0;

    int ost_solution = solution * 1000;
    if(ost_solution % 10 >= 5) {
        int_solution += 1;
    }

    std::cout << (int_solution / 100) << '.' << std::setw(2) << std::setfill('0') << (int_solution % 100) << std::endl;
}

int main()
{
    std::ios::sync_with_stdio(false);

    int c;
    std::cin >> c;

    for(int i = 0; i < c; i++) {
        if(i > 0) {
            std::cout << std::endl;
        }
        solve();
    }

    return 0;
}
