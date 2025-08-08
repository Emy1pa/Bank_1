#include <iostream>
using namespace std;

enum enMainMenuOption {
    ShowClientList = 1,
    AddNewClient = 2, 
    DeleteClient = 3,
    UpdateClientInfo = 4,
    FindClient = 5,
    Exit = 6,
};

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
    ShowMenuScreen();
    enMainMenuOption UserChoice;

    UserChoice = ReadUserChoice();
    ResetScreen();
    HandleUserChoice(UserChoice);
}


int main()
{
    StartProgram();
    system("pause>0");
}
