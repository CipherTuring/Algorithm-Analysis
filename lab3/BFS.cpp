#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue> // Required for the BFS queue

class Graph {
private:
    // Adjacency List
    std::unordered_map<int, std::vector<int>> adjList;

public:
    
    void addEdge(int src, int dest) {
        adjList[src].push_back(dest);
    }

    void BFS(int startNode) {
        std::unordered_set<int> visited; 
        std::queue<int> q;               

        visited.insert(startNode);
        q.push(startNode);

        while (!q.empty()) {
            int currentNode = q.front();
            q.pop();
            std::cout << currentNode << " ";

            for (int neighbor : adjList[currentNode]) {
                if (visited.find(neighbor) == visited.end()) {
                    visited.insert(neighbor);
                    q.push(neighbor);
                }
            }
        }
        std::cout << std::endl;
    }
};

int main() {
    Graph g;

    // Building the graph 
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(2, 4);
    g.addEdge(3, 4);
    g.addEdge(4, 0); // Cycle back to 0

    std::cout << "Breadth First Traversal (starting from node 0): \n";
    g.BFS(0);

    return 0;
}