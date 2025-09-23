# Comportamento do Programa: Jetpack Multiclick

## Visão Geral
O programa implementa um jogo simples onde um pinguim pode "voar" usando múltiplos cliques do mouse.

## Máquina de Estados Implementada

### Estados:
- **IDLE**: Estado inicial, pinguim no chão
- **VOA**: Aguardando cliques adicionais (200ms)
- **CAI**: Período de espera expirado

### Transições:
- **IDLE → VOA**: Primeiro clique detectado
- **VOA → VOA**: Clique adicional dentro de 200ms
- **VOA → CAI**: Timeout de 200ms atingido
- **CAI → VOA**: Clique adicional dentro de 200ms
- **CAI → IDLE**: Timeout de 200ms atingido

## Comportamento do Jogo

### 1. **Sistema de Eventos**
- **EVENT_MULTI_CLICK (código 1)**: Disparado a cada clique do mouse
- **EVENT_TIME_EXPIRE (código 0)**: Disparado quando timeout de 200ms é atingido

### 2. **Mecânica de Voo**
- **Clique do mouse**: Pinguim sobe 5 pixels (`y_pinguim -= 5`)
- **Timeout (200ms)**: Pinguim desce 5 pixels (`y_pinguim += 5`) se não estiver no chão
- **Chão**: Pinguim para na posição inicial (`Y_INICIAL`)

### 3. **Fluxo de Execução**

```
1. Pinguim inicia no chão (IDLE)
2. Usuário clica → EVENT_MULTI_CLICK → pinguim sobe (WAITING)
3. Se clica novamente em <200ms → pinguim sobe mais (WAITING)
4. Após 200ms sem cliques → EVENT_TIME_EXPIRE → pinguim desce (IDLE)
5. Repete até pinguim voltar ao chão
```

### 4. **Controles**
- **Botão esquerdo do mouse**: Fazer pinguim voar
- **ESC/Fechar janela**: Sair do jogo
