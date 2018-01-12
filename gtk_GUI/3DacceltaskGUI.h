/**
 * @file		3DacceltaskGUI.h
 * @version		v1.0
 * @date		Jan 2018
 * @author		Egermann, Resch
 *
 * @brief		3Dacceltask GUI header
 *
 */

#ifndef _3DACCELTASKGUI_
#define _3DACCELTASKGUI_

#include "menucallbacks.h"
#include "rs232.h"
#include <gtk/gtk.h>
#include <gdk/gdkkeysyms.h>

#define PI 3.14159265
#define G 9.81
#define GDIVIDER 8190.0	// 2G = 16380 4G = 8190 8G = 4096 16G = 1365
#define UARTWAIT 100
#define BUTTONWAIT 100
#define POLLMIN 10
#define POLLMAX 1000
#define GMIN -4.0
#define GMAX +4.0
#define BAUD 115200
#define OSBUFFER 4096
#define FREELO 0.400
#define FREEHI 1.050
#define FREEFALLTIME 2000

// main struct for all data

typedef struct
{
	GtkApplication *app;
	GMenu *appmenu, *gearmenu;
	GtkWidget *window, *headerbar, *grid, *gearicon, *gearmenubutton, *terminalwindow, *statusBar;
	GtkWidget *button[11], *label[16], *image[2], *box[2], *entry[5], *radioUSB[5];
	GtkWidget *view, *scroll;
	GtkTextIter iter, start, end;
	GtkTextBuffer *buffer;
	gchar line[OSBUFFER], decodedLine[100], bufferStatusBar[100], position6D[4];
	gchar accelerationXout[25], accelerationYout[1525], accelerationZout[25], tempOut[25];
	gchar tiltXout[25], tiltYout[25], tiltZout[25], pitchOut[25], rollOut[25];
	gchar packagesOut[15], errorOut[9], restartPackagesOut[15], fileName[100];
	gboolean sendSerial, safeWaitStep, safeWaitStop, safeWaitClose, safeEnd, transmission, buttonXMC, freeFallLabel;
 	guint id, servoState, saveOutgoing, average;
	gint pollTimeSensor, radioButtonUSBstate, position6Dint;
	gdouble accelerationXdouble, accelerationYdouble, accelerationZdouble;
	gdouble tiltX, tiltY, tiltZ, pitch, roll;
	gdouble acceltriggerX, acceltriggerY, acceltriggerZ;
	GtkStyleContext *context;
} widgets;

typedef struct tm TM;

// function prototypes

void startup(GApplication *app, gpointer data);
void activate(GtkApplication *app, gpointer data);
void constructMenu(GtkApplication *app, gpointer data);
void constructGUI(gpointer data);

#endif

/** EOF **/
