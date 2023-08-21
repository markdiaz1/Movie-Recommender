This project is a movie recommendation system created in C++. It creates a list of movie recommendations by looking through a given users watch history and calculating compatibility scores for potential movies.

It’s implemented using a Tree Multi-map to create a database of over 100k users and 20k movies. 

Compatibility Score Calculations:

1. Movies with common directors: 30 points
2. Movies with common actors: 20 points
3. Movies with common genres: 15 points


The process of generating the list of recommendations is as follows:

1. Generate a database of users and movies that allows for fast lookups based on keys like: actors, genres, etc.
2. Use a hash table to map a movie to its compatibility score, adding 30 points for common directors, 20 for actors, and 15 for genres
3. Sort the movies and recommendations in descending order and return the number of movie recommendations specified by the user
