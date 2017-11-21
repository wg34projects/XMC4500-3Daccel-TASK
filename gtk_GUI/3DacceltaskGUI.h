#ifndef _beltcontrol_
#define _beltcontrol_

#include "menucallbacks.h"
#include <gtk/gtk.h>
#include <gdk/gdkkeysyms.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include <glib/gprintf.h>
#include <gio/gio.h>
#include <unistd.h>
#include <fcntl.h>

typedef struct
{
	GtkApplication *app;
	GtkWidget *window, *headerbar, *grid, *gearicon, *button[25], *label[5], *image[5], *box, *entry[5];
	GtkWidget *gearmenubutton, *terminalwindow;
	GMenu *appmenu, *gearmenu;
	gchar line[OSBUFFER], decodedLine[100];
	GtkWidget *view, *scroll;
	GtkTextIter iter, start, end;
	GtkTextBuffer *buffer;
	gboolean pollSerial; 

} widgets;

typedef struct tm TM;

void startup(GApplication *app, gpointer data);
void activate(GtkApplication *app, gpointer data);
void constructMenu(GtkApplication *app, gpointer data);
void constructGUI(gpointer data);

#endif
