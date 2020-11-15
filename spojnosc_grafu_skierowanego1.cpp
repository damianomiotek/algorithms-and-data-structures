#include <iostream>
#include <stack>
#include <vector>
#include <iomanip>

using namespace std;

// DFS do przechodzenia grafu nieskierowanego. Algorytm zwraca ilość odwiedzonych wierzchołków.
int dfs(int vs, vector< vector<int> > &graph, int &n)
{
    stack<int> s;                                   // Stos dla DFS
    int num_visited_vertices = 0;
    int v;
    vector<bool> visited(n, false);                 // Tworzymy tablicę odwiedzin i wypełniamy ją wartościami false

    s.push(vs);                                     // Na stosie umieszczamy wierzchołek startowy
    visited[vs] = true;                             // Wierzchołek vs oznaczamy jako odwiedzony

    while(!s.empty())
    {
        v = s.top();                                // Odczytujemy wierzchołek ze stosu
        num_visited_vertices++;                     // Zwiększamy licznik wierzchołków
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

    return num_visited_vertices;
}

// Tworzy i zwraca graf nieskierowany na podstawie grafu skierowanego
vector< vector<int> > create_undirected_graph(vector< vector<int> > &directed_graph)
{
    vector< vector<int> > undirected_graph(directed_graph);             // Tablica list sąsiedztwa grafu nieskierowanego

    for(int vertex = 0; vertex < directed_graph.size(); vertex++)       // Przechodzimy przez każdy wierzchołek grafu skierowanego     
        for(int & neighbor : directed_graph[vertex])                    // Przechodzimy przez sąsiadów wierzchołka vertex
        undirected_graph[neighbor].push_back(vertex);                   // Tworzymy krawędź w odwrotnum kierunku neighbor->vertex

    return undirected_graph;
}

// **********************
// *** PROGRAM GŁÓWNY ***
// **********************
int main()
{
    int n, m, i, v, u, num_vertices;
    vector< vector<int> > directed_graph;                               // Lista sąsiedztwa dla grafu skierowanego
    vector< vector<int> > undirected_graph;                             // Lista sąsiedztwa dla grafu nieskierowanego
    cin>>n>>m;                                                          // Czytamy liczbę wierzchołków i krawędzi

    // Graf skierowany wypełniamy pustymi listami
    for(i = 0; i < n; i++)
        directed_graph.push_back( vector<int>() );

    // Odczytujemy definicje krawędzi
    for (int i = 0; i < m; i++)
    {
        cin >> v >> u;                                                  // Wierzchołek startowy i końcowy krawędzi
        directed_graph[v].push_back(u);
    }

    // Tworzymy nowy graf nieskierowany z grafu skierowanego
    undirected_graph = create_undirected_graph(directed_graph);

    cout<<endl;

    //Badamy spójność grafu nieskierowanego
    num_vertices = dfs(0, undirected_graph, n);

    // Wyświetlamy wynik
    if (num_vertices == n)
        cout << "Connected graph";
    else
        cout << "Dicsonneted graph";
    cout << endl;

    return 0;
}
