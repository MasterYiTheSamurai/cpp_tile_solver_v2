import random

unique = []
lista = []

max_moves = 10;

def get_position(ind, prev_turn):
    turns = []
    if (ind  > 0 and ind <= 2) or (ind > 3 and ind <= 5) or(ind > 6 and ind <= 8)  and prev_turn != "R":
        turns.append("L")
    if (ind  >= 0 and ind < 2) or (ind >= 3 and ind < 5) or(ind >= 6 and ind < 8)  and prev_turn != "L":
        turns.append("R")
    if ind > 2  and prev_turn != "D":
        turns.append("U")
    if ind < 6 and prev_turn != "U":
        turns.append("D")
    return turns

def solution(arr,turn,prev_turns):
    #print(arr[:3])
    #print(arr[3:6])
    #print(arr[6:])
    #print(prev_turns)

    if turn == "":
        ind = arr.index(9)
        turns = get_position(ind,"")
        for turn in turns:
            solution(arr,turn,prev_turns)
    else:
        if len(prev_turns) == max_moves:
            print(prev_turns)
            print(arr)
        ind = arr.index(9)
        if turn == "L":
            arr[ind] = arr[ind-1]
            arr[ind-1] = 9
        if turn == "R":
            arr[ind] = arr[ind+1]
            arr[ind+1] = 9
        if turn == "U":
            arr[ind] = arr[ind-3]
            arr[ind-3] = 9
        if turn == "D":
            arr[ind] = arr[ind+3]
            arr[ind+3] = 9
        if arr == lista:
            return
        if arr == range(1,10):
            return True
        ind = arr.index(9)
        prev_turns.append(turn)
        turns = get_position(ind,turn)
        for turn in turns:
            solution(arr,turn,prev_turns)


while len(unique)!=9:
    num = random.randrange(1,10)
    if num not in unique:
        unique.append(num)

unique = [2,1,3,4,5,6,7,8,9]

lista = [i for i in unique]

if solution(unique,"",[]):
    print("Heureka")