using namespace std;
void returnMovie()
{
    int status, retryCounter = 0, totalMoviesWithUser, UserIndexOfMovie, indexOfMovieInDb, totalCopyWithUser;
    string userPhoneNumber, userEnteredImdb;
    char c;
    cls();
    printEnd("DEVELOPED BY AADARSHA KHANAL, BIGYAN POKHREL, SURAJ GUVAJU & NISHANT SUBEDI");
    centerMe("RETURN A MOVIE");
    cout << endl
         << endl
         << "Enter the user phone number: +977 ";
    status = enterPhoneNumber(userPhoneNumber);
    if (status == 0)
    {
        fullCenterMe("INVALID PHONE NUMBER");
        fullCenterMe("Press esc to return to menu any other key to retry....", -5);
        c = _getch();
        if (c == 27)
        {
            menu();
        }
        else
        {
            returnMovie();
        }
    }
    else
    {
        status = checkUserStatus(userPhoneNumber);
        if (status == 0)
        {
            fullCenterMe("USER DOES NOT EXIST");
            fullCenterMe("Press esc to return to menu any other key to retry....", -5);
            c = _getch();
            if (c == 27)
            {
                menu();
            }
            else
            {
                returnMovie();
            }
        }
    }
retryIMDB:
    if (retryCounter != 0)
    {
        cls();
        printEnd("DEVELOPED BY AADARSHA KHANAL, BIGYAN POKHREL, SURAJ GUVAJU & NISHANT SUBEDI");
        centerMe("RETURN A MOVIE");
        cout << endl
             << endl
             << "Enter the user phone number: +977 " << userPhoneNumber;
    }
    userEnteredImdb.push_back('t');
    userEnteredImdb.push_back('t');
    cout << endl
         << endl
         << "Enter the IMDB ID: " << userEnteredImdb;
    fflush(stdin);
    getIMDBRequestID(userEnteredImdb);
    status = getMovieIndex(userEnteredImdb);
    if (status == 0 || status == -1)
    {
        fullCenterMe("Movie not found in the DB!");
        fullCenterMe("Press esc to return to menu or any other key to retry.......", -7);
        c = _getch();
        if (c == 27)
        {
            menu();
        }
        else
        {
            retryCounter = 1;
            goto retryIMDB;
        }
    }
    indexOfMovieInDb = status;
    ifstream getIndexOfMovieUser("appData/rentedMovies/user" + userPhoneNumber + "/totalMovie.file");
    getIndexOfMovieUser >> totalMoviesWithUser;
    getIndexOfMovieUser.close();
    status = getMovieIndexUser(userPhoneNumber, userEnteredImdb, totalMoviesWithUser);
    if (status == 0)
    {
        fullCenterMe("Movie was not rented by user!");
        fullCenterMe("Press esc to return to menu or any other key to retry.......", -7);
        c = _getch();
        if (c == 27)
        {
            menu();
        }
        else
        {
            returnMovie();
        }
    }
    UserIndexOfMovie = status;
    ifstream getTotalCopyWithUser("appData/rentedMovies/user" + userPhoneNumber + "/copy" + to_string(UserIndexOfMovie) + ".file");
    getTotalCopyWithUser >> totalCopyWithUser;
    getTotalCopyWithUser.close();
    cout << endl
         << endl
         << "Are you sure you want to return " << totalCopyWithUser << " copies of the movie?(y/n): ";
    c = _getch();
    cout << c;
    if (c == 'n' || c == 'n')
    {
        fullCenterMe("OPERATION CANCELLED BY THE USER!");
        fullCenterMe("Press esc to return to menu.......", -7);
        _getch();
        menu();
    }
    int beforeCopyDb;
    ifstream getBeforeCopyDb("appData/allMovies/movie" + to_string(indexOfMovieInDb) + "/copies.file");
    getBeforeCopyDb >> beforeCopyDb;
    getBeforeCopyDb.close();
    remove(("appData/rentedMovies/user" + userPhoneNumber + "/movie" + to_string(UserIndexOfMovie) + ".file").c_str());
    remove(("appData/rentedMovies/user" + userPhoneNumber + "/copy" + to_string(UserIndexOfMovie) + ".file").c_str());
    remove(("appData/rentedMovies/user" + userPhoneNumber + "/date" + to_string(UserIndexOfMovie) + ".file").c_str());
    ofstream reTotalUserMovie("appData/rentedMovies/user" + userPhoneNumber + "/totalMovie.file");
    reTotalUserMovie << totalMoviesWithUser - 1;
    reTotalUserMovie.close();
    ofstream reDbTotal("appData/allMovies/movie" + to_string(indexOfMovieInDb) + "/copies.file");
    reDbTotal << beforeCopyDb + totalCopyWithUser;
    reDbTotal.close();
    fullCenterMe("SUCCESSFULLY RETURNED THE MOVIE!");
    fullCenterMe("Press esc to return to menu.......", -7);
    _getch();
    menu();
}