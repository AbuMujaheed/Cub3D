🎮 Cub3D - Comprehensive Project README
Welcome to Cub3D, a 42 school project that recreates the iconic first-person perspective rendering of the legendary Wolfenstein 3D game. This project uses raycasting to transform a 2D maze map into an immersive 3D experience in real-time .

🎯 Project Overview
Cub3D challenges you to build a 3D game engine from scratch in C, using the MiniLibX graphics library. The core technology behind it is raycasting - a rendering technique that creates a 3D perspective within a 2D map by casting rays from the player's viewpoint and calculating wall intersections .

What You'll Learn
Low-level graphics programming with window management and event handling

Raycasting mathematics using trigonometry and vector operations

File parsing with rigorous error handling

Memory management in C (no leaks allowed!)

Team collaboration using Git (this is a two-person project)

This project serves as a remarkable playground to explore the practical applications of mathematics without having to master complex, low-level specifics .

📋 Mandatory Requirements
Core Features
Your Cub3D implementation must include:

Requirement	Description
Textured Walls	Different XPM textures for North (NO), South (SO), East (EA), and West (WE) walls
Floor & Ceiling	Custom RGB colors defined in the map file
Movement Controls	WASD keys for movement, arrow keys for rotation
Clean Exit	ESC key or window close button exits gracefully
Map Parsing	Read .cub files and validate map structure 
Scene Description File (.cub)
Your program must parse a configuration file with:

bash
NO ./path_to_the_north_texture.xpm   # North wall texture
SO ./path_to_the_south_texture.xpm   # South wall texture  
WE ./path_to_the_west_texture.xpm    # West wall texture
EA ./path_to_the_east_texture.xpm    # East wall texture
F 220,100,0                          # Floor color (RGB)
C 225,30,0                           # Ceiling color (RGB)

1111111111111111111111111            # Map (1=wall, 0=empty)
1000000000110000000000001
1011000001110000000000001
1001000000000000000000001
111111111011000001110000000000001
100000000011000001110111111111111
11110111111111011100000010001
11110111111111011101010010001
11000000110101011100000010001
10000000000000001100000010001
10000000000000001101010010001
11000001110101011111011110N0111   # N = player start facing North
Map Validation Requirements
The parser must verify:

Map is closed/surrounded by walls (no openings)

Only one player starting position (N, S, E, or W)

Valid characters only: 0 (empty), 1 (wall), N/S/E/W (player)

Empty lines or spaces are allowed but must be validated

Invalid maps display "Error\n" with a meaningful message 

🎮 Controls
Key	Action
W	Move forward
S	Move backward
A	Strafe left
D	Strafe right
←	Rotate camera left
→	Rotate camera right
ESC	Exit game
❌	Close window button

🏗️ Project Architecture
A well-structured Cub3D typically follows this organization:

cub3d/
├── mandatory/
│   ├── include/
│   │   ├── cub3d.h        # Main header with structs
│   │   ├── constants.h    # Game constants (screen size, FOV)
│   │   ├── errors.h       # Error messages
│   │   └── functions.h    # Function prototypes
│   ├── src/
│   │   ├── main.c         # Entry point
│   │   ├── parse/         # Map file parsing
│   │   ├── init/          # MLX initialization
│   │   ├── rays/          # Raycasting core logic
│   │   ├── graphics/      # Texture and image handling
│   │   ├── events/        # Keyboard/mouse input
│   │   ├── math/          # Vector and DDA operations
│   │   └── utils/         # Helper functions
├── bonus/                 # Bonus features (separate)
├── lib/
│   ├── libft/             # Your custom library
│   └── minilibx-linux/    # MiniLibX submodule
└── Makefile

The Core Algorithm
Raycasting works by simulating light rays from the player's eye through each pixel column on the screen:

Cast a ray for each vertical screen column

Calculate direction using camera plane and player angle

Find wall intersections using DDA (Digital Differential Analyzer)

Calculate wall height based on perpendicular distance

Select texture column based on exact hit point

Draw vertical slice with proper shading 

Understanding the Math
Field of View (FOV)
Typically 60-66 degrees for first-person games

The camera plane determines how wide your view is

Formula: plane_size = tan(FOV / 2)

// Typical setup with 66° FOV
double dirX = -1.0, dirY = 0.0;      // Player facing West
double planeX = 0.0, planeY = 0.66;   // Camera plane (FOV = 2 * atan(0.66) ≈ 66°)

The DDA Algorithm
DDA (Digital Differential Analyzer) efficiently finds which grid cell a ray hits:

// Step 1: Calculate initial ray direction
double rayDirX = dirX + planeX * cameraX;
double rayDirY = dirY + planeY * cameraX;

// Step 2: Calculate step direction and distance
int stepX = (rayDirX < 0) ? -1 : 1;
int stepY = (rayDirY < 0) ? -1 : 1;

// Step 3: Walk along the ray until hitting a wall
while (map[mapX][mapY] != '1') {
    if (sideDistX < sideDistY) {
        sideDistX += deltaDistX;
        mapX += stepX;
        side = 0;  // Hit vertical wall
    } else {
        sideDistY += deltaDistY;
        mapY += stepY;
        side = 1;  // Hit horizontal wall
    }
}

Perpendicular Distance & Fisheye Fix
To prevent the fisheye effect (walls curving unnaturally), you must use perpendicular distance:
// Calculate correct distance (no fisheye)
if (side == 0)
    perpWallDist = (sideDistX - deltaDistX);
else
    perpWallDist = (sideDistY - deltaDistY);

// Calculate wall height (inversely proportional to distance)
int lineHeight = (int)(screenHeight / perpWallDist);

🖼️ Texture Rendering
Wall Textures
Each wall orientation requires its own texture:

NO - North-facing walls

SO - South-facing walls

WE - West-facing walls

EA - East-facing walls 

Texture Mapping Formula

// Calculate which X coordinate of texture to use
double wallX;
if (side == 0)  // Vertical wall hit
    wallX = playerY + perpWallDist * rayDirY;
else            // Horizontal wall hit
    wallX = playerX + perpWallDist * rayDirX;
wallX -= floor(wallX);

// Get texture pixel column
int texX = (int)(wallX * (double)textureWidth);
if ((side == 0 && rayDirX > 0) || (side == 1 && rayDirY < 0))
    texX = textureWidth - texX - 1;

    Floor and Ceiling
Simple RGB colors (no textures for mandatory part):

F 220,100,0 - Floor color

C 225,30,0 - Ceiling color 

🛠️ Technical Requirements
Allowed Functions
Your Cub3D can only use:

Standard: open, close, read, write, printf, malloc, free, perror, strerror, exit

Math Library: -lm functions

MiniLibX: All MLX graphics functions

Libft: Your custom library
make        # Compile mandatory part
make bonus  # Compile with bonus features
make clean  # Remove object files
make fclean # Remove everything
make re     # Recompile fresh


📚 Resources & References
Official Documentation
MiniLibX Documentation

Lode's Raycasting Tutorial (essential!)

42 Subject PDF

Student Projects (for reference only)
MiguelViHe/42-Cub3d - Robust implementation with complete parsing

qnert/cub3d - Bonus features (doors, minimap, mouse)

ysahih/cub3d - Clean, well-structured code

Technical References
Raycasting: Rendering walls by casting rays from player viewpoint

DDA Algorithm: Digital Differential Analyzer for line drawing

Bresenham's Line Algorithm: Alternative to DDA for ray stepping

FOV (Field of View): Angular extent of the observable world 

Perpendicular Distance: Corrects the fisheye effect

Camera Plane: Determines ray direction for each screen column

👥 Team Collaboration Tips
Cub3D is a team project. Here's how to split work effectively:

Partitioning Strategies
Vertical Split (Recommended):

Person A: Map parser + file validation + initialization + memory management

Person B: Raycasting engine + rendering + event handling + textures

Horizontal Split:

Both work on parsing first (together)

Split rendering vs input handling

Merge and test extensively

Suggested Git workflow:

bash
# Create branches
git checkout -b parser
git checkout -b raycasting

# Regular integration
git merge main  # Keep up to date
git push origin branch-name
Communication Essentials
Discuss data structures before coding (especially the t_game struct)

Agree on function prototypes early

Use pair programming for complex algorithms (DDA, texture mapping)

Document edge cases found during parsing

Create a shared test map suite 

🏆 Evaluation Tips
What evaluators look for:

Smooth movement - No jerky or slow rendering

Correct textures - Different per wall orientation

Clean exit - No crashes, no memory leaks

Map validation - Proper error messages

Norm compliance - Strict adherence to 42 style

Grade potential:

Mandatory only: up to 100/100

With bonuses: up to 125/100 (extra 25 points)

📖 Final Words
Cub3D is one of the most rewarding projects in the 42 curriculum. You'll transform abstract math into visible, playable graphics. The feeling when you first see textured walls rendering correctly is unforgettable!

Remember: Start simple (flat colors), then add textures, finally bonuses. Master the DDA algorithm before adding complexity.

Good luck, and may your rays be swift and your walls well-textured! 🎮✨

Made with ️❤️ for the 42 Network
