#include "Recommender.h"
#include "UserDatabase.h"
#include "MovieDatabase.h"
#include "User.h"
#include "Movie.h"
#include <unordered_map>

#include <string>
#include <vector>
#include <algorithm>
using namespace std;


Recommender::Recommender(const UserDatabase& user_database, const MovieDatabase& movie_database)
:m_udb(user_database), m_mdb(movie_database)
{}

Recommender::~Recommender(){}

vector<MovieAndRank> Recommender::recommend_movies(const string& user_email, int movie_count) const
{
    unordered_map<string, int> map;
    
    vector<MovieAndRank> movieRecs;
    
    User* user = m_udb.get_user_from_email(user_email);
    if (user == nullptr)
        return vector<MovieAndRank>();
    
    vector<string> watchHistory = user->get_watch_history();
    
    for(int i = 0; i < watchHistory.size(); i++) // for every movie in their watch history
    {
        Movie* movie = m_mdb.get_movie_from_id(watchHistory.at(i));
        
        vector<string> directors = movie->get_directors();
        for(int j = 0; j < directors.size(); j++) //find every director in one of their movies in their watch history
        {
            vector<Movie*> movies_with_dir = m_mdb.get_movies_with_director(directors.at(j));
            for(int k = 0; k < movies_with_dir.size(); k++) // insert those movies with that director
            {
                string id = movies_with_dir.at(k)->get_id();
                map[id] += 20;
            }
        }
        
        vector<string> actors = movie->get_actors();
        for(int j = 0; j < actors.size(); j++) //find every actor in one of their movies in their watch history
        {
            vector<Movie*> movies_with_actor = m_mdb.get_movies_with_actor(actors.at(j));
            for(int k = 0; k < movies_with_actor.size(); k++) // insert those movies with that actor
            {
                string id = movies_with_actor.at(k)->get_id();
                map[id] += 30;
            }
        }
        
        vector<string> genres = movie->get_genres();
        for(int j = 0; j < genres.size(); j++) // find every genre in one of their movies in their watch history
        {
            vector<Movie*> movies_with_genre = m_mdb.get_movies_with_genre(genres.at(j));
            for(int k = 0; k < movies_with_genre.size(); k++) //insert those movies with those genres
            {
                string id = movies_with_genre.at(k)->get_id();
                map[id] += 1;
            }
        }
        
    }

    //Delete all the movies they have already watched
    for(int i = 0; i < watchHistory.size(); i++)
    {
        map.erase(watchHistory.at(i));
    }

    // converting the map back into a vector
    for(auto it = map.begin(); it != map.end(); it++)
    {
        movieRecs.push_back(MovieAndRank(it->first, it->second));
    }
    
    //using the sorting function I created to sort the movie and rank scores
    sort(movieRecs.begin(), movieRecs.end(), compareMovieAndRankScore());
    
    
    if(movie_count < movieRecs.size()) //if the movie count is less than the recs
    {
        return vector<MovieAndRank>(movieRecs.begin(), movieRecs.begin() + movie_count); //return the amount of movies of movie_count
    }

    return movieRecs;  // return the recs
    
}