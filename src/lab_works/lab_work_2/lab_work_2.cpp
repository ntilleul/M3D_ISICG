#include "imgui.h"
#include "lab_work_2.hpp"
#include "utils/read_file.hpp"
#include <iostream>

namespace M3D_ISICG
{
	const std::string LabWork2::_shaderFolder = "src/lab_works/lab_work_2/shaders/";

	LabWork2::~LabWork2()
	{
		glDeleteProgram( _program );
		glDeleteBuffers( 1, &_vbo );
		glDeleteBuffers( 1, &_vboColor );
		glDeleteBuffers( 1, &_elementBuffer );
		glDisableVertexArrayAttrib( _vao, 0 );
		glDeleteVertexArrays( 1, &_vao );
	}

	bool LabWork2::init()
	{
		std::cout << "Initializing lab work 2..." << std::endl;
		// Set the color used by glClear to clear the color buffer (in render()).
		glClearColor( _bgColor.x, _bgColor.y, _bgColor.z, _bgColor.w );

		_program = glCreateProgram();

		//Création des points
		_points.push_back( Vec2f( -0.5f, 0.5f ) );
		_points.push_back( Vec2f( 0.5f, -0.5f ) );
		_points.push_back( Vec2f( 0.5f, 0.5f ) );
		_points.push_back( Vec2f( -0.5f, -0.5f ) );

		_indices = { 0, 1, 2, 1, 2, 3 };

		_colors.push_back( Vec3f( 1.f, 0.f, 0.f ) );
		_colors.push_back( Vec3f( 0.f, 1.f, 0.f ) );
		_colors.push_back( Vec3f( 0.f, 0.f, 1.f ) );
		_colors.push_back( Vec3f( 1.f, 0.f, 1.f ) );

		//Creation du VBO
		glCreateBuffers( 1, &_vbo );
		glNamedBufferData( _vbo, _points.size() * sizeof( Vec2f ), _points.data(), GL_STATIC_DRAW );

		//Création du VBO pour les couleurs
		glCreateBuffers( 1, &_vboColor );
		glNamedBufferData( _vboColor, _colors.size() * sizeof( Vec3f ), _colors.data(), GL_STATIC_DRAW );

		//Création du EBO
		glCreateBuffers( 1, &_elementBuffer );
		glNamedBufferData( _elementBuffer, _indices.size() * sizeof( Vec2f ), _indices.data(), GL_STATIC_DRAW );

		//Creation du VAO
		glCreateVertexArrays( 1, &_vao );
		glEnableVertexArrayAttrib( _vao, 0 );
		glVertexArrayAttribFormat( _vao, 0, 2, GL_FLOAT, GL_FALSE, 0 );
		glEnableVertexArrayAttrib( _vao, 1 );
		glVertexArrayAttribFormat( _vao, 1, 3, GL_FLOAT, GL_FALSE, 0 );

		//Liaison des VBO & du EBO au VAO
		glVertexArrayVertexBuffer( _vao, 0, _vbo, 0, sizeof( Vec2f ) );
		glVertexArrayVertexBuffer( _vao, 1, _vboColor, 0, sizeof( Vec3f ) );
		glVertexArrayAttribBinding( _vao, 0, 0 );
		glVertexArrayAttribBinding( _vao, 1, 1 );
		glVertexArrayElementBuffer( _vao, _elementBuffer );
		

		const std::string vertexShaderStr	= readFile( _shaderFolder + "lw1.vert" );
		const std::string fragmentShaderStr = readFile( _shaderFolder + "lw1.frag" );

		const GLuint vertexShader	= glCreateShader( GL_VERTEX_SHADER );
		const GLuint fragmentShader = glCreateShader( GL_FRAGMENT_SHADER );

		//Passage du type string à *char
		const GLchar * vSrc = vertexShaderStr.c_str();
		const GLchar * fSrc = fragmentShaderStr.c_str();
		//Passage des chaines aux shaders
		glShaderSource( vertexShader, 1, &vSrc, NULL );
		glShaderSource( fragmentShader, 1, &fSrc, NULL );

		// Compile and attach shaders to the program
		glCompileShader( vertexShader );
		glCompileShader( fragmentShader );
		glAttachShader( _program, vertexShader );
		glAttachShader( _program, fragmentShader );

		glLinkProgram( _program );

		// Check if compilation is ok . (Checker du sujet du TP)
		GLint compiled;
		glGetShaderiv( vertexShader, GL_COMPILE_STATUS, &compiled );
		if ( !compiled )
		{
			GLchar log[ 1024 ];
			glGetShaderInfoLog( vertexShader, sizeof( log ), NULL, log );
			glDeleteShader( vertexShader );
			glDeleteShader( fragmentShader );
			std ::cerr << " Error compiling vertex shader : " << log << std ::endl;
			return false;
		}
		glGetShaderiv( fragmentShader, GL_COMPILE_STATUS, &compiled );
		if ( !compiled )
		{
			GLchar log[ 1024 ];
			glGetShaderInfoLog( fragmentShader, sizeof( log ), NULL, log );
			glDeleteShader( vertexShader );
			glDeleteShader( fragmentShader );
			std ::cerr << " Error compiling fragment shader : " << log << std ::endl;
			return false;
		}

		// Check if link is ok . (Checker du sujet du TP)
		GLint linked;
		glGetProgramiv( _program, GL_LINK_STATUS, &linked );
		if ( !linked )
		{
			GLchar log[ 1024 ];
			glGetProgramInfoLog( _program, sizeof( log ), NULL, log );
			std ::cerr << " Error linking program : " << log << std ::endl;
			return false;
		}

		// Suppression des shaders
		glDeleteShader( vertexShader );
		glDeleteShader( fragmentShader );
		std::cout << "Done!" << std::endl;
		return true;
	}

	void LabWork2::animate( const float p_deltaTime ) {}

	void LabWork2::render()
	{
		glClear( GL_COLOR_BUFFER_BIT );
		glUseProgram( _program );
		glBindVertexArray( _vao );
		glDrawElements( GL_TRIANGLES, _indices.size(), GL_UNSIGNED_INT, 0 );
		glBindVertexArray( 0 );
	}

	void LabWork2::handleEvents( const SDL_Event & p_event ) {}

	void LabWork2::displayUI()
	{
		ImGui::Begin( "Settings lab work 2" );
		ImGui::Text( "No setting available!" );
		ImGui::End();
	}

} // namespace M3D_ISICG
