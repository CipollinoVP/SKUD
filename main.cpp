#include <iostream>
#include "LoginApp.h"
#include "MessengerApp.h"
#include "SecurityApp.h"
#include "SinglePassApp.h"
#include "DirectorApp.h"
#include "MenuApp.h"

int main(int argc, char *argv[]) {
    login_window(argc,argv);
    if (type_user == CLOSE_LOGIN_APP) {
        return 0;
    }
    int next_app = NO_APP;
    int previous_app = MAIN_APP;
    main_menu(argc,argv,next_app);
    std::cout << next_app << std::endl;
    return 0;
}
