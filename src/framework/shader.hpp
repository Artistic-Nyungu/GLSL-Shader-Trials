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

    /// @brief Gets the unsigned int that represents the shader
    /// @return Shader ID
    unsigned int GetID() const
    {
        return _id;
    }

    unsigned int GenerateTexture(const string& filename, GLenum format = GL_RGB, GLenum textureUnit = GL_TEXTURE0)
    {
        glActiveTexture(textureUnit);

        // Set texture wrap parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

        // Set border color
        float borderColor[] = {0.f, 0.f, 0.f, 1.f};
        glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

        // Set texture filtering parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        int width;
        int height;
        int nChannels;

        // loading the image file
        stbi_set_flip_vertically_on_load(true);
        unsigned char* data = stbi_load(filename.c_str(), &width, &height, &nChannels, 0);

        if(!data)
        {
            cerr << "Could not load texture image: " << filesystem::absolute(filesystem::path(filename)).string() << endl;
            return 0;
        }

        unsigned int texture;
        glGenTextures(1, &texture);

        glBindTexture(GL_TEXTURE_2D, texture);

        // Generate texture
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);    // For low res rendering bluh*3

        stbi_image_free(data);
        glBindTexture(GL_TEXTURE_2D, 0);

        return texture;
    }

    void SetUniform(const string& uniformName, ImVec2 value)
    {
        int uniformLocation = glGetUniformLocation(_id, uniformName.c_str());
        glUniform2f(uniformLocation, value.x, value.y);
    }

    void SetUniform(const string& uniformName, ImVec4 value)
    {
        int uniformLocation = glGetUniformLocation(_id, uniformName.c_str());
        glUniform4f(uniformLocation, value.x, value.y, value.z, value.w);
    }

    void SetUniform(const string& uniformName, float value)
    {
        int uniformLocation = glGetUniformLocation(_id, uniformName.c_str());
        glUniform1f(uniformLocation, value);
    }

    void SetUniform(const string& uniformName, int value)
    {
        int uniformLocation = glGetUniformLocation(_id, uniformName.c_str());
        glUniform1i(uniformLocation, value);
    }

    void SetUniform(const string& uniformName, bool value)
    {
        int uniformLocation = glGetUniformLocation(_id, uniformName.c_str());
        glUniform1i(uniformLocation, value? 1: 0);
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