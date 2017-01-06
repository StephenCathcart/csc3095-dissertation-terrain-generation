#include "Main.h"
#include "Shader.h"
#include "Mesh.h"
#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "TerrainHelper.h"
#include "Settings.h"

//bool	isWireMode = false;		// Alternate between wireframe mode and fill mode

int main() {
	// Declare and create a new window
	sf::RenderWindow application(sf::VideoMode(1920, 1080), "Terrain Generator", sf::Style::Default, sf::ContextSettings(32));
	application.setVerticalSyncEnabled(true);

	// Create heightmap and icon
	heightMap = new DiamondSquare("heightmap", Settings::dataSize, Settings::noiseSeed, Settings::cornerSeed, 32);
	TerrainHelper::smoothTerrain(heightMap->getData(), heightMap->getDataSize(), 5, Settings::smoothingScale);
	heightMap->saveToBitmap();

	heightMapIcon = new DiamondSquare("heightmapIcon", 129, Settings::noiseSeed, Settings::cornerSeed, 32);
	TerrainHelper::smoothTerrain(heightMapIcon->getData(), heightMapIcon->getDataSize(), 5, Settings::smoothingScale);
	heightMapIcon->saveToBitmap();

	// Create OpenGL Renderer for planet scene
	Renderer renderer(application);

	// Input Listener for GUI
	GUI gui(renderer);

	// Create an SFGUI. This is required before doing anything with SFGUI.
    sfg::SFGUI m_sfgui;

	// Create a desktop and add the window to it.
	sfg::Desktop desktop = gui.getDesktop();
	if(!desktop.LoadThemeFromFile("Themes/main.theme")) {
		return -1;
	}
	
	startup(application);

	// Background texture
	sf::Texture bgTex;
	if (!bgTex.loadFromFile("Images/space.jpg")) {
		// error...
		return -1;
	}
	sf::Sprite bgSprite;
	bgSprite.setTexture(bgTex);
	auto size = bgSprite.getTexture()->getSize();
	bgSprite.setScale(float(application.getSize().x)/size.x, float(application.getSize().y)/size.y);


	sf::Clock clock;
	bool running = true;
	// The main loop - ends as soon as the window is closed
	while (running) {
		// Handle events
		sf::Event event;
		while (application.pollEvent(event)) {
			desktop.HandleEvent( event );
			if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
				// End the program
				running = false;
			}
			if (event.type == sf::Event::Resized) {
				// Adjust the viewport when the window is resized
				glViewport(0, 0, event.size.width, event.size.height);
				gui.resize();
			}
			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Num1) {
					//isWireMode = !isWireMode;
				}
				if (event.key.code == sf::Keyboard::W) { renderer.getCamera().keyW(); }
				if (event.key.code == sf::Keyboard::A) { renderer.getCamera().keyA(); }
				if (event.key.code == sf::Keyboard::S) { renderer.getCamera().keyS(); }
				if (event.key.code == sf::Keyboard::D) { renderer.getCamera().keyD(); }
				if (event.key.code == sf::Keyboard::LShift) { renderer.getCamera().keyShift(); }
				if (event.key.code == sf::Keyboard::Space) { renderer.getCamera().keySpace(); }
			}
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				renderer.getCamera().mouseLeft(); 
			}
		}
		//glClearColor( 0.145098039f ,0.145098039f ,0.14901960f ,1.0f ); 
		glClearColor( 0.13333333333f ,0.18039215686f ,0.2431372549f ,1.0f ); 
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Background
		application.pushGLStates();
		application.resetGLStates ();
		application.draw(bgSprite);
		application.popGLStates();

		// Render scene	and restart timer
		!Settings::isWireMode ? glPolygonMode(GL_FRONT_AND_BACK, GL_FILL) : glPolygonMode(GL_FRONT_AND_BACK, GL_LINE );
		render(renderer, clock.getElapsedTime().asMilliseconds());
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		// Update SFGUI with elapsed seconds since last call and draw GUI.
		// We need to save OpenGL states then restore afterwards as it messes with the GUI
		application.pushGLStates();
		application.resetGLStates ();
		desktop.Update(clock.restart().asSeconds() );
		m_sfgui.Display(application);
		application.popGLStates();

		// End the current frame and display its contents on screen
		application.display();
    }
	shutdown();
	return 0;
}

void startup(sf::RenderWindow& application) {
	// Check Supported OpenGL verisons
	cout << (char *)glGetString(GL_VERSION) << endl;

    // We have to set up our own OpenGL viewport because we are using an sf::Window.
    glViewport( 0, 0, application.getSize().x, application.getSize().y );
}

void render(Renderer &renderer, float delta) {
	// Update and draw from renderer
	renderer.update(delta);
	renderer.draw(delta);
}

void shutdown() {
	delete heightMap;
	delete heightMapIcon;
}
