#include "Movie.h"

#include <string>
#include <vector>
using namespace std;

//Such simple code requires no comments...

Movie::Movie(const string& id, const string& title, const string& release_year,
             const vector<string>& directors, const vector<string>& actors,
             const vector<string>& genres, float rating):movie_ID(id), movie_title(title), movie_release_year(release_year), movie_directors(directors), movie_actors(actors), movie_genres(genres), movie_rating(rating){}

string Movie::get_id() const
{
    return movie_ID;
}

string Movie::get_title() const
{
    return movie_title;
}

string Movie::get_release_year() const
{
    return movie_release_year;
}

float Movie::get_rating() const
{
    return movie_rating;
}

vector<string> Movie::get_directors() const
{
    return movie_directors;
}

vector<string> Movie::get_actors() const
{
    return movie_actors;
}

vector<string> Movie::get_genres() const
{
    return movie_genres;
}
