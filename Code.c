
//BIBLIOTECAS---------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL_ttf.h>
#include <time.h>
#include <string.h>
//CONSTANTES----------------------------------------------------------------------------------
#define TEMPOLIMITE 6
#define FPS 25
#define PAREDE 1
#define BLOCO 2
#define BOMBA 3
#define SAIDA 5
#define LARGURA 800
#define ALTURA  600
#define BPP       0


SDL_Surface * tela, * fundo, * parede, * direita, * esquerda, * baixo, * cima , * bloco, * bomba, * morte, *i3_cima, *i3_baixo, *i3_esquerda, *i3_direita, *explosao_bomba, *tempo,*introducao,*seta,*ponto;
SDL_Surface * botoes, *numGG, *trans,*saida,*vida,*player,*finn,*manual,*num;
    SDL_Event evento, eventomenu; /* para os eventos */
    SDL_Rect destino,anima[8], inimigo3[4],bomba1[6],destino_bomba,rect_explosao[7],tempoJogo[11],tempoMin,tempopont,tempoSe1,tempoSe2,intro[41],rectsaida,rectpontos;
    SDL_Rect asaida, numeros[10],destbotoes, destseta[4],explo[8][4], destexplo[5],NumerosGG[10],numerofase,pontos[3],liferect,blitaPonto[8];
    int coluna_atual1cb = 1, linha_atual1cb = 1, fim=0, linha_atual2cb = 1, coluna_atual2cb = 1, pontuacao[5],score;
    int coluna_atual1de = 1, linha_atual1de = 1, linha_atual2de = 1, coluna_atual2de = 1, linha_atual3de = 1;
    int linha_bomba, coluna_bomba, tempo_bomba, bomba_ativa=0,passo_h,passo_v = 0; //variaveis da bomba
    int morreu=0, posicao, key, life=3;
    int morreuI[5], resu=0,gameover=0;
    int linhasaida,colunasaida;
    int temp_key = 2,fase=1,lado[5],posi[5];
    int  contI[5],totalDePontos[8];
    int tempoI=0, t=0,contadorInimigo;
    int s1=5,s2=9,m=5;
    int contcima, contbaixo, contesquerda, contdireita, explodindo;
    int telajogo=0,telamenu=0, telaintro=1, telainstru=0,telascore=0,telafase=0;
    SDL_Rect destinoI0, destinoI1,destinoI2, destinoI3,destinoI4;
    TTF_Font *fonte;
/* O Mapa */
    int mapa[13][20];

void pega_mapa()
{

        int indice_i = 0, indice_j = 0;
        FILE * arquivo;
        arquivo = fopen("file.txt","r");

        for(int i=0; i<fase;i++)
        {

         	for (indice_i = 0; indice_i < 13; indice_i++)
            {
			//indice_j = 0;
                for (indice_j = 0; indice_j < 20; indice_j++)
                {
                  fscanf(arquivo,"%d", &mapa[indice_i][indice_j]);
                }
            }
        }
   fclose(arquivo);
    }
/*==========================FUNCOES==========================*/
/* Funcao que controla o fps */
void controla_fps ( int tempo_inicial )
{
		int fps = 1000/FPS; // converte 60 FPS para milissegundos
		int tempo_agora = SDL_GetTicks() - tempo_inicial;

		if(tempo_agora < fps)
			SDL_Delay(fps - tempo_agora);
	}

/* Funcao de inicializacao */
int carrega_imagens ()
{
/* Carrega as Imagens */

        /*fonte = TTF_OpenFont("fonte\pixel.ttf",20);
 	if(fonte == NULL)
    {
    	printf("Não carregou a fonte.");
    	return 0;
    }*/

        num= IMG_Load("numbers.png");
        if (numeros == NULL)
        {
            printf("Não carregou numebers.png\n");
            return 0;
        }

        manual = IMG_Load("manual.png");
        if (manual == NULL)
        {
            printf("Não carregou manual.png\n");
            return 0;
        }
         finn = IMG_Load("fim.png");
        if (finn == NULL)
        {
            printf("Não carregou fim.png\n");
            return 0;
        }

        vida = IMG_Load("life.png");
        if (vida == NULL)
        {
            printf("Não carregou life.png\n");
            return 0;
        }
        saida = IMG_Load("saida.png");
        if (saida == NULL)
        {
            printf("Não carregou saida.png\n");
            return 0;
        }
        trans = IMG_Load("transicao.png");
        if (trans == NULL)
        {
            printf("Não carregou transicao.png\n");
            return 0;
        }
        numGG = IMG_Load("numbersGG.png");
        if (numGG == NULL)
        {
            printf("Não carregou numbersGG.png\n");
            return 0;
        }
        botoes = IMG_Load("botoes.png");
        if (botoes == NULL)
        {
            printf("Não carregou botoes.png\n");
            return 0;
        }
        seta = IMG_Load("seta.png");
        if (seta == NULL)
        {
            printf("Não carregou seta.png\n");
            return 0;
        }
        introducao = IMG_Load("introducao.png");
        if (introducao == NULL)
        {
            printf("Não carregou introducao.png\n");
            return 0;
        }
        tempo = IMG_Load("time.png");
        if (tempo == NULL)
        {
            printf("Não carregou time.bmp\n");
            return 0;
        }

        explosao_bomba = IMG_Load("explosao.png");
        if (explosao_bomba == NULL)
        {
            printf("Não carregou explosao_bomba.bmp\n");
            return 0;
        }

		i3_baixo = IMG_Load("inimigo3Baixo.png");
        if (i3_baixo == NULL)
        {
            printf("Não carregou inimigo 3 baixo.bmp\n");
            return 0;
        }

        i3_cima = IMG_Load("Inimigo3Cima.png");
        if (i3_cima == NULL)
        {
            printf("Não carregou inimigo 3 cima.bmp\n");
            return 0;
        }

        i3_direita = IMG_Load("Inimigo3Direita.png");
        if (i3_direita == NULL)
        {
            printf("Não carregou inimigo 3 direita.bmp\n");
            return 0;
        }

        i3_esquerda = IMG_Load("Inimigo3Esquerda.png");
        if (i3_esquerda == NULL)
        {
            printf("Não carregou inimigo 3 esquerda.bmp\n");
            return 0;
        }

		parede = IMG_Load("parede.png");
        if (parede == NULL)
        {
            printf("Não carregou parede.bmp\n");
            return 0;
        }

        cima = IMG_Load("cima.png");
        if (cima == NULL)
        {
            printf("não carregou cima.png\n");
             return 0;
        }

        baixo = IMG_Load("baixo.png");
         if (baixo == NULL)
         {
            printf("não carregou baixo.png\n");
             return 0;
         }
        direita = IMG_Load("direita.png");
         if (direita == NULL)
         {
             printf("não carregou direita.png\n");
             return 0;
         }

        esquerda = IMG_Load("esquerda.png");
         if (esquerda == NULL)
         {
            printf("não carregou esquerda.png\n");
            return 0;
         }

		fundo = IMG_Load("Cenario.png");
        if (fundo == NULL)
        {
            printf("Não carregou fundo.bmp\n");
			return 0;
        }

        bloco = IMG_Load("bloco.png");
        if (bloco == NULL)
        {
            printf("Não carregou bloco.bmp\n");
			return 0;
        }

        bomba = IMG_Load("bomba.png");
        if (bomba == NULL)
        {
            printf("Não carregou bomba.png\n");
			return 0;
        }

      /*  morte = IMG_Load("morte.png");
        if (morte == NULL)
        {
            printf("Não carregou morte.png\n");
			return 0;
        }*/

		return 1;
	}

int trocafase()
{
    fundo = IMG_Load("Cenario1.png");
        if (fundo == NULL)
        {
            printf("Não carregou fundo.bmp\n");
			return 0;
        }
    bloco = IMG_Load("bloco1.png");
        if (bloco == NULL)
        {
            printf("Não carregou bloco.bmp\n");
			return 0;
        }
    parede = IMG_Load("parede1.png");
        if (parede == NULL)
        {
            printf("Não carregou parede.bmp\n");
            return 0;
        }

}

	 int colisao(SDL_Rect A, SDL_Rect B)//novo
{
    //The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    //Calculate the sides of rect A
    leftA = A.x;
    rightA = A.x + A.w;
    topA = A.y;
    bottomA = A.y + A.h;

    //Calculate the sides of rect B
    leftB = B.x;
    rightB = B.x + B.w;
    topB = B.y;
    bottomB = B.y + B.h;

    //If any of the sides from A are outside of B
    if( bottomA <= topB )
    {
        return 0;
    }

    if( topA >= bottomB )
    {
        return 0;
    }

    if( rightA <= leftB )
    {
        return 0;
    }

    if( leftA >= rightB )
    {
        return 0;
    }

    //If none of the sides from A are outside B
    return 1;


}


 int retorna_coordenada(int li,int co)
    {
        int v=1;

//        for(n=0;n<4;n++)
       // {


           // printf("%d\n",contI[contadorInimigo]);

                srand( (unsigned)time(NULL) );
                lado[contadorInimigo]=rand()%4;
               // lado[contadorInimigo]=3;
                // printf("%d\n",lado);

                //printf("%d:%d\n",contI[contadorInimigo],lado);

            if(lado[contadorInimigo]==0)
            {



                if(mapa[li-1][co]==0)
                {

                    return 0;

                }

            else
                    return 5;
            }


            if(lado[contadorInimigo]==1)
            {



                if(mapa[li][co+1]==0)
                {
                    return 1;

                }

            else
                    return 5;
            }

           if(lado[contadorInimigo]==2)
            {



                if(mapa[li+1][co]==0)
                {
                    return 2;

                }
            else
                    return 5;
            }



            if(lado[contadorInimigo]==3)
            {



                if(mapa[li][co-1]==0)
                {
                    return 3;

                }


            else
                    return 5;
            }







    }


    void blita_inimigo(SDL_Rect *inimigo){
        int cont=0, colunai, linhai,coli=0;

        colunai=(inimigo->x)/40;
        linhai=(inimigo->y-90)/40;
        //mapa[linhai][colunai]=7;



        if(morreuI[contadorInimigo]==0){

            if(contI[contadorInimigo]==0 ){
            posi[contadorInimigo]=retorna_coordenada(linhai,colunai);
            mapa[linhai][colunai]=7;
            if(mapa[linhai+1][colunai]==7)
                mapa[linhai+1][colunai]=0;
            if(mapa[linhai-1][colunai]==7)
                mapa[linhai-1][colunai]=0;
            if(mapa[linhai][colunai+1]==7)
                mapa[linhai][colunai+1]=0;
            if(mapa[linhai][colunai-1]==7)
                mapa[linhai][colunai-1]=0;
            //printf("entrou\n");
            }

            if(posi[contadorInimigo]==5)
            {
                SDL_BlitSurface(i3_baixo, &inimigo3[0], tela,inimigo);
                contI[contadorInimigo]+=1;

            }
            if(posi[contadorInimigo]==0)
            {


                inimigo->y -= 4;

                SDL_BlitSurface(i3_cima, &inimigo3[cont], tela,inimigo);


                cont++;
                if (cont==4)
                {
                    cont=0;
                }
                contI[contadorInimigo]+=1;
            }
            if(posi[contadorInimigo]==1)
            {
                inimigo->x += 4;
                SDL_BlitSurface(i3_direita, &inimigo3[cont], tela,inimigo);

                cont++;
                if (cont==4)
                    cont=0;
                contI[contadorInimigo]+=1;
            }
            if(posi[contadorInimigo]==2)
            {
                inimigo->y += 4;
                SDL_BlitSurface(i3_baixo, &inimigo3[cont], tela,inimigo);

                cont++;
                if (cont==4)
                    cont=0;
                contI[contadorInimigo]+=1;
            }
            if(posi[contadorInimigo]==3)
            {
                inimigo->x -= 4 ;
                SDL_BlitSurface(i3_esquerda, &inimigo3[cont], tela,inimigo);

                cont++;
                if (cont==4)
                    cont=0;
                 contI[contadorInimigo]+=1;
            }

            if(contI[contadorInimigo]==10)
                contI[contadorInimigo]=0;

            resu=colisao(destino,*inimigo);
            if(resu==1){

                morreu=1;


            }
            }
            contadorInimigo++;
            if(contadorInimigo==5)
                    contadorInimigo=0;

           // printf("%d\n", contadorInimigo);
    }

void ler_into()
{
    FILE* ds;
    ds=fopen("ds.txt","r");
    for(int i=0; i<42;i++)
    {
        fscanf(ds,"%d", &intro[i].x);
        fscanf(ds,"%d", &intro[i].y);
        fscanf(ds,"\n");
        intro[i].w=800;
        intro[i].h=600;
    }
    fclose(ds);
}
//novo


void rects_anima()
{

     /*asaida.x=colunasaida*40;
     asaida.y=(linhasaida*40)+90;
     asaida.w=40;
     asaida.h=40;
    */

     blitaPonto[7].x=760;

    blitaPonto[0].x=769;
    blitaPonto[1].x=738;
    blitaPonto[2].x=707;
    blitaPonto[3].x=123;
    blitaPonto[4].x=164;
    blitaPonto[5].x=205;
    blitaPonto[6].x=246;
    blitaPonto[7].x=287;
    for(int i = 0; i < 8; i++)
    {
         blitaPonto[i].y=40;
         blitaPonto[i].h=40;
         blitaPonto[i].w=30;
    }

    /*anima movimento personagem*/
    anima[0].x=0;
    anima[1].x=41;
    anima[2].x=82;
    anima[3].x=123;
    anima[4].x=164;
    anima[5].x=205;
    anima[6].x=246;
    anima[7].x=287;
    for(int i = 0; i < 8; i++)
    {
        anima[i].y=0;
        anima[i].h=40;
        anima[i].w=41;
    }

    numeros[0].x=0;
    numeros[1].x=31;
    numeros[2].x=62;
    numeros[3].x=93;
    numeros[4].x=124;
    numeros[5].x=155;
    numeros[6].x=186;
    numeros[7].x=217;
    numeros[8].x=248;
    numeros[9].x=279;
    for(int i = 0; i < 8; i++)
    {
        numeros[i].y=0;
        numeros[i].h=40;
        numeros[i].w=41;
    }
    //novo
     //pontos
    pontos[0].x=0;
    pontos[1].x=41;
    pontos[2].x=72;
    pontos[0].w=40;
    pontos[1].w=30;
    pontos[2].w=30;
    for(int i = 0; i < 4; i++)
    {
        pontos[i].y=0;
        pontos[i].h=20;
    }

    /*movimentação do inimigo*/
    inimigo3[0].x=0;
    inimigo3[1].x=41;
    inimigo3[2].x=81;
    inimigo3[3].x=121;
    for(int i = 0; i < 4; i++)
    {
        inimigo3[i].y=0;
        inimigo3[i].h=40;
        inimigo3[i].w=40;
    }
    /*pavío*/
    bomba1[0].x=0;
    bomba1[1].x=41;
    bomba1[2].x=81;
    bomba1[3].x=121;
    bomba1[4].x=161;
    bomba1[5].x=201;
    for(int i = 0; i < 6; i++)
    {
        bomba1[i].y=0;
        bomba1[i].h=40;
        bomba1[i].w=40;
    }

    //explosãaaaaaaaaao booooooooom centro
    for(int i=0; i<4;i++)
    {
        //centro
        explo[0][i].x=0;
        explo[0][i].y=(40*i)+i;
        explo[0][i].h=40;
        explo[0][i].w=40;
        //cima1
        explo[1][i].x=164;
        explo[1][i].y=(40*i)+i;
        explo[1][i].h=40;
        explo[1][i].w=40;
        //cima2
        explo[2][i].x=205;
        explo[2][i].y=(40*i)+i;
        explo[2][i].h=40;
        explo[2][i].w=40;
        //baixo1
        explo[3][i].x=246;
        explo[3][i].y=(40*i)+i;
        explo[3][i].h=40;
        explo[3][i].w=40;
        //baixo2
        explo[4][i].x=287;
        explo[4][i].y=(40*i)+i;
        explo[4][i].h=40;
        explo[4][i].w=40;
        //ESQUERDA 1
        explo[5][i].x=41;
        explo[5][i].y=(40*i)+i;
        explo[5][i].h=40;
        explo[5][i].w=40;
        // centro ed
        explo[6][i].x=82;
        explo[6][i].y=(40*i)+i;
        explo[6][i].h=40;
        explo[6][i].w=40;
        //direita1
        explo[7][i].x=123;
        explo[7][i].y=(40*i)+i;
        explo[7][i].h=40;
        explo[7][i].w=40;
    }

    /*temporizador*/
    tempoJogo[0].x=0;
    tempoJogo[1].x=41;
    tempoJogo[2].x=81;
    tempoJogo[3].x=121;
    tempoJogo[4].x=161;
    tempoJogo[5].x=201;
    tempoJogo[6].x=241;
    tempoJogo[7].x=281;
    tempoJogo[8].x=321;
    tempoJogo[9].x=361;
    tempoJogo[10].x=402;

    for(int i = 0; i < 11; i++)
    {
        tempoJogo[i].y=0;
        tempoJogo[i].h=40;
        tempoJogo[i].w=40;
    }

    destbotoes.x=60;
    destbotoes.y=544;
    destseta[0].x=65;
    destseta[0].y=544;
    destseta[1].x=211;
    destseta[1].y=544;
    destseta[2].x=405;
    destseta[2].y=544;
    destseta[3].x=605;
    destseta[3].y=544;

    //numeros grandes

   for(int i =0; i<10;i++)
   {
       NumerosGG[i].y=0;
       NumerosGG[i].x=(60*i)+1;
       NumerosGG[i].h=80;
       NumerosGG[i].w=60;
   }


}

void conta_ponto(int a,int b)
{
    score+=(a*10)+b;
    pontuacao[1]+=a;
    pontuacao[0]+=b;
    if(pontuacao[0]>9)
    {
        pontuacao[1]+=1;
        pontuacao[0]=0;
    }
    if(pontuacao[1]>9)
    {
        pontuacao[2]+=1;
        pontuacao[1]=0;
    }
    if(pontuacao[2]>9)
    {
        pontuacao[2]=0;
        pontuacao[3]+=1;
    }
    if(pontuacao[3]>9)
    {
        pontuacao[3]=0;
        pontuacao[4]+=1;
    }

}

// NOVO
void queima_inimigo(SDL_Rect fogo){
    resu=colisao(fogo,destinoI0);
    if(resu==1)
        conta_ponto(5,0);
        morreuI[0]=1;
    resu=colisao(fogo,destinoI1);
    if(resu==1)
        conta_ponto(5,0);
        morreuI[1]=1;
    resu=colisao(fogo,destinoI2);
    if(resu==1)
        conta_ponto(5,0);
        morreuI[2]=1;
    resu=colisao(fogo,destinoI3);
    if(resu==1)
        conta_ponto(5,0);
        morreuI[3]=1;
    resu=colisao(fogo,destinoI4);
    if(resu==1)
        conta_ponto(5,0);
        morreuI[4]=1;

    resu=colisao(fogo,destino);
    if(resu==1)
        morreu=1;

}

void perde_vida()
{
    s2=9;
    s1=5;
    m=5;
    life-=1;
    morreu=0;
    contI[0]=0;
    contI[1]=0;
    contI[2]=0;
    contI[3]=0;
    contI[4]=0;

    if(life==0)
    {
        gameover=1;
    }else
    {
        bomba_ativa=0;
        telajogo=0;
        pega_mapa();
        telafase=1;
    }


}
void tempo_Jogo()
{
    tempopont.x=350;
    tempopont.y=30;
    tempoMin.x=320;
    tempoMin.y=30;
    tempoSe1.x=380;
    tempoSe1.y=30;
    tempoSe2.x=410;
    tempoSe2.y=30;
    s2-=1;
    if(s2<0)
    {
        s1-=1;
        s2=9;
        if(s1<0)
        {
            s1=5;
            m--;

        }
    }
    if(m==0 && s1==0 && s2 <0)
            {

                morreu=1;
                m=5;
                s1=5;
                s2=9;
            }


}

 void testa_jogador()
{
/*=============== Deslocamento do jogador =====================*/
    if(evento.key.keysym.sym == SDLK_SPACE)
    {
        if(mapa[linha_atual2de][coluna_atual1cb] ==0)
        {
            if (bomba_ativa == 0 )
            {
                    destino_bomba.x=(coluna_atual1cb*40);
                    destino_bomba.y=((linha_atual2de*40)+90 );
                    linha_bomba = linha_atual2de;
                    coluna_bomba = coluna_atual1cb;
                    bomba_ativa = 1;
                    tempo_bomba = SDL_GetTicks();
            }
        }
    }
        if(evento.key.keysym.sym == SDLK_UP)
        {
            if (linha_atual1cb-1 == 0)
            {
                key=0;
            }
            else
            {
                key = 1;
                temp_key=key;
           }
        }
        if(evento.key.keysym.sym == SDLK_DOWN)
        {
            if (linha_atual1cb+1 == 13)
            {
                key=0;
            }else
            {
                key = 2;
                temp_key=key;
            }
        }
        if(evento.key.keysym.sym == SDLK_LEFT )
        {
            if (coluna_atual1cb-1 == 0)
            {
                key=0;
            }
            else
            {
                key = 3;
                temp_key=key;
            }
        }
         if(evento.key.keysym.sym == SDLK_RIGHT)
        {
            if (coluna_atual1cb+1 ==19)
            {
                key=0;
            }
            else
            {
                key = 4;
                temp_key=key;
            }
        }
}



void explosao()
{
    int i, j, k, l;
    //explosão de personagem
    /*if(linha_bomba == linha_atual1cb && coluna_bomba == coluna_atual1cb)
        {
            morreu=1;
        }*/
    //explosão de bloco e verifica parede e player
    for(i=1;i<4;i++)//cima
    {
        /*if(linha_bomba-i == linha_atual1cb && coluna_bomba == coluna_atual1cb)
        {
            morreu=1;
            contcima=i;
            break;
        }*/
        if(mapa[linha_bomba-i][coluna_bomba]==PAREDE)
        {
            contcima=i-1;
            break;
        }

        if(mapa[linha_bomba-i][coluna_bomba]==BLOCO)
        {
            mapa[linha_bomba-i][coluna_bomba] = 0;
            conta_ponto(2,5);
            contcima=i;
            break;
        }
        if(mapa[linha_bomba-i][coluna_bomba]==SAIDA)
        {
            mapa[linha_bomba-i][coluna_bomba] = 6;
            conta_ponto(2,5);
            contcima=i;
            break;
        }
        contcima=i;
    }
     for(j=1;j<4;j++)//baixo
    {
        /*if(linha_bomba+j == linha_atual1cb && coluna_bomba == coluna_atual1cb)
        {
            contbaixo=j;
            morreu=1;
            break;
        }*/
        if(mapa[linha_bomba+j][coluna_bomba]==PAREDE)
            {
                contbaixo=j-1;
                break;
            }
        if(mapa[linha_bomba+j][coluna_bomba]==BLOCO)
        {
            mapa[linha_bomba+j][coluna_bomba] = 0;
            conta_ponto(2,5);
            contbaixo=j;
            break;
        }
        if(mapa[linha_bomba+j][coluna_bomba]==SAIDA)
        {
            mapa[linha_bomba+j][coluna_bomba] = 6;
            conta_ponto(2,5);
            contbaixo=j;
            break;
        }
        contbaixo=j;
    }
     for(k=1;k<4;k++)//direita
    {
        /* if(linha_bomba == linha_atual1cb && coluna_bomba+k == coluna_atual1cb)
        {
            contdireita=k;
            morreu=1;
            break;
        }*/
        if(mapa[linha_bomba][coluna_bomba+k]==PAREDE)
        {
            contdireita=k-1;
            break;
        }
        if(mapa[linha_bomba][coluna_bomba+k]==BLOCO)
        {
            mapa[linha_bomba][coluna_bomba+k] = 0;
            conta_ponto(2,5);
            contdireita=k;
            break;
        }
        if(mapa[linha_bomba][coluna_bomba+k]==SAIDA)
        {
            mapa[linha_bomba][coluna_bomba+k] = 6;
            conta_ponto(2,5);
            contdireita=k;
            break;
        }
        contdireita=k;
    }
    for(l=1;l<4;l++)//esquerda
    {
       /*if(linha_bomba == linha_atual1cb && coluna_bomba-l == coluna_atual1cb)
        {
            contesquerda=l;
            morreu=1;
            break;
        }*/
        if(mapa[linha_bomba][coluna_bomba-l]==PAREDE)
        {
            contesquerda=l-1;
            break;
        }
        if(mapa[linha_bomba][coluna_bomba-l]==BLOCO)
        {
            mapa[linha_bomba][coluna_bomba-l] = 0;
            conta_ponto(2,5);
            contesquerda=l;

            break;
        }
        if(mapa[linha_bomba][coluna_bomba-l]==SAIDA)
        {
            mapa[linha_bomba][coluna_bomba-l] = 6;
            conta_ponto(2,5);
            contesquerda=l;
            break;
        }
        contesquerda=l;
    }
    mapa[linha_bomba][coluna_bomba] = 0;
    bomba_ativa = 0;
    tempo_bomba = 0;
}
void anima_explo()
{
    explodindo = 1;
    explosao();
    destexplo[0] = destino_bomba;
    destexplo[1] = destino_bomba;
    destexplo[2] = destino_bomba;
    destexplo[3] = destino_bomba;
    destexplo[4] = destino_bomba;

  /*  for(int i=0;i<4+1;i++)
    {
        SDL_BlitSurface(explosao_bomba,&explo[0][i],tela,&destexplo[0]);
    }*/
}
void passa_fase()
{
    fase+=1;
    telajogo=0;
    telafase=1;
    pega_mapa();
}
void anima_bomba()
{
    t++;
    if(t == 6)
    {
        t=0;
        anima_explo();
    }
}

void desenha_mapa()
{
	SDL_Rect destino;
	int linha, coluna;
    int x,y,i=0;
    int h=0;
	for (linha = 1; linha < 12; linha++)
	{
		destino.y = 90 + linha * 40;
		for (coluna = 1; coluna < 19; coluna++)
		{
			destino.x = coluna * 40;
			if (mapa[linha][coluna] == PAREDE)
			{
				/* pegue a imagem parede completa(NULL) e jogue na tela em destino */
				SDL_BlitSurface(parede, NULL, tela, &destino);
			}
            if (mapa[linha][coluna] == BLOCO)
			{
				/* pegue a imagem parede completa(NULL) e jogue na tela em destino */
				SDL_BlitSurface(bloco, NULL, tela, &destino);
			}
            if (mapa[linha][coluna] == SAIDA)
			{

				/* pegue a imagem parede completa(NULL) e jogue na tela em destino */
				SDL_BlitSurface(bloco, NULL, tela, &destino);
			}
			 if (mapa[linha][coluna] == 6)
			{
                colunasaida=coluna;
                linhasaida=linha;
				/* pegue a imagem parede completa(NULL) e jogue na tela em destino */
				SDL_BlitSurface(saida, NULL, tela, &destino);
			}

			if (mapa[linha][coluna] == 4)
			{
			    x=(coluna*40)+1;
                y=(((linha*40)+90)+1);
                if(i==0){
                destinoI0.x=x;
                destinoI0.y=y;

                }
                if(i==1){
                destinoI1.x=x;
                destinoI1.y=y;

                }
                if(i==2){
                destinoI2.x=x;
                destinoI2.y=y;

                }
                if(i==3){
                destinoI3.x=x;
                destinoI3.y=y;

                }
                if(i==4){
                destinoI4.x=x;
                destinoI4.y=y;

                }
                i++;
                mapa[linha][coluna] = 0;
                h++;
			}
		}
	}

}


int main ()
{

    int coli_bomba=0, coli_saida=0;

    destino.x = 41;
    destino.y = 90 + 40;


    /*inicializando a SDL e verificando possiveis erros */
	SDL_Init(SDL_INIT_EVERYTHING);
	if(SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		printf("Erro: %s\n", SDL_GetError());
		exit(-1);
	}

	/* Carrega as imagens */
	if (carrega_imagens() == 0) /* Se não carregou uma ou outra imagem */
	{
	    printf("erro de imagens");
		return 1; /* encerre o programa */
	}

	/* Configura o Video */
	tela = SDL_SetVideoMode(LARGURA, ALTURA, BPP, SDL_SWSURFACE | SDL_ANYFORMAT);

	if(tela == NULL)
	{
		printf("Erro: %s\n", SDL_GetError());
		return 1; /* encerre o programa */
	}
	int coli;
    int frame;
	int tempo_inicial;
	int tempodejogo;
	tempodejogo=SDL_GetTicks();
    pega_mapa();
    rects_anima();
    ler_into();
    int c=0;
    int j=0;
    int i=0;
    numerofase.x=320;
    numerofase.y=30;
    fim=0;
    bomba_ativa=0;
    t=0;
    liferect.x=100;
    liferect.y=40;
    rectpontos.y=30;

    // Inilialize SDL_mixer , exit if fail
    if( SDL_Init(SDL_INIT_AUDIO) < 0 ){
        //printf("nao foi");
        exit(1);
    }
    // Setup audio mode
//    	Mix_OpenAudio(22050,AUDIO_S16SYS,2,4096);
  //  Mix_Music *musStrokes  ;  // Background Music
    //Mix_Chunk *s_bomba , *wav2 ;  // For Sounds
    //musStrokes = Mix_LoadMUS("strokes.mp3");

    //mus2 = Mix_LoadMUS("./mixer/aria.mp3");
    //wav = Mix_LoadWAV("./mixer/po_p2k.wav");
    //wav2 = Mix_LoadWAV("./mixer/start.wav");


	/* Loop principal */
    while (fim == 0) /* Enquanto NÃO for verdadeiro o fim */
    {
        SDL_WM_SetCaption("Bomberman Hora de Aventura","Bomberman Hora de Aventura");
//        if( Mix_PlayingMusic() == 0 )
							{
							//printf("ds");
								//Play the music
//								Mix_PlayMusic(musStrokes, -1 );
							}
        tempo_inicial = SDL_GetTicks();
        if(fase==5)
        {
            trocafase();
        }
        if(gameover==1)
        {
            life=3;
            bomba_ativa=0;
            telajogo=0;
            fase=1;
            SDL_BlitSurface(finn,NULL,tela,NULL);
            SDL_UpdateRect(tela,0,0,0,0); /* Atualiza a tela inteira */
            controla_fps(tempo_inicial);
            SDL_Delay(2000);
            telamenu=1;
            gameover=0;
            pega_mapa();
        }
        if(telaintro==1)
        {
            SDL_BlitSurface(introducao,&intro[c],tela,NULL);
            c++;
            if(c==40)
            {
                telaintro=0;
                telamenu=1;
            }
            SDL_UpdateRect(tela,0,0,0,0); /* Atualiza a tela inteira */
            controla_fps(tempo_inicial); // controla o FPS

        }
        if(telamenu==1)
        {
            fase=1;
            SDL_BlitSurface(introducao,&intro[40],tela,NULL);
            SDL_BlitSurface(botoes, NULL,tela, &destbotoes); //&posibotoes
            SDL_BlitSurface(seta, NULL,tela, &destseta[j]);
            while(SDL_PollEvent(&eventomenu))
            {
                    if(eventomenu.type == SDL_QUIT )
                        fim = 1;
                    if(eventomenu.type == SDL_KEYDOWN)
                    {


                        if(eventomenu.key.keysym.sym == SDLK_LEFT)
                        {
                            j-=1;
                            if(j<0)
                                j=3;
                        }
                        if(eventomenu.key.keysym.sym == SDLK_RIGHT)
                        {
                            j+=1;
                            if(j>3)
                                j=0;
                        }
                        if(eventomenu.key.keysym.sym == SDLK_RETURN || evento.key.keysym.sym == SDLK_SPACE)
                        {
                            if(j==0)
                            {
                                telamenu=0;
                                telafase=1;
                            }
                            if(j==1)
                            {
                                telamenu=0;
                                telascore=1;
                            }
                            if(j==2)
                            {
                                telamenu=0;
                                telainstru=1;
                            }
                            if(j==3)
                                fim=1;
                        }
                    }
            }
        SDL_UpdateRect(tela,0,0,0,0); /* Atualiza a tela inteira */
        controla_fps(tempo_inicial); // controla o FPS
        }
        if(telainstru==1)
        {
            SDL_BlitSurface(manual,NULL,tela,NULL);
            while(SDL_PollEvent(&eventomenu))
            {
                    if(eventomenu.type == SDL_QUIT )
                        fim = 1;
                    if(eventomenu.type == SDL_KEYDOWN)
                    {
                        telainstru=0;
                        telamenu=1;
                    }
            }
            SDL_UpdateRect(tela,0,0,0,0); /* Atualiza a tela inteira */
            controla_fps(tempo_inicial); // controla o FPS
        }
        if(telafase==1)
        {
            SDL_BlitSurface(trans, NULL, tela, NULL);
            SDL_BlitSurface(numGG, &NumerosGG[0],tela,&numerofase);
            numerofase.x+=100;
            SDL_BlitSurface(numGG, &NumerosGG[fase],tela,&numerofase);
            numerofase.x-=100;
            SDL_UpdateRect(tela,0,0,0,0); /* Atualiza a tela inteira */
            controla_fps(tempo_inicial);
            SDL_Delay(3000);
            destino.x = 41;
            destino.y = 90 + 40;
            telafase=0;
            telajogo=1;
        }
        if(telajogo==1)
        {

            //para testar o movimento de cima e baixo (cb)
            linha_atual1cb = (destino.y-50)/40;
            coluna_atual1cb = (destino.x+8)/40;
            linha_atual2cb = (destino.y-70)/40;
            coluna_atual2cb = (destino.x+30)/40;
            //para testar o movimento para os lados (de)
            linha_atual1de = (destino.y-53)/40;
            coluna_atual1de = (destino.x)/40;
            linha_atual2de = (destino.y-65)/40;
            coluna_atual2de = (destino.x+39)/40;
          /*=================segundos===============*/
            if(SDL_GetTicks()>tempodejogo+1000)
            {
                printf("minuto %d e segundos %d%d\n ", m , s1, s2);
                tempo_Jogo();
                tempodejogo = SDL_GetTicks();
            }
        /*========================bomba===============*/
            if(bomba_ativa == 1)
            {
                if(SDL_GetTicks() > tempo_bomba + 500)
                {
                  anima_bomba();
                  tempo_bomba=SDL_GetTicks();
                }
            }
            if(morreu==1)
            {


                s2=9;
                s1=5;
                m=5;

                perde_vida();
            }
        /* ============ blits aqui embaixo =============*/
            SDL_FillRect(tela, NULL, SDL_MapRGB(tela->format, 0, 0, 0));
            SDL_BlitSurface(fundo, NULL, tela, NULL);
            SDL_BlitSurface(tempo, &tempoJogo[s1], tela,&tempoSe1);
            SDL_BlitSurface(tempo, &tempoJogo[s2], tela,&tempoSe2);
            SDL_BlitSurface(tempo, &tempoJogo[10], tela,&tempopont);
            SDL_BlitSurface(tempo, &tempoJogo[m], tela, &tempoMin);
             //pontos
            SDL_BlitSurface(tempo, &tempoJogo[pontuacao[4]], tela, &rectpontos);
            rectpontos.x+=25;
            SDL_BlitSurface(tempo, &tempoJogo[pontuacao[3]], tela, &rectpontos);
            rectpontos.x+=25;
            SDL_BlitSurface(tempo, &tempoJogo[pontuacao[2]], tela, &rectpontos);
            rectpontos.x+=25;
            SDL_BlitSurface(tempo, &tempoJogo[pontuacao[1]], tela, &rectpontos);
            rectpontos.x+=25;
            SDL_BlitSurface(tempo, &tempoJogo[pontuacao[0]], tela, &rectpontos);
            rectpontos.x=600;


            for(int y=1; y<life+1;y++)
            {
                liferect.x=40;

                liferect.x+=40*y;
                SDL_BlitSurface(vida, NULL, tela,&liferect);
            }

            /* Loop de eventos */
            while(SDL_PollEvent(&evento))
            {
                    if(evento.type == SDL_QUIT)
                        fim = 1;
                    if(evento.type == SDL_KEYUP)
                        key = 0;
                    if(evento.type == SDL_KEYDOWN)
                    {
                        testa_jogador();
                    }
            }

        desenha_mapa();
       // if(morreuI[0]==0)
        blita_inimigo(&destinoI0);
      //  if(morreuI[1]==0)
        blita_inimigo(&destinoI1);
    //    if(morreuI[2]==0)
        blita_inimigo(&destinoI2);
     //  if(morreuI[3]==0)
        blita_inimigo(&destinoI3);
     //   if(morreuI[4]==0)
        blita_inimigo(&destinoI4);//blita o inimigo [0] no DestinoI, contador de animações.


        if(bomba_ativa==1)
        {
            SDL_BlitSurface(bomba, &bomba1[t], tela, &destino_bomba);
            coli_bomba=colisao(destino,destino_bomba);
    if(coli_bomba==0)
        mapa[linha_bomba][coluna_bomba]=3;

        }
        if(explodindo==1)
        {
              frame=0;
              while(frame < 4)
            {  //blita o do centro
                SDL_BlitSurface(explosao_bomba,&explo[0][frame],tela,&destexplo[0]);
                queima_inimigo(destexplo[0]);
                frame++;
            }
            for(int r=0; r<contcima;r++)
            {   //blita cima
                destexplo[1].y -= 40;
                frame=0;
                while(frame<4)
                {
                        SDL_BlitSurface(explosao_bomba,&explo[1][frame],tela,&destexplo[1]);
                        queima_inimigo(destexplo[1]);
                        frame++;
                }
            }
            for(int r=0; r<contbaixo;r++)
            {   //blita baixo
                destexplo[2].y+=40;
                frame=0;
                while(frame < 4)
                    {
                        SDL_BlitSurface(explosao_bomba,&explo[3][frame],tela,&destexplo[2]);
                        queima_inimigo(destexplo[2]);
                        frame++;
                    }
            }
            for(int r=0; r<contesquerda;r++)
            {   //blita esquerda
                destexplo[3].x-=40;
                frame=0;
                while(frame < 4)
                {
                    SDL_BlitSurface(explosao_bomba,&explo[6][frame],tela,&destexplo[3]);
                    queima_inimigo(destexplo[3]);
                    frame++;
                }
            }
            for(int r=0; r<contdireita;r++)
            {   //blita direita
                //printf("x %d\n", explo[6][frame].x);
                //printf("y %d\n", explo[6][frame].y);
                destexplo[4].x+=40;
                frame=0;
                while(frame < 4)
                {
                    SDL_BlitSurface(explosao_bomba,&explo[6][frame],tela,&destexplo[4]);
                    queima_inimigo(destexplo[4]);
                    frame++;
                }
            }
            explodindo=0;
        }
            coli_saida=colisao(destino,asaida);
            //if(mapa[linha_atual2cb][coluna_atual1cb] ==6  || mapa[linha_atual2cb][coluna_atual1cb] ==6 || mapa[linha_atual2cb][coluna_atual1cb] ==6 || mapa[linha_atual2cb][coluna_atual1cb] ==6)
            if(coli==1)
            {
                passa_fase();
            }
        /*movimentação e animação*/
        if(key!=0)
        {
            if(key == 1)
            {
                if (linha_atual1cb > 1)
                {
                    if(mapa[linha_atual2cb-1][coluna_atual1cb]==6)
                        {
                            passa_fase();
                        }
                        if(mapa[linha_atual2cb][coluna_atual2cb]==0 && mapa[linha_atual2cb][coluna_atual1cb]==0)
                        {
                            SDL_BlitSurface(cima, &anima[i], tela, &destino);
                            destino.y -= 4;
                            i++;
                            if(i == 8)
                                i=0;
                        }
                        else
                            SDL_BlitSurface(cima, &anima[1], tela, &destino);
                }
                else
                    SDL_BlitSurface(cima, &anima[1], tela, &destino);
            }
            if(key == 2)
            {
                if (linha_atual1cb < 12)
                {
                    if(mapa[linha_atual2cb+1][coluna_atual1cb]==6)
                        {
                            passa_fase();
                        }
                    if(mapa[linha_atual1cb][coluna_atual2cb] ==0 && mapa[linha_atual1cb][coluna_atual1cb] ==0)
                    {
                        SDL_BlitSurface(baixo, &anima[i], tela, &destino);
                        destino.y += 4;
                        i++;
                        if(i == 8)
                            i=0;
                    }
                    else
                            SDL_BlitSurface(baixo, &anima[1], tela, &destino);
                }
                else
                    SDL_BlitSurface(baixo, &anima[1], tela, &destino);
            }
            if(key == 3)
            {
                if (coluna_atual1cb > 0)
                {
                if(mapa[linha_atual2cb][coluna_atual1cb-1]==6)
                        {
                            passa_fase();
                        }
                    if(mapa[linha_atual1de][coluna_atual1de] ==0 && mapa[linha_atual2de][coluna_atual1de]==0 )
                    {
                        SDL_BlitSurface(esquerda, &anima[i], tela, &destino);
                        destino.x -= 4;
                        i++;
                        if(i == 8)
                            i=0;
                    }
                    else
                        SDL_BlitSurface(esquerda, &anima[1], tela, &destino);
                }
                else
                    SDL_BlitSurface(esquerda, &anima[1], tela, &destino);

            }
            if(key == 4)
            {
                if(mapa[linha_atual2cb][coluna_atual1cb+1]==6)
                {
                    passa_fase();
                }
                 if(coluna_atual1de < 18)
                 {
                    if(mapa[linha_atual1de][coluna_atual2de] ==0 && mapa[linha_atual2de][coluna_atual2de] ==0)
                     {
                        SDL_BlitSurface(direita, &anima[i], tela, &destino);
                        destino.x += 4;
                        i++;
                        if(i == 8)
                            i=0;
                     }
                     else
                        SDL_BlitSurface(direita, &anima[1], tela, &destino);
                }
                else
                    SDL_BlitSurface(direita, &anima[1], tela, &destino);
            }
        }



        if(key == 0)
        {
            switch(temp_key) // printa o Stand
            {
                case 1:
                    SDL_Delay(FPS);
                    SDL_BlitSurface(cima,&anima[1],tela,&destino);
                break;
                case 2:
                    SDL_Delay(FPS);
                    SDL_BlitSurface(baixo,&anima[1],tela,&destino);
                break;
                case 3:
                    SDL_Delay(FPS);
                    SDL_BlitSurface(esquerda,&anima[1],tela,&destino);
                break;
                case 4:
                    SDL_Delay(FPS);
                    SDL_BlitSurface(direita,&anima[1],tela,&destino);
                break;
                }
             }
            SDL_UpdateRect(tela,0,0,0,0); /* Atualiza a tela inteira */
            controla_fps(tempo_inicial); // controla o FPS
        }
	}
	//Mix_FreeChunk(&musStrokes);
/* Finalizando o SDL */
/* Finalizando o SDL */

SDL_Quit();

return 0;
}
