int height, width;
void getConsoleSize(){
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    HANDLE console_handle = GetStdHandle(STD_OUTPUT_HANDLE);
    if (GetConsoleScreenBufferInfo(console_handle, &csbi))
    {
        width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    }
    if (GetConsoleScreenBufferInfo(console_handle, &csbi))
    {
        height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    }
}
void setCursorPosition(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void centerMe(std::string text) {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    int screenWidth = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    int padding = (screenWidth - static_cast<int>(text.length())) / 2;
    setCursorPosition(padding, csbi.dwCursorPosition.Y);
    std::cout << text;
}

void printEnd(std::string text, int i = 1){ 
    int padding = (width - static_cast<int>(text.length())) / 2;
    setCursorPosition(padding, height - i);
    std::cout << text;
    setCursorPosition(0,0);
}

void fullCenterMe(std::string text, int y = 0){
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    int screenWidth = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    int padding = (screenWidth - static_cast<int>(text.length())) / 2;
    int paddingY = (height - y) / 2;
    setCursorPosition(padding, paddingY);
    std::cout << text << std::endl;
}

void fullscreen()
{
keybd_event(VK_MENU,0x38,0,0);
keybd_event(VK_RETURN,0x1c,0,0);
keybd_event(VK_RETURN,0x1c,KEYEVENTF_KEYUP,0);
keybd_event(VK_MENU,0x38,KEYEVENTF_KEYUP,0);
Sleep(300);
getConsoleSize();
}

void cls(){
    system("cls");
    getConsoleSize();
}

int makeDirectory(const char *name)
{
    int status = mkdir(name);
    if (status == 0)
    {
        return 0;
    }
    else if (status == -1)
    {
        return -1;
    }
    else
    {
        return 1;
    }
}

void sleep(int milliseconds){
    Sleep(milliseconds);
}

void getDate(int *year, int *month, int *day){
    time_t t = time(nullptr);
    tm* localTime = localtime(&t);
    *year = localTime->tm_year + 1900;
    *month = localTime->tm_mon + 1;
    *day = localTime->tm_mday;
}