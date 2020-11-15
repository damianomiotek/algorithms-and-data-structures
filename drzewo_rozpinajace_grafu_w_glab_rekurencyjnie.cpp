#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

void dfsTree(const int &v, vector< vector<int> > &graph, vector< vector<int> > &spanning_tree, vector<bool> &visited)
{
    visited[v] = true;                                          // Oznaczamy wierzchołek jako odwiedzony
    for(const int &neighbor : graph[v])                         // Przeglądamy sąsiadów
    {
        if(!visited[neighbor])                                  // Interesują nas tylko nieodwiedzeni sąsiedzi
        {
            spanning_tree[v].push_back(neighbor);
            dfsTree(neighbor, graph, spanning_tree, visited);   // Rekurencyjnie tworzymy drzewo
        }
    }

}

// **********************
// *** Program główny ***
// **********************
int main( )
{
    vector< vector<int> > graph;                                // Tablica list sąsiadztwa grafu
    vector< vector<int> > spanning_tree;                        // Tablica list sąsiedztwa drzewa rozpinającego
    vector<bool> visited;                                       // Tablica odwiedzin
    int n, m, i, v1, v2;

    cin >> n >> m;                                              // Czytamy liczbę wierzchołków i krawędzi

    // Graf wypełniamy pustymi listami, tablicę visited wartościami false, spanning_tree pustymi listami
    for(i = 0; i < n; i++)
    {
        graph.push_back( vector<int>() );
        visited.push_back(false);
        spanning_tree.push_back( vector<int>() );
    }

    // Odczytujemy kolejne definicje krawędzi
    for(int i = 0; i < m; i++)
    {
        cin >> v1 >> v2;                                        // Wierzchołek startowy i końcowy krawędzi
        graph[v1].push_back(v2);
        graph[v2].push_back(v1);                                // To samo dla krawędzi w drugą stronę
    }

    // Tworzymy drzewo rozpinające w głąb
    cin >> v1;                                                  // Czytamy wierzchołek startowy
    dfsTree(v1, graph, spanning_tree, visited);

    // Wyświetlamy tablicę list sąsiedztwa drzewa rozpinającego
    cout << endl;
    for(i = 0; i < n; i++)
    {
        cout << i << ":";
        for(const int & neighbor : spanning_tree[i])
            cout << setw(3) << neighbor;
        cout << endl;
    }

    cout << endl;

    return 0;
}
