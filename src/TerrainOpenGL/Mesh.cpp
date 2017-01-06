#include "Mesh.h"

#include <iostream>;
#include "glm/ext.hpp"  

unsigned int faces[] = {
    2, 1, 0,
    3, 2, 0,
    4, 3, 0,
    5, 4, 0,
    1, 5, 0,

    11, 6,  7,
    11, 7,  8,
    11, 8,  9,
    11, 9,  10,
    11, 10, 6,

    1, 2, 6,
    2, 3, 7,
    3, 4, 8,
    4, 5, 9,
    5, 1, 10,

    2,  7, 6,
    3,  8, 7,
    4,  9, 8,
    5, 10, 9,
    1, 6, 10 
};

Mesh::Mesh(void) {
	glewInit();

	for( int i = 0; i < MAX_BUFFER ; ++i) {
		bufferObject[i] = 0;
	}
	glGenVertexArrays(1, &arrayObject);

	numVertices		= NULL;
	texture			= NULL;
	numIndices		= NULL;
	indices			= NULL;
	textureCoords	= NULL;
	vertices		= NULL;
	colours			= NULL;
	normals			= NULL;
	type			= NULL;
}


Mesh::~Mesh(void) {
	glDeleteVertexArrays(1, &arrayObject);
	glDeleteBuffers(MAX_BUFFER ,bufferObject);
	glDeleteTextures(1 ,& texture);
	glDeleteTextures(1 ,& snowTexture);
	glDeleteTextures(1 ,& gravelTexture);
	glDeleteTextures(1 ,& sandTexture);
	delete[]vertices;
	delete[]textureCoords;
	delete[]colours;
	delete[]normals;
	delete[]indices;
}

void Mesh::draw() {
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D , texture);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D , snowTexture);

	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D , gravelTexture);

	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D , sandTexture);

	glBindVertexArray(arrayObject);

	if(bufferObject[INDEX_BUFFER]) {
		glDrawElements (type ,numIndices ,GL_UNSIGNED_INT ,0);
	}
	else {
		glDrawArrays(type , 0, numVertices);
	}

	glBindVertexArray(0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D , 0);
}

Mesh* Mesh::generateIco()	{
	Mesh*m = new Mesh();
	m-> numVertices = 12;
	m->type = GL_PATCHES;

	m-> vertices = new glm::vec3 [m-> numVertices];
	m-> vertices[0]		= glm::vec3 (0.000f ,  0.000f,  1.000f);
	m-> vertices[1]		= glm::vec3 (0.894f ,  0.000f,  0.447f);
	m-> vertices[2]		= glm::vec3 (0.276f ,  0.851f,  0.447f);
	m-> vertices[3]		= glm::vec3 (-0.724f,  0.526f,  0.447f);
	m-> vertices[4]		= glm::vec3 (-0.724f, -0.526f,  0.447f);
	m-> vertices[5]		= glm::vec3 (0.276f , -0.851f,  0.447f);
	m-> vertices[6]		= glm::vec3 (0.724f ,  0.526f, -0.447f);
	m-> vertices[7]		= glm::vec3 (-0.276f,  0.851f, -0.447f);
	m-> vertices[8]		= glm::vec3 (-0.894f,  0.000f, -0.447f);
	m-> vertices[9]		= glm::vec3 (-0.276f, -0.851f, -0.447f);
	m-> vertices[10]	= glm::vec3 (0.724f , -0.526f, -0.447f);
	m-> vertices[11]	= glm::vec3 (0.000f ,  0.000f, -1.000f);

	m-> colours = new glm::vec4 [m-> numVertices];
	m-> colours[0]		= glm::vec4 (1.0f, 0.0f, 0.0f ,1.0f);
	m-> colours[1]		= glm::vec4 (0.0f, 1.0f, 0.0f ,1.0f);
	m-> colours[2]		= glm::vec4 (0.0f, 0.0f, 1.0f ,1.0f);
	m-> colours[3]		= glm::vec4 (1.0f, 0.0f, 0.0f ,1.0f);
	m-> colours[4]		= glm::vec4 (0.0f, 1.0f, 0.0f ,1.0f);
	m-> colours[5]		= glm::vec4 (0.0f, 0.0f, 1.0f ,1.0f);
	m-> colours[6]		= glm::vec4 (1.0f, 0.0f, 0.0f ,1.0f);
	m-> colours[7]		= glm::vec4 (0.0f, 1.0f, 0.0f ,1.0f);
	m-> colours[8]		= glm::vec4 (0.0f, 0.0f, 1.0f ,1.0f);
	m-> colours[9]		= glm::vec4 (1.0f, 0.0f, 0.0f ,1.0f);
	m-> colours[10]		= glm::vec4 (0.0f, 1.0f, 0.0f ,1.0f);
	m-> colours[11]		= glm::vec4 (0.0f, 0.0f, 1.0f ,1.0f);

	m->numIndices = sizeof(faces) / sizeof(faces[0]);
	m->indices = faces;

	m->generateNormals();
	m->bufferData();	//Send our new data to the GPU

	return m;
}

Mesh* Mesh::generateRectangle() {
	Mesh*m = new Mesh();
	m-> numVertices = 4;
	m->type = GL_TRIANGLES;

	m-> vertices = new glm::vec3 [m-> numVertices];
	m-> vertices[0] = glm::vec3 (1.0f, 1.0f, 0.0f);
	m-> vertices[1] = glm::vec3 (1.0f, 0.0f, 0.0f);
	m-> vertices[2] = glm::vec3 (0.0f, 0.0f, 0.0f);
	m-> vertices[3] = glm::vec3 (0.0f, 1.0f, 0.0f);

	m-> textureCoords = new glm::vec2 [m-> numVertices];
	m-> textureCoords[0] = glm::vec2 (1.0f, 1.0f);
	m-> textureCoords[1] = glm::vec2 (1.0f, 0.0f);
	m-> textureCoords[2] = glm::vec2 (0.0f, 0.0f);
	m-> textureCoords[2] = glm::vec2 (0.0f, 1.0f);

	m-> colours = new glm::vec4 [m-> numVertices];
	m-> colours[0] = glm::vec4 (1.0f, 0.0f, 0.0f ,1.0f);
	m-> colours[1] = glm::vec4 (0.0f, 1.0f, 0.0f ,1.0f);
	m-> colours[2] = glm::vec4 (0.0f, 0.0f, 1.0f ,1.0f);
	m-> colours[2] = glm::vec4 (0.0f, 0.0f, 1.0f ,1.0f);

	m->generateNormals();
	m->bufferData();	//Send our new data to the GPU
	return m;
}

Mesh* Mesh::generateTriangle()	{
	Mesh*m = new Mesh();
	m-> numVertices = 3;
	m->type = GL_TRIANGLES;

	m-> vertices = new glm::vec3 [m-> numVertices];
	m-> vertices[0] = glm::vec3 (0.0f, 0.5f, 0.0f);
	m-> vertices[1] = glm::vec3 (0.5f, -0.5f, 0.0f);
	m-> vertices[2] = glm::vec3 (-0.5f, -0.5f, 0.0f);

	m-> textureCoords = new glm::vec2 [m-> numVertices];
	m-> textureCoords[0] = glm::vec2 (0.5f, 0.0f);
	m-> textureCoords[1] = glm::vec2 (1.0f, 1.0f);
	m-> textureCoords[2] = glm::vec2 (0.0f, 1.0f);

	m-> colours = new glm::vec4 [m-> numVertices];
	m-> colours[0] = glm::vec4 (1.0f, 0.0f, 0.0f ,1.0f);
	m-> colours[1] = glm::vec4 (0.0f, 1.0f, 0.0f ,1.0f);
	m-> colours[2] = glm::vec4 (0.0f, 0.0f, 1.0f ,1.0f);

	m->generateNormals();
	m->bufferData();	//Send our new data to the GPU
	return m;
}

Mesh * Mesh::generateQuadPatch() {
	Mesh * m = new Mesh ();
	m-> numVertices = 4; // Number of vertices
	m-> type = GL_PATCHES ; // The OpenGL render type

	m-> vertices = new glm::vec3 [m-> numVertices ];
	m-> vertices [0] = glm::vec3 (-1.0f, -1.0f, 0.0f);
	m-> vertices [1] = glm::vec3 (-1.0f, 1.0f, 0.0f);
	m-> vertices [2] = glm::vec3 (1.0f, -1.0f, 0.0f);
	m-> vertices [3] = glm::vec3 (1.0f, 1.0f, 0.0f);

	m-> textureCoords = new glm::vec2 [m-> numVertices ];
	m-> textureCoords [0] = glm::vec2 (0.0f, 1.0f);
	m-> textureCoords [1] = glm::vec2 (0.0f, 0.0f);
	m-> textureCoords [2] = glm::vec2 (1.0f, 1.0f);
	m-> textureCoords [3] = glm::vec2 (1.0f, 0.0f);

	m-> bufferData (); // Function containing all of the VAO and VBO setup

	return m;
}

//How you implement this function is up to you, but it
//should create some VBOs (and perhaps a VAO?), and upload
//some data into it, so that it can be used by the Draw function
void Mesh :: bufferData () {
	#define normalIndex 3

	glBindVertexArray(arrayObject );
	glGenBuffers(1, &bufferObject[VERTEX_BUFFER]);
	glBindBuffer(GL_ARRAY_BUFFER , bufferObject[VERTEX_BUFFER]);
	glBufferData(GL_ARRAY_BUFFER , numVertices * sizeof(glm::vec3),
		vertices ,GL_STATIC_DRAW );
	glVertexAttribPointer(VERTEX_BUFFER ,3, GL_FLOAT ,GL_FALSE ,0, 0);
	glEnableVertexAttribArray(VERTEX_BUFFER);

	if(textureCoords) { 
		glGenBuffers(1, & bufferObject[ TEXTURE_BUFFER ]);
		glBindBuffer(GL_ARRAY_BUFFER , bufferObject[ TEXTURE_BUFFER ]);
		glBufferData(GL_ARRAY_BUFFER , numVertices * sizeof(glm::vec2),
			textureCoords , GL_STATIC_DRAW);
		glVertexAttribPointer(TEXTURE_BUFFER , 2, GL_FLOAT , GL_FALSE ,0 ,0);
		glEnableVertexAttribArray(TEXTURE_BUFFER);
	}

	if(colours) {
		glGenBuffers(1, &bufferObject[COLOUR_BUFFER]);
		glBindBuffer(GL_ARRAY_BUFFER , bufferObject[COLOUR_BUFFER]);
		glBufferData(GL_ARRAY_BUFFER , numVertices * sizeof(glm::vec4),
			colours ,GL_STATIC_DRAW);
		glVertexAttribPointer(COLOUR_BUFFER ,4 ,GL_FLOAT ,GL_FALSE ,0 ,0);
		glEnableVertexAttribArray(COLOUR_BUFFER);
	}

	if(normals) {
		glGenBuffers(1, & bufferObject [NORMAL_BUFFER]);
		glBindBuffer(GL_ARRAY_BUFFER ,bufferObject[NORMAL_BUFFER]);
		glBufferData(GL_ARRAY_BUFFER ,numVertices * sizeof(glm::vec3),
			normals, GL_STATIC_DRAW);
		glVertexAttribPointer(NORMAL_BUFFER ,3, GL_FLOAT ,GL_FALSE ,0 ,0);
		glEnableVertexAttribArray(NORMAL_BUFFER);
	}

	if(indices) {
		glGenBuffers(1, &bufferObject[INDEX_BUFFER]);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,
			bufferObject[INDEX_BUFFER]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER ,sizeof(faces),
			faces, GL_STATIC_DRAW );
	}

	glBindBuffer( GL_ARRAY_BUFFER, 0 );
	glBindVertexArray (0);
}

Mesh*	Mesh::loadMeshFile(const string &filename) {
	Mesh *m = new Mesh ();

	std::ifstream f(filename);

	if (!f) {
		return NULL;
	}

	//m->type = GL_TRIANGLES;
	f >> m-> numVertices;

	int hasTex = 0;
	int hasColour = 0;

	f >> hasTex ; // Oooh ! Sneak preview of later tutorial ...
	f >> hasColour;

	m-> vertices = new glm::vec3 [m->numVertices];
	m-> textureCoords = new glm::vec2 [m->numVertices ];
	m-> colours = new glm::vec4[m->numVertices ];

	for (int i = 0; i < m-> numVertices ; ++i) {
		f >> m-> vertices [i].x;
		f >> m-> vertices [i].y;
		f >> m-> vertices [i].z;
	}
	if( hasColour ) {
		for (int i = 0; i < m-> numVertices ; ++i) {
			f >> m-> colours [i].x; 
			f >> m-> colours [i].y;
			f >> m-> colours [i].z; 
			f >> m-> colours [i].w;
		}
	}
	if( hasTex ) { // new bit !!
		for ( unsigned int i = 0; i < m -> numVertices ; ++ i ) {
			f >> m -> textureCoords [ i ]. x ;
			f >> m -> textureCoords [ i ]. y ;
		}
	} // end of new bit :)


	for(int i = 0; i < m->numVertices; i++){
		if(i < 6){
			m->colours [i].x = 100.1f;
			m->colours [i].y = 0.0f;
			m->colours [i].z = 0.0f;
			m->colours [i].w = 1.0f;
		}else if(i >= 6 && i < 12) {
			m->colours [i].x = 0.0f;
			m->colours [i].y = 100.0f;
			m->colours [i].z = 0.0f;
			m->colours [i].w = 1.0f;
		}else if(i >= 6 && i < 12) {
			m->colours [i].x = 0.0f;
			m->colours [i].y = 0.0f;
			m->colours [i].z = 100.0f;
			m->colours [i].w = 1.0f;
		}else if(i >= 12 && i < 18) {
			m->colours [i].x = 100.0f;
			m->colours [i].y = 100.0f;
			m->colours [i].z = 0.0f;
			m->colours [i].w = 1.0f;
		}else if(i >= 18 && i < 24) {
			m->colours [i].x = 100.0f;
			m->colours [i].y = 0.0f;
			m->colours [i].z = 100.0f;
			m->colours [i].w = 0.0f;
		}else if(i >= 24 && i < 30) {
			m->colours [i].x = 0.0f;
			m->colours [i].y = 100.0f;
			m->colours [i].z = 100.0f;
			m->colours [i].w = 1.0f;
		}else if(i >= 30) {
			m->colours [i].x = 100.0f;
			m->colours [i].y = 100.0f;
			m->colours [i].z = 100.0f;
			m->colours [i].w = 1.0f;
		}
	}

	m->generateNormals();
	m->bufferData();	//Send our new data to the GPU
	return m;
}

void Mesh::generateNormals () {
	if (!normals) {
		normals = new glm::vec3[numVertices];
	}
	for ( GLuint i = 0; i < numVertices ; ++i){
		normals[i] = glm::vec3();
	}
	if( indices ) { // Generate per - vertex normals
		for ( GLuint i = 0; i < numIndices ; i +=3){
			unsigned int a = indices [i];
			unsigned int b = indices [i +1];
			unsigned int c = indices [i +2];

			glm::vec3 normal = glm::cross(
				( vertices [b]- vertices [a]) ,( vertices [c]- vertices [a ]));

			normals [a] += normal ;
			normals [b] += normal ;
			normals [c] += normal ;
		}
	}
	else { // It 's just a list of triangles , so generate face normals
		for ( GLuint i = 0; i < numVertices ; i +=3){
			glm::vec3 &a = vertices [i];
			glm::vec3 &b = vertices [i +1];
			glm::vec3 &c = vertices [i +2];

			glm::vec3 normal = glm::cross(b-a,c-a);

			normals [i] = normal;
			normals [i+1] = normal;
			normals [i+2] = normal;
		}
	}
	for ( GLuint i = 0; i < numVertices; ++i){
		glm::normalize(normals[i]);
	}
}
