using namespace std;

void rentMovie()
{
    cls();
    string userRequestedImdb, phoneNumber;
    int userRequestedCopies;
    printEnd("DEVELOPED BY AADARSHA KHANAL, BIGYAN POKHREL, SURAJ GUVAJU & NISHANT SUBEDI");
    centerMe("RENT A MOVIE");
    cout << endl
         << endl
         << "Enter the IMDB ID of the movie: ";
    userRequestedImdb.push_back('t');
    userRequestedImdb.push_back('t');
    cout << userRequestedImdb;
    getIMDBRequestID(userRequestedImdb);
    int indexInDb = getMovieIndex(userRequestedImdb);
    if (indexInDb == 0)
    {
        fullCenterMe("No movies found in Database!");
        fullCenterMe("Press any key to return to menu....", -5);
        _getch();
        menu();
    }
    else if (indexInDb == -1)
    {
        fullCenterMe("Movie not found in Database!");
        fullCenterMe("Press any key to return to menu....", -5);
        _getch();
        menu();
    }
    else
    {
        cout << endl
             << endl
             << "How many copies? ";
        cin >> userRequestedCopies;
        int copiesInDb = getTotalCopiesOfMoviesInDb(userRequestedCopies, indexInDb);
        if (copiesInDb != 1)
        {
            fullCenterMe("Only " + to_string(copiesInDb) + " copies left!");
            fullCenterMe("Press any key to return to menu......", -5);
            _getch();
            menu();
        }
        else
        {
            cout << endl
                 << endl
                 << "Enter user phone number: +977 ";
            int status = enterPhoneNumber(phoneNumber);
            if (status == 0)
            {
                fullCenterMe("Invalid phone number");
                fullCenterMe("Press esc to return to menu or any other key to retry.....", -5);
                char c = _getch();
                if (c == 27)
                {
                    menu();
                }
                rentMovie();
            }
            else
            {
                status = checkUserStatus(phoneNumber);
                if (status == 0)
                {
                    encrypt(&phoneNumber);
                    status = addUser(phoneNumber);
                    if (status == 0)
                    {
                        fullCenterMe("Could not add the user!");
                        fullCenterMe("Press any key to go back to menu......");
                        _getch();
                        menu();
                    }
                    decrypt(&phoneNumber);
                }
                status = canUserRent(phoneNumber, userRequestedImdb);
                if (status == 0)
                {
                    fullCenterMe("Renting limit reached for user!");
                    fullCenterMe("Press any key to return to menu.....", -5);
                    _getch();
                    menu();
                }
                int totalCopyInDb;
                ifstream totalCopyInDbCheck("appData/allMovies/movie" + to_string(indexInDb) + "/copies.file");
                totalCopyInDbCheck >> totalCopyInDb;
                totalCopyInDbCheck.close();
                status = giveUserTheMovie(phoneNumber, userRequestedImdb, totalCopyInDb, userRequestedCopies, indexInDb);
                if (status == 1)
                {
                    fullCenterMe(("Successfully rented the movie to " + phoneNumber));
                    fullCenterMe("Press any key to return to menu.....", -5);
                    _getch();
                    menu();
                }
                else
                {
                    fullCenterMe(("Could not rent the movie to " + phoneNumber));
                    fullCenterMe("Press any key to return to menu.....", -5);
                    _getch();
                    menu();
                }
            }
        }
    }
}