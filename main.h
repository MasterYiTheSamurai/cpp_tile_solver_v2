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
    std::vector<std::string> Get_position(std::vector<Node> nodes);
    static void Increase_g()
    {
        Node::g++;
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
    if (this->value <= 3 && 1 <= this->value)
        this->idealy = 3;
    if (this->value <= 6 && 4 <= this->value)
        this->idealy = 2;
    if (this->value <= 9 && 7 <= this->value)
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
    int xdiff = this->x - this->idealx;
    xdiff = abs(xdiff);
    int ydiff = this->y - this->idealy;
    ydiff = abs(ydiff);

    int diff = xdiff + ydiff;
    this->Setheuristic(diff);
    return;
};

void Calculate_Manhattan_distance(std::vector<Node> nodes)
{
    int sum = 0;
    for (int i = 0; i < nodes.size(); i++)
    {
        sum += nodes[i].Getheuristic();
    }
    Node::Set_h(sum);
}

int GetNode(std::vector<Node> nodes, int value)
{
    for (int i = 0; i < nodes.size(); i++)
    {
        if (nodes[i].Getvalue() == value)
            return i;
    }
}

std::vector<std::string> Node::Get_position(std::vector<Node> nodes)
{
    int mini = 999;
    std::vector<std::string> turns;
    int ind = GetNode(nodes, this->value);
    int h = Node::Get_h();
    int g = Node::Get_g();
   // int f = Node::Get_f();
    if (nodes[ind].GetX() > 1)
    {
        int heur = nodes[ind - 1].Getheuristic();
        if (h - heur + g + 1 <= g + h)
            turns.push_back("L");
    }
    if (nodes[ind].GetX() < 3)
    {
        int heur = nodes[ind + 1].Getheuristic();
         if (h - heur + g + 1 <= g + h)
            turns.push_back("R");
    }
    if (nodes[ind].GetY() < 3)
    {
        int heur = nodes[ind - 3].Getheuristic();
         if (h - heur + g + 1 <= g + h)
            turns.push_back("U");
    }
    if (nodes[ind].GetY() > 1)
    {
        int heur = nodes[ind + 3].Getheuristic();
         if (h - heur + g + 1 <= g + h)
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

std::vector<std::string> Solve(std::vector<Node> arr, std::string turn, std::vector<std::string> prev_turns)
{
     std::vector<std::string> empty;
    if (turn == "")
    {
        if(!prev_turns.empty())
            return empty;
        if (inPlace(arr))
            return prev_turns;
        int ind = GetNode(arr, 9);
        std::vector<std::string> turns = arr[ind].Get_position(arr);
        for (const std::string &t : turns)
        {

            std::vector<std::string> tmp = Solve(arr, t, prev_turns);
            if (!tmp.empty())
                return tmp;
        }
        return prev_turns;
    }
    else
    {
        int ind = GetNode(arr, 9);
        if (turn == "L")
        {
            std::swap(arr.at(ind), arr[ind - 1]);
            Node::Increase_g();
        }
        if (turn == "R")
        {
            std::swap(arr[ind], arr[ind + 1]);
            Node::Increase_g();
        }
        if (turn == "U")
        {
            std::swap(arr[ind], arr[ind - 3]);
            Node::Increase_g();
        }
        if (turn == "D")
        {
            std::swap(arr[ind], arr[ind + 3]);
            Node::Increase_g();
        }
        std::vector<std::string> tmp;
        prev_turns.push_back(turn);
        if (inPlace(arr))
            return prev_turns;
        std::vector<std::string> turns = arr[ind].Get_position(arr);
        for (const std::string &t : turns)
        {
            tmp = Solve(arr, t, prev_turns);
            if (!tmp.empty())
                prev_turns.insert(std::end(prev_turns), std::begin(tmp), std::end(tmp));
        }
    }
    return empty;
}
