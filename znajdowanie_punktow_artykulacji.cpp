#include <iostream>
#include <vector>

using namespace std;

// Zmienne globalne
vector< vector<int> > graph;                                    // Graf jako tablica list sąsiedztwa
vector<int> d;                                                  // Numery DFS
int cv;                                                         // Numeracja DFS
vector<int> ap;                                                 // Punkty artykulacji

// Funkcja rekurencyjna wyszukująca punkty artykulacji wśród 
// wierzchołków niebędących korzeniami
// v  - numer bieżącego wierzchołka
// vf - ojciec bieżącego wierzchołka na drzewie rozpinającym
// Reszta parametrów to zmienne globalne
int dfsap(const int &v, const int &vf)
{
    int low, temp;
    bool test = false;

    // Numerujemy wierzchołek, ustalamy wstępną wartość low oraz zwiększamy numerację    
    d[v] = low = cv++;

    // Przeglądamy listę sąsiadów
    for(vector<int>::iterator u = graph[v].begin(); u != graph[v].end(); u++)
        if(*u != vf)                                            // u nie może być ojcem v
        {
            if(d[*u] == 0)                                      // Jeśli sąsiad nie był odwiedzony to,
            {
                temp = dfsap(*u, v);                             // Rekurencyjnie odwiedzamy go
                if(temp < low)
                    low = temp;
                if(temp >= d[v])                                // Test na punkt artykulacji
                    test = true;
            }
            else if(d[*u] < low)
                low = d[*u];
        }

    // Wszyscy sąsiedzi zostali odwiedzeni. Sprawdzamy wynik testu
    if( test )
        ap.insert(ap.begin(), v);

    return low;
}

// Funkcja szukająca punktów artykulacji wśród wszystkich 
// wierzchołków, wewnątrz jest wywoływana funkcja dfsap
void searchap()
{
    int nc;                                                     // Licznik synów
    for(int v = 0; v < d.size(); v++)
        if(d[v] == 0)                                           // Szukamy nieodwiedzonego wierzchołka
        {
            cv = 2;                                             // Numer dfs dla pierwszego syna
            nc = 0;                                             // Zerujemy licznik synów
            d[v] = 1;                                           // Korzeń ma zawsze numer dfs 1
            // Przeglądamy sąsiadów v
            for(vector<int>::iterator u = graph[v].begin(); u != graph[v].end(); u++)
                if(d[*u] == 0)
                {
                    nc++;                                       // Zwiększamy licznik synów
                    dfsap(*u, v);                               // Szukamy punktów artykulacji w grafie
                }
            
            if(nc > 1)                                          // Czy korzeń jest punktem artykulacji
                ap.insert(ap.begin(), v);
        }

}

// **********************
// *** Program główny ***
// **********************
int main()
{
    int n, m;                                                   // Liczba wierzchołków i krawędzi
    int i, u, v;                                                // Numery wierzchołków
    vector<int>list;                                            // Lista sąsiedztwa

    cin >> n >> m;                                              // Odczytujemy liczbę wierzchołków i krawędzi
    
    // Graf wypełniamy pustymi listami a numery DFS ustawiamy na 0
    for(i = 0; i < n; i++)
    {
        graph.push_back(list);
        d.push_back(0);
    }

    // Odczytujemy kolejne definicje krawędzi
    for(i = 0; i < m; i++)
    {
        cin>>v>>u;
        graph[v].insert(graph[v].begin(), u);
        graph[u].insert(graph[u].begin(), v);
    }

    // Szukamy punktów artykulacji
    searchap();

    // Wypisujemy znalezione punkty artykulacji
    cout << endl;
    for(const auto &el : ap )
    {
        cout << el << " ";
    }

    cout << endl;

    return 0;
}
