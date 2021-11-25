-- Keep a log of any SQL queries you execute as you solve the mystery.

-- Let's see what this database looks like.
.schema

-- Pull up the crime scene report for the date and location in question.
SELECT description FROM crime_scene_reports
WHERE street = 'Chamberlin Street'
AND month = 7
AND day = 28
and year = 2020;
-- Theft of the CS50 duck took place at 10:15am at the Chamberlin Street
-- courthouse. Interviews were conducted today with three witnesses who were
-- present at the time — each of their interview transcripts mentions the
-- courthouse.

-- Let's see the courthouse security logs at the time of the theft.
SELECT activity, license_plate FROM courthouse_security_logs
WHERE month = 7
AND day = 28
AND year = 2020
AND hour = 10
AND minute = 15;
-- No results

-- Let's broaden search to anything between 10 and 11 am.
SELECT activity, license_plate FROM courthouse_security_logs
WHERE month = 7
AND day = 28
AND year = 2020
AND hour = 10;
-- entrance|R3G7486
-- entrance|13FNH73
-- exit|5P2BI95
-- exit|94KL13X
-- exit|6P58WS2
-- exit|4328GD8
-- exit|G412CB7
-- exit|L93JTIZ
-- exit|322W7JE
-- exit|0NTHK55
-- exit|1106N58
-- entrance|NRYN856
-- entrance|WD5M8I6
-- entrance|V47T75I

-- Let's look at the interviews.
SELECT name, transcript FROM interviews
WHERE month = 7
AND day = 28
AND year = 2020
AND (
    transcript LIKE '%courthouse%'
    OR transcript LIKE '%duck%' );
-- Ruth|Sometime within ten minutes of the theft, I saw the thief get into a
-- car in the courthouse parking lot and drive away. If you have security
-- footage from the courthouse parking lot, you might want to look for cars
-- that left the parking lot in that time frame.
-- Eugene|I don't know the thief's name, but it was someone I recognized.
-- Earlier this morning, before I arrived at the courthouse, I was walking by
-- the ATM on Fifer Street and saw the thief there withdrawing some money.
-- Raymond|As the thief was leaving the courthouse, they called someone who
-- talked to them for less than a minute. In the call, I heard the thief say
-- that they were planning to take the earliest flight out of Fiftyville
-- tomorrow. The thief then asked the person on the other end of the phone to
-- purchase the flight ticket.

-- Let's redo the courthouse search to only include results from 10:15 to
-- 10:25.
SELECT activity, license_plate FROM courthouse_security_logs
WHERE month = 7
AND day = 28
AND year = 2020
AND hour = 10
AND minute >= 15
AND minute <= 25;
-- exit|5P2BI95
-- exit|94KL13X
-- exit|6P58WS2
-- exit|4328GD8
-- exit|G412CB7
-- exit|L93JTIZ
-- exit|322W7JE
-- exit|0NTHK55

-- Let's try and find Eugene's license plate.
SELECT name, license_plate FROM people
WHERE name LIKE 'Eugene%';
-- Eugene|47592FJ

-- Let's see when Eugene arrived at the courthouse:
SELECT activity, hour, minute FROM courthouse_security_logs
WHERE license_plate = '47592FJ'
AND month = 7
AND day = 28
AND year = 2020;
-- No results

-- So we can't narrow down when the ATM transaction occurred any more than
-- on the day of. Let's see what those are.

SELECT name, bank_accounts.account_number,
transaction_type, amount FROM atm_transactions
JOIN bank_accounts
ON atm_transactions.account_number = bank_accounts.account_number
JOIN people ON people.id = bank_accounts.person_id
WHERE month = 7
AND day = 28
AND year = 2020
AND atm_location LIKE '%Fifer Street%';
-- Ernest|49610011|withdraw|50
-- Robert|86363979|deposit|10
-- Russell|26013199|withdraw|35
-- Roy|16153065|withdraw|80
-- Bobby|28296815|withdraw|20
-- Elizabeth|25506511|withdraw|20
-- Danielle|28500762|withdraw|48
-- Madison|76054385|withdraw|60
-- Victoria|81061156|withdraw|30

-- Let's cross reference with the license plates.
SELECT name FROM people
WHERE license_plate IN (
    SELECT license_plate FROM courthouse_security_logs
    WHERE month = 7
    AND day = 28
    AND year = 2020
    AND hour = 10
    AND minute >= 15
    AND minute <= 25 )
AND name IN (
    SELECT name FROM atm_transactions
    JOIN bank_accounts
    ON atm_transactions.account_number = bank_accounts.account_number
    JOIN people ON people.id = bank_accounts.person_id
    WHERE month = 7
    AND day = 28
    AND year = 2020
    AND atm_location LIKE '%Fifer Street%' );
-- Elizabeth
-- Danielle
-- Russell
-- Ernest

-- Let's see any calls as the thief was leaving the courthouse (let's say
-- 10:15 - 10:30) that are less than a minute long on the day of the theft.
-- EDIT: Nevermind, can't select calls by time of day so we'll have to see all
-- calls that day less than a minute in length.
-- Let's try to limit it to callers who are on the above list.
SELECT name, caller, receiver FROM phone_calls
JOIN people ON people.phone_number = phone_calls.caller
WHERE month = 7
AND day = 28
AND year = 2020
AND duration < 60
AND name IN (
    SELECT name FROM people
    WHERE license_plate IN (
        SELECT license_plate FROM courthouse_security_logs
        WHERE month = 7
        AND day = 28
        AND year = 2020
        AND hour = 10
        AND minute >= 15
        AND minute <= 25 )
    AND name IN (
        SELECT name FROM atm_transactions
        JOIN bank_accounts
        ON atm_transactions.account_number = bank_accounts.account_number
        JOIN people ON people.id = bank_accounts.person_id
        WHERE month = 7
        AND day = 28
        AND year = 2020
        AND atm_location LIKE '%Fifer Street%' ));
-- Ernest|(367) 555-5533|(375) 555-8161
-- Russell|(770) 555-1861|(725) 555-3243

-- Let's see who these people called.
SELECT name, phone_number FROM people
WHERE phone_number IN (
    SELECT receiver FROM phone_calls
    JOIN people ON people.phone_number = phone_calls.caller
    WHERE month = 7
    AND day = 28
    AND year = 2020
    AND duration < 60
    AND name IN (
        SELECT name FROM people
        WHERE license_plate IN (
            SELECT license_plate FROM courthouse_security_logs
            WHERE month = 7
            AND day = 28
            AND year = 2020
            AND hour = 10
            AND minute >= 15
            AND minute <= 25 )
        AND name IN (
            SELECT name FROM atm_transactions
            JOIN bank_accounts
            ON atm_transactions.account_number = bank_accounts.account_number
            JOIN people ON people.id = bank_accounts.person_id
            WHERE month = 7
            AND day = 28
            AND year = 2020
            AND atm_location LIKE '%Fifer Street%' )));
-- Philip|(725) 555-3243
-- Berthold|(375) 555-8161

-- Let's see what the Fiftyville airport is called.
SELECT * FROM airports
WHERE city = 'Fiftyville';
-- 8|CSF|Fiftyville Regional Airport|Fiftyville

-- And now let's find the earliest flight the next day out of Fiftyville
SELECT id, hour, minute FROM flights
WHERE origin_airport_id = 8
AND month = 7
AND day = 29
AND year = 2020
ORDER BY hour ASC, minute ASC LIMIT 1;
-- 36|8|20

-- Let's see if any of the accomplices are on the passenger manifest.
SELECT name FROM people
JOIN passengers ON passengers.passport_number = people.passport_number
WHERE passengers.flight_id = 36
AND name IN (
    SELECT name FROM people
    WHERE phone_number IN (
        SELECT receiver FROM phone_calls
        JOIN people ON people.phone_number = phone_calls.caller
        WHERE month = 7
        AND day = 28
        AND year = 2020
        AND duration < 60
        AND name IN (
            SELECT name FROM people
            WHERE license_plate IN (
                SELECT license_plate FROM courthouse_security_logs
                WHERE month = 7
                AND day = 28
                AND year = 2020
                AND hour = 10
                AND minute >= 15
                AND minute <= 25 )
            AND name IN (
                SELECT name FROM atm_transactions
                JOIN bank_accounts
                ON atm_transactions.account_number = bank_accounts.account_number
                JOIN people ON people.id = bank_accounts.person_id
                WHERE month = 7
                AND day = 28
                AND year = 2020
                AND atm_location LIKE '%Fifer Street%' ))));
-- No results

-- Let's check the suspects:
SELECT name FROM people
JOIN passengers ON passengers.passport_number = people.passport_number
WHERE passengers.flight_id = 36
AND name IN (
    SELECT name FROM phone_calls
    JOIN people ON people.phone_number = phone_calls.caller
    WHERE month = 7
    AND day = 28
    AND year = 2020
    AND duration < 60
    AND name IN (
        SELECT name FROM people
        WHERE license_plate IN (
            SELECT license_plate FROM courthouse_security_logs
            WHERE month = 7
            AND day = 28
            AND year = 2020
            AND hour = 10
            AND minute >= 15
            AND minute <= 25 )
        AND name IN (
            SELECT name FROM atm_transactions
            JOIN bank_accounts
            ON atm_transactions.account_number = bank_accounts.account_number
            JOIN people ON people.id = bank_accounts.person_id
            WHERE month = 7
            AND day = 28
            AND year = 2020
            AND atm_location LIKE '%Fifer Street%' )));
-- Ernest

-- Ernest talked to Berthold, so my first thought is that they are the
-- thieves.

-- Let's see where Ernest went.
SELECT city FROM airports
JOIN flights ON flights.destination_airport_id = airports.id
WHERE flights.id = 36;
-- London

-- The THIEF is: Ernest
-- The thief ESCAPED TO: London
-- The ACCOMPLICE is: Berthold
