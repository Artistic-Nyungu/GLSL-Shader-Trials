#pragma once

#include <iostream>

// Image loader library
#define STB_IMAGE_IMPLEMENTATION

#ifdef _DEBUG
#include "dependencies/glad/glad.h"
#include "_deps/glfw-src/include/GLFW/glfw3.h"
#include "dependencies/imgui/imgui.h"
#include "dependencies/imgui/imgui_impl_glfw.h"
#include "dependencies/imgui/imgui_impl_opengl3.h"
#include "dependencies/stb/stb_image.h"
#else
#include <glad/glad.h>  // OpenGL, has to be before glfw
#include <GLFW/glfw3.h> // Windowing stuff
#include <imgui/imgui.h>  // UI stuff
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h> 
#include <stb/stb_image.h>
#endif

// Reading from files
#include <fstream>
#include <sstream>
#include <string>

#include <filesystem>