#include <cmath>
#include <iostream>
#include <unistd.h>

using namespace std;

int main(int argc, char* argv[]) {

    string username,password;
    string correctPass = "password";

    cout << "Your username: ";
    cin >> username;

    cout << "Your password: ";
    cin >> password;

    if (password == correctPass) {

        cout << "Welcome, " + username + "!\n";

    };

    return 0;
}
