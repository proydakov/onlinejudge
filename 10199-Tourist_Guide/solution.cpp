#include <set>
#include <queue>
#include <vector>
#include <iostream>
#include <unordered_map>

std::unordered_map<std::string, std::vector<std::string>> read(int count)
{
    std::unordered_map<std::string, std::vector<std::string>> graph;

    //std::cout << "graph graphname {" << std::endl;

    for(int i = 0; i < count; i++) {
        std::string name;
        std::cin >> name;
        graph[name] = std::vector<std::string>();

        //std::cout << "    " << name << ";" << std::endl;
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

        //std::cout << "    " << name1 << " -- " << name2 << ";" << std::endl;
    }

    //std::cout << "}" << std::endl;

    return graph;
}

std::vector<std::vector<std::string>> mark(std::unordered_map<std::string, std::vector<std::string>>& graph)
{
    std::vector<std::vector<std::string>> nodes;

    std::unordered_map<std::string, int> colors;

    for(const auto& item : graph) {
        colors[item.first] = -1;
    }

    int color = 0;
    for(const auto& item : graph) {
        const int test_color = colors[item.first];
        if(-1 == test_color) {
            std::queue<std::string> queue;
            queue.push(item.first);

            while(!queue.empty()) {
                const std::string from = queue.front();
                queue.pop();

                if(colors[from] != -1) {
                    continue;
                }

                colors[from] = color;

                for(const auto& city : graph[from]) {
                    queue.push(city);
                }
            }

            color++;
        }
    }

    nodes.resize(color);
    for(const auto& item : colors) {
        nodes[item.second].push_back(item.first);
    }

    return nodes;
}

std::set<std::string> find(std::unordered_map<std::string, std::vector<std::string>>& graph, std::vector<std::vector<std::string>>& colors)
{
    std::set<std::string> cameras;

    for(const auto& nodes : colors) {
        if(nodes.size() < 3) {
            continue;
        }

        for(const auto& node : nodes) {
            std::set<std::string> visited;
            std::queue<std::string> queue;

            std::string begin_name = nodes.front();
            if(node == begin_name) {
                begin_name = nodes.back();
            }
            queue.push(begin_name);

            while(!queue.empty()) {
                std::string from = queue.front();
                queue.pop();

                // skip city
                if(node == from) {
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

            if((visited.size() + 1) != nodes.size()) {
                cameras.insert(node);
            }
        }
    }

    return cameras;
}

void solve(int index, int count)
{
    std::unordered_map<std::string, std::vector<std::string>> graph = read(count);
    std::vector<std::vector<std::string>> colors = mark(graph);
    std::set<std::string> cameras = find(graph, colors);

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
