#include <set>
#include <queue>
#include <vector>
#include <iostream>
#include <unordered_map>

void solve(int index, int count)
{
    std::unordered_map<std::string, std::vector<std::string>> graph;

    for(int i = 0; i < count; i++) {
        std::string name;
        std::cin >> name;
        graph[name] = std::vector<std::string>();
    }

    int edges;
    std::cin >> edges;

    for(int i = 0; i < edges; i++) {
        std::string name1;
        std::string name2;

        std::cin >> name1;
        std::cin >> name2;

        graph[name1].push_back(name2);
        graph[name2].push_back(name1);
    }

    std::set<std::string> cameras;

    for(const auto& item : graph) {
        std::set<std::string> visited;
        std::queue<std::string> queue;

        const std::string begin_name = graph.begin()->first;
        if(item.first == begin_name) {
            auto it = graph.begin(); ++it;
            queue.push(it->first);
        }
        else {
            queue.push(begin_name);
        }

        while(!queue.empty()) {
            std::string from = queue.front();
            queue.pop();

            // skip city
            if(from == item.first) {
                continue;
            }

            if(visited.count(from) > 0) {
                continue;
            }

            visited.insert(from);

            for(const auto& city : graph[from]) {
                queue.push(city);
            }
        }

        if((visited.size() + 1) != graph.size()) {
            cameras.insert(item.first);
        }
    }

    std::cout << "City map #" << index << ": " << cameras.size() << " camera(s) found" << std::endl;
    for(const auto& camera : cameras) {
        std::cout << camera << std::endl;
    }
}

int main()
{
    std::ios::sync_with_stdio(false);

    int c;

    for(int i = 1; std::cin >> c, c; i++) {
        if(i > 1) {
            std::cout << std::endl;
        }
        solve(i, c);
    }

    return 0;
}
