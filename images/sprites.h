/*
 * Exported with nin10kit v1.7
 * Invocation command was nin10kit --mode=sprites --bpp=4 --for_bitmap --transparent=FFFFFF sprites grappleboi.png 
 * Time-stamp: Friday 04/12/2019, 04:11:14
 * 
 * Image Information
 * -----------------
 * grappleboi.png 8@16
 * Transparent color: (255, 255, 255)
 * 
 * All bug reports / feature requests are to be filed here https://github.com/TricksterGuy/nin10kit/issues
 */

#ifndef SPRITES_H
#define SPRITES_H

#define SPRITES_PALETTE_TYPE (0 << 13)
#define SPRITES_DIMENSION_TYPE (1 << 6)

extern const unsigned short sprites_palette[256];
#define SPRITES_PALETTE_SIZE 512
#define SPRITES_PALETTE_LENGTH 256

extern const unsigned short sprites[32];
#define SPRITES_SIZE 64
#define SPRITES_LENGTH 32

#define GRAPPLEBOI_PALETTE_ID (0 << 12)
#define GRAPPLEBOI_SPRITE_SHAPE (2 << 14)
#define GRAPPLEBOI_SPRITE_SIZE (0 << 14)
#define GRAPPLEBOI_ID 512

#endif

