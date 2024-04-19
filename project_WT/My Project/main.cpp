// are defined for the project My Project here. paths are relative to the project directory. Can be found in tasks.json (version 2.0.0).
#include <GL/glut.h>
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

// Global variables for the wind turbine's rotation
float current_angle = 0.0f;
float step_angle = 0.5f;  // Default rotation step

void init() {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0, 400, 0.0, 300.0);
}

void readSpeedSetting() {
    std::ifstream speedFile("speed.txt");
    if (speedFile.is_open()) {
        int speedSetting;
        speedFile >> speedSetting;
        // Map the speed setting (1 to 10) to a step angle between 0.5 and 5
        step_angle = 0.5f * speedSetting;
        speedFile.close();
    } else {
        std::cerr << "Unable to open speed.txt" << std::endl;
    }
}

void timer(int value) {
    readSpeedSetting();
    glutTimerFunc(5000, timer, 0);  // Reread the speed every 5 seconds
}

void drawTurbine() {
    // Draw the tower
    glBegin(GL_LINES);
    glColor3f(1.0, 1.0, 1.0);
    glVertex2f(160, 40);
    glVertex2f(163, 180);
    glVertex2f(160, 40);
    glVertex2f(175, 40);
    glVertex2f(175, 40);
    glVertex2f(172, 180);
    glEnd();

    // Rotate object
    glPushMatrix();
    glTranslatef(168, 180, 0.0f);
    glRotatef(current_angle, 0, 0, 1);
    current_angle += step_angle; // Increment the angle for the next frame

    // Draw first rotor blade
    glBegin(GL_TRIANGLES);
    glColor3f(1.0, 1.0, 1.0);
    glVertex2f(5, 0);
    glVertex2f(-5, 0);
    glVertex2f(0, 90);
    glEnd();

    // Draw second rotor blade
    glRotatef(120, 0, 0, 1); // 120 degrees between each blade
    glBegin(GL_TRIANGLES);
    glColor3f(1.0, 1.0, 1.0);
    glVertex2f(5, 0);
    glVertex2f(-5, 0);
    glVertex2f(0, 90);
    glEnd();

    // Draw third rotor blade
    glRotatef(120, 0, 0, 1); // Another 120 degrees for the third blade
    glBegin(GL_TRIANGLES);
    glColor3f(1.0, 1.0, 1.0);
    glVertex2f(5, 0);
    glVertex2f(-5, 0);
    glVertex2f(0, 90);
    glEnd();

    // Draw circle in the middle of the rotor blades
    float theta;
    glBegin(GL_POLYGON);
    glColor3f(1.0, 1.0, 1.0);
    for (int i = 0; i < 360; i++) {
        theta = i * 3.1415926 / 180;
        glVertex2f(7 * cos(theta), 7 * sin(theta));
    }
    glEnd();
    glPopMatrix();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    drawTurbine();
    glFlush();
    glutSwapBuffers();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(700, 600);
    glutInitWindowPosition(10, 10);
    glutCreateWindow("Wind Turbine");
    init();
    glutDisplayFunc(display);
    glutTimerFunc(0, timer, 0);  // Start the timer for the first time
    glutMainLoop();
    return 0;
}
