#include <iostream>
#include <vector>
#include <main.h>

int main()
{

   // TODO
   // Initialize Random starting position
   // Calculate Manhattan distance (h)

    std::vector<Node> unique;
    std::vector<std::string> prev_turns;

    if (Solve(unique, "", prev_turns))
    {
        std::cout << "Heureka" << std::endl;
    }

    return 0;
}