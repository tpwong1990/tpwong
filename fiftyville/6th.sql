SELECT hour, minute, city FROM flights JOIN airports ON origin_airport_id = airports.id WHERE year = 2021 AND month = 7 AND day = 29;
