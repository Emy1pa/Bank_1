#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <iomanip>

using namespace std;

void StartProgram();
void StartTransactionMenu();

const string ClientInfoFileName = "ClientInfo.txt";

struct stTransactionsClient {
    double Deposit;
    double Withdraw;
    double TotalBalances;
};

struct stClientData {
    string AccountNumber = "";
    string PinCode = "";
    string ClientName = "";
    string ClientPhone = "";
    int AccountBalance = 0;
    bool MarkForDelete = false;
};

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
    Exit = 7,
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

    for(stClientData &Client: vClientData){
        PrintClientRecord(Client);
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
    cout << "Client Phone     : " << ClientInfo.ClientPhone << endl;
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
    vector <stClientData> vClients;
    string AccountNumber = ReadClientAccountNumber();
    if (FindClientByAccountNumber(AccountNumber, vClients, Client)) {
        PrintOneClientRecord(Client);
        system("pause");
    }
    else {
        cout << "\nClient with Account Number (" << AccountNumber << ") is NOT Found!\n";
    }
    system("pause");
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
    string AccountNumber = ReadClientAccountNumber();
    vector <stClientData> vClients = LoadClientsDataFromFile(ClientInfoFileName);
    DeleteClientByAccountNumber(AccountNumber, vClients);
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
    string AccountNumber = ReadClientAccountNumber();
    vector <stClientData> vClients = LoadClientsDataFromFile(ClientInfoFileName);
    UpdateClientByAccountNumber(AccountNumber, vClients);

}

enMainMenuOption ReadUserChoice() {
    short UserChoice = 0;
    while (true) {
        cout << "Choose what do you want to do ? [1-7] ? ";
        cin >> UserChoice;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            system("Color 4F");
            cout << "\nInvalid input. Numbers only, please.\n";
            continue;
        }
        if (UserChoice < 1 || UserChoice > 7) {
            system("Color 4F");
            cout << "\nInvalid choice. Please enter a number between 1 and 7.\n";
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
        cout << "\t [7] Exit. \n";
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
    case enMainMenuOption::Exit:
        ExitProgram();
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

    char Answer = 'no';
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

void StartProgram() {
    enMainMenuOption UserChoice;

    do
    {
        ResetScreen();
        ShowMenuScreen();
        UserChoice = ReadUserChoice();
        ResetScreen();
        HandleUserChoice(UserChoice);
    } while (UserChoice != enMainMenuOption::Exit);
}

int main()
{
    StartProgram();
    system("pause>0");
}
