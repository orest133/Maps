#pragma once

#include <iostream>
#include <map>
#include <string>
#define GLEW_STATIC
#include <GL/glew.h>

#include <glm/gtc/type_ptr.hpp>
// FreeType
#include <ft2build.h>
#include FT_FREETYPE_H
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
// GL includes
#include "Shader.h"
class Text
{
public:
	Text();
	~Text();
	int a = 0;
public:void  RenderText(Shader *Shader, std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color);
	   struct Character {
		   GLuint TextureID;   // ID handle of the glyph texture
		   glm::ivec2 Size;    // Size of glyph
		   glm::ivec2 Bearing;  // Offset from baseline to left/top of glyph
		   GLuint Advance;    // Horizontal offset to advance to next glyph
	   };
	   void loadTexture();
	   std::map<GLchar, Character> Characters;

	   GLuint VAOText, VBOText;
	   FT_Library ft;
	   FT_Face face;

};

