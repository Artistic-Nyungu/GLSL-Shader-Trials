#pragma once

#include <iostream>

#ifdef _DEBUG
#include "dependencies/glad/glad.h"
#include "_deps/glfw-src/include/GLFW/glfw3.h"
#else
#include <glad/glad.h>  // OpenGL, has to be before glfw
#include <GLFW/glfw3.h> // Windowing stuff
#endif

// Reading from files
#include <fstream>
#include <sstream>
#include <string>

#include <vector>