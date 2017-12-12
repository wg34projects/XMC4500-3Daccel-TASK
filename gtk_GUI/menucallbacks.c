#include "3DacceltaskGUI.h"

void entryPollTime (GtkWidget *widget, gpointer data)
{
	widgets *a = (widgets *) data;
	gchar *buffer;

	buffer = (gchar*) gtk_entry_get_text (GTK_ENTRY (a->entry[0]));
	getInteger(buffer, &a->pollTimeSensor);

	if (a->pollTimeSensor < 10)
	{
		g_sprintf (a->bufferStatusBar, "you have chosen %d ms poll time, lower limit is 10 ms, this is now set", a->pollTimeSensor);
		gtk_statusbar_push (GTK_STATUSBAR (a->statusBar), a->id, a->bufferStatusBar);
		a->pollTimeSensor = 10;
	}
	else if (a->pollTimeSensor > 1000)
	{
		g_sprintf (a->bufferStatusBar, "you have chosen %d ms poll time, upper limit is 1000 ms, this is now set", a->pollTimeSensor);
		gtk_statusbar_push (GTK_STATUSBAR (a->statusBar), a->id, a->bufferStatusBar);
		a->pollTimeSensor = 1000;		
	}
	else if (a->pollTimeSensor > 0 && a->pollTimeSensor < 1001)
	{
		g_sprintf (a->bufferStatusBar, "you have chosen %d ms poll time", a->pollTimeSensor);
		gtk_statusbar_push (GTK_STATUSBAR (a->statusBar), a->id, a->bufferStatusBar);
	}
}

void entryXtrigger (GtkWidget *widget, gpointer data)
{
	widgets *a = (widgets *) data;
	gchar *buffer;
	gint rv = 0;

	buffer = (gchar*) gtk_entry_get_text (GTK_ENTRY (a->entry[1]));
	rv = getDouble(buffer, &a->acceltriggerX);

	if (a->acceltriggerX < -2.0 && rv == 0)
	{
		g_sprintf (a->bufferStatusBar, "minimum -2.0 g set");
		gtk_statusbar_push (GTK_STATUSBAR (a->statusBar), a->id, a->bufferStatusBar);
		a->acceltriggerX = -2.0;
	}
	else if (a->acceltriggerX > 2.0 && rv == 0)
	{
		g_sprintf (a->bufferStatusBar, "maximum +2,0 g set");
		gtk_statusbar_push (GTK_STATUSBAR (a->statusBar), a->id, a->bufferStatusBar);
		a->acceltriggerX = 2.0;		
	}
	else if (a->acceltriggerX >= -2.0 && a->acceltriggerX <= 2.0 && rv == 0)
	{
		g_sprintf (a->bufferStatusBar, "you have chosen %.2f g trigger for X", a->acceltriggerX);
		gtk_statusbar_push (GTK_STATUSBAR (a->statusBar), a->id, a->bufferStatusBar);
	}
	else if (rv == 1)
	{
		g_sprintf (a->bufferStatusBar, "you did not enter a correct number");
		gtk_statusbar_push (GTK_STATUSBAR (a->statusBar), a->id, a->bufferStatusBar);
	}
}

void entryYtrigger (GtkWidget *widget, gpointer data)
{
	widgets *a = (widgets *) data;
	gchar *buffer;
	gint rv = 0;

	buffer = (gchar*) gtk_entry_get_text (GTK_ENTRY (a->entry[2]));
	rv = getDouble(buffer, &a->acceltriggerY);

	if (a->acceltriggerY < -2.0 && rv == 0)
	{
		g_sprintf (a->bufferStatusBar, "minimum -2.0 g set");
		gtk_statusbar_push (GTK_STATUSBAR (a->statusBar), a->id, a->bufferStatusBar);
		a->acceltriggerY = -2.0;
	}
	else if (a->acceltriggerY > 2.0 && rv == 0)
	{
		g_sprintf (a->bufferStatusBar, "maximum +2,0 g set");
		gtk_statusbar_push (GTK_STATUSBAR (a->statusBar), a->id, a->bufferStatusBar);
		a->acceltriggerY = 2.0;		
	}
	else if (a->acceltriggerY >= -2.0 && a->acceltriggerY <= 2.0 && rv == 0)
	{
		g_sprintf (a->bufferStatusBar, "you have chosen %.2f g trigger for Y", a->acceltriggerY);
		gtk_statusbar_push (GTK_STATUSBAR (a->statusBar), a->id, a->bufferStatusBar);
	}
	else if (rv == 1)
	{
		g_sprintf (a->bufferStatusBar, "you did not enter a correct number");
		gtk_statusbar_push (GTK_STATUSBAR (a->statusBar), a->id, a->bufferStatusBar);
	}
}

void entryZtrigger (GtkWidget *widget, gpointer data)
{
	widgets *a = (widgets *) data;
	gchar *buffer;
	gint rv = 0;

	buffer = (gchar*) gtk_entry_get_text (GTK_ENTRY (a->entry[3]));
	rv = getDouble(buffer, &a->acceltriggerZ);

	if (a->acceltriggerZ < -2.0 && rv == 0)
	{
		g_sprintf (a->bufferStatusBar, "minimum -2.0 g set");
		gtk_statusbar_push (GTK_STATUSBAR (a->statusBar), a->id, a->bufferStatusBar);
		a->acceltriggerZ = -2.0;
	}
	else if (a->acceltriggerZ > 2.0 && rv == 0)
	{
		g_sprintf (a->bufferStatusBar, "maximum +2,0 g set");
		gtk_statusbar_push (GTK_STATUSBAR (a->statusBar), a->id, a->bufferStatusBar);
		a->acceltriggerZ = 2.0;		
	}
	else if (a->acceltriggerZ >= -2.0 && a->acceltriggerZ <= 2.0 && rv == 0)
	{
		g_sprintf (a->bufferStatusBar, "you have chosen %.2f g trigger for Z", a->acceltriggerZ);
		gtk_statusbar_push (GTK_STATUSBAR (a->statusBar), a->id, a->bufferStatusBar);
	}
	else if (rv == 1)
	{
		g_sprintf (a->bufferStatusBar, "you did not enter a correct number");
		gtk_statusbar_push (GTK_STATUSBAR (a->statusBar), a->id, a->bufferStatusBar);
	}
}

void readRadioUSB(GtkWidget *button, gpointer *data)
{
	widgets *a = (widgets *) data;
	gboolean r[5];
	gint i = 0;

	for (i = 0; i < 5; i++) 
	{
		r[i] = FALSE;
	}

	for (i = 0; i < 5; i++) 
	{
		r[i] = gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (a->radioUSB[i]));
	}

	g_sprintf (a->bufferStatusBar, "you have chosen /dev/ttyUSB0, ID %d - please now press connect", a->radioButtonUSBstate);
	gtk_statusbar_push (GTK_STATUSBAR (a->statusBar), a->id, a->bufferStatusBar);

	if (r[0] == TRUE) 
	{
		a->radioButtonUSBstate = 16;
		g_sprintf (a->bufferStatusBar, "you have chosen /dev/ttyUSB0, ID %d - please now press connect", a->radioButtonUSBstate);
		gtk_statusbar_push (GTK_STATUSBAR (a->statusBar), a->id, a->bufferStatusBar);
	}
	else if (r[1] == TRUE) 
	{
		a->radioButtonUSBstate = 17;
		g_sprintf (a->bufferStatusBar, "you have chosen /dev/ttyUSB1, ID %d - please now press connect", a->radioButtonUSBstate);
		gtk_statusbar_push (GTK_STATUSBAR (a->statusBar), a->id, a->bufferStatusBar);
	}
	else if (r[2] == TRUE) 
	{
		a->radioButtonUSBstate = 18;
		g_sprintf (a->bufferStatusBar, "you have chosen /dev/ttyUSB2, ID %d - please now press connect", a->radioButtonUSBstate);
		gtk_statusbar_push (GTK_STATUSBAR (a->statusBar), a->id, a->bufferStatusBar);
	}
	else if (r[3] == TRUE) 
	{
		a->radioButtonUSBstate = 19;
		g_sprintf (a->bufferStatusBar, "you have chosen /dev/ttyUSB3, ID %d - please now press connect", a->radioButtonUSBstate);
		gtk_statusbar_push (GTK_STATUSBAR (a->statusBar), a->id, a->bufferStatusBar);
	}
	else if (r[4] == TRUE) 
	{
		a->radioButtonUSBstate = 20;
		g_sprintf (a->bufferStatusBar, "you have chosen /dev/ttyUSB4, ID %d - please now press connect", a->radioButtonUSBstate);
		gtk_statusbar_push (GTK_STATUSBAR (a->statusBar), a->id, a->bufferStatusBar);
	}
}

guint waitSendTerminal(gpointer data)
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

guint waitSendnoTerminal(gpointer data)
{
	widgets *a = (widgets *) data;

	requestData((gpointer) a);
	rawProtocolDataTimed((gpointer) a);

	return a->sendSerial;
}

guint waitSendPython(gpointer data)
{
	widgets *a = (widgets *) data;

	requestData((gpointer) a);

	return a->sendSerial;
}

guint safeWait(gpointer data)
{
	widgets *a = (widgets *) data;

	a->sendSerial = TRUE;
	g_timeout_add (a->pollTimeSensor, (GSourceFunc) waitSendnoTerminal, (gpointer) a);

	return a->safeWaitStep;
}

void connectSerial(GtkButton *button, gpointer data)
{
	widgets *a = (widgets *) data;
    char mode[]= {'8','N','1', 0};
	const char openComPortError[] = "ERROR opening COM port";
	const char openComPortSuccess[] = "SUCCESS opening COM port";
	unsigned char requestConnection[] = "#CON,";
	gint i = 0;

    if(RS232_OpenComport(a->radioButtonUSBstate, BAUD, mode))
    {
		snprintf(a->bufferStatusBar, sizeof(openComPortError)+1, "%s", openComPortError);
		gtk_statusbar_push (GTK_STATUSBAR (a->statusBar), a->id, a->bufferStatusBar);
    }
	else
	{
		snprintf(a->bufferStatusBar, sizeof(openComPortSuccess)+1, "%s", openComPortSuccess);
		gtk_statusbar_push (GTK_STATUSBAR (a->statusBar), a->id, a->bufferStatusBar);
		gtk_widget_set_sensitive (GTK_WIDGET (a->button[0]), FALSE);

		for (i = 1; i < 7; i++) 
		{
			gtk_widget_set_sensitive (GTK_WIDGET (a->button[i]), TRUE);
		}

		for (i = 0; i < 5; i++) 
		{
			gtk_widget_set_sensitive (GTK_WIDGET (a->radioUSB[i]), FALSE);
		}

		gtk_widget_set_sensitive (GTK_WIDGET (a->entry[0]), FALSE);

		RS232_flushTX(a->radioButtonUSBstate);
		RS232_SendBuf(a->radioButtonUSBstate, requestConnection, (int)sizeof(requestConnection));
		RS232_SendByte(a->radioButtonUSBstate, '\r');
		RS232_SendByte(a->radioButtonUSBstate, '\r');
	}
}

void requestData(gpointer data)
{
	widgets *a = (widgets *) data;
	unsigned char requestText[] = "#REQ,";

	RS232_flushTX(a->radioButtonUSBstate);	
	RS232_SendBuf(a->radioButtonUSBstate, requestText, (int)sizeof(requestText));
	RS232_SendByte(a->radioButtonUSBstate, '\r');
	RS232_SendByte(a->radioButtonUSBstate, '\r');
}

void servoConnector (GtkButton *button, gpointer data)
{
	widgets *a = (widgets *) data;
	unsigned char requestServo[] = "#SER,";

	gtk_widget_set_sensitive (GTK_WIDGET (a->button[2]), FALSE);
	gtk_widget_set_sensitive (GTK_WIDGET (a->button[3]), FALSE);

	a->sendSerial = FALSE;

	RS232_flushTX(a->radioButtonUSBstate);
	RS232_SendBuf(a->radioButtonUSBstate, requestServo, (int)sizeof(requestServo));
	RS232_SendByte(a->radioButtonUSBstate, '\r');
	RS232_SendByte(a->radioButtonUSBstate, '\r');

	a->safeWaitStep = FALSE;
	g_timeout_add (250, (GSourceFunc) safeWait, (gpointer) a);
}

void disconnectSerial(GtkButton *button, gpointer data)
{
	widgets *a = (widgets *) data;
	const char closeComPortSuccess[] = "SUCCESS closing COM port";
	unsigned char requestStop[] = "#END,";
	gint i = 0;

	gtk_widget_set_sensitive (GTK_WIDGET (a->button[0]), TRUE);
	for (i = 1; i < 7; i++) 
	{
		gtk_widget_set_sensitive (GTK_WIDGET (a->button[i]), FALSE);
	}

	gtk_widget_set_sensitive (GTK_WIDGET (a->entry[0]), TRUE);

	for (i = 0; i < 5; i++) 
	{
		gtk_widget_set_sensitive (GTK_WIDGET (a->radioUSB[i]), TRUE);
	}
	gtk_entry_set_text(GTK_ENTRY (a->entry[0]), "");
	gtk_entry_set_placeholder_text(GTK_ENTRY (a->entry[0]), "enter poll time in ms");

	a->sendSerial = FALSE;

	RS232_flushTX(a->radioButtonUSBstate);
	RS232_SendBuf(a->radioButtonUSBstate, requestStop, (int)sizeof(requestStop));
	RS232_SendByte(a->radioButtonUSBstate, '\r');
	RS232_SendByte(a->radioButtonUSBstate, '\r');

    RS232_CloseComport(a->radioButtonUSBstate);
	snprintf(a->bufferStatusBar, sizeof(closeComPortSuccess)+1, "%s", closeComPortSuccess);
	gtk_statusbar_push (GTK_STATUSBAR (a->statusBar), a->id, a->bufferStatusBar);
}

void dataTransmission(GtkButton *button, gpointer data)
{
	widgets *a = (widgets *) data;
	gint i = 0;

	for (i = 2; i < 6; i++) 
	{
		gtk_widget_set_sensitive (GTK_WIDGET (a->button[i]), FALSE);
	}
	a->sendSerial = TRUE;
	g_timeout_add (a->pollTimeSensor, (GSourceFunc) waitSendnoTerminal, (gpointer) a);
}

void pythonConnector(GtkButton *button, gpointer data)
{
	widgets *a = (widgets *) data;
	char pythonCall[100];

	g_sprintf(pythonCall, "python3 ../python/protocol_plotter.py %d &", a->radioButtonUSBstate);

	system(pythonCall);

	gtk_widget_set_sensitive (GTK_WIDGET (a->button[2]), FALSE);
	gtk_widget_set_sensitive (GTK_WIDGET (a->button[3]), FALSE);
	gtk_widget_set_sensitive (GTK_WIDGET (a->button[5]), FALSE);

	a->sendSerial = TRUE;
	g_timeout_add (a->pollTimeSensor, (GSourceFunc) waitSendPython, (gpointer) a);
}

void pythonSpriteConnector(GtkButton *button, gpointer data)
{
	widgets *a = (widgets *) data;
	char pythonCall[100];

	g_sprintf(pythonCall, "python3 ../python/direction.py %d &", a->radioButtonUSBstate);

	system(pythonCall);

	gtk_widget_set_sensitive (GTK_WIDGET (a->button[2]), FALSE);
	gtk_widget_set_sensitive (GTK_WIDGET (a->button[3]), FALSE);
	gtk_widget_set_sensitive (GTK_WIDGET (a->button[4]), FALSE);

	a->sendSerial = TRUE;
	g_timeout_add (a->pollTimeSensor, (GSourceFunc) waitSendPython, (gpointer) a);
}

void rawProtocolData(GtkButton *button, gpointer data)
{
	widgets *a = (widgets *) data;
	gint i = 0;

	gtk_widget_set_sensitive (GTK_WIDGET (a->button[3]), FALSE);

	for (i = 2; i < 6; i++) 
	{
		gtk_widget_set_sensitive (GTK_WIDGET (a->button[i]), FALSE);
	}

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

	g_timeout_add (a->pollTimeSensor, (GSourceFunc) waitSendTerminal, (gpointer) a);
}

void rawProtocolDataTimed(gpointer data)
{
	widgets *a = (widgets *) data;
	unsigned char buf[OSBUFFER];
	int n = 0, i = 0;
	gchar accelerationX[7], accelerationY[7], accelerationZ[7], temperature[3], packages[10], error[3];
	gint accelerationXint, accelerationYint, accelerationZint, temperatureint, packagesInt, errorInt;

	memset (&buf, 0, sizeof (buf));
	n = RS232_PollComport(a->radioButtonUSBstate, buf, (OSBUFFER-1));
	RS232_flushRX(a->radioButtonUSBstate);

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
	
	if (strncmp(a->position6D, "STA", 3) == 0)
	{
		if (strncpy(packages, a->line+5, 10) != packages)
		{
			g_print("strncpy error\n");
		}
		packages[10] = '\0';
		getInteger(packages, &packagesInt);
		g_sprintf(a->packagesOut, "data %d", packagesInt);

		
		if (strncpy(error, a->line+16, 3) != error)
		{
			g_print("strncpy error\n");
		}
		error[3] = '\0';
		getInteger(error, &errorInt);
		g_sprintf(a->errorOut, "error %d", errorInt);

		gtk_label_set_label((GtkLabel*)a->label[13], a->packagesOut);
		gtk_label_set_label((GtkLabel*)a->label[14], a->errorOut);
	}
	else
	{
		gtk_label_set_label((GtkLabel*)a->label[0], a->position6D);

		if (strncpy(accelerationX, a->line+5, 7) != accelerationX)
		{
			g_print("strncpy2 error\n");
		}
		accelerationX[7] = '\0';
		getInteger(accelerationX, &accelerationXint);
		a->accelerationXdouble = accelerationXint / GDIVIDER;
		sprintf(a->accelerationXout, "accelX %7.3f g", a->accelerationXdouble);
		gtk_label_set_label((GtkLabel*)a->label[1], a->accelerationXout);

		if (strncpy(accelerationY, a->line+13, 7) != accelerationY)
		{
			g_print("strncpy3 error\n");
		}
		accelerationY[7] = '\0';
		getInteger(accelerationY, &accelerationYint);
		a->accelerationYdouble = accelerationYint / GDIVIDER;
		sprintf(a->accelerationYout, "accelY %7.3f g", a->accelerationYdouble);
		gtk_label_set_label((GtkLabel*)a->label[2], a->accelerationYout);

		if (strncpy(accelerationZ, a->line+21, 7) != accelerationZ)
		{
			g_print("strncpy4 error\n");
		}
		accelerationZ[7] = '\0';
		getInteger(accelerationZ, &accelerationZint);
		a->accelerationZdouble = accelerationZint / GDIVIDER;
		sprintf(a->accelerationZout, "accelZ %7.3f g", a->accelerationZdouble);
		gtk_label_set_label((GtkLabel*)a->label[3], a->accelerationZout);

		if (strncpy(temperature, a->line+29, 2) != temperature)
		{
			g_print("strncpy5 error\n");
		}
		temperature[2] = '\0';
		getInteger(temperature, &temperatureint);
		a->temperaturedouble = temperatureint / 1.0;
		sprintf(a->tempOut, "%3.2f °C", a->temperaturedouble);
		gtk_label_set_label((GtkLabel*)a->label[4], a->tempOut);

		a->tiltX = asin(a->accelerationXdouble/G) * 180 / PI;
		a->tiltY = asin(a->accelerationYdouble/G) * 180 / PI;
		a->tiltZ = asin(a->accelerationZdouble/G) * 180 / PI;
		a->pitch = atan(a->accelerationXdouble/(sqrt((a->accelerationYdouble*a->accelerationYdouble)+(a->accelerationZdouble*a->accelerationZdouble)))) * 180 / PI;
		a->roll = atan(a->accelerationYdouble/(sqrt((a->accelerationXdouble*a->accelerationXdouble)+(a->accelerationZdouble*a->accelerationZdouble)))) * 180 / PI;

		sprintf(a->tiltXout, "tiltX %7.2f °", a->tiltX);
		sprintf(a->tiltYout, "tiltY %7.2f °", a->tiltY);
		sprintf(a->tiltZout, "tiltZ %7.2f °", a->tiltZ);
		sprintf(a->pitchOut, "pitch %7.2f °", a->pitch);
		sprintf(a->rollOut, "roll  %7.2f °", a->roll);

		gtk_label_set_label((GtkLabel*)a->label[5], a->tiltXout);
		gtk_label_set_label((GtkLabel*)a->label[6], a->tiltYout);
		gtk_label_set_label((GtkLabel*)a->label[7], a->tiltZout);
		gtk_label_set_label((GtkLabel*)a->label[8], a->pitchOut);
		gtk_label_set_label((GtkLabel*)a->label[9], a->rollOut);

		if (strncmp(a->position6D, "TOP", 3) == 0)
		{
			gtk_container_remove(GTK_CONTAINER(a->grid), a->box[0]);
			a->image[1] = gtk_image_new_from_file("./pictures/TOP.png");
			a->box[0] = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
			gtk_grid_attach(GTK_GRID (a->grid), a->box[0], 3, 0, 2, 5);
			gtk_box_pack_start(GTK_BOX(a->box[0]), a->image[1], FALSE, FALSE, 0);
			gtk_widget_set_halign(GTK_WIDGET(a->box[0]), GTK_ALIGN_CENTER);
			gtk_widget_set_valign(GTK_WIDGET(a->box[0]), GTK_ALIGN_CENTER);
			gtk_widget_show_all(a->grid);
			a->position6Dint = 1;
		}
		else if (strncmp(a->position6D, "BOT",3) == 0)
		{
			gtk_container_remove(GTK_CONTAINER(a->grid), a->box[0]);
			a->image[1] = gtk_image_new_from_file("./pictures/BOT.png");
			a->box[0] = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
			gtk_grid_attach(GTK_GRID (a->grid), a->box[0], 3, 0, 2, 5);
			gtk_box_pack_start(GTK_BOX(a->box[0]), a->image[1], FALSE, FALSE, 0);
			gtk_widget_set_halign(GTK_WIDGET(a->box[0]), GTK_ALIGN_CENTER);
			gtk_widget_set_valign(GTK_WIDGET(a->box[0]), GTK_ALIGN_CENTER);
			gtk_widget_show_all(a->grid);
			a->position6Dint = 2;
		}
		else if (strncmp(a->position6D, "DDX",3) == 0)
		{
			gtk_container_remove(GTK_CONTAINER(a->grid), a->box[0]);
			a->image[1] = gtk_image_new_from_file("./pictures/DDX.png");
			a->box[0] = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
			gtk_grid_attach(GTK_GRID (a->grid), a->box[0], 3, 0, 2, 5);
			gtk_box_pack_start(GTK_BOX(a->box[0]), a->image[1], FALSE, FALSE, 0);
			gtk_widget_set_halign(GTK_WIDGET(a->box[0]), GTK_ALIGN_CENTER);
			gtk_widget_set_valign(GTK_WIDGET(a->box[0]), GTK_ALIGN_CENTER);
			gtk_widget_show_all(a->grid);
			a->position6Dint = 3;	
		}
		else if (strncmp(a->position6D, "DSX", 3) == 0)
		{
			gtk_container_remove(GTK_CONTAINER(a->grid), a->box[0]);
			a->image[1] = gtk_image_new_from_file("./pictures/DSX.png");
			a->box[0] = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
			gtk_grid_attach(GTK_GRID (a->grid), a->box[0], 3, 0, 2, 5);
			gtk_box_pack_start(GTK_BOX(a->box[0]), a->image[1], FALSE, FALSE, 0);
			gtk_widget_set_halign(GTK_WIDGET(a->box[0]), GTK_ALIGN_CENTER);
			gtk_widget_set_valign(GTK_WIDGET(a->box[0]), GTK_ALIGN_CENTER);
			gtk_widget_show_all(a->grid);
			a->position6Dint = 4;	
		}
		else if (strncmp(a->position6D, "UDX", 3) == 0)
		{
			gtk_container_remove(GTK_CONTAINER(a->grid), a->box[0]);
			a->image[1] = gtk_image_new_from_file("./pictures/UDX.png");
			a->box[0] = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
			gtk_grid_attach(GTK_GRID (a->grid), a->box[0], 3, 0, 2, 5);
			gtk_box_pack_start(GTK_BOX(a->box[0]), a->image[1], FALSE, FALSE, 0);
			gtk_widget_set_halign(GTK_WIDGET(a->box[0]), GTK_ALIGN_CENTER);
			gtk_widget_set_valign(GTK_WIDGET(a->box[0]), GTK_ALIGN_CENTER);
			gtk_widget_show_all(a->grid);
			a->position6Dint = 5;	
		}
		else if (strncmp(a->position6D, "USX", 3) == 0)
		{
			gtk_container_remove(GTK_CONTAINER(a->grid), a->box[0]);
			a->image[1] = gtk_image_new_from_file("./pictures/USX.png");
			a->box[0] = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
			gtk_grid_attach(GTK_GRID (a->grid), a->box[0], 3, 0, 2, 5);
			gtk_box_pack_start(GTK_BOX(a->box[0]), a->image[1], FALSE, FALSE, 0);
			gtk_widget_set_halign(GTK_WIDGET(a->box[0]), GTK_ALIGN_CENTER);
			gtk_widget_set_valign(GTK_WIDGET(a->box[0]), GTK_ALIGN_CENTER);
			gtk_widget_show_all(a->grid);
			a->position6Dint = 6;	
		}
		else
		{
			gtk_container_remove(GTK_CONTAINER(a->grid), a->box[0]);
			a->image[1] = gtk_image_new_from_file("./pictures/ALL.png");
			a->box[0] = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
			gtk_grid_attach(GTK_GRID (a->grid), a->box[0], 3, 0, 2, 5);
			gtk_box_pack_start(GTK_BOX(a->box[0]), a->image[1], FALSE, FALSE, 0);
			gtk_widget_set_halign(GTK_WIDGET(a->box[0]), GTK_ALIGN_CENTER);
			gtk_widget_set_valign(GTK_WIDGET(a->box[0]), GTK_ALIGN_CENTER);
			gtk_widget_show_all(a->grid);
			a->position6Dint = 0;
		}

		if (a->accelerationXdouble > a->acceltriggerX || a->accelerationXdouble < -a->acceltriggerX)
		{
			gtk_label_set_label((GtkLabel*)a->label[10], "<span foreground='white' background='red' weight='ultrabold' font='20'> X  ALARM  </span>");
		}
		else
		{
			gtk_label_set_label((GtkLabel*)a->label[10], "<span foreground='white' background='green' weight='ultrabold' font='20'> X TRIGGER </span>");
		}

		if (a->accelerationYdouble > a->acceltriggerY || a->accelerationYdouble < -a->acceltriggerY)
		{
			gtk_label_set_label((GtkLabel*)a->label[11], "<span foreground='white' background='red' weight='ultrabold' font='20'> Y  ALARM  </span>");
		}
		else
		{
			gtk_label_set_label((GtkLabel*)a->label[11], "<span foreground='white' background='green' weight='ultrabold' font='20'> Y TRIGGER </span>");
		}

		if (a->accelerationZdouble > a->acceltriggerZ || a->accelerationZdouble < -a->acceltriggerZ)
		{
			gtk_label_set_label((GtkLabel*)a->label[12], "<span foreground='white' background='red' weight='ultrabold' font='20'> Z  ALARM  </span>");
		}
		else
		{
			gtk_label_set_label((GtkLabel*)a->label[12], "<span foreground='white' background='green' weight='ultrabold' font='20'> Z TRIGGER </span>");
		}
	}
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

unsigned int getDouble(char *input, double *numDouble)
{
    long double number = 0;
    char *pointToEnd = NULL;

    number = strtod(input, &pointToEnd);
    if(*pointToEnd != '\0')
    {
        return 1;
    }
    else
    {
        *numDouble = (double)number;
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
