SELECT movies.title
    FROM movies, ratings, people, stars
    WHERE people.name = "Chadwick Boseman" AND
        people.id = stars.person_id  AND
        stars.movie_id = movies.id AND
        ratings.movie_id = movies.id
    ORDER BY ratings.rating DESC, movies.title ASC
    LIMIT 5