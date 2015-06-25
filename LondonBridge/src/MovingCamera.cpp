#include "MovingCamera.h"
#ifdef _WIN32
#define  WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <GL/gl.h>
#pragma comment (lib, "opengl32.lib")
#pragma comment (lib, "glu32.lib")
#endif
/*MovingCamera::MovingCamera()
{
    //ctor
}

/*MovingCamera::~MovingCamera()
{
    //dtor
}*/

MovingCamera::MovingCamera(float x, float y, float z) {
	memset(Transform, 0, 16*sizeof(float));
	Transform[0] = 1.0f;
	Transform[5] = 1.0f;
	Transform[10] = -1.0f;
	Transform[15] = 1.0f;
	Transform[12] = x; Transform[13] = y; Transform[14] = z;

	Right=&Transform[0];
	Up=&Transform[4];
	Forward=&Transform[8];
	Position=&Transform[12];
}

MovingCamera::~MovingCamera() {}

/*
This one does pretty much the same as gluLookAt, just that it doesnt require
to extract the vectors for gluLookAt and have it rebuild the matrix we already
got.
*/
void MovingCamera::setView() {
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	float viewmatrix[16]={//Remove the three - for non-inverted z-axis
						  Transform[0], Transform[4], -Transform[8], 0,
						  Transform[1], Transform[5], -Transform[9], 0,
						  Transform[2], Transform[6], -Transform[10], 0,

						  -(Transform[0]*Transform[12] +
						  Transform[1]*Transform[13] +
						  Transform[2]*Transform[14]),

						  -(Transform[4]*Transform[12] +
						  Transform[5]*Transform[13] +
						  Transform[6]*Transform[14]),

						  //add a - like above for non-inverted z-axis
						  (Transform[8]*Transform[12] +
						  Transform[9]*Transform[13] +
						  Transform[10]*Transform[14]), 1};
	glLoadMatrixf(viewmatrix);


}

void MovingCamera::moveLoc(float x, float y, float z, float distance) {
	float dx=x*Transform[0] + y*Transform[4] + z*Transform[8];
	float dy=x*Transform[1] + y*Transform[5] + z*Transform[9];
	float dz=x*Transform[2] + y*Transform[6] + z*Transform[10];
	Transform[12] += dx * distance;
	Transform[13] += dy * distance;
	Transform[14] += dz * distance;
}

void MovingCamera::moveGlob(float x, float y, float z, float distance) {
	Transform[12] += x * distance;
	Transform[13] += y * distance;
	Transform[14] += z * distance;
}

/*
Here we let OpenGls (most likely quite optimized) functions do the work.
Note that its transformations already are in local coords.
*/
void MovingCamera::rotateLoc(float deg, float x, float y, float z) {
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadMatrixf(Transform);
	glRotatef(deg, x,y,z);
	glGetFloatv(GL_MODELVIEW_MATRIX, Transform);
	glPopMatrix();
}

/*
We have to invert the rotations to get the global axes in local coords.
Luckily thats just the transposed in this case.
*/
void MovingCamera::rotateGlob(float deg, float x, float y, float z) {
	float dx=x*Transform[0] + y*Transform[1] + z*Transform[2];
	float dy=x*Transform[4] + y*Transform[5] + z*Transform[6];
	float dz=x*Transform[8] + y*Transform[9] + z*Transform[10];
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadMatrixf(Transform);
	glRotatef(deg, dx,dy,dz);
	glGetFloatv(GL_MODELVIEW_MATRIX, Transform);
	glPopMatrix();
}

/*void MovingCamera :: setModelViewMatrix(void) {
    // load modelview matrix with existing camera values
    float m[16]; Vector3 eVec(eye.x, eye.y, eye.z); // a vector version of eye
    m[0] =  u.x; m[4] =  u.y; m[8]  =  u.z;  m[12] = -eVec.dot(u);
    m[1] =  v.x; m[5] =  v.y; m[9]  =  v.z;  m[13] = -eVec.dot(v);
    m[2] =  n.x; m[6] =  n.y; m[10] =  n.z;  m[14] = -eVec.dot(n);
    m[3] =  0;   m[7] =  0;   m[11] =  0;    m[15] = 1.0;
    glMatrixMode(GL_MODELVIEW); glLoadMatrixf(m); // load OpenGL’s modelview matrix
    }
void MovingCamera:: set(Point3 Eye, Point3 look, Vector3 up) {
    // create a modelview matrix and send it to OpenGL
    eye.set(Eye); // store the given eye position n.set(eye.x - look.x, eye.y - look.y, eye.z - look.z); // make n u.set(up.cross(n)); // make u = up X n n.normalize(); u.normalize(); // make them unit length v.set(n.cross(u));  // make v =  n X u setModelViewMatrix(); // tell OpenGL }
    */
