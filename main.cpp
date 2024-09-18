#include "screen.h"
#include <numeric>
#include <cmath>
#undef main

// Define a struct for the cube's vertices
struct vec3
{   
    float x, y, z;
};

// Struct for the connections between the points of the cube
struct connection
{
    int a, b;
};

// Function to rotate the cube around the x, y, and z axes
void rotate(vec3& point, float x = 1, float y = 1, float z = 1)
{
    float rad = 0;

    // Rotation along the x-axis
    rad = x;
    float newY = std::cos(rad) * point.y - std::sin(rad) * point.z;
    float newZ = std::sin(rad) * point.y + std::cos(rad) * point.z;
    point.y = newY;
    point.z = newZ;

    // Rotation along the y-axis
    rad = y;
    float newX = std::cos(rad) * point.x + std::sin(rad) * point.z;
    point.z = -std::sin(rad) * point.x + std::cos(rad) * point.z;
    point.x = newX;

    // Rotation along the z-axis
    rad = z;
    newX = std::cos(rad) * point.x - std::sin(rad) * point.y;
    newY = std::sin(rad) * point.x + std::cos(rad) * point.y;
    point.x = newX;
    point.y = newY;
}

// Function to draw a line between two points
void line(Screen& screen, float x1, float y1, float x2, float y2)
{
    float dx = x2 - x1;
    float dy = y2 - y1;

    // Calculate the length of the line using Pythagoras theorem
    float length = std::sqrt(dx * dx + dy * dy);
    float angle = std::atan2(dy, dx);

    // Draw the line pixel by pixel
    for (float i = 0; i < length; i++)
    {
        screen.pixel(
            x1 + std::cos(angle) * i,
            y1 + std::sin(angle) * i
        );
    }
}

int main()
{
    Screen screen;

    // Define the vertices of the cube
    std::vector<vec3> points{
        {100, 100, 100},
        {200, 100, 100},
        {200, 200, 100},
        {100, 200, 100},
        {100, 100, 200},
        {200, 100, 200},
        {200, 200, 200},
        {100, 200, 200}
    };

    // Define the connections (edges) of the cube
    std::vector<connection> connections
    {
        {0, 4}, {1, 5}, {2, 6}, {3, 7},
        {0, 1}, {1, 2}, {2, 3}, {3, 0},
        {4, 5}, {5, 6}, {6, 7}, {7, 4},
    };

    // Calculate the cube's centroid
    vec3 c{0, 0, 0};
    for (auto& p : points)
    {
        c.x += p.x;
        c.y += p.y;
        c.z += p.z;
    }

    c.x /= points.size();
    c.y /= points.size();
    c.z /= points.size();

    // Movement variables
    // float moveSpeed = 1.0f;  // Slow down movement speed
    float moveSpeed = 0.25f;
    bool movingUp = false, movingDown = false, movingLeft = false, movingRight = false;
    float offsetX = 0.0f, offsetY = 0.0f;  // Initial offsets

    while (true)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
                return 0;

            // Handle key presses for movement
            if (event.type == SDL_KEYDOWN)
            {
                switch (event.key.keysym.sym)
                {
                    case SDLK_w:
                    case SDLK_UP:
                        movingUp = true;
                        break;
                    case SDLK_s:
                    case SDLK_DOWN:
                        movingDown = true;
                        break;
                    case SDLK_a:
                    case SDLK_LEFT:
                        movingLeft = true;
                        break;
                    case SDLK_d:
                    case SDLK_RIGHT:
                        movingRight = true;
                        break;
                }
            }
            if (event.type == SDL_KEYUP)
            {
                switch (event.key.keysym.sym)
                {
                    case SDLK_w:
                    case SDLK_UP:
                        movingUp = false;
                        break;
                    case SDLK_s:
                    case SDLK_DOWN:
                        movingDown = false;
                        break;
                    case SDLK_a:
                    case SDLK_LEFT:
                        movingLeft = false;
                        break;
                    case SDLK_d:
                    case SDLK_RIGHT:
                        movingRight = false;
                        break;
                }
            }

        }

        // Apply movement
        if (movingUp) offsetY -= moveSpeed;
        if (movingDown) offsetY += moveSpeed;
        if (movingLeft) offsetX -= moveSpeed;
        if (movingRight) offsetX += moveSpeed;

        // Rotate and move the cube
        for (auto& p : points)
        {
            p.x -= c.x;
            p.y -= c.y;
            p.z -= c.z;

            rotate(p, 0.02, 0.01, 0.04);

            p.x += c.x + offsetX;
            p.y += c.y + offsetY;
            p.z += c.z;

            screen.pixel(p.x, p.y);
        }

        // Draw the cube's edges
        for (auto& conn : connections)
        {
            line(screen, points[conn.a].x,
                 points[conn.a].y,
                 points[conn.b].x,
                 points[conn.b].y);
        }

        screen.show();   // Display the pixels
        screen.clear();  // Clear the screen for the next frame
        screen.input();  // Handle screen input events
        SDL_Delay(35);   // Frame delay for smoothness
    }

    return 0;
}