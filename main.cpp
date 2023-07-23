#include <iostream>
#include <vector>
#include <algorithm>

class Node
{

private:
    int value;
    int x;
    int y;
    int idealx;
    int idealy;
    int heuristic;

public:
 // static int Manhattan_distance;
 // static int g;
 // static int f;
    Node(int v, int x, int y)
    {
        this->x = x;
        this->y = y;
        value = v;
        Set_ideals();
        Calculate_heuristic();
    }
    void Set_ideals();
    void Calculate_heuristic();

    int Getvalue()
    {
        return value;
    }
    void Setvalue(int v)
    {
        value = v;
    }
    int Getheuristic()
    {
        return heuristic;
    }
    void Setheuristic(int h)
    {
        heuristic = h;
    }
    int GetX()
    {
        return x;
    }
    int GetY()
    {
        return y;
    }
    void SetX(int x)
    {
        this->x = x;
    }
    void SetY(int y)
    {
        this->y = y;
    }
    int GetIdealX()
    {
        return idealx;
    }
    int GetIdealY()
    {
        return idealy;
    }
};

void Node::Calculate_heuristic()
{
    int xdiff = x - this->idealx;
    int ydiff = y - this->idealy;

    int diff = xdiff + ydiff;
    this->Setheuristic(diff);
    return;
};

void Node::Set_ideals()
{
    if (this->value <= 1 && this->value >= 3)
        this->idealy = 3;
    if (this->value <= 6 && this->value >= 4)
        this->idealy = 2;
    if (this->value <= 9 && this->value >= 7)
        this->idealy = 1;

    if (this->value == 1 || this->value == 4 || this->value == 7)
        this->idealx = 1;
    if (this->value == 2 || this->value == 5 || this->value == 8)
        this->idealx = 2;
    if (this->value == 3 || this->value == 6 || this->value == 9)
        this->idealx = 3;

    return;
};

/*void Calculate_Manhattan_distance(std::vector<Node> nodes)
{
    int sum = 0;
    for(Node& n : nodes)
    {
        sum += n.Getheuristic();
    }
   Node::Manhattan_distance = sum;
}*/

std::vector<std::string> Get_position(int ind, std::string prev_turn)
{
    std::vector<std::string> turns;
    if ((ind > 0 && ind <= 2) || (ind > 3 && ind <= 5) || (ind > 6 && ind <= 8) && prev_turn != "R")
    {
        turns.push_back("L");
    }
    if ((ind >= 0 && ind < 2) || (ind >= 3 && ind < 5) || (ind >= 6 && ind < 8) && prev_turn != "L")
    {
        turns.push_back("R");
    }
    if (ind > 2 && prev_turn != "D")
    {
        turns.push_back("U");
    }
    if (ind < 6 && prev_turn != "U")
    {
        turns.push_back("D");
    }
    return turns;
}

bool Solve(std::vector<int> arr, std::string turn, std::vector<std::string> prev_turns)
{
    if (turn == "")
    {
        /*if (arr == compari) {
             return true;
         } */
        int ind = std::find(arr.begin(), arr.end(), 9) - arr.begin();
        std::vector<std::string> turns = Get_position(ind, "");
        for (const std::string &t : turns)
        {
            Solve(arr, t, prev_turns);
        }
    }
    else
    {
        int ind = std::find(arr.begin(), arr.end(), 9) - arr.begin();
        if (turn == "L")
        {
            std::swap(arr[ind], arr[ind - 1]);
        }
        if (turn == "R")
        {
            std::swap(arr[ind], arr[ind + 1]);
        }
        if (turn == "U")
        {
            std::swap(arr[ind], arr[ind - 3]);
        }
        if (turn == "D")
        {
            std::swap(arr[ind], arr[ind + 3]);
        }
        /*   if (arr == lista) {
               return false;
           }
           if (arr == compari) {
               return true;
           }*/
        ind = std::find(arr.begin(), arr.end(), 9) - arr.begin();
        prev_turns.push_back(turn);
        std::vector<std::string> turns = Get_position(ind, turn);
        for (const std::string &t : turns)
        {
            Solve(arr, t, prev_turns);
        }
    }
    return false;
}

int main()
{

    // Calculate_Manhattan_distance();

    /* int arr[] = {1, 2, 3, 4, 5, 6, 8, 7, 9};
     compari.assign(temp,temp+9);
     unique.assign(arr,arr+9);*/

   // std::vector<std::string> g;
   // Node::g = g.size();
   // Node::f = Node::g + Node::Manhattan_distance;

    std::vector<Node> unique;

    /*if (solution(unique, "", prev_turns)) {
        std::cout << "Heureka" << std::endl;
    }*/

    return 0;
}