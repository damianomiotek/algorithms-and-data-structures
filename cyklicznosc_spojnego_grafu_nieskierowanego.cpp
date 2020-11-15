#include <iostream>
#include <vector>
#include <stack>

using namespace std;

// Funkcja bada cykliczność grafu
bool isCyclic(vector< vector<int> > &graph)
{
    stack<int> s;                                               // Stos
    bool *visited;                                              // Tablica odwiedzin
    int w, v, z, i;                                             // Zmienne pomocnicze
    int n = graph.size();                                       // Liczba wierzchołków w grafie

    visited = new bool[n];                                      // Tworzymy tablicę odwiedzin
    for(i = 0; i < n; i++)                                      // i zerujemy ją
        visited[i] = false;

    s.push( 0 ); s.push( -1 );                                  // Na stos wierzchołek startowy i -1
    visited[0] = true;                                          // Oznaczamy wierzchołek jako odwiedzony
    while(!s.empty())                                           // W pętli przechodzimy graf za pomocą DFS
    {
        w = s.top(); s.pop();                                   // Pobieramy ze stosu wierzchołek z którego przyszliśmy
        v = s.top(); s.pop();                                   // oraz wierzchołek bieżący

        // Przeglądamy jego listę sąsiadów
        for(vector<int>::iterator p = graph[v].begin(); p != graph[v].end(); p++)
        {
            z = *p;                                             // Numer sąsiada
            if(!visited[z])
            {
                s.push(z); s.push(v);                           // Sąsiada nieodwiedzonego umieszczamy na stosie
                visited[z] = true;                              // Oznaczamy go jako odwiedzonego
            }
            else if(z != w)                                     // Jeśli sąsiad jest odwiedzony i nie jest wierzchołkiem
            {                                                   // z którego przyszliśmy, to odkryliśmy cykl
                delete [] visited;                              // Usuwamy zmienne pomocnicze
                return true;                                    // Kończymy z wynikiem true
            }    
        }
    }
    delete [] visited;                                          // W grafie nie ma cykli
    return false;                                               // Kończymy z wynikiem false
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
        graph[u].insert(graph[u].begin(), v);
    }
    
    if(isCyclic(graph))
        cout << "CYCLIC GRAPH" << endl;
    else
        cout << "ACYCLIC GRAPH" << endl;
    

    cout << endl;
    return 0;
}