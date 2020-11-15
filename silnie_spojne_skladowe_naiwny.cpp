#include <iostream>
#include <stack>
#include <vector>
#include <iomanip>


using namespace std;

/*Funkcja bada, czy istnieje ścieżka od u do v
u    - wierzchołek startowy ścieżki
v    - wierzchołek końcowy ścieżki
n    - liczba wierzchołków w grafie
graph - tablica list sąsiedztwa
Wynik:
true - istnieje ścieżka od u do v
false- nie istnieje ścieżka od u do v
*/
bool dfs_path(int &u, int &v, int &n, vector< vector<int> > &graph)
{
    stack<int> s;
    vector<bool> visited(n, false);                     // Tworzymy tablicę odwiedzin i wypełniamy ją wartościami false
    int x;

    s.push(u);                                          // Na stosie umieszczamy wierzczołek startowy
    visited[u] = true;                                  // Wierzchołek startowy oznaczamy jako odwiedzony

    while(!s.empty())
    {
        x = s.top();                                    // Pobieramy wierzchołek ze stosu
        s.pop();                                        // Usuwamy ze stosu odczytany wierzchołek

        // Przeglądamy sąsiadów wierzchołka x
        for(const int & neighbor : graph[x])
        {
            if(neighbor == v)                           // Jeśli sąsiadem jest wierzchołek v to ścieżka została znaleziona
                return true;

            if(!visited[neighbor])
            {
                s.push(neighbor);                       // Sąsiad zostaje umieszczony na stosie
                visited[neighbor] = true;               // i oznaczony jako odwiedzony
            }
        }  
    }

    return false;
}

/*Procedura przechodzi przez graf od wierzchołka startowego start_vertex
i umieszcza w tablicy C informację o przynależności wierzchołków
do określonej silnie spójnej składowej.
v    - wierzchołek startowy
n    - liczba wierzchołków w grafie
graph - tablica list sąsiedztwa
cn   - numer silnie spójnej składowej
connected_components    - tablica numerów silnie spójnych składowych dla wierzchołków
Wynik:
Ustawia tablicę connected_components
*/
void dfs_scc( int &start_vertex, int &n, vector< vector<int> > &graph, int &cn, vector<int> &connected_components )
{
    stack<int> s;
    vector<bool> visited(n, false);
    int i, u;

    s.push(start_vertex);                                                   // Na stosie umieszczamy wierzczołek startowy
    visited[start_vertex] = true;                                           // Wierzchołek startowy oznaczamy jako odwiedzony    
    connected_components[start_vertex] = cn;                                // Ustawiamy dla v numer składowej

    while(!s.empty())
    {
        u = s.top();                                                        // Pobieramy wierzchołek ze stosu
        s.pop();                                                            // Usuwamy ze stosu odczytany wierzchołek

        if( (u != start_vertex) && dfs_path(u, start_vertex, n, graph))     // Jeśli można przejść w odwrotnym kierunku od wierzchołka u do start_vertex
            connected_components[u] = cn;
        
        // Przeglądamy sąsiadów wierzchołka u
        for(const int &neighbor : graph[u])
        {
            if (!visited[neighbor])
            {
                s.push(neighbor);                                           // Nieodwiedzonego sąsiada umieszczamy na stosie
                visited[neighbor] = true;                                   // i oznaczamy jako odwiedzonego
            }
        }
    }
}

// **********************
// *** Program główny ***
// **********************
int main( )
{
    int n, m;                                                               // Liczba wierzchołków i krawędzi
    vector< vector<int> > graph;                                            // Tablica list sąsiedztwa
    vector<int> connected_components;                                       // Tablica z numerami spójnych składowych
    int i, v, u, cn;

    cin >> n >> m;                                                          // Odczytujemy liczbę wierzchołków i krawędzi

    // Graf wypełniamy pustymi listami, a tablicę spójnych składowych wypełniamy zerami
    for(i = 0; i < n; i++)
    {
        graph.push_back( vector<int>() );
        connected_components.push_back(0);
    }

    // Odczytujemy kolejne definicje krawędzi
    for(int i = 0; i < m; i++)
    {
        cin >> v >> u;                                                      // Wierzchołek startowy i końcowy krawędzi
        graph[v].push_back(u);
    }

    // Wyznaczamy silne spójne składowe
    cn = 0;                                                                 // Inicjujemy licznik składowych

    for (v = 0; v < n; v++)                                                 // Przeglądamy kolejne wierzchołki grafu
        if (!connected_components[v])
            dfs_scc(v, n, graph, ++cn, connected_components);               // Wyznaczamy silnie spójną składową

    // Wyświetlamy silnie spójnie składowe
    cout << endl;
    for (i = 1; i <= cn; i++)
    {
        cout << "Strongly connected component no." << setw( 3 ) << i << ":";
        for (v = 0; v < n; v++)
            if (connected_components[v] == i)
                cout << setw ( 3 ) << v;                                    // Wierzchołki tej składowej

        cout << endl;
    }

    cout << endl;

    return 0;
}