#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include "graph.h"

using namespace graph;

class Kosaraju {
private:
    std::vector<bool> visited;
    std::vector<int> component;
    void DFSFirstPass(const Graph& g, Vertex u, std::stack<Vertex>& stack) {
        visited[u] = true;
        for (Vertex v : g.GetAdjacents(u)) {
            if (!visited[v]) {
                DFSFirstPass(g, v, stack);
            }
        }
        stack.push(u); 
    }
    void DFSSecondPass(const Graph& g, Vertex u, int comp_id) {
        visited[u] = true;
        component[u] = comp_id;
        for (Vertex v : g.GetAdjacents(u)) {
            if (!visited[v]) {
                DFSSecondPass(g, v, comp_id);
            }
        }
    }
public:
    std::vector<int> FindSCC(const Graph& g) {
        int n = g.size();
        visited.assign(n, false);
        component.assign(n, -1);
        std::stack<Vertex> stack;
        for (Vertex i = 0; i < n; ++i) {
            if (!visited[i]) {
                DFSFirstPass(g, i, stack);
            }
        }
        Graph transposed = g.GetTransposed();
        visited.assign(n, false);
        int comp_id = 0;
        while (!stack.empty()) {
            Vertex u = stack.top();
            stack.pop();
            if (!visited[u]) {
                DFSSecondPass(transposed, u, comp_id);
                comp_id++;
            }
        }
        return component;
    }
};

int main() {
    Graph gr(8);
    gr.AddEdge(0, 1);
    gr.AddEdge(1, 2);
    gr.AddEdge(2, 0);
    gr.AddEdge(2, 3);
    gr.AddEdge(3, 4);
    gr.AddEdge(4, 5);
    gr.AddEdge(5, 3);
    gr.AddEdge(6, 5);
    gr.AddEdge(6, 7);
    gr.AddEdge(7, 6);
    Kosaraju kosaraju;
    std::vector<int> components = kosaraju.FindSCC(gr);
    std::cout << "Strongly Connected Components:\n";
    for (Vertex i = 0; i < components.size(); ++i) {
        std::cout << "Vertex " << i << " -> Component " << components[i] << "\n";
    }
    return 0;
}