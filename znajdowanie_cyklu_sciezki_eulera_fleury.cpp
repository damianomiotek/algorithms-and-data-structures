#include <iostream>
#include <vector>

using namespace std;

// Zmienne globalne
int cv;
vector< vector<int> > graph;                                // Graf jako macierz sąsiedztwa
vector<int>s;                                               // Stos w tablicy
vector<int>d;                                               // Tablica numerów wierzchołków

// Funkcja wyszukująca mosty w grafie
// We:
// v  - numer wierzchołka startowego
// vf - ojciec wierzchołka v na drzewie rozpinającym
// Wy:
// Parametr Low dla wierzchołka v
int dfsb(const int &v, const int &vf)
{
    int low, temp, i;

    // Numerujemy wierzchołek, ustalamy wstępną wartość low oraz zwiększamy numerację    
    d[v] = low = cv++;

    // Przeglądamy listę sąsiadów
    for(int i = 0; i < graph.size(); i++)
        if( graph[v][i] && ( i != vf ) )                        // u nie może być ojcem v
        {
            if(d[ i ] == 0)                                     // Jeśli sąsiad nie był odwiedzony to,
            {
                temp = dfsb(i, v);                              // Rekurencyjnie odwiedzamy go
                if(temp < low)
                    low = temp;
            }
            else if(d[ i ] < low)
                low = d[ i ];
        }

    // Wszyscy sąsiedzi zostali odwiedzeni. Teraz robimy test na most
    if(d[v] == low && vf > -1)
        graph [ vf ][ v ] = graph [ v ][ vf ] = 2; // Oznaczamy krawędź vf-v jako most

    return low;
}

// Procedura wyszukuje cykl lub ścieżkę Eulera
// We:
// v - wierzchołek startowy
void findEuler(int &v)
{
    int u, w, i;

    while( true )               // W pętli przetwarzamy graf
    {
        s.push_back(v);         // v umieszczamy na stosie

        for( u = 0; u < graph.size() && graph[ v ][ u ] == 0; u++ )       // Szukamy pierwszego sąsiada v
            ;

        if( u == graph.size() ) 
            break; // Nie ma sąsiadów, kończymy

        for( i = 0; i < graph.size(); i++ ) 
            d [ i ] = 0; // Zerujemy tablicę D

        cv = 1;             // Numer pierwszego wierzchołka dla DFS
        dfsb ( v, -1 );     // Identyfikujemy krawędzie-mosty

        // Szukamy krawędzi nie będącej mostem
        for( w = u + 1; ( graph [ v ][ u ] == 2 ) && ( w < graph.size() ); w++ )
            if( graph [ v ][ w ] ) 
                u = w;

        graph [ v ][ u ] = graph [ u ][ v ] = 0; // Usuwamy krawędź v-u
        v = u;              // Przechodzimy do u
    }
}

// **********************
// *** Program główny ***
// **********************
int main()
{
    int n, m;                                               // Liczba wierzchołków i krawędzi
    int i, u, v;                                            // Numery wierzchołków
    vector<int>vd;                                          // Stopnie wierzchołków

    cin >> n >> m;                                          // Odczytujemy liczbę wierzchołków i krawędzi
    
    // Graf wypełniamy pustymi listami
    vector<int>emptyList(n, 0);                                   // Lista sąsiedztwa
    for(i = 0; i < n; i++)
        graph.push_back(emptyList);


    // Tablicę stopni i tablicę numerów wierzchołków wypełniamy zerami
    for(i = 0; i < n; i++)
    {
        vd.push_back(0);
        d.push_back(0);
    }

    // Odczytujemy kolejne definicje krawędzi
    for(i = 0; i < m; i++)
    {
        cin>>v>>u;
        graph[v][u] = 1;
        graph[u][v] = 1;                              // Krawędź w drugą stronę, bo graf jest nieskierowany
        vd[v]++;                                            // Obliczamy stopnie v i u
        vd[u]++;
    }
    
    cout << endl;
    
    for( v = 0; v < n; v++ )                                // Szukamy pozycji startowej v
        if( vd [ v ] )
            break;                                  

    for( i = v; i < n; i++ )
        if( vd [ i ] % 2 )
        {
            v = i;
            break;
        }

    findEuler( v );                                         // Wyznaczamy cykl lub ścieżkę Eulera

    // Wypisujemy zawartość stosu
    if( vd [ v ] % 2 ) 
        cout << "EULERIAN PATH :";
    else 
        cout << "EULERIAN CYCLE :";

    for(const auto el : s)
        cout << el << " ";
    cout << endl;

    return 0;
}



// #include <iostream>
// #include <vector>
// #include <set>
// #include <map>

// using namespace std;

// // Zmienne globalne
// int cv;
// vector< vector<int> > graph;                                // Graf jako tablica list sąsiedztwa
// vector<int>s;                                               // Stos w tablicy
// vector<int>d;                                               // Tablica numerów wierzchołków
// map< int, set<int> >bridges;                                // Klucz to wierzchołek z którego krawędź wychodzi

// // Funkcja wyszukująca mosty w grafie
// // We:
// // v  - numer wierzchołka startowego
// // vf - ojciec wierzchołka v na drzewie rozpinającym
// // Wy:
// // Parametr Low dla wierzchołka v
// int dfsb(const int &v, const int &vf)
// {
//     int low, temp, u;

//     // Numerujemy wierzchołek, ustalamy wstępną wartość low oraz zwiększamy numerację    
//     d[v] = low = cv++;

//     // Przeglądamy listę sąsiadów
//     for(int i = 0; i < graph[v].size(); i++)
//         if(graph[v][i] != vf && graph[v][i] != -1)                                            // u nie może być ojcem v
//         {
//             u = graph[v][i];
//             if(d[ u ] == 0)                                      // Jeśli sąsiad nie był odwiedzony to,
//             {
//                 temp = dfsb(u, v);                             // Rekurencyjnie odwiedzamy go
//                 if(temp < low)
//                     low = temp;
//             }
//             else if(d[ u ] < low)
//                 low = d[ u ];
//         }

//     // Wszyscy sąsiedzi zostali odwiedzeni. Teraz robimy test na most
//     if(d[v] == low && vf > -1)
//     {
//         bridges[v].insert(vf);
//         bridges[vf].insert(v);
//     }

//     return low;
// }

// // Procedura wyszukuje cykl lub ścieżkę Eulera
// // We:
// // v - wierzchołek startowy
// void findEuler(int &v)
// {
//     int u, w, i;

//     while( true )         // W pętli przetwarzamy graf
//     {
//         s.push_back(v);         // v umieszczamy na stosie

//         for( u = 0; u < graph[v].size() && graph[ v ][ u ] == -1; u++ )       // Szukamy pierwszego sąsiada v
//             ;

//         if( u == graph[v].size() ) 
//             break; // Nie ma sąsiadów, kończymy

//         for( i = 0; i < graph.size(); i++ ) 
//             d [ i ] = 0; // Zerujemy tablicę D

//         cv = 1;             // Numer pierwszego wierzchołka dla DFS
//         dfsb ( v, -1 );     // Identyfikujemy krawędzie-mosty

//         // Szukamy krawędzi nie będącej mostem
//         i = u;
//         u = graph[v][u];
//         for(w = i; w < graph[v].size(); w++)
//         {
//             if( graph[ v ][ w ] != -1 && bridges[v].count(graph[ v ][ w ]) == 0)
//             {
//                 u = graph[ v ][ w ];
//                 i = w;
//                 break;
//             }
//         }

//         graph[v][i] = -1;               // Usuwamy krawędź v-u
//         for(i = 0; i < graph[u].size(); i++)
//             if(graph[u][i] == v);
//                 graph[u][i] = -1;

//         v = u;              // Przechodzimy do u
//     }
// }

// // **********************
// // *** Program główny ***
// // **********************
// int main()
// {
//     int n, m;                                               // Liczba wierzchołków i krawędzi
//     int i, u, v;                                            // Numery wierzchołków
//     vector<int>emptyList;                                   // Lista sąsiedztwa
//     vector<int>vd;                                          // Stopnie wierzchołków
//     set<int>endEdgeBridges;

//     cin >> n >> m;                                          // Odczytujemy liczbę wierzchołków i krawędzi
    
//     // Graf wypełniamy pustymi listami
//     for(i = 0; i < n; i++)
//         graph.push_back(emptyList);

//     // Tablicę stopni wypełniamy zerami
//     for(i = 0; i < n; i++)
//     {
//         vd.push_back(0);
//         d.push_back(0);
//         bridges[i] = endEdgeBridges;
//     }

//     // Odczytujemy kolejne definicje krawędzi
//     for(i = 0; i < m; i++)
//     {
//         cin>>v>>u;
//         graph[v].push_back(u);
//         graph[u].push_back(v);                              // Krawędź w drugą stronę, bo graf jest nieskierowany
//         vd[v]++;                                            // Obliczamy stopnie v i u
//         vd[u]++;
//     }
    
//     cout << endl;
    
//     for( v = 0; v < n; v++ )                                // Szukamy pozycji startowej v
//         if( vd [ v ] )
//             break;                                  

//     for( i = v; i < n; i++ )
//         if( vd [ i ] % 2 )
//         {
//             v = i;
//             break;
//         }

//     findEuler( v );                                         // Wyznaczamy cykl lub ścieżkę Eulera

//     // Wypisujemy zawartość stosu
//     if( vd [ v ] % 2 ) 
//         cout << "EULERIAN PATH :";
//     else 
//         cout << "EULERIAN CYCLE :";

//     for(const auto el : s)
//         cout << el << " ";
//     cout << endl;

//     return 0;
// }