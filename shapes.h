#ifndef SHAPES_H
#define SHAPES_H

#define WIDTH 60
#define HEIGHT 20
#define MAX_SHAPES 100

// Enumeration for supported shape types
typedef enum {
    SHAPE_LINE,
    SHAPE_RECTANGLE,
    SHAPE_CIRCLE,
    SHAPE_TRIANGLE
} ShapeType;

// Parameters for drawing a line
typedef struct {
    int x1, y1;
    int x2, y2;
} LineParams;

// Parameters for drawing a rectangle
typedef struct {
    int x, y;
    int width, height;
} RectParams;

// Parameters for drawing a circle
typedef struct {
    int cx, cy;
    int radius;
} CircleParams;

// Parameters for drawing a triangle
typedef struct {
    int x1, y1;
    int x2, y2;
    int x3, y3;
} TriangleParams;

// Unified shape structure
typedef struct {
    ShapeType type;
    union {
        LineParams line;
        RectParams rect;
        CircleParams circle;
        TriangleParams triangle;
    } data;
} Shape;

// Canvas functions
void init_canvas(char canvas[HEIGHT][WIDTH]);
void render_canvas(Shape shapes[], int count, char canvas[HEIGHT][WIDTH]);
void display_canvas(char canvas[HEIGHT][WIDTH]);

// Low-level shape rendering functions
void draw_line(char canvas[HEIGHT][WIDTH], int x1, int y1, int x2, int y2);
void draw_circle(char canvas[HEIGHT][WIDTH], int cx, int cy, int radius);
void draw_rect(char canvas[HEIGHT][WIDTH], int x, int y, int w, int h);
void draw_triangle(char canvas[HEIGHT][WIDTH], int x1, int y1, int x2, int y2, int x3, int y3);

#endif // SHAPES_H
