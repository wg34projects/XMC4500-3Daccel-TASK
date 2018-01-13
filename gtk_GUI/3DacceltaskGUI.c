/**
 * @file		3DacceltaskGUI.c
 * @version		v1.0
 * @date		Jan 2018
 * @author		Egermann, Resch
 *
 * @brief		3Dacceltask GUI
 *
 */

#include "3DacceltaskGUI.h"

/**
 * @brief	GMenu entries
 *
 */
const GActionEntry appActions[] =
{
    { "help", 		help },
    { "about", 		about },
    { "quit", 		quit }
};

/**
 * @brief	main function to describe GUI
 *
 */
void constructGUI(gpointer data)
{
    widgets *a = (widgets *) data;
    const gchar initialinfo[] = "please choose your USB connection ID and poll time - standard is /dev/ttyUSB0 and 100ms";
    gchar stringUSB[15];
    gint i;

    // initialization

    a->position6Dint = 0;
    a->acceltriggerX = 1.5;
    a->acceltriggerY = 1.5;
    a->acceltriggerZ = 1.5;
    a->servoState = 0;
    a->average = 0;
    a->transmission = FALSE;
    a->sendSerial = FALSE;
    a->wait = FALSE;
    a->radioButtonUSBstate = 16;
    a->pollTimeSensor = 100;
    a->connectionStatus = 0;

    // flush cache

    RS232_flushRXTX(a->radioButtonUSBstate);

    // grid

    a->grid = gtk_grid_new();
    gtk_grid_set_column_homogeneous(GTK_GRID (a->grid), TRUE);
    gtk_grid_set_row_homogeneous(GTK_GRID (a->grid), TRUE);
    gtk_grid_set_row_spacing(GTK_GRID (a->grid), 10);
    gtk_grid_set_column_spacing(GTK_GRID (a->grid), 10);
    gtk_widget_set_margin_start(a->grid, 10);
    gtk_widget_set_margin_end(a->grid, 10);
    gtk_widget_set_margin_top(a->grid, 10);
    gtk_widget_set_margin_bottom(a->grid, 10);
    gtk_container_add(GTK_CONTAINER (a->window), a->grid);

    // initial picture

    a->image[0] = gtk_image_new_from_file("./pictures/ALL.png");
    a->box[0] = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_grid_attach(GTK_GRID (a->grid), a->box[0], 3, 0, 2, 5);
    gtk_box_pack_start(GTK_BOX(a->box[0]), a->image[0], FALSE, FALSE, 0);
    gtk_widget_set_halign(GTK_WIDGET(a->box[0]), GTK_ALIGN_CENTER);
    gtk_widget_set_valign(GTK_WIDGET(a->box[0]), GTK_ALIGN_CENTER);

    // radio buttons for USB

    a->box[1] = gtk_box_new (GTK_ORIENTATION_VERTICAL, 5);
    gtk_grid_attach(GTK_GRID (a->grid), a->box[1], 1, 5, 1, 3);
    gtk_widget_set_halign(GTK_WIDGET(a->box[1]), GTK_ALIGN_CENTER);
    gtk_widget_set_valign(GTK_WIDGET(a->box[1]), GTK_ALIGN_CENTER);
    a->radioUSB[0] = gtk_radio_button_new_with_label (NULL, "/dev/ttyUSB0");
    for (i = 1; i < 5; i++)
    {
        g_sprintf (stringUSB, "/dev/ttyUSB%d", i);
        a->radioUSB[i] = gtk_radio_button_new_with_label_from_widget (GTK_RADIO_BUTTON (a->radioUSB[0]), stringUSB);
        memset (&stringUSB, 0, sizeof (stringUSB));
    }
    for (i = 0; i < 5; i++)
    {
        gtk_box_pack_start (GTK_BOX (a->box[1]), a->radioUSB[i], FALSE, TRUE, 0);
    }
    for (i = 0; i < 5; i++)
    {
        g_signal_connect (G_OBJECT (a->radioUSB[i]), "toggled", G_CALLBACK (readRadioUSB), (gpointer) a);
    }

    // entry section

    a->entry[0] = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY (a->entry[0]), "enter poll time in ms");
    gtk_grid_attach(GTK_GRID (a->grid), a->entry[0], 1, 4, 1, 1);
    g_signal_connect (a->entry[0], "activate", G_CALLBACK (entryPollTime), (gpointer) a);

    a->entry[1] = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY (a->entry[1]), "trigger accelX");
    gtk_grid_attach(GTK_GRID (a->grid), a->entry[1], 3, 5, 1, 1);
    g_signal_connect (a->entry[1], "activate", G_CALLBACK (entryXtrigger), (gpointer) a);

    a->entry[2] = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY (a->entry[2]), "trigger accelY");
    gtk_grid_attach(GTK_GRID (a->grid), a->entry[2], 3, 6, 1, 1);
    g_signal_connect (a->entry[2], "activate", G_CALLBACK (entryYtrigger), (gpointer) a);

    a->entry[3] = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY (a->entry[3]), "trigger accelZ");
    gtk_grid_attach(GTK_GRID (a->grid), a->entry[3], 3, 7, 1, 1);
    g_signal_connect (a->entry[3], "activate", G_CALLBACK (entryZtrigger), (gpointer) a);

    a->entry[4] = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY (a->entry[4]), "enter your filename");
    gtk_grid_attach(GTK_GRID (a->grid), a->entry[4], 3, 8, 1, 1);
    g_signal_connect (a->entry[4], "activate", G_CALLBACK (fileName), (gpointer) a);
    gtk_widget_set_sensitive (GTK_WIDGET (a->entry[4]), FALSE);

    // label section

    a->label[0] = gtk_label_new("6D POSITION");
    gtk_grid_attach(GTK_GRID (a->grid), a->label[0], 1, 0, 1, 1);

    a->label[1] = gtk_label_new("X-VALUE");
    gtk_grid_attach(GTK_GRID (a->grid), a->label[1], 1, 1, 1, 1);

    a->label[2] = gtk_label_new("Y-VALUE");
    gtk_grid_attach(GTK_GRID (a->grid), a->label[2], 1, 2, 1, 1);

    a->label[3] = gtk_label_new("Z-VALUE");
    gtk_grid_attach(GTK_GRID (a->grid), a->label[3], 1, 3, 1, 1);

    a->label[4] = gtk_label_new("sensor readings");
    gtk_label_set_xalign(GTK_LABEL(a->label[4]), 0.0);
    gtk_grid_attach(GTK_GRID (a->grid), a->label[4], 2, 5, 1, 1);

    a->label[5] = gtk_label_new("TILT X");
    gtk_grid_attach(GTK_GRID (a->grid), a->label[5], 2, 0, 1, 1);

    a->label[6] = gtk_label_new("TILT Y");
    gtk_grid_attach(GTK_GRID (a->grid), a->label[6], 2, 1, 1, 1);

    a->label[7] = gtk_label_new("TILT Z");
    gtk_grid_attach(GTK_GRID (a->grid), a->label[7], 2, 2, 1, 1);

    a->label[8] = gtk_label_new("PITCH");
    gtk_grid_attach(GTK_GRID (a->grid), a->label[8], 2, 3, 1, 1);

    a->label[9] = gtk_label_new("ROLL");
    gtk_grid_attach(GTK_GRID (a->grid), a->label[9], 2, 4, 1, 1);

    a->label[10] = gtk_label_new ("<span foreground='white' background='green' weight='ultrabold' font='20'> X TRIGGER </span>");
    gtk_label_set_use_markup (GTK_LABEL (a->label[10]), TRUE);
    gtk_grid_attach(GTK_GRID (a->grid), a->label[10], 4, 5, 1, 1);

    a->label[11] = gtk_label_new ("<span foreground='white' background='green' weight='ultrabold' font='20'> Y TRIGGER </span>");
    gtk_label_set_use_markup (GTK_LABEL (a->label[11]), TRUE);
    gtk_grid_attach(GTK_GRID (a->grid), a->label[11], 4, 6, 1, 1);

    a->label[12] = gtk_label_new ("<span foreground='white' background='green' weight='ultrabold' font='20'> Z TRIGGER </span>");
    gtk_label_set_use_markup (GTK_LABEL (a->label[12]), TRUE);
    gtk_grid_attach(GTK_GRID (a->grid), a->label[12], 4, 7, 1, 1);

    a->label[13] = gtk_label_new("sent by XMC since reset");
    gtk_label_set_xalign(GTK_LABEL(a->label[13]), 0.0);
    gtk_grid_attach(GTK_GRID (a->grid), a->label[13], 2, 6, 1, 1);

    a->label[14] = gtk_label_new("errors XMC");
    gtk_label_set_xalign(GTK_LABEL(a->label[14]), 0.0);
    gtk_grid_attach(GTK_GRID (a->grid), a->label[14], 2, 7, 1, 1);

    a->label[15] = gtk_label_new ("<span foreground='white' weight='ultrabold' font='20'> SAFE </span>");
    gtk_label_set_use_markup (GTK_LABEL (a->label[15]), TRUE);
    gtk_grid_attach(GTK_GRID (a->grid), a->label[15], 4, 8, 1, 1);

    a->label[16] = gtk_label_new ("<span foreground='white' weight='ultrabold' font='16'> BUTTON 1 </span>");
    gtk_label_set_use_markup (GTK_LABEL (a->label[16]), TRUE);
    gtk_label_set_xalign(GTK_LABEL(a->label[16]), 0.5);
    gtk_grid_attach(GTK_GRID (a->grid), a->label[16], 1, 8, 1, 1);

    a->label[17] = gtk_label_new ("<span foreground='white' weight='ultrabold' font='16'> BUTTON 2 </span>");
    gtk_label_set_use_markup (GTK_LABEL (a->label[17]), TRUE);
    gtk_label_set_xalign(GTK_LABEL(a->label[17]), 0.5);
    gtk_grid_attach(GTK_GRID (a->grid), a->label[17], 2, 8, 1, 1);

    // button section

    a->button[0] = gtk_toggle_button_new_with_label("CONNECTION off");
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(a->button[0]), FALSE);
    gtk_widget_set_tooltip_text(GTK_WIDGET(a->button[0]), "toggle RS232 connection on / off");
    gtk_widget_set_hexpand(a->button[0], TRUE);
    gtk_widget_set_vexpand(a->button[0], TRUE);
    g_signal_connect(a->button[0], "toggled", G_CALLBACK (connectSerial), (gpointer) a);
    gtk_grid_attach(GTK_GRID (a->grid), a->button[0], 0, 0, 1, 1);

    a->button[1] = gtk_button_new_with_mnemonic("STATISTIC");
    gtk_widget_set_tooltip_text(GTK_WIDGET(a->button[1]), "request statistic package from XMC");
    gtk_widget_set_hexpand(a->button[1], TRUE);
    gtk_widget_set_vexpand(a->button[1], TRUE);
    g_signal_connect(a->button[1], "clicked", G_CALLBACK (statisticConnector), (gpointer) a);
    gtk_grid_attach(GTK_GRID (a->grid), a->button[1], 0, 1, 1, 1);
    gtk_widget_set_sensitive (GTK_WIDGET (a->button[1]), FALSE);

    a->button[7] = gtk_toggle_button_new_with_label("SAVE");
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(a->button[7]), FALSE);
    gtk_widget_set_tooltip_text(GTK_WIDGET(a->button[7]), "toggle save data");
    gtk_widget_set_hexpand(a->button[7], TRUE);
    gtk_widget_set_vexpand(a->button[7], TRUE);
    g_signal_connect(a->button[7], "toggled", G_CALLBACK (saveData), (gpointer) a);
    gtk_grid_attach(GTK_GRID (a->grid), a->button[7], 0, 2, 1, 1);
    gtk_widget_set_sensitive (GTK_WIDGET (a->button[7]), FALSE);

    a->button[2] = gtk_button_new_with_mnemonic("TERMINAL");
    gtk_widget_set_tooltip_text(GTK_WIDGET(a->button[2]), "view raw incoming protocol");
    gtk_widget_set_hexpand(a->button[2], TRUE);
    gtk_widget_set_vexpand(a->button[2], TRUE);
    g_signal_connect(a->button[2], "clicked", G_CALLBACK (rawProtocolData), (gpointer) a);
    gtk_grid_attach(GTK_GRID (a->grid), a->button[2], 0, 3, 1, 1);
    gtk_widget_set_sensitive (GTK_WIDGET (a->button[2]), FALSE);

    a->button[3] = gtk_toggle_button_new_with_label("TRANSMISSION off");
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(a->button[3]), FALSE);
    gtk_widget_set_tooltip_text(GTK_WIDGET(a->button[3]), "toggle data transmission");
    gtk_widget_set_hexpand(a->button[3], TRUE);
    gtk_widget_set_vexpand(a->button[3], TRUE);
    g_signal_connect(a->button[3], "toggled", G_CALLBACK (dataTransmission), (gpointer) a);
    gtk_grid_attach(GTK_GRID (a->grid), a->button[3], 0, 4, 1, 1);
    gtk_widget_set_sensitive (GTK_WIDGET (a->button[3]), FALSE);

    a->button[4] = gtk_button_new_with_mnemonic("DIAGRAMS");
    gtk_widget_set_tooltip_text(GTK_WIDGET(a->button[4]), "python diagrams");
    gtk_widget_set_hexpand(a->button[4], TRUE);
    gtk_widget_set_vexpand(a->button[4], TRUE);
    g_signal_connect(a->button[4], "clicked", G_CALLBACK (pythonConnector), (gpointer) a);
    gtk_grid_attach(GTK_GRID (a->grid), a->button[4], 0, 5, 1, 1);
    gtk_widget_set_sensitive (GTK_WIDGET (a->button[4]), FALSE);

    a->button[5] = gtk_button_new_with_mnemonic("SPRITES");
    gtk_widget_set_tooltip_text(GTK_WIDGET(a->button[5]), "python sprites");
    gtk_widget_set_hexpand(a->button[5], TRUE);
    gtk_widget_set_vexpand(a->button[5], TRUE);
    g_signal_connect(a->button[5], "clicked", G_CALLBACK (pythonSpriteConnector), (gpointer) a);
    gtk_grid_attach(GTK_GRID (a->grid), a->button[5], 0, 6, 1, 1);
    gtk_widget_set_sensitive (GTK_WIDGET (a->button[5]), FALSE);

    a->button[6] = gtk_toggle_button_new_with_label("SERVO off");
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(a->button[6]), FALSE);
    gtk_widget_set_tooltip_text(GTK_WIDGET(a->button[6]), "toggle servo control");
    gtk_widget_set_hexpand(a->button[6], TRUE);
    gtk_widget_set_vexpand(a->button[6], TRUE);
    g_signal_connect(a->button[6], "toggled", G_CALLBACK(servo), (gpointer) a);
    gtk_grid_attach(GTK_GRID (a->grid), a->button[6], 0, 7, 1, 1);
    gtk_widget_set_sensitive (GTK_WIDGET (a->button[6]), FALSE);

    a->button[8] = gtk_toggle_button_new_with_label("PWM average");
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(a->button[8]), FALSE);
    gtk_widget_set_tooltip_text(GTK_WIDGET(a->button[8]), "toggle average control");
    gtk_widget_set_hexpand(a->button[8], TRUE);
    gtk_widget_set_vexpand(a->button[8], TRUE);
    g_signal_connect(a->button[8], "toggled", G_CALLBACK(average), (gpointer) a);
    gtk_grid_attach(GTK_GRID (a->grid), a->button[8], 0, 8, 1, 1);
    gtk_widget_set_sensitive (GTK_WIDGET (a->button[8]), FALSE);

    // statusbar section

    a->statusBar = gtk_statusbar_new();
    gtk_grid_attach (GTK_GRID (a->grid), a->statusBar, 0, 9, 4, 1);
    a->id = gtk_statusbar_get_context_id (GTK_STATUSBAR (a->statusBar), "demo");
    snprintf(a->bufferStatusBar, sizeof(initialinfo)+1, "%s", initialinfo);
    gtk_statusbar_push (GTK_STATUSBAR (a->statusBar), a->id, a->bufferStatusBar);
}

/**
 * @brief	main function to describe Menu
 *
 */
void constructMenu(GtkApplication *app, gpointer data)
{
    widgets *a = (widgets *) data;

    a->headerbar = gtk_header_bar_new ();
    gtk_widget_show(a->headerbar);
    gtk_header_bar_set_title(GTK_HEADER_BAR (a->headerbar), "GUI 3DacceltaskGUI BEL3 Embedded Systems Software Design");
    gtk_header_bar_set_subtitle(GTK_HEADER_BAR (a->headerbar), "Werner Egermann, Helmut Resch");
    gtk_header_bar_set_show_close_button(GTK_HEADER_BAR (a->headerbar), TRUE);
    gtk_window_set_titlebar(GTK_WINDOW (a->window), a->headerbar);

    a->appmenu = g_menu_new();
    g_menu_append(a->appmenu, "help", "app.help");
    g_menu_append(a->appmenu, "about", "app.about");
    g_menu_append(a->appmenu, "quit", "app.quit");
    gtk_application_set_app_menu (GTK_APPLICATION (app), G_MENU_MODEL (a->appmenu));
    g_object_unref(a->appmenu);

    a->gearmenubutton = gtk_menu_button_new();
    a->gearicon = gtk_image_new_from_icon_name ("emblem-system-symbolic", GTK_ICON_SIZE_SMALL_TOOLBAR);
    gtk_button_set_image (GTK_BUTTON (a->gearmenubutton), a->gearicon);
    gtk_header_bar_pack_end (GTK_HEADER_BAR (a->headerbar), a->gearmenubutton);

    a->gearmenu = g_menu_new();
    g_menu_append(a->gearmenu, "help", "app.help");
    g_menu_append(a->gearmenu, "about", "app.about");
    g_menu_append(a->gearmenu, "quit", "app.quit");
    gtk_menu_button_set_menu_model(GTK_MENU_BUTTON (a->gearmenubutton), G_MENU_MODEL (a->gearmenu));
    g_object_unref(a->gearmenu);
}

/**
 * @brief	main function to activate GUI
 *
 */
void activate(GtkApplication *app, gpointer data)
{
    widgets *a = (widgets *) data;

    a->window = gtk_application_window_new(app);

    gtk_window_set_application(GTK_WINDOW (a->window), GTK_APPLICATION (app));
    gtk_window_set_title(GTK_WINDOW (a->window), "GNOME Menu");
    gtk_window_set_position(GTK_WINDOW (a->window), GTK_WIN_POS_CENTER);
    gtk_window_set_resizable(GTK_WINDOW (a->window), FALSE);
    gtk_window_set_deletable(GTK_WINDOW (a->window), FALSE);

    constructMenu(app,(gpointer)a);
    constructGUI((gpointer)a);

    gtk_widget_show_all(GTK_WIDGET(a->window));
}

/**
 * @brief	main function to start GUI
 *
 */
void startup(GApplication *app, gpointer data)
{
    widgets *a = (widgets *)data;

    g_action_map_add_action_entries(G_ACTION_MAP(app), appActions, G_N_ELEMENTS(appActions), (gpointer)a);

}

/**
 * @brief	main routine
 *
 */
int main(int argc, char **argv)
{
    widgets *a = g_malloc(sizeof(widgets));

    a->app = gtk_application_new("org.accel.bel3", G_APPLICATION_FLAGS_NONE);
    g_signal_connect(a->app, "activate", G_CALLBACK (activate), (gpointer)a);
    g_signal_connect(a->app, "startup", G_CALLBACK (startup), (gpointer)a);

    a->status = g_application_run(G_APPLICATION (a->app), argc, argv);

    g_object_unref(a->app);
    g_free(a);

    return a->status;
}

/** EOF **/
