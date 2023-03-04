#include <stdio.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "math_3d.h"

GLuint VBO; //назначение GLuint в качестве глобальной переменной для хранения указателя на буфер вершин

static void RenderSceneCB()
{
    glClear(GL_COLOR_BUFFER_BIT); //очистка буфера кадра

    glEnableVertexAttribArray(0); //включаем инжексацию атрибутов каждой вершины, задаем индекс 0
    glBindBuffer(GL_ARRAY_BUFFER, VBO); //задаемм буфферу хранение вершин 
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0); // указываем, как воспринимать данные внутри буфера:индекс атрибута, количество компонентов, тип данных, нормализация, байтовый шаг между атрибутами, смещение в структуре

    glDrawArrays(GL_TRIANGLES, 0, 3); //вызываем функцию отрисовки треугольника, отризовка с 0 вершины, всего 3 вершины

    glDisableVertexAttribArray(0); //отключаем каждый атрибут вершины 

    glutSwapBuffers(); //замена фонового буфера и буфера кадра местами
}


static void InitializeGlutCallbacks()
{
    glutDisplayFunc(RenderSceneCB); //отрисовка окна(1кадр)
}

static void CreateVertexBuffer()
{
    Vector3f Vertices[3]; //создаем массив точек треугольника и заносим координаты
    Vertices[0] = Vector3f(-1.0f, -1.0f, 0.0f);
    Vertices[1] = Vector3f(1.0f, -1.0f, 0.0f);
    Vertices[2] = Vector3f(0.0f, 1.0f, 0.0f);

    glGenBuffers(1, &VBO); //функция для генерации объектов переменных типов, первый определяет количество объектов, и второй ссылка на массив типа GLuints для хранения указателя, по которому будут храниться данные
    glBindBuffer(GL_ARRAY_BUFFER, VBO); //задаемм буфферу хранение вершин 
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW); //обозначаем буффер хранения вершин, размер данных в байтах, адрес массива вершин, и флаг обозначающий, будем ли мы изменять значения буффера
}


int main(int argc, char** argv)
{
    glutInit(&argc, argv); //инициализируем GLUT
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); //GLUT_DOUBLE включает двойную буферизацию и буфер цвета, непрерывно используемого для конечной цели рендеринга
    glutInitWindowSize(1020, 768); //размер окна в пикселях 1020х768
    glutInitWindowPosition(400, 100); //расположение окна на экране
    glutCreateWindow("IKG_LAB_1"); //название окна

    InitializeGlutCallbacks();

    GLenum res = glewInit(); //инициализация GLEW и проверка на ошибки
    if (res != GLEW_OK) {
        fprintf(stderr, "Error: '%s'\n", glewGetErrorString(res));
        return 1;
    }

    glClearColor(0.1f, 0.0f, 0.3f, 0.0f); //цвет фона 

    CreateVertexBuffer();

    glutMainLoop(); //передача управления GLUT для выполнения собственного цикла

    return 0;
}
