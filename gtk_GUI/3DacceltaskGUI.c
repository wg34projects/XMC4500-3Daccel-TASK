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

	const char initialinfo[] = "information center accelerometer task...";

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

/*	a->label[0] = gtk_label_new("GUI accelerator task - informations...");*/
/*	gtk_grid_attach(GTK_GRID (a->grid), a->label[0], 0, 0, 4, 1);*/

/*	a->image[0] = gtk_image_new_from_file("./pictures/ALL.png");*/
/*	a->box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);*/
/*	gtk_grid_attach(GTK_GRID (a->grid), a->box, 2, 1, 2, 8);*/
/*	gtk_box_pack_start(GTK_BOX(a->box), a->image[0], FALSE, FALSE, 0);*/
/*	gtk_widget_set_opacity(GTK_WIDGET(a->box), 0.20);*/

/*	a->image[0] = gtk_image_new_from_file("./pictures/3Da.png");*/
/*	a->box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);*/
/*	gtk_grid_attach(GTK_GRID (a->grid), a->box, 2, 1, 3, 8);*/
/*	gtk_box_pack_start(GTK_BOX(a->box), a->image[0], FALSE, FALSE, 0);*/
/*	gtk_widget_set_opacity(GTK_WIDGET(a->box), 0.20);*/

/*	a->entry[0] = gtk_entry_new();*/
/*    gtk_entry_set_placeholder_text(GTK_ENTRY (a->entry[0]), "X-VALUE");*/
/*	gtk_grid_attach(GTK_GRID (a->grid), a->entry[0], 1, 1, 1, 1);*/

/*	a->entry[1] = gtk_entry_new();*/
/*    gtk_entry_set_placeholder_text(GTK_ENTRY (a->entry[1]), "Y-VALUE");*/
/*	gtk_grid_attach(GTK_GRID (a->grid), a->entry[1], 1, 2, 1, 1);*/

/*	a->entry[2] = gtk_entry_new();*/
/*    gtk_entry_set_placeholder_text(GTK_ENTRY (a->entry[2]), "Z-VALUE");*/
/*	gtk_grid_attach(GTK_GRID (a->grid), a->entry[2], 1, 3, 1, 1);*/

	a->label[1] = gtk_label_new("6D POSITION");
	gtk_grid_attach(GTK_GRID (a->grid), a->label[1], 1, 1, 1, 1);

	a->label[2] = gtk_label_new("X-VALUE");
	gtk_grid_attach(GTK_GRID (a->grid), a->label[2], 1, 2, 1, 1);

	a->label[3] = gtk_label_new("Y-VALUE");
	gtk_grid_attach(GTK_GRID (a->grid), a->label[3], 1, 3, 1, 1);

	a->label[4] = gtk_label_new("Z-VALUE");
	gtk_grid_attach(GTK_GRID (a->grid), a->label[4], 1, 4, 1, 1);

	a->label[5] = gtk_label_new("TEMPERATURE");
	gtk_grid_attach(GTK_GRID (a->grid), a->label[5], 1, 5, 1, 1);

	a->button[0] = gtk_button_new_with_mnemonic("_CONNECT serial port");
	gtk_widget_set_tooltip_text(GTK_WIDGET(a->button[0]), "connect serial port");
	gtk_widget_set_hexpand(a->button[0], TRUE);
	gtk_widget_set_vexpand(a->button[0], TRUE);
	g_signal_connect(a->button[0], "clicked", G_CALLBACK (connectSerial), (gpointer) a);
	gtk_grid_attach(GTK_GRID (a->grid), a->button[0], 0, 1, 1, 1);

	a->button[1] = gtk_button_new_with_mnemonic("_DISCONNECT serial port");
	gtk_widget_set_tooltip_text(GTK_WIDGET(a->button[1]), "disconnect serial port");
	gtk_widget_set_hexpand(a->button[1], TRUE);
	gtk_widget_set_vexpand(a->button[1], TRUE);
	g_signal_connect(a->button[1], "clicked", G_CALLBACK (disconnectSerial), (gpointer) a);
	gtk_grid_attach(GTK_GRID (a->grid), a->button[1], 0, 2, 1, 1);
	gtk_widget_set_sensitive (GTK_WIDGET (a->button[1]), FALSE);

	a->button[2] = gtk_button_new_with_mnemonic("_TERMINAL raw protocol");
	gtk_widget_set_tooltip_text(GTK_WIDGET(a->button[2]), "teminal raw protocol");
	gtk_widget_set_hexpand(a->button[2], TRUE);
	gtk_widget_set_vexpand(a->button[2], TRUE);
	g_signal_connect(a->button[2], "clicked", G_CALLBACK (rawProtocolData), (gpointer) a);
	gtk_grid_attach(GTK_GRID (a->grid), a->button[2], 0, 3, 1, 1);
	gtk_widget_set_sensitive (GTK_WIDGET (a->button[2]), FALSE);

	a->statusBar = gtk_statusbar_new();
	gtk_grid_attach (GTK_GRID (a->grid), a->statusBar, 0, 9, 3, 1);
	a->id = gtk_statusbar_get_context_id (GTK_STATUSBAR (a->statusBar), "demo");

	snprintf(a->bufferStatusBar, sizeof(initialinfo)+1, "%s", initialinfo);
	gtk_statusbar_push (GTK_STATUSBAR (a->statusBar), a->id, a->bufferStatusBar);

/*	a->button[3] = gtk_button_new_with_mnemonic("_REQUEST data");*/
/*	gtk_widget_set_tooltip_text(GTK_WIDGET(a->button[3]), "request data");*/
/*	gtk_widget_set_hexpand(a->button[3], TRUE);*/
/*	gtk_widget_set_vexpand(a->button[3], TRUE);*/
/*	g_signal_connect(a->button[3], "clicked", G_CALLBACK (requestData), (gpointer) a);*/
/*	gtk_grid_attach(GTK_GRID (a->grid), a->button[3], 0, 4, 1, 1);*/

/*	a->button[2] = gtk_button_new_with_mnemonic("PLOT r_aw acceleration");*/
/*	gtk_widget_set_tooltip_text(GTK_WIDGET(a->button[2]), "raw protocol data");*/
/*	gtk_widget_set_hexpand(a->button[2], TRUE);*/
/*	gtk_widget_set_vexpand(a->button[2], TRUE);*/
/*	g_signal_connect(a->button[2], "clicked", G_CALLBACK (stopAll), (gpointer) a);*/
/*	gtk_grid_attach(GTK_GRID (a->grid), a->button[2], 0, 5, 1, 1);*/

/*	a->button[3] = gtk_button_new_with_mnemonic("PLOT a_cceleration vector");*/
/*	gtk_widget_set_tooltip_text(GTK_WIDGET(a->button[3]), "acceleration vector");*/
/*	gtk_widget_set_hexpand(a->button[3], TRUE);*/
/*	gtk_widget_set_vexpand(a->button[3], TRUE);*/
/*	g_signal_connect(a->button[3], "clicked", G_CALLBACK (stopAll), (gpointer) a);*/
/*	gtk_grid_attach(GTK_GRID (a->grid), a->button[3], 0, 6, 1, 1);*/

/*	a->button[6] = gtk_button_new_with_mnemonic("Setup _communication");*/
/*	gtk_widget_set_tooltip_text(GTK_WIDGET(a->button[6]), "Setup communication");*/
/*	gtk_widget_set_hexpand(a->button[6], TRUE);*/
/*	gtk_widget_set_vexpand(a->button[6], TRUE);*/
/*	g_signal_connect(a->button[6], "clicked", G_CALLBACK (stopAll), (gpointer) a);*/
/*	gtk_grid_attach(GTK_GRID (a->grid), a->button[6], 0, 7, 1, 1);*/

/*	a->button[7] = gtk_button_new_with_mnemonic("Infos _about us");*/
/*	gtk_widget_set_tooltip_text(GTK_WIDGET(a->button[7]), "Infos about us");*/
/*	gtk_widget_set_hexpand(a->button[7], TRUE);*/
/*	gtk_widget_set_vexpand(a->button[7], TRUE);*/
/*	g_signal_connect(a->button[7], "clicked", G_CALLBACK (stopAll), (gpointer) a);*/
/*	gtk_grid_attach(GTK_GRID (a->grid), a->button[7], 0, 8, 1, 1);*/

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
