#pragma once

#include "config.h"

using namespace std;

class Shader
{
    public:
    Shader(){_id = 0;}

    Shader(const string& vertFilepath, const string& fragFilepath)
    {
        _id = makeShader(vertFilepath, fragFilepath);
    }

    unsigned int GetID() const
    {
        return _id;
    }

    void Use()
    {
        glUseProgram(_id);
    }

    private:
    unsigned int _id;

    /// @brief Read shader source code from a file
    /// @param filepath File with the shader source code
    /// @param module_type 
    /// @return 
    unsigned int makeModule(const string& filepath, unsigned int module_type)
    {
        ifstream file;
        stringstream ssStream;
        string line, absolutePath;

        absolutePath = filesystem::absolute(filesystem::path(filepath)).string();

        file.open(absolutePath);

        if (file.fail()) 
        {
            std::cerr << "Could not open file: " << absolutePath << std::endl;

            // Check if the file exists
            if (!std::filesystem::exists(absolutePath))
                std::cerr << "File does not exist." << std::endl;
            else
                std::cerr << "File exists but could not be opened. Check permissions." << std::endl;
        } 
        else
            std::cout << "File " << absolutePath << " opened successfully." << std::endl;

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
};