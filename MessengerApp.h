//
// Created by student on 08.08.2022.
//

#ifndef SINGLEPASSSYSTEM_MESSENGERAPP_H
#define SINGLEPASSSYSTEM_MESSENGERAPP_H

#include "main_settings.h"

GtkWidget *MessengerWindow;
GtkWidget *InputMessagesShowButton;
GtkWidget *OutputMessagesShowButton;
GtkWidget *WriteMessageButton;
GtkWidget *ReadMessageGrid;
GtkWidget *MessageLabel;
GtkWidget *DataLabel;
GtkWidget *RecipientLabel;
GtkWidget *SenderLabel;
GtkWidget *TitleMessageLabel;
GtkWidget *EnterMessageGrid;
GtkWidget *AdressatEntry;
GtkWidget *TitleEntry;
GtkWidget *MessageEntry;
GtkWidget *WidgetListMessages;
GtkWidget *ListMessages;
GtkWidget *BackButton;
GtkWidget *SendButton;
GtkWidget *StatusLabelMessenger;
GObject *SenderColumn;

static void create_messenger_window();

void messenger();

G_MODULE_EXPORT void Input_Show_Press(GtkWidget *object);

G_MODULE_EXPORT void Output_Show_Press(GtkWidget *object);

G_MODULE_EXPORT void Write_Button_Press(GtkWidget *object);

G_MODULE_EXPORT void Back_Button_Press(GtkWidget *object);

G_MODULE_EXPORT void Send_Button_Press(GtkWidget *object);

G_MODULE_EXPORT void Select_Message_Press(GtkWidget *object);

struct s_message{
    int id;
    std::string user_send;
    std::string title;
    std::string time_message;
    bool read_status = false;
};

std::vector<s_message> list_message(0);

int select_message = -1;

static void create_messenger_window(){
    GtkBuilder *builder;
    GError* error = nullptr;

    builder = gtk_builder_new();
    if(!gtk_builder_add_from_file(builder, path_glade, &error)){
        g_critical("Не могу загрузить файл: %s", error->message);
        g_error_free(error);
    }

    gtk_builder_connect_signals(builder, nullptr);

    if(!(MessengerWindow = GTK_WIDGET(gtk_builder_get_object(builder, "MessengerWindow"))))
        g_critical("Ошибка при получении виджета окна\n");
    if(!(InputMessagesShowButton = GTK_WIDGET(gtk_builder_get_object(builder, "InputMessagesShowButton"))))
        g_critical("Ошибка при получении виджета окна\n");
    if(!(OutputMessagesShowButton = GTK_WIDGET(gtk_builder_get_object(builder, "OutputMessagesShowButton"))))
        g_critical("Ошибка при получении виджета окна\n");
    if(!(WriteMessageButton = GTK_WIDGET(gtk_builder_get_object(builder, "WriteMessageButton"))))
        g_critical("Ошибка при получении виджета окна\n");
    if(!(MessageLabel = GTK_WIDGET(gtk_builder_get_object(builder, "MessageLabel"))))
        g_critical("Ошибка при получении виджета окна\n");
    if(!(DataLabel = GTK_WIDGET(gtk_builder_get_object(builder, "DataLabel"))))
        g_critical("Ошибка при получении виджета окна\n");
    if(!(RecipientLabel = GTK_WIDGET(gtk_builder_get_object(builder, "RecipientLabel"))))
        g_critical("Ошибка при получении виджета окна\n");
    if(!(SenderLabel = GTK_WIDGET(gtk_builder_get_object(builder, "SenderLabel"))))
        g_critical("Ошибка при получении виджета окна\n");
    if(!(TitleMessageLabel = GTK_WIDGET(gtk_builder_get_object(builder, "TitleMessageLabel"))))
        g_critical("Ошибка при получении виджета окна\n");
    if(!(EnterMessageGrid = GTK_WIDGET(gtk_builder_get_object(builder, "EnterMessageGrid"))))
        g_critical("Ошибка при получении виджета окна\n");
    if(!(AdressatEntry = GTK_WIDGET(gtk_builder_get_object(builder, "AdressatEntry"))))
        g_critical("Ошибка при получении виджета окна\n");
    if(!(TitleEntry = GTK_WIDGET(gtk_builder_get_object(builder, "TitleEntry"))))
        g_critical("Ошибка при получении виджета окна\n");
    if(!(MessageEntry = GTK_WIDGET(gtk_builder_get_object(builder, "MessageEntry"))))
        g_critical("Ошибка при получении виджета окна\n");
    if(!(WidgetListMessages = GTK_WIDGET(gtk_builder_get_object(builder, "WidgetListMessages"))))
        g_critical("Ошибка при получении виджета окна\n");
    if(!(ListMessages = GTK_WIDGET(gtk_builder_get_object(builder, "ListMessages"))))
        g_critical("Ошибка при получении виджета окна\n");
    if(!(SendButton = GTK_WIDGET(gtk_builder_get_object(builder, "SendButton"))))
        g_critical("Ошибка при получении виджета окна\n");
    if(!(BackButton = GTK_WIDGET(gtk_builder_get_object(builder, "BackButton"))))
        g_critical("Ошибка при получении виджета окна\n");
    if(!(ReadMessageGrid = GTK_WIDGET(gtk_builder_get_object(builder, "ReadMessageGrid"))))
        g_critical("Ошибка при получении виджета окна\n");
    if(!(StatusLabelMessenger = GTK_WIDGET(gtk_builder_get_object(builder, "StatusLabelMessenger"))))
        g_critical("Ошибка при получении виджета окна\n");
    if(!(SenderColumn = gtk_builder_get_object(builder, "SenderRecipientColumn")))
        g_critical("Ошибка при получении виджета окна\n");
    g_object_unref(builder);

}

void messenger(){
    create_messenger_window();
    g_signal_connect(G_OBJECT(InputMessagesShowButton),"clicked",G_CALLBACK(Input_Show_Press),NULL);
    g_signal_connect(G_OBJECT(OutputMessagesShowButton),"clicked",G_CALLBACK(Output_Show_Press),NULL);
    g_signal_connect(G_OBJECT(WriteMessageButton),"clicked",G_CALLBACK(Write_Button_Press),NULL);
    g_signal_connect(G_OBJECT(BackButton),"clicked",G_CALLBACK(Back_Button_Press),NULL);
    g_signal_connect(G_OBJECT(SendButton),"clicked",G_CALLBACK(Send_Button_Press),NULL);
    g_signal_connect(G_OBJECT(ListMessages),"row-activated",G_CALLBACK(Select_Message_Press),NULL);
    gtk_widget_show(MessengerWindow);
}

void Input_Show_Press(GtkWidget *object){
    gtk_widget_set_visible(GTK_WIDGET(ReadMessageGrid),false);
    gtk_widget_set_visible(GTK_WIDGET(WidgetListMessages),true);
    gtk_widget_set_visible(GTK_WIDGET(EnterMessageGrid),false);
    gtk_tree_view_column_set_title(GTK_TREE_VIEW_COLUMN(SenderColumn),"Отправитель");
    std::stringstream query;
    query << "SELECT id,id_sender,title,read_status,time_send FROM messages WHERE id_recepient = "
          << id_user << " ORDER BY time_send;";
    GtkListStore *list_view_message = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(ListMessages)));
    gtk_list_store_clear(list_view_message);
    PGresult *res = PQexec(conn,query.str().c_str());
    int n = PQntuples(res);
    list_message.clear();
    for (int i = 0; i < n; ++i) {
        s_message message;
        message.id = std::stoi(std::string(PQgetvalue(res,i,0)));
        std::stringstream query_user;
        query_user << "SELECT login_database FROM registers_user WHERE id = " << std::string(PQgetvalue(res,i,1)) << ";";
        message.user_send = PQgetvalue(PQexec(conn,query_user.str().c_str()),0,0);
        message.title = PQgetvalue(res,i,2);
        char *s = PQgetvalue(res,i,3);
        if (s[0] == 'f') {
            message.read_status = false;
        } else {
            message.read_status = true;
        }
        message.time_message = PQgetvalue(res,i,4);
        list_message.push_back(message);
        GtkTreeIter iter;
        gtk_list_store_append(list_view_message,&iter);
        gtk_list_store_set(list_view_message,&iter,0,message.time_message.c_str(),
                           1,message.user_send.c_str(),2,message.title.c_str(),-1);
    }
};

void Output_Show_Press(GtkWidget *object){
    gtk_widget_set_visible(GTK_WIDGET(ReadMessageGrid),false);
    gtk_widget_set_visible(GTK_WIDGET(WidgetListMessages),true);
    gtk_widget_set_visible(GTK_WIDGET(EnterMessageGrid),false);
    gtk_tree_view_column_set_title(GTK_TREE_VIEW_COLUMN(SenderColumn),"Получатель");
    std::stringstream query;
    query << "SELECT id,id_recepient,title,read_status,time_send FROM messages WHERE id_sender = "
          << id_user << " ORDER BY time_send;";
    GtkListStore *list_view_message = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(ListMessages)));
    gtk_list_store_clear(list_view_message);
    PGresult *res = PQexec(conn,query.str().c_str());
    int n = PQntuples(res);
    list_message.clear();
    for (int i = 0; i < n; ++i) {
        s_message message;
        message.id = std::stoi(std::string(PQgetvalue(res,i,0)));
        std::stringstream query_user;
        query_user << "SELECT login_database FROM registers_user WHERE id = "
                   << std::string(PQgetvalue(res,i,1)) << ";";
        message.user_send = PQgetvalue(PQexec(conn,query_user.str().c_str()),0,0);
        message.title = PQgetvalue(res,i,2);
        char *s = PQgetvalue(res,i,3);
        if (s[0] == 'f') {
            message.read_status = false;
        } else {
            message.read_status = true;
        }
        message.time_message = PQgetvalue(res,i,4);
        list_message.push_back(message);
        GtkTreeIter iter;
        gtk_list_store_append(list_view_message,&iter);
        gtk_list_store_set(list_view_message,&iter,0,message.time_message.c_str(),
                           1,message.user_send.c_str(),2,message.title.c_str(),-1);
    }
};

void Write_Button_Press(GtkWidget *object){
    gtk_widget_set_visible(GTK_WIDGET(ReadMessageGrid),false);
    gtk_widget_set_visible(GTK_WIDGET(WidgetListMessages),false);
    gtk_widget_set_visible(GTK_WIDGET(EnterMessageGrid), true);
};

void Back_Button_Press(GtkWidget *object){
    gtk_window_close(GTK_WINDOW(MessengerWindow));
};

void Send_Button_Press(GtkWidget *object){
    std::string message = gtk_entry_get_text(GTK_ENTRY(MessageEntry));
    std::string title = gtk_entry_get_text(GTK_ENTRY(TitleEntry));
    std::string adressat = gtk_entry_get_text(GTK_ENTRY(AdressatEntry));
    std::stringstream query1;
    query1 << "SELECT id FROM registers_user WHERE login_database = '" <<
           adressat << "';";
    PGresult *res = PQexec(conn,query1.str().c_str());
    char *rs = PQgetvalue(res,0,0);
    if (rs == nullptr) {
        gtk_label_set_text(GTK_LABEL(StatusLabelMessenger),"Не существует адресат");
        return;
    }
    int n_a = std::stoi(std::string(rs));
    std::stringstream  query2;
    query2 << "INSERT INTO messages (title,message,id_sender,id_recepient) VALUES (";
    query2 << "'" << title << "','" << message << "'," << id_user << "," << n_a << ");";
    PQexec(conn,query2.str().c_str());
    gtk_entry_set_text(GTK_ENTRY(MessageEntry),"");
    gtk_entry_set_text(GTK_ENTRY(TitleEntry),"");
    gtk_entry_set_text(GTK_ENTRY(AdressatEntry),"");
    gtk_label_set_text(GTK_LABEL(StatusLabelMessenger),"Сообщение отправлено");
};

void Select_Message_Press(GtkWidget *object){
    GtkTreePath *path;
    GtkTreeViewColumn *column;
    gtk_tree_view_get_cursor(GTK_TREE_VIEW(object),&path,&column);
    int* a = gtk_tree_path_get_indices(path);
    if (a == nullptr) {
        select_message = -1;
        return;
    }
    select_message = *a;
    gtk_widget_set_visible(GTK_WIDGET(ReadMessageGrid),true);
    gtk_widget_set_visible(GTK_WIDGET(WidgetListMessages),false);
    gtk_widget_set_visible(GTK_WIDGET(EnterMessageGrid), false);
    std::stringstream query;
    query << "SELECT id_sender,id_recepient,title,message,time_send FROM messages WHERE id = " <<
          list_message[select_message].id << ";";
    PGresult *res = PQexec(conn,query.str().c_str());
    std::string login_sender;
    std::stringstream query_user;
    query_user << "SELECT login_database FROM registers_user WHERE id = "
               << std::string(PQgetvalue(res,0,0)) << ";";
    login_sender = PQgetvalue(PQexec(conn,query_user.str().c_str()),0,0);
    std::string login_recepient;
    std::stringstream query_user2;
    query_user2 << "SELECT login_database FROM registers_user WHERE id = "
                << std::string(PQgetvalue(res,0,1)) << ";";
    login_recepient = PQgetvalue(PQexec(conn,query_user2.str().c_str()),0,0);
    std::string title = PQgetvalue(res,0,2);
    std::string message = PQgetvalue(res,0,3);
    std::string time_send = PQgetvalue(res,0,4);
    gtk_label_set_text(GTK_LABEL(MessageLabel),message.c_str());
    gtk_label_set_text(GTK_LABEL(SenderLabel),login_sender.c_str());
    gtk_label_set_text(GTK_LABEL(RecipientLabel),login_recepient.c_str());
    gtk_label_set_text(GTK_LABEL(TitleMessageLabel),title.c_str());
    gtk_label_set_text(GTK_LABEL(DataLabel),time_send.c_str());
};


#endif //SINGLEPASSSYSTEM_MESSENGERAPP_H
