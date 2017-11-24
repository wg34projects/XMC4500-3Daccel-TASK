#include "3DacceltaskGUI.h"

guint wait(gpointer data)
{
	widgets *a = (widgets *) data;

	rawProtocolDataTimed((gpointer) a);

	gtk_text_buffer_get_start_iter (a->buffer, &a->iter);
  	gtk_text_buffer_insert (a->buffer, &a->iter, a->line, -1);
	gtk_text_buffer_get_bounds (a->buffer, &a->start, &a->end);
	gtk_text_buffer_apply_tag_by_name (a->buffer, "word_wrap", &a->start, &a->end);
	gtk_text_buffer_apply_tag_by_name (a->buffer, "not_editable", &a->start, &a->end);

	return a->pollSerial;
}

void connectSerial(GtkButton *button, gpointer data)
{
	widgets *a = (widgets *) data;
    char mode[]= {'8','N','1', 0};

	a->pollSerial = TRUE;

    if(RS232_OpenComport(16, BAUD, mode))
    {
		gtk_label_set_label((GtkLabel*)a->label[0], "ERROR opening COM port");
    }
	else
	{
		gtk_label_set_label((GtkLabel*)a->label[0], "SUCCESS opening COM port");
		gtk_widget_set_sensitive (GTK_WIDGET (a->button[0]), FALSE);
		gtk_widget_set_sensitive (GTK_WIDGET (a->button[1]), TRUE);
		gtk_widget_set_sensitive (GTK_WIDGET (a->button[2]), TRUE);
	}
}

void disconnectSerial(GtkButton *button, gpointer data)
{
	widgets *a = (widgets *) data;

	gtk_widget_set_sensitive (GTK_WIDGET (a->button[0]), TRUE);
	gtk_widget_set_sensitive (GTK_WIDGET (a->button[1]), FALSE);
	gtk_widget_set_sensitive (GTK_WIDGET (a->button[2]), FALSE);
	a->pollSerial = FALSE;
    RS232_CloseComport(16);
	gtk_label_set_label((GtkLabel*)a->label[0], "SUCCESS closing COM port");
}

void showRawData(GtkButton *button, gpointer data)
{
/*	widgets *a = (widgets *) data;*/
}

void rawProtocolData(GtkButton *button, gpointer data)
{
	widgets *a = (widgets *) data;
	
	strcpy(a->line, "TEST");

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

	g_timeout_add (100, (GSourceFunc) wait, (gpointer) a);
}

void rawProtocolDataTimed(gpointer data)
{
	widgets *a = (widgets *) data;
	unsigned char buf[OSBUFFER];
	int i = 0, n = 0, lineCount = 0;

	memset (&buf, 0, sizeof (buf));
	n = RS232_PollComport(16, buf, (OSBUFFER-1));
	RS232_flushRX(16);

	for (i = 0; i < strlen((char *)buf); i++)
	{
		if (buf[i] == '\n')
		{
			lineCount++;
		}
	}

/*	char test[lineCount][100];*/
/*	for (i = 0; i < lineCount; i++)*/
/*	{*/
/*		memset (&test[i], 0, sizeof (test[i]));	*/
/*		sscanf((char *)buf, "%s", test[i]);*/
/*		g_print("txt%2d  %s\n", i, test[i]);*/
/*	}*/

	g_print("lines %d\n", lineCount);
	g_print("recvd %d\n", n);
	g_print("chars %ld\n", strlen((char *)buf));

	if (lineCount > 0)
	{
		sprintf(a->line, "%s", (char *)buf);
	}

//	g_print("%s", (char *)buf);	
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
