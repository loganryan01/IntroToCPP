#pragma once

// The information about the player.
struct Player
{
    char initials[4] = "\0";
    int score;
};

// The x and y position for the slot.
struct Point2D
{
    int x;
    int y;
};