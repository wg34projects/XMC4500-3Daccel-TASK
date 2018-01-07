/**
 * @file		menucallbacks.c
 * @version		v1.0
 * @date		Jan 2018
 * @author		Egermann, Resch
 *
 * @brief		menucallbacks 3Dacceltask GUI
 *
 */

#include "menucallbacks.h"

// entry callbacks

/**
 * @brief	prepare filename for logging
 *
 */
void fileName (GtkWidget *widget, gpointer data)
{
	widgets *a = (widgets *) data;
	gchar *buffer;
	gchar timeZone[100];
	TM *timeStamp, timeTemp;
	time_t timeEpoch;

	// prepare timestamp

	timeEpoch = time(NULL);
	timeStamp = localtime_r(&timeEpoch, &timeTemp);

	// prepare save and log string

	if (strftime(timeZone, sizeof(timeZone), "%Y.%B.%d_%T", timeStamp) == 0)
	{
		g_print ("strftime returned 0");
		return;
	}

	buffer = (gchar*) gtk_entry_get_text (GTK_ENTRY (a->entry[4]));
	g_sprintf(a->fileName, "%s_%s.log", timeZone, buffer);
	g_print("%s\n", a->fileName);
	g_sprintf (a->bufferStatusBar, "filename in local folder %s", a->fileName);
	gtk_statusbar_push (GTK_STATUSBAR (a->statusBar), a->id, a->bufferStatusBar);

	if (a->transmission == TRUE)
	{
		gtk_widget_set_sensitive (GTK_WIDGET (a->button[7]), TRUE);
		gtk_widget_set_sensitive (GTK_WIDGET (a->entry[4]), FALSE);
	}
	else
	{
		gtk_widget_set_sensitive (GTK_WIDGET (a->button[7]), FALSE);
		gtk_widget_set_sensitive (GTK_WIDGET (a->entry[4]), TRUE);
	}
}

/**
 * @brief	get poll time from entry
 *
 */
void entryPollTime (GtkWidget *widget, gpointer data)
{
	widgets *a = (widgets *) data;
	gchar *buffer;
	gint rv = 0;

	buffer = (gchar*) gtk_entry_get_text (GTK_ENTRY (a->entry[0]));
	rv = getInteger(buffer, &a->pollTimeSensor);

	if (rv == 1)
	{
		g_sprintf (a->bufferStatusBar, "you did not enter a correct number");
		gtk_statusbar_push (GTK_STATUSBAR (a->statusBar), a->id, a->bufferStatusBar);
		return;
	}

	if (a->pollTimeSensor < POLLMIN)
	{
		g_sprintf (a->bufferStatusBar, "you have chosen %d ms poll time, lower limit is 10 ms, this is now set", a->pollTimeSensor);
		gtk_statusbar_push (GTK_STATUSBAR (a->statusBar), a->id, a->bufferStatusBar);
		a->pollTimeSensor = POLLMIN;
	}
	else if (a->pollTimeSensor > POLLMAX)
	{
		g_sprintf (a->bufferStatusBar, "you have chosen %d ms poll time, upper limit is 1000 ms, this is now set", a->pollTimeSensor);
		gtk_statusbar_push (GTK_STATUSBAR (a->statusBar), a->id, a->bufferStatusBar);
		a->pollTimeSensor = POLLMAX;		
	}
	else
	{
		g_sprintf (a->bufferStatusBar, "you have chosen %d ms poll time", a->pollTimeSensor);
		gtk_statusbar_push (GTK_STATUSBAR (a->statusBar), a->id, a->bufferStatusBar);
	}
}

/**
 * @brief	get X trigger from entry
 *
 */
void entryXtrigger (GtkWidget *widget, gpointer data)
{
	widgets *a = (widgets *) data;
	gchar *buffer;
	gint rv = 0;

	buffer = (gchar*) gtk_entry_get_text (GTK_ENTRY (a->entry[1]));
	rv = getDouble(buffer, &a->acceltriggerX);

	if (rv == 1)
	{
		g_sprintf (a->bufferStatusBar, "you did not enter a correct number");
		gtk_statusbar_push (GTK_STATUSBAR (a->statusBar), a->id, a->bufferStatusBar);
		return;
	}

	if (a->acceltriggerX < GMIN)
	{
		g_sprintf (a->bufferStatusBar, "minimum %.2fg set", GMIN);
		gtk_statusbar_push (GTK_STATUSBAR (a->statusBar), a->id, a->bufferStatusBar);
		a->acceltriggerX = GMIN;
	}
	else if (a->acceltriggerX > GMAX)
	{
		g_sprintf (a->bufferStatusBar, "maximum %.2fg set", GMAX);
		gtk_statusbar_push (GTK_STATUSBAR (a->statusBar), a->id, a->bufferStatusBar);
		a->acceltriggerX = GMAX;		
	}
	else
	{
		g_sprintf (a->bufferStatusBar, "you have chosen %.2f g trigger for X", a->acceltriggerX);
		gtk_statusbar_push (GTK_STATUSBAR (a->statusBar), a->id, a->bufferStatusBar);
	}
}

/**
 * @brief	get Y trigger from entry
 *
 */
void entryYtrigger (GtkWidget *widget, gpointer data)
{
	widgets *a = (widgets *) data;
	gchar *buffer;
	gint rv = 0;

	buffer = (gchar*) gtk_entry_get_text (GTK_ENTRY (a->entry[2]));
	rv = getDouble(buffer, &a->acceltriggerY);

	if (rv == 1)
	{
		g_sprintf (a->bufferStatusBar, "you did not enter a correct number");
		gtk_statusbar_push (GTK_STATUSBAR (a->statusBar), a->id, a->bufferStatusBar);
		return;
	}

	if (a->acceltriggerY < GMIN)
	{
		g_sprintf (a->bufferStatusBar, "minimum %.2fg set", GMIN);
		gtk_statusbar_push (GTK_STATUSBAR (a->statusBar), a->id, a->bufferStatusBar);
		a->acceltriggerY = GMIN;
	}
	else if (a->acceltriggerY > GMAX)
	{
		g_sprintf (a->bufferStatusBar, "maximum %.2fg set", GMAX);
		gtk_statusbar_push (GTK_STATUSBAR (a->statusBar), a->id, a->bufferStatusBar);
		a->acceltriggerY = GMAX;		
	}
	else
	{
		g_sprintf (a->bufferStatusBar, "you have chosen %.2f g trigger for X", a->acceltriggerY);
		gtk_statusbar_push (GTK_STATUSBAR (a->statusBar), a->id, a->bufferStatusBar);
	}
}

/**
 * @brief	get Z trigger from entry
 *
 */
void entryZtrigger (GtkWidget *widget, gpointer data)
{
	widgets *a = (widgets *) data;
	gchar *buffer;
	gint rv = 0;

	buffer = (gchar*) gtk_entry_get_text (GTK_ENTRY (a->entry[3]));
	rv = getDouble(buffer, &a->acceltriggerZ);

	if (rv == 1)
	{
		g_sprintf (a->bufferStatusBar, "you did not enter a correct number");
		gtk_statusbar_push (GTK_STATUSBAR (a->statusBar), a->id, a->bufferStatusBar);
		return;
	}

	if (a->acceltriggerZ < GMIN)
	{
		g_sprintf (a->bufferStatusBar, "minimum %.2fg set", GMIN);
		gtk_statusbar_push (GTK_STATUSBAR (a->statusBar), a->id, a->bufferStatusBar);
		a->acceltriggerX = GMIN;
	}
	else if (a->acceltriggerZ > GMAX)
	{
		g_sprintf (a->bufferStatusBar, "maximum %.2fg set", GMAX);
		gtk_statusbar_push (GTK_STATUSBAR (a->statusBar), a->id, a->bufferStatusBar);
		a->acceltriggerZ = GMAX;		
	}
	else
	{
		g_sprintf (a->bufferStatusBar, "you have chosen %.2f g trigger for X", a->acceltriggerZ);
		gtk_statusbar_push (GTK_STATUSBAR (a->statusBar), a->id, a->bufferStatusBar);
	}
}

// radiobuttons callbacks

/**
 * @brief	read radio buttons for UART connection
 *
 */
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
	else
	{
		a->radioButtonUSBstate = 20;
		g_sprintf (a->bufferStatusBar, "you have chosen /dev/ttyUSB4, ID %d - please now press connect", a->radioButtonUSBstate);
		gtk_statusbar_push (GTK_STATUSBAR (a->statusBar), a->id, a->bufferStatusBar);
	}
}

// timer functions

/**
 * @brief	timer to highlight pressed button
 *
 */
guint buttonFeedback(gpointer data)
{
	widgets *a = (widgets *) data;

    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(a->button[8]), FALSE);
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(a->button[9]), FALSE);

	return a->buttonXMC;
}

/**
 * @brief	timer to highlight freefall label
 *
 */
guint freeFallLabel(gpointer data)
{
	widgets *a = (widgets *) data;

	gtk_label_set_label((GtkLabel*)a->label[15], "<span foreground='white' weight='ultrabold' font='20'> SAFE </span>");

	return a->freeFallLabel;
}

/**
 * @brief	timer for output and request terminal function
 *
 */
guint waitSendTerminal(gpointer data)
{
	widgets *a = (widgets *) data;
	char lineWithLF[OSBUFFER+1];

	g_sprintf(lineWithLF, "%s\n", a->line);

	requestData((gpointer) a);
	rawProtocolDataTimed((gpointer) a);

	gtk_text_buffer_get_start_iter (a->buffer, &a->iter);
  	gtk_text_buffer_insert (a->buffer, &a->iter, lineWithLF, -1);
	gtk_text_buffer_get_bounds (a->buffer, &a->start, &a->end);
	gtk_text_buffer_apply_tag_by_name (a->buffer, "word_wrap", &a->start, &a->end);
	gtk_text_buffer_apply_tag_by_name (a->buffer, "not_editable", &a->start, &a->end);

	return a->sendSerial;
}

/**
 * @brief	timer for output and request function
 *
 */
guint waitSendnoTerminal(gpointer data)
{
	widgets *a = (widgets *) data;

	requestData((gpointer) a);
	rawProtocolDataTimed((gpointer) a);

	return a->sendSerial;
}

/**
 * @brief	timer for output and request function Python
 *
 */
guint waitSendPython(gpointer data)
{
	widgets *a = (widgets *) data;

	requestData((gpointer) a);

	return a->sendSerial;
}

/**
 * @brief	timer for safe UART stop
 *
 */
guint safeStop(gpointer data)
{
	widgets *a = (widgets *) data;
	unsigned char requestServoOff[] = "#SER,f";
	a->servoState = 0;	

	RS232_flushTX(a->radioButtonUSBstate);	
	RS232_SendBuf(a->radioButtonUSBstate, requestServoOff, (int)sizeof(requestServoOff));
	RS232_SendByte(a->radioButtonUSBstate, '\r');

    a->safeEnd = FALSE;
    g_timeout_add (UARTWAIT, (GSourceFunc) safeEnd, (gpointer) a);

	return a->safeWaitStop;
}

/**
 * @brief	timer for safe UART end
 *
 */
guint safeEnd(gpointer data)
{
	widgets *a = (widgets *) data;
	unsigned char requestStop[] = "#END,";
	a->servoState = 0;	

	RS232_flushTX(a->radioButtonUSBstate);
	RS232_SendBuf(a->radioButtonUSBstate, requestStop, (int)sizeof(requestStop));
	RS232_SendByte(a->radioButtonUSBstate, '\r');

    a->safeWaitClose = FALSE;
    g_timeout_add (UARTWAIT, (GSourceFunc) safeClose, (gpointer) a);

	return a->safeEnd;
}

/**
 * @brief	timer for safe UART close
 *
 */
guint safeClose(gpointer data)
{
	widgets *a = (widgets *) data;
	const char closeComPortSuccess[] = "SUCCESS closing COM port";
	gint i = 0;

    RS232_CloseComport(a->radioButtonUSBstate);
	snprintf(a->bufferStatusBar, sizeof(closeComPortSuccess)+1, "%s", closeComPortSuccess);
	gtk_statusbar_push (GTK_STATUSBAR (a->statusBar), a->id, a->bufferStatusBar);

	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(a->button[3]), FALSE);
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(a->button[6]), FALSE);
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(a->button[7]), FALSE);
	gtk_label_set_label((GtkLabel*)a->label[4], "LED OFF");

	gtk_widget_set_sensitive (GTK_WIDGET (a->button[0]), TRUE);
	for (i = 1; i < BUTTONS; i++) 
	{
		gtk_widget_set_sensitive (GTK_WIDGET (a->button[i]), FALSE);
	}

	gtk_widget_set_sensitive (GTK_WIDGET (a->entry[0]), TRUE);

	for (i = 0; i < 5; i++) 
	{
		gtk_widget_set_sensitive (GTK_WIDGET (a->radioUSB[i]), TRUE);
	}

	return a->safeWaitClose;
}

// connection callbacks

/**
 * @brief	function connect UART
 *
 */
void connectSerial(GtkButton *button, gpointer data)
{
	widgets *a = (widgets *) data;
    char mode[]= {'8','N','1', 0};
	const char openComPortError[] = "ERROR opening COM port";
	const char openComPortSuccess[] = "SUCCESS opening COM port";
	unsigned char requestConnection[] = "#CON,";
	gint i = 0;

    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(button)))
    {
        g_print("%s toggled on\n", gtk_button_get_label(GTK_BUTTON(button)));
		if(RS232_OpenComport(a->radioButtonUSBstate, BAUD, mode))
		{
			snprintf(a->bufferStatusBar, sizeof(openComPortError)+1, "%s", openComPortError);
			gtk_statusbar_push (GTK_STATUSBAR (a->statusBar), a->id, a->bufferStatusBar);
		}
		else
		{
			snprintf(a->bufferStatusBar, sizeof(openComPortSuccess)+1, "%s", openComPortSuccess);
			gtk_statusbar_push (GTK_STATUSBAR (a->statusBar), a->id, a->bufferStatusBar);
			gtk_label_set_label((GtkLabel*)a->label[4], "<span foreground='white' background='red' weight='ultrabold' font='12'> LED ON  </span>");

			for (i = 1; i < BUTTONS; i++) 
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
		}
    }
    else
    {
        g_print("%s toggled off\n", gtk_button_get_label(GTK_BUTTON(button)));
		a->sendSerial = FALSE;
		a->safeWaitStop = FALSE;
		g_timeout_add (UARTWAIT, (GSourceFunc) safeStop, (gpointer) a);
	}
}

/**
 * @brief	function request data from XMC UART
 *
 */
void requestData(gpointer data)
{
	widgets *a = (widgets *) data;
	unsigned char requestText[] = "#REQ,";

	RS232_flushTX(a->radioButtonUSBstate);	
	RS232_SendBuf(a->radioButtonUSBstate, requestText, (int)sizeof(requestText));
	RS232_SendByte(a->radioButtonUSBstate, '\r');
}

/**
 * @brief	function servo connector
 *
 */
void servoConnector (gpointer data)
{
	widgets *a = (widgets *) data;
	unsigned char requestServoOn[] = "#SER,n";
	unsigned char requestServoOff[] = "#SER,f";

	a->sendSerial = FALSE;

	gtk_widget_set_sensitive (GTK_WIDGET (a->button[2]), FALSE);

	RS232_flushTX(a->radioButtonUSBstate);

	if (a->servoState == 0)
	{
		a->servoState = 1;
		RS232_SendBuf(a->radioButtonUSBstate, requestServoOn, (int)sizeof(requestServoOn));
	}
	else if (a->servoState == 1)
	{
		a->servoState = 0;
		RS232_SendBuf(a->radioButtonUSBstate, requestServoOff, (int)sizeof(requestServoOff));
	}

	RS232_SendByte(a->radioButtonUSBstate, '\r');

	if (a->transmission == TRUE)
	{
		a->sendSerial = TRUE;
	}
}

/**
 * @brief	function statistic request from XMC
 *
 */
void statisticConnector (GtkButton *button, gpointer data)
{
	widgets *a = (widgets *) data;
	unsigned char requestStat[] = "#STA,";

	a->sendSerial = FALSE;

	RS232_flushTX(a->radioButtonUSBstate);
	RS232_SendBuf(a->radioButtonUSBstate, requestStat, (int)sizeof(requestStat));
	RS232_SendByte(a->radioButtonUSBstate, '\r');

	if (a->transmission == TRUE)
	{
		a->sendSerial = TRUE;
	}
}

/**
 * @brief	function toggle servo on off
 *
 */
void servo(GtkWidget *button, gpointer data)
{
	widgets *a = (widgets *) data;

    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(button)))
    {
        g_print("%s toggled on\n", gtk_button_get_label(GTK_BUTTON(button)));
		a->servoState = 0;
    }
    else
    {
        g_print("%s toggled off\n", gtk_button_get_label(GTK_BUTTON(button)));
		a->servoState = 1;
    }

	servoConnector((gpointer) a);
}

/**
 * @brief	function for timed data request
 *
 */
void dataTransmission(GtkButton *button, gpointer data)
{
	widgets *a = (widgets *) data;
	gint i = 0;
	
	for (i = 2; i < BUTTONS-2; i++) 
	{
		gtk_widget_set_sensitive (GTK_WIDGET (a->button[i]), FALSE);
	}
	gtk_widget_set_sensitive (GTK_WIDGET (a->button[3]), TRUE);

    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(button)))
    {
        g_print("%s toggled on\n", gtk_button_get_label(GTK_BUTTON(button)));
		a->transmission = TRUE;
		gtk_widget_set_sensitive (GTK_WIDGET (a->button[1]), TRUE);
		gtk_widget_set_sensitive (GTK_WIDGET (a->button[4]), FALSE);
		gtk_widget_set_sensitive (GTK_WIDGET (a->button[5]), FALSE);
		gtk_widget_set_sensitive (GTK_WIDGET (a->entry[4]), TRUE);
		gtk_widget_set_sensitive (GTK_WIDGET (a->button[8]), TRUE);
		gtk_widget_set_sensitive (GTK_WIDGET (a->button[9]), TRUE);
		a->sendSerial = TRUE;
		g_timeout_add (a->pollTimeSensor, (GSourceFunc) waitSendnoTerminal, (gpointer) a);
    }
    else
    {
        g_print("%s toggled off\n", gtk_button_get_label(GTK_BUTTON(button)));
		a->transmission = FALSE;
		a->sendSerial = FALSE;
		gtk_widget_set_sensitive (GTK_WIDGET (a->button[7]), FALSE);
		gtk_widget_set_sensitive (GTK_WIDGET (a->button[1]), FALSE);
		gtk_widget_set_sensitive (GTK_WIDGET (a->button[4]), TRUE);
		gtk_widget_set_sensitive (GTK_WIDGET (a->button[5]), TRUE);
		gtk_widget_set_sensitive (GTK_WIDGET (a->entry[4]), FALSE);
		gtk_widget_set_sensitive (GTK_WIDGET (a->button[8]), FALSE);
		gtk_widget_set_sensitive (GTK_WIDGET (a->button[9]), FALSE);
	}
}

/**
 * @brief	function to start python script plotter
 *
 */
void pythonConnector(GtkButton *button, gpointer data)
{
	widgets *a = (widgets *) data;
	char pythonCall[100];

	g_sprintf(pythonCall, "python3 ../python/protocol_plotter.py %d &", a->radioButtonUSBstate);

	system(pythonCall);

	gtk_widget_set_sensitive (GTK_WIDGET (a->button[2]), FALSE);
	gtk_widget_set_sensitive (GTK_WIDGET (a->button[3]), FALSE);
	gtk_widget_set_sensitive (GTK_WIDGET (a->button[5]), FALSE);
	gtk_widget_set_sensitive (GTK_WIDGET (a->button[6]), FALSE);

	a->sendSerial = TRUE;
	g_timeout_add (a->pollTimeSensor, (GSourceFunc) waitSendPython, (gpointer) a);
}

/**
 * @brief	function to start python sprite
 *
 */
void pythonSpriteConnector(GtkButton *button, gpointer data)
{
	widgets *a = (widgets *) data;
	char pythonCall[100];

	g_sprintf(pythonCall, "python3 ../python/direction.py %d &", a->radioButtonUSBstate);

	system(pythonCall);

	gtk_widget_set_sensitive (GTK_WIDGET (a->button[2]), FALSE);
	gtk_widget_set_sensitive (GTK_WIDGET (a->button[3]), FALSE);
	gtk_widget_set_sensitive (GTK_WIDGET (a->button[4]), FALSE);
	gtk_widget_set_sensitive (GTK_WIDGET (a->button[6]), FALSE);

	a->sendSerial = TRUE;
	g_timeout_add (a->pollTimeSensor, (GSourceFunc) waitSendPython, (gpointer) a);
}

/**
 * @brief	function to show data in terminal window
 *
 */
void rawProtocolData(GtkButton *button, gpointer data)
{
	widgets *a = (widgets *) data;
	gint i = 0;

	a->transmission = TRUE;

	gtk_widget_set_sensitive (GTK_WIDGET (a->button[3]), FALSE);

	for (i = 2; i < 8; i++) 
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

// input callback

/**
 * @brief	function to toggle protocol on off
 *
 */
void saveData(GtkButton *button, gpointer data)
{
	widgets *a = (widgets *) data;

    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(button)))
    {
		a->saveOutgoing = 1;
	}
	else
	{
		a->saveOutgoing = 0;
	}
}

/**
 * @brief	main function to receive timed data from XMC and handle protocol etc.
 *
 */
void rawProtocolDataTimed(gpointer data)
{
	widgets *a = (widgets *) data;
	unsigned char buf[OSBUFFER] = { 0 };
	int n = 0, i = 0;
	FILE *saveFile = NULL;
	gchar accelerationX[8], accelerationY[8], accelerationZ[8], packages[11], error[4];
	gint accelerationXint, accelerationYint, accelerationZint, packagesInt, errorInt;
	TM *timeStamp, timeTemp;
	time_t timeEpoch;
	gchar timeZone[100];

	// prepare timestamp

	timeEpoch = time(NULL);
	timeStamp = localtime_r(&timeEpoch, &timeTemp);

	// prepare save and log string

	if (strftime(timeZone, sizeof(timeZone), "%A %d %B %Y %T", timeStamp) == 0)
	{
		g_print ("strftime returned 0");
		return;
	}

	memset (&buf, 0, sizeof (buf));
	n = RS232_PollComport(a->radioButtonUSBstate, buf, (OSBUFFER-1));
	RS232_flushRX(a->radioButtonUSBstate);
	RS232_flushTX(a->radioButtonUSBstate);

	if (n > 0)
	{
		g_sprintf(a->line, "%s", (char *)buf);
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
		return;
	}
	else if (strncmp(a->position6D, "BUT", 3) == 0)
	{
		if(a->line[5] == '1')
		{
		    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(a->button[8]), TRUE);
			a->buttonXMC = FALSE;
			g_timeout_add (BUTTONWAIT, (GSourceFunc) buttonFeedback, (gpointer) a);
		}
		else if(a->line[5] == '2')
		{
		    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(a->button[9]), TRUE);
			a->buttonXMC = FALSE;
			g_timeout_add (BUTTONWAIT, (GSourceFunc) buttonFeedback, (gpointer) a);
		}				
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
		g_sprintf(a->accelerationXout, "accelX %7.3f g", a->accelerationXdouble);
		gtk_label_set_label((GtkLabel*)a->label[1], a->accelerationXout);

		if (strncpy(accelerationY, a->line+13, 7) != accelerationY)
		{
			g_print("strncpy3 error\n");
		}
		accelerationY[7] = '\0';
		getInteger(accelerationY, &accelerationYint);
		a->accelerationYdouble = accelerationYint / GDIVIDER;
		g_sprintf(a->accelerationYout, "accelY %7.3f g", a->accelerationYdouble);
		gtk_label_set_label((GtkLabel*)a->label[2], a->accelerationYout);

		if (strncpy(accelerationZ, a->line+21, 7) != accelerationZ)
		{
			g_print("strncpy4 error\n");
		}
		accelerationZ[7] = '\0';
		getInteger(accelerationZ, &accelerationZint);
		a->accelerationZdouble = accelerationZint / GDIVIDER;
		g_sprintf(a->accelerationZout, "accelZ %7.3f g", a->accelerationZdouble);
		gtk_label_set_label((GtkLabel*)a->label[3], a->accelerationZout);

		a->tiltX = asin(a->accelerationXdouble/G) * 180 / PI;
		a->tiltY = asin(a->accelerationYdouble/G) * 180 / PI;
		a->tiltZ = asin(a->accelerationZdouble/G) * 180 / PI;
		a->pitch = atan(a->accelerationXdouble/(sqrt((a->accelerationYdouble*a->accelerationYdouble)+(a->accelerationZdouble*a->accelerationZdouble)))) * 180 / PI;
		a->roll = atan(a->accelerationYdouble/(sqrt((a->accelerationXdouble*a->accelerationXdouble)+(a->accelerationZdouble*a->accelerationZdouble)))) * 180 / PI;

		if (a->saveOutgoing == 1)
		{
			saveFile = fopen(a->fileName, "a");
			if (fprintf(saveFile, "%lu|%s|%s|%f|%f|%f|%f|%f|%f|%f|%f\n", timeEpoch, timeZone, a->position6D, a->accelerationXdouble, a->accelerationYdouble, a->accelerationZdouble, a->tiltX, a->tiltY, a->tiltZ, a->pitch, a->roll) < 1)
			{
				g_print ("problems writing save file\n");
				fclose(saveFile);
				return;
			}
			fclose(saveFile);
		}

		g_sprintf(a->tiltXout, "tiltX %7.2f °", a->tiltX);
		g_sprintf(a->tiltYout, "tiltY %7.2f °", a->tiltY);
		g_sprintf(a->tiltZout, "tiltZ %7.2f °", a->tiltZ);
		g_sprintf(a->pitchOut, "pitch %7.2f °", a->pitch);
		g_sprintf(a->rollOut, "roll  %7.2f °", a->roll);

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
		else if (strncmp(a->position6D, "BOT", 3) == 0)
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
		else if (strncmp(a->position6D, "DDX", 3) == 0)
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

		if (fabs(a->accelerationXdouble) > a->acceltriggerX)
		{
			gtk_label_set_label((GtkLabel*)a->label[10], "<span foreground='white' background='red' weight='ultrabold' font='20'> X  ALARM  </span>");
		}
		else
		{
			gtk_label_set_label((GtkLabel*)a->label[10], "<span foreground='white' background='green' weight='ultrabold' font='20'> X TRIGGER </span>");
		}

		if (fabs(a->accelerationYdouble) > a->acceltriggerY)
		{
			gtk_label_set_label((GtkLabel*)a->label[11], "<span foreground='white' background='red' weight='ultrabold' font='20'> Y  ALARM  </span>");
		}
		else
		{
			gtk_label_set_label((GtkLabel*)a->label[11], "<span foreground='white' background='green' weight='ultrabold' font='20'> Y TRIGGER </span>");
		}

		if (fabs(a->accelerationZdouble) > a->acceltriggerZ)
		{
			gtk_label_set_label((GtkLabel*)a->label[12], "<span foreground='white' background='red' weight='ultrabold' font='20'> Z  ALARM  </span>");
		}
		else
		{
			gtk_label_set_label((GtkLabel*)a->label[12], "<span foreground='white' background='green' weight='ultrabold' font='20'> Z TRIGGER </span>");
		}

		if (((fabs(a->accelerationXdouble) < FREELO) && (fabs(a->accelerationYdouble) < FREELO) && (fabs(a->accelerationZdouble) > FREEHI)) || ((fabs(a->accelerationXdouble) < FREELO) && (fabs(a->accelerationYdouble) > FREEHI) && (fabs(a->accelerationZdouble) < FREELO)) || ((fabs(a->accelerationXdouble) > FREEHI) && (fabs(a->accelerationYdouble) < FREELO) && (fabs(a->accelerationZdouble) < FREELO)))
		{
			gtk_label_set_label((GtkLabel*)a->label[15], "<span foreground='white' background='red' weight='ultrabold' font='20'> FALL </span>");
			a->freeFallLabel = FALSE;
			g_timeout_add (FREEFALLTIME, (GSourceFunc) freeFallLabel, (gpointer) a);
		}

	}
}

// message dialog callbacks

/**
 * @brief	about message dialog
 *
 */
void about(GSimpleAction *action, GVariant *parameter, gpointer data)
{
	widgets *a = (widgets *) data;

	messageDialog(action, NULL, (gpointer) a, "BEL3 ESS accelerometer task\n\nWerner Egermann, Helmut Resch");
}

/**
 * @brief	help message dialog text concenation
 *
 */
void help(GSimpleAction *action, GVariant *parameter, gpointer data)
{
	widgets *a = (widgets *) data;
	const char connectionText[] = "CONNECTION - choose your /dev/ttyUSB and connect to XMC\n";
	const char statisticText[] = "STATISTIC - receive statistic from XMC with next transmission\n";
	const char saveText[] = "SAVE - enter a filename after activating transmission\n";
	const char terminalText[] = "TERMINAL - simple terminal for raw data, close window to exit\n";
	const char transmissionText[] = "TRANSMISSION - starts and ends transmission and connected tasks\n";
	const char diagramsText[] = "DIAGRAMS - Python connector diagrams X Y Z acceleration\n";
	const char spritesText[]  = "SPRITES - Python connector sprites for ROLL and PITCH\n";
	const char servoText[] = "SERVO - starts stops the servos connected to XMC\n";
	const char enterpolltimeText[] = "polltime in milliseconds - from 10 to 1000 possible\n";
	const char triggeraccText[] = "trigger g-force for every axis can be set and is triggered\n";
	const char buttonText[] = "buttons highlight the pressed buttons on XMC\n";
	gchar messageText[1000];

	g_sprintf(messageText, "%s%s%s%s%s%s%s%s%s%s%s", connectionText, statisticText, saveText, terminalText, transmissionText, diagramsText, spritesText, servoText, enterpolltimeText, triggeraccText, buttonText);
	
	messageDialog(action, NULL, (gpointer) a, messageText);
}

/**
 * @brief	help message dialog
 *
 */
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

/**
 * @brief	quit dialog
 *
 */
void quit(GSimpleAction *action, GVariant *parameter, gpointer data)
{
	widgets *a = (widgets *) data;

	g_application_quit(G_APPLICATION (a->app));
}

// some functions needed

/**
 * @brief	function to convert string to integer
 * @param	input string and output integer pointer
 * @return	0 on success, 1 on error
 *
 */
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

/**
 * @brief	function to convert string to double
 * @param	input string and output double pointer
 * @return	0 on success, 1 on error
 *
 */
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

/** EOF **/
