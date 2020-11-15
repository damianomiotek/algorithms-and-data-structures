#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

vector< vector<int> > graph_transposition(const vector< vector<int> > &A, const int &n)
{
    // Inicjalizacja listy sąsiedztwa, która będzie reprezentować transponowany graf 
    vector< vector<int> > AT;
    // Listę sąsiedztwa wypełniamy pustymi listami
    for(int i = 0; i < n; i++)
        AT.push_back( vector<int>() );


    // Wyznaczenie grafu transponowanego
    for(int v = 0; v < n; v++)
        for(const int node : A[v])
            AT[node].push_back(v);

    return AT;
}

// **********************
// *** PROGRAM GŁÓWNY ***
// **********************
int main()
{
    int n, m, i;                                // Liczba wierzchołków i krawędzi
    vector< vector<int> > A, AT;                // Listy sąsiedztwa
    int v, u;                                   // Zmienne pomocnicze

    cin >> n >> m;                              // Odczytujemy liczbę wierzchołków i krawędzi

    // Listę sąsiedztwa wypełniamy pustymi listami
    for(i = 0; i < n; i++)
        A.push_back( vector<int>() );

    // Odczytujemy definicje krawędzi
    for(i = 0; i < m; i++)
    {
        cin >> v >> u;                        // Wierzchołek startowy i końcowy krawędzi
        A[v].push_back(u);
    }

    // Wyznaczamy graf transponowany
    AT = graph_transposition(A, n);

    // Wypisujemy graf transponowany
    cout << endl;
    for( v = 0; v < n; v++ )
    {
        cout << v << ":";
        for( const int node : AT[v] ) 
            cout << " " << node;
        cout << endl;
    }

    return 0;
}