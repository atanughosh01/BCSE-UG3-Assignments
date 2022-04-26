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


# Driver Code
if __name__ == "__main__":
    g = Graph()
    g.add_edge(0, 1)
    g.add_edge(0, 2)
    g.add_edge(1, 2)
    g.add_edge(2, 0)
    g.add_edge(2, 3)
    g.add_edge(3, 3)

    inp = int(input("Enter Starting Vertex : "))
    print(f"Following is DFS from (Starting from vertex {inp})")
    g.dfs(inp)
