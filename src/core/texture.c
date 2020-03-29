//
//  texture.c
//  floppycock
//
//  Created by Stephen Gowen on 1/29/14.
//  Copyright (c) 2014 Techne Games. All rights reserved.
//

#include "texture.h"
#include "platform_gl.h"
#include <assert.h>

GLuint load_texture(const GLsizei width, const GLsizei height, const GLenum type, const GLvoid* pixels)
{
	GLuint texture_object_id;
	glGenTextures(1, &texture_object_id);
	assert(texture_object_id != 0);

	glBindTexture(GL_TEXTURE_2D, texture_object_id);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, type, width, height, 0, type, GL_UNSIGNED_BYTE, pixels);
    

	glBindTexture(GL_TEXTURE_2D, 0);
	return texture_object_id;
}