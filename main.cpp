#include <iostream>
#include <vector>
#include "main.h"
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <thread>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

void crossPlatformSleep(int seconds)
{
#ifdef _WIN32
    // Windows implementation
    Sleep(seconds * 1000);
#else
    // Unix-based (Mac and Linux) implementation
    usleep(seconds * 1000000);
#endif
}

int main()
{

    srand(time(NULL));
    char a;
    int tmp;
    int seconds = 1;

    std::vector<Node> unique;
    std::vector<std::string> prev_turns;
    std::vector<int> random_numbers;

    int index = 0;

    int offset = 9;

    while (random_numbers.size() != 9)
    {
        tmp = 1 + rand() % 9;
        if (!count(random_numbers.begin(), random_numbers.end(), tmp))
            random_numbers.push_back(tmp);
    }

    for (int j = 3; 0 < j; j--)
    {
        for (int k = 1; k < 4; k++)
        {
            unique.push_back(Node(random_numbers[index++], k, j));
        }
    }

    Calculate_Manhattan_distance(unique, offset);

    Node::Set_f(Node::Get_h());

    Display(unique, offset);

    prev_turns = Solve(unique, "", prev_turns, offset);

    if (!prev_turns.empty())
    {

        int ind = GetNode(unique, offset);

        for (int i = 0; i < prev_turns.size(); i++)
        {
            int ind = GetNode(unique, offset);
            Turn(unique, offset, ind, prev_turns[i]);
            Display(unique, offset);
            crossPlatformSleep(seconds);
        }
    }
    else
    {
        std::cout << "No solution found." << std::endl;
    }

    // std::cin >> a;

    return 0;
}