// INCLUDES
#include "TextureBuilder.h"
#include "Model_3DS.h"
#include "GLTexture.h"
#include <glut.h>
#include <math.h>
////////// CAMERA CLASS AND SETUP
#define GLUT_KEY_ESCAPE 27
#define DEG2RAD(a) (a * 0.0174532925)
class Vector3f {
public:
	float x, y, z;

	Vector3f(float _x = 0.0f, float _y = 0.0f, float _z = 0.0f) {
		x = _x;
		y = _y;
		z = _z;
	}

	Vector3f operator+(Vector3f &v) {
		return Vector3f(x + v.x, y + v.y, z + v.z);
	}

	Vector3f operator-(Vector3f &v) {
		return Vector3f(x - v.x, y - v.y, z - v.z);
	}

	Vector3f operator*(float n) {
		return Vector3f(x * n, y * n, z * n);
	}

	Vector3f operator/(float n) {
		return Vector3f(x / n, y / n, z / n);
	}

	Vector3f unit() {
		return *this / sqrt(x * x + y * y + z * z);
	}

	Vector3f cross(Vector3f v) {
		return Vector3f(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
	}
};

class Camera {
public:
	Vector3f eye, center, up;

	Camera(float eyeX = 0.0f, float eyeY = 3.0f, float eyeZ = 1.0f, float centerX = 0.0f, float centerY = 3.0f, float centerZ = 0.0f, float upX = 0.0f, float upY = 1.0f, float upZ = 0.0f) {
		eye = Vector3f(eyeX, eyeY, eyeZ);
		center = Vector3f(centerX, centerY, centerZ);
		up = Vector3f(upX, upY, upZ);
		moveX(6);
		moveZ(-38);

	}

	void moveX(float d) {
		Vector3f right = up.cross(center - eye).unit();
		eye = eye + right * d;
		center = center + right * d;
	}

	void moveY(float d) {
		eye = eye + up.unit() * d;
		center = center + up.unit() * d;
	}

	void moveZ(float d) {
		Vector3f view = (center - eye).unit();
		eye = eye + view * d;
		center = center + view * d;
	}

	void rotateX(float a) {
		Vector3f view = (center - eye).unit();
		Vector3f right = up.cross(view).unit();
		view = view * cos(DEG2RAD(a)) + up * sin(DEG2RAD(a));
		up = view.cross(right);
		center = eye + view;
	}

	void rotateY(float a) {
		Vector3f view = (center - eye).unit();
		Vector3f right = up.cross(view).unit();
		view = view * cos(DEG2RAD(a)) + right * sin(DEG2RAD(a));
		right = view.cross(up);
		center = eye + view;
	}

	void look() {
		gluLookAt(
			eye.x, eye.y, eye.z,
			center.x, center.y, center.z,
			up.x, up.y, up.z
		);
	}
};

Camera camera;

void setupCamera() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, 640 / 480, 0.001, 100 + 10000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	camera.look();
}
int WIDTH = 1280;
int HEIGHT = 720;
#define GLUT_KEY_ESCAPE 27
#define DEG2RAD(a) (a * 0.0174532925)
GLuint tex;
char title[] = "3D Model Loader Sample";
// 3D Projection Options
GLdouble fovy = 45.0;
GLdouble aspectRatio = (GLdouble)WIDTH / (GLdouble)HEIGHT;
GLdouble zNear = 0.1;
GLdouble zFar = 100;

// VARIABLES INITIALIZATION


bool level1 = true;
bool firstview = true;
bool thirdview = false;


double xlighttranslation;
double zlighttranslation;
double xintensity = 0;
double yintensity = 0;
bool increaseintensity = true;

double xlighttranslation1;
double zlighttranslation1;
double xintensity1 = 0;
double yintensity1 = 0;
bool increaseintensity1 = true;
bool zincreaselight = true;

double xtranslateplayer = 0;
double ztranslateplayer = 0;
bool shoot = false;
double bulletZ = 0;
double bulletX = 0;
int playerhealth = 100;
int playerscore = 0;


double xtranslatezombie = 0;
bool moverightzombie = true;
bool moveleftzombie = false;
double xmaxzombie;
double  xminzombie;
double zmaxzombie;
bool zombiedie = false;
double counterzombie;

double xtranslatemonster = 0;
bool moverightmonster = true;
bool moveleftmonster = false;
double xmaxmonster;
double  xminmonster;
double zmaxmonster;
bool monsterdie = false;
double countermonster;


double xtranslateskeleton = 20;
bool moverightskeleton = false;
bool moveleftskeleton = true;
double xmaxskeleton;
double  xminskeleton;
double zmaxskeleton;
bool skeletondie = false;
double counterskeleton;


double xtranslatescion= 0;
bool moverightscion = true;
bool moveleftscion = false;
double xmaxscion;
double  xminscion;
double zmaxscion;
bool sciondie = false;
double counterscion = 0;





void print(int x, int y, char *string)
{
	int len, i;


	glRasterPos2f(x, y);


	len = (int)strlen(string);

	for (i = 0; i < len; i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[i]);
	}
}
class Vector
{
public:
	GLdouble x, y, z;
	Vector() {}
	Vector(GLdouble _x, GLdouble _y, GLdouble _z) : x(_x), y(_y), z(_z) {}
	//================================================================================================//
	// Operator Overloading; In C++ you can override the behavior of operators for you class objects. //
	// Here we are overloading the += operator to add a given value to all vector coordinates.        //
	//================================================================================================//
	void operator +=(float value)
	{
		x += value;
		y += value;
		z += value;
	}
};
Vector Eye(20, 5, 20);
Vector At(0, 0, 0);
Vector Up(0, 1, 0);
int cameraZoom = 0;
// Model Variables
Model_3DS model_house;
Model_3DS model_tree;
Model_3DS model_sky;
Model_3DS model_zombie;
Model_3DS model_skeleton;
Model_3DS model_monster;
Model_3DS model_player;
Model_3DS model_scion;
Model_3DS model_flag;
Model_3DS model_grasswall;
Model_3DS model_bullet;
Model_3DS model_rock;
// Textures
GLTexture tex_ground;
GLTexture tex_wall;
//=======================================================================
// Lighting Configuration Function
//=======================================================================
void InitLightSource(){
	// Enable Lighting for this OpenGL Program
	glEnable(GL_LIGHTING);

	// Enable Light Source number 0
	// OpengL has 8 light sources
	glEnable(GL_LIGHT0);

	// Define Light source 0 ambient light
	GLfloat ambient[] = { 0.2f, 0.3f, 0.6f, 1.0f };
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);

	// Define Light source 0 diffuse light
	GLfloat diffuse[] = { 0.2f, 0.3f, 0.6f, 1.0f };
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);

	// Define Light source 0 Specular light
	GLfloat specular[] = { 0.5f, 0.5f, 0.5f, 1.0f };
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);

	// Finally, define light source 0 position in World Space
	GLfloat light_position[] = { 0.0f, 10.0f, 0.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	glEnable(GL_LIGHT1);

	// Define Light source 0 ambient light
	GLfloat ambient1[] = { 0.1f, 0.1f, 0.1, 1.0f };
	glLightfv(GL_LIGHT1, GL_AMBIENT, ambient1);

	// Define Light source 0 diffuse light
	GLfloat diffuse1[] = { 0.5f, 0.5f, 0.5f, 1.0f };
	glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse1);

	// Define Light source 0 Specular light
	GLfloat specular1[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glLightfv(GL_LIGHT1, GL_SPECULAR, specular1);

	// Finally, define light source 0 position in World Space
	GLfloat light_position1[] = { 0.0f, 10.0f, 0.0f, 1.0f };
	glLightfv(GL_LIGHT1, GL_POSITION, light_position1);
}
//=======================================================================
// Material Configuration Function
//======================================================================
void InitMaterial()
{
	// Enable Material Tracking
	glEnable(GL_COLOR_MATERIAL);

	// Sich will be assigneet Material Properties whd by glColor
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	// Set Material's Specular Color
	// Will be applied to all objects
	GLfloat specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);

	// Set Material's Shine value (0->128)
	GLfloat shininess[] = { 96.0f };
	glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
}
//=======================================================================
// OpengGL Configuration Function
//=======================================================================
void myInit(void){
	glClearColor(0.0, 0.0, 0.0, 0.0);

	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();

	gluPerspective(fovy, aspectRatio, zNear, zFar);
	//*******************************************************************************************//
	// fovy:			Angle between the bottom and top of the projectors, in degrees.			 //
	// aspectRatio:		Ratio of width to height of the clipping plane.							 //
	// zNear and zFar:	Specify the front and back clipping planes distances from camera.		 //
	//*******************************************************************************************//

	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();

	//camera.look();
	//*******************************************************************************************//
	// EYE (ex, ey, ez): defines the location of the camera.									 //
	// AT (ax, ay, az):	 denotes the direction where the camera is aiming at.					 //
	// UP (ux, uy, uz):  denotes the upward orientation of the camera.							 //
	//*******************************************************************************************//

	//InitLightSource();

	InitMaterial();

	glEnable(GL_DEPTH_TEST);

	glEnable(GL_NORMALIZE);
}
//=======================================================================
// Render Ground Function
//========================================================================
void RenderGround()
{
	glDisable(GL_LIGHTING);	// Disable lighting 

	glColor3f(0.6, 0.6, 0.6);	// Dim the ground texture a bit

	glEnable(GL_TEXTURE_2D);	// Enable 2D texturing

	glBindTexture(GL_TEXTURE_2D, tex_ground.texture[0]);	// Bind the ground texture

	glPushMatrix();
	glTranslated(30, 0, 0);
	glScaled(2, 2, 2);
	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);	// Set quad normal direction.
	glTexCoord2f(0, 0);		// Set tex coordinates ( Using (0,0) -> (5,5) with texture wrapping set to GL_REPEAT to simulate the ground repeated grass texture).
	glVertex3f(-20, 0, -20);
	glTexCoord2f(5, 0);
	glVertex3f(20, 0, -20);
	glTexCoord2f(5, 5);
	glVertex3f(20, 0, 20);
	glTexCoord2f(0, 5);
	glVertex3f(-20, 0, 20);
	glEnd();
	glPopMatrix();

	glEnable(GL_LIGHTING);	// Enable lighting again for other entites coming throung the pipeline.

	glColor3f(1, 1, 1);	// Set material back to white instead of grey used for the ground texture.
}
void RenderWall() {
	glDisable(GL_LIGHTING);	// Disable lighting 

	glColor3f(0.6, 0.6, 0.6);	// Dim the ground texture a bit

	glEnable(GL_TEXTURE_2D);	// Enable 2D texturing

	glBindTexture(GL_TEXTURE_2D, tex_wall.texture[0]);	// Bind the ground texture

	glPushMatrix();
	glRotated(90, 0, 0, 1);

	glScaled(2, 2, 2);
	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);	// Set quad normal direction.
	glTexCoord2f(0, 0);		// Set tex coordinates ( Using (0,0) -> (5,5) with texture wrapping set to GL_REPEAT to simulate the ground repeated grass texture).
	glVertex3f(-20, 0, -20);
	glTexCoord2f(5, 0);
	glVertex3f(20, 0, -20);
	glTexCoord2f(5, 5);
	glVertex3f(20, 0, 20);
	glTexCoord2f(0, 5);
	glVertex3f(-20, 0, 20);
	glEnd();
	glPopMatrix();

	glEnable(GL_LIGHTING);	// Enable lighting again for other entites coming throung the pipeline.

	glColor3f(1, 1, 1);	// Set material back to white instead of grey used for the ground texture.
}
void drawsky() {
	glPushMatrix();
	glScaled(2, 2, 2);
	glColor3f(1, 0, 0);
	GLUquadricObj * qobj;
	qobj = gluNewQuadric();
	glTranslated(50, 0, 0);
	glRotated(90, 1, 0, 1);
	glBindTexture(GL_TEXTURE_2D, tex);
	gluQuadricTexture(qobj, true);
	gluQuadricNormals(qobj, GL_SMOOTH);
	gluSphere(qobj, 100, 100, 100);
	gluDeleteQuadric(qobj);
	glPopMatrix();
}
void drawBullet() {
	glColor3f(0.3, 0.3, 0.0);
	glPushMatrix();
	glTranslated(xtranslateplayer-4 ,2, 34+ bulletZ);
	glRotatef(90.f, 0, 1, 0);
	glScaled(0.02, 0.02, 0.02);
	model_bullet.Draw();
	//glutSolidSphere(0.3, 15, 15);
	glPopMatrix();
}
void drawrock() {
	glPushMatrix();
	glColor3f(0, 0, 0);
	glTranslatef(5, 0, 5);
	glScaled(0.07, 0.07, 0.07);
	model_rock.Draw();
	glPopMatrix();
}
void score() {
	char* p1s[20];
	glColor3f(0, 0, 0);
	sprintf((char *)p1s, "Current Score : %d", playerscore);
	print(10, 24, (char *)p1s);
}
void GameOver() {
	char* p1s[20];
	glColor3f(0, 0, 0);
	sprintf((char *)p1s, "Game Over your final Score is: %d", playerscore);
	print(10, 24, (char *)p1s);
}
void health() {
	char* p1s[20];
	glColor3f(0, 0, 0);
	sprintf((char *)p1s, " Health : %d", playerhealth);
	print(10, 26, (char *)p1s);
}
void drawtree() {
	glPushMatrix();
	glTranslatef(10, 0, 0);
	glScalef(0.7, 0.7, 0.7);
	model_tree.Draw();
	glPopMatrix();
}
void drawplayer() {
	glPushMatrix();
	glTranslated(xtranslateplayer, 0, ztranslateplayer);
	//glColor3f(0, 0, 0);
	//glTranslated(-7, -3, -1);
	glRotatef(90, 1, 0, 0);
	glRotatef(180, 0, 0, 1);
	//glRotatef(-90, 0, 0, 1);
	//glRotatef(90, 1, 0, 0);
	//glTranslatef(-6, -2, 30);
	glTranslated(4, -35, -1);
	//glTranslatef(5, 0, 10);
	//glScalef(0.05, 0.05, 0.05);
	glScalef(15, 15, 15);
	model_player.Draw();
	glPopMatrix();
}
void drawhouse() {
	glPushMatrix();
	glScalef(2, 2, 2);
	glRotatef(90.f, 1, 0, 0);
	model_house.Draw();
	glPopMatrix();
}
void drawzombie() {
	glPushMatrix();
	glTranslatef(20, 0, 10);
	zmaxzombie = -28;
	glRotated(90, 1, 0, 0);
	glTranslated(xtranslatezombie, 0, 0);
	//glColor3f(0, 0, 0);
	glScalef(0.05, 0.05, 0.05);
	model_zombie.Draw();
	glPopMatrix();
}
void drawmonster(){
	glPushMatrix();
	glTranslatef(20, 0, -20);
	zmaxmonster = -56;
	glRotated(90, 1, 0, 0);
	glTranslated(xtranslatemonster, 0, 0);
	//glColor3f(1, 0, 0);
	//glScalef(3,3, 3);
	glScalef(0.05, 0.05, 0.05);
	model_zombie.Draw();
	glPopMatrix();
}
void drawskeleton() {
	glPushMatrix();
	glTranslatef(20, 3, 25);
	zmaxskeleton = -14;
	glRotated(90, 1, 0, 0);
	glTranslated(xtranslateskeleton, 0,0);
	glColor3f(1, 1, 1);
	glScalef(0.07, 0.07, 0.07);
	model_skeleton.Draw();
	glPopMatrix();
}
void drawscion() {
	glPushMatrix();
	glTranslatef(20, 0, 32);
	glRotated(90, 1, 0, 0);
	zmaxscion = -7;
	glTranslated(xtranslatescion, 0, 0);
	xmaxmonster = xmaxmonster + xtranslatescion;
	xminmonster = xminmonster + xtranslatescion;
	glScalef(2, 2, 2);
	model_scion.Draw();
	glPopMatrix();
}
void drawflag() {
	glPushMatrix();
	glTranslatef(-4, 0, -33);
	glRotated(90, 1, 0, 0);
	glScalef(0.2, 0.2, 0.2);
	model_flag.Draw();
	glPopMatrix();
}
void drawgrasswall1() {
	glPushMatrix();
	glTranslatef(-6, 0, -40);
	glRotated(90, 1, 0, 0);
	glScalef(0.2, 0.2, 0.2);
	model_grasswall.Draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(3, 0, -40);
	glRotated(90, 1, 0, 0);
	glScalef(0.2, 0.2, 0.2);
	model_grasswall.Draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(6, 0, -40);
	glRotated(90, 1, 0, 0);
	glScalef(0.2, 0.2, 0.2);
	model_grasswall.Draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(12, 0, -40);
	glRotated(90, 1, 0, 0);
	glScalef(0.2, 0.2, 0.2);
	model_grasswall.Draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(18, 0, -40);
	glRotated(90, 1, 0, 0);
	glScalef(0.2, 0.2, 0.2);
	model_grasswall.Draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(24, 0, -40);
	glRotated(90, 1, 0, 0);
	glScalef(0.2, 0.2, 0.2);
	model_grasswall.Draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(30, 0, -40);
	glRotated(90, 1, 0, 0);
	glScalef(0.2, 0.2, 0.2);
	model_grasswall.Draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(36, 0, -40);
	glRotated(90, 1, 0, 0);
	glScalef(0.2, 0.2, 0.2);
	model_grasswall.Draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(42, 0, -40);
	glRotated(90, 1, 0, 0);
	glScalef(0.2, 0.2, 0.2);
	model_grasswall.Draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(48, 0, -40);
	glRotated(90, 1, 0, 0);
	glScalef(0.2, 0.2, 0.2);
	model_grasswall.Draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(54, 0, -40);
	glRotated(90, 1, 0, 0);
	glScalef(0.2, 0.2, 0.2);
	model_grasswall.Draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(60, 0, -40);
	glRotated(90, 1, 0, 0);
	glScalef(0.35, 0.2, 0.2);
	model_grasswall.Draw();
	glPopMatrix();
}
void drawgrasswall2() {
	glPushMatrix();
	glTranslatef(70, 0, -40);
	glRotated(90, 1, 0, 0);
	glRotated(90, 0, 0, 1);
	glScalef(0.35, 0.2, 0.2);
	model_grasswall.Draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(70, 0, -34);
	glRotated(90, 1, 0, 0);
	glRotated(90, 0, 0, 1);
	glScalef(0.35, 0.2, 0.2);
	model_grasswall.Draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(70, 0, -28);
	glRotated(90, 1, 0, 0);
	glRotated(90, 0, 0, 1);
	glScalef(0.35, 0.2, 0.2);
	model_grasswall.Draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(70, 0, -22);
	glRotated(90, 1, 0, 0);
	glRotated(90, 0, 0, 1);
	glScalef(0.35, 0.2, 0.2);
	model_grasswall.Draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(70, 0, -16);
	glRotated(90, 1, 0, 0);
	glRotated(90, 0, 0, 1);
	glScalef(0.35, 0.2, 0.2);
	model_grasswall.Draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(70, 0, -10);
	glRotated(90, 1, 0, 0);
	glRotated(90, 0, 0, 1);
	glScalef(0.35, 0.2, 0.2);
	model_grasswall.Draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(70, 0, -4);
	glRotated(90, 1, 0, 0);
	glRotated(90, 0, 0, 1);
	glScalef(0.35, 0.2, 0.2);
	model_grasswall.Draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(70, 0, 2);
	glRotated(90, 1, 0, 0);
	glRotated(90, 0, 0, 1);
	glScalef(0.35, 0.2, 0.2);
	model_grasswall.Draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(70, 0, 8);
	glRotated(90, 1, 0, 0);
	glRotated(90, 0, 0, 1);
	glScalef(0.35, 0.2, 0.2);
	model_grasswall.Draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(70, 0, 14);
	glRotated(90, 1, 0, 0);
	glRotated(90, 0, 0, 1);
	glScalef(0.35, 0.2, 0.2);
	model_grasswall.Draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(70, 0, 20);
	glRotated(90, 1, 0, 0);
	glRotated(90, 0, 0, 1);
	glScalef(0.35, 0.2, 0.2);
	model_grasswall.Draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(70, 0, 26);
	glRotated(90, 1, 0, 0);
	glRotated(90, 0, 0, 1);
	glScalef(0.35, 0.2, 0.2);
	model_grasswall.Draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(70, 0, 32);
	glRotated(90, 1, 0, 0);
	glRotated(90, 0, 0, 1);
	glScalef(0.35, 0.2, 0.2);
	model_grasswall.Draw();
	glPopMatrix();

}
void drawgrasswall3() {
	glPushMatrix();
	glTranslatef(-12, 0, -40);
	glRotated(90, 1, 0, 0);
	glRotated(-90, 0, 0, 1);
	glScalef(0.35, 0.2, 0.2);
	model_grasswall.Draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-12, 0, -34);
	glRotated(90, 1, 0, 0);
	glRotated(-90, 0, 0, 1);
	glScalef(0.35, 0.2, 0.2);
	model_grasswall.Draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-12, 0, -28);
	glRotated(90, 1, 0, 0);
	glRotated(-90, 0, 0, 1);
	glScalef(0.35, 0.2, 0.2);
	model_grasswall.Draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-12, 0, -22);
	glRotated(90, 1, 0, 0);
	glRotated(-90, 0, 0, 1);
	glScalef(0.35, 0.2, 0.2);
	model_grasswall.Draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-12, 0, -16);
	glRotated(90, 1, 0, 0);
	glRotated(-90, 0, 0, 1);
	glScalef(0.35, 0.2, 0.2);
	model_grasswall.Draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-12, 0, -10);
	glRotated(90, 1, 0, 0);
	glRotated(-90, 0, 0, 1);
	glScalef(0.35, 0.2, 0.2);
	model_grasswall.Draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-12, 0, -4);
	glRotated(90, 1, 0, 0);
	glRotated(-90, 0, 0, 1);
	glScalef(0.35, 0.2, 0.2);
	model_grasswall.Draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-12, 0, 2);
	glRotated(90, 1, 0, 0);
	glRotated(-90, 0, 0, 1);
	glScalef(0.35, 0.2, 0.2);
	model_grasswall.Draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-12, 0, 8);
	glRotated(90, 1, 0, 0);
	glRotated(-90, 0, 0, 1);
	glScalef(0.35, 0.2, 0.2);
	model_grasswall.Draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-12, 0, 14);
	glRotated(90, 1, 0, 0);
	glRotated(-90, 0, 0, 1);
	glScalef(0.35, 0.2, 0.2);
	model_grasswall.Draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-12, 0, 20);
	glRotated(90, 1, 0, 0);
	glRotated(-90, 0, 0, 1);
	glScalef(0.35, 0.2, 0.2);
	model_grasswall.Draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-12, 0, 26);
	glRotated(90, 1, 0, 0);
	glRotated(-90, 0, 0, 1);
	glScalef(0.35, 0.2, 0.2);
	model_grasswall.Draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-12, 0, 32);
	glRotated(90, 1, 0, 0);
	glRotated(-90, 0, 0, 1);
	glScalef(0.35, 0.2, 0.2);
	model_grasswall.Draw();
	glPopMatrix();

}
void drawmaze() {
	glPushMatrix();
	glTranslated(0,0,60);
	glPushMatrix();
	glTranslatef(-6, 0, -40);
	glRotated(90, 1, 0, 0);
	glScalef(0.2, 0.2, 0.2);
	model_grasswall.Draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(3, 0, -40);
	glRotated(90, 1, 0, 0);
	glScalef(0.2, 0.2, 0.2);
	model_grasswall.Draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(6, 0, -40);
	glRotated(90, 1, 0, 0);
	glScalef(0.2, 0.2, 0.2);
	model_grasswall.Draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(12, 0, -40);
	glRotated(90, 1, 0, 0);
	glScalef(0.2, 0.2, 0.2);
	model_grasswall.Draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(18, 0, -40);
	glRotated(90, 1, 0, 0);
	glScalef(0.2, 0.2, 0.2);
	model_grasswall.Draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(24, 0, -40);
	glRotated(90, 1, 0, 0);
	glScalef(0.2, 0.2, 0.2);
	model_grasswall.Draw();
	glPopMatrix();
	glPopMatrix();

	glPushMatrix();
	glTranslated(0, 0, 30);
	glPushMatrix();
	glTranslatef(-6, 0, -40);
	glRotated(90, 1, 0, 0);
	glScalef(0.2, 0.2, 0.2);
	model_grasswall.Draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(3, 0, -40);
	glRotated(90, 1, 0, 0);
	glScalef(0.2, 0.2, 0.2);
	model_grasswall.Draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(6, 0, -40);
	glRotated(90, 1, 0, 0);
	glScalef(0.2, 0.2, 0.2);
	model_grasswall.Draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(12, 0, -40);
	glRotated(90, 1, 0, 0);
	glScalef(0.2, 0.2, 0.2);
	model_grasswall.Draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(18, 0, -40);
	glRotated(90, 1, 0, 0);
	glScalef(0.2, 0.2, 0.2);
	model_grasswall.Draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(24, 0, -40);
	glRotated(90, 1, 0, 0);
	glScalef(0.2, 0.2, 0.2);
	model_grasswall.Draw();
	glPopMatrix();
	glPopMatrix();

	glPushMatrix();
	glTranslated(0,0,45);
	glPushMatrix();
	glTranslatef(18, 0, -40);
	glRotated(90, 1, 0, 0);
	glScalef(0.2, 0.2, 0.2);
	model_grasswall.Draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(24, 0, -40);
	glRotated(90, 1, 0, 0);
	glScalef(0.2, 0.2, 0.2);
	model_grasswall.Draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(30, 0, -40);
	glRotated(90, 1, 0, 0);
	glScalef(0.2, 0.2, 0.2);
	model_grasswall.Draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(36, 0, -40);
	glRotated(90, 1, 0, 0);
	glScalef(0.2, 0.2, 0.2);
	model_grasswall.Draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(42, 0, -40);
	glRotated(90, 1, 0, 0);
	glScalef(0.2, 0.2, 0.2);
	model_grasswall.Draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(48, 0, -40);
	glRotated(90, 1, 0, 0);
	glScalef(0.2, 0.2, 0.2);
	model_grasswall.Draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(54, 0, -40);
	glRotated(90, 1, 0, 0);
	glScalef(0.2, 0.2, 0.2);
	model_grasswall.Draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(60, 0, -40);
	glRotated(90, 1, 0, 0);
	glScalef(0.35, 0.2, 0.2);
	model_grasswall.Draw();
	glPopMatrix();
	glPopMatrix();
	/*glPushMatrix();
	glTranslatef(-6, 0, 0);
	glRotated(90, 1, 0, 0);
	glScalef(0.2, 0.2, 0.2);
	model_grasswall.Draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(3, 0, -30);
	glRotated(90, 1, 0, 0);
	glScalef(0.2, 0.2, 0.2);
	model_grasswall.Draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(6, 0, -30);
	glRotated(90, 1, 0, 0);
	glScalef(0.2, 0.2, 0.2);
	model_grasswall.Draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(12, 0, -10);
	glRotated(90, 1, 0, 0);
	glScalef(0.2, 0.2, 0.2);
	model_grasswall.Draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(18, 0, -10);
	glRotated(90, 1, 0, 0);
	glScalef(0.2, 0.2, 0.2);
	model_grasswall.Draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(24, 0, 10);
	glRotated(90, 1, 0, 0);
	glScalef(0.2, 0.2, 0.2);
	model_grasswall.Draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(30, 0, 10);
	glRotated(90, 1, 0, 0);
	glScalef(0.2, 0.2, 0.2);
	model_grasswall.Draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(36, 0, 30);
	glRotated(90, 1, 0, 0);
	glScalef(0.2, 0.2, 0.2);
	model_grasswall.Draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(42, 0,20);
	glRotated(90, 1, 0, 0);
	glScalef(0.2, 0.2, 0.2);
	model_grasswall.Draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(48, 0, 15);
	glRotated(90, 1, 0, 0);
	glScalef(0.2, 0.2, 0.2);
	model_grasswall.Draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(54, 0, 30);
	glRotated(90, 1, 0, 0);
	glScalef(0.2, 0.2, 0.2);
	model_grasswall.Draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(60, 0, 0);
	glRotated(90, 1, 0, 0);
	glScalef(0.35, 0.2, 0.2);
	model_grasswall.Draw();
	glPopMatrix();*/
}

void myDisplay(void)
{

		if (level1) {
			setupCamera();
			glPushMatrix();
			
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			GLfloat lightIntensity[] = { 0.0+xintensity, 0.0+yintensity, 0.0, 1.0f };
			GLfloat lightPosition[] = { 4.0f +xlighttranslation  , 0.0f    ,  -35.0f + zlighttranslation  , 0.0f }; // x,y,*,*
			glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
			glLightfv(GL_LIGHT0, GL_AMBIENT, lightIntensity);
			GLfloat lightIntensity1[] = { 0.0 + xintensity1, 0.0 + yintensity1, 0.0, 1.0f };
			GLfloat lightPosition1[] = { 0.0f + xlighttranslation1  , 0.0f    ,  0.0f + zlighttranslation1  , 0.0f };
			glLightfv(GL_LIGHT1, GL_POSITION, lightPosition1);
			glLightfv(GL_LIGHT1, GL_AMBIENT, lightIntensity1);
			
			// Draw Ground
			RenderGround();
			

			// Draw Tree Model
			drawtree();

			glPushMatrix();
			glTranslated(30, 0, 10);
			drawtree();
			glPopMatrix();

			glPushMatrix();
			glTranslated(50, 0, 30);
			drawtree();
		glPopMatrix();
		// Draw house Model
		drawhouse();
		drawflag();
		drawgrasswall1();
		drawgrasswall2();
		drawgrasswall3();
		// Draw Zombie

		if (zombiedie == false)
		drawzombie();
		if (monsterdie == false)
		drawmonster();
		if (skeletondie == false)
		drawskeleton();
		if (sciondie == false)
		drawscion();

		//draw palyer

		drawplayer();

		//sky box
		drawsky();
		
		
		if (shoot)
		drawBullet();

		//Draw health and score
		glPushMatrix();
		glTranslated(-40 + xtranslateplayer, 0, -4 + ztranslateplayer);
		if (playerhealth > 0) {
			health();
			score();
		}
		else {
			GameOver();
		}
		glPopMatrix();
		drawrock();
		glPushMatrix();
		glTranslated(20, 0,15);
		drawrock();
		glPopMatrix();

		glPushMatrix();
		glTranslated(30, 0, 20);
		drawrock();

		glPopMatrix();
		glPushMatrix();
		glTranslated(20, 0, -30);
		drawrock();
		glPopMatrix();

		glPopMatrix();
		glPushMatrix();
		glTranslated(60, 0, -30);
		drawrock();
		glPopMatrix();

		glPopMatrix();
		glPushMatrix();
		glTranslated(50, 0, 15);
		drawrock();
		glPopMatrix();

		glPopMatrix();
		glPushMatrix();
		glTranslated(40, 0, -30);
		drawrock();
		glPopMatrix();


	//wall 1
	/*glPushMatrix();
	glTranslated(-20, 3, 20);
	glScaled(0.0001, 0.1, 1);
	RenderWall();
	glPopMatrix();*/
	// wall 2
	//glPushMatrix();
	//glTranslated(-20, 3, 20);
	////glScaled(0.0001, 0.1, 1);
	//RenderWall();
	//glPopMatrix();

	glutSwapBuffers();
		}
		else {
		setupCamera();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		GLfloat lightIntensity[] = { 0.0 + xintensity, 0.0 + yintensity, 0.0, 1.0f };
		GLfloat lightPosition[] = { 4.0f + xlighttranslation  , 0.0f    ,  -35.0f + zlighttranslation  , 0.0f };

		GLfloat lightIntensity1[] = { 0.0 + xintensity1/2, 0.0 + yintensity1/2, 0.0, 1.0f };
		GLfloat lightPosition1[] = { 0.0f + xlighttranslation1  , 0.0f    ,  0.0f + zlighttranslation1  , 0.0f };

		//GLfloat lightPosition[] = { 4.0f + xlighttranslation  , 0.0f    , -35.0f + zlighttranslation  , 0.0f };
		glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
		glLightfv(GL_LIGHT0, GL_AMBIENT, lightIntensity);

		glLightfv(GL_LIGHT1, GL_POSITION, lightPosition1);
		glLightfv(GL_LIGHT1, GL_AMBIENT, lightIntensity1);
		// Draw Ground
		RenderGround();
		drawgrasswall1();
		drawgrasswall2();
		drawgrasswall3();
		drawmaze();
		glPushMatrix();
		glTranslated(67, 0, 0);
		drawflag();
		glPopMatrix();
		if (zombiedie == false)
			drawzombie();
		if (monsterdie == false)
			drawmonster();

		if (sciondie == false)
			drawscion();
		
		//sky box
		drawplayer();
		drawsky();
		
		
		//draw palyer
		
		if (shoot)
			drawBullet();
	
		//Draw health and score
		glPushMatrix();
		glTranslated(-40 + xtranslateplayer, 0, -4 + ztranslateplayer);
		if (playerhealth > 0) {
			health();
			score();
		}
		else {
			GameOver();
		}
		glPopMatrix();

		glutSwapBuffers();
		}
	
	
}



//=======================================================================
// Keyboard Function
//=======================================================================
void myKeyboard(unsigned char key, int x, int y)
{
	if (playerhealth > 0) {
		float d = 1;
		switch (key) {


		case 'd':

			if (xtranslateplayer > 70) {

			}
			else if (level1 && (ztranslateplayer < -32 && ztranslateplayer > -46 && xtranslateplayer <= -1 && xtranslateplayer >= -2)) {

			}
			else if (!level1 && (ztranslateplayer < -28 && ztranslateplayer > -36 && xtranslateplayer <= 18 && xtranslateplayer >= 17)) {}
			else {
				xtranslateplayer = xtranslateplayer + 1;
				xlighttranslation = xlighttranslation + 1;
				bulletX++;
				camera.moveX(-1);
			}
			break;
		case 'a':
			if (xtranslateplayer < -2) {
			}
			else if (level1 && (ztranslateplayer < -32 && ztranslateplayer > -46 && xtranslateplayer <= 13 && xtranslateplayer >= 12)) {}
			else if ((!level1 && ztranslateplayer < -14 && ztranslateplayer > -21 && xtranslateplayer <= 37 && xtranslateplayer >= 36) || (!level1 && ztranslateplayer < -44 && ztranslateplayer > -53 && xtranslateplayer <= 37 && xtranslateplayer >= 36)) {}
			else {
				xtranslateplayer = xtranslateplayer - 1;
				xlighttranslation = xlighttranslation - 1;
				bulletX--;
				camera.moveX(1);
			}
			break;
		case 's':
			if (ztranslateplayer > 3) {
			}
			else if (level1 && (ztranslateplayer <= -43 && ztranslateplayer >= -44 && xtranslateplayer > -1 && xtranslateplayer < 12)) {}
			else if ((!level1 && ztranslateplayer < -20 && ztranslateplayer > -22 && xtranslateplayer <= 36 && xtranslateplayer >= -3) || (!level1 && ztranslateplayer < -53 && ztranslateplayer > -55 && xtranslateplayer <= 36 && xtranslateplayer >= -3) || (!level1 && ztranslateplayer < -36 && ztranslateplayer > -38 && xtranslateplayer <= 70 && xtranslateplayer >= 18)) {}
			else {
				ztranslateplayer = ztranslateplayer + 1;
				zlighttranslation = zlighttranslation + 1;
				camera.moveZ(-1);
			}
			break;
		case 'w':
			if (ztranslateplayer < -70) {
			}
			else if (level1 && (ztranslateplayer <= -31 && ztranslateplayer >= -32 && xtranslateplayer > -1 && xtranslateplayer < 12)) {}
			else if ((!level1 && ztranslateplayer <= -13 && ztranslateplayer >= -14 && xtranslateplayer <= 36 && xtranslateplayer >= -3) || (!level1 && ztranslateplayer <= -43 && ztranslateplayer >= -44 && xtranslateplayer <= 36 && xtranslateplayer >= -3) || (!level1 && ztranslateplayer <= -27 && ztranslateplayer >= -28 && xtranslateplayer <= 70 && xtranslateplayer >= 18)) {}
			else {
				ztranslateplayer = ztranslateplayer - 1;
				zlighttranslation = zlighttranslation - 1;
				camera.moveZ(1);
			}
			break;
		case ' ':
			PlaySound(TEXT("M9-pistol-sound-effect.wav"), NULL, SND_FILENAME | SND_ASYNC);
			shoot = true;
			break;
		case 'c':
			if (thirdview == false) {
				camera.moveZ(-4);
				thirdview = true;
			}

			else {
				thirdview = false;
				camera.moveZ(4);
			}
			break;
		case 'e':
			printf("%f,%f,%f,%f,%f,%f,%f,%f,%f\n", camera.eye.x, camera.eye.y, camera.eye.z, camera.center.x, camera.center.y, camera.center.z, camera.up.x, camera.up.y, camera.up.z);
			
			break;
		case 'r':
			camera.eye.x = -6.00000+xtranslateplayer; camera.eye.y = 3.000000; camera.eye.z = 39.000000+ztranslateplayer; camera.center.x = -6.000000+xtranslateplayer; camera.center.y = 3.000000; camera.center.z = 38.000000+ztranslateplayer; camera.up.x = 0.000000; camera.up.y = 1.000000; camera.up.z = 0.000000;
			firstview = true;
			thirdview = false;
			break;
		case 'u':
			camera.moveY(d);
			break;
		case 'i':
			camera.moveY(-d);
			break;
		case 'o':
			camera.moveX(d);
			break;
		case 'j':
			camera.moveX(-d);
			break;
		case 'k':
			camera.moveZ(d);
			break;
		case 'l':
			camera.moveZ(-d);
			break;

		case GLUT_KEY_ESCAPE:
			exit(EXIT_SUCCESS);
		}

		glutPostRedisplay();
	}
}

//=======================================================================
// Motion Function
//=======================================================================
void myMotion(int x, int y)
{
	y = HEIGHT - y;

	if (cameraZoom - y > 0)
	{
		Eye.x += -0.1;
		Eye.z += -0.1;
	}
	else
	{
		Eye.x += 0.1;
		Eye.z += 0.1;
	}

	cameraZoom = y;

	glLoadIdentity();	//Clear Model_View Matrix

	gluLookAt(Eye.x, Eye.y, Eye.z, At.x, At.y, At.z, Up.x, Up.y, Up.z);	//Setup Camera with modified paramters


	GLfloat light_position[] = { 0.0f, 10.0f, 0.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	glutPostRedisplay();	//Re-draw scene 
}


//=======================================================================
// Mouse Function
//=======================================================================
/////////  Mouse Function
//void myMouse(int x, int y)
//{
//	camera.rotateX(x);;//it moves the red square center to the mouse location.
//	camera.rotateY(y);
//	glutPostRedisplay();
//}

//=======================================================================
// Reshape Function
//=======================================================================
void myReshape(int w, int h)
{
	if (h == 0) {
		h = 1;
	}

	WIDTH = w;
	HEIGHT = h;

	// set the drawable region of the window
	glViewport(0, 0, w, h);

	// set up the projection matrix 
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(fovy, (GLdouble)WIDTH / (GLdouble)HEIGHT, zNear, zFar * 1000);

	// go back to modelview matrix so we can move the objects about
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(Eye.x, Eye.y, Eye.z, At.x, At.y, At.z, Up.x, Up.y, Up.z);
}

//=======================================================================
// Assets Loading Function
//=======================================================================
void LoadAssets()
{
	// Loading Model files
	model_house.Load("Models/house/house.3DS");
	model_tree.Load("Models/tree/Tree1.3ds");
	model_skeleton.Load("Models/skeleton/skeleton.3ds");
	//model_monster.Load("Models/monster/INJ_iOS_VILLAIN_Doomsday_Injustice.3ds");
	model_zombie.Load("Models/zombie/Zombie.3DS");
	model_scion.Load("Models/scion/scion.3ds");
	model_player.Load("Models/player/rtm_gf_machine_gun.3ds");
	model_flag.Load("Models/flag/flag.3ds");
	model_grasswall.Load("Models/grasswall/TallGrass.3ds");
	model_bullet.Load("Models/bullet/sniper.3ds");
	model_rock.Load("Models/rock/Small Rock.3ds");
	// Loading texture files
	tex_ground.Load("Textures/ground.bmp");
	loadBMP(&tex, "Textures/blu-sky-3.bmp", true);


}
void Special(int key, int x, int y) {
	float a = 1.0;

	switch (key) {
	case GLUT_KEY_UP:
		camera.rotateX(a);
		break;
	case GLUT_KEY_DOWN:
		camera.rotateX(-a);
		break;
	case GLUT_KEY_LEFT:
		camera.rotateY(a);
		break;
	case GLUT_KEY_RIGHT:
		camera.rotateY(-a);
		break;
	}

	glutPostRedisplay();
}
void animation() {
	
	if (playerhealth > 0) {
		if (xintensity >= 1)
			increaseintensity = false;
		if (xintensity <= 0)
			increaseintensity = true;
		if (increaseintensity == true) {
			xintensity = xintensity + 0.001;
			yintensity = yintensity + 0.001;
		}
		else {
			xintensity = xintensity - 0.001;
			yintensity = yintensity - 0.001;
		}

		if (xintensity1 >= 1)
			increaseintensity1 = false;
		if (xintensity1 <= 0)
			increaseintensity1 = true;
		if (increaseintensity1 == true) {
			xintensity1 = xintensity1 + 0.001;
			yintensity1 = yintensity1 + 0.001;
		}
		else {
			xintensity1 = xintensity1 - 0.001;
			yintensity1 = yintensity1 - 0.001;
		}
		if (zlighttranslation1 >= 70)
			zincreaselight = false;
		else
			zincreaselight = true;
		if (zincreaselight == true) {
			zlighttranslation1 = zlighttranslation1 + 1;
		}
		else {
			zlighttranslation1 = zlighttranslation1 + 1;
		}
		if (level1) {
			if (xtranslatezombie > 45) {
				moveleftzombie = true;
				moverightzombie = false;
				
			}
			if (xtranslatezombie < -25) {
				moverightzombie = true;
				moveleftzombie = false;
			}
			if (moverightzombie == true) {
				xtranslatezombie = xtranslatezombie + 0.05;
				xlighttranslation1 = xlighttranslation1 + 0.05;
			}
			if (moveleftzombie == true) {
				xtranslatezombie = xtranslatezombie - 0.05;
				xlighttranslation1 = xlighttranslation1 - 0.05;
			}

			if (xtranslatemonster > 45) {
				moveleftmonster = true;
				moverightmonster = false;
			}
			if (xtranslatemonster < -25) {
				moverightmonster = true;
				moveleftmonster = false;
			}
			if (moverightmonster == true)
				xtranslatemonster = xtranslatemonster + 0.1;
			if (moveleftmonster == true)
				xtranslatemonster = xtranslatemonster - 0.1;



			if (xtranslateskeleton > 45) {
				moveleftskeleton = true;
				moverightskeleton = false;
			}
			if (xtranslateskeleton < -25) {
				moverightskeleton = true;
				moveleftskeleton = false;
			}
			if (moverightskeleton == true)
				xtranslateskeleton = xtranslateskeleton + 0.03;
			if (moveleftskeleton == true)
				xtranslateskeleton = xtranslateskeleton - 0.03;

			if (xtranslatescion > 45) {
				moveleftscion = true;
				moverightscion = false;
			}
			if (xtranslatescion < -25) {
				moverightscion = true;
				moveleftscion = false;
			}
			if (moverightscion == true)
				xtranslatescion = xtranslatescion + 0.01;
			if (moveleftscion == true)
				xtranslatescion = xtranslatescion - 0.01;



			if (shoot == true) {
				bulletZ -= 1;
				if (bulletZ < -70) {
					shoot = false;
					bulletZ = ztranslateplayer;
				}
				if (bulletZ < -32 && bulletZ > -42 && bulletX > -1 && bulletX < 12) {
					shoot = false;
					bulletZ = ztranslateplayer;
				}
				else if (!sciondie && bulletZ > zmaxscion - 4 && bulletZ < zmaxscion && bulletX<(26 + xtranslatescion + 1) && bulletX >(26 + xtranslatescion - 2)) {
					sciondie = true;
					shoot = false;
					bulletZ = ztranslateplayer;
					playerscore += 10;
				}
				else if (!skeletondie && bulletZ > zmaxskeleton - 4 && bulletZ < zmaxskeleton && bulletX<(26 + xtranslateskeleton + 1) && bulletX >(26 + xtranslateskeleton - 2)) {
					skeletondie = true;
					shoot = false;
					bulletZ = ztranslateplayer;
					playerscore += 10;
				}
				else if (!zombiedie && bulletZ > zmaxzombie - 4 && bulletZ < zmaxzombie && bulletX<(26 + xtranslatezombie + 2) && bulletX >(26 + xtranslatezombie - 2)) {
					zombiedie = true;
					shoot = false;
					bulletZ = ztranslateplayer;
					playerscore += 10;
				}
				else if (!monsterdie && bulletZ > zmaxmonster - 4 && bulletZ < zmaxmonster && bulletX<(26 + xtranslatemonster + 3) && bulletX >(26 + xtranslatemonster - 3)) {
					monsterdie = true;
					shoot = false;
					bulletZ = ztranslateplayer;
					playerscore += 10;
				}


			}

			if (!sciondie && xtranslateplayer<(26 + xtranslatescion + 1) && xtranslateplayer >(26 + xtranslatescion - 1) && ztranslateplayer > zmaxscion - 3 && ztranslateplayer <= zmaxscion + 2) {
				playerhealth--;
			}
			else if (!skeletondie && xtranslateplayer<(26 + xtranslateskeleton + 1) && xtranslateplayer >(26 + xtranslateskeleton - 1) && ztranslateplayer > zmaxskeleton - 3 && ztranslateplayer <= zmaxskeleton + 2) {
				playerhealth--;
			}
			else if (!zombiedie && xtranslateplayer<(26 + xtranslatezombie + 3) && xtranslateplayer >(26 + xtranslatezombie - 3) && ztranslateplayer > zmaxzombie - 4 && ztranslateplayer <= zmaxzombie + 2) {
				playerhealth--;
			}
			else if (!monsterdie && xtranslateplayer<(26 + xtranslatemonster + 4) && xtranslateplayer >(26 + xtranslatemonster - 4) && ztranslateplayer > zmaxmonster - 4 && ztranslateplayer <= zmaxmonster + 2) {
				playerhealth--;
			}

			if (xtranslateplayer < 3 && xtranslateplayer >0 && ztranslateplayer > -71 && ztranslateplayer < -67) {
				level1 = false;
				camera.moveZ(ztranslateplayer);
				ztranslateplayer = 0;
				monsterdie = false;
				sciondie = false;
				zombiedie = false;

			}
			if (sciondie == true) {
				counterscion = counterscion + 1;
				if (counterscion == 100) {
					counterscion = 0;
					drawscion();
					sciondie = false;
				}

			}

			if (zombiedie == true) {
				counterzombie = counterzombie + 1;
				if (counterzombie == 100) {
					counterzombie = 0;
					drawzombie();
					zombiedie = false;
				}

			}

			if (skeletondie == true) {
				counterskeleton = counterskeleton + 1;
				if (counterskeleton == 100) {
					counterskeleton = 0;
					drawskeleton();
					skeletondie = false;
				}

			}

			if (monsterdie == true) {
				countermonster = countermonster + 1;
				if (countermonster == 100) {
					countermonster = 0;
					drawmonster();
					monsterdie = false;
				}


			}

			glutPostRedisplay();
		}
		else {
			if (xtranslatezombie > 45) {
				moveleftzombie = true;
				moverightzombie = false;
			}
			if (xtranslatezombie < -25) {
				moverightzombie = true;
				moveleftzombie = false;
			}
			if (moverightzombie == true)
				xtranslatezombie = xtranslatezombie + 0.05;
			if (moveleftzombie == true)
				xtranslatezombie = xtranslatezombie - 0.05;


			if (xtranslatemonster > 45) {
				moveleftmonster = true;
				moverightmonster = false;
			}
			if (xtranslatemonster < -25) {
				moverightmonster = true;
				moveleftmonster = false;
			}
			if (moverightmonster == true)
				xtranslatemonster = xtranslatemonster + 0.1;
			if (moveleftmonster == true)
				xtranslatemonster = xtranslatemonster - 0.1;

			if (xtranslatescion > 45) {
				moveleftscion = true;
				moverightscion = false;
			}
			if (xtranslatescion < -25) {
				moverightscion = true;
				moveleftscion = false;
			}
			if (moverightscion == true)
				xtranslatescion = xtranslatescion + 0.01;
			if (moveleftscion == true)
				xtranslatescion = xtranslatescion - 0.01;



			if (shoot == true) {
				bulletZ -= 1;
				if (bulletZ < -70) {
					shoot = false;
					bulletZ = ztranslateplayer;
				}
				if (bulletZ < -32 && bulletZ > -42 && bulletX > -1 && bulletX < 12) {
					shoot = false;
					bulletZ = ztranslateplayer;
				}
				else if (!sciondie && bulletZ > zmaxscion - 4 && bulletZ < zmaxscion && bulletX<(26 + xtranslatescion + 1) && bulletX >(26 + xtranslatescion - 2)) {
					sciondie = true;
					shoot = false;
					bulletZ = ztranslateplayer;
					playerscore += 10;
				}
				else if (!zombiedie && bulletZ > zmaxzombie - 4 && bulletZ < zmaxzombie && bulletX<(26 + xtranslatezombie + 2) && bulletX >(26 + xtranslatezombie - 2)) {
					zombiedie = true;
					shoot = false;
					bulletZ = ztranslateplayer;
					playerscore += 10;
				}
				else if (!monsterdie && bulletZ > zmaxmonster - 4 && bulletZ < zmaxmonster && bulletX<(26 + xtranslatemonster + 3) && bulletX >(26 + xtranslatemonster - 3)) {
					monsterdie = true;
					shoot = false;
					bulletZ = ztranslateplayer;
					playerscore += 10;
				}


			}

			if (!sciondie && xtranslateplayer<(26 + xtranslatescion + 1) && xtranslateplayer >(26 + xtranslatescion - 1) && ztranslateplayer > zmaxscion - 3 && ztranslateplayer <= zmaxscion + 2) {
				playerhealth--;
			}

			else if (!zombiedie && xtranslateplayer<(26 + xtranslatezombie + 1) && xtranslateplayer >(26 + xtranslatezombie - 1) && ztranslateplayer > zmaxzombie - 4 && ztranslateplayer <= zmaxzombie + 2) {
				playerhealth--;
			}
			else if (!monsterdie && xtranslateplayer<(26 + xtranslatemonster + 1) && xtranslateplayer >(26 + xtranslatemonster - 1) && ztranslateplayer > zmaxmonster - 4 && ztranslateplayer <= zmaxmonster + 2) {
				playerhealth--;
			}


			if (xtranslateplayer < 71 && xtranslateplayer >65 && ztranslateplayer > -71 && ztranslateplayer < -63) {
				playerhealth = 0;
			}
			if (sciondie == true) {
				counterscion = counterscion + 1;
				if (counterscion == 100) {
					counterscion = 0;
					drawscion();
					sciondie = false;
				}

			}

			if (zombiedie == true) {
				counterzombie = counterzombie + 1;
				if (counterzombie == 100) {
					counterzombie = 0;
					drawzombie();
					zombiedie = false;
				}

			}



			if (monsterdie == true) {
				countermonster = countermonster + 1;
				if (countermonster == 100) {
					countermonster = 0;
					drawmonster();
					monsterdie = false;
				}


			}
		}
	}
	else {
	glPushMatrix();
	glTranslated(-40 + xtranslateplayer, 0, -4 + ztranslateplayer);
	GameOver();
	glPopMatrix();
}
		glutPostRedisplay();
}

void mouseClicks(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		
		PlaySound(TEXT("M9-pistol-sound-effect.wav"), NULL, SND_FILENAME | SND_ASYNC);
		shoot = true;
	}
}
//=======================================================================
// Main Function
//=======================================================================
void main(int argc, char** argv)
{
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	glutInitWindowSize(WIDTH, HEIGHT);

	glutInitWindowPosition(100, 150);

	glutCreateWindow(title);

	glutDisplayFunc(myDisplay);

	glutKeyboardFunc(myKeyboard);

	glutMotionFunc(myMotion);

	glutMouseFunc(mouseClicks);

	glutSpecialFunc(Special);

	glutIdleFunc(animation);

	glutReshapeFunc(myReshape);

	myInit();

	LoadAssets();
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);

	glShadeModel(GL_SMOOTH);

	glutMainLoop();
}