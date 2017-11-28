/* This is a GTK example program for catching (unix-)signals */

#include <stdio.h>		/* for printf and friends */
#include <stdlib.h>		/* for exit */
#include <unistd.h>		/* for write, pipe */
#include <fcntl.h>		/* for fcntl, O_NONBLOCK */
#include <signal.h>		/* for signal */
#include <gtk/gtk.h>		/* well guess for what ... */

/* 
 * Unix signals that are cought are written to a pipe. The pipe connects 
 * the unix signal handler with GTK's event loop. The array signal_pipe will 
 * hold the file descriptors for the two ends of the pipe (index 0 for 
 * reading, 1 for writing).
 * As reaction to a unix signal we change the text of a label, hence the
 * label must be global.
 */
int signal_pipe[2];
GtkWidget *label;

/* Callback for the Quit button */
static void destroy( GtkWidget *widget, gpointer   data )
{
  gtk_main_quit ();
}

/* 
 * The unix signal handler.
 * Write any unix signal into the pipe. The writing end of the pipe is in 
 * non-blocking mode. If it is full (which can only happen when the 
 * event loop stops working) signals will be dropped.
 */
void pipe_signals(int signal)
{
  if(write(signal_pipe[1], &signal, sizeof(int)) != sizeof(int))
    {
      fprintf(stderr, "unix signal %d lost\n", signal);
    }
}
  
/* 
 * The event loop callback that handles the unix signals. Must be a GIOFunc.
 * The source is the reading end of our pipe, cond is one of 
 *   G_IO_IN or G_IO_PRI (I don't know what could lead to G_IO_PRI)
 * the pointer d is always NULL
 */
gboolean deliver_signal(GIOChannel *source, GIOCondition cond, gpointer d)
{
  GError *error = NULL;		/* for error handling */

  /* 
   * There is no g_io_channel_read or g_io_channel_read_int, so we read
   * char's and use a union to recover the unix signal number.
   */
  union {
    gchar chars[sizeof(int)];
    int signal;
  } buf;
  GIOStatus status;		/* save the reading status */
  gsize bytes_read;		/* save the number of chars read */
  char text[40];		/* the text that will appear in the label */
  

  /* 
   * Read from the pipe as long as data is available. The reading end is 
   * also in non-blocking mode, so if we have consumed all unix signals, 
   * the read returns G_IO_STATUS_AGAIN. 
   */
  while((status = g_io_channel_read_chars(source, buf.chars, 
		     sizeof(int), &bytes_read, &error)) == G_IO_STATUS_NORMAL)
    {
      g_assert(error == NULL);	/* no error if reading returns normal */

      /* 
       * There might be some problem resulting in too few char's read.
       * Check it.
       */
      if(bytes_read != sizeof(int)){
	fprintf(stderr, "lost data in signal pipe (expected %d, received %d)\n",
		sizeof(int), bytes_read);
	continue;	      /* discard the garbage and keep fingers crossed */
      }

      /* Ok, we read a unix signal number, so let the label reflect it! */
      snprintf(text, 40, "received signal %d", buf.signal);
      gtk_label_set_text(GTK_LABEL(label), text);
    }
  
  /* 
   * Reading from the pipe has not returned with normal status. Check for 
   * potential errors and return from the callback.
   */
  if(error != NULL){
    fprintf(stderr, "reading signal pipe failed: %s\n", error->message);
    exit(1);
  }
  if(status == G_IO_STATUS_EOF){
    fprintf(stderr, "signal pipe has been closed\n");
    exit(1);
  }

  g_assert(status == G_IO_STATUS_AGAIN);
  return (TRUE);		/* keep the event source */
}


int main( int argc, char *argv[] )
{
  /* Create a window with a button and a label inside a table */
  GtkWidget *window;
  GtkWidget *button;
  /* GtkWidget *label is global so that we can change it outside */
  GtkWidget *table;

  /* 
   * In order to register the reading end of the pipe with the event loop 
   * we must convert it into a GIOChannel.
   */
  GIOChannel *g_signal_in; 

  GError *error = NULL;	/* handle errors */
  long fd_flags; 	    /* used to change the pipe into non-blocking mode */
    
  /* initialize gtk, create the table, the button and the label 
   * put everything together and show it
   */
  gtk_init (&argc, &argv);

  window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  g_signal_connect (G_OBJECT (window), "destroy",
		    G_CALLBACK (destroy), NULL);
  gtk_container_set_border_width (GTK_CONTAINER (window), 5);

  table = gtk_table_new (2, 1, FALSE);
  gtk_container_add (GTK_CONTAINER (window), table);

  button = gtk_button_new_with_label ("Quit");
  g_signal_connect (G_OBJECT (button), "clicked",
		    G_CALLBACK (destroy), NULL);
  gtk_table_attach(GTK_TABLE(table), button, 0,1,0,1, 
		   GTK_SHRINK | GTK_EXPAND, GTK_SHRINK | GTK_EXPAND, 0,0);

  label = gtk_label_new("No signal yet");
  gtk_table_attach(GTK_TABLE(table), label, 0,1,1,2, 
		   GTK_SHRINK | GTK_EXPAND, GTK_SHRINK | GTK_EXPAND, 0,0);

  gtk_widget_show (button);
  gtk_widget_show (label);
  gtk_widget_show (table);
  gtk_widget_show (window);


  /* 
   * Set the unix signal handling up.
   * First create a pipe.
   */
  if(pipe(signal_pipe)) {
    perror("pipe");
    exit(1);
  }

  /* 
   * put the write end of the pipe into nonblocking mode,
   * need to read the flags first, otherwise we would clear other flags too.
   */
  fd_flags = fcntl(signal_pipe[1], F_GETFL);
  if(fd_flags == -1)
    {
      perror("read descriptor flags");
      exit(1);
    }
  if(fcntl(signal_pipe[1], F_SETFL, fd_flags | O_NONBLOCK) == -1)
    {
      perror("write descriptor flags");
      exit(1);
    }

  /* Install the unix signal handler pipe_signals for the signals of interest */
  signal(SIGINT, pipe_signals);
  signal(SIGUSR1, pipe_signals);

  /* convert the reading end of the pipe into a GIOChannel */
  g_signal_in = g_io_channel_unix_new(signal_pipe[0]);

  /* 
   * we only read raw binary data from the pipe, 
   * therefore clear any encoding on the channel
   */
  g_io_channel_set_encoding(g_signal_in, NULL, &error);
  if(error != NULL){		/* handle potential errors */
    fprintf(stderr, "g_io_channel_set_encoding failed %s\n",
	    error->message);
    exit(1);
  }

  /* put the reading end also into non-blocking mode */
  g_io_channel_set_flags(g_signal_in,     
      g_io_channel_get_flags(g_signal_in) | G_IO_FLAG_NONBLOCK, &error);

  if(error != NULL){		/* tread errors */
    fprintf(stderr, "g_io_set_flags failed %s\n",
	    error->message);
    exit(1);
  }

  /* register the reading end with the event loop */
  g_io_add_watch(g_signal_in, G_IO_IN | G_IO_PRI, deliver_signal, NULL);

  /* let it run */
  gtk_main ();

  return 0;
}


/*** Local Variables: ***/
/*** compile-command: "gcc -Wall -o catch_signals `pkg-config --cflags --libs gtk+-2.0` catch_signals.c" ***/
/*** End: ***/

