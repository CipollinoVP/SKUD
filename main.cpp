#include <iostream>
#include "LoginApp.h"
#include "MessengerApp.h"
#include "SecurityApp.h"
#include "SinglePassApp.h"
#include "DirectorApp.h"

int main(int argc, char *argv[]) {
    login_window(argc,argv);
    if (type_user == CLOSE_LOGIN_APP) {
        return 0;
    }

    std::cout << "Hello, World!" << std::endl;
    return 0;
}
