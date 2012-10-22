#include <string.h>
#include <GL/glut.h>
#include<stdio.h>
#include<windows.h>



struct AL
{
	char alpha;
	int vertices[2][2];
}A[28];

/*26 for 26 alphabets
 *2 for the OK and CANCEL options
 */

void *font =  GLUT_BITMAP_9_BY_15;


/******Prototypes******************/
AL Search_Alpha(int x,int y);
void Alphabet_Palette_Draw();
void display(void);
/**********************************/


int Xpos = 0,
	Ypos = 300,
	Win_Code,
	RW_Mode,
	Page_Over = 0;
	

char Name_Of_File[100];
unsigned char write_pixel_info[1440000];
char full_filename[100] = {".\\User_Files\\"};	


/*Info about the Bitmap image*/
typedef struct { 
   unsigned short type; 
   unsigned long size; 
   unsigned short reserved1; 
   unsigned short reserved2; 
   unsigned long offsetbits; 
} BITMAPFILEHEADER1; 

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
} BITMAPINFOHEADER1; 

typedef struct { 
   unsigned char blue; 
   unsigned char green; 
   unsigned char red; 
} SINGLE_PIXEL1; 

/***********************Read Bitmap***************************/	
void Open_Bitmap_File(char *fname)
{
	FILE *fp;unsigned char p;
	int x=0,y=0,c=0;
	float r,g,b;
	extern int w;

	
	glutDestroyWindow(Win_Code);
	BITMAPINFOHEADER1 bitm;
	BITMAPFILEHEADER1 bitmp;
	Sleep(1000);

	fp = fopen(fname,"rb");
	
	fread(&bitmp,14,1,fp);
	fread(&bitm,40,1,fp);
	
	gluOrtho2D(0.0,640.0,0.0,480.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();	
		
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
	printf("\n\n\nCaution:-->%d",c);
	
}

	
/****Read/Write into the file********************************/
void Perform_Operation(char *fname)
{

	int x = 50,y = 50;
	char *message = "File Created !! ";
	extern int Window_Done,Read_Op,FileNameCount;
	

//	extern int done,Motion_Flag,TWO_D_MODE,entry;

	/*Write*/
	if(RW_Mode == 1)
	{
		
				FILE *fp;/*The White File*/
				FILE *fp1;/*The file you have to write into*/
				
				unsigned char r,g,b;
				int i;
		

				BITMAPINFOHEADER1 bitm;
				BITMAPFILEHEADER1 bitmp;

	
				/*White File*/
				fp = fopen(".\\sample\\MUK.bmp","rb");
	
				fread(&bitmp,14,1,fp);			
				fread(&bitm,40,1,fp);	
				
				
				strcat(fname,".bmp");
				strcat(full_filename ,fname);	
	
				/*To be written into this*/
				fp1 = fopen(full_filename,"wb");		


				/*Write into the new file*/
				fwrite(&bitmp,14,1,fp1);
				fwrite(&bitm,40,1,fp1);
					
				
				/*Write the r,g,b values into the file*/
				for(i=0; i<3*800*600;i += 3){
          				b = write_pixel_info[i+2];
		  			fwrite(&b,1,1,fp1);
		  			g = write_pixel_info[i+1];
		  			fwrite(&g,1,1,fp1);
		  			r = write_pixel_info[i];
		  			fwrite(&r,1,1,fp1);
				}
				fclose(fp);
				fclose(fp1);	

				/*File Created message*/
				for(i=0 ;message[i] != '\0';){
					glRasterPos2f(x+=10,y);
					glutBitmapCharacter(font,message[i++]);
				}
				
				Window_Done = 1;
				Sleep(1000);
				strcpy(full_filename,".\\User_Files\\");
				FileNameCount = 0;
				glutDestroyWindow(Win_Code);
			
	}	
		
	else if(RW_Mode == 2){
		strcat(fname,".bmp");
		strcat(full_filename ,fname);
			
		Window_Done = 0;
		Read_Op = 1;
		
		glutDestroyWindow(Win_Code);
		
		
	}
		
	
//	done = 0;
//	Motion_Flag  = 0;
//	TWO_D_MODE = 1; 
//	entry = 1;   
//	glutDestroyWindow(Win_Code);  
}

/**********************************************************************/

/*Draw the small Squares where the palettes are displayed*/
void Draw_SQu(int x1,int y1,int x2,int y2,char let)
{
	glRasterPos2f(x1+5,y1+5);
	glutBitmapCharacter(font, let);
	
	glColor3f(1.0,0.0,0.0);
	
	glBegin(GL_LINE_LOOP);
	 glVertex2i(x1,y1);
	 glVertex2i(x1,y2);
	 glVertex2i(x2,y2);	
	 glVertex2i(x2,y1);
	glEnd();
	glFlush();
	
}



/********************Display Options***********************************/

void Alphabet_Palette_Draw()
{
	int xx = 200,yy = 100,i;
	char let = 65;
	char *modes1 = "FILENAME";
	char *modes2 = "OK";
	char *modes3 = "CANCEL";

	/*******************************************************************************************/
	/*Draw the background for the display*/
	{
		float colorRed   = 0.4588;
		float colorGreen = 0.4190;
		float colorBlue  = 0.3247;
		int x1 = 0, y1 = 0, x2 = 300, y2 = 300;
		
		//glColor3f(0.3921,0.6313,0.9091);Initally used color -> a blue shade
		
		for(; y1 != y2 ;){
			glColor3f( colorRed += 0.002 ,  colorGreen += 0.0025 , colorBlue += 0.002);
			glBegin(GL_LINES);
		  	 glVertex2i(x1,y1);
		   	 glVertex2i(x2,y1++);
		  	glEnd();
			glFlush();
			//Sleep(100);
		
		}
	}
	/*******************************************************************************************/
 	
	glColor3f(0.0,0.0,0.0);
	Xpos = 20;Ypos = 225;
	for(i = 0; i < (signed)strlen(modes1); i++){
		glRasterPos2f(Xpos+=10,Ypos);
		glutBitmapCharacter(font, modes1[i]);
	}

	Xpos = 20;Ypos = 150;
	for(i = 0; i < (signed)strlen(modes2) ; i++){
		glRasterPos2f(Xpos+=10,Ypos);
		glutBitmapCharacter(font, modes2[i]);
	}
	
	Xpos = 60;Ypos = 150;
	for(i = 0; i < (signed)strlen(modes3); i++){
		glRasterPos2f(Xpos+=10,Ypos);
		glutBitmapCharacter(font, modes3[i]);
	}

	Draw_SQu(20,175,150,200,NULL);
	Xpos = 22;
	Ypos = 180;
	
	for(i = 0 ; i < 26 ; i++){
		
		if(xx >= 280){
			yy += 20;
			xx = 200;
		}
		A[i].alpha = let++;
				
		A[i].vertices[0][0] = xx;
		A[i].vertices[0][1] = yy;
		
		xx+=20;
		yy+=20;


		A[i].vertices[1][0] = xx;
		A[i].vertices[1][1] = yy;

		yy-=20;

	}
	A[26].vertices[0][0] = 30;
	A[26].vertices[0][1] = 147;
	A[26].vertices[1][0] = 60;
	A[26].vertices[1][1] = 160;
	A[i].alpha = 25; /*For OK case*/

	A[27].vertices[0][0] = 60;
	A[27].vertices[0][1] = 140;
	A[27].vertices[1][0] = 150;
	A[27].vertices[1][1] = 160;
	A[27].alpha = 26; /*For CANCEL case*/

	for(i = 0 ; i < 26 ; i++)
		Draw_SQu(A[i].vertices[0][0],A[i].vertices[0][1],A[i].vertices[1][0],A[i].vertices[1][1],A[i].alpha);
	
}


/******************Search for alphabet in Palette***********************/

AL Search_Alpha(int x,int y)
{
    AL a;
	for(int i=0 ;i<28 ; i++){
		if((x>(A[i].vertices[0][0])) && (x<(A[i].vertices[1][0])) && (y>(A[i].vertices[0][1])) && (y<(A[i].vertices[1][1])))
		{
			return A[i];
		}
	}

	a.alpha = 'a';
	return a;
}

/***********************************************************************/

void MouseC(int b, int s ,int x, int y)
{
	 AL a;
	 extern int Window_Done,FileNameCount;

	 if(b == GLUT_LEFT_BUTTON && s == GLUT_DOWN)
	 {
		
		a = Search_Alpha(x,300-y);

		if(a.alpha == 25){
			Name_Of_File[FileNameCount++] = '\0';
			Perform_Operation(Name_Of_File);
		}
		
		
		else if(a.alpha == 26){
			Window_Done = 1;
			glutDestroyWindow(Win_Code);
		}
   
		else
			Name_Of_File[FileNameCount++] = a.alpha;
		
		glRasterPos2f(Xpos,Ypos);
		glutBitmapCharacter(font, a.alpha);
		glFlush();
		
		Xpos+=10;	
		
	 }

	 if(Xpos >= 150 && b == GLUT_LEFT_BUTTON){
		Window_Done = 1;
	 	glutDestroyWindow(Win_Code);
	 }
	 
	 if(Xpos >= 150 && b == GLUT_RIGHT_BUTTON){
		 Page_Over = 1;
	 }
	
	 if((RW_Mode == 4 || RW_Mode == 3 || RW_Mode == 5)  && b == GLUT_LEFT_BUTTON){
		Window_Done = 1;
	 	glutDestroyWindow(Win_Code);
	 }
	 
	 	 

}
		

void KeybC(unsigned char c,int x,int y)
{
	extern int FileNameCount;
		
	glRasterPos2f(Xpos,Ypos);
	glutBitmapCharacter(font, c-32);/*Print the alphabets*/
	glFlush();
	Name_Of_File[FileNameCount++] = c-32;		

	Xpos+=10;
}


void Display_About()
{
	int xn = 10,yn = 250,i;	
	void *font =  GLUT_BITMAP_9_BY_15;

	glClearColor(0.75, 0.75, 0.45, 0.0);	
  	glClear(GL_COLOR_BUFFER_BIT);
  	glFlush();  

	/*******************************************************************************************/
	/*Draw the background for the display*/
	{
		float colorRed   = 0.3588;
		float colorGreen = 0.3190;
		float colorBlue  = 0.3247;
		int x1 = 0, y1 = 0, x2 = 300, y2 = 300;
		
		//glColor3f(0.3921,0.6313,0.9091);Initally used color -> a blue shade
		
		for(; y1 != y2 ;){
			glColor3f( colorRed += 0.003 ,  colorGreen += 0.002 , colorBlue += 0.002);
			glBegin(GL_LINES);
		  	 glVertex2i(x1,y1);
		   	 glVertex2i(x2,y1++);
		  	glEnd();
			glFlush();
			//Sleep(100);
		
		}
	}
	/*******************************************************************************************/
	
	xn  = 200;
	glColor3f(0.0,0.0,1.0);
	glRasterPos2f(xn+=10,yn);

	char About[] = "GOGH PAINT";

	glRasterPos2f(90,270);
	for(i = 0;i < (signed)strlen(About); i++){
		glutBitmapCharacter(font, About[i]);
		
	}
	char About1[] = "DEVELOPED BY MUKUND Y.K";

	glRasterPos2f(50,220);
	for(i = 0;i < (signed)strlen(About1); i++){
		glutBitmapCharacter(font, About1[i]);
		
	}

	char About2[] = "B  N  M  I  T";
	
	glRasterPos2f(80,195);
	for(i = 0;i < (signed)strlen(About2); i++){
		glutBitmapCharacter(font, About2[i]);
		
	}
	char About3[] = "Email Id : ykmukund@gmail.com";
	
	glRasterPos2f(20,180);
	for(i = 0;i < (signed)strlen(About3); i++){
		glutBitmapCharacter(font, About3[i]);
		
	}
	
	glColor3f(0.5,0.5,0.5);
	glRectf(100,65,150,115);
	glFlush();

	glColor3f(0.0,0.0,0.5);
	glRectf(105,70,145,110);
	glFlush();

	glColor3f(1.0,1.0,0.0);
	char About4[] = "OK";
	
	glRasterPos2f(120,80);
	for(i = 0;i < (signed)strlen(About4); i++){
		glutBitmapCharacter(font, About4[i]);
		
	}

}

void Display_Credits()
{
	int xn = 10,yn = 150,i;	
	void *font =  GLUT_BITMAP_9_BY_15;

	glClearColor(0.75, 0.75, 0.45, 0.0);	
  	glClear(GL_COLOR_BUFFER_BIT);
  	glFlush();  
	
	/*******************************************************************************************/
	/*Draw the background for the display*/
	{
		float colorRed   = 0.4588;
		float colorGreen = 0.6190;
		float colorBlue  = 0.5247;
		int x1 = 0, y1 = 0, x2 = 300, y2 = 300;
		
		//glColor3f(0.3921,0.6313,0.9091);Initally used color -> a blue shade
		
		for(; y1 != y2 ;){
			glColor3f( colorRed += 0.003 ,  colorGreen += 0.002 , colorBlue += 0.002);
			glBegin(GL_LINES);
		  	 glVertex2i(x1,y1);
		   	 glVertex2i(x2,y1++);
		  	glEnd();
			glFlush();
			//Sleep(100);
		
		}
	}
	/*******************************************************************************************/
	
	glColor3f(1.0,1.0,1.0);
	glRasterPos2f(xn+=10,yn);
	
	char Credits[] = "*************";

	for(i = 0;i < (signed)strlen(Credits); i++){
		glutBitmapCharacter(font, Credits[i]);
		glRasterPos2f(xn+=10,yn);
	}
	

}


void display(void)
{
  glClearColor(0.75, 0.75, 0.45, 0.0);	
  glClear(GL_COLOR_BUFFER_BIT);
  glFlush();  
  
  if(RW_Mode == 3){
	  glMatrixMode(GL_PROJECTION);
  	  glLoadIdentity();		
  	  gluOrtho2D(0.0,500,0.0,500);	
  }else if(RW_Mode == 1 || RW_Mode == 2){
          glMatrixMode(GL_PROJECTION);
  	  glLoadIdentity();		
  	  gluOrtho2D(0.0,300,0.0,300);  		
	  Alphabet_Palette_Draw();
 }else if(RW_Mode == 4){
	  glMatrixMode(GL_PROJECTION);
  	  glLoadIdentity();		
  	  gluOrtho2D(0.0,300,0.0,300);	
	  Display_About();
 }else if(RW_Mode == 5){
	  glMatrixMode(GL_PROJECTION);
  	  glLoadIdentity();		
  	  gluOrtho2D(0.0,300,0.0,300);	
	  Display_Credits();	

 }////////////////////hahahahha show error!

}	  


void File_Operations(int Mode)/*Indicates open of write file*/
{

     char win_name[25];  	

     if(Mode == 1){
	strcpy(win_name,"  SAVE");
	RW_Mode = 1;
     }else if(Mode == 2){
	strcpy(win_name,"  OPEN");
	RW_Mode = 2;	
     }else if(Mode == 3){
		 FreeConsole();
		 system(".\\help\\Help.pdf");/* Open the help pdf file */
		 FreeConsole();
		 return;	
     }else if(Mode == 4){
	strcpy(win_name,"        ABOUT");
	RW_Mode = 4;
     }else if(Mode == 5){
	strcpy(win_name,"       CREDITS");
	RW_Mode = 5;	 	
     }		
	
    /*Spaces given above so that the name appears in the middle of title bar*/	  	 		
  	
     glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
     
	 
	 /* DEFINE GLOBAL CONSTANTS FOR ALL THESE(ie save,open,etc modes */
	 if(RW_Mode == 3){
		glutInitWindowSize(500, 500);
		glutInitWindowPosition(0,0);
	 }else{
		glutInitWindowSize(300, 300);
        glutInitWindowPosition(310,310);
	 }	
	 Win_Code = glutCreateWindow(win_name);
     glutMouseFunc(MouseC);
	 glutKeyboardFunc(KeybC);
     glutDisplayFunc(display);	  
  
    /***************COOOOOOOL!! from the forum*************************/
	//HWND hThisWnd = FindWindow( "GLUT", win_name );
	//if( hThisWnd )
	//{
	//	LONG lStyle = GetWindowLong( hThisWnd, GWL_STYLE );
	//	SetWindowLong( hThisWnd, GWL_STYLE, lStyle & 
	//		(~(WS_MAXIMIZEBOX|WS_MINIMIZEBOX|WS_SYSMENU ) ) );
	//}
    /******************Remove Close,Min option*************************/
 	
     glutMainLoop();	
	

}







