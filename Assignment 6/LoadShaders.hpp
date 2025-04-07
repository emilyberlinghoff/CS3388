#ifndef LOAD_SHADERS_HPP
#define LOAD_SHADERS_HPP

GLuint LoadShaders(const char* vertex_file_path,
                   const char* fragment_file_path,
                   const char* tessControl_file_path,
                   const char* tessEval_file_path,
                   const char* geometry_file_path);

#endif
