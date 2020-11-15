#include <iostream>
#include <stack>
#include <vector>
#include <iomanip>

using namespace std;

// Stosowa procedura przejścia w głąb
//----------------------------------------
void dfs(const int vs, const vector< vector<int> > &graph, const int &n)
{
    stack<int> s;                                   // Stos dla DFS
    int v;
    vector<bool> visited(n, false);                 // Tworzymy tablicę odwiedzin i wypełniamy ją wartościami false


    s.push(vs);                                     // Na stosie umieszczamy wierzchołek startowy
    visited[vs] = true;                             // Wierzchołek vs oznaczamy jako odwiedzony

    while(!s.empty())
    {
        v = s.top();                                // Odczytujemy wierzchołek ze stosu
        cout << v << setw(3);                       // Wyświetlamy odczytany wierzchołek
        s.pop();                                    // Usuwamy ze stosu odczytany wierzchołek

        // Przechodzimy przez sąsiadów odczytanego wierzchołka
        for(const int &neighbor : graph[v])
        {
            //Jeśli sąsiad nie był jeszcze odwiedzony to umieszczamy go na stosie i zaznaczamy jako odwiedzonego
            if(!visited[neighbor])
            {
                s.push(neighbor);
                visited[neighbor] = true;
            }
        }
    }
}

// **********************
// *** PROGRAM GŁÓWNY ***
// **********************
int main()
{
    int n, m, v1, v2, i;                        // Liczba wierzchołków i krawędzi oraz zmienne pomocnicze
    vector< vector<int> > adjacement_list;      // Lista sąsiedztwa
    cin>>n>>m;                                  // Czytamy liczbę wierzchołków i krawędzi

    // Listę sąsiedztwa wypełniamy pustymi listami
    for(i = 0; i < n; i++)
        adjacement_list.push_back( vector<int>() );

    // Odczytujemy definicje krawędzi
    for(i = 0; i < m; i++)
    {
        cin >> v1 >> v2;                        // Wierzchołek startowy i końcowy krawędzi
        adjacement_list[v1].push_back(v2);
    }

    cout<<endl;

    //Przechodzimy graf w głąb
    dfs(0, adjacement_list, n);

    cout << endl;

    return 0;
}