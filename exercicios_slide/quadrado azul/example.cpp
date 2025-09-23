#include <SDL2/SDL.h>
#include <iostream>

// Template para criar e usar User Events no SDL2

// 1. Definir códigos de eventos personalizados
enum CustomEventCodes {
    EVENT_MULTI_CLICK = 1,
    EVENT_TIMER_EXPIRED = 2,
    EVENT_CUSTOM_ACTION = 3
};

// 2. Função para criar um evento de usuário
SDL_Event createUserEvent(int code, void* data1 = nullptr, void* data2 = nullptr) {
    SDL_Event userEvent;
    userEvent.type = SDL_USEREVENT;           // Tipo do evento
    userEvent.user.code = code;               // Código personalizado
    userEvent.user.data1 = data1;             // Dados opcionais
    userEvent.user.data2 = data2;             // Dados opcionais
    return userEvent;
}

// 3. Função para enviar evento para a fila
void sendUserEvent(int code, void* data1 = nullptr, void* data2 = nullptr) {
    SDL_Event userEvent = createUserEvent(code, data1, data2);
    SDL_PushEvent(&userEvent);
    std::cout << "Evento enviado: código " << code << std::endl;
}

// 4. Callback de timer que envia evento
Uint32 timerCallback(Uint32 interval, void* param) {
    int* counter = static_cast<int*>(param);
    (*counter)++;
    
    // Enviar evento quando timer expira
    sendUserEvent(EVENT_TIMER_EXPIRED, param);
    
    return 0; // Não repetir o timer
}

int main() {
    // Inicializar SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0) {
        std::cerr << "Erro ao inicializar SDL: " << SDL_GetError() << std::endl;
        return 1;
    }
    
    // Criar janela
    SDL_Window* window = SDL_CreateWindow("Template User Events",
                                         SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                         400, 300, SDL_WINDOW_SHOWN);
    if (!window) {
        std::cerr << "Erro ao criar janela: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }
    
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "Erro ao criar renderer: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    
    // Variáveis para demonstração
    int clickCount = 0;
    int timerCounter = 0;
    SDL_TimerID timer = nullptr;
    
    std::cout << "=== Template User Events SDL2 ===" << std::endl;
    std::cout << "Clique com botão esquerdo para gerar eventos" << std::endl;
    std::cout << "Pressione 't' para iniciar timer" << std::endl;
    std::cout << "Pressione 'e' para enviar evento manual" << std::endl;
    std::cout << "Pressione ESC para sair" << std::endl;
    std::cout << "=================================" << std::endl;
    
    bool running = true;
    SDL_Event event;
    
    while (running) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    running = false;
                    break;
                    
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym) {
                        case SDLK_ESCAPE:
                            running = false;
                            break;
                            
                        case SDLK_t:
                            // Iniciar timer que envia evento
                            if (!timer) {
                                timer = SDL_AddTimer(2000, timerCallback, &timerCounter);
                                std::cout << "Timer iniciado (2 segundos)" << std::endl;
                            }
                            break;
                            
                        case SDLK_e:
                            // Enviar evento manual
                            sendUserEvent(EVENT_CUSTOM_ACTION, &clickCount);
                            break;
                    }
                    break;
                    
                case SDL_MOUSEBUTTONDOWN:
                    if (event.button.button == SDL_BUTTON_LEFT) {
                        clickCount++;
                        
                        // Enviar evento de múltiplo clique
                        sendUserEvent(EVENT_MULTI_CLICK, &clickCount);
                        
                        std::cout << "Clique detectado! Total: " << clickCount << std::endl;
                    }
                    break;
                    
                // 5. Processar eventos de usuário
                case SDL_USEREVENT:
                    std::cout << "=== EVENTO DE USUÁRIO RECEBIDO ===" << std::endl;
                    std::cout << "Código: " << event.user.code << std::endl;
                    std::cout << "Data1: " << event.user.data1 << std::endl;
                    std::cout << "Data2: " << event.user.data2 << std::endl;
                    
                    // Processar baseado no código
                    switch (event.user.code) {
                        case EVENT_MULTI_CLICK:
                            std::cout << "Ação: Múltiplo clique processado!" << std::endl;
                            break;
                            
                        case EVENT_TIMER_EXPIRED:
                            std::cout << "Ação: Timer expirado! Contador: " << timerCounter << std::endl;
                            break;
                            
                        case EVENT_CUSTOM_ACTION:
                            std::cout << "Ação: Evento customizado processado!" << std::endl;
                            break;
                            
                        default:
                            std::cout << "Ação: Evento desconhecido" << std::endl;
                            break;
                    }
                    std::cout << "=================================" << std::endl;
                    break;
            }
        }
        
        // Renderizar (janela simples)
        SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);
        
        SDL_Delay(16);
    }
    
    // Limpeza
    if (timer) {
        SDL_RemoveTimer(timer);
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    
    return 0;
}

/*
TEMPLATE RESUMIDO:

1. Definir códigos de eventos:
   enum CustomEventCodes { EVENT_EXAMPLE = 1 };

2. Criar evento:
   SDL_Event userEvent;
   userEvent.type = SDL_USEREVENT;
   userEvent.user.code = EVENT_EXAMPLE;
   userEvent.user.data1 = data1;
   userEvent.user.data2 = data2;

3. Enviar evento:
   SDL_PushEvent(&userEvent);

4. Processar no loop de eventos:
   case SDL_USEREVENT:
       switch (event.user.code) {
           case EVENT_EXAMPLE:
               // Processar evento
               break;
       }
       break;
*/
