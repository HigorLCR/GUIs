#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <string>

int AUX_WaitEventTimeoutCount(SDL_Event* evt, Uint32* ms) {
    Uint32 start = SDL_GetTicks();
    int isevt = SDL_WaitEventTimeout(evt, *ms);
    Uint32 end = SDL_GetTicks();
    if (isevt) {
        *ms -= (end - start);
    } else {
        *ms = 500;
    }
    return isevt;
}

int main (int argc, char* args[])
{   
    /* VARIAVEIS */
    int largura = 200, altura = 200;
    int rx = 0, ry = 0, quadrados = 0;
    Uint32& timeout = *(new Uint32(500));

    SDL_Rect r = { 40,20, 10,10 }, r2 = {0, 0, 10, 10};
    int triClica_x1 = 0, triClica_y1 = 0, triClica_x2 = 10, triClica_y2 = 0, triClica_x3 = 5, triClica_y3 = 10;
    int triSeta_x1 = 10, triSeta_y1 = 0, triSeta_x2 = 20, triSeta_y2 = 0, triSeta_x3 = 15, triSeta_y3 = 10;
    int triAutonomo_x1 = 20, triAutonomo_y1 = 0, triAutonomo_x2 = 30, triAutonomo_y2 = 0, triAutonomo_x3 = 25, triAutonomo_y3 = 10;
    std::string estado_x = "direita", estado_y = "baixo";

    int isRuning = 1;

    /* INICIALIZACAO */
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* win = SDL_CreateWindow("Movendo triangulos",
                         SDL_WINDOWPOS_UNDEFINED,
                         SDL_WINDOWPOS_UNDEFINED,
                         largura, altura, SDL_WINDOW_SHOWN
                      );
    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, 0);

    /* EXECUÇÃO */
    while (isRuning == 1) {
        SDL_SetRenderDrawColor(ren, 0xFF,0xFF,0xFF,0x00);
        SDL_RenderClear(ren);
        //SDL_SetRenderDrawColor(ren, 0x00,0x00,0xFF,0x00);
        filledTrigonColor(
            ren, 
            triClica_x1, triClica_y1, 
            triClica_x2, triClica_y2, 
            triClica_x3, triClica_y3, 
            0xFF0000FF
        );
        filledTrigonColor(
            ren, 
            triSeta_x1, triSeta_y1, 
            triSeta_x2, triSeta_y2, 
            triSeta_x3, triSeta_y3, 
            0xFF00FF00
        );
        filledTrigonColor(
            ren, 
            triAutonomo_x1, triAutonomo_y1, 
            triAutonomo_x2, triAutonomo_y2, 
            triAutonomo_x3, triAutonomo_y3,
            0xFFFF0000
        );
        
        SDL_RenderPresent(ren);
        
        SDL_Event evt;

        int isevt = AUX_WaitEventTimeoutCount(&evt, &timeout);
        if (isevt) {
            //triangulo seta
            if (evt.type == SDL_KEYDOWN) {
                switch (evt.key.keysym.sym) {
                    case SDLK_UP:
                        if (triSeta_y1 - 5 > 0) {
                            triSeta_y1 -= 5;
                            triSeta_y2 -= 5;
                            triSeta_y3 -= 5;
                        }
                        break;
                    case SDLK_DOWN:
                        if (triSeta_y3 + 5 < altura) {
                            triSeta_y1 += 5;
                            triSeta_y2 += 5;
                            triSeta_y3 += 5;
                        }
                        break;
                    case SDLK_LEFT:
                        if (triSeta_x1 - 5 > 0) {
                            triSeta_x1 -= 5;
                            triSeta_x2 -= 5;
                            triSeta_x3 -= 5;
                        }
                        break;
                    case SDLK_RIGHT:
                        if (triSeta_x2 + 5 < largura) {
                            triSeta_x1 += 5;
                            triSeta_x2 += 5;
                            triSeta_x3 += 5;
                        }
                        break;
                }
            } 
            else if (evt.type == SDL_MOUSEMOTION) {
                //triangulo mouse
                triClica_x1 = evt.motion.x;
                triClica_y1 = evt.motion.y;
                triClica_x2 = evt.motion.x + 10;
                triClica_y2 = evt.motion.y;
                triClica_x3 = evt.motion.x + 5;
                triClica_y3 = evt.motion.y + 10;   
            }
            else if (evt.type == SDL_QUIT) {
                isRuning = 0;
            }
        } else {
            //triangulo autonomo
            if (estado_x == "direita" && triAutonomo_x2 + 5 < largura) {
                triAutonomo_x1 += 5;
                triAutonomo_x2 += 5;
                triAutonomo_x3 += 5;

            } else {
                estado_x = "esquerda";
            }
            if (estado_x == "esquerda" && triAutonomo_x1 - 5 > 0) {
                triAutonomo_x1 -= 5;
                triAutonomo_x2 -= 5;
                triAutonomo_x3 -= 5;

            } else {
                triAutonomo_x1 += 5;
                triAutonomo_x2 += 5;
                triAutonomo_x3 += 5;
                estado_x = "direita";
            }

            if (estado_y == "baixo" && triAutonomo_y3 + 5 < altura) {
                triAutonomo_y1 += 5;
                triAutonomo_y2 += 5;
                triAutonomo_y3 += 5;

            } else {
                estado_y = "cima";
            }
            if (estado_y == "cima" && triAutonomo_y1 - 5 > 0) {
                triAutonomo_y1 -= 5;
                triAutonomo_y2 -= 5;
                triAutonomo_y3 -= 5;

            } else {
                triAutonomo_y1 += 5;
                triAutonomo_y2 += 5;
                triAutonomo_y3 += 5;
                estado_y = "baixo";
            }
        }
    }

    /* FINALIZACAO */
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
}
