#ifndef USER_HPP
#define USER_HPP

#include <string>

class User {
protected:
    std::string username;
    std::string password;
    std::string role;

public:
    User(const std::string& uname, const std::string& pwd, const std::string& r);
    virtual ~User() = default;

    virtual void displayMenu() = 0; 
    void setPassword(const std::string& pwd);
    void setRole(const std::string& role);

    bool authenticate();
    std::string getUsername() const;
    std::string getPassword() const;
    std::string getRole() const;
};

#endif 