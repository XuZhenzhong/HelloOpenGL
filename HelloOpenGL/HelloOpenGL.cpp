#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include <iostream>
#include <stdio.h>
#include <Windows.h>
#include <cmath>

using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
//setting
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
/*const char *vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"gl_Postion = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
const char *fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\n\0";*/
const char *vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos, 1.0);\n"
"}\0";

const char *fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"uniform vec4 ourColor;\n"
"void main()\n"
"{\n"
"   FragColor = ourColor;\n"
"}\n\0";


int main()
{
	//glfw: initialize and configure
	//------------------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);			//设置主版本号GLFW版本号
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);			//设置次版本号
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);	//明确GLFW的核心模式

#ifdef _APPLE_
	GLFWwindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	//兼容MAC OS X
#endif // _APPLE_
	//glfw window creation
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		cout << "failed to creat GLFW window" << endl;
		glfwTerminate();
		getchar();
		return -1;
	}
	//this function makes the context of the specified window current on the calling thread.
	glfwMakeContextCurrent(window);
	//注册函数，告知GLFW希望每当窗口调整大小的时候调用此函数；
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	//glad: load all OpenGL function pointers
	//---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		//初始化GLAD
		cout << "failed to initialize GLAD" << endl;
		getchar();
		return -1;
	}
	/*
	while (!glfwWindowShouldClose(window))		//glfwWindowShouldClose函数在我们每次循环的开始前检查一次GLFW是否被要求退出
	{
	processInput(window);
	glClearColor(0.2f,0.3f,0.3f,1.0f);//清空屏幕颜色缓冲
	glClear(GL_COLOR_BUFFER_BIT);
	glfwSwapBuffers(window);		//交换颜色缓冲（它是一个储存着GLFW窗口每一个像素颜色值的大缓冲）它在这一迭代中被用来绘制，并且将会作为输出显示在屏幕上。
	glfwPollEvents();				//检查有没有触发什么事件（比如键盘输入、鼠标移动等）更新窗口状态，并调用对应的回调函数（可以通过回调方法手动设置）。
	}
	glfwTerminate();
	getchar();
	return 0;
	}
	void framebuffer_size_callback(GLFWwindow* window, int width, int height)
	{
	glViewport(0,0,width,height);
	//设置OpenGL渲染窗口的尺寸大小，即视口；
	}

	void processInput(GLFWwindow * window)
	{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE)==GLFW_PRESS)
	//检查ESC这个按键是否按下
	{
	glfwSetWindowShouldClose(window,true);
	}
	}
	*/
	// build and compile our shader program
	//--------------------------------------
	//vertex shader
	int vertexShader = glCreateShader(GL_VERTEX_TEXTURE);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	//check for shader compile errors
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << endl;
	}
	//fragment shader
	int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	//check for shader compile errors
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << endl;
	}
	//link shaders
	int shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	//check for linking errors
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED" << infoLog << endl;
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	//set up vertex data(and buffer(s)) and configure vertex attributes
	//----------------------------------------------------------------
	float vertices[] = {
		0.5f, -0.5f, 0.0f,		//left
		-0.5f, -0.5f, 0.0f,		//right
		0.0f,  0.5f, 0.0f		//top
	};
	/*	float vertices[] = {
	0.5f,   0.5f, 0.0f,			//top right
	0.5f,  -0.5f, 0.0f,		//bottom right
	-0.5f, -0.5f, 0.0f,		//bottom left
	-0.5f,  0.5f, 0.0f			//top left
	};
	unsigned int indices[] = {
	0,1,2,	//first Triangle
	1,2,3	//second Triangle
	};*/
	//unsigned int VBO, VAO,EBO;
	unsigned int VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	//glGenBuffers(1, &EBO);
	//bind the Vertext Array Object first, then bind and set vertex buffer(s), and then
	//configure vertex attributes.
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//note that this is allowed, the call to glVertexAttribPointer registered VBO 
	//as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	/*	you can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO,
	but this  rarely happens. Modifying other VAOs requires a call to glBindVertexArray anyways
	so we generally don't unbind VAOs(nor VBOs) when it's not directly necessary

	The function glBindVertexArrart binds a vertex array object.
	Any subsequent VBO, EBO, glVertexAttribPointer and
	glEnableVertexAttribArray calls will be stored inside the VAO currently bound.
	*/
	glBindVertexArray(VAO);

	//uncommnet this call to draw in wireframe pulygons
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	//render loop
	//----------
	while (!glfwWindowShouldClose(window))
	{
		//input
		//-----
		processInput(window);

		//render
		//-----
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//draw our first triangle
		glUseProgram(shaderProgram);

		// update shader uniform
		float timeValue = glfwGetTime();
		float greenValue = sin(timeValue) / 2.0f + 0.5f;
		int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
		glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

		//seeing as we only have a single VAO ;				  
		//there's no need to bind it every time, but we'll do so to keep things a bit more organized

		//render the triangle
		glDrawArrays(GL_TRIANGLES, 0, 3);
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		//glBindVertexArray(0);//no need to unbind it every time
		//glfw: swap buffers and poll IOevents(keys pressed/released, mouse moved etd.);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	//optional: de-allocate all resources once they've outlived their purpose:
	//-----------------------------------------------------------------------
	glDeleteVertexArrays(1, &VBO);
	glDeleteBuffers(1, &VBO);
	//glDeleteBuffers(1, &EBO);
	glfwTerminate();
	return 0;
}
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}

// glfw: whenever the window size changed(by OS or user resize)this callback function executes
// -------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	//make sure the viewport matches the new window dimensions; note that width and
	//height will be singificantly larger than specified on retina displays
	glViewport(0, 0, width, height);
}






















