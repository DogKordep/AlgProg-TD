#include "raylib.h"
#include <string.h>

#define LARGURA 800
#define ALTURA 450

int main(void){
 char texto[50] = "Pressione uma seta";//texto inicial
 //--------------------------------------------------------------------------------------
 //Inicializações
 InitWindow(LARGURA, ALTURA, "Teclas");//Inicializa janela, com certo tamanho e título
 SetTargetFPS(60);// Ajusta a execução do jogo para 60 frames por segundo
 //--------------------------------------------------------------------------------------
 //Laço principal do jogo
 while (!WindowShouldClose()) // Detect window close button or ESC key
 {
  // Trata entrada do usuário e atualiza estado do jogo
  //----------------------------------------------------------------------------------
  if (IsKeyPressed(KEY_RIGHT)) strcpy(texto,"Direita");
  if (IsKeyPressed(KEY_LEFT)) strcpy(texto,"Esquerda");
  if (IsKeyPressed(KEY_UP)) strcpy(texto,"Cima");
  if (IsKeyPressed(KEY_DOWN)) strcpy(texto,"Baixo");
  //----------------------------------------------------------------------------------
  // Atualiza a representação visual a partir do estado do jogo
  //----------------------------------------------------------------------------------
  BeginDrawing();//Inicia o ambiente de desenho na tela
  ClearBackground(RAYWHITE);//Limpa a tela e define cor de fundo
  DrawText(texto, 300, 200, 40, RED);//Desenha um texto, com posição, tamanho e cor
  EndDrawing();//Finaliza o ambiente de desenho na tela
  //----------------------------------------------------------------------------------
 }
 CloseWindow();// Fecha a janela e o contexto OpenGL
return 0;
}
