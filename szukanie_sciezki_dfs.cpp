#include <iostream>
#include <map>
#include <vector>
#include <stack>
#include <iomanip>


using namespace std;

bool dfs_path(int &vs, int &vk, vector< vector<int> > &graph, map<int, int> &predecessors)
{
    stack<int> s;
    int v, i;

    predecessors.insert( pair<int, int>(vs, -1) );                      // Poprzednik elementu startowego to -1
    s.push(vs);                                                         // Na stosie umieszczamy wierzczołek startowy

    while(!s.empty())
    {
        v = s.top();                                                    // Pobieramy ze stosu wierzchołek v
        s.pop();

        if (v == vk)                                                    // Sprawdzamy czy osiągneliśmy wierzchołek końcowy
            return true;

        // Przeglądamy sąsiadów wierzchołka v
        for(const int &neighbor : graph[v])
        {
            if(predecessors.find(neighbor) == predecessors.end())      // Jeśli sąsiad nie był wcześniej odwiedzony
            {
                predecessors.insert( pair<int, int>(neighbor, v) );     // Zapisujemy ten wierzchołek i jego rodzica
                s.push(neighbor);                                       // Sąsiad zostaje umieszczony na stosie
            }
        }  
    }

    return false;
}        

// **********************
// *** PROGRAM GŁÓWNY ***
// **********************
int main()
{
    int n, m;                                   // Liczba wierzchołków i krawędzi
    vector< vector<int> > graph;                // Graf jako lista sąsiedztwa
    int vs, vk;                                 // Wierzchołek startowy i końcowy
    map<int, int> predecessors;                 // Mapa gdzie kluczem jest wierzchołek, a wartością wierzchołek z którego przyszło się do wierzchołka który jest kluczem
    stack<int>path;                             // Stos gdzie zapisana jest ścieżka od startowego wierzchołka do końcowego
    int i, v, u;                                // Zmienne pomocnicze

    cin >> n >> m;                              // Czytamy liczbę wierzchołków i krawędzi
    
    // Tablicę list sąsiedztwa wypełniamy pustymi listami
    for(i = 0; i < n; i++)
        graph.push_back( vector<int>() );

    // Odczytujemy kolejne definicje krawędzi
    for(i = 0; i < m; i++)
    {
        cin >> v >> u;                          // Wierzchołek startowy i końcowy krawędzi
        graph[v].push_back(u);
    }

    // Odczytujemy wierzczołek startowy i końcowy ścieżki
    cin >> vs >> vk;

    cout << endl;

    // Szukamy ścieżki, jeśli znaleziono scieżkę wypisujemy ją
    if( dfs_path(vs, vk, graph, predecessors) )
    {
        int v = predecessors[vk];
        path.push(vk);
        while (v > -1)
        {
            path.push(v);
            v = predecessors[v];
        }

        while(!path.empty())
        {
            v = path.top();
            path.pop();
            cout << v << setw(3);
        }

    }
    else                                        // Jeśli nie znaleziono ścieżki wypisujemy No Path
        cout << "No Path" << endl;

    cout << endl;

    return 0;
}