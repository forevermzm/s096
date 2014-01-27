#include <glload/gl_3_0.h>
#include <glload/gll.hpp>
#include <GL/freeglut.h>

#include <algorithm>
#include <vector>
#include <string>
#include <iostream>
#include <cstdint>

constexpr char ESCAPE_KEY = 27;

void DebugFunc( GLenum source, GLenum type, 
                GLuint /*id*/, GLenum severity, GLsizei /*length*/,
                const GLchar* message, GLvoid* /*userParam*/ ) {
  std::string srcName, errorType, typeSeverity;

  switch( source ) {
    case             GL_DEBUG_SOURCE_API_ARB: srcName = "API"; break;
    case   GL_DEBUG_SOURCE_WINDOW_SYSTEM_ARB: srcName = "Window System"; break;
    case GL_DEBUG_SOURCE_SHADER_COMPILER_ARB: srcName = "Shader Compiler"; break;
    case     GL_DEBUG_SOURCE_THIRD_PARTY_ARB: srcName = "Third Party"; break;
    case     GL_DEBUG_SOURCE_APPLICATION_ARB: srcName = "Application"; break;
    case           GL_DEBUG_SOURCE_OTHER_ARB: srcName = "Other"; break;
  }

  switch( type ) {
    case               GL_DEBUG_TYPE_ERROR_ARB: errorType = "Error"; break;
    case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR_ARB: errorType = "Deprecated Functionality"; break;
    case  GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR_ARB: errorType = "Undefined Behavior"; break;
    case         GL_DEBUG_TYPE_PORTABILITY_ARB: errorType = "Portability"; break;
    case         GL_DEBUG_TYPE_PERFORMANCE_ARB: errorType = "Performance"; break;
    case               GL_DEBUG_TYPE_OTHER_ARB: errorType = "Other"; break;
  }

  switch( severity ) {
    case   GL_DEBUG_SEVERITY_HIGH_ARB: typeSeverity = "High"; break;
    case GL_DEBUG_SEVERITY_MEDIUM_ARB: typeSeverity = "Medium"; break;
    case    GL_DEBUG_SEVERITY_LOW_ARB: typeSeverity = "Low"; break;
  }

  std::cout << errorType << " from " << srcName << ",\t" << typeSeverity;
  std::cout << " priority\nMessage: " << message << "\n";
}


GLuint CreateShader( GLenum eShaderType, const std::string &strShaderFile ) {
  GLuint shader = glCreateShader( eShaderType );
  const char *strFileData = strShaderFile.c_str();
  glShaderSource( shader, 1, &strFileData, nullptr );
  glCompileShader( shader );

  GLint status;
  glGetShaderiv( shader, GL_COMPILE_STATUS, &status );

  if (status == GL_FALSE) {
    GLint infoLogLength;
    glGetShaderiv( shader, GL_INFO_LOG_LENGTH, &infoLogLength );

    GLchar *strInfoLog = new GLchar[infoLogLength + 1];
    glGetShaderInfoLog( shader, infoLogLength, nullptr, strInfoLog );

    std::string shaderType;

    switch(eShaderType) {
      case   GL_VERTEX_SHADER: shaderType = "vertex"; break;
//      case GL_GEOMETRY_SHADER: shaderType = "geometry"; break;
      case GL_FRAGMENT_SHADER: shaderType = "fragment"; break;
    }

    std::cerr << "Compile failure in " << shaderType << ":\n";
    std::cerr << strInfoLog << "\n";
    delete [] strInfoLog;
  }

  return shader;
}

GLuint CreateProgram( const std::vector<GLuint> &shaderList ) {
  GLuint program = glCreateProgram();

  for( auto shader : shaderList ) {
    glAttachShader( program, shader );
  }

  glLinkProgram( program );

  GLint status;
  glGetProgramiv( program, GL_LINK_STATUS, &status );

  if( status == GL_FALSE ) {
    GLint infoLogLength;
    glGetProgramiv( program, GL_INFO_LOG_LENGTH, &infoLogLength );

    GLchar *strInfoLog = new GLchar[infoLogLength + 1];
    glGetProgramInfoLog( program, infoLogLength, nullptr, strInfoLog );
    std::cerr << "Linker failure: " << strInfoLog << "\n";
    delete[] strInfoLog;
  }

  for( auto shader : shaderList ) {
    glDetachShader( program, shader );
  }

  return program;
}

GLuint theProgram;

const std::string strVertexShader(
  "#version 130\n"
  "in vec4 position;\n"
  "void main()\n"
  "{\n"
  "   gl_Position = position;\n"
  "}\n"
);

const std::string strFragmentShader(
  "#version 130\n"
  "out vec4 outputColor;\n"
  "void main()\n"
  "{\n"
  "   float lerpValue = gl_FragCoord.y / 500.0f;"
  "   outputColor = mix( vec4(1.0f, 0.5f, 1.0f, 1.0f),\n"
  "         vec4(0.2f, 0.2f, 0.2f, 1.0f), lerpValue );\n"
  "}\n"
);

void InitializeProgram() {
  std::vector<GLuint> shaderList;

  shaderList.push_back( CreateShader( GL_VERTEX_SHADER, strVertexShader ) );
  shaderList.push_back( CreateShader( GL_FRAGMENT_SHADER, strFragmentShader ) );

  theProgram = CreateProgram( shaderList );

  std::for_each( std::begin( shaderList ), std::end( shaderList ), glDeleteShader );
}

const float vertexPositions[] = { 0.75f,  0.75f, 0.0f, 1.0f,
                                  0.75f, -0.75f, 0.0f, 1.0f,
                                 -0.75f, -0.75f, 0.0f, 1.0f  };

GLuint positionBufferObject;
GLuint vao;

void InitializeVertexBuffer() {
  glGenBuffers( 1, &positionBufferObject );

  glBindBuffer( GL_ARRAY_BUFFER, positionBufferObject );
  glBufferData( GL_ARRAY_BUFFER, sizeof( vertexPositions ), vertexPositions, GL_STATIC_DRAW );
  glBindBuffer( GL_ARRAY_BUFFER, 0 );
}

void init() {
  InitializeProgram();
  InitializeVertexBuffer();
  glGenVertexArrays( 1, &vao );
  glBindVertexArray( vao );
}

// Called upon any key press
void keyboard( unsigned char key, int x, int y ) {
  x = x + y;
  if( key == ESCAPE_KEY ) {
    glutLeaveMainLoop();
  }
}

void reshape( int width, int height ) {
  glViewport( 0, 0, (GLsizei) width, (GLsizei) height );
}

static int theCount = 0;

void display() {
  glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
  glClear( GL_COLOR_BUFFER_BIT );
  ++theCount;

  glUseProgram( theProgram );
  glBindBuffer( GL_ARRAY_BUFFER, positionBufferObject );
  glEnableVertexAttribArray( 0 );
  glVertexAttribPointer( 0, 4, GL_FLOAT, GL_FALSE, 0, 0 );

  glDrawArrays( GL_TRIANGLES, 0, 3 );

  glDisableVertexAttribArray( 0 );
  glUseProgram( 0 );

  glutSwapBuffers();
}


int main( int argc, char **argv ) {
  glutInit( &argc, argv );
  uint32_t displayMode = GLUT_DOUBLE | GLUT_ALPHA | GLUT_DEPTH | GLUT_STENCIL;
  // displayMode = defaults...

  glutInitDisplayMode( displayMode );
  glutInitContextVersion( 3, 0 );
  glutInitContextProfile( GLUT_CORE_PROFILE );
  glutInitContextFlags( GLUT_DEBUG );

  int width = 500, height = 500;
  glutInitWindowSize( width, height );
  int window = glutCreateWindow( argv[0] );

  glload::LoadFunctions();

  glutSetOption( GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION );

  if( !glload::IsVersionGEQ( 3, 0 ) ) {
    std::cout << "You have OpenGL " << glload::GetMajorVersion();
    std::cout << "." << glload::GetMinorVersion() << " but this needs 3.0.\n";
    glutDestroyWindow( window );
  }

  if( glext_ARB_debug_output ) {
    glEnable( GL_DEBUG_OUTPUT_SYNCHRONOUS_ARB );
    glDebugMessageCallbackARB( DebugFunc, (void*) 15 );
  }

  init();

  glutDisplayFunc( display );
  glutReshapeFunc( reshape );
  glutKeyboardFunc( keyboard );
  glutMainLoop();
  return 0;
}
