#include<gl/glut.h>
#include<stdio.h>
#include<stdlib.h>


/*Info about the Bitmap image*/
typedef struct { 
   unsigned short type; 
   unsigned long size; 
   unsigned short reserved1; 
   unsigned short reserved2; 
   unsigned long offsetbits; 
} BITMAPFILEHEADER12; 

typedef struct { 
   unsigned long size; 
   unsigned long width; 
   unsigned long height; 
   unsigned short planes; 
   unsigned short bitcount; 
   unsigned long compression; 
   unsigned long sizeimage; 
   long xpelspermeter; 
   long ypelspermeter; 
   unsigned long colorsused; 
   unsigned long colorsimportant; 
} BITMAPINFOHEADER12; 

typedef struct { 
   unsigned char blue; 
   unsigned char green; 
   unsigned char red; 
} SINGLE_PIXEL12; 





void Open_Bitmap(char *name)
{
	FILE *fp;
	unsigned char p;
	int x=0,y=0,c=0;
	float r,g,b;
	extern int Win_Width,Win_Height;//SUMMER OF 69!!!!!!!!!!!!!
	extern int Image_Rotate_Flag;

	BITMAPINFOHEADER12 bitm;
	BITMAPFILEHEADER12 bitmp;

	fp = fopen(name,"rb");

	if(fp == NULL)
		exit(0);	

	fread(&bitmp,14,1,fp);
	fread(&bitm,40,1,fp);
	//fread(&bitmp,sizeof(BITMAPFILEHEADER1),1,fp);

	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	/*Orhtho vol can be set to the width and height of image*/
	glOrtho(0.0,bitm.width,0.0,bitm.height,-500,500);
/*	
	printf("\n0:%d",sizeof(SINGLE_PIXEL12));
	printf("\n1:%d",bitm.size);
	printf("\n2 width = %d",bitm.width);
	printf("\n3:height= %d",bitm.height);
	printf("\n4:%d",bitm.planes);
	printf("\n5:%d",bitm.bitcount);
	printf("\n6:%d",bitm.compression);
	printf("\n7:%d",bitm.colorsimportant);
*/

	/*This is for the image rotation case*/
	if(Image_Rotate_Flag == 1){
		Image_Rotate_Flag = 0;
		glViewport(50, 61, 696, 502);
	}
	
	glPointSize(2);
	glBegin(GL_POINTS);
	while(!feof(fp))
	{
		fread(&p,1,1,fp);
		b = p/255.0;
		fread(&p,1,1,fp);
		g = p/255.0;
		fread(&p,1,1,fp);
		r = p/255.0;

		//printf("\n%f",r);
		
		/*Analyse*/
		//if(r == 1 && g == 1 && b == 1)
		//	glColor3f(0.11,0.295,0.56);
		//else
			glColor3f(r,g,b);
		
		glVertex2i(x++,y);

		if(x == (signed)bitm.width)
		{	
			x = 0;
			y++;
		}
		
	}
	glEnd();
	glFlush();
	fclose(fp);
	//printf("\n\n\nCaution:-->%d",c);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	/*Restore the Ortho volume*/
	glOrtho(0.0,800,0.0,600,-500,500);
	
	/*Set the viewport to Win_Width ,Win_Height*/
	glViewport(0,0,800,600);
	
}

	