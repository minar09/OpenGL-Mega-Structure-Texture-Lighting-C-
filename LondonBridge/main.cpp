#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include <windows.h>
#include<GL/glut.h>
#include "MovingCamera.h"


#define BLACK 0, 0, 0
#define pi 2*acos(0)

//make a global variable -- for tracking the anglular position of camera
double cameraAngle;			//in radian
double cameraAngleDelta;
double height,r,eyex,eyey;
double centerx,centery,centerz;
double upx,upy,upz;
double rectAngle;	//in degree
bool canDrawGrid;
double Angle;
int diffuse_flag;
int ambient_flag;
int specular_flag;
int spot_flag;
struct point
{
    double x,y,z;
};


GLUquadric* IDquadric=gluNewQuadric() ;//=new GLUquadricObj(

MovingCamera camobj(00,00,400);


GLuint texid1,texid2,texid3, texid4,texid5,texid6,texid7,texid8;
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

    texid1 =LoadBitmap("lll.bmp");   /*here bkg1.bmp is the bitmap image to be used as texture, texid is global varible declared to uniquely  identify this particular image*/
    texid2 =LoadBitmap("wall.bmp");
    texid3=LoadBitmap("sky.bmp");
    texid4=LoadBitmap("water.bmp");
    texid5=LoadBitmap("up_base.bmp");
    texid6=LoadBitmap("road.bmp");
    texid7=LoadBitmap("halfwall.bmp");
    texid8=LoadBitmap("top.bmp");
}
void base(float radius,int slices,int stacks)
{
    struct point points[100][100];
    int i,j;
    double h,r;
    for(i=0; i<=stacks; i++)
    {
        h=radius*sin(((double)i/(double)stacks)*(pi/2));
        r=sqrt(radius*radius-h*h);
        for(j=0; j<=slices; j++)
        {
            points[i][j].x=r*cos(((double)j/(double)slices)*2*pi);
            points[i][j].y=r*sin(((double)j/(double)slices)*2*pi);
            points[i][j].z=h;
        }

    }
    for(i=0; i<stacks; i++)
    {
        for(j=0; j<slices; j++)
        {
            glColor3f((double)i/(double)stacks,(double)i/(double)stacks,(double)i/(double)stacks);
            glBegin(GL_QUADS);
            {
                glVertex3f(points[i][j].x,points[i][j].y,points[i][j].z);
                glVertex3f(points[i][j+1].x,points[i][j+1].y,points[i][j+1].z);
                glVertex3f(points[i+1][j+1].x,points[i+1][j+1].y,points[i+1][j+1].z);
                glVertex3f(points[i+1][j].x,points[i+1][j].y,points[i+1][j].z);

            }
            glEnd();
        }

    }
}

void half_tower()
{

    glPushMatrix();
    {
        glTranslatef(0,60,0);
        //glColor3f(1,0,0);
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texid2); // here texid corresponds a bitmap image.
        gluQuadricNormals(IDquadric,GLU_FILL);
        gluQuadricTexture(IDquadric, GLU_TRUE);

        gluCylinder(IDquadric,30 ,30 ,40,25,25);
        gluCylinder(IDquadric,20 ,20 ,20,15,15);
        gluCylinder(IDquadric,25 ,25 ,30,20,20);
        gluCylinder(IDquadric,10 ,10 ,20,15,15);
        gluCylinder(IDquadric,5 ,5 ,10,5,5);
        gluCylinder(IDquadric,12 ,12 ,22,12,12);
        for(int i=0;i<40;i++)
           gluCylinder(IDquadric,i ,i ,40,i,i);

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
    glPushMatrix();
    {

        glRotatef(-90,0,-1,0);
        glTranslatef(-70,45,-15);
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

        glRotatef(90,0,0,-1);
        glTranslatef(-45,-15,70);
        //glColor3f(0,1,0);
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D,texid7);
        glNormal3f(1.0,0.0,0.0);
        glBegin(GL_POLYGON);
        glTexCoord2f(0,0);
        glVertex3f(0,0,0);
        glTexCoord2f(1,0);
        glVertex3f(0,30,0);
        glTexCoord2f(1,1);
        glVertex3f(0,30,65);
        glTexCoord2f(0,1);
        glVertex3f(0,0,65);
        glEnd();
        glDisable(GL_TEXTURE_2D);
    }
    glPopMatrix();


    glPushMatrix();
    {


        glTranslatef(-15,45,70);
        //glColor3f(0,1,0);
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D,texid7);
        glNormal3f(1.0,0.0,0.0);
        glBegin(GL_POLYGON);
        glTexCoord2f(0,0);
        glVertex3f(0,0,0);
        glTexCoord2f(1,0);
        glVertex3f(0,30,0);
        glTexCoord2f(1,1);
        glVertex3f(0,30,65);
        glTexCoord2f(0,1);
        glVertex3f(0,0,65);
        glEnd();
        glDisable(GL_TEXTURE_2D);
    }
    glPopMatrix();

     glPushMatrix();
    {


        glTranslatef(15,45,70);
        //glColor3f(0,1,0);
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D,texid7);
        glNormal3f(1.0,0.0,0.0);
        glBegin(GL_POLYGON);
        glTexCoord2f(0,0);
        glVertex3f(0,0,0);
        glTexCoord2f(1,0);
        glVertex3f(0,30,0);
        glTexCoord2f(1,1);
        glVertex3f(0,30,66);
        glTexCoord2f(0,1);
        glVertex3f(0,0,65);
        glEnd();
        glDisable(GL_TEXTURE_2D);
    }
    glPopMatrix();
     glPopMatrix();

     glPushMatrix();
    {
glTranslatef(15,75,70);
 glRotatef(90,0,0,1);
       // glTranslatef(15,45,70);
        //glColor3f(0,1,0);
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D,texid7);
        glNormal3f(1.0,0.0,0.0);
        glBegin(GL_POLYGON);
        glTexCoord2f(0,0);
        glVertex3f(0,0,0);
        glTexCoord2f(1,0);
        glVertex3f(0,30,0);
        glTexCoord2f(1,1);
        glVertex3f (0,30,65);
        glTexCoord2f(0,1);
        glVertex3f(0,0,65);
        glEnd();
        glDisable(GL_TEXTURE_2D);
    }
    glPopMatrix();






}

void draw_grid()
{
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



void up_linker(float radius,int slices,int stacks)
{

	struct point points[100][100];
	int i,j;
	double h,r;
	for(i=0;i<=stacks;i++)
	{
		h=radius*sin(((double)i/(double)stacks)*(pi/2));

		r=sqrt(radius*radius-h*h);
		r=4;
		for(j=0;j<=slices;j++)
		{
			points[i][j].x=r*cos(((double)j/(double)slices)*2*pi);
			points[i][j].y=r*sin(((double)j/(double)slices)*2*pi);
			points[i][j].z=h;
		}

	}
	for(i=0;i<stacks;i++)
	{
		for(j=0;j<slices;j++)
		{
		    glBindTexture(GL_TEXTURE_2D,texid7);
			glColor3f(0.5,0.5,.5);
			glBegin(GL_QUADS);{
				glVertex3f(points[i][j].x,points[i][j].y,points[i][j].z);
				glVertex3f(points[i][j+1].x,points[i][j+1].y,points[i][j+1].z);
				glVertex3f(points[i+1][j+1].x,points[i+1][j+1].y,points[i+1][j+1].z);
				glVertex3f(points[i+1][j].x,points[i+1][j].y,points[i+1][j].z);

			}
			glColor3f(1,1,1);
			glEnd();
		}

	}
}
void up_link()
{
        glPushMatrix();
    {
          glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D,texid8);

        glTranslatef(50,-12,120);
        glRotated(-90,0,1,0);

        up_linker(95,6,7);
        glTranslatef(-50,+12,-120);
        glTranslatef(46,14,120);
        up_linker(95,6,7);
        glRotated(-90,0,1,0);
        //glColor3f(0,1,0);
      /*  glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D,texid8);
        glNormal3f(1.0,0.0,0.0);
        glBegin(GL_POLYGON);
        glTexCoord2f(0,0);
        glVertex3f(0,0,0);
        glTexCoord2f(1,0);
        glVertex3f(0,20,0);
        glTexCoord2f(1,1);
        glVertex3f(0,20,100);
        glTexCoord2f(0,1);
        glVertex3f(0,0,100);
        glEnd();
        glDisable(GL_TEXTURE_2D);*/
    }
    glPopMatrix();
}

void up_link_side()
{
    glPushMatrix();
    {
        glTranslatef(50,-10,120);
        glRotated(-90,0,1,0);

        //glColor3f(0,1,0);
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D,texid1);
        glNormal3f(1.0,0.0,0.0);
        glBegin(GL_POLYGON);
        glTexCoord2f(0,0);
        glVertex3f(0,0,0);
        glTexCoord2f(1,0);
        glVertex3f(0,20,0);
        glTexCoord2f(1,1);
        glVertex3f(0,20,100);
        glTexCoord2f(0,1);
        glVertex3f(0,0,100);
        glEnd();
        glDisable(GL_TEXTURE_2D);
    }
    glPopMatrix();
}

void side_way()
{
    glPushMatrix();
    {
        glTranslatef(170,-15,30);
        glRotated(-90,0,1,0);

        //glColor3f(0,1,0);
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D,texid6);
        glNormal3f(1.0,0.0,0.0);
        glBegin(GL_POLYGON);
        glTexCoord2f(0,0);
        glVertex3f(0,0,0);
        glTexCoord2f(1,0);
        glVertex3f(0,30,0);
        glTexCoord2f(1,1);
        glVertex3f(0,30,100);
        glTexCoord2f(0,1);
        glVertex3f(0,0,100);
        glEnd();
        glDisable(GL_TEXTURE_2D);
    }
    glPopMatrix();

    glPushMatrix();
    {
        glTranslatef(-75,-15,30);
        glRotated(-90,0,1,0);

        //glColor3f(0,1,0);
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D,texid6);
        glNormal3f(1.0,0.0,0.0);
        glBegin(GL_POLYGON);
        glTexCoord2f(0,0);
        glVertex3f(0,0,0);
        glTexCoord2f(1,0);
        glVertex3f(0,30,0);
        glTexCoord2f(1,1);
        glVertex3f(0,30,100);
        glTexCoord2f(0,1);
        glVertex3f(0,0,100);
        glEnd();
        glDisable(GL_TEXTURE_2D);
    }
    glPopMatrix();
}

void down_angle_road()
{
    glPushMatrix();
    {
        glTranslatef(55,-10,120);
        glRotated(-55,0,1,0);

        //glColor3f(0,1,0);
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D,texid6);
        glNormal3f(1.0,0.0,0.0);
        glBegin(GL_POLYGON);
        glTexCoord2f(0,0);
        glVertex3f(0,0,0);
        glTexCoord2f(1,0);
        glVertex3f(0,20,0);
        glTexCoord2f(1,1);
        glVertex3f(0,20,65);
        glTexCoord2f(0,1);
        glVertex3f(0,0,65);
        glEnd();
        glDisable(GL_TEXTURE_2D);
    }
    glPopMatrix();







}

void down_angle_road_rev()
{
    glPushMatrix();
    {
        glTranslatef(40,0,120);
        glRotated(45,0,1,0);

        //glColor3f(0,1,0);
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D,texid6);
        glNormal3f(1.0,0.0,0.0);
        glBegin(GL_POLYGON);
        glTexCoord2f(0,0);
        glVertex3f(0,-20,-65);
        glTexCoord2f(1,0);
        glVertex3f(0,0,-65);
        glTexCoord2f(1,1);
        glVertex3f(0,20,0);
        glTexCoord2f(0,1);
        glVertex3f(0,0,0);
        glEnd();
        glDisable(GL_TEXTURE_2D);
    }
    glPopMatrix();



}




void drawsphere(float radius,int slices,int stacks)
{

    struct point points[100][100];
    int i,j;
    double h,r;
    for(i=0; i<=stacks; i++)
    {
        h=radius*sin(((double)i/(double)stacks)*(pi/2));

        r=sqrt(radius*radius-h*h);
        r=1;
        for(j=0; j<=slices; j++)
        {
            points[i][j].x=r*cos(((double)j/(double)slices)*2*pi);
            points[i][j].y=r*sin(((double)j/(double)slices)*2*pi);
            points[i][j].z=h;
        }

    }
    for(i=0; i<stacks; i++)
    {
        for(j=0; j<slices; j++)
        {
            //glColor3f((double)i/(double)stacks,(double)i/(double)stacks,(double)i/(double)stacks);
            glColor3f(0.5,0.5,0.5);
            glBegin(GL_QUADS);
            {
                glVertex3f(points[i][j].x,points[i][j].y,points[i][j].z);
                glVertex3f(points[i][j+1].x,points[i][j+1].y,points[i][j+1].z);
                glVertex3f(points[i+1][j+1].x,points[i+1][j+1].y,points[i+1][j+1].z);
                glVertex3f(points[i+1][j].x,points[i+1][j].y,points[i+1][j].z);

            }
            glEnd();
        }

    }
}
void drawspheress(float radius,int slices,int stacks)
{

    struct point points[100][100];
    int i,j;
    double h,r;
    for(i=0; i<=stacks; i++)
    {
        h=radius*sin(((double)i/(double)stacks)*(pi/2));

        r=sqrt(radius*radius-h*h);
        r=.5;
        for(j=0; j<=slices; j++)
        {
            points[i][j].x=r*cos(((double)j/(double)slices)*2*pi);
            points[i][j].y=r*sin(((double)j/(double)slices)*2*pi);
            points[i][j].z=h;
        }

    }
    for(i=0; i<stacks; i++)
    {
        for(j=0; j<slices; j++)
        {
            glBindTexture(GL_TEXTURE_2D,texid7);
            glColor3f(0,0,1);
            glBegin(GL_QUADS);
            {
                glVertex3f(points[i][j].x,points[i][j].y,points[i][j].z);
                glVertex3f(points[i][j+1].x,points[i][j+1].y,points[i][j+1].z);
                glVertex3f(points[i+1][j+1].x,points[i+1][j+1].y,points[i+1][j+1].z);
                glVertex3f(points[i+1][j].x,points[i+1][j].y,points[i+1][j].z);

            }
            glColor3f(1,1,1);
            glEnd();
        }

    }
}
void one_side()
{
    glPushMatrix();
    {


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
            glVertex3f(0,30,10);
            glTexCoord2f(0,1);
            glVertex3f(0,0,1);
            glEnd();
            glDisable(GL_TEXTURE_2D);
            glTranslatef(-15,-45,-40);
        }
        glPopMatrix();
    }

}


void lighting()
{
    //Global white ambient light
    //glEnable(GL_LIGHTING);
    if(ambient_flag==1)
    {
        glShadeModel(GL_SMOOTH);
        glEnable(GL_NORMALIZE);
        GLfloat global_ambient[] = { 1, 1, 1, 1.0 }; //white light
        glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);
        glEnable(GL_LIGHTING);

        GLfloat diffuseDir[] = {0.5, 0.5, 0.5, 1.0}; //Color (0.5, 0.2, 0.2)
        GLfloat lightDir[] = {-1.0, 0.5, 0.5, 0.0}; //Coming from the direction (-1, 0.5, 0.5)
        glLightfv(GL_LIGHT2, GL_DIFFUSE, diffuseDir);
        glLightfv(GL_LIGHT2, GL_POSITION, lightDir);
        glEnable(GL_LIGHT2);
    }

    //Diffuse Light
    if(specular_flag==1)
    {
        /*GLfloat diffuseDir[] = {0.5, 0.5, 0.5, 1.0}; //Color (0.5, 0.2, 0.2)
        GLfloat lightDir[] = {-1.0, 0.5, 0.5, 0.0}; //Coming from the direction (-1, 0.5, 0.5)
        glLightfv(GL_LIGHT2, GL_DIFFUSE, diffuseDir);
        glLightfv(GL_LIGHT2, GL_POSITION, lightDir);
        glEnable(GL_LIGHT2);*/


        GLfloat light_emission_white[] = {1.0, 1.0, 1.0, 1.0};
        GLfloat light_emission_blue[] = {0.0, 0.0, 1.0, 1.0};
        GLfloat light_emission_de[] = {0.0, 0.0, 0.0, 1.0};
        GLfloat diffusePoint[] = {0.5, 0.5, 0.5, 1.0}; //Color (0.5, 0.5, 0.5)
        //GLfloat position[] = {-100.0, -100.0, 50.0, 1.0}; //Positioned at (-10, -10, 5)
        GLfloat position[] = {100.0*cos(Angle),100.0*sin(Angle),-100,1.0};
        glLightfv(GL_LIGHT1, GL_DIFFUSE, diffusePoint);
        glLightfv(GL_LIGHT1, GL_POSITION, position);

        if(diffuse_flag==1)
        {
            glLightfv(GL_LIGHT1, GL_DIFFUSE, light_emission_white);
            glLightfv(GL_LIGHT1, GL_POSITION, position);
        }
        else if(diffuse_flag==2)
        {
            glLightfv(GL_LIGHT1, GL_DIFFUSE, light_emission_blue);
            glLightfv(GL_LIGHT1, GL_POSITION, position);
        }
        else
        {
            glLightfv(GL_LIGHT1, GL_DIFFUSE, light_emission_de);
            glLightfv(GL_LIGHT1, GL_POSITION, position);
        }


        GLfloat mat_specular[] = { 0.5, 0.5, 0.5, 1.0 }; //equal to the light source
        GLfloat high_shininess[] = { 100.0 }; //high value  mirror like
        //glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
        //glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
        //  glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
        //  glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
        glEnable(GL_LIGHT1);

        //diffuse light
        //GLfloat position[] = {-10.0*cos(Angle),-10.0*sin(Angle),5,1.0};
        //GLfloat position[] = {0,0,200,1};
        //glLightfv(GL_LIGHT2, GL_POSITION, position);

        /*if(diffuse_flag==1)
            glMaterialfv(GL_FRONT, GL_EMISSION, light_emission_blue);
        else if(diffuse_flag==2)
            glMaterialfv(GL_FRONT, GL_EMISSION, light_emission_white);
        else
            glMaterialfv(GL_FRONT, GL_EMISSION, light_emission_de);*/
        glPushMatrix();
        //glTranslatef(0,0,0);
        glTranslatef (100.0*cos(Angle),100.0*sin(Angle),100);  // change angle based on key
        glutSolidSphere(3, 20, 20);
        glPopMatrix();
    }

    /*GLfloat diffusePoint[] = {0.5, 0.5, 0.5, 1.0}; //Color (0.5, 0.5, 0.5)
    GLfloat position[] = {-10.0, -10.0, 5.0, 1.0}; //Positioned at (-10, -10, 5)
    glLightfv(GL_LIGHT1, GL_DIFFUSE, diffusePoint);
    glLightfv(GL_LIGHT1, GL_POSITION, position);*/




    //Spot Light
    if(spot_flag==1)
    {
        //glDisable(GL_LIGHT0);
        GLfloat diffusePoint[] = {1, 1, 1, 0.0};
        glLightfv(GL_LIGHT0, GL_DIFFUSE, diffusePoint);
        glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 30.0); // a cutoff angle of 30
        glLightf(GL_LIGHT0,GL_SPOT_EXPONENT, 4.0); // ε = 4.0
        GLfloat dir[] = {-1.0, 0.0, 0.0}; // the spotlight’s direction
        glLightfv(GL_LIGHT0,GL_SPOT_DIRECTION, dir);
        glEnable(GL_LIGHT0);


        /*GLfloat position[] = {0.0, 0.0, 0.0, 1.0};
        GLfloat diffusePoint[] = {1, 1, 1, 1.0};
                glLightfv(GL_LIGHT2, GL_DIFFUSE, diffusePoint);
                glLightfv(GL_LIGHT2, GL_POSITION, position);
            glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 30.0); // a cutoff angle of 30
            //glLightf(GL_LIGHT2,GL_SPOT_EXPONENT, 4.0); // ε = 4.0
            GLfloat dir[] = {1.0, 0.0, 0.0}; // the spotlight’s direction
            glLightfv(GL_LIGHT2,GL_SPOT_DIRECTION, dir);
            glEnable(GL_LIGHT2);*/
    }



    //GLfloat lmodel_ambient[] = { .3, .3, .3, 1.0 }; //color of the global ambient light
    //glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);




    /*GLfloat spotPosition[] = {2.0f, 4.0f, 0.0f, 1.0f};
    GLfloat spotDirection[] = {0.0f, -1.0f, 0.0f, 1.0f};

    glLightfv(GL_LIGHT0, GL_POSITION, spotPosition);
    glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 30);
    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spotDirection);*/


}


void display()
{

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

    //gluLookAt(eyex, eyey, height,		centerx,centery,centerz,		upx,upy,upz);//150 is radius
    camobj.setView();
    //gluLookAt(r*cos(cameraAngle), r*sin(cameraAngle), height,		0,0,0,		0,0,1);//150 is radius
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
    glColor3f(0,0,0.3);
    glRotatef(45,0,0,1);
    half_tower();
    glTranslatef(0,120,0);
    half_tower();
    glRotatef(45,0,0,1);

    glColor3f(0.5,0,0.5);
    glRotatef(-135,0,0,1);
    up_link();
    //glTranslatef(0,0,10);
    //up_link();
    glColor3f(0.2,0,0);
    glTranslatef(5,0,-90);
    down_angle_road();
    glTranslatef(-5,0,+90);

    glTranslatef(-45,5,-55);
    //glColor3f(0,0.5,0);
    down_angle_road_rev();
    glTranslatef(45,-5,55);


///rod akte hobe

    glTranslatef(90,15,45);
    //glRotatef(-90,0,1,0);
    drawsphere(65,3,4);
    //glRotatef(+90,0,1,0);
    glTranslatef(-90,-15,-45);

    glTranslatef(100,15,45);
    //glRotatef(-90,0,1,0);
    drawsphere(55,3,4);
    //glRotatef(+90,0,1,0);
    glTranslatef(-100,-15,-45);
    glTranslatef(110,15,45);
    //glRotatef(-90,0,1,0);
    drawsphere(45,3,4);
    //glRotatef(+90,0,1,0);
    glTranslatef(-110,-15,-45);

    glTranslatef(120,15,45);
    //glRotatef(-90,0,1,0);
    drawsphere(35,3,4);
    //glRotatef(+90,0,1,0);
    glTranslatef(-120,-15,-40);



    glTranslatef(90,-12,40);
    //glRotatef(-90,0,1,0);
    drawsphere(65,3,4);
    //glRotatef(+90,0,1,0);
    glTranslatef(-90,12,-40);

    glTranslatef(100,-12,40);
    //glRotatef(-90,0,1,0);
    drawsphere(55,3,4);
    //glRotatef(+90,0,1,0);
    glTranslatef(-100,12,-40);
    glTranslatef(110,-12,40);
    //glRotatef(-90,0,1,0);
    drawsphere(45,3,4);
    //glRotatef(+90,0,1,0);
    glTranslatef(-110,12,-40);

    glTranslatef(120,-12,40);
    //glRotatef(-90,0,1,0);
    drawsphere(35,3,4);
    //glRotatef(+90,0,1,0);
    glTranslatef(-120,12,-40);




    glTranslatef(-90,10,40);
    //glRotatef(-90,0,1,0);
    drawsphere(65,3,4);
    //glRotatef(+90,0,1,0);
    glTranslatef(+90,-10,-40);

    glTranslatef(-100,10,40);
    //glRotatef(-90,0,1,0);
    drawsphere(55,3,4);
    //glRotatef(+90,0,1,0);
    glTranslatef(+100,-10,-40);
    glTranslatef(-110,10,40);
    //glRotatef(-90,0,1,0);
    drawsphere(45,3,4);
    //glRotatef(+90,0,1,0);
    glTranslatef(+110,-10,-40);

    glTranslatef(-120,10,40);
    //glRotatef(-90,0,1,0);
    drawsphere(35,3,4);
    //glRotatef(+90,0,1,0);
    glTranslatef(+120,-10,-35);



    glTranslatef(-90,-15,35);
    //glRotatef(-90,0,1,0);
    drawsphere(65,3,4);
    //glRotatef(+90,0,1,0);
    glTranslatef(90,+15,-35);

    glTranslatef(-100,-15,35);
    //glRotatef(-90,0,1,0);
    drawsphere(55,3,4);
    //glRotatef(+90,0,1,0);
    glTranslatef(100,+15,-35);
    glTranslatef(-110,-15,35);
    //glRotatef(-90,0,1,0);
    drawsphere(45,3,4);
    //glRotatef(+90,0,1,0);
    glTranslatef(+110,+15,-35);

    glTranslatef(-120,-15,35);
    //glRotatef(-90,0,1,0);
    drawsphere(35,3,4);
    //glRotatef(+90,0,1,0);

    glTranslatef(+120,+15,-35);

    glRotatef(90,0,0,1);

    one_side();

    glRotatef(90,0,0,-1);


    //up_link();
    glPushMatrix();
    {
        glTranslatef(+75,+13,115);

        glRotatef(135,0,1,0);
        drawspheress(115,3,8);
        glTranslatef(-75,-13,-115);

    }
    glPopMatrix();

    glPushMatrix();
    {
        glTranslatef(+75,-10,115);

        glRotatef(135,0,1,0);
        drawspheress(115,3,8);
        glTranslatef(-75,+10,-115);
    }
    glPopMatrix();




    glPushMatrix();
    {
        glTranslatef(-160,-13,29);

        glRotatef(45,0,1,0);
        drawspheress(115,3,8);
        glTranslatef(160,13,-29);
    }
    glPopMatrix();


    glPushMatrix();
    {
        glTranslatef(-160,10,29);

        glRotatef(45,0,1,0);
        drawspheress(115,3,8);
        glTranslatef(160,-10,-29);
    }
    glPopMatrix();
    side_way();
    glTranslatef(60,0,122);
    base(15,5,6);
    drawsphere(20,3,8);
    glTranslatef(-60,0,-122);
    glTranslatef(-60,0,122);

    base(15,5,6);
    drawsphere(20,3,8);

    glTranslatef(60,0,-122);
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

//lighting
    lighting();

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
        camobj.rotateLoc(10,0,1,0);
        break;
    case '2':	//reverse the rotation of camera
        cameraAngle -= cameraAngleDelta;
        camobj.rotateLoc(-10,0,1,0);
        break;
    case '3':	//reverse the rotation of camera
        if(r-3>0) r -= 3;
        camobj.rotateLoc(10,1,0,0);
        break;
    case '4':	//reverse the rotation of camera
        r += 3;
        camobj.rotateLoc(-10,1,0,0);
        break;
    case '5':	//reverse the rotation of camera
        height += 3;
        camobj.rotateGlob(10,1,0,1);
        break;
    case '6':	//reverse the rotation of camera
        height -= 3;
        camobj.rotateGlob(-10,1,0,1);
        break;

    case 'w':	//change light
        diffuse_flag=2;
        break;

    case 'b':	//change light
        diffuse_flag=1;
        break;

    case 'p':	//change light
        diffuse_flag=0;
        spot_flag=0;
        specular_flag=0;
        ambient_flag=0;
        break;

    case 'a':	//ambient light
        ambient_flag=1;
        break;

    case 'd':	//ambient light
        specular_flag=1;
        break;

    case 's':	//ambient light
        spot_flag=1;
        break;

    case '0':	//ambient light
        Angle+=0.03;
        break;

        /*case '7':	//increase rotation of camera by 10%
            cameraAngleDelta *= 1.1;
            break;

        case '8':	//decrease rotation
            cameraAngleDelta /= 1.1;
            break;

        case '9':	//toggle grids
            canDrawGrid = 1 - canDrawGrid;
            break;*/

    default:
        break;
    }
}

void specialKeyListener(int key, int x,int y)
{
    switch(key)
    {
    case GLUT_KEY_DOWN:		//down arrow key
        height -= 3.0;
        eyex -= 3;
        //eyey -= 3;
        camobj.moveLoc(0,30,0,1);
        break;
    case GLUT_KEY_UP:		// up arrow key
        height += 3.0;
        eyex += 3;
        //eyey += 3;
        camobj.moveLoc(0,-30,0,1);
        break;

    case GLUT_KEY_RIGHT:
        cameraAngle += 0.03;
        camobj.moveLoc(-30,0,0,1);
        break;
    case GLUT_KEY_LEFT:
        cameraAngle -= 0.03;
        camobj.moveLoc(30,0,0,1);
        break;

    case GLUT_KEY_PAGE_UP:
        camobj.moveLoc(0,0,30,1);
        break;
    case GLUT_KEY_PAGE_DOWN:
        camobj.moveLoc(0,0,-30,1);
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
    eyex=200;
    eyey=200;
    centerx=0,centery=0,centerz=0;
    upx=0,upy=0,upz=1;
    canDrawGrid = true;
    r=150;
    //func();
    Angle = 0;
    diffuse_flag = 0;
    ambient_flag = 0;
    specular_flag = 0;
    spot_flag = 0;

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
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(0, 0);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);	//Depth, Double buffer, RGB color

    glutCreateWindow("London Bridge");

    init();

    glEnable(GL_DEPTH_TEST);	//enable Depth Testing

    glutDisplayFunc(display);	//display callback function
    glutIdleFunc(animate);		//what you want to do in the idle time (when no drawing is occuring)

    //ADD keyboard listeners:
    glutKeyboardFunc(keyboardListener);
    glutSpecialFunc(specialKeyListener);

    glutMainLoop();		//The main loop of OpenGL

    return 0;
}
