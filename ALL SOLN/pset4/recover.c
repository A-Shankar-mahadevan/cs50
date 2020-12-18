#include<stdio.h>
#include <stdlib.h>




int main(int argc, char *argv[])
{
    //Make sure that you have one command line argument
    if (argc != 2)
    {
        printf( "Please enter file to open.\n");
        return 1;
    }

// open memory card file
FILE *file=fopen(argv[1],"r");
if(file == NULL)
{ 
    printf("not a file\n");
}

// set jpg count
int jpg_found=0;

// set filecount
int filecount=0;

// set buffer with 512 bytes. 
unsigned char buffer[512]; // alternate : unsigned char buffer[BUFFER_SIZE]  but you have to :#define BUFFER_SIZE 512 at top

// define file for images
FILE *img=NULL;

// set filename 
char filename[8]; // 8= 3 digits(000-049) 1 dot 3 char(jpg) 1 /0(null terminating char)

// read file
while(fread(buffer,512,1,file)==1) // data,size,qty,file; while this condition is satisfied

// check if jpg using 1st four bytes
 {
 if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0) // for buffer[3] condition watch walkthrough video explanation
{
if( jpg_found==1) // already opened a prior jpg byte then close it
{
    fclose(img);
}
else // if not then you found a jpeg so increment counter
{ 
    jpg_found=1;
}

sprintf(filename,"%03i.jpg",filecount); // print filename 000.jpg and increasing each time
img=fopen(filename,"w"); // open file for images to append/write 
filecount++; // after each file is opened increment file count counter
}
if(jpg_found==1) // once found jpeg write from buffer to img file 
{
    fwrite(&buffer,512,1,img);
}
}
fclose(file); // close file(memory card to buffer) and img(buffer to img file)
fclose(img);

// done
return 0;

}
