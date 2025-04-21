class Solution:
    def isBipartite(self, graph: list[list[int]]) -> bool:
        visited = [-1] * len(graph)
        color = 0

        for cur in graph:
            visited[cur]
            color = not color
            for i in cur:
                visited[i] = color
                
