#include "MovieDatabase.h"
#include "Movie.h"

#include <string>
#include <vector>
#include <fstream>
#include <iostream>

using namespace std;

//Function to process the string of directors separated by commas

vector<string> commaSplicer(string input)
{
    vector<string> vec;
    size_t pos = 0; // input.find() returns an unsigned long
    string temp;

    while ((pos = input.find(",")) != string::npos) // until it finds commas
    {
        temp = input.substr(0, pos);
        vec.push_back(temp);
        input.erase(0, pos + 1);
    }

    vec.push_back(input); // Push the last substring after the last delimiter
    return vec;
}


MovieDatabase::MovieDatabase()
{}


bool MovieDatabase::load(const string& filename)
{
    ifstream infile(filename);
    if (!infile)
    {
        cerr << "Error opening file " << filename << endl;
        return false;
    }
    
    //all necessary temps
    string movieID;
    string name;
    string year;
    
    string directorsStr;
    vector <string> directors;
    
    string actorsStr;
    vector <string> actors;
    
    string genreStr;
    vector <string> genre;
    
    string ratingStr;
    float rating = 0;
    string line;
    
    while (getline(infile, line))
    {
        
        movieID = line;
        
        getline(infile, line);
        name = line;
        
        getline(infile, line);
        year = line;
        
        getline(infile, line);
        directorsStr = line;
        
        getline(infile, line);
        actorsStr = line;
        
        getline(infile, line);
        genreStr = line;
        
        getline(infile, line);
        ratingStr = line;
        
        //Case insensitive keys
        string upperID;
        for(int i = 0; i < movieID.size(); i++)
        {
            upperID += toupper(movieID.at(i));
        }
        
        string upperDir;
        for(int i = 0; i < directorsStr.size(); i++)
        {
            upperDir += toupper(directorsStr.at(i));
        }
        
        string upperActors;
        for(int i = 0; i < actorsStr.size(); i++)
        {
            upperActors += toupper(actorsStr.at(i));
        }
        
        string upperGenre;
        for(int i = 0; i < genreStr.size(); i++)
        {
            upperGenre += toupper(genreStr.at(i));
        }

        //calls commasplicer function
        directors = commaSplicer(upperDir);
        
        actors = commaSplicer(upperActors);
        
        genre = commaSplicer(upperGenre);
        
        
        if(!line.empty())
        {
            rating = stof(line); //string to float
        }
        
        Movie* temp = new Movie(movieID, name, year, directors, actors, genre, rating);
            
        m_movies.push_back(temp); // push back into vector
        
        m_mapID.insert(upperID, temp); //into map
        
        //Insert all of the keys in to the map with the temp movie
        for(int i = 0; i < directors.size(); i++)
        {
            m_mapDir.insert(directors[i], temp);
        }
        
        for(int i = 0; i < actors.size(); i++)
        {
            m_mapActor.insert(actors[i], temp);
        }
        
        for(int i = 0; i < genre.size(); i++)
        {
            m_mapGenre.insert(genre[i], temp);
        }
        
        //new movie
        getline(infile, line);
    }
    
    return true;
}

Movie* MovieDatabase::get_movie_from_id(const string& id) const
{
    //case insensity keys
    string upperID;
    for(int i = 0; i < id.size(); i++)
    {
        upperID += toupper(id.at(i));
    }
    
    TreeMultimap<string, Movie*>::Iterator it = m_mapID.find(upperID);
    
    if(it.is_valid())
    {
        return it.get_value();
    }
    
    return nullptr; // not found
}

vector<Movie*> MovieDatabase::get_movies_with_director(const string& director) const
{
    vector<Movie*> temp;

    //case insensitive keys
    string upperDir;
    for(int i = 0; i < director.size(); i++)
    {
        upperDir += toupper(director.at(i));
    }
        
    TreeMultimap<string, Movie*>::Iterator it = m_mapDir.find(upperDir);
    
    while(it.is_valid())
    {
        temp.push_back(it.get_value());
        it.advance();
    }
    
    return temp;  // empty vector if not found
}

vector<Movie*> MovieDatabase::get_movies_with_actor(const string& actor) const
{
    vector<Movie*> temp;
    
    //case insensitive keys
    string upperActor;
    for(int i = 0; i < actor.size(); i++)
    {
        upperActor += toupper(actor.at(i));
    }

    TreeMultimap<string, Movie*>::Iterator it = m_mapActor.find(upperActor);
    
    while(it.is_valid())
    {
        temp.push_back(it.get_value());
        it.advance();
    }
    
    return temp;  // empty vector if not found
}

vector<Movie*> MovieDatabase::get_movies_with_genre(const string& genre) const
{
    vector<Movie*> temp;

    //case insensitive keys
    string upperGenre;
    for(int i = 0; i < genre.size(); i++)
    {
        upperGenre += toupper(genre.at(i));
    }

    TreeMultimap<string, Movie*>::Iterator it = m_mapGenre.find(upperGenre);

    while(it.is_valid())
    {
        temp.push_back(it.get_value());
        it.advance();
    }
    

    return temp;  // empty vector if not found
}


MovieDatabase::~MovieDatabase()
{
    //loop through vector to destroy movies
    for(auto it = m_movies.begin(); it != m_movies.end(); it++)
    {
        delete (*it);
    }
}
