#ifndef USERDATABASE_INCLUDED
#define USERDATABASE_INCLUDED

#include <string>
#include <map>
#include "treemm.h"
#include <vector>

class User;


class UserDatabase
{
    public:
        UserDatabase();
        bool load(const std::string& filename);
        User* get_user_from_email(const std::string& email) const;
        ~UserDatabase();
    
    private: 
        
        std::vector<User*> m_users;
        TreeMultimap<std::string, User*> m_map;
};

#endif // USERDATABASE_INCLUDED
