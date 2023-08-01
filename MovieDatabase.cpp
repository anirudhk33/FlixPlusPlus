#include "MovieDatabase.h"
#include "Movie.h"
#include "treemm.h"

#include <string>
#include "fstream"
#include <iostream>
#include <sstream>
#include <vector>
#include <cctype>
using namespace std;

MovieDatabase::MovieDatabase():temp_count(0),loaded(false)
{}

MovieDatabase::~MovieDatabase()
{
//    Deleting every movie
    for(int i = 0; i<movie_ID_record.size(); i++)
    {
        string lower;
        for (char c : movie_ID_record[i])
        {
            lower += tolower(c);
        }
        TreeMultimap<string, Movie*>::Iterator itr = movie_ID_to_movie.find(lower);
        if(itr.is_valid())
        {
            delete itr.get_value();
        }
    }
}



bool MovieDatabase::load(const string& filename)
{
    if(loaded) return false;
    
    ifstream infile(filename);
    if (!infile )
    {
        return false;
    }
    loaded = true;
    
//    Logic: Keep reading in lines and everytime we reach an empty line, we create a movie, insert it into the treemm, and refresh the data-structures which save the movie-data.
    
    string line;
    while (getline(infile, line))
    {
        if(line.empty())
        {
            Movie* temp_movie = new Movie(temp_movie_ID,
                                          temp_movie_title,
                                          temp_movie_release_year,
                                          temp_movie_directors,
                                          temp_movie_actors,
                                          temp_movie_genres,
                                          temp_movie_rating);
//             We store keys in lower case for case insensitivity
            string lowerID;
            for (char c : temp_movie_ID)
            {
                lowerID += tolower(c);
            }

            movie_ID_to_movie.insert(lowerID, temp_movie);
            
            for(int i = 0; i<temp_movie_directors.size();i++)
            {
                string lower;
                for (char c : temp_movie_directors[i])
                {
                    lower += tolower(c);
                }
                director_to_movie.insert(lower, temp_movie);
            }
            
            for(int i = 0; i<temp_movie_genres.size();i++)
            {
                string lower;
                for (char c : temp_movie_genres[i])
                {
                    lower += tolower(c);
                }
                genre_to_movie.insert(lower, temp_movie);
            }
            
            for(int i = 0; i<temp_movie_actors.size();i++)
            {
                string lower;
                for (char c : temp_movie_actors[i])
                {
                    lower += tolower(c);
                }
                actor_to_movie.insert(lower, temp_movie);
            }

            temp_count = 0;
            temp_movie_directors.clear();
            temp_movie_actors.clear();
            temp_movie_genres.clear();
        }
        
        else if(temp_count == 0)
        {
            temp_movie_ID = line;
            movie_ID_record.push_back(line);
            temp_count++;
        }
        
        else if(temp_count == 1)
        {
            temp_movie_title = line;
            temp_count++;
        }
        
        else if(temp_count == 2)
        {
            temp_movie_release_year = line;
            temp_count++;
        }
        
        else if(temp_count == 3)
        {
            istringstream dir(line);
            string director;

            while (getline(dir, director, ',')) {
                temp_movie_directors.push_back(director);
            }
            temp_count++;
        }
        
        else if(temp_count==4)
        {
            istringstream act(line);
            string actor;

            while (getline(act, actor, ',')) {
                temp_movie_actors.push_back(actor);
            }
            temp_count++;
        }
        
        else if(temp_count==5)
        {
            istringstream gen(line);
            string genre;

            while (getline(gen, genre, ',')) {
                temp_movie_genres.push_back(genre);
            }
            temp_count++;
        }
        
        else if (temp_count==6)
        {
            temp_movie_rating = stof(line);
            temp_count++;
        }
        
    }
    
//    IN CASE THE LAST LINE OF THE FILE IS NOT AN EMPTY LINE, then this is executed.
    if(temp_count != 0)
    {
        Movie* temp_movie = new Movie(temp_movie_ID,
                                      temp_movie_title,
                                      temp_movie_release_year,
                                      temp_movie_directors,
                                      temp_movie_actors,
                                      temp_movie_genres,
                                      temp_movie_rating);
        movie_ID_to_movie.insert(temp_movie_ID, temp_movie);
        
        for(int i = 0; i<temp_movie_directors.size();i++)
        {
            director_to_movie.insert(temp_movie_directors[i], temp_movie);
        }
        for(int i = 0; i<temp_movie_actors.size();i++)
        {
            actor_to_movie.insert(temp_movie_actors[i], temp_movie);
        }
        for(int i = 0; i<temp_movie_genres.size();i++)
        {
            genre_to_movie.insert(temp_movie_genres[i], temp_movie);
        }
        temp_count = 0;
        temp_movie_directors.clear();
        temp_movie_actors.clear();
        temp_movie_genres.clear();
    }
    
    return true;
}

Movie* MovieDatabase::get_movie_from_id(const string& id) const
{
    string lower;
    for (char c : id)
    {
        lower += tolower(c);
    }
    TreeMultimap<string, Movie*>::Iterator itr = movie_ID_to_movie.find(lower);
    return itr.is_valid()? itr.get_value() : nullptr;
}

vector<Movie*> MovieDatabase::get_movies_with_director(const string& director) const
{
    string lower;
    for (char c : director)
    {
        lower += tolower(c);
    }
    vector<Movie*> movies;
    TreeMultimap<string, Movie*>::Iterator itr = director_to_movie.find(lower);
    while(itr.is_valid()){
        movies.push_back(itr.get_value());
        itr.advance();
    }
    return movies;
}

vector<Movie*> MovieDatabase::get_movies_with_actor(const string& actor) const
{
    string lower;
    for (char c : actor)
    {
        lower += tolower(c);
    }
    vector<Movie*> movies;
    TreeMultimap<string, Movie*>::Iterator itr = actor_to_movie.find(lower);
    while(itr.is_valid()){
        movies.push_back(itr.get_value());
        itr.advance();
    }
    return movies;
}

vector<Movie*> MovieDatabase::get_movies_with_genre(const string& genre) const
{
    string lower;
    for (char c : genre)
    {
        lower += tolower(c);
    }
    vector<Movie*> movies;
    TreeMultimap<string, Movie*>::Iterator itr = genre_to_movie.find(lower);
    while(itr.is_valid()){
        movies.push_back(itr.get_value());
        itr.advance();
    }
    return movies;
}
