#include <iostream>
#include <queue>
#include <vector>
#include <iomanip>

using namespace std;

void bfs(const int vs, const vector< vector<int> > &graph, const int &n)
{
    queue<int>q;                                    // Kolejka dla BFS
    int v;
    vector<bool> visited(n, false);                 // Tworzymy tablicę odwiedzin i wypełniamy ją wartościami false

    q.push(vs);                                     // W kolejce umieszczamy wierzchołek startowy
    visited [ vs ] = true;                          // Wierzchołek vs oznaczamy jako odwiedzony

    while(!q.empty())
    {
        v = q.front();                              // Odczytujemy wierzchołek z kolejki
        cout << v << setw(3);                       // Wyświetlamy odczytany wierzchołek
        q.pop();                                    // Usuwamy z kolejki odczytany wierzchołek

        // Przechodzimy przez sąsiadów odczytanego wierzchołka
        for(const int & neighbor : graph[v])
        {
            //Jeśli sąsiad nie był jeszcze odwiedzony to umieszczamy go w kolejce i zaznaczamy jako odwiedzonego
            if(!visited[neighbor])
            {
                q.push(neighbor);
                visited[neighbor] = true;
            }
        }
    }
}

// **********************
// *** PROGRAM GŁÓWNY ***
// **********************
int main()
{
    int n, m;                                       // Liczba wierzchołków i krawędzi
    vector< vector<int> > adjacement_list;          // Graf jako lista sąsiedztwa
    int v1, v2, i;                                  // Zmienne pomocnicze

    cin>>n>>m;                                      // Czytamy liczbę wierzchołków i krawędzi

    // Listę sąsiedztwa wypełniamy pustymi listami
    for(i = 0; i < n; i++)
        adjacement_list.push_back( vector<int>() );

    // Odczytujemy definicje krawędzi
    for(i = 0; i < m; i++)
    {
        cin >> v1 >> v2;                            // Wierzchołek startowy i końcowy krawędzi
        adjacement_list[v1].push_back(v2);
    }

    cout<<endl;

    //Przechodzimy graf wszerz
    bfs(0, adjacement_list, n);

    cout << endl;

    return 0;
}
