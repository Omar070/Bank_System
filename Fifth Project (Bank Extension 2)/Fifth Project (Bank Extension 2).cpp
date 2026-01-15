#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;
const string ClientsFileName = "Clients.txt";
const string UsersFileName = "Users.txt";

void ShowMainMenue(short Permissions); 
void ShowTransactionsMenue(short Permissions);
void ShowManageUsersMenue(short Permissions);

struct sClient
{
    string AccountNumber;
    string PinCode;
    string Name;
    string Phone;
    double AccountBalance;
    bool MarkForDelete = false;


};

vector<string> SplitString(string S1, string Delim)
{

    vector<string> vString;

    short pos = 0;
    string sWord; // define a string variable  

    // use find() function to get the position of the delimiters  
    while ((pos = S1.find(Delim)) != std::string::npos)
    {
        sWord = S1.substr(0, pos); // store the word   
        if (sWord != "")
        {
            vString.push_back(sWord);
        }

        S1.erase(0, pos + Delim.length());  /* erase() until positon and move to next word. */
    }

    if (S1 != "")
    {
        vString.push_back(S1); // it adds last word of the string.
    }

    return vString;

}

sClient ConvertLinetoRecord(string Line, string Seperator = "#//#")
{

    sClient Client;
    vector<string> vClientData;

    vClientData = SplitString(Line, Seperator);

    Client.AccountNumber = vClientData[0];
    Client.PinCode = vClientData[1];
    Client.Name = vClientData[2];
    Client.Phone = vClientData[3];
    Client.AccountBalance = stod(vClientData[4]);//cast string to double


    return Client;

}

string ConvertRecordToLine(sClient Client, string Seperator = "#//#")
{

    string stClientRecord = "";

    stClientRecord += Client.AccountNumber + Seperator;
    stClientRecord += Client.PinCode + Seperator;
    stClientRecord += Client.Name + Seperator;
    stClientRecord += Client.Phone + Seperator;
    stClientRecord += to_string(Client.AccountBalance);

    return stClientRecord;

}

bool ClientExistsByAccountNumber(string AccountNumber, string FileName)
{

    vector <sClient> vClients;

    fstream MyFile;
    MyFile.open(FileName, ios::in);//read Mode

    if (MyFile.is_open())
    {

        string Line;
        sClient Client;

        while (getline(MyFile, Line))
        {

            Client = ConvertLinetoRecord(Line);
            if (Client.AccountNumber == AccountNumber)
            {
                MyFile.close();
                return true;
            }


            vClients.push_back(Client);
        }

        MyFile.close();

    }

    return false;


}

sClient ReadNewClient()
{
    sClient Client;

    cout << "Enter Account Number? ";

    // Usage of std::ws will extract allthe whitespace character
    getline(cin >> ws, Client.AccountNumber);

    while (ClientExistsByAccountNumber(Client.AccountNumber, ClientsFileName))
    {
        cout << "\nClient with [" << Client.AccountNumber << "] already exists, Enter another Account Number? ";
        getline(cin >> ws, Client.AccountNumber);
    }


    cout << "Enter PinCode? ";
    getline(cin, Client.PinCode);

    cout << "Enter Name? ";
    getline(cin, Client.Name);

    cout << "Enter Phone? ";
    getline(cin, Client.Phone);

    cout << "Enter AccountBalance? ";
    cin >> Client.AccountBalance;

    return Client;

}

vector <sClient> LoadCleintsDataFromFile(string FileName)
{

    vector <sClient> vClients;

    fstream MyFile;
    MyFile.open(FileName, ios::in);//read Mode

    if (MyFile.is_open())
    {

        string Line;
        sClient Client;

        while (getline(MyFile, Line))
        {

            Client = ConvertLinetoRecord(Line);

            vClients.push_back(Client);
        }

        MyFile.close();

    }

    return vClients;

}

void PrintClientRecordLine(sClient Client)
{

    cout << "| " << setw(15) << left << Client.AccountNumber;
    cout << "| " << setw(10) << left << Client.PinCode;
    cout << "| " << setw(40) << left << Client.Name;
    cout << "| " << setw(12) << left << Client.Phone;
    cout << "| " << setw(12) << left << Client.AccountBalance;

}

void PrintClientRecordBalanceLine(sClient Client)
{

    cout << "| " << setw(15) << left << Client.AccountNumber;
    cout << "| " << setw(40) << left << Client.Name;
    cout << "| " << setw(12) << left << Client.AccountBalance;

}

void ShowAllClientsScreen()
{


    vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);

    cout << "\n\t\t\t\t\tClient List (" << vClients.size() << ") Client(s).";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

    cout << "| " << left << setw(15) << "Accout Number";
    cout << "| " << left << setw(10) << "Pin Code";
    cout << "| " << left << setw(40) << "Client Name";
    cout << "| " << left << setw(12) << "Phone";
    cout << "| " << left << setw(12) << "Balance";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

    if (vClients.size() == 0)
        cout << "\t\t\t\tNo Clients Available In the System!";
    else

        for (sClient Client : vClients)
        {

            PrintClientRecordLine(Client);
            cout << endl;
        }

    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

}

void ShowTotalBalances()
{

    vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);

    cout << "\n\t\t\t\t\tBalances List (" << vClients.size() << ") Client(s).";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

    cout << "| " << left << setw(15) << "Accout Number";
    cout << "| " << left << setw(40) << "Client Name";
    cout << "| " << left << setw(12) << "Balance";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

    double TotalBalances = 0;

    if (vClients.size() == 0)
        cout << "\t\t\t\tNo Clients Available In the System!";
    else

        for (sClient Client : vClients)
        {

            PrintClientRecordBalanceLine(Client);
            TotalBalances += Client.AccountBalance;

            cout << endl;
        }

    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
    cout << "\t\t\t\t\t   Total Balances = " << TotalBalances;

}

void PrintClientCard(sClient Client)
{
    cout << "\nThe following are the client details:\n";
    cout << "-----------------------------------";
    cout << "\nAccout Number: " << Client.AccountNumber;
    cout << "\nPin Code     : " << Client.PinCode;
    cout << "\nName         : " << Client.Name;
    cout << "\nPhone        : " << Client.Phone;
    cout << "\nAccount Balance: " << Client.AccountBalance;
    cout << "\n-----------------------------------\n";

}

bool FindClientByAccountNumber(string AccountNumber, vector <sClient> vClients, sClient& Client)
{

    for (sClient C : vClients)
    {

        if (C.AccountNumber == AccountNumber)
        {
            Client = C;
            return true;
        }

    }
    return false;

}

sClient ChangeClientRecord(string AccountNumber)
{
    sClient Client;

    Client.AccountNumber = AccountNumber;

    cout << "\n\nEnter PinCode? ";
    getline(cin >> ws, Client.PinCode);

    cout << "Enter Name? ";
    getline(cin, Client.Name);

    cout << "Enter Phone? ";
    getline(cin, Client.Phone);

    cout << "Enter AccountBalance? ";
    cin >> Client.AccountBalance;

    return Client;

}

bool MarkClientForDeleteByAccountNumber(string AccountNumber, vector <sClient>& vClients)
{

    for (sClient& C : vClients)
    {

        if (C.AccountNumber == AccountNumber)
        {
            C.MarkForDelete = true;
            return true;
        }

    }

    return false;

}

vector <sClient> SaveCleintsDataToFile(string FileName, vector <sClient> vClients)
{

    fstream MyFile;
    MyFile.open(FileName, ios::out);//overwrite

    string DataLine;

    if (MyFile.is_open())
    {

        for (sClient C : vClients)
        {

            if (C.MarkForDelete == false)
            {
                //we only write records that are not marked for delete.  
                DataLine = ConvertRecordToLine(C);
                MyFile << DataLine << endl;

            }

        }

        MyFile.close();

    }

    return vClients;

}

void AddDataLineToFile(string FileName, string  stDataLine)
{
    fstream MyFile;
    MyFile.open(FileName, ios::out | ios::app);

    if (MyFile.is_open())
    {

        MyFile << stDataLine << endl;

        MyFile.close();
    }

}

void AddNewClient()
{
    sClient Client;
    Client = ReadNewClient();
    AddDataLineToFile(ClientsFileName, ConvertRecordToLine(Client));

}

void AddNewClients()
{
    char AddMore = 'Y';
    do
    {
        //system("cls");
        cout << "Adding New Client:\n\n";

        AddNewClient();
        cout << "\nClient Added Successfully, do you want to add more clients? Y/N? ";


        cin >> AddMore;

    } while (toupper(AddMore) == 'Y');

}

bool DeleteClientByAccountNumber(string AccountNumber, vector <sClient>& vClients)
{

    sClient Client;
    char Answer = 'n';

    if (FindClientByAccountNumber(AccountNumber, vClients, Client))
    {

        PrintClientCard(Client);

        cout << "\n\nAre you sure you want delete this client? y/n ? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            MarkClientForDeleteByAccountNumber(AccountNumber, vClients);
            SaveCleintsDataToFile(ClientsFileName, vClients);

            //Refresh Clients 
            vClients = LoadCleintsDataFromFile(ClientsFileName);

            cout << "\n\nClient Deleted Successfully.";
            return true;
        }

    }
    else
    {
        cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!";
        return false;
    }

}

bool UpdateClientByAccountNumber(string AccountNumber, vector <sClient>& vClients)
{

    sClient Client;
    char Answer = 'n';

    if (FindClientByAccountNumber(AccountNumber, vClients, Client))
    {

        PrintClientCard(Client);
        cout << "\n\nAre you sure you want update this client? y/n ? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {

            for (sClient& C : vClients)
            {
                if (C.AccountNumber == AccountNumber)
                {
                    C = ChangeClientRecord(AccountNumber);
                    break;
                }

            }

            SaveCleintsDataToFile(ClientsFileName, vClients);

            cout << "\n\nClient Updated Successfully.";
            return true;
        }

    }
    else
    {
        cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!";
        return false;
    }

}

bool DepositBalanceToClientByAccountNumber(string AccountNumber, double Amount, vector <sClient>& vClients)
{
    char Answer = 'n';

    cout << "\n\nAre you sure you want perfrom this transaction? y/n ? ";
    cin >> Answer;
    if (Answer == 'y' || Answer == 'Y')
    {

        for (sClient& C : vClients)
        {
            if (C.AccountNumber == AccountNumber)
            {
                C.AccountBalance += Amount;
                SaveCleintsDataToFile(ClientsFileName, vClients);
                cout << "\n\nDone Successfully. New balance is: " << C.AccountBalance;

                return true;
            }

        }


        return false;
    }

}

string ReadClientAccountNumber()
{
    string AccountNumber = "";

    cout << "\nPlease enter AccountNumber? ";
    cin >> AccountNumber;
    return AccountNumber;

}

void ShowDeleteClientScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tDelete Client Screen";
    cout << "\n-----------------------------------\n";

    vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
    string AccountNumber = ReadClientAccountNumber();
    DeleteClientByAccountNumber(AccountNumber, vClients);

}

void ShowUpdateClientScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tUpdate Client Info Screen";
    cout << "\n-----------------------------------\n";

    vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
    string AccountNumber = ReadClientAccountNumber();
    UpdateClientByAccountNumber(AccountNumber, vClients);

}

void ShowAddNewClientsScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tAdd New Clients Screen";
    cout << "\n-----------------------------------\n";

    AddNewClients();

}

void ShowFindClientScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tFind Client Screen";
    cout << "\n-----------------------------------\n";

    vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
    sClient Client;
    string AccountNumber = ReadClientAccountNumber();
    if (FindClientByAccountNumber(AccountNumber, vClients, Client))
        PrintClientCard(Client);
    else
        cout << "\nClient with Account Number[" << AccountNumber << "] is not found!";

}

void ShowEndScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tProgram Ends :-)";
    cout << "\n-----------------------------------\n";

}

void ShowDepositScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tDeposit Screen";
    cout << "\n-----------------------------------\n";


    sClient Client;

    vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
    string AccountNumber = ReadClientAccountNumber();


    while (!FindClientByAccountNumber(AccountNumber, vClients, Client))
    {
        cout << "\nClient with [" << AccountNumber << "] does not exist.\n";
        AccountNumber = ReadClientAccountNumber();
    }


    PrintClientCard(Client);

    double Amount = 0;
    cout << "\nPlease enter deposit amount? ";
    cin >> Amount;

    DepositBalanceToClientByAccountNumber(AccountNumber, Amount, vClients);

}

void ShowWithDrawScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tWithdraw Screen";
    cout << "\n-----------------------------------\n";

    sClient Client;

    vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
    string AccountNumber = ReadClientAccountNumber();


    while (!FindClientByAccountNumber(AccountNumber, vClients, Client))
    {
        cout << "\nClient with [" << AccountNumber << "] does not exist.\n";
        AccountNumber = ReadClientAccountNumber();
    }

    PrintClientCard(Client);

    double Amount = 0;
    cout << "\nPlease enter withdraw amount? ";
    cin >> Amount;

    //Validate that the amount does not exceeds the balance
    while (Amount > Client.AccountBalance)
    {
        cout << "\nAmount Exceeds the balance, you can withdraw up to : " << Client.AccountBalance << endl;
        cout << "Please enter another amount? ";
        cin >> Amount;
    }

    DepositBalanceToClientByAccountNumber(AccountNumber, Amount * -1, vClients);

}

void ShowTotalBalancesScreen()
{

    ShowTotalBalances();

}

enum enTransactionsMenueOptions { eDeposit = 1, eWithdraw = 2, eShowTotalBalance = 3, eShowMainMenue = 4 };

enum enMainMenueOptions { eListClients = 1, eAddNewClient = 2, eDeleteClient = 3, eUpdateClient = 4, eFindClient = 5, eShowTransactionsMenue = 6, eShowManageUsersMenue = 7, eLogOut = 8 };

void GoBackToMainMenue(short Permissions)
{
    cout << "\n\nPress any key to go back to Main Menue...";
    system("pause>0");
    ShowMainMenue(Permissions); 

}
void GoBackToTransactionsMenue(short Permissions)
{
    cout << "\n\nPress any key to go back to Transactions Menue...";
    system("pause>0");
    ShowTransactionsMenue(Permissions);

}
short ReadTransactionsMenueOption()
{
    cout << "Choose what do you want to do? [1 to 4]? ";
    short Choice = 0;
    cin >> Choice;

    return Choice;
}

void PerfromTranactionsMenueOption(enTransactionsMenueOptions TransactionMenueOption, short Permissions)
{
    switch (TransactionMenueOption)
    {
    case enTransactionsMenueOptions::eDeposit:
    {
        system("cls");
        ShowDepositScreen();
        GoBackToTransactionsMenue(Permissions);
        break;
    }

    case enTransactionsMenueOptions::eWithdraw:
    {
        system("cls");
        ShowWithDrawScreen();
        GoBackToTransactionsMenue(Permissions);
        break;
    }


    case enTransactionsMenueOptions::eShowTotalBalance:
    {
        system("cls");
        ShowTotalBalancesScreen();
        GoBackToTransactionsMenue(Permissions);
        break;
    }


    case enTransactionsMenueOptions::eShowMainMenue:
    {

        ShowMainMenue(Permissions);  

    }
    }

}

void ShowTransactionsMenue(short Permissions)
{
    system("cls");
    cout << "===========================================\n";
    cout << "\t\tTransactions Menue Screen\n";
    cout << "===========================================\n";
    cout << "\t[1] Deposit.\n";
    cout << "\t[2] Withdraw.\n";
    cout << "\t[3] Total Balances.\n";
    cout << "\t[4] Main Menue.\n";
    cout << "===========================================\n";
    PerfromTranactionsMenueOption((enTransactionsMenueOptions)ReadTransactionsMenueOption(), Permissions); 
}

// New Extension (2)

// Add New Client Functions

struct stUser
{
    string UserName;
    string Password;
    short Permissions;
    bool MarkForDelete = false;
};

stUser ConvertUserLinetoRecord(string Line, string Seperator = "#//#")
{
    stUser User;
    vector<string> vClientData;

    vClientData = SplitString(Line, Seperator);

    User.UserName = vClientData[0];
    User.Password = vClientData[1];
    User.Permissions = stod(vClientData[2]);

    return User;
}

bool UserExistByUserName(string UserName, string FileName)
{
    vector <stUser> vUsers;

    fstream MyFile;
    MyFile.open(FileName, ios::in);//read Mode

    if (MyFile.is_open())
    {

        string Line;
        stUser User;

        while (getline(MyFile, Line))
        {

            User = ConvertUserLinetoRecord(Line);
            if (User.UserName == UserName)
            {
                MyFile.close();
                return true;
            }


            vUsers.push_back(User);
        }

        MyFile.close();

    }

    return false;


}

string ConvertUserRecordToLine(stUser User, string Seperator = "#//#")
{
    string stClientRecord = "";

    stClientRecord += User.UserName + Seperator;
    stClientRecord += User.Password + Seperator;
    stClientRecord += to_string(User.Permissions);

    return stClientRecord;
}

stUser ReadNewUser()
{
    stUser User;
    char Answer = 'y';

    cout << "Enter User Name? ";
    getline(cin >> ws, User.UserName);

    while (UserExistByUserName(User.UserName, UsersFileName))
    {
        cout << "\nUser with [" << User.UserName << " ] already exists, Enter another UserName? ";
        getline(cin >> ws, User.UserName);
    }

    cout << "Enter Password? ";
    getline(cin, User.Password);

    cout << "\nDo You Want User To Have Full Access? ";
    cin >> Answer;

    if (toupper(Answer) == 'Y')
    {
        User.Permissions = -1;
    }

    else
    {
        User.Permissions = 0;

        cout << "\nDo You Want User To Have Access On Show Clients List Screen? ";
        cin >> Answer;
        if (toupper(Answer) == 'Y')
        {
            User.Permissions += 1;
        }

        cout << "\nDo You Want User To Have Access On Add New Client Screen ? ";
        cin >> Answer;
        if (toupper(Answer) == 'Y')
        {
            User.Permissions += 2;
        }

        cout << "\nDo You Want User To Have Access On Delete Client Screen ? ";
        cin >> Answer;
        if (toupper(Answer) == 'Y')
        {
            User.Permissions += 4;
        }

        cout << "\nDo You Want User To Have Access On Update Client Screen ? ";
        cin >> Answer;
        if (toupper(Answer) == 'Y')
        {
            User.Permissions += 8;
        }

        cout << "\nDo You Want User To Have Access On Find Client Screen ? ";
        cin >> Answer;
        if (toupper(Answer) == 'Y')
        {
            User.Permissions += 16;
        }

        cout << "\nDo You Want User To Have Access On Transactions Screen ? ";
        cin >> Answer;
        if (toupper(Answer) == 'Y')
        {
            User.Permissions += 32;
        }

        cout << "\nDo You Want User To Have Access On Manage Users Screen ? ";
        cin >> Answer;
        if (toupper(Answer) == 'Y')
        {
            User.Permissions += 64;
        }

    }

    return User;
}

void AddNewUser()
{
    stUser User;
    User = ReadNewUser();
    AddDataLineToFile(UsersFileName, ConvertUserRecordToLine(User));

}

void AddNewUsers()
{
    char AddMore = 'Y';
    do
    {
        //system("cls");
        cout << "Adding New User:\n\n";

        AddNewUser();
        cout << "\nUser Added Successfully, do you want to add more Users? Y/N? ";

        cin >> AddMore;

    } while (toupper(AddMore) == 'Y');

}

void ShowAddNewUsersScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tAdd New Users Screen";
    cout << "\n-----------------------------------\n";

    AddNewUsers();

}

// Delete User functions


void PrintUserCard(stUser User)
{
    cout << "\nThe following are the Users details:\n";
    cout << "-----------------------------------";
    cout << "\nUser Name   : " << User.UserName;
    cout << "\nPassword    : " << User.Password;
    cout << "\nPermissions : " << User.Permissions;
    cout << "\n-----------------------------------\n";
}

vector <stUser> LoadUsersDataFromFile(string FileName)
{
    vector <stUser> vUsers;

    fstream MyFile;
    MyFile.open(FileName, ios::in);//read Mode

    if (MyFile.is_open())
    {

        string Line;
        stUser User;

        while (getline(MyFile, Line))
        {

            User = ConvertUserLinetoRecord(Line);

            vUsers.push_back(User);
        }

        MyFile.close();

    }

    return vUsers;
}

bool FindUserByUserName(string UserName, vector <stUser> vUsers, stUser& User)
{

    for (stUser U : vUsers)
    {

        if (U.UserName == UserName)
        {
            User = U;
            return true;
        }

    }
    return false;

}

bool MarkUserForDeleteByUserName(string UserName, vector <stUser>& vUsers)
{
    for (stUser& U : vUsers)
    {
        if (U.UserName == UserName)
        {
            U.MarkForDelete = true;
            return true;
        }
    }
    return false;
}

vector <stUser> SaveUsersDataToFile(string FileName, vector <stUser> vUsers)
{
    fstream MyFile;
    MyFile.open(FileName, ios::out);//overwrite

    string DataLine;

    if (MyFile.is_open())
    {
        for (stUser U : vUsers)
        {
            if (U.MarkForDelete == false)
            {
                //we only write records that are not marked for delete.  
                DataLine = ConvertUserRecordToLine(U);
                MyFile << DataLine << endl;
            }
        }
        MyFile.close();
    }
    return vUsers;
}

bool DeleteUserByUserName(string UserName, vector <stUser>& vUsers)
{

    stUser User;
    char Answer = 'n';

    if (FindUserByUserName(UserName, vUsers, User))
    {

        PrintUserCard(User);

        cout << "\n\nAre you sure you want delete this User? y/n ? ";
        cin >> Answer;

        if (Answer == 'y' || Answer == 'Y')
        {
            if (User.UserName == "Admin" && User.Password == "1234")
            {
                cout << "\nThis User Can't be Deleted";
                return true;
            }

            MarkUserForDeleteByUserName(UserName, vUsers);
            SaveUsersDataToFile(UsersFileName, vUsers);

            //Refresh Clients 
            vUsers = LoadUsersDataFromFile(UsersFileName);

            cout << "\n\nUser Deleted Successfully.";

            return true;
        }

    }

    else
    {
        cout << "\nUser with User Name (" << UserName << ") is Not Found!";
        return false;
    }

}

string ReadUserName()
{
    string UserName = "";

    cout << "\nPlease enter User Name? ";
    getline(cin >> ws, UserName);
    return UserName;

}

void ShowDeleteUserScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tDelete User Screen";
    cout << "\n-----------------------------------\n";

    vector <stUser> vUsers = LoadUsersDataFromFile(UsersFileName);
    string UserName = ReadUserName();
    DeleteUserByUserName(UserName, vUsers);

}

// Update User Functios

stUser ChangeUserRecord(string UserName)
{
    stUser User;
    char Answer = 'y';

    User.UserName = UserName;

    cout << "\n\nEnter Password? ";
    getline(cin >> ws, User.Password);

    cout << "\nDo You Want User To Have Full Access? ";
    cin >> Answer;

    if (toupper(Answer) == 'Y')
    {
        User.Permissions = -1;
    }

    else
    {
        User.Permissions = 0;

        cout << "\nDo You Want User To Have Access On Show Clients List Screen? ";
        cin >> Answer;
        if (toupper(Answer) == 'Y')
        {
            User.Permissions += 1;
        }

        cout << "\nDo You Want User To Have Access On Add New Client Screen ? ";
        cin >> Answer;
        if (toupper(Answer) == 'Y')
        {
            User.Permissions += 2;
        }

        cout << "\nDo You Want User To Have Access On Delete Client Screen ? ";
        cin >> Answer;
        if (toupper(Answer) == 'Y')
        {
            User.Permissions += 4;
        }

        cout << "\nDo You Want User To Have Access On Update Client Screen ? ";
        cin >> Answer;
        if (toupper(Answer) == 'Y')
        {
            User.Permissions += 8;
        }

        cout << "\nDo You Want User To Have Access On Find Client Screen ? ";
        cin >> Answer;
        if (toupper(Answer) == 'Y')
        {
            User.Permissions += 16;
        }

        cout << "\nDo You Want User To Have Access On Transactions Screen ? ";
        cin >> Answer;
        if (toupper(Answer) == 'Y')
        {
            User.Permissions += 32;
        }

        cout << "\nDo You Want User To Have Access On Manage Users Screen ? ";
        cin >> Answer;
        if (toupper(Answer) == 'Y')
        {
            User.Permissions += 64;
        }
    }
    return User;
}

bool UpdateUserByUserName(string UserName, vector <stUser>& vUsers)
{

    stUser User;
    char Answer = 'n';

    if (FindUserByUserName(UserName, vUsers, User))
    {

        PrintUserCard(User);

        cout << "\n\nAre you sure you want update this User? y/n ? ";
        cin >> Answer;

        if (Answer == 'y' || Answer == 'Y')
        {
            for (stUser& U : vUsers)
            {
                if (U.UserName == UserName)
                {
                    U = ChangeUserRecord(UserName);
                    break;
                }

            }

            SaveUsersDataToFile(UsersFileName, vUsers);

            cout << "\n\nClient Updated Successfully.";
            return true;
        }
    }

    else
    {
        cout << "\nClient with User Name (" << UserName << ") is Not Found!";
        return false;
    }

}

void ShowUpdateUserScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tUpdate User Info Screen";
    cout << "\n-----------------------------------\n";

    vector <stUser> vUsers = LoadUsersDataFromFile(UsersFileName);
    string UserName = ReadUserName();
    UpdateUserByUserName(UserName, vUsers);

}

// fnd User

void ShowFindUserScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tFind User Screen";
    cout << "\n-----------------------------------\n";

    vector <stUser> vUsers = LoadUsersDataFromFile(UsersFileName);
    stUser User;
    string UserName = ReadUserName();
    if (FindUserByUserName(UserName, vUsers, User))
        PrintUserCard(User);
    else
        cout << "\nClient with User Name [" << UserName << "] is not found!";
}

// Users List Functions

void PrintUserRecordLine(stUser User)
{

    cout << "| " << setw(20) << left << User.UserName;
    cout << "| " << setw(15) << left << User.Password;
    cout << "| " << setw(15) << left << User.Permissions;

}

void ShowAllUsersScreen()
{
    vector <stUser> vUsers = LoadUsersDataFromFile(UsersFileName);

    cout << "\n\t\t\t\t\tUsers List (" << vUsers.size() << ") User(s).";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

    cout << "| " << left << setw(20) << "User Name";
    cout << "| " << left << setw(15) << "Password";
    cout << "| " << left << setw(15) << "Permissions";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

    if (vUsers.size() == 0)
        cout << "\t\t\t\tNo Clients Available In the System!";

    else

        for (stUser User : vUsers)
        {

            PrintUserRecordLine(User);
            cout << endl;
        }

    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

}


// Main Switch

enum enManageUsersMenue { eListUsers = 1, eAddNewUser = 2, eDeleteUsser = 3, eUpdateUser = 4, eFindUser = 5, eMainMenue = 6 };

void GoBackToManageUsersMenue(short Permissions)
{
    cout << "\n\nPress any key to go back to Manage Users Menue...";
    system("pause>0");
    ShowManageUsersMenue(Permissions); 

}

short ReadManageUsersOptions()
{
    cout << "Choose what do you want to do? [1 to 6]? ";
    short Choice = 0;
    cin >> Choice;

    return Choice;
}

void PerfromManageUsersMenueOption(enManageUsersMenue ManageUsers, short Permissions)
{
    switch (ManageUsers)
    {
    case enManageUsersMenue::eListUsers:
    {
        system("cls");
        ShowAllUsersScreen();
        GoBackToManageUsersMenue(Permissions);
        break;
    }

    case enManageUsersMenue::eAddNewUser:
    {
        system("cls");
        ShowAddNewUsersScreen();
        GoBackToManageUsersMenue(Permissions);
        break;
    }


    case enManageUsersMenue::eDeleteUsser:
    {
        system("cls");
        ShowDeleteUserScreen();
        GoBackToManageUsersMenue(Permissions);
        break;
    }


    case enManageUsersMenue::eUpdateUser:

        system("cls");
        ShowUpdateUserScreen();
        GoBackToManageUsersMenue(Permissions);
        break;


    case enManageUsersMenue::eFindUser:

        system("cls");
        ShowFindUserScreen();
        GoBackToManageUsersMenue(Permissions);
        break;

    case enManageUsersMenue::eMainMenue:

        ShowMainMenue(Permissions); 
    }

}

void ShowManageUsersMenue(short Permissions)
{
    system("cls");
    cout << "===========================================\n";
    cout << "\t\tManage Users Menue Screen\n";
    cout << "===========================================\n";
    cout << "\t[1] List Users.\n";
    cout << "\t[2] Add New User.\n";
    cout << "\t[3] Delet User.\n";
    cout << "\t[4] Update User.\n";
    cout << "\t[5] Find User.\n";
    cout << "\t[6] Main Menue.\n";

    cout << "===========================================\n";
    PerfromManageUsersMenueOption((enManageUsersMenue)ReadManageUsersOptions(), Permissions);
}

// End Of Extension

bool HasPermission(short THePermissions, short NumberOfPermission)
{
    short Permissions = THePermissions;

    if (Permissions == -1 || Permissions == 127)
    {
        return true;
    }

    if (Permissions >= 64)
    {
        Permissions -= 64;
        if (NumberOfPermission == 64) { return true; }
    }

    if (Permissions >= 32)
    {
        Permissions -= 32;
        if (NumberOfPermission == 32) { return true; }
    }

    if (Permissions >= 16)
    {
        Permissions -= 16;
        if (NumberOfPermission == 16) { return true; }
    }

    if (Permissions >= 8)
    {
        Permissions -= 8;
        if (NumberOfPermission == 8) { return true; }
    }

    if (Permissions >= 4)
    {
        Permissions -= 4;
        if (NumberOfPermission == 4) { return true; }
    }

    if (Permissions >= 2)
    {
        Permissions -= 2;
        if (NumberOfPermission == 2) { return true; }
    }

    if (Permissions >= 1)
    {
        Permissions -= 1;
        if (NumberOfPermission == 1) { return true; }
    }

    return false;

}

void ShowPermissionStatus()
{
    system("cls");
    cout << "\n_____________________________\n";
    cout << "Access Denied\n";
    cout << "You Dont Have Permission To Do This\n";
    cout << "Please Contact Your Admin\n";
    cout << "\n_____________________________\n";
}

void ShowLogInScreen();   

short ReadMainMenueOption()
{
    cout << "Choose what do you want to do? [1 to 8]? ";
    short Choice = 0;
    cin >> Choice;

    return Choice;
}

void PerfromMainMenueOption(enMainMenueOptions MainMenueOption, short Permissions)
{

    switch (MainMenueOption)
    {
    case enMainMenueOptions::eListClients:
    {
        if (HasPermission(Permissions, 1))
        {
            system("cls");
            ShowAllClientsScreen();
        }
        else 
        {
            ShowPermissionStatus();
        }

        GoBackToMainMenue(Permissions);
        break;
    }
    case enMainMenueOptions::eAddNewClient:
        
        if (HasPermission(Permissions, 2))
        {
            system("cls");
            ShowAddNewClientsScreen();
        }
        else
        {
            ShowPermissionStatus();
        }
        GoBackToMainMenue(Permissions);
        break;

    case enMainMenueOptions::eDeleteClient:
        if (HasPermission(Permissions, 4))
        {
            system("cls");
            ShowDeleteClientScreen();
        }
        else
        {
            ShowPermissionStatus();
        }
        GoBackToMainMenue(Permissions);
        break;

    case enMainMenueOptions::eUpdateClient:
        if (HasPermission(Permissions, 8))
        {
            system("cls");
            ShowUpdateClientScreen();
        }
        else
        {
            ShowPermissionStatus();
        }
        GoBackToMainMenue(Permissions);
        break;

    case enMainMenueOptions::eFindClient:
        if (HasPermission(Permissions, 16))
        {
            system("cls");
            ShowFindClientScreen();
        }
        else
        {
            ShowPermissionStatus();
        }

        GoBackToMainMenue(Permissions);
        break;

    case enMainMenueOptions::eShowTransactionsMenue:
        if (HasPermission(Permissions, 32))
        {
            system("cls");
            ShowTransactionsMenue(Permissions);
        }
        else
        {
            ShowPermissionStatus(); 
            GoBackToMainMenue(Permissions);
        }

        break;

    case enMainMenueOptions::eShowManageUsersMenue:
        if (HasPermission(Permissions, 64))
        {
            system("cls");
            ShowManageUsersMenue(Permissions);
        }
        else 
        {
            ShowPermissionStatus();     
            GoBackToMainMenue(Permissions);
        }
        break;

    case enMainMenueOptions::eLogOut:
        system("cls");
        ShowLogInScreen();
        break;
    }

}

string ReadPassWord()
{
    string UserName = "";

    cout << "\nPlease enter Password? ";
    getline(cin >> ws, UserName);
    return UserName;

}

bool FindUserByUserNameAndPassword(string UserName, string Password, vector <stUser> vUsers, stUser& User)
{

    for (stUser U : vUsers)
    {

        if (U.UserName == UserName && U.Password == Password)
        {
            User = U;
            return true;
        }

    }
    return false;

}


// End

void ShowMainMenue(short Permissions = 0)
{
    system("cls");
    cout << "===========================================\n";
    cout << "\t\tMain Menue Screen\n";
    cout << "===========================================\n";
    cout << "\t[1] Show Client List.\n";
    cout << "\t[2] Add New Client.\n";
    cout << "\t[3] Delete Client.\n";
    cout << "\t[4] Update Client Info.\n";
    cout << "\t[5] Find Client.\n";
    cout << "\t[6] Transactions.\n";
    cout << "\t[7] Manage Users.\n";
    cout << "\t[8] Log Out.\n";
    cout << "===========================================\n";
    PerfromMainMenueOption((enMainMenueOptions)ReadMainMenueOption(), Permissions); 
}
 
void ShowLogInScreen()  
{ 
    cout << "\n________________________________\n";
    cout << "\tLog In Screen";
    cout << "\n________________________________\n";

    vector <stUser> vUsers = LoadUsersDataFromFile(UsersFileName); 
    string UserName = ReadUserName();
    string Password = ReadPassWord();
    stUser User;

    while (!FindUserByUserNameAndPassword(UserName, Password, vUsers, User))
    {
        cout << "\nInvalid UserName/password\n";
        UserName = ReadUserName();
        Password = ReadPassWord();
    }

        ShowMainMenue(User.Permissions); 
}

int main()

{
    ShowLogInScreen(); 
    system("pause>0");
    return 0;
}

