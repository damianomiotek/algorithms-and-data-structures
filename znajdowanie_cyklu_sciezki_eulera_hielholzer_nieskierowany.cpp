#include <iostream>
#include <vector>
#include <list>

using namespace std;

// Zmienne globalne
vector< vector<int> >graph;                                     // Lista sąsiedztwa jako graf
vector<bool>visited;                                            // Tablica odwiedzin
list<int>c;                                                     // Lista przechowująca cykl Eulera dla grafu skierowanego

// Rekurencyjna funkcja dodająca do listy nowy cykl
// v - wierzchołek startowy i końcowy cyklu
// w - wierzchołek bieżący
// p - referencja do wskazania punktu wstawiania na liście
bool dfsAddCycle(const int &v, const int &w, list<int>::iterator &it)
{
    visited[w] = true;                                              // Oznaczamy w jako odwiedzony

    for(int i = 0; i < graph[w].size(); i++)                        // Przeglądamy sąsiadów w
        if(graph[w][i] != -1 && graph[w][i] != *it)
        {
            ++it;
            it = c.insert(it, w);                                   // Dodajemy w do cyklu
            if(graph[w][i] == v)                                    // Cykl znaleziony?
            {
                ++it;
                it = c.insert(it, graph[w][i]);                     // Zamykamy cykl na liście c
                int pom = *it;
                --it;
                while(*it != v)                                     // Usuwamy krawędzie cyklu
                {
                    for(int j = 0; j < graph[pom].size(); j++)      // Usuwanie krawędzi it->pom
                        if(graph[pom][j] == *it)
                        {
                            graph[pom][j] = -1;
                            break;
                        }
                    for(int j = 0; j < graph[*it].size(); j++)      // Usuwanie krawędzi pom->it
                        if(graph[*it][j] == pom)
                        {
                            graph[*it][j] = -1;
                            break;
                        }

                    pom = *it;
                    --it;
                }

                if(*it == v)
                    return true;
            }
            if(!visited[ graph[w][i] ] && dfsAddCycle(v, graph[w][i], it))
                return true;

            it = c.erase(it);                                               // Z listy usuwamy w
            --it;
        }

    return false;
}

void findEuler(const int &v)
{
    c.push_back(v);

    for(list<int>::iterator it = c.begin(); it != c.end(); it++)        // Przeglądamy listę c
        for(int i = 0; i < graph[*it].size(); i++)                      // Szukamy sąsiadów
            if(graph[*it][i] != -1)
            {
                for( int j = 0; j < graph.size(); j++ ) 
                    visited [ j ] = false;
                dfsAddCycle(*it, graph[*it][i], it);                    // Dla każdego sąsiada uruchamiamy szukanie cyklu
            }
}

// **********************
// *** PROGRAM GŁÓWNY ***
// **********************
int main()
{
    int n, m;                                                       // Liczba wierzchołków i krawędzi
    int i, u, v;                                                    // Numery wierzchołków
    vector<int>emptyList;                                           // Lista sąsiedztwa

    cin >> n >> m;                                                  // Odczytujemy liczbę wierzchołków i krawędzi
    
    // Graf wypełniamy pustymi listami, a tablicę visited wartościami false
    for(i = 0; i < n; i++)
    {
        graph.push_back(emptyList);
        visited.push_back(false);
    }

    // Odczytujemy kolejne definicje krawędzi
    for(i = 0; i < m; i++)
    {
        cin>>v>>u;
        graph[v].push_back(u);
        graph[u].push_back(v);                                      // Graf nieskierowany
    }
    
    cout << endl;

    findEuler(v);                                                   // Szukamy cyklu Eulera gdzie punktem startowym
                                                                    // jest ostatnio wczytany wierzchołek(nie sąsiad)

    // Wyświetlamy zawartość listy C, czyli pełny cykl Eulera
    for(const auto el : c)
        cout << el << " ";
    cout << endl;

    return 0;

}