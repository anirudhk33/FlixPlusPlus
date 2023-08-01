#include "Recommender.h"
#include "UserDatabase.h"
#include "User.h"
#include "Movie.h"
#include "MovieDatabase.h"

#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

Recommender::Recommender(const UserDatabase& user_database,
                         const MovieDatabase& movie_database): udb(user_database), mdb(movie_database)
{}

vector<MovieAndRank> Recommender::recommend_movies(const string& user_email, int movie_count) const
{
    if(movie_count<0) movie_count = 0;
    
    unordered_map<string, int> M_and_R_map;
    
    User* user = udb.get_user_from_email(user_email);
    if(user==nullptr) return vector<MovieAndRank>();
    
    vector<string> watch_history = user->get_watch_history();
    
    for (int i = 0; i < watch_history.size(); i++)      //Iterating over whole watch history
    {
        string m_ID = watch_history[i];
        Movie* m = mdb.get_movie_from_id(m_ID);
        const vector<string>& dirs = m->get_directors();
        const vector<string>& actors = m->get_actors();
        const vector<string>& genres = m->get_genres();
        
        // Directors:
        for (int j = 0; j < dirs.size(); j++) //Iterating over all directors
        {
            const vector<Movie*>& movies_of_dir = mdb.get_movies_with_director(dirs[j]);
            // For every director in this vector, we increase the compatibility score by 20;
            for (int k = 0; k < movies_of_dir.size(); k++)
            {
                string movie_id = movies_of_dir[k]->get_id();
                if (M_and_R_map.count(movie_id) > 0)
                {
                    M_and_R_map[movie_id] += 20;
                }
                else
                {
//                    MovieAndRank movie_and_rank(movie_id, 20);
                    M_and_R_map[movie_id] = 20;
//                    M_and_R_map.emplace(movie_id, movie_and_rank);
                }
            }
        }
        
        // Actors:
        for (int j = 0; j < actors.size(); j++) //Iterating over all actors
        {
            const vector<Movie*>& movies_of_actor = mdb.get_movies_with_actor(actors[j]);
            // For every actor in this vector, we increase the compatibility score by 30;
            for (int k = 0; k < movies_of_actor.size(); k++)
            {
                string movie_id = movies_of_actor[k]->get_id();
                if (M_and_R_map.count(movie_id) > 0)
                {
                    M_and_R_map[movie_id] += 30;
                }
                else
                {
//                    MovieAndRank movie_and_rank(movie_id, 30);
                    M_and_R_map[movie_id] = 30;
//                    M_and_R_map.emplace(movie_id, movie_and_rank);
                }
            }
        }
        
        // Genres:
        for (int j = 0; j < genres.size(); j++) //Iterating over all actors
        {
            const vector<Movie*>& movies_of_genre = mdb.get_movies_with_genre(genres[j]);
            // For every genre in this vector, we increase the compatibility score by 1;
            for (int k = 0; k < movies_of_genre.size(); k++)
            {
                string movie_id = movies_of_genre[k]->get_id();
                if (M_and_R_map.count(movie_id) > 0)
                {
                    M_and_R_map[movie_id] += 1;
                }
                else
                {
//                    MovieAndRank movie_and_rank(movie_id, 1);
                    M_and_R_map[movie_id] = 1;
//                    M_and_R_map.emplace(movie_id, movie_and_rank);
                }
            }
        }
        
        // Removing the movie if the user has already watched it
        if (M_and_R_map.count(watch_history[i]) > 0)
        {
            M_and_R_map.erase(watch_history[i]);
        }
    }
    
    // Converting unordered_map to vector of objects and sorting by compatibility_score(decreasing)
    vector<MovieAndRank> recommended_movies;
    
    for (auto it = M_and_R_map.begin(); it != M_and_R_map.end(); it++)
    {
        recommended_movies.emplace_back(MovieAndRank(it->first, it->second));
    }
    
    sort(recommended_movies.begin(), recommended_movies.end(), [this](const MovieAndRank &a, const MovieAndRank &b){
        if(a.compatibility_score != b.compatibility_score)
        {
            return a.compatibility_score > b.compatibility_score;
        }
        else
        {
            Movie* am = mdb.get_movie_from_id(a.movie_id);
            Movie* bm = mdb.get_movie_from_id(b.movie_id);
            if(am->get_rating() != bm->get_rating())
            {
                return am->get_rating() > bm->get_rating();
            }
            else
            {
                return am->get_title() < bm->get_title();
            }
        }

    }
);
    
    if (movie_count > recommended_movies.size())
    {
        movie_count = recommended_movies.size();
    }
    
    vector<MovieAndRank> final_recommendations(recommended_movies.begin(), recommended_movies.begin() + movie_count);
//
    return final_recommendations;
}
