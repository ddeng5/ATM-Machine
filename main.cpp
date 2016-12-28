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


//returns our client's data
std::string getRecording(std::string user) {
    std::string *p;

    p = getData(user);

    return *(p+2);
}


//returns our client's full name
std::string getClientName(std::string user) {
    std::string *p;

    p = getData(user);

    return *(p+4);
}


//returns our client's role 0 = normal, 1 = manager, 2 = system's engineer
std::string getRole(std::string user) {
    std::string *p;

    p = getData(user);

    return *(p+1);
}


//return our client's chequings account balance
std::string getCheqBal(std::string user) {
    std::string *p;

    p = getData(user);
    userCheqBal = std::stod(*(p+2));

    return *(p+2);
}


//return our client's savings account balance
std::string getSavBal(std::string user) {
    std::string *p;

    p = getData(user);

    userSavBal = std::stod(*(p+3));
    return *(p+3);
}


//returns our client's full name
std::string getOverdraft(std::string user) {
    std::string *p;

    p = getData(user);

    return *(p+5);
}


//function for the manager to see all accounts in our database and their details
void listData() {
    std::ifstream file("users.txt");
    std::string line;
    //keep track of the number of users in our database
    numberOfUsers = 0;

    while (std::getline(file, line)) {
        std::string *array = new std::string[5];
        int i=0;
        std::stringstream iss;

        iss << line;


        while (std::getline(iss, line, ',')) {
            array[i] = line;
            ++i;
        }

        std::cout << "Userid: " + array[0] + '\t' + " Chequings Balance: " + array[2] + '\t' + " Savings Balance: " + array[3] + '\t' + " Client: " + array[4] << std::endl;

        totalCheqBank = totalCheqBank + std::stod(array[2]);
        totalSavBank = totalSavBank + std::stod(array[3]);
        ++numberOfUsers;


        iss.clear();


    }

    std::ostringstream convertCheqBank;
    convertCheqBank << totalCheqBank;
    std::string str = convertCheqBank.str();

    std::ostringstream convertSavBank;
    convertSavBank << totalSavBank;
    std::string str2 = convertSavBank.str();

    std::ostringstream convertUsers;
    convertUsers << numberOfUsers;
    std::string str3 = convertUsers.str();

    std::cout << "" << std::endl;
    std::cout << "Total money in chequings accounts in the bank: " + str << std::endl;
    std::cout << "Total money in the savings accounts in the bank: " + str2 << std::endl;
    std::cout << "Total number of client's in the bank: " + str3 << std::endl;


}



//check if system recording is on and if it is, print activity with time to log.txt
void checkRecording(std::string message) {
    if (recording == 1) {
        auto t = std::time(nullptr);
        auto tm = *std::localtime(&t);

        std::ostringstream oss;
        oss << std::put_time(&tm, "%d-%m-%Y %H:%M:%S");
        auto str = oss.str();

        std::string activity;
        activity = str + '\t' + message;

        std::ofstream file;
        file.open("log.txt", std::ios_base::app);
        file << activity << '\n';
    }
}




//prompt the customer to enter their username and and tells them if they have logged in successfully
bool login() {
    std::cout << "Welcome to the Bank of CS!!!" << std::endl;
    std::cout << "" << std::endl;
    std::cout << "" << std::endl;
    std::cout << "" << std::endl;

    std::cout << "Enter your username: " << std::endl;
    std::string username;
    std::cin >> username;
    std::cout << "Enter your password: " << std::endl;
    std::string password;
    std::cin >> password;

    std::string combination = username + password;
    std::string uniqueID;
    uniqueID = decrypt(combination);

    uniqueUserID = uniqueID;
    std::cout << uniqueID <<std::endl;

    bool status;
    status = checkUserID(uniqueID);
    if (getRecording("230150").compare("0") == 0) {
        recording = 0;
    }
    else {
        recording = 1;
    }

    if (status) {
        std::cout << "Login Successful" << std::endl;
        checkRecording(getClientName(uniqueUserID) + " logged in.");
        return true;
    }
    else {
        std::cout << "Login Unsuccessful" << std::endl;
        checkRecording("Unsuccessful login attempt!");
        return false;
    }

}


void printCustomer(std::string userId) {
    std::ifstream file("users.txt");
    std::string line;
    //keep track of the number of users in our database
    numberOfUsers = 0;

    while (std::getline(file, line)) {
        std::string *array = new std::string[5];
        int i=0;
        std::stringstream iss;

        iss << line;


        while (std::getline(iss, line, ',')) {
            array[i] = line;
            ++i;
        }

        if (array[0] == userId) {


            std::cout
                    << "Userid: " + array[0] + '\t' + " Chequings Balance: " + array[2] + '\t' + " Savings Balance: " +
                       array[3] + '\t' + " Client: " + array[4] << std::endl;

            totalCheqBank = totalCheqBank + std::stod(array[2]);
            totalSavBank = totalSavBank + std::stod(array[3]);
            ++numberOfUsers;


            iss.clear();
        }

    }

}


//these are all the normal activities (banking stuff like deposit withdraw etc...)
int normalUser(std::string user, int accountUserRole) {
    userRole = accountUserRole;
    clientName = getClientName(user);

    //create a new account object
    accounts userAcct(std::stod(getCheqBal(user)), std::stod(getSavBal(user)));
        std::cout << "" << std::endl;
        std::cout << "Greetings " << clientName << std::endl;
        std::cout << "" << std::endl;

        //display the status of their accounts and their balances if they are open
        if (std::stod(getCheqBal(user)) <= 0) {
            std::cout << "Chequings Account Balance: Closed" << std::endl;
        }
        else {
            std::cout << "Chequings Account Balance: " + getCheqBal(user) << std::endl;
        }

        if (std::stod(getSavBal(user)) <= 0) {
            std::cout << "Savings Account Balance: Closed" << std::endl;
        }
        else {
                std::cout << "Savings Account Balance: " + getSavBal(user) << std::endl;
        }

        std::cout << "" << std::endl;
        std::cout << "" << std::endl;

        //main menu
        std::cout << "0. Cash Withdrawal" << std::endl;
        std::cout << "1. Deposit" << std::endl;
        std::cout << "2. Transfer Between Accounts" << std::endl;
        std::cout << "3. Exit/Logout" << std::endl;

        std::cout << "" << std::endl;
        std::cout << "" << std::endl;

        std::cout << "Enter the number of the process you would like to complete today: " << std::endl;

        int task;
        std::cin >> task;

        //cash withdrawal function
        if (task == 0) {
            std::cout << "" << std::endl;
            std::cout << "" << std::endl;
            std::cout << "" << std::endl;

            //ask which account they would like to withdraw from
            std::cout << "Which account would you like to withdraw from?" << std::endl;
            std::cout << "0. Chequings Account" << std::endl;
            std::cout << "1. Savings Account" << std::endl;
            std::cout << "Press Any Other Number to Go Back" << std::endl;

            int account;
            std::cin >> account;

            //guarantees that they enter a number only and will keep prompting them if incorrect
            while(std::cin.fail()) {
                std::cout << "Please Enter a Number Only: " << std::endl;
                std::cin.clear();
                std::cin.ignore(256,'\n');
                std::cin >> account;
            }

            //withdrawing from the chequings account
            if (account == 0) {
                //check to see if the account is closed
                if (std::stod(getCheqBal(user)) == 0) {
                    std::cout << "Cannot withdraw from a closed account, contact your bank manager to open!" << std::endl;
                    checkRecording(getClientName(user) + " tried to withdraw from closed chequings account.");
                    return 0;
                }
                //ask how much they would like to withdraw
                std::cout << "Enter amount to withdraw" << std::endl;
                double withdrawAmt;
                std::cin >> withdrawAmt;

                //check if there are sufficient funds in the chequings account
                if (userAcct.cashWithdrawal(userCheqBal, withdrawAmt) < 0) {
                    std::cout << "Insufficient funds to withdraw from chequings account." << std::endl;
                    checkRecording(getClientName(user) + " tried to withdraw but did not have sufficient funds.");
                    return 0;
                }
                else {
                    double temp;
                    temp = userAcct.cashWithdrawal(userCheqBal, withdrawAmt);
                    //if withdrawing from a chequings account and the resulting balance will be less than $1000, warn user and tell them a $2 charge will incur if they agree
                    if (temp < 1000) {
                        std::cout << "You will be charged $2 if you proceed with this action because your chequings account will be <$1000. Would you like to proceed?" << std::endl;
                        std::cout << "0. No" << std::endl;
                        std::cout << "1. Yes" << std::endl;
                        int pick;
                        std::cin >> pick;

                        //if the user doesn't agree to the charges then go back to the main menu
                        if (pick == 0) {
                            checkRecording(getClientName(user) + " denied extra charge to withdraw from chequings account.");
                            return 0;
                        }
                            //if they agree go through with the transaction and charge $2
                        else {
                            double newTotal;
                            newTotal = userAcct.cashWithdrawal(userCheqBal, withdrawAmt);
                            newTotal = newTotal - 2;
                            std::cout << "Withdraw Complete" << std::endl;
                            std::ostringstream strs;
                            strs << withdrawAmt;
                            std::string str = strs.str();
                            checkRecording(getClientName(user) + " withdrew " + str + " from chequings account with extra charge.");
                            userCheqBal = newTotal;
                            rewriteFile();
                            return 0;
                        }
                    }
                    double newTotal;
                    newTotal = userAcct.cashWithdrawal(userCheqBal, withdrawAmt);
                    //update balance and tell user their action is completed
                    std::cout << "Withdraw Complete" << std::endl;
                    std::ostringstream strs;
                    strs << withdrawAmt;
                    std::string str = strs.str();
                    checkRecording(getClientName(user) + " withdrew " + str + " from chequings account.");
                    userCheqBal = newTotal;
                    rewriteFile();
                    return 0;
                }
            }
            //withdraw from savings
            else if (account == 1) {
                //check if account is closed
                if (std::stod(getSavBal(user)) == 0) {
                    std::cout << "Cannot withdraw from a closed account, contact your bank manager to open!" << std::endl;
                    checkRecording(getClientName(user) +  " tried to withdraw from closed savings account.");
                    return 0;
                }
                std::cout << "Enter amount to withdraw" << std::endl;
                double withdrawAmt;
                std::cin >> withdrawAmt;
                //check for sufficient funds
                if (userAcct.cashWithdrawal(userSavBal, withdrawAmt) < 0) {
                    std::cout << "Insufficient Funds to withdraw from savings account." << std::endl;
                    checkRecording(getClientName(user) +  " tried to withdraw from a savings account that had insufficient funds.");
                    return 0;
                }
                else {
                    double newTotal;
                    newTotal = userAcct.cashWithdrawal(userSavBal, withdrawAmt);

                    std::cout << "Withdraw Complete" << std::endl;
                    std::ostringstream strs;
                    strs << withdrawAmt;
                    std::string str = strs.str();
                    checkRecording(getClientName(user) +  " withdrew " + str + " from their savings account.");
                    userSavBal = newTotal;
                    rewriteFile();
                    return 0;
                }
            } else {
                normalUser(user, 0);
            }
        }
        std::ostringstream strs;
        strs << withdrawAmt;
        std::string str = strs.str();
        checkRecording(getClientName(user) +  " withdrew " + str + " from their savings account.");
        userSavBal = newTotal;
        rewriteFile();
        return 0;

        std::ostringstream strs;
        strs << withdrawAmt;
        std::string str = strs.str();
        checkRecording(getClientName(user) +  " withdrew " + str + " from their savings account.");
        userSavBal = newTotal;
        rewriteFile();
        return 0;
