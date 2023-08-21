#ifndef MOVIEDATABASE_INCLUDED
#define MOVIEDATABASE_INCLUDED

#include <string>
#include <vector>
#include <map>
#include "treemm.h"

class Movie;

class MovieDatabase
{
    public:
        MovieDatabase();
        bool load(const std::string& filename);
        Movie* get_movie_from_id(const std::string& id) const;
    
        std::vector<Movie*> get_movies_with_director(const std::string& director) const;
        std::vector<Movie*> get_movies_with_actor(const std::string& actor) const;
        std::vector<Movie*> get_movies_with_genre(const std::string& genre) const;
        ~MovieDatabase();

    private:
        std::vector<Movie*> m_movies;
        TreeMultimap<std::string, Movie*> m_mapID;
        TreeMultimap<std::string, Movie*> m_mapDir;
        TreeMultimap<std::string, Movie*> m_mapActor;
        TreeMultimap<std::string, Movie*> m_mapGenre;

};

std::vector<std::string> commaSplicer(std::string input);

#endif // MOVIEDATABASE_INCLUDED
