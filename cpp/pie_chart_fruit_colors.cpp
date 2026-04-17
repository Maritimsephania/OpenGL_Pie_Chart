//Group 9
//Members:
//1. sct211 - 0245 / 2023 Kipkoech Sephania
//2. sct211 - 0014 / 2023 Ali Abdirahaman




#include <GL/glut.h>
#include <cmath>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>

#define PI 3.14159265358979323846
#define NUM_SLICES 6
#define RADIUS     0.55f
#define LABEL_RADIUS    0.65f   /* Distance of labels from center */
#define SEGMENTS   150     /* smoothness of each arc  */

/* Store survey data  */
struct Slice {
    std::string name;
    int         count;
    float       r, g, b;   /* slice colour */
};



/* Draw a string at (x, y) */
void drawText(float x, float y, const std::string& text)
{
    glRasterPos2f(x, y);
    for (char c : text) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
    }
}


class PieChart {
private:
    std::vector <Slice> slices;

    float getTotal() const {
        float total = 0.0f;
        for (const auto& slice : slices) {
            total += slice.count;
        }
        return total;
    }

public:
    PieChart(const std::vector<Slice>& data) : slices(data) {}

    void drawTitle() {
        glColor3f(0.1f, 0.1f, 0.1f);
        drawText(-0.45f, 0.90f, "Gachororo Youth Fruit Preference Survey");
        drawText(-0.10f, 0.82f, "(n = " + std::to_string((int)getTotal()) + ")");
    }
    void draw() {
        drawTitle();

        float total = getTotal();
        float startAngle = 90.0f;

        for (const auto& s : slices) {

            float slicePercentage = s.count / total;
            float angleWidth = slicePercentage * 360.0f;
            float endAngle = startAngle - angleWidth;

            /* Draw sector */
            glColor3f(s.r, s.g, s.b);
            glBegin(GL_TRIANGLE_FAN);
            glVertex2f(0.0f, 0.0f);

            for (int i = 0; i <= SEGMENTS; i++) {
                float stepAngle = (startAngle - (angleWidth * i / SEGMENTS)) * PI / 180.0f;
                glVertex2f(RADIUS * cos(stepAngle), RADIUS * sin(stepAngle));
            }
            glEnd();

            /*Draw sector border*/
            glColor3f(1.0f, 1.0f, 1.0f);
            glLineWidth(1.5f);
            glBegin(GL_LINE_LOOP);
            glVertex2f(0.0f, 0.0f);

            for (int i = 0; i <= SEGMENTS; i++) {
                float ang = (startAngle - (angleWidth * i / SEGMENTS)) * PI / 180.0f;
                glVertex2f(RADIUS * cos(ang), RADIUS * sin(ang));
            }
            glEnd();

            //Add Label
            float midDeg = startAngle - angleWidth * 0.5f;
            float midRad = midDeg * PI / 180.0f;

            float lx = LABEL_RADIUS * cos(midRad);
            float ly = LABEL_RADIUS * sin(midRad);

            std::ostringstream ss;
            ss << s.name << " "
                << std::fixed << std::setprecision(1)
                << (slicePercentage * 100) << "%";

            std::string label = ss.str();

            float tx = lx + (lx > 0 ? 0.03f : -0.15f);
            float ty = ly - 0.01f;

            glColor3f(0.1f, 0.1f, 0.1f);
            drawText(tx, ty, label);

            startAngle = endAngle;
        }
    }




};


//Create chart object 
PieChart chart({
    {"Orange",  41, 1.0, 0.5, 0.00},
    {"Avocado", 36, 0.10, 0.25, 0.10},
    {"Mango",   30, 1.0, 0.8, 0.00},
    {"Kiwi",    28, 0.6, 0.80, 0.2},
    {"Banana",  19, 0.95, 0.95, 0.20},
    {"Grapes",  16, 0.5, 0.00, 0.5}, });

// Display
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    chart.draw();

    glutSwapBuffers();
}


// Resize
void reshape(int w, int h)
{
    int side = (w < h) ? w : h;
    glViewport((w - side) / 2, (h - side) / 2, side, side);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.2, 1.2, -1.2, 1.2);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

// Main 
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(700, 700);
    glutCreateWindow("Gachororo Fruit Prefence Pie Chart");

    glClearColor(0.8f, 0.1f, 0.2f, 1.0f);

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

    glutMainLoop();
    return 0;
}

