#include <iostream>

using namespace std;

int main()
{
    cout << "Enter a positive number: ";

    int num;
    int tekija2 = 1;
    int tallennettu_jakaja = 1;

    cin >> num;

    int a = num;

    if (num <= 0) {
        cout << "Only positive numbers accepted" << endl;
    }

    if (num > 0) {



        for (int tekija1 = 1; tekija1 <= num; ++tekija1) {

            if (num % tekija1 == 0) {
                tekija2 = num / tekija1;

                int ero = abs(tekija1 - tekija2);

                if (ero <= a) {
                    a = ero;
                    tallennettu_jakaja = tekija1;
                }
            }
        }

        cout << num << " = " << num / tallennettu_jakaja << " * " << tallennettu_jakaja << endl;
    }

    return 0;
}
