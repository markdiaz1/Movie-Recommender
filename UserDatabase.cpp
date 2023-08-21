#include "UserDatabase.h"
#include "User.h"

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;

UserDatabase::UserDatabase()
{}

bool UserDatabase::load(const string& filename) // processes txt file
{
    ifstream infile(filename);
    if (!infile)
    {
        cerr << "Error opening file " << filename << endl;
        return false;
    }
    
    string name;
    string email;
    vector<string> movieHistory;
    
    string line;
    while (getline(infile, line))
    {
        
        name = line; // first line is always name
                
        getline(infile, line);
        email = line;
        
        
        getline(infile, line);
    
        int num_ids = 0;
        
        if(!line.empty()) // if the line isn't empty you have the number of ID's that are going to come
        {
            num_ids = stoi(line); //string to int
        }
        

        for (int i = 0; i < num_ids; i++) // constant time so it doesn't matter too much
        {
            getline(infile, line);
            movieHistory.push_back(line);
        }
        
        User* temp = new User(name, email, movieHistory);
        
    
        m_map.insert(email, temp);
        m_users.push_back(temp);
        
        // Clear the movieHistory vector for the next user
        movieHistory.clear();
        
        getline(infile, line); // new line

    }
    
    return true;
}


//IF YOU CALL THIS FUNCTION MAKE SURE TO DELETE WHAT IT RETURNS

User* UserDatabase::get_user_from_email(const string& email) const
{
    if(m_map.find(email).is_valid()) //if it doesn't exist return a nullptr
    {
        return m_map.find(email).get_value();
    }
    return nullptr;
}

UserDatabase::~UserDatabase()
{
    std::vector<User*>::iterator it = m_users.begin(); //loop through vector to destroy dynamically allocated objects
    
    for(; it != m_users.end(); it++)
    {
        delete (*it);
    }
}

