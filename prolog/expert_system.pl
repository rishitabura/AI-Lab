% Facts
movie(the_shawshank_redemption, drama).
movie(the_godfather, drama).
movie(the_dark_knight, action).
movie(inception, action).
movie(fight_club, drama).
movie(forrest_gump, drama).
movie(pulp_fiction, drama).
movie(the_matrix, action).

% Rules
belongs_to_genre(Movie, Genre) :-
    movie(Movie, Genre).

recommend_movie_action(Movie) :-
    belongs_to_genre(Movie, action).

recommend_movie_drama(Movie) :-
    belongs_to_genre(Movie, drama).

% Predicate to recommend movies
recommend_movies(Preference) :-
    (Preference == action -> write('Action movies: '), findall(Movie, recommend_movie_action(Movie), ActionMovies), write(ActionMovies), nl ;
    Preference == drama -> write('Drama movies: '), findall(Movie, recommend_movie_drama(Movie), DramaMovies), write(DramaMovies), nl ;
    write('Invalid preference')).

