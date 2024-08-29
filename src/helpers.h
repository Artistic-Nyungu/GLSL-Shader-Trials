#include "config.h"

using namespace std;

struct Vector3
{
    float X;
    float Y;
    float Z;
};

struct Vector2
{
    float X;
    float Y;
};

int genRandInt(int min, int max)
{
    return rand()%(max - min + 1) + min;
}

float genRandFloat(float min, float max)
{
    std::stringstream ss;
    int minUnits, maxUnits, minDecimalPoints, maxDecimalPoints;
    bool isUnits = true;

    ss << min;
    std::string value;
    ss >> value;
    for(char digit: value)
    {
        if(isUnits && digit == '.')
        {
            isUnits = false;
            ss >> minUnits;
            continue;
        }
        
        ss << digit;
    }
    ss >> minDecimalPoints;


    isUnits = true;
    ss << max;
    value;
    ss >> value;
    for(char digit: value)
    {
        if(isUnits && digit == '.')
        {
            isUnits = false;
            ss >> maxUnits;
            continue;
        }
        
        ss << digit;
    }
    ss >> maxDecimalPoints;


    ss << ((minUnits == maxUnits) ? 0 : genRandInt(minUnits, maxUnits)) << '.' << ((minDecimalPoints == maxDecimalPoints) ? 0 : genRandInt(minDecimalPoints, maxDecimalPoints));

    float randF;
    ss >> randF;

    return randF;
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

/// @brief Creates a shader program with a vertex shader module and a fragment shader module
/// @param vertFilepath File path to the vertex shader source code
/// @param fragFilepath File path to the fragment shader source code
/// @return Shader program
unsigned int makeShader(const string& vertFilepath, const string& fragFilepath)
{
    unsigned int shader = glCreateProgram();
    unsigned int vertex, fragment;
    // Attach shader modules to shader program
    glAttachShader(shader, vertex = makeModule(vertFilepath, GL_VERTEX_SHADER)); 
    glAttachShader(shader, fragment = makeModule(fragFilepath, GL_FRAGMENT_SHADER)); 
    
    glLinkProgram(shader);

    int success;
    glGetProgramiv(shader, GL_LINK_STATUS, &success); // Shader integer value of link status into success variable
    if(!success)
    {
        // Get shader error log and print in the error stream
        char errLog[1024];
        glGetProgramInfoLog(shader, 1024, NULL, errLog);
        cerr << "Shader linking error:\n" << errLog << endl;
    }

    // Shader modules are already copied over and linked, so delete them
    glDeleteShader(vertex);
    glDeleteShader(fragment);

    return shader;
}

/// @brief Resizes the viewport that OpenGL has to work with
/// @param window A pointer to the GLFWwindow
/// @param width The viewport width
/// @param height The viewport height
/// @param offsetX The viewport's x offset
/// @param offsetY The viewport's y offset
void resizeViewport(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}