#include <iostream>
#include <vector>
#include <algorithm>

std::vector<int> unique;
std::vector<int> lista;
const int max_moves = 10;
int temp[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
std::vector<int> compari;


std::vector<std::string> get_position(int ind, std::string prev_turn) {
    std::vector<std::string> turns;
    if ((ind > 0 && ind <= 2) || (ind > 3 && ind <= 5) || (ind > 6 && ind <= 8) && prev_turn != "R") {
        turns.push_back("L");
    }
    if ((ind >= 0 && ind < 2) || (ind >= 3 && ind < 5) || (ind >= 6 && ind < 8) && prev_turn != "L") {
        turns.push_back("R");
    }
    if (ind > 2 && prev_turn != "D") {
        turns.push_back("U");
    }
    if (ind < 6 && prev_turn != "U") {
        turns.push_back("D");
    }
    return turns;
}

bool solution(std::vector<int> arr, std::string turn, std::vector<std::string> prev_turns) {
    if (turn == "") {
        if (arr == compari) {
            return true;
        }
        int ind = std::find(arr.begin(), arr.end(), 9) - arr.begin();
        std::vector<std::string> turns = get_position(ind, "");
        for (const std::string& t : turns) {
            solution(arr, t, prev_turns);
        }
    } else {
        if (prev_turns.size() == max_moves) {
            for (const std::string& t : prev_turns) {
                std::cout << t << " ";
            }
            std::cout << std::endl;
            for (int num : arr) {
                std::cout << num << " ";
            }
            std::cout << std::endl;
        }
        int ind = std::find(arr.begin(), arr.end(), 9) - arr.begin();
        if (turn == "L") {
            std::swap(arr[ind], arr[ind - 1]);
        }
        if (turn == "R") {
            std::swap(arr[ind], arr[ind + 1]);
        }
        if (turn == "U") {
            std::swap(arr[ind], arr[ind - 3]);
        }
        if (turn == "D") {
            std::swap(arr[ind], arr[ind + 3]);
        }
        if (arr == lista) {
            return false;
        }
        if (arr == compari) {
            return true;
        }
        ind = std::find(arr.begin(), arr.end(), 9) - arr.begin();
        prev_turns.push_back(turn);
        std::vector<std::string> turns = get_position(ind, turn);
        for (const std::string& t : turns) {
            solution(arr, t, prev_turns);
        }
    }
    return false;
}

int main() {
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    compari.assign(temp,temp+9);
    std::vector<int> unique;
    unique.assign(arr,arr+9);
    std::vector<int> lista = unique;
    std::vector<std::string> prev_turns;

    if (solution(unique, "", prev_turns)) {
        std::cout << "Heureka" << std::endl;
    }

    return 0;
}