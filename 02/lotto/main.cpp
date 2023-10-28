#include <iostream>

using namespace std;

int factorial(int luku) {

    unsigned long int fact = 1;

    for (int i = 1; i <= luku; ++i) {
        fact *= i;
        //cout << fact << endl;
    }

    return fact;
}

int propability(int kaikki, int nostettavat) {

    //unsigned long int a = factorial(kaikki);
    //unsigned long int b = factorial(kaikki - nostettavat);
    //unsigned long int c = factorial(nostettavat);
    //long long d = b * c;
    //cout << b*c << endl;

    int i = 0;
    int k = 1;

    while (i < nostettavat) {
        unsigned long int a = kaikki - i;
        k *= a;

        i++;

    }

    unsigned long int prob = k / factorial(nostettavat);
    return prob;
}



int main()
{
    cout << "Enter the total number of lottery balls: ";

    int lottery_balls = 0;
    cin >> lottery_balls;

    cout << "Enter the number of drawn balls: ";

    int drawn_balls = 0;
    cin >> drawn_balls;

    if (lottery_balls < 0) {
        cout << "The number of balls must be a positive number." << endl;
        return 0;
    }

    if (drawn_balls < 0) {
        cout << "The number of balls must be a positive number." << endl;
        return 0;
    }

    if (drawn_balls > lottery_balls) {
        cout << "The maximum number of drawn balls is the total amount of balls." << endl;
        return 0;
    }

    cout << "The probability of guessing all " << drawn_balls << " balls correctly is 1/" <<
            propability(lottery_balls, drawn_balls) << endl;



    return 0;
}
