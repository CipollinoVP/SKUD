//
// Created by student on 10.08.2022.
//

#ifndef SKUD_MENUAPP_H
#define SKUD_MENUAPP_H
#include "main_settings.h"

GtkWidget *WindowWelcome;
GtkWidget *SinglePassSystem;
GtkWidget *MainMenuMessengerButton;
GtkWidget *AdminButton;
GtkWidget *RegisterButton;
GtkWidget *ChangePasswordButton;
GtkWidget *MainExitButton;

static void create_main_menu_window();

static void create_main_menu_window(){
    GtkBuilder *builder;
    GError* error = nullptr;

    builder = gtk_builder_new();
    if(!gtk_builder_add_from_file(builder, path_glade, &error)){
        g_critical("Не могу загрузить файл: %s", error->message);
        g_error_free(error);
    }

    gtk_builder_connect_signals(builder, nullptr);
    if(!(WindowWelcome = GTK_WIDGET(gtk_builder_get_object(builder, "LoginWindow"))))
        g_critical("Ошибка при получении виджета окна\n");
    if(!(LoginEntryA = GTK_WIDGET(gtk_builder_get_object(builder, "LoginEntry"))))
        g_critical("Ошибка при получении виджета окна\n");
    if(!(PasswordEntryA = GTK_WIDGET(gtk_builder_get_object(builder, "PasswordEntry"))))
        g_critical("Ошибка при получении виджета окна\n");
    if(!(StatusLoginA = GTK_WIDGET(gtk_builder_get_object(builder, "StatusLogin"))))
        g_critical("Ошибка при получении виджета окна\n");
    if(!(LoginButtonA = GTK_WIDGET(gtk_builder_get_object(builder, "LoginButton"))))
        g_critical("Ошибка при получении виджета окна\n");
    g_object_unref(builder);
}


#endif //SKUD_MENUAPP_H
