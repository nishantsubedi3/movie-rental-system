using namespace std;
void addUser()
{
    cls();
    usrnpass user;
    char c;
    int i = 0;
    printEnd("DEVELOPED BY AADARSHA KHANAL, BIGYAN POKHREL, SURAJ GUVAJU & NISHANT SUBEDI");
    cout << endl;
    centerMe("REGISTER A USER");
    cout << endl;
    cout << endl;
    cout << "Enter the username: ";
    cout << endl
         << " ";
    while ((c = _getch()) != 13 || user.name.length() < 1)
    {
        if (c == 13)
        {
            continue;
        }
        else if (c == 8)
        {
            if (user.name.length() > 0)
            {
                user.name.pop_back();
                std::cout << "\b \b";
            }
        }
        else
        {
            user.name.push_back(c);
            std::cout << c;
        }
    }
    cout << endl;
    cout << endl;
    cout << "Enter user phone number: ";
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
    if (user.password[0] != '9' || user.password[1] != '8' && user.password[0] != '9' || user.password[1] != '7')
    {
        fullCenterMe("Invalid phone number", 1);
        fullCenterMe("Press any key to return back to menu...", -1);
        _getch();
        addUser();
    }
    int status = checkUserStatus(user.password);
    encrypt(&user.password);
    encrypt(&user.name);
    if (status == 1)
    {
        fullCenterMe("User already exists", 1);
        fullCenterMe("Press any key to return back to menu...", -1);
        _getch();
        addUser();
    }
    else
    {
        int totalUsers;
        ifstream file("appData/Users/totalUser.file");
        if (!file)
        {
            fullCenterMe("Unknown Error!");
            return;
        }
        else
        {
            file >> totalUsers;
            file.close();
            ofstream create("appData/Users/user" + to_string(totalUsers + 1) + ".file");
            create << user.password;
            create.close();
            ofstream update("appData/Users/totalUser.file");
            update << totalUsers + 1;
            update.close();
            ofstream userNameAdd("appData/Users/user_name" + to_string(totalUsers + 1) + ".file");
            userNameAdd << user.name;
            userNameAdd.close();
            decrypt(&user.password);
            int stat = makeDirectory(("appData/rentedMovies/user" + user.password).c_str());
            if (stat == 0 || status == -1)
            {
                ofstream rented("appData/rentedMovies/user" + user.password + "/totalMovie.file");
                rented << 0;
                rented.close();
            }
            fullCenterMe("User added successfully", 1);
            fullCenterMe("Press any key to return back to menu...", -1);
            _getch();
            menu();
            return;
        }
    }
}

int checkUserStatus(string phone)
{
    string line;
    int user;
    ifstream file("appData/Users/totalUser.file");
    if (!file)
    {
        file.close();
        ofstream create("appData/Users/totalUser.file");
        create << 0;
        create.close();
    }
    else
    {
        file.close();
    }
    ifstream find("appData/Users/totalUser.file");
    find >> user;
    find.close();
    if (user == 0)
    {
        return 0;
    }
    for (int i = 1; i <= user; i++)
    {
        ifstream checkMyStatus("appData/Users/user" + to_string(i) + ".file");
        getline(checkMyStatus, line);
        decrypt(&line);
        if (line == phone)
        {
            return 1;
        }
        checkMyStatus.close();
    }
    return 0;
}

int addUser(string phone)
{
    string name;
    char c;
    cout << endl
         << "Enter the user name: ";
    while ((c = _getch()) != 13 || name.length() < 1)
    {
        if (c == 13)
        {
            continue;
        }
        else if (c == 8)
        {
            if (name.length() > 0)
            {
                name.pop_back();
                std::cout << "\b \b";
            }
        }
        else
        {
            name.push_back(c);
            std::cout << c;
        }
    }
    cout << endl;
    cout << endl;
    int totalUsers;
    ifstream file("appData/Users/totalUser.file");
    if (!file)
    {
        fullCenterMe("Unknown Error!");
        return 0;
    }
    else
    {
        file >> totalUsers;
        file.close();
        ofstream create("appData/Users/user" + to_string(totalUsers + 1) + ".file");
        create << phone;
        create.close();
        ofstream update("appData/Users/totalUser.file");
        update << totalUsers + 1;
        update.close();
        ofstream userNameAdd("appData/Users/user_name" + to_string(totalUsers + 1) + ".file");
        encrypt(&name);
        userNameAdd << name;
        userNameAdd.close();
        decrypt(&phone);
        int status = makeDirectory(("appData/rentedMovies/user" + phone).c_str());
        if (status == 0 || status == -1)
        {
            ofstream rented("appData/rentedMovies/user" + phone + "/totalMovie.file");
            rented << 0;
            rented.close();
        }
        return 1;
    }
    return 0;
}