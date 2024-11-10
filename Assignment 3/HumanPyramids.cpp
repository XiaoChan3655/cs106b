#include "HumanPyramids.h"
#include "error.h"
#include "map.h"
using namespace std;

/* TODO: Refer to HumanPyramids.h for more information about what this function should do.
 * Then, delete this comment.
 */


double weightOnBackOfWrapper(int row, int col, int pyramidHeight, Map<string, double>& weightLib) {
    string prev0;
    string prev1;
    string cur = to_string(row) + to_string(col);
    double result;
    if (row < 0 || col < 0 || col > row) {
        error("out of bounds");
    } else if (row >= pyramidHeight) {
        error("row doesn't exits in a pyramid with the height of pyramidHeight ");
    } else if (row == 0 && col == 0) {
        result = 0;
    } else if (row != 0 && col == 0) {
        prev0 = to_string(row - 1) + to_string(col);
        if (weightLib.containsKey(prev0)) {
            result = 80 + weightLib.get(prev0) / 2;
        } else {
            result = 80 + weightOnBackOfWrapper(row - 1, col, pyramidHeight, weightLib) / 2;
        }
    } else if (row == col) {
        prev0 = to_string(row - 1) + to_string(col - 1);
        if (weightLib.containsKey(prev0)) {
            result = 80 + weightLib.get(prev0) / 2;
        } else {
            result = 80 + weightOnBackOfWrapper(row - 1, col - 1, pyramidHeight, weightLib) / 2;
        }
    } else {
        prev0 = to_string(row - 1) + to_string(col - 1);
        prev1 = to_string(row - 1) + to_string(col);
        //std::cout << weightLib << std::endl;
        if (!weightLib.containsKey(prev0) && !weightLib.containsKey(prev1)) {
            result = 160 + weightOnBackOfWrapper(row - 1, col - 1, pyramidHeight, weightLib) / 2
                     + weightOnBackOfWrapper(row - 1, col, pyramidHeight, weightLib) / 2;
        } else if (weightLib.containsKey(prev0) && !weightLib.containsKey(prev1)) {
            result = 160 + weightLib.get(prev0) / 2 + weightOnBackOfWrapper(row - 1, col, pyramidHeight, weightLib) / 2;
        } else if (!weightLib.containsKey(prev0) && weightLib.containsKey(prev1)) {
            result = 160 + weightOnBackOfWrapper(row - 1, col - 1, pyramidHeight, weightLib) / 2 + weightLib.get(prev1) / 2;
        } else {
            result = 160 + weightLib.get(prev0) / 2 + weightLib.get(prev1) / 2;
        }
    }
    weightLib.put(cur, result);
    return result;
}

double weightOnBackOf(int row, int col, int pyramidHeight) {
    Map<string, double> weightLib;
    return weightOnBackOfWrapper(row, col, pyramidHeight, weightLib);
}






/* * * * * * Test Cases * * * * * */
#include "GUI/SimpleTest.h"

STUDENT_TEST ("ERROR TEST") {
    EXPECT_ERROR(weightOnBackOf(-1, 0, 3));
    EXPECT_ERROR(weightOnBackOf(3, 3, 3));
}

STUDENT_TEST("Check Person H from the handout.") {
    std::cout << weightOnBackOf(4, 2, 5) << endl;
    EXPECT_EQUAL(weightOnBackOf(4, 2, 5), 500);
}

STUDENT_TEST("Check Person E from the handout.") {
    std::cout << weightOnBackOf(4, 2, 5) << endl;
    EXPECT_EQUAL(weightOnBackOf(3, 1, 5), 340);
}













/* * * * * * Test cases from the starter files below this point. * * * * * */

PROVIDED_TEST("Check Person E from the handout.") {
    /* Person E is located at row 2, column 1. */
    EXPECT_EQUAL(weightOnBackOf(2, 1, 5), 240);
}

PROVIDED_TEST("Function reports errors in invalid cases.") {
    EXPECT_ERROR(weightOnBackOf(-1, 0, 10));
    EXPECT_ERROR(weightOnBackOf(10, 10, 5));
    EXPECT_ERROR(weightOnBackOf(-1, 10, 20));
}

PROVIDED_TEST("Stress test: Memoization is implemented (should take under a second)") {
    /* TODO: Yes, we are asking you to make a change to this test case! Delete the
     * line immediately after this one - the one that starts with SHOW_ERROR - once
     * you have implemented memoization to test whether it works correctly.
     */
    //SHOW_ERROR("This test is configured to always fail until you delete this line from\n         HumanPyramids.cpp. Once you have implemented memoization and want\n         to check whether it works correctly, remove the indicated line.");

    /* Do not delete anything below this point. :-) */

    /* This will take a LONG time to complete if memoization isn't implemented.
     * We're talking "heat death of the universe" amounts of time. :-)
     *
     * If you did implement memoization but this test case is still hanging, make
     * sure that in your recursive function (not the wrapper) that your recursive
     * calls are to your new recursive function and not back to the wrapper. If you
     * call the wrapper again, you'll get a fresh new memoization table rather than
     * preserving the one you're building up in your recursive exploration, and the
     * effect will be as if you hadn't implemented memoization at all.
     */
    EXPECT(weightOnBackOf(100, 50, 200) >= 10000);
}

/* TODO: Add your own tests here. You know the drill - look for edge cases, think about
 * very small and very large cases, etc.
 */
