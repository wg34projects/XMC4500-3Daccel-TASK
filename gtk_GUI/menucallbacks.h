#ifndef _menucallbacks_
#define _menucallbacks_

#include "3DacceltaskGUI.h"
#include <gtk/gtk.h>
#include <gdk/gdkkeysyms.h>

#include "rs232.h"

#define BAUD 115200
#define OSBUFFER 4096

void connectSerial(GtkButton *button, gpointer data);
void disconnectSerial(GtkButton *button, gpointer data);
guint wait(gpointer data);
void rawProtocolData(GtkButton *button, gpointer data);
void rawProtocolDataTimed(gpointer data);
void quit(GSimpleAction *action, GVariant *parameter, gpointer data);
void about(GSimpleAction *action, GVariant *parameter, gpointer data);
void help(GSimpleAction *action, GVariant *parameter, gpointer data);
void messageDialog(GSimpleAction *action, GVariant *parameter, gpointer data, gchar *showText);

#endif