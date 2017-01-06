#ifndef MESH_H
#define MESH_H

#include <GL\glew.h>
#include "glm\glm.hpp"
#include <fstream>
#include <string>

using std::string;

enum MeshBuffer {
	VERTEX_BUFFER , COLOUR_BUFFER , TEXTURE_BUFFER , NORMAL_BUFFER , INDEX_BUFFER, MAX_BUFFER
};

extern unsigned int faces[60];

class Mesh {
public:
	Mesh(void);
	virtual ~Mesh(void);

	virtual void draw();

	static Mesh* generateIco();
	static Mesh* generateRectangle();
	static Mesh* generateTriangle();
	static Mesh* generateQuadPatch();
	static Mesh* loadMeshFile(const string &filename);

	void setTexture(GLuint tex) { texture = tex ;}
	GLuint getTexture() { return texture ;}

	void setSnowTexture(GLuint tex) { snowTexture = tex ;}
	GLuint getSnowTexture() { return snowTexture ;}

	void setGravelTexture(GLuint tex) { gravelTexture = tex ;}
	GLuint getGravelTexture() { return gravelTexture ;}

	void setSandTexture(GLuint tex) { sandTexture = tex ;}
	GLuint getSandTexture() { return sandTexture ;}

	void generateNormals();

protected:
	//Buffers all VBO data into graphics memory. Required before drawing!
	void bufferData();
	
	GLuint arrayObject;
	GLuint bufferObject[MAX_BUFFER];
	GLuint numVertices;
	GLuint texture;
	GLuint type;

	GLuint snowTexture;
	GLuint gravelTexture;
	GLuint sandTexture;

	glm::vec3* normals;
	
	//Pointer to vertex position attribute data (badly named...?)
	glm::vec3*		vertices;
	//Pointer to vertex colour attribute data
	glm::vec4*		colours;
	//Pointer to vertex texture coordinate attribute data
	glm::vec2*		textureCoords;

	//Optional, but using indices is more efficient
	GLuint numIndices;
	unsigned int* indices;
};

#endif

