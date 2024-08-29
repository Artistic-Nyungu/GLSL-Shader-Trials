#include "helpers.h"

int main()
{
    // To determine the window size, 16:9 ratio
    unsigned int size = 100;
    unsigned int VBO, VAO, EBO;
    // Create a window ref
    GLFWwindow* window;

    // Initialize library
    if(!glfwInit())
    {
        std::cerr << "GLFW could not start\n";
        return -1;  
    }

    // Instantiate window
    window = glfwCreateWindow(640, 480, "OpenGL Programming Journey", NULL, NULL);
    if(!window)
    {
        std::cerr << "Failed to create window\n";
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

    // Set callback function for when the window size is changed
    glfwSetFramebufferSizeCallback(window, resizeViewport);

    unsigned int shader = makeShader("../src/shaders/vertex.txt", "../src/shaders/fragment.txt");

    float vertices[] = {
        0.5f,   0.5f,   0.0f, // top right
        0.5f,  -0.5f,   0.0f, // bottom right
       -0.5f,  -0.5f,   0.0f, // bottom left
       -0.5f,   0.5f,   0.0f // top left
    };
    
    unsigned int indeces[] = {
        0, 1, 3,
        1, 2, 3
    };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) , vertices, GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indeces), indeces, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*) 0);
    glEnableVertexAttribArray(0);


    // Unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // Render loop
    while(!glfwWindowShouldClose(window))
    {
        glClearColor(0.4f, 0.7f, 0.49f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shader);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        glfwPollEvents();
    }


    glDeleteProgram(shader);
    glfwTerminate();

    return 0;
}
