#include <set>
#include <queue>
#include <string>
#include <vector>
#include <iostream>
#include <unordered_map>

std::vector<std::string> extract(const std::string& buffer)
{
    std::vector<std::string> names;

    std::string name;
    name.reserve(64);

    int counter = 0;
    for(int i = 0; i < buffer.size(); i++) {
        const char c = buffer[i];

        switch(c) {
            case ':':
            case ',':
                counter++;
                break;
        }

        name.push_back(c);

        if(counter == 2) {
            counter = 0;
            name.resize(name.size() - 1);
            names.push_back(name);
            name.resize(0);
            i++;
        }
    }

    return names;
}

void solve()
{
    // read params
    int edges; int nodes;

    std::cin >> edges;
    std::cin >> nodes;

    {
        std::string temp;
        std::getline(std::cin, temp);
    }

    // read graph
    std::unordered_map<std::string, std::set<std::string>> graph;
    graph.reserve(nodes);

    for(int i = 0; i < edges; i++) {
        std::string buffer;
        std::getline(std::cin, buffer);
        std::vector<std::string> names = extract(buffer);
        for(const auto& name1 : names) {
            for(const auto& name2 : names) {
                if(name1 == name2) {
                    continue;
                }
                graph[name1].insert(name2);
            }
        }
    }

    // solve
    std::unordered_map<std::string, int> solution;
    solution.reserve(nodes);

    std::queue<std::pair<std::string, int>> queue;
    queue.push(std::make_pair("Erdos, P.", 0));

    while(!queue.empty()) {
        const auto item = queue.front();
        queue.pop();

        auto it = solution.find(item.first);
        if(it != solution.end()) {
            continue;
        }

        solution[item.first] = item.second;

        auto graph_it = graph.find(item.first);
        if(graph_it == graph.end()) {
            continue;
        }

        for(const auto& name : graph_it->second) {
            queue.push(std::make_pair(name, item.second + 1));
        }
    }

    // output
    for(int i = 0; i < nodes; i++) {
        std::string vertex;
        std::getline(std::cin, vertex);

        std::cout << vertex << ' ';
        auto it = solution.find(vertex);
        if(it == solution.end()) {
            std::cout << "infinity";
        }
        else {
            std::cout << it->second;
        }
        std::cout << std::endl;
    }
}

int main()
{
    std::ios::sync_with_stdio(false);

    int n = 0;
    std::cin >> n;

    for(int i = 1; i <= n; i++) {
        std::cout << "Scenario " << i << std::endl;
        solve();
    }

    return 0;
}
