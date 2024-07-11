using namespace std;
void menu()
{
    cls();
    printEnd("DEVELOPED BY AADARSHA KHANAL, BIGYAN POKHREL, SURAJ GUVAJU & NISHANT SUBEDI");
    int choice;
    cout << endl;
    centerMe("Menu");
    cout << endl;
    cout << endl;
    centerMe("1. Rent a movie");
    cout << endl;
    cout << endl;
    centerMe("2. Return a movie");
    cout << endl;
    cout << endl;
    centerMe("3. View all movies");
    cout << endl;
    cout << endl;
    centerMe("4. Add a user");
    cout << endl;
    cout << endl;
    centerMe("5. Remove a user");
    cout << endl;
    cout << endl;
    centerMe("6. View all users");
    cout << endl;
    cout << endl;
    centerMe("7. Add a movie");
    cout << endl;
    cout << endl;
    centerMe("8. Remove a movie");
    cout << endl;
    cout << endl;
    centerMe("Enter your choice: ");
    cin >> choice;
    switch (choice)
    {
    case 1:
        rentMovie();
        break;
    case 3:
        viewMovie(1, 0);
        break;
    case 4:
        addUser();
        break;
    case 5:
        removeUser();
        break;
    case 6:
        viewUser(1, 0);
        break;
    case 7:
        addMovie();
        break;
    case 8:
        removeMovie();
        break;
    default:
        fullCenterMe("INVALID CHOICE!");
        sleep(1000);
        menu();
        break;
    }
}