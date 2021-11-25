SELECT people.name FROM people
JOIN stars ON stars.person_id = people.id
WHERE stars.movie_id IN (
	SELECT stars.movie_id FROM stars
	JOIN people ON stars.person_id = people.id
	WHERE people.name = 'Kevin Bacon'
	AND people.birth = 1958 )
AND people.id NOT IN (
	SELECT people.id FROM people
	WHERE name = 'Kevin Bacon'
	AND people.birth = 1958 );
