using namespace std;
void addMovie()
{
    cls();
    movie m1;
    string line;
    char c;
    int i = 0;
    ifstream checkForStatusOfFile("appData/allMovies/totalMovie.file");
    if (!checkForStatusOfFile)
    {
        checkForStatusOfFile.close();
        ofstream totalMoviesMake("appData/allMovies/totalMovie.file");
        totalMoviesMake << 0;
        totalMoviesMake.close();
    }
    checkForStatusOfFile.close();
    printEnd("DEVELOPED BY AADARSHA KHANAL, BIGYAN POKHREL, SURAJ GUVAJU & NISHANT SUBEDI");
    cout << endl;
    centerMe("ADD A MOVIE");
    m1.imdbID.push_back('t');
    m1.imdbID.push_back('t');
    cout << endl;
    cout << endl;
    cout << endl
         << "Enter the movie IMDB ID: " << m1.imdbID;
    getIMDBRequestID(m1.imdbID);
    cout << endl
         << endl
         << "Enter the movie name: ";
    cin.ignore();
    getline(cin, m1.movieName);
    cout << endl
         << endl
         << "Enter the movie year: ";
    while (true)
    {
        c = _getch();
        if (c == 13 && i == 4)
        {
            break;
        }
        else if (c == 8)
        {
            if (m1.movieYear.length() > 0)
            {
                i--;
                m1.movieYear.pop_back();
                std::cout << "\b \b";
            }
        }
        else if (c > 47 && c < 58 && i < 4)
        {
            i++;
            m1.movieYear.push_back(c);
            std::cout << c;
        }
        else if (c == 32)
        {
            continue;
        }
    }
    cout << endl
         << endl
         << endl
         << "Enter the movie rating: ";
    i = 0;
    while (true)
    {
        c = _getch();
        if (c == 13 && i > 1)
        {
            break;
        }
        else if (c == 8)
        {
            if (m1.movieRating.length() > 0)
            {
                i--;
                m1.movieRating.pop_back();
                std::cout << "\b \b";
            }
        }
        else if (c > 47 && c < 58 || c == '.')
        {
            i++;
            m1.movieRating.push_back(c);
            std::cout << c;
        }
        else if (c == 32)
        {
            continue;
        }
    }
    cout << endl
         << endl
         << endl
         << "Enter the movie director: ";
    cin.ignore();
    getline(cin, m1.movieDirector);
    cout << endl
         << endl
         << "Enter the movie actors: ";
    cin.ignore();
    getline(cin, m1.movieActors);
    cout << endl
         << endl
         << "Enter the movie language: ";
    cin.ignore();
    getline(cin, m1.movieLanguage);
    cout << endl << endl << "How many copies are available: ";
    while (true)
    {
        c = _getch();
        if (c == 13)
        {
            break;
        }
        else if (c == 8)
        {
            if (line.length() > 0)
            {
                i--;
                line.pop_back();
                std::cout << "\b \b";
            }
        }
        else if (c > 47 && c < 58)
        {
            i++;
            line.push_back(c);
            std::cout << c;
        }
        else if (c == 32)
        {
            continue;
        }
    }
    m1.copies = stoi(line);
    line.clear();
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
            if (line == m1.imdbID)
            {
                fullCenterMe("Movie already exists!", 1);
                fullCenterMe("Press any key to return to menu...", -2);
                _getch();
                menu();
            }
        }
    }
    int status = makeDirectory(("appData/allMovies/movie" + to_string(totalMovies + 1)).c_str());
    if (status == 1)
    {
        fullCenterMe("Movie could not be added!", 1);
        fullCenterMe("Press any key to return to menu...", -2);
        _getch();
        menu();
    }
    totalMovies++;
    encrypt(&m1.imdbID);
    encrypt(&m1.movieName);
    encrypt(&m1.movieYear);
    encrypt(&m1.movieRating);
    encrypt(&m1.movieDirector);
    encrypt(&m1.movieActors);
    encrypt(&m1.movieLanguage);
    ofstream movieFile("appData/allMovies/movie" + to_string(totalMovies) + "/movie.file");
    movieFile << m1.imdbID;
    movieFile.close();
    ofstream movieNameFile("appData/allMovies/movie" + to_string(totalMovies) + "/name.file");
    movieNameFile << m1.movieName;
    movieNameFile.close();
    ofstream movieYearFile("appData/allMovies/movie" + to_string(totalMovies) + "/year.file");
    movieYearFile << m1.movieYear;
    movieYearFile.close();
    ofstream movieRatingFile("appData/allMovies/movie" + to_string(totalMovies) + "/rating.file");
    movieRatingFile << m1.movieRating;
    movieRatingFile.close();
    ofstream movieDirectorFile("appData/allMovies/movie" + to_string(totalMovies) + "/director.file");
    movieDirectorFile << m1.movieDirector;
    movieDirectorFile.close();
    ofstream movieActorsFile("appData/allMovies/movie" + to_string(totalMovies) + "/actor.file");
    movieActorsFile << m1.movieActors;
    movieActorsFile.close();
    ofstream movieLanguageFile("appData/allMovies/movie" + to_string(totalMovies) + "/language.file");
    movieLanguageFile << m1.movieLanguage;
    movieLanguageFile.close();
    ofstream movieTotalCopies("appData/allMovies/movie" + to_string(totalMovies) + "/copies.file");
    movieTotalCopies << m1.copies;
    movieTotalCopies.close();
    ofstream totalMoviesFile1("appData/allMovies/totalMovie.file");
    totalMoviesFile1 << totalMovies;
    totalMoviesFile1.close();
    fullCenterMe("Movie added successfully!", 1);
    fullCenterMe("Press any key to return to menu...", -2);
    _getch();
    menu();
}