# 2D Text-Based Graphics Editor in C

A menu-driven C application that allows you to draw, modify, and delete vector-like shapes on a 60x20 text-based canvas.

## Features

- **Standard Shapes**:
  - **Line**: Drawn using Bresenham's Line Algorithm.
  - **Rectangle**: Boundary outlines drawn to specified widths and heights.
  - **Circle**: Drawn symmetrically using Bresenham's Midpoint Circle Algorithm.
  - **Triangle**: Drawn by connecting three custom vertex coordinates.
- **Interactive Editing**:
  - Add shape objects to the scene list.
  - Modify parameters of any existing shape.
  - Delete shapes from the scene.
  - Clear all objects.
- **Premium Grid Display**:
  - Canvas renders with column-indexing guides (tens and units rows) and left-aligned row numbers, making it easy to see exactly where coordinates lie.

## File Structure

- **[shapes.h](shapes.h)**: Configuration, data structures, and function declarations.
- **[shapes.c](shapes.c)**: Math algorithms and rendering logic for drawing shapes onto the 2D array.
- **[main.c](main.c)**: Command-line menu interface and input validation/sanitization.

## Compilation and Execution

To compile using GCC (for example, via Dev-C++'s bundled MinGW toolchain):

```bash
gcc -std=c99 -Wall -Wextra main.c shapes.c -o editor.exe
```

Run the compiled executable:

```bash
./editor.exe
```
