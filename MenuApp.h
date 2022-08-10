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
GtkWidget *WorkersSystemButton;

static void create_main_menu_window();

int main_menu(int argc, char *argv[], int& open_next_window);

G_MODULE_EXPORT void click_admin_button(GtkWidget *object);

G_MODULE_EXPORT void click_registration_button(GtkWidget *object);

G_MODULE_EXPORT void click_change_password_button(GtkWidget *object);

G_MODULE_EXPORT void click_workers_system_button(GtkWidget *object);

G_MODULE_EXPORT void click_single_pass_system_button(GtkWidget *object);

G_MODULE_EXPORT void click_menu_messenger_button(GtkWidget *object);

G_MODULE_EXPORT void destroy_menu_window(GtkWidget *object);

int main_menu_next = NO_APP;

static void create_main_menu_window(){
    GtkBuilder *builder;
    GError* error = nullptr;

    builder = gtk_builder_new();
    if(!gtk_builder_add_from_file(builder, path_glade, &error)){
        g_critical("Не могу загрузить файл: %s", error->message);
        g_error_free(error);
    }

    gtk_builder_connect_signals(builder, nullptr);
    if(!(WindowWelcome = GTK_WIDGET(gtk_builder_get_object(builder, "WindowWelcome"))))
        g_critical("Ошибка при получении виджета окна\n");
    g_signal_connect(G_OBJECT(WindowWelcome),"destroy",G_CALLBACK(destroy_menu_window),NULL);
    g_signal_connect(G_OBJECT(WindowWelcome),"destroy-event",G_CALLBACK(destroy_menu_window),NULL);
    if(!(SinglePassSystem = GTK_WIDGET(gtk_builder_get_object(builder, "SinglePassSystem"))))
        g_critical("Ошибка при получении виджета окна\n");
    g_signal_connect(G_OBJECT(SinglePassSystem),"clicked",G_CALLBACK(click_single_pass_system_button),NULL);
    if(!(MainMenuMessengerButton = GTK_WIDGET(gtk_builder_get_object(builder, "MainMenuMessengerButton"))))
        g_critical("Ошибка при получении виджета окна\n");
    g_signal_connect(G_OBJECT(MainMenuMessengerButton),"clicked",G_CALLBACK(click_menu_messenger_button),NULL);
    if(!(ChangePasswordButton = GTK_WIDGET(gtk_builder_get_object(builder, "ChangePasswordButton"))))
        g_critical("Ошибка при получении виджета окна\n");
    g_signal_connect(G_OBJECT(ChangePasswordButton),"clicked",G_CALLBACK(click_change_password_button),NULL);
    if(!(MainExitButton = GTK_WIDGET(gtk_builder_get_object(builder, "MainExitButton"))))
        g_critical("Ошибка при получении виджета окна\n");
    g_signal_connect(G_OBJECT(MainExitButton),"clicked",G_CALLBACK(destroy_menu_window),NULL);
    if (type_user == ADMIN) {
        if (!(AdminButton = GTK_WIDGET(gtk_builder_get_object(builder, "AdminButton"))))
            g_critical("Ошибка при получении виджета окна\n");
        gtk_widget_set_visible(AdminButton,true);
        g_signal_connect(G_OBJECT(AdminButton),"clicked",G_CALLBACK(click_admin_button),NULL);
        if (!(RegisterButton = GTK_WIDGET(gtk_builder_get_object(builder, "RegisterButton"))))
            g_critical("Ошибка при получении виджета окна\n");
        gtk_widget_set_visible(RegisterButton,true);
        g_signal_connect(G_OBJECT(RegisterButton),"clicked",G_CALLBACK(click_registration_button),NULL);
    }
    if ((type_user == CHECKPOINT_AFOOT) || (type_user == CHECKPOINT_CAR) || (type_user == MATCHING_BOSS) ||
            (type_user == ORDER_BOSS)) {
        if (!(WorkersSystemButton = GTK_WIDGET(gtk_builder_get_object(builder, "WorkersSystemButton"))))
            g_critical("Ошибка при получении виджета окна\n");
        gtk_widget_set_visible(WorkersSystemButton,true);
        g_signal_connect(G_OBJECT(WorkersSystemButton),"clicked",G_CALLBACK(click_workers_system_button),NULL);
    }
    g_object_unref(builder);
}

int main_menu(int argc, char *argv[], int& open_next_window){
    main_menu_next = NO_APP;
    create_main_menu_window();
    gtk_widget_show(WindowWelcome);
    gtk_main();
    open_next_window = main_menu_next;
    return 0;
}

G_MODULE_EXPORT void click_admin_button(GtkWidget *object){
    main_menu_next = ADMIN_APP;
    gtk_window_close(GTK_WINDOW(WindowWelcome));
}

G_MODULE_EXPORT void click_registration_button(GtkWidget *object){
    main_menu_next = REGISTER_APP;
    gtk_window_close(GTK_WINDOW(WindowWelcome));
}

G_MODULE_EXPORT void click_change_password_button(GtkWidget *object){
    main_menu_next = CHANGE_PASSWORD_APP;
    gtk_window_close(GTK_WINDOW(WindowWelcome));
}

G_MODULE_EXPORT void click_workers_system_button(GtkWidget *object){
    if ((type_user == CHECKPOINT_CAR) || (type_user == CHECKPOINT_AFOOT)) {
        main_menu_next = SECURITY_APP;
    }
    else if ((type_user == CHECKPOINT_CAR) || (type_user == CHECKPOINT_AFOOT)){
        main_menu_next = DIRECTOR_APP;
    }
    gtk_window_close(GTK_WINDOW(WindowWelcome));
}

G_MODULE_EXPORT void click_single_pass_system_button(GtkWidget *object){
    main_menu_next = SINGLE_PASS_SYSTEM_APP;
    gtk_window_close(GTK_WINDOW(WindowWelcome));
}

G_MODULE_EXPORT void click_menu_messenger_button(GtkWidget *object){
    main_menu_next = MESSENGER_APP;
    gtk_window_close(GTK_WINDOW(WindowWelcome));
}

G_MODULE_EXPORT void destroy_menu_window(GtkWidget *object){
    gtk_main_quit();
}


#endif //SKUD_MENUAPP_H
