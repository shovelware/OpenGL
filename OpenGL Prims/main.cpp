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

////////////////////////////////////////////////////////////
///Entrypoint of application 
//////////////////////////////////////////////////////////// 
int main()
{
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

		//TODO: Draw Items
		drawLineGrid(rows, cols, spacer, squareW, squareH);

		window.display();

	}

	return EXIT_SUCCESS;
}