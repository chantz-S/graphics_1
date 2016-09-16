#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//Chantz Spears Graphics project 1
//ppm converter for p6 and p3 images

//Make struct outside of functions for global use
typedef struct Pixel{
  unsigned int r, g ,b;
}Pixel;

int main(int argc, char const *argv[]) {
  // Some error catching lines incase of bad input

  //open the file to read and error if there is problem opening given file
  FILE* fhin = fopen(argv[2],"r");
  if(fhin == NULL) {
    fprintf(stderr, "Error opening input file\n" );
    return 1;
  }

  //Needs four inputs
  if(argc != 4){
    fprintf(stderr, "Input pattern must be: ppmrw # input.ppm output.ppm\n" );
    return 1;
  }

  //if its not p3 or p6 desired then error
  if(*argv[1] !='3' && *argv[1]!='6'){
    fprintf(stderr, "Must enter 3 or 6 for argument format number\n" );
    return 1;
  }


//check image is p3 or p6 format
char m_n[] = {fgetc(fhin), fgetc(fhin), '\0'};
if(strcmp("P3", m_n) !=0 && strcmp("P6", m_n) !=0){
  fprintf(stderr, "File is not ppm format\n");
  return 1;
}

//passes to next needed line or char
char pass = fgetc(fhin);
pass = fgetc(fhin);
fprintf(stdout, "%c\n", pass);

char ar[1000];
int comments = 0;
while (pass == '#'){
   fgets(ar,1000,fhin);
   comments++;
   pass = fgetc(fhin);
}

//gets the file width
char width[10];
int iterator = 0;
while(pass != ' '){
  width[iterator++] = pass;
  pass = fgetc(fhin);
}


int iwidth = atoi(width);
fprintf(stdout, "%i", iwidth );

//gets file height
char height[10];
iterator = 0;
while(pass != '\n'){
  height[iterator++] = pass;
  pass = fgetc(fhin);
}
int iheight = atoi(height);
fprintf(stdout, " %i\n", iheight );

//gets chanel size
pass = fgetc(fhin);
char channel[4];
iterator = 0;
while(pass != '\n'){
  channel[iterator++] = pass;
  pass = fgetc(fhin);
}
// scans the channel size to make sure its 255
int channel_int;
sscanf(channel, "%d" &channel_int);
if(channel_int != 255){
  fprintf(stderr, "Files channel size must be 255");
  fclose(fhin);
  return 1;
}

//now that header has been checked need to rewind to read everything in
rewind(fhin);
char hbuff[5000] = {'\0'}
pass = fgetc(fhin);
int counter = 0; // determine pos
int line_num = 3 + comments; // determine line number program is on
while(line_num != 0) {
  if (pass == '\n'){
    line_num--;
  }

  hbuff[counter++] = pass; //increment position
  pass = fgetc(fhin);
}

hbuff[1] = *argv[1];
fprintf(stdout, "%s\n", hbuff); //print out header



fflush(stdout);
  return 0;
}
