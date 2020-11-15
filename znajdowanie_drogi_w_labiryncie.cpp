#include <iostream>
#include <vector>
#include <queue>
#include <string>

using namespace std;

vector<string> readMaze()
{
    vector<string> maze;
    string line;

    while( getline(cin, line) )
        maze.push_back(line);

    return maze;
}

void searchStartEndPoints(vector<string> &maze, int &rowStart, int &columnStart, 
                          int &rowEnd, int &columnEnd)
{
    rowStart = columnStart = rowEnd = columnEnd = -1;

    for(int i = 0; i < maze.size(); i++)                            // Szukamy punktów startowego i końcowego grafu
        for(int j = 0; j < maze[i].length(); j++)
            if(maze[i][j] == 'S')                                   // Punkt startowy znaleziony
            {
                rowStart = i;
                columnStart = j;                 
            }
            else if(maze[i][j] == 'W')                              // Punkt wyjściowy znaleziony
            {
                rowEnd = i;
                columnEnd = j;                    
                maze[rowEnd][columnEnd] = ' ';
            }
}

void searchPath(vector<string> &maze, int &rowStart, int &columnStart,
                int &rowEnd, int &columnEnd)
{
    queue< pair<int, int> > points;
    int w, k;                                                       // Wiersz i kolumna bieżącego wierzchołka
    int i, j;
    pair<int, int> singlePoint;

    points.push(make_pair(rowStart, columnStart));                  // W kolejce umieszczamy wierzchołek i kolumnę punktu startowego

    while(!points.empty())
    {
        singlePoint = points.front(); points.pop();                 // Pobieramy z kolejki wiersz i kolumnę bieżącego wierzchołka
        w = singlePoint.first;
        k = singlePoint.second;

        if( (w == rowEnd) && (k == columnEnd) )                     // Sprawdzamy czy osiągneliśmy wyjście
            break;

        // Przeglądamy sąsiadów bieżącego wierzchołka
        for (i = -1; i <= 1; i++)
            for (j = -1; j <= 1; j++)
                if ( (i != j) && (!i || !j))                        // Sąsiedzi mogą być tylko w poziomie lub w pionie
                    // Poniższy warunek jest po to aby nie szukać sąsiadów poza grafem
                    if ( (w + i >= 0) && (w + i < maze.size()) && (k + j >= 0) && (k + j < maze[w + i].length()) )
                        if (maze[w + i][k + j] == ' ')
                        {
                            // W komórce zapisujemy skąd przyszliśmy do niej
                            if ( i == -1)   maze[w + i][k + j] = 'd';       // Z dołu
                            else if ( i == 1)   maze[w + i][k + j] = 'g';   // Z góry
                            else if (j == -1)   maze[w + i][k + j] = 'p';   // Z prawej
                            else if (j == 1)    maze[w + i][k + j] = 'l';   // Z lewej

                            points.push(make_pair(w + i, k + j));           // Sąsiad zostaje umieszczony w kolejce
                        }
    }
}

// Procedura wypisuje labirynt z ewentualną ścieżką
void printMaze(vector<string> &maze, int &rowStart, int &columnStart, 
               int &rowEnd, int &columnEnd)
{
    int i, j;
    char direction;

    // Najpierw sprawdzamy czy ścieżka została znaleziona
    // Jeśli tak to zastępujemy ją strzałkami będącymi kierunkami
    if (maze[rowEnd][columnEnd] != ' ')
    {
        i = rowEnd; 
        j = columnEnd;

        while ( (i != rowStart) || (j != columnStart) )
        {
            direction = maze[i][j];
            maze[i][j] = '.';
            
            switch (direction)
            {
                case 'd' : i++; break;
                case 'g' : i--; break;
                case 'p' : j++; break;
                case 'l' : j--; break;
            }
        }
    }

    maze[rowEnd][columnEnd] = 'W';                                      // Odtwarzamy znak wyjścia

    // Teraz usuwamy znaki kierunku i wypisujemy labirynt 
    for(i = 0; i < maze.size(); i++)
    {
        for(j = 0; j < maze[i].size(); j++)
            switch(maze[i][j])
            {
                case 'g': ;
                case 'd': ;
                case 'p': ;
                case 'l': maze[i][j] = ' ';
            }
        cout << maze[i] << endl;
    }
    cout << endl;
}

// **********************
// *** PROGRAM GŁÓWNY ***
// **********************
int main()
{
    int rowStart, rowEnd, columnStart, columnEnd;                       // Wiersz startowy, końcowy
                                                                        // Kolumna startowa, końcowa
    vector<string>maze;                                                 // Labirynt

    maze = readMaze();                                                  // Wczytujemy labirynt
    searchStartEndPoints(maze, rowStart, columnStart,                   // Szukamy punktu startu i wyjścia
                         rowEnd, columnEnd);

    if ( (rowStart == -1) || (rowEnd == -1))                            // Jeśli brak w grafie punktu startowego lub wyjściowego    
    {
        cout << "Lack of S or W definition!!\n";
    }
    else
    {
        cout << endl;
        searchPath(maze, rowStart, columnStart, rowEnd,  columnEnd);    // Szukamy wyjścia
        printMaze(maze, rowStart, columnStart, rowEnd, columnEnd);      // Wyświetlamy wyniki poszukiwań
    }

    return 0;
}