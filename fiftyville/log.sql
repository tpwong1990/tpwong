-- Keep a log of any SQL queries you execute as you solve the mystery.
SELECT * FROM crime_scene_reports WHERE year = 2021 AND month = 7 AND day = 28 AND street = "Humphrey Street";
-- (1st)to see if there are any crime report on 28, July 2021 at Humphrey Street. The second report should be irrelevant to the crime.
SELECT id, name, transcript FROM interviews WHERE year = 2021 AND month = 7 AND day = 28 AND transcript LIKE "%bakery%";
-- (2nd)to see the transcript of witnesses
SELECT id, hour, minute, license_plate FROM bakery_security_logs WHERE year = 2021 AND month = 7 AND day = 28 AND activity = "exit";
-- (3rd)based on the transcript of the withness (Ruth id:161, )to check the license plate no of the car which the thief drive and escape from the bakery car park
SELECT name, license_plate, passport_number FROM people JOIN bank_accounts ON id = bank_accounts.person_id WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE year = 2021 AND month = 7 AND day = 28 AND atm_location = "Leggett Street" AND transaction_type = "withdraw");
-- (4th)to check the personal detail who had withdrawn some money on Leggett Street's ATM on 28, July, 2021
SELECT name, passport_number FROM people JOIN bank_accounts ON id = bank_accounts.person_id WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE year = 2021 AND month = 7 AND day = 28 AND atm_location = "Leggett Street" AND transaction_type = "withdraw") AND license_plate IN (SELECT license_plate FROM bakery_security_logs WHERE year = 2021 AND month = 7 AND day = 28 AND activity = "exit" AND hour = 10 AND (minute >= 15 AND minute <= 25));
-- (5th)combine the result from bakery park log and ATM withdrawn record.
SELECT hour, minute, city FROM flights JOIN airports ON origin_airport_id = airports.id WHERE year = 2021 AND month = 7 AND day = 29;
-- (6th)to check the early flight details on 29 July 2021 based on the transcript of witnesses (Raymond)
SELECT passport_number FROM passengers JOIN flights ON flight_id = flights.id WHERE year = 2021 AND month = 7 AND day = 29 AND hour = 8;
-- (7th)get the passport number who take the first fligt on 29 July 2021 which the leave fiftyville
SELECT name FROM people JOIN bank_accounts ON id = bank_accounts.person_id WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE year = 2021 AND month = 7 AND day = 28 AND atm_location = "Leggett Street" AND transaction_type = "withdraw") AND license_plate IN (SELECT license_plate FROM bakery_security_logs WHERE year = 2021 AND month = 7 AND day = 28 AND activity = "exit" AND hour = 10 AND (minute >= 15 AND minute <= 25)) AND passport_number IN (SELECT passport_number FROM passengers JOIN flights ON flight_id = flights.id WHERE year = 2021 AND month = 7 AND day = 29 AND hour = 8);
-- (8th)combine the passport result from 5th and 7th sql result, find the people who take the first flight on 29, July and withdraw money from Leggett Street's ATM and exit the bakery car park
SELECT name FROM people WHERE phone_number IN (SELECT caller FROM phone_calls WHERE year = 2021 AND month = 7 AND day = 28 AND duration <= 60);
-- (9th)find the person who make a call on the crime day and the duration less not 60s.
SELECT name FROM people WHERE phone_number IN (SELECT caller FROM phone_calls WHERE year = 2021 AND month = 7 AND day = 28 and duration <= 60) AND name IN (SELECT name FROM people JOIN bank_accounts ON id = bank_accounts.person_id WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE year = 2021 AND month = 7 AND day = 28 AND atm_location = "Leggett Street" AND transaction_type = "withdraw") AND license_plate IN (SELECT license_plate FROM bakery_security_logs WHERE year = 2021 AND month = 7 AND day = 28 AND activity = "exit" AND hour = 10 AND (minute >= 15 AND minute <= 25)) AND passport_number IN (SELECT passport_number FROM passengers JOIN flights ON flight_id = flights.id WHERE year = 2021 AND month = 7 AND day = 29 AND hour = 8));
-- (10th) combine the result from 9th sql and 8th sql, only one person name in the list which is Bruce, who is the thief.
SELECT phone_number FROM people WHERE name = "Bruce";
-- (11th) get Bruce's phone number
SELECT name FROM people WHERE phone_number = (SELECT receiver FROM phone_calls WHERE caller = (SELECT phone_number FROM people WHERE name = "Bruce") AND year = 2021 AND month = 7 AND day = 28 AND duration <= 60);
-- (12th) from the result of 11th sql, find who is called by Bruce after the crime and is asked to buy air ticket from Bruce. There is only one result which is Robin.
SELECT city FROM flights JOIN airports ON destination_airport_id = airports.id WHERE year = 2021 AND month = 7 AND day = 29 AND hour = 8;
-- (13th) base the 6th sql result, the thief escape to New York City
