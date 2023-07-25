#include <iostream>
#include <vector>
#include "main.h"

int main()
{

    char a;

    std::vector<Node> unique;
    std::vector<std::string> prev_turns;

    int offset = 9;

    // E
    /*Node n(1, 1, 3);
    Node n1(2, 2, 3);
    Node n2(3, 3, 3);
    Node n3(9, 1, 2);
    Node n4(4, 2, 2);
    Node n5(6, 3, 2);
    Node n6(7, 1, 1);
    Node n7(5, 2, 1);
    Node n8(8, 3, 1);*/

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
     Node n(1, 1, 3);
     Node n1(5, 2, 3);
     Node n2(2, 3, 3);
     Node n3(9, 1, 2);
     Node n4(3, 2, 2);
     Node n5(6, 3, 2);
     Node n6(7, 1, 1);
     Node n7(8, 2, 1);
     Node n8(4, 3, 1);


    unique.push_back(n);
    unique.push_back(n1);
    unique.push_back(n2);
    unique.push_back(n3);
    unique.push_back(n4);
    unique.push_back(n5);
    unique.push_back(n6);
    unique.push_back(n7);
    unique.push_back(n8);

    Calculate_Manhattan_distance(unique,offset);

    Node::Set_f(Node::Get_h());

    prev_turns = Solve(unique, "", prev_turns, offset);

    if (!prev_turns.empty())
    {
        std::cout << "Heureka" << std::endl;
    }

    std::cin >> a;

    return 0;
}