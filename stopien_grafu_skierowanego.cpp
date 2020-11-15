#include <iostream>
#include <vector>

using namespace std;

int main()
{
    int n, m;                                           // Liczba wierzchołków, liczba krawędzi
    vector< vector<int> > graph;                        // Graf
    vector<int> vertex_degrees;                         // Tablica stopni wierzczołków
    int graph_degree, v, i, u;

    cin>>n>>m;                                          // Czytamy rozmiary grafu

    for(i = 0; i < n; i++)
    {
        graph.push_back( vector<int>() );               // Wypełniamy graf pustymi wektorami
        vertex_degrees.push_back(0);                    // Wypełniamy tablicę stopni wierzchołków zerami
    }

    // Odczytujemy definicje krawędzi grafu
    for(i = 0; i < m; i++)
    {
        cin >> v >> u;                                  // Wierzchołek startowy i końcowy krawędzi
        graph[v].push_back(u);                          // Wierzchołek v -> u
    }

    // Wyznaczamy stopień grafu
    for(v = 0; v < n; v++)                              // Przechodzimy przez kolejne wierzchołki grafu
        for(const int &neighbor : graph[v])             // Przeglądamy listę sąsiadów wierzchołka v
        {
            vertex_degrees[v]++;                        // Zwiększamy stopień wyjściowy v
            vertex_degrees[neighbor]++;                 // Zwiększamy stopień wejściowy sąsiada v
        }
        
    // Szukamy największego stopnia
    graph_degree = vertex_degrees[0];
    for(v = 1; v < n; v++)
        if(vertex_degrees[v] > graph_degree)
            graph_degree = vertex_degrees[v];

    // Wyświetlamy wynik
    cout<<endl<<graph_degree<<endl;

    return 0;
}