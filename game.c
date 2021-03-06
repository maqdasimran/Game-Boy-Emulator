#include "game.h"

#include <stdio.h>
#include <stdlib.h>
#include "images/startScreen.h"
#include "images/garbage.h"
#include "images/playScreen.h"
#include "images/icon.h"
#include "images/back.h"
#include "images/obstacle.h"
#include "images/flag.h"
#include "images/lostScreen.h"
#include "images/winScreen.h"
#include "images/altScreen.h"
#include "gba.h"
/* TODO: */
// Include any header files for title screen or exit
// screen images generated by nin10kit. Example for the provided garbage
// image:
// #include "images/garbage.h"

/* TODO: */
// Add any additional states you need for your app.
typedef enum {
  START,
  PLAY,
  WIN,
  LOSE,
  LOSE_TIME
} GBAState;

int main(void) {
  REG_DISPCNT = MODE3 | BG2_ENABLE;
  int value = 0;
  /* TODO: */
  // Manipulate REG_DISPCNT here to set Mode 3. //

  // Save current and previous state of button input.
  u32 previousButtons = BUTTONS;
  u32 currentButtons = BUTTONS;



  // Load initial game state
  GBAState state = START;
  Racer player;
  player.row = 120;
  player.col = 0;
  player.sprite = icon;

  while (1) {
    currentButtons = BUTTONS;  // Load the current state of the buttons
    if (KEY_JUST_PRESSED(BUTTON_SELECT, currentButtons, previousButtons)) {
        state = START;
          player.row = 120;
          player.col = 0;
          player.sprite = icon;
          value = 0;
      }

      if (value > 20) {
        state = LOSE_TIME;
      }

    /* TODO: */
    // Manipulate the state machine below as needed //
    // NOTE: Call waitForVBlank() before you draw
    waitForVBlank();
    switch (state) {
      case START:
        drawFullScreenImageDMA(startScreen);
        drawString(120, 65, "Press A to start.", BLACK);
        if (KEY_JUST_PRESSED(BUTTON_A, currentButtons, previousButtons)) {
            state = PLAY;
        }
        // state = ?
        break;
      case PLAY:
        drawFullScreenImageDMA(playScreen);
        drawImageDMA(player.row, player.col, ICON_WIDTH, ICON_HEIGHT, player.sprite);
        if (vBlankCounter % 40 == 0) {
          value++;
        }
        char time[51];
        sprintf(time, "Time: %ds", value);
        drawString(90, 90, time, WHITE);
        drawImageDMA(100,65, OBSTACLE_WIDTH , OBSTACLE_HEIGHT, obstacle);
        drawImageDMA(140,155, OBSTACLE_WIDTH , OBSTACLE_HEIGHT, obstacle);
        drawImageDMA(90,224, FLAG_WIDTH, FLAG_HEIGHT, flag);
        
        if (KEY_DOWN(BUTTON_RIGHT, currentButtons)) {
          // player.width = 16 // player.height = 16 // obstacle.width = 16 // obstacle.height = 24
          //
        
        if (((player.row >= 76 && player.row <= 124) && (player.col >= 49 && player.col <= 81)) || ((player.row >= 116 && player.row <= 164) && (player.col >= 139 && player.col <= 171 ))) {
            state = LOSE;
            break;
          }
          };

        if (KEY_DOWN(BUTTON_UP, currentButtons)) {
          if (!(player.row < 120 - ICON_HEIGHT )) {
            player.row = player.row - 1;
          }
        }

        if (KEY_DOWN(BUTTON_DOWN, currentButtons)) {
            player.row = player.row + 1;
        }

        if (KEY_DOWN(BUTTON_RIGHT, currentButtons)) {
          if ( player.col > WIDTH - ICON_WIDTH) {
            state = WIN;
            break;
          } else {
            player.col = player.col + 1;
          }
          player.sprite = icon;
        }

        if (KEY_DOWN(BUTTON_LEFT, currentButtons)) {
          if (!(player.row > HEIGHT - ICON_HEIGHT || player.col - 1> WIDTH - ICON_WIDTH || player.row < 0 || player.col - 1< 0)) {
            player.col = player.col - 1;
          }
            player.sprite = back;
        }

        // state = ?
        break;
      case WIN:
        drawFullScreenImageDMA(winScreen);
        sprintf(time, "You finished in: %ds", value);
        drawString(140, 65, time, WHITE);

        // state = ?
        break;
      case LOSE:
        drawFullScreenImageDMA(lostScreen);
        drawString(140, 65, "You hit an obstacle", WHITE);

        // state = ?
        break;

      case LOSE_TIME:
        drawFullScreenImageDMA(altScreen);
        drawString(140, 5, "Unfortunately You did not finish in 20s", WHITE);

        // state = ?
        break;
    }

    previousButtons = currentButtons;  // Store the current state of the buttons
  }

  UNUSED(previousButtons);  // You can remove this once previousButtons is used

  return 0;
}
