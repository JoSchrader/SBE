#include "ClientPCH.h"
#include "..\Camera.h"

SBR::Mesh* CreatePlane();

void main()
{
	
	SBR::Mesh* plane = CreatePlane();
	/*
	SBR::i3fP3fN2fT::Model* model = plane->To_i3fP3fN2fT_Model();

	char* buffer = (char*)malloc(model->GetSize());
	model->Save(buffer);

	SBR::i3fP3fN2fT::Model *model2 = new SBR::i3fP3fN2fT::Model();
	model2->Load(buffer);

	int size = 0;
	char* bufferLewl = SBR::File::Read("Content/Models/Porsche_911.sbm", &size);
	auto loadedPorsche = new SBR::i3fP3fN2fT::Model();
	loadedPorsche->Load(bufferLewl);
	
	auto obj = SBR::Loader::OBJ(" Content\\Models\\Porsche_911.obj");

	SBR::i3fP3fN2fT::Model* proscheModel = obj->objObjects[0]->mesh->To_i3fP3fN2fT_Model(); 
	char* porscheBuffer = (char*)malloc(proscheModel->GetSize());
	proscheModel->Save(porscheBuffer);

	SBR::i3fP3fN2fT::Model *porscheLoaded = new SBR::i3fP3fN2fT::Model();
	porscheLoaded->Load(porscheBuffer);

	SBR::File::Write("Content/Models/Porsche_911.sbm", porscheBuffer, proscheModel->GetSize());*/

	glewExperimental = GL_TRUE;
	SBI::Input::SBI_Init();
	SBN::Network::Init();
	SBI::Window* window = SBI::Input::CreateWindowXX(1920, 1080, "Client");
	window->CatchCursor();
	SBI::Keyboard* keyboard = new SBI::Keyboard(window);
	SBI::Cursor* cursor = new SBI::Cursor(window);
	SBI::Time* time = new SBI::Time();
	SBGM::Pipeline* pipe = new SBGM::Pipeline();
	pipe->viewMatrix = SBM::Matrix4::LookAt(0, 0, -40, 0, 0, 0, 0, 1, 0);
	pipe->projectionMatrix = SBM::Matrix4::Perspective(60, 16.0f/9.0f, 1, 1000);
	*pipe = SBM::Matrix4::Scale(12, 12, 12);
	
	SBR::VBO* vbo = new SBR::VBO(plane);
	
	SBR::Shader* frag = SBR::Loader::Shader("Content/Shaders/DefaultShader.frag");
	SBR::Shader* vert = SBR::Loader::Shader("Content/Shaders/DefaultShader.vert");
	SBR::Program* program = new SBR::Program(vert, frag);

	SBR::VAO* vao = new SBR::VAO(vbo, program);

	Camera* camera = new Camera();

	while (!window->ShouldClose())
	{
		keyboard->Update();
		cursor->Update();
		time->Update();

		camera->Update(keyboard, cursor, time, pipe);
		glBindVertexArray(vao->glid);

		*pipe *= SBM::Matrix4::RotationY(0.0001f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		pipe->UpdateMatrices(program->glid);
		glUseProgram(program->glid);
		glVertexArrayVertexBuffer(vao->glid, 0, vbo->glid, 0, sizeof(SBR::VBO::VBO_Vertex));
		glBindVertexArray(vao->glid);
		glDrawArrays(GL_TRIANGLES, 0, vbo->vertexCount);

		window->Update();
		window->SwapBuffers();
		glfwPollEvents();
	}

	SBN::Network::Cleanup();

}

SBR::Mesh* CreatePlane()
{
	SBR::Mesh* mesh = new SBR::Mesh();

	mesh->positions.push_back(SBM::Vector3(-1, -1, 0));
	mesh->positions.push_back(SBM::Vector3(+1, -1, 0));
	mesh->positions.push_back(SBM::Vector3(+1, +1, 0));
	mesh->positions.push_back(SBM::Vector3(-1, +1, 0));

	mesh->normals.push_back(SBM::Vector3(0, 0, -1));

	mesh->uvs.push_back(SBM::Vector2(0, 0));
	mesh->uvs.push_back(SBM::Vector2(1, 0));
	mesh->uvs.push_back(SBM::Vector2(1, 1));
	mesh->uvs.push_back(SBM::Vector2(0, 1));

	std::vector<SBR::VertexIndex> vertexes;
	vertexes.push_back(SBR::VertexIndex(0, 0, 0));
	vertexes.push_back(SBR::VertexIndex(1, 1, 0));
	vertexes.push_back(SBR::VertexIndex(2, 2, 0));
	vertexes.push_back(SBR::VertexIndex(3, 3, 0));

	mesh->triangleIndexes.push_back(SBR::TriangleIndex(vertexes[0], vertexes[1], vertexes[2]));
	mesh->triangleIndexes.push_back(SBR::TriangleIndex(vertexes[2], vertexes[3], vertexes[0]));

	return mesh;
}