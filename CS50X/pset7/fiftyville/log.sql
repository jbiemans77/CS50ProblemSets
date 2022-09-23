-- Keep a log of any SQL queries you execute as you solve the mystery.
-- Sorry bad formatting, might clean up later

-- Get crime scene report
SELECT * FROM "crime_scene_reports" WHERE "month" = '7' AND "day" = '28' AND "description" LIKE '%Theft%'

-- Get interviews
SELECT * FROM "interviews" WHERE "month" = '7' AND "day" = '28' AND "transcript" LIKE '%bakery%'

-- Within 10 minutes of theft got into car, check security logs for plates. (10:15am - 10:25am)
SELECT * FROM "bakery_security_logs" WHERE "month" = '7' AND "day" = '28' AND "hour" = '10' AND "minute" > '15' AND "minute" < '25'
-- SELECT license_plate FROM "bakery_security_logs" WHERE "month" = '7' AND "day" = '28' AND "hour" = '10' AND "minute" > '15' AND "minute" < '25'
--(Plate IN ("5P2BI95", "94KL13X", "6P58WS2", "4328GD8", "G412CB7", "L9JTIZ", "322W7JE", "0NTHK55"))

-- Check when those cars arrived at the bakery
SELECT * FROM "bakery_security_logs" WHERE license_plate IN (SELECT license_plate FROM "bakery_security_logs" WHERE "month" = '7' AND "day" = '28' AND "hour" = '10' AND "minute" > '15' AND "minute" < '25') AND activity = "entrance" ORDER BY license_plate

-- Seen by ATM on Leggett St withdrawing money earlier in day
SELECT * FROM "atm_transactions" WHERE "month" = '7' AND "day" = '28' AND "atm_location" LIKE 'Leggett Street' AND "transaction_type" LIKE 'withdraw'
--SELECT account_number FROM "atm_transactions" WHERE "month" = '7' AND "day" = '28' AND "atm_location" LIKE 'Leggett Street' AND "transaction_type" LIKE 'withdraw'

-- Find the people who have bank accounts that made a withdraw that day
SELECT person_id FROM "bank_accounts" WHERE "account_number" IN (SELECT account_number FROM "atm_transactions" WHERE "month" = '7' AND "day" = '28' AND "atm_location" LIKE 'Leggett Street' AND "transaction_type" LIKE 'withdraw')

-- Find the people who have a matching bank account and license plate
SELECT * from people WHERE id IN (SELECT person_id FROM "bank_accounts" WHERE "account_number" IN (SELECT account_number FROM "atm_transactions" WHERE "month" = '7' AND "day" = '28' AND "atm_location" LIKE 'Leggett Street' AND "transaction_type" LIKE 'withdraw'))
    AND license_plate IN (SELECT license_plate FROM "bakery_security_logs" WHERE "month" = '7' AND "day" = '28' AND "hour" = '10' AND "minute" > '15' AND "minute" < '25')
/* SUSPECTS:
396669 IMAN
467400 LUCA
514354 DIANA
686048 BRUCE */

-- At the theft, thief called someone for less than a minute - take earliest flight out of fiftyville tomorrow. (July 29) - asked to purchase ticket
-- Find earliest flight out of Fiftyville
SELECT * FROM "flights" WHERE "month" = '7' AND "day" = '29' ORDER BY hour, minute LIMIT 1
-- flight ID = 36
-- Destination ID: 4
SELECT city from airports WHERE id = '4' -- New York City

-- Who made calls for less than a minute on the 28th
SELECT caller FROM "phone_calls" WHERE "month" = '7' AND "day" = '28' AND "duration" < '60'

SELECT * from people WHERE id IN (SELECT person_id FROM "bank_accounts" WHERE "account_number" IN (SELECT account_number FROM "atm_transactions" WHERE "month" = '7' AND "day" = '28' AND "atm_location" LIKE 'Leggett Street' AND "transaction_type" LIKE 'withdraw'))
    AND license_plate IN (SELECT license_plate FROM "bakery_security_logs" WHERE "month" = '7' AND "day" = '28' AND "hour" = '10' AND "minute" > '15' AND "minute" < '25')
    AND phone_number IN (SELECT caller FROM "phone_calls" WHERE "month" = '7' AND "day" = '28' AND "duration" < '60')
/*SUSPECTS:
514354 DIANA
686048 BRUCE*/

SELECT * FROM "passengers" WHERE "flight_id" = '36' AND passport_number IN (SELECT passport_number from people WHERE id IN (SELECT person_id FROM "bank_accounts" WHERE "account_number" IN (SELECT account_number FROM "atm_transactions" WHERE "month" = '7' AND "day" = '28' AND "atm_location" LIKE 'Leggett Street' AND "transaction_type" LIKE 'withdraw'))
AND license_plate IN (SELECT license_plate FROM "bakery_security_logs" WHERE "month" = '7' AND "day" = '28' AND "hour" = '10' AND "minute" > '15' AND "minute" < '25') AND phone_number IN (SELECT caller FROM "phone_calls" WHERE "month" = '7' AND "day" = '28' AND "duration" < '60'))
-- PASSPORT Number: 5773159633
SELECT * FROM "people" WHERE "passport_number" = '5773159633'
-- Thief = BRUCE!

-- Acomplice phone number
SELECT receiver FROM "phone_calls" WHERE "caller" LIKE '(367) 555-5533' AND "month" = '7' AND "day" = '28' AND "duration" < '60'
SELECT name FROM "people" WHERE "phone_number" IN (SELECT receiver FROM "phone_calls" WHERE "caller" LIKE '(367) 555-5533' AND "month" = '7' AND "day" = '28' AND "duration" < '60')
-- ACcomplice = ROBIN!