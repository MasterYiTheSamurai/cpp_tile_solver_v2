import random

unique=[]

def solution(arr):
    print(arr)

while len(unique)!=9:
    num = random.randrange(1,10)
    if num not in unique:
        unique.append(num)

solution(unique)