#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

vector< vector<int> > do_square_of_graph(vector< vector<int> > &graph, int &n)
{
    // Inicjalizacja tablicy list sąsiedztwa, która będzie reprezentować kwadrat grafu
    vector< vector<int> > square_of_graph(n, vector<int>());

    // Przechodzimy przez kolejne wierzchołki grafu
    for(int i = 0; i < n; i++)
    {
        // Kopiujemy listę graph[i] do square_of_graph[i]
        square_of_graph[i] = graph[i];

        // Teraz kopiujemy sąsiadów graph[i] do square_of_graph[i]
        for(const int &neighbor1 : graph[i])
        {
            // Przeglądamy listę sąsiedztwa sąsiada
            for(const int &neighbor2 : graph[neighbor1])
            {
                // Sprawdzamy czy dany wierzchołek jest unikalny
                bool exist = false;
                for(vector<int>::iterator it = square_of_graph[i].begin(); it != square_of_graph[i].end(); it++)
                    if(*it == neighbor2)
                    {
                        exist = true;
                        break;
                    }
                // Jeśli wierzchołek neighbor2 jest unikalny, to dodajemy go do listy square_of_graph[i]
                if(!exist)
                    square_of_graph[i].push_back(neighbor2);
            }
        }
    }

    return square_of_graph;
}

// **********************
// *** PROGRAM GŁÓWNY ***
// **********************
int main()
{
    int n, m, v, u, i;                                  // liczba wierzchołków, krawędzi, numer wierzchołka startowego i końcowego krawędzi, zmienna jako iterator
    vector< vector<int> > graph, square_of_graph;       // Listy sąsiedztwa

    cin >> n >> m;                                      // Odczytujemy liczbę wierzchołków i krawędzi

    // Tablicę list sąsiedztwa wypełniamy pustymi listami
    for(i = 0; i < n; i++)
        graph.push_back( vector<int>() );

    // Odczytujemy kolejne definicje krawędzi
    for(i = 0; i < m; i++)
    {
        cin >> v >> u;                                  // Wierzchołek startowy i końcowy krawędzi
        graph[v].push_back(u);
    }

    cout << endl;
    // Obliczamy kwadrat grafu który przypisujemy do tablicy square_of_graph
    square_of_graph = do_square_of_graph(graph, n);

    // Wypisujemy zawartość tablicy list sąsiedztwa kwadratu grafu
    for( int i = 0; i < n; i++ )
    {
        cout << i << ": ";
        for( const int &neighbor : square_of_graph[i] ) 
            cout << setw ( 3 ) << neighbor;
        cout << endl;
    }

    return 0;
}