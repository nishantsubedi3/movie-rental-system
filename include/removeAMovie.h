using namespace std;
void remove_all(string path)
{
    remove((path + "/movie.file").c_str());
    remove((path + "/name.file").c_str());
    remove((path + "/year.file").c_str());
    remove((path + "/rating.file").c_str());
    remove((path + "/director.file").c_str());
    remove((path + "/actor.file").c_str());
    remove((path + "/language.file").c_str());
    remove((path + "/copies.file").c_str());
}

void removeMovie()
{
    cls();
    int i;
    string line;
    printEnd("DEVELOPED BY AADARSHA KHANAL, BIGYAN POKHREL, SURAJ GUVAJU & NISHANT SUBEDI");
    string imdbID;
    cout << endl;
    centerMe("REMOVE A MOVIE");
    cout << endl;
    cout << endl;
    ifstream checkForStatusOfFile("appData/allMovies/totalMovie.file");
    if (!checkForStatusOfFile)
    {
        checkForStatusOfFile.close();
        fullCenterMe("NO MOVIES TO REMOVE!", 1);
        fullCenterMe("PRESS ANY KEY TO RETURN TO MENU.....", -2);
        getch();
        menu();
    }
    checkForStatusOfFile.close();
    cout << endl
         << "Enter the IMDB ID of the movie you want to remove: ";
    cin >> imdbID;
    int totalMovies;
    ifstream totalMoviesFile("appData/allMovies/totalMovie.file");
    totalMoviesFile >> totalMovies;
    totalMoviesFile.close();
    if (totalMovies > 0)
    {
        for (i = 1; i <= totalMovies; i++)
        {
            ifstream checkForMovieIMDB("appData/allMovies/movie" + to_string(i) + "/movie.file");
            getline(checkForMovieIMDB, line);
            checkForMovieIMDB.close();
            decrypt(&line);
            if (line == imdbID)
            {
                break;
            }
        }
        if (line == imdbID)
        {
            remove_all("appData/allMovies/movie" + to_string(i));
            sleep(100);
            RemoveDirectory(("appData/allMovies/movie" + to_string(i)).c_str());
            for (i = i; i <= totalMovies; i++)
            {
                rename(("appData/allMovies/movie" + to_string(i + 1)).c_str(), ("appData/allMovies/movie" + to_string(i)).c_str());
            }
            ofstream totalMoviesFile("appData/allMovies/totalMovie.file");
            totalMoviesFile << totalMovies - 1;
            totalMoviesFile.close();
            fullCenterMe("MOVIE REMOVED SUCCESSFULLY!", 1);
            fullCenterMe("PRESS ANY KEY TO RETURN TO MENU.....", -2);
            _getch();
            menu();
        }
        else
        {
            fullCenterMe("MOVIE NOT FOUND!", 1);
            fullCenterMe("PRESS ANY KEY TO RETURN TO MENU.....", -2);
            _getch();
            menu();
        }
    }
}