#ifndef __ALLEGRO_INCLUDED__
#define __ALLEGRO_INCLUDED__

#include <"allegro/allegro.h">
#include <"allegro/allegro_image.h">
#include <"allegro/allegro_primitives.h">

#endif

class Hero {
   public:
      Hero(int tx, int ty);
      void loadSprite(char *filename);
      void draw();

      void stopMotion();
      void setMotionUp();
      void setMotionDown();
      void setMotionLeft();
      void setMotionRight();

      bool debug;
   private:
      // direction/movement
      enum {STILL, DOWN, UP, LEFT, RIGHT};
      // sprite loading
      enum {RIGHT_STEP, STANDING, LEFT_STEP};
      
      int x, y;
      short int dir;
      short int movement;

      // to do with animating the sprites
      int frameCount;
      int currentFrame;
      int animationDelay;

      ALLEGRO_BITMAP *spriteSheet;

      // methods
      void drawState(int direction, int step);
      void move(int direction);
      
};

Hero::Hero(int tx, int ty) {
   x = tx; 
   y = ty; 
   dir = DOWN;
   movement = STILL;
   debug = false;
   animationDelay = 3;
   currentFrame = 0;
}

void Hero::loadSprite(char *filename) {
   spriteSheet = al_load_bitmap(filename);
}

void Hero::draw(void) {
   // this will hold the frame that the animation is to hold
   int state;

   // increments frameCount and updates currentFrame if necessary
   ++frameCount;

   if (frameCount == animationDelay) {
      frameCount = 0;
      ++currentFrame;
      // overflows currentFrame
      if (currentFrame == 4) 
         currentFrame = 0;
   }

   switch(currentFrame) {
      case 0:
         state = STANDING; break;
      case 1:
         state = RIGHT_STEP; break;
      case 2:
         state = STANDING; break;
      case 3:
         state = LEFT_STEP; break;
   }

   // `still' doesn't require animation
   if (movement == STILL) {
      // erases old image
      al_draw_filled_rectangle(x, y, x + 16, y + 16, al_map_rgb(0,0,0));

      // draws still guy
      drawState(dir, STANDING);
   }

   // animated movement
   else {
      // erases the old image
      al_draw_filled_rectangle(x, y, x + 16, y + 16, al_map_rgb(0,0,0));

      // moves the character
      move(movement);

      // draws the moved character
      drawState(movement, state);
   }
}

void Hero::stopMotion(void) {
   movement = STILL;
}
void Hero::setMotionUp(void) {
   dir = movement = UP;
   frameCount = 0;
}
void Hero::setMotionDown(void) {
   dir = movement = DOWN;
   frameCount = 0;
}
void Hero::setMotionLeft(void) {
   dir = movement = LEFT;
   frameCount = 0;
}
void Hero::setMotionRight(void) {
   dir = movement = RIGHT;
   frameCount = 0;
}

void Hero::drawState(int direction, int step) {
   al_draw_bitmap_region(spriteSheet, step * 16, (direction - 1) * 16, 16, 16, x, y, 0);
}

void Hero::move(int direction) {
   switch(direction) {
      case DOWN:  y++; break;
      case UP:    y--; break;
      case LEFT:  x--; break;
      case RIGHT: x++; break;
   }
}