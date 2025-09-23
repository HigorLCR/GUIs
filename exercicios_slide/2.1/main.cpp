#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <assert.h>
#include <iostream>

enum CustomEventCodes {
    EVENT_TIME_EXPIRE = 0,
    EVENT_MULTI_CLICK = 1 //1 ate N
};

SDL_Event CreateUserEvent(int code) {
    SDL_Event user_event;
    user_event.type = SDL_USEREVENT;
    user_event.user.code = code;

    return user_event;
}

void draw_penguin(SDL_Renderer* renderer,SDL_Texture* img, int x_pinguim, int y_pinguim) {
    SDL_Rect pinguim = {x_pinguim, y_pinguim, 50, 50};

    SDL_RenderCopy(renderer, img, NULL, &pinguim);
}

int main (int argc, char* args[]) {
    int LARGURA = 500, ALTURA = 500;
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);

    SDL_Window* window = SDL_CreateWindow(
        "jetpack multiclick",                                 
        SDL_WINDOWPOS_UNDEFINED, 
        SDL_WINDOWPOS_UNDEFINED,
        LARGURA, 
        ALTURA, 
        SDL_WINDOW_SHOWN
    );
    SDL_Renderer* renderer = SDL_CreateRenderer(
        window, 
        -1, 
        SDL_RENDERER_ACCELERATED
    );

    int is_running = 1, click_counter = 0;
    Uint32 timeout = 200;
    SDL_Event event;

    SDL_Rect grama = { 0, ALTURA - 30, LARGURA, 10}, terra = { 0, ALTURA - 20, LARGURA, 20};
    int X_INICIAL = (LARGURA/2) - 25, Y_INICIAL = ALTURA - 80;
    int x_pinguim = X_INICIAL, y_pinguim = Y_INICIAL;

    SDL_Texture *pinguim_sentado = IMG_LoadTexture(renderer, "./imgs/sentado.webp");
    assert(pinguim_sentado != NULL);

    while(is_running) {
        
        //ceu
        SDL_SetRenderDrawColor(renderer, 50, 200, 235, 0);
        SDL_RenderClear(renderer);

        //chao
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 0);
        SDL_RenderFillRect(renderer, &grama);
        SDL_SetRenderDrawColor(renderer, 85, 38, 23, 0);
        SDL_RenderFillRect(renderer, &terra);

        //pinguim
        draw_penguin(renderer, pinguim_sentado, x_pinguim, y_pinguim);

        SDL_RenderPresent(renderer);
        Uint32 start = SDL_GetTicks();
        if (SDL_WaitEventTimeout(&event, timeout)) {
            SDL_Event multi_click_event;
            switch (event.type) {
                case SDL_QUIT:
                    is_running = 0;
                    break;

                case SDL_MOUSEBUTTONDOWN: {
                    multi_click_event = CreateUserEvent(1);
                    SDL_PushEvent(&multi_click_event);
                    break;
                }
                case SDL_USEREVENT:
                    switch (event.user.code) {
                        case 0:
                            if (y_pinguim < Y_INICIAL) {
                                y_pinguim += 5;
                            }
                            break;
                        case 1:
                            y_pinguim -= 5;
                            break;
                    }
                    timeout = 200;  
                    break;
                default:
                    timeout -= (SDL_GetTicks() - start);
                    break;

            }
        } else {
            if (click_counter > 0) {
                click_counter -= 1;
            }
            SDL_Event timeout_event = CreateUserEvent(0);
            SDL_PushEvent(&timeout_event);

            timeout = 200;
        }
    }


    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}