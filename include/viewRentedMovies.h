using namespace std;
string getMovieName(string id)
{
    int total, flag = 0;
    string IMDB, name;
    ifstream getTotalMoviesInDB("appData/allMovies/totalMovie.file");
    getTotalMoviesInDB >> total;
    getTotalMoviesInDB.close();
    for (int i = 1; i <= total; i++)
    {
        ifstream getMovieName("appData/allMovies/movie" + to_string(i) + "/movie.file");
        getMovieName >> IMDB;
        decrypt(&IMDB);
        getMovieName.close();
        if (IMDB == id)
        {
            ifstream getMovie("appData/allMovies/movie" + to_string(i) + "/name.file");
            getMovie >> name;
            getMovie.close();
            flag++;
            break;
        }
    }
    if (flag != 0)
    {
        decrypt(&name);
        return name;
    }
    return "0";
}

void getListOfUsersWithRentedMovies(int total, string userRented[])
{
    fstream openFile, openFile1;
    string phone;
    int flag = 0;
    for (int i = 1; i <= total; i++)
    {
        openFile.open("appData/Users/user" + to_string(i) + ".file", ios::in);
        if (!openFile)
        {
            openFile.close();
            continue;
        }
        openFile >> phone;
        decrypt(&phone);
        openFile.close();
        openFile1.open("appData/rentedMovies/user" + phone + "/totalMovie.file", ios::in);
        if (!openFile1)
        {
            openFile1.close();
            continue;
        }
        int totalWithUser = 0;
        openFile1 >> totalWithUser;
        if (totalWithUser == 0)
        {
            openFile1.close();
            continue;
        }
        userRented[flag] = phone;
        flag++;
        openFile1.close();
    }
}

void viewAllRentedMovies(int n = 0, int q = 0)
{
    cls();
    int i = 0, total;
    movie m;
    string path, date;
    fstream fileOpenner1, fileOpenner2, fileOpenner3;
    printEnd("DEVELOPED BY AADARSHA KHANAL, BIGYAN POKHREL, SURAJ GUVAJU & NISHANT SUBEDI");
    cout << endl;
    centerMe("List of all rented movies");
    string *usersWithRentedMovies;
    ifstream getTotalUserFile("appData/Users/totalUser.file");
    if (!getTotalUserFile)
    {
        getTotalUserFile.close();
        fullCenterMe("NO USERS AVAILABLE!", 1);
        fullCenterMe("PRESS ANY KEY TO GO BACK", -4);
        _getch();
        menu();
    }
    int totalUser;
    getTotalUserFile >> totalUser;
    getTotalUserFile.close();
    if (totalUser == 0)
    {
        getTotalUserFile.close();
        fullCenterMe("NO USERS AVAILABLE!", 1);
        fullCenterMe("PRESS ANY KEY TO GO BACK", -4);
        _getch();
        menu();
    }
    int totalAllocation = getTotalRentedUserAmount(totalUser);
    if (totalAllocation != 0)
    {
        usersWithRentedMovies = new string[totalAllocation];
        getListOfUsersWithRentedMovies(totalUser, usersWithRentedMovies);
        cout << endl
             << endl;
        cout << setw(25) << left << "Phone Number " << setw(50) << left << "Movie Name (IMDB ID)" << setw(25) << left << "Copies Taken" << setw(25) << left << "Rented on" << endl
             << endl;
        while (totalAllocation > n && i < 8)
        {
            path = "appData/rentedMovies/user" + usersWithRentedMovies[n];
            fileOpenner1.open(path + "/totalMovie.file", ios::in);
            fileOpenner1 >> total;
            fileOpenner1.close();
            fileOpenner1.clear();
            cout << setw(25) << left << usersWithRentedMovies[n];
            for (int k = 1; k <= total; k++)
            {
                if (k > 1)
                {
                    cout << setw(25) << left << "";
                }
                fileOpenner2.open(path + "/movie" + to_string(k) + ".file");
                fileOpenner2 >> m.imdbID;
                decrypt(&m.imdbID);
                fileOpenner2.close();
                fileOpenner2.clear();
                m.movieName = getMovieName(m.imdbID);
                fileOpenner3.open(path + "/copy" + to_string(k) + ".file");
                fileOpenner3 >> m.copies;
                fileOpenner3.close();
                fileOpenner3.clear();
                fileOpenner3.open(path + "/date" + to_string(k) + ".file");
                getline(fileOpenner3, date);
                fileOpenner3.close();
                fileOpenner3.clear();
                cout << setw(50) << left << m.movieName + " (" + m.imdbID + ")" << setw(25) << left << m.copies << setw(25) << left << date << endl
                     << endl;
                i++;
            }
            n++;
            i++;
        }
        char c;
        cout << endl;
        cout << endl;
        cout << endl;
        fflush(stdin);
        if (totalAllocation > 8)
        {
            cout << "Press d key to view more movies (a to go back) or any other key to go back to menu.....";
            c = _getch();
            if (c == 100 && n < totalAllocation)
            {
                q++;
                viewAllRentedMovies(n, q);
            }
            else if (c == 97 && n > i && q > 0)
            {
                q--;
                n -= i;
                viewAllRentedMovies((n - 8), q);
            }
            else if (c != 100 && c != 97)
            {
                menu();
            }
            else
            {
                viewAllRentedMovies();
            }
        }
        else
        {
            cout << "Press any key to go back to menu.....";
            _getch();
            menu();
        }
    }
    else
    {
        fullCenterMe("NO USER HAS RENTED MOVIE/S!", 1);
        fullCenterMe("PRESS ANY KEY TO GO BACK", -4);
        _getch();
        menu();
    }
    _getch();
}