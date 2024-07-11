using namespace std;
int firstTime(){
    ifstream file("appData/login/adminDetail.file");
    if(!file){
        return 1;
    }
    else{
        return 0;
    }
}

void initialize(){
    int status;
    status = firstTime();
    if(status == 0){
        loginPannel();
    }
    else if(status == 1){
        fullCenterMe("WELCOME TO MOVIE RENTAL SYSTEM");
        sleep(2000);
        fullCenterMe("DEVELOPED BY AADARSHA KHANAL, BIGYAN POKHREL, SURAJ GUVAJU & NISHANT SUBEDI");
        sleep(1000);
        cls();
        makeFilesandFolders();
        registerAdmin();
    }
    else{
        cout << "Error: " << status << endl;
    }
}