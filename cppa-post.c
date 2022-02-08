/******************************************************************************
cppa-post.c -- This module of the cppa program handles 'post' mode.
$Id: cppa-post.c 2717 2011-06-20 17:49:43Z miles $
$Source$
******************************************************************************/
#include "cppa.h"
  

/******************************************************************************
Post--- Post-process the text.

    1. Replace each double-quote with a single quote.
    2. Ignore blank lines when the most recent non-blank line was ".DIRECTIVE".
    3. Remove "." from front of lines that begin with ".#".
    4. Replace .BLANK with a blank line.
******************************************************************************/
Post() {

  char line[LINE_CHARS_MAXCNT];
  char adjusted[LINE_CHARS_MAXCNT];
  int len, lindex, aindex;
  int blank_enable;

  blank_enable = TRUE;

  while (Gil_Get_Line(line)) {
    if STREQ(line, ".DIRECTIVE") blank_enable = FALSE;
    else if STREQ(line, ".BLANK") printf("\n");
    else if (line[0] == '\0') {
      if (blank_enable) printf("\n");
    }
    else {
      if (strncmp(line, ".notdirective.", 14) == NULL) {
	/* Remove the ".notdirective." that was added in front of "#" */
	strcpy(tempstr, &line[14]);
	strcpy(line, tempstr);
      }
      blank_enable = TRUE;
      len = strlen(line);
      lindex = 0;
      aindex = 0;
      while (lindex < len) {
	if (((line[lindex] == '"' ) && (line[lindex+1] == '"' )) ||
	    ((line[lindex] == '\'') && (line[lindex+1] == '\''))) {
	  adjusted[aindex++] = line[lindex++];
	  lindex++;
	}
	else adjusted[aindex++] = line[lindex++];
      }
      adjusted[aindex++] = '\0';
      printf("%s\n", adjusted);
    }
  }
}
