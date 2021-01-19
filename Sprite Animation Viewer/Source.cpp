// DON'T FORGET TO COPY SFML DLL'S INTO PROJECT FOLDER!

#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>

#include<iostream>
using namespace std;

// Declare vars
sf::Sprite sprite;
sf::Texture texture;
string filename;
int row, width, height, frames, delay, scale;

int main()
{
	cout << "Sprite animation viewer version 1.01 \n\n";

	// Get sprite file, close if not found
	cout << "Sprite sheet (include file extension): ";
	cin >> filename;
	if (!texture.loadFromFile(filename)) {
		cout << filename << "could not be found. \n"
			"Please make sure it is in the same folder as Sprite Animation Viewer.exe \n\n";
		system("Pause");
		return -1;
	}

	// Set up sprite
	texture.setSmooth(false);
	sprite.setTexture(texture);

	// Get frame info
	cout << "sprite sheet row (starts from zero): ";
	cin >> row;
	cout << "sprite width (pixels): ";
	cin >> width;
	cout << "sprite height (pixels): ";
	cin >> height;
	cout << "number of frames: ";
	cin >> frames;
	cout << "delay between frames (at 60 fps): ";
	cin >> delay;
	cout << "scale factor (integer): ";
	cin >> scale;

	// Set up window and counters
	int frame_no = 0;
	int anim_frame_no = 0;
	int wnd_width = scale * width;
	int wnd_height = scale * height;
	if (wnd_width < 250) wnd_width = 300;
	sf::RenderWindow window(sf::VideoMode(wnd_width, wnd_height), "Sprite Animation Viewer");
	window.setFramerateLimit(60);
	sprite.setScale(scale, scale);

	while (window.isOpen())
	{
		sf::Event event;
		window.pollEvent(event);
		if (event.type == sf::Event::Closed) { window.close(); } // Program pauses to handle events

		// Cycle Frames
		if (frame_no == delay)
		{
			anim_frame_no++;

			// Reset animation loop, refresh image
			if (anim_frame_no == frames) {
				anim_frame_no = 0;
				if (!texture.loadFromFile(filename));
			}
			frame_no = 0;
		}
		frame_no++;

		// Extract frames from image
		sprite.setTextureRect(sf::IntRect(width * anim_frame_no, height * row, width, height));

		// Draw Sprite
		window.clear(sf::Color(50, 170, 255));
		window.draw(sprite);
		window.display();
	}

	return 0;
}
