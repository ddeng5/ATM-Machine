#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <stdio.h>
#include <ctime>
#include "accounts.h"


std::string uniqueUserID;
double userCheqBal;
double userSavBal;
int userRole;
double totalCheqBank = 0;
double totalSavBank = 0;
std::string clientName;
int numberOfUsers;

int recording;


std::string decrypt(std::string code) {
    long randomizer = 100;



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
