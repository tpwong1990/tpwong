-- Keep a log of any SQL queries you execute as you solve the mystery.
SELECT * FROM crime_scene_reports WHERE year = 2021 AND month = 7 AND day = 28 AND street = "Humphrey Street";
-- to see if there are any crime report on 28, July 2021 at Humphrey Street. The second report should be irrelevant to the crime.
SELECT id, name, transcript FROM interviews WHERE year = 2021 AND month = 7 AND day = 28 AND transcript LIKE "%bakery%";
-- to see the transcript of witnesses
SELECT id, hour, minute, license_plate FROM bakery_security_logs WHERE year = 2021 AND month = 7 AND day = 28 AND activity = "exit";
-- based on the transcript of the withness (Ruth id:161, )to check the license plate no of the car which the thief drive and escape from the bakery car park
SELECT name, license_plate, passport_number FROM people JOIN bank_accounts ON id = bank_accounts.person_id WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE year = 2021 AND month = 7 AND day = 28 AND atm_location = "Leggett Street" AND transaction_type = "withdraw");
-- to check the personal detail who had withdrawn some money on Leggett Street's ATM on 28, July, 2021