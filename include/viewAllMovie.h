using namespace std;
void viewMovie(int n = 1, int q = 0)
{
    cls();
    int i = 0;
    movie m;
    string path;
    printEnd("DEVELOPED BY AADARSHA KHANAL, BIGYAN POKHREL, SURAJ GUVAJU & NISHANT SUBEDI");
    int total;
    cout << endl;
    centerMe("List of all movies");
    ifstream totalMoviesCountFile("appData/allMovies/totalMovie.file");
    if (!totalMoviesCountFile)
    {
        totalMoviesCountFile.close();
        fullCenterMe("NO MOVIES AVAILABLE!", 1);
        fullCenterMe("PRESS ANY KEY TO GO BACK", -2);
        _getch();
        menu();
    }
    totalMoviesCountFile >> total;
    totalMoviesCountFile.close();
    cout << endl
         << endl;
    cout << setw(10) << left << "IMDB ID " << setw(50) << left << "Movie Name (Year)" << setw(25) << left << "Rating" << setw(25) << left << "Copies Left" << endl
         << endl;
    while (n <= total && i < 8)
    {
        path = "appData/allMovies/movie" + to_string(n);
        ifstream imdbID((path + "/movie.file"));
        getline(imdbID, m.imdbID);
        imdbID.close();
        ifstream movieName((path + "/name.file"));
        getline(movieName, m.movieName);
        movieName.close();
        ifstream movieYear((path + "/year.file"));
        getline(movieYear, m.movieYear);
        movieYear.close();
        ifstream movieRating((path + "/rating.file"));
        getline(movieRating, m.movieRating);
        movieRating.close();
        ifstream movieCopies((path + "/copies.file"));
        movieCopies >> m.copies;
        movieCopies.close();
        cout << endl;
        cout << endl;
        decrypt(&m.imdbID);
        decrypt(&m.movieName);
        decrypt(&m.movieYear);
        decrypt(&m.movieRating);
        cout << setw(10) << left << m.imdbID << setw(50) << left << m.movieName + " (" + m.movieYear + ")" << setw(25) << left << m.movieRating << setw(25) << left << m.copies << endl
             << endl;
        n++;
        i++;
    }
    char c;
    cout << endl;
    cout << endl;
    cout << endl;
    fflush(stdin);
    if (total > 8)
    {
        cout << "Press d key to view more movies (a to go back) or any other key to go back to menu.....";
        c = _getch();
        if (c == 100 && n < total)
        {
            q++;
            viewMovie(n, q);
        }
        else if (c == 97 && n > i && q > 0)
        {
            q--;
            n -= i;
            viewMovie((n - 8), q);
        }
        else if (c != 100 && c != 97)
        {
            menu();
        }
        else
        {
            viewMovie();
        }
    }
    else
    {
        cout << "Press any key to go back to menu.....";
        _getch();
        menu();
    }
}