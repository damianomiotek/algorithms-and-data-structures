#include <iostream>
#include <stack>
#include <vector>
#include <iomanip>

using namespace std;

// DFS do przechodzenia grafu. Zamiast tablicy visited wykorzystujemy 
// tablicę connected_components z numerami spójnych składowych
void dfs(int &vs, vector< vector<int> > &graph, vector<int> &connected_components, int &cn)
{
    stack<int> s;                                           // Stos dla DFS
    int v, u;

    s.push(vs);                                             // Na stosie umieszczamy wierzchołek startowy
    connected_components[vs] = cn;                          // i oznaczamy go jako odwiedzonego i ponumerowanego

    while (!s.empty())
    {
        v = s.top();                                        // Odczytujemy wierzchołek ze stosu
        s.pop();                                            // Usuwamy ze stosu odczytany wierzchołek

        // Przechodzimy przez sąsiadów odczytanego wierzchołka
        for (const int &neighbor : graph[v])
        {
            // Jeśli sąsiad nie był jeszcze odwiedzony to umieszczamy go na stosie i 
            // zaznaczamy jako odwiedzonego wpisując w connected_components numer jego spójnej składowej
            if (!connected_components[neighbor])
            {
                s.push(neighbor);
                connected_components[neighbor] = cn;
            }
        }
    }
}

// **********************
// *** PROGRAM GŁÓWNY ***
// **********************
int main()
{
    int n, m;                                               // Liczba wierzchołków i krawędzi
    vector< vector<int> > graph;                            // Graf jako tablica list sąsiedztwa
    vector<int> connected_components;                       // Tablica z numerami spójnych składowych
    int cn, i, j, v, u;

    cin>>n>>m;                                              // Czytamy liczbę wierzchołków i krawędzi

    // Graf wypełniamy pustymi listami, a tablicę spójnych składowych wypełniamy zerami
    for(i = 0; i < n; i++)
    {
        graph.push_back( vector<int>() );
        connected_components.push_back(0);
    }

    // Odczytujemy definicje krawędzi dla grafu nieskierowanego
    for(int i = 0; i < m; i++)
    {
        cin >> v >> u;                                      // Wierzchołek startowy i końcowy krawędzi
        graph[v].push_back(u);
        graph[u].push_back(v);                              // To samo dla krawędzi w drugą stronę
    }

    cout<<endl;

    cn = 0;                                                 // Zerujemy licznik spójnych składowych
    for(i = 0; i < n; i++)
        if(!connected_components[i])                        // Szukamy nieodwiedzonego jeszcze wierzchołka
        {
            cn++;                                           // Zwiększamy licznik składowych
            dfs(i, graph, connected_components, cn);
        }

    for(i = 1; i <= cn; i++)
    {
        cout << "Connected component no. " << i << ":";
        for(j = 0; j < n; j++)
            if(connected_components[j] == i)
                cout << "  " << j;                          // Wierzchołki tej składowej

        cout << endl;
    }

    cout << endl;

    return 0;
}