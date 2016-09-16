#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//Chantz Spears Graphics project 1
//ppm converter for p6 and p3 images

//Make struct outside of functions for global use
typedef struct Pixel{
  unsigned int red, grn ,blu;
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
sscanf(width, "%d", &iwidth);

//gets file height
char height[10];
iterator = 0;
while(pass != '\n'){
  height[iterator++] = pass;
  pass = fgetc(fhin);
}
int iheight = atoi(height);
sscanf(height, "%d", &iheight);

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
sscanf(channel, "%d", &channel_int);
if(channel_int != 255){
  fprintf(stderr, "Files channel size must be 255");
  fclose(fhin);
  return 1;
}

//now that header has been checked need to rewind to read everything in
rewind(fhin);
char hbuff[5000] = {'\0'};
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

//Reading pixel data
Pixel img_arr[iheight][iwidth];
if (strcmp("P3", m_n) == 0){
  for(int rows = 0; rows < iheight; rows++){
    for(int cols = 0; cols < iwidth; cols++){
      char red[4] = {'\0'};
      char grn[4] = {'\0'};
      char blu[4] = {'\0'};
      pass = fgetc(fhin);
      for(int x = 0; x < 3; x++){
        if (pass == ' ' || pass == '\n'){break;}
        red[x] = pass;
        pass = fgetc(fhin);
      }
      while (pass == ' ' || pass == '\n') {pass = fgetc(fhin);}

      for(int x = 0; x < 3; x++){
        if (pass == ' ' || pass == '\n'){break;}
        grn[x] = pass;
        pass = fgetc(fhin);
      }
      while (pass == ' ' || pass == '\n') {pass = fgetc(fhin);}

      for(int x = 0; x < 3; x++){
        if (pass == ' ' || pass == '\n'){break;}
        blu[x] = pass;
        pass = fgetc(fhin);
      }
      while (pass == ' ' || pass == '\n') {pass = fgetc(fhin);}

      ungetc(pass, fhin);

      img_arr[rows][cols].red = atoi(red);
      img_arr[rows][cols].grn = atoi(grn);
      img_arr[rows][cols].blu = atoi(blu);

    }
  }
} else{
  for(int rows = 0; rows < iheight; rows++){
    for(int cols = 0; cols < iwidth; cols ++){
      int rpx[1];
      int gpx[1];
      int bpx[1];
      fread(rpx, 1, 1, fhin);
      fread(gpx, 1, 1, fhin);
      fread(bpx, 1, 1, fhin);
      img_arr[rows][cols].red = rpx[0];
      img_arr[rows][cols].grn = gpx[0];
      img_arr[rows][cols].blu = bpx[0];
    }
  }
}

//Writing the pixels to output file
FILE* out = fopen(argv[3], "w");
fprintf(out, "%s\n",hbuff);
if(*argv[1] == '3'){
  for(int rows = 0; rows < iheight; rows++){
    for(int cols = 0; cols < iwidth; cols++){
      fprintf(out, "%i %i %i\n",img_arr[rows][cols].red, img_arr[rows][cols].grn, img_arr[rows][cols].blu);
    }
  }
}
fclose(fhin);
fclose(out);
fflush(stdout);
  return 0;
}
