#include <string>
#include <vector>
#include <sstream>
#include <iostream>

void debug(int ip, const std::vector<int>& regs, const std::vector<int>& memory)
{
    std::cout << "\nip: " << ip << std::endl;

    std::cout << "\nregs" << std::endl;
    for(size_t i = 0; i < regs.size(); i++) {
        std::cout << i << ": " << regs[i] << std::endl;
    }

    std::cout << "\nmemory" << std::endl;
    for(size_t i = 0; i < 20; i++) {
        std::cout << i << ": " << memory[i] << std::endl;
    }
}

void simulate()
{
    int ip = 0;
    std::vector<int> regs(10, 0);
    std::vector<int> memory(1000, 0);

    for (int i = 0; !std::cin.eof(); i++) {
        std::string buffer;
        std::getline(std::cin, buffer);
        if(buffer.empty()) {
            break;
        }
        memory[i] = std::stoi(buffer);
    }

    //debug(ip, regs, memory);

    int counter = 1;
    for(; true; counter++) {
        int inst = memory[ip];

        if(100 == inst) {
            break;
        }

        ip++;

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

        //debug(ip, regs, memory);
    }

    std::cout << counter << std::endl;
}

int main()
{
    std::ios::sync_with_stdio(false);

    std::string buffer;
    std::getline(std::cin, buffer);

    int count = std::stoi(buffer);

    std::getline(std::cin, buffer);

    for(int i = 0; i < count; i++) {
        simulate();
        if(i != count - 1) {
            std::cout << std::endl;
        }
    }

    return 0;
}
