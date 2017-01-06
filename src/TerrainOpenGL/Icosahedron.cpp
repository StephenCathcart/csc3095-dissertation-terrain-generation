#include "Icosahedron.h"
#include "Mesh.h"
#include <iostream>

Icosahedron::Icosahedron(void) {
	glewInit();
	this->tessLevelInner = 3;
	this->tessLevelOuter = 2;

	glGenVertexArrays(1, &vao);
	createIcosahedron();
}


Icosahedron::~Icosahedron(void) {
	glDeleteVertexArrays(1, &vao);
}

void Icosahedron::createIcosahedron() {
    const int faces[] = {
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

	const float vertices[] = {
         0.000f,  0.000f,  1.000f,
         0.894f,  0.000f,  0.447f,
         0.276f,  0.851f,  0.447f,
        -0.724f,  0.526f,  0.447f,
        -0.724f, -0.526f,  0.447f,
         0.276f, -0.851f,  0.447f,
         0.724f,  0.526f, -0.447f,
        -0.276f,  0.851f, -0.447f,
        -0.894f,  0.000f, -0.447f,
        -0.276f, -0.851f, -0.447f,
         0.724f, -0.526f, -0.447f,
         0.000f,  0.000f, -1.000f 
	};

	indexCount = sizeof(faces) / sizeof(faces[0]);

	// Bind the VAO:
    glBindVertexArray(vao);

    // Create the VBO for positions:
    GLuint positions;
    GLsizei stride = 3 * sizeof(float);
    glGenBuffers(1, &positions);
    glBindBuffer(GL_ARRAY_BUFFER, positions);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(VERTEX_BUFFER);
	glVertexAttribPointer(VERTEX_BUFFER, 3, GL_FLOAT, GL_FALSE, stride, 0);
	std::cout << "sizeof(vertices): " << sizeof(vertices) << std::endl;

    // Create the VBO for indices:
    GLuint indices;
    glGenBuffers(1, &indices);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indices);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(faces), faces, GL_STATIC_DRAW); 
	std::cout << "sizeof(faces): " << sizeof(faces) << std::endl;

	glBindVertexArray(0);
}

void Icosahedron::render(GLuint program) {
	updateUniforms(program);

	glPatchParameteri(GL_PATCH_VERTICES, 3);

	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
	//glDrawElements(GL_PATCHES, indexCount, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
}

void Icosahedron::update(float msec) {
}

void Icosahedron::updateUniforms(GLuint program) {
	glUniform1f(glGetUniformLocation(program, "tessLevelInner"), tessLevelInner);
	glUniform1f(glGetUniformLocation(program, "tessLevelOuter"), tessLevelOuter);
    
	glm::vec4 lightPosition = glm::vec4(0.25f, 0.25f, 1.0f, 0.0f);
    glUniform3fv(glGetUniformLocation(program, "lightPosition"), 1, &lightPosition.x);

	//glm::mat3 nm = glm::transpose(normals);
 //   float packed[9] = { nm.col0.x, nm.col1.x, nm.col2.x,
 //                       nm.col0.y, nm.col1.y, nm.col2.y,
 //                       nm.col0.z, nm.col1.z, nm.col2.z };
 //   glUniformMatrix3fv(uniforms.normalMatrix, 1, 0, &packed[0]);

    // Render the scene:
    glUniform3f(glGetUniformLocation(program, "ambientMaterial"), 0.04f, 0.04f, 0.04f);
    glUniform3f(glGetUniformLocation(program, "diffuseMaterial"), 0, 0.75, 0.75);
}