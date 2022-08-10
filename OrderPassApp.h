//
// Created by student on 05.08.2022.
//

#ifndef SINGLEPASSSYSTEM_ORDERPASSAPP_H
#define SINGLEPASSSYSTEM_ORDERPASSAPP_H

#include "main_settings.h"
#include "iostream"

//Виджеты окна заказа пропусков
GtkWidget *windowO;
GtkWidget *SurnameEnterO;
GtkWidget *NameEnterO;
GtkWidget *FathernameEnterO;
GtkWidget *DocumentTypeEnterO;
GtkWidget *DocumentNumEnterO;
GtkWidget *NumAutoEntryO;
GtkWidget *ChooseDateWidgetO;
GtkWidget *CancelButtonO;
GtkWidget *HourEnterO;
GtkWidget *MinutEnterO;
GtkWidget *OrganizationEnterO;
GtkWidget *OrderButtonO;
GtkWidget *CommentaryEntryO;
GtkWidget *DriverSwitchO;


//Виджеты диалога
GtkWidget *DialogH;
GtkWidget *LabelH;
GtkWidget *CancelButtonH;
GtkWidget *AcceptButtonH;


//Необходимое для заказа пропусков
int id = -1;
std::string surname;
std::string name;
std::string fathername;
std::string type_document;
std::string num_document;
std::string organization;
std::string date_pass;
std::string time_pass;
std::string num_auto;
bool driver;
std::string commentary;
int id_customer = -1;
std::string info_label_str;

static void create_window_single_pass_order();

void OrderPassApp();

void EditPassApp(s_single_pass const& edited_pass);

extern "C" void CancelButtonO_press(GtkWidget *object);

extern "C" void CancelButtonH_press(GtkWidget *object);

extern "C" void Press_OrderButtonO(GtkWidget *object);

extern "C" void ApprovalButtonH_Press(GtkWidget *object);

void dialog();

void dialogE();

extern "C" void Press_OrderButtonOE(GtkWidget *object);

extern "C" void ApprovalButtonHE_Press(GtkWidget *object);

static void create_window_single_pass_order(){
    GtkBuilder *builder;
    GError* error = nullptr;

    builder = gtk_builder_new();
    if(!gtk_builder_add_from_file(builder, path_glade, &error)){
        g_critical("Не могу загрузить файл: %s", error->message);
        g_error_free(error);
    }

    gtk_builder_connect_signals(builder, nullptr);
    if(!(windowO = GTK_WIDGET(gtk_builder_get_object(builder, "SinglePassOrderWindow"))))
        g_critical("Ошибка при получении виджета окна\n");
    if(!(SurnameEnterO = GTK_WIDGET(gtk_builder_get_object(builder, "SurnameEntryO"))))
        g_critical("Ошибка при получении виджета окна\n");
    if(!(NameEnterO = GTK_WIDGET(gtk_builder_get_object(builder, "NameEntryO"))))
        g_critical("Ошибка при получении виджета окна\n");
    if(!(FathernameEnterO = GTK_WIDGET(gtk_builder_get_object(builder, "FathernameEntryO"))))
        g_critical("Ошибка при получении виджета окна\n");
    if(!(DocumentTypeEnterO = GTK_WIDGET(gtk_builder_get_object(builder, "DocumentTypeEntryO"))))
        g_critical("Ошибка при получении виджета окна\n");
    if(!(DocumentNumEnterO = GTK_WIDGET(gtk_builder_get_object(builder, "DocumentNumEntryO"))))
        g_critical("Ошибка при получении виджета окна\n");
    if(!(OrganizationEnterO = GTK_WIDGET(gtk_builder_get_object(builder, "OrganizationEntryO"))))
        g_critical("Ошибка при получении виджета окна\n");
    if(!(DriverSwitchO = GTK_WIDGET(gtk_builder_get_object(builder, "DriverSwitchO"))))
        g_critical("Ошибка при получении виджета окна\n");
    if(!(ChooseDateWidgetO = GTK_WIDGET(gtk_builder_get_object(builder, "ChooseDateWidgetO"))))
        g_critical("Ошибка при получении виджета окна\n");
    if(!(NumAutoEntryO = GTK_WIDGET(gtk_builder_get_object(builder, "NumAutoEntryO"))))
        g_critical("Ошибка при получении виджета окна\n");
    if(!(OrderButtonO = GTK_WIDGET(gtk_builder_get_object(builder, "OrderButtonO"))))
        g_critical("Ошибка при получении виджета окна\n");
    if(!(CancelButtonO = GTK_WIDGET(gtk_builder_get_object(builder, "CancelButtonO"))))
        g_critical("Ошибка при получении виджета окна\n");
    if(!(CommentaryEntryO = GTK_WIDGET(gtk_builder_get_object(builder, "CommentaryEntryO"))))
        g_critical("Ошибка при получении виджета окна\n");
    if(!(HourEnterO = GTK_WIDGET(gtk_builder_get_object(builder, "HourComboBox"))))
        g_critical("Ошибка при получении виджета окна\n");
    if(!(MinutEnterO = GTK_WIDGET(gtk_builder_get_object(builder, "MinutComboBox"))))
        g_critical("Ошибка при получении виджета окна\n");
    g_object_unref(builder);
}

void OrderPassApp(){
    create_window_single_pass_order();
    g_signal_connect(G_OBJECT(CancelButtonO), "clicked", G_CALLBACK(CancelButtonO_press), NULL);
    g_signal_connect(G_OBJECT(OrderButtonO), "clicked", G_CALLBACK(Press_OrderButtonO), NULL);
    gtk_widget_show(windowO);
};

void CancelButtonO_press(GtkWidget *object){
    gtk_window_close(GTK_WINDOW(windowO));
}

void CancelButtonH_press(GtkWidget *object){
    gtk_widget_destroy(DialogH);
}

void Press_OrderButtonO(GtkWidget *object){
    surname = std::string(gtk_entry_get_text(GTK_ENTRY(SurnameEnterO)));
    name = std::string(gtk_entry_get_text(GTK_ENTRY(NameEnterO)));
    fathername = std::string(gtk_entry_get_text(GTK_ENTRY(FathernameEnterO)));
    type_document = std::string(gtk_entry_get_text(GTK_ENTRY(DocumentTypeEnterO)));
    num_document = std::string(gtk_entry_get_text(GTK_ENTRY(DocumentNumEnterO)));
    organization = std::string(gtk_entry_get_text(GTK_ENTRY(OrganizationEnterO)));
    guint month;
    guint year;
    guint day;
    gtk_calendar_get_date(GTK_CALENDAR(ChooseDateWidgetO),&year,&month,&day);
    month++;
    int hour = gtk_combo_box_get_active(GTK_COMBO_BOX(HourEnterO));
    int minute = gtk_combo_box_get_active(GTK_COMBO_BOX(MinutEnterO));
    std::stringstream pass_date;
    pass_date << year << "-" << month << "-" << day;
    date_pass = pass_date.str();
    std::stringstream pass_time;
    pass_time << hour << ":" << minute << "+03:00";
    time_pass = pass_time.str();
    driver = gtk_switch_get_active(GTK_SWITCH(DriverSwitchO));
    num_auto = std::string(gtk_entry_get_text(GTK_ENTRY(NumAutoEntryO)));
    commentary = std::string(gtk_entry_get_text(GTK_ENTRY(CommentaryEntryO)));
    std::stringstream info_label;
    info_label << "Подтвердите заказ пропуска\n" << "Фамилия: " << surname << std::endl <<
               "Имя: " << name << std::endl << "Отчество: " << fathername << std::endl;
    if (driver) {
        info_label << "Водитель: да\n";
    } else {
        info_label << "Водитель: нет\n";
    }
    info_label << "Тип документа: " << type_document << std::endl << "Номер документа: " << num_document << std::endl
               << "Номер авто: " << num_auto << std::endl <<
               "Организация: " << organization << std::endl << "Дата: " << date_pass << std::endl <<
               "Время: " << time_pass << std::endl << "Комментарий: " << commentary;
    info_label_str = info_label.str();
    dialog();
}

void dialog(){
    GtkBuilder *builder;
    GError* error = nullptr;

    builder = gtk_builder_new();
    if(!gtk_builder_add_from_file(builder, path_glade, &error)){
        g_critical("Не могу загрузить файл: %s", error->message);
        g_error_free(error);
    }

    gtk_builder_connect_signals(builder, nullptr);
    if(!(DialogH = GTK_WIDGET(gtk_builder_get_object(builder, "DialogSinglePass"))))
        g_critical("Ошибка при получении виджета окна\n");
    if(!(CancelButtonH = GTK_WIDGET(gtk_builder_get_object(builder, "CancelButtonDialog"))))
        g_critical("Ошибка при получении виджета окна\n");
    if(!(AcceptButtonH = GTK_WIDGET(gtk_builder_get_object(builder, "ButtonOkDialog"))))
        g_critical("Ошибка при получении виджета окна\n");
    if(!(LabelH = GTK_WIDGET(gtk_builder_get_object(builder, "LabelInfoDialog"))))
        g_critical("Ошибка при получении виджета окна\n");
    g_object_unref(builder);
    g_signal_connect(G_OBJECT(CancelButtonH), "clicked", G_CALLBACK(CancelButtonH_press), NULL);
    g_signal_connect(G_OBJECT(AcceptButtonH),"clicked", G_CALLBACK(ApprovalButtonH_Press),NULL);
    gtk_label_set_text(GTK_LABEL(LabelH),info_label_str.c_str());
    gtk_dialog_run(GTK_DIALOG(DialogH));
}

void ApprovalButtonH_Press(GtkWidget *object){
    std::stringstream  help_query;
    help_query << "SELECT organization FROM registers_user WHERE id_workers = " <<
               id_user << ";";
    PGresult *rs_help = PQexec(conn,help_query.str().c_str());
    std::string order_organization;
    char *s_h = PQgetvalue(rs_help,0,0);
    if (s_h != nullptr)
        order_organization = s_h;
    std::stringstream  query;
    query << "INSERT INTO single_passes "<< std::endl
          <<"(surname,name,fathername,type_document,number_document,organization,date_pass,"
          <<"time_pass,date_query,time_query,id_director,driver,num_auto,organization_custom,commentary)"<< std::endl
          <<" VALUES ('" << surname << "','" << name <<"','" << fathername << "','" <<
          type_document << "','" << num_document << "','" << organization << "','"<< date_pass << "','" <<
          time_pass << "',now(),now(),"<< id_worker << ",";
    if (driver){
        query << "true" << ",'" << num_auto << "','"
              << order_organization << "','" << commentary << "');";
    } else {
        query << "false" << ",'" << num_auto << "','"
              << order_organization << "','" << commentary << "');";
    }
    PQexec(conn,query.str().c_str());
    if (type_user == MATCHING_BOSS) {
        std::stringstream query1;
        query1 << "UPDATE single_passes SET status_pass = true, status_appology = true WHERE ((name = '" << name
               << "') AND (surname = '" << surname << "') AND (date_pass ='" << date_pass << "'));";
        PQexec(conn,query1.str().c_str());
    }
    gtk_widget_destroy(DialogH);
    gtk_window_close(GTK_WINDOW(windowO));
}

void EditPassApp(s_single_pass const& edited_pass){
    id = edited_pass.id;
    create_window_single_pass_order();
    g_signal_connect(G_OBJECT(CancelButtonO), "clicked", G_CALLBACK(CancelButtonO_press), NULL);
    g_signal_connect(G_OBJECT(OrderButtonO), "clicked", G_CALLBACK(Press_OrderButtonOE), NULL);
    gtk_entry_set_text(GTK_ENTRY(SurnameEnterO),edited_pass.surname.c_str());
    gtk_entry_set_text(GTK_ENTRY(NameEnterO),edited_pass.name.c_str());
    gtk_entry_set_text(GTK_ENTRY(FathernameEnterO),edited_pass.fathername.c_str());
    gtk_entry_set_text(GTK_ENTRY(OrganizationEnterO),edited_pass.organization.c_str());
    gtk_entry_set_text(GTK_ENTRY(DocumentTypeEnterO),edited_pass.type_document.c_str());
    gtk_entry_set_text(GTK_ENTRY(DocumentNumEnterO),edited_pass.number_document.c_str());
    gtk_entry_set_text(GTK_ENTRY(NumAutoEntryO),edited_pass.num_auto.c_str());
    gtk_entry_set_text(GTK_ENTRY(CommentaryEntryO),edited_pass.commentary.c_str());
    gtk_combo_box_set_active(GTK_COMBO_BOX(HourEnterO),
                             std::stoi(edited_pass.time_pass.substr(0,2)));
    gtk_combo_box_set_active(GTK_COMBO_BOX(MinutEnterO),
                             std::stoi(edited_pass.time_pass.substr(3,2)));
    gtk_calendar_select_day(GTK_CALENDAR(ChooseDateWidgetO),
                            std::stoi(edited_pass.date_pass.substr(8,2)));
    gtk_calendar_select_month(GTK_CALENDAR(ChooseDateWidgetO),
                              std::stoi(edited_pass.date_pass.substr(5,2))-1,
                              std::stoi(edited_pass.date_pass.substr(0,4)));
    gtk_switch_set_active(GTK_SWITCH(DriverSwitchO),edited_pass.driver);
    gtk_widget_show(windowO);
}

void Press_OrderButtonOE(GtkWidget *object){
    surname = std::string(gtk_entry_get_text(GTK_ENTRY(SurnameEnterO)));
    name = std::string(gtk_entry_get_text(GTK_ENTRY(NameEnterO)));
    fathername = std::string(gtk_entry_get_text(GTK_ENTRY(FathernameEnterO)));
    type_document = std::string(gtk_entry_get_text(GTK_ENTRY(DocumentTypeEnterO)));
    num_document = std::string(gtk_entry_get_text(GTK_ENTRY(DocumentNumEnterO)));
    organization = std::string(gtk_entry_get_text(GTK_ENTRY(OrganizationEnterO)));
    guint month;
    guint year;
    guint day;
    gtk_calendar_get_date(GTK_CALENDAR(ChooseDateWidgetO),&year,&month,&day);
    month++;
    int hour = gtk_combo_box_get_active(GTK_COMBO_BOX(HourEnterO));
    int minute = gtk_combo_box_get_active(GTK_COMBO_BOX(MinutEnterO));
    std::stringstream pass_date;
    pass_date << year << "-" << month << "-" << day;
    date_pass = pass_date.str();
    std::stringstream pass_time;
    pass_time << hour << ":" << minute << "+03:00";
    time_pass = pass_time.str();
    driver = gtk_switch_get_active(GTK_SWITCH(DriverSwitchO));
    num_auto = std::string(gtk_entry_get_text(GTK_ENTRY(NumAutoEntryO)));
    commentary = std::string(gtk_entry_get_text(GTK_ENTRY(CommentaryEntryO)));
    std::stringstream info_label;
    info_label << "Подтвердите изменения\n" << "Фамилия: " << surname << std::endl <<
               "Имя: " << name << std::endl << "Отчество: " << fathername << std::endl;
    if (driver) {
        info_label << "Водитель: да\n";
    } else {
        info_label << "Водитель: нет\n";
    }
    info_label << "Тип документа: " << type_document << std::endl << "Номер документа: " << num_document << std::endl
               << "Номер авто: " << num_auto << std::endl <<
               "Организация: " << organization << std::endl << "Дата: " << date_pass << std::endl <<
               "Время: " << time_pass << std::endl << "Комментарий: " << commentary;
    info_label_str = info_label.str();
    dialogE();
};

void ApprovalButtonHE_Press(GtkWidget *object){
    std::stringstream  query;
    query << "UPDATE single_passes SET "<< std::endl;
    query << "surname = '" << surname << "', name = '" << name <<
          "', fathername = '" << fathername << "', type_document = '" <<
          type_document << "', number_document = '" << num_document << "', num_auto = '" <<
          num_auto << "', commentary = '" << commentary << "', date_pass = '" <<
          date_pass << "', time_pass = '" << time_pass << "', driver = ";
    if (driver){
        query << "true, status_appology = NULL, status_pass = FALSE WHERE id = " << id << ";";
    } else {
        query << "false, status_appology = NULL, status_pass = FALSE WHERE id = " << id << ";";
    }
    PQexec(conn,query.str().c_str());
    if (type_user == MATCHING_BOSS) {
        std::stringstream query1;
        query1 << "UPDATE single_passes SET status_pass = true, status_appology = true WHERE ((name = '" << name
               << "') AND (surname = '" << surname << "') AND (date_pass ='" << date_pass << "'));";
        PQexec(conn,query1.str().c_str());
    }
    gtk_widget_destroy(DialogH);
    gtk_window_close(GTK_WINDOW(windowO));
};

void dialogE(){
    GtkBuilder *builder;
    GError* error = nullptr;

    builder = gtk_builder_new();
    if(!gtk_builder_add_from_file(builder, path_glade, &error)){
        g_critical("Не могу загрузить файл: %s", error->message);
        g_error_free(error);
    }

    gtk_builder_connect_signals(builder, nullptr);
    if(!(DialogH = GTK_WIDGET(gtk_builder_get_object(builder, "DialogSinglePass"))))
        g_critical("Ошибка при получении виджета окна\n");
    if(!(CancelButtonH = GTK_WIDGET(gtk_builder_get_object(builder, "CancelButtonDialog"))))
        g_critical("Ошибка при получении виджета окна\n");
    if(!(AcceptButtonH = GTK_WIDGET(gtk_builder_get_object(builder, "ButtonOkDialog"))))
        g_critical("Ошибка при получении виджета окна\n");
    if(!(LabelH = GTK_WIDGET(gtk_builder_get_object(builder, "LabelInfoDialog"))))
        g_critical("Ошибка при получении виджета окна\n");
    g_object_unref(builder);
    g_signal_connect(G_OBJECT(CancelButtonH), "clicked", G_CALLBACK(CancelButtonH_press), NULL);
    g_signal_connect(G_OBJECT(AcceptButtonH),"clicked", G_CALLBACK(ApprovalButtonHE_Press),NULL);
    gtk_label_set_text(GTK_LABEL(LabelH),info_label_str.c_str());
    gtk_dialog_run(GTK_DIALOG(DialogH));
}

#endif //SINGLEPASSSYSTEM_ORDERPASSAPP_H
