#include "user.h"

User::User()
    : username(""), password(""), admin(false) {}

User::User(const std::string& username, const std::string& password, bool admin)
    : username(username), password(password), admin(admin) {}

std::string User::getUsername() const
{
    return username;
}

void User::setUsername(const std::string& username)
{
    this->username = username;
}

std::string User::getPassword() const
{
    return password;
}

void User::setPassword(const std::string& password)
{
    this->password = password;
}

bool User::isAdmin() const
{
    return admin;
}

void User::setAdmin(bool admin)
{
    this->admin = admin;
}