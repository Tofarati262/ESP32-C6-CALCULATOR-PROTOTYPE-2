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
  int pages;

  void increase()
  {
    level++;
    if(level == 6 && screenstart < pages / 6)
    {
      screenstart++;
      level = 0;
    }
  }

  void movegriddown() //to navigate down the tic tax to y axis grid 
  {
    level++;
    if(level == 2)
    {
      screenstart++;
      level = 0;
    }
  }

  void movegridup() //to navigate up the tic tax to y axis grid 
  {
    if(level == 0)
    {
      level = 0;
    }else if (level > 0){
      level--;
    }
  }

  void decrease()
  { 
      
      if (level == 0 && screenstart >= 1)
      {
        level = 0;
        screenstart--;
      }else if (level > 0)
      {
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