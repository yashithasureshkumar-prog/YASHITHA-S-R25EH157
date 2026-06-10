#include <stdio.h>
#include <stdlib.h>
#include "shapes.h"

// Internal helper function to plot a pixel if it is within bounds
static void plot_point(char canvas[HEIGHT][WIDTH], int x, int y) {
    if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT) {
        canvas[y][x] = '*';
    }
}

// Fills the entire canvas with the background character '_'
void init_canvas(char canvas[HEIGHT][WIDTH]) {
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            canvas[y][x] = '_';
        }
    }
}

// Draws a line using Bresenham's Line Algorithm
void draw_line(char canvas[HEIGHT][WIDTH], int x1, int y1, int x2, int y2) {
    int dx = abs(x2 - x1);
    int sx = x1 < x2 ? 1 : -1;
    int dy = -abs(y2 - y1);
    int sy = y1 < y2 ? 1 : -1;
    int err = dx + dy;
    int e2;

    while (1) {
        plot_point(canvas, x1, y1);
        if (x1 == x2 && y1 == y2) {
            break;
        }
        e2 = 2 * err;
        if (e2 >= dy) {
            err += dy;
            x1 += sx;
        }
        if (e2 <= dx) {
            err += dx;
            y1 += sy;
        }
    }
}

// Draws a circle using Bresenham's Midpoint Circle Algorithm
void draw_circle(char canvas[HEIGHT][WIDTH], int cx, int cy, int radius) {
    if (radius < 0) {
        return;
    }
    int x = 0;
    int y = radius;
    int d = 3 - 2 * radius;

    while (y >= x) {
        plot_point(canvas, cx + x, cy + y);
        plot_point(canvas, cx - x, cy + y);
        plot_point(canvas, cx + x, cy - y);
        plot_point(canvas, cx - x, cy - y);
        plot_point(canvas, cx + y, cy + x);
        plot_point(canvas, cx - y, cy + x);
        plot_point(canvas, cx + y, cy - x);
        plot_point(canvas, cx - y, cy - x);

        if (d < 0) {
            d = d + 4 * x + 6;
        } else {
            d = d + 4 * (x - y) + 10;
            y--;
        }
        x++;
    }
}

// Draws the outline of a rectangle
void draw_rect(char canvas[HEIGHT][WIDTH], int x, int y, int w, int h) {
    if (w <= 0 || h <= 0) {
        return;
    }
    int x2 = x + w - 1;
    int y2 = y + h - 1;

    // Draw horizontal lines (top and bottom)
    for (int i = x; i <= x2; i++) {
        plot_point(canvas, i, y);
        plot_point(canvas, i, y2);
    }
    // Draw vertical lines (left and right)
    for (int j = y; j <= y2; j++) {
        plot_point(canvas, x, j);
        plot_point(canvas, x2, j);
    }
}

// Draws a triangle outline by drawing lines between vertices
void draw_triangle(char canvas[HEIGHT][WIDTH], int x1, int y1, int x2, int y2, int x3, int y3) {
    draw_line(canvas, x1, y1, x2, y2);
    draw_line(canvas, x2, y2, x3, y3);
    draw_line(canvas, x3, y3, x1, y1);
}

// Clears the canvas and renders all stored shapes
void render_canvas(Shape shapes[], int count, char canvas[HEIGHT][WIDTH]) {
    init_canvas(canvas);
    for (int i = 0; i < count; i++) {
        switch (shapes[i].type) {
            case SHAPE_LINE:
                draw_line(canvas, shapes[i].data.line.x1, shapes[i].data.line.y1,
                                  shapes[i].data.line.x2, shapes[i].data.line.y2);
                break;
            case SHAPE_RECTANGLE:
                draw_rect(canvas, shapes[i].data.rect.x, shapes[i].data.rect.y,
                                  shapes[i].data.rect.width, shapes[i].data.rect.height);
                break;
            case SHAPE_CIRCLE:
                draw_circle(canvas, shapes[i].data.circle.cx, shapes[i].data.circle.cy,
                                    shapes[i].data.circle.radius);
                break;
            case SHAPE_TRIANGLE:
                draw_triangle(canvas, shapes[i].data.triangle.x1, shapes[i].data.triangle.y1,
                                      shapes[i].data.triangle.x2, shapes[i].data.triangle.y2,
                                      shapes[i].data.triangle.x3, shapes[i].data.triangle.y3);
                break;
        }
    }
}

// Displays the canvas on the terminal with coordinates helper grids
void display_canvas(char canvas[HEIGHT][WIDTH]) {
    // Print column indices: tens digit
    printf("     ");
    for (int x = 0; x < WIDTH; x++) {
        printf("%d", (x / 10) % 10);
    }
    printf("\n");

    // Print column indices: units digit
    printf("     ");
    for (int x = 0; x < WIDTH; x++) {
        printf("%d", x % 10);
    }
    printf("\n");

    // Print top horizontal border
    printf("    +");
    for (int x = 0; x < WIDTH; x++) {
        printf("-");
    }
    printf("+\n");

    // Print each row with vertical borders and row indices
    for (int y = 0; y < HEIGHT; y++) {
        printf("%02d  |", y);
        for (int x = 0; x < WIDTH; x++) {
            putchar(canvas[y][x]);
        }
        printf("|\n");
    }

    // Print bottom horizontal border
    printf("    +");
    for (int x = 0; x < WIDTH; x++) {
        printf("-");
    }
    printf("+\n");

    // Print column indices: units digit for ease of reading
    printf("     ");
    for (int x = 0; x < WIDTH; x++) {
        printf("%d", x % 10);
    }
    printf("\n\n");
}
