using namespace std;
void loginPannel()
{
    usrnpass admin, check;
    cls();
    printEnd("DEVELOPED BY AADARSHA KHANAL, BIGYAN POKHREL, SURAJ GUVAJU & NISHANT SUBEDI");
    cout << endl;
    centerMe("Login Pannel For Admin");
    cout << endl;
    cout << endl;
    cout << "Enter the admin name (no spaces are allowed): ";
    cout << endl
         << " ";
    char c;
    while ((c = _getch()) != 13 || admin.name.length() < 1)
    {
        if (c == 13)
        {
            continue;
        }
        else if (c == 8)
        {
            if (admin.name.length() > 0)
            {
                admin.name.pop_back();
                std::cout << "\b \b";
            }
        }
        else if (c == 32)
        {
            continue;
        }
        else
        {
            admin.name.push_back(c);
            std::cout << c;
        }
    }
    cout << endl;
    cout << endl;
passwordEntry:
    cout << "Enter the admin password (no spaces allowed): ";
    cout << endl
         << " ";
    while ((c = _getch()) != 13 || admin.password.length() < 1)
    {
        if (c == 13)
        {
            continue;
        }
        else if (c == 8)
        {
            if (admin.password.length() > 0)
            {
                admin.password.pop_back();
                std::cout << "\b \b";
            }
        }
        else if (c == 32)
        {
            continue;
        }
        else
        {
            admin.password.push_back(c);
            std::cout << "*";
        }
    }
    ifstream file("appData/login/adminDetail.file");
    file >> check.name >> check.password;
    file.close();
    decrypt(&check.password);
    decrypt(&check.name);
    if (admin.name == check.name)
    {
        if (check.password == admin.password)
        {
            cls();
            fullCenterMe("Login Successful");
            sleep(1000);
            menu();
        }
        else
        {
            admin.password.clear();
            fullCenterMe("Incorrect Password", 1);
            fullCenterMe("Press any key to try again", -1);
            getch();
            cls();
            printEnd("DEVELOPED BY AADARSHA KHANAL, BIGYAN POKHREL, SURAJ GUVAJU & NISHANT SUBEDI");
            cout << endl;
            centerMe("Login Pannel For Admin");
            cout << endl;
            cout << endl;
            cout << "Enter the admin name (no spaces are allowed): ";
            cout << endl
                 << " " << admin.name << endl
                 << endl;
            goto passwordEntry;
        }
    }
    else
    {
        fullCenterMe("Incorrect Username", 1);
        fullCenterMe("Press any key to try again", -1);
        getch();
        loginPannel();
    }
}