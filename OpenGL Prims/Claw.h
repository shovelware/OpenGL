#ifndef CLAW_H
#define CLAW_H

#include "stdafx.h"

class Claw  {
private:
	void drawBox(const float x, const float y)
	{
		glBegin(GL_QUADS);
		glVertex2d(-(x / 2), -(y / 2));
		glVertex2d(+(x / 2), -(y / 2));
		glVertex2d(+(x / 2), +(y / 2));
		glVertex2d(-(x / 2), +(y / 2));
		glEnd();
	}

	float xConv(const int x)
	{
		return -1.0 + ((2.0 / screenW) * x);
	}

	float yConv(const int y)
	{
		return 1.0 - ((2.0 / screenH) * y);
	}

	float xMeas(const int x)
	{
		return (2.0 / screenW) * x;
	}

	float yMeas(const int y)
	{
		return (2.0 / screenH) * y;
	}

	void setGLCol(const float r, const float g, const float b)
	{
		if (r <= 1 && g <= 1 && b <= 1)
			glColor3f(r, g, b);
		else glColor3f(r / 255, g / 255, b / 255);
	}

	void setGLColArr(const float col[3])
	{
		if (col[0] <= 1 && col[1] <= 1 && col[2] <= 1)
			glColor3f(col[0], col[1], col[2]);
		else glColor3f(col[0] / 255, col[1] / 255, col[2] / 255);
	}

	void randColor()
	{
		glColor3f(rand() % 255 / 255.0, rand() % 255 / 255.0, rand() % 255 / 255.0);
	}

public:
	//Position & Size
	float x = 0,
		y = 0,
		w = 100,
		h = 100;
	//Rotation
	float fUpper = 0,
		fLower = 0,
		fClaw = 0,
		fClawG = 0;
	//Speed
	float sBody = 1,
		sUpper = 1,
		sLower = 1,
		sClaw = 1,
		sClawG = 0.001;
	//Color
	float base[4],
		upper[4],
		lower[4],
		claw[4];
	
	//Constructor
	Claw(const float x = 0, const float y = 0, const float w = 100, const float h = 100) : x(x), y(y), w(w), h(h)
	{
		base[0] = 0.5;
		base[1] = 0.5;
		base[2] = 0.25;
		base[3] = 0;

		upper[0] = 0.25;
		upper[1] = 0.25;
		upper[2] = 0.25;
		upper[3] = 0;

		lower[0] = 0.5;
		lower[1] = 0.5;
		lower[2] = 0.5;
		lower[3] = 0;

		claw[0] = 0.75;
		claw[1] = 0.75;
		claw[2] = 0;
		claw[3] = 0;
	}

	//left & right
	void moveBodyH(const bool dir)
	{
		if (dir)
			x += sBody;
		else x -= sBody;
	}

	//up & down
	void moveBodyV(const bool dir)
	{
		if (dir)
			y += sBody;
		else y -= sBody;
	}

	//widdershins & turnwise
	void rotUpper(const bool dir)
	{
		if (dir)
			fUpper += sUpper;
		else fUpper -= sUpper;
	}

	void rotLower(const bool dir)
	{
		if (dir)
			fLower += sLower;
		else fLower -= sLower;
	}

	void rotClaw(const bool dir)
	{
		if (dir)
			fClaw += sClaw;
		else fClaw -= sClaw;
	}

	//out & in
	void gripClaw(const bool dir)
	{
		if (dir)
			fClawG += sClawG;
		else fClawG-= sClawG;
	}

	void Draw()
	{
		//Store old vars
		float oldColor[4];
		glGetFloatv(GL_CURRENT_COLOR, oldColor);
		float oldMat[16];
		glGetFloatv(GL_MODELVIEW_MATRIX, oldMat);

		//Set up numbers
		float xc, yc, 
			  wc, hc,
			  uwc, uhc,
			  lwc, lhc,
			  cwc, chc;

		xc = xConv(x);
		yc = yConv(y);

		wc = xMeas(w);
		hc = yMeas(h);

		uwc = wc / 4;
		uhc = hc;

		lwc = wc / 4;
		lhc = hc;

		cwc = wc / 4;
		chc = hc / 2;

		//Clear old matrices
		glLoadIdentity();

		//Body
		setGLColArr(base);
		glTranslatef(xc, yc, 0);
		drawBox(wc, hc);

		//Upper
		setGLColArr(upper);
		glTranslatef(0, uhc / 2, 0);
		glRotatef(fUpper, 0, 0, 1);
		glTranslatef(0, uhc / 2, 0);
		drawBox(uwc, uhc);

		//Lower
		setGLColArr(lower);
		glTranslatef(0, lhc / 2, 0);
		glRotatef(fLower, 0, 0, 1);
		glTranslatef(0, lhc / 2, 0);
		drawBox(lwc, lhc);

		//Claw
		setGLColArr(claw);
		glTranslatef(0, chc * 0.75, 0);
		glRotatef(fClaw, 0, 0, 1);

		glPushMatrix();
		glTranslatef(-cwc / 2 - fClawG, chc * .75, 0);
		drawBox(cwc, chc);

		glPopMatrix();
		glTranslatef(cwc / 2 + fClawG, chc * .75, 0);
		drawBox(cwc, chc);

		//Reset Vars
		setGLColArr(oldColor);
		glLoadMatrixf(oldMat);
	}

};

#endif