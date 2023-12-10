#include "ShaderProgram.h"
#include <iostream>

namespace Renderer {
	ShaderProgram::ShaderProgram(const std::string& vertexShader, const std::string& fragmentShader) {
		GLuint vs = 0;
		if (!createShader(vertexShader, GL_VERTEX_SHADER, vs)) {
			std::cerr << "VERTEX::SHADER::COMPILE-TIME_ERROR" << std::endl;
			glDeleteShader(vs);
			return;
		}

		GLuint fs = 0;
		if (!createShader(fragmentShader, GL_FRAGMENT_SHADER, fs)) {
			std::cerr << "FRAGMENT::SHADER::COMPILE-TIME_ERROR" << std::endl;
			glDeleteShader(fs);
			return;
		}

		m_ID = glCreateProgram();
		glAttachShader(m_ID, vs);
		glAttachShader(m_ID, fs);
		glLinkProgram(m_ID);

		GLint success;
		glGetProgramiv(m_ID, GL_LINK_STATUS, &success);
		if (!success)
		{
			GLchar infoLog[1024];
			glGetShaderInfoLog(m_ID, 1024, nullptr, infoLog);
			std::cerr << "ERROR::SHADER: Link-time error:\n" << infoLog << std::endl;
		}
		else {
			m_isCompiled = true;
		}

		glDeleteShader(vs);
		glDeleteShader(fs);
	}

	bool ShaderProgram::createShader(const std::string& source, const GLenum shaderType, GLuint& shaderID) {
		shaderID = glCreateShader(shaderType);
		const char* code = source.c_str();
		glShaderSource(shaderID, 1, &code, nullptr);
		glCompileShader(shaderID);

		//Проверка компиляции
		GLint  success;
		glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			GLchar infoLog[1024];
			glGetShaderInfoLog(shaderID, 1024, nullptr, infoLog);
			std::cerr << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
			return false;
		}
		return true;
	}

	ShaderProgram::~ShaderProgram() {
		glDeleteProgram(m_ID);
	}

	void ShaderProgram::use() const {
		glUseProgram(m_ID);
	}

	ShaderProgram& ShaderProgram::operator=(ShaderProgram&& shaderProgram) noexcept {
		glDeleteProgram(m_ID);
		m_ID = shaderProgram.m_ID;
		m_isCompiled = shaderProgram.m_isCompiled;
		
		shaderProgram.m_ID = 0;
		shaderProgram.m_isCompiled = false;
		return *this;
	}

	ShaderProgram::ShaderProgram(ShaderProgram&& shaderProgram) noexcept {
		m_ID = shaderProgram.m_ID;
		m_isCompiled = shaderProgram.m_isCompiled;

		shaderProgram.m_ID = 0;
		shaderProgram.m_isCompiled = false;
	}
}