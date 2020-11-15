#include <iostream>
#include <vector>

using namespace std;

// Zmienne globalne
vector< vector<int> > graph;                                    // Graf jako tablica list sąsiedztwa
vector<int>d;                                                   // Numery DFS
int cv;                                                         // Numeracja DFS
vector< pair<int, int> > bridges;                               // Mosty jako para liczb int

// Funkcja rekurencyjna wyszukująca mosty
// v  - numer bieżącego wierzchołka
// vf - ojciec bieżącego wierzchołka na drzewie rozpinającym
// Reszta parametrów to zmienne globalne
int dfsb(const int & v, const int & vf)
{
    int low, temp;

    // Numerujemy wierzchołek, ustalamy wstępną wartość low oraz zwiększamy numerację    
    d[v] = low = cv++;

    // Przeglądamy listę sąsiadów
    for(auto u = graph[v].begin(); u != graph[v].end(); u++)
        if(*u != vf)                                            // u nie może być ojcem v
        {
            if(d[*u] == 0)                                      // Jeśli sąsiad nie był odwiedzony to,
            {
                temp = dfsb(*u, v);                             // Rekurencyjnie odwiedzamy go
                if(temp < low)
                    low = temp;
            }
            else if(d[*u] < low)
                low = d[*u];
        }

    // Wszyscy sąsiedzi zostali odwiedzeni. Teraz robimy test na most
    if(d[v] == low && vf > -1)
        bridges.insert(bridges.begin(), make_pair(vf, v));

    return low;
}

// **********************
// *** Program główny ***
// **********************
int main( )
{
    int n, m;                                                   // Liczba wierzchołków i krawędzi
    int i, u, v;                                                // Numery wierzchołków
    vector<int>list;                                            // Lista sąsiedztwa
    int parentFirstEdge = -1;

    cin >> n >> m;                                              // Odczytujemy liczbę wierzchołków i krawędzi
    
    // Graf wypełniamy pustymi listami a numery DFS ustawiamy na 0
    for(i = 0; i < n; i++)
    {
        graph.push_back(list);
        d.push_back(0);
    }

    // Odczytujemy kolejne definicje krawędzi
    for(i = 0; i < m; i++)
    {
        cin>>v>>u;
        graph[v].insert(graph[v].begin(), u);
        graph[u].insert(graph[u].begin(), v);
    }

    // Szukamy mostów
    for(i = 0; i < n; i++)
        if(d[i] == 0)                                           // Szukamy niedwiedzonego wierzchołka
        {
            cv = 1;                                             // Początek numeracji DFS
            dfsb(i, parentFirstEdge);                           // Szukamy mostów
        }

    // Wypisujemy znalezione mosty
    cout << endl;
    for(pair<int, int> p : bridges)
        cout << p.first << " " << p.second << endl;


    return 0;
}