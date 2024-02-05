#include <iostream>
#include <string>
#include <unistd.h>

using namespace std;

int main() {

    string username,password,correctPass = "password";

    int waitTime = 5;

    cout << "Your username: ";
    cin >> username;

    cout << "Your password: ";
    cin >> password;

    while (waitTime >= 0) {
        
        sleep(1);
        cout << "Checking... " << waitTime;
        waitTime -= 1;

    };

    if (password == correctPass) {

        cout << "Welcome, " << username + "! \n";

    } else {
        
        cout << "\033[1;31mWrong password, try again!\033[0m\n";

    };

    return 0;
}
