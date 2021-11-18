#include <iostream>
#include <list>

class Graph {
    int nb_vertices_;
    std::list<int> *adj;
public:
    Graph(int nb_vertices);

    void add_edge(int v, int w);

    void breath_first_search(int s);
};

Graph::Graph(int V) {
    this->nb_vertices_ = V;
    adj = new std::list<int>[V];
}

void Graph::add_edge(int v, int w) {
    adj[v].push_back(w); // Add w to v’s list.
}

void Graph::breath_first_search(int s) {
    // Mark all the vertices as not visited
    bool *visited = new bool[nb_vertices_];
    for (int i = 0; i < nb_vertices_; i++)
        visited[i] = false;

    // Create a queue for BFS
    std::list<int> queue;

    // Mark the current node as visited and enqueue it
    visited[s] = true;
    queue.push_back(s);

    // 'i' will be used to get all adjacent
    // vertices of a vertex
    std::list<int>::iterator i;

    while (!queue.empty()) {
        // Dequeue a vertex from queue and print it
        s = queue.front();
        std::cout << s << " ";
        queue.pop_front();

        // Get all adjacent vertices of the dequeued
        // vertex s. If a adjacent has not been visited,
        // then mark it visited and enqueue it
        for (i = adj[s].begin(); i != adj[s].end(); ++i) {
            if (!visited[*i]) {
                visited[*i] = true;
                queue.push_back(*i);
            }
        }
    }
    std::cout << std::endl;
}

enum Connexion {
    croix,
    full
};

class Grid {
public:
    Grid(int width, int height, Connexion connexion);

private:

};

Grid::Grid(int width, int height, Connexion connexion) {

}

int main() {
    // Create a graph given in the above diagram
    Graph g(4);
    g.add_edge(0, 1);
    g.add_edge(0, 2);
    g.add_edge(1, 2);
    g.add_edge(2, 0);
    g.add_edge(2, 3);
    g.add_edge(3, 3);

    std::cout << "Following is Breadth First Traversal "
              << "(starting from vertex 2) \n";
    g.breath_first_search(2);
    return 0;
}
