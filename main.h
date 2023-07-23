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
    static int g;
    static int f;
    static int h;
public:
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
    std::vector<std::string> Get_position();
     static void Set_g(int value)
    {
         Node::g = value;
    }
     static int Get_g()
    {
         return g;
    }
    static void Set_f(int value)
    {
         Node::f = value;
    }
     static int Get_f()
    {
         return f;
    }
    static void Set_h(int value)
    {
         Node::h = value;
    }
     static int Get_h()
    {
         return h;
    }
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

int Node::g = 0;

int Node::f = 0;

int Node::h = 0;

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

void Node::Calculate_heuristic()
{
    int xdiff = x - this->idealx;
    int ydiff = y - this->idealy;

    int diff = xdiff + ydiff;
    this->Setheuristic(diff);
    return;
};

void Calculate_Manhattan_distance(std::vector<Node> nodes)
{
    int sum = 0;
    for (Node &n : nodes)
    {
        sum += n.Getheuristic();
    }
    Node::Set_h(sum);
}

std::vector<std::string> Node::Get_position()
{
    std::vector<std::string> turns;
    if (x > 1)
    {
        turns.push_back("L");
    }
    if (x < 3)
    {
        turns.push_back("R");
    }
    if (y < 3)
    {
        turns.push_back("U");
    }
    if (y > 1)
    {
        turns.push_back("D");
    }
    return turns;
}

bool inPlace(std::vector<Node> nodes)
{
    for (Node &node : nodes)
    {
        if (node.GetIdealX() != node.GetX() || node.GetIdealY() != node.GetIdealY())
            return false;
    }
    return true;
}

Node Get9(std::vector<Node> nodes)
{
    for (Node &n : nodes)
    {
        if (n.Getvalue() == 9)
            return n;
    }
}

bool Solve(std::vector<Node> arr, std::string turn, std::vector<std::string> prev_turns)
{
    if (turn == "")
    {
        if (inPlace(arr))
            return true;
        Node nine = Get9(arr);
        std::vector<std::string> turns = nine.Get_position();
        for (const std::string &t : turns)
        {
            Solve(arr, t, prev_turns);
        }
    }
    else
    {
        Node nine = Get9(arr);
        // TODO 
        // Finish turning logic
        // auto ind = std::find(arr.begin(),arr.begin()+9,nine);
        /* if (turn == "L")
         {
             std::swap(arr.at(ind), arr[ind - 1]);
             Node::g++;
         }
         if (turn == "R")
         {
             std::swap(arr[ind], arr[ind + 1]);
             Node::g++;
         }
         if (turn == "U")
         {
             std::swap(arr[ind], arr[ind - 3]);
             Node::g++;
         }
         if (turn == "D")
         {
             std::swap(arr[ind], arr[ind + 3]);
             Node::g++;
         }*/
        if(Node::Get_g()+Node::Get_h() > Node::Get_f())
            return false;
        if (inPlace(arr))
            return true;
        prev_turns.push_back(turn);
        std::vector<std::string> turns = nine.Get_position();
        for (const std::string &t : turns)
        {
            Solve(arr, t, prev_turns);
        }
    }
    return false;
}
