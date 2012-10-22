// Paint_Main.cpp : Defines the entry point for the console application.
//

// Paint_Main.cpp : Defines the entry point for the console application.
//





#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include"Animation.cpp"
#include"Palette.cpp"
#include"Details.cpp"
#include<gl/glut.h>

#define CLEAR 0
#define FILL  1 

/***********Function Prototypes*********************/
/***************************************************/
void Mouse_Mot(int x,int y);
void Mouse(int button,int state,int x,int y);
void Keyb(unsigned char c,int x,int y);
void Idle(void);
void Enter_Window(void);
void Sub_Mode_Palette_Draw(int n,int size,int mod);
void Draw_Palettes(void);
void Draw_Circle(int centreX,int centreY,int rad);
void Clear_Region(int region,int mode);
void Menu_Handles(void);
void Thickness(int thickness);
void Cursor_Handles(void);
void Display(void);
void Begin_Animate(void);
void Menu_Options(int opt);
void Cursor_Handles(void);
void Thickness(int thickness);
void Menu_Options(int opt);
void Mouse_Mot(int x,int y);
void Pass_Mouse(int x,int y);
void Clear_Region(int region,int mode);
void Begin_Animate1(void);
void Begin_Animate2(void);
void Begin_Animate3(void);
void Begin_Animate(void);
void Display_Info(void);
void Special_Keys(int , int , int);
void Print_Coords(int , int );
void Fin(void);
/********************************************************************************************/
/********************************************************************************************/

/* Linked list implementation for the undo Operation */
struct Undo{
	unsigned char *pixel_data;/* This stores the pixel data */
	struct Undo *ptr;         /* This is the pointer to the next node */
	int op_num;				  /* A number indicating the operation number */
};

struct Undo *TOP    = NULL;   /* Pointer to the top of the list ie the most recent opn */
struct Undo *BOTTOM = NULL;   /* Pointer to the bottom of the list */

/******************************************************************************************/
//enum M{NO_MODE,FREE_ARC,FREE_RECT,ANIM}MODE;

MAIN_MODE m;


int X,
	Y,
	w,
	Flag = 0,
	Sel  = 0,
	done = 0,
	Motion_Flag  = 0,
	File_Opt_Sel = 0,
	Mouse_PositionX,
	Mouse_PositionY,
	reshape,
	Window_Done = 0,
	Read_Op     = 0,//Shows that a file is read
	Xt,
	Yt,
	Rotate_Angle       = 0,
	Point_Count        = 0,
	Win_Height         = 600,
	Win_Width          = 800,
	Music              = 0,
	Cur_Song           = 0,
	BEGIN_WINDOW       = 0,
	Rot_FlagX          = 0,
	Rot_FlagY          = 0,
	Rot_FlagZ          = 0,
	Pal_Done	       = 0,
	Ang			       = 0,
	cur			       = -1,/* Used for the beginning window */
	i                  = 0,
	rad			       = 0,/* For the circle used in the Two_D */
	theme		       = 1,
    template_no        = 0,/* For the filenames */
	Image_Rot	       = 0,/* The angle by which the image has to be rotated */
	Image_Rotate_Flag  = 0,/* Flag for checking the case of image rotation*/
	Cur_Text_Flag	   = 0,/* Flag for the info display*/		
	Menu_Done		   = 0,/* Flag for setting different Sub Menus */
	Erasor_Size		   = 10,/* Size of the erasor is initially 10 */
	Spray_Size		   = 20,/* Size of the spray is initially 20 */
	Undo_Op_Count	   = 0,/* This is necessary for the Undo Operation */	
	Increase_Flag      = 0,/* This is used in 3D for scaling the objects */
	Mouse_Click_Spot   = 0,/* Used in 3D mode */
	View			   = 0,/* Used in 3D mode */
	Filled			   = 0,/* Used in 2D mode for Filled/Unfilled shape */
	FileNameCount    = 0;/* Used for file operations */

void *text_font = GLUT_BITMAP_HELVETICA_12;

/*Random value 2*/
	int thickness_menu = 2;
	int point_size     = 2;
	int erasor_size    = 2;
	int spray_size	   = 2;
	int stipple		   = 2;
	int no_options	   = 2;
	int text_mode	   = 2;

int array[10]={0,0, 100, 100 , 150 ,150 ,200, 200};

float Scale_Factor = 1.0;

char *mode_name1 = "TWO_DIMENSION";
char *mode_name2 = "THREE_DIMENSION";
char *mode_name3 = "ANIMATION";
char *mode_name4 = "MATH";

wchar_t point_on[] = L".//sounds//haha.wav";

/* Array for storing the "screenshot" */
unsigned char pixel_info[1440000] = {0};/*Store pixel data for 640xWin_Height Pixels*/


/* The Wallpapers */
char wallpaper[10][100] = {".\\wallpapers\\wall1.bmp",
						   ".\\wallpapers\\wall2.bmp",
						   ".\\wallpapers\\wall3.bmp",
						   ".\\wallpapers\\wall1.bmp",
						   ".\\wallpapers\\wall1.bmp",
						   ".\\wallpapers\\wall1.bmp",
						   ".\\wallpapers\\wall1.bmp",
						   ".\\wallpapers\\wall1.bmp",
						   ".\\wallpapers\\wall1.bmp",
						   ".\\wallpapers\\wall1.bmp",};
	
/**********************************************************************************/
/**********************************************************************************/

void Display()
{
	printf("\nENTERED DISPLAY\n");

	if(BEGIN_WINDOW == 0)
		Enter_Window();		

	else if(done == 0){
		glClearColor(1.0,1.0,1.0,0.0);
		glClear(GL_COLOR_BUFFER_BIT);
		glColor3f(1.0,0.0,0.0);
		
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0.0,Win_Width,0.0,Win_Height,-500,500);

		Main_Mode_Palette_Draw();
		glFlush();
	}
	/*This is made to ensure that the main mode palette is
	 *drawn only when the first time the window is created 
	 *and whenever the user wishes to go back to the main 
	 *mode to select options again
     */

	else if(Window_Done == 1){
		glClearColor(1.0,1.0,1.0,0.0);
		glClear(GL_COLOR_BUFFER_BIT);
		glColor3f(1.0,0.0,0.0);

		glRasterPos2f(0,0);
		glDrawPixels(Win_Width,Win_Height,GL_RGB, GL_UNSIGNED_BYTE,pixel_info);
		glFlush();
		
		Window_Done = 0;
	}

	else if(Read_Op == 1){
			glViewport(0,0,800,600);
			Read_Op = 0;
			Open_Bitmap(full_filename);/*Open the file*/
			glViewport(0, 0, Win_Width, Win_Height);
	}
}


void Draw_Palettes()
{

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0 ,800, 0, 600, -500, 500);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glRasterPos2f(0,0);
	glDrawPixels(50,Win_Height,GL_RGB, GL_UNSIGNED_BYTE,palette_Left);
	glFlush();

	glRasterPos2f(0,0);
	glDrawPixels(Win_Width,62,GL_RGB, GL_UNSIGNED_BYTE,palette_Bottom);

	glRasterPos2f(0,562);
	glDrawPixels(Win_Width,38,GL_RGB, GL_UNSIGNED_BYTE,palette_Top);

	glRasterPos2f(749,0);
	glDrawPixels(51,Win_Height,GL_RGB, GL_UNSIGNED_BYTE,palette_Right);

	glFlush();
}


void Enter_Window()
{
	

	int rand_num = rand()%2;
	Open_Bitmap(wallpaper[rand_num]);
	printf("\nRAND is %d ",rand_num);

	
	glLineWidth(3);
	glColor3f(1.0 , 1.0 , 1.0);
	glBegin(GL_LINE_LOOP);
		glVertex2i(268,200);
		glVertex2i(268,220);
		glVertex2i(500,220);
		glVertex2i(500,200);
	glEnd();
	glFlush();


	/* The moving bar */ 
	{
		float colorRed   = 0.3588;
		float colorGreen = 0.6190;
		float colorBlue  = 0.6247;
		int x1 = 270, y1 = 200, x2 = 500, y2 = 220;
		
		
		for(; x1 != x2 ;){
			glColor3f( colorRed += 0.002 ,  colorGreen += 0.002 , colorBlue += 0.002);
			glBegin(GL_LINES);
		  	 glVertex2i(x1,y1);
		   	 glVertex2i(x1++,y2);
		  	glEnd();
			glFlush();
			Sleep(10);
		
		}
	}


	
}

void Init()
{
	glClearColor(1.0,1.0,1.0,0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0,0.0,0.0);
	glFlush();
	X = 0;
	Y = 0;
	Flag = 0;
}



void Reshape(int w,int h)
{

	glutReshapeWindow( 800, 600);
	/*
	Win_Height = h;
	Win_Width  = w;	

	reshape = 1;
	glViewport (0, 0, (GLsizei) w, (GLsizei) h);
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0,Win_Width,0.0,Win_Height);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	Window_Done = 1;*/
}


void Undo_Operation_Push()
{
	struct Undo *undo;
	unsigned char *info;
	struct Undo *temp;

	info = (unsigned char*)malloc(800 * 600 *3);

	glReadPixels(0 ,0 ,800 , 600 , GL_RGB , GL_UNSIGNED_BYTE , (info) );
	undo = (struct Undo * )malloc(sizeof(struct Undo));

	if(Undo_Op_Count >= 10){
		temp   = BOTTOM -> ptr;
		free(BOTTOM);/* Free the first operation (Only 10 undo operations possible) */
		BOTTOM = temp;
		Undo_Op_Count = 10;
	}	
	

	/* Creating a linked list.A stack implementation using a linked list */
	if( TOP == NULL){
		TOP    = undo;
		BOTTOM = undo;
		undo -> pixel_data = info;
		undo -> op_num = Undo_Op_Count; 
		undo -> ptr	   = NULL;
	}else{
		undo -> pixel_data = info;
		TOP  -> ptr	   = undo;
		undo -> op_num = Undo_Op_Count; 
		TOP  = undo;
	}

}

/* Logic: Simple linked list implementation.Create a new node when an operation is performed.
 * Maximum of 10 undo operations supported here. Now if the 10 nodes are filled then 
 * the new node created is made as "TOP" and "BOTTOM is shifted by one position
 */

void Undo_Operation_Pop()
{
	unsigned char *info;
	struct Undo *temp = BOTTOM;
	struct Undo *temp1 = BOTTOM;

	/* Undo operation not possible */
	if(TOP == NULL || Undo_Op_Count <= 1)
		return;

	else if(TOP -> ptr == NULL){
		glDrawPixels(800 , 600 , GL_RGB , GL_UNSIGNED_BYTE , (TOP -> pixel_data) );

		free(TOP);/* This is the pop operation */
		
		TOP    = NULL;/*This is the first operation */
		BOTTOM = NULL;
		Undo_Op_Count--;

		return;
	}


	else{
		for(;temp -> ptr != TOP;)
			temp = temp -> ptr;
		
		glDrawPixels(800 , 600 , GL_RGB , GL_UNSIGNED_BYTE , (temp->pixel_data) );

		temp1 = temp -> ptr;
		free(temp->ptr->pixel_data);
		free(temp1);/* This is the pop operation */
		
		TOP = temp;
		Undo_Op_Count--;

	}

}

void Fin()
{
	char *dev_by   = "DEVELOPED BY";	
	char *dev_name = "MUKUND Y.K";
	char *col_name = "BNMIT";
	int i = 0;
	void *f_type  = GLUT_BITMAP_TIMES_ROMAN_24;
	void *f_type1 = GLUT_BITMAP_HELVETICA_12;
	int posX = 200,posY ,old_posX = 200,old_posY = 10,initX,initY;
	float t;
	int ran = 0;

	initX = 400;
	initY = 300;
	
	glLineWidth(40);
	/* The circle lines 
	for(i = 0;i < 360 ;i++){
		t = i * (3.14/180.0);
		glColor3f(rand()%500/500.0,rand()%500/500.0,rand()%500/500.0);
		glBegin(GL_LINES);
			glVertex2f(400 , 300);
			glVertex2f(initX + (300 * cos(t)) , initY + (300 * sin(t)));
		glEnd();
		glFlush();
		//Sleep(10);
	}
	glColor3f(0.0,0.0,0.0);
	for(i = 0;i < 360 ;i++){
		t = i * (3.14/180.0);
		glBegin(GL_LINES);
			glVertex2f(400 , 300);
			glVertex2f(initX + (300 * cos(t)) , initY + (300 * sin(t)));
		glEnd();
		glFlush();
		Sleep(10);
	}
	*/

	/* Seee */
	/*glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(100,0,0,0.0, 0.0, 0.0, 0.0, 1.0, 0.0);*/


	glColor3f(1.0,1.0,1.0);
	glLineWidth(10);
	glBegin(GL_LINE_LOOP);
		glVertex2i(0 , 0);
		glVertex2i(0 , 600);
		glVertex2i(800 , 600);
		glVertex2i(800 , 0);
	glEnd();
	glFlush();

	

	/* The "DEVELOPED BY" part */
	posX = 230;
	for(i = 0;i < (signed)strlen(dev_by);i++){
		for(posY = 10;posY < 400 ;posY+=10){
			glColor3f(0.0,0.0,0.0);
			glRasterPos2f( old_posX , old_posY );
			glutBitmapCharacter(f_type ,  dev_by[i]);	
			
			glColor3f(0.0,1.0,0.0);
			glRasterPos2f( posX , posY );
			glutBitmapCharacter(f_type , dev_by[i]);

			//glColor3f(1.0,0.0,0.0);
			//if(ran == 1){
			//	glRasterPos2f( posX + (rand()% 800) ,(rand()% 600));
			//	glutBitmapCharacter(f_type1 ,  rand()%200);	
			//	ran = 0;
			//}else if(ran == 0){
			//	glRasterPos2f( posX - (rand()% 800) ,(rand()% 600));
			//	glutBitmapCharacter(f_type1 ,  rand()%200);	
			//	ran = 1;
			//}
			
			old_posX = posX;
			old_posY = posY;

			Sleep(10);
		}
		posX += 24;
		old_posX = 200;
		old_posY = 10;
	}

	/* The "MUKUND Y.K" part */
	posX = 250;
	for(i = 0;i < (signed)strlen(dev_name);i++){
		for(posY = 10;posY < 300 ;posY+=10){
			glColor3f(0.0,0.0,0.0);
			glRasterPos2f( old_posX , old_posY );
			glutBitmapCharacter(f_type , dev_name[i]);
	
			glColor3f(0.0,1.0,0.0);
			glRasterPos2f( posX , posY );
			glutBitmapCharacter(f_type , dev_name[i]);	

			//glColor3f(1.0,0.0,0.0);
			//if(ran == 1){
			//	glRasterPos2f( posX + (rand()% 800) ,(rand()% 600));
			//	glutBitmapCharacter(f_type1 ,  rand()%200);	
			//	ran = 0;
			//}else if(ran == 0){
			///	glRasterPos2f( posX - (rand()% 800) ,(rand()% 600));
			//	glutBitmapCharacter(f_type1 ,  rand()%200);	
			//	ran = 1;
			//}
			
			old_posX = posX;
			old_posY = posY;

			Sleep(10);
		}
		posX += 24;
		old_posX = 200;
		old_posY = 10;
	}

	/* The "BNMIT" part */
	posX = 300;
	for(i = 0;i < (signed)strlen(col_name);i++){
		for(posY = 10;posY < 200 ;posY+=10){
			glColor3f(0.0,0.0,0.0);
			glRasterPos2f( old_posX , old_posY );
			glutBitmapCharacter(f_type , col_name[i]);
	
			glColor3f(0.0,1.0,0.0);
			glRasterPos2f( posX , posY );
			glutBitmapCharacter(f_type , col_name[i]);	

			//glColor3f(1.0,0.0,0.0);
			//if(ran == 1){
			//	glRasterPos2f( posX + (rand()% 800) ,(rand()% 600));
			///	glutBitmapCharacter(f_type1 ,  rand()%200);	
			//	ran = 0;
			//}else if(ran == 0){
			//	glRasterPos2f( posX - (rand()% 800) ,(rand()% 600));
			//	glutBitmapCharacter(f_type1 ,  rand()%200);	
			//	ran = 1;
			//}
			
			old_posX = posX;
			old_posY = posY;

			Sleep(5);
		}
		posX += 24;
		old_posX = 300;
		old_posY = 10;
	}
	Sleep(3000);
	exit(0);
}

/* Perform Undo operation when F10 is pressed and exit when F5 is pressed */
void Special_Keys(int key , int x , int y)
{
	if( key == GLUT_KEY_F10 ){
		glRasterPos2f(0,0);
		Undo_Operation_Pop();
		glFlush();
	}

	else if( key == GLUT_KEY_F5 ){
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0,800,0,600,-500,500);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		glClearColor(0.0,0.0,0.0,0.0);
		glClear(GL_COLOR_BUFFER_BIT);
		Fin();
	}
}


void Mouse(int button,int state,int x,int y)
{
	FILE_PALETTE f;	
	

	if(button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN && TWO_D_MODE == 5){
		Flag = 0;
		glBegin(GL_LINE_STRIP);
		 glVertex2i(X,Y);
		 glVertex2i(Init_Pointx ,Init_Pointy );
		glEnd();
		glFlush();
	    /*Connect the first and the last point*/
	}


	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
		if(x > 749 && (Win_Height - y) > 50 && (Win_Height - y) < 75){
			entry = 1;
		}
		
		if(theme == 4)
			theme = 1;
	}

	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && BEGIN_WINDOW == 0){
		BEGIN_WINDOW  = 1; 
		glutPostRedisplay();
	}

	else if(button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN)
		PlaySoundW(point_on,NULL,SND_FILENAME|SND_ASYNC);
	

	/*done is used for seeing if the Main Mode option is done*/
	else if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && done == 0){
		glutIdleFunc(NULL);/*De-Register the Idle Function*/
	
		glMatrixMode(GL_MODELVIEW);/*Restore Identity in case it was left mod*/
		glLoadIdentity();

		Main_Mode_Palette_Draw();

		m = Main_Mode_Search(x,Win_Height-y);
		done = 1;	
		
		Resolve_Modes(m,x,Win_Height-y);
	}	

	else if(button == GLUT_LEFT_BUTTON && state == GLUT_UP && File_Opt_Sel == 1){
		glReadPixels(0,0,Win_Width,Win_Height,GL_RGB, GL_UNSIGNED_BYTE,write_pixel_info);

		f  = File_Palette_Search(x,Win_Height-y);/*For File Operations*/

		if(f.mode <= 5)
		 File_Operations(f.mode);
	

		glRasterPos2f(0,0);

		if(Read_Op == 1)
			glDrawPixels(Win_Width,Win_Height,GL_RGB, GL_UNSIGNED_BYTE,write_pixel_info);
		else
			glDrawPixels(Win_Width,Win_Height,GL_RGB, GL_UNSIGNED_BYTE,pixel_info);
	}

	else if(button == GLUT_LEFT_BUTTON && state == GLUT_UP && BITMAP_MODE > 0)	
	   Create_Curve_Window();
	 

	
	else if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && done == 1){
		Resolve_Modes(m,x,Win_Height-y);
	}

	if(button == GLUT_LEFT_BUTTON && state == GLUT_UP && (TWO_D_MODE > 0 || THREE_D_MODE) ){
		Motion_Flag = 0;
		glEnable(GL_LOGIC_OP);
		glLogicOp(GL_COPY);

		Undo_Operation_Push();
		Undo_Op_Count++;
	}
	

	if(Music == 1){
		glViewport(0,20,35,35);
		
		/*Load the speaker ON icon*/
		Open_Bitmap(".\\bit\\vol_on.bmp");
		 
		glViewport(0,0,Win_Width,Win_Height);
		PlaySoundW(point_on,NULL,SND_FILENAME|SND_ASYNC);
	}

	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		Mouse_Click_Spot = x;

}


void Keyb(unsigned char c,int x,int y)
{
	
	FILE *fp;
	void *font = GLUT_BITMAP_HELVETICA_18;

	if(c == 'u' || c == 'U')
		Filled = 0;
	else if(c == 'r' || c == 'R')
		Filled = 1;
	else
		Filled = 2;

	if(THREE_D_MODE == 9)
		View += 10;

	if(m.mode == 1 && TWO_D_MODE == 16 && c == 'j'){
		glRasterPos2f(x,Win_Height-y);
		glDrawPixels(abs(Xr),abs(Yr),GL_RGB, GL_UNSIGNED_BYTE,temp_pixel_info);
		glFlush();
		Draw_Palettes();
	}

	else if(m.mode == 1 && TWO_D_MODE == 14 && c == 'e'){
		Xt = x;
		Yt = Win_Height - y;
		
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0.0,Win_Width,0.0,Win_Height,100,-100);

		glutIdleFunc(Idle);
	}

	else if(m.mode == 1 && TWO_D_MODE == 13 && c == 'r'){
		Xt = x;
		Yt = Win_Height - y;
		
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0.0,Win_Width,0.0,Win_Height,100,-100);

		glutIdleFunc(Idle);
	}
	
	else if((TWO_D_MODE == 13 || TWO_D_MODE == 14)  && c == 's'){
		glutIdleFunc(NULL);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		Point_Count = 0;
	}

	else if(m.mode == 1 && TWO_D_MODE == 8)
	{
		glRasterPos2f(X,Y);
		glutBitmapCharacter(text_font,c);/*Key Pressed*/
		X += 12;
		glFlush();
		Draw_Palettes();
	}

	else if(THREE_D_MODE == 6)
	{
		if(c == 'x' || c == 'X'){
			Rot_FlagX = 1;
		    	Rot_FlagY = 0;
			Rot_FlagZ = 0;
		}
		else if(c == 'x' || c == 'X'){
			Rot_FlagX = 0;
		    	Rot_FlagY = 1;
			Rot_FlagZ = 0;
		}
		else if(c == 'Z' || c == 'z'){
			Rot_FlagX = 0;
		    	Rot_FlagY = 0;
			Rot_FlagZ = 1;
		}

	}


	else if(m.mode == 3)
	{
		
		if(c == 'd' || c == 'D'){
			dir =  1;
			vpx += 5;				/*Direction = Upwards*/
		}

		if(c == 'w' || c == 'W'){
			vpy += 5;				/*Direction = Rightwards*/
			dir =  2;
		}	

		if(c == 's' || c == 'S'){
			vpy -= 5;				/*Direction = Downwards*/
			dir =  3;
		}

		if(c == 'a' || c == 'A'){
			vpx -= 5;				/*Direction = Leftwards*/
			dir =  4;				
		}
	
		glViewport(vpx,vpy,400,400);
		MOVES[COUNT++] = dir;

		Init();

		if(ANIMATION_MODE == 1)
			Draw_Man();
		
		else 
			Draw_Dog();
	

	

		if(c == 'P' || c == 'p')
		{

			fp = fopen("animation_details.anim","wb");
			fwrite(&ANIMATION_MODE,sizeof(int),1,fp);
			fwrite(&MOVES,sizeof(int)*COUNT,1,fp);
			fclose(fp);
		}

		if(c == 'O' || c == 'o')
		{

			FILE *fp;
		
			fp = fopen("animation_details.anim","rb");
			fread(&obj_mode,sizeof(int),1,fp);
			fread(&dircn,sizeof(int),1,fp);
			vpx = vpy = 0;	
		
			while(!feof(fp))
			{
				Init();
			
				if(dircn == 1)
					vpx += 5;
				if(dircn == 2)
					vpy += 5;
				if(dircn == 3)
					vpy -= 5;
				if(dircn == 4)
					vpx -= 5;
			
				glViewport(vpx,vpy,400,400);		
				fread(&dircn,sizeof(int),1,fp);

				if(obj_mode == 1)
					Draw_Man();
				else 
					Draw_Dog();

				Sleep(250); /*Sleep for some time*/
			}
			fclose(fp);
		}
	
		glViewport(0,0,Win_Width,Win_Height);

	}

	else if(m.mode == 3 && c == 'i')
		Scale_Factor += 0.1;

	else{
		PlaySoundW(point_on,NULL,SND_FILENAME|SND_ASYNC);
	}

}

void Begin_Animate()
{
		void *font = GLUT_BITMAP_HELVETICA_18;
		glLineWidth(2);
		//////////////////////////////SEEEEEEEEEEEEEEEEE!!!	
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		
		glEnable(GL_LINE_SMOOTH);

		glColor3f( (rand()%500/500.0) , (rand()%500/500.0) , (rand()%500/500.0));
		glRasterPos2f(Ang += 20,250);
		glutBitmapCharacter(font , *mode_name1++);
		
		Draw_Circle(130 , 100 ,rad += 10);
		if(rad >= 90)
			rad = 0;
		
		if(*mode_name1 == '\0'){
			Ang = 0;
			mode_name1 = (char*)malloc(strlen("TWO_DIMENSION"));
			strcpy(mode_name1, "TWO_DIMENSION");
		}
		glFlush();
		Sleep(100);
	
		glDisable(GL_LINE_SMOOTH);
		glFlush();
}

void Begin_Animate1()
{

		glLineWidth(2);
		void *font = GLUT_BITMAP_HELVETICA_18;
	
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		
		//Clear_Region(cur,CLEAR);

		glColor3f( (rand()%500/500.0) , (rand()%500/500.0) , (rand()%500/500.0));
		glRasterPos2f(Ang += 20,550);
		glutBitmapCharacter(font , *mode_name2++);

		

		if(*mode_name2 == '\0'){
			Ang = 0;
			mode_name2 = (char*)malloc(strlen("THREE_DIMENSION"));
			strcpy(mode_name2, "THREE_DIMENSION");
		}

		glLineWidth(2);
		glTranslatef(140,410,0);
		glRotatef(Ang , 0, 1, 1);/*REV!!!!!!!!!!*/
		
		/*Blusih shade*/
		glColor3f(0.2117,0.4313,0.6941);
		glutSolidSphere(100,10,10);
		glColor3f(0.0,0.0,0.0);
		glutWireSphere(100,20,20);
		
		glFlush();

		Sleep(100);
	
		glColor3f(1.0,1.0,1.0);
		glutSolidSphere(100,10,10);
		glutWireSphere(100,20,20);
		glFlush();
}

void Begin_Animate2()
{
		void *font = GLUT_BITMAP_HELVETICA_18;
		
		glLineWidth(2);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
	
		glColor3f( (rand()%500/500.0) , (rand()%500/500.0) , (rand()%500/500.0));
		
		glRasterPos2f((Ang + 600),500);
		Ang += 20;
		
		glutBitmapCharacter(font , *mode_name3++);

		if(*mode_name3 == '\0'){
			Ang = 0;
			mode_name3 = (char*)malloc(strlen("ANIMATION"));
			strcpy(mode_name3, "ANIMATION");
		}
		

		Sleep(100);

		
}

void Begin_Animate3()
{	
		void *font = GLUT_BITMAP_HELVETICA_18;

		glLineWidth(2);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
	
		glColor3f( (rand()%500/500.0) , (rand()%500/500.0) , (rand()%500/500.0));
		glRasterPos2f((Ang + 600),250);
		Ang += 20;
		
		glutBitmapCharacter(font , *mode_name4++);

		if(*mode_name4 == '\0'){
			Ang = 0;
			mode_name4 = (char*)malloc(strlen("MATH"));
			strcpy(mode_name4, "MATH");
		}

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluOrtho2D(0, 2, -1.2, 1.2);

		glViewport(Win_Width/2, 0, Win_Width/2, Win_Height/2);
	

		float num1 = 0;

		glColor3f(0.0,0.0,1.0);

		glLineWidth(5);
	
		glBegin(GL_LINE_STRIP);
		for(num = 0 ; num < 360 ; num += 2){
			glBegin(GL_LINE_STRIP);	
				glVertex2f(num1 , sin(num*K));
				glVertex2f(num1 += 0.007 , sin(num*K));
			glEnd();
			glFlush();
			
		}		
		Sleep(10);	

		glViewport(0.0, 0.0, Win_Width, Win_Height);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0, Win_Width, 0, Win_Height,-500, 500);
	
}

void Clear_Region(int region,int mode)
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	if(region == 1 && mode == CLEAR){
		glColor3f(0.415, 0.47, 0.5372);
		glRectf(0, 0, 400, 300);

		glColor3f(0.6, 0.5, 1.6);
		glLineWidth(5);
		glBegin(GL_LINE_LOOP);
			glVertex2i( 0 , 0);
			glVertex2i( 0 , 300);
			glVertex2i( 400 , 300);
			glVertex2i( 400  , 0);
		glEnd();
		glFlush();
	}
	else if(region == 1 && mode == FILL){
		glViewport(0, 0, Win_Width/2, Win_Height/2);
		Open_Bitmap(".\\bit\\TwoD.bmp");
		glViewport(0.0, 0.0, Win_Width, Win_Height);
	}

	if(region == 2 && mode == CLEAR){
		glColor3f(0.2078, 0.2196, 0.3490);
		glRectf(0, Win_Height/2, Win_Width/2, Win_Height);

		glColor3f(0.6, 0.5, 0.6);
		glLineWidth(5);
		glBegin(GL_LINE_LOOP);
			glVertex2i( 0 , Win_Height/2);
			glVertex2i( 0 , Win_Height);
			glVertex2i( Win_Width/2 , Win_Height);
			glVertex2i( Win_Width/2  ,Win_Height/2);
		glEnd();
		glFlush();
	}
	else if(region == 2 && mode == FILL){
		glViewport(0, Win_Height/2, Win_Width/2, Win_Height/2);
		Open_Bitmap(".\\bit\\ThreeD.bmp");
		glViewport(0.0, 0.0, Win_Width, Win_Height);
	}
	
	if(region == 3 && mode == CLEAR){
		glColor3f(1.0, 1.0, 1.0);
		glRectf(Win_Width/2, Win_Height/2, Win_Width, Win_Height);

		glColor3f(0.6, 0.5, 0.6);
		glLineWidth(5);
		glBegin(GL_LINE_LOOP);
			glVertex2i( Win_Width/2 , Win_Height/2);
			glVertex2i( Win_Width/2 , Win_Height);
			glVertex2i( Win_Width , Win_Height);
			glVertex2i( Win_Width  ,Win_Height/2);
		glEnd();
		glFlush();
	}
	else if(region == 3 && mode == FILL){
		glViewport(Win_Width/2, Win_Height/2,Win_Width/2, Win_Height/2);
		Open_Bitmap(".\\bit\\Animation.bmp");
		glViewport(0.0, 0.0, Win_Width, Win_Height);
	}

	if(region == 4 && mode == CLEAR){
		glColor3f(0.2078, 0.2196, 0.3490);
		glRectf(Win_Width/2, 0, Win_Width, Win_Height/2);

		glColor3f(0.6, 0.5, 0.6);
		glLineWidth(5);
		glBegin(GL_LINE_LOOP);
			glVertex2i( Win_Width/2 , 0);
			glVertex2i( Win_Width/2 , Win_Height/2);
			glVertex2i( Win_Width , Win_Height/2);
			glVertex2i( Win_Width  ,0);
		glEnd();
		glFlush();
	}
	else if(region == 4 && mode == FILL){
		glViewport(Win_Width/2, 0, Win_Width/2, Win_Height/2);
		Open_Bitmap(".\\bit\\Math.bmp");
		glViewport(0.0, 0.0, Win_Width, Win_Height);
	}

}


void Print_Coords(int x, int y)
{
	int xCord[5],yCord[5],xCordNew[5],yCordNew[5];
	int i,count = 0,c;
	void *f_type = GLUT_BITMAP_HELVETICA_18;

	glColor3f(0.5,0.5,0.5);
	glRectf(590,25,750,55);

	glColor3f(0.0,0.0,0.0);
	glBegin(GL_LINE_LOOP);
		glVertex2i(590,25);
		glVertex2i(590,55);
		glVertex2i(750,55);
		glVertex2i(750,25);
	glEnd();
	glFlush();
	
	while( x != 0 ){
		xCord[count++] = (x%10);
		x /= 10;
	}
	
	count = 0;	
	
	while( y != 0 ){
		yCord[count++] = (y%10);
		y /= 10;
	}
	
	for(i = 0,c = 2 ;i < 3; i++){
		xCordNew[c] = xCord[i];
		yCordNew[c--] = yCord[i];
	}

	glRasterPos2f(625 , 30);
	for(i = 0;i < 3; i++)
		glutBitmapCharacter(f_type , xCordNew[i] + '0');

	glutBitmapCharacter(f_type , 32); /* Space */
	glutBitmapCharacter(f_type , ',');
	glutBitmapCharacter(f_type , 32); /* Space */

	for(i = 0;i < 3; i++)
		glutBitmapCharacter(f_type , yCordNew[i] + '0');

	glFlush();

}

void Pass_Mouse(int x,int y)
{	

	extern int THREE_D_MODE;

	glPushAttrib(GL_ALL_ATTRIB_BITS);

	if( done == 1 )
		Print_Coords( x , Win_Height - y);

	if(BEGIN_WINDOW == 1 && done == 0)
	{
		MAIN_MODE m;
		
	
		m = Main_Mode_Search(Mouse_PositionX,Mouse_PositionY);	
		
		if( m.mode != cur ){
			Ang = 0;
			i = 0;
			mode_name1 = (char*)malloc(strlen("TWO_DIMENSION"));
			mode_name2 = (char*)malloc(strlen("THREE_DIMENSION"));
			mode_name3 = (char*)malloc(strlen("ANIMATION"));
			mode_name4 = (char*)malloc(strlen("MATH"));
			strcpy(mode_name1, "TWO_DIMENSION");
			strcpy(mode_name2, "THREE_DIMENSION");
			strcpy(mode_name3, "ANIMATION");
			strcpy(mode_name4, "MATH");
			Clear_Region(cur,FILL);
			Clear_Region(m.mode,CLEAR);
	
		}

		if(Mouse_PositionX > 0 && Mouse_PositionY < Win_Height/2 && Mouse_PositionX < Win_Width/2)
				{//Clear_Region(1,CLEAR);
				 cur = 1;
				 glutIdleFunc(Begin_Animate);}
	
		
		
		if(Mouse_PositionX > 0 && Mouse_PositionY > Win_Height/2 && Mouse_PositionX < Win_Width/2)
				{//Clear_Region(2,CLEAR);
				 cur = 2;
				 glutIdleFunc(Begin_Animate1);}

	
		if(Mouse_PositionX > Win_Width/2 && Mouse_PositionY > Win_Height/2)
				{//Clear_Region(3,CLEAR);
				 cur = 3;
				 glutIdleFunc(Begin_Animate2);}
	

		if( Mouse_PositionY < Win_Height/2 && Mouse_PositionX > Win_Width/2)
				{//Clear_Region(4,CLEAR);
				 cur = 4;	
				 glutIdleFunc(Begin_Animate3);}
		
		
	}

	/* Define the area where selection mode is OFF */
	if(x > 50 && (Win_Height-y) > 65 && (Win_Height-y) < 550 && x < 749 ){
		Sel = 0;
	}

	else 
		Sel = 1;
	


	if(x > 30 && (Win_Height-y) > 550)
		File_Opt_Sel = 1;

	else 
		File_Opt_Sel = 0;
	
	Mouse_PositionX = x;
	Mouse_PositionY = Win_Height-y;

	//printf("\n%d %d",Mouse_PositionX,Mouse_PositionY);

	//TESSSSSSTINNNNNNNNNNNNNNNGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG
	if((Sel == 1  && x < 25) || (Sel == 1  && x > 615 ) && THREE_D_MODE == 0)
	{
		SUB_MODE s;

		s = Sub_Mode_Search(x,Win_Height-y,20);
		Print_Details(s);
	}
    //////////////////////////////////////////////////////////////////////

	if(Mouse_PositionX < 25 && Mouse_PositionY > 25 &&  Mouse_PositionY < 50)
		Music = 1;
	else 
		Music = 0;

	
	glPopAttrib();
	
}


void Mouse_Mot(int x,int y)
{
	if(Motion_Flag == 0)
		Flag = 0;


	if( x > Mouse_Click_Spot)
			Increase_Flag = 1;
	else
			Increase_Flag = 0;



	Motion_Flag = 1;

	Resolve_Modes(m,x,Win_Height-y);

	
}


void Menu_Options(int opt)
{

	if(opt == 0){
		glClearColor(1.0,1.0,1.0,1.0);
		glClear(GL_COLOR_BUFFER_BIT);
		glFlush();

		glMatrixMode (GL_MODELVIEW);		
	    glLoadIdentity();

		glRasterPos2f(0,0);

		if(Read_Op == 0)
			glDrawPixels(Win_Width,Win_Height,GL_RGB, GL_UNSIGNED_BYTE,pixel_info);
	
		else{
			Read_Op = 0;
			glDrawPixels(640,Win_Height,GL_RGB, GL_UNSIGNED_BYTE,write_pixel_info);
		}

		glFlush();

	}


	else if(opt == 1){
		Main_Mode_Palette_Draw();
		done = 0;		
		TWO_D_MODE     = 1; 
		THREE_D_MODE   = 1; 
		ANIMATION_MODE = 1;
		entry = 1;     	
		/*done is made 0 => we get main mode option again
		/*Default 2D mode is set
		/*Go back and get palettes again*/

		/*Restore the original ortho volume*/
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluOrtho2D(0.0,Win_Width,0.0,Win_Height);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		Initialise();/*For the three D mode*/
		
	}
	else if(opt == 2)
		exit(0);

	else if(opt == 5)
		exit(0);
}

void PointSize(int point_size)
{
	switch(point_size)
	{
	case 1:glPointSize(5);
		   break;
	case 2:glPointSize(15);
		   break;
	case 3:glPointSize(25);
		   break;
	case 4:glPointSize(35);
		   break;
	}
}

void ErasorSize(int erasor_size)
{
		
	switch(erasor_size)
	{
	case 1:Erasor_Size = 20;
		   break;
	case 2:Erasor_Size = 30;
		   break;
	case 3:Erasor_Size = 40;
		   break;
	case 4:Erasor_Size = 50;
		   break;
	}
}

void SpraySize(int spray_size)
{

	switch(spray_size)
	{
	case 1:Spray_Size = 20;
		   break;
	case 2:Spray_Size = 30;
		   break;
	case 3:Spray_Size = 40;
		   break;
	case 4:Spray_Size = 50;
		   break;
	}
}

void Stipple(int stipple)
{
	glEnable (GL_LINE_STIPPLE);
	switch(stipple)
	{
	case 1:glLineStipple (1, 0x0101);
		   break;
	case 2:glLineStipple (1, 0x00FF);
		   break;
	case 3:glLineStipple (1, 0x0101);
		   break;
	case 4:glDisable(GL_LINE_STIPPLE);
		   break;
	}
}

void TextMode(int text_mode)
{
	switch(text_mode)
	{
	case 1:text_font = GLUT_BITMAP_HELVETICA_18;
		   break;
	case 2:text_font = GLUT_BITMAP_TIMES_ROMAN_24;
		   break;
	case 3:text_font = GLUT_BITMAP_8_BY_13;
		   break;
	case 4:text_font = GLUT_BITMAP_9_BY_15;
		   break;
	case 5:text_font = GLUT_BITMAP_TIMES_ROMAN_10;
		   break;
	}
}

void No_Options(int no_op)
{
	/*This is the case where no options are present
	 *There was some problem with the usual 
	 *replacement of menus
	 *So trying this
	 */
}


void Menu_Handles()
{

	if(Menu_Done == 0){
		thickness_menu = glutCreateMenu(Thickness);
		glutAddMenuEntry("Thickness 1",1);
		glutAddMenuEntry("Thickness 2",2);
		glutAddMenuEntry("Thickness 3",3);
		glutAddMenuEntry("Thickness 4",4);

		point_size = glutCreateMenu(PointSize);
		glutAddMenuEntry("Size 1",1);
		glutAddMenuEntry("Size 2",2);
		glutAddMenuEntry("Size 3",3);
		glutAddMenuEntry("Size 4",4);

		erasor_size = glutCreateMenu(ErasorSize);
		glutAddMenuEntry("Size 1",1);
		glutAddMenuEntry("Size 2",2);
		glutAddMenuEntry("Size 3",2);
		glutAddMenuEntry("Size 4",2);

		spray_size = glutCreateMenu(SpraySize);
		glutAddMenuEntry("Size 1",1);
		glutAddMenuEntry("Size 2",2);
		glutAddMenuEntry("Size 3",3);
		glutAddMenuEntry("Size 4",4);

		stipple = glutCreateMenu(Stipple);
		glutAddMenuEntry("Type 1",1);
		glutAddMenuEntry("Type 2",2);
		glutAddMenuEntry("Type 3",3);
		glutAddMenuEntry("Disable",4);

		text_mode = glutCreateMenu(TextMode);
		glutAddMenuEntry("Helvetica 18",1);
		glutAddMenuEntry("Times Roman 24",2);
		glutAddMenuEntry("8 BY 13",3);
		glutAddMenuEntry("9 BY 15",4);
		glutAddMenuEntry("Times Roman 10",5);

		no_options = glutCreateMenu(No_Options);
		glutAddMenuEntry("NO",1);

		glutCreateMenu(Menu_Options);
		glutAddMenuEntry("Clear",0);
		glutAddMenuEntry("Exit",1);
		glutAddSubMenu("No Options",no_options);

		Menu_Done = 1;
	}
	
	else if(TWO_D_MODE == 18){
		glutRemoveMenuItem(3); 
		glutAddSubMenu("NO OPTIONS!!!",no_options);
		glutChangeToSubMenu(3, "Point Size", point_size); 
	}
	
	else if(TWO_D_MODE == 1){
		glutRemoveMenuItem(3); 
		glutAddSubMenu("NO",no_options);
		glutChangeToSubMenu(3, "Thickness", thickness_menu); 
	}

	else if(TWO_D_MODE == 6){
		glutRemoveMenuItem(3); 
		glutAddSubMenu("NO",no_options);
		glutChangeToSubMenu(3, "Erasor Size", erasor_size); 
	}

	else if(TWO_D_MODE == 7){
		glutRemoveMenuItem(3); 
		glutAddSubMenu("NO",no_options);
		glutChangeToSubMenu(3, "Spray Size", spray_size);
	}

	else if(TWO_D_MODE == 3){
		glutRemoveMenuItem(3); 
		glutAddSubMenu("NO",no_options);
		glutChangeToSubMenu(3, "Type", stipple);
	}

	else if(TWO_D_MODE == 8){
		glutRemoveMenuItem(3); 
		glutAddSubMenu("NO",no_options);
		glutChangeToSubMenu(3, "Font Type", text_mode);
	}

	else{ 
		glutRemoveMenuItem(3); 
		glutAddSubMenu("NO",no_options);
	}

}

void Thickness(int thickness)
{
	switch(thickness)
	{
	case 1:glLineWidth(5);
		   break;
	case 2:glLineWidth(10);
		   break;
	case 3:glLineWidth(20);
		   break;
	case 4:glLineWidth(40);
		   break;
	}
}


void Cursor_Handles()
{
	switch(TWO_D_MODE)
	{
	case 1:glutSetCursor(GLUT_CURSOR_CROSSHAIR);
		   break;
	case 2:glutSetCursor(GLUT_CURSOR_CYCLE);
		   break;
    case 8:glutSetCursor(GLUT_CURSOR_TEXT);
		   break;
	case 10:glutSetCursor(GLUT_CURSOR_DESTROY);
		   break;
	case 7:glutSetCursor(GLUT_CURSOR_SPRAY);
		   break;
	case 20:glutSetCursor(GLUT_CURSOR_INHERIT);
			break;
	default:glutSetCursor(GLUT_CURSOR_CROSSHAIR);
		   break;
	}
}


void Idle()
{
	int i;
	
	glLineWidth(2);

	if(TWO_D_MODE == 13){	
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		
		glTranslatef(Xt , Yt , 0);
		glRotatef(Rotate_Angle+=5 , 0, 0, 1);	
		glTranslatef(-Xt , -Yt , 0);
		
		glBegin(GL_LINES);
		for(i = 0 ; i< Point_Count - 1 ; i++){
			glVertex2i(arr1[i][0],arr1[i][1]);
			glVertex2i(arr1[i+1][0],arr1[i+1][1]);		
		}
		glEnd();
		glFlush();
		Sleep(100);
	}
	else if(TWO_D_MODE == 14){
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
	
		glTranslatef(Xt , Yt , 0);
		glScalef(Scale_Factor+=0.1 ,Scale_Factor+=0.1, 1);	
		glTranslatef(-Xt , -Yt , 0);		

		glBegin(GL_LINES);
		for(i = 0 ; i< Point_Count - 1 ; i++){
			glVertex2i(arr1[i][0],arr1[i][1]);
			glVertex2i(arr1[i+1][0],arr1[i+1][1]);
	
		}
		glEnd();
		glFlush();
		Sleep(1000);
	}

	/*Restore the icons*/
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	Draw_Palettes();
	glFlush();
  
}


int main(int argc,char **argv)
{
	FreeConsole();

	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);

	
	glutInitWindowPosition(200,100);/*PHEW!!! resolution!!!!*/
	glutInitWindowSize(800,600);
	
	w = glutCreateWindow("                                                 GOGH PAINT");


	/* Registering the callback functions */
	/***************************************/
	glutDisplayFunc(Display);
	glutReshapeFunc(Reshape);
	glutMouseFunc(Mouse);
	glutMotionFunc(Mouse_Mot);
	glutPassiveMotionFunc(Pass_Mouse);
	glutKeyboardFunc(Keyb);
	glutSpecialFunc(Special_Keys);
	/***************************************/

	Menu_Handles();

	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutSetCursor(GLUT_CURSOR_CROSSHAIR);/* Cursor is "crosshair" initially */

	Init();

	/***************COOOOOOOL!! from the forum*************/
	//HWND hThisWnd = FindWindow( "GLUT", "RECT" );
	//if( hThisWnd )
	//{
	//	LONG lStyle = GetWindowLong( hThisWnd, GWL_STYLE );
	//	SetWindowLong( hThisWnd, GWL_STYLE, lStyle & 
	//		(~(WS_MAXIMIZEBOX|WS_MINIMIZEBOX|WS_SYSMENU ) ) );
	//}
	/******************Remove Close,Min option****************/
	
	glutMainLoop();

	return 0;
}





