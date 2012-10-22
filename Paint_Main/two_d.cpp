#include<windows.h>
#include<math.h>
#include<stdio.h>
#include<stdlib.h>
#include<gl/glut.h>

typedef struct { 
   unsigned short type; 
   unsigned long size; 
   unsigned short reserved1; 
   unsigned short reserved2; 
   unsigned long offsetbits; 
} BITMAPFILEHEADERS; 

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
} BITMAPINFOHEADERS; 

typedef struct { 
   unsigned char blue; 
   unsigned char green; 
   unsigned char red; 
} SINGLE_PIXELS;


#define C (3.14/180)

int	Init_Pointx,
	Init_Pointy,
	Xn,
	Yn,
	arr1[100][2],
	Xr,
	Yr,
	Add_Menu_Done;



char Templates[15][100] = {".\\Templates\\template1.bmp",
			   ".\\Templates\\template3.bmp",				
			   ".\\Templates\\template4.bmp",
			   ".\\Templates\\template5.bmp",
			   ".\\Templates\\template6.bmp",
			   ".\\Templates\\template7.bmp",				
			   ".\\Templates\\template2.bmp",
			   ".\\Templates\\template8.bmp",
			   ".\\Templates\\template9.bmp",
			   ".\\Templates\\template11.bmp",	
			   ".\\Templates\\template10.bmp",
			   ".\\Templates\\template12.bmp",
			   ".\\Templates\\template13.bmp",
			   ".\\Templates\\template14.bmp",	
			   ".\\Templates\\template15.bmp"};
		



unsigned char *temp_pixel_info;
void Draw_Palettes();
void Open_Bitmap(char *);
void Menu_Handles();


void Draw_Rectangle(int x,int y)
{
	
	extern int X,Y,Flag,theme;	
	
	if(Flag == 0){		
		X =  x;
		Y =  y;

		Xn = x;
		Yn = y;

		Flag = 1;
		
		glPointSize(5);
		glBegin(GL_POINTS);
		 glVertex2i(x,y);
		glEnd();
		glFlush();
	}
	else if(Flag == 1){	
		 glPushAttrib(GL_ALL_ATTRIB_BITS);

         if(theme == 2){
		   glColor3f(0.9019,0.9411,1.0);/* BackGround color */
		  }
		else if(theme == 3){
			glColor3f(1.0,1.0,1.0);/* BackGround color */
		}	
		else if(theme == 1){
			glColor3f(0.2901,0.3490,0.4627);/* BackGround color */
		}	
			
		glBegin(GL_LINE_LOOP);
		 glVertex2i(X,Y);
		 glVertex2i(X,Yn);
		 glVertex2i(Xn,Yn);
		 glVertex2i(Xn,Y);		 
		glEnd();
		glFlush();

		glPopAttrib();	

		glBegin(GL_LINE_LOOP);
		 glVertex2i(X,Y);
		 glVertex2i(X,y);
		 glVertex2i(x,y);
		 glVertex2i(x,Y);
		glEnd();
		glFlush();
		
		Xn = x;
		Yn = y;
	}
	
	Draw_Palettes();
}



void Draw_Filled_Rectangle(int x,int y)
{
		
	extern int X,Y,Flag,theme;	
	
	if(Flag == 0)
	{		
		X =  x;
		Y =  y;

		Xn = x;
		Yn = y;

		Flag = 1;
		
	}
	else if(Flag == 1){	
	   glPushAttrib(GL_ALL_ATTRIB_BITS);

       if(theme == 2){
		glColor3f(0.9019,0.9411,1.0);/* BackGround color */
	   }
	   else if(theme == 3){
		glColor3f(1.0,1.0,1.0);/* BackGround color */
	   }	
	   else if(theme == 1){
		glColor3f(0.2901,0.3490,0.4627);/* BackGround color */
	   }	

		glRectf(X, Y, Xn, Yn);
		
		glPopAttrib();
		
		glRectf(X, Y, x, y);
		glFlush();
		
		Xn = x;
		Yn = y;
	}
	
	Draw_Palettes();

}


void Draw_Lines(int x,int y)
{

	extern int X,Y,Flag,theme;
	extern unsigned char pixel_info[921600];

	if(Flag == 0){	
		glPointSize(5);
		glBegin(GL_POINTS);
		 glVertex2i(x,y);
		glEnd();
		glFlush();	
		
		X =  x;
		Y =  y;

		Xn = x;
		Yn = y;

		Flag = 1;
	}
	
	else if(Flag == 1){	
	   glPushAttrib(GL_ALL_ATTRIB_BITS);

       if(theme == 2){
		glColor3f(0.9019,0.9411,1.0);/* BackGround color */
	   }
	   else if(theme == 3){
		glColor3f(1.0,1.0,1.0);/* BackGround color */
	   }	
	   else if(theme == 1){
		glColor3f(0.2901,0.3490,0.4627);/* BackGround color */
	   }	

		glBegin(GL_LINES);
		 glVertex2i(X,Y);
		 glVertex2i(Xn,Yn);
		glEnd();
		glFlush();

		glPopAttrib();
			
		glBegin(GL_LINES);
		 glVertex2i(X,Y);
		 glVertex2i(x, y);
		glEnd();
		glFlush();
		
		Xn = x;
		Yn = y;
	}

	Draw_Palettes();
		
}

void Draw_Circ(int x,int y)
{

	extern int X,Y,Flag;
	float t,rad,sqx,sqy;
	extern unsigned char pixel_info[921600];

	if(Flag == 0)
	{
		X =    x;
		Y =    y;
		Flag = 1;
	}

	else
	{	
		sqx = (X-x) * (X-x);
		sqy = (Y-y) * (Y-y);

		rad = sqrt(sqx+sqy);

		glBegin(GL_LINE_LOOP);
		for(int i=0; i<360; i+=5){
			t = i*C;
			x = rad * sin(t);
			y = rad * cos(t);
			glVertex2i(x+X,y+Y);
		}
		glEnd();
		glFlush();
		Flag = 0;
	}
	Draw_Palettes();
}


void Draw_Filled_Circ(int x,int y)
{

	extern int X,Y,Flag;
	float t,rad,sqx,sqy;
	extern unsigned char pixel_info[921600];

	if(Flag == 0)
	{
		X =    x;
		Y =    y;
		Flag = 1;
	}

	else
	{	
		sqx = (X-x) * (X-x);
		sqy = (Y-y) * (Y-y);

		rad = sqrt(sqx+sqy);

		glBegin(GL_POLYGON);
		for(int i=0; i<360; i+=5){
			t = i*C;
			x = rad * sin(t);
			y = rad * cos(t);
			glVertex2i(x+X,y+Y);
		}
		glEnd();
		glFlush();
		Flag = 0;
	}
	Draw_Palettes();
}

void Draw_Ring(int x,int y)
{

	int xc,yc;
	extern int X,Y,Flag;
	float t,rad,sqx,sqy;
	extern unsigned char pixel_info[921600];

	if(Flag == 0)
	{
		X =    x;
		Y =    y;
		Flag = 1;
	}

	else
	{	
		glPushAttrib(GL_ALL_ATTRIB_BITS);

		sqx = (X-x) * (X-x);
		sqy = (Y-y) * (Y-y);

		glLineWidth(5);

		rad = sqrt(sqx+sqy);

		for(int i=0; i<360; i++){
			t  = i*C;
			x  = rad * sin(t);
			y  = rad * cos(t);

			xc = (rad - 30) * sin(t);
			yc = (rad - 30) * cos(t);	

			glBegin(GL_LINES);
				glVertex2i(x + X, y + Y);
				glVertex2i(xc + X, yc + Y);
				glEnd();
			glFlush();	
			Sleep(5);
		}	
		Flag = 0;
		glPopAttrib();
	}
	Draw_Palettes();
}

void Draw_Points(int x,int y)
{

	extern int X,Y,Flag;
	extern unsigned char pixel_info[921600];
	extern unsigned char palette_Left[57600];
	extern unsigned char palette_Top[57600];
	extern unsigned char palette_Right[57600];
	extern unsigned char palette_Bottom[57600];

	glLineWidth(2);
	if(Flag == 0)
	{		
		X =    x;
		Y =    y;
		Flag = 1;
	}
	
	else if(Flag == 1)
	{		
		glBegin(GL_LINE_STRIP);
		 glVertex2i(X,Y);
		 glVertex2i(x,y);
		glEnd();
		X = x;
		Y = y;
	}
	
	
	Draw_Palettes();
}


void Draw_Polygon(int x,int y)
{
	void *font =  GLUT_BITMAP_9_BY_15;
	extern int X,Y,Flag,Mouse_PositionX,Mouse_PositionY;
		 	

	if(Flag == 0)
	{
		glPointSize(5);
		glBegin(GL_POINTS);
		 glVertex2i(x,y);
		glEnd();
		glFlush();

		Init_Pointx = x;
		Init_Pointy = y;	
		X = x;			
		Y = y;
		Flag = 1;
	}
	else if(Flag == 1)
	{
		glBegin(GL_LINE_STRIP);
		 glVertex2i(X,Y);
		 glVertex2i(x,y);
		glEnd();
		X = x;
		Y = y;
		glFlush();
	}
	Draw_Palettes();
}


void Erasor(int x,int y)
{
	extern int Erasor_Size,theme;

	   if(theme == 1)
		glColor3f(0.2901,0.3490,0.4627);
		
	   else if(theme == 2)
		glColor3f(0.9019,0.9411,1.0);
	   
	   else if(theme == 3)
		glColor3f(1.0,1.0,1.0);
	  
	/*Draw a colored quad(depending on the theme) ,which acts as erasor*/
		glBegin(GL_QUADS);		 
		 glVertex2i(x-Erasor_Size,y-Erasor_Size);
		 glVertex2i(x-Erasor_Size,y+Erasor_Size);
		 glVertex2i(x+Erasor_Size,y+Erasor_Size);
		 glVertex2i(x+Erasor_Size,y-Erasor_Size);	
		glEnd();	
	
	glColor3f(0.0,0.0,0.0);
	glFlush();
	Draw_Palettes();
	
}


void Spray_Points(int x,int y)
{
	
	extern int Spray_Size;
	glPointSize(1);

	for(int i=0 ;i < (Spray_Size * 3) ;i++ ){
		glBegin(GL_POINTS);
		 glVertex2i(x+rand()%Spray_Size,y+rand()%Spray_Size);
		glEnd();
		glFlush();
	}

	Draw_Palettes();
}


void Display_Txt(int x,int y)
{
	extern int X,Y;

	X = x;
	Y = y;
	
	glLineWidth(2);
			
	
	glBegin(GL_LINES);
	  glVertex2i(x,y);
	  glVertex2i(x,y+20);
	  glEnd();
	glFlush();

	Draw_Palettes();

}



void Draw_Spiral(int x,int y)

{
	extern int Flag,X,Y;
	float pi = 3.14,sqx,sqy,radius;
	int i=0;
	float angle,xnew,ynew;

	if(Flag == 0)
	{	
		glPointSize(3);
		glBegin(GL_POINTS);
		glVertex2i(x,y);
		glEnd();
		X = x;
		Y = y;
		glFlush();
		Flag = 1;
	}
	
	else
	{
		sqx = (X-x) * (X-x);
		sqy = (Y-y) * (Y-y);
		
		radius = sqrt(sqx + sqy);

		glBegin(GL_LINE_STRIP);
		while(radius >= 0){
			i += 5;
			angle = (i*(pi/180.0));

			xnew = X + (cos(angle)*radius);
			ynew = Y + (sin(angle)*radius);

			glVertex2f(xnew,ynew);
			
			radius = radius - 0.3;
			
			
		}
		glEnd();
		glFlush();
		Flag = 0;
	}
	Draw_Palettes();
}

void Draw_Line_Wave(int x,int y)
{
	
	extern int X,Y,Flag;

	glLineWidth(1);
	
	if(Flag == 0)
	{		
		X =    x;
		Y =    480 - y;
		Flag = 1;
	}
	
	else if(Flag == 1)
	{		
		glBegin(GL_LINE_STRIP);
		 glVertex2i(X,Y);
		 glVertex2i(x, 480 - y);
		glEnd();
		glFlush();
	
		X = x;
		Y = y;
	}
	Draw_Palettes();	
}


void Pick_Color(int x,int y)
{

	unsigned char pick_col[3];

	glColor3f(1.0 , 0.0 ,0.0 );
	glRectf(195 , 195 , 505 ,505);

	glViewport(200,200,300,300);

    Open_Bitmap(".\\bit\\colors.bmp");
	
	glReadPixels(x , y , 1 , 1 , GL_RGB , GL_UNSIGNED_BYTE , pick_col);

	glColor3f(pick_col[0]/255.0 , pick_col[1]/255.0 , pick_col[2]/255.0);

	glViewport(0,0,800,600);
	printf("\n%f %f %f is th nEW COL \n",pick_col[0]/255.0 , pick_col[1]/255.0 , pick_col[2]/255.0);

}


void Rotate_Shape(int x,int y)
{
	
	extern int Point_Count;

	glPointSize(5);

	
	arr1[Point_Count][0]   = x;
	arr1[Point_Count++][1] = y;

	glBegin(GL_POINTS);
	  glVertex2i(x,y);		
	glEnd();
	glFlush();
	
	if(Point_Count == 1){}
	else
	{
	  glBegin(GL_LINES);
	   glVertex2i(arr1[Point_Count-2][0],arr1[Point_Count-2][1]);
	   glVertex2i(arr1[Point_Count-1][0],arr1[Point_Count-1][1]);			
           glEnd();
	   glFlush();
	}
	Draw_Palettes();
		
}		

void Scale_Shape(int x,int y)
{
	
	extern int Point_Count;

	glPointSize(5);

	
	arr1[Point_Count][0]   = x;
	arr1[Point_Count++][1] = y;

	glBegin(GL_POINTS);
	  glVertex2i(x,y);		
	glEnd();
	glFlush();
	
	if(Point_Count == 1){}
	else
	{
	  glBegin(GL_LINES);
	   glVertex2i(arr1[Point_Count-2][0],arr1[Point_Count-2][1]);
	   glVertex2i(arr1[Point_Count-1][0],arr1[Point_Count-1][1]);			
           glEnd();
	   glFlush();
	}
	Draw_Palettes();
		
}

void Cut_Image(int x,int y)
{	
	extern int X,Y,Flag;

	if(Flag == 0){
		X = x;
		Y = y;
		Flag = 1;
		
		glPointSize(5);
		glBegin(GL_POINTS);
			glVertex2i(X,Y);
		glEnd();
		glFlush();
	}else{	
		glPointSize(5);
		glBegin(GL_POINTS);
			glVertex2i(x,y);
		glEnd();
		glFlush();

		Xr = ((x - X));/*In order to read an area of L x B*/
		Yr = ((y - Y));

		glBegin(GL_LINE_LOOP);
		   glVertex2i(X,Y);
		   glVertex2i(x,Y);	
	           glVertex2i(x,y);
		   glVertex2i(X,y);
	  	glEnd();
	  	glFlush();
				
			
		temp_pixel_info = (unsigned char *)malloc(Xr * Yr * 3);
		glReadPixels(X,Y,abs(Xr),abs(Yr),GL_RGB, GL_UNSIGNED_BYTE,temp_pixel_info);
	}
	Draw_Palettes();
}
	

void Draw_Point(int x,int y)
{
	glEnable(GL_POINT_SMOOTH);
	
	glBegin(GL_POINTS);
		glVertex2i(x,y);
	glEnd();
	glFlush();

	glDisable(GL_POINT_SMOOTH);
}	


void Draw_Colored_Rectangle(int x,int y)
{
	extern int X,Y,Flag;	
	int xTemp,yTemp;	

	if(Flag == 0)
	{
		X = x;
		Y = y;
		Flag  = 1;
		
		glPointSize(5);
		glBegin(GL_POINTS);
			glVertex2i(X,Y);
		glEnd();
		glFlush();
	}

	else
	{
	  glPointSize(5);
		glBegin(GL_POINTS);
			glVertex2i(x,y);
		glEnd();
	  glFlush();	
		
	  xTemp = X;
	  yTemp = Y;		
		
	  /*Draw the random colored line loops till x1 becomes = x2 */	
	    for(; (xTemp <= x) && (yTemp <= y) ;){
			glColor3f(rand()%3,rand()%3,rand()%3);
			glBegin(GL_LINE_LOOP);
			  glVertex2i(xTemp , yTemp);
	 		  glVertex2i(xTemp++ , y);
	 		  glVertex2i(x , y--);	
	 		  glVertex2i(x-- , yTemp++);
			glEnd();
			glFlush();
	 		Sleep(100);
	   }	
				
	
	  
	Flag = 0;
    }

}


void Open_Template(int x, int y)
{
	extern int Win_Width, Win_Height,template_no;

	glViewport(50,61,696,502);
	Open_Bitmap(Templates[template_no++]);

	if(template_no == 15)
		template_no = 0;

	glViewport(0, 0, 800, 600);	
	//glViewport(0, 0, Win_Width, Win_Height);

	//if(temp_no == 3)
		//temp_no = 0;
}


void Draw_Ellipse(int x, int y)
{
	int a,b;
	
	extern int X,Y,Flag;
	float t,rad,sqx,sqy;
	extern unsigned char pixel_info[921600];

	
	if(Flag == 0)
	{
		X =    x;
		Y =    y;
		Flag = 1;
	}

	else
	{	
		sqx = (X-x) * (X-x);
		sqy = (Y-y) * (Y-y);

		b = abs(X - x);
		a = abs(Y - y);	 
		
		rad = sqrt(sqx+sqy);

		glBegin(GL_LINE_LOOP);
		for(int i=0; i<360; i+=5){
			t = i*C;
			x = b * sin(t);
			y = a * cos(t);
			glVertex2i(x+X,y+Y);
		}
		glEnd();
		glFlush();
		Flag = 0;
	}
	Draw_Palettes();

}	

void Draw_Filled_Ellipse(int x, int y)
{
	int a,b;
	
	extern int X,Y,Flag;
	float t,rad,sqx,sqy;
	extern unsigned char pixel_info[921600];

	
	if(Flag == 0)
	{
		X =    x;
		Y =    y;
		Flag = 1;
	}

	else
	{	
		sqx = (X-x) * (X-x);
		sqy = (Y-y) * (Y-y);

		b = abs(X - x);
		a = abs(Y - y);	 
		
		rad = sqrt(sqx+sqy);

		glBegin(GL_POLYGON);
		for(int i=0; i<360; i+=5){
			t = i*C;
			x = b * sin(t);
			y = a * cos(t);
			glVertex2i(x+X,y+Y);
		}
		glEnd();
		glFlush();
		Flag = 0;
	}
	Draw_Palettes();

}	


void Rotate_Image(int x,int y)
{
	
	/*Logic:The current drawing area's screenshot is taken.A bitmap is written and is 
	 *then loaded after being rotated.
	 *Awesome logic by Bharat L(senior) 
	 */

	FILE *fp,*fp1;
	unsigned char *temp_image,r,g,b;
	BITMAPINFOHEADERS bitm;
	BITMAPFILEHEADERS bitmp;
	extern int Image_Rot;/*The angle by which the image has to be rotated*/
	extern int Image_Rotate_Flag,Flag;/*In order to tell the Open_Bitmap function*/
								  	
	int i;

	temp_image = (unsigned char*)malloc(696 * 502 * 3);
	if(Flag == 0){
		glReadPixels(50, 61, 696, 502, GL_RGB, GL_UNSIGNED_BYTE,temp_image);

		/*White File*/
		fp = fopen(".\\sample\\MUK1.bmp","rb");
	
		fread(&bitmp,14,1,fp);			
		fread(&bitm,40,1,fp);	

		fp1 = fopen(".\\sample\\Temp.bmp","wb");

		/*Write into the new file*/
		fwrite(&bitmp,14,1,fp1);
		fwrite(&bitm,40,1,fp1);
					
				
		/*Write the r,g,b values into the file*/
		for(i=0; i<696 * 502 * 3;i += 3){
			b = temp_image[i+2];
			fwrite(&b,1,1,fp1);
			g = temp_image[i+1];
			fwrite(&g,1,1,fp1);
			 r = temp_image[i];
			 fwrite(&r,1,1,fp1);
		}
		fclose(fp);
		fclose(fp1);

		Flag = 1;
	}

	else{
		/*Load Identity in the MODELVIEW matrix*/
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		glTranslatef(348,251,0);
		glRotatef(Image_Rot += 10, 0 ,0, 1);	 /*Half the image size*/
		glTranslatef(-348,-251,0); 

		Image_Rotate_Flag = 1;
		Open_Bitmap(".\\sample\\Temp.bmp");/*Now image is rotated!WooHOO*/
	
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		Draw_Palettes();
		free(temp_image);
	}

}	

void Draw_Weird_Things(int x, int y)
{
	unsigned char read_image[1200];
	
	glReadPixels(x ,y , 20 , 20 ,GL_RGB , GL_UNSIGNED_BYTE , read_image);
	
	glRasterPos2f(x + (rand()%10) , y + (rand()%10));
	glDrawPixels(20 , 20 ,GL_RGB , GL_UNSIGNED_BYTE , read_image);
	
	Draw_Palettes();
}