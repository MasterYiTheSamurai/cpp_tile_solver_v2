#include <iostream>
#include <vector>
#include "main.h"

int main()
{

    std::vector<Node> unique;
    std::vector<std::string> prev_turns;

    Node n(6, 1, 3);
    Node n1(3, 2, 3);
    Node n2(1, 3, 3);
    Node n3(8, 1, 2);
    Node n4(2, 2, 2);
    Node n5(4, 3, 2);
    Node n6(7, 1, 1);
    Node n7(5, 2, 1);
    Node n8(9, 3, 1);

    unique.push_back(n);
    unique.push_back(n1);
    unique.push_back(n2);
    unique.push_back(n3);
    unique.push_back(n4);
    unique.push_back(n5);
    unique.push_back(n6);
    unique.push_back(n7);
    unique.push_back(n8);

    Calculate_Manhattan_distance(unique);

    Node::Set_f(Node::Get_h());

    if (!Solve(unique, "", prev_turns).empty())
    {
        std::cout << "Heureka" << std::endl;
    }

    return 0;
}