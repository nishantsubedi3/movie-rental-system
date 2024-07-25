using namespace std;
void getIMDBRequestID(string &userRequestedImdb)
{
    char c;
    while ((c = _getch()) != 13 || userRequestedImdb.length() < 1)
    {
        if (c == 13)
        {
            continue;
        }
        else if (c == 8)
        {
            if (userRequestedImdb.length() > 2)
            {
                userRequestedImdb.pop_back();
                std::cout << "\b \b";
            }
        }
        else if (c == 32)
        {
            continue;
        }
        else if (userRequestedImdb.length() < 2 && c != 't')
        {
            continue;
        }
        else if (userRequestedImdb.length() > 1 && c >= '0' && c <= '9')
        {
            userRequestedImdb.push_back(c);
            std::cout << c;
        }
        else
        {
            continue;
        }
    }
}

int getMovieIndex(string id)
{
    int totalMoviesInDb, i;
    string checkID;
    ifstream totalMoviesInDbCheck("appData/allMovies/totalMovie.file");
    if (!totalMoviesInDbCheck)
    {
        totalMoviesInDb = 0;
    }
    totalMoviesInDbCheck >> totalMoviesInDb;
    totalMoviesInDbCheck.close();
    if (totalMoviesInDb == 0)
    {
        return 0;
    }
    fstream checkMyFile;
    for (i = 1; i <= totalMoviesInDb; i++)
    {
        checkMyFile.open("appData/allMovies/movie" + to_string(i) + "/movie.file", ios::in);
        checkMyFile >> checkID;
        checkMyFile.close();
        decrypt(&checkID);
        if (checkID == id)
        {
            break;
        }
    }
    if (checkID == id)
    {
        return i;
    }
    else
    {
        return -1;
    }
    return -1;
}

int getTotalCopiesOfMoviesInDb(int userRequestedCopies, int index)
{
    int totalCopyInDb;
    ifstream totalCopyInDbCheck("appData/allMovies/movie" + to_string(index) + "/copies.file");
    totalCopyInDbCheck >> totalCopyInDb;
    totalCopyInDbCheck.close();
    if (userRequestedCopies <= totalCopyInDb)
    {
        return 1;
    }
    else
    {
        return totalCopyInDb;
    }
}

int enterPhoneNumber(string &phone)
{
    phone.clear();
    char c;
    int i = 0;
    while (true)
    {
        c = _getch();
        if (c == 13 && i == 10)
        {
            break;
        }
        else if (c == 8)
        {
            if (phone.length() > 0)
            {
                i--;
                phone.pop_back();
                std::cout << "\b \b";
            }
        }
        else if (c > 47 && c < 59 && i < 10)
        {
            i++;
            phone.push_back(c);
            std::cout << c;
        }
        else if (c == 32)
        {
            continue;
        }
    }
    if (phone[0] != '9' || phone[1] != '8' && phone[1] != '7')
    {
        return 0;
    }
    else
    {
        return 1;
    }
    return 0;
}

int getMovieIndexUser(string phone, string id, int totalMoviesWithUser)
{
    fstream checkFile;
    int i;
    string checkID;
    for (i = 1; i <= totalMoviesWithUser; i++)
    {
        checkFile.open("appData/rentedMovies/user" + phone + "/movie" + to_string(i) + ".file");
        checkFile >> checkID;
        decrypt(&checkID);
        checkFile.close();
        if (checkID == id)
        {
            break;
        }
    }
    if (checkID == id)
    {
        return i;
    }
    else
    {
        return 0;
    }
}

int canUserRent(string phone, string id)
{
    int totalMoviesWithUser;
    ifstream fileCheck("appData/rentedMovies/user" + phone + "/totalMovie.file");
    fileCheck >> totalMoviesWithUser;
    fileCheck.close();
    if (totalMoviesWithUser >= 10)
    {
        return 0;
    }
    else
    {
        int index = getMovieIndexUser(phone, id, totalMoviesWithUser);
        if (index == 0)
        {
            return 1;
        }
        int copiesWithUser;
        ifstream checkUserCopies("appData/rentedMovies/user" + phone + "/copy" + to_string(index) + ".file");
        checkUserCopies >> copiesWithUser;
        checkUserCopies.close();
        if (copiesWithUser >= 5)
        {
            return 0;
        }
        else
        {
            return 1;
        }
    }
    return 0;
}

int giveUserTheMovie(string phone, string uimdb, int copydb, int copyrq, int indexdb)
{
    int totalMoviesWithUser, copybefore;
    ifstream fileCheck("appData/rentedMovies/user" + phone + "/totalMovie.file");
    fileCheck >> totalMoviesWithUser;
    fileCheck.close();
    int uindex = getMovieIndexUser(phone, uimdb, totalMoviesWithUser);
    fstream fileCreate;
    if (uindex == 0)
    {
        totalMoviesWithUser++;
        fileCreate.open(("appData/rentedMovies/user" + phone + "/totalMovie.file"), ios::out);
        fileCreate << totalMoviesWithUser;
        fileCreate.close();
        fileCreate.open(("appData/rentedMovies/user" + phone + "/movie" + to_string(totalMoviesWithUser) + ".file"), ios::out);
        encrypt(&uimdb);
        fileCreate << uimdb;
        fileCreate.close();
        fileCreate.open(("appData/rentedMovies/user" + phone + "/copy" + to_string(totalMoviesWithUser) + ".file"), ios::out);
        fileCreate << copyrq;
        fileCreate.close();
        fileCreate.open(("appData/rentedMovies/user" + phone + "/date" + to_string(totalMoviesWithUser) + ".file"), ios::out);
        int y, m, d;
        getDate(&y, &m, &d);
        fileCreate << setfill('0') << setw(2) << d << "/" << setfill('0') << setw(2) << m << "/" << setfill('0') << setw(4) << y;
        fileCreate.close();
        fileCreate.open("appData/allMovies/movie" + to_string(indexdb) + "/copies.file", ios::out);
        fileCreate << (copydb - copyrq);
        fileCreate.close();
        return 1;
    }
    fileCreate.open(("appData/rentedMovies/user" + phone + "/copy" + to_string(totalMoviesWithUser) + ".file"), ios::in);
    fileCreate >> copybefore;
    fileCreate.close();
    fileCreate.open(("appData/rentedMovies/user" + phone + "/copy" + to_string(totalMoviesWithUser) + ".file"), ios::out);
    fileCreate << copybefore + copyrq;
    fileCreate.close();
    fileCreate.open(("appData/rentedMovies/user" + phone + "/date" + to_string(totalMoviesWithUser) + ".file"), ios::out);
    int y, m, d;
    getDate(&y, &m, &d);
    fileCreate << setfill('0') << setw(2) << d << "/" << setfill('0') << setw(2) << m << "/" << setfill('0') << setw(4) << y;
    fileCreate.close();
    fileCreate.open("appData/allMovies/movie" + to_string(indexdb) + "/copies.file", ios::out);
    fileCreate << (copydb - copyrq);
    fileCreate.close();
    return 1;
}

int getTotalRentedUserAmount(int total)
{
    fstream openFile1, openFile2;
    string phone;
    int flag = 0, totalWithUser;
    for (int i = 1; i <= total; i++)
    {
        phone.clear();
        openFile1.open("appData/Users/user" + to_string(i) + ".file", ios::in);
        if (!openFile1)
        {
            openFile1.close();
            continue;
        }
        openFile1 >> phone;
        decrypt(&phone);
        openFile1.close();
        openFile2.open("appData/rentedMovies/user" + phone + "/totalMovie.file", ios::in);
        if (!openFile2)
        {
            openFile2.close();
            continue;
        }
        openFile2 >> totalWithUser;
        if (totalWithUser == 0)
        {
            openFile2.close();
            continue;
        }
        openFile2.close();
        flag++;
    }
    return flag;
}