#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <stdio.h>
#include <ctime>
#include "accounts.h"

//global variables for key logged in user information
std::string uniqueUserID;
double userCheqBal;
double userSavBal;
int userRole;
double totalCheqBank = 0;
double totalSavBank = 0;
std::string clientName;
int numberOfUsers;
//when recording = 0, the program is not recording
int recording;

//function will decrypt the username and password into a uniqueID
std::string decrypt(std::string code) {
    long randomizer = 100;


    // Converts each character of string into an integer
    // and adds them together
    for (int i = 0; i < code.size(); i++)
    {
        randomizer += code[i];
    }

    // Make our number a little bit more unique
    randomizer *= 3.1415;
    randomizer += code.size() * (int)code[0];
    randomizer *= (int)code[code.size() - 1];

    std::ostringstream ss;
    ss << randomizer;
    std::string str = ss.str();

    return str;
}


//updates our database with the newest data
void rewriteFile() {
    std::ifstream fileIn("users.txt");
    std::ofstream fileOut("temp.txt");
    std::string line;

    //get each line in the text file and separate each line's contents by the comma and put them in an array
    while (std::getline(fileIn, line)) {
        std::string *array = new std::string[6];
        int i=0;
        std::stringstream iss;

        iss << line;

        //separate the userid, role, chequings account and savings account balances for each user
        while (std::getline(iss, line, ',')) {
            array[i] = line;
            ++i;
        }

        //if we find the user we are looking for, we update its information
        if (array[0] == uniqueUserID) {
            std::stringstream values;
            values << uniqueUserID << ',' << userRole << ',' << std::setprecision(2) << std::fixed << userCheqBal << ',' << std::setprecision(2) << std::fixed << userSavBal << ',' << clientName;
            std::string input;
            input = values.str();
            fileOut << input << "\n";
        }
        else {
            std::string secondInput;
            secondInput = array[0] + "," + array[1] + "," + array[2] + "," + array[3] + "," + array[4];
            fileOut << secondInput << "\n";
        }

    }

    //close our files and remove the old users.txt file so that it can be replaced with the updated information that's being temporarily stored in temp.txt
    fileOut.close();
    fileIn.close();
    remove("users.txt");

    //copy text.txt data over to the new users.txt file
    std::ifstream secondInFile("temp.txt");
    std::ofstream secondOutFile("users.txt");

    if (secondInFile)
    {
        std::stringstream buffer;

        buffer << secondInFile.rdbuf();

        secondInFile.close();

        // operations on the buffer...

        secondOutFile << buffer.rdbuf();

    }

    //remove the temp.txt file
    remove("temp.txt");

}




//updates our database with the newest data
void updateRecording(std::string value) {
    std::ifstream fileIn("users.txt");
    std::ofstream fileOut("temp.txt");
    std::string line;

    //get each line in the text file and separate each line's contents by the comma and put them in an array
    while (std::getline(fileIn, line)) {
        std::string *array = new std::string[5];
        int i=0;
        std::stringstream iss;

        iss << line;

        //separate the userid, role, chequings account and savings account balances for each user
        while (std::getline(iss, line, ',')) {
            array[i] = line;
            ++i;
        }

        //if we find the user we are looking for, we update its information
        if (array[0] == uniqueUserID) {
            std::stringstream values;
            values << uniqueUserID << ',' << userRole << ','  << value << "," << "0" << "," << clientName;
            std::string input;
            input = values.str();
            fileOut << input << "\n";
        }
        else {
            std::string secondInput;
            secondInput = array[0] + "," + array[1] + "," + array[2] + "," + array[3] + "," + array[4];
            fileOut << secondInput << "\n";
        }

    }

    //close our files and remove the old users.txt file so that it can be replaced with the updated information that's being temporarily stored in temp.txt
    fileOut.close();
    fileIn.close();
    remove("users.txt");

    //copy text.txt data over to the new users.txt file
    std::ifstream secondInFile("temp.txt");
    std::ofstream secondOutFile("users.txt");

    if (secondInFile)
    {
        std::stringstream buffer;

        buffer << secondInFile.rdbuf();

        secondInFile.close();

        // operations on the buffer...

        secondOutFile << buffer.rdbuf();

    }

    //remove the temp.txt file
    remove("temp.txt");

}




//this gets our selected user's data and closes an account by setting it to 0
void changeAccount(std::string userId, std::string role, std::string otherAcctBal, int account, std::string clientName, std::string value) {
    std::ifstream fileIn("users.txt");
    std::ofstream fileOut("temp.txt");
    std::string line;

    //affects chequings account
    if (account == 0) {
        while (std::getline(fileIn, line)) {
            std::string *array = new std::string[5];
            int i = 0;
            std::stringstream iss;

            iss << line;

            //separate the userid, role, chequings account and savings account balances for each user
            while (std::getline(iss, line, ',')) {
                array[i] = line;
                ++i;
            }

            //the selected user's data has been found and we set the chequings to value
            if (array[0] == userId) {
                std::stringstream values;
                values << userId << ',' << role << ',' << value
                       << ',' << std::setprecision(2) << std::fixed << otherAcctBal << ',' << clientName;
                std::string input;
                input = values.str();
                fileOut << input << "\n";
            } else {
                std::string secondInput;
                secondInput = array[0] + "," + array[1] + "," + array[2] + "," + array[3] + "," + array[4];
                fileOut << secondInput << "\n";
            }

        }
    }
    //affects savings account
    else {
        while (std::getline(fileIn, line)) {
            std::string *array = new std::string[5];
            int i = 0;
            std::stringstream iss;

            iss << line;

            //separate the userid, role, chequings account and savings account balances for each user
            while (std::getline(iss, line, ',')) {
                array[i] = line;
                ++i;
            }

            //set the savings account to 0/null
            if (array[0] == userId) {
                std::stringstream values;
                values << userId << ',' << role << ',' << std::setprecision(2) << std::fixed << otherAcctBal
                       << ',' << value << ',' << clientName;
                std::string input;
                input = values.str();
                fileOut << input << "\n";
            } else {
                std::string secondInput;
                secondInput = array[0] + "," + array[1] + "," + array[2] + "," + array[3] + "," + clientName;
                fileOut << secondInput << "\n";
            }

        }
    }

    //close files and replicate the temp.txt into a new users.txt and remove the temp.txt file
    fileOut.close();
    fileIn.close();
    remove("users.txt");

    std::ifstream secondInFile("temp.txt");
    std::ofstream secondOutFile("users.txt");

    if (secondInFile) {
        std::stringstream buffer;

        buffer << secondInFile.rdbuf();

        secondInFile.close();

        // operations on the buffer...

        secondOutFile << buffer.rdbuf();

    }

    remove("temp.txt");
}




//key function that returns a pointer to the array of strings containing the specified user's data
std::string *getData(std::string user) {

    std::ifstream file("users.txt");
    std::string line;


    while (std::getline(file, line)) {
        std::string *array = new std::string[5];
        int i=0;
        std::stringstream iss;

        iss << line;


        while (std::getline(iss, line, ',')) {
            array[i] = line;
            ++i;
        }
        iss.clear();

        //if this array matches our user's id then we return it
        if (array[0] == user) {
            return array;
        }

    }

}



//check to see if the inputted user's id exists in our database
bool checkUserID(std::string user) {

    std::ifstream file("users.txt");
    std::string line;


    while (std::getline(file, line)) {
        std::string *array = new std::string[5];
        int i=0;
        std::stringstream iss;

        iss << line;


        while (std::getline(iss, line, ',')) {
            array[i] = line;
            ++i;
        }
        iss.clear();

        //return true if user is found
        if (array[0] == user) {
            return true;
        }

    }
    return false;

}
