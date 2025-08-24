#include <SDL2/SDL.h>

int main( int argc, char* args[] )
{
    SDL_Init(SDL_INIT_VIDEO);
    
    // Criando a janela
    SDL_Window* window = SDL_CreateWindow("Pintura formas", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);
    
    // Criando o renderizador
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    
    // Setando a cor de desenho para azul
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    // Limpando a tela com a cor azul
    SDL_RenderClear(renderer);
    // Atualizando a tela
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    SDL_Rect r = { 50, 50, 20, 20 };
    SDL_RenderFillRect(renderer, &r);
    SDL_RenderPresent(renderer);
    SDL_Delay(5000);
    
    // Esperando o usuário fechar a janela
    //SDL_Event e; bool quit = false; while( quit == false ){ while( SDL_PollEvent( &e ) ){ if( e.type == SDL_QUIT ) quit = true; } }
    
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    
    return 0;
}