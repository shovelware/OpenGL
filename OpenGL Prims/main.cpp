//////////////////////////////////////////////////////////// 
// Headers 
//////////////////////////////////////////////////////////// 
#include "stdafx.h" 
#include <iostream>
#include "Claw.h"

#include <time.h>
#define _USE_MATH_DEFINES
#include "math.h"

const double RD = 180 / M_PI;
const double DR = M_PI / 180;

using std::cout;
using std::endl;

////////////////////////////////////////////////////////////
///Global Variables
//////////////////////////////////////////////////////////// 

int spacer = 2;
int squareW = 32;
int squareH = 32;
int rows = 8;
int cols = 8;
Claw c;

////////////////////////////////////////////////////////////
///Functions
//////////////////////////////////////////////////////////// 

float xConv(const int x)
{
	return -1 + ((2.0 / screenW) * x);
}

float yConv(const int y)
{
	return 1 - ((2.0 / screenH) * y);
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

sf::Vector2f VecConv(const sf::Vector2i inVector)
{
	float x = -1 + (2.0 / screenW) * inVector.x;
	float y = -1 + (2.0 / screenH) * inVector.y;

	return sf::Vector2f(x, y);
}

void drawSquare(const int x, const int y, const int w, const int h)
{
	//Convert pixel coords to screenspace
	sf::Vector2f tl(xConv(x), yConv(y));
	sf::Vector2f bl(xConv(x), yConv(y + h));
	sf::Vector2f br(xConv(x + w), yConv(y + h));
	sf::Vector2f tr(xConv(x + w), yConv(y));

	//Draw
	glBegin(GL_LINE_LOOP);

	glVertex2f(tl.x, tl.y);
	glVertex2f(bl.x, bl.y);
	glVertex2f(br.x, br.y);
	glVertex2f(tr.x, tr.y);

	glEnd();
}

void drawFillSquare(const int x, const int y, const int w, const int h)
{
	//Convert pixel coords to screenspace
	sf::Vector2f tl(xConv(x), yConv(y));
	sf::Vector2f bl(xConv(x), yConv(y + h));
	sf::Vector2f br(xConv(x + w), yConv(y + h));
	sf::Vector2f tr(xConv(x + w), yConv(y));

	//Draw
	glBegin(GL_QUADS);

	glVertex2f(tl.x, tl.y);
	glVertex2f(bl.x, bl.y);
	glVertex2f(br.x, br.y);
	glVertex2f(tr.x, tr.y);

	glEnd();
}

void drawRandSquare(const int x, const int y, const int w, const int h)
{
	//Convert pixel coords to screenspace
	sf::Vector2f tl(xConv(x), yConv(y));
	sf::Vector2f bl(xConv(x), yConv(y + h));
	sf::Vector2f br(xConv(x + w), yConv(y + h));
	sf::Vector2f tr(xConv(x + w), yConv(y));

	//Draw
	glBegin(GL_QUADS);

	randColor();
	glVertex2f(tl.x, tl.y);
	randColor();
	glVertex2f(bl.x, bl.y);
	randColor();
	glVertex2f(br.x, br.y);
	randColor();
	glVertex2f(tr.x, tr.y);

	glEnd();
}


void drawLinePoly(const int x, const int y, const int vertices, const int radius)
{
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < vertices; ++i)
	{
		glVertex2f(xConv(x + radius * (cos(DR * 360 / vertices * i))), yConv(y + radius * (sin(DR * 360 / vertices * i))));
	}
	glEnd();
}

void drawFillPoly(const int x, const int y, const int vertices, const int radius)
{
	glBegin(GL_POLYGON);
	for (int i = 0; i < vertices; ++i)
	{
		glVertex2f(xConv(x + radius * (cos(DR * 360 / vertices * i))), yConv(y + radius * (sin(DR * 360 / vertices * i))));
	}
	glEnd();
}

void drawSpiral(const int x, const int y, const int revolutions, const float smoothness, const float innerDist, const float expansion)
{
	int count = 0;
	glBegin(GL_LINE_STRIP);
	for (int r = 0; r <= revolutions; ++r)
	{
		for (int d = 0; d <= 360; ++d)
		{
			float posx = x + (((innerDist * r + d) * expansion) * cos(DR * 360 / smoothness * d));
			float posy = y + (((innerDist * r + d) * expansion) * sin(DR * 360 / smoothness * d));
			glVertex2f(xConv(posx), yConv(posy));
			//cout << posx << " | " << posy << endl;
			count++;
		}
	}
	glEnd();
	cout << count << endl;
}

void drawThing(const int x, const int y, const int revolutions, const float smoothness, const float innerDist, const float expansion)
{
	int count = 0;
	glBegin(GL_LINE_STRIP);
	for (int r = 0; r <= revolutions; ++r)
	{
		for (int d = 0; d <= 360; ++d)
		{
			float posx = x + (((innerDist * r + d) * expansion) * cos(DR * 360 / smoothness * d));
			float posy = y + (((innerDist * r + d) * expansion) * sin(DR * 360 / smoothness * d));
			glVertex2f(xConv(posx), yConv(posy));
			count++;
		}
	}
	glEnd();
	cout << count << endl;
}

void drawSpiral2(const int x, const int y, const float vertices, const float revolutions)
{
	glBegin(GL_LINE_STRIP);
	float interval = 360 / vertices;
	float degrees = 360 * revolutions;
	for (float d = 0; d <= degrees; d += interval)
	{
		//float posX = xConv(x + radius * (cos(DR * 360 / vertices * i)));
		//float posY = yConv(y + radius * (sin(DR * 360 / vertices * i))));
		//glVertex2f(xConv(posx), yConv(posy));
		//cout << posx << " | " << posy << endl;
	}

	glEnd();
}

void drawSpiral3(const int x, const int y, const int vertices, float radius, const float revolutions)
{
	glBegin(GL_LINE_STRIP);
	for (int i = 0; i < vertices * revolutions; ++i)
	{
		float posX = xConv(x + radius * (cos(DR * 360 / vertices * i)));
		float posY = yConv(y + radius * (sin(DR * 360 / vertices * i)));
		glVertex2f(xConv(posX), yConv(posY));
		radius = radius * 0.99;
	}
	glEnd();
}

void drawSpiral4(const int x, const int y, const float radius, const float revolutions, const float expansion, const float fidelity = 360)
{

	float posX, posY;
	const float vertices = revolutions * fidelity;

	glBegin(GL_LINE_STRIP);
	for (int i = 0; i < revolutions * fidelity; ++i)
	{
		posX = x + ((radius + i * expansion) * (cos(DR * 360 / fidelity * i)));
		posY = y + ((radius + i * expansion) * (sin(DR * 360 / fidelity * i)));

		glVertex2f(xConv(posX), yConv(posY));
	}
	glEnd();
}

void drawSine(const int x, const int y, const float width, const float height, const float frequency, const float fidelity = 360)
{
	float sineX = x - width / 2;
	float sineY = y - height / 2;
	float radius = height / 2;

	float posX, posY;
	const float vertices = frequency * fidelity;

	glBegin(GL_LINE_STRIP);
	for (int i = 0; i < vertices; ++i)
	{
		posX = sineX + (width / frequency / fidelity) * i * 1.0;
		posY = y + radius * (sin(DR * 360 / fidelity * i * 1.0));
		randColor();
		glVertex2f(xConv(posX), yConv(posY));
	}
	glEnd();
}

void drawLineGrid(const int rows, const int cols, const int spacer, const int width, const int height)
{
	for (int r = 0; r < rows; r++)
	{
		for (int c = 0; c < cols; c++)
		{
			drawSquare(spacer + (spacer + width) * c, spacer + (spacer + height) * r, width, height);
		}
	}
}

void drawFillGrid(const int rows, const int cols, const int spacer, const int width, const int height)
{
	for (int r = 0; r < rows; r++)
	{
		for (int c = 0; c < cols; c++)
		{
			drawFillSquare(spacer + (spacer + width) * c, spacer + (spacer + height) * r, width, height);
		}
	}
}

void drawChessGrid(const int rows, const int cols, const int spacer, const int width, const int height)
{
	for (int r = 0; r < rows; r++)
	{
		int count = r % 2;
		for (int c = 0; c < cols; c++)
		{
			count % 2 ? glColor3f(0, 0, 0) : glColor3f(1, 1, 1);

			drawFillSquare(spacer + (spacer + width) * c, spacer + (spacer + height) * r, width, height);
			count++;
		}
	}
}

void drawRandomGrid(const int rows, const int cols, const int spacer, const int width, const int height)
{
	for (int r = 0; r < rows; r++)
	{
		for (int c = 0; c < cols; c++)
		{
			randColor();
			drawFillSquare(spacer + (spacer + width) * c, spacer + (spacer + height) * r, width, height);
		}
	}
}

void drawSubRandomGrid(const int rows, const int cols, const int spacer, const int width, const int height)
{
	for (int r = 0; r < rows; r++)
	{
		for (int c = 0; c < cols; c++)
		{
			drawRandSquare(spacer + (spacer + width) * c, spacer + (spacer + height) * r, width, height);
		}
	}
}

////////////////////////////////////////////////////////////
///Entrypoint of application 
//////////////////////////////////////////////////////////// 
int main()
{
	srand(time(NULL));
	bool toggle = true;
	c = Claw(midX, midY + midY / 2, 50, 50);

	// Create the main window 
	sf::RenderWindow window(sf::VideoMode(screenW, screenH, 32), "SFML OpenGL Program");

	// Start game loop 
	while (window.isOpen())
	{
		// Process events 
		sf::Event Event;
		while (window.pollEvent(Event))
		{
			// Close window : exit 
			if (Event.type == sf::Event::Closed)
				window.close();

			// Escape key : exit 
			if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Escape))
				window.close();
				
			//A : Move Left
			if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::A))
				c.moveBodyH(false);

			//D : Move Right
			if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::D))
				c.moveBodyH(true);

			//W : Move Up
			if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::W))
				c.moveBodyV(false);

			//S : Move Down
			if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::S))
				c.moveBodyV(true);

			//Arrow L : Upper Left
			if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Left))
				c.rotUpper(true);

			//Arrow R : Upper Right
			if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Right))
				c.rotUpper(false);

			//Arrow U : Lower Left
			if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Up))
				c.rotLower(true);

			//Arrow D : Lower Right
			if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Down))
				c.rotLower(false);

			//E : Claw Right
			if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::E))
				c.rotClaw(false);

			//Q : Claw Left
			if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Q))
				c.rotClaw(true);

			//Space : Claw Close
			if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Space))
				c.gripClaw(false);

			//BackSpace : Close Claws
			if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::BackSpace))
				c.gripClaw(true);

		}

		// Draw loop
		window.clear();
		//if (toggle)
		//drawSpiral4(midX, midY, 1, 15, 0.05);
		//drawSine(midX, midY, screenW, screenH, 10);
		//toggle = false;
		c.Draw();
		window.display();

	}

	return EXIT_SUCCESS;
}