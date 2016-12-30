#ifndef ACCOUNTS_H
#define ACCOUNTS_H

#include <string>


class accounts {
    private:
        double t_cheBal;
        double t_savBal;

    public:
        //constructor
        accounts(double m_cheBal, double m_savBal);

        double cashWithdrawal(double accBal, double amount);
        double deposit(double accBal, double amount);
        double transferFrom(double fromAccount, double destinationAccount, double amount);
        double transferTo(double fromAccount, double destinationAccount, double amount);
};


#endif
