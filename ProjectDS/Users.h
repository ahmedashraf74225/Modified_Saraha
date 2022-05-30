
#ifndef DEADLINE_USERS_H
#define DEADLINE_USERS_H
#ifndef USERS_H
#define USERS_H
#include<iostream>
#include<vector>
#include<queue>
#include <stack>
#include"Messages.h"

using namespace std;



class Users
{

private:
    string ID;
public:
    string username;
    string password;
    

    

    vector<string>ListOfContacts;

    vector<Messages>Message;
    vector <Messages>sentMessages;
    deque <Messages> Fav_Message;

    vector <Users> getUserInfo();

    string& getID();
    void setID(string &id);



    void ViewAllFav();
    void ViewAllSent();
    void ViewForFav();
    void ViewFromSpeceific_Contact(string name);
    void viewAllusers();


    void AddContact(string name);
    void AddToFav(int index);

    void DisplayContacts();



    void SendMessage(Messages msg);
    void SendMSG_Anonymus(Messages msg);


    void UndoLast();

    void UploadMessages();
    void UploadSentMessages();
    void UploadUsers();
    void UploadContacts();
   
    void mainPage();

    void search_contact(string nameContact);

    string getContact(int index);

    void Register(string name, string id, string pass, string surePass);
    void Login(string name, string pass);

    void setCurrentUser(Users user);
    Users getCurrentUser();


    Messages getMessage(int index);
    Messages getSentMessages(int index);

    void RemoveOldestFav();




    virtual ~Users();

protected:

private:
};

#endif // USERS_H
#endif //DEADLINE_USERS_H
