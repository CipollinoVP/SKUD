//
// Created by vadik on 27.07.22.
//

#ifndef INC_345MF_POSTGRES_H
#define INC_345MF_POSTGRES_H

#include <libpq-fe.h>
#include "fstream"
#include <string>
#include "sstream"
#include <unistd.h>
#include <gtk/gtk.h>
#include <vector>
#include <filesystem>

#define CHECKPOINT_AFOOT 1
#define CHECKPOINT_CAR 2
#define ORDER_BOSS 3
#define ORDER_TENANT 4
#define MATCHING_BOSS 5
#define ADMIN 6
#define CLOSE_LOGIN_APP 0

#define SINGLE_PASS_SYSTEM 0
#define DIRECTOR_APP 1
#define SYS_ADMIN_APP 2
#define MESSENGER_APP 3
#define SECURITY_APP 4
#define MAIN_APP 5
#define NO_APP -1

int type_user = 0;

std::string login;

int id_worker;

int id_user;

std::ofstream journal("./log.txt",std::ios::app);

int open_app = -1;

void journal_init(){
    if (!journal) {
        journal = std::ofstream("./log.txt");
    }
}

//Основное соединение приложения
PGconn* conn;

struct s_single_pass{
    int id = 0;
    std::string surname;
    std::string name;
    std::string fathername;
    bool status_factory = false;
    int id_director = 0;
    std::string type_document;
    std::string number_document;
    bool status_pass = false;
    std::string organization;
    std::string date_query;
    std::string time_query;
    std::string date_pass;
    std::string time_pass;
    std::string enter_time;
    std::string exit_time;
    bool pass_using = false;
    bool driver = false;
    std::string num_auto;
    std::string organization_custom;
    int status_appology = -1;
    std::string commentary;
};

char* const path_glade = "./Application.xml";

#endif //INC_345MF_POSTGRES_H
