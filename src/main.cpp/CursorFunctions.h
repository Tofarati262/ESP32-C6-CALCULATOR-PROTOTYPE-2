#ifndef CURSOR_FUNCTIONS_H
#define  CURSOR_FUNCTIONS_H

#define CURSOR_WIDTH 5
#define CURSOR_HEIGHT 7
#define CURSOR_BLINK_DELAY 100  // Blinking speed in milliseconds
#define MAX_CHARS 22  // Maximum characters visible before scrolling

extern int lastcursorPos;
extern bool cursorVisible;  // Blinking state
extern unsigned long lastBlinkTime;
extern int cursorIndex;
extern int cursorPos;  // Cursor X position
extern int xPos;

extern uint8_t *screenendptr;
extern uint8_t screenstart;
extern uint8_t previousmapped;

extern void cursorMoveback();
extern void cursorMoveForward();


#endif// CURSOR_FUNCTIONS