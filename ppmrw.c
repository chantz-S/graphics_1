#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char const *argv[]) {
  if(argc != 4){
    fprintf(stderr, "Input pattern must be: ppmrw # input.ppm output.ppm\n" );
    return 1;
  }
  if(*argv[1] !='3' && *argv[1]!='6'){
    fprintf(stderr, "Must enter 3 or 6 for argument format number\n" );
    return 1;
  }

FILE* fh = fopen(argv[2],"r");
if(fh == NULL) {
  fprintf(stderr, "Error opening file\n" );
  return 1;
}

char m_n[] = {fgetc(fh), fgetc(fh), '\0'};
if(strcmp("P3", m_n) !=0 && strcmp("P6", m_n) !=0){
  fprintf(stderr, "File is not ppm format\n");
  return 1;
}

char pass = fgetc(fh);
pass = fgetc(fh);
fprintf(stdout, "%c\n", pass);

while (pass == '#'){
  char ar[100];
   fgets(ar,100,fh);
  pass = fgetc(fh);
}


char width[10];
int iterator = 0;
while(pass != ' '){
  width[iterator++] = pass;
  pass = fgetc(fh);
}

int iwidth = atoi(width);
fprintf(stdout, "%i", iwidth );

char height[10];
iterator = 0;
while(pass != '\n'){
  height[iterator++] = pass;
  pass = fgetc(fh);
}
int iheight = atoi(height);
fprintf(stdout, " %i\n", iheight );


fflush(stdout);
  return 0;
}
