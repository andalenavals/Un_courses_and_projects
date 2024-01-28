from itertools import combinations
def solution(num_buns, num_required):
    sol = [[] for num in range(num_buns)]
    cop_key = num_buns - num_required + 1
    for col, rowindx in enumerate(combinations(range(num_buns), cop_key)):
        for r in rowindx:
            sol[r].append(col)
    return sol


if __name__ == "__main__":
    print(solution(6,4))

