//
// breakout.c
//
// Computer Science 50
// Problem Set 3
//

// standard libraries
#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Stanford Portable Library
#include <spl/gevents.h>
#include <spl/gobjects.h>
#include <spl/gwindow.h>

// height and width of game's window in pixels
#define HEIGHT 600
#define WIDTH 400

// number of rows of bricks
#define ROWS 5

// number of columns of bricks
#define COLS 10

// radius of ball in pixels
#define DIAMETER 10

// lives
#define LIVES 3

// prototypes
void initBricks(GWindow window);
GOval initBall(GWindow window);
GRect initPaddle(GWindow window);
GLabel initScoreboard(GWindow window);
void updateScoreboard(GWindow window, GLabel label, int points);
GObject detectCollision(GWindow window, GOval ball);

int main(void)
{
    // seed pseudorandom number generator
    srand48(time(NULL));

    // instantiate window
    GWindow window = newGWindow(WIDTH, HEIGHT);

    // instantiate bricks
    initBricks(window);

    // instantiate ball, centered in middle of window
    GOval ball = initBall(window);

    // instantiate paddle, centered at bottom of window
    GRect paddle = initPaddle(window);

    // instantiate scoreboard, centered in middle of window, just above ball
    GLabel label = initScoreboard(window);

    // number of bricks initially
    int bricks = COLS * ROWS;

    // number of lives initially
    int lives = LIVES;

    // number of points initially
    int points = 0;

    // Wait for mouse click to start game
    waitForClick();
    
    // Set initial velocity, set x velocity to random
    double xvelocity = drand48() * 1.5;
    double yvelocity = 2.5;
        
    // keep playing until game over
    while (lives > 0 && bricks > 0)
    {
        updateScoreboard(window, label, points);
        
        GEvent event = getNextEvent(MOUSE_EVENT);       
        if (event != NULL)
        {
            // If mouse if moved, move paddle horizontally
            if (getEventType(event) == MOUSE_MOVED)
            {
                double x = getX(event) - getWidth(paddle) / 2;
                setLocation(paddle, x, 550);
            }
        }
        // Move ball per initial velocity
        // Reverse velocity to bounce off of walls
        move(ball, xvelocity, yvelocity);
               
        if (getX(ball) + getWidth(ball) >= getWidth(window))
        {
            xvelocity = -xvelocity;
        }
        if (getX(ball) <= 0)
        {
            xvelocity = -xvelocity;
        }
        // If balls hits bottom of window, lose life, reposition ball
        if (getY(ball) + getHeight(ball) >= getHeight(window))
        {
            lives--;
            setLocation(ball, 195, 295);
            waitForClick();
        }
        if (getY(ball) <= 0)
        {
            yvelocity = -yvelocity;
        }
        pause(10);
        
        // Bounce vertically off rectanglular objects
        GObject object = detectCollision(window, ball);
        if (object != NULL)
        {
            if (object == paddle)
            {
                yvelocity = -yvelocity;         
            }
            else if (strcmp(getType(object), "GRect") == 0)
            {
                removeGWindow(window, object);
                yvelocity = -yvelocity;
                points++;
                bricks--;
            }
        }
    }
    // If all bricks are broken, post "Winner" message
    if (bricks == 0)
    {
        updateScoreboard(window, label, points);
        GLabel winner = newGLabel("WINNER!");
        setFont(winner, "ArialBlack-36");
        setColor(winner, "ORANGE");
        add(window, winner);
        setLocation(winner, 120, 200);
    }
    // If all lives are lost, post "Game Over" message
    if (lives == 0)
    {
        GLabel loser = newGLabel("GAME OVER");
        setFont(loser, "ArialBlack-36");
        setColor(loser, "MAGENTA");
        add(window, loser);
        setLocation(loser, 90, 200);
    }   
    // wait for click before exiting
    waitForClick();

    // game over
    closeGWindow(window);
    return 0;
}

/**
 * Initializes window with a grid of bricks.
 */
void initBricks(GWindow window)
{
    // Loop through 5 rows of bricks, starting at y = 50
    for (int i = 0, y = 50; i < ROWS; i++, y = y + 15)
    {
        // Loop through 10 Columns, starting at x = 2
        for (int j = 0, x = 2; j < COLS; j++, x = x + 40)
        {
            // Make bricks 36x10
            GRect bricks = newGRect (x, y, 36, 10);
            // Change colors for each row
            setFilled(bricks, true);
            setColor(bricks, "BLACK");    
            if (i == 0)
            {
                setFillColor(bricks, "YELLOW");
            }
            if (i == 1)
            {
                setFillColor(bricks, "ORANGE");
            }
            if (i == 2)
            {
                setFillColor(bricks, "GREEN");
            }
            if (i == 3)
            {
                setFillColor(bricks, "CYAN");
            }
            if (i == 4)
            {
                setFillColor(bricks, "BLUE");
            }
            // Add bricks to window
            add(window, bricks);
        }
    }
}

/**
 * Instantiates ball in center of window.  Returns ball.
 */
GOval initBall(GWindow window)
{
    GOval ball = newGOval (195, 295, DIAMETER, DIAMETER);
    setFilled(ball, true);
    setColor(ball, "BLACK");
    setFillColor(ball, "LIGHT_GRAY");
    add(window, ball);
    return ball;
}

/**
 * Instantiates paddle in bottom-middle of window.
 */
GRect initPaddle(GWindow window)
{
    GRect paddle = newGRect (170, 550, 60, 10);
    setFilled(paddle, true);
    setColor(paddle, "BLACK");
    setFillColor(paddle, "DARK_GRAY");
    add(window, paddle);
    return paddle;
}
/**
 * Instantiates, configures, and returns label for scoreboard.
 */
GLabel initScoreboard(GWindow window)
{
    GLabel label = newGLabel(" ");
    setFont(label, "ArialBlack-50");
    setColor(label, "LIGHT_GRAY");
    add(window, label);
    return label;
}

/**
 * Updates scoreboard's label, keeping it centered in window.
 */
void updateScoreboard(GWindow window, GLabel label, int points)
{
    // update label
    char s[12];
    sprintf(s, "%i", points);
    setLabel(label, s);

    // center label in window
    double x = (getWidth(window) - getWidth(label)) / 2;
    double y = (getHeight(window) - getHeight(label)) / 2;
    setLocation(label, x, y);
}
/**
 * Detects whether ball has collided with some object in window
 * by checking the four corners of its bounding box (which are
 * outside the ball's GOval, and so the ball can't collide with
 * itself).  Returns object if so, else NULL.
 */
GObject detectCollision(GWindow window, GOval ball)
{
    // ball's location
    double x = getX(ball);
    double y = getY(ball);

    // for checking for collisions
    GObject object;

    // check for collision at ball's top-left corner
    object = getGObjectAt(window, x, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's top-right corner
    object = getGObjectAt(window, x + DIAMETER, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-left corner
    object = getGObjectAt(window, x, y + DIAMETER);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-right corner
    object = getGObjectAt(window, x + DIAMETER, y + DIAMETER);
    if (object != NULL)
    {
        return object;
    }

    // no collision
    return NULL;
}
