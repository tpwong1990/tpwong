SELECT DISTINCT(name) FROM people
WHERE id IN (SELECT person_id FROM directors where person_id IN (SELECT movie_id FROM ratings WHERE rating >= 9.0));