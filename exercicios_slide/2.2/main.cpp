#include <SDL2/SDL.h>
#include <string>

enum CustomEventCodes {
    EVENT_DRAG_AND_DROP = 1
};

SDL_Event CreateUserEvent(int code) {
    SDL_Event user_event;
    user_event.type = SDL_USEREVENT;
    user_event.user.code = code;

    return user_event;
}

int main (int argc, char* args[]) {
    int LARGURA = 500, ALTURA = 500;
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window = SDL_CreateWindow(
        "drag and drop quadrado",
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

    int is_running = 1;
    Uint32 timeout = 50;
    std::string estado = "free"; //draging, free
    SDL_Event event;

    SDL_Rect quadrado = {0, 0, 20, 20};


    while(is_running) {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 128, 0, 128, 0);
        SDL_RenderFillRect(renderer, &quadrado);

        SDL_RenderPresent(renderer);

        Uint32 start = SDL_GetTicks();
        if (SDL_WaitEventTimeout(&event, timeout)) {
            SDL_Event drag_and_drop_event;
            switch (event.type) {
                case SDL_QUIT:
                    is_running = 0;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    if (estado == "free") {
                        //se clique está dentro do intervalo x do quadrado
                        if (!(event.button.x < quadrado.x || event.button.x > (quadrado.x + quadrado.w))) {
                            //se clique está dentro do intervalo y do quadrado
                            if (!(event.button.y < quadrado.y || event.button.y > (quadrado.y + quadrado.h))) {
                                estado = "draging";
                            }
                        }
                    }
                    break;
                case SDL_MOUSEBUTTONUP:
                    estado = "free";
                    break;
                case SDL_MOUSEMOTION:
                    if (estado == "draging") {
                        quadrado.x = event.motion.x;
                        quadrado.y = event.motion.y;
                    }
                    break;
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym) {
                        case SDLK_ESCAPE:
                            quadrado.x = 0;
                            quadrado.y = 0;
                            estado = "free";
                            break;
                    };
                    break;
            }
        }
    }


    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}