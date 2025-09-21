#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <assert.h>
#include <iostream>
using namespace std;

int AUX_WaitEventTimeoutCount(SDL_Event* evt, Uint32* ms) {
    int isevt = SDL_WaitEventTimeout(evt, *ms);
    
    return isevt;
}

void draw_penguin(SDL_Renderer* renderer,SDL_Texture* img, int x_pinguim, int y_pinguim) {
    SDL_Rect pinguim = {x_pinguim, y_pinguim, 50, 50};

    SDL_RenderCopy(renderer, img, NULL, &pinguim);
}

void draw_cloud(SDL_Renderer* renderer, int x, int y) {
    filledCircleColor(renderer, x + 25, y + 5, 15, 0xFFFFFFFF); 
    filledEllipseColor(renderer, x, y + 20, 40, 20, 0xFFFFFFFF); 
    filledEllipseColor(renderer, x + 50, y + 20, 30, 15, 0xFFFFFFFF); 
}

void draw_waves(SDL_Renderer* renderer, int x, int y) {
    filledEllipseColor(renderer, x + 10, y - 5, 40, 20, 0xFFFF0000);
    filledEllipseColor(renderer, x + 70, y - 5, 40, 20, 0xFFFF0000);
    filledEllipseColor(renderer, x + 130, y - 5, 40, 20, 0xFFFF0000);
    filledEllipseColor(renderer, x + 200, y - 5, 40, 20, 0xFFFF0000);
    filledEllipseColor(renderer, x + 260, y - 5, 40, 20, 0xFFFF0000);
}

void draw_fish(SDL_Renderer* renderer, int x, int y) {
    filledEllipseColor(renderer, x-5, y, 15, 5, 0xFF0255C9); 
    filledTrigonColor(renderer, x - 20, y, x - 30, y - 5, x - 30, y + 5, 0xFF00691C); 
    filledCircleColor(renderer, x + 5, y - 2, 2, 0xFF000000); 
}

void draw_ladder(SDL_Renderer* renderer, int x, int y) {
    thickLineColor(renderer, x, y, x, y + 50, 3, 0xFF1A72B0);
    thickLineColor(renderer, x + 10, y, x + 10, y + 50, 3, 0xFF1A72B0);
    for (int i = 0; i <= 4; i++) {
        thickLineColor(renderer, x, y - (i * -10), x + 10, y - (i * -10), 3, 0xFF1A72B0);      
    }
}

int main( int argc, char* args[] )
{   
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);

    int TAMANHO_X = 500;
    int TAMANHO_Y = 500;
    int isRuning = 1;
    Uint32& timeout = *(new Uint32(50));

    // Criando a janela
    SDL_Window* window = SDL_CreateWindow("Pintura formas", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, TAMANHO_X, TAMANHO_Y, SDL_WINDOW_SHOWN);
    // Criando o renderizador
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    
    
    SDL_Rect chao_1  = { 0, (TAMANHO_Y / 3), 70, TAMANHO_Y }, chao_2 = { 4*(TAMANHO_X / 5), 2*(TAMANHO_Y / 3), TAMANHO_X, TAMANHO_Y };
    SDL_Rect grama_1 = { 0, (TAMANHO_Y / 3)- 10, 70, 10}, grama_2 = { 4*(TAMANHO_X / 5), 2*(TAMANHO_Y / 3) - 10, TAMANHO_X, 10 };
    SDL_Rect mar = { 70, 4*(TAMANHO_Y / 5), 4*(TAMANHO_X / 5) - 70, TAMANHO_Y/5 };
    SDL_Rect poste_1 = { 30, (TAMANHO_Y / 3)- 65, 10, 55 }, poste_2 = { 4*(TAMANHO_X / 5) + 30, 2*(TAMANHO_Y / 3)- 65, 10, 55 };
    float tirolesa_x = 110, tirolesa_y = 155; 
    std::string estado_pessoa = "tirolesa"; // "tirolesa", "caindo", "nadando", "escada"
    std::string estado_tirolesa = "ocupada"; // "pronta", "ocupada", "indisponivel"
    Sint16 vento_x_1[4] = {200, 250, 300, 350}, vento_x_2[4] = {170, 200, 230, 260};
    Sint16 vento_y_1[4] = {100, 50, 150, 100}, vento_y_2[4] = {120, 90, 150, 120};
    
    int x_pinguim = 73, y_pinguim = 155;
    SDL_Texture* pinguim_acenando = IMG_LoadTexture(renderer, "./imgs/acenando.webp");
    SDL_Texture* pinguim_caindo = IMG_LoadTexture(renderer, "./imgs/caindo.webp");
    assert(pinguim_acenando != NULL);
    assert(pinguim_caindo != NULL);
    

    while (isRuning == 1) {
        // Setando a cor de desenho para azul
        SDL_SetRenderDrawColor(renderer, 50, 200, 235, 0);
        SDL_RenderClear(renderer);
        
        //chão e grama
        SDL_SetRenderDrawColor(renderer, 85, 38, 23, 0); 
        SDL_RenderFillRect(renderer, &chao_2);
        SDL_RenderFillRect(renderer, &chao_1);

        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 0);
        SDL_RenderFillRect(renderer, &grama_1);
        SDL_RenderFillRect(renderer, &grama_2);

        //escada
        draw_ladder(renderer, 100, 150);
        draw_ladder(renderer, 100, 200);
        draw_ladder(renderer, 100, 250);
        draw_ladder(renderer, 100, 300);
        draw_ladder(renderer, 100, 350);

        
        //postes
        SDL_SetRenderDrawColor(renderer, 100, 65, 200, 0);
        SDL_RenderFillRect(renderer, &poste_1);
        SDL_RenderFillRect(renderer, &poste_2);

        //mar
        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 0);
        SDL_RenderFillRect(renderer, &mar);
        draw_waves(renderer, 100, 410);
    

        //tirolesa
        arcColor(renderer, 1080, -1850, 2225, 107, 118, 0xFF40403F);
        filledCircleColor(renderer, tirolesa_x, tirolesa_y, 5, 0xFF0000FF);
        filledCircleColor(renderer, tirolesa_x, tirolesa_y, 2, 0xFF111111);

        //vento
        bezierColor(renderer, vento_x_1, vento_y_1, 4, 100, 0xFFFFFFFF);
        bezierColor(renderer, vento_x_2, vento_y_2, 4, 100, 0xFFFFFFFF);

        //sol
        filledCircleColor(renderer, 420, 80, 40, 0xFF00FFFF); 

        //nuvens
        draw_cloud(renderer, 100, 50);
        draw_cloud(renderer, 250, 30);

        //bandeira
        thickLineColor(renderer, 480, 200, 480, 320, 6, 0xFFAAAAAA);
        filledTrigonColor(renderer, 477, 200, 450, 210, 477, 220, 0xFF0000FF);

        //peixes
        draw_fish(renderer, 150, 450);
        draw_fish(renderer, 300, 470);

        //pessoas
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        draw_penguin(renderer, (estado_pessoa == "tirolesa" ? pinguim_acenando : pinguim_caindo), x_pinguim, y_pinguim);

        
        SDL_RenderPresent(renderer);
        SDL_Event evt;

        Uint32 start = SDL_GetTicks();
        int isevt = AUX_WaitEventTimeoutCount(&evt, &timeout);
        if (evt.type == SDL_MOUSEMOTION) continue;
        if (isevt) {
            if (evt.type == SDL_KEYDOWN) {
                switch (evt.key.keysym.sym) {
                    case SDLK_UP:
                        if (estado_pessoa == "escada") {
                            //sobe a escada
                            y_pinguim = y_pinguim - 10;

                            if (y_pinguim <= 155 && estado_tirolesa == "pronta") {
                                estado_pessoa = "tirolesa";
                                estado_tirolesa = "ocupada";
                            }
                        }
                        break;
                    case SDLK_DOWN:
                        if (estado_pessoa == "escada") {
                            //sobe a escada
                            y_pinguim = y_pinguim + 10;
                                        
                            if (y_pinguim >= 410) {
                                estado_pessoa = "nadando";
                            }
                        }
                        break;
                    case SDLK_LEFT:
                        if (estado_pessoa == "nadando") {
                            //nada de volta
                            x_pinguim = x_pinguim - 5;

                            if (x_pinguim <= 73) {
                                estado_pessoa = "escada";
                            }
                        }
                        break;
                    case SDLK_RIGHT:
                        if (estado_pessoa == "nadando") {
                            //nada de volta
                            x_pinguim = x_pinguim + 5;
                        }
                        break;
                }
            }
            else if (evt.type == SDL_QUIT) {
                isRuning = 0;
            }
            Uint32 end = SDL_GetTicks();
            timeout -= (end - start);
        } else {
            if (estado_pessoa == "tirolesa") {
                //desce tirolesa
                x_pinguim = x_pinguim + 5;
                y_pinguim = y_pinguim + 2;
                
                tirolesa_x = tirolesa_x + 5;
                tirolesa_y = tirolesa_y + 2;
                
                if (x_pinguim >= 350) {
                    estado_pessoa = "caindo";
                }
            } else if (estado_pessoa == "caindo") {
                //cai na água
                
                y_pinguim = y_pinguim + 10;
            
                if (y_pinguim >= 410) {
                    estado_pessoa = "nadando";
                }
                if (estado_tirolesa == "ocupada") {
                    estado_tirolesa = "indisponivel";
                }
            } 
            if (estado_tirolesa == "indisponivel") {
                tirolesa_x = tirolesa_x - 5;
                tirolesa_y = tirolesa_y - 2;

                if (tirolesa_x <= 110) {
                    estado_tirolesa = "pronta";
                }
            }
            timeout = 50;
        }
    }
    
    SDL_DestroyTexture(pinguim_acenando);
    SDL_DestroyTexture(pinguim_caindo);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    
    return 0;
}