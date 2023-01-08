SELECT id FROM people WHERE name = "Johnny Depp";
SELECT id FROM people WHERE name = "Helena Bonham Carter";
SElECT movie_id FROM stars WHERE person_id = (SELECT id FROM people WHERE name = "Johnny Depp");
SElECT movie_id FROM stars WHERE person_id = (SELECT id FROM people WHERE name = "Helena Bonham Carter");