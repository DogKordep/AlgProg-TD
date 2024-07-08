#include "raylib.h"
#include <string.h>

#define LARGURA 600
#define ALTURA 600

int main(void){
int y = 300, x = 300;
 //char texto[50] ;//= "Pressione uma seta";//texto inicial
 //--------------------------------------------------------------------------------------
 //Inicializações
 InitWindow(LARGURA, ALTURA, "Quadrado");//Inicializa janela, com certo tamanho e título
 SetTargetFPS(60);// Ajusta a execução do jogo para 60 frames por segundo
 //--------------------------------------------------------------------------------------
 //Laço principal do jogo
 while (!WindowShouldClose()) // Detect window close button or ESC key
 {
  // Trata entrada do usuário e atualiza estado do jogo
  //----------------------------------------------------------------------------------
  if (IsKeyPressed(KEY_RIGHT)) x=x+20; //strcpy(texto,"Direita");
  if (IsKeyPressed(KEY_LEFT)) x=x-20 ;//strcpy(texto,"Esquerda");
  if (IsKeyPressed(KEY_UP)) y=y-20;//strcpy(texto,"Cima");
  if (IsKeyPressed(KEY_DOWN))y=y+20; //strcpy(texto,"Baixo");
  //----------------------------------------------------------------------------------
  // Atualiza a representação visual a partir do estado do jogo
  //----------------------------------------------------------------------------------
  BeginDrawing();//Inicia o ambiente de desenho na tela
  DrawRectangle(x, y, 20, 20, GREEN);
  ClearBackground(RAYWHITE);//Limpa a tela e define cor de fundo
  //DrawText(texto, x, y, 40, GREEN);//Desenha um texto, com posição, tamanho e cor
  EndDrawing();//Finaliza o ambiente de desenho na tela
  //----------------------------------------------------------------------------------
  if(x>600 || x<0 || y>600 || y<0)
    CloseWindow();
 }
 CloseWindow();// Fecha a janela e o contexto OpenGL
return 0;
}
