#include <cmath>
#include <vector>
#include <iomanip>
#include <iostream>
#include <algorithm>

void solve(int N)
{
    std::vector<int> students(N, 0);

    int sum = 0;
    for (int i = 0; i < N; ++i)
    {
        int dollar; char dot; int cent;
        std::cin >> dollar >> dot >> cent;
        students[i] = dollar * 100 + cent;
        sum += students[i];
    }

    int lowAverage = sum / N;
    int highAverage = lowAverage + ((sum % N) ? 1 : 0);

    int sumAbove = 0;
    for (int i = 0; i < N; ++i)
    {
        if (students[i] > highAverage)
            sumAbove += students[i] - highAverage;
    }

    int sumBelow = 0;
    for (int i = 0; i < N; ++i)
    {
        if (students[i] < lowAverage)
            sumBelow += lowAverage - students[i];
    }

    int ansSum = std::max(sumAbove, sumBelow);

    std::cout << '$' << (ansSum / 100) << '.' << std::setw(2) << std::setfill('0') << (ansSum % 100) << '\n';
}

int main()
{
    std::ios::sync_with_stdio(false);

    int N;

    while (std::cin >> N, N)
    {
        solve(N);
    }

    return 0;
}
