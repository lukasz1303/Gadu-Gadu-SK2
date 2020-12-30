#include "user.h"

User *User::instance=0;
User::User()
{
    numberGG=0;
}

User *User::getInstance()
{
    if(!instance){
        instance = new User();
    }
    return instance;
}

int User::getNumberGG()
{
    return numberGG;
}

void User::setNumberGG(int number)
{
    numberGG = number;
}
