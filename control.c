// sdl-jstest - Joystick Test Program for SDL
// Copyright (C) 2007 Ingo Ruhnke <grumbel@gmail.com>
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
// 02111-1307, USA.
//
//
// Modified by Rosangélica
// 05 feb 2017

#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>


void print_joystick_info(int joy_idx, SDL_Joystick* joy)
{
  printf("Joystick Name:     '%s'\n", SDL_JoystickName(joy_idx));
  printf("Joystick Number:   %2d\n", joy_idx);
  printf("Number of Axes:    %2d\n", SDL_JoystickNumAxes(joy));
  printf("Number of Buttons: %2d\n", SDL_JoystickNumButtons(joy));
  printf("Number of Hats:    %2d\n", SDL_JoystickNumHats(joy));
  printf("Number of Balls:   %2d\n", SDL_JoystickNumBalls(joy));
  printf("\n");
}


int main(int argc, char** argv){

  // FIXME: We don't need video, but without it SDL will fail to work in SDL_WaitEvent()
  if(SDL_Init(SDL_INIT_TIMER | SDL_INIT_VIDEO | SDL_INIT_JOYSTICK) < 0)
  {
    fprintf(stderr, "Unable to init SDL: %s\n", SDL_GetError());
    exit(1);
  }
  else
  {
    atexit(SDL_Quit);
///////////////////////////////
    int joy_idx=0;

    SDL_Joystick* joy = SDL_JoystickOpen(joy_idx);
    if (!joy)
    {
      fprintf(stderr, "Unable to open joystick %d\n", joy_idx);
    }
    else
    {
      print_joystick_info(joy_idx, joy);

      printf("Entering joystick test loop, press Ctrl-c to exit\n");
      int quit = 0;
      SDL_Event event;
      int valorXanterior=0;
      int valorYanterior=0;

      while(!quit && SDL_WaitEvent(&event))
      {
        switch(event.type)
        {
          case SDL_JOYAXISMOTION:
            if(event.jaxis.axis ==0  && event.jaxis.value != valorXanterior){
                printf("SDL_JOYAXISMOTION: joystick: %d axis: %d value: %d\n",
                       event.jaxis.which, event.jaxis.axis, event.jaxis.value);
                valorXanterior=event.jaxis.value;
            }

            else if(event.jaxis.axis ==5  && event.jaxis.value != valorYanterior){
               printf("SDL_JOYAXISMOTION: joystick: %d axis: %d value: %d\n",
                      event.jaxis.which, event.jaxis.axis, event.jaxis.value);
               valorYanterior=event.jaxis.value;
            }
            break;

          case SDL_JOYBUTTONDOWN:
            printf("SDL_JOYBUTTONDOWN: joystick: %d button: %d state: %d\n",
                   event.jbutton.which, event.jbutton.button, event.jbutton.state);
            break;
          case SDL_JOYBUTTONUP:
            printf("SDL_JOYBUTTONUP: joystick: %d button: %d state: %d\n",
                   event.jbutton.which, event.jbutton.button, event.jbutton.state);
            break;

          case SDL_JOYHATMOTION:
            printf("SDL_JOYHATMOTION: joystick: %d hat: %d value: %d\n",
                   event.jhat.which, event.jhat.hat, event.jhat.value);
            break;

          case SDL_JOYBALLMOTION:
            printf("SDL_JOYBALLMOTION: joystick: %d ball: %d x: %d y: %d\n",
                   event.jball.which, event.jball.ball, event.jball.xrel, event.jball.yrel);
            break;

          case SDL_QUIT:
            quit = 1;
            printf("Recieved interrupt, exiting\n");
            break;

          default:
            fprintf(stderr, "Error: Unhandled event type: %d\n", event.type);
            break;
        }
      }
      SDL_JoystickClose(joy);

    }
  }
  return 0;
}

/* EOF */
