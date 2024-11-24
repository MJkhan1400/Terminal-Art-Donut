#include <stdio.h>
#include <math.h>
#include <string.h>
#include <unistd.h> // For usleep function

#define WIDTH 80
#define HEIGHT 22
#define NUM_PIXELS (WIDTH * HEIGHT)

// Define colors
#define RESET "\x1b[0m"
#define BUN_COLOR "\x1b[38;5;94m"
#define TOPPING_COLOR "\x1b[38;5;213m"

// Function to return color based on character
const char *getColor(char c)
{
    switch (c)
    {
    case '@':
    case '#':
    case '$':
    case '*':
    case '=':
    case '!':
        return TOPPING_COLOR;
    default:
        return BUN_COLOR;
    }
}

int main()
{
    double A = 0, B = 0;
    float z[NUM_PIXELS];
    char b[NUM_PIXELS];

    // Hide the cursor and clear the screen
    printf("\x1b[?25l"); // Hide cursor
    printf("\x1b[2J");    // Clear the screen

    for (;;)
    {
        // Clear buffers
        memset(b, ' ', NUM_PIXELS);
        memset(z, 0, sizeof(z));

        for (float j = 0; j < 6.28; j += 0.07) // Loop over theta (j)
        {
            for (float i = 0; i < 6.28; i += 0.02) // Loop over phi (i)
            {
                float c = sin(i);
                float d = cos(j);
                float e = sin(A);
                float f = sin(j);
                float g = cos(A);
                float h = d + 2;
                float D = 1 / (c * h * e + f * g + 5);
                float l = cos(i);
                float m = cos(B);
                float n = sin(B);
                float t = c * h * g - f * e;

                int x = 40 + 30 * D * (l * h * m - t * n);
                int y = 12 + 15 * D * (l * h * n + t * m);
                int o = x + WIDTH * y;
                int N = 8 * ((f * e - c * d * g) * m - c * d * e - f * g - l * d * n);

                if (y >= 0 && y < HEIGHT && x >= 0 && x < WIDTH && D > z[o])
                {
                    z[o] = D;
                    b[o] = ".,-~:;=!*#$@"[N > 0 ? N : 0];
                }
            }
        }

        // Print the buffer with colors
        printf("\x1b[H"); // Move cursor to home position
        for (int k = 0; k < NUM_PIXELS; k++)
        {
            if (k % WIDTH == 0 && k != 0)
                putchar('\n');
            printf("%s%c" RESET, getColor(b[k]), b[k]);
        }

        // Update angles for rotation
        A += 0.04;
        B -= 0.02; // Rotate from right to left

        // Add delay to slow down the animation
        usleep(30000);
    }

    // Show cursor when done (though this is never reached in the infinite loop)
    printf("\x1b[?25h");
    return 0;
}

