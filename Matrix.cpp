#include "Matrix.hpp"
#include "Camera.hpp"
#include "CubeTuto.hpp"

using namespace std;
using namespace glm;
using namespace GC_3D;


GLuint MatrixID;
GLuint ViewID;
GLuint ModelID;
GLuint TextureLocId;

mat4 mvp;
mat4 View;
mat4 Projection;

mat4 Matrix::ModelViewMaker(mat4 Model) {

	Camera Camera;
	CubeTuto Cube;

	// Model view Parameter
	View = Camera.GetViewMatrix();

	Projection = perspective(radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);

	// Our ModelViewProjection : multiplication of our 3 matrices
	mvp = Projection * View * Model;

	return mvp;
}

void Matrix::ModelViewSetter(GLuint Program, GLuint &TextureLocId, mat4 Model) {

	MatrixID = glGetUniformLocation(Program, "MVP");
	ViewID = glGetUniformLocation(Program, "View");
	ModelID = glGetUniformLocation(Program, "Model");
	TextureLocId = glGetUniformLocation(Program, "MyTextureSampler");

	// Send our transformation to the currently bound shader, in the "MVP" uniform
	// This is done in the main loop since each model will have a different MVP matrix (At least for the M part)
	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvp[0][0]);
	glUniformMatrix4fv(ViewID, 1, GL_FALSE, &View[0][0]);
	glUniformMatrix4fv(ModelID, 1, GL_FALSE, &Model[0][0]);

}
