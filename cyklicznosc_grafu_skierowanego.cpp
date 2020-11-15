#include <iostream>
#include <vector>

using namespace std;

// Funkcje badające cykliczność grafu
bool isGraphCyclic(vector< vector<int> > &graph, int v, char * visited)
{
    int u;
    visited[ v ] = 'G';                                         // Kolorujemy wierzchołek na szaro

    // Przeglądamy jego listę sąsiadów
        for(vector<int>::iterator p = graph[v].begin(); p != graph[v].end(); p++)
        {
            u = *p;                                             // u -> numer sąsiada
            if(visited[u] == 'G')
                return true;                                    // Sąsiad szary - mamy cykl, przerywamy
            if( (visited[u] == 'W') && (isGraphCyclic(graph, u, visited)) )      // Wywołanie rekurencyjne
                return true;
        }

    visited[ v ] = 'B';                                         // Kolorujemy wierzchołek na czarno
    return false;
}

bool isCyclic(vector< vector<int> > &graph)
{
    int i;
    int n = graph.size();
    char *visited;
    
    visited = new char[n];                                // Tworzymy tablicę odwiedzin

    for(i = 0; i < n; i++)                                      // Zerujemy ją
        visited[i] = 'W';

    for(i = 0; i < n; i++)
        if( (visited[i] == 'W') && (isGraphCyclic(graph, i, visited)) )
        {
            delete [] visited;
            return true;
        }

    delete [] visited;
    return false;
}
// **********************
// *** PROGRAM GŁÓWNY ***
// **********************
int main()
{
    vector< vector<int> > graph;                                // Graf jako tablica list sąsiedztwa
    int n, m;                                                   // Liczba wierzchołków i krawędzi
    int i, u, v;                                                // Numery wierzchołków
    vector<int>list;                                            // Lista sąsiedztwa

    cin >> n >> m;                                              // Odczytujemy liczbę wierzchołków i krawędzi
    
    // Graf wypełniamy pustymi listami
    for(i = 0; i < n; i++)
        graph.push_back(list);

    // Odczytujemy kolejne definicje krawędzi
    for(i = 0; i < m; i++)
    {
        cin>>v>>u;
        graph[v].insert(graph[v].begin(), u);
    }
    
    if(isCyclic(graph))
        cout << "CYCLIC GRAPH" << endl;
    else
        cout << "ACYCLIC GRAPH" << endl;

    cout << endl;
    return 0;
}
