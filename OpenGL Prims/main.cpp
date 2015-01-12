//////////////////////////////////////////////////////////// 
// Headers 
//////////////////////////////////////////////////////////// 
#include "stdafx.h" 
#ifdef _DEBUG 
#pragma comment(lib,"sfml-graphics-d.lib") 
#pragma comment(lib,"sfml-audio-d.lib") 
#pragma comment(lib,"sfml-system-d.lib") 
#pragma comment(lib,"sfml-window-d.lib") 
#pragma comment(lib,"sfml-network-d.lib") 
#else 
#pragma comment(lib,"sfml-graphics.lib") 
#pragma comment(lib,"sfml-audio.lib") 
#pragma comment(lib,"sfml-system.lib") 
#pragma comment(lib,"sfml-window.lib") 
#pragma comment(lib,"sfml-network.lib") 
#endif 
#pragma comment(lib,"opengl32.lib") 
#pragma comment(lib,"glu32.lib") 

#include "SFML/Graphics.hpp" 
#include "SFML/OpenGL.hpp" 
#include <iostream>

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

const int screenW = 400;
const int screenH = 400;

int spacer = 2;
int squareW = 32;
int squareH = 32;
int rows = 8;
int cols = 8;

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
	glColor3f(r / 255, g / 255, b / 255);
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

////EXERCISE
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
	int midX = screenW / 2;
	int midY = screenH / 2;
	bool toggle = true;

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

			//Arrow L : Width Down
			if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Left))
				squareW--;

			//Arrow R : Width Up
			if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Right))
				squareW++;

			//Arrow U : Height Up
			if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Up))
				squareH++;

			//Arrow D : Height Down
			if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Down))
				squareH--;
				
		}

		// Draw loop
		window.clear();
		//if (toggle)
		drawSpiral4(midX, midY, 1, 15, 0.05);
		//drawSine(midX, midY, screenW, screenH, 10);
		toggle = false;
		window.display();

	}

	return EXIT_SUCCESS;
}