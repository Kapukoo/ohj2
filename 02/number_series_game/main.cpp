#include <iostream>

using namespace std;

int main()
{
    std::cout << "How many numbers would you like to have? ";

    int nums = 0;

    cin >> nums;

    for (int rivi = 1; rivi <= nums; ++rivi){

        if (rivi % 3 == 0 and rivi % 7 == 0) {
            cout << "zip boing" << endl;
            continue;
        }

        if (rivi % 3 == 0){
            cout << "zip" << endl;
            continue;
        }

        if (rivi % 7 == 0) {
            cout << "boing" << endl;
            continue;
        }

        cout << rivi << endl;
    }

    return 0;
}
