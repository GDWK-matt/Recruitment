#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include <iomanip>
#include<stdlib.h>

class User {
public:
    std::string login;
    std::string password;
    bool isAdmin;

    User(const std::string& l, const std::string& p, bool admin)
        : login(l), password(p), isAdmin(admin) {
    }
};

class AuthSystem {
public:
    std::vector<User> users;
    const std::string userFile = "users.txt";//
    void ensureFileExists();//
    void loadUsers();//
    void saveUsers();//
    bool checkAuth(const std::string& login, const std::string& password, bool& isAdmin);//
    bool addUser(const std::string& login, const std::string& password, bool isAdmin);//
    bool removeUser(const std::string& login);//
    void showAllUsers();//
};

