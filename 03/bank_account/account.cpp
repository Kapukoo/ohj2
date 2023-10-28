#include "account.hh"
#include <iostream>

Account::Account(const std::string& owner, bool has_credit):
    owner_(owner), has_credit_(has_credit)
{
    generate_iban();
}

// Setting initial value for the static attribute running_number_
int Account::running_number_ = 0;

void Account::generate_iban()
{
    ++running_number_;
    std::string suffix = "";
    if(running_number_ < 10)
    {
        suffix.append("0");
    }
    else if(running_number_ > 99)
    {
        std::cout << "Too many accounts" << std::endl;
    }
    suffix.append(std::to_string(running_number_));

    iban_ = "FI00 1234 ";
    iban_.append(suffix);
}

void Account::print() const {
    std::cout << owner_ << " : " << iban_ << " : " << account_balance << " euros" <<std::endl;
}

void Account::set_credit_limit(int limit) {
    if (has_credit_ == true) {
        credit_limit = limit;
    } else {
        std::cout << "Cannot set credit limit: the account has no credit card" << std::endl;
    }
}

void Account::save_money(int money) {
    account_balance += money;
}

bool Account::take_money(int money_taken) {
    int credit = 0;
    if (has_credit_ == true) {
        credit = credit_limit;
    }


    if (account_balance + credit < money_taken) {
        std::cout << "Cannot take money: balance underflow" << std::endl;
        return false;

    } else {
        account_balance -= money_taken;
        std::cout << money_taken
                  << " euros taken: new balance of "
                  << iban_
                  << " is "
                  << account_balance
                  << " euros"
                  << std::endl;
        return true;
    }
}

void Account::transfer_to(Account& account, int amount) {
    if ( take_money(amount) == true) {


        account.save_money(amount);
    } else {
        std::cout << "Transfer from " << iban_ << " Failed" << std::endl;
    }
}
