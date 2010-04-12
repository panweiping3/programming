#include <QtGui>
#include <QtOpenGL>

#include <math.h>

#include "glwidget.h"

GLWidget::GLWidget(QWidget *parent)
: QGLWidget(parent)
{
	gear1 = gear2 = gear3 = 0;
	xRot = yRot = zRot = 0;
	gear1Rot = 0;
	
	QTimer *timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(advanceGears()));	
	timer->start(20);
}

GLWidget::~GLWidget()
{
	makeCurrent();
	glDeleteLists(gear1, 1);
	glDeleteLists(gear2, 1);
	glDeleteLists(gear1, 1);
}

void GLWidget::setXRotation(int angle)
{
	normalizeAngle(&angle);
	if (angle != xRot)
	{
		xRot = angle;
		emit xRotationChanged(angle);
		updateGL();
	}
}

void GLWidget::setYRotation(int angle)
{
	normalizeAngle(&angle);
	if (angle != yRot)
	{
		yRot = angle;
		emit yRotationChanged(angle);
		updateGL();
	}
}

void GLWidget::setZRotation(int angle)
{
	normalizeAngle(&angle);
	if (angle != zRot)
	{
		zRot = angle;
		emit zRotationChanged(angle);
		updateGL();
	}
}

void GLWidget::initializeGL()
{
	static const GLfloat lightPos[4] = {5.0f, 5.0f, 10.0f, 10.0f};
	static const GLfloat reflectance1[4] = {0.8f, 0.1f, 0.0f, 1.0f};
	static const GLfloat reflectance2[4] = {0.0f, 0.8f, 0.2f, 1.0f};
	static const GLfloat reflectance3[4] = {0.2f, 0.2f, 1.0f, 1.0f};
	
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);

	gear1 = makeGear(reflectance1, 1.0, 4.0, 1.0, 0.7, 20);
	gear2 = makeGear(reflectance2, 0.5, 2.0, 2.0, 0.7, 10);
	gear3 = makeGear(reflectance3, 1.3, 2.0, 0.5, 0.7, 10);
	
	glEnable(GL_NORMALIZE);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void GLWidget::paintGL()
{
	glGclear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
	glRotated(xRot / 16.0, 1.0, 0.0, 0.0);
	glRotated(yRot / 16.0, 0.0, 1.0, 0.0);
	glRotated(zRot / 16.0, 0.0, 0.0, 1.0);
	
	drawGear(gear1, -3.0, -2.0, 0.0, gear1Rot / 16.0);
	drawGear(gear2, +3.1, -2.0, 0.0, -2.0 * (gear1Rot / 16.0) -9.0);

	glRotated(+90.0, 1.0, 0.0, 0.0);
	drawGear(gear3, -3.1, -1.8, -2.2, +2.0 * (gear1Rot / 16.0) -2.0);
	
	glPopMatrix();
}

void GLWidget::resizeGL(int width, int height)
{
	int side = qMin(width, height);
	glViewport((width - size) / 2, (height - side) / 2, side, side);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentify();
	
	glFrustum(-1.0, +1.0, -1.0, 1.0, 5.0, 60.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentify();
	glTranslated();
}
















