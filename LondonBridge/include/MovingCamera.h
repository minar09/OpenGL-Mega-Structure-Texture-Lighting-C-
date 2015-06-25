#ifndef MOVINGCAMERA_H
#define MOVINGCAMERA_H


class MovingCamera
{

     /*private:
         Point3 eye;
         Vector3 u,v,n;
         double viewAngle, aspect, nearDist, farDist; // view volume shape
         void setModelviewMatrix(); // tell OpenGL where the camera is
     public:
         MovingCamera(); // default constructor
         void set(Point3 eye, Point3 look, Vector3 up); // like gluLookAt()
         void roll(float angle); // roll it
         void pitch(float angle); // increase pitch
         void yaw(float angle); // yaw it
         void slide(float delU, float delV, float delN); // slide it
         void setShape(float vAng, float asp, float nearD, float farD); };*/
public:
    float const *Right, *Up, *Forward;
    float *Position;
private:
    float Transform[16];

public:
    MovingCamera(float x=0.0f, float y=0.0f, float z=0.0f);
    ~MovingCamera();

    void setView();
    void moveLoc(float x, float y, float z, float distance=1);
    void moveGlob(float x, float y, float z, float distance=1);
    void rotateLoc(float deg, float x, float y, float z);
    void rotateGlob(float deg, float x, float y, float z);
};

/*class MovingCamera {
public:
	float const *Right, *Up, *Forward;
	float *Position;
private:
	float Transform[16];

public:
	MovingCamera(float x=0.0f, float y=0.0f, float z=0.0f);
	~MovingCamera();

	void setView();
	void moveLoc(float x, float y, float z, float distance=1);
	void moveGlob(float x, float y, float z, float distance=1);
	void rotateLoc(float deg, float x, float y, float z);
	void rotateGlob(float deg, float x, float y, float z);
};*/

#endif // MOVINGCAMERA_H
