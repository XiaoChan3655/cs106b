#include "Plotter.h"
#include "strlib.h"
using namespace std;




void runPlotterScript(istream& input) {
    /* TODO: Delete this line and the one after it, then implement this function. */
    int state = 0;  //penUp
    double cordiX = 0;
    double cordiY = 0;
    PenStyle style = { 1, "black" };

    for (string line; getline(input, line);) {
        Vector<string> result = stringSplit(line, ' ');
        if (result.size() == 1) {
            if (toLowerCase(result[0]) == "pendown") {
                state = 1;
            } else {
                state = 0;
            }
        } else if (result.size() == 2) {
            if (toLowerCase(result[0]) == "pencolor") {
                style = { style.width, result[1] };
            } else {
                style = { stringToReal(result[1]), style.color };
            }
        } else if (result.size() == 3) {
            double r1 = stringToReal(result[1]);
            double r2 = stringToReal(result[2]);
            if (toLowerCase(result[0]) == "moverel") {
                if (state == 1) {
                    drawLine(cordiX, cordiY, cordiX + r1, cordiY + r2, style);
                }
                cordiX += r1;
                cordiY += r2;
            } else {
                if (state == 1) {
                    drawLine(cordiX, cordiY, r1, r2, style);
                }
                cordiX = r1;
                cordiY = r2;
            }
        }
    }
}
