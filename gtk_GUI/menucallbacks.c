#include "3DacceltaskGUI.h"

guint waitSend(gpointer data)
{
	widgets *a = (widgets *) data;
	char lineWithLF[OSBUFFER+1];

	sprintf(lineWithLF, "%s\n", a->line);

	requestData((gpointer) a);

	rawProtocolDataTimed((gpointer) a);

	gtk_text_buffer_get_start_iter (a->buffer, &a->iter);
  	gtk_text_buffer_insert (a->buffer, &a->iter, lineWithLF, -1);
	gtk_text_buffer_get_bounds (a->buffer, &a->start, &a->end);
	gtk_text_buffer_apply_tag_by_name (a->buffer, "word_wrap", &a->start, &a->end);
	gtk_text_buffer_apply_tag_by_name (a->buffer, "not_editable", &a->start, &a->end);

	return a->sendSerial;
}

void connectSerial(GtkButton *button, gpointer data)
{
	widgets *a = (widgets *) data;
    char mode[]= {'8','N','1', 0};
	const char openComPortError[] = "ERROR opening COM port";
	const char openComPortSuccess[] = "SUCCESS opening COM port";

    if(RS232_OpenComport(16, BAUD, mode))
    {
		snprintf(a->bufferStatusBar, sizeof(openComPortError)+1, "%s", openComPortError);
		gtk_statusbar_push (GTK_STATUSBAR (a->statusBar), a->id, a->bufferStatusBar);
    }
	else
	{
		snprintf(a->bufferStatusBar, sizeof(openComPortSuccess)+1, "%s", openComPortSuccess);
		gtk_statusbar_push (GTK_STATUSBAR (a->statusBar), a->id, a->bufferStatusBar);
		gtk_widget_set_sensitive (GTK_WIDGET (a->button[0]), FALSE);
		gtk_widget_set_sensitive (GTK_WIDGET (a->button[1]), TRUE);
		gtk_widget_set_sensitive (GTK_WIDGET (a->button[2]), TRUE);
	}
}

void requestData(gpointer data)
{
/*	widgets *a = (widgets *) data;*/
	unsigned char requestText[] = "REQUEST";
/*	const char requestDataPackage[] = "NEW DATA requested";*/

	RS232_flushTX(16);
	RS232_SendBuf(16, requestText, (int)sizeof(requestText));
	RS232_SendByte(16, '\r');

/*	snprintf(a->bufferStatusBar, sizeof(requestDataPackage)+1, "%s", requestDataPackage);*/
/*	gtk_statusbar_push (GTK_STATUSBAR (a->statusBar), a->id, a->bufferStatusBar);*/
}

void disconnectSerial(GtkButton *button, gpointer data)
{
	widgets *a = (widgets *) data;

	const char closeComPortSuccess[] = "SUCCESS closing COM port";

	gtk_widget_set_sensitive (GTK_WIDGET (a->button[0]), TRUE);
	gtk_widget_set_sensitive (GTK_WIDGET (a->button[1]), FALSE);
	gtk_widget_set_sensitive (GTK_WIDGET (a->button[2]), FALSE);

	a->sendSerial = FALSE;

    RS232_CloseComport(16);
	snprintf(a->bufferStatusBar, sizeof(closeComPortSuccess)+1, "%s", closeComPortSuccess);
	gtk_statusbar_push (GTK_STATUSBAR (a->statusBar), a->id, a->bufferStatusBar);
}

void showRawData(GtkButton *button, gpointer data)
{
/*	widgets *a = (widgets *) data;*/
}

void rawProtocolData(GtkButton *button, gpointer data)
{
	widgets *a = (widgets *) data;

	strcpy(a->line, ".");

    a->terminalwindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title (GTK_WINDOW (a->terminalwindow), "Terminal window");
    gtk_container_set_border_width (GTK_CONTAINER (a->terminalwindow), 0);
    gtk_widget_set_size_request (a->terminalwindow, 400, 800);
	gtk_window_set_resizable(GTK_WINDOW (a->terminalwindow), TRUE);
    
	a->buffer = gtk_text_buffer_new (NULL);

	gtk_text_buffer_create_tag (a->buffer, "not_editable",	"editable", FALSE, NULL);
	gtk_text_buffer_create_tag (a->buffer, "word_wrap", "wrap_mode", GTK_WRAP_WORD, NULL);

	a->view = gtk_text_view_new_with_buffer (a->buffer);

	a->scroll = gtk_scrolled_window_new (NULL, NULL);
	gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (a->scroll), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);

	gtk_container_add (GTK_CONTAINER (a->scroll), a->view);

	gtk_container_add (GTK_CONTAINER (a->terminalwindow), a->scroll);
	gtk_widget_show_all(GTK_WIDGET(a->terminalwindow));

	a->sendSerial = TRUE;

	g_timeout_add (100, (GSourceFunc) waitSend, (gpointer) a);
}

void rawProtocolDataTimed(gpointer data)
{
	widgets *a = (widgets *) data;
	unsigned char buf[OSBUFFER];
	int n = 0, i = 0;
	gchar accelerationX[7], accelerationY[7], accelerationZ[7], temperature[3];
	gint accelerationXint, accelerationYint, accelerationZint, temperatureint;

	memset (&buf, 0, sizeof (buf));
	n = RS232_PollComport(16, buf, (OSBUFFER-1));
	RS232_flushRX(16);

	if (n > 0)
	{
		sprintf(a->line, "%s", (char *)buf);
	}

	for (i = 0; i < strlen(a->line); i++)
	{
		if (a->line[i] == '\n' || a->line[i] == '\r')
		{
			a->line[i] = '\0';
			break;
		}
	}

	if (strncpy(a->position6D, a->line+1, 3) != a->position6D)
	{
		g_print("strncpy1 error\n");
	}

	gtk_label_set_label((GtkLabel*)a->label[1], a->position6D);

	if (strncpy(accelerationX, a->line+5, 7) != accelerationX)
	{
		g_print("strncpy2 error\n");
	}
	accelerationX[7] = '\0';
	getInteger(accelerationX, &accelerationXint);
	a->accelerationXdouble = accelerationXint / 15987.0;
	sprintf(a->accelerationXout, "%f g", a->accelerationXdouble);

	gtk_label_set_label((GtkLabel*)a->label[2], a->accelerationXout);

	if (strncpy(accelerationY, a->line+13, 7) != accelerationY)
	{
		g_print("strncpy3 error\n");
	}
	accelerationY[7] = '\0';
	getInteger(accelerationY, &accelerationYint);
	a->accelerationYdouble = accelerationYint / 15987.0;
	sprintf(a->accelerationYout, "%f g", a->accelerationYdouble);

	gtk_label_set_label((GtkLabel*)a->label[3], a->accelerationYout);

	if (strncpy(accelerationZ, a->line+21, 7) != accelerationZ)
	{
		g_print("strncpy4 error\n");
	}
	accelerationZ[7] = '\0';
	getInteger(accelerationZ, &accelerationZint);
	a->accelerationZdouble = accelerationZint / 15987.0;
	sprintf(a->accelerationZout, "%f g", a->accelerationZdouble);

	gtk_label_set_label((GtkLabel*)a->label[4], a->accelerationZout);

	if (strncpy(temperature, a->line+29, 2) != temperature)
	{
		g_print("strncpy5 error\n");
	}
	temperature[2] = '\0';
	getInteger(temperature, &temperatureint);
	a->temperaturedouble = temperatureint / 1.0;
	sprintf(a->tempOut, "%.2f °C", a->temperaturedouble);

	gtk_label_set_label((GtkLabel*)a->label[5], a->tempOut);
}

unsigned int getInteger(char *input, int *numInteger)
{
    unsigned long int number = 0;
    char *pointToEnd = NULL;

    number = strtoul(input, &pointToEnd, 0);
    if(*pointToEnd != '\0')
    {
        return 1;
    }
    else
    {
        *numInteger = (int)number;
        return 0;
    }
}

void about(GSimpleAction *action, GVariant *parameter, gpointer data)
{
	widgets *a = (widgets *) data;

	messageDialog(action, NULL, (gpointer) a, "BEL3 ESS accelerometer task\n\nWerner Egermann, Helmut Resch");
}

void help(GSimpleAction *action, GVariant *parameter, gpointer data)
{
	widgets *a = (widgets *) data;

	messageDialog(action, NULL, (gpointer) a, "Find here some helpful information");
}

void messageDialog(GSimpleAction *action, GVariant *parameter, gpointer data, gchar *showText)
{
	widgets *a = (widgets *) data;
	const gchar *name;
	GtkWidget *dialog;

	name = g_action_get_name (G_ACTION (action));
	dialog = gtk_message_dialog_new (GTK_WINDOW (a->window), GTK_DIALOG_DESTROY_WITH_PARENT|GTK_DIALOG_MODAL, GTK_MESSAGE_INFO, GTK_BUTTONS_OK, "%s\n\n%s", name, showText);

	g_signal_connect (dialog, "response", G_CALLBACK (gtk_widget_destroy), NULL);
	gtk_widget_show (dialog);
}

void quit(GSimpleAction *action, GVariant *parameter, gpointer data)
{
	widgets *a = (widgets *) data;

	g_application_quit(G_APPLICATION (a->app));
}
