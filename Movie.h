#ifndef MOVIE_INCLUDED
#define MOVIE_INCLUDED

#include <string>
#include <vector>

class Movie
{
  public:
    Movie(const std::string& id, const std::string& title,
          const std::string& release_year,
          const std::vector<std::string>& directors,
          const std::vector<std::string>& actors,
          const std::vector<std::string>& genres, float rating);
    std::string get_id() const;
    std::string get_title() const;
    std::string get_release_year() const;
    float get_rating() const;
    std::vector<std::string> get_directors() const;
    std::vector<std::string> get_actors() const;
    std::vector<std::string> get_genres() const;

  private:
    std::string movie_ID;
    std::string movie_title;
    std::string movie_release_year;
    std::vector<std::string> movie_directors;
    std::vector<std::string> movie_actors;
    std::vector<std::string> movie_genres;
    float movie_rating;
};

#endif // MOVIE_INCLUDED
