#ifndef ICO_H
#define ICO_H

#include <GL\glew.h>
#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"

class Icosahedron {
public:
	Icosahedron();
	~Icosahedron(void);

	void	createIcosahedron();
	void	render(GLuint program);
	void	update(float msec);
	void	updateUniforms(GLuint program);

	float	getTessLevelInner() const { return tessLevelInner; }
	float	getTessLevelOuter() const { return tessLevelOuter; }

private:
	GLuint		vao;
	GLsizei		indexCount;
	glm::mat3	normals;
	GLuint		LightPosition;
    GLuint		AmbientMaterial;
    GLuint		DiffuseMaterial;
	float		tessLevelInner;
	float		tessLevelOuter;
};

#endif // !--ICO_H

