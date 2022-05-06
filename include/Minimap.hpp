#pragma once

#include <windows.h>
#include <GL/glew.h>
#include <GL/gl.h>
#include <iostream>

#include "SceneObject.hpp"

class Minimap : public SceneObject {
public:
    Minimap();
    ~Minimap();

protected:
    void privateInit();
    void privateRender();
    void privateUpdate();

    void CheckFrameBufferStatus();

private:
    unsigned int g_fbo;				// frame buffer object
    unsigned int g_pbo;				// pixel buffer object
    unsigned int g_texture;			// texture object
    int g_iTexWidth  = 512;		// texture width
    int g_iTexHeight = 512;		// texture height
};