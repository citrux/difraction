// main.c

#include <GL/glew.h>
#include <GL/glut.h>
#include <SOIL/SOIL.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* readFile(const char* fileName);
GLuint createShader(const char* fileName);

int main(int argc, char** argv) {
    char* baseName;
    if (argc == 2)
        baseName = argv[1];
    else
        baseName = "square";

    int width = 800;
    int height = 800;
    GLuint fbo, tex;

    // Нужно для инициализации контекста
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB);
    glutInitWindowSize(width, height);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("difraction");
    glewInit();

    // компиляция и линковка шейдера
    char* shaderName = (char*) calloc(sizeof(char), strlen(baseName) +
                                                    strlen(".glsl") + 1);
    sprintf(shaderName, "%s.glsl", baseName);
    GLuint shader = createShader(shaderName);

    glUseProgram(shader);

    // рисуем квадрат на всё окно
    // именно его текстуру будет рисовать шейдер
    glBegin(GL_POLYGON);
    glTexCoord2f(1, 0);
    glVertex2f(1, -1);
    glTexCoord2f(1, 1);
    glVertex2f(1, 1);
    glTexCoord2f(0, 1);
    glVertex2f(-1, 1);
    glTexCoord2f(0, 0);
    glVertex2f(-1, -1);
    glEnd();

    GLubyte* img =(GLubyte*) calloc(sizeof(GLubyte), 3 * width * height);
    glReadPixels(0, 0, width, height, GL_BGR, GL_UNSIGNED_BYTE, img);

    char* imageName = (char*) calloc(sizeof(char), strlen(baseName) +
                                                   strlen(".bmp") + 1);
    sprintf(imageName, "%s.bmp", baseName);
    int save_result = SOIL_save_image(imageName, SOIL_SAVE_TYPE_BMP,
                                      width, height, 3*sizeof(GLubyte), img);
}

GLuint createShader(const char* fileName) {
    GLuint program = glCreateProgram();
    GLuint shader = glCreateShader(GL_FRAGMENT_SHADER);
    const char* buffer = readFile(fileName);
    glShaderSource(shader, 1, &buffer, 0);
    glCompileShader(shader);
    glAttachShader(program, shader);
    glLinkProgram(program);
    return program;
}

char * readFile(const char* fileName) {
    FILE* fp;
    long lSize;
    char* buffer;

    fp = fopen (fileName, "r");
    if(!fp) {
        perror(fileName);
        exit(1);
    }

    fseek(fp, 0L, SEEK_END);
    lSize = ftell(fp);
    rewind(fp);

    /* выделяем память для текста + 1 для нулевого байта в конце */
    buffer = calloc(sizeof(char), lSize+1);
    if(!buffer) {
        fclose(fp);
        fputs("memory alloc fails", stderr);
        exit(1);
    }

    /* копируем содержимое файла в буфер */
    if(1!=fread(buffer, lSize, 1, fp)) {
      fclose(fp);
      free(buffer);
      fputs("entire read fails", stderr);
      exit(1);
    }

    fclose(fp);
    return buffer;
}
