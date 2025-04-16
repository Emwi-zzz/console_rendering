# Console Rendering API

**Note:** This is a school project aimed at gaining an understanding of how raycasting works. The code is not optimized due to the low resolution and the minimal number of objects present in the scene.

For instance, figures are represented as objects, and each point is defined for each polygon, even if two polygons share the same point. Please note that this code will not be optimized or updated.

## Compilation Instructions

I use **clang++** for compiling the project.

To compile the code, run the following command in your terminal:

```bash
clang++ -std=c++17 main.cpp
```
## How It Works

The project utilizes raycasting to render polygons on the screen with light direction and perspective applied to a screen of dimensions `WIDTH x HEIGHT`. Due to the non-square nature of console symbols, the final raycast is scaled accordingly.

Each more complex figure is composed of polygons or other shapes, all of which are located in the `src/render/` directory.

To adapt the project for your own resolution and font, you will need to adjust the `WIDTH` and `HEIGHT` values. These values represent the number of symbols displayed in your command line. Additionally, you may need to modify the scaling factor (the proportion between the height and width of a symbol).

You can also change the direction of the sunlight and create objects from the given figures or even define your own.
