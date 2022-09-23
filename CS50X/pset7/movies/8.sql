SELECT people.name
    FROM movies, people, stars
    WHERE movies.title = "Toy Story" AND
        movies.id = stars.movie_id AND
        stars.person_id = people.id