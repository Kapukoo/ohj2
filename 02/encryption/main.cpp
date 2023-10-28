#include <iostream>
#include <string>
#include <cctype>

using namespace std;

int main()
{
    cout << "Enter the encryption key: ";

    string key = "";
    cin >> key;

    string::size_type key_lenght = key.length();

    if (key_lenght != 26) {
        cout << "Error! The encryption key must contain 26 characters." << endl;
        return EXIT_FAILURE;
     }

    for (int i = 0; i <= 26; i++) {
        if (isupper(key[i])) {
            cout << "Error! The encryption key must contain only lower case characters." << endl;
            return EXIT_FAILURE;
        }
    }

    for (char kirjain = 'a'; kirjain <= 'z'; ++kirjain ){

        string::size_type apu = key.find(kirjain);

        if (apu == string::npos) {
            cout << "Error! The encryption key must contain all alphabets a-z." << endl;
            return EXIT_FAILURE;
        }

    }

    cout << "Enter the text to be encrypted: ";

    string text = "";
    cin >> text;

    for (int i = 0; i <= 26; i++) {
        if (isupper(text[i])) {
            cout << "Error! The text to be encrypted must contain only lower case characters." << endl;
            return EXIT_FAILURE;
        }
    }

    string crypt_text = "";

    string::size_type text_lenght = text.length();

    for ( unsigned int j = 0; j < text_lenght; j++) {

        int calc = 0;

        for ( char kirjain = 'a'; kirjain < text[j]; ++kirjain ) {
            calc += 1;
        }
        crypt_text += key[calc];
    }

    cout << "Encrypted text: " << crypt_text << endl;

    return 0;
}
