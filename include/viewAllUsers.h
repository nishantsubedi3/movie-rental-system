using namespace std;
void viewUser(int n = 1, int q = 0)
{
    cls();
    usrnpass user;
    int i = 0;
    printEnd("DEVELOPED BY AADARSHA KHANAL, BIGYAN POKHREL, SURAJ GUVAJU & NISHANT SUBEDI");
    cout << endl;
    centerMe("List of all users");
    cout << endl;
    cout << endl;
    int total;
    ifstream totalUser("appData/Users/totalUser.file");
    if (!totalUser)
    {
        fullCenterMe("No users found!", 1);
        fullCenterMe("Press any key to return to menu.....", -2);
        _getch();
        menu();
    }
    totalUser >> total;
    totalUser.close();
    cout << setw(10) << left << "S.N. " << setw(50) << left << "User's Name" << setw(25) << left << "User's Phone Number" << endl
         << endl;
    while (n <= total && i < 10)
    {
        ifstream userPhone("appData/Users/user" + to_string(n) + ".file");
        getline(userPhone, user.password);
        ifstream userName("appData/Users/user_name" + to_string(n) + ".file");
        getline(userName, user.name);
        userPhone.close();
        userName.close();
        decrypt(&user.name);
        decrypt(&user.password);
        cout << setw(10) << left << to_string(n) + ". " << setw(50) << left << user.name << setw(25) << left << user.password << endl
             << endl;
        n++;
        i++;
    }
    char c;
    cout << endl;
    cout << endl;
    cout << endl;
    fflush(stdin);
    if (total > 10)
    {
        cout << "Press d key to view more movies (a to go back) or any other key to go back to menu.....";
        c = _getch();
        if (c == 100 && n < total)
        {
            q++;
            viewUser(n, q);
        }
        else if (c == 97 && n > i && q > 0)
        {
            q--;
            n -= i;
            viewUser((n - 10), q);
        }
        else if (c != 100 && c != 97)
        {
            menu();
        }
        else
        {
            viewUser();
        }
    }
    else
    {
        cout << "Press any key to go back to menu.....";
        _getch();
        menu();
    }
}