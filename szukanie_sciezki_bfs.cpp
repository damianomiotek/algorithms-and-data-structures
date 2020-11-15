#include <iostream>
#include <queue>
#include <vector>
#include <map>
#include <stack>
#include <iomanip>


using namespace std;

bool bfs_path(int &vs, int &vk, vector< vector<int> > &graph, map<int, int> &predecessors)
{
    queue<int>q;                                                        // Kolejka dla BFS
    int v, i;

    predecessors.insert( pair<int, int>(vs, -1) );
    q.push(vs);                                                         // W kolejce umieszczamy wierzchołek startowy

    while(!q.empty())
    {
        v = q.front();
        q.pop();

        if(v == vk)                                                     // Sprawdzamy koniec ścieżki
            return true;

        // Przeglądamy sąsiadów wierzchołka v
        for(const int &neighbor : graph[v])
        {
            if(predecessors.find(neighbor) == predecessors.end())       // Jeśli sąsiad nie był wcześniej odwiedzony
            {
                predecessors.insert( pair<int, int>(neighbor, v) );     // Zapisujemy ten wierzchołek i jego rodzica
                q.push(neighbor);                                       // Sąsiad zostaje umieszczony w kolejce
            }
        }
    }

    return false;
}

int main()
{
    int n, m;                                           // Liczba wierzchołków i krawędzi
    vector< vector<int> > graph;                        // Lista sąsiedztwa
    int vs, vk;                                         // Wierzchołek startowy i końcowy
    map<int, int> predecessors;                         // Mapa w której wartości są wierzchołkami i rodzicami dla wierzchołków w kluczach
    stack<int> path;                                    // Stos gdzie zapisana jest ścieżka od startowego wierzchołka do końcowego
    int v, u, i;

    cin >> n >> m;                                      // Czytamy liczbę wierzchołków i krawędzi
    
    // Tablicę list sąsiedztwa wypełniamy pustymi listami
    for(i = 0; i < n; i++)
        graph.push_back( vector<int>() );

    // Odczytujemy kolejne definicje krawędzi
    for(i = 0; i < m; i++)
    {
        cin >> v >> u;                                  // Wierzchołek startowy i końcowy krawędzi
        graph[v].push_back(u);
    }

    // Odczytujemy wierzczołek startowy i końcowy ścieżki
    cin >> vs >> vk;

    cout << endl;

    // Szukamy ścieżki, jeśli znaleziono scieżkę wypisujemy ją
    if( bfs_path(vs, vk, graph, predecessors) )
    {
        path.push(vk);
        v = predecessors[vk];

        while (v > -1)
        {
            path.push(v);
            v = predecessors[v];
        }

        while (!path.empty())
        {
            v = path.top();
            path.pop();
            cout << v <<setw(3);
        }

    }
    else                                                // Jeśli nie znaleziono ścieżki wypisujemy BRAK
        cout << "No path" << endl;

    cout << endl;

    return 0;
}
