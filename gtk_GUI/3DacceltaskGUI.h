#ifndef _3DACCELTASKGUI_
#define _3DACCELTASKGUI_

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
#include <math.h>

#define PI 3.14159265
#define G 9.81
#define GDIVIDER 8190.0	//2G = 16380 4G = 8190 8G = 4096 16G = 1365 15987.0

typedef struct
{
	GtkApplication *app;
	GtkWidget *window, *headerbar, *grid, *gearicon, *button[25], *label[25], *image[5], *box[2], *entry[10];
	GtkWidget *gearmenubutton, *terminalwindow, *statusBar, *radioUSB[5], *eventbox[5];
	GMenu *appmenu, *gearmenu;
	gchar line[OSBUFFER], decodedLine[100];
	GtkWidget *view, *scroll;
	GtkTextIter iter, start, end;
	GtkTextBuffer *buffer;
	gboolean sendSerial;
 	guint id;
	gint pollTimeSensor;
	gchar bufferStatusBar[100], position6D[4];
	gdouble accelerationXdouble, accelerationYdouble, accelerationZdouble, temperaturedouble;
	gdouble tiltX, tiltY, tiltZ, pitch, roll;
	gchar accelerationXout[25], accelerationYout[1525], accelerationZout[25], tempOut[25];
	gchar tiltXout[25], tiltYout[25], tiltZout[25], pitchOut[25], rollOut[25];
	gint radioButtonUSBstate, position6Dint;
	gdouble acceltriggerX, acceltriggerY, acceltriggerZ;
	gchar packagesOut[15], errorOut[9];
	gint servoSign;

} widgets;

int fd[2];
GIOChannel *channel;
GMainLoop *loop;

typedef struct tm TM;

void startup(GApplication *app, gpointer data);
void activate(GtkApplication *app, gpointer data);
void constructMenu(GtkApplication *app, gpointer data);
void constructGUI(gpointer data);


#endif
