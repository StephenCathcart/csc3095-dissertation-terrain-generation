#pragma once

#include "OGLRenderer.h"
#include "Shader.h"
#include "Mesh.h"
#include "Camera.h"
#include "Light.h"
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Graphics.hpp>

class Renderer : public OGLRenderer {
public:
	Renderer(sf::RenderWindow &window);
	~Renderer(void);

	float	getTime(){ return time; };
	void	update(float msec);
	void	draw(float delta);
	void	switchToPerspective(sf::RenderWindow &window);
	void	switchToOrtho(sf::RenderWindow &window);

	void	updateTexture();
	void	initPlanetTextures();

	Camera&	getCamera() { return *camera; };
	Light&	getLight() { return *light; };
	Mesh&	getIco()	{ return *planet; }

	sf::RenderWindow& getWindow() { return window;  };

	Mesh* planet;
	Mesh* water;
	Mesh* atmosphere;
	Shader*	planetShader;
	Shader*	waterShader;
	Shader*	atmosphereShader;
	Camera* camera;
	Light* light;

protected:
	void	setShaderLight(GLuint program, const Light &l);

	sf::RenderWindow &window;

	float	time;
};

