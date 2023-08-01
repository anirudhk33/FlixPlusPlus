#include "User.h"

#include <string>
#include <vector>
using namespace std;

User::User(const string& full_name, const string& email,
           const vector<string>& watch_history) : user_name(full_name), user_email(email), user_watch_history(watch_history)
{}

string User::get_full_name() const
{
    return user_name;  // Replaced this line with correct code.
}

string User::get_email() const
{
    return user_email;  // Replaced this line with correct code.
}

vector<string> User::get_watch_history() const
{
    return user_watch_history;  // Replaced this line with correct code.
}
