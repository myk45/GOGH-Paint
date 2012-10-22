
#include<stdio.h>
#include"Two_D.cpp"
#include<windows.h>
#include"Bitmap.cpp"
#include<string.h>
#include"File.cpp"
#include"Three_D.cpp"
#include"Maths.cpp"
#include<math.h>
#include"Loading.cpp"
#include<gl/glut.h>

void Draw_Highlighted_Boxes(int n,int size);

struct COLOR_PALETTE
{
	float colors[3];
	int vertices[2][2];	/*Used to define the color palette*/
};

COLOR_PALETTE COL[18];

struct MAIN_MODE
{
	int mode;			/*Used to define the basic 4 modes*/
	int vertices[2][2];
	char mode_name;
}MAIN_MOD[4];


struct SUB_MODE
{
	int mode;			/*Used to define the sub mode palette*/
	int vertices[2][2];
	char mode_name[100]; /*Name of mode ie bitmap to be loaded*/
}SUB_MOD[20];


struct FILE_PALETTE
{
	int mode;			/*File Open etc*/
	int vertices[2][2];
	char name[100];
}FILE_OPT[5];
	
	
int entry = 1;				/*Global variable for controlling entry in mode*/	

/**********Function Prototypes*********/
void Two_Dimension(int x,int y);		
void Three_Dimension(int x,int y);		
void Animation(int x,int y);				
void Bitmap(int x,int y);
MAIN_MODE Main_Mode_Search(int x,int y);	
void Menu_Handles();
void Cursor_Handles();
/**************************************/



unsigned char palette_Left[90000]    = {0};
unsigned char palette_Top[91200]     = {0} ;
unsigned char palette_Right[91800]   = {0};
unsigned char palette_Bottom[148800] = {0};

int xx = 0,
	yy = 0,
	TWO_D_MODE     = 0,
	THREE_D_MODE   = 0,
	ANIMATION_MODE = 0,
	BITMAP_MODE    = 0,
	CREATE         = 1;	
    
float r,g,b;

char File_Opt_Name[5][100] = {"SAVE",
							  "OPEN",
							  "HELP",
							  "ABOUT",
							  "CREDITS"};		

/*Array for holding the Colors*/
float arr[] = {		 1	,1	,1     ,
			 0.7529 ,0.7529 ,0.7529,
			 0.2509 ,0.5019 ,0.7019,
			 0.5019 ,0.7019 ,0.2019,
			 1	,0.2509 ,0.6210,
			 1	,0	,0     ,
			 1	,0.5019 ,0.7529,
			 0.5019 ,0.5019 ,0.7529,
			 1	,0	,0.5019,
			 0	,0	,1     ,
			 0	,0	,0     ,
			 0	,1	,0     ,
			 0.5019 ,0.2509 ,0.2509,
			 0.5372 ,0.8784 ,0.8705,
			 0	,0.5019 ,0     , 
			 0.4588 ,0.4666 ,0.8   ,
			 0.8039 ,0.6117 ,0.6117,
			 0.5019 ,0	,0.5019,
			 0.5	,0	,0.5   ,
			 1	,0	,1	
	    };

char fmodes[20][100] = {".\\bit\\lines.bmp",
						".\\bit\\rectangle.bmp",
						".\\bit\\circle.bmp",
						".\\bit\\freehand.bmp",
						".\\bit\\polygon.bmp",
						".\\bit\\erasor.bmp",
						".\\bit\\spray.bmp",
						".\\bit\\alpha.bmp",
						".\\bit\\spiral.bmp",
						".\\bit\\bubbles.bmp",
						".\\bit\\templates.bmp",
						".\\bit\\pick.bmp",
						".\\bit\\rotate.bmp",
						".\\bit\\scale.bmp",
						".\\bit\\fill.bmp",
						".\\bit\\cut.bmp",
						".\\bit\\rotimage.bmp",
						".\\bit\\point.bmp",
						".\\bit\\colrect.bmp",
						".\\bit\\ellipse.bmp"};

char cmodes[9][100] = {".\\bit\\cube.bmp",
					   ".\\bit\\sphere.bmp",
					   ".\\bit\\cone.bmp",
					   ".\\bit\\torus.bmp",
					   ".\\bit\\empty.bmp",
					   ".\\bit\\rotobj.bmp",
					   ".\\bit\\selobj.bmp",
					   ".\\bit\\scaleobj.bmp",
					   ".\\bit\\rotimage3d.bmp"};
					  
			
char amodes[2][100] = {".\\bit\\man.bmp",
						".\\bit\\dog.bmp"};	


char bmodes[4][100] = {".\\bit\\log.bmp",
					   ".\\bit\\sin.bmp",
					   ".\\bit\\cos.bmp",
					   ".\\bit\\tan.bmp"};


/***********************************************************************************************/

/*Draw the small Squares where the palettes are displayed*/
void Draw_SQ(int x1,int y1,int x2,int y2,int type)
{
	int width = 6;/*Width of the background*/
	
	glBegin(GL_QUADS);
	  glVertex2i(x1,y1);
	  glVertex2i(x1,y2);
	  glVertex2i(x2,y2);	
	  glVertex2i(x2,y1);
	glEnd();
	glFlush();
	
	if(type == 1){
		width = 4;
		glColor3f(0.875,0.875,0.875);/*background*/	
	}else{
		glColor3f(0.0,0.9254,0.7921);
	}

	glBegin(GL_QUADS);
	 glVertex2i(x1,y1);
	 glVertex2i(x1,y1+width);
	 glVertex2i(x2,y1+width);	
	 glVertex2i(x2,y1);
	glEnd();
	glFlush();

	glBegin(GL_QUADS);
	 glVertex2i(x1,y1);
	 glVertex2i(x1,y2);
	 glVertex2i(x1+width,y2);	
	 glVertex2i(x1+width,y1);
	glEnd();
	glFlush();

	glBegin(GL_QUADS);
	 glVertex2i(x2-width,y1);
	 glVertex2i(x2-width,y2);
	 glVertex2i(x2,y2);	
	 glVertex2i(x2,y1);
	glEnd();
	glFlush();

	glBegin(GL_QUADS);
	 glVertex2i(x1,y2-width);
	 glVertex2i(x1,y2);
	 glVertex2i(x2,y2);	
	 glVertex2i(x2,y2-width);
	glEnd();
	glFlush();
	
	if(type == 1){
		width = 4;
		glLineWidth(2);
		glColor3f(0.0,0.0,0.0);
		glBegin(GL_LINE_LOOP);
		 glVertex2i(x1,y1);
	 	 glVertex2i(x1,y2);
	 	 glVertex2i(x2,y2);	
	 	 glVertex2i(x2,y1);
		glEnd();
		glFlush();
	 
	        glBegin(GL_LINE_LOOP);
		 glVertex2i(x1+width,y1+width);
	 	 glVertex2i(x1+width,y2-width);
	 	 glVertex2i(x2-width,y2-width);	
	 	glVertex2i(x2-width,y1+width);
		glEnd();
		glFlush();
	}		
	
}

/***********COLOR PALETTE************************************************/

/*Perform Linear Search for finding the color*/
COLOR_PALETTE Color_Search(int x,int y)
{
	COLOR_PALETTE c;int i;

	for(i=0 ;i<18 ; i++){
		if(x>COL[i].vertices[0][0] && x<COL[i].vertices[1][0] && y>COL[i].vertices[0][1] && y<COL[i].vertices[1][1])
		{
			//printf("\nWOho");
			return COL[i];
		}
	}	
	
	c.colors[0] = c.colors[1] = c.colors[2] = 0;
	
	return c;
}

void Color_Palette_Draw()
{
	int i,c = 0,size = 30;
	xx = 45;
	yy = 25;

	for(i = 0 ; i < 18; i++){
		COL[i].colors[0] = arr[c++];
		COL[i].colors[1] = arr[c++];
		COL[i].colors[2] = arr[c++];
		
		COL[i].vertices[0][0] = xx;
		COL[i].vertices[0][1] = yy;
		
		xx += size;
		yy += size;

		COL[i].vertices[1][0] = xx;
		COL[i].vertices[1][1] = yy;

		yy -= size;

		if(xx >= 575){
		 yy += size;
		 xx  = 50;	
		}  
	}

	for(i = 0 ; i < 18 ; i++){
		glColor3f(COL[i].colors[0] , COL[i].colors[1] , COL[i].colors[2]);
		Draw_SQ(COL[i].vertices[0][0],COL[i].vertices[0][1],COL[i].vertices[1][0],COL[i].vertices[1][1],1);
	}
}


/****************************************************************************/


/***************MAIN MODE PALETTE********************************************/

/*Perform Linear Search for finding the Sub Mode*/
MAIN_MODE Main_Mode_Search(int x,int y)
{
	MAIN_MODE k;

	for(int i=0 ;i<4 ; i++){
		if((x>MAIN_MOD[i].vertices[0][0]) && (x<MAIN_MOD[i].vertices[1][0]) && (y>MAIN_MOD[i].vertices[0][1]) && (y<MAIN_MOD[i].vertices[1][1]))
		{
			return MAIN_MOD[i];
		}
	}	

	k.mode = 100;
	return k;
}


void Main_Mode_Palette_Draw()
{
	int k = 1;
	int i;
	extern int Win_Width , Win_Height;

	for(i=0 ;i<4 ; i++)
		MAIN_MOD[i].mode = k++;

	/*Mode 1:2D
	 *Mode 2:3D
	 *Mode 3:Animation
	 *Mode 4:Bitmap
	 */	
	
		
		MAIN_MOD[0].vertices[0][0] = 0;
		MAIN_MOD[0].vertices[0][1] = 0;
		MAIN_MOD[0].vertices[1][0] = 400;
		MAIN_MOD[0].vertices[1][1] = 300;
		
		MAIN_MOD[1].vertices[0][0] = 0;
		MAIN_MOD[1].vertices[0][1] = 300;
		MAIN_MOD[1].vertices[1][0] = 400;
		MAIN_MOD[1].vertices[1][1] = 600;

		MAIN_MOD[2].vertices[0][0] = 400;
		MAIN_MOD[2].vertices[0][1] = 300;
		MAIN_MOD[2].vertices[1][0] = 800;
		MAIN_MOD[2].vertices[1][1] = 600;

		MAIN_MOD[3].vertices[0][0] = 400;
		MAIN_MOD[3].vertices[0][1] = 0;
		MAIN_MOD[3].vertices[1][0] = 800;
		MAIN_MOD[3].vertices[1][1] = 300;

		
		glViewport(0, 0, Win_Width/2, Win_Height/2);
		Open_Bitmap(".\\bit\\TwoD.bmp");
		
		glViewport(0, Win_Height/2, Win_Width/2, Win_Height/2);
		Open_Bitmap(".\\bit\\ThreeD.bmp");
	
		
		glViewport(Win_Width/2, Win_Height/2,Win_Width/2, Win_Height/2);
		Open_Bitmap(".\\bit\\Animation.bmp");
	
		
		glViewport(Win_Width/2, 0, Win_Width/2, Win_Height/2);
		Open_Bitmap(".\\bit\\Math.bmp");

		glViewport(0.0, 0.0, Win_Width, Win_Height);

}


/***************MAIN MODE PALETTE********************************************/


/***************SUB MODE PALETTE*********************************************/

SUB_MODE Sub_Mode_Search(int x,int y,int n)
{
	SUB_MODE s;	

	for(int i=0 ;i<n ; i++){
		if(x>SUB_MOD[i].vertices[0][0] && x<SUB_MOD[i].vertices[1][0] && y>SUB_MOD[i].vertices[0][1] && y<SUB_MOD[i].vertices[1][1])
			    
				return SUB_MOD[i];
			
	}
	s.mode = 100;/*If not matched*/
	
	return s;
}	


/*n is the no of modes in the sub mode and size is the size of the Sq*/
void Sub_Mode_Palette_Draw(int n,int size,int mod)
{
	int xd = 5;
	int yd = 100;
	yy = yd+size;
	xx = 5;
	int i;
	extern int Win_Width,Win_Height;

	
	for(i = 0 ; i < n; i++){
		SUB_MOD[i].vertices[0][0] = xx;
		SUB_MOD[i].vertices[0][1] = yy;
		
		if(mod == 1)
			strcpy(SUB_MOD[i].mode_name,fmodes[i]);
	
		else if(mod == 2)
			strcpy(SUB_MOD[i].mode_name,cmodes[i]);

		else if(mod == 3)
			strcpy(SUB_MOD[i].mode_name,amodes[i]);

		xx += size;
		yy += size;

		SUB_MOD[i].vertices[1][0] = xx;
		SUB_MOD[i].vertices[1][1] = yy;

		xx -= size;
		yy += 5;
		

		if(yy >= 525){
			xx = Win_Width - (size + 5);
			yy = 100 + size;
		}

		SUB_MOD[i].mode = i+1;	
		
	}

	for(i = 0 ; i < n ; i++){
		if(yd >= 500){
			yd = 100;			
			xd = Win_Width - (size + 5);
		}	
		glViewport(xd,yd+=size,size,size);
		Open_Bitmap(SUB_MOD[i].mode_name);
	 	yd += 5;
	}	
	/*Load the volume icon*/
	glViewport(0,25,size,size);
	Open_Bitmap(".\\bit\\vol_off.bmp");

	/*Load the theme change icon*/
	glViewport((Win_Width - size ),50,size,size);
	Open_Bitmap(".\\bit\\theme.bmp");

	glViewport(0,0,Win_Width,Win_Height);
	
	/*Draw the small area where the help info is displayed*/
	{
		float colorRed   = 0.4588;
		float colorGreen = 0.6190;
		float colorBlue  = 0.8247;
		int x1 = 0, y1 = 0, x2 = Win_Width, y2 = 25;
		
		//glColor3f(0.3921,0.6313,0.9091);Initally used color -> a blue shade
		
		for(; y1 != y2 ;){
			glColor3f( colorRed += 0.02 ,  colorGreen += 0.02 , colorBlue += 0.02);
			glBegin(GL_LINES);
		  	 glVertex2i(x1,y1);
		   	glVertex2i(x2,y1++);
		  	 glEnd();
			glFlush();
			
		
		}
	}
	/*This above toolbar is generated as a mumber of lines woth different colors*/
	 	
	/************************************************************/
	/*Load different themes here instead of drawing every button*/
	/*Open_Bitmap("try.bmp");*/
	/************************************************************/
	
	/*Different Modes for different sub modes*/
}

/***************SUB MODE PALETTE*********************************************/

/***************FILE PALETTE*************************************************/

void File_Palette_Draw()
{
	int xx = 40;
	int yy = 570;
	int i;
	int k;

    	//void *font = GLUT_BITMAP_HELVETICA_18;
	void *font =  GLUT_BITMAP_TIMES_ROMAN_24;

	/*For the options*/
	//glColor3f(0.5, 0.89, 0.7);
	//glRectf(40, 560, 600 ,600);
	//glFlush();
	
	for(i = 0;i < 5;i++){
		FILE_OPT[i].vertices[0][0] = xx;
		FILE_OPT[i].vertices[0][1] = yy;

		strcpy(FILE_OPT[i].name,File_Opt_Name[i]);
		FILE_OPT[i].mode = i+1;

		xx += 80;
		yy += 25;
		
		FILE_OPT[i].vertices[1][0] = xx;
		FILE_OPT[i].vertices[1][1] = yy;

		yy -= 25;
		
	}
	xx = 30;
	glColor3f(0.0,0.0,1.0);
	
	for(i = 0;i < 5;i++){
		for(k = 0;k < (signed)strlen(FILE_OPT[i].name);k++){
			glRasterPos2f(xx += 15,570);
			glutBitmapCharacter(font,FILE_OPT[i].name[k]);
		}
	 xx += 20;
	}
}	


FILE_PALETTE File_Palette_Search(int x,int y)
{
	FILE_PALETTE f;

	

	for(int i=0 ;i<5 ; i++){
		if((x>FILE_OPT[i].vertices[0][0]) && (x<FILE_OPT[i].vertices[1][0]) && (y>FILE_OPT[i].vertices[0][1]) && (y<FILE_OPT[i].vertices[1][1]))
		{
			
			return FILE_OPT[i];
		}
	}	

	f.mode = 100;
	return f;
}

/***************FILE PALETTE*************************************************/

/***************Resolve Modes************************************************/
void Resolve_Modes(MAIN_MODE m,int x,int y)
{

	switch(m.mode){
		case 1:Two_Dimension(x,y);
			   break; 	
		case 2:Three_Dimension(x,y);
			   break;	
		case 3:Animation(x,y);
			   break;	
		case 4:Bitmap(x,y);
			   	
	}		   	
	
}

/***************Resolve Modes************************************************/

void Two_Dimension(int x,int y)
{
	SUB_MODE s;
	COLOR_PALETTE co;
	extern int Sel,Motion_Flag,Flag,done,w,Pal_Done,theme,Win_Width,Win_Height,Filled;
	extern unsigned char pixel_info[1440000];

	/*When the mode is enterted*/
	if(entry == 1)
	{
	   entry++;	
	   Flag = 0;
	
	   if(theme == 1){	
	    glClearColor(0.875,0.875,0.875,0.0);
	   	glClear(GL_COLOR_BUFFER_BIT);
	   }
	   else if(theme == 2){
		glClearColor(1.0,1.0,1.0,0.0);
	   	glClear(GL_COLOR_BUFFER_BIT);
	
	   }
	   else if(theme == 3){
		glClearColor(0.3843,0.4078,0.5019,0.0);
	   	glClear(GL_COLOR_BUFFER_BIT);
	
	   }	
	
	   glFlush();
	   Draw_Load_Box(1);/*This the one that says: Loading.Please Wait */	
	
	   Color_Palette_Draw();
	   Sub_Mode_Palette_Draw(20,35,1);/*20 modes and 25x25 sq 1 is 2D mode*/
	   File_Palette_Draw();	
	   Draw_Highlighted_Boxes(20,35);	
		
	   Draw_Load_Box(2);/*THis is the one that says:Done!*/       

	   /*For the eclosing boxes
	  {
		glColor3f(0.4588 , 0.4666 , 0.8 );
		glLineWidth(2);
		glBegin(GL_LINE_LOOP);
			glVertex2i(3,118);
			glVertex2i(3,525);
			glVertex2i(35,525);
			glVertex2i(35,118);
		glEnd();
		glFlush();
	
		glColor3f(0.4588 , 0.4666 , 0.8 );
		glLineWidth(2);
		glBegin(GL_LINE_LOOP);
			glVertex2i(740,118);
			glVertex2i(790,425);
			glVertex2i(638,425);
			glVertex2i(638,118);
		glEnd();
		glFlush();
	   }*/	
	
		
       if(theme == 1){
		glColor3f(0.9019,0.9411,1.0);/*BackGround*/
	   	Draw_SQ(45,55,752,568,1);
	   }
	   else if(theme == 2){
		glColor3f(1.0,1.0,1.0);/*BackGround*/
	   	Draw_SQ(45,55,752,568,1);
	   }	
	   else if(theme == 3){
		glColor3f(0.2901,0.3490,0.4627);/*BackGround*/
	   	Draw_SQ(45,55,752,568,1);	
	   }	
	   glFlush();
	
           theme++;

	   glReadPixels(0,0,800,600,GL_RGB, GL_UNSIGNED_BYTE,pixel_info);

	   glReadPixels(0,0,50,600,GL_RGB, GL_UNSIGNED_BYTE,palette_Left);
	   glReadPixels(0,0,800,62,GL_RGB, GL_UNSIGNED_BYTE,palette_Bottom);
	   glReadPixels(0,562,800,38,GL_RGB, GL_UNSIGNED_BYTE,palette_Top);
	   glReadPixels(749,0,51,600,GL_RGB, GL_UNSIGNED_BYTE,palette_Right);		
	    
	   glRasterPos2f(0,0);	
	   glDrawPixels(Win_Width,Win_Height,GL_RGB, GL_UNSIGNED_BYTE,pixel_info);
	   glFlush();

	   Pal_Done = 1;
		 
	   
	}	
	
	if(Sel == 1)
	{
	   s  = Sub_Mode_Search(x,y,20);/*Current Mode(20 modes here)*/
	   
	   if( y < 60){
			co = Color_Search(x,y);  /*Current Color*/
			glColor3f(co.colors[0],co.colors[1],co.colors[2]);
			r = co.colors[0]; 
			g = co.colors[1]; 
			b = co.colors[2];	
	   }

	   //r = co.colors[0] * 255; 
	   //g = co.colors[1] * 255; 
	   //b = co.colors[2] * 255;	

	   if(s.mode <= 20){
		 Flag = 0;
		 TWO_D_MODE = s.mode;
	   }

	   Menu_Handles();
	   Cursor_Handles();
	}

	else
	{
	  
	 /*For the modes not requiring Mouse Motion Callback*/  
	 if(Motion_Flag == 0)
	 {	
	   switch(TWO_D_MODE)
	   {	     	
		
		 case 3:if(Filled == 0)
					Draw_Circ(x,y);
				else if(Filled == 1)
					Draw_Ring(x,y); 
				else
					Draw_Filled_Circ(x,y);
				glFlush();
			    break;	
		
		 case 5:Draw_Polygon(x,y);
		    	glFlush();
			    break;

		 case 8:Display_Txt(x,y);
				glFlush();
			    break;
		 
		 case 9:Draw_Spiral(x,y);
				glFlush();
				break;
		
		case 11:Open_Template(x,y);			
				   glFlush();	
				   break;

		case 12:Pick_Color(x,y);
				glFlush();
				break;
		
		case 13:Rotate_Shape(x,y);			    
				break;

		case 14:Scale_Shape(x,y);
				break;

		case 16:Cut_Image(x,y);
				break;
		
		case 17:Rotate_Image(x,y);
				break;
		
		case 18:Draw_Point(x,y);
				break;
		
		case 19:Draw_Colored_Rectangle(x,y);
				break;
			   
		case 20:if(Filled == 0)
					Draw_Ellipse(x,y);
				else
					Draw_Filled_Ellipse(x,y);
				glFlush();
			    break; 	
			
		}
	 }

	   else
	   {
		 switch(TWO_D_MODE)
		 {	
		   case 1://r = ~r;
			  //g = ~g;
			  //b = ~b;
			  //glColor3f(r/255.0 , g/255.0 , b/255.0);
			  Draw_Lines(x,y);
		     	  glFlush();
		 	      break;	 
		  
		  case 2:if(Filled == 0)
					 Draw_Rectangle(x,y);
				 else
					 Draw_Filled_Rectangle(x,y);
				 glFlush();
			     break;			 

	  	   case 4:Draw_Points(x,y);
			      glFlush();
				  break;
			
		   case 6:Erasor(x,y);
			      glFlush();
			      break;	
	   
		   case 7:Spray_Points(x,y);
			      glFlush();
			      break;

		   case 10:if(Filled == 0)
					Draw_Circ(x,y);
				  else
					Draw_Filled_Circ(x,y);
				  glFlush();	

		   case 15:Draw_Weird_Things(x,y);
                   glFlush();
				   break;

		   case 20:if(Filled == 0)
					Draw_Ellipse(x,y);
				   else
					Draw_Filled_Ellipse(x,y);
				   glFlush();
			       break; 	
			
		 }
	   }
		
		

				   
	  
	}

}

/**************************************************************************/

/**************THREE DIMENSION*********************************************/
void Three_Dimension(int x,int y)
{
	SUB_MODE s;
	COLOR_PALETTE co;
	
	extern int Sel,Motion_Flag,Flag,X,Y,Win_Width,Win_Height,theme;
	extern unsigned char pixel_info[921600];

	/*When the mode is enterted*/
	if(entry == 1)
	{
	   entry++;	
	   Flag = 0;

	   if(theme == 1){	
	    glClearColor(1.0,1.0,1.0,0.0);
	   	glClear(GL_COLOR_BUFFER_BIT);
	   }
	   else if(theme == 2){
		glClearColor(1.0,1.0,1.0,0.0);
	   	glClear(GL_COLOR_BUFFER_BIT);
	
	   }
	   else if(theme == 3){
		glClearColor(1.0,1.0,1.0,0.0);
	   	glClear(GL_COLOR_BUFFER_BIT);
	
	   }	

	   Draw_Load_Box(1);/*This the one that says: Loading.Please Wait */	   

	   Color_Palette_Draw();
	   Sub_Mode_Palette_Draw(9,35,2);/*10 modes and 50x50 sq 2 is 3Dmode*/
	   File_Palette_Draw();	
	    
	
	   Draw_Load_Box(2);/*THis is the one that says:Done!*/ 
	  
	   
	   if(theme == 1){
		glColor3f(1.0,1.0,1.0);/*BackGround*/
	   	Draw_SQ(45,55,752,568,1);
	   }
	   else if(theme == 2){
		glColor3f(1.0,1.0,1.0);/*BackGround*/
	   	Draw_SQ(45,55,752,568,1);
	   }	
	   else if(theme == 3){
		glColor3f(1.0,1.0,1.0);/*BackGround*/
	   	Draw_SQ(45,55,752,568,1);	
	   }	
	   glFlush();
	
           theme++;

	   glViewport(40,410,30,30);	
	   glReadPixels(0,0,Win_Width,Win_Height,GL_RGB, GL_UNSIGNED_BYTE,pixel_info);/*Take the screenshot*/
	    
	   glReadPixels(0,0,50,600,GL_RGB, GL_UNSIGNED_BYTE,palette_Left);
	   glReadPixels(0,0,800,62,GL_RGB, GL_UNSIGNED_BYTE,palette_Bottom);
	   glReadPixels(0,562,800,38,GL_RGB, GL_UNSIGNED_BYTE,palette_Top);
	   glReadPixels(749,0,51,600,GL_RGB, GL_UNSIGNED_BYTE,palette_Right);

	   glViewport(0,0,Win_Width,Win_Height);	
		
	   Initialise();/*Initialise all the structures*/	

	   X = 0;
	   Y = 0;
	   THREE_D_MODE = 0;
	
	   glEnable(GL_BLEND);
	   glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	if(Sel == 1)
	{
	   s  = Sub_Mode_Search(x,y,9);/*Current Mode(9 modes here)*/
	   if(y < 50){	
	   	co = Color_Search(x,y);  /*Current Color*/
	    glColor3f(co.colors[0],co.colors[1],co.colors[2]);

	    r = co.colors[0];
	    g = co.colors[1];
	    b = co.colors[2];
	  }   
	
	   if(s.mode <= 10){
		 Flag = 0;
		 THREE_D_MODE = s.mode;
	   }

	  
	}

	else
	{
		if(Motion_Flag == 0){
			switch(THREE_D_MODE)
			{	
		 	 
             case 1:Draw_Cube(x,y);
				glFlush();
				break;

			 case 2:Draw_Sphere(x,y);
				glFlush();
				break;  	

			case 3:Draw_Cone(x,y);
			       glFlush();
			       break;	
			
			case 4:Draw_Torus(x,y);
			       glFlush();
			       break;	 
			
			 case 6:Rotate_Obj();
				   glFlush();
				   break;
		
			case 7:Select_Object(x,y);
				  glFlush();
				  break;

			case 8:Scale_Obj();
			       glFlush();
			       break; 	
			
			}	
		}
		else{
			switch(THREE_D_MODE)
			{	
		
			 case 6:Rotate_Obj();
				glFlush();
				break;
			
			
			 
			case 8:Scale_Obj();
			       glFlush();
			       break; 			
			
			case 9:Rotate_Scene(x,y);
					glFlush();
			}	
		}
	}

}

/**************************************************************************/	

/**************ANIMATION***************************************************/	
void Animation(int x,int y)		
{
	SUB_MODE s;

	extern int Sel,Motion_Flag,Flag;
	extern unsigned char pixel_info[921600];

	/*When the mode is enterted*/
	if(entry == 1)
	{
	   entry++;	
	   Flag = 0;
	   glClearColor(1.0,1.0,1.0,0.0);
	   glClear(GL_COLOR_BUFFER_BIT);
	   
	   Sub_Mode_Palette_Draw(2,50,3);/*10 modes and 50x50 sq '3' is Animation mode*/
	   File_Palette_Draw();	
	   
	   glColor3f(1.0,1.0,1.0);/*BackGround*/
	   Draw_SQ(50,55,752,568,1);
	   glReadPixels(0,0,800,600,GL_RGB, GL_UNSIGNED_BYTE,pixel_info);/*Full Screen*/

	}

	if(Sel == 1)
	{
	   s  = Sub_Mode_Search(x,y,2);/*Current Mode(2 modes here)*/

	   if(s.mode <= 2){
		 Flag = 0;
		 ANIMATION_MODE = s.mode;
	   }
	
	}

}	


/**************************************************************************/


/*****************BITMAP***************************************************/
void Bitmap(int x,int y)
{	

	SUB_MODE s;
	
	
	extern int Sel,Motion_Flag,Flag;
	extern unsigned char pixel_info[921600];

	/*When the mode is enterted*/
	if(entry == 1)
	{
	   entry++;	
	   Flag = 0;
	   glClearColor(1.0,1.0,1.0,0.0);
	   glClear(GL_COLOR_BUFFER_BIT);
	   
	   Color_Palette_Draw();
	   Sub_Mode_Palette_Draw(5,35,1);/*10 modes and 25x25 sq 1 is 2D mode*/
	   File_Palette_Draw();	
	   
	   glColor3f(1.0,1.0,1.0);/*BackGround*/
	   Draw_SQ(50,55,752,568,1);
	   glReadPixels(0,0,800,600,GL_RGB, GL_UNSIGNED_BYTE,pixel_info);/*Full Screen*/
	}
	
	if(Sel == 1)
	{
	   s  = Sub_Mode_Search(x,y,10);/*Current Mode(10 modes here)*/
	   // f  = File_Palette_Search(x,y);/*For File Operations*/
	  
	

	   if(s.mode <= 10){
		 Flag = 0;
		 BITMAP_MODE = s.mode;
	   }

	   
	}
		   	

}

/****************************************************************************************/
