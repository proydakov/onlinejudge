#include <map>
#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <algorithm>

void solve()
{
    int n;
    std::cin >> n;

    {
        std::string buffer;
        std::getline(std::cin, buffer);
    }

    std::map<int, std::string> candidates;
    for(int i = 1; i <= n; i++) {
        std::string buffer;
        std::getline(std::cin, buffer);
        candidates.insert(std::make_pair(i, buffer));
    }

    std::vector<std::vector<int>> votes;
    for (int i = 0; !std::cin.eof(); i++) {
        std::string buffer;
        std::getline(std::cin, buffer);
        if(buffer.empty()) {
            break;
        }
        std::stringstream sstream;
        sstream << buffer;

        std::vector<int> ids(n);
        for(int j = 0; j < n; j++) {
            int id;
            sstream >> id;
            ids[j] = id;
        }

        votes.push_back( std::move(ids) );
    }

    while(true) {
        std::map<int, int> scores;

        for(const auto& candidate : candidates) {
            scores[candidate.first] = 0;
        }

        for(const auto& ids : votes) {
            scores[ids.front()]++;
        }

        int min = votes.size() * 2;
        int max = 0;
        int max_id = -1;

        for(const auto& score : scores) {
            if(score.second > max) {
                max = score.second;
                max_id = score.first;
            }
            if(score.second < min) {
                min = score.second;
            }
        }

        if(max * 2 > votes.size()) {
            std::cout << candidates[max_id] << std::endl;
            break;
        }

        if(min == max) {
            for(const auto candidate : candidates) {
                std::cout << candidate.second << std::endl;
            }
            break;
        }

        for(auto score_it = scores.begin(), end_it = scores.end(); score_it != end_it;) {
            if(score_it->second == min) {
                const int remove_id = score_it->first;
                candidates.erase(remove_id);

                for(auto& ids : votes) {
                    auto vec_it = std::remove(ids.begin(), ids.end(), remove_id);
                    ids.erase(vec_it, ids.end());
                }
                score_it = scores.erase(score_it);
            }
            else {
                ++score_it;
            }
        }
    }
}

int main()
{
    std::ios::sync_with_stdio(false);

    int n;
    std::cin >> n;

    for(int i = 0; i < n; i++) {
        if(i > 0) {
            std::cout << std::endl;
        }
        solve();
    }

    return 0;
}
