#include <SDL2/SDL.h>

int main (int argc, char* args[])
{
    /* INICIALIZACAO */
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* win = SDL_CreateWindow("Movendo um Retângulo",
                         SDL_WINDOWPOS_UNDEFINED,
                         SDL_WINDOWPOS_UNDEFINED,
                         200, 100, SDL_WINDOW_SHOWN
                      );
    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, 0);

    /* EXECUÇÃO */
    int rx = 0, ry = 0, quadrados = 0;
    SDL_Rect
    SDL_Rect r = { 40,20, 10,10 }, r2 = {0, 0, 10, 10};
    int isRuning = 1;
    SDL_Event evt;
    while (isRuning == 1) {
        SDL_SetRenderDrawColor(ren, 0xFF,0xFF,0xFF,0x00);
        SDL_RenderClear(ren);
        SDL_SetRenderDrawColor(ren, 0x00,0x00,0xFF,0x00);
        SDL_RenderFillRect(ren, &r);
        SDL_RenderFillRect(ren, &r2);
        
        SDL_RenderPresent(ren);

        SDL_WaitEvent(&evt);
        if (evt.type == SDL_KEYDOWN) {
            switch (evt.key.keysym.sym) {
                case SDLK_UP:
                    if (r.y > 0) {
                        r.y -= 5;
                    }
                    break;
                case SDLK_DOWN:
                    if (r.y < 90) {
                        r.y += 5;
                    }
                    break;
                case SDLK_LEFT:
                    if (r.x > 0) {
                        r.x -= 5;
                    }
                    break;
                case SDLK_RIGHT:
                    if (r.x < 190) {
                        r.x += 5;
                    }
                    break;
            }
        } 
        if (evt.type == SDL_MOUSEBUTTONDOWN) {
            
            if (evt.button.x > 0 && evt.button.x < 200) {
                rx = evt.button.x;
            } else if (evt.button.x < 0) {
                rx = 5;
            } else {
                rx = 195;
            }
            if (evt.button.y > 0 && evt.button.y < 100) {
                ry = evt.button.y;
            } else if (evt.button.y < 0) {
                ry = 5;
            } else {
                ry = 95;
            }
            
            r2.x = rx;
            r2.y = ry;

            quadrados++;
            SDL_RenderPresent(ren);
            SDL_Delay(100);
        }
        if (evt.type == SDL_QUIT) {
            isRuning = 0;
        }
    }

    /* FINALIZACAO */
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
}
