 SELECT movie_id FROM stars JOIN people ON person_id = people.id WHERE people.name ="Kevin Bacon" AND people.birth = 1958;

 SELECT name FROM people WHERE id IN (SELECT person_id FROM stars WHERE movie_id IN (SELECT movie_id FROM stars JOIN people ON person_id = people.id WHERE people.name ="Kevin Bacon" AND people.birth = 1958));

 SELECT name FROM people JOIN stars ON id = stars.person_id WHERE movie_id IN (SELECT movie_id FROM people JOIN stars on id = stars.person_id WHERE name = "Kevin Bacon" AND birth = 1958);