#include <iostream>
#include <stack>
#include <vector>
#include <iomanip>

using namespace std;

// DFS do przechodzenia grafu nieskierowanego. Algorytm zwraca ilość odwiedzonych wierzchołków.
int dfs(int vs, vector< vector<int> > &graph, int &n)
{
    stack<int> s;                                   // Stos dla DFS
    int num_visited_vertices = 0;
    int v;
    vector<bool> visited(n, false);                 // Tworzymy tablicę odwiedzin i wypełniamy ją wartościami false

    s.push(vs);                                     // Na stosie umieszczamy wierzchołek startowy
    visited[vs] = true;                             // Wierzchołek vs oznaczamy jako odwiedzony

    while(!s.empty())
    {
        v = s.top();                                // Odczytujemy wierzchołek ze stosu
        num_visited_vertices++;                     // Zwiększamy licznik wierzchołków
        s.pop();                                    // Usuwamy ze stosu odczytany wierzchołek

        // Przechodzimy przez sąsiadów odczytanego wierzchołka
        for(const int &neighbor : graph[v])
        {
            //Jeśli sąsiad nie był jeszcze odwiedzony to umieszczamy go na stosie i zaznaczamy jako odwiedzonego
            if(!visited[neighbor])
            {
                s.push(neighbor);
                visited[neighbor] = true;
            }
        }
    }

    return num_visited_vertices;
}

// **********************
// *** PROGRAM GŁÓWNY ***
// **********************
int main()
{
    int n, m, i, v, u, num_vertices;
    vector< vector<int> > graph;                // Graf jako lista sąsiedztwa

    cin>>n>>m;                                  // Czytamy liczbę wierzchołków i krawędzi

    // Tablicę list sąsiedztwa wypełniamy pustymi listami
    for(i = 0; i < n; i++)
        graph.push_back( vector<int>() );

    // Odczytujemy definicje krawędzi
    for (int i = 0; i < m; i++)
    {
        cin >> v >> u;                          // Wierzchołek startowy i końcowy krawędzi
        graph[v].push_back(u);
        graph[u].push_back(v);                  // To samo dla krawędzi w drugą stronę
    }

    cout<<endl;

    //Badamy spójność grafu nieskierowanego
    num_vertices = dfs(0, graph, n);

    // Wyświetlamy wynik
    if (num_vertices == n)
        cout << "Connected graph";
    else
        cout << "Dicsonneted graph";
    cout << endl;

    return 0;
}