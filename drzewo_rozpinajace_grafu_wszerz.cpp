#include <iostream>
#include <iomanip>
#include <queue>
#include <vector>

using namespace std;

void dfsTree(int &v, vector< vector<int> > &graph, vector< vector<int> > &spanning_tree, vector<bool> &visited)
{
    queue<int> q;
    int w, z;

    q.push(-1);                                         // Na stosie umieszczamy krawędź -1->v
    q.push(v);
    visited[v] = true;                                  // Wierzcholek v oznaczamy jako odwiedzony
    while(!q.empty())
    {
        v = q.front();                                  // Pobieramy parę v-w z kolejki
        q.pop();
        w = q.front();
        q.pop();

        if(v > -1)
            spanning_tree[v].push_back(w);              // w dodajemy do listy spanning_tree[v]

        for(const int &neighbor : graph[w])             // Sąsiadów wierzchołka umieszczamy w kolejce
        {
            if(!visited[neighbor])
            {
                visited[neighbor] = true;
                q.push(w);                              // Do kolejki para w-sąsiad
                q.push(neighbor);
            }
        }
    }

}

// **********************
// *** Program główny ***
// **********************
int main( )
{
    vector< vector<int> > graph;                        // Tablica list sąsiadztwa grafu
    vector< vector<int> > spanning_tree;                // Tablica list sąsiedztwa drzewa rozpinającego
    vector<bool> visited;                               // Tablica odwiedzin
    int n, m, i, v1, v2;

    cin >> n >> m;                                      // Czytamy liczbę wierzchołków i krawędzi

    // Graf wypełniamy pustymi listami, tablicę visited wartościami false, spanning_tree pustymi listami sąsiedztwa
    for(i = 0; i < n; i++)
    {
        graph.push_back( vector<int>() );
        visited.push_back(false);
        spanning_tree.push_back( vector<int>() );
    }

    // Odczytujemy definicje krawędzi dla grafu nieskierowanego
    for(int i = 0; i < m; i++)
    {
        cin >> v1 >> v2;                                // Wierzchołek startowy i końcowy krawędzi
        graph[v1].push_back(v2);
        graph[v2].push_back(v1);                        // To samo dla krawędzi w drugą stronę
    }

    // Tworzymy drzewo rozpinające wgłąb
    cin >> v1;                                          // Czytamy wierzchołek startowy
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
