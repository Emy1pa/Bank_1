#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <iomanip>
using namespace std;



void StartProgram();
void StartTransactionMenu();
void RedirectUserToMainMenue();
void ManageUsersMenuScreen();
void HandleUserManagement();

const string ClientInfoFileName = "ClientInfo.txt";
const string UserInfoFileName = "Users.txt";

struct stTransactionsClient {
    double Deposit;
    double Withdraw;
    double TotalBalances = 0;
};

struct stClientData {
    string AccountNumber = "";
    string PinCode = "";
    string ClientName = "";
    string ClientPhone = "";
    int AccountBalance = 0;
    bool MarkForDelete = false;
};

struct stUserInfo {
    string UserName = "";
    string Password = "";
    short Permission;
    bool FullAccess = false;
    bool MarkForDelete = false;
};

stUserInfo CurrentUser;

enum enSubMenuOption {
    enDeposit = 1,
    enWithdraw = 2,
    enTotalBalances = 3,
    enMainMenu = 4,
};

enum enMainMenuOption {
    ShowClientList = 1,
    AddNewClient = 2,
    DeleteClient = 3,
    UpdateClientInfo = 4,
    FindClient = 5,
    Transactions = 6,
    ManageUsers = 7,
    Logout = 8,
};

enum enUserMenuOption {
    ShowUserList = 1,
    AddNewUser = 2,
    DeleteUser = 3,
    UpdateUserInfo = 4,
    FindUser = 5,
    MainMenu = 6,
};

enum enListOfPermissions {
    enShowClientList = 1,
    enAddNewClient = 2,
    enDeleteClient = 3,
    enUpdateClient = 4,
    enFindClient = 5,
    enHandleTransaction = 6,
    enManageUsers = 7,
};

string ConvertRecordToLine(stClientData ClientInfo, string Seperator = "#//#") {
    string stClientRecord = "";
    stClientRecord += ClientInfo.AccountNumber + Seperator;
    stClientRecord += ClientInfo.PinCode + Seperator;
    stClientRecord += ClientInfo.ClientName + Seperator;
    stClientRecord += ClientInfo.ClientPhone + Seperator;
    stClientRecord += to_string(ClientInfo.AccountBalance);
    return stClientRecord;
}

vector <string> SplitString(string S1, string Seperator){
    short pos = 0;
    vector <string> vClient;
    string sWord = "";
    while((pos = S1.find(Seperator)) != std::string::npos){
        sWord = S1.substr(0, pos);
        if (sWord != "") {
            vClient.push_back(sWord);
        }
        S1.erase(0, pos + Seperator.length());
    }
    if (S1 != "") {
        vClient.push_back(S1);
    }
    return vClient;
}

stClientData ConvertLineToRecord(string Line, string Seperator = "#//#") {
    stClientData ClientInfo;
    vector <string> vClientData;
    vClientData = SplitString(Line, Seperator);


    ClientInfo.AccountNumber = vClientData[0];
    ClientInfo.PinCode = vClientData[1];
    ClientInfo.ClientName = vClientData[2];
    ClientInfo.ClientPhone = vClientData[3];
    ClientInfo.AccountBalance = stod(vClientData[4]);
    return ClientInfo;
}

vector <stClientData> LoadClientsDataFromFile(string FileName) {
    fstream MyFile;
    vector <stClientData> vClientData;
    MyFile.open(ClientInfoFileName, ios::in);
    if (MyFile.is_open()) {
        string Line;
        stClientData ClientInfo;
        while (getline(MyFile, Line)) {
            ClientInfo = ConvertLineToRecord(Line);
            vClientData.push_back(ClientInfo);
        }
        MyFile.close();
    }
    return vClientData;
}

stClientData ReadNewClient() {
    vector <stClientData> vClients = LoadClientsDataFromFile(ClientInfoFileName);
    stClientData ClientInfo;
    cout << "****************************\n";
    cin.ignore();
    while (true) {
        cout << "Enter Account Number ? ";
        getline(cin, ClientInfo.AccountNumber);
        bool exists = false;

        for (stClientData& C : vClients) {
            if (ClientInfo.AccountNumber == C.AccountNumber) {
                cout << "Client with [" << ClientInfo.AccountNumber << "] already exists, ";
                exists = true;
                break;
            }
        }
        if (!exists) break;
    }
    cout << "Enter Pincode ? ";
    getline(cin, ClientInfo.PinCode);
    cout << "Enter Client Name ? ";
    getline(cin, ClientInfo.ClientName);
    cout << "Enter Client Phone ? ";
    getline(cin, ClientInfo.ClientPhone);
    cout << "Enter Account Balance ? ";
    cin >> ClientInfo.AccountBalance;
    cout << "****************************\n";
    return ClientInfo;
}

void PrintClientRecord(stClientData ClientInfo){
    cout << "| " << left << setw(15) << ClientInfo.AccountNumber;
    cout << "| " << left << setw(10) << ClientInfo.PinCode;
    cout << "| " << left << setw(30) << ClientInfo.ClientName;
    cout << "| " << left << setw(12) << ClientInfo.ClientPhone;
    cout << "| " << left << setw(12) << ClientInfo.AccountBalance;
}

void PrintUserRecord(stUserInfo UserInfo){
    cout << "| " << left << setw(15) << UserInfo.UserName;
    cout << "| " << left << setw(10) << UserInfo.Password;
    cout << "| " << left << setw(12) << UserInfo.Permission;

}

void PrintAllClientsData(vector <stClientData> vClientData){
    cout << "\n\t\t\t\t\t Client List (" << vClientData.size() << ") Client(s).";
    cout << "\n---------------------------------------------------------";
    cout << "-------------------------------------------\n" << endl;
    cout << "| " << left << setw(15) << "Account Number";
    cout << "| " << left << setw(10) << "Pin Code ";
    cout << "| " << left << setw(30) << "Client Name";
    cout << "| " << left << setw(12) << "Phone ";
    cout << "| " << left << setw(12) << "Balance ";
    cout << "\n---------------------------------------------------------";
    cout << "-------------------------------------------\n" << endl;

    if (vClientData.size() == 0) 
        cout << "\t\t\tNo Clients Available In the System! ";
    else

        for(stClientData &Client: vClientData){
            PrintClientRecord(Client);
        cout << endl;
    }
    cout << "\n---------------------------------------------------------";
    cout << "-------------------------------------------\n" << endl;
    system("pause");

}

void PrintAllUsersData(vector <stUserInfo> vUserData) {
    cout << "\n\t\t\t\t\t Users List (" << vUserData.size() << ") User(s).";
    cout << "\n---------------------------------------------------------";
    cout << "-------------------------------------------\n" << endl;
    cout << "| " << left << setw(15) << "Username";
    cout << "| " << left << setw(10) << "Password ";
    cout << "| " << left << setw(12) << "Permissions ";
    cout << "\n---------------------------------------------------------";
    cout << "-------------------------------------------\n" << endl;

    if (vUserData.size() == 0)
        cout << "\t\t\tNo Users Available In the System! ";
    else

        for (stUserInfo& User : vUserData) {
            PrintUserRecord(User);
            cout << endl;
        }
    cout << "\n---------------------------------------------------------";
    cout << "-------------------------------------------\n" << endl;
    system("pause");

}

void DisplayAllUsers(){
    vector <stClientData> ClientData = LoadClientsDataFromFile(ClientInfoFileName);
    PrintAllClientsData(ClientData);
}

void AddDataLineToFile(string FileName, string strDataLine) {
    fstream MyFile;
    MyFile.open(FileName, ios::app | ios::out);
    if (MyFile.is_open()) {
        MyFile << strDataLine << endl;
        MyFile.close();
    }
}

void AddNewClientHeader() {
    cout << "\n------------------------------------------\n";
    cout << "\t     Add New Clients Screen \n";
    cout << "------------------------------------------\n\n";
    cout << "Adding New Client: \n";
}

void AddNewClientFunction(){
   
    stClientData ClientData = ReadNewClient();
    AddDataLineToFile(ClientInfoFileName, ConvertRecordToLine(ClientData));
}

void AddNewClients() {
    char AddMore = 'Y';
    do
    {
        AddNewClientFunction();
        cout << "Client Added Successfully, do you want to add more clients ? (Y/N) ? ";
        cin >> AddMore;
        cout << "\n";
    } while (toupper(AddMore) == 'Y');

}

void FindClientHeader() {
    cout << "\n------------------------------------------\n";
    cout << "\t     Find Client Screen \n";
    cout << "------------------------------------------\n\n";
}

void PrintOneClientRecord(stClientData ClientInfo){
    cout << "\n\nThe following is the extracted client record: \n\n";
    cout << "------------------------------------------------\n";
    cout << "Account Number  : " << ClientInfo.AccountNumber << endl;
    cout << "Pincode         : " << ClientInfo.PinCode << endl;
    cout << "Client Name     : " << ClientInfo.ClientName << endl;
    cout << "Client Phone    : " << ClientInfo.ClientPhone << endl;
    cout << "Account Balance : " << ClientInfo.AccountBalance << endl;
    cout << "------------------------------------------------\n\n";

}

bool FindClientByAccountNumber(string AccountNumber, vector <stClientData> &vClients, stClientData &ClientInfo){
    vClients = LoadClientsDataFromFile(ClientInfoFileName);
    for (stClientData C : vClients) {
        if(C.AccountNumber == AccountNumber){
            ClientInfo = C;
            return true;
        }
    }
    return false;
}

string ReadClientAccountNumber() {
    string AccountNumber = "";
    cout << "\nPlease enter Account Number ? ";
    cin >> AccountNumber;
    return AccountNumber;
}

void PrintClientFindResult() {
    FindClientHeader();
    stClientData Client;
    vector <stClientData> vClients = LoadClientsDataFromFile(ClientInfoFileName);
    if (vClients.empty()) {
        cout << "No Clients Available In the System! \n\n";
        system("pause");
    }
    else {
    string AccountNumber = ReadClientAccountNumber();
    if (FindClientByAccountNumber(AccountNumber, vClients, Client)) {
        PrintOneClientRecord(Client);
        system("pause");
    }
    else {
        cout << "\nClient with Account Number (" << AccountNumber << ") is NOT Found!\n\n";
        system("pause");
    }
   }
    
}

void DeleteClientScreen(){
    cout << "\n------------------------------------------\n";
    cout << "\t     Delete Client Screen \n";
    cout << "------------------------------------------\n\n";
}

bool MarkClientForDeletion(string AccountNumber, vector <stClientData> &vClients){
    for (stClientData& C : vClients) {
        if (C.AccountNumber == AccountNumber) {
            C.MarkForDelete = true;
            return true;
        }
    }
    return false;
}

vector <stClientData> SaveClientsDataToFile(string FileName, vector <stClientData> vClients){
    fstream MyFile;
    MyFile.open(FileName, ios::out);
    string DataLine;
    if (MyFile.is_open()) {
        for (stClientData &C: vClients )
        {
            if (C.MarkForDelete == false) {
                DataLine = ConvertRecordToLine(C);
                MyFile << DataLine << endl;
            }
        }
        MyFile.close();
    }
    return vClients;
}

bool DeleteClientByAccountNumber(string AccountNumber, vector <stClientData> &vClients){

    stClientData Client;
    char Answer = 'n';
    if (FindClientByAccountNumber(AccountNumber, vClients, Client)) {
        PrintOneClientRecord(Client);
        cout << "\n\nAre you sure you want delete client ? (Y/N) ? ";
        cin >> Answer;
        if (toupper(Answer) == 'Y') {
            MarkClientForDeletion(AccountNumber, vClients);
            SaveClientsDataToFile(ClientInfoFileName, vClients);

            vClients = LoadClientsDataFromFile(ClientInfoFileName);
            cout << "\n\nClient Deleted Successfully. \n";
            system("pause");
            return true;
        }
        
    }
    else
    {
        cout << "\nClient with Account Number (" << AccountNumber << ") is NOT Found!\n\n";
        system("pause");
        return false;
    }
}

void DeleteClientRecord() {
    DeleteClientScreen();

    vector <stClientData> vClients = LoadClientsDataFromFile(ClientInfoFileName);
    if (vClients.empty()) {
        cout << "No Clients Available In the System! \n\n";
        system("pause");
    }
    else {
    string AccountNumber = ReadClientAccountNumber();
    DeleteClientByAccountNumber(AccountNumber, vClients);
    }
}

void UpdateClientInfoScreen() {
    cout << "\n------------------------------------------\n";
    cout << "\t     Update Client Info Screen \n";
    cout << "------------------------------------------\n\n";
}

stClientData ChangeClientRecord(string AccountNumber) {
    stClientData Client;

    Client.AccountNumber = AccountNumber;

    cout << "Enter PinCode ? ";
    getline(cin >> ws, Client.PinCode);
    cout << "Enter Name ? ";
    getline(cin, Client.ClientName);
    cout << "Enter Phone ? ";
    getline(cin, Client.ClientPhone);
    cout << "Enter Account Balance ? ";
    cin >> Client.AccountBalance;
    return Client;
}

bool UpdateClientByAccountNumber(string AccountNumber, vector <stClientData>& vClients) {
    stClientData Client;
    char Answer = 'n';
    if (FindClientByAccountNumber(AccountNumber, vClients, Client)) {
        PrintOneClientRecord(Client);
        cout << "\n\nAre you sure you want Update client ? (Y/N) ? ";
        cin >> Answer;
        if (toupper(Answer) == 'Y') {
            for (stClientData& C : vClients) {
                if (C.AccountNumber == AccountNumber) {
                    C = ChangeClientRecord(AccountNumber);
                    break;
                }
            }
            SaveClientsDataToFile(ClientInfoFileName, vClients);
            vClients = LoadClientsDataFromFile(ClientInfoFileName);
            cout << "\n\n Client Updated Successfully. \n\n";
            system("pause");
            return true;
        }
        
    }
    else {
        cout << "\nClient with Account Number (" << AccountNumber << ") is NOT Found!\n\n";
        system("pause");
        return false;
    }
    
}

void UpdateClientRecord() {
    UpdateClientInfoScreen();

    vector <stClientData> vClients = LoadClientsDataFromFile(ClientInfoFileName);
    if (vClients.empty()) {
        cout << "No Clients Available In the System! \n\n";
        system("pause");
    }
    else {
    string AccountNumber = ReadClientAccountNumber();
    UpdateClientByAccountNumber(AccountNumber, vClients);
    }

}

enUserMenuOption ReadAdminUserChoice() {
    short AdminUserChoice = 0;
    while (true) {
        cout << "Choose what do you want to do ? [1-6] ? ";
        cin >> AdminUserChoice;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            system("Color 4F");
            cout << "\nInvalid input. Numbers only, please.\n";
            continue;
        }
        if (AdminUserChoice < 1 || AdminUserChoice > 6) {
            system("Color 4F");
            cout << "\nInvalid choice. Please enter a number between 1 and 6.\n";
            continue;
        }
        break;
    }
    return (enUserMenuOption) AdminUserChoice;
}

enMainMenuOption ReadUserChoice() {
    short UserChoice = 0;
    while (true) {
        cout << "Choose what do you want to do ? [1-8] ? ";
        cin >> UserChoice;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            system("Color 4F");
            cout << "\nInvalid input. Numbers only, please.\n";
            continue;
        }
        if (UserChoice < 1 || UserChoice > 8) {
            system("Color 4F");
            cout << "\nInvalid choice. Please enter a number between 1 and 8.\n";
            continue;
        }
        break;
    }
    return (enMainMenuOption)UserChoice;
}

enSubMenuOption ReadUserSubMenuChoice() {
    short UserChoice = 0;
    while (true) {
        cout << "Choose what do you want to do ? [1-4] ? ";
        cin >> UserChoice;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            system("Color 4F");
            cout << "\nInvalid input. Numbers only, please.\n";
            continue;
        }
        if (UserChoice < 1 || UserChoice > 4) {
            system("Color 4F");
            cout << "\nInvalid choice. Please enter a number between 1 and 4.\n";
            continue;
        }
        break;
    }
    return (enSubMenuOption)UserChoice;
}

void ShowMenuScreen() {    
        cout << "====================================================\n";
        cout << "\t\t Main Menu Screen\n";
        cout << "====================================================\n";
        cout << "\t [1] Show Client List. \n";
        cout << "\t [2] Add New Client. \n";
        cout << "\t [3] Delete Client. \n";
        cout << "\t [4] Update Client Info. \n";
        cout << "\t [5] Find Client. \n";
        cout << "\t [6] Transactions. \n";
        cout << "\t [7] Manage Users. \n";
        cout << "\t [8] Logout. \n";
        cout << "====================================================\n";
}

void ShowTransactionsMenuScreen() {
    cout << "====================================================\n";
    cout << "\t\t Transactions Menu Screen\n";
    cout << "====================================================\n";
    cout << "\t [1] Deposit. \n";
    cout << "\t [2] Withdraw. \n";
    cout << "\t [3] Total Balances. \n";
    cout << "\t [4] Main Menu. \n";
    cout << "====================================================\n";
}

void ExitProgram() {
    cout << "\n------------------------------------------\n";
    cout << "\t     Program Ends :-) \n";
    cout << "------------------------------------------\n\n";
    system("pause");
}

void ResetScreen() {
    system("Color 0F");
    system("cls");
}

void HandleUserChoice(enMainMenuOption UserMenuChoice){

    switch (UserMenuChoice)
    {
    case enMainMenuOption::ShowClientList:
        DisplayAllUsers();
        
        break;
    case enMainMenuOption::AddNewClient:
        AddNewClientHeader();
        AddNewClients();
        break;
    case enMainMenuOption::DeleteClient:
        DeleteClientRecord();
        break;
    case enMainMenuOption::UpdateClientInfo:
        UpdateClientRecord();
        break;
    case enMainMenuOption::FindClient:
        PrintClientFindResult();
        break;
    case enMainMenuOption::Transactions:
        StartTransactionMenu();
        break;
    case enMainMenuOption::ManageUsers:
        HandleUserManagement();
        break;
    case enMainMenuOption::Logout:
        RedirectUserToMainMenue();
        break;
    }
}

void DepositScreen() {
    cout << "\n------------------------------------------\n";
    cout << "\t     Deposit Screen \n";
    cout << "------------------------------------------\n\n";
}

stTransactionsClient ReadDepositNumber() {
    stTransactionsClient TransactionClient;
    cout << "Please enter positive deposit amount ? ";
    cin >> TransactionClient.Deposit;
    return TransactionClient;
}

stTransactionsClient ReadWithdrawNumber() {
    stTransactionsClient TransactionClient;
    cout << "Please enter positive withdraw amount ? ";
    cin >> TransactionClient.Withdraw;
    return TransactionClient;
}

void HandleDepositBalanceTotal(string AccountNumber, stClientData &Client) {
    vector <stClientData> vClients;
    vClients = LoadClientsDataFromFile(ClientInfoFileName);
    stTransactionsClient TransactionClient;
    do
    {
        TransactionClient = ReadDepositNumber();
    } while (TransactionClient.Deposit < 0);

    char Answer = 'n';
    cout << "\nAre you sure you want to perform this transaction ? (Y/N) ? ";
    cin >> Answer;
    cout << endl;
    if (toupper(Answer) == 'Y') {
        for (stClientData& C : vClients) {
            if (C.AccountNumber == AccountNumber) {
                C.AccountBalance += TransactionClient.Deposit ;
                Client = C;
            }
        }
    }
    SaveClientsDataToFile(ClientInfoFileName, vClients);
    vClients = LoadClientsDataFromFile(ClientInfoFileName);
    cout << "Done Successfully, New Balance is [" << Client.AccountBalance << "] \n\n";
    system("pause");
}

void HandleDepositAccount() {
    string AccountNumber;
    vector <stClientData> vClients;

    vClients = LoadClientsDataFromFile(ClientInfoFileName);
    stClientData Client;
    bool Found = false;
    do
    {
        AccountNumber = ReadClientAccountNumber();
        Found = false;
        for (stClientData& C : vClients) {
            if (AccountNumber == C.AccountNumber) {

                Client = C;
                Found = true;
                break;
            }
        }
        if (!Found) {
            cout << "Client with [" << AccountNumber << "] does not exist.\n";
        }

    } while (!Found);

    PrintOneClientRecord(Client);
    HandleDepositBalanceTotal(AccountNumber, Client);
}

void WithdrawScreen() {
    cout << "\n------------------------------------------\n";
    cout << "\t     Withdraw Screen \n";
    cout << "------------------------------------------\n\n";
}

void HandleWithdrawBalanceTotal(string AccountNumber, stClientData &Client){
    vector <stClientData> vClients;
    vClients = LoadClientsDataFromFile(ClientInfoFileName);
    stTransactionsClient TransactionClient;
    do
    {
        TransactionClient = ReadWithdrawNumber();
    } while (TransactionClient.Withdraw < 0);
    for (stClientData& C : vClients) {
        if (C.AccountNumber == AccountNumber) {

            if (TransactionClient.Withdraw > Client.AccountBalance) {
                do
                {
                    cout << "\nAmount Exceeds the balance, you can withdraw up to: " << Client.AccountBalance << endl;
                    cout << "\nPlease enter another amount ? ";
                    cin >> TransactionClient.Withdraw;
                } while (TransactionClient.Withdraw > Client.AccountBalance);
            }
            char Answer = 'n';
            cout << "\nAre you sure you want to perform this transaction ? (Y/N) ? ";
            cin >> Answer;
            if (toupper(Answer) == 'Y') {
            C.AccountBalance -= TransactionClient.Withdraw;
            Client = C;
            SaveClientsDataToFile(ClientInfoFileName, vClients);
            vClients = LoadClientsDataFromFile(ClientInfoFileName);
            cout << "\nDone Successfully, New Balance is [" << Client.AccountBalance << "] \n\n";
            system("pause");
            }

            else {
                cout << "\n";
                system("pause");
                
            }
        }

    }
    
}

void HandleWithdrawFunction() {
    string AccountNumber;
    vector <stClientData> vClients;
    vClients = LoadClientsDataFromFile(ClientInfoFileName);
    stClientData Client;
    bool Found = false;
    do
    {
        AccountNumber = ReadClientAccountNumber();
        Found = false;
        for (stClientData& C : vClients) {
            if (AccountNumber == C.AccountNumber) {

                Client = C;
                Found = true;
                break;
            }
        }
        if (!Found) {
            cout << "\nClient with [" << AccountNumber << "] does not exist.\n";
        }
    } while (!Found);
    PrintOneClientRecord(Client);
    HandleWithdrawBalanceTotal(AccountNumber, Client);

}

void PrintClientBalanceRecord(stClientData ClientInfo) {
    cout << "| " << left << setw(15) << ClientInfo.AccountNumber;
    cout << "| " << left << setw(30) << ClientInfo.ClientName;
    cout << "| " << left << setw(12) << ClientInfo.AccountBalance;
}

double DisplayAllBalancesOfClients(vector <stClientData> vClientData){
    stTransactionsClient TranScationClient;
    for (stClientData C : vClientData) {
        TranScationClient.TotalBalances += C.AccountBalance;
    }
    return TranScationClient.TotalBalances;
}

void PrintAllClientsBalanceData(vector <stClientData> vClientData) {
    cout << "\n\t\t\t\t\t Balances List (" << vClientData.size() << ") Client(s).";
    cout << "\n---------------------------------------------------------";
    cout << "-------------------------------------------\n" << endl;
    cout << "| " << left << setw(15) << "Account Number";
    cout << "| " << left << setw(30) << "Client Name";
    cout << "| " << left << setw(12) << "Balance ";
    cout << "\n---------------------------------------------------------";
    cout << "-------------------------------------------\n" << endl;

    for (stClientData& Client : vClientData) {
        PrintClientBalanceRecord(Client);
        cout << endl;
    }
    cout << "\n---------------------------------------------------------";
    cout << "-------------------------------------------\n" << endl;
    cout << "\t\t\t\t\t Total Balances = " << DisplayAllBalancesOfClients(vClientData) << endl << endl;
    system("pause");

}

void DisplayBalancesAllUsers() {
    vector <stClientData> ClientData = LoadClientsDataFromFile(ClientInfoFileName);
    PrintAllClientsBalanceData(ClientData);
}

void HandleUserSubMenuChoice(enSubMenuOption UserSubMenuChoice) {
    switch (UserSubMenuChoice)
    {
    case enSubMenuOption::enDeposit:
        DepositScreen();
        HandleDepositAccount();
        break;
    case enSubMenuOption::enWithdraw:
        WithdrawScreen();
        HandleWithdrawFunction();
        break;
    case enSubMenuOption::enTotalBalances:
        DisplayBalancesAllUsers();
        break;
    case enSubMenuOption::enMainMenu:
        ShowMenuScreen();
        break;
    }
}

void StartTransactionMenu() {
    enSubMenuOption UserChoice;
    do
    {
        ResetScreen();
        ShowTransactionsMenuScreen();
        UserChoice = ReadUserSubMenuChoice();
        ResetScreen();
        HandleUserSubMenuChoice(UserChoice);

    } while (UserChoice != enSubMenuOption::enMainMenu);
}

void DisplayAccessDenied() {
    cout << "\n------------------------------------------\n";
    cout << "Access Denied, \n";
    cout << "You don't Have Permission To Do this,\n";
    cout << "Please Contact Your Admin.\n";
    cout << "------------------------------------------\n";
    system("pause");
}

bool CheckForUserPermission(enMainMenuOption UserChoice) {
    if (CurrentUser.Permission == -1) {
        return true;
    }
    switch (UserChoice)
    {
    case enMainMenuOption::ShowClientList:
        return (CurrentUser.Permission & (1 << (enShowClientList - 1))) != 0;
    case enMainMenuOption::AddNewClient:
        return (CurrentUser.Permission & (1 << (enAddNewClient - 1))) != 0;
    case enMainMenuOption::DeleteClient:
        return (CurrentUser.Permission & (1 << (enDeleteClient - 1))) != 0;
    case enMainMenuOption::UpdateClientInfo:
        return (CurrentUser.Permission & (1 << (enUpdateClient - 1))) != 0;
    case enMainMenuOption::FindClient:
        return (CurrentUser.Permission & (1 << (enFindClient - 1))) != 0;
    case enMainMenuOption::Transactions:
        return (CurrentUser.Permission & (1 << (enHandleTransaction - 1))) != 0;
    case enMainMenuOption::ManageUsers:
        return (CurrentUser.Permission & (1 << (enManageUsers - 1))) != 0;
    case enMainMenuOption::Logout:
        return true;
    default:
        return false;
    }
}

void StartProgram() {
    enMainMenuOption UserChoice;

    do
    {
        ResetScreen();
        ShowMenuScreen();
        UserChoice = ReadUserChoice();
        if (CheckForUserPermission(UserChoice)) {
        ResetScreen();
        HandleUserChoice(UserChoice);
        }
        else {
            ResetScreen();
            DisplayAccessDenied();
        }
    } while (UserChoice != enMainMenuOption::Logout);
}

stUserInfo ConvertUserLineToRecord(string Line, string Seperator = "#//#") {
    stUserInfo UserInfo;
    vector <string> vUserData;
    vUserData = SplitString(Line, Seperator);


    UserInfo.UserName = vUserData[0];
    UserInfo.Password = vUserData[1];
    UserInfo.Permission = stoi(vUserData[2]);
    return UserInfo;
}

vector <stUserInfo> LoadUsersDataFromFile(string FileName) {
    fstream MyFile;
    vector <stUserInfo> vUserData;
    MyFile.open(UserInfoFileName, ios::in);
    if (MyFile.is_open()) {
        string Line;
        stUserInfo UserInfo;
        while (getline(MyFile, Line)) {
            UserInfo = ConvertUserLineToRecord(Line);
            vUserData.push_back(UserInfo);
        }
        MyFile.close();
    }
    return vUserData;
}

void LoginScreen() {
    cout << "\n------------------------------------------\n";
    cout << "\t     Login Screen \n";
    cout << "------------------------------------------\n";
}

stUserInfo ReadUserInfo() {
    stUserInfo UserInfo;
    cout << "Enter Username ? ";
    getline(cin >> ws, UserInfo.UserName);
    cout << "Enter Password ? ";
    getline(cin, UserInfo.Password);
    
    return UserInfo;
}

bool CheckForExistingUser() {
    vector <stUserInfo> vUsers = LoadUsersDataFromFile(UserInfoFileName);
    stUserInfo UserInfo = ReadUserInfo();
    for (stUserInfo &U: vUsers) {
        if (UserInfo.UserName == U.UserName && UserInfo.Password == U.Password) {
            CurrentUser = U;
            return true;
        }
    }
    return false;
}

void RedirectUserToMainMenue() {
    LoginScreen();
    while (!CheckForExistingUser()) {
        ResetScreen();
        LoginScreen();
        cout << "\nInvalid username/Password !\n\n";
    }
    StartProgram();

}

void ManageUsersMenuScreen() {
    cout << "====================================================\n";
    cout << "\t\t Manage Users Menu Screen\n";
    cout << "====================================================\n";
    cout << "\t [1] List Users. \n";
    cout << "\t [2] Add New User. \n";
    cout << "\t [3] Delete User. \n";
    cout << "\t [4] Update User. \n";
    cout << "\t [5] Find User. \n";
    cout << "\t [6] Main Menu. \n";
    cout << "====================================================\n";
}

void DisplayAllUsersSubMenu() {
    ResetScreen();
    vector <stUserInfo> UserData = LoadUsersDataFromFile(UserInfoFileName);
    PrintAllUsersData(UserData);
    
}

void HandleAddNewUserScreen(){
    cout << "\n------------------------------------------\n";
    cout << "\t     Add New User Screen \n";
    cout << "------------------------------------------\n";
    cout << "Adding New User: \n";
}

stUserInfo ListOfPermissions(stUserInfo UserInfo) {
    char GivePermission = 'n';
    cout << "\nShow Client List ? (Y/N) ? ";
    cin >> GivePermission;
    if (toupper(GivePermission) == 'Y')
        UserInfo.Permission |= (1 << (enShowClientList - 1));

    cout << "\nAdd New Client ? (Y/N) ? ";
    cin >> GivePermission;
    if (toupper(GivePermission) == 'Y')
        UserInfo.Permission |= (1 << (enAddNewClient - 1));
    cout << "\nDelete Client List ? (Y/N) ? ";
    cin >> GivePermission;
    if (toupper(GivePermission) == 'Y')
        UserInfo.Permission |= (1 << (enDeleteClient - 1));
    cout << "\nUpdate Client ? (Y/N) ? ";
    cin >> GivePermission;
    if (toupper(GivePermission) == 'Y')
        UserInfo.Permission |= (1 << (enUpdateClient - 1));
    cout << "\nFind Client ? (Y/N) ? ";
    cin >> GivePermission;
    if (toupper(GivePermission) == 'Y')
        UserInfo.Permission |= (1 << (enFindClient - 1));
    cout << "\nTranscations ? (Y/N) ? ";
    cin >> GivePermission;
    if (toupper(GivePermission) == 'Y')
        UserInfo.Permission |= (1 << (enHandleTransaction - 1));
    cout << "\nManage Users ? (Y/N) ? ";
    cin >> GivePermission;
    if (toupper(GivePermission) == 'Y')
        UserInfo.Permission |= (1 << (enManageUsers - 1));
    return UserInfo;
}

stUserInfo AddNewUserFunc() {
    vector <stUserInfo> vUsers = LoadUsersDataFromFile(UserInfoFileName);
    stUserInfo UserInfo;
    cout << "****************************\n";
    cin.ignore();
    while (true) {
        cout << "Enter Username ? ";
        getline(cin, UserInfo.UserName);
        bool exists = false;

        for (stUserInfo& U : vUsers) {
            if (UserInfo.UserName == U.UserName) {
                cout << "\nUser with [" << UserInfo.UserName << "] already exists, ";
                exists = true;
                break;
            }
        }
        if (!exists) break;
    }
    /*cout << "Enter Username ? ";
    getline(cin, UserInfo.UserName);*/
    cout << "Enter Password ? ";
    getline(cin, UserInfo.Password);
    cout << "\nDo you want to give full access? (1/0) ? ";
    cin >> UserInfo.FullAccess;
    UserInfo.Permission = 0;
    if (UserInfo.FullAccess)
        UserInfo.Permission = -1;
    else {
        cout << "What do you want to give acces to: \n";
        UserInfo = ListOfPermissions(UserInfo);
    }
    cout << "****************************\n";
    return UserInfo;
}

string ConvertUserRecordToLine(stUserInfo UserInfo, string Seperator = "#//#") {
    string stUserRecord = "";
    stUserRecord += UserInfo.UserName + Seperator;
    stUserRecord += UserInfo.Password + Seperator;
    stUserRecord += to_string(UserInfo.Permission);
    return stUserRecord;
}

void AddNewUserFunction() {

    stUserInfo UserData = AddNewUserFunc();
    AddDataLineToFile(UserInfoFileName, ConvertUserRecordToLine(UserData));
}

void AddNewUsers() {
    char AddMore = 'Y';
    do
    {
        ResetScreen();
        HandleAddNewUserScreen();
        AddNewUserFunction();
        cout << "\nUser Added Successfully, do you want to add more users ? (Y/N) ? ";
        cin >> AddMore;
        cout << "\n\n";
    } while (toupper(AddMore) == 'Y');

}

void HandleAddNewUser() {
    ResetScreen();
    HandleAddNewUserScreen();
    AddNewUsers();
    system("pause");
    HandleUserManagement();
}

void DeleteUserScreen(){
    cout << "\n------------------------------------------\n";
    cout << "\t     Delete Users Screen \n";
    cout << "------------------------------------------\n";
}

bool FindUserByUserName(string UserName, vector <stUserInfo>& vUsers, stUserInfo& UserInfo) {
    vUsers = LoadUsersDataFromFile(UserInfoFileName);
    for (stUserInfo U : vUsers) {
        if (U.UserName == UserName) {
            UserInfo = U;
            return true;
        }
    }
    return false;
}

void FindUserHeader() {
    cout << "\n------------------------------------------\n";
    cout << "\t     Find User Screen \n";
    cout << "------------------------------------------\n\n";
}

string ReadUserByUserName() {
    string UserName = "";
    cout << "\nPlease enter Username ? ";
    cin >> UserName;
    return UserName;
}

void PrintOneUserRecord(stUserInfo UserInfo) {
    cout << "\n\nThe following is the extracted user record: \n\n";
    cout << "------------------------------------------------\n";
    cout << "User Name  : " << UserInfo.UserName << endl;
    cout << "Password   : " << UserInfo.Password << endl;
    cout << "Permission : " << UserInfo.Permission << endl;
    cout << "------------------------------------------------\n\n";

}

void PrintUserFindResult() {
    FindUserHeader();
    stUserInfo UserInfo;
    vector <stUserInfo> vUsers = LoadUsersDataFromFile(UserInfoFileName);
    if (vUsers.empty()) {
        cout << "No Users Available In the System! \n\n";
        system("pause");
    }
    else {
        string UserName = ReadUserByUserName();
        if (FindUserByUserName(UserName, vUsers, UserInfo)) {
            PrintOneUserRecord(UserInfo);
            system("pause");
        }
        else {
            cout << "\nUser with UserName (" << UserName << ") is NOT Found!\n\n";
            system("pause");
        }
    }

}

bool MarkUserForDeletion(string UserName, vector <stUserInfo>& vUsers) {
    for (stUserInfo& U : vUsers) {         
        if (U.UserName == UserName) {
            U.MarkForDelete = true;
            return true;
        }
    }
    return false;
}

vector <stUserInfo> SaveUsersDataToFile(string FileName, vector <stUserInfo> vUsers) {
    fstream MyFile;
    MyFile.open(FileName, ios::out);
    string DataLine;
    if (MyFile.is_open()) {
        for (stUserInfo& U : vUsers)
        {
            if (U.MarkForDelete == false) {
                DataLine = ConvertUserRecordToLine(U);
                MyFile << DataLine << endl;
            }
        }
        MyFile.close();
    }
    return vUsers;
}

bool DeleteUserByUserName(string UserName, vector <stUserInfo>& vUsers) {

    stUserInfo UserInfo;
    char Answer = 'n';
    if (FindUserByUserName(UserName, vUsers, UserInfo)) {
        if (UserName == "Admin") {
            cout << "You Can't Delete This User\n";
            system("pause");
        }
        else {
        PrintOneUserRecord(UserInfo);
        cout << "\nAre you sure you want delete user ? (Y/N) ? ";
        cin >> Answer;
        if (toupper(Answer) == 'Y') {
            MarkUserForDeletion(UserName, vUsers);
            SaveUsersDataToFile(UserInfoFileName, vUsers);
            vUsers = LoadUsersDataFromFile(UserInfoFileName);
            cout << "\nUser Deleted Successfully. \n";
            system("pause");
            return true;
        }
        }
    }
    else
    {
        cout << "\nUser with UserName (" << UserName << ") is NOT Found!\n\n";
        system("pause");
        return false;
    }
}

void DeleteUserRecord() {
    DeleteUserScreen();

    vector <stUserInfo> vUsers = LoadUsersDataFromFile(UserInfoFileName);
    if (vUsers.empty()) {
        cout << "No Users Available In the System! \n\n";
        system("pause");
    }
    else {
        string UserName = ReadUserByUserName();
        DeleteUserByUserName(UserName, vUsers);
    }
}

void UpdateUserInfoScreen() {
    cout << "\n------------------------------------------\n";
    cout << "\t     Update User Info Screen \n";
    cout << "------------------------------------------\n\n";
}

stUserInfo ChangeUserRecord(string UserName) {
    stUserInfo UserInfo;

    UserInfo.UserName = UserName;

    cout << "Enter Password ? ";
    getline(cin >> ws, UserInfo.Password);
    cout << "\nDo you want to give full access ? (1/0) ? ";
    cin >> UserInfo.FullAccess;
    UserInfo.Permission = 0;
    if (UserInfo.FullAccess)
        UserInfo.Permission = -1;
    else {
        cout << "\nWhat do you want to give acces to: \n";
        UserInfo = ListOfPermissions(UserInfo);
    }
    
    return UserInfo;
}

bool UpdateUserByUserName(string UserName, vector <stUserInfo>& vUsers) {
    stUserInfo UserInfo;
    char Answer = 'n';
    if (FindUserByUserName(UserName, vUsers, UserInfo)) {
        PrintOneUserRecord(UserInfo);
        cout << "\n\nAre you sure you want update this user ? (Y/N) ? ";
        cin >> Answer;
        cout << endl;
        if (toupper(Answer) == 'Y') {
            for (stUserInfo& U : vUsers) {
                if (U.UserName == UserName) {
                    U = ChangeUserRecord(UserName);
                    break;
                }
            }
            SaveUsersDataToFile(UserInfoFileName, vUsers);
            vUsers = LoadUsersDataFromFile(UserInfoFileName);
            cout << "\n\nUser Updated Successfully. \n\n";
            system("pause");
            return true;
        }

    }
    else {
        cout << "\nUser with UserName (" << UserName << ") is NOT Found!\n\n";
        system("pause");
        return false;
    }

}

void UpdateUserRecord() {
    UpdateUserInfoScreen();

    vector <stUserInfo> vUsers = LoadUsersDataFromFile(UserInfoFileName);
    if (vUsers.empty()) {
        cout << "No Users Available In the System! \n\n";
        system("pause");
    }
    else {
        string UserName = ReadUserByUserName();
        UpdateUserByUserName(UserName, vUsers);
    }

}

void HandleAdminUserChoice(enUserMenuOption AdminUserMenuChoice) {
    switch (AdminUserMenuChoice)
    {
    case enUserMenuOption::ShowUserList:
        DisplayAllUsersSubMenu();
        HandleUserManagement();
        break;
    case enUserMenuOption::AddNewUser:
        HandleAddNewUser();
        break;
    case enUserMenuOption::DeleteUser:
        ResetScreen();
        DeleteUserRecord();
        HandleUserManagement();
        break;
    case enUserMenuOption::UpdateUserInfo:
        ResetScreen();
        UpdateUserRecord();
        HandleUserManagement();
        break;
    case enUserMenuOption::FindUser:
        ResetScreen();
        PrintUserFindResult();
        HandleUserManagement();
        break;
    case enUserMenuOption::MainMenu:
        StartProgram();
        break;

    }
}

void HandleUserManagement() {
    ResetScreen();
    ManageUsersMenuScreen();
    enUserMenuOption HandleAdminChoice = ReadAdminUserChoice();
    HandleAdminUserChoice(HandleAdminChoice);
}


int main()
{
    RedirectUserToMainMenue();
    system("pause>0");
}
