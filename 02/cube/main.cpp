#include <iostream>

using namespace std;

int main()
{
    cout << "Enter a number: ";

    int num;
    cin >> num;

    int potenssi = num * num *num;

    if ( potenssi >= num ) {
        cout << "The cube of " << num << " is " << potenssi << "." << endl;

    } else {
        cout << "Error! the cube of " << num << " is not " << potenssi << endl;
    }


    return 0;
}
