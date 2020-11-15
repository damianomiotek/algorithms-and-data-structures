#include <iostream>
#include <vector>
#include <list>

using namespace std;

// Zmienne globalne
vector< vector<int> > graph;                                // Graf jako lista sąsiedztwa
list<int> stack;                                            // Tablica-stos
vector<bool>visited;                                        // Tablica odwiedzin
vector< pair<string, list<int>> > hamiltonians;             // Tablica gdzie element jest złożony ze stringa i listy zawierającej cykl lub ścieżkę Hamiltona 
int n;                                                      // Liczba wierzchołków
int d = 0;

// Rekurencyjna procedura wyznaczająca ścieżki i cykle Hamiltona
// v - wierzchołek bieżący
void dfsHamilton(const int &v)
{
    stack.push_back(v);                                         // Wierzchołek v na stos
    if(stack.size() < n)                                        // Jest ścieżka Hamiltona?
    {
        visited[v] = true;                                      // Nie ma, odwiedzamy v
        for(int i = 0; i < graph[v].size(); i++)                // Przeglądamy sąsiadów v
            if(!visited[ graph[v][i] ] )
                dfsHamilton(graph[v][i]);                       // Wywołanie rekurencyjne

        visited[v] = false;                                     // Wycofujemy się z v
    }
    else
    {
        bool test = true;
        for(auto el : hamiltonians)                             // Sprawdzamy czy nie znaleźliśmy wcześniej ścieżki/cyklu w odwróconej kolejności
        {
            test = false;
            auto s = stack.begin();
            for(auto hs = el.second.rbegin(); s != stack.end() && hs != el.second.rend(); s++, hs++)
                if(*s != *hs)
                {
                    test = true;
                    break;
                }
            if(!test)                                           // Jeśli znaleźliśmy wcześniej ścieżkę/cykl w odwróconej kolejności to kończymy przeszukiwanie cykli                                  
                break;
        }

        if(test)                                                // Jeśli nie znaleźliśmy wcześniej odwrotnej ścieżki to dodajemy 
        {                                                       // obecną ścieżkę/cykl do znalezionych ścieżek/cykli
            pair< string, list<int> >p;
            test = false;                                       // Zakładamy brak cyklu
            for(int i = 0; i < graph[v].size(); i++)            // Przeglądamy sąsiadów
                if(graph[v][i] == 0)                            // Jeśli sąsiadem jest wierzchołek 0  
                {
                    test = true;                                // Mamy cykl
                    break;
                }

            if(test)                                            // Tworzymy element hamiltonians dla cyklu Hamiltona
            {
                p.first = "Hamiltonian Cycle :";
                p.second = stack;
                p.second.push_back(0);                          // Dla cyklu dopisujemy wierzchołek startowy
            }
            else                                                // Tworzymy element hamiltonians dla ścieżki Hamiltona
            {
                p.first = "Hamiltonian Path  :";
                p.second = stack;
            }

            hamiltonians.push_back(p);                          // Dodawanie do znalezionych ścieżek/cykli   
        }
    }
    
    stack.pop_back();                                           // Wierzchołek v usuwamy ze stosu
}


// **********************
// *** PROGRAM GŁÓWNY ***
// **********************
int main()
{
    int m;                                                  // Liczba krawędzi
    int i, u, v;                                            // Numery wierzchołków
    vector<int>emptyList;                                   // Lista sąsiedztwa

    cin >> n >> m;                                          // Odczytujemy liczbę wierzchołków i krawędzi
    
    // Graf wypełniamy pustymi listami, a tablicę odwiedzin wartościami false
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
        graph[u].push_back(v);                              // Krawędź w drugą stronę, bo graf jest nieskierowany
    }
    
    cout << endl;
    
    dfsHamilton( 0 );                                       // Wyznaczamy cykle i scieżki Hamiltona

    for(auto el : hamiltonians)                             // Wypisujemy znalezione ścieżki i cykle Hamiltona
    {
        cout << el.first << " ";
        for(list<int>::iterator it = el.second.begin(); it != el.second.end(); it++)
            cout << *it << " ";
        cout << endl;
    }

    return 0;
}