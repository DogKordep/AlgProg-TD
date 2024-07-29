#ifndef FUNCOES_H_INCLUDED
#define FUNCOES_H_INCLUDED



#endif // FUNCOES_H_INCLUDED

#define ALTURA_MAPA 30
#define LARGURA_MAPA 60

#define ALTURA_BLOCO 20
#define LARGURA_BLOCO 20

#define TAM_POPUP 200

char mapa[ALTURA_MAPA][LARGURA_MAPA];


struct pos_J
{
    float x;
    float y;
};

void carregaMapa(const char *arquivoMapa)
{
    FILE *file = fopen(arquivoMapa, "r");
    if (file == NULL)
    {
        fprintf(stderr, "Erro ao abrir o arquivo do mapa!\n");
        exit(1);
    }

    for (int i = 0; i < ALTURA_MAPA; i++)
    {
        for (int j = 0; j < LARGURA_MAPA; j++)
        {
            int caractere = fgetc(file);
            if (caractere == 'W' || caractere == ' ' || caractere == 'J' || caractere == 'M' || caractere == 'H' || caractere == 'R' || caractere == 'S' || caractere == 'D')
            {
                mapa[i][j] = caractere;
            }
            else if (caractere == '\n')
            {
                j--;
            }
        }
    }
    fclose(file);
}

void DesenhaMapa()
{
    for (int i = 0; i < ALTURA_MAPA; i++)
    {
        for (int j = 0; j < LARGURA_MAPA; j++)
        {
            if (mapa[i][j] == 'W')
            {
                DrawRectangle(j * LARGURA_BLOCO, i * ALTURA_BLOCO, LARGURA_BLOCO, ALTURA_BLOCO, GRAY);
            }
            if (mapa[i][j] == 'R')
            {
                DrawRectangle(j * LARGURA_BLOCO, i * ALTURA_BLOCO, LARGURA_BLOCO, ALTURA_BLOCO, GREEN);
            }
            if (mapa[i][j] == 'H')
            {
                DrawRectangle(j * LARGURA_BLOCO, i * ALTURA_BLOCO, LARGURA_BLOCO, ALTURA_BLOCO, BLACK);
            }
            if (mapa[i][j] == 'S')
            {
                DrawRectangle(j * LARGURA_BLOCO, i * ALTURA_BLOCO, LARGURA_BLOCO, ALTURA_BLOCO, SKYBLUE);
            }
            if (mapa[i][j] == 'M')
            {
                DrawRectangle(j * LARGURA_BLOCO, i * ALTURA_BLOCO, LARGURA_BLOCO, ALTURA_BLOCO, RED);
            }
            if (mapa[i][j] == 'D')
            {
                DrawRectangle(j * LARGURA_BLOCO, i * ALTURA_BLOCO, LARGURA_BLOCO, ALTURA_BLOCO, BROWN);
            }
        }
    }
}

void InitPosicaoJogador(struct pos_J *J)
{
    for (int i = 0; i < ALTURA_MAPA; i++)
    {
        for (int j = 0; j < LARGURA_MAPA; j++)
        {
            if (mapa[i][j] == 'J')
            {
                J->x = j * LARGURA_BLOCO;
                J->y = i * ALTURA_BLOCO;
                return;  // Encerra a busca após encontrar a posição inicial do jogador
            }
        }
    }
}

void MovimentoJogador(struct pos_J *J)
{
    if (IsKeyDown(KEY_UP) && J->y > 0 && mapa[(int)(J->y - 1)/ALTURA_BLOCO][(int)J->x/LARGURA_BLOCO] != 'W' && mapa[(int)(J->y - 1)/ALTURA_BLOCO][(int)(J->x + LARGURA_BLOCO - 1)/LARGURA_BLOCO] != 'W')
    {
        J->y -= 1;
        printf("Moving up: J.y = %f\n", J->y);
    }
    if (IsKeyDown(KEY_DOWN) && J->y < ((ALTURA_MAPA*ALTURA_BLOCO)-ALTURA_BLOCO) && mapa[(int)(J->y + ALTURA_BLOCO)/ALTURA_BLOCO][(int)J->x/LARGURA_BLOCO] != 'W' && mapa[(int)(J->y + ALTURA_BLOCO)/ALTURA_BLOCO][(int)(J->x + LARGURA_BLOCO - 1)/LARGURA_BLOCO] != 'W')
    {
        J->y += 1;
        printf("Moving down: J.y = %f\n", J->y);
    }
    if (IsKeyDown(KEY_LEFT) && J->x > 0 && mapa[(int)J->y/ALTURA_BLOCO][(int)(J->x - 1)/LARGURA_BLOCO] != 'W' && mapa[(int)(J->y + ALTURA_BLOCO - 1)/ALTURA_BLOCO][(int)(J->x - 1)/LARGURA_BLOCO] != 'W' &&  mapa[(int)(J->y + ALTURA_BLOCO - 1)/ALTURA_BLOCO][(int)(J->x - 1)/LARGURA_BLOCO] != 'D')
    {
        J->x -= 1;
        printf("Moving left: J.x = %f\n", J->x);
    }
    if (IsKeyDown(KEY_RIGHT) && J->x < ((LARGURA_MAPA*LARGURA_BLOCO)-LARGURA_BLOCO) && mapa[(int)J->y/ALTURA_BLOCO][(int)(J->x + LARGURA_BLOCO)/LARGURA_BLOCO] != 'W' && mapa[(int)(J->y + ALTURA_BLOCO - 1)/ALTURA_BLOCO][(int)(J->x + LARGURA_BLOCO)/LARGURA_BLOCO] != 'W')
    {
        J->x += 1;
        printf("Moving right: J.x = %f\n", J->x);
    }

}

void PortaTrancada (struct pos_J *J)
{
    if(mapa[(int)J->y/ALTURA_BLOCO][(int)J->x/LARGURA_BLOCO] == 'D')
    {


            DrawText("CHAVE PARA PORTA", 200, 200, 50, BLACK);
    }
}
