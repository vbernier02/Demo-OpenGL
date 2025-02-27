#include <GL4D/gl4duw_SDL2.h>
#include <GL4D/gl4dg.h>
#include <GL4D/gl4dh.h>
#include <SDL_image.h>
#include <stdio.h>
#include <assert.h>
#include <time.h>
#include <math.h>
#include "audioHelper.h"

#define WW 1366
#define WH 768

static void init(void);
static void draw(void);
static void sortie(void);
static float a = 0;

GLuint cpu = 0;
GLuint _sphere2 = 0;
GLuint _fond = 0;
GLuint texture[5] = { 0 };
time_t startTime;
GLfloat camerazoom = 10.0f;
GLfloat delai = 5.0;

void systeme(int state){
  
  switch(state) {
  case GL4DH_INIT:
    init();
    return;
  case GL4DH_FREE:
    sortie();
    return;
  case GL4DH_UPDATE_WITH_AUDIO:
    return;
  default:
    draw();
    return;
  }
}

void init(void){

  startTime = time(NULL);
  SDL_Surface *surface = NULL;
  SDL_GL_SetSwapInterval(1);
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glEnable(GL_DEPTH_TEST);
  _sphere2 = gl4dgGenSpheref(20, 20);
  _fond = gl4dgGenQuadf();
  cpu = gl4duCreateProgram("<vs>shaders/S6.vs", "<fs>shaders/S6.fs", NULL);
  gl4duGenMatrix(GL_FLOAT, "model");
  gl4duGenMatrix(GL_FLOAT, "view");
  gl4duGenMatrix(GL_FLOAT, "proj");
  gl4duBindMatrix("proj");
  gl4duLoadIdentityf();
  gl4duFrustumf(-1, 1, -(1.0f * WH) / WW, (1.0f * WH) / WW, 1, 1000.0f);

  glGenTextures(sizeof texture / sizeof *texture, texture);

  glBindTexture(GL_TEXTURE_2D, texture[0]);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  surface = IMG_Load("texture/rockb.tif");
  if(surface != NULL) {
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surface->w, surface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, surface->pixels);
    printf("erreur");
    SDL_FreeSurface(surface);
  }
  else{
    GLuint p = {(0xFF << 24) | 0xFF};
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, &p);
  }

  glBindTexture(GL_TEXTURE_2D, texture[1]);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  surface = IMG_Load("texture/rockw.tif");
  if(surface != NULL) {
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surface->w, surface->h, 0, GL_RGB, GL_UNSIGNED_BYTE, surface->pixels);
    SDL_FreeSurface(surface);
  }
  else{
    GLuint p = {(0xFF << 24) | 0xFF};
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, &p);
  }

  glBindTexture(GL_TEXTURE_2D, texture[2]);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  surface = IMG_Load("texture/mars.jpg");
  if(surface != NULL) {
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surface->w, surface->h, 0, GL_RGB, GL_UNSIGNED_BYTE, surface->pixels);
    SDL_FreeSurface(surface);
  }
  else{
    GLuint p = {(0xFF << 24) | 0xFF};
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, &p);
  }

  glBindTexture(GL_TEXTURE_2D, texture[3]);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  surface = IMG_Load("texture/ocean.jpeg");
  if(surface != NULL) {
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surface->w, surface->h, 0, GL_RGB, GL_UNSIGNED_BYTE, surface->pixels);
    SDL_FreeSurface(surface);
  }
  else{
    GLuint p = {(0xFF << 24) | 0xFF};
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, &p);
  }

  glBindTexture(GL_TEXTURE_2D, texture[4]);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  surface = IMG_Load("texture/fond2.jpg");
  if(surface != NULL) {
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surface->w, surface->h, 0, GL_RGB, GL_UNSIGNED_BYTE, surface->pixels);
    SDL_FreeSurface(surface);
  }
  else{
    GLuint p = {(0xFF << 24) | 0xFF};
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, &p);
  }

  
  glBindTexture(GL_TEXTURE_2D, 0);
}

void drawsystemeG(float X, float Y, int colorE, float VV){
  
  static const GLfloat blanc[] = {1.0f, 1.0f, 1.0f, 1.0f}, orange[] = {5.0f , 1.5f , 0.0f, 1.0f};
  time_t currentTime = time(NULL);
  double elapsedTime = difftime(currentTime, startTime); 

  if (elapsedTime > 8.0 + delai){
    camerazoom += 0.005f;
    if (camerazoom > 50.0f){
      camerazoom = 50.0f;
    }
  }
  
  gl4duBindMatrix("view");
  gl4duLoadIdentityf();
  gl4duLookAtf(0.0f, 0.0f, camerazoom, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
  gl4duTranslatef(0.0f + X, 0.0f + Y, 0.0);
  
  gl4duBindMatrix("model");
  gl4duLoadIdentityf();
  gl4duTranslatef(2.0f * cos(M_PI * a / (1000.0f + VV)), 2.0f * -sin(M_PI * a / (1000.0f + VV)), 0);
  gl4duRotatef(1.0f * a / M_PI, 0.0f, 1.0f, 0.0f);
  gl4duScalef(0.4f, 0.4f, 0.4f);
  gl4duSendMatrices();
  glUniform4fv(glGetUniformLocation(cpu, "couleur"), 1, orange);
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, texture[2]);
  glUniform1f(glGetUniformLocation(cpu, "tex_zoom"), 1.0f);
  glUniform1i(glGetUniformLocation(cpu, "use_tex"), 1);
  if (elapsedTime > 1.0 + delai) {
    gl4dgDraw(_sphere2);
  }

  gl4duLoadIdentityf();
  gl4duTranslatef(5.0f * cos(M_PI * a / (1200.0f + VV)), 5.0f * sin(M_PI * a / (1200.0f + VV)), 0);
  gl4duRotatef(1.5f * a / M_PI, 0.0f, 1.0f, 0.0f);
  gl4duScalef(0.5f, 0.5f, 0.5f);
  gl4duSendMatrices();
  glUniform4fv(glGetUniformLocation(cpu, "couleur"), 1, blanc);
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, texture[0]);
  glUniform1f(glGetUniformLocation(cpu, "tex_zoom"), 1.0f);  
  glUniform1i(glGetUniformLocation(cpu, "use_tex"), 1);
  if (elapsedTime > 3.0 + delai) {
    gl4dgDraw(_sphere2);
  }
  
  gl4duLoadIdentityf();
  gl4duTranslatef(3.0f * cos(M_PI * a / (1400.0f + VV)), 3.0f * -sin(M_PI * a / (1400.0f + VV)), 1);
  gl4duRotatef(0.5f * a / M_PI, 0.0f, 1.0f, 0.0f);
  gl4duScalef(0.3f, 0.3f, 0.3f);
  gl4duSendMatrices();
  glUniform4fv(glGetUniformLocation(cpu, "couleur"), 1, blanc);
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, texture[3]);
  glUniform1f(glGetUniformLocation(cpu, "tex_zoom"), 1.0f);  
  glUniform1i(glGetUniformLocation(cpu, "use_tex"), 1);
  if (elapsedTime > 5.0 + delai) {
    gl4dgDraw(_sphere2);
  }
  
  //(lune)
  gl4duLoadIdentityf();
  float OrbiteR = 0.7f;
  float OrbiteV = 0.2f;
  float LuneX = 3.0f * cos(M_PI * a / (1400.0f + VV)) + OrbiteR * cos(M_PI * a * OrbiteV / 100.0f);
  float LuneY = 3.0f *-sin(M_PI * a / (1400.0f + VV)) + OrbiteR * sin(M_PI * a * OrbiteV / 100.0f);
  float LuneZ = 1.0f;
  
  gl4duTranslatef(LuneX, LuneY, LuneZ);
  gl4duRotatef(1.0f * a / M_PI, 0.0f, 0.0f, 1.0f);
  gl4duScalef(0.1f, 0.1f, 0.1f);
  gl4duSendMatrices();
  glUniform4fv(glGetUniformLocation(cpu, "couleur"), 1, blanc);
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, texture[1]);
  glUniform1f(glGetUniformLocation(cpu, "tex_zoom"), 1.0f);
  glUniform1i(glGetUniformLocation(cpu, "use_tex"), 1);
  if (elapsedTime > 5.0 + delai) {
    gl4dgDraw(_sphere2);
  }

  glUniform4fv(glGetUniformLocation(cpu, "couleur"), 1, orange);//lumiere soleil principal
  glBindTexture(GL_TEXTURE_2D, 0);
  
  a += 1;
}

void drawsystemeM(float X, float Y, int colorE, float VV){
  
  static const GLfloat blanc[] = {1.0f, 1.0f, 1.0f, 1.0f}, orange[] = {5.0f , 1.5f , 0.0f, 1.0f};
  time_t currentTime = time(NULL);
  double elapsedTime = difftime(currentTime, startTime);

  if (elapsedTime >8.0 + delai){
    camerazoom += 0.005f;
    if (camerazoom > 50.0f){
      camerazoom = 50.0f;
    }
  }
  
  gl4duBindMatrix("view");
  gl4duLoadIdentityf();
  gl4duLookAtf(0.0f, 0.0f, camerazoom, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
  gl4duTranslatef(0.0f + X, 0.0f + Y, 0.0);
  
  gl4duBindMatrix("model");
  gl4duLoadIdentityf();
  gl4duTranslatef(2.5f * cos(M_PI * a / (1000.0f + VV)), 2.5f * -sin(M_PI * a / (1000.0f + VV)), 0);
  gl4duRotatef(0.7f * a / M_PI, 0.0f, 1.0f, 0.0f);
  gl4duScalef(0.4f, 0.4f, 0.4f);
  gl4duSendMatrices();
  glUniform4fv(glGetUniformLocation(cpu, "couleur"), 1, orange);
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, texture[2]);
  glUniform1f(glGetUniformLocation(cpu, "tex_zoom"), 1.0f);
  glUniform1i(glGetUniformLocation(cpu, "use_tex"), 1);
  gl4dgDraw(_sphere2);
  
  gl4duLoadIdentityf();
  gl4duTranslatef(5.0f * cos(M_PI * a / (1200.0f + VV)), 5.0f * sin(M_PI * a / (1200.0f + VV)), 0);
  gl4duRotatef(0.6f * a / M_PI, 0.0f, 1.0f, 0.0f);
  gl4duScalef(0.5f, 0.5f, 0.5f);
  gl4duSendMatrices();
  glUniform4fv(glGetUniformLocation(cpu, "couleur"), 1, blanc);
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, texture[0]);
  glUniform1f(glGetUniformLocation(cpu, "tex_zoom"), 1.0f);
  glUniform1i(glGetUniformLocation(cpu, "use_tex"), 1);
  gl4dgDraw(_sphere2);

  glBindTexture(GL_TEXTURE_2D, 0);
}

void drawsystemeP(float X, float Y, int colorE, float VV){
  
  static const GLfloat blanc[] = {1.0f, 1.0f, 1.0f, 1.0f};
  
  gl4duBindMatrix("view");
  gl4duLoadIdentityf();
  gl4duLookAtf(0.0f, 0.0f, camerazoom, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
  gl4duTranslatef(0.0f + X, 0.0f + Y, 0.0);
  
  gl4duBindMatrix("model");
  gl4duLoadIdentityf();
  gl4duTranslatef(4.0f * cos(M_PI * a / (1200.0f + VV)), 4.0f * -sin(M_PI * a / (1200.0f + VV)), 0);
  gl4duRotatef(1.1f * a / M_PI, 0.0f, 1.0f, 0.0f);
  gl4duScalef(0.5f, 0.5f, 0.5f);
  gl4duSendMatrices();
  glUniform4fv(glGetUniformLocation(cpu, "couleur"), 1, blanc);
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, texture[0]);
  glUniform1f(glGetUniformLocation(cpu, "tex_zoom"), 1.0f);
  glUniform1i(glGetUniformLocation(cpu, "use_tex"), 1);
  gl4dgDraw(_sphere2);
  
  glBindTexture(GL_TEXTURE_2D, 0);
}

void drawcomete(){

  static const GLfloat blanc[] = {1.0f, 1.0f, 1.0f, 1.0f};
  time_t currentTime = time(NULL);
  double elapsedTime = difftime(currentTime, startTime);

  static float t = 3.0f;
  static const float v = 0.01f;
  static const float c = 0.1f;

  GLfloat cometeX = 120.0f * cos(M_PI * t * c);
  GLfloat cometeY = -1.0f * t * t + 35.0f;
  GLfloat cometeZ = 0.0f;

  if (elapsedTime > 8.0 + delai){
    camerazoom += 0.005f;
    if (camerazoom > 50.0f){
      camerazoom = 50.0f;
    }
  }

  gl4duBindMatrix("view");
  gl4duLoadIdentityf();
  gl4duLookAtf(0.0f, 10.0f, camerazoom, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

  gl4duBindMatrix("model");
  
  gl4duLoadIdentityf();
  gl4duTranslatef(cometeX, cometeY, cometeZ);
  gl4duScalef(0.2f, 0.2f, 0.2f);
  gl4duSendMatrices();
  glUniform4fv(glGetUniformLocation(cpu, "couleur"), 1, blanc);
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, texture[0]);
  glUniform1f(glGetUniformLocation(cpu, "tex_zoom"), 1.0f);
  glUniform1i(glGetUniformLocation(cpu, "use_tex"), 1);
  if (elapsedTime > 12.0 + delai) {
    gl4dgDraw(_sphere2);
    t += v;
  }
}

void drawfond(){
  
  time_t currentTime = time(NULL);
  double elapsedTime = difftime(currentTime, startTime);

  if (elapsedTime > 5.0){
    camerazoom += 0.005f;
    if (camerazoom > 50.0f){
      camerazoom = 50.0f;
    }
  }
  gl4duBindMatrix("view");
  gl4duLoadIdentityf();
  gl4duLookAtf(0.0f, 0.0f, camerazoom, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
  
  gl4duBindMatrix("model");
  gl4duLoadIdentityf();
  gl4duScalef(50.0f, 30.0f, 30.0f);
  gl4duSendMatrices();
  
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, texture[4]);
  glUniform1f(glGetUniformLocation(cpu, "tex_zoom"), 1.0f);
  glUniform1i(glGetUniformLocation(cpu, "use_tex"), 1);
  
  gl4dgDraw(_fond); 
}

void draw(void){
 
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glUseProgram(cpu);
  //glUniform4fv(glGetUniformLocation(cpu, "couleur"), 1, rouge);
  time_t currentTime = time(NULL);
  double elapsedTime = difftime(currentTime, startTime); 

  if(elapsedTime > 8.0 + delai){
    camerazoom += 0.005f;
    if(camerazoom > 50.0f){
      camerazoom = 50.0f;
    }
  }
  
  drawfond();
  drawcomete();
  drawsystemeG(0, 0, 1, 0.0f);
  GLfloat lumpos0[] = {0.0f, 0.0f, 0.20f, 1.0f};
  glUniform4fv(glGetUniformLocation(cpu, "lumpos0"), 1, lumpos0);
  
  drawsystemeP(20, -5, 2, 230.0f);
  GLfloat lumpos1[] = {20.0f, -5.0f, 0.20f, 1.0f};
  glUniform4fv(glGetUniformLocation(cpu, "lumpos1"), 1, lumpos1);
  
  drawsystemeM(-16, -7, 3, 125.0f);
  GLfloat lumpos2[] = {-16.0f, -7.0f, 0.20f, 1.0f};
  glUniform4fv(glGetUniformLocation(cpu, "lumpos2"), 1, lumpos2);

  drawsystemeM(-36, -15, 2, 150.0f);
  GLfloat lumpos3[] = {-36.0f, -15.0f, 0.20f, 1.0f};
  glUniform4fv(glGetUniformLocation(cpu, "lumpos3"), 1, lumpos3);
  
  drawsystemeM(30, -17, 3, 80.0f);
  GLfloat lumpos4[] = {30.0f, -17.0f, 0.20f, 1.0f};
  glUniform4fv(glGetUniformLocation(cpu, "lumpos4"), 1, lumpos4);
  
  drawsystemeM(27, 20, 2, 160.0f);
  GLfloat lumpos5[] = {27.0f, 20.0f, 0.20f, 1.0f};
  glUniform4fv(glGetUniformLocation(cpu, "lumpos5"), 1, lumpos5);
  
  drawsystemeG(-29, 20, 1, 200.0f);
  GLfloat lumpos6[] = {-29.0f, 20.0f, 0.20f, 1.0f};
  glUniform4fv(glGetUniformLocation(cpu, "lumpos6"), 1, lumpos6);
  
  glUseProgram(0);

}

void sortie(void){
  
  if(texture[0]){
    glDeleteTextures(sizeof texture / sizeof * texture, texture);
    texture[0] = 0;
  }
}
