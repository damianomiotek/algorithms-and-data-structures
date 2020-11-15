#include <iostream>
#include <vector>

using namespace std;

vector< vector<int> > do_line_graph(vector< vector<pair<int, int>> > &graph, int &n, int &m)
{
    vector< vector<int> > line_graph(m, vector<int>());

    for (int v = 0; v < n; v++)                                                     // Przechodzimy przez kolejne wierzchołki grafu
        for (const pair<int, int> &neighbor : graph[v])                             // Przechodzimy przez listę sąsiadów wierzchołka v
            for (const pair<int, int> &neighbor_neighbor : graph[neighbor.first])   // Przechodzimy przez listę sąsiadów sąsiada v
                if (neighbor_neighbor.first != v)                                   // Jeśli sąsiad sąsiada v nie jest wierzchołkiem v
                {
                    // Dodajemy krawędź do grafu krawędziowego
                    // Wierzchołkiem startowym jest numer krawędzi v->neighbor, wierzchołekiem docelowym jest numer krawędzi neighbor->neighbor_neighbor
                    line_graph[neighbor.second].push_back(neighbor_neighbor.second);     
                }

    return line_graph;
}


int main()
{
    int n, m, i;                                        // Liczba wierzchołków, liczba krawędzi
    vector< vector<pair<int, int>> > graph;             // Graf wejściowy
    vector< vector<int> > line_graph;                   // Graf krawędziowy
    int u, v, ei;

    cin >> n >> m;                                      // Czytamy rozmiary grafu

    // Graf wypełniamy pustymi listami
    for(i = 0; i < n; i++)
        graph.push_back( vector<pair<int, int>>() );

    // Odczytujemy definicje krawędzi grafu G
    for( i = 0; i < m; i++ )
    {
        cin >> v >> u >> ei;                            // Wierzchołek startowy i końcowy krawędzi, numer krawędzi
        graph[v].push_back( make_pair(u, ei));          // Krawędź o numerze ei, wierzchołek startowy v, końcowy u

        // Poniższą linijkę wykonujemy tylko dla grafu nieskierowanego
        graph[u].push_back( make_pair(v, ei));          // Krawędź o numerze ei, wierzchołek startowy u, końcowy v
    }

    line_graph = do_line_graph(graph, n, m);            // Tworzymy graf krawędziowy

    // Wyświetlamy wyniki
    cout << endl;
    for( i = 0; i < m; i++ )
    {
        cout << i << ": ";
        for( const int &neighbor : line_graph[i] ) 
            cout << neighbor << " ";
        cout << endl;
    }

    return 0;
}