#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <iostream>

void draw_car(SDL_Renderer* renderer, int x, int y, std::string color="vermelho") {
    //rodas
    filledCircleColor(renderer, x + 8, y + 18, 7, 0xFF000000);
    filledCircleColor(renderer, x + 42, y + 18, 7, 0xFF000000);

    SDL_Rect corpo = {x, y, 50, 15};
    SDL_Rect teto = {x + 10, y - 10, 30, 10};
    SDL_Rect janela = {x + 13, y - 5, 10, 8}, janela2 = {x + 28, y - 5, 10, 8};
    
    int r = color == "vermelho" ? 255 : 0;
    int g = color == "verde" ? 255 : 0;
    int b = color == "azul" ? 255 : 0;

    SDL_SetRenderDrawColor(renderer, r, g, b, 255);
    //carroceria
    SDL_RenderFillRect(renderer, &corpo);
    SDL_RenderFillRect(renderer, &teto);
    SDL_SetRenderDrawColor(renderer, 200, 200, 255, 255);
    //janela
    SDL_RenderFillRect(renderer, &janela);
    SDL_RenderFillRect(renderer, &janela2);
}

void draw_endline(SDL_Renderer* renderer, int x, int y, int mode) {
    SDL_Rect bloco1 = {x, y, 20, 20}, bloco2 = {x + 20, y, 20, 20};

    if (mode == 1) {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderFillRect(renderer, &bloco1);
        
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderFillRect(renderer, &bloco2);
    } else {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderFillRect(renderer, &bloco1);
        
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderFillRect(renderer, &bloco2);
    }  
}

void renderizarTexto(SDL_Renderer* renderer, const std::string& texto, int x, int y) {
    // Configurações padrão
    SDL_Color cor = {255, 255, 255};  // Branco
    TTF_Font* fonte = TTF_OpenFont("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf", 24);
    
    if (!fonte) {
        std::cerr << "Erro ao carregar fonte: " << TTF_GetError() << std::endl;
        return;
    }

    // Criar superfície com o texto
    SDL_Surface* superficie = TTF_RenderText_Solid(fonte, texto.c_str(), cor);
    if (!superficie) {
        std::cerr << "Erro ao renderizar texto: " << TTF_GetError() << std::endl;
        TTF_CloseFont(fonte);
        return;
    }

    // Criar textura a partir da superfície
    SDL_Texture* textura = SDL_CreateTextureFromSurface(renderer, superficie);
    if (!textura) {
        std::cerr << "Erro ao criar textura: " << SDL_GetError() << std::endl;
        SDL_FreeSurface(superficie);
        TTF_CloseFont(fonte);
        return;
    }

    // Criar retângulo de destino com a posição especificada
    SDL_Rect destino = {x, y, superficie->w, superficie->h};

    // Renderizar a textura
    SDL_RenderCopy(renderer, textura, NULL, &destino);

    // Liberar recursos
    SDL_DestroyTexture(textura);
    SDL_FreeSurface(superficie);
    TTF_CloseFont(fonte);
}

int main (int argc, char* args[])
{   
    /* INICIALIZACAO */
    int largura = 1000, altura = 500;

    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();
    SDL_Window* win = SDL_CreateWindow("Corrida de carros",
       SDL_WINDOWPOS_UNDEFINED,
       SDL_WINDOWPOS_UNDEFINED,
       largura, altura, SDL_WINDOW_SHOWN
    );                
    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, 0);
    

    

    /* VARIAVEIS */    
    int timeout = 100;
    int x_carro_1 = 0, y_carro_1 = 100;
    int x_carro_2 = 0, y_carro_2 = 200;
    int x_carro_3 = 0, y_carro_3 = 300;
    int vencedor = -1;

    int isRunning = 1, isRaceFinished = 0; 
    
    /* EXECUÇÃO */
    while (isRunning == 1) {
        SDL_SetRenderDrawColor(ren, 0xAA,0xAA,0xAA,0x00);
        SDL_RenderClear(ren);

        if (isRaceFinished == 1) {
            std::string mensagem;
            if (vencedor == 1) mensagem = "Carro Vermelho venceu!";
            else if (vencedor == 2) mensagem = "Carro Verde venceu!";
            else if (vencedor == 3) mensagem = "Carro Azul venceu!";
            else mensagem = "Nenhum carro venceu!";
            renderizarTexto(ren, mensagem, 250, 250);
        }
        

        for(int i = 0; i < largura; i += 20) {
            draw_endline(ren, 900, i, (i/20) % 2);
        }

        draw_car(ren, x_carro_1, y_carro_1, "vermelho");
        draw_car(ren, x_carro_2, y_carro_2, "verde");
        draw_car(ren, x_carro_3, y_carro_3, "azul");

        SDL_RenderPresent(ren);
        
        SDL_Event evt;
        Uint32 inicio_tick = SDL_GetTicks();
        int isevt = SDL_WaitEventTimeout(&evt, timeout);
        if (isevt) {
            timeout -= (SDL_GetTicks() - inicio_tick);
            //triangulo seta
            if (evt.type == SDL_KEYDOWN) {
                switch (evt.key.keysym.sym) {
                    case SDLK_LEFT:
                        if (x_carro_1 >= 0 && x_carro_1 <= 850) {
                            x_carro_1 -= 10;
                        }
                        break;
                    case SDLK_RIGHT:
                        if (x_carro_1 <= 850) {
                            x_carro_1 += 10;
                        } else {
                            if (vencedor == -1) {
                                vencedor = 1;
                            }
                        }
                        break;
                }
            } 
            else if (evt.type == SDL_MOUSEMOTION) {
                //triangulo mouse
                if (x_carro_2 <= 850) {
                    x_carro_2 = evt.motion.x;
                } else {
                    if (vencedor == -1) {
                        vencedor = 2;
                    }
                }
            }
            else if (evt.type == SDL_QUIT) {
                isRunning = 0;
            }
        } else {
            timeout = 100;
            if (x_carro_3 <= 850) {
                x_carro_3 += 10;
            } else {
                if (vencedor == -1) {
                    vencedor = 3;
                }
            }

            if (isRaceFinished == 1) {
                SDL_Delay(2000);
                isRaceFinished = 0;
                x_carro_1 = 0;
                x_carro_2 = 0;
                x_carro_3 = 0;
                vencedor = -1;
            }

            if (x_carro_1 > 850 && x_carro_2 > 850 && x_carro_3 > 850) {
                isRaceFinished = 1;
            }
        }
    }

    /* FINALIZACAO */
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    TTF_Quit();
    SDL_Quit();
}
