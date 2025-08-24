#include <SDL2/SDL.h>

void draw_person(SDL_Renderer* renderer,int x,int y) {
    // Pernas
    SDL_RenderDrawLine(renderer, x, y + 10, x - 10, y + 20);
    SDL_RenderDrawLine(renderer, x, y + 10, x + 10, y + 20);
    // Braços
    SDL_RenderDrawLine(renderer, x, y, x - 10, y + 10);
    SDL_RenderDrawLine(renderer, x, y, x + 10, y + 10);
    // Corpo
    SDL_RenderDrawLine(renderer, x, y + 10, x, y);
    // Cabeça
    SDL_Rect r = { x-4, y-10, 10, 10 };
    SDL_RenderFillRect(renderer, &r);
}

int main( int argc, char* args[] )
{   
    SDL_Init(SDL_INIT_VIDEO);
    int TAMANHO_X = 500;
    int TAMANHO_Y = 500;
    // Criando a janela
    SDL_Window* window = SDL_CreateWindow("Pintura formas", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, TAMANHO_X, TAMANHO_Y, SDL_WINDOW_SHOWN);
    // Criando o renderizador
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    
    // Setando a cor de desenho para azul
    SDL_SetRenderDrawColor(renderer, 50, 200, 235, 0);
    SDL_RenderClear(renderer);


    SDL_Rect r = { 50, 50, 20, 20 };
    SDL_Rect chao_1  = { 0, (TAMANHO_Y / 3), 70, TAMANHO_Y }, chao_2 = { 4*(TAMANHO_X / 5), 2*(TAMANHO_Y / 3), TAMANHO_X, TAMANHO_Y };
    SDL_Rect grama_1 = { 0, (TAMANHO_Y / 3)- 10, 70, 10}, grama_2 = { 4*(TAMANHO_X / 5), 2*(TAMANHO_Y / 3) - 10, TAMANHO_X, 10 };
    SDL_Rect mar = { 70, 2*(TAMANHO_Y / 3), 4*(TAMANHO_X / 5) - 70, TAMANHO_Y - (TAMANHO_Y / 3) };
    SDL_Rect sol = { 4*TAMANHO_X / 5, TAMANHO_Y/10, 50, 50 };
    SDL_Rect poste_1 = { 30, (TAMANHO_Y / 3)- 65, 10, 55 }, poste_2 = { 4*(TAMANHO_X / 5) + 30, 2*(TAMANHO_Y / 3)- 65, 10, 55 };
    int x_pessoa_1 = 50, y_pessoa_1 = (TAMANHO_Y / 3) - 30; //boneco tem 20 de altura
    int x_pessoa_2 = 450, y_pessoa_2 = 2*(TAMANHO_Y / 3) - 30; 
    int x_pessoa_3 = 200, y_pessoa_3 = 400;


    SDL_SetRenderDrawColor(renderer, 85, 38, 23, 0); 
    SDL_RenderFillRect(renderer, &chao_2);
    SDL_RenderFillRect(renderer, &chao_1);

    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 0);
    SDL_RenderFillRect(renderer, &grama_1);
    SDL_RenderFillRect(renderer, &grama_2);


    //SDL_RenderFillRect(renderer, &r);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    draw_person(renderer, x_pessoa_1, y_pessoa_1);
    draw_person(renderer, x_pessoa_2, y_pessoa_2);

    SDL_RenderDrawLine(renderer, 30, (TAMANHO_Y / 3)- 60, 4*(TAMANHO_X / 5) + 30, 2*(TAMANHO_Y / 3)- 60);

    SDL_SetRenderDrawColor(renderer, 100, 65, 200, 0);
    SDL_RenderFillRect(renderer, &poste_1);
    SDL_RenderFillRect(renderer, &poste_2);

    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 0);
    SDL_RenderFillRect(renderer, &mar);

    SDL_SetRenderDrawColor(renderer, 255, 255, 0, 0);
    SDL_RenderFillRect(renderer, &sol);

    SDL_RenderPresent(renderer);
    
    // Esperando o usuário fechar a janela
    SDL_Event e; bool quit = false; while( quit == false ){ while( SDL_PollEvent( &e ) ){ if( e.type == SDL_QUIT ) quit = true; } }
    
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    
    return 0;
}