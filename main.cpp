#include "UserDatabase.h"
#include "MovieDatabase.h"
#include "User.h"
#include "Movie.h"
#include <chrono>
#include <iostream>
#include <vector>
#include <string>
#include "Recommender.h"
using namespace std;

//////////////////////////i/////////////////////////////////////////////////////
//
// You are free to do whatever you want with this file, since you won't
// be turning it in.  Presumably, you will make changes to help you test
// your classes.  For example, you might try to implement only some User
// member functions to start out with, and so replace our main routine with
// one that simply creates a User and verifies that the member functions you
// implemented work correctly.
//
//////////////////////////i/////////////////////////////////////////////////////


  // If your program is having trouble finding these files. replace the
  // string literals with full path names to the files.  Also, for test
  // purposes, you may want to create some small, simple user and movie
  // data files to makde debuggiing easier, so you can replace the string
  // literals with the names of those smaller files.

const string USER_DATAFILE  = "/Users/anirudhkrishna/Downloads/Pnetphlix/users.txt";
const string MOVIE_DATAFILE = "/Users/anirudhkrishna/Downloads/Pnetphlix/movies.txt";

//const string USER_DATAFILE  = "users.txt";
//const string MOVIE_DATAFILE = "movies.txt";


void findMatches(const Recommender& r, const MovieDatabase& md, const string& user_email, int num_recommendations){
    vector<MovieAndRank> recommendations = r.recommend_movies(user_email, num_recommendations);
    if(recommendations.empty()) cout<< "No Movies Recommended" <<endl;
    else
    {
        for(int i = 0; i < recommendations.size(); i++)
        {
            const MovieAndRank& mr = recommendations[i];
            Movie* m = md.get_movie_from_id(mr.movie_id);
            cout << i << ". " << m->get_title() << " ("
            << m->get_release_year() << ")\n Rating: "
            << m->get_rating() << "\n Compatibility Score: "
            << mr.compatibility_score << "\n";
        }
    }
    
}


int main()
{
	MovieDatabase mdb;
    UserDatabase udb;
    
    auto start1 = chrono::steady_clock::now();
    udb.load(USER_DATAFILE); // In skeleton, load always return false
    auto stop1 = chrono::steady_clock::now();
        
    auto start2 = chrono::steady_clock::now();
    mdb.load(MOVIE_DATAFILE);  // In skeleton, load always return false
    auto stop2 = chrono::steady_clock::now();

    
    cout << "Loading UserDB Took " << (chrono::duration_cast<chrono::milliseconds>(stop1 - start1).count()) << "ms" << endl;
    cout << "Loading MovieDB Took " << (chrono::duration_cast<chrono::milliseconds>(stop2 - start2).count()) << "ms" << endl;
    
    auto start3 = chrono::steady_clock::now();
    Recommender r(udb, mdb);
    findMatches(r, mdb, "indeevar@hotmail.com", 20);
    auto stop3 = chrono::steady_clock::now();
    
    cout << "Recommending Took " << (chrono::duration_cast<chrono::milliseconds>(stop3 - start3).count()) << "ms" << endl;
    
}
