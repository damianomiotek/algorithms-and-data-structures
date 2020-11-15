#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;


// Rekurencyjna procedura przejścia w głąb
//----------------------------------------
void dfs(const int v, const vector< vector<int> > &graph, vector<bool> &visited)
{
    visited[v] = true;                          // Zaznaczamy wierzchołek jako odwiedzony
    cout << v << setw(3);

    // Rekurencyjnie odwiedzamy nieodwiedzonych sasiadów
    for(const int neighbor : graph[v])
        if(!visited[neighbor]) 
            dfs(neighbor, graph, visited);
}


// **********************
// *** PROGRAM GŁÓWNY ***
// **********************
int main()
{
    int n, m, v1, v2, i;                        // Liczba wierzchołków i krawędzi oraz zmienne pomocnicze
    vector< vector<int> > adjacement_list;      // Lista sąsiedztwa

    cin>>n>>m;                                  // Czytamy liczbę wierzchołków i krawędzi
    vector<bool> visited(n, false);             // Tworzymy tablicę odwiedzin i wypełniamy ją wartościami false

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
    dfs(0, adjacement_list, visited);

    cout << endl;

    return 0;
}