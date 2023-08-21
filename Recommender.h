#ifndef RECOMMENDER_INCLUDED
#define RECOMMENDER_INCLUDED

#include <string>
#include <vector>
#include "UserDatabase.h"
#include "MovieDatabase.h"
#include "Movie.h"

class Movie;
class UserDatabase;
class MovieDatabase;


struct MovieAndRank // an additional struct to contain the movie ID along with its compatability score
{
    MovieAndRank(const std::string& id, int score)
     : movie_id(id), compatibility_score(score)
    {}

    std::string movie_id;
    int compatibility_score;
};

class Recommender
{
    public:
        Recommender(const UserDatabase& user_database, const MovieDatabase& movie_database);
        ~Recommender();
        std::vector<MovieAndRank> recommend_movies(const std::string& user_email, int movie_count) const;

    private:
    
        const UserDatabase& m_udb;
        const MovieDatabase& m_mdb;

    
    
    //lambda function in order to compare movieAndRank objects
    auto compareMovieAndRankScore() const
    {
        return [this](MovieAndRank& left, MovieAndRank& right)
        {
            if(left.compatibility_score > right.compatibility_score) // left comp score > right comp score
                return true;
            else if(left.compatibility_score < right.compatibility_score)
                return false;
            else // they have same comp score
            {
                if(m_mdb.get_movie_from_id(left.movie_id)->get_rating() > m_mdb.get_movie_from_id(right.movie_id)->get_rating()) //comp ratings
                    return true;
                else if(m_mdb.get_movie_from_id(left.movie_id)->get_rating() < m_mdb.get_movie_from_id(right.movie_id)->get_rating())
                    return false;
                else // rating are the same
                {
                    if(m_mdb.get_movie_from_id(left.movie_id)->get_title() < m_mdb.get_movie_from_id(right.movie_id)->get_title()) // comp title names
                        return true;
                    else
                        return false;
                }
            }
            
        };
    }
};

#endif // RECOMMENDER_INCLUDED
