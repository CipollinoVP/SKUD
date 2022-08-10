//
// Created by student on 04.08.2022.
//

#ifndef SINGLEPASSSYSTEM_SINGLEPASSAPP_H
#define SINGLEPASSSYSTEM_SINGLEPASSAPP_H

#include "main_settings.h"
#include "OrderPassApp.h"
#include "MessengerApp.h"

//Режимы вывода информации
#define ADMIT 1
#define LET 2
#define SHOW_MY 3
#define APOLOGY 4
#define FUTURE 5
#define HISTORY 6

int output_mode = 0;

int selected = -1;

//Виджеты окна разовых пропусков
GtkWidget *WindowMain;
GtkWidget *OrderSinglePassButton;
GtkWidget *ShowPersonalPassButton;
GtkWidget *HistoryPassesButton;
GtkWidget *ApprovalPassesButton;
GtkWidget *AdmitButton;
GtkWidget *LetButton;
GtkWidget *FuturePassButton;
GtkWidget *MessengerButton;
GtkWidget *ExitButton;
GtkWidget *AcceptButton;
GtkWidget *CancelButton;
GtkWidget *DeclineButton;
GtkWidget *SurnameSearchEntry;
GtkWidget *NameSearchEntry;
GtkWidget *FathernameSearchEntry;
GtkWidget *DocumentSearchEntry;
GtkWidget *CarNumberEntry;
GtkWidget *StatusLabel;
GObject *TypeDocumentColumn;
GObject *NumDocumentColumn;
GObject *NumCarColumn;
GObject *NameOrdererColumn;
GObject *StatusApologyColumn;
GObject *OrderOrganizationColumn;
GObject *EnteringOrganizationColumn;
GObject *DateOrderColumn;
GObject *TimeOrderColumn;
GObject *CommentaryColumn;
GObject *EnterTimeColumn;
GObject *ExitTimeColumn;
GtkWidget *HintLabel;
GtkWidget *GridDocument;
GtkWidget *GridCar;
GtkWidget *EditOrderButton;
GtkWidget *ReSendOrderButton;
GtkWidget *CheckpointButton;
GtkWidget *PassesView;

//Виджеты диалога отказа
GtkWidget *CommentaryDeclineEntry;
GtkWidget *CancelButtonDialog2;
GtkWidget *DeclineButtonDialog;
GtkWidget *DeclineDialog;

static void create_window_SinglePassApp();

int SinglePassApp(int argc, char *argv[]);

G_MODULE_EXPORT void window_single_pass_destroy(GtkWidget *object);

G_MODULE_EXPORT void OrderSinglePassButton_click(GtkWidget *object);

G_MODULE_EXPORT void ShowPersonalPassButton_click(GtkWidget *object);

G_MODULE_EXPORT void HistoryPassesButton_click(GtkWidget *object);

G_MODULE_EXPORT void ApprovalPassesButton_click(GtkWidget *object);

G_MODULE_EXPORT void AdmitButton_click(GtkWidget *object);

G_MODULE_EXPORT void LetButton_click(GtkWidget *object);

G_MODULE_EXPORT void FuturePassButton_click(GtkWidget *object);

G_MODULE_EXPORT void MessengerButton_click(GtkWidget *object);

G_MODULE_EXPORT void CancelButton_click(GtkWidget *object);

G_MODULE_EXPORT void AcceptButton_click(GtkWidget *object);

G_MODULE_EXPORT void DeclineButton_click(GtkWidget *object);

G_MODULE_EXPORT void SearchEntry_edit(GtkWidget *object);

G_MODULE_EXPORT void EditOrderButton_click(GtkWidget *object);

G_MODULE_EXPORT void ReSendOrderButton_click(GtkWidget *object);

G_MODULE_EXPORT void CheckpointButton_click(GtkWidget *object);

G_MODULE_EXPORT void PassesView_cursor_changed(GtkWidget *object);

G_MODULE_EXPORT void DeclineButtonDialog_click(GtkWidget *object);

G_MODULE_EXPORT void CancelButtonDialog_click(GtkWidget *object);

void list_view_refresh();

std::vector<s_single_pass> list_pass(0);

int SinglePassApp(int argc, char *argv[]){
    gtk_init(&argc,&argv);
    create_window_SinglePassApp();
    g_signal_connect(G_OBJECT(WindowMain), "destroy", G_CALLBACK(window_single_pass_destroy), NULL);
    g_signal_connect(G_OBJECT(ExitButton), "clicked", G_CALLBACK(window_single_pass_destroy), NULL);
    g_signal_connect(G_OBJECT(WindowMain), "destroy-event", G_CALLBACK(window_single_pass_destroy), NULL);
    g_signal_connect(G_OBJECT(MessengerButton), "clicked", G_CALLBACK(MessengerButton_click), NULL);;
    g_signal_connect(G_OBJECT(SurnameSearchEntry), "changed", G_CALLBACK(SearchEntry_edit), NULL);
    g_signal_connect(G_OBJECT(NameSearchEntry), "changed", G_CALLBACK(SearchEntry_edit), NULL);
    g_signal_connect(G_OBJECT(FathernameSearchEntry), "changed", G_CALLBACK(SearchEntry_edit), NULL);
    g_signal_connect(G_OBJECT(PassesView),"cursor-changed",G_CALLBACK(PassesView_cursor_changed),NULL);
    gtk_widget_show(WindowMain);
    gtk_main();
}

static void create_window_SinglePassApp(){
    GtkBuilder *builder;
    GError* error = nullptr;

    builder = gtk_builder_new();
    if(!gtk_builder_add_from_file(builder, path_glade, &error)){
        g_critical("Не могу загрузить файл: %s", error->message);
        g_error_free(error);
    }

    gtk_builder_connect_signals(builder, nullptr);
    if(!(WindowMain = GTK_WIDGET(gtk_builder_get_object(builder, "WindowMain"))))
        g_critical("Ошибка при получении виджета окна\n");
    if ((type_user == ORDER_TENANT) || (type_user == ORDER_BOSS) || (type_user == MATCHING_BOSS)) {
        if (!(OrderSinglePassButton = GTK_WIDGET(gtk_builder_get_object(builder, "OrderSinglePassButton"))))
            g_critical("Ошибка при получении виджета окна\n");
        gtk_widget_set_visible(OrderSinglePassButton,true);
        g_signal_connect(G_OBJECT(OrderSinglePassButton), "clicked", G_CALLBACK(OrderSinglePassButton_click), NULL);
        if (!(ShowPersonalPassButton = GTK_WIDGET(gtk_builder_get_object(builder, "ShowPersonalPassButton"))))
            g_critical("Ошибка при получении виджета окна\n");
        gtk_widget_set_visible(ShowPersonalPassButton,true);
        g_signal_connect(G_OBJECT(ShowPersonalPassButton), "clicked", G_CALLBACK(ShowPersonalPassButton_click), NULL);
    }
    if ((type_user == CHECKPOINT_CAR) || (type_user == CHECKPOINT_AFOOT) || (type_user == MATCHING_BOSS)) {
        if (!(HistoryPassesButton = GTK_WIDGET(gtk_builder_get_object(builder, "HistoryPassesButton"))))
            g_critical("Ошибка при получении виджета окна\n");
        gtk_widget_set_visible(HistoryPassesButton,true);
        g_signal_connect(G_OBJECT(HistoryPassesButton), "clicked", G_CALLBACK(HistoryPassesButton_click), NULL);
    }
    if (type_user == MATCHING_BOSS) {
        if (!(ApprovalPassesButton = GTK_WIDGET(gtk_builder_get_object(builder, "ApprovalPassesButton"))))
            g_critical("Ошибка при получении виджета окна\n");
        gtk_widget_set_visible(ApprovalPassesButton,true);
        g_signal_connect(G_OBJECT(ApprovalPassesButton), "clicked", G_CALLBACK(ApprovalPassesButton_click), NULL);
    }
    if ((type_user == CHECKPOINT_CAR) || (type_user == CHECKPOINT_AFOOT)) {
        if (!(AdmitButton = GTK_WIDGET(gtk_builder_get_object(builder, "AdmitButton"))))
            g_critical("Ошибка при получении виджета окна\n");
        gtk_widget_set_visible(AdmitButton,true);
        if (!(LetButton = GTK_WIDGET(gtk_builder_get_object(builder, "LetButton"))))
            g_critical("Ошибка при получении виджета окна\n");
        gtk_widget_set_visible(LetButton,true);
        g_signal_connect(G_OBJECT(AdmitButton), "clicked", G_CALLBACK(AdmitButton_click), NULL);
        g_signal_connect(G_OBJECT(LetButton), "clicked", G_CALLBACK(LetButton_click), NULL);
    }
    if ((type_user == MATCHING_BOSS) || (type_user == CHECKPOINT_AFOOT) || (type_user == CHECKPOINT_CAR)) {
        if (!(FuturePassButton = GTK_WIDGET(gtk_builder_get_object(builder, "FuturePassButton"))))
            g_critical("Ошибка при получении виджета окна\n");
        gtk_widget_set_visible(FuturePassButton,true);
        g_signal_connect(G_OBJECT(FuturePassButton), "clicked", G_CALLBACK(FuturePassButton_click), NULL);
    }
    if(!(MessengerButton = GTK_WIDGET(gtk_builder_get_object(builder, "MessengerButton"))))
        g_critical("Ошибка при получении виджета окна\n");
    if(!(ExitButton = GTK_WIDGET(gtk_builder_get_object(builder, "ExitButton"))))
        g_critical("Ошибка при получении виджета окна\n");
    if ((type_user == ORDER_BOSS) || (type_user == ORDER_TENANT) || (type_user == MATCHING_BOSS)) {
        if (!(CancelButton = GTK_WIDGET(gtk_builder_get_object(builder, "CancelButton"))))
            g_critical("Ошибка при получении виджета окна\n");
        gtk_widget_set_visible(CancelButton,true);
        g_signal_connect(G_OBJECT(CancelButton), "clicked", G_CALLBACK(CancelButton_click), NULL);
    }
    if (type_user == MATCHING_BOSS) {
        if (!(AcceptButton = GTK_WIDGET(gtk_builder_get_object(builder, "AcceptButton"))))
            g_critical("Ошибка при получении виджета окна\n");
        gtk_widget_set_visible(AcceptButton,true);
        g_signal_connect(G_OBJECT(AcceptButton), "clicked", G_CALLBACK(AcceptButton_click), NULL);
        if (!(DeclineButton = GTK_WIDGET(gtk_builder_get_object(builder, "DeclineButton"))))
            g_critical("Ошибка при получении виджета окна\n");
        gtk_widget_set_visible(DeclineButton,true);
        g_signal_connect(G_OBJECT(DeclineButton), "clicked", G_CALLBACK(DeclineButton_click), NULL);
    }
    if(!(SurnameSearchEntry = GTK_WIDGET(gtk_builder_get_object(builder, "SurnameSearchEntry"))))
        g_critical("Ошибка при получении виджета окна\n");
    if(!(NameSearchEntry = GTK_WIDGET(gtk_builder_get_object(builder, "NameSearchEntry"))))
        g_critical("Ошибка при получении виджета окна\n");
    if(!(FathernameSearchEntry = GTK_WIDGET(gtk_builder_get_object(builder, "FathernameSearchEntry"))))
        g_critical("Ошибка при получении виджета окна\n");
    if (type_user == CHECKPOINT_AFOOT) {
        if (!(GridDocument = GTK_WIDGET(gtk_builder_get_object(builder, "GridDocument"))))
            g_critical("Ошибка при получении виджета окна\n");
        if (!(DocumentSearchEntry = GTK_WIDGET(gtk_builder_get_object(builder, "DocumentSearchEntry"))))
            g_critical("Ошибка при получении виджета окна\n");
        gtk_widget_set_visible(GridDocument,true);
        g_signal_connect(G_OBJECT(DocumentSearchEntry), "changed", G_CALLBACK(SearchEntry_edit), NULL);
    }
    if (type_user == CHECKPOINT_CAR) {
        if (!(GridCar = GTK_WIDGET(gtk_builder_get_object(builder, "GridCar"))))
            g_critical("Ошибка при получении виджета окна\n");
        if (!(CarNumberEntry = GTK_WIDGET(gtk_builder_get_object(builder, "CarNumberEntry"))))
            g_critical("Ошибка при получении виджета окна\n");
        gtk_widget_set_visible(GridCar,true);
        g_signal_connect(G_OBJECT(CarNumberEntry), "changed", G_CALLBACK(SearchEntry_edit), NULL);
    }
    if ((type_user == ORDER_TENANT) || (type_user == ORDER_BOSS) || (type_user == MATCHING_BOSS)) {
        if (!(EditOrderButton = GTK_WIDGET(gtk_builder_get_object(builder, "EditOrderButton"))))
            g_critical("Ошибка при получении виджета окна\n");
        gtk_widget_set_visible(EditOrderButton,true);
        g_signal_connect(G_OBJECT(EditOrderButton), "clicked", G_CALLBACK(EditOrderButton_click), NULL);
        if (!(ReSendOrderButton = GTK_WIDGET(gtk_builder_get_object(builder, "ReSendOrderButton"))))
            g_critical("Ошибка при получении виджета окна\n");
        gtk_widget_set_visible(ReSendOrderButton,true);
        g_signal_connect(G_OBJECT(ReSendOrderButton), "clicked", G_CALLBACK(ReSendOrderButton_click), NULL);
    }
    if ((type_user == CHECKPOINT_CAR) || (type_user == CHECKPOINT_AFOOT)) {
        if (!(CheckpointButton = GTK_WIDGET(gtk_builder_get_object(builder, "CheckpointButton"))))
            g_critical("Ошибка при получении виджета окна\n");
        gtk_widget_set_visible(CheckpointButton,true);
        g_signal_connect(G_OBJECT(CheckpointButton), "clicked", G_CALLBACK(CheckpointButton_click), NULL);
    }
    if(!(HintLabel = GTK_WIDGET(gtk_builder_get_object(builder, "HintLabel"))))
        g_critical("Ошибка при получении виджета окна\n");
    if(!(StatusLabel = GTK_WIDGET(gtk_builder_get_object(builder, "StatusLabel"))))
        g_critical("Ошибка при получении виджета окна\n");
    if(!(TypeDocumentColumn = gtk_builder_get_object(builder, "TypeDocumentColumn")))
        g_critical("Ошибка при получении виджета окна\n");
    if(!(NumDocumentColumn = gtk_builder_get_object(builder, "NumDocumentColumn")))
        g_critical("Ошибка при получении виджета окна\n");
    if(!(NumCarColumn = gtk_builder_get_object(builder, "NumCarColumn")))
        g_critical("Ошибка при получении виджета окна\n");
    if(!(NameOrdererColumn = gtk_builder_get_object(builder, "NameOrdererColumn")))
        g_critical("Ошибка при получении виджета окна\n");
    if(!(OrderOrganizationColumn = gtk_builder_get_object(builder, "OrderOrganizationColumn")))
        g_critical("Ошибка при получении виджета окна\n");
    if(!(EnteringOrganizationColumn = gtk_builder_get_object(builder, "EnteringOrganizationColumn")))
        g_critical("Ошибка при получении виджета окна\n");
    if(!(DateOrderColumn = gtk_builder_get_object(builder, "DateOrderColumn")))
        g_critical("Ошибка при получении виджета окна\n");
    if(!(TimeOrderColumn = gtk_builder_get_object(builder, "TimeOrderColumn")))
        g_critical("Ошибка при получении виджета окна\n");
    if(!(CommentaryColumn = gtk_builder_get_object(builder, "CommentaryColumn")))
        g_critical("Ошибка при получении виджета окна\n");
    if(!(EnterTimeColumn = gtk_builder_get_object(builder, "EnterTimeColumn")))
        g_critical("Ошибка при получении виджета окна\n");
    if(!(ExitTimeColumn = gtk_builder_get_object(builder, "ExitTimeColumn")))
        g_critical("Ошибка при получении виджета окна\n");
    if(!(StatusApologyColumn = gtk_builder_get_object(builder, "StatusApologyColumn")))
        g_critical("Ошибка при получении виджета окна\n");
    if(!(PassesView = GTK_WIDGET(gtk_builder_get_object(builder, "PassesView"))))
        g_critical("Ошибка при получении виджета окна\n");
    g_object_unref(builder);
}

void window_single_pass_destroy(GtkWidget *object){
    gtk_main_quit();
};

void OrderSinglePassButton_click(GtkWidget *object){
    OrderPassApp();
};

void ShowPersonalPassButton_click(GtkWidget *object){
    gtk_widget_set_visible(CancelButton,true);
    gtk_widget_set_visible(EditOrderButton,true);
    gtk_widget_set_visible(ReSendOrderButton,true);
    if (type_user == MATCHING_BOSS) {
        gtk_widget_set_visible(DeclineButton,false);
        gtk_widget_set_visible(AcceptButton,false);
    }
    output_mode = SHOW_MY;
    list_view_refresh();
};

void HistoryPassesButton_click(GtkWidget *object){
    if ((type_user == CHECKPOINT_CAR) || (type_user == CHECKPOINT_AFOOT)) {
        gtk_widget_set_visible(CheckpointButton,false);
    }
    if (type_user == MATCHING_BOSS) {
        gtk_widget_set_visible(CancelButton,false);
        gtk_widget_set_visible(EditOrderButton,false);
        gtk_widget_set_visible(ReSendOrderButton,false);
        gtk_widget_set_visible(DeclineButton,false);
        gtk_widget_set_visible(AcceptButton,false);
    }
    output_mode = HISTORY;
    list_view_refresh();
};

void ApprovalPassesButton_click(GtkWidget *object){
    gtk_widget_set_visible(DeclineButton,true);
    gtk_widget_set_visible(AcceptButton,true);
    gtk_widget_set_visible(CancelButton,false);
    gtk_widget_set_visible(EditOrderButton,false);
    gtk_widget_set_visible(ReSendOrderButton,false);
    output_mode = APOLOGY;
    list_view_refresh();
};

void AdmitButton_click(GtkWidget *object){
    gtk_widget_set_visible(CheckpointButton,true);
    output_mode = ADMIT;
    list_view_refresh();
};

void LetButton_click(GtkWidget *object){
    gtk_widget_set_visible(CheckpointButton,true);
    output_mode = LET;
    list_view_refresh();
};

void FuturePassButton_click(GtkWidget *object){
    if ((type_user == CHECKPOINT_CAR) || (type_user == CHECKPOINT_AFOOT)) {
        gtk_widget_set_visible(CheckpointButton, false);
    } else {
        gtk_widget_set_visible(DeclineButton,false);
        gtk_widget_set_visible(AcceptButton,false);
        gtk_widget_set_visible(CancelButton,false);
        gtk_widget_set_visible(EditOrderButton,false);
        gtk_widget_set_visible(ReSendOrderButton,false);
    }
    output_mode = FUTURE;
    list_view_refresh();
};

void MessengerButton_click(GtkWidget *object){
    messenger();
};

void CancelButton_click(GtkWidget *object){
    if (selected != -1) {
        std::stringstream query;
        query << "DELETE FROM single_passes WHERE id = " <<
              list_pass[selected].id << ";";
        PGresult *res = PQexec(conn,query.str().c_str());
    }
    list_view_refresh();
};

void AcceptButton_click(GtkWidget *object){
    std::stringstream query;
    query << "UPDATE single_passes SET status_pass = true WHERE id = " <<
          list_pass[selected].id << ";";
    std::stringstream query1;
    query1 << "UPDATE single_passes SET status_appology = true WHERE id = " <<
           list_pass[selected].id << ";";
    PGresult *res = PQexec(conn,query.str().c_str());
    PGresult *res1 = PQexec(conn,query1.str().c_str());
    list_view_refresh();
};

void DeclineButton_click(GtkWidget *object){
    GtkBuilder *builder;
    GError* error = nullptr;

    builder = gtk_builder_new();
    if(!gtk_builder_add_from_file(builder, path_glade, &error)){
        g_critical("Не могу загрузить файл: %s", error->message);
        g_error_free(error);
    }

    gtk_builder_connect_signals(builder, nullptr);
    if(!(CommentaryDeclineEntry = GTK_WIDGET(gtk_builder_get_object(builder, "CommentaryDeclineEntry"))))
        g_critical("Ошибка при получении виджета окна\n");
    if(!(DeclineDialog = GTK_WIDGET(gtk_builder_get_object(builder, "DeclineDialog"))))
        g_critical("Ошибка при получении виджета окна\n");
    if(!(DeclineButtonDialog = GTK_WIDGET(gtk_builder_get_object(builder, "DeclineButtonDialog"))))
        g_critical("Ошибка при получении виджета окна\n");
    if(!(CancelButtonDialog2 = GTK_WIDGET(gtk_builder_get_object(builder, "CancelButtonDialog2"))))
        g_critical("Ошибка при получении виджета окна\n");
    g_object_unref(builder);
    g_signal_connect(G_OBJECT(DeclineDialog),"destroy",G_CALLBACK(CancelButtonDialog_click),NULL);
    g_signal_connect(G_OBJECT(DeclineDialog),"destroy-event",G_CALLBACK(CancelButtonDialog_click),NULL);
    g_signal_connect(G_OBJECT(CancelButtonDialog2),"clicked",G_CALLBACK(CancelButtonDialog_click),NULL);
    g_signal_connect(G_OBJECT(DeclineButtonDialog),"clicked",G_CALLBACK(DeclineButtonDialog_click),NULL);
    gtk_widget_show(DeclineDialog);
};

void SearchEntry_edit(GtkWidget *object){
    list_view_refresh();
};

void EditOrderButton_click(GtkWidget *object){
    if (selected != -1) {
        EditPassApp(list_pass[selected]);
    }
};

void ReSendOrderButton_click(GtkWidget *object){
    if (selected != -1) {
        std::stringstream query;
        query << "UPDATE single_passes SET status_appology = NULL WHERE id = " <<
              list_pass[selected].id << ";";
        PGresult *rs = PQexec(conn,query.str().c_str());
        list_view_refresh();
    }
};

void CheckpointButton_click(GtkWidget *object){
    if (selected != -1) {
        std::stringstream query1;
        query1 << "SELECT status_factory FROM single_passes WHERE id = " << list_pass[selected].id << ";";
        PGresult *res1 = PQexec(conn,query1.str().c_str());
        char *r1 = PQgetvalue(res1,0,0);
        if (r1 == nullptr) {
            journal << (time(nullptr) % (24 * 3600)) / 3600 + 3 << ":"
                    << (time(nullptr) % (3600)) / 60 << ":" << (time(nullptr) % (60)) <<
                    ": Development error: SinglePassApp.h:367\n";
        } else {
            if (r1[0] == 'f') {
                std::stringstream query2;
                query2 << "UPDATE single_passes SET status_factory = true, pass_using = true, enter_time = now() WHERE "
                       << "id = " << list_pass[selected].id << ";";
                PGresult *res2 = PQexec(conn,query2.str().c_str());
            } else {
                std::stringstream query2;
                query2 << "UPDATE single_passes SET status_factory = false, status_pass = false, exit_time = now() WHERE "
                       << "id = " << list_pass[selected].id << ";";
                PGresult *res2 = PQexec(conn,query2.str().c_str());
            }
        }
    }
    list_view_refresh();
};

void list_view_refresh(){
    if (output_mode != 0) {
        std::string surname_search = gtk_entry_get_text(GTK_ENTRY(SurnameSearchEntry));
        std::string name_search = gtk_entry_get_text(GTK_ENTRY(NameSearchEntry));
        std::string fathername_search = gtk_entry_get_text(GTK_ENTRY(FathernameSearchEntry));
        std::string document_search;
        if (type_user == CHECKPOINT_AFOOT) {
            document_search = gtk_entry_get_text(GTK_ENTRY(DocumentSearchEntry));
        } else {
            document_search = "";
        }
        std::string car_number_search;
        if (type_user == CHECKPOINT_CAR) {
            car_number_search = gtk_entry_get_text(GTK_ENTRY(CarNumberEntry));
        } else {
            car_number_search = "";
        }
        std::stringstream query;
        query << "SELECT * FROM single_passes WHERE ((surname LIKE '%" << surname_search << "%') AND (name LIKE '%" <<
              name_search << "%') AND (fathername LIKE '%" << fathername_search << "%') AND (number_document LIKE '%" <<
              document_search << "%') AND (num_auto LIKE '%" << car_number_search << "%') AND ";
        switch (output_mode) {
            case SHOW_MY:
                query << "(id_director = " << id_worker <<
                      ") AND (pass_using = false));";
                gtk_tree_view_column_set_visible(GTK_TREE_VIEW_COLUMN(TypeDocumentColumn),true);
                gtk_tree_view_column_set_visible(GTK_TREE_VIEW_COLUMN(NumDocumentColumn),true);
                gtk_tree_view_column_set_visible(GTK_TREE_VIEW_COLUMN(NumCarColumn),true);
                gtk_tree_view_column_set_visible(GTK_TREE_VIEW_COLUMN(NameOrdererColumn),false);
                gtk_tree_view_column_set_visible(GTK_TREE_VIEW_COLUMN(StatusApologyColumn),true);
                gtk_tree_view_column_set_visible(GTK_TREE_VIEW_COLUMN(OrderOrganizationColumn),false);
                gtk_tree_view_column_set_visible(GTK_TREE_VIEW_COLUMN(EnteringOrganizationColumn),false);
                gtk_tree_view_column_set_visible(GTK_TREE_VIEW_COLUMN(DateOrderColumn),false);
                gtk_tree_view_column_set_visible(GTK_TREE_VIEW_COLUMN(TimeOrderColumn),false);
                gtk_tree_view_column_set_visible(GTK_TREE_VIEW_COLUMN(CommentaryColumn),true);
                gtk_tree_view_column_set_visible(GTK_TREE_VIEW_COLUMN(EnterTimeColumn),false);
                gtk_tree_view_column_set_visible(GTK_TREE_VIEW_COLUMN(ExitTimeColumn),false);
                break;
            case ADMIT:
                if (type_user == CHECKPOINT_AFOOT) {
                    gtk_tree_view_column_set_visible(GTK_TREE_VIEW_COLUMN(TypeDocumentColumn), true);
                    gtk_tree_view_column_set_visible(GTK_TREE_VIEW_COLUMN(NumDocumentColumn),true);
                    gtk_tree_view_column_set_visible(GTK_TREE_VIEW_COLUMN(NumCarColumn),false);
                } else {
                    gtk_tree_view_column_set_visible(GTK_TREE_VIEW_COLUMN(TypeDocumentColumn), false);
                    gtk_tree_view_column_set_visible(GTK_TREE_VIEW_COLUMN(NumDocumentColumn),false);
                    gtk_tree_view_column_set_visible(GTK_TREE_VIEW_COLUMN(NumCarColumn),true);
                }
                gtk_tree_view_column_set_visible(GTK_TREE_VIEW_COLUMN(NameOrdererColumn),true);
                gtk_tree_view_column_set_visible(GTK_TREE_VIEW_COLUMN(StatusApologyColumn),false);
                gtk_tree_view_column_set_visible(GTK_TREE_VIEW_COLUMN(OrderOrganizationColumn),false);
                gtk_tree_view_column_set_visible(GTK_TREE_VIEW_COLUMN(EnteringOrganizationColumn),false);
                gtk_tree_view_column_set_visible(GTK_TREE_VIEW_COLUMN(DateOrderColumn),false);
                gtk_tree_view_column_set_visible(GTK_TREE_VIEW_COLUMN(TimeOrderColumn),false);
                gtk_tree_view_column_set_visible(GTK_TREE_VIEW_COLUMN(CommentaryColumn),false);
                gtk_tree_view_column_set_visible(GTK_TREE_VIEW_COLUMN(EnterTimeColumn),false);
                gtk_tree_view_column_set_visible(GTK_TREE_VIEW_COLUMN(ExitTimeColumn),false);
                switch (type_user) {
                    case CHECKPOINT_AFOOT:
                        query << "(status_pass = true) AND (status_factory = false) AND (driver = false));";
                        break;
                    default:
                        query << "(status_pass = true) AND (status_factory = false) AND (driver = true));";
                }
                break;
            case LET:
                if (type_user == CHECKPOINT_AFOOT) {
                    gtk_tree_view_column_set_visible(GTK_TREE_VIEW_COLUMN(TypeDocumentColumn), true);
                    gtk_tree_view_column_set_visible(GTK_TREE_VIEW_COLUMN(NumDocumentColumn),true);
                    gtk_tree_view_column_set_visible(GTK_TREE_VIEW_COLUMN(NumCarColumn),false);
                } else {
                    gtk_tree_view_column_set_visible(GTK_TREE_VIEW_COLUMN(TypeDocumentColumn), false);
                    gtk_tree_view_column_set_visible(GTK_TREE_VIEW_COLUMN(NumDocumentColumn),false);
                    gtk_tree_view_column_set_visible(GTK_TREE_VIEW_COLUMN(NumCarColumn),true);
                }
                gtk_tree_view_column_set_visible(GTK_TREE_VIEW_COLUMN(NameOrdererColumn),true);
                gtk_tree_view_column_set_visible(GTK_TREE_VIEW_COLUMN(StatusApologyColumn),false);
                gtk_tree_view_column_set_visible(GTK_TREE_VIEW_COLUMN(OrderOrganizationColumn),false);
                gtk_tree_view_column_set_visible(GTK_TREE_VIEW_COLUMN(EnteringOrganizationColumn),false);
                gtk_tree_view_column_set_visible(GTK_TREE_VIEW_COLUMN(DateOrderColumn),false);
                gtk_tree_view_column_set_visible(GTK_TREE_VIEW_COLUMN(TimeOrderColumn),false);
                gtk_tree_view_column_set_visible(GTK_TREE_VIEW_COLUMN(CommentaryColumn),false);
                gtk_tree_view_column_set_visible(GTK_TREE_VIEW_COLUMN(EnterTimeColumn),false);
                gtk_tree_view_column_set_visible(GTK_TREE_VIEW_COLUMN(ExitTimeColumn),false);
                switch (type_user) {
                    case CHECKPOINT_AFOOT:
                        query << "(status_factory = true) AND (driver = false));";
                        break;
                    default:
                        query << "(status_factory = true) AND (driver = true));";
                }
                break;
            case HISTORY:
                gtk_tree_view_column_set_visible(GTK_TREE_VIEW_COLUMN(TypeDocumentColumn),true);
                gtk_tree_view_column_set_visible(GTK_TREE_VIEW_COLUMN(NumDocumentColumn),true);
                gtk_tree_view_column_set_visible(GTK_TREE_VIEW_COLUMN(NumCarColumn),true);
                gtk_tree_view_column_set_visible(GTK_TREE_VIEW_COLUMN(NameOrdererColumn),true);
                gtk_tree_view_column_set_visible(GTK_TREE_VIEW_COLUMN(StatusApologyColumn),true);
                gtk_tree_view_column_set_visible(GTK_TREE_VIEW_COLUMN(OrderOrganizationColumn),true);
                gtk_tree_view_column_set_visible(GTK_TREE_VIEW_COLUMN(EnteringOrganizationColumn),true);
                gtk_tree_view_column_set_visible(GTK_TREE_VIEW_COLUMN(DateOrderColumn),false);
                gtk_tree_view_column_set_visible(GTK_TREE_VIEW_COLUMN(TimeOrderColumn),false);
                gtk_tree_view_column_set_visible(GTK_TREE_VIEW_COLUMN(CommentaryColumn),false);
                gtk_tree_view_column_set_visible(GTK_TREE_VIEW_COLUMN(EnterTimeColumn),true);
                gtk_tree_view_column_set_visible(GTK_TREE_VIEW_COLUMN(ExitTimeColumn),true);
                query << "((pass_using = true) OR (current_date > date_pass)));";
                break;
            case APOLOGY:
                gtk_tree_view_column_set_visible(GTK_TREE_VIEW_COLUMN(TypeDocumentColumn),true);
                gtk_tree_view_column_set_visible(GTK_TREE_VIEW_COLUMN(NumDocumentColumn),true);
                gtk_tree_view_column_set_visible(GTK_TREE_VIEW_COLUMN(NumCarColumn),true);
                gtk_tree_view_column_set_visible(GTK_TREE_VIEW_COLUMN(NameOrdererColumn),true);
                gtk_tree_view_column_set_visible(GTK_TREE_VIEW_COLUMN(StatusApologyColumn),true);
                gtk_tree_view_column_set_visible(GTK_TREE_VIEW_COLUMN(OrderOrganizationColumn),true);
                gtk_tree_view_column_set_visible(GTK_TREE_VIEW_COLUMN(EnteringOrganizationColumn),true);
                gtk_tree_view_column_set_visible(GTK_TREE_VIEW_COLUMN(DateOrderColumn),true);
                gtk_tree_view_column_set_visible(GTK_TREE_VIEW_COLUMN(TimeOrderColumn),true);
                gtk_tree_view_column_set_visible(GTK_TREE_VIEW_COLUMN(CommentaryColumn),true);
                gtk_tree_view_column_set_visible(GTK_TREE_VIEW_COLUMN(EnterTimeColumn),false);
                gtk_tree_view_column_set_visible(GTK_TREE_VIEW_COLUMN(ExitTimeColumn),false);
                query << "(((status_appology = true) OR (status_appology IS NULL)) AND ((date_pass = current_date)"
                      <<" OR (date_pass > current_date))));";
                std::cout << query.str();
                break;
            case FUTURE:
                gtk_tree_view_column_set_visible(GTK_TREE_VIEW_COLUMN(TypeDocumentColumn),true);
                gtk_tree_view_column_set_visible(GTK_TREE_VIEW_COLUMN(NumDocumentColumn),true);
                gtk_tree_view_column_set_visible(GTK_TREE_VIEW_COLUMN(NumCarColumn),true);
                gtk_tree_view_column_set_visible(GTK_TREE_VIEW_COLUMN(NameOrdererColumn),true);
                gtk_tree_view_column_set_visible(GTK_TREE_VIEW_COLUMN(StatusApologyColumn),false);
                gtk_tree_view_column_set_visible(GTK_TREE_VIEW_COLUMN(OrderOrganizationColumn),true);
                gtk_tree_view_column_set_visible(GTK_TREE_VIEW_COLUMN(EnteringOrganizationColumn),true);
                gtk_tree_view_column_set_visible(GTK_TREE_VIEW_COLUMN(DateOrderColumn),true);
                gtk_tree_view_column_set_visible(GTK_TREE_VIEW_COLUMN(TimeOrderColumn),true);
                gtk_tree_view_column_set_visible(GTK_TREE_VIEW_COLUMN(CommentaryColumn),false);
                gtk_tree_view_column_set_visible(GTK_TREE_VIEW_COLUMN(EnterTimeColumn),false);
                gtk_tree_view_column_set_visible(GTK_TREE_VIEW_COLUMN(ExitTimeColumn),false);
                if (type_user == CHECKPOINT_AFOOT)
                    query << "((status_pass = true) AND (date_pass > current_date) AND (driver = false)));";
                else
                    query << "((status_pass = true) AND (date_pass > current_date) AND (driver = true)));";
                break;
            default:
                journal << (time(nullptr) % (24 * 3600)) / 3600 + 3 << ":"
                        << (time(nullptr) % (3600)) / 60 << ":" << (time(nullptr) % (60))
                        << ":  programm error: SinglePassApp.h:362" << "\n";
        }
        PGresult *res = PQexec(conn,query.str().c_str());
        int n = PQntuples(res);
        list_pass.clear();
        GtkListStore *tree_list = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(PassesView)));
        gtk_list_store_clear(tree_list);
        for (int i = 0; i < n; ++i) {
            s_single_pass s_pass;
            s_pass.surname = PQgetvalue(res,i,0);
            s_pass.name = PQgetvalue(res,i,1);
            s_pass.fathername = PQgetvalue(res,i,2);
            s_pass.id = std::stoi(std::string(PQgetvalue(res,i,3)));
            char *s_f = PQgetvalue(res,i,4);
            if (s_f[0] == 'f') {
                s_pass.status_factory = false;
            } else {
                s_pass.status_factory = true;
            }
            s_pass.id_director = std::stoi(std::string(PQgetvalue(res,i,5)));
            s_pass.type_document = PQgetvalue(res,i,6);
            s_pass.number_document = PQgetvalue(res,i,7);
            char *s1_f = PQgetvalue(res,i,8);
            if (s1_f[0] == 'f') {
                s_pass.status_pass = false;
            } else {
                s_pass.status_pass = true;
            }
            s_pass.organization = PQgetvalue(res,i,9);
            s_pass.date_query = PQgetvalue(res,i,10);
            s_pass.time_query = PQgetvalue(res,i,11);
            s_pass.date_pass = PQgetvalue(res,i,12);
            s_pass.time_pass = PQgetvalue(res,i,13);
            s_pass.enter_time = PQgetvalue(res,i,14);
            s_pass.exit_time = PQgetvalue(res,i,15);
            char *s2_f = PQgetvalue(res,i,16);
            if (s2_f[0] == 'f') {
                s_pass.pass_using = false;
            } else {
                s_pass.pass_using = true;
            }
            char *s3_f = PQgetvalue(res,i,17);
            if (s3_f[0] == 'f') {
                s_pass.driver = false;
            } else {
                s_pass.driver = true;
            }
            s_pass.num_auto = PQgetvalue(res,i,18);
            s_pass.organization_custom = PQgetvalue(res,i,19);
            char *s4_f = PQgetvalue(res,i,20);
            if (s4_f[0] == 'f') {
                s_pass.status_appology = 1;
            } else if (s4_f[0] == 't') {
                s_pass.status_appology = 0;
            } else {
                s_pass.status_appology = -1;
            }
            s_pass.commentary = PQgetvalue(res,i,21);
            list_pass.push_back(s_pass);
            std::string status_str;
            GdkRGBA consideration = {1.0,1.0,0,1.0};
            GdkRGBA decline = {1.0,0,0,1.0};
            GdkRGBA accept = {0,1.0,0,1.0};
            GdkRGBA input_table;
            switch (output_mode) {
                case ADMIT:
                case LET:
                case FUTURE:
                    status_str = "";
                    input_table = decline;
                    break;
                case APOLOGY:
                case SHOW_MY:
                    switch (s_pass.status_appology) {
                        case -1:
                            status_str = "На рассмотрении";
                            input_table = consideration;
                            break;
                        case 1:
                            status_str = "Отклонено";
                            input_table = decline;
                            break;
                        case 0:
                            status_str = "Одобрено";
                            input_table = accept;
                            break;
                        default:
                            journal << (time(nullptr) % (24 * 3600)) / 3600 + 3 << ":"
                                    << (time(nullptr) % (3600)) / 60 << ":" << (time(nullptr) % (60))
                                    << ":  programm error: SinglePassApp.h:549" << "\n";
                    }
                    break;
                case HISTORY:
                    if (s_pass.pass_using) {
                        status_str = "Использован";
                        input_table = accept;
                    } else {
                        status_str = "Не использован";
                        input_table = decline;
                    }
                    break;
                default:
                    journal << (time(nullptr) % (24 * 3600)) / 3600 + 3 << ":"
                            << (time(nullptr) % (3600)) / 60 << ":" << (time(nullptr) % (60))
                            << ":  programm error: SinglePassApp.h:549" << "\n";
            }
            std::string director_surname;
            std::stringstream query1;
            query1 << "SELECT surname FROM workers WHERE id = " << s_pass.id_director << ";";
            PGresult *res1 = PQexec(conn,query1.str().c_str());
            director_surname = std::string(PQgetvalue(res1,0,0));
            GtkTreeIter iter;
            gtk_list_store_append(tree_list,&iter);
            gtk_list_store_set(tree_list,&iter,0,s_pass.surname.c_str(),1,s_pass.name.c_str(),2,s_pass.fathername.c_str(),
                               3,s_pass.date_pass.c_str(),4,s_pass.time_pass.c_str(),5,s_pass.organization.c_str(),
                               6,s_pass.organization_custom.c_str(),7,s_pass.date_query.c_str(),
                               8,s_pass.time_query.c_str(),9,status_str.c_str(),10,director_surname.c_str(),
                               11,s_pass.type_document.c_str(),12,s_pass.number_document.c_str(),13,s_pass.num_auto.c_str(),
                               14,s_pass.commentary.c_str(),15,s_pass.enter_time.c_str(),16,s_pass.exit_time.c_str(),
                               17,input_table,-1);
        }
    }
}

void PassesView_cursor_changed(GtkWidget *object){
    GtkTreePath *path;
    GtkTreeViewColumn *col;
    gtk_tree_view_get_cursor(GTK_TREE_VIEW(PassesView),&path,&col);
    int* a = gtk_tree_path_get_indices(path);
    if (a == nullptr) {
        selected = -1;
        return;
    }
    selected = *a;
}

void DeclineButtonDialog_click(GtkWidget *object){
    std::stringstream query;
    query << "UPDATE single_passes SET status_pass = false WHERE id = " <<
          list_pass[selected].id << ";";
    std::stringstream query1;
    query1 << "UPDATE single_passes SET status_appology = false WHERE id = " <<
           list_pass[selected].id << ";";
    PGresult *res = PQexec(conn,query.str().c_str());
    PGresult *res1 = PQexec(conn,query1.str().c_str());
    std::stringstream query2;
    query2 << "SELECT id FROM registers_user WHERE id_workers = " << list_pass[selected].id_director << ";";
    PGresult *res2 = PQexec(conn,query2.str().c_str());
    std::string id_recepient = PQgetvalue(res2,0,0);
    std::string message = gtk_entry_get_text(GTK_ENTRY(CommentaryDeclineEntry));
    std::string title = "Отклонение заявки";
    std::stringstream query3;
    query3 << "INSERT INTO messages (id_sender,id_recepient,title,message,time_send) VALUES (" << id_user << "," <<
           id_recepient << ",'" << title << "','" << message << "',now());";
    std::cout << query3.str();
    PQexec(conn,query3.str().c_str());
    gtk_widget_destroy(DeclineDialog);
    list_view_refresh();
}

void CancelButtonDialog_click(GtkWidget *object){
    gtk_widget_destroy(DeclineDialog);
};

#endif //SINGLEPASSSYSTEM_SINGLEPASSAPP_H
