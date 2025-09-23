#include <SDL2/SDL.h>
#include <iostream>

// typedef struct SDL_CliqueTriplo
// {
    // Uint32 type;        /**< SDL_USEREVENT through SDL_LASTEVENT-1 */
    // Uint32 timestamp;   /**< In milliseconds, populated using SDL_GetTicks() */
    // Uint32 windowID;    /**< The associated window if any */
    // Sint32 code;        /**< User defined event code */
    // void *data1;        /**< User defined data pointer */
    // void *data2;        /**< User defined data pointer */
// } SDL_UserEvent;

int AUX_WaitEventTimeoutCount(SDL_Event* evt, Uint32* ms) {

    Uint32 start = SDL_GetTicks();
    int isevt = SDL_WaitEventTimeout(evt, *ms);
    Uint32 end = SDL_GetTicks();
    if (isevt)
    {
        Uint32 delta = (end > start) ? (end - start) : 1;
        *ms = (*ms > delta) ? (*ms - delta) : 0;
    }

    return isevt;
}

int main(int argc, char* args[]) {
    //VAR
    int isRunning = 1, largura = 1000, altura = 1000;
    Uint32 timeout = 100;
    Uint32 CLIQUE_TRIPLO{SDL_RegisterEvents(1)};
    SDL_Event MeuEvento{CLIQUE_TRIPLO};
    SDL_PushEvent(&MeuEvento);

    //EXEC
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* win = SDL_CreateWindow("Clique triplo",
       SDL_WINDOWPOS_UNDEFINED,
       SDL_WINDOWPOS_UNDEFINED,
       largura, altura, SDL_WINDOW_SHOWN
    );
    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, 0);
    //SDL_UserEvent userEvt;
    

    while(isRunning == 1) {
        SDL_Event evt;
        int isEvt = SDL_WaitEventTimeout(&evt, timeout);

    
        if (isEvt) {
            std::cout << "rolou evento";
            if (evt.type == SDL_QUIT) {
                isRunning = 0;
                SDL_DestroyRenderer(ren);
                SDL_DestroyWindow(win);
                SDL_Quit();
            } else if (evt.type == CLIQUE_TRIPLO) {
                std::cout << "rolou um clique triplo";
            } else if ( evt.type == SDL_MOUSEBUTTONUP) {
                
            }
        }
    }

    return 0;
}