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
#define GDIVIDER 16380.0	//2G = 16380 4G = 8190 8G = 4096 16G = 1365 15987.0
#define UARTWAIT 100
#define BUTTONWAIT 50
#define BUTTONS 7

typedef struct
{
	GtkApplication *app;
	GMenu *appmenu, *gearmenu;
	GtkWidget *window, *headerbar, *grid, *gearicon, *gearmenubutton, *terminalwindow, *statusBar;
	GtkWidget *button[10], *label[16], *image[2], *box[2], *entry[5], *radioUSB[5];
	GtkWidget *view, *scroll;
	GtkTextIter iter, start, end;
	GtkTextBuffer *buffer;
	gchar line[OSBUFFER], decodedLine[100], bufferStatusBar[100], position6D[4];
	gchar accelerationXout[25], accelerationYout[1525], accelerationZout[25], tempOut[25];
	gchar tiltXout[25], tiltYout[25], tiltZout[25], pitchOut[25], rollOut[25];
	gchar packagesOut[15], errorOut[9], fileName[100];
	gboolean sendSerial, safeWaitStep, safeWaitStop, safeWaitClose, safeEnd, transmission, buttonXMC;
 	guint id, servoState, saveOutgoing;
	gint pollTimeSensor, radioButtonUSBstate, position6Dint;
	gdouble accelerationXdouble, accelerationYdouble, accelerationZdouble, temperaturedouble;
	gdouble tiltX, tiltY, tiltZ, pitch, roll;
	gdouble acceltriggerX, acceltriggerY, acceltriggerZ;
} widgets;

typedef struct tm TM;

void startup(GApplication *app, gpointer data);
void activate(GtkApplication *app, gpointer data);
void constructMenu(GtkApplication *app, gpointer data);
void constructGUI(gpointer data);

#endif
