#include <iostream>
#include <stack>
#include <vector>

using namespace std;

// Funkcja rekurencyjna wyszukująca cykl
bool dfsFindCycle(vector <vector<int> > &graph, const int &v, const int &w, stack<int> &s, bool * visited)
{
    visited[w] = true;                                          // Oznaczamy wierzczhołek jako odwiedzony
    // Przeglądamy sąsiadów
    for(vector<int>::iterator it = graph[w].begin(); it != graph[w].end(); it++)
        if(*it != s.top())                                      // Pomijamy wierzchołek z którego przyszliśmy
        {
            s.push(w);                                          // Na stos wierzchołek bieżący
            if(*it == v)                                        // Cykl znaleziony, kończymy
                return true;
            if(!visited[*it] && dfsFindCycle(graph, v, *it, s, visited))
                return true;
            s.pop();
        }

    return false;
}

void findCycles(vector <vector<int> > &graph, const int &n)
{
    bool *visited = new bool[ n ];                              // Tworzymy tablicę odwiedzin
    stack<int>s;                                                // Tworzymy stos zawierający odwróconą ścieżkę cyklu
    for(int i = 0; i < n; i++)                                  // Przechodzimy przez kolejne wierzchołki grafu
    {
        for(int i = 0; i < n; i++)                              // Zerujemy tablicę odwiedzin
            visited[i] = false;

        s.push(-1);                                             // Na stos znacznik początku ścieżki
        if( !dfsFindCycle(graph, i, i, s, visited))             // Szukamy cyklu
        {
            s.pop();                                            // Usuwamy ze stosu początek ścieżki
            cout << " - no cycle\n";                            // Komunikat
        }
        else                                                    // Wypisujemy cykl jeśli istnieje
        {
            stack<int>s1;
            while(!s.empty())                                   // Przerzucamy ścieżkę ze stosu s do stosu s1 i tym samym odwracamy kolejność cyklu na właściwą
            {
                s1.push(s.top());
                s.pop();
            }
            s1.pop();                                           // -1 nie wyświetlamy
            while(!s1.empty())                                  // Wyświetlamy znaleziony cykl
            {
                cout << s1.top() << " " ;
                s1.pop();
            }
            cout << i;                                              // Wypisujemy wierzchołek startowy cyklu jako koniec cyklu
            cout << endl;
        }
    }

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
    
    cout << endl;
    
    findCycles(graph, n);

    cout << endl;
    return 0;
}