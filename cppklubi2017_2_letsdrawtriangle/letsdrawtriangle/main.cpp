#define _CRT_SECURE_NO_WARNINGS 1

#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <assert.h>
#include <string>
#include <iostream>
#include <time.h>


#define GL_CHECK(call)	\
		do {			\
			call;		\
			GLenum glerr = glGetError(); \
			assert(glerr == GL_NO_ERROR);\
		} while (0)

GLuint load_shader(GLenum type, const std::string& filepath)
{
	GLuint id = glCreateShader(type);

	FILE* file = fopen(filepath.c_str(), "rb");
	assert(file != NULL);
	fseek(file, 0, SEEK_END); //kelataan loppuun
	long size = ftell(file); // kysyt‰‰n tiedostokoko
	fseek(file, 0, SEEK_SET); // kelataan alkuun
	char* buffer = (char*)malloc(size + 1); //varaan muistia tekstille + 1 merkki nul terminaattorille
	fread(buffer, 1, size, file); // luetaan koko tiedosto bufferiin
	buffer[size] = '\0';
	fclose(file);

	GL_CHECK(glShaderSource(id, 1, (const GLchar**)&buffer, NULL));
	GL_CHECK(glCompileShader(id));

	// vapautetaan muisti
	free(buffer);

	GLint compiled = 0;
	GL_CHECK(glGetShaderiv(id, GL_COMPILE_STATUS, &compiled));

	if (compiled == 0)
	{
		char log[1024];
		GLsizei logLen;
		GL_CHECK(glGetShaderInfoLog(id, sizeof(log), &logLen, log));
		std::cout << "Failed to compile shader " << id << ": " << log;
		GL_CHECK(glDeleteShader(id));
		return 0;
	}

	return id;
}

int main(int argc, char* argv[])
{
	(void)argc; (void)argv;
	SDL_Init(SDL_INIT_VIDEO);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);

	SDL_Window* window = SDL_CreateWindow(
		"Ikkuna",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		640,
		480,
		SDL_WINDOW_OPENGL
		);

	//FULLSCREEN
	SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);

	SDL_GLContext context = SDL_GL_CreateContext(window);

	glewExperimental = GL_TRUE;
	glewInit();
	glGetError();

	//GL_CHECK(glClearColor(0.99f, 0.57f, 0.66f, 1.f));


	bool running = true;

	static const float vertices[] = {
		-1.0f, -1.f, 0.0f, 0.2f, 0.3f, 0.4f, 1.0f,
		1.0f, -1.f, 0.0f, 0.1f, 0.5f, 0.1f, 1.0f,
		0.0f, 1.0f, 0.0f, 0.4f, 0.7f, 0.9f, 1.0f
	};

	GLuint vsh = load_shader(GL_VERTEX_SHADER, "shaders/vertex.vs");
	GLuint fsh = load_shader(GL_FRAGMENT_SHADER, "shaders/fragment.fs");

	assert(vsh != 0 && fsh != 0);

	GLuint program = glCreateProgram();
	GL_CHECK(glAttachShader(program, vsh));
	GL_CHECK(glAttachShader(program, fsh));
	GL_CHECK(glLinkProgram(program));
	GLint linked;
	glGetProgramiv(program, GL_LINK_STATUS, &linked);

	if (linked == 0)
	{
		char log[1024];
		glGetProgramInfoLog(program, sizeof(log), NULL, log);
		std::cout << "Failed to link program: " << log;
		return 1;
	}


	GLuint VBO, VAO;

	GL_CHECK(glGenVertexArrays(1, &VAO));
	GL_CHECK(glBindVertexArray(VAO));

	GL_CHECK(glGenBuffers(1, &VBO));
	GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, VBO));

	GL_CHECK(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW));

	GL_CHECK(glEnableVertexAttribArray(0));
	GL_CHECK(glEnableVertexAttribArray(1));

	GLsizei stride = sizeof(float) * 7;

	GL_CHECK(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, nullptr));

	GL_CHECK(glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, stride, (void*)(sizeof(float) * 3)));

	// otetaan VBO pois p‰‰lt‰
	GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, 0));
	GL_CHECK(glBindVertexArray(0));

	while (running)
	{
		SDL_Event ev;
		while (SDL_PollEvent(&ev))
		{
			if (ev.type == SDL_QUIT)
				running = false;
		}

		uint32_t ticks = SDL_GetTicks();
		float secs = ticks / 1000.f;

		glClearColor(
			abs(sinf(secs) * 2 + 0.5f),
			abs(cosf(secs) * 2 + 0.5f),
			abs(tanf(secs) * 2 + 0.5f),
			1.f
			);

		GL_CHECK(glClear(GL_COLOR_BUFFER_BIT));

		GL_CHECK(glUseProgram(program));

		GLint location = glGetUniformLocation(program, "u_time");
		glUniform1f(location, ticks / 1000.f);

		GL_CHECK(glBindVertexArray(VAO));

		GL_CHECK(glDrawArrays(GL_TRIANGLES, 0, 3));

		GL_CHECK(glBindVertexArray(0));

		GL_CHECK(glUseProgram(0));

		SDL_GL_SwapWindow(window);
	}

	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}