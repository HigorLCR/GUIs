#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>

void draw_person(SDL_Renderer* renderer,int x,int y, bool isArmUp=false) {
    // Pernas
    SDL_RenderDrawLine(renderer, x, y + 10, x - 10, y + 20);
    SDL_RenderDrawLine(renderer, x, y + 10, x + 10, y + 20);
    // Braços
    if (isArmUp) {
        SDL_RenderDrawLine(renderer, x, y, x + 10, y - 10);
    } else {
        SDL_RenderDrawLine(renderer, x, y, x + 10, y + 10);
    }
    SDL_RenderDrawLine(renderer, x, y, x - 10, y + 10);
    
    // Corpo
    SDL_RenderDrawLine(renderer, x, y + 10, x, y);
    // Cabeça
    filledCircleColor(renderer, x, y-5, 5, 0xFF000000); 
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


    SDL_Rect chao_1  = { 0, (TAMANHO_Y / 3), 70, TAMANHO_Y }, chao_2 = { 4*(TAMANHO_X / 5), 2*(TAMANHO_Y / 3), TAMANHO_X, TAMANHO_Y };
    SDL_Rect grama_1 = { 0, (TAMANHO_Y / 3)- 10, 70, 10}, grama_2 = { 4*(TAMANHO_X / 5), 2*(TAMANHO_Y / 3) - 10, TAMANHO_X, 10 };
    SDL_Rect mar = { 70, 4*(TAMANHO_Y / 5), 4*(TAMANHO_X / 5) - 70, TAMANHO_Y/5 };
    SDL_Rect poste_1 = { 30, (TAMANHO_Y / 3)- 65, 10, 55 }, poste_2 = { 4*(TAMANHO_X / 5) + 30, 2*(TAMANHO_Y / 3)- 65, 10, 55 };
    int x_pessoa_1 = 50, y_pessoa_1 = (TAMANHO_Y / 3) - 30; //boneco tem 20 de altura
    int x_pessoa_2 = 450, y_pessoa_2 = 2*(TAMANHO_Y / 3) - 30; 
    int x_pessoa_3 = 240, y_pessoa_3 = 228;
    Sint16 vento_x_1[4] = {200, 250, 300, 350}, vento_x_2[4] = {170, 200, 230, 260};
    Sint16 vento_y_1[4] = {100, 50, 150, 100}, vento_y_2[4] = {120, 90, 150, 120};

    //chão e grama
    SDL_SetRenderDrawColor(renderer, 85, 38, 23, 0); 
    SDL_RenderFillRect(renderer, &chao_2);
    SDL_RenderFillRect(renderer, &chao_1);

    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 0);
    SDL_RenderFillRect(renderer, &grama_1);
    SDL_RenderFillRect(renderer, &grama_2);

    //pessoas
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    draw_person(renderer, x_pessoa_1, y_pessoa_1, false);
    draw_person(renderer, x_pessoa_2, y_pessoa_2, true);

    //postes
    SDL_SetRenderDrawColor(renderer, 100, 65, 200, 0);
    SDL_RenderFillRect(renderer, &poste_1);
    SDL_RenderFillRect(renderer, &poste_2);

    //mar
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 0);
    SDL_RenderFillRect(renderer, &mar);
    draw_waves(renderer, 100, 410);
    

    //tiroleza
    arcColor(renderer, 1080, -1850, 2225, 107, 118, 0xFF40403F);
    filledCircleColor(renderer, 250, 215, 5, 0xFF0000FF);
    filledCircleColor(renderer, 250, 215, 2, 0xFF111111); 

    draw_person(renderer, x_pessoa_3, y_pessoa_3, true);

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
    
    //não usadas
    //Sint16 vx[5] = {400, 450, 480, 430, 390};
    //Sint16 vy[5] = {80, 60, 110, 140, 120};
    //filledPolygonColor(renderer, vx, vy, 5, 0xFFFF0000); // polígono vermelho preenchido
    //roundedRectangleColor(renderer, 50, 300, 150, 380, 15, 0xFF000000); // retângulo cinza com cantos arredondados
    //roundedBoxColor(renderer, 350, 300, 450, 380, 30, 0xFFFFFF00); // retângulo amarelo com cantos arredondados
    //pixelColor(renderer, 490, 490, 0xFFFFFFFF); // pixel branco no canto inferior direito

    


    SDL_RenderPresent(renderer);
    
    // Esperando o usuário fechar a janela
    SDL_Event e; bool quit = false; while( quit == false ){ while( SDL_PollEvent( &e ) ){ if( e.type == SDL_QUIT ) quit = true; } }
    
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    
    return 0;
}