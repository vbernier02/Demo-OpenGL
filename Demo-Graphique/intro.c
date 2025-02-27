#include <GL4D/gl4duw_SDL2.h>
#include <GL4D/gl4dh.h>
#include <stdio.h>
#include <assert.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

static GLuint _quadId = 0;
static GLuint _pId = 0;
static GLuint _texId = 0;

static void init(void);
static void draw(void);
static void sortie(void);

void intro(int state) {
    switch(state) {
        case GL4DH_INIT:
            init();
            break;
        case GL4DH_FREE:
            sortie();
            break;
        case GL4DH_UPDATE_WITH_AUDIO:
            break;
        default:
            draw();
            break;
    }
}

void init(void){
  
    SDL_Surface* surface = NULL;
    TTF_Font* font = NULL;
    SDL_Color color = {255, 255, 255, 0};

    _quadId = gl4dgGenQuadf();
    _pId = gl4duCreateProgram("<vs>shaders/texte.vs", "<fs>shaders/texte.fs", NULL);

    if(TTF_Init() == -1) {
        fprintf(stderr, "TTF_Init: %s\n", TTF_GetError());
        exit(2);
    }

    font = TTF_OpenFont("DejaVuSans-Bold.ttf", 128);
    if(font == NULL) {
        fprintf(stderr, "TTF_OpenFont: %s\n", TTF_GetError());
        exit(2);
    }

    surface = TTF_RenderUTF8_Blended_Wrapped(font, "Demo ap8", color, 2048);
    if(surface == NULL) {
        fprintf(stderr, "Erreur lors du TTF_RenderText\n");
        exit(2);
    }

    int screenWidth = 1366;
    int screenHeight = 768;
    int textWidth = surface->w;
    int textHeight = surface->h;
    int x = (screenWidth - textWidth) / 2;
    int y = (screenHeight - textHeight) / 2;

    SDL_Surface* finalSurface = SDL_CreateRGBSurface(0, screenWidth, screenHeight, 32, R_MASK, G_MASK, B_MASK, A_MASK);
    SDL_BlitSurface(surface, NULL, finalSurface, &(SDL_Rect){x, y, 0, 0});
    SDL_FreeSurface(surface);
    glGenTextures(1, &_texId);
    glBindTexture(GL_TEXTURE_2D, _texId);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, finalSurface->w, finalSurface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, finalSurface->pixels);

    glBindTexture(GL_TEXTURE_2D, 0);
    SDL_FreeSurface(finalSurface);
    TTF_CloseFont(font);

    gl4duGenMatrix(GL_FLOAT, "model");
    gl4duGenMatrix(GL_FLOAT, "view");
    gl4duGenMatrix(GL_FLOAT, "proj_id");
    gl4duBindMatrix("proj_id");
    gl4duLoadIdentityf();
}

void draw(void){

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(_pId);
    gl4duBindMatrix("view");
    gl4duLoadIdentityf();

    gl4duBindMatrix("model");
    gl4duLoadIdentityf();
    gl4duSendMatrices();

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, _texId);
    glUniform1i(glGetUniformLocation(_pId, "use_tex"), 1);
    gl4dgDraw(_quadId);

    glUseProgram(0);
}

void sortie(void) {
    if(_texId) {
        glDeleteTextures(1, &_texId);
        _texId = 0;
    }
}
