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
    std::vector<std::string> Get_position(std::vector<Node> nodes, int offset, std::vector<std::string> prev_turns, std::string prev_turn);
    static void Decrease_g()
    {
        Node::g--;
    }
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

void Calculate_Manhattan_distance(std::vector<Node> nodes, int offset)
{
    int sum = 0;
    for (int i = 0; i < nodes.size(); i++)
    {
        if (nodes[i].Getvalue() != offset)
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
    return 1;
}

std::vector<std::string> Node::Get_position(std::vector<Node> nodes, int offset, std::vector<std::string> prev_turns, std::string prev_turn)
{
    std::vector<std::string> turns;

    std::vector<int> priorities;

    int ind = GetNode(nodes, offset);

    int R_heur;
    int L_heur;
    int U_heur;
    int D_heur;

    int R = count(prev_turns.begin(), prev_turns.end(), "R");
    int L = count(prev_turns.begin(), prev_turns.end(), "L");
    int U = count(prev_turns.begin(), prev_turns.end(), "U");
    int D = count(prev_turns.begin(), prev_turns.end(), "D");

    if (ind < nodes.size() - 1 && nodes[ind].GetX() < 3)
    {
        R_heur = nodes[ind + 1].Getheuristic();
        priorities.push_back(R_heur);
    }
    if (0 < ind && 1 < nodes[ind].GetX())
    {
        L_heur = nodes[ind - 1].Getheuristic();
        priorities.push_back(L_heur);
    }
    if (ind < nodes.size() - 3 && 1 < nodes[ind].GetY())
    {
        D_heur = nodes[ind + 3].Getheuristic();
        priorities.push_back(D_heur);
    }
    if (2 < ind && nodes[ind].GetY() < 3)
    {
        U_heur = nodes[ind - 3].Getheuristic();
        priorities.push_back(U_heur);
    }

    sort(priorities.rbegin(), priorities.rend());

    for (int i = 0; i < priorities.size(); i++)
    {
        if (priorities[i] == L_heur && !count(turns.begin(), turns.end(), "L"))
        {
            if (nodes[ind].GetX() > 1)
            {
                if (prev_turn != "R")
                    turns.push_back("L");
            }
        }
        if (priorities[i] == R_heur && !count(turns.begin(), turns.end(), "R"))
        {
            if (nodes[ind].GetX() < 3)
            {

                if (prev_turn != "L")
                    turns.push_back("R");
            }
        }
        if (priorities[i] == U_heur && !count(turns.begin(), turns.end(), "U"))
        {
            if (nodes[ind].GetY() < 3)
            {
                if (prev_turn != "D")
                    turns.push_back("U");
            }
        }
        if (priorities[i] == D_heur && !count(turns.begin(), turns.end(), "D"))
        {
            if (nodes[ind].GetY() > 1)
            {
                if (prev_turn != "U")
                    turns.push_back("D");
            }
        }
    }

    return turns;
}

bool inPlace(std::vector<Node> nodes, int offset)
{
    for (int i = 0; i < nodes.size(); i++)
    {
        if ((nodes[i].GetIdealX() != nodes[i].GetX() && nodes[i].Getvalue() != offset) || (nodes[i].GetIdealY() != nodes[i].GetY() && nodes[i].Getvalue() != offset))
            return false;
    }
    return true;
}

void Display(std::vector<Node> nodes, int offset)
{
    for (int i = 0; i < 1; i++)
    {
        std::cout << "_______";
    }
    std::cout << std::endl;
    std::cout << "|";
    for (int i = 0; i < 3; i++)
    {
        if (nodes[i].Getvalue() != offset)
        {
            std::cout << nodes[i].Getvalue() << "|";
        }
        else
        {
            std::cout << " "
                      << "|";
        }
    }
    std::cout << std::endl;
    std::cout << "|";
    for (int i = 3; i < 6; i++)
    {
        if (nodes[i].Getvalue() != offset)
        {
            std::cout << nodes[i].Getvalue() << "|";
        }
        else
        {
            std::cout << " "
                      << "|";
        }
    }
    std::cout << std::endl;
    std::cout << "|";
    for (int i = 6; i < 9; i++)
    {
        if (nodes[i].Getvalue() != offset)
        {
            std::cout << nodes[i].Getvalue() << "|";
        }
        else
        {
            std::cout << " "
                      << "|";
        }
    }
    std::cout << std::endl;
    for (int i = 0; i < 1; i++)
    {
        std::cout << "-------";
    }
    std::cout << std::endl;
    std::cout << std::endl;
}

void Turn(std::vector<Node> &arr, int offset, int ind, std::string turn)
{
    if (turn == "L")
    {

        int tmp_x = arr[ind - 1].GetX();
        int tmp_y = arr[ind - 1].GetY();
        arr[ind - 1].SetX(arr[ind].GetX());
        arr[ind - 1].SetY(arr[ind].GetY());
        arr[ind].SetX(tmp_x);
        arr[ind].SetY(tmp_y);
        std::swap(arr.at(ind), arr[ind - 1]);
        Node::Increase_g();
        arr[ind - 1].Calculate_heuristic();
        arr[ind].Calculate_heuristic();
        Calculate_Manhattan_distance(arr, offset);
    }
    if (turn == "R")
    {
        int tmp_x = arr[ind + 1].GetX();
        int tmp_y = arr[ind + 1].GetY();
        arr[ind + 1].SetX(arr[ind].GetX());
        arr[ind + 1].SetY(arr[ind].GetY());
        arr[ind].SetX(tmp_x);
        arr[ind].SetY(tmp_y);
        std::swap(arr[ind], arr[ind + 1]);
        Node::Increase_g();
        arr[ind + 1].Calculate_heuristic();
        arr[ind].Calculate_heuristic();
        Calculate_Manhattan_distance(arr, offset);
    }
    if (turn == "U")
    {
        int tmp_x = arr[ind - 3].GetX();
        int tmp_y = arr[ind - 3].GetY();
        arr[ind - 3].SetX(arr[ind].GetX());
        arr[ind - 3].SetY(arr[ind].GetY());
        arr[ind].SetX(tmp_x);
        arr[ind].SetY(tmp_y);
        std::swap(arr[ind], arr[ind - 3]);
        Node::Increase_g();
        arr[ind - 3].Calculate_heuristic();
        arr[ind].Calculate_heuristic();
        Calculate_Manhattan_distance(arr, offset);
    }
    if (turn == "D")
    {
        int tmp_x = arr[ind + 3].GetX();
        int tmp_y = arr[ind + 3].GetY();
        arr[ind + 3].SetX(arr[ind].GetX());
        arr[ind + 3].SetY(arr[ind].GetY());
        arr[ind].SetX(tmp_x);
        arr[ind].SetY(tmp_y);
        std::swap(arr[ind], arr[ind + 3]);
        Node::Increase_g();
        arr[ind + 3].Calculate_heuristic();
        arr[ind].Calculate_heuristic();
        Calculate_Manhattan_distance(arr, offset);
    }
}

std::vector<std::string> Solve(std::vector<Node> arr, std::string turn, std::vector<std::string> prev_turns, int offset)
{
    std::vector<std::string> empty;
    if (turn == "")
    {
        if (!prev_turns.empty())
            return empty;
        if (inPlace(arr, offset))
            return prev_turns;
        int ind = GetNode(arr, offset);
        std::vector<std::string> turns = arr[ind].Get_position(arr, offset, prev_turns, turn);
        for (int i = 0; i < turns.size(); i++)
        {
            std::vector<std::string> tmp = Solve(arr, turns[i], prev_turns, offset);
            if (!tmp.empty())
            {
                return tmp;
            }
            else
            {
                Node::Decrease_g();
            }
        }
        return prev_turns;
    }
    else
    {
        std::vector<std::string> tmp;
        int ind = GetNode(arr, offset);
        Turn(arr, offset, ind, turn);
        prev_turns.push_back(turn);
        if (inPlace(arr, offset))
            return prev_turns;
        std::vector<std::string> turns = arr[ind].Get_position(arr, offset, prev_turns, turn);
        if (turns.empty())
        {
            Node::Decrease_g();
            return empty;
        }
        for (int i = 0; i < turns.size(); i++)
        {
            tmp = Solve(arr, turns[i], prev_turns, offset);
            if (!tmp.empty())
            {
                return tmp;
            }
            else
            {
                Node::Decrease_g();
            }
        }
    }
    return empty;
}
