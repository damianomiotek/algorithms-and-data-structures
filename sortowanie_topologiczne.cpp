#include <iostream>
#include <stack>
#include <vector>

using namespace std;

// Zmienne globalne
const char WHITE = 0;             // kolory wierzchołków
const char GRAY  = 1;
const char GREEN = 2;

// Funkcja rekurencyjna wyszukująca cykl
bool dfsTopologicalSort(vector <vector<int> > &graph, const int &v, vector<char> &visited, stack<int> &sortedGraph)
{
    visited[v] = GRAY;                                          // Oznaczamy wierzchołek jako przetwarzany
    // Przeglądamy sąsiadów wierzchołka v
    for(int i = 0; i < graph[v].size(); i++)
        if(visited[ graph[v][i] ] == GRAY)                      // Jeśli wierzchołek jest szary to kończymy z false
            return false;
        else if(visited[ graph[v][i] ] == WHITE)                // Odwiedzamy rekurencyjnie wierzchołki pokolorowane na biało
            if( dfsTopologicalSort(graph, graph[v][i], visited, sortedGraph) == false )
                return false;
                
    visited[v] = GREEN;                                         // Po odwiedzeniu sąsiadów wierzchołek jest przetworzony
    sortedGraph.push(v);                                        // Umieszczamy go na stosie
    return true;
}

bool topologicalSort(vector <vector<int> > &graph, stack<int> &sortedGraph)
{
    int v;
    int verticesNumber = graph.size();                          // Liczba wierzchołków
    vector<char> visited;                                       // Tablica z kolorami wierzchołków
    for(v = 0; v < verticesNumber; v++)                         // Wierzchołki w tablicy visited kolorujemy na biało
        visited.push_back(WHITE);

    for(v = 0; v < verticesNumber; v++)
        if(visited[v] == WHITE)                                 // Dla każdego nieprzetworzonego wierzchołka wywołujemy DFS
            if(dfsTopologicalSort(graph, v, visited, sortedGraph) == false)
                return false;

    return true;
}

// **********************
// *** PROGRAM GŁÓWNY ***
// **********************
int main()
{
    vector< vector<int> > graph;                                // Graf jako tablica list sąsiedztwa
    int n, m;                                                   // Liczba wierzchołków i krawędzi
    int i, u, v;                                                // Numery wierzchołków
    vector<int> list;                                           // Lista sąsiedztwa
    stack<int> sortedGraph;                                     // Stos z wynikowym posortowanym topologicznie grafem

    cin >> n >> m;                                              // Odczytujemy liczbę wierzchołków i krawędzi
    
    // Graf wypełniamy pustymi listami
    for(i = 0; i < n; i++)
        graph.push_back(list);

    // Odczytujemy kolejne definicje krawędzi
    for(i = 0; i < m; i++)
    {
        cin>>v>>u;
        graph[v].insert(graph[v].begin(), u);
    }
    
    cout << endl;
    
    if( topologicalSort(graph, sortedGraph)  == false)
        cout << "Graph can not be topological sorted" << endl;
    else
    {
        while(sortedGraph.size() > 0)
        {
            cout << sortedGraph.top() << " ";
            sortedGraph.pop();
        }
    }

    cout << endl;
    return 0;
}