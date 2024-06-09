#ifndef USER_H
#define USER_H

#include <string>

class User {
private:
    std::string username;
    std::string password;
    bool admin;
public:
    User();
    User(const std::string& username, const std::string& password, bool admin);
    std::string getUsername() const;
    void setUsername(const std::string& username);
    std::string getPassword() const;
    void setPassword(const std::string& password);
    bool isAdmin() const;
    void setAdmin(bool admin);
};

#endif