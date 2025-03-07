#ifndef _AUDIO_HELPER_H
#define _AUDIO_HELPER_H

#include <SDL_mixer.h>
#include <GL4D/gl4dh.h>

#ifdef __cplusplus
extern "C" {
#endif

  extern void    ahInitAudio(const char * filename);
  extern void    ahClean(void);
  extern Uint8 * ahGetAudioStream(void);
  extern int     ahGetAudioStreamLength(void);
  extern void    ahSetAudioStream(Uint8 * audioStream, int audioStreamLength);

#ifdef __cplusplus
}
#endif

#endif


