#include <stdio.h>
#include <stdlib.h>
#include "shapes.h"

// Read integer safely from stdin, clearing invalid inputs
int read_int(const char* prompt) {
    int value;
    while (1) {
        printf("%s", prompt);
        if (scanf("%d", &value) == 1) {
            // Consume the remaining characters up to newline
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            return value;
        } else {
            printf("Invalid input. Please enter an integer.\n");
            // Clear invalid buffer
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
        }
    }
}

// Display shape specifications in text format
void print_shape(int index, Shape s) {
    printf("[%d] ", index);
    switch (s.type) {
        case SHAPE_LINE:
            printf("Line from (%d, %d) to (%d, %d)\n",
                   s.data.line.x1, s.data.line.y1,
                   s.data.line.x2, s.data.line.y2);
            break;
        case SHAPE_RECTANGLE:
            printf("Rectangle at top-left (%d, %d), width %d, height %d\n",
                   s.data.rect.x, s.data.rect.y,
                   s.data.rect.width, s.data.rect.height);
            break;
        case SHAPE_CIRCLE:
            printf("Circle at center (%d, %d) with radius %d\n",
                   s.data.circle.cx, s.data.circle.cy,
                   s.data.circle.radius);
            break;
        case SHAPE_TRIANGLE:
            printf("Triangle with vertices A(%d, %d), B(%d, %d), C(%d, %d)\n",
                   s.data.triangle.x1, s.data.triangle.y1,
                   s.data.triangle.x2, s.data.triangle.y2,
                   s.data.triangle.x3, s.data.triangle.y3);
            break;
    }
}

// List all active shapes in the picture vector
void list_shapes(Shape shapes[], int count) {
    if (count == 0) {
        printf("\nNo objects in the picture.\n");
        return;
    }
    printf("\n--- Objects in the Picture ---\n");
    for (int i = 0; i < count; i++) {
        print_shape(i + 1, shapes[i]);
    }
    printf("------------------------------\n");
}

// Create a new shape and append it to the shape vector
void add_shape(Shape shapes[], int* count) {
    if (*count >= MAX_SHAPES) {
        printf("Canvas shape list is full! Cannot add more shapes.\n");
        return;
    }

    printf("\n--- Add Object ---\n");
    printf("1. Line\n");
    printf("2. Rectangle\n");
    printf("3. Circle\n");
    printf("4. Triangle\n");
    int choice = read_int("Select Shape Type (1-4): ");

    if (choice < 1 || choice > 4) {
        printf("Invalid choice. Operation cancelled.\n");
        return;
    }

    Shape s;
    switch (choice) {
        case 1:
            s.type = SHAPE_LINE;
            printf("Enter coordinates (Canvas dimensions: 60 columns x 20 rows):\n");
            s.data.line.x1 = read_int("  x1 (0-59): ");
            s.data.line.y1 = read_int("  y1 (0-19): ");
            s.data.line.x2 = read_int("  x2 (0-59): ");
            s.data.line.y2 = read_int("  y2 (0-19): ");
            break;
        case 2:
            s.type = SHAPE_RECTANGLE;
            printf("Enter rectangle details:\n");
            s.data.rect.x = read_int("  Top-left x (0-59): ");
            s.data.rect.y = read_int("  Top-left y (0-19): ");
            s.data.rect.width = read_int("  Width (positive integer): ");
            s.data.rect.height = read_int("  Height (positive integer): ");
            if (s.data.rect.width <= 0 || s.data.rect.height <= 0) {
                printf("Width and Height must be positive. Operation cancelled.\n");
                return;
            }
            break;
        case 3:
            s.type = SHAPE_CIRCLE;
            printf("Enter circle details:\n");
            s.data.circle.cx = read_int("  Center cx (0-59): ");
            s.data.circle.cy = read_int("  Center cy (0-19): ");
            s.data.circle.radius = read_int("  Radius (positive integer): ");
            if (s.data.circle.radius < 0) {
                printf("Radius must be non-negative. Operation cancelled.\n");
                return;
            }
            break;
        case 4:
            s.type = SHAPE_TRIANGLE;
            printf("Enter three vertices:\n");
            s.data.triangle.x1 = read_int("  x1 (0-59): ");
            s.data.triangle.y1 = read_int("  y1 (0-19): ");
            s.data.triangle.x2 = read_int("  x2 (0-59): ");
            s.data.triangle.y2 = read_int("  y2 (0-19): ");
            s.data.triangle.x3 = read_int("  x3 (0-59): ");
            s.data.triangle.y3 = read_int("  y3 (0-19): ");
            break;
    }

    shapes[*count] = s;
    (*count)++;
    printf("Object added successfully.\n");
}

// Modify an existing shape's parameters
void modify_shape(Shape shapes[], int count) {
    if (count == 0) {
        printf("\nNo objects to modify.\n");
        return;
    }

    list_shapes(shapes, count);
    int idx = read_int("Enter the index of the object to modify: ");
    if (idx < 1 || idx > count) {
        printf("Invalid shape index.\n");
        return;
    }

    Shape* s = &shapes[idx - 1];
    printf("\nModifying Shape: ");
    print_shape(idx, *s);

    switch (s->type) {
        case SHAPE_LINE:
            printf("Enter new Line coordinates:\n");
            s->data.line.x1 = read_int("  New x1: ");
            s->data.line.y1 = read_int("  New y1: ");
            s->data.line.x2 = read_int("  New x2: ");
            s->data.line.y2 = read_int("  New y2: ");
            break;
        case SHAPE_RECTANGLE:
            printf("Enter new Rectangle details:\n");
            s->data.rect.x = read_int("  New Top-left x: ");
            s->data.rect.y = read_int("  New Top-left y: ");
            s->data.rect.width = read_int("  New Width (positive integer): ");
            s->data.rect.height = read_int("  New Height (positive integer): ");
            if (s->data.rect.width <= 0 || s->data.rect.height <= 0) {
                printf("Width and Height must be positive. Reverting modification.\n");
                return;
            }
            break;
        case SHAPE_CIRCLE:
            printf("Enter new Circle details:\n");
            s->data.circle.cx = read_int("  New Center cx: ");
            s->data.circle.cy = read_int("  New Center cy: ");
            s->data.circle.radius = read_int("  New Radius (positive integer): ");
            if (s->data.circle.radius < 0) {
                printf("Radius must be non-negative. Reverting modification.\n");
                return;
            }
            break;
        case SHAPE_TRIANGLE:
            printf("Enter new Triangle vertices:\n");
            s->data.triangle.x1 = read_int("  New x1: ");
            s->data.triangle.y1 = read_int("  New y1: ");
            s->data.triangle.x2 = read_int("  New x2: ");
            s->data.triangle.y2 = read_int("  New y2: ");
            s->data.triangle.x3 = read_int("  New x3: ");
            s->data.triangle.y3 = read_int("  New y3: ");
            break;
    }

    printf("Object modified successfully.\n");
}

// Delete an object from the list by shifting array elements
void delete_shape(Shape shapes[], int* count) {
    if (*count == 0) {
        printf("\nNo objects to delete.\n");
        return;
    }

    list_shapes(shapes, *count);
    int idx = read_int("Enter the index of the object to delete: ");
    if (idx < 1 || idx > *count) {
        printf("Invalid shape index.\n");
        return;
    }

    // Shift elements left to maintain contiguity
    for (int i = idx - 1; i < *count - 1; i++) {
        shapes[i] = shapes[i + 1];
    }
    (*count)--;
    printf("Object deleted successfully.\n");
}

int main() {
    Shape shapes[MAX_SHAPES];
    int count = 0;
    char canvas[HEIGHT][WIDTH];

    // Initial canvas setup
    render_canvas(shapes, count, canvas);

    while (1) {
        printf("\n======================================\n");
        printf("      2D TEXT-BASED GRAPHICS EDITOR\n");
        printf("======================================\n");
        printf(" 1. Add Shape\n");
        printf(" 2. Delete Shape\n");
        printf(" 3. Modify Shape\n");
        printf(" 4. Render and Display Canvas\n");
        printf(" 5. List Shapes\n");
        printf(" 6. Clear All Shapes\n");
        printf(" 7. Exit\n");
        printf("======================================\n");

        int option = read_int("Choose an option (1-7): ");
        switch (option) {
            case 1:
                add_shape(shapes, &count);
                render_canvas(shapes, count, canvas);
                break;
            case 2:
                delete_shape(shapes, &count);
                render_canvas(shapes, count, canvas);
                break;
            case 3:
                modify_shape(shapes, count);
                render_canvas(shapes, count, canvas);
                break;
            case 4:
                render_canvas(shapes, count, canvas);
                display_canvas(canvas);
                break;
            case 5:
                list_shapes(shapes, count);
                break;
            case 6:
                count = 0;
                render_canvas(shapes, count, canvas);
                printf("All shapes have been cleared.\n");
                break;
            case 7:
                printf("Exiting... Thanks for using the Graphics Editor!\n");
                return 0;
            default:
                printf("Option not recognized. Please choose 1-7.\n");
                break;
        }
    }
    return 0;
}
