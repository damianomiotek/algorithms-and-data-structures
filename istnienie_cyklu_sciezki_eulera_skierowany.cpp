#include <iostream>
#include <vector>
#include <stack>
#include <cstdlib>

using namespace std;

// Zmienne globalne
vector< vector<int> > graph;                                // Graf jako tablica list sąsiedztwa
vector<int> vn, vlow, vind, voutd, c;
vector<bool>visited;
stack<int>s;
int cvn;

// Procedura wykonująca przejście DFS i wyznaczająca
// silnie spójną składową oraz stopnie wierzchołków
// v - wierzchołek startowy dla DFS
void DFSscc(int v)
{
    int u;
    vn[v] = vlow[v] = ++cvn;                                // Ustalamy wstępnie parametr low
    s.push(v);                                              // Wierzchołek na stos
    visited[v] = true;                                      // Zapamiętujemy że v jest na stosie

    for(vector<int>::iterator it = graph[v].begin(); it != graph[v].end(); it++)
    {
        ++voutd[v];                                         // Zwiększamy stopień wychodzący
        ++vind[*it];                                        // i wchodzący

        if(!vn[*it])                                        // Jeśli sąsiad jest nieodwiedzony, to
        {
            DFSscc(*it);                                    // Wywołujemy dla niego rekurencyjnie DFS
            vlow[v] = min(vlow[v], vlow[*it]);              // i obliczamy parametr Low dla v
        }
        else if(visited[*it])                               // Jeśli sąsiad odwiedzony, lecz wciąż na stosie,
            vlow[v] = min(vlow[v], vn[*it]);                // to wyznaczamy parametr Low dla v
    }

    if(vlow[v] == vn[v])                                    // Sprawdzamy czy mamy kompletną składową
        do
        {
            u = s.top();                                    // Pobieramy wierzchołek ze stosu
            s.pop();                                        // Pobrany wierzchołek usuwamy ze stosu
            visited[u] = false;                             // Zapamiętujemy że nie ma go już na stosie
            c[u] = v;                                       // Zapamiętujemy numer silnie spójnej składowej
        } while(u != v);                                    // Kontynujemy aż do korzenia składowej
        
}

// Funkcja bada istnienie cyklu lub ścieżki Eulera
// Zwraca:
// 0 - brak cyklu i ścieżki
// 1 - jest ścieżka Eulera
// 2 - jest cykl Eulera
int isEulerian(const int &n)
{
    int v, cinout, coutin;
    cvn = 0;                                                // Zerujemy numer wierzchołka
    for(v = 0; v < n; v++)                                  // Przeglądamy kolejne wierzchołki
        if(!vn[v])                                          // W wierzchołku nieodwiedzonym uruchamiamy DFS
            DFSscc(v);

    // Szukamy pierwszego wierzchołka o niezerowym stopniu
    for(v = 0; v < n && (vind[v] + voutd[v] == 0); v++)
        ;

    if(v == n)
        return 0;                                           // Graf jest pusty

    cvn = c[v];                                             // Zapamiętujemy numer silnie spójnej składowej
    cinout = coutin = 0;                                    // Zerujemy liczniki

    for(; v < n; v++)                                       // Przeglądamy graf
    {
        if(vind[v] + voutd[v] > 0)
        {
            if(c[v] != cvn)
                return 0;                                   // Graf nie jest silnie spójny

            if(vind[v] != voutd[v])
            {
                if(vind[v] - voutd[v] == 1)
                {
                    if(++cinout > 1)
                        return 0;                           // Za dużo wierzchołków o nierównych stopniach
                }
                else if(voutd[v] - vind[v] == 1)
                {
                    if(++coutin > 1)                        // Za dużo wierzchołków o nierównych stopniach
                        return 0;
                }
                else
                    return 0;                               // Stopnie różnią się o więcej niż 1   
            }
        }
    }

    // Analizujemy stan liczników
    if(cinout == 1)
        return 1;                                           // Mamy ścieżkę Eulera
    else
        return 2;                                           // Mamy cykl Eulera
}

// **********************
// *** PROGRAM GŁÓWNY ***
// **********************
int main()
{
    int n, m;                                               // Liczba wierzchołków i krawędzi
    int i, u, v;                                            // Numery wierzchołków
    vector<int>list;                                        // Lista sąsiedztwa

    cin >> n >> m;                                          // Odczytujemy liczbę wierzchołków i krawędzi
    
    // Inicjujemy tablice
    for(i = 0; i < n; i++)
    {
        graph.push_back(list);
        vn.push_back(0);
        vind.push_back(0);
        voutd.push_back(0);
        vlow.push_back(0);
        c.push_back(0);
        visited.push_back(false);
    }

    // Odczytujemy kolejne definicje krawędzi
    for(i = 0; i < m; i++)
    {
        cin>>v>>u;
        graph[v].insert(graph[v].begin(), u);
    }
    
    cout << endl;
    
    switch( isEulerian( n ) )
    {
        case 0: 
            cout << "NOT AN EULERIAN GRAPH\n";
            break;
        case 1: 
            cout << "SEMI-EULERIAN GRAPH\n";
            break;
        case 2: 
            cout << "EULERIAN GRAPH\n";
            break;
    }

    cout << endl;
    return 0;
}