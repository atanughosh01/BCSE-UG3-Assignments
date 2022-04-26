from collections import defaultdict


class Graph:

    def __init__(self) -> None:
        self.graph = defaultdict(list)

    def add_edge(self, u: int, v: int) -> None:
        self.graph[u].append(v)

    def dfs_util(self, v: int, visited: set) -> None:
        visited.add(v)
        print(v, end=" ")
        for adj in self.graph[v]:
            if adj not in visited:
                self.dfs_util(adj, visited)

    def dfs(self, v: int) -> None:
        visited = set()
        self.dfs_util(v, visited)

    def bfs(self, node: int) -> None:
        visited = [False]*(max(self.graph)+1)
        que = []
        que.append(node)
        visited[node] = True

        while que:
            node = que.pop(0)
            print(node, end=" ")
            for __node in self.graph[node]:
                if visited[__node] is False:
                    que.append(__node)
                    visited[__node] = True

    # def new()

    
if __name__ == "__main__":
    gp = Graph()
    # con = input("Continue (y/N) ? : ")
    while True:
        # print("Enter 1st and 2nd : ")
        ff = int(input("First : "))
        ss = int(input("Second : "))
        gp.add_edge(ff, ss)
        con = input("Continue (y/N) ? : ")
        if con in ["N", "n"]:
            break
    
    inp = int(input("Enter Starting Vertex : "))
    print(f"Following is the from (Starting from vertex {inp})")
    gp.bfs(inp)
