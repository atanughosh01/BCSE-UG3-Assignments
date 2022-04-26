from collections import defaultdict


class Graph:

    def __init__(self, vertices):
        self.V = vertices
        self.graph = defaultdict(list)


    def add_edge(self, u, v):
        self.graph[u].append(v)


##########################################################################################
#                       D               F                   S
##########################################################################################
    def dfs_path_util(self, u: int, d: int, visited: list, path: list):
        visited[u] = True
        path.append(u)

        if u == d:
            print("Path = ", path)
            # return

        for i in self.graph[u]:
            if visited[i] == False:
                self.dfs_path_util(i, d, visited, path)

        path.pop()
        visited[u] = False

    def dfs_order_util(self, u:int, d:int, visited: list, order: list):
        visited[u] = True
        order.append(u)

        if u == d:
            print("Order = ", order)
            return

        for i in self.graph[u]:
            if visited[i] == False:
                self.dfs_order_util(i, d, visited, order)

        visited[u] = False


    def print_dfs_paths(self, s, d):
        visited = [False]*(self.V)
        path = []
        self.dfs_path_util(s, d, visited, path)

    
    def print_dfs_order(self, s, d):
        visited = [False]*(self.V)
        order = []
        self.dfs_order_util(s, d, visited, order)


##########################################################################################
#                       D               F                   S
##########################################################################################
    def bfs_path_util(self, u: int, d: int, visited: list, path: list):
        visited[u] = True
        path.append(u)

        if u == d:
            print("Path = ", path)
            # return

        for i in self.graph[u]:
            if visited[i] == False:
                self.bfs_path_util(i, d, visited, path)

        path.pop()
        visited[u] = False

    def bfs_order_util(self, u:int, d:int, visited: list, order: list):
        visited[u] = True
        order.append(u)

        if u == d:
            print("Order = ", order)
            return

        for i in self.graph[u]:
            if visited[i] == False:
                self.bfs_order_util(i, d, visited, order)

        visited[u] = False


    def print_bfs_paths(self, s, d):
        visited = [False]*(self.V)
        path = []
        self.bfs_path_util(s, d, visited, path)

    
    def print_bfs_order(self, s, d):
        visited = [False]*(self.V)
        order = []
        self.bfs_order_util(s, d, visited, order)



###########################################################################
    def print_grpah(self):
        return dict(self.graph)


###########################################################################
if __name__ == "__main__":
    ver = int(input("Enter Number of Vertices of The Graph : "))
    gp = Graph(ver)

    gp.add_edge(0, 3)
    gp.add_edge(0, 1)
    gp.add_edge(0, 2)
    gp.add_edge(2, 0)
    gp.add_edge(2, 1)
    gp.add_edge(1, 3)
    # s = 2
    # d = 3


    # while True:
    #     ff = int(input("First : "))
    #     ss = int(input("Second : "))
    #     gp.add_edge(ff, ss)
    #     con = input("Continue (y/N) ? : ")
    #     if con in ["N", "n"]:
    #         break

    print("Graph : ", gp.print_grpah())

    s = int(input("Enter Source : "))
    d = int(input("Enter Destination : "))

    print(f"\nFollowing are all different paths from {s} to {d} -" )
    gp.print_dfs_paths(s, d)

    print(f"\nFollowing are order (based on adjacency list) from {s} to {d} -" )
    gp.print_dfs_order(s, d)
