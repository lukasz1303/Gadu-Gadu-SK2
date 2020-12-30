#ifndef USER_H
#define USER_H


class User
{
private:
    static User *instance;
    int numberGG;

    User();

public:
    static User *getInstance();
    int getNumberGG();
    void setNumberGG(int number);
};
#endif // USER_H
