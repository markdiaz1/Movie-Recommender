#include "UserDatabase.h"
#include "User.h"
#include "Movie.h"
#include "MovieDatabase.h"
#include <iostream>
#include <string>
#include "Recommender.h"
using namespace std;

// This main file serves as a driver for the movie recommnedation system
// implemented using a Tree Multi Map that maps different keys to the same values
// e.g. Both actors Robert Downey Jr and Chris Evans map to Avengers: Endgame


const string USER_DATAFILE  = "users.txt";
const string MOVIE_DATAFILE = "movies.txt";

void findMatches(const Recommender& r,
                 const MovieDatabase& md,
                 const string& user_email,
                 int num_recommendations)
{
    // Generates 10 movie recommendations for the user

    vector<MovieAndRank> recommendations = r.recommend_movies(user_email, 10);
    
    if (recommendations.empty())
        cout << "We found no movies to recommend :(.\n";
    else
    {
        for (int i = 0; i < recommendations.size(); i++)
        {
            const MovieAndRank& mr = recommendations[i];
            Movie* m = md.get_movie_from_id(mr.movie_id);
            cout << i + 1 << ". " << m->get_title() << " ("
            << m->get_release_year() << ")\n Rating: "
            << m->get_rating() << "\n Compatibility Score: "
            << mr.compatibility_score << "\n";
        }
    }
}


int main()
{
    UserDatabase udb; // Creates a user data base by parsing through a text file of over 100K users with a unique watch history
    if (!udb.load(USER_DATAFILE))  
    {
        cout << "Failed to load user data file " << USER_DATAFILE << "!" << endl;
        return 1;
    }
    
    MovieDatabase mdb; // Creates a movie data base by parsing through a text file of over 20k movies
    if (!mdb.load(MOVIE_DATAFILE))  
    {
        cout << "Failed to load user data file " << MOVIE_DATAFILE << "!" << endl;
        return 1;
    }

    while(true)
    {
        cout << "What do you want to test? (or say quit) Say: user, id, director, actor, genre or recs: ";
        string answer;
        getline(cin, answer);
        
        if (answer == "quit")
            return 0;
        
        if (answer == "user") // outputs a users watch history from the user database
        {
            cout << "Enter user email address (or quit): ";
            string email;
            getline(cin, email);
            if (email == "quit")
                return 0;
            User* u = udb.get_user_from_email(email);
            if (u == nullptr)
                cout << "No user in the database has that email address." << endl;
            else
            {
                cout << "Found " << u->get_full_name() << endl;
                vector<string> watch_history = u->get_watch_history();
                for(int i = 0 ; i < watch_history.size(); i++)
                {
                    cout << watch_history[i] << endl;
                }
            }
        }
        
        if (answer == "id") // outputs a movie from the movie database 
        {
            cout << "Enter 7 character movie id (or quit): ";
            string id;
            getline(cin, id);
            if (id == "quit")
                return 0;
            Movie* m = mdb.get_movie_from_id(id);
            if (m == nullptr)
                cout << "No movie in the database has that this movie ID." << endl;
            else
                cout << "Found " << m->get_title() << endl;
        }
        
        if (answer == "director") // searches a movies by director
        {
            cout << "Enter a director (or quit): ";
            string director;
            getline(cin, director);
            if (director == "quit")
                return 0;
            vector<Movie*> result = mdb.get_movies_with_director(director);
            if (result.size()==0)
                cout << "No movies in the database has that this director." << endl;
            else
            {
                for (int i = 0; i < result.size(); i++)
                    cout <<result[i]->get_title()<< endl;
            }
        }
        
        if (answer == "actor") // searches movies by actors
        {
            cout << "Enter a actor (or quit): ";
            string actor;
            getline(cin, actor);
            if (actor == "quit")
                return 0;
            vector<Movie*> result = mdb.get_movies_with_actor(actor);
            if (result.size()==0)
                cout << "No movies in the database has that this actor." << endl;
            else
            {
                for (int i = 0; i < result.size(); i++)
                    cout <<result[i]->get_title()<< endl;
            }
        }
        
        if (answer == "genre") // searches movies by genre
        {
            cout << "Enter a genre (or quit): ";
            string genre;
            getline(cin, genre);
            if (genre == "quit")
                return 0;
            vector<Movie*> result = mdb.get_movies_with_genre(genre);
            if (result.size()==0)
                cout << "No movies in the database has that this genre." << endl;
            else
            {
                for (int i = 0; i < result.size(); i++)
                    cout << result[i]->get_title()<< endl;
            }
        }
        if (answer == "recs") // creates a recommendation for a user
        {
            cout << "Enter a user for recs (or quit): ";
            string user;
            getline(cin, user);
            if (user == "quit")
                return 0;
            
            Recommender name(udb, mdb);
            findMatches(name, mdb, user, 10);
        }
        
    }
}