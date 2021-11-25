SELECT DISTINCT(people.name) FROM directors
JOIN people on people.id = directors.person_id
JOIN movies ON movies.id = directors.movie_id
JOIN ratings ON movies.id = ratings.movie_id
WHERE ratings.rating >= 9.0;
