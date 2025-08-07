#include "pch.h"
#include "CAdminControl.h"
#include <gl/GL.h>

CAdminControl::CAdminControl()
{
}

CAdminControl::~CAdminControl()
{
}

void CAdminControl::Draw()
{
	// ì_ÇÃï`âÊ
	glColor3f(1.0, 1.0, 1.0);
	glPointSize(10.0);
	glBegin(GL_POINTS);
	glVertex2f(-1.0, 0.5);
	glVertex2f(0.0, -0.5);
	glVertex2f(1.0, 0.5);
	glVertex2f(-1.0, 0.5);
	glEnd();

	// ê¸ÇÃï`âÊ;
	glColor3f(1.0, 1.0, 1.0);
	glLineWidth(2.0);
	glBegin(GL_LINE_STRIP);
	glVertex2f(-1.0, 0.5);
	glVertex2f(0.0, -0.5);
	glVertex2f(1.0, 0.5);
	glVertex2f(-1.0, 0.5);
	glEnd();
}
