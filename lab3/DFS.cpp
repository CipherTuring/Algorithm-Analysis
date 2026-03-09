#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>

class Graph {
private:
    // The Adjacency List
    std::unordered_map<int, std::vector<int>> adjList;

    // Recursive utility for the DFS
    void DFSUtil(int node, std::unordered_set<int>& visited) {
        visited.insert(node);
        std::cout << node << " ";

        for (int neighbor : adjList[node]) {
            if (visited.find(neighbor) == visited.end()) {
                DFSUtil(neighbor, visited);
            }
        }
    }

public:
    // Function to add an edge to the graph (it is a directed graph by default)
    void addEdge(int src, int dest) {
        adjList[src].push_back(dest);
        
    }

    void DFS(int startNode) {
        std::unordered_set<int> visited; // Keeps track of visited nodes to prevent infinite loops
        
        DFSUtil(startNode, visited);
        std::cout << std::endl;
    }
};

int main() {
    Graph g;

    // Construction of the graph
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(2, 4);
    g.addEdge(3, 4);
    
    // Add an edge that loops back to test cycle prevention
    g.addEdge(4, 0); 

    std::cout << "Depth First Traversal (starting from node 0): \n";
    g.DFS(0);

    return 0;
}