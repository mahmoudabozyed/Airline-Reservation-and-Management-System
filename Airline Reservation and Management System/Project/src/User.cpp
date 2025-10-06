#include "User.hpp"
#include "Database.hpp"

void User::setPassword(const std::string& password) {
    this->password = password;
}

void User::setRole(const std::string& role) {
    this->role = role;
}
User::User(const std::string& uname, const std::string& pwd, const std::string& r)
    : username(uname), password(pwd), role(r) {}

bool User::authenticate() {
    return Database::validateUser(username, password);
}

std::string User::getUsername() const {
    return username;
}

std::string User::getPassword() const {
    return password;
}

std::string User::getRole() const {
    return role;
}