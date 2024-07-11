using namespace std;
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
        fullCenterMe("Press any key to return back to menu...", -1);
        _getch();
        addUser();
    }
    int status = checkUserStatus(user.password);
    if (status == 0)
    {
        fullCenterMe("User not found", 1);
        fullCenterMe("Press any key to return back to menu...", -1);
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
            fullCenterMe("Press any key to return back to menu...", -1);
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
        }
    }
    _getch();
    menu();
}