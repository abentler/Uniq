#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_SIZE 256

char *read_long_line(FILE *file);

int main(int argc, char *argv[]) {
   FILE *infile = stdin;	/* defaults to reading from stdin */
   FILE *outfile = stdout;	/* defaults to writing to stdout */
   char *line = NULL;		/* this will store the current line */
   char *prev = "";		/* this will store the prev. line */

   if(argc > 1) { /* check for command line arguments */

      if(NULL == (infile = fopen(argv[1], "r"))) {
         perror(argv[1]);
         exit(EXIT_FAILURE);
      }

      if(argc > 2) { /* first arg -> infile, 2nd arg (if exist) -> outfile */

         if(NULL == (outfile = fopen(argv[2], "w+"))) {
            perror(argv[1]);
            exit(EXIT_FAILURE);
         }


      }
      
   }

   while(-1 != *(line = read_long_line(infile))) { /* reads lines until EOF */
            
      if(strcmp(prev, line)) { /* if current line isn't a dup, print */
    
         fprintf(outfile, "%s\n", line);
    
      }  
       
      prev = line; /* update the previous line before looping again */

   }

   
   return 0;

}

/* read_long_line reads one line from the given file stream until \n or EOF.
 * If the line is too long for the buffer, it will expand the buffer and
 * continue reading. */
char *read_long_line(FILE *file) {

   char *line = NULL; 	/* line is a pointer to the current line */
   int len = 0;		/* current index in the line */
   int c;		/* current character */
   int maxlen = LINE_SIZE; /* tracks the max buffer size */

   if(NULL == (line = malloc(LINE_SIZE * sizeof(char)))) {
      perror("malloc");
      exit(EXIT_FAILURE);
   }

/* I use getc to facilitate checking for eof and newline, but since it
 * is buffered i/o there should not be a significant performance hit.
 * it will loop until EOF or newline */
   while(-1 != (c = fgetc(file)) && c != '\n') {

      line[len] = c;	/* append char to line */
      len++;

      if(len == (maxlen - 1)) { /* resize line buffer before overflow */
      
         char *upgrade = realloc(line, maxlen + LINE_SIZE);
         line = upgrade;
         maxlen += LINE_SIZE;
      
      }

   }
   
   /* append EOF or null character */
   if(c == -1) {
      line[len] = c;
   } else {
      line[len] = '\0';
   }

   return line;

}
