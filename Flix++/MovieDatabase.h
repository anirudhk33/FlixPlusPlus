#ifndef MOVIEDATABASE_INCLUDED
#define MOVIEDATABASE_INCLUDED

#include <string>
#include <vector>
#include "treemm.h"

class Movie;

class MovieDatabase
{
  public:
    MovieDatabase();
    ~MovieDatabase();
    bool load(const std::string& filename);
    Movie* get_movie_from_id(const std::string& id) const;
    std::vector<Movie*> get_movies_with_director(const std::string& director) const;
    std::vector<Movie*> get_movies_with_actor(const std::string& actor) const;
    std::vector<Movie*> get_movies_with_genre(const std::string& genre) const;
    
  private:
    bool loaded;    //To prevent multiple loads
    TreeMultimap<std::string, Movie*> movie_ID_to_movie;
    TreeMultimap<std::string, Movie*> director_to_movie;
    TreeMultimap<std::string, Movie*> actor_to_movie;
    TreeMultimap<std::string, Movie*> genre_to_movie;
    int temp_count;         //To mark every line of the datafile while parsing
    std::string temp_movie_ID;
    std::string temp_movie_title;
    std::string temp_movie_release_year;
    std::vector<std::string> temp_movie_directors; //All temp variables help temporarily store data
    std::vector<std::string> temp_movie_actors;    //for each movie in the datafile
    std::vector<std::string> temp_movie_genres;
    float temp_movie_rating;
    std::vector<std::string> movie_ID_record;   //Saved records used to delete Movies in destructor
};

#endif // MOVIEDATABASE_INCLUDED
