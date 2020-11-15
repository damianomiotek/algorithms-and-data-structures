#include <iostream>
#include <vector>
#include <stack>

using namespace std;

// Funkcja bada cykliczność składowej grafu
bool isComponentCyclic(vector< vector<int> > &graph, int &v, bool *visited)
{
    stack<int> s;                                               // Stos
    int w, z, i;                                             // Zmienne pomocnicze

    s.push( v ); s.push( -1 );                                  // Na stos wierzchołek startowy i -1
    visited[v] = true;                                          // Oznaczamy wierzchołek jako odwiedzony
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
                return true;                                    // Kończymy z wynikiem true
            }    
        }
    }
    return false;                                               // Kończymy z wynikiem false
}

// Funkcja bada cykliczność grafu
bool isCyclic(vector< vector<int> > &graph)
{
    int i;
    int n = graph.size();
    bool *visited = new bool[ n ];                              // Tworzymy tablicę odwiedzin
    for(i = 0; i < n; i++)                                      // i zerujemy ją
        visited[i] = false;

    for(i = 0; i < n; i++)                                      // Szukamy wierzchołka startowego
    {
        if(!visited[i] && isComponentCyclic(graph, i, visited))
        {
            delete [] visited;
            return true;                                        // Graf znaleziony, kończymy z true
        }
    }

    delete [] visited;
    return false;                                               // Graf nie posiada cyklu, kończymy z false
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
