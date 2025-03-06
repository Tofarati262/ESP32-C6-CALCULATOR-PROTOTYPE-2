#ifndef CURSOR_FUNCTIONS_H
#define  CURSOR_FUNCTIONS_H

#define CURSOR_WIDTH 5
#define CURSOR_HEIGHT 7
#define CURSOR_BLINK_DELAY 100  // Blinking speed in milliseconds
#define MAX_CHARS 22  // Maximum characters visible before scrolling

#include <vector>

extern int lastcursorPos;
extern bool cursorVisible;  // Blinking state
extern unsigned long lastBlinkTime;
extern int cursorIndex;
extern int cursorPos;  // Cursor X position
extern int xPos;

extern int  *screenendptr;
extern int  screenstart;
extern int  previousmapped;

extern void cursorMoveback();
extern void cursorMoveForward();
extern void cursorDelete();
extern void calcrun();
extern void drawCursor();
extern void  updateScreen();

class cursorArrow
{
  private:
  int level = 0;
  public:
  int screenstart = 0;
  void increase()
  {
    level++;
    if(level == 6)
    {
      screenstart++;
      level = 0;
    }
  }
  void decrease()
  { 
    if(level > 0){
      level--;
    }
  }

  int  getcursorLevel()
  {
    return level;
  }

  int getNextpage()
  {
    return screenstart;
  }
};

extern std::vector<char>equationbuffer;  // Stores the equation input


#endif// CURSOR_FUNCTIONS