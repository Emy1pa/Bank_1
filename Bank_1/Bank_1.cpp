#include <iostream>
#include <string>
#include <fstream>

using namespace std;

const string ClientInfoFileName = "ClientInfo.txt";

struct stClientData {
    string AccountNumber = "";
    string PinCode = "";
    string ClientName = "";
    string ClientPhone = "";
    int AccountBalance = 0;
};

enum enMainMenuOption {
    ShowClientList = 1,
    AddNewClient = 2,
    DeleteClient = 3,
    UpdateClientInfo = 4,
    FindClient = 5,
    Exit = 6,
};

stClientData ReadNewClient(){
    stClientData ClientInfo;
    cout << "****************************\n";
    cout << "Enter Account Number ? ";
    cin.ignore(1, '\n');
    getline(cin, ClientInfo.AccountNumber);
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

string ConvertRecordToLine(stClientData ClientInfo, string Seperator = "#//#") {
    string stClientRecord = "";
    stClientRecord += ClientInfo.AccountNumber + Seperator;
    stClientRecord += ClientInfo.PinCode + Seperator;
    stClientRecord += ClientInfo.ClientName + Seperator;
    stClientRecord += ClientInfo.ClientPhone + Seperator;
    stClientRecord += to_string(ClientInfo.AccountBalance);
    return stClientRecord;
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

enMainMenuOption ReadUserChoice() {
    short UserChoice = 0;
    while (true) {
        cout << "Choose what do you want to do ? [1-6] ? ";
        cin >> UserChoice;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            system("Color 4F");
            cout << "\nInvalid input. Numbers only, please.\n";
            continue;
        }
        if (UserChoice < 1 || UserChoice > 6) {
            system("Color 4F");
            cout << "\nInvalid choice. Please enter a number between 1 and 6.\n";
            continue;
        }
        break;
    }
    return (enMainMenuOption)UserChoice;
}

void ShowMenuScreen() {    
        cout << "====================================================\n";
        cout << "\t\t Main Menue Screen\n";
        cout << "====================================================\n";
        cout << "\t [1] Show Client List. \n";
        cout << "\t [2] Add New Client. \n";
        cout << "\t [3] Delete Client. \n";
        cout << "\t [4] Update Client Info. \n";
        cout << "\t [5] Find Client. \n";
        cout << "\t [6] Exit. \n";
        cout << "====================================================\n";
}

void ExitProgram() {
    cout << "\n------------------------------------------\n";
    cout << "\t     Program Ends :-) \n";
    cout << "------------------------------------------\n\n";
    system("pause");
}

void HandleUserChoice(enMainMenuOption UserMenuChoice){
    switch (UserMenuChoice)
    {
    case enMainMenuOption::ShowClientList:
        break;
    case enMainMenuOption::AddNewClient:
        AddNewClientHeader();
        AddNewClients();
        break;
    case enMainMenuOption::DeleteClient:
        break;
    case enMainMenuOption::UpdateClientInfo:
        break;
    case enMainMenuOption::FindClient:
        break;
    case enMainMenuOption::Exit:
        ExitProgram();
        break;
    
    }
}

void ResetScreen() {
    system("Color 0F");
    system("cls");
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
