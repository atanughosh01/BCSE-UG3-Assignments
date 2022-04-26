from collections import defaultdict


class Graph:

    def __init__(self) -> None:
        self.graph = defaultdict(list)

    def add_edge(self, u: int, v: int) -> None:
        self.graph[u].append(v)

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
    print(f"Following is BFS from (Starting from vertex {inp})")
    g.bfs(inp)
