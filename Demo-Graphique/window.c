#include <GL4D/gl4duw_SDL2.h>
#include <GL4D/gl4dm.h>
#include <GL4D/gl4dg.h>
#include <GL4D/gl4du.h>
#include <GL4D/gl4dh.h>
#include "audioHelper.h"
#include "animations.h"

#define WW 1366
#define WH 768


static void init(void);
static void quit(void);


static GL4DHanime _animations[] = {
  { 5000, intro, NULL, NULL },
  { 32000, systeme, NULL, NULL},
  { 8000, systeme, NULL, fondu },
  { 20000, credit, NULL, NULL },
  { 0, NULL, NULL, NULL }
};

int main(int argc, char ** argv) {
  if(!gl4duwCreateWindow(argc, argv,
			 "GL4D projet",
			 15, 15, WW, WH,
			 GL4DW_SHOWN)){

    return 1;
  }
  init();
  atexit(quit);
  gl4duwDisplayFunc(gl4dhDraw);
  ahInitAudio("son/space.mp3");
  gl4duwMainLoop();
  return 0;
}

static void init(void){
  
  glClearColor(0.2f, 0.2f, 0.2f, 0.0f);
  gl4dhInit(_animations, 1366, 768, animationsInit);
}

void quit(void){
  gl4duClean(GL4DU_ALL);
}

