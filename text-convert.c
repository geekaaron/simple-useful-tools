
/* Program name	- text-convert
 * Author	- Aaron
 * Date		- 2018/11/1
 */

/* Program act
 *	convert <mode> <target> <output> 
 *		mode:
 *			1 - linux to windows
 *			2 - windows to linux
 */

/* Steps
 *	1. Open the target text file
 *	2. Read one line and change old entern string by new entern string
 */

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAME		"text-convert"
#define TEMPFILE	".tempfile"
#define BUFFSIZE	1024
#define MAX_ENTER_LEN	2
#define WINDOWS_ENTER	"\r\n"
#define LINUX_ENTER	"\n"

int repalce_enter (FILE *target, FILE *output, char *old_enter, char *new_enter)
{
	char buffer[BUFFSIZE];
	int rd_count, pos;
	int old_len, new_len;

	old_len = strlen (old_enter);
	new_len = strlen (new_enter);
	while (fgets (buffer, BUFFSIZE-1-MAX_ENTER_LEN, target))
	{
		rd_count = strlen (buffer);
		pos = rd_count - old_len;
		if (!strncmp (buffer+pos, old_enter, old_len))
		{
			strncpy (buffer+pos, new_enter, new_len);
			buffer[pos+new_len] = '\0';
		}
		fputs (buffer, output);
	}

	return 0;
}

int l2w (FILE *target, FILE *output)
{
	return repalce_enter (target, output, LINUX_ENTER, WINDOWS_ENTER);
}

int w2l (FILE *target, FILE *output)
{
	return repalce_enter (target, output, WINDOWS_ENTER, LINUX_ENTER);
}

void usage ()
{
	printf ("Usage: %s <mode> <target> <output>\n", NAME);
	printf ("\tmode:\n");
	printf ("\t\t1 - linux to windows\n");
	printf ("\t\t2 - windows to linux\n");
}

int main (int argc, char *argv[])
{
	FILE *target, *output;
	int mode;

	if (argc != 4)
	{
		fprintf (stderr, "Too many or few arguments!\n");
		goto HELP;
	}

	if (!(target = fopen (argv[2], "r")))
	{
		fprintf (stderr, "Open target file failed!\n");
		exit (-1);
	}

	if (!(output = fopen (argv[3], "w")))
	{
		fprintf (stderr, "Open output file failed!\n");
		exit (-1);
	}

	sscanf (argv[1], "%d", &mode);
	switch (mode)
	{
		case 1: 
			l2w (target, output);
			break;
		case 2: 
			w2l (target, output);
			break;
		default:
			fprintf (stderr, "Unknown mode\n");
			goto HELP;
	}

	fclose (target);
	fclose (output);

NORMAL:
	return 0;

HELP:
	usage ();
	exit (-1);
}
