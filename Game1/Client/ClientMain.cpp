#include "ClientPCH.h"
#include "..\Camera.h"

void SetGLProperties()
{
	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);				// Black Background
	glClearDepth(1.0f);									// Depth Buffer Setup
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_MULTISAMPLE);
}

void init()
{
	glewExperimental = GL_TRUE;
	SBI::Input::SBI_Init();
	SBN::Network::Init();

	
}

void main()
{
	init();

	SBI::WindowHint* windowHint = new SBI::WindowHint();

	SBI::Window* window = SBI::Input::CreateWindowXX(1920, 1080, "Client");
	window->CatchCursor();
	SBGM::Pipeline* pipe = new SBGM::Pipeline();
	pipe->viewMatrix = SBM::Matrix4::LookAt(0, 0, -40, 0, 0, 0, 0, 1, 0);
	pipe->projectionMatrix = SBM::Matrix4::Perspective(60, 16.0f / 9.0f, 1, 1000);
	*pipe = SBM::Matrix4::Scale(1, 1, 1);

	SBR::Shader* frag = SBR::Loader::Shader("Content/Shaders/WIPShader.frag");
	SBR::Shader* vert = SBR::Loader::Shader("Content/Shaders/WIPShader.vert");
	SBR::Program* program = new SBR::Program(vert, frag);

	SBR::f3fPc3fN2sT::Model* flatLoaded = SBR::f3fPc3fN2sT::Model::LoadFromFile("Content/Models/r8_gt.sbm", false);
	SBR::f3fPc3fN2sT::ModelPart* merged = flatLoaded->MergeParts();
	SBR::VBO* vbo = new SBR::VBO(merged);
	SBR::VAO* vao = new SBR::VAO(vbo, program);

	delete flatLoaded;
	delete merged;

	Camera* camera = new Camera();

	float lastUpdate = 0;
	SetGLProperties();
	while (!window->ShouldClose())
	{
		if (window->keyboard->GetKeyPressed(SBI::Keys::F5) && (window->time->ellapsedTime - lastUpdate) > 0.5)
		{
			lastUpdate = window->time->ellapsedTime;
			frag = SBR::Loader::Shader("Content/Shaders/WIPShader.frag");
			vert = SBR::Loader::Shader("Content/Shaders/WIPShader.vert");
			program = new SBR::Program(vert, frag);
		}

		window->keyboard->Update();
		window->cursor->Update();
		window->time->Update();

		camera->Update(window->keyboard, window->cursor, window->time, pipe);
		glBindVertexArray(vao->glid);

		*pipe *= SBM::Matrix4::RotationY(0.0001f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		pipe->UpdateMatrices(program->glid);
		glUseProgram(program->glid);
		glVertexArrayVertexBuffer(vao->glid, 0, vbo->glid, 0, sizeof(SBR::f3fPc3fN2sT::CompressedVertex));
		glBindVertexArray(vao->glid);
		glDrawArrays(GL_TRIANGLES, 0, vbo->vertexCount);

		window->Update();
		window->SwapBuffers();
		glfwPollEvents();
	}
	SBI::Input::Teminate();
	SBN::Network::Cleanup();
	
}