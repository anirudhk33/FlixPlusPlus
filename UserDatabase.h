#ifndef USERDATABASE_INCLUDED
#define USERDATABASE_INCLUDED

#include "treemm.h"
#include <string>
#include <vector>

class User;

class UserDatabase
{
  public:
    UserDatabase();
    ~UserDatabase(); //CHECK IF WE CAN PUBLIC THIS
    bool load(const std::string& filename);
    User* get_user_from_email(const std::string& email) const;

  private:
    TreeMultimap<std::string, User*> user_database;
    int temp_count;     //Temp variables assist storing data while parsing it from the file
    std::string temp_name;
    std::string temp_email;
    std::vector<std::string> temp_movie_history;
    std::vector<std::string> email_record;      //Helps store emails for deletion with destructor
    bool loaded;
};

#endif // USERDATABASE_INCLUDED
