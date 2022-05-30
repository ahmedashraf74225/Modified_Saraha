
#ifndef DEADLINE_MESSAGES_H
#define DEADLINE_MESSAGES_H

#ifndef MESSAGES_H
#define MESSAGES_H
#include<iostream>
using namespace std;


class Messages
{
public:

    string content;
    string sender;
    string receiver;
    bool Fav = false;

    virtual ~Messages();

protected:

private:
};

#endif // MESSAGES_H



#endif //DEADLINE_MESSAGES_H
