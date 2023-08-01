#include "UserDatabase.h"
#include "User.h"

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;

UserDatabase::UserDatabase():temp_name(""),temp_count(0),temp_email(""), loaded(false)
{}

UserDatabase::~UserDatabase()
{
    for(int i = 0; i<email_record.size(); i++)
    {
        TreeMultimap<string, User*>::Iterator itr = user_database.find(email_record[i]);
        if(itr.is_valid())
        {
            delete itr.get_value();
        }
    }
}

 //Exact same parsing logic used as MovieDatabase
bool UserDatabase::load(const string& filename)
{
    if(loaded) return false;
    
    ifstream infile(filename);
    if (!infile )
    {
        return false;
    }
    
    loaded = true;
    std::string line;
    while (getline(infile, line))
    {
        if(line.empty())
        {
            User* temp_user = new User(temp_name, temp_email, temp_movie_history);
            user_database.insert(temp_email, temp_user);
            temp_count = 0;
            temp_movie_history.clear();
        }
        
        else if(temp_count == 0)
        {
            temp_name = line;
            temp_count++;
        }
        
        else if(temp_count == 1)
        {
            temp_email = line;
            email_record.push_back(temp_email);
            temp_count++;
        }
        
        else if(temp_count==2)
        {
            temp_count++;
        }
        
        else if(temp_count>2)
        {
            temp_movie_history.push_back(line);
            temp_count++;
        }
    }
    
//    IN CASE THE LAST LINE OF THE FILE IS NOT AN EMPTY LINE, then this is executed.
    
    if(temp_count != 0)
    {
        User* temp_user = new User(temp_name, temp_email, temp_movie_history);
        user_database.insert(temp_email, temp_user);
        temp_count = 0;
    }
    return true;
}

User* UserDatabase::get_user_from_email(const string& email) const
{
    TreeMultimap<string, User*>::Iterator itr = user_database.find(email);
    return itr.is_valid()? itr.get_value() : nullptr;
}
