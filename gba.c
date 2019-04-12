#include "gba.h"

volatile unsigned short *videoBuffer = (volatile unsigned short *) 0x6000000;
u32 vBlankCounter = 0;
volatile OamEntry shadow[128];
volatile OamEntry* playerFrog = &shadow[0];

void waitForVBlank(void) {
    while(*SCANLINECOUNTER > 160);
    while(*SCANLINECOUNTER < 160);
    vBlankCounter++;
}

static int __qran_seed= 42;
static int qran(void) {
    __qran_seed= 1664525*__qran_seed+1013904223;
    return (__qran_seed>>16) & 0x7FFF;
}

int randint(int min, int max) {
    return (qran()*(max-min)>>15)+min;
}

void setPixel(int x, int y, u16 color) {
    videoBuffer[((y - 1) * 240) + x - 1] = color;
}

void drawRectDMA(int x, int y, int width, int height, volatile u16 color) {
    for(int i = 0; i < height; i++) {
        DMAHelper((void *) &color, (void *) &videoBuffer[(y + i) * WIDTH + x], width, 0);
    }
}

void drawFullScreenImageDMA(u16 *image) {
    DMAHelper((void *) image, (void *) videoBuffer, (WIDTH * HEIGHT), 1);
}

void drawImageDMA(int x, int y, int width, int height, u16 *image) {
    for(int i = 0; i < height; i++) {
        DMAHelper((void *) &image[i * width], (void *) &videoBuffer[(y + i) * WIDTH + x], width, 1);
    }
}

void fillScreenDMA(volatile u16 color) {
    
    DMAHelper((void *) &color, (void *) videoBuffer, (WIDTH * HEIGHT), 0);
}

void DMAHelper(void *source, void *dest, u16 count, int mode) {
    DMA[DMA_CHANNEL_3].cnt = 0;
    DMA[DMA_CHANNEL_3].src = source;
    DMA[DMA_CHANNEL_3].dst = dest;

    if (mode == 0) {
        DMA[DMA_CHANNEL_3].cnt = count | DMA_SOURCE_FIXED | DMA_16 | DMA_ON;
    } else {
        DMA[DMA_CHANNEL_3].cnt = count | DMA_SOURCE_INCREMENT | DMA_16 | DMA_ON;
    }
}

/** void spriteSetUp(void) {
    //load palette
    DMA[3].src = (void *) sprites_palette;
    DMA[3].dst = SPRITEPAL;
    DMA[3].cnt = SPRITES_PALETTE_LENGTH | DMA_ON;

    //copy sprite data
    DMA[3].src = (void *) sprites;
    DMA[3].dst = &CHARBLOCKBASE[5];
    DMA[3].cnt = SPRITES_LENGTH | DMA_ON;

    //hide sprites
    for(int i = 0; i < 128; i++) {
       shadow[i].attr0 = ATTR0_HIDE;
    }

    playerFrog = &shadow[0];
    playerFrog->attr2 = FROG_PALETTE_ID| FROG_ID;


}

void drawSprite(int x, int y) {
    playerFrog->attr0 = (y) | SPRITES_PALETTE_TYPE | FROG_SPRITE_SHAPE;
    playerFrog ->attr1 = (x) | FROG_SPRITE_SIZE;

    DMA[3].src = shadow;
    DMA[3].dst = OAMMEM;
    DMA[3].cnt = 128*4 | DMA_ON;
}

void hideSprite(void) {
    playerFrog->attr0 = ATTR0_HIDE;

    DMA[3].src = shadow;
    DMA[3].dst = OAMMEM;
    DMA[3].cnt = 128*4 | DMA_ON;
} */

void drawChar(int col, int row, char ch, u16 color) {
    for(int r = 0; r<8; r++) {
        for(int c=0; c<6; c++) {
            if(fontdata_6x8[OFFSET(r, c, 6) + ch*48]) {
                setPixel(col+c, row+r, color);
            }
        }
    }
}

void drawString(int col, int row, char *str, u16 color) {
    while(*str) {
        drawChar(col, row, *str++, color);
        col += 6;
    }
}

void drawCenteredString(int x, int y, int width, int height, char *str, u16 color) {
    u32 len = 0;
    char *strCpy = str;
    while (*strCpy) {
        len++;
        strCpy++;
    }

    u32 strWidth = 6 * len;
    u32 strHeight = 8;

    int col = x + ((width - strWidth) >> 1);
    int row = y + ((height - strHeight) >> 1);
    drawString(col, row, str, color);
}
