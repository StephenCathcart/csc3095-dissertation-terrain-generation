#include "Renderer.h"
#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include "Settings.h"

Renderer::Renderer(sf::RenderWindow &window) : OGLRenderer(),  window(window) {
	camera = new Camera(window);
	camera->setPosition(glm::vec3(0, 0, 5));

	// PLANET
	planet = Mesh::generateIco();
	initPlanetTextures();
	planetShader = new Shader("Shaders/Planet/vert.glsl",
					"Shaders/Planet/frag.glsl",
					"Shaders/Planet/geom.glsl",
					"Shaders/Planet/tcs.glsl",
					"Shaders/Planet/tes.glsl");

	if (!planetShader->linkProgram ()) {
		return ;
	}
	// END PLANET

	// WATER
	water = Mesh::generateIco();
	water->setTexture(SOIL_load_OGL_texture("heightmap.bmp",
		SOIL_LOAD_AUTO , SOIL_CREATE_NEW_ID , 0));
	if (!water->getTexture()) {
		return;
	}
	waterShader = new Shader("Shaders/Water/vert.glsl",
					"Shaders/Water/frag.glsl",
					"Shaders/Water/geom.glsl",
					"Shaders/Water/tcs.glsl",
					"Shaders/Water/tes.glsl");
	if (!waterShader->linkProgram ()) {
		return ;
	}
	// END WATER

	// ATMOSPHERE
	atmosphere = Mesh::generateIco();
	atmosphere->setTexture(SOIL_load_OGL_texture("heightmap.bmp",
		SOIL_LOAD_AUTO , SOIL_CREATE_NEW_ID , 0));
	if (!atmosphere->getTexture()) {
		return;
	}
	atmosphereShader = new Shader("Shaders/Atmosphere/vert.glsl",
					"Shaders/Atmosphere/frag.glsl",
					"Shaders/Atmosphere/geom.glsl",
					"Shaders/Atmosphere/tcs.glsl",
					"Shaders/Atmosphere/tes.glsl");
	if (!atmosphereShader->linkProgram ()) {
		return ;
	}
	// END ATMOSPHERE


	light = new Light(glm::vec3(20.0f, 10.0f, 20.0f),
		glm::vec4(Settings::lightRed ,Settings::lightGreen , Settings::lightBlue ,0), 
					Settings::radius);
	
	// Set up standard perspective view
	switchToPerspective(window);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable (GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

Renderer::~Renderer(void) {
	delete planetShader;
	delete waterShader;
	delete atmosphereShader;
	delete camera;
	delete light;
}

void Renderer::initPlanetTextures() {
	planet->setTexture(SOIL_load_OGL_texture("heightmap.bmp",
	SOIL_LOAD_AUTO , SOIL_CREATE_NEW_ID , 0));
	if (!planet->getTexture()) {
		return;
	}

	planet->setSnowTexture(SOIL_load_OGL_texture("Images/snow.jpg",
	SOIL_LOAD_AUTO , SOIL_CREATE_NEW_ID , 0));
	if (!planet->getSnowTexture()) {
		return;
	}

	planet->setGravelTexture(SOIL_load_OGL_texture("Images/gravel.jpg",
	SOIL_LOAD_AUTO , SOIL_CREATE_NEW_ID , 0));
	if (!planet->getGravelTexture()) {
		return;
	}

	planet->setSandTexture(SOIL_load_OGL_texture("Images/sand.jpg",
	SOIL_LOAD_AUTO , SOIL_CREATE_NEW_ID , 0));
	if (!planet->getSandTexture()) {
		return;
	}
}

void Renderer::updateTexture() {
	planet->setTexture(SOIL_load_OGL_texture("heightmap.bmp",
		SOIL_LOAD_AUTO , 1 , 0));
	if (!planet->getTexture()) {
		return;
	}

	water->setTexture(SOIL_load_OGL_texture("heightmap.bmp",
		SOIL_LOAD_AUTO , 1 , 0));
	if (!water->getTexture()) {
		return;
	}
}

void Renderer::update(float msec) {
	camera->updateCamera(msec);
	viewMatrix = camera->buildViewMatrix(); 
	time += msec;
}

void Renderer::draw(float delta) {
	// Rotate all
	//glm::mat4 mat = glm::rotate(glm::mat4(1.0f), -0.2f , glm::vec3 (1.0f ,1.0f ,0.0f));
	//this->modelMatrix *= mat;

	//** DRAW PLANET **//
	GLuint program = planetShader->getShaderProgram();
	glUseProgram (program);
	updateShaderMatrices(program);
	glUniform1i(glGetUniformLocation(program, "heightmapTex"),		planet->getTexture()-1);
	glUniform1i(glGetUniformLocation(program, "snowTex"),			planet->getSnowTexture()-1);
	glUniform1i(glGetUniformLocation(program, "gravelTex"),			planet->getGravelTexture()-1);
	glUniform1i(glGetUniformLocation(program, "sandTex"),			planet->getSandTexture()-1);
	glUniform1f(glGetUniformLocation(program, "tessLevelInner"),	Settings::tessLevelInner);
	glUniform1f(glGetUniformLocation(program, "tessLevelOuter"),	Settings::tessLevelOuter);
	glUniform1f(glGetUniformLocation(program, "mountainScale"),		Settings::mountainScale);
	glUniform1f(glGetUniformLocation(program, "groundTypeAmount"),	Settings::groundTypeScale);
	glUniform3fv(glGetUniformLocation(program,"cameraPos"), 1, (float*)&camera->getPosition());
	glUniform1f(glGetUniformLocation(program, "time"), getTime());
	setShaderLight(program, *light);
	planet->draw();
	glUseProgram(0);
	//** END PLANET **//

	//** DRAW WATER **//
	GLuint program2 = waterShader->getShaderProgram();
	glUseProgram (program2);
	updateShaderMatrices(program2);
	glUniform1f(glGetUniformLocation(program2, "time"), getTime());
	glUniform1i(glGetUniformLocation(program2, "heightmapTex"),		planet->getTexture()-1);
	glUniform1f(glGetUniformLocation(program2, "tessLevelInner"),	Settings::tessLevelInner);
	glUniform1f(glGetUniformLocation(program2, "tessLevelOuter"),	Settings::tessLevelOuter);
	glUniform1f(glGetUniformLocation(program2, "waterScale"),		Settings::waterScale);
	glUniform1f(glGetUniformLocation(program2, "ripple"),			Settings::rippleIntensity);
	glUniform1f(glGetUniformLocation(program2, "transparency"),		Settings::transparency);
	glUniform1f(glGetUniformLocation(program2, "waterRed"),			Settings::waterRed);
	glUniform1f(glGetUniformLocation(program2, "waterGreen"),		Settings::waterGreen);
	glUniform1f(glGetUniformLocation(program2, "waterBlue"),		Settings::waterBlue);
	glUniform3fv(glGetUniformLocation(program2,"cameraPos"), 1, (float*)&camera->getPosition());
	setShaderLight(program2, *light);
	water->draw();
	glUseProgram(0);
	//** END WATER **//

	////** DRAW ATMOSPHERE **//
	//GLuint program3 = atmosphereShader->getShaderProgram();
	//glUseProgram (program3);

	////glm::mat4 mat = glm::rotate(glm::mat4(), 0.2f , glm::vec3 (1.0f ,1.0f ,0.0f));
	////this->modelMatrix *= mat;

	//updateShaderMatrices(program3);
	//glUniform1f(glGetUniformLocation(program3, "time"), getTime());
	//glUniform1i(glGetUniformLocation(program3, "heightmapTex"),		planet->getTexture()-1);
	//glUniform1f(glGetUniformLocation(program3, "tessLevelInner"),	atmosphere->getTessLevelInner());
	//glUniform1f(glGetUniformLocation(program3, "tessLevelOuter"),	atmosphere->getTessLevelOuter());
	//glUniform3fv(glGetUniformLocation(program3,"cameraPos"), 1, (float*)&camera->getPosition());
	//atmosphere->draw();
	//glUseProgram(0);
	////** END ATMOSPHERE **//
}

void Renderer::switchToPerspective(sf::RenderWindow &window) {
	setProjectionMatrix(glm::perspective(45.0f, (float)window.getSize().x / (float)window.getSize().y, 1.0f, 1500.0f));
}

void Renderer::switchToOrtho(sf::RenderWindow &window) {
	// TODO
	//setProjectionMatrix(glm::ortho(45.0f, (float)window.getSize().x / (float)window.getSize().y, 1.0f, 1500.0f));
}

void Renderer::setShaderLight(GLuint program, const Light &l) {
	glUniform3fv(glGetUniformLocation(program,
		"lightPos") ,1,(float*)&l.GetPosition());

	glUniform4fv(glGetUniformLocation(program,
		"lightColour"),1,(float*)&l.GetColour());

	glUniform1f(glGetUniformLocation(program,
		"lightRadius"),l.GetRadius());
}