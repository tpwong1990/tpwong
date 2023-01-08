-- Keep a log of any SQL queries you execute as you solve the mystery.
SELECT * FROM crime_scene_reports WHERE year = 2021 AND month = 7 AND day = 28 AND street = "Humphrey Street";
-- (1st)to see if there are any crime report on 28, July 2021 at Humphrey Street. The second report should be irrelevant to the crime.
SELECT id, name, transcript FROM interviews WHERE year = 2021 AND month = 7 AND day = 28 AND transcript LIKE "%bakery%";
-- (2nd)to see the transcript of witnesses
SELECT id, hour, minute, license_plate FROM bakery_security_logs WHERE year = 2021 AND month = 7 AND day = 28 AND activity = "exit";
-- (3rd)based on the transcript of the withness (Ruth id:161, )to check the license plate no of the car which the thief drive and escape from the bakery car park
SELECT name, license_plate, passport_number FROM people JOIN bank_accounts ON id = bank_accounts.person_id WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE year = 2021 AND month = 7 AND day = 28 AND atm_location = "Leggett Street" AND transaction_type = "withdraw");
-- (4th)to check the personal detail who had withdrawn some money on Leggett Street's ATM on 28, July, 2021
SELECT name, passport_number FROM people JOIN bank_accounts ON id = bank_accounts.person_id WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE year = 2021 AND month = 7 AND day = 28 AND atm_location = "Leggett Street" AND transaction_type = "withdraw") AND license_plate IN (SELECT license_plate FROM bakery_security_logs WHERE year = 2021 AND month = 7 AND day = 28 AND activity = "exit");
-- (5th)combine the result from bakery park log and ATM withdrawn record.
SELECT hour, minute, city FROM flights JOIN airports ON origin_airport_id = airports.id WHERE year = 2021 AND month = 7 AND day = 29;
-- (6th)to check the early flight details on 29 July 2021 based on the transcript of witnesses (Raymond)
SELECT passport_number FROM passengers JOIN flights ON flight_id = flights.id WHERE year = 2021 AND month = 7 AND day = 29 AND hour = 8;
-- (7th)get the passport number who take the first fligt on 29 July 2021 which the leave fiftyville
 SELECT name FROM people JOIN bank_accounts ON id = bank_accounts.person_id WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE year = 2021 AND month = 7 AND day = 28 AND atm_location = "Leggett Street" AND transaction_type = "withdraw") AND license_plate IN (SELECT license_plate FROM bakery_security_logs WHERE year = 2021 AND month = 7 AND day = 28 AND activity = "exit") AND passport_number IN (SELECT passport_number FROM passengers JOIN flights ON flight_id = flights.id WHERE year = 2021 AND month = 7 AND day = 29 AND hour = 8);
-- (8th)combine the passport result from 6th and 7th sql result.
SELECT name FROM people WHERE phone_number IN (SELECT receiver FROM phone_calls WHERE year = 2021 AND month = 7 AND day = 28);
-- (9th)find the person who recieve a call on the crime day
SELECT name FROM people WHERE phone_number IN (SELECT caller FROM phone_calls WHERE year = 2021 AND month = 7 AND day = 28);
-- (10th)find the person who make a call on the crime day