#include <iostream>
#include <vector>
#include <list>

using namespace std;

vector< vector<int> > graph;                                // Graf jako tablica list sąsiedztwa
list<int>s;                                                 // Stos w tablicy

void dfsEuler(const int &v)
{
    int u;
    for( int i = 0; i < graph[v].size(); i++ )              // Przeglądamy sąsiadów
        if(graph[v][i] != -1)
        {
            u = graph[v][i];
            graph[v][i] = -1;                               // Każdą krawędź usuwamy, aby nie była wykorzystana dwukrotnie
            for(int j = 0; j < graph[u].size(); j++)
                if(graph[u][j] == v)
                {
                    graph[u][j] = -1;
                    break;
                }
                
            dfsEuler(u);                                    // Rekurencyjnie wywołujemy procedurę DFS
        }

    s.push_back(v);                                         // Po przetworzeniu, wierzchołek umieszczamy na stosie
}

// **********************
// *** PROGRAM GŁÓWNY ***
// **********************
int main()
{
    int n, m;                                               // Liczba wierzchołków i krawędzi
    int i, u, v;                                            // Numery wierzchołków
    vector<int>emptyList;                                   // Lista sąsiedztwa

    cin >> n >> m;                                          // Odczytujemy liczbę wierzchołków i krawędzi
    
    // Graf wypełniamy pustymi listami
    for(i = 0; i < n; i++)
        graph.push_back(emptyList);

    // Odczytujemy kolejne definicje krawędzi
    for(i = 0; i < m; i++)
    {
        cin>>v>>u;
        graph[v].push_back(u);
        graph[u].push_back(v);                              // Krawędź w drugą stronę, bo graf jest nieskierowany
    }
    
    cout << endl;
    
    dfsEuler( 0 );                                          // Wyznaczamy cykl Eulera

    cout << "EULERIAN CYCLE : ";                            // Wypisujemy zawartość stosu
    for(const auto el : s)
        cout << el << " ";
    cout << endl;

    return 0;
}









// #include <iostream>
// #include <list>
// #include <vector>
// #include <algorithm>

// using namespace std;

// vector< list<int> > graph;                                  // Graf jako tablica list sąsiedztwa
// list<int>s;                                                 // Stos w tablicy

// void dfsEuler(const int &v)
// {
//     for( auto u : graph[v] )
//     {
//         // Każdą krawędź usuwamy, aby nie była wykorzystana dwukrotnie
//         // u = *it;
//         // it = graph[v].erase(graph[v].begin());        
//         // u = graph[v].front();
//         // list<int>::iterator el = std::find(graph[v].begin(), graph[v].end(), u);
//         // graph[v].erase(el);
//         // el = std::find(graph[u].begin(), graph[u].end(), v);
//         // graph[u].erase(el);
//         // if(graph[v].size() == 1)
//         //     u = *(graph[v].end());

//         graph[v].remove(u);
//         graph[u].remove(v);     

//         // for(list<int>::iterator it1 = graph[u].begin(); it1 != graph[u].end(); it1++)
//         //     if(*it1 == v)
//         //     {
//         //         graph[u].erase(it1);
//         //         break;
//         //     }
//         dfsEuler(u);                                        // Rekurencyjnie wywołujemy procedurę DFS
//     }
//     s.push_back(v);                                         // Po przetworzeniu, wierzchołek umieszczamy na stosie
// }

// // **********************
// // *** PROGRAM GŁÓWNY ***
// // **********************
// int main()
// {
//     int n, m;                                               // Liczba wierzchołków i krawędzi
//     int i, u, v;                                            // Numery wierzchołków
//     list<int>emptyList;                                     // Lista sąsiedztwa

//     cin >> n >> m;                                          // Odczytujemy liczbę wierzchołków i krawędzi
    
//     // Graf wypełniamy pustymi listami
//     for(i = 0; i < n; i++)
//         graph.push_back(emptyList);

//     // Odczytujemy kolejne definicje krawędzi
//     for(i = 0; i < m; i++)
//     {
//         cin>>v>>u;
//         graph[v].push_front(u);
//         graph[u].push_front(v);                             // Krawędź w drugą stronę, bo graf jest nieskierowany
//     }
    
//     cout << endl;

//     // for( list<int>::iterator it = graph[v].begin(); it != graph[v].end(); it++)
//     //     cout << *it << " ";
    
//     // int dupa = 0;
//     dfsEuler( 0 );                                          // Wyznaczamy cykl Eulera

//     cout << "EULERIAN CYCLE : ";                            // Wypisujemy zawartość stosu
//     for(const auto el : s)
//         cout << el << " ";
//     cout << endl;

//     return 0;
// }