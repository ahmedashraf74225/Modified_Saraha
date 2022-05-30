
#include "Users.h"

using namespace std;

#include <iostream>
#include <fstream>
#include <unordered_set>
#include <set>
#include <string>
#include <sstream>
#include <vector>
#include <iterator>
#include <conio.h>
#include <map>
#include <list>


#pragma warning(disable:4996)
#define _CRT_SECURE_NO_WARNINGS

ifstream myfile;
ifstream UsersReader("users.txt");

Users tempUser;
static Users currentUser;
static vector<Users> AllUsers;


vector<Users> Users::getUserInfo() {
	return AllUsers;
}



void Users::ViewAllSent() {
	Messages msg;
	stack<Messages> last_to_old;
	myfile.open("Data/sentMessages/" + currentUser.username + ".txt");
	if (!myfile) {
		cout << "There is no sent Messages Available  " << endl;
		mainPage();
	}
	if (myfile.is_open()) {

		int i = 1;
		for (string line; getline(myfile, line); i++) {
			if (i == 1) {
				// cout << "Content : " << line << endl;
				msg.content = line;
			}
			else if (i == 3) {
				vector<string> words{};
				char delimiter = ' ';

				istringstream sstream(line);
				string word;
				while (std::getline(sstream, word, delimiter)) {
					word.erase(remove_if(word.begin(), word.end(), ispunct), word.end());
					words.push_back(word);
				}

				msg.receiver = words[0];
				msg.sender = words[1];
				if (words[2] == "0") {
					msg.Fav = false;
				}
				else {
					msg.Fav = true;
				}

			}

			if (i == 3) {
				last_to_old.push(msg);
				i = 0;

			}

		}
	}
	myfile.close();
	Messages msg2;

	cout << "\t\t-> Messages From Latest to oldest : " << "\n";

	while (!last_to_old.empty()) {
		msg2 = last_to_old.top();
		last_to_old.pop();
		cout << "___________________________________________________\n" << endl;
		cout << "|  Content of the Message is   :  " << msg2.content <<" |" << "\n";
		cout << "|  Receiver of the Message is  :  " << msg.receiver <<" |" << '\n';
		cout << "___________________________________________________\n" << endl;
	}
	return;
	
}
void Users::ViewForFav() {
	Messages msg;

	myfile.open("Data/Messages/" + currentUser.username + ".txt");
	if (!myfile) {
		cout << "There is no Received Messages " << endl;
		cout << "to go back the | Main Page | Press m \n";
		char ch;
		cin >> ch;
		if (ch == 'm')
		{ 
			mainPage();
		}
	}
	if (myfile.is_open()) {

		int i = 1;
		int index = 0;
		for (string line; getline(myfile, line); i++) {

			if (i == 1) {
				cout << "(" << index << ")" << endl;
				cout << "Content : " << line << endl;

			}
			else if (i == 3) {
				vector<string> words{};
				char delimiter = ' ';

				istringstream sstream(line);
				string word;
				while (std::getline(sstream, word, delimiter)) {
					word.erase(remove_if(word.begin(), word.end(), ispunct), word.end());
					words.push_back(word);
				}
				cout << "Receiver : " << words[0] << endl;
				cout << "Sender : " << words[1] << endl;;

				if (words[2] == "0") {
					msg.Fav = false;
					cout << "Message in your favourites !" << endl;
				}
				else {
					msg.Fav = true;
					cout << "Message in your favourites !" << endl;
				}

			}

			if (i == 3) {

				cout << "_______________________" << endl;
				index++;
				i = 0;

			}

		}
	}
	myfile.close();

}

void Users::ViewFromSpeceific_Contact(string name) {

	bool flag = false;
	for (int i = 0; i < currentUser.ListOfContacts.size(); i++) {
		if (currentUser.ListOfContacts[i] == name) {
			flag = true;
			break;
		}
	}
	if (flag) {
		myfile.open("Data/sentMessages/" + name + ".txt");
		if (!myfile) {
			cout << "\tCONTACT NAME IS WRONG OR DOSEN'T EXIST !!!!" << endl;
			return;
		}
		if (myfile.is_open()) {

			Messages msg;

			int i = 1;
			for (string line; getline(myfile, line); i++)
			{
				if (i == 1) {
					msg.content = line;
				}
				else if (i == 3) {
					vector<string> words{};
					char delimiter = ' ';

					istringstream sstream(line);
					string word;
					while (std::getline(sstream, word, delimiter)) {
						word.erase(std::remove_if(word.begin(), word.end(), ispunct), word.end());
						words.push_back(word);
					}
					msg.receiver = words[0];
					msg.sender = words[1];


					if (words[2] == "0") {

						msg.Fav = false;
					}
					else {
						msg.Fav = true;
					}

				}

				if (i == 3) {
					if (msg.sender == name && msg.receiver == currentUser.username) {
						cout << "Content : " << msg.content << endl;
						cout << "Came From : " << name << endl;
						cout << "__________________________\n\n" << endl;
					}

					i = 0;
					msg.content.clear();
					msg.sender.clear();
					msg.receiver.clear();
					msg.Fav = false;

				}

			}
		}
		myfile.close();
	}
	else {
		cout << "Contact Name Doesn't Exist !" << endl;
	}

}


void Users::AddContact(string name) {

	bool is = 0;
	fstream myfile("Data/Contacts/" + currentUser.username + ".txt",ios::in);
	string line;
	list<string> list_of;
	list_of.clear();
	while (!myfile.eof())
	{
		myfile >> line;
		list_of.push_front(line);
	}
	myfile.close();
	while (!list_of.empty())
	{
		if (list_of.front() == name)
		{
			is = 1;
			break;
		}
		else
		{
			list_of.pop_front();
		}
	}
	if (is)
	{
		cout << "\tYou Added this Contact before | Please Add a new contact :\n";
		string newName;
		cin >> newName;
		AddContact(newName);
	}
	else
	{

		int check = 0;
		// what that loop mean ????????
		for (int i = 0; i < currentUser.getUserInfo().size(); i++) {
			if (currentUser.getUserInfo()[i].username == name) {
				check = 1;
				currentUser.ListOfContacts.push_back(name);
				ofstream UpdateLocalContacts("Data/Contacts/" + currentUser.username + ".txt", ios::app);
				UpdateLocalContacts << name;
				UpdateLocalContacts << "\n";
				cout << "Contact Added Successfully !" << endl;

				UpdateLocalContacts.close();
				break;
			}
		}
		if (check == 0) {
			cout << "\t_____________________________________________________\n\n";
			cout << "\t\t Contact name dosen't EXIST !!\n\t\t\t| You Can't ADD |" << endl;
			cout << "\t_____________________________________________________\n";
		}
	}
}

void Users::DisplayContacts() {

	int i = 1;
	myfile.open("Data/Contacts/" + currentUser.username + ".txt", ios::in);
	string line;
	unordered_set<string> mySet;

	if (!myfile.is_open()) {
		cout << "You don't Have any contacts | try to add some . \n";
		cout << "\t\tif u wanna add Press A \n\t\tif u wanna return back main Press M : \n";
		char c;
		cin >> c;

		char ch = tolower(c);
		if (ch == 'a') {
			cout << "What is the name of the contact u wanna add :\n";
			string nameContact;
			cin >> nameContact;
			AddContact(nameContact);
		}
		else {
			mainPage();
		}


	}
	else {
		while (!myfile.eof()) {
			myfile >> line;
			mySet.insert(line);

		}
	}
	if (mySet.size() == 0) {
		cout << "|  You don't Have any contacts  |\n\n";
		myfile.close();
		mainPage();
	}
	else {
		cout << "\t\t Your contacts are :" << "\n";
		for (const auto& elem : mySet) {
			cout <<"\t(" << i++ << ")" << "|   " << elem << "\n";
		}
		cout << "\n\n";
	}
	
	myfile.close();
}


void Users::SendMessage(Messages message) {
	bool flag = false;
	for (int i = 0; i < currentUser.ListOfContacts.size(); i++) {
		if (currentUser.ListOfContacts[i] == message.receiver) {
			flag = true;
			break;
		}
	}
	if (flag) {
		myfile.open("Data/Messages/" + message.receiver + ".txt");

		if (!myfile) {
			ofstream createTheFile("Data/Messages/" + message.receiver + ".txt", ios::app);
		}
		ofstream MSGUpdate("Data/Messages/" + message.receiver + ".txt", ios::app);

		MSGUpdate << message.content;
		MSGUpdate << "\n***\n";
		MSGUpdate << message.receiver;
		MSGUpdate << " ";
		MSGUpdate << message.sender;
		MSGUpdate << " ";
		MSGUpdate << message.Fav << endl;
		MSGUpdate.close();


		/////////////////////////////////
		currentUser.Message.push_back(message);
		currentUser.sentMessages.push_back(message);
		/////////////////////////////////

		cout << "\t | Message has been Sent Successfully .\n\n" << endl;
		myfile.close();

		myfile.open("Data/sentMessages/" + message.sender + ".txt");

		if (!myfile) {
			ofstream createTheFile("Data/sentMessages/" + message.sender + ".txt", ios::app);
		}
		ofstream SentMSGUpdate("Data/sentMessages/" + message.sender + ".txt", ios::app);

		SentMSGUpdate << message.content;
		SentMSGUpdate << "\n***\n";
		SentMSGUpdate << message.receiver;
		SentMSGUpdate << " ";
		SentMSGUpdate << message.sender;
		SentMSGUpdate << " ";
		SentMSGUpdate << message.Fav << endl;

		myfile.close();
		SentMSGUpdate.close();
	}
	else {
		cout << "\t__________________________________________\n\n";
		cout << "\t| Receiver Doesn't Exist In Your Contact |" << endl;
		cout << "\t___________________________________________\n\n";

	}

}
void Users::SendMSG_Anonymus(Messages message) {
	bool flag = false;
	for (int i = 0; i < currentUser.getUserInfo().size(); i++) {
		if (currentUser.getUserInfo()[i].username == message.receiver) {
			flag = true;
			break;
		}
	}
	if (flag) {
		myfile.open("Data/Messages/" + message.receiver + ".txt");

		if (!myfile) {
			ofstream createTheFile("Data/Messages/" + message.receiver + ".txt", ios::app);
		}
		ofstream MSGUpdate("Data/Messages/" + message.receiver + ".txt", ios::app);

		MSGUpdate << message.content;
		MSGUpdate << "\n***\n";
		MSGUpdate << message.receiver;
		MSGUpdate << " ";
		MSGUpdate << message.sender;
		MSGUpdate << " ";
		MSGUpdate << message.Fav << endl;
		MSGUpdate.close();

		cout << "MSG Sent As Anonymous Successfully !" << endl;
		myfile.close();

		/* myfile.open("Data/sentMessages/" + message.sender + ".txt");

		 if (!myfile) {
			 ofstream createTheFile("Data/sentMessages/" + message.sender + ".txt", ios::app);
		 }
		 ofstream SentMSGUpdate("Data/sentMessages/" + message.sender + ".txt", ios::app);

		 SentMSGUpdate << message.content;
		 SentMSGUpdate << "\n***\n";
		 SentMSGUpdate << message.receiver;
		 SentMSGUpdate << " ";
		 SentMSGUpdate << message.sender;
		 SentMSGUpdate << " ";
		 SentMSGUpdate << message.Fav << endl;

		 myfile.close();
		 SentMSGUpdate.close();*/
	}
	else {
		cout << "Receiver Doesn't Even Exist !!" << endl;
		cout << "-------------------" << endl;
	}


}

void Users::UploadMessages() {
	//begin login to clear
	currentUser.Message.clear();
	currentUser.Fav_Message.clear();

	myfile.open("Data/Messages/" + currentUser.username + ".txt");
	if (!myfile) {
		ofstream createTheFile("Data/Messages/" + currentUser.username + ".txt", ios::app);
	}
	else {

		bool isContentRead = false;
		string check, fav;

		Messages tempMessage;
		while (myfile) {
			if (!isContentRead) {
				myfile >> check;
				if (check == "***") {
					isContentRead = true;
				}
				else {
					tempMessage.content += check;
					tempMessage.content += " ";
				}
			}
			else {
				myfile >> tempMessage.receiver;
				myfile >> tempMessage.sender;
				myfile >> fav;

				if (fav == "1") {
					tempMessage.Fav = true;
					currentUser.Fav_Message.push_back(tempMessage);
				}
				else {
					tempMessage.Fav = false;
				}

				currentUser.Message.push_back(tempMessage);
				isContentRead = false;
				tempMessage.content.clear();
			}
		}
	}
	myfile.close();
}


void Users::search_contact(string nameContact) {

	bool found = false;
	string line;

	ifstream myfile("Data/Contacts/" + currentUser.username + ".txt", ios::in);
	vector<string> tempContacts;
	if (!myfile)
	{
		cout << "\t | You  don't have any contacts . |" << endl;
		return;

	}

	while ( !myfile.eof() ) {
		myfile >> line;
		tempContacts.push_back(line);
	}

	/*if (tempContacts.size() == 0) {
		myfile.close();
		return;

	}*/
	

	/*if (binary_search(tempContacts.begin(), tempContacts.end(), nameContact) )
		found = true;
	else
		 found = false;*/


	for (int i = 0; i < tempContacts.size(); i++) {
		if (nameContact == tempContacts[i])
			found = true;

	}
	if (!found)
		cout << "\t NOT FOUND" << endl;
	else {
		cout << "\| The contact is FOUND |\n\n" << endl;
	}
	myfile.close();


}

void Users::UploadSentMessages() {
	currentUser.sentMessages.clear();

	myfile.open("Data/sentMessages/" + currentUser.username + ".txt");
	if (!myfile) {
		ofstream createTheFile("Data/sentMessages/" + currentUser.username + ".txt", ios::app);
	}
	else {

		bool isContentRead = false;
		string check, fav;

		Messages tempMessage;
		while (myfile) {
			if (!isContentRead) {
				myfile >> check;
				if (check == "***") {
					isContentRead = true;
				}
				else {
					tempMessage.content += check;
					tempMessage.content += " ";
				}
			}
			else {
				myfile >> tempMessage.receiver;
				myfile >> tempMessage.sender;
				myfile >> fav;

				if (fav == "1")
					tempMessage.Fav = true;
				else
					tempMessage.Fav = false;

				currentUser.sentMessages.push_back(tempMessage);
				isContentRead = false;
				tempMessage.content.clear();
			}
		}
	}
	myfile.close();
}

void Users::UndoLast() {

	Messages msg;
	msg = currentUser.sentMessages.back();
	currentUser.sentMessages.pop_back();



	myfile.open("Data/sentMessages/" + currentUser.username + ".txt");

	if (!myfile) {
		ofstream createTheFile("Data/sentMessage/" + currentUser.username + ".txt", ios::app);
	}
	ofstream Hell("Data/sentMessages/" + currentUser.username + ".txt");
	for (int i = 0; i < currentUser.sentMessages.size(); i++) {
		Hell << currentUser.sentMessages[i].content;
		Hell << "\n***\n";
		Hell << currentUser.sentMessages[i].receiver;
		Hell << " ";
		Hell << currentUser.sentMessages[i].sender;
		Hell << " ";
		Hell << currentUser.sentMessages[i].Fav << endl;
	}
	Hell.close();



	//myfile.open("Data/Messages/" + msg.receiver + ".txt");

	//if (!myfile) {
	//    ofstream createTheFile("Data/Message/" + msg.receiver + ".txt", ios::app);
	//}
	//ofstream tst("Data/Messages/" + msg.receiver + ".txt");
	//for (int i = 0;i < currentUser.Message.size()-1;i++) {
	//    tst << currentUser.Message[i].content;
	//    tst << "\n***\n";
	//    tst << currentUser.Message[i].receiver;
	//    tst << " ";
	//    tst << currentUser.Message[i].sender;
	//    tst << " ";
	//    tst << currentUser.Message[i].Fav << endl;
	//}
	//tst.close();

	cout << "Messages Deleted Successfully From Files And DS !" << endl;

}

string Users::getContact(int index) {
	return currentUser.ListOfContacts[index];
}


Messages Users::getMessage(int i) {
	return currentUser.Message[i];
}

Messages Users::getSentMessages(int i) {
	return currentUser.sentMessages[i];
}

void Users::ViewAllFav() {

	if (currentUser.Fav_Message.size() == 0) {
		cout << " | You don't have any favourite messages . \n\n" << endl;
		return;
	}

	cout << "| Your Favourite Messages are :\n\n" << endl;

	for (int i = 0; i < currentUser.Fav_Message.size(); i++) {
		cout << "Content : " << currentUser.Fav_Message[i].content << endl;
		cout << "Sender : " << currentUser.Fav_Message[i].sender << endl;
		cout << "___________________________________" << endl;
	}
}

void Users::viewAllusers() {

	fstream usersFile("users.txt", ios::in);
	set<string> mySet;

	string s1, s2, s3;
	if (!usersFile.is_open()) {
		cout << "| NO Available USERS yet |\n\n " << endl;
		return;
	}
	else {
		while (!usersFile.eof()) {
			usersFile >> s1;
			usersFile >> s2;
			usersFile >> s3;

			mySet.insert(s1);
		}
		usersFile.close();
		int j = 0;
		cout << "\n";
		cout << "\t\t\tALL USERS ARE :\n\n";
		for (auto i : mySet) {
			cout << "\t |(" << (++j) << ")  " << i << " \n";
		}
		cout << "___________________________________________________\n\n";
	}
}

void Users::UploadContacts() {


	myfile.open("Data/Contacts/" + currentUser.username + ".txt");
	Users tempUser;
	if (myfile.is_open()) {
		string s1;

		while (!myfile.eof()) {
			myfile >> s1;

			currentUser.ListOfContacts.push_back(s1);
		}
		myfile.close();
		currentUser.ListOfContacts.pop_back();

	}





}


void Users::RemoveOldestFav() {
	if (currentUser.Fav_Message.empty()) {
		cout << "\tThere is no Favourite Messages For You .\n" << endl;
		cout << "________________________________________________\n\n";
		return;
	}
	else {
		Messages msg;

		msg = currentUser.Fav_Message.front();

		currentUser.Fav_Message.pop_front();


		for (int i = 0; i < currentUser.Message.size(); i++) {

			if (msg.receiver == currentUser.Message[i].receiver && msg.content == currentUser.Message[i].content) {
				currentUser.Message[i].Fav = false;

				break;
			}
		}



		myfile.open("Data/Messages/" + currentUser.username + ".txt");

		if (!myfile) {
			ofstream createTheFile("Data/Message/" + currentUser.username + ".txt", ios::app);
		}
		ofstream Hell("Data/Messages/" + currentUser.username + ".txt");
		for (int i = 0; i < currentUser.Message.size(); i++) {
			Hell << currentUser.Message[i].content;
			Hell << "\n***\n";
			Hell << currentUser.Message[i].receiver;
			Hell << " ";
			Hell << currentUser.Message[i].sender;
			Hell << " ";
			Hell << currentUser.Message[i].Fav << endl;
		}
		Hell.close();
		myfile.close();

		cout << "Oldest Fav Message has been Removed and Edited IN [ Message Files ]  ." << endl;
		cout << "______________________________________________________\n\n" << endl;

	}
}

void Users::UploadUsers() {

	fstream usersFile("users.txt", ios::in);
	Users tempUser;

	string s1, s2, s3;
	while (!usersFile.eof()) {
		usersFile >> s1;
		usersFile >> s2;
		usersFile >> s3;

		tempUser.username = s1;
		tempUser.password = s2;
		tempUser.ID = s3;
		AllUsers.push_back(tempUser);
	}
	usersFile.close();
	AllUsers.pop_back();

}

void Users::Register(string name, string id, string pass, string surePass) {

	Users UserChecking;
	UserChecking.UploadUsers();

	int registerState = 0;
	ofstream usersFileUpdate("users.txt", ios::app);

	for (int i = 0; i < UserChecking.getUserInfo().size(); i++) {
		if (name == AllUsers[i].username) {
			registerState = 1;
			break;
		}
	}
	for (int i = 0; i < UserChecking.getUserInfo().size(); i++) {
		if (id == AllUsers[i].ID) {
			registerState = 4;
			break;
		}
	}

	
	if (pass != surePass) {
		registerState = 2;
	}
	else if (pass.size() < 4) {
		registerState = 3;

	}
	if (registerState == 0) {
		UserChecking.username = name;
		UserChecking.password = pass;
		UserChecking.ID = id;
		
		usersFileUpdate << name;
		usersFileUpdate << " ";
		usersFileUpdate << pass;
		usersFileUpdate << " ";
		usersFileUpdate << id;
		usersFileUpdate << "\n";
		AllUsers.push_back(UserChecking);
		usersFileUpdate.close();
		cout << "\n\t\t\t Registration is successfull! \n";
	}
	else if (registerState == 3) {

		usersFileUpdate.close();
		cout << "Password is Too SMALL !!" << endl;
		cout << "Please Write a correct Password  : ";
		cin >> UserChecking.password;
		cout << " Your Password again : ";
		string confirm;
		cin >> confirm;
		Users::Register(name, id, UserChecking.password, confirm);

	}
	else if (registerState == 2) {
		usersFileUpdate.close();
		cout << "Passwords don't match \n";
		cout << "Please write the Same PASSWORDS | your password : ";
		cin >> UserChecking.password;
		cout << " Confirm your password : ";
		string confirm;
		cin >> confirm;
		Users::Register(name, id, UserChecking.password, confirm);

	}
	else if (registerState == 1){
		usersFileUpdate.close();
		cout << "Name is taken before | TAKE ANOTER ONE :" << endl;
		cin >> UserChecking.username;
		Users::Register(UserChecking.username, id, pass, surePass);

	}
	else if (registerState == 4)
	{
		usersFileUpdate.close();
		cout << "ID is taken before [MUST BE UNIQUE] | TAKE ANOTER ONE :" << endl;
		string set_ID;
		cin >> set_ID;
		UserChecking.setID(set_ID);
		Users::Register(name, set_ID, pass, surePass);

	}
	usersFileUpdate.close();
}
void Users::AddToFav(int index) {

	Messages msg = currentUser.Message[index];
	if (msg.Fav == true) {
		cout << "Already in Favourite !!" << endl;
		return;
	}
	else {


		msg.Fav = true;
		currentUser.Message[index].Fav = true;
		currentUser.Fav_Message.push_back(msg);



		//"----"
		myfile.open("Data/Messages/" + currentUser.username + ".txt");

		if (!myfile) {
			ofstream createTheFile("Data/Message/" + currentUser.username + ".txt", ios::app);
		}
		ofstream Hell("Data/Messages/" + currentUser.username + ".txt");
		for (int i = 0; i < currentUser.Message.size(); i++) {
			Hell << currentUser.Message[i].content;
			Hell << "\n***\n";
			Hell << currentUser.Message[i].receiver;
			Hell << " ";
			Hell << currentUser.Message[i].sender;
			Hell << " ";
			Hell << currentUser.Message[i].Fav << endl;
		}
		Hell.close();
		cout << "Message Added To Favourite Successfully !!" << endl;
		cout << "___________________________________________\n\n" << endl;
		//"---"
	   /* myfile.open("Data/sentMessages/" + msg.sender + ".txt");

		if (!myfile) {
			ofstream createTheFile("Data/sentMessage/" + msg.sender + ".txt", ios::app);
		}
		ofstream tst("Data/sentMessages/" + msg.sender + ".txt");
		for (int i = 0;i < currentUser.sentMessages.size();i++) {
			tst << currentUser.sentMessages[i].content;
			tst << "\n***\n";
			tst << currentUser.sentMessages[i].receiver;
			tst << " ";
			tst << currentUser.sentMessages[i].sender;
			tst << " ";
			tst << currentUser.sentMessages[i].Fav << endl;
		}
		tst.close();*/

	}

}
void Users::setID(string &id) {
	currentUser.ID = id;
}

string &Users::getID() {
	return currentUser.ID;
}

//void Users::UploadFavourite() {
//
//    currentUser.Fav_Message.clear();
//
//    myfile.open("Data/Favourites/" + currentUser.username + ".txt");
//    if (!myfile) {
//        ofstream createTheFile("Data/Favourites/" + currentUser.username + ".txt", ios::app);
//    }
//    else {
//
//        bool isContentRead = false;
//        string check, fav;
//
//        Messages tempMessage;
//        while (myfile) {
//            if (!isContentRead) {
//                myfile >> check;
//                if (check == "***") {
//                    isContentRead = true;
//                }
//                else {
//                    tempMessage.content += check;
//                    tempMessage.content += " ";
//                }
//            }
//            else {
//                myfile >> tempMessage.receiver;
//                myfile >> tempMessage.sender;
//                myfile >> fav;
//
//           
//
//                tempMessage.Fav = true;
//                currentUser.Fav_Message.push_back(tempMessage);
//                isContentRead = false;
//                tempMessage.content.clear();
//            }
//        }
//    }
//    myfile.close();
//}

void Users::setCurrentUser(Users user) {
	currentUser = user;
}

Users Users::getCurrentUser() {
	return currentUser;
}

void Users::Login(string name, string pass) {

	Users UserChecking;
	UserChecking.UploadUsers();

	bool is = 0;
	int userMatch = 0;
	for (int i = 0; i < UserChecking.getUserInfo().size(); i++) {
		if (name == UserChecking.getUserInfo()[i].username) {
			is = 1;
			if (pass == UserChecking.getUserInfo()[i].password) {
				userMatch = 1;

				currentUser.username = UserChecking.getUserInfo()[i].username;
				currentUser.password = UserChecking.getUserInfo()[i].password;
				currentUser.ID = UserChecking.getUserInfo()[i].ID;

				setCurrentUser(currentUser);
				break;
			}

		}
	}
	if (!is) {
		cout << "\n\t\tSORRY | you don't have account . \n You should register first \n \n";
		cout << "\t\t|  Press 1 to Register  |\n";
		cout << "\t\t|  Press 2 to Main Page|\n";

		cout << "\t_________________________________________________________________" << "\n";
		int option;
		cin >> option;
		if (option == 1) {
			string confirm;
			cout << "\t\t\t Enter the username : ";
			cin >> UserChecking.username;
			cout << "\t\t\t Enter the ID : ";
			cin >> UserChecking.ID;
			cout << "\t\t\t Enter the password : ";
			cin >> UserChecking.password;
			cout << "\t\t\t Enter the password again : ";
			cin >> confirm;
			UserChecking.Register(UserChecking.username, UserChecking.ID, UserChecking.password, confirm);
			return;

		}
		else {
			mainPage();
		}
	}
	if (userMatch == 1) {

		cout << "\t\t___________________________________________________\n\n";
		cout << "\t\t\tWELCOME      [   "<< currentUser.username << "   ]\n\t\t\tYour LOGIN is successful \n";

		UserChecking.UploadContacts();
		UserChecking.UploadSentMessages();
		UserChecking.UploadMessages();

	}
	else {
		userMatch = 0;
		cout << "YOU CAN'T LOGIN \n ";
		cout << "Write the USERNAME & PASSWORD again :\n\n";

		cout << "\t\t\t Enter the username : ";
		cin >> UserChecking.username;

		cout << "\t\t\t Enter the password : ";
		cin >> UserChecking.password;

		Login(UserChecking.username, UserChecking.password);
	}


}

void Users::mainPage() {
	string name, id, pass, confirm, op;
	map<string, string> mp;
	mp.clear();


	int c;
	cout << "\t\t\t____________________________________________________________\n\n\n";
	cout << "\t\t\t                  Weclome to the Login page         \n\n\n ";
	cout << "\t\t\t____________________           MENU         ________________\n\n";
	cout << "                                                                             \n\n";
	cout << "\t | Press 1 to LOGIN                     |" << "\n";
	cout << "\t | Press 2 to REGISTER                  |" << "\n";
	cout << "\t | Press 3 if you forgot your PASSWORD  |" << "\n";
	cout << "\t | Press 4 to EXIT                      |" << "\n";
	cout << "\n\t\t\t Please enter your choice : ";
	cin >> c;
	cout << "\n";

	switch (c) {
	case 1:
		cout << "\t\t\t USERNAME :";
		cin >> name;
		cout << "\t\t\t PASSWORD :";
		int ch;
		ch = getch();
		while (ch != 13) {
			pass.push_back(ch);
			cout << "*";
			ch = getch();
		}
		cout << endl;
		Login(name, pass);
		break;
	case 2:
		cout << "\t\t\t Enter the username : ";
		cin >> name;
		cout << "\t\t\t Enter the ID : ";
		cin >> id;
		cout << "\t\t\t Enter the password : ";
		cin >> pass;
		cout << "\t\t\t Enter the password again : ";
		cin >> confirm;
		Register(name, id, pass, confirm);
		break;
	case 3:
	{ {
			cout << "\n\t\t\t You forgot the password ? No worries \n\n";
			cout << "| Press 1 to search your password by ID |" << endl;
			cout << "| Press 2 to go back to the main menu   |" << endl;
			cout << "\t\t\t Enter your choice : ";
			cin >> op;
			if (op == "1") {
				string name_r;
				cout << "\n\t\t Enter the ID which you remembered : ";
				cin >> name_r;
				myfile.open("users.txt", ios::in);
				string s1, s2, s3;
				while (!myfile.eof()) {

					myfile >> s1;
					myfile >> s2;
					myfile >> s3;

					mp.insert(pair<string, string>(s3, s2));
				}
				myfile.close();
				bool is = 0;
				for (auto itr = mp.begin(); itr != mp.end(); ++itr) {
					if (itr->first == name_r) {
						is = 1;
						cout << "Your account is found | your PASSWORD is : " << itr->second << "\n\n";
						break;
					}
				}
				if (is) {
					cout << "if u wanna return Main Page Press M \n";
					cout << "if u wanna LOGIN Press L :\n";
					char ch;
					cin >> ch;

					if (ch == 'm') {
						mainPage();
					}
					else {
						string usname, passwo;
						cout << "\t\t\t Enter the username : ";
						cin >> usname;
						cout << "\t\t\t Enter the password : ";
						cin >> passwo;
						Login(usname, passwo);
					}
				}
				else {
					cout << "\t\t | This Username doesn't exist |\n";
					cout << "| IF u wanna Register Press R| \n | IF u wanna back to Main Page Press M |\n";
					char c;
					cin >> c;
					if (c == 'r') {
						cout << "\t\t\t Enter the username : ";
						cin >> name;
						cout << "\t\t\t Enter the ID : ";
						cin >> id;
						cout << "\t\t\t Enter the password : ";
						cin >> pass;
						cout << "\t\t\t Enter the password again : ";
						cin >> confirm;
						Register(name, id, pass, confirm);
					}
					else if (c == 'm')
						mainPage();
				}

			}
			else {
				mainPage();

			}

		}
	break;
	}
	case 4:
		cout << "\t________________________________________________________________________\n\n";
		cout << "\t\t\t Thank you for your time , i hope you enjoyed \n";
		cout << "\t_________________________________________________________________________\n";
		break;
	default:
		system("cls");
		cout << "\n\n\t\t\t  >>>>> Please select form the options given above  \n" << "\n";
		mainPage();
	}
}


Users::~Users() {

}
