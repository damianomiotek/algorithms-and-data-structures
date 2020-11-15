#include <iostream>
#include <vector>

using namespace std;

int main()
{
    int n, m;                                   // Liczba wierzchołków, liczba krawędzi
    vector< vector<int> > graph;                // Graf
    int graph_degree, vertex_degree, i, v, u;

    cin >> n >> m;                              // Czytamy rozmiary grafu

    for(int i = 0; i < n; i++)                  // Wypełniamy graf pustymi wektorami
        graph.push_back(vector<int>());

    // odczytujemy definicje krawędzi grafu G
    for(int i = 0; i < m; i++)
    {
        cin >> v >> u;                          // Wierzchołek startowy i końcowy krawędzi
        graph[v].push_back(u);                  // Wierzchołek v -> u
        if(v != u)                              // Wierzchołek v -> v dołączamy tylko raz
            graph[u].push_back(v);              // Wierzchołek u -> v
    }

    // Wyznaczamy stopień grafu
    graph_degree = 0;

    for(int v = 0; v < n; v++)                  // Przechodzimy przez kolejne wierzchołki grafu
    {
        vertex_degree = 0;                      // Zerujemy stopień wierzchołka
        for(const int &neighbor : graph[v])     // Przeglądamy sąsiadów wierzchołka v
            if(neighbor == v)                   // Pętle zliczamy za dwa
                vertex_degree += 2; 
            else                                // Zwykłą krawędź zliczamy za 1
                vertex_degree++;

        if(vertex_degree > graph_degree)        // Jeśli stopień wierzchołka jest większy od stopnia grafu, to uaktualniamy
            graph_degree = vertex_degree;
    }

    // Wyświetlamy wynik
    cout<<endl<<graph_degree<<endl;

    return 0;
}