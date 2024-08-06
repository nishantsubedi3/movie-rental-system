using namespace std;

int removeCheckForRentedMovies(string phone)
{
    int totalCopies;
    ifstream check1("appData/rentedMovies/user" + phone + "/totalMovie.file");
    if (!check1)
    {
        return -1;
    }
    check1 >> totalCopies;
    check1.close();
    if (totalCopies > 0)
    {
        return totalCopies;
    }
    else
    {
        return -1;
    }
    return -1;
}

void listTheMovies(string phone)
{
    cout << endl << endl;
    cout << setw(50) << left << "Movie Name" << setw(10) << left << "Total Copies" << endl;
    int totalCopies, total, j = 0;
    string movieID, cmovieID;
    int copies;
    ifstream check1("appData/rentedMovies/user" + phone + "/totalMovie.file");
    if (!check1)
    {
        fullCenterMe("Error listing movies!");
        return;
    }
    check1 >> totalCopies;
    check1.close();
    ifstream check("appData/allMovies/totalMovie.file");
    check >> total;
    check.close();
    for (int i = 1; i <= totalCopies; i++)
    {
        ifstream file1("appData/rentedMovies/user" + phone + "/movie" + to_string(i) + ".file");
        ifstream file2("appData/rentedMovies/user" + phone + "/copy" + to_string(i) + ".file");
        if (!file1 || !file2)
        {
            continue;
        }
        file1 >> movieID;
        decrypt(&movieID);
        file2 >> copies;
        file1.close();
        file2.close();
        for (j = 1; j <= total; j++)
        {
            ifstream file3("appData/allMovies/movie" + to_string(j) + "/movie.file");
            if (!file3)
            {
                continue;
            }
            file3 >> cmovieID;
            decrypt(&cmovieID);
            file3.close();
            if (movieID == cmovieID)
            {
                break;
            }
        }
        if (movieID == cmovieID)
        {
            ifstream file4("appData/allMovies/movie" + to_string(j) + "/name.file");
            if (!file4)
            {
                cout << "";
            }
            file4 >> movieID;
            decrypt(&movieID);
            file4.close();
            cout << setw(50) << left << movieID << setw(10) << left << totalCopies << endl;
        }
    }
}

void makeChangesToTotal(string phone)
{
    cout << "I AM HERE!";
    int totalCopies, total, j = 0, i = 0;
    string movieID, cmovieID;
    int copies;
    ifstream check1("appData/rentedMovies/user" + phone + "/totalMovie.file");
    if (!check1)
    {
        fullCenterMe("Error listing movies!");
        return;
    }
    check1 >> totalCopies;
    check1.close();
    ifstream check("appData/allMovies/totalMovie.file");
    check >> total;
    check.close();
    for (i = 1; i <= totalCopies; i++)
    {
        ifstream file1("appData/rentedMovies/user" + phone + "/movie" + to_string(i) + ".file");
        ifstream file2("appData/rentedMovies/user" + phone + "/copy" + to_string(i) + ".file");
        if (!file1 || !file2)
        {
            continue;
        }
        file1 >> movieID;
        decrypt(&movieID);
        file2 >> copies;
        file1.close();
        file2.close();
        for (j = 1; j <= total; j++)
        {
            ifstream file3("appData/allMovies/movie" + to_string(j) + "/movie.file");
            if (!file3)
            {
                continue;
            }
            file3 >> cmovieID;
            decrypt(&cmovieID);
            file3.close();
            if (movieID == cmovieID)
            {
                break;
            }
        }
        if (movieID == cmovieID)
        {
            ifstream file4("appData/allMovies/movie" + to_string(j) + "/copies.file");
            int cp = 0;
            file4 >> cp;
            file4.close();
            ofstream file5("appData/allMovies/movie" + to_string(j) + "/copies.file");
            file5 << cp + copies;
            file5.close();
        }
    }
}

void removeUser()
{
    cls();
    int i = 0, totalUsr;
    char c;
    usrnpass user;
    printEnd("DEVELOPED BY AADARSHA KHANAL, BIGYAN POKHREL, SURAJ GUVAJU & NISHANT SUBEDI");
    cout << endl;
    centerMe("REMOVE A USER");
    cout << endl;
    cout << endl;
    ifstream totalUser33("appData/Users/totalUser.file");
    if (!totalUser33)
    {
        fullCenterMe("No users found!", 1);
        fullCenterMe("Press any key to return to menu.....", -2);
        _getch();
        menu();
    }
    totalUser33.close();

    cout << "Enter the user phone number: ";
    cout << endl
         << " ";
    while (true)
    {
        c = _getch();
        if (c == 13 && i == 10)
        {
            break;
        }
        else if (c == 8)
        {
            if (user.password.length() > 0)
            {
                i--;
                user.password.pop_back();
                std::cout << "\b \b";
            }
        }
        else if (c > 47 && c < 59 && i < 10)
        {
            i++;
            user.password.push_back(c);
            std::cout << c;
        }
        else if (c == 32)
        {
            continue;
        }
    }
    if (user.password[0] != '9' && user.password[1] != '8' || user.password[0] != '9' && user.password[1] != '7')
    {
        fullCenterMe("Invalid phone number", 1);
        fullCenterMe("Press any key to return back to menu...", -2);
        _getch();
        addUser();
    }
    int status = checkUserStatus(user.password);
    if (status == 0)
    {
        fullCenterMe("User not found", 1);
        fullCenterMe("Press any key to return back to menu...", -2);
        _getch();
        menu();
    }
    else
    {
        ifstream totalUserFile("appData/Users/totalUser.file");
        totalUserFile >> totalUsr;
        totalUserFile.close();
        if (totalUsr == 0)
        {
            fullCenterMe("No users found", 1);
            fullCenterMe("Press any key to return back to menu...", -2);
            _getch();
            menu();
        }
        for (i = 1; i <= totalUsr; i++)
        {
            ifstream phoneNumberFile("appData/Users/user" + to_string(i) + ".file");
            getline(phoneNumberFile, user.name);
            decrypt(&user.name);
            if (user.name == user.password)
            {
                phoneNumberFile.close();
                break;
            }
            phoneNumberFile.close();
        }
        if (user.name == user.password)
        {
            status = removeCheckForRentedMovies(user.password);
            if (status == -1)
            {
                remove(("appData/Users/user" + to_string(i) + ".file").c_str());
                remove(("appData/Users/user_name" + to_string(i) + ".file").c_str());
                if (i < totalUsr)
                {
                    for (i = i; i <= totalUsr; i++)
                    {
                        rename(("appData/Users/user" + to_string(i + 1) + ".file").c_str(), ("appData/Users/user" + to_string(i) + ".file").c_str());
                        rename(("appData/Users/user_name" + to_string(i + 1) + ".file").c_str(), ("appData/Users/user_name" + to_string(i) + ".file").c_str());
                    }
                }
                fullCenterMe("User removed successfully", 1);
                fullCenterMe("Press any key to get back to menu...", -2);
                totalUsr--;
                ofstream totalUserFile1("appData/Users/totalUser.file");
                totalUserFile1 << totalUsr;
                totalUserFile1.close();
                _getch();
                menu();
            }
            else
            {
                int totalCopies = status;
                cout << endl << endl << endl << ("Looks like the user has " + to_string(totalCopies) + " movies in his account!");
                listTheMovies(user.password);
                cout << endl
                     << "Has user returned all these movies (y/n)" << endl;
                c = _getch();
                if (tolower(c) == 'n')
                {
                    cls();
                    printEnd("DEVELOPED BY AADARSHA KHANAL, BIGYAN POKHREL, SURAJ GUVAJU & NISHANT SUBEDI");
                    cout << endl;
                    centerMe("REMOVE A USER");
                    fullCenterMe("User needs to return the movies before cancelling the account!");
                    fullCenterMe("Press any key to return to menu......", -2);
                    _getch();
                    menu();
                }
                cls();
                printEnd("DEVELOPED BY AADARSHA KHANAL, BIGYAN POKHREL, SURAJ GUVAJU & NISHANT SUBEDI");
                cout << endl;
                centerMe("REMOVE A USER");
                makeChangesToTotal(user.password);
                remove(("appData/Users/user" + to_string(i) + ".file").c_str());
                remove(("appData/Users/user_name" + to_string(i) + ".file").c_str());
                if (i < totalUsr)
                {
                    for (i = i; i <= totalUsr; i++)
                    {
                        rename(("appData/Users/user" + to_string(i + 1) + ".file").c_str(), ("appData/Users/user" + to_string(i) + ".file").c_str());
                        rename(("appData/Users/user_name" + to_string(i + 1) + ".file").c_str(), ("appData/Users/user_name" + to_string(i) + ".file").c_str());
                    }
                }
                remove(("appData/rentedMovies/user" + user.password + "/totalMovie.file").c_str());
                for (i = 1; i <= totalCopies; i++)
                {
                    remove(("appData/rentedMovies/user" + user.password + "/movie" + to_string(i) + ".file").c_str());
                    remove(("appData/rentedMovies/user" + user.password + "/copy" + to_string(i) + ".file").c_str());
                    remove(("appData/rentedMovies/user" + user.password + "/date" + to_string(i) + ".file").c_str());
                }
                sleep(100);
                RemoveDirectory(("appData/rentedMovies/user" + user.password).c_str());
                fullCenterMe("User removed successfully", 1);
                fullCenterMe("Press any key to get back to menu...", -2);
                totalUsr--;
                ofstream totalUserFile1("appData/Users/totalUser.file");
                totalUserFile1 << totalUsr;
                totalUserFile1.close();
                _getch();
                menu();
            }
        }
    }
}