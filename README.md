![Banner](assets/banner.png)
# Project Table of Contents
- [Project Table of Contents](#project-table-of-contents)
- [1. Introduction](#1-introduction)
- [2. Project Description](#2-project-description)
- [3. Data](#3-data)
- [4. OOP Technicalities:](#4-oop-technicalities)
- [5. Results](#5-results)

# 1. Introduction
This project is a C++ program that calculates the cost of a movie production. The program reads a CSV file with the cast of the movie and calculates the cost of the production based on the cast. The program also generates a CSV file with the cast and the cost of the production.

# 2. Project Description
The project does the following:
- Reads a CSV file with the cast of the movie
- Generates random names for extra cast members
- Uses object-oriented programming to store the cast, the cost of the production and the cost of each cast member. The cast is stored in a vector of objects of the class CastMember.
- Calculates the cost of the production based on the cast, transport, hotel, food, drinks, makeup, etc.
- Generates a CSV file with the cast and the cost of the production

# 3. Data
The data used in this project is taken from IMBD. The data is stored in a CSV file. The raw data was modified to fit the needs of the program. The data is stored in the following format:
- The first line is the header of the CSV file
- The first column is the name of the cast member
- The second column is the function of the cast member

# 4. OOP Technicalities:
- The class CastMember is used to store the cast members. The class has the following attributes:
    - `nume` - string
    - `functie` - string
    - `clasa` - string
    - `dieta` - string
- The class CastMember has the following methods:
    - `getNume()` - returns the name of the cast member
    - `getFunctie()` - returns the function of the cast member
    - `getClasa()` - returns the class of the cast member
    - `getDieta()` - returns the diet of the cast member
    - `setNume(string nume)` - sets the name of the cast member
    - `setFunctie(string functie)` - sets the function of the cast member
- The class Cost is used to store the cost of the production. The class has the following attributes:
    - `costTransport` - double
    - `costHotel` - double
    - `costBautura` - double
    - `costMachiaj` - double
    - `costDieta` - double
    - `costFilmari` - double
    - `costTotal` - double
- FileProcessor class is used to read and write data from and to files. The class has the following attributes:
    - `cast` - vector<CastMember>
    - `cost` - Cost
- The class `FileProcessor` has the following methods:
    - `readCastFile(string filename)` - reads the cast from the CSV file
    - `writeFinalCastFile(string filename)` - writes the cast and the cost of the production to a CSV file
    - `writeMenuFile(string filename)` - writes the menu to a CSV file
    - `writeCostFile(string filename)` - writes the cost of the production to a CSV file
    - `getCast()` - returns the cast
    - `getCost()` - returns the cost of the production

# 5. Results
The program generates a CSV file with the cast and the cost of the production