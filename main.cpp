#include <iostream>
#include <vector>
#include "main.h"
#include <cstdlib>
#include <ctime>

int main()
{

    srand(time(NULL));
    char a;
    int tmp;

    std::vector<Node> unique;
    std::vector<std::string> prev_turns;
    std::vector<int> random_numbers;

    int index = 0;

    // E
    Node n(1, 1, 3);
    Node n1(2, 2, 3);
    Node n2(3, 3, 3);
    Node n3(9, 1, 2);
    Node n4(4, 2, 2);
    Node n5(6, 3, 2);
    Node n6(7, 1, 1);
    Node n7(5, 2, 1);
    Node n8(8, 3, 1);

    // BATGIRL
    /*Node n(2, 1, 3);
    Node n1(6, 2, 3);
    Node n2(3, 3, 3);
    Node n3(8, 1, 2);
    Node n4(1, 2, 2);
    Node n5(5, 3, 2);
    Node n6(4, 1, 1);
    Node n7(9, 2, 1);
    Node n8(7, 3, 1);*/

    // EVOSOFT
    /* Node n(8, 1, 3);
     Node n1(9, 2, 3);
     Node n2(5, 3, 3);
     Node n3(2, 1, 2);
     Node n4(3, 2, 2);
     Node n5(7, 3, 2);
     Node n6(4, 1, 1);
     Node n7(1, 2, 1);
     Node n8(6, 3, 1); */

    // HOW-TO-SOLVE
    /*Node n(1, 1, 3);
    Node n1(5, 2, 3);
    Node n2(2, 3, 3);
    Node n3(9, 1, 2);
    Node n4(3, 2, 2);
    Node n5(6, 3, 2);
    Node n6(7, 1, 1);
    Node n7(8, 2, 1);
    Node n8(4, 3, 1);*/

    /*unique.push_back(n);
    unique.push_back(n1);
    unique.push_back(n2);
    unique.push_back(n3);
    unique.push_back(n4);
    unique.push_back(n5);
    unique.push_back(n6);
    unique.push_back(n7);
    unique.push_back(n8);*/

    int offset = 9;

    // RANDOM CONFIGURATION
    while (random_numbers.size() != 9)
    {
        tmp = 1 + rand() % 9;
        if (!count(random_numbers.begin(), random_numbers.end(), tmp))
            random_numbers.push_back(tmp);
    }

    for (int j = 3; j > 0; j--)
    {
        for (int k = 3; k > 0; k--)
        {
            unique.push_back(Node(random_numbers[index++], j, k));
        }
    }

    Calculate_Manhattan_distance(unique, offset);

    Node::Set_f(Node::Get_h());

    prev_turns = Solve(unique, "", prev_turns, offset);

    if (!prev_turns.empty())
    {
        std::cout << "DEBUG Ended." << std::endl;

        int ind = GetNode(unique, offset);

        Display(unique, offset);

        for (int i = 0; i < prev_turns.size(); i++)
        {
            int ind = GetNode(unique, offset);
            Turn(unique, offset, ind, prev_turns[i]);
            Display(unique, offset);
        }
    }
    else
    {
        std::cout << "No solution found." << std::endl;
    }

    std::cin >> a;

    return 0;
}