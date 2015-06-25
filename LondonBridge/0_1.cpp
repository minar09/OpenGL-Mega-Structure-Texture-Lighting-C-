#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include <windows.h>
#include<GL/glut.h>

#define BLACK 0, 0, 0

//make a global variable -- for tracking the anglular position of camera
double cameraAngle;			//in radian
double cameraAngleDelta;
double height,r;
double rectAngle;	//in degree
bool canDrawGrid;
GLUquadric* IDquadric=gluNewQuadric() ;//=new GLUquadricObj(

GLuint texid1,texid2,texid3, texid4;
int num_texture = -1;
int LoadBitmap(char *filename)
{
    int i, j=0;
    FILE *l_file;
    unsigned char *l_texture;

    BITMAPFILEHEADER fileheader;
    BITMAPINFOHEADER infoheader;
    RGBTRIPLE rgb;

    num_texture++;

    if( (l_file = fopen(filename, "rb"))==NULL) return (-1);

    fread(&fileheader, sizeof(fileheader), 1, l_file);

    fseek(l_file, sizeof(fileheader), SEEK_SET);
    fread(&infoheader, sizeof(infoheader), 1, l_file);

    l_texture = (byte *) malloc(infoheader.biWidth * infoheader.biHeight * 4);
    memset(l_texture, 0, infoheader.biWidth * infoheader.biHeight * 4);

    for (i=0; i < infoheader.biWidth*infoheader.biHeight; i++)
    {
        fread(&rgb, sizeof(rgb), 1, l_file);

        l_texture[j+0] = rgb.rgbtRed;
        l_texture[j+1] = rgb.rgbtGreen;
        l_texture[j+2] = rgb.rgbtBlue;
        l_texture[j+3] = 255;
        j += 4;
    }
    fclose(l_file);

    glBindTexture(GL_TEXTURE_2D, num_texture);

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);

// glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glTexImage2D(GL_TEXTURE_2D, 0, 4, infoheader.biWidth, infoheader.biHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, l_texture);
    gluBuild2DMipmaps(GL_TEXTURE_2D, 4, infoheader.biWidth, infoheader.biHeight, GL_RGBA, GL_UNSIGNED_BYTE, l_texture);

    free(l_texture);

    return (num_texture);

}

void func(void)
{

    texid1 =LoadBitmap("tower.bmp");   /*here bkg1.bmp is the bitmap image to be used as texture, texid is global varible declared to uniquely  identify this particular image*/
    texid2 =LoadBitmap("wall.bmp");
    texid3=LoadBitmap("sky.bmp");
    texid4=LoadBitmap("water.bmp");
}

void half_tower()
{

    glPushMatrix();
    {
        glTranslatef(0,60,0);
        //glColor3f(1,0,0);
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texid2); // here texid corresponds a bitmap image.
        gluQuadricNormals(IDquadric,GLU_SMOOTH);
        gluQuadricTexture(IDquadric, GLU_TRUE);
        gluCylinder(IDquadric,30 ,30 ,40,25,25);
        glDisable(GL_TEXTURE_2D);
    }
    glPopMatrix();


    glPushMatrix();
    {
        glTranslatef(15,45,40);
        //glColor3f(0,1,0);
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D,texid1);
        glNormal3f(1.0,0.0,0.0);
        glBegin(GL_POLYGON);
        glTexCoord2f(0,0);
        glVertex3f(0,0,0);
        glTexCoord2f(1,0);
        glVertex3f(0,30,0);
        glTexCoord2f(1,1);
        glVertex3f(0,30,30);
        glTexCoord2f(0,1);
        glVertex3f(0,0,30);
        glEnd();
        glDisable(GL_TEXTURE_2D);
    }
    glPopMatrix();


    glPushMatrix();
    {
        glTranslatef(-15,45,40);
        //glColor3f(0,1,0);
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D,texid1);
        glNormal3f(1.0,0.0,0.0);
        glBegin(GL_POLYGON);
        glTexCoord2f(0,0);
        glVertex3f(0,0,0);
        glTexCoord2f(1,0);
        glVertex3f(0,30,0);
        glTexCoord2f(1,1);
        glVertex3f(0,30,30);
        glTexCoord2f(0,1);
        glVertex3f(0,0,30);
        glEnd();
        glDisable(GL_TEXTURE_2D);
    }
    glPopMatrix();

    glPushMatrix();
    {
        glTranslatef(-15,45,40);
        glRotatef(90,0,0,-1);
        //glColor3f(0,1,0);
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D,texid1);
        glNormal3f(1.0,0.0,0.0);
        glBegin(GL_POLYGON);
        glTexCoord2f(0,0);
        glVertex3f(0,0,0);
        glTexCoord2f(1,0);
        glVertex3f(0,30,0);
        glTexCoord2f(1,1);
        glVertex3f(0,30,30);
        glTexCoord2f(0,1);
        glVertex3f(0,0,30);
        glEnd();
        glDisable(GL_TEXTURE_2D);
    }
    glPopMatrix();

    glPushMatrix();
    {
        glTranslatef(-15,45,40);
        glRotatef(90,0,0,-1);
        glTranslatef(-30,0,0);
        //glColor3f(0,1,0);
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D,texid1);
        glNormal3f(1.0,0.0,0.0);
        glBegin(GL_POLYGON);
        glTexCoord2f(0,0);
        glVertex3f(0,0,0);
        glTexCoord2f(1,0);
        glVertex3f(0,30,0);
        glTexCoord2f(1,1);
        glVertex3f(0,30,30);
        glTexCoord2f(0,1);
        glVertex3f(0,0,30);
        glEnd();
        glDisable(GL_TEXTURE_2D);
    }
    glPopMatrix();

}

void draw_grid(){
    glBegin(GL_POLYGON);
    glTexCoord2f(0,0);
    glVertex3f(0,0,0);
    glTexCoord2f(1,0);
    glVertex3f(0,200,0);
    glTexCoord2f(1,1);
    glVertex3f(0,200,200);
    glTexCoord2f(0,1);
    glVertex3f(0,0,200);
    glEnd();
    glDisable(GL_TEXTURE_2D);
}

void display()
{

    //clear the display
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(BLACK, 0);	//color black
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /********************
    / set-up camera here
    ********************/
    //load the correct matrix -- MODEL-VIEW matrix
    glMatrixMode(GL_MODELVIEW);

    //initialize the matrix
    glLoadIdentity();

    //now give three info
    //1. where is the camera (viewer)?
    //2. where is the camera is looking?
    //3. Which direction is the camera's UP direction?

    //instead of CONSTANT information, we will define a circular path.
//	gluLookAt(-30,-30,50,	0,0,0,	0,0,1);

    gluLookAt(r*cos(cameraAngle), r*sin(cameraAngle), height,		0,0,0,		0,0,1);//150 is radius
    //NOTE: the camera still CONSTANTLY looks at the center
    // cameraAngle is in RADIAN, since you are using inside COS and SIN


    //again select MODEL-VIEW
    glMatrixMode(GL_MODELVIEW);


    /****************************
    / Add your objects from here
    ****************************/
    //add objects

    /*glEnable(GL_TEXTURE_2D);
    	glBindTexture(GL_TEXTURE_2D,texid1);
    	glNormal3f(1.0,0.0,0.0);
    	glBegin(GL_POLYGON);
    		glTexCoord2f(0,0); glVertex3f(0,0,0);
    		glTexCoord2f(1,0); glVertex3f(0,30,0);
    		glTexCoord2f(1,1); glVertex3f(0,30,30);
    		glTexCoord2f(0,1); glVertex3f(0,0,30);
    	glEnd();
    glDisable(GL_TEXTURE_2D);*/
    glRotatef(45,0,0,1);
    half_tower();
    glTranslatef(0,120,0);
    half_tower();
    glRotatef(45,0,0,1);

    /*glPushMatrix();{
    		glTranslatef(0,-60,0);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texid3);
    gluQuadricNormals(IDquadric,GLU_SMOOTH);
    gluQuadricTexture(IDquadric, GLU_TRUE);
    	gluSphere(IDquadric,20,20,20);
    }glPopMatrix();*/




//draw first two : as half spheres: bottom half.
    /// the cutting plane equation: z = 30
    /// we will keep the points with
    //		z >= 30
    //OR	0.x + 0.y + 1.z - 30 >= 0  //// standard format:: ax + by + cz + d >= 0

    /*double equ[4];
    equ[0] = 0;	//+0.x
    equ[1] = 0;	//+0.y
    equ[2] = 1;//+1.z
    equ[3] = -30;//-30

    glClipPlane(GL_CLIP_PLANE0,equ);*/

    //now we enable the clip plane

    /*glEnable(GL_CLIP_PLANE0);{
    	glColor3f(0,0.3,0.8);	//blue

    	glPushMatrix();{
    		glTranslatef(50,0,30);
    		glutWireSphere(20, 20, 20);	//radius, slices(XY), stacks(Z) -- like earth
    	}glPopMatrix();

    }glDisable(GL_CLIP_PLANE0);*/



    //some gridlines along the field
    int i;

    //WILL draw grid IF the "canDrawGrid" is true:

    if(canDrawGrid == true)
    {

        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D,texid4);
        glRotatef(90,0,1,0);
        glNormal3f(1.0,0.0,0.0);
        draw_grid();
    //}
    //glPopMatrix();


    glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D,texid4);
        glTranslatef(0,0,0);
        glRotatef(90,1,0,0);
        glNormal3f(1.0,0.0,0.0);
        draw_grid();
    //glPopMatrix();

    glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D,texid4);
        glRotatef(90,1,0,0);
        glNormal3f(1.0,0.0,0.0);
        draw_grid();
    //glPopMatrix();

    glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D,texid4);
        glRotatef(90,1,0,0);
        glNormal3f(1.0,0.0,0.0);
        draw_grid();
    }
    glPopMatrix();

    /*glPushMatrix();{
    //glTranslatef(0,60,0);
    //glColor3f(1,0,0);
    glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D, texid2); // here texid corresponds a bitmap image.
        glBindTexture(GL_TEXTURE_2D, texid4);
    glColor3f(0.3, 0.3, 0.3);	//grey
    glBegin(GL_LINES);{
    	for(i=-10;i<=10;i++){

    		if(i==0)
    			continue;	//SKIP the MAIN axes

    		//lines parallel to Y-axis
    		glVertex3f(i*10, -100, 0);
    		glVertex3f(i*10,  100, 0);

    		//lines parallel to X-axis
    		glVertex3f(-100, i*10, 0);
    		glVertex3f( 100, i*10, 0);
    	}
    }glEnd();

    glDisable(GL_TEXTURE_2D);
    }glPopMatrix();*/
//}

// draw the two AXES
glColor3f(1, 1, 1);	//100% white
glBegin(GL_LINES);
{
    //Y axis
    glVertex3f(0, -150, 0);	// intentionally extended to -150 to 150, no big deal
    glVertex3f(0,  150, 0);

    //X axis
    glVertex3f(-150, 0, 0);
    glVertex3f( 150, 0, 0);
}
glEnd();


//ADD this line in the end --- if you use double buffer (i.e. GL_DOUBLE)
glutSwapBuffers();
}

void animate()
{
    //codes for any changes in Camera

    //cameraAngle += cameraAngleDelta;	// camera will rotate at 0.002 radians per frame.	// keep the camera steady NOW!!

    //codes for any changes in Models

    rectAngle -= 1;

    //MISSING SOMETHING? -- YES: add the following
    glutPostRedisplay();	//this will call the display AGAIN
}

void keyboardListener(unsigned char key, int x,int y)
{
    switch(key)
    {

    case '1':	//reverse the rotation of camera
        cameraAngle += cameraAngleDelta;
        break;
    case '2':	//reverse the rotation of camera
        cameraAngle -= cameraAngleDelta;
        break;
    case '3':	//reverse the rotation of camera
        if(r-3>0) r -= 3;
        break;
    case '4':	//reverse the rotation of camera
        r += 3;
        break;
    case '5':	//reverse the rotation of camera
        height += 3;
        break;
    case '6':	//reverse the rotation of camera
        height -= 3;
        break;
    case '7':	//increase rotation of camera by 10%
        cameraAngleDelta *= 1.1;
        break;

    case '8':	//decrease rotation
        cameraAngleDelta /= 1.1;
        break;

    case '9':	//toggle grids
        canDrawGrid = 1 - canDrawGrid;
        break;

    default:
        break;
    }
}

void init()
{
    //codes for initialization
    cameraAngle = 0;	//// init the cameraAngle
    cameraAngleDelta = 0.02;
    rectAngle = 0;
    height=200;
    canDrawGrid = true;
    r=150;
    func();


    //clear the screen
    glClearColor(BLACK, 0);

    /************************
    / set-up projection here
    ************************/
    //load the PROJECTION matrix
    glMatrixMode(GL_PROJECTION);

    //initialize the matrix
    glLoadIdentity();

    //give PERSPECTIVE parameters
    gluPerspective(70,	1,	0.1,	10000.0);
    //field of view in the Y (vertically)
    //aspect ratio that determines the field of view in the X direction (horizontally)
    //near distance
    //far distance
}

int main(int argc, char **argv)
{
    glutInit(&argc,argv);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(0, 0);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);	//Depth, Double buffer, RGB color

    glutCreateWindow("London Bridge");

    init();

    glEnable(GL_DEPTH_TEST);	//enable Depth Testing

    glutDisplayFunc(display);	//display callback function
    glutIdleFunc(animate);		//what you want to do in the idle time (when no drawing is occuring)

    //ADD keyboard listeners:
    glutKeyboardFunc(keyboardListener);

    glutMainLoop();		//The main loop of OpenGL

    return 0;
}
