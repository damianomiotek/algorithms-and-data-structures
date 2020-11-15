#include <iostream>
#include <vector>
#include <set>
#include <climits>

using namespace std;

struct PairComparator                                                   // Klasa z funkcją operator do porównywania elementów w zbiorze q
{
    bool operator()(const pair<int, int> &p1, const pair<int, int> &p2) const 
    { 
        return p1.second < p2.second;                                   // Kolejność od najmniejszego do największego
    };
};

void dijkstry(const int &starting_vertex, const vector< vector<pair<int, int>> > &graph, vector<int> &distances, vector<int> &predecessors)
{
    set< pair<int, int>, PairComparator > q;                            // Zbiór q zawierający wierzchołki czekające na przetworzenie
    pair<int, int> tmp;
    int v, weight;

    for(int i = 0; i < graph.size(); i++)                               // Tablicę dystansów wypełniamy INT_MAX a poprzedników na ścieżce do wierzchołka startowego wartościami -1
    {
        distances.push_back(INT_MAX);
        predecessors.push_back(-1);
    }
    
    distances[starting_vertex] = 0;                                     // Dystans od wierzchołka startowego do wierzchołka startowego to 0
    q.insert(make_pair(starting_vertex, distances[starting_vertex]));   // Na stos wrzucamy wierzchołek startowy i jego dystans

    while(!q.empty())
    {
        tmp = *(q.begin());                                             // Pobieramy wierzchołek o najmniejszym koszcie dojścia
        q.erase(q.begin());

        for(const pair<int, int> &neighbor : graph[tmp.first])          // Przechodzimy przez sąsiadów pobranego wierzchołka z q
        {
            v = neighbor.first;                                         // Pobieramy numer wierzchołka sąsiada
            weight = neighbor.second;                                   // Pobieramy koszt dojścia sąsiada do wierzchołka startowego

            if(distances[v] > distances[tmp.first] + weight)
            {
                if(distances[v] != INT_MAX)                             // Jeśli dystans wierzchołka v nie jest INT_MAX to na pewno jest w zbiorze q
                    q.erase(make_pair(v, distances[v]));

                distances[v] = distances[tmp.first] + weight;           // Aktualizacja dystansu
                q.insert(make_pair(v, distances[v]));                   // Na stos wrzucamy wierzchołek i zaktualizowany dystans
                predecessors[v] = tmp.first;                            // Aktualizacja poprzednika
            }
        }
    }
}

int main()
{
    vector< vector<pair<int, int>> > graph;                     // Graf jako tablica list sąsiedztwa
    int starting_vertex, num_vertices, num_edges;               // Wierzchołek startowy, liczba wierzchołków i krawędzi
    vector<int> distances;                                      // Odległości pomiędzy danym wierzchołkiem a wierzchołkiem startowym
    vector<int> predecessors;                                   // Poprzednicy na najkrótszych ścieżkach
    set<int>path;
    int i, v, u, w, p;

    // Wypełnianie grafu pustymi listami sąsiedztwa
    for(i = 0; i < num_vertices; i++)
        graph.push_back( vector<pair<int, int>>() );

    cin >> starting_vertex >> num_vertices >> num_edges;        // Wczytywanie wierzchołka startowego, liczby wierzchołków i krawędzi
    for(i = 0; i < num_edges; i++)
    {
        cin >> v >> u >> w;
        graph[v].push_back(make_pair(u, w));
    }

    dijkstry(starting_vertex, graph, distances, predecessors);  // Wyznaczanie najkrótszych ścieżek i długości tych ścieżek

    for(i = 0; i < num_vertices; i++)                           // Wyświetlanie najkrótszych ścieżek i odległości do wierzchołka startowego
    {
        if(i != starting_vertex)                                // Pomijamy najkrótszą ścieżkę od wierzchołka startowego do wierzchołka startowego
        {
            cout << "The shortest path from " << starting_vertex << " to " << i << " :\n";
            p = i;
            while(p != -1)
            {
                path.insert(p);                                 // Korzystanie ze stosu aby wyświetlać wierzchołki w kolejności od wierzchołka startowego do docelowego
                p = predecessors[p];
            }

            while(!path.empty())
            {
                cout << *(path.begin()) << " ";
                path.erase(path.begin());
            }

            cout << "The distance is : " << distances[i] << endl << endl;
        }
    }

    cout << endl;

    return 0;
}