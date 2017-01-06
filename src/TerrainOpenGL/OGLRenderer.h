#pragma once

#include <GL\glew.h>
#include "glm\glm.hpp"
#include "SOIL.h"

//#pragma comment(lib, "SOIL.lib")

class OGLRenderer {
public:
	OGLRenderer(void);
	virtual ~OGLRenderer(void);
	
	virtual void	draw(float delta) = 0;
	virtual void	update(float msec);

	void			setProjectionMatrix(const glm::mat4 &m) { projMatrix = m; }
	void			setViewMatrix(const glm::mat4 &m) { viewMatrix = m; }
	void			setTextureMatrix(const glm::mat4 &m) { textureMatrix = m; }
	void			setModelMatrix(const glm::mat4 &m) { modelMatrix = m; }
protected:
	void			updateShaderMatrices(GLuint program);

	glm::mat4		projMatrix;		//Projection matrix
	glm::mat4		modelMatrix;	//Model matrix. NOT MODELVIEW
	glm::mat4		viewMatrix;		//View matrix
	glm::mat4		textureMatrix;	//Texture matrix
};