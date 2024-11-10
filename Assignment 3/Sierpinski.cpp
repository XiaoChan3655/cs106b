#include "Sierpinski.h"
#include "error.h"
using namespace std;

/**
 * Draws a triangle with the specified corners in the specified window. Feel free
 * to edit this function as you see fit to change things like color, fill style,
 * etc. in whatever way you'd like!
 *
 * @param window The window in which to draw the triangle.
 * @param x0 y0 The first corner of the triangle.
 * @param x1 y1 The second corner of the triangle.
 * @param x2 y2 The third corner of the triangle.
 */
void drawTriangle(GWindow& window,
                  double x0, double y0,
                  double x1, double y1,
                  double x2, double y2) {
    window.setColor("black");
    window.fillPolygon({ x0, y0, x1, y1, x2, y2 });
}

/* TODO: Refer to Sierpinski.h for more information about what this function should do.
 * Then, delete this comment.
 */
void drawSierpinskiTriangle(GWindow& window,
                            double x0, double y0,
                            double x1, double y1,
                            double x2, double y2,
                            int order) {
    if (order < 0) {
        error("order should be not less than zero");
    } else if (order == 0) {
        drawTriangle(window, x0, y0, x1, y1, x2, y2);
    } else {
        double mx0 = (x0 + x1) / 2;
        double mx1 = (x0 + x2) / 2;
        double mx2 = (x1 + x2) / 2;
        double my0 = (y0 + y1) / 2;
        double my1 = (y0 + y2) / 2;
        double my2 = (y1 + y2) / 2;
        order = order - 1;
        drawSierpinskiTriangle(window, x0, y0, mx0, my0, mx1, my1, order);
        drawSierpinskiTriangle(window, mx0, my0, x1, y1, mx2, my2, order);
        drawSierpinskiTriangle(window, mx1, my1, mx2, my2, x2, y2, order);
    }
}
