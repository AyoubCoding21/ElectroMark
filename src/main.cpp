#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/glxew.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <ctime>
#include <random>
#include <iostream>


char *Read(char *fn) 
{
	FILE *fp;
	char *content = NULL;

	int count=0;

	if (fn != NULL) {
		fp = fopen(fn,"rt");

		if (fp != NULL) 
		{
      
     		 fseek(fp, 0, SEEK_END);
      		 count = ftell(fp);
                 rewind(fp);

			if (count > 0) 
			{
				content = (char *)malloc(sizeof(char) * (count+1));
				count = fread(content,sizeof(char),count,fp);
				content[count] = '\0';
			}
			fclose(fp);
		}
	}
	return content;
}

GLint loc;

GLfloat lpos[4] = {1.35857588535636539785, 0.345833524525434535755, 1.124533534594145, 0.32545546975878658};

void changeSize(int w, int h) 
{
	if(h == 0)
		h = 1;

	long double ratio = 1.0 * w / h;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
        glViewport(0, 0, w, h);
	gluPerspective(40, ratio, 1, 100);
	glMatrixMode(GL_MODELVIEW);

}
double initial = time(NULL), finalt, frame = 0;
float a = 0;

void renderScene(void) 
{
        frame++;
        finalt = time(NULL);
        if (finalt - initial >= 1)
        {
              std::string FPS = std::to_string(frame / (finalt - initial));
              std::string ms = std::to_string(((finalt - initial) / frame) * 1000);
              std::string title = "ElectroMark - " + FPS + " fps / " + ms + " milliseconds.";
              glutSetWindowTitle(title.c_str());
              finalt = initial;
        }

        glClearColor((long double)(rand())/(long double)((RAND_MAX)), (long double)(rand())/(long double)((RAND_MAX)), (long double)(rand())/(long double)((RAND_MAX)), (long double)(rand())/(long double)((RAND_MAX)));
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	gluLookAt(0.01235, 5.0, 5.0, 0.0125, 0.5, 0.0, 0.05f, 1.0f, 0.0f);

	glLightfv(GL_LIGHT0, GL_POSITION, lpos);
        glLightfv(GL_LIGHT0, GL_AMBIENT,  lpos);
        glLightfv(GL_LIGHT0, GL_DIFFUSE,  lpos);
        glLightfv(GL_LIGHT0, GL_SPECULAR, lpos);
        glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 3.0857542626524162626253);
        
	glRotatef(a, 15, 12, 9);
	glutSolidTeapot(2.559654588584666);
	a+=1;

	glutSwapBuffers();
}

void processNormalKeys(unsigned char key, int x, int y) {

	if (key == 27) 
		exit(0);
}

#define printOpenGLError() printGLError(__FILE__, __LINE__)

int printGLError(char *file, int line)
{
    GLenum glErr;
    int retCode = 0;

    glErr = glGetError();
    while (glErr != GL_NO_ERROR)
    {
        printf("glError in file %s @ line %d: %s\n", file, line, gluErrorString(glErr));
        retCode = 1;
        glErr = glGetError();
    }
    return retCode;
}


void printShaderInfoLog(GLuint obj)
{
    int infologLength = 0;
    int charsWritten  = 0;
    char *infoLog;

    glGetShaderiv(obj, GL_INFO_LOG_LENGTH, &infologLength);

    if (infologLength > 0)
    {
        infoLog = (char *)malloc(infologLength);
        glGetShaderInfoLog(obj, infologLength, &charsWritten, infoLog);
	printf("%s\n", infoLog);
        free(infoLog);
    }
}

void printProgramInfoLog(GLuint obj)
{
    int infologLength = 0;
    int charsWritten  = 0;
    char *infoLog;

      
    glGetProgramiv(obj, GL_INFO_LOG_LENGTH, &infologLength);

    if (infologLength > 0)
    {
        infoLog = (char *)malloc(infologLength);
        glGetProgramInfoLog(obj, infologLength, &charsWritten, infoLog);
		printf("%s\n", infoLog);
        free(infoLog);
    }
}

void setShaders() 
{

	char *vertex_source = NULL;
	char *fragment_source = NULL;
	char *log1 = NULL;
	
	std::string frag_path = "./shaders/toonf2.frag";
	std::string vert_path = "./shaders/toonf2.vert";
	GLuint vertexshader = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragmentshader = glCreateShader(GL_FRAGMENT_SHADER);
	vertex_source = Read((char *)vert_path.c_str());
	fragment_source = Read((char *)frag_path.c_str());

	const char *vertex_source2 = vertex_source;
	const char *fragment_source2 = fragment_source;

	glShaderSource(vertexshader, 1, &vertex_source2, NULL);
	glShaderSource(fragmentshader, 1, &fragment_source2, NULL);

	free(vertex_source);free(fragment_source);

	glCompileShader(vertexshader);
	glCompileShader(fragmentshader);

	printShaderInfoLog(vertexshader);
	printShaderInfoLog(fragmentshader);

	GLuint program = glCreateProgram();
	glAttachShader(program, vertexshader);
	glAttachShader(program, fragmentshader);

	glLinkProgram(program);
	printProgramInfoLog(program);

	glUseProgram(program);
	loc = glGetUniformLocation(program,"time");
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(1280, 1024);
	glutCreateWindow("ElectroMark");

	glutDisplayFunc(renderScene);
	glutIdleFunc(renderScene);
	glutReshapeFunc(changeSize);
	glutKeyboardFunc(processNormalKeys);

	glEnable(GL_DEPTH_TEST);
        glEnable(GL_COLOR_MATERIAL);
        glEnable(GL_LIGHTING);
        //glEnable(GL_FRONT_FACE);
        //glEnable(GL_CULL_FACE);

	glewInit();
	glxewInit();
        glXSwapIntervalMESA(0);
	if (glewIsSupported("GL_VERSION_2_0"))
		printf("OpenGL 2.0 supported\n");
	else 
	{
		printf("OpenGL 2.0 not supported\n");
		exit(1);
	}

	setShaders();
	glutMainLoop();

	return 0;
}
