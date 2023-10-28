#ifndef BOOK_HH
#define BOOK_HH
#include <string>
#include "date.hh"

class Book
{
public:
    Book();

    Book(std::string book_author, std::string book_name);

    void print() const;

    void loan(Date& date);

    void renew();

    void give_back();


private:
    std::string book_author_;
    std::string book_name_;


    bool loaned_ = false;
    Date loan_date_;
    Date return_date_;

};

#endif // BOOK_HH
