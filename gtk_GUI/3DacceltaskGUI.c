#include "3DacceltaskGUI.h"

const GActionEntry appActions[] =
{
	{ "help", 		help },
	{ "about", 		about },
	{ "quit", 		quit }
};

void constructGUI(gpointer data)
{
	widgets *a = (widgets *) data;

	const char initialinfo[] = "please choose your USB connection ID and poll time - standard is /dev/ttyUSB0 and 50ms";
	gchar stringUSB[15];
	gint i;

	a->position6Dint = 0;
	a->acceltriggerX = 0;
	a->acceltriggerY = 0;
	a->acceltriggerZ = 0;

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

	a->image[0] = gtk_image_new_from_file("./pictures/ALL.png");
	a->box[0] = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	gtk_grid_attach(GTK_GRID (a->grid), a->box[0], 3, 0, 2, 5);
	gtk_box_pack_start(GTK_BOX(a->box[0]), a->image[0], FALSE, FALSE, 0);
	gtk_widget_set_halign(GTK_WIDGET(a->box[0]), GTK_ALIGN_CENTER);
	gtk_widget_set_valign(GTK_WIDGET(a->box[0]), GTK_ALIGN_CENTER);

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
	a->radioButtonUSBstate = 16;

	a->entry[0] = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY (a->entry[0]), "enter poll time in ms");
	gtk_grid_attach(GTK_GRID (a->grid), a->entry[0], 2, 5, 1, 1);
	g_signal_connect (a->entry[0], "activate", G_CALLBACK (entryPollTime), (gpointer) a);
	a->pollTimeSensor = 50;

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

	a->label[0] = gtk_label_new("6D POSITION");
	gtk_grid_attach(GTK_GRID (a->grid), a->label[0], 1, 0, 1, 1);

	a->label[1] = gtk_label_new("X-VALUE");
	gtk_grid_attach(GTK_GRID (a->grid), a->label[1], 1, 1, 1, 1);

	a->label[2] = gtk_label_new("Y-VALUE");
	gtk_grid_attach(GTK_GRID (a->grid), a->label[2], 1, 2, 1, 1);

	a->label[3] = gtk_label_new("Z-VALUE");
	gtk_grid_attach(GTK_GRID (a->grid), a->label[3], 1, 3, 1, 1);

	a->label[4] = gtk_label_new("TEMPERATURE");
	gtk_grid_attach(GTK_GRID (a->grid), a->label[4], 1, 4, 1, 1);

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

	a->label[13] = gtk_label_new("Packages XMC");
	gtk_grid_attach(GTK_GRID (a->grid), a->label[13], 2, 6, 1, 1);

	a->label[14] = gtk_label_new("Errors XMC");
	gtk_grid_attach(GTK_GRID (a->grid), a->label[14], 2, 7, 1, 1);

	a->button[0] = gtk_button_new_with_mnemonic("_CONNECT serial port");
	gtk_widget_set_tooltip_text(GTK_WIDGET(a->button[0]), "connect serial port");
	gtk_widget_set_hexpand(a->button[0], TRUE);
	gtk_widget_set_vexpand(a->button[0], TRUE);
	g_signal_connect(a->button[0], "clicked", G_CALLBACK (connectSerial), (gpointer) a);
	gtk_grid_attach(GTK_GRID (a->grid), a->button[0], 0, 0, 1, 1);

	a->button[1] = gtk_button_new_with_mnemonic("_DISCONNECT serial port");
	gtk_widget_set_tooltip_text(GTK_WIDGET(a->button[1]), "disconnect serial port");
	gtk_widget_set_hexpand(a->button[1], TRUE);
	gtk_widget_set_vexpand(a->button[1], TRUE);
	g_signal_connect(a->button[1], "clicked", G_CALLBACK (disconnectSerial), (gpointer) a);
	gtk_grid_attach(GTK_GRID (a->grid), a->button[1], 0, 1, 1, 1);
	gtk_widget_set_sensitive (GTK_WIDGET (a->button[1]), FALSE);

	a->button[2] = gtk_button_new_with_mnemonic("_TERMINAL raw protocol");
	gtk_widget_set_tooltip_text(GTK_WIDGET(a->button[2]), "teminal raw protocol");
	gtk_widget_set_hexpand(a->button[2], TRUE);
	gtk_widget_set_vexpand(a->button[2], TRUE);
	g_signal_connect(a->button[2], "clicked", G_CALLBACK (rawProtocolData), (gpointer) a);
	gtk_grid_attach(GTK_GRID (a->grid), a->button[2], 0, 2, 1, 1);
	gtk_widget_set_sensitive (GTK_WIDGET (a->button[2]), FALSE);

	a->button[3] = gtk_button_new_with_mnemonic("_DATA transmission");
	gtk_widget_set_tooltip_text(GTK_WIDGET(a->button[3]), "data transmission");
	gtk_widget_set_hexpand(a->button[3], TRUE);
	gtk_widget_set_vexpand(a->button[3], TRUE);
	g_signal_connect(a->button[3], "clicked", G_CALLBACK (dataTransmission), (gpointer) a);
	gtk_grid_attach(GTK_GRID (a->grid), a->button[3], 0, 3, 1, 1);
	gtk_widget_set_sensitive (GTK_WIDGET (a->button[3]), FALSE);

	a->button[4] = gtk_button_new_with_mnemonic("_PYTHON diagrams");
	gtk_widget_set_tooltip_text(GTK_WIDGET(a->button[4]), "python diagrams");
	gtk_widget_set_hexpand(a->button[4], TRUE);
	gtk_widget_set_vexpand(a->button[4], TRUE);
	g_signal_connect(a->button[4], "clicked", G_CALLBACK (pythonConnector), (gpointer) a);
	gtk_grid_attach(GTK_GRID (a->grid), a->button[4], 0, 4, 1, 1);
	gtk_widget_set_sensitive (GTK_WIDGET (a->button[4]), FALSE);

	a->button[5] = gtk_button_new_with_mnemonic("P_YTHON sprites");
	gtk_widget_set_tooltip_text(GTK_WIDGET(a->button[5]), "python sprites");
	gtk_widget_set_hexpand(a->button[5], TRUE);
	gtk_widget_set_vexpand(a->button[5], TRUE);
	g_signal_connect(a->button[5], "clicked", G_CALLBACK (pythonSpriteConnector), (gpointer) a);
	gtk_grid_attach(GTK_GRID (a->grid), a->button[5], 0, 5, 1, 1);
	gtk_widget_set_sensitive (GTK_WIDGET (a->button[5]), FALSE);

	a->button[6] = gtk_button_new_with_mnemonic("SER_VO control");
	gtk_widget_set_tooltip_text(GTK_WIDGET(a->button[6]), "servo control");
	gtk_widget_set_hexpand(a->button[6], TRUE);
	gtk_widget_set_vexpand(a->button[6], TRUE);
	g_signal_connect(a->button[6], "clicked", G_CALLBACK (servoConnector), (gpointer) a);
	gtk_grid_attach(GTK_GRID (a->grid), a->button[6], 0, 6, 1, 1);
	gtk_widget_set_sensitive (GTK_WIDGET (a->button[6]), FALSE);

	a->statusBar = gtk_statusbar_new();
	gtk_grid_attach (GTK_GRID (a->grid), a->statusBar, 0, 9, 4, 1);
	a->id = gtk_statusbar_get_context_id (GTK_STATUSBAR (a->statusBar), "demo");

	snprintf(a->bufferStatusBar, sizeof(initialinfo)+1, "%s", initialinfo);
	gtk_statusbar_push (GTK_STATUSBAR (a->statusBar), a->id, a->bufferStatusBar);

	a->label[10] = gtk_label_new ("<span foreground='white' background='green' weight='ultrabold' font='20'> X TRIGGER </span>");
	gtk_label_set_use_markup (GTK_LABEL (a->label[10]), TRUE);
	gtk_grid_attach(GTK_GRID (a->grid), a->label[10], 4, 5, 1, 1);

	a->label[11] = gtk_label_new ("<span foreground='white' background='green' weight='ultrabold' font='20'> Y TRIGGER </span>");
	gtk_label_set_use_markup (GTK_LABEL (a->label[11]), TRUE);
	gtk_grid_attach(GTK_GRID (a->grid), a->label[11], 4, 6, 1, 1);

	a->label[12] = gtk_label_new ("<span foreground='white' background='green' weight='ultrabold' font='20'> Z TRIGGER </span>");
	gtk_label_set_use_markup (GTK_LABEL (a->label[12]), TRUE);
	gtk_grid_attach(GTK_GRID (a->grid), a->label[12], 4, 7, 1, 1);
}

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

void activate(GtkApplication *app, gpointer data)
{
	widgets *a = (widgets *) data;

	a->window = gtk_application_window_new(app);

	gtk_window_set_application(GTK_WINDOW (a->window), GTK_APPLICATION (app));
	gtk_window_set_title(GTK_WINDOW (a->window), "GNOME Menu");
	gtk_window_set_position(GTK_WINDOW (a->window), GTK_WIN_POS_CENTER);
	gtk_window_set_resizable(GTK_WINDOW (a->window), FALSE);

	constructMenu(app,(gpointer)a);
	constructGUI((gpointer)a);

	gtk_widget_show_all(GTK_WIDGET(a->window));
}

void startup(GApplication *app, gpointer data)
{
	widgets *a = (widgets *)data;

	g_action_map_add_action_entries(G_ACTION_MAP(app), appActions, G_N_ELEMENTS(appActions), (gpointer)a);
}

int main(int argc, char **argv)
{
	gint status;
	widgets *a = g_malloc(sizeof(widgets));

	a->app = gtk_application_new("org.gtk.example", G_APPLICATION_FLAGS_NONE);
	g_signal_connect(a->app, "activate", G_CALLBACK (activate), (gpointer)a);
	g_signal_connect(a->app, "startup", G_CALLBACK (startup), (gpointer)a);
	status = g_application_run(G_APPLICATION (a->app), argc, argv);
	
	g_object_unref(a->app);
	g_free(a);

	return status;
}
