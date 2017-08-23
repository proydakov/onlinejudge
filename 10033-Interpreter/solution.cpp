#include <string>
#include <vector>
#include <iostream>

void simulate()
{
    std::string skip;
    std::getline(std::cin, skip);
    std::getline(std::cin, skip);

    int ip = 0;
    std::vector<int> regs(10, 0);
    std::vector<int> memory(1000, 0);

    for (int i = 0; std::cin.peek() != '\n' && !std::cin.eof(); i++) {
        std::cin >> memory[i];
        char c; std::cin >> c;
    }

    int counter = 0;
    for(; true; counter++) {
        int inst = memory[ip];

        std::cout << "ip: " << ip << std::endl;

        if(100 == inst) {
            break;
        }

        const int cmd = inst / 100;
        const int op1 = inst % 100 / 10;
        const int op2 = inst % 10;

        switch(cmd) {
            case 2:
            {
                regs[op1] = op2;
            }
            break;

            case 3:
            {
                regs[op1] += op2;
                regs[op1] %= 1000;
            }
            break;

            case 4:
            {
                regs[op1] *= op2;
                regs[op1] %= 1000;
            }
            break;

            case 5:
            {
                regs[op1] = regs[op2];
            }
            break;

            case 6:
            {
                regs[op1] += regs[op2];
                regs[op1] %= 1000;
            }
            break;

            case 7:
            {
                regs[op1] *= regs[op2];
                regs[op1] %= 1000;
            }
            break;

            case 8:
            {
                regs[op1] = memory[regs[op2]];
            }
            break;

            case 9:
            {
                memory[regs[op2]] = regs[op1];
            }
            break;

            case 0:
            {
                if(0 != regs[op2]) {
                    ip = regs[op1];
                }
            }
            break;
        }

        ip++;
    }

    std::cout << counter << std::endl;
}

int main()
{
    std::ios::sync_with_stdio(false);

    int count;
    std::cin >> count;

    simulate();

    return 0;
}
