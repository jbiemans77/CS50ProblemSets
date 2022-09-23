SELECT DISTINCT people.name
    FROM people, movies, stars
    WHERE
    movies.id IN (SELECT movies.id
        FROM movies, people, stars
        WHERE people.name = "Kevin Bacon" AND
            birth = '1958' AND
            stars.movie_id = movies.id AND
            stars.person_id = people.id)
    AND
    stars.movie_id = movies.id AND
    stars.person_id = people.id AND
    NOT(people.name = "Kevin Bacon" AND people.birth = '1958')