#include "book.hh"
#include <iostream>
#include <date.hh>

Book::Book(std::string book_author, std::string book_name):
    book_author_(book_author), book_name_(book_name)
{

}

void Book::print() const {
    std::cout << book_author_ << " : " << book_name_ << std::endl;
    bool loaned = loaned_;


    if (loaned == false) {
        std::cout << "- available" << std::endl;
    }
    if (loaned == true) {

        std::cout << "- loaned: "; loan_date_.print();



        std::cout << "- to be returned: "; return_date_.print();
    }

}

void Book::renew() {
    if (loaned_ == true) {
        return_date_.advance(28);
    }
    if ( loaned_ == false) {
        std::cout << "Not loaned: cannot be renewed" << std::endl;
    }
}

void Book::loan(Date& date) {
    bool loaned = loaned_;

    if (loaned == false) {

        loan_date_ = date;
        loaned_ = true;

        return_date_ = date;
        return_date_.advance(28);

    } else {
        std::cout << "Already loaned: cannot be loaned" << std::endl;
    }
}

void Book::give_back() {
    loaned_ = false;
}
