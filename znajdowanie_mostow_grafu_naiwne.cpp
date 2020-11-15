#include <iostream>
#include <stack>
#include <vector>

using namespace std;

// Funkcja oblicza liczbę spójnych składowych w grafie
// n    - liczba wierzchołków w grafie
// graph - tablica list sąsiedztwa
int ccn(int n, vector<vector<int> > &graph)
{
    int * C, cc, i, j, v, u;
    stack<int> s;

    C = new int [ n ];                          // Tworzymy tablicę spójnych składowych
    for( i = 0; i < n; i++ ) 
        C [ i ] = 0;                            // Zerujemy tablicę spójnych składowych

    cc = 0;                                     // Zerujemy licznik spójnych składowych

    for (i = 0; i < n; i++)
    {
        if(!C[i])                               // Szukamy nieodwiedzonego jeszcze wierzchołka        
        {
            cc++;                               // Zwiększamy licznik składowych
            s.push(i);                          // Na stosie umieszczamy numer bieżącego węzła
            C[i] = cc;                          // Wierzchołek numerujemy i oznaczamy jako odwiedzony

            while(!s.empty())                   // Przechodzimy graf algorytmem DFS
            {
                v = s.top();                    // Pobieramy wierzchołek
                s.pop();                        // Usuwamy wierzchołek ze stosu

                for(j = 0; j < graph[v].size(); j++ )
                {
                    u = graph[v][j];
                    if (!C[u])
                    {
                        s.push(u);              // Na stos idą sąsiedzi nieodwiedzeni
                        C[u] = cc;              // i ponumerowani
                    }
                }
            }
        }
    }

    delete [ ] C;                               // Usuwamy tablicę C
    return cc;                                  // Zwracamy wynik
}

void removeEdge(int edge1, int edge2, vector< vector<int> > &graph)
{
    vector<int>::iterator edgeIterator = graph[edge1].begin();
    while(*edgeIterator != edge2)
        edgeIterator++;
    graph[edge1].erase(edgeIterator);

    edgeIterator = graph[edge2].begin();
    while(*edgeIterator != edge1)
        edgeIterator++;
    graph[edge2].erase(edgeIterator);
}

// **********************
// *** Program główny ***
// **********************
int main( )
{
    vector<vector<int> >graph;                  // Graf jako tablica list sąsiedztwa
    int n, m;                                   // Liczba wierzchołków i krawędzi
    int nc, i, v, u;
    vector<int>list;
    vector< pair<int, int> > bridges;           // Mosty w grafie

    cin >> n >> m;                              // Czytamy liczbę wierzchołków i krawędzi

    // Graf wypełniamy pustymi listami
    for(i = 0; i < n; i++)
        graph.push_back(list);

    // Odczytujemy kolejne definicje krawędzi
    for( i = 0; i < m; i++ )
    {
        cin >> v >> u;
        graph[v].push_back(u);
        graph[u].push_back(v);
    }

    // Algorytm znajdowania mostów
    nc = ccn(n, graph);                         // Zapamiętujemy liczbę spójnych składowych
    for(v = 0; v < n; v++)                      // Przechodzimy przez kolejne wierzchołki grafu
        for(i = 0; i < graph[v].size(); i++)    // Przeglądamy listę sąsiedztwa wierzchołka v
        {
            u = graph[v][i];                    // u - numer wierzchołka sąsiedniego w grafie
            if (u > v)
            {
                removeEdge(v, u, graph);
                if(ccn(n, graph) > nc)
                    bridges.push_back(make_pair(v, u));     // Znaleziony most dodajemy do listy

                // Krawędź usuniętą z powrotem dodajemy do grafu
                graph[v].insert(graph[v].begin(), u);
                graph[u].insert(graph[u].begin(), v);
            }
        }

    // Wyświetlamy znalezione mosty grafu
    cout << endl;
    for(pair<int, int> p : bridges)
    {
        cout << p.first << " " << p.second << endl;
    }



    return 0;
}