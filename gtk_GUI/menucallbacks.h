#ifndef _MENUCALLBACKS_
#define _MENUCALLBACKS_

#include "3DacceltaskGUI.h"
#include <gtk/gtk.h>
#include <gdk/gdkkeysyms.h>

#include "rs232.h"

#define BAUD 115200
#define OSBUFFER 4096

// entry callbacks

void entryPollTime (GtkWidget *widget, gpointer data);
void entryXtrigger (GtkWidget *widget, gpointer data);
void entryYtrigger (GtkWidget *widget, gpointer data);
void entryZtrigger (GtkWidget *widget, gpointer data);
void fileName (GtkWidget *widget, gpointer data);

// radio button callbacks

void readRadioUSB(GtkWidget *button, gpointer *data);

// timer

guint waitSendTerminal(gpointer data);
guint waitSendnoTerminal(gpointer data);
guint waitSendPython(gpointer data);
guint safeStop(gpointer data);
guint safeEnd(gpointer data);
guint safeClose(gpointer data);
guint buttonFeedback(gpointer data);

// connection callbacks

void connectSerial(GtkButton *button, gpointer data);
void requestData(gpointer data);
void servoConnector (gpointer data);
void statisticConnector (GtkButton *button, gpointer data);
void servo(GtkWidget *checkbutton, gpointer data);
void dataTransmission(GtkButton *button, gpointer data);
void pythonConnector(GtkButton *button, gpointer data);
void pythonSpriteConnector(GtkButton *button, gpointer data);
void rawProtocolData(GtkButton *button, gpointer data);

// input callback

void rawProtocolDataTimed(gpointer data);
void saveData(GtkButton *button, gpointer data);

// dialog callbacks

void quit(GSimpleAction *action, GVariant *parameter, gpointer data);
void about(GSimpleAction *action, GVariant *parameter, gpointer data);
void help(GSimpleAction *action, GVariant *parameter, gpointer data);
void messageDialog(GSimpleAction *action, GVariant *parameter, gpointer data, gchar *showText);

// misc functions

unsigned int getInteger(char *input, int *numInteger);
unsigned int getDouble(char *input, double *numDouble);

#endif
