# Python3 program to print all paths of
# source to destination in given graph
from typing import List
from collections import deque


# Utility function for printing
# the found path in graph
def print_path(path: List[int]) -> None:
    size = len(path)
    for i in range(size):
        print(path[i], end=" ")
    print()


# Utility function to check if current
# vertex is already present in path
def is_not_visited(x: int, path: List[int]) -> int:
    size = len(path)
    for i in range(size):
        if path[i] == x:
            return 0
    return 1


# Utility function for finding paths in graph
# from source to destination
def find_paths(g: List[List[int]], src: int, dst: int) -> None:

    # Create a queue which stores
    # the paths
    q = deque()

    # Path vector to store the current path
    path = []
    path.append(src)
    q.append(path.copy())

    while q:
        path = q.popleft()
        last = path[len(path) - 1]

        # If last vertex is the desired destination
        # then print the path
        if (last == dst):
            print_path(path)

        # Traverse to all the nodes connected to
        # current vertex and push new path to queue
        for i in range(len(g[last])):
            if is_not_visited(g[last][i], path):
                new_path = path.copy()
                new_path.append(g[last][i])
                q.append(new_path)


# Driver code
if __name__ == "__main__":

    # Number of vertices
    v = 4
    g = [[] for _ in range(4)]

    # Construct a graph
    g[0].append(3)
    g[0].append(1)
    g[0].append(2)
    g[1].append(3)
    g[2].append(0)
    g[2].append(1)
    src = 2
    dst = 3
    print(f"path from src {src} to dst {dst} are -")

    # Function for finding the paths
    find_paths(g, src, dst)
