#include <iostream>
#include "Users.h"
#include "Messages.h"
#include <string>

#include <iostream>
#include <fstream>
#include <istream>

void  showMenu();
string name, id, pass, confirm;
Users user;
Messages msg;



int main() {


    user.mainPage();
    cout << "\t\t________________________________________________________\n\n";


    showMenu();

}

void  showMenu() {
    int n;

    cout << "\t\tEnter (1) to: Add a user to your contact\n";
    cout << "\t\tEnter (2) to: Send a message to a contact\n";
    cout << "\t\tEnter (3) to: Undo the last sent message\n";
    cout << "\t\tEnter (4) to: Search for a contact\n";
    cout << "\t\tEnter (5) to: View all contacts\n";
    cout << "\t\tEnter (6) to: View all sent messages from latest to oldest\n";
    cout << "\t\tEnter (7) to: View all received messages from a contact\n";
    cout << "\t\tEnter (8) to: Put a message in favorites\n";
    cout << "\t\tEnter (9) to: Remove oldest message from favorites\n";
    cout << "\t\tEnter (10) to: View all favorite messages\n";
    cout << "\t\tEnter (11) to: View all users\n";
    cout << "\t\tEnter (12) to: Send Anonymously\n";
    cout << "\t\tEnter (0) to: Exit\n\n";

    cout << "Your choice: ";
    cin >> n;
    switch (n) {
    case 1:
    {
        string contactName;
        cout << "Please enter the name of user to Add in your contacts :\n";
        cin >> contactName;
        user.AddContact(contactName);
        cout << "\n";

        cout << "IF you want to return back to | Main Page | Press M.\n";
        cout << "IF you want to return back to | show Menu | Press S :\n\n";

        char s;
        cin >> s;
        char ch = tolower(s);
        if (ch == 'm')
            user.mainPage();
        else
            showMenu();
    }
    break;
    case 2:
    {
        string con, con1;
        cout << "Please Write the content of the Message :" << endl;
        getline(cin >> ws, con);
        msg.content = con;
        cout << endl;

        cout << "Please write the name who u wanna send a message :" << endl;
        cin >> con1;
        msg.receiver = con1;
        cout << "\n";
        msg.sender = user.getCurrentUser().username;
        user.SendMessage(msg);

        cout << "to return back | Main Page | Press M \n";
        cout << "to return back | show Menu | Press S \n\n";
        char c;
        cin >> c;
        if (c == 'm')
            user.mainPage();
        else
            showMenu();
    }
    break;
    case 3:
        user.UndoLast();
        break;

    case 4:
    {
        cout << "| Please Enter the name of contact u wanna search for :\n";
        string contact_name;
        cin >> contact_name;
        user.search_contact(contact_name);

        cout << "to return back | Main Page | Press M \n";
        cout << "to return back | show Menu | Press S \n\n";
        char c;
        cin >> c;
        if (c == 'm')
        {
            user.mainPage();
        }
        else
        {
            showMenu();

        }
        break;
    }
    case 5:
    {
        user.DisplayContacts();
        cout << "to return back | Main Page | Press M \n";
        cout << "to return back | show Menu | Press S \n\n";

        char c;
        cin >> c;
        if (c == 'm')
        {
            user.mainPage();
        }
        else
        {
            showMenu();

        }
        break;
    }
    case 6:
    {
        user.ViewAllSent();

        cout << "to return back | Main Page | Press M \n";
        cout << "to return back | show Menu | Press S \n\n";
        char c;
        cin >> c;
        if (c == 'm')
            user.mainPage();
        else
            showMenu();
        break;
    }
    case 7:
    {
        ////////////// ER
        cout << "What is the name of the contact u wanna know read his messages :" << endl;
        string Name;
        cin >> Name;
        user.ViewFromSpeceific_Contact(Name);
        break;
    }
    case 8:
    {
        user.ViewForFav();
        int x;
        cout << "Enter Message no to add it to your Favourites : " << endl;
        cin >> x;
        user.AddToFav(x);

        cout << "\n";
        cout << "to return back | Main Page | Press M \n";
        cout << "to return back | show Menu | Press S \n\n";
        char c;
        cin >> c;
        if (c == 'm')
            user.mainPage();
        else
            showMenu();
        break;
    }
    case 9:
    {
        user.RemoveOldestFav();

        cout << "to return back | Main Page | Press M \n";
        cout << "to return back | show Menu | Press S \n\n";
        char c;
        cin >> c;
        if (c == 'm')
            user.mainPage();
        else
            showMenu();
        break;
    }
    case 10:
    {
        user.ViewAllFav();

        cout << "to return back | Main Page | Press M \n";
        cout << "to return back | show Menu | Press S \n\n";
        char c;
        cin >> c;
        if (c == 'm')
            user.mainPage();
        else
            showMenu();
        break;
    }
    case 11:
        user.viewAllusers();

        cout << "to return back | Main Page | Press M \n";
        cout << "to return back | show Menu | Press S \n\n";
        char c;
        cin >> c;
        if (c == 'm')
            user.mainPage();
        else
            showMenu();

        break;
    case 12:
    {
        string con, con1;
        cout << "Please Write The Content Of The Message :\n" << endl;
        getline(cin >> ws, con);
        msg.content = con;

        cout << "\n";

        cout << "Please Write The Name Who You Wanna Send A Message :\n" << endl;
        cin >> con1;
        msg.receiver = con1;

        cout << "\n";

        msg.sender = user.getCurrentUser().getID();
        user.SendMSG_Anonymus(msg);

        cout << "to return back | Main Page | Press M \n";
        cout << "to return back | show Menu | Press S \n\n";
        char c;
        cin >> c;
        if (c == 'm')
            user.mainPage();
        else
            showMenu();

        break;



    }
    }

}
