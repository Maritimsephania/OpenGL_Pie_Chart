from OpenGL.GL import *
from OpenGL.GLUT import *
from OpenGL.GLU import *
import math


PI = math.pi
TOTAL = 170
NUM_SLICES = 6
RADIUS = 0.55
LABEL_R = 0.72
SEGMENTS = 120

# Slice Data
# slices = [
#     ("Orange",     41, 0.88, 0.49, 0.23),
#     ("Avocado",    36, 0.20, 0.40, 0.68),
#     ("Mango",      30, 0.56, 0.36, 0.73),
#     ("Kiwi fruit", 28, 0.79, 0.30, 0.49),
#     ("Banana",     19, 0.23, 0.67, 0.43),
#     ("Grapes",     16, 0.30, 0.72, 0.77),
# ]
#slice data with fruit colors.
slices = [
    ("Orange",     41, 1.0, 0.5, 0.00),
    ("Avocado",    36, 0.10, 0.25, 0.10),
    ("Mango",      30, 1.0, 0.8, 0.00),
    ("Kiwi",      28, 0.6, 0.80, 0.2),
    ("Banana",     19, 0.95, 0.95, 0.20),
    ("Grapes",     16, 0.5, 0.00, 0.5),
]

#Draw text
def drawText(x, y, text):
    glRasterPos2f(x, y)
    for ch in text:
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, ord(ch))

def getTextWidth(text):
    width = 0
    for ch in text:
        width += glutBitmapWidth(GLUT_BITMAP_HELVETICA_12, ord(ch))
    return width

#Draw title
def drawTitle():
    glColor3f(0.15, 0.15, 0.15)
    drawText(-0.45,0.90,"Gachororo Youth Fruit Preference Survey")
    drawText(-0.10,0.82,"(n=170)")

#Display
def display():
    glClear(GL_COLOR_BUFFER_BIT)

    drawTitle()

    startAngle = 90.0

    for name, count, r, g, b in slices:
        pct = count / TOTAL
        sweepDeg = pct * 360.0
        endAngle = startAngle - sweepDeg

#Draw Slice
        glColor3f(r, g, b)
        glBegin(GL_TRIANGLE_FAN)
        glVertex2f(0.0, 0.0)

        for s in range(SEGMENTS + 1):
            ang = (startAngle - (sweepDeg * s / SEGMENTS)) * PI / 180.0
            glVertex2f(RADIUS * math.cos(ang), RADIUS * math.sin(ang))

        glEnd()

#Draw Border
        glColor3f(1.0, 1.0, 1.0)
        glLineWidth(1.5)
        glBegin(GL_LINE_LOOP)
        glVertex2f(0.0, 0.0)

        for s in range(SEGMENTS + 1):
            ang = (startAngle - (sweepDeg * s / SEGMENTS)) * PI / 180.0
            glVertex2f(RADIUS * math.cos(ang), RADIUS * math.sin(ang))

        glEnd()

# write Label
        midDeg = startAngle - sweepDeg * 0.5
        midRad = midDeg * PI / 180.0

        lx = LABEL_R * math.cos(midRad)
        ly = LABEL_R * math.sin(midRad)

        label = f"{name}  {pct * 100:.1f}%"

        textWidth = getTextWidth(label)
        scale = 0.0015
        textOffset = textWidth * scale

        if lx > 0:
            tx = lx + 0.03
        else:
            tx = lx - textOffset - 0.03

        ty = ly - 0.01

        glColor3f(0.1, 0.1, 0.1)
        drawText(tx, ty, label)

        startAngle = endAngle

    glutSwapBuffers()

# Reshape
def reshape(w, h):
    side = min(w, h)
    glViewport((w - side)//2, (h - side)//2, side, side)
    

    glMatrixMode(GL_PROJECTION)
    glLoadIdentity()
    gluOrtho2D(-1.2, 1.2, -1.2, 1.2)

    glMatrixMode(GL_MODELVIEW)
    glLoadIdentity()

# Main Function
def main():
    glutInit()
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB)
    glutInitWindowSize(700, 700)
    glutCreateWindow(b"Gachororo Fruit Preference Pie Chart")

    glClearColor(1.0, 1.0, 1.0, 1.0)  # For Yellow background

    glutDisplayFunc(display)
    glutReshapeFunc(reshape)

    glutMainLoop()

main()