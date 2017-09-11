#include <set>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

int main()
{
    std::ios::sync_with_stdio(false);

    std::vector<std::vector<char>> canvas;

    while(true) {
        char command = 'X';
        std::cin >> command;
        if(command == 'X') {
            break;
        }

        switch(command) {
            case 'I':
            {
                int M; int N;
                std::cin >> M;
                std::cin >> N;

                canvas.resize(0);
                canvas.shrink_to_fit();

                canvas = std::vector<std::vector<char>>(N, std::vector<char>(M, 'O'));
            }
            break;

            case 'C':
            {
                for(size_t y = 0; y < canvas.size(); y++) {
                    for(size_t x = 0; x < canvas[0].size(); x++) {
                        canvas[y][x] = 'O';
                    }
                }
            }
            break;

            case 'S':
            {
                std::string name;
                std::cin >> name;

                std::cout << name << std::endl;
                for(size_t y = 0; y < canvas.size(); y++) {
                    for(size_t x = 0; x < canvas[0].size(); x++) {
                        std::cout << canvas[y][x];
                    }
                    std::cout << std::endl;
                }
            }
            break;

            case 'L':
            {
                int X; int Y; char C;
                std::cin >> X;
                std::cin >> Y;
                std::cin >> C;

                canvas[Y - 1][X - 1] = C;
            }
            break;

            case 'V':
            {
                int X; int Y1; int Y2; char C;
                std::cin >> X;
                std::cin >> Y1;
                std::cin >> Y2;
                std::cin >> C;

                X--;
                Y1--;
                Y2--;

                for(int y = std::min(Y1, Y2); y <= std::max(Y1, Y2); y++) {
                    canvas[y][X] = C;
                }
            }
            break;

            case 'H':
            {
                int X1; int X2; int Y; char C;
                std::cin >> X1;
                std::cin >> X2;
                std::cin >> Y;
                std::cin >> C;

                X1--;
                X2--;
                Y--;

                for(int x = std::min(X1, X2); x <= std::max(X1, X2); x++) {
                    canvas[Y][x] = C;
                }
            }
            break;

            case 'K':
            {
                int X1; int Y1; int X2; int Y2; char C;
                std::cin >> X1;
                std::cin >> Y1;
                std::cin >> X2;
                std::cin >> Y2;
                std::cin >> C;

                X1--;
                X2--;
                Y1--;
                Y2--;

                for(int y = std::min(Y1, Y2); y <= std::max(Y1, Y2); y++) {
                    for(int x = std::min(X1, X2); x <= std::max(X1, X2); x++) {
                        canvas[y][x] = C;
                    }
                }
            }
            break;

            case 'F':
            {
                int X; int Y; char C;
                std::cin >> X;
                std::cin >> Y;
                std::cin >> C;

                X--;
                Y--;

                const char origin = canvas[Y][X];

                auto copy(canvas);
                for(size_t y = 0; y < copy.size(); y++) {
                    for(size_t x = 0; x < copy[y].size(); x++) {
                        copy[y][x] = 0;
                    }
                }

                std::set<std::pair<int, int>> set;
                set.insert(std::make_pair(X, Y));

                while(!set.empty()) {
                    auto it = set.begin();
                    auto item = *it;
                    set.erase(it);

                    if(item.first < 0 || item.second < 0) {
                        continue;
                    }

                    if(item.first >= copy[0].size() || item.second >= copy.size()) {
                        continue;
                    }

                    if(copy[item.second][item.first] != 0) {
                        continue;
                    }

                    copy[item.second][item.first] = 1;

                    if(origin != canvas[item.second][item.first]) {
                        continue;
                    }

                    std::pair<int, int> p1(item.first - 1, item.second);
                    std::pair<int, int> p2(item.first + 1, item.second);

                    std::pair<int, int> p3(item.first, item.second - 1);
                    std::pair<int, int> p4(item.first, item.second + 1);

                    canvas[item.second][item.first] = C;

                    set.insert(p1);
                    set.insert(p2);
                    set.insert(p3);
                    set.insert(p4);
                }
            }
            break;

            default:
            {
                std::string buffer;
                std::getline(std::cin, buffer);
            }
            break;
        }
    }

    return 0;
}
