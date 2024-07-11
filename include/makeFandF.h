void makeFilesandFolders()
{
    int status;
    status = makeDirectory("appData");
    if (status == 0 || status == -1)
    {
        status = makeDirectory("appData/login");
        if (status == 0 || status == -1)
        {
            status = makeDirectory("appData/Users");
            if (status == 0 || status == -1)
            {
                status = makeDirectory("appData/allMovies");
                if (status == 0 || status == -1)
                {
                    status = makeDirectory("appData/rentedMovies");
                    if (status == 0 || status == -1)
                    {
                        return;
                    }
                    else
                    {
                        remove("appData/allMovies");
                        remove("appData/Users");
                        remove("appData/login");
                        remove("appData");
                        cls();
                        fullCenterMe("Initialization error! Please restart the app!");
                    }
                }
                else
                {
                    remove("appData/Users");
                    remove("appData/login");
                    remove("appData");
                    cls();
                    fullCenterMe("Initialization error! Please restart the app!");
                }
            }
            else
            {
                remove("appData/login");
                remove("appData");
                cls();
                fullCenterMe("Initialization error! Please restart the app!");
            }
        }
        else
        {
            remove("appData");
            cls();
            fullCenterMe("Initialization error! Please restart the app!");
        }
    }
    else
    {
        cls();
        fullCenterMe("Initialization error! Please restart the app!");
    }
}