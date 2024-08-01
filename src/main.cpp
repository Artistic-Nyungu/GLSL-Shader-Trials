#include "config.h"

using namespace std;

unsigned int makeShader(const string& vertFilepath, const string& fragFilepath);
unsigned int makeModule(const string& filepath, unsigned int module_type);

int main()
{
    // Create a window ref
    GLFWwindow* window;

    // Initialize library
    if(!glfwInit())
    {
        std::cerr << "GLFW could not start\n";
        return -1;  
    }

    // Instantiate window
    window = glfwCreateWindow(640, 480, "Window", NULL, NULL);
    if(!window)
    {
        glfwTerminate();
        return -1;
    }
     
    // Make window's context current, has to be before loading glad
    glfwMakeContextCurrent(window);

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        glfwTerminate();
        return -1;
    }

    glClearColor(0.2f, 0.5f, 0.1f, 1.0f);

    unsigned int shader = makeShader("../src/vertex.txt", "../src/fragment.txt");

    while(!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shader);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    glDeleteProgram(shader);
    glfwTerminate();

    return 0;
}

/// @brief Creates a shader program with a vertex shader module and a fragment shader module
/// @param vertFilepath File path to the vertex shader source code
/// @param fragFilepath File path to the fragment shader source code
/// @return Shader program
unsigned int makeShader(const string& vertFilepath, const string& fragFilepath)
{
    vector<unsigned int> modules;

    modules.push_back(makeModule(vertFilepath, GL_VERTEX_SHADER));
    modules.push_back(makeModule(fragFilepath, GL_FRAGMENT_SHADER));

    unsigned int shader = glCreateProgram();
    for(unsigned int module: modules)
    {
        glAttachShader(shader, module); // Attach shader modules to shader program
    }
    glLinkProgram(shader);

    int success;
    glGetProgramiv(shader, GL_LINK_STATUS, &success); // Shader integer value of link status into success variable
    if(!success)
    {
        // Get shader error log and print in the error stream
        char errLog[1024];
        glGetProgramInfoLog(shader, 1024, NULL, errLog);
        cerr << "Shader linking error:\n" << errLog << endl;

        // I think the function should terminate
    }

    // Shader modules are already copied over and linked, so delete them
    for(unsigned int module: modules)
    {
        glDeleteShader(module);
    }

    return shader;
}

/// @brief Read shader source code from a file
/// @param filepath File with the shader source code
/// @param module_type 
/// @return 
unsigned int makeModule(const string& filepath, unsigned int module_type)
{
    ifstream file;
    stringstream ssStream;
    string line;

    file.open(filepath);

    while (getline(file, line))
    {
        ssStream << line << endl;
    }

    file.close();

    string shaderSource = ssStream.str();
    ssStream.str("");
    
    // Convert shader source to c_string
    const char* shaderSrc = shaderSource.c_str();

    // Compile shader module
    unsigned int shaderModule = glCreateShader(module_type);
    glShaderSource(shaderModule, 1, &shaderSrc, NULL);  // Attach source code to shader module
    glCompileShader(shaderModule);

    int success;
    glGetShaderiv(shaderModule, GL_COMPILE_STATUS, &success); // Shader integer value of compile status into success variable
    if(!success)
    {
        // Get shader error log and print in the error stream
        char errLog[1024];
        glGetShaderInfoLog(shaderModule, 1024, NULL, errLog);
        cerr << "Shader Module compilation error:\n" << errLog << endl;

        // I think the function should terminate
    }

    return shaderModule;
}