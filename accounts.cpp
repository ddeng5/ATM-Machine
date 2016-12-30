#include "accounts.h"
#include <string>

accounts::accounts(double m_cheBal, double m_savBal) {

}

double accounts::cashWithdrawal(double accBal, double amount) {
    return accBal - amount;
}

double accounts::deposit(double accBal, double amount) {
    return (accBal + amount);
}

double accounts::transferFrom(double fromAccount, double destinationAccount, double amount) {
    return (fromAccount - amount);
}

double accounts::transferTo(double fromAccount, double destinationAccount, double amount) {
    return (destinationAccount + amount);
}