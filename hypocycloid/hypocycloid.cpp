#include <iostream>
#include <vector>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>

using namespace std;
using namespace sf;

int main() {
	// Input
	cout << "Ve hinh hypocycloid voi tham so k = R / r.\n";
	cout << "Example K = 3 : deltoid, ";
	cout << "K = 4 : astroid, ";
	cout << "K = 5 : pentoid \n";
	cout << "Input k = ";
	int k; cin >> k;

	// Initialize the screen
	// Window Attr
	int windowWidth = 1280, windowHeight = 720;

	RenderWindow window(VideoMode(windowWidth, windowHeight), "Screen");

	// Root Coordinate
	float x0 = windowWidth / 2, y0 = windowHeight / 2;

	// Time tracking 
	Clock clock;
	float t = 0; // Time in program

	// Orbit 1 
	float orbit1Radius = 300;
	float orbit1X0 = x0 - orbit1Radius;
	float orbit1Y0 = y0 - orbit1Radius;
	CircleShape orbit1(300);
	orbit1.setPosition(orbit1X0, orbit1Y0);
	orbit1.setFillColor(Color::Transparent);
	orbit1.setOutlineColor(Color::White);
	orbit1.setOutlineThickness(2);

	// Orbit 2
	float orbit2Radius = orbit1Radius / k;
	float orbit2X0 = x0 - orbit2Radius;
	float orbit2Y0 = y0 - orbit1Radius;
	CircleShape orbit2(orbit2Radius);
	orbit2.setFillColor(Color::Transparent);
	orbit2.setOutlineColor(Color::White);
	orbit2.setOutlineThickness(2);

	// Object
	float objRadius = 8;
	float objX0 = x0 - objRadius, objY0 = y0 - objRadius - orbit1Radius;
	CircleShape obj(objRadius);
	obj.setFillColor(Color::Red);

	// Hypocycloid
	vector <Vector2f> hypocycloid;

	// Main loop
	while (window.isOpen()) {
		
		Event event;

		// Event handle
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed)
				window.close();
		}

		Time elapsed = clock.restart();
		t += elapsed.asSeconds();

		// Orbit 2 Movement
		float xOrbit2 = (orbit1Radius - orbit2Radius) * cos(t);
		float yOrbit2 = (orbit1Radius - orbit2Radius) * sin(t);
		orbit2.setPosition(x0 + xOrbit2 - orbit2Radius, y0 + yOrbit2 - orbit2Radius);


		// Object Movement
		float xObj = (orbit1Radius - orbit2Radius) * cos(t) + orbit2Radius * cos((orbit1Radius - orbit2Radius) / orbit2Radius * t);
		float yObj = (orbit1Radius - orbit2Radius) * sin(t) - orbit2Radius * sin((orbit1Radius - orbit2Radius) / orbit2Radius * t);
		
		obj.setPosition(x0 + xObj - objRadius,y0 + yObj - objRadius);

		hypocycloid.push_back(Vector2f(x0 + xObj, y0 + yObj) );


		// Render
		window.clear();

		window.draw(orbit1);
		window.draw(orbit2);
		window.draw(obj);

		for (int i = 1; i < hypocycloid.size(); i++) {
			Vertex line[]{
				Vertex(hypocycloid[i], Color::White),
				Vertex(hypocycloid[i - 1], Color::White),
			};
			window.draw(line, 5, Lines);
		}

		window.display();
	}
	return 0;
}