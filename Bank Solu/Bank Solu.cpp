#include <iostream>
#include<fstream>
#include<string>
#include<iomanip>
#include<vector>
using namespace std;
const string path = "MyClients.txt";
const string Userpath = "Users.txt";

struct stUser
{
	string Username;
	string Password;
	short Permissions;
	bool MarkforDelete = false;
};
struct PersonData
{
	string Account_Number, Pin_code, Name, PhoneNumber;
	double Account_Balance;
	bool Mark = false;
};
stUser LoginUser;
enum enTransaction
{
	eDeposit=1,eWithdraw=2,eTotal_Balance=3,eMain_Menu=4
};
enum enMenuChoice {
	eShow = 1, eAdd = 2, eDelete = 3, eUpdate = 4, eFind = 5, eTransaction = 6,eMangeUsers=7,eLogout=8
};
enum MainMenuPeromssions
{
	enAll = -1, eShowClinets = 1, eAddClients = 2,eDeleteClients=4, eUpdateClients=8, eFindClient=16, eTransactionScreen=32, eMangeUsersScreen=64
};
enum enMangeUsers
{
	eShowUsers=1, eAddUser = 2, eDeleteUser = 3, eUpdateUser = 4, eFindUser = 5, eMainMenu=6
};
enMenuChoice ReadChoice();
enTransaction ReadTransaction();

string  fromrecordtoline(PersonData Client, string Dil = "#//#");
PersonData fromlinetorecord(string line);
vector<string> split(string line, string dil = "#//#");
vector<PersonData> from_file_to_Vpersons();
bool isthere(string acc_number);
PersonData ReadPerson(bool edit=false);
void PrintClient(PersonData Client);
void PrintBar();
void Showclients();
void BacktoMainMenu();
void AddClients();
void Addclient();
bool isexist(string Acc_Number, PersonData& Client);
void Markfordelete(vector< PersonData>& myClients, string Acc_Number);
void from_Vpersons_to_file(vector<PersonData> myvec);
void ChangeinVpersons(vector<PersonData>& myClients, PersonData New);
void Update();
void UpdateAcc(string Acc);
void FindByAccNum(string acc);
void Find();
void Delete();
void DeleteAcc(string Acc);
void end();
void Main_Menu();
void Transaction_Bar();
void Deposit(double Value, PersonData Client, string Perform="Deposit");
void Deposit_Menu();
void Withdraw_Menu();
void BackTransactionMenu();
void Total_Balance_Menu();
vector<PersonData> Transactions_Clients();
double TotalBalance(vector<PersonData> Clients);
void TransactionMenu();
void PerformTransaction(enTransaction T_Choice);
void Bank();
void Login();
void isEligible(MainMenuPeromssions Permission);
enMangeUsers ReadMangeUsersChoice();
void ShowUsers();
void MangeUsers();
void AddUsers();
void DeleteUser();
void UpdateUser();
void FindUser();
int main()
{
	Login();

}


string  fromrecordtoline(PersonData Client, string Dil) {
	string line = "";
	line += Client.Account_Number + Dil;
	line += Client.Pin_code + Dil;
	line += Client.Name + Dil;
	line += Client.PhoneNumber + Dil;
	line += to_string(Client.Account_Balance);
	return line;
}
PersonData fromlinetorecord(string line) {
	vector<string> tmp = split(line);
	PersonData Client;

	Client.Account_Number = tmp[0];
	Client.Pin_code = tmp[1];
	Client.Name = tmp[2];
	Client.PhoneNumber = tmp[3];
	Client.Account_Balance = stod(tmp[4]);
	return Client;
}
vector<string> split(string line, string dil) {
	vector<string> myvec;
	int pos;
	while ((pos = line.find(dil)) != line.npos) {
		string tmp = line.substr(0, pos);
		if (tmp != "")
			myvec.push_back(tmp);
		line.erase(0, pos + dil.length());
	}
	if (line != "")
		myvec.push_back(line);
	return myvec;
}
vector<PersonData> from_file_to_Vpersons() {
	vector<PersonData> Vpersons;
	string line;
	fstream myfile;
	myfile.open(path, ios::in);
	while (getline(myfile, line))
	{
		Vpersons.push_back(fromlinetorecord(line));
	}
	return Vpersons;
}
PersonData ReadPerson(bool edit) {
	PersonData client;
	if (!edit) {
		cout << "\nPlease enter The account Number : ";
		getline(cin >> ws, client.Account_Number);
		while ((isthere(client.Account_Number))) {
			cout << "\n    (" << client.Account_Number << ")    Already Exists !! \nPlease enter The account Number :  ";
			getline(cin, client.Account_Number);
		}
	}
	cout << "\nPlease enter The account Pindcode : ";
	getline(cin >> ws, client.Pin_code);
	cout << "\nPlease enter The account Name : ";
	getline(cin, client.Name);
	cout << "\nPlease enter The account Phone Number : ";
	getline(cin, client.PhoneNumber);
	cout << "\nPlease enter The account Balance : ";
	cin >> client.Account_Balance;
	return client;




}
bool isthere(string acc_number) {
fstream	myfile;
myfile.open(path, ios::in);
if (myfile.is_open()) {
	vector<PersonData> Clients = from_file_to_Vpersons();
	for (PersonData tmp : Clients) {
		if (tmp.Account_Number == acc_number) {
			myfile.close();
			return true;
		}
	}
	return false;

}



}
void PrintClient(PersonData Client) {
	cout << "\n ----------------------------";
	cout << "\n Account Number : ";
	cout << Client.Account_Number;
	cout << "\n Account PinCode : ";
	cout << Client.Pin_code;
	cout << "\n Account Name : ";
	cout << Client.Name;
	cout << "\n Account Phone Number : ";
	cout << Client.PhoneNumber;
	cout << "\n Account Balance : ";
	cout << Client.Account_Balance;
	cout << "\n ----------------------------";

}
void Main_Menu() {
	system("cls");
	cout << "========================================";
	cout << endl << "========================================" << endl;
	printf("%32s", "[1] Show Client List\n");
		printf("%30s", "[2] Add New Client\n");
		printf("%29s", "[3] Delete Client\n");
		printf("%29s", "[4] Update Client\n");
		printf("%27s", "[5] Find Client\n");
		printf("%27s", "[6] Transaction\n");
		printf("%28s", "[7] Manage Users\n");
		printf("%22s", "[7] Logout\n");
	cout << "========================================" << endl;

}
enMenuChoice ReadChoice() {
	cout << "Choose What do you want 1-->8 ? : ";
	int Number;
	cin >> Number;
	return enMenuChoice(Number);

}

void PerformBychoice(enMenuChoice choice) {
	system("cls");
	switch (choice)
	{
	case eShow:
		isEligible(MainMenuPeromssions::eAddClients);
		Showclients();
		BacktoMainMenu();
		break;
	case eAdd:
		isEligible(MainMenuPeromssions::eShowClinets);
		AddClients();
		BacktoMainMenu();

		break;
	case eDelete:
		isEligible(MainMenuPeromssions::eDeleteClients);
		Delete();
		BacktoMainMenu();
		break;
	case eUpdate:
		isEligible(MainMenuPeromssions::eUpdateClients);
		Update();
		BacktoMainMenu();
		break;
	case eFind:
		isEligible(MainMenuPeromssions::eFindClient);
		Find();
		BacktoMainMenu();

		break;
	case eTransaction:
		isEligible(MainMenuPeromssions::eTransactionScreen);
		TransactionMenu();

		break;
	case eMangeUsers:
		isEligible(MainMenuPeromssions::eMangeUsersScreen);
		MangeUsers();

		break;
	case eLogout:
		Login();
		break;
	default:
		Bank();
		break;
	}
}
void Showclients() {

	vector<PersonData> vClient = from_file_to_Vpersons();
	cout << "\n\n                                   Client List (" << vClient.size() << ") Client(s)\n";

	PrintBar();

	for (PersonData& tmp : vClient) {
		if (tmp.Account_Number.length() > 0) {
			cout << endl << left << setw(19) << "|" + tmp.Account_Number;
			cout << left << setw(18) << "|" + tmp.Pin_code;
			cout << left << setw(30) << "|" + tmp.Name;
			cout << left << setw(19) << "|" + tmp.PhoneNumber;
			cout << left << setw(13) << "|" + to_string(tmp.Account_Balance) << "|";
		}
	}

	cout << "\n====================================================================================================";


}
void PrintBar() {
	cout << "====================================================================================================";
	cout << "\n|  Account Number  " << "|     Pin Code    " << "|      Clinet  Name           " << "|    Phone Number  " << "|    Balance |";
	cout << "\n====================================================================================================";


}
void BacktoMainMenu() {
	cout << "\n\n    Press any key to go back !! ";
	system("pause>0");
	Bank();

}
void  AddClients() {
	cout << "-------------------------------";
	cout << "\n\t Add new Clients\n";
	cout << "-------------------------------\n";
	char answer;

	
	do
	{
		Addclient();

		cout << "\nDo you want to add new Clients : ";
		cin >> answer;
	} while (tolower(answer)=='y');


}
void Addclient() {
	PersonData Client = ReadPerson();
	fstream myfile;
	myfile.open(path, ios::app | ios::out);
	if (myfile.is_open()) {
		myfile << fromrecordtoline(Client)<<endl;
		myfile.close();


	}


}
void Delete() {
	cout << "-------------------------------";
	cout << "\n\t Delete Client Screen\n";
	cout << "-------------------------------\n";
	cout << "Please enter Client You want to delete : ";
	string Acc;
	getline(cin>>ws, Acc);
	DeleteAcc(Acc);
}
void DeleteAcc(string Acc) {
	PersonData Client;
	if (isexist(Acc, Client)) {
		cout << "\n";
		PrintClient(Client);
		cout << "\n do you want to delete the client Y/ N : ";
		char answer;
		cin >> answer;
		if (tolower(answer) == 'y') {
			vector<PersonData> Clients = from_file_to_Vpersons();
			Markfordelete(Clients, Acc);
			from_Vpersons_to_file(Clients);
			cout << "   [" << Acc << "] Deleted Succusfuly";
		}


	}
	else {
		cout << Acc << " Doesn't Exist !!";
	}

}
bool isexist(string Acc_Number, PersonData& Client) {
	vector<PersonData> Vclients = from_file_to_Vpersons();
	for (PersonData& tmp : Vclients) {
		if (tmp.Account_Number == Acc_Number) {
			Client = tmp;
			return true;
		}

	}
	return false;
}
void Markfordelete(vector< PersonData>& myClients, string Acc_Number) {
	for (PersonData& client : myClients) {
		if (client.Account_Number == Acc_Number) {
			client.Mark = true;
			return;
		}


	}

}
void from_Vpersons_to_file(vector<PersonData> myvec) {
	fstream myfile;
	myfile.open(path, ios::out);
	if (myfile.is_open()) {
		for (PersonData& client : myvec) {
			if (!client.Mark && client.Account_Number.length() > 0)
				myfile << fromrecordtoline(client) << endl;
		}

		myfile.close();
	}
}
void Update() {
	cout << "-------------------------------";
	cout << "\n\t Delete Client Screen\n";
	cout << "-------------------------------\n";
	cout << "Please enter Client You want to delete : ";
	string Acc;
	getline(cin >> ws, Acc);
	UpdateAcc(Acc);

}
void UpdateAcc(string Acc) {

	PersonData Client;
	if (isexist(Acc, Client)) {
		cout << "\n";
		PrintClient(Client);
		cout << "\n do you want to update the client Y/N : ";
		char answer;
		cin >> answer;
		if (tolower(answer) == 'y') {
			
			Client = ReadPerson(true);
			Client.Account_Number = Acc;
			vector<PersonData> Clients = from_file_to_Vpersons();
			ChangeinVpersons(Clients, Client);
			from_Vpersons_to_file(Clients);
			cout << "   [" << Acc << "]  Updated Succusfuly";
		}


	}
	else {
		cout << Acc << " Doesn't Exist !!";
	}



}
void ChangeinVpersons(vector<PersonData>& myClients ,PersonData New) {
	for (PersonData& tmp : myClients) {
		if (tmp.Account_Number == New.Account_Number) {
			tmp = New;
			return;
		}

	}



}
void FindByAccNum(string acc) {


	PersonData Clinet;
	if (isexist(acc, Clinet)) {
		cout << endl;
		PrintClient(Clinet);
	}
	else {

		cout <<"  [" << acc << "] Doesn't Exist !!";
	}

}
void Find() {
	cout << "-------------------------------";
	cout << "\n\t Delete Client Screen\n";
	cout << "-------------------------------\n";
	cout << "Please enter Client You want to find : ";
	string Acc;
	getline(cin >> ws, Acc);
	FindByAccNum(Acc);

}
void Bank() {
	Main_Menu();
	PerformBychoice(ReadChoice());

}
void end() {
	cout << "-------------------------------";
	cout << "\n\t End Screen :)\n";
	cout << "-------------------------------\n";
}
void TransactionMenu() {
	cout << "----------------------------------------";
	cout << "\n      Transaction Menu screen" << endl;
	cout << "----------------------------------------\n";
	cout << "     [1] Desposit" << endl;
	cout << "     [2] Withdraw" << endl;
	cout << "     [3] Total Balanced" << endl;
	cout << "     [4] Main Menu" << endl;
	cout << "----------------------------------------";
	PerformTransaction(ReadTransaction());


}
void Transaction_Bar() {
	cout << "====================================================================================================";
	cout << "\n|  Account Number       " << " | Clinet  Name                             " << "| Balance                      | ";
	cout << "\n====================================================================================================\n";


}
enTransaction ReadTransaction() {
	cout << "\n Enter Number 1---->4 : ";
	int Number;
	cin >> Number;
	return enTransaction(Number);
}
void PerformTransaction(enTransaction T_Choice) {
	system("cls");
	switch (T_Choice)
	{
	case eDeposit:
		Deposit_Menu();
		BackTransactionMenu();
		break;
	case eWithdraw:
		Withdraw_Menu();
		BackTransactionMenu();
		break;
	case eTotal_Balance:
		Total_Balance_Menu();
		BackTransactionMenu();

		break;
	case eMain_Menu:
		Bank();
		break;
	default:
		break;
	}
}
void Deposit_Menu() {
	cout << "----------------------------------------";
	cout << "\n      Deposit Menu screen" << endl;
	cout << "----------------------------------------\n";
	cout << "Enter Account Number You want to Deposit in : ";
	string Acc;
	getline(cin >> ws, Acc);
	PersonData	Client;
	while (!isexist(Acc, Client)) {
		cout << "\n [" << Acc << "] Doesn't Exist !! \n  Pleas enter another account : ";
		getline(cin, Acc);
	}
	PrintClient(Client);
	cout << "\n Please enter amount of Deposit : ";
	double Amount;
	cin >> Amount;
	Deposit(Amount, Client);

}
void Deposit(double Value, PersonData Client,string Perform) {
	cout << "Do you want to [" << Perform << "] This Amount Y/N : ";
	char answer;
	cin >> answer;
	if (tolower(answer) == 'y') {
		Client.Account_Balance += Value;
		vector<PersonData> myClients = from_file_to_Vpersons();
		ChangeinVpersons(myClients, Client);
		from_Vpersons_to_file(myClients);
		cout << endl << " [" << Perform << " ] Done Successfully :) \n New Balance is   : "<<Client.Account_Balance;
	}
	else {
		cout << endl << " [" << Perform << " ]  Not Done  :( ";

	}
}
void Withdraw_Menu() {
	cout << "----------------------------------------";
	cout << "\n      Withdraw_Menu Menu screen" << endl;
	cout << "----------------------------------------\n";
	cout << "Enter Account Number You want to Withdraw from : ";
	string Acc;
	getline(cin >> ws, Acc);
	PersonData	Client;
	while (!isexist(Acc, Client)) {
		cout << "\n [" << Acc << "] Doesn't Exist !! \n  Pleas enter another account : ";
		getline(cin, Acc);
	}
	cout << "\n Please enter amount of Withdraw : ";
	double Amount;
	cin >> Amount;
	while (Amount>Client.Account_Balance)
	{
		cout << "Amount Exceeds The Balance, you are allowed to withdraw up to " << Client.Account_Balance;
		cout << endl << "Please enter another amount of Withdraw : ";
		cin >> Amount;
	}

	Deposit(Amount*( - 1), Client,"Withdraw");

}
void BackTransactionMenu() {
	cout << "\n\n    Press any key to go back !! ";
	system("pause>0");
	system("cls");
	TransactionMenu();

}
void Total_Balance_Menu(){
	vector<PersonData> Clients = Transactions_Clients();
	if (Clients.size() == 0) {
		cout << right << setw(50) << "The is no Clients !";
	}
	else {
		cout << right << setw(50) << "Total Balance : ";
		cout << TotalBalance(Clients);
	}




}
vector<PersonData> Transactions_Clients() {
	vector<PersonData> Clients = from_file_to_Vpersons();
	cout << "\n\n\t\t\t\t\t " << "List of (" << Clients.size() << " )Client(s)\n";
	Transaction_Bar();
	for (PersonData Client : Clients) {
		cout << left << setw(25) << "|" + Client.Account_Number;
		cout << left << setw(44) << "|" + Client.Name;
		cout << left << setw(30) << "|" + to_string(Client.Account_Balance);
		cout << "|";
		cout << endl;

	}

	cout << "====================================================================================================\n";
	return Clients;
}
double TotalBalance(vector<PersonData> Clients) {
	double Balance = 0;
	for (PersonData Client : Clients) {
		Balance += Client.Account_Balance;
	}
	return Balance;
}
stUser ConverLinetoUser(string User) {
	vector<string> User_info = split(User, "#//#");
	stUser sUser;
	sUser.Username = User_info[0];
	sUser.Password = User_info[1];
	sUser.Permissions = stoi(User_info[2]);
	return sUser;

}
vector<stUser> from_file_to_Vusers() {
	fstream file;
	file.open(Userpath, ios::in);
	if (file.is_open()) {
		string line;
		vector<stUser> Vusers;
		while (getline(file,line))
		{
			Vusers.push_back(ConverLinetoUser(line));
		}

		file.close();
		return Vusers;

	}
	else {
		cout << "\n File Doesn't Exist !! ";
		return { {"Error in file","Error in file",-1}};
	}


}
bool isUserCorrect(string username, string password, stUser& LoginUser ,bool OnlyUsername=false) {
	vector<stUser> Vusers = from_file_to_Vusers();
	for (const stUser& User : Vusers) {
		if (User.Username == username && OnlyUsername)
			return true;
		if (User.Username == username && User.Password == password) {
			LoginUser = User;
			return true;
		}

	}

	return false;
}
bool isUserExist(stUser User, bool OnlyUsername = false) {
	stUser Dummy;
	return isUserCorrect(User.Username, User.Password, Dummy, OnlyUsername);

}
bool isLoginCorrect(string username, string password) {
	return isUserCorrect(username, password, LoginUser);
}
void Login() {
	cout << "Please  Enter Username and Password : "<<endl;
	bool isLoginFaild = false;
	do {
		if (isLoginFaild)
			cout << "\nLogin Failed , Invalid Username/Password !! " << endl;
		cout << "Username : ";
		string username;
		string password;
		cin >> username;
		cout <<endl<< "Password : ";
		cin >> password;
		
		isLoginFaild = !isLoginCorrect(username, password);


	} while (isLoginFaild);
	Bank();
}
string ConvertUsertoLine(stUser sUser,string Dil="#//#") {
	return sUser.Username + Dil + sUser.Password + Dil + to_string(sUser.Permissions);

}
void AddDatatoFile(string FilePath, string Line) {
	fstream myfile;
	myfile.open(FilePath, ios::app|ios::out);
	if (myfile.is_open()) {
		myfile << Line << endl;
		myfile.close();
		return;
	}
	else {

		cout << "\nError in FILE !!!";
		return;
	}
}
void AddUser(stUser sUser) {
	AddDatatoFile(Userpath, ConvertUsertoLine(sUser));
}
void from_Vuser_to_File(vector<stUser> Vusers) {
	fstream file;
	file.open(Userpath, ios::out);
	if (file.is_open()) {
		file.close();
		for (stUser& sUser : Vusers) {
			if(!sUser.MarkforDelete)
			AddUser(sUser);
		}
	
	}
	else {
		cout << "\nError in creating file";
	}
}
bool CheckEligibility(MainMenuPeromssions Permission) {
	if ((LoginUser.Permissions & Permission) == Permission)
		return true;
	return false;
}
void AccesDeniedScreen() {
	cout << "--------------------------------\n";
	cout << "Acess Denied \n";
	cout << "You Don't Have Permissions to Do this\n";
	cout << "Please Contact Your Admin\n ";
	cout << "--------------------------------\n";
	BacktoMainMenu();
}
void isEligible(MainMenuPeromssions Permission) {
	if (CheckEligibility(Permission)) {
		return;
	}
	else {
		AccesDeniedScreen();
	}

}
void MangeUsersScreen() {
	cout << "========================================";
	cout << endl << "========================================" << endl;
	printf("%32s", "[1] Show Users List\n");
	printf("%29s", "[2] Add New User\n");
	printf("%28s", "[3] Delete User\n");
	printf("%28s", "[4] Update User\n");
	printf("%26s", "[5] Find User\n");
	printf("%26s", "[7] Main Menu\n");
	cout << "========================================" << endl;



}
enMangeUsers ReadMangeUsersChoice() {
	cout << "Please Enter Number 1------> 7 : ";
	int Number;
	cin >> Number;
	return enMangeUsers(Number);
}



void PrintUsersBar() {
	cout << "=====================================================================================================";
	cout << "\n|  Useranme        " << "|    Password      " << "|" << left << setw(61) << "Password" << "|";
	cout << "\n====================================================================================================="<<endl;


}
void PrintLineUser(stUser User) {
	cout << "|" << left << setw(18) << User.Username << "|" << left << setw(18) << User.Password << "|" <<left <<setw(61) << to_string(User.Permissions) << "|"<<endl;
}
void ShowUsers() {
	PrintUsersBar();
	vector<stUser> Users = from_file_to_Vusers();
	for (stUser& sUser : Users)
		PrintLineUser(sUser);
	cout << "=====================================================================================================";
}

void BacktoMangeUsersMenu() {
	cout << "\n\n    Press any key to go back !! ";
	system("pause>0");
	system("cls");
	MangeUsers();
}
void PerformMangeUser(enMangeUsers Choice) {
	system("cls");
	switch (Choice)
	{
	case eShowUsers:
		ShowUsers();
		BacktoMangeUsersMenu();
		break;
	case eAddUser:
		AddUsers();
		BacktoMangeUsersMenu();
		break;
	case eDeleteUser:
		DeleteUser();
		BacktoMangeUsersMenu();
		break;
	case eUpdateUser:
		 UpdateUser();
		 BacktoMangeUsersMenu();
		break;
	case eFindUser:
		FindUser();
		BacktoMangeUsersMenu();
		break;
	case eMainMenu:
		Bank();
		break;
	default:
		PerformMangeUser(ReadMangeUsersChoice());
		break;
	}


}
void MangeUsers() {
	MangeUsersScreen();
	PerformMangeUser(ReadMangeUsersChoice());

}
void WhichScreen(string Perform) {
	cout << "---------------------------------"<<endl;
	cout << "           "<<Perform<<" Screen" << endl;
	cout << "---------------------------------" << endl;

}
int ReadPermissions() {
	cout << "Do you want to Give All Permissions Y/N : ";
	char answer;
	cin >> answer;
	if (tolower(answer) == 'y')
		return MainMenuPeromssions::enAll;
	else {
		string Permissions[] = { "Show Clients","Add Client","Update Client","Delete Client","Find Client","Transactions","Manage Users" };
		MainMenuPeromssions enPermissions[7] = { eShowClinets, eAddClients, eDeleteClients, eUpdateClients, eFindClient, eTransactionScreen,eMangeUsersScreen };
		cout << "\n You want to give access to : \n";
		int PermissionValue = 0;
			for (int i = 0; i < 7; i++)
			{
				cout << Permissions[i] << " Y/N : ";
				cin >> answer;
				if (tolower(answer) == 'y')
					PermissionValue += enPermissions[i];

			}
			return PermissionValue;
	}


}
stUser ReadUser(bool ReadUserName=true) {
	stUser sUser;

	if (ReadUserName) {
		cout << "Enter Username : ";
		cin >> sUser.Username;
		while (isUserExist(sUser, true))
		{
			cout << "[ " << sUser.Username << " ] is Already Exsit in The System !! \n Please enter Another Username :  ";
			cin >> sUser.Username;
		}
	}
	cout << endl << "Enter Password : ";
	cin >> sUser.Password;
	sUser.Permissions = ReadPermissions();
	return sUser;
}
void AddUser() {

	cout << "\nAdding New User" << endl;
	AddDatatoFile(Userpath, ConvertUsertoLine(ReadUser()));

}
void AddUsers() {
	WhichScreen("Add New User");
	char answer;
	do
	{
		AddUser();
		cout << "\n Do You want to add more Users ? Y/N : " ;
		cin >> answer;

	} while (tolower(answer)=='y');
}
stUser FindUserByName(string Username) {
	vector<stUser> Vusers = from_file_to_Vusers();
	for (stUser &User: Vusers )
	{
		if (User.Username == Username)
			return User;
	}
	return { Username ,"-1",-2};
}
void PrintUserCard(stUser User) {
	cout << "\nThe Following  are User Details : \n";
	cout << "\n ---------------------------";
	cout << "\nUsername    : " << User.Username<<endl;
	cout << "Password    : " << User.Password<<endl;
	cout << "Permissions : " << User.Permissions;
	cout << "\n ---------------------------\n";
}
vector<stUser>  MarkforDeleteUser(stUser User) {
	vector<stUser> Users = from_file_to_Vusers();
	for (stUser& user : Users) {
		if (user.Username == User.Username) {
			user.MarkforDelete = true;
			return Users;
		}
	}
}
void PerformDelete(stUser User) {
	from_Vuser_to_File(MarkforDeleteUser(User));
}
void DeleteUser() {
	WhichScreen("Delete User ");
	cout << "Enter User You Want to Delete : \n";
	stUser sUser;
	cout << "Please Enter Username : ";
	cin >> sUser.Username;
	while (sUser.Username=="Admin")
	{
		cout << "\nYou can't Delete Admin !! please enter Another User :  ";
		cin >> sUser.Username;
	}
	sUser = FindUserByName(sUser.Username);
	if (sUser.Password != "-1") {

		PrintUserCard(sUser);
		cout << "Are you sure  you want to update  this User ? Y/N :  ";
		char answer;
		cin >> answer;

		if (tolower(answer) == 'y') {
			PerformDelete(sUser);
			cout << "\n [ " << sUser.Username << " ] Deleted Seccusfully";
		}
		else {
			cout << "\nYou Choosed to Not delete [" << sUser.Username << "]";

		}
	}
	else {
		cout << "\n [ " << sUser.Username << " ] Not Found in The System !! ";
	}

}
vector<stUser> RemplaceUserbyother(stUser sUser, stUser NewUser) {
	vector<stUser> Users = from_file_to_Vusers();
	NewUser.Username = sUser.Username;
	for (stUser& User : Users)
		if (User.Username == sUser.Username) {
			User = NewUser;
			break;
		}

	return Users;
}
void PerformUpdate(stUser sUser) {
	stUser NewUser = ReadUser(false);
	vector<stUser> NewVusers = RemplaceUserbyother(sUser, NewUser);
	from_Vuser_to_File(NewVusers);

	
}
void UpdateUser() {
	WhichScreen("Update User ");
	cout << "Enter User You Want to Update : \n";
	stUser sUser;
	cout << "Please Enter Username : ";
	cin >> sUser.Username;
	while (sUser.Username == "Admin")
	{
		cout << "\nYou can't Update Admin !! please enter Another User :  ";
		cin >> sUser.Username;
	}
	sUser = FindUserByName(sUser.Username);
	if (sUser.Password != "-1") {
		PrintUserCard(sUser);
		cout << "Are you sure  you want to update  this User ? Y/N :  ";
		char answer;
		cin >> answer;

		if (tolower(answer) == 'y') {
			PerformUpdate(sUser);
			cout << "\n [ " << sUser.Username << " ] Updated Seccusfully";
		}
		else {
			cout << "\nYou Choosed to Not delete [" << sUser.Username << "]";
		}
	}
	else {
		cout << "\n [ " << sUser.Username << " ] Not Found in The System !! ";
	}
}
void FindUser() {
	WhichScreen("Find User ");
	cout << "Enter User You Want to Find : \n";
	stUser sUser;
	cout << "Please Enter Username : ";
	cin >> sUser.Username;
	sUser = FindUserByName(sUser.Username);
	if (sUser.Password != "-1") {
		PrintUserCard(sUser);
	}
	else {
		cout << "\n [ " << sUser.Username << " ] Not Found in The System !! ";
	}
}

