# Flix++
Flix++ is a C++ based app which offers personalized movie recommendations based on the viewing history of 100,000+ users and 20,000+ films. The app's database has been designed from scratch and enables speedy data loading and retrieval. This is a modified version of a class project for CS 32 (Data Structures & Algorithms) at UCLA. 

### Key Features
* User Profiles: Each user has a unique profile containing their full name, email, and a history of watched movies.
* UserDatabase: The UserDatabase class efficiently stores and manages user profiles, enabling quick retrieval based on email addresses. Over 100,000+ user profiles are handled by this database.
* Movie Details: Every movie is represented by the Movie class, which stores information such as the title, release year, director(s), actor(s), genre(s), and rating.
* MovieDatabase: The MovieDatabase class organizes the vast collection of 20,000+ movies, supporting searches by unique ID, director(s), actor(s), and genre(s).
* Personalized Recommendations: The Recommender class generates rank-ordered movie recommendations for a given user. It analyzes a user's watch history and suggests movies with the most common attributes.

### Algorithms Implemented
* **Collaborative filtering:** Collaborative filtering suggests movies by identifying similar users (user-based) or similar movies (item-based) based on past user interactions and ratings, providing recommendations based on collective user behavior.
* **Content-based filtering:** Content-based filtering recommends movies based on their attributes, such as genre, actors, and directors, matching them to a user's previous preferences for similar movies.
* **Database Design and handling**: I implemented a _TreeMultimap class_ from scratch involving the use of a binary search tree-based map. It ensures the efficient storage and retrieval of various data types.

