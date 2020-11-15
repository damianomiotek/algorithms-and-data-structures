#include <iostream>
#include <vector>
#include <stack>

using namespace std;

// Funkcja bada graf pod kątem posiadania cyklu lub ścieżki Eulera
// n    - liczba wierzchołków w grafie
// graf - tablica list sąsiedztwa
// Wynik:
// 0 - graf nie zawiera ścieżki lub cyklu Eulera
// 1 - graf zawiera ścieżkę Eulera
// 2 - graf zawiera cykl Eulera
int isEulerian(const int &n, vector< vector<int> > & graph)
{
    int nc, no, i, v, u;
    stack<int> s;
    vector<int> visited;

    // Szukamy pierwszego wierzchołka z sąsiadami
    for(i = 0; (i < n) && (graph[i].size() == 0); i++)

    if(i == n)                                              // Graf nie ma krawędzi
        return 0;

    for(v = 0; v < n; v++)                                  // Tablicę odwiedzin wypełniamy zerami
        visited.push_back(false);

    no = 0;                                                 // Zerujemy licznik odwiedzin o stopniu nieparzystym

    s.push(i);                                              // Wierzchołek startowy na stos
    visited[i] = true;                                      // Oznaczamy go jako odwiedzony

    // Uruchamiamy przejście DFS aby wyznaczyć spójną składową
    // zawierającą wierzchołek startowy oraz policzyć stopnie wierzchołków
    // i wyznaczyć liczbę wierzchołków o stopniach nieparzystych
    while(!s.empty())
    {
        v = s.top();                                        // Pobieramy do v wierzchołek ze stosu
        s.pop();                                            // Pobrany wierzchołek usuwamy ze stosu

        nc = 0;                                             // Licznik sąsiadów na zero
        for(vector<int>::iterator it = graph[v].begin(); it != graph[v].end(); it++)
        {
            nc++;                                           // Zwiększamy licznik sąsiadów
            if(!visited[*it])                               // Szukamy nieodwiedzonych sąsiadów
            {
                visited[*it] = true;                        // Zaznaczamy ich jako odwiedzonych
                s.push(*it);                                // i umieszczamy na stosie
            }
        }
        if(nc%2 == 1)
            no++;                                           // Zwiększamy nieparzystę liczbę sąsiadów
    }
    
    for(v = i; v < n; v++)                                  // Przeglądamy pozostałe wierzchołki grafu
        if(!visited[v] && graph[v].size() > 0)
            return 0;                                       // Graf nie jest spójny

    if(no == 0)                                             // Graf zawiera cykl Eulera
        return 2;
    if(no == 2)                                             // Graf zawiera ścieżkę Eulera
        return 1;

    return 0;                                               // Graf nie zawiera ścieżki lub cyklu Eulera
}

// **********************
// *** PROGRAM GŁÓWNY ***
// **********************
int main()
{
    vector< vector<int> > graph;                            // Graf jako tablica list sąsiedztwa
    int n, m;                                               // Liczba wierzchołków i krawędzi
    int i, u, v;                                            // Numery wierzchołków
    vector<int>list;                                        // Lista sąsiedztwa

    cin >> n >> m;                                          // Odczytujemy liczbę wierzchołków i krawędzi
    
    // Graf wypełniamy pustymi listami
    for(i = 0; i < n; i++)
        graph.push_back(list);

    // Odczytujemy kolejne definicje krawędzi
    for(i = 0; i < m; i++)
    {
        cin>>v>>u;
        graph[v].insert(graph[v].begin(), u);
        graph[u].insert(graph[u].begin(), v);               // Krawędź w drugą stronę, bo graf jest nieskierowany
    }
    
    cout << endl;
    
    switch( isEulerian( n, graph ) )
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