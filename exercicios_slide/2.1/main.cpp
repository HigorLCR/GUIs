#include <SDL2/SDL.h>

typedef struct SDL_CliqueTriplo
{
    Uint32 type;        /**< SDL_USEREVENT through SDL_LASTEVENT-1 */
    Uint32 timestamp;   /**< In milliseconds, populated using SDL_GetTicks() */
    Uint32 windowID;    /**< The associated window if any */
    Sint32 code;        /**< User defined event code */
    void *data1;        /**< User defined data pointer */
    void *data2;        /**< User defined data pointer */
} SDL_UserEvent;

int main(int argc, char* args[]) {
    
}