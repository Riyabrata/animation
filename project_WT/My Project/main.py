import pygame
from pygame.locals import *
from OpenGL.GL import *
from OpenGL.GLU import *
import numpy as np

# Global variables for the wind turbine's rotation
current_angle = 0.0
step_angle = 0.5  # Default rotation step

def read_speed_setting():
    global step_angle
    try:
        with open("speed.txt", "r") as file:
            speed_setting = int(file.read().strip())
            step_angle = 0.5 * speed_setting
    except IOError:
        print("Unable to open speed.txt")

def init():
    glClearColor(0.0, 0.0, 0.0, 0.0)
    glMatrixMode(GL_PROJECTION)
    gluOrtho2D(0.0, 400, 0.0, 300.0)

def draw_turbine():
    global current_angle
    glClear(GL_COLOR_BUFFER_BIT)
    glMatrixMode(GL_MODELVIEW)
    glLoadIdentity()

    # Draw the tower
    glBegin(GL_LINES)
    glColor3f(1.0, 1.0, 1.0)
    glVertex2f(160, 40)
    glVertex2f(163, 180)
    glVertex2f(160, 40)
    glVertex2f(175, 40)
    glVertex2f(175, 40)
    glVertex2f(172, 180)
    glEnd()

    # Rotate object
    glPushMatrix()
    glTranslatef(168, 180, 0)
    glRotatef(current_angle, 0, 0, 1)
    current_angle += step_angle  # Increment the angle for the next frame

    # Draw blades
    glColor3f(1.0, 1.0, 1.0)
    for _ in range(3):
        glBegin(GL_TRIANGLES)
        glVertex2f(5, 0)
        glVertex2f(-5, 0)
        glVertex2f(0, 90)
        glEnd()
        glRotatef(120, 0, 0, 1)  # 120 degrees between each blade

    # Draw circle in the middle of the rotor blades
    glBegin(GL_POLYGON)
    for i in range(360):
        theta = np.radians(i)
        glVertex2f(7 * np.cos(theta), 7 * np.sin(theta))
    glEnd()
    glPopMatrix()
    pygame.display.flip()

def main():
    pygame.init()
    pygame.display.set_mode((700, 600), DOUBLEBUF | OPENGL)
    init()
    pygame.display.set_caption("Wind Turbine")
    clock = pygame.time.Clock()

    pygame.time.set_timer(USEREVENT + 1, 5000)  # Timer event every 5 seconds

    running = True
    while running:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                running = False
            elif event.type == USEREVENT + 1:
                read_speed_setting()
        draw_turbine()
        clock.tick(60)  # Run at 60 frames per second

    pygame.quit()

if __name__ == "__main__":
    main()
