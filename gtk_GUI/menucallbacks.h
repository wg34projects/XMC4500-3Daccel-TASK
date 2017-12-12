#ifndef _MENUCALLBACKS_
#define _MENUCALLBACKS_

#include "3DacceltaskGUI.h"
#include <gtk/gtk.h>
#include <gdk/gdkkeysyms.h>

#include "rs232.h"

#define BAUD 115200
#define OSBUFFER 4096

void connectSerial(GtkButton *button, gpointer data);
void disconnectSerial(GtkButton *button, gpointer data);
guint waitSendTerminal(gpointer data);
guint waitSendnoTerminal(gpointer data);
guint waitSendPython(gpointer data);
void readRadioUSB(GtkWidget *button, gpointer *data);
void entryPollTime (GtkWidget *widget, gpointer data);
unsigned int getInteger(char *input, int *numInteger);
void dataTransmission(GtkButton *button, gpointer data);
void rawProtocolData(GtkButton *button, gpointer data);
void rawProtocolDataTimed(gpointer data);
void quit(GSimpleAction *action, GVariant *parameter, gpointer data);
void about(GSimpleAction *action, GVariant *parameter, gpointer data);
void help(GSimpleAction *action, GVariant *parameter, gpointer data);
void messageDialog(GSimpleAction *action, GVariant *parameter, gpointer data, gchar *showText);
void closeTerminalWindow(GtkButton *button, gpointer data);
void requestData(gpointer data);
void pythonConnector(GtkButton *button, gpointer data);
void pythonSpriteConnector(GtkButton *button, gpointer data);
unsigned int getDouble(char *input, double *numDouble);
void entryXtrigger (GtkWidget *widget, gpointer data);
void entryYtrigger (GtkWidget *widget, gpointer data);
void entryZtrigger (GtkWidget *widget, gpointer data);
void servoConnector (GtkButton *button, gpointer data);

#endif
