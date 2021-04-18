#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <windows.h>


#define MAXNOTAS 25
#define MIN_SCORE -500
#define MAX_MUSICA 45
#define largura_tela 900
#define altura_tela 600
#define FPS 130


const float dy = 1.0;
const int hit_altura = 500;
int sortear_nota;
int sortear_nota2;
int sortear_nota3;





typedef struct Nota {
    float x,y,dx; //x center, y bottom 
    float altura, largura, variacao;
    int status;
    int id;
    ALLEGRO_BITMAP *color;
} Nota;

void cria_nota(Nota *n, int i, float ln, float an){
    
        if (i<=4){
            n->x = largura_tela/2.0-55; //modificar o x para nao ficar parecido com o do Luan
            n->y = 210;
            n->dx = -0.46; //-0,368 -0.455
            n->largura = ln;
            n->altura = an;
            n->status = 0;
            n->color = al_load_bitmap("nota1.png");;
            n->id = 1;
            n->variacao = 15.0;

        }
        if (i>=5 && i<=9){
            n->x = largura_tela/2.0-25;
            n->y = 210;
            n->dx = -0.3; //0,192
            n->largura = ln;
            n->altura = an;
            n->status = 0;
            n->color = al_load_bitmap("nota2.png");;
            n->id = 2;
            n->variacao = 15.0;

        }
        if (i>=10 && i<=14){
            n->x = largura_tela/2.0-5;
            n->y = 210;
            n->dx = -0.1; // 0
            n->largura = ln;
            n->altura = an;
            n->status = 0;
            n->color = al_load_bitmap("nota3.png");;
            n->id = 3;
            n->variacao = 15.0;

        }
        if (i>=15 && i<=19){
            n->x = largura_tela/2.0+5;
            n->y = 210;
            n->dx= 0.135; // 0,192
            n->largura = ln;
            n->altura = an;
            n->status = 0;
            n->color = al_load_bitmap("nota4.png");; 
            n->id = 4;  
             n->variacao = 15.0;
        }
        if (i>=20 && i<=24){
            n->x = largura_tela/2.0+25;
            n->y = 210;
            n->dx = 0.36; // -0.26; -0.368; -0.403
            n->largura = ln;
            n->altura = an;
            n->status = 0;
            n->color = al_load_bitmap("nota5.png");; 
            n->id = 5; 
            n->variacao = 15.0; 
        }
}

void cria_menu(ALLEGRO_DISPLAY *display, ALLEGRO_BITMAP *menu){
    al_draw_bitmap(menu,0,0,0);
}

void cria_cenario(ALLEGRO_DISPLAY *display,  ALLEGRO_BITMAP *image, ALLEGRO_FONT *font){
    char nomejogo[20];
    al_draw_bitmap(image,0,0,0);
;
 
}


void desenhar_nota(Nota *n){

 
    al_draw_scaled_bitmap(n->color, 0, 0, (n->largura), (n->altura), (n->x), (n->y), (n->variacao) , (n->variacao),0);
    //se divirtam tentando aprender como usa esse comando aí de cima kkk
}


void desenhar_notaS(Nota *n){
    do{ 
        sortear_nota = rand()%25;
    }while (n[sortear_nota].status == 1 ); //se o nota sorteado já estiver em uso sorteia de novo
    n[sortear_nota].status = 1; 
    desenhar_nota(&n[sortear_nota]);
}

void desenhar_notaD(Nota *n){
    do{ 
        sortear_nota = rand()%25;
    }while (n[sortear_nota].status == 1 ); //se o nota sorteado já estiver em uso sorteia de novo
    n[sortear_nota].status = 1;

    do{ 
        sortear_nota2 = rand()%25;
    }while (n[sortear_nota2].status == 1 || n[sortear_nota2].id == n[sortear_nota].id ); //se o circulo sorteado já estiver em uso sorteia de novo
    n[sortear_nota2].status = 1;

    desenhar_nota(&n[sortear_nota]);
    desenhar_nota(&n[sortear_nota2]);
}


void desenhar_notaT(Nota *n){
    do{ 
        sortear_nota = rand()%25;
    }while (n[sortear_nota].status == 1 ); //se o nota sorteado já estiver em uso sorteia de novo
    n[sortear_nota].status = 1;

    do{ 
        sortear_nota2 = rand()%25;
    }while (n[sortear_nota2].status == 1 || n[sortear_nota2].id == n[sortear_nota].id ); //se o circulo sorteado já estiver em uso sorteia de novo
    n[sortear_nota2].status = 1;


    do{ 
        sortear_nota3 = rand()%25;
    } while (n[sortear_nota3].status == 1 || n[sortear_nota3].id == n[sortear_nota].id || n[sortear_nota3].id == n[sortear_nota2].id );
    n[sortear_nota3].status = 1;

    desenhar_nota(&n[sortear_nota]);
    desenhar_nota(&n[sortear_nota2]);
    desenhar_nota(&n[sortear_nota3]);
}



int checagem(Nota *n, Nota *n1, int i, int pontuacao, ALLEGRO_TIMER *tempo, float largura_nota, float altura_nota, ALLEGRO_SAMPLE *error, ALLEGRO_SAMPLE *hit, int multi, bool *broke){ // checa se vai ganhar ou perder pontos
    
    if (n1->y <= (hit_altura + 10) && n1->y >= (hit_altura - 10)){
        pontuacao = pontuacao + (100*multi);
        al_play_sample(hit, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
        cria_nota(n1,i,largura_nota,altura_nota);
        *broke = false;

    }

    if(n1->y < (hit_altura - 10) && n1->y >= (hit_altura - 40)){
        pontuacao = pontuacao - 50;
        al_play_sample(error, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
        cria_nota(n1,i,largura_nota,altura_nota);
        *broke = true;
            
    }
    return pontuacao;
}

int multiplicar(int na){
    if (na<=10)
        return 1;
    if(na>10 && na<=20 )
        return 2;
    if (na>20 && na<=30)
        return 3;
    if (na>30)
        return 4;

}



int main(int argc, char **argv){ 


    //------------------------------ rotinas de inicializacao -------------------------
    ALLEGRO_DISPLAY *display = NULL;
    ALLEGRO_EVENT_QUEUE *event_queue = NULL;
    ALLEGRO_TIMER *timer = NULL;
    ALLEGRO_FONT *size_32;
    ALLEGRO_FONT *size_26;
    ALLEGRO_BITMAP *cenario = NULL;
    ALLEGRO_BITMAP *cenario2 = NULL;
    ALLEGRO_BITMAP *cenario3 = NULL;
    ALLEGRO_BITMAP *cenario4 = NULL;
    ALLEGRO_BITMAP *cenario5 = NULL;
    ALLEGRO_BITMAP *telainicial = NULL;
    ALLEGRO_BITMAP *menu = NULL;
    ALLEGRO_BITMAP *menu2 = NULL;
    ALLEGRO_BITMAP *easy = NULL;
    ALLEGRO_BITMAP *medium = NULL;
    ALLEGRO_BITMAP *hard = NULL;
    ALLEGRO_BITMAP *expert = NULL;
    ALLEGRO_BITMAP *nota1 = NULL; //preciso de uma nota qualquer só pra peagr dimensão
    ALLEGRO_BITMAP *verde = NULL; 
    ALLEGRO_BITMAP *vermelho = NULL;
    ALLEGRO_BITMAP *amarelo = NULL;
    ALLEGRO_BITMAP *azul = NULL;
    ALLEGRO_BITMAP *laranja = NULL;
    ALLEGRO_BITMAP *fogo = NULL;
    ALLEGRO_BITMAP *m2 = NULL;
    ALLEGRO_BITMAP *m3 = NULL;
    ALLEGRO_BITMAP *m4 = NULL;
    ALLEGRO_BITMAP *medidor = NULL;

    ALLEGRO_AUDIO_STREAM *musica = NULL;
    ALLEGRO_SAMPLE *sample = NULL;
    ALLEGRO_SAMPLE *ir = NULL;
    ALLEGRO_SAMPLE *erro = NULL;
    ALLEGRO_SAMPLE *acerto = NULL;
    ALLEGRO_SAMPLE *plateia = NULL;
    ALLEGRO_SAMPLE *aplauso = NULL;



    al_init();
    timer = al_create_timer(1.0 / FPS);
    display = al_create_display(largura_tela, altura_tela);
    event_queue = al_create_event_queue();
    al_init_image_addon();
    al_init_font_addon();
    al_init_ttf_addon();
    al_install_keyboard();
    al_install_audio();
    al_init_acodec_addon();
    al_reserve_samples(1);
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_start_timer(timer);
   

   
    //------------------------------ rotinas de inicializacao -------------------------
    nota1 = al_load_bitmap("nota1.png");
    cenario = al_load_bitmap("cenario.png");
    cenario2 = al_load_bitmap("cenario2.png");
    cenario3 = al_load_bitmap("cenario3.png");
    cenario4 = al_load_bitmap("cenario4.png");
    cenario5 = al_load_bitmap("cenario5.png");
    size_32 = al_load_font("arial.ttf", 32, 1);
    size_26 = al_load_font("DS-DIGI.ttf", 26, 1);
    verde = al_load_bitmap("verde.png");
    vermelho = al_load_bitmap("vermelho.png");
    amarelo = al_load_bitmap("amarelo.png");
    azul = al_load_bitmap("azul.png");
    laranja = al_load_bitmap("laranja.png");
    fogo = al_load_bitmap("fogo.png");
     menu = al_load_bitmap("menu.png");
     menu2 = al_load_bitmap("menu2.png");
    easy = al_load_bitmap("easy.png");
    medium = al_load_bitmap("medium.png");
    hard = al_load_bitmap("hard.png");
    expert = al_load_bitmap("expert.png");
    sample = al_load_sample("pipe.wav");
    musica = al_load_audio_stream("background.ogg", 4, 1024);
    ir = al_load_sample("ir.wav");
    erro = al_load_sample("erro.wav");
    acerto = al_load_sample("acerto.wav");
    plateia = al_load_sample("plateia.wav");
    aplauso = al_load_sample("aplauso.wav");
    m2 = al_load_bitmap("m2.png");
    m3 = al_load_bitmap("m3.png");
    m4 = al_load_bitmap("m4.png");
    medidor = al_load_bitmap("medidor.png");
    telainicial = al_load_bitmap("tela.png");
   
   

    float largura_nota =  al_get_bitmap_width(nota1);
    float altura_nota =  al_get_bitmap_height(nota1);
    int multiplicador = 1;
    int i=0,j=0,o=0,k=0;
    int playing = 1;
    int espera = 0 ;
    int esperainicial = 500;
    int sortear_n; //sorteio da nota
    int sortear_tc; // sorteio tipo de nota
    int total_notas = 0;
    int score = 0; //escore atual
    int scoreV= 0; //escore anterior
    int auxfinal ;
    int posmenu = 0; 
    int dificuldade = 0;
    int cheer = 0; //torcida
    int notas_acertadas = 0;
    int delay = 0;
    char my_score[20];
    bool fimdejogo = false;
    bool select = false; //menu 1
    bool select2 = false; //menu 2
    bool geralselect = false; //menugeral
    bool flagQ = false;
    bool flagW = false;
    bool flagE = false;
    bool flagR = false;
    bool flagI = false;
    bool flagSPACE = false;
    bool redraw = true; //variavel que indica se eh para redesenhar o nota
    bool c1 = false; //cenario 1
    bool c2 = false; 
    bool c3 = false; 
    bool c4 = false;
    bool c5 = false;
    bool quebra = false; //quebra sequencia notas
    bool inicio = true;
    char minhasnotas[20];

   
    Nota nota[MAXNOTAS];

    int testerand = rand()%25;


    srand(time(NULL));

    cria_cenario(display,cenario,size_32); //cria a imagem de fundo junto com o nome do jogo   

    for (i= 0; i < MAXNOTAS; ++i){
       cria_nota(&nota[i],i,largura_nota,altura_nota);
    }

    al_draw_bitmap(telainicial,0,0,0);
    al_flip_display();
    

while(inicio){ //tela inicial

        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);

        if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE  ) {
                playing = 0;
                break;
                
        } 
        if(ev.type == ALLEGRO_EVENT_KEY_DOWN) {
                switch(ev.keyboard.keycode) {

                case ALLEGRO_KEY_ENTER:
                    al_play_sample(ir, 2.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                    geralselect = true;
                    inicio = false;   
                break;

                case ALLEGRO_KEY_BACKSPACE:
                    inicio = false;   
                    playing = 0;
                break;
                }
        }     
}




while(geralselect){ 
    while(!select){ // menu de seleção de dificuldade

            al_attach_audio_stream_to_mixer(musica, al_get_default_mixer());
            al_set_audio_stream_playing(musica, true);

            ALLEGRO_EVENT ev;
            al_wait_for_event(event_queue, &ev);

            if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE  ) {

                select2 = true;
                geralselect = false;
                playing = 0;
                break;
            }

            if(ev.type == ALLEGRO_EVENT_TIMER) {
                cria_menu(display,menu);
                if (posmenu == 0)
                    al_draw_bitmap(easy,160,190,0);
                if (posmenu == 1)
                    al_draw_bitmap(medium,160,251,0);
                if (posmenu == 2)
                    al_draw_bitmap(hard,160,314,0);
                if (posmenu == 3)
                    al_draw_bitmap(expert,152,372,0);
                
                al_flip_display();
            }
            if(ev.type == ALLEGRO_EVENT_KEY_DOWN) {
               
                switch(ev.keyboard.keycode) {
                case ALLEGRO_KEY_UP:
                    al_play_sample(sample, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                    if(posmenu == 0)
                        posmenu=3;
                    else
                        posmenu--;

                break;
                    
                case ALLEGRO_KEY_DOWN:
                    al_play_sample(sample, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                    if(posmenu == 3)
                        posmenu = 0;
                    else
                        posmenu++;
                        
                break;

                case ALLEGRO_KEY_ENTER:
                    al_play_sample(ir, 2.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                    dificuldade = posmenu;
                    select = true;
                    select2 = false;
                    playing = 1;
                    
                break;

                case ALLEGRO_KEY_BACKSPACE:
                    select = true;
                    playing = 0;
                    geralselect = false;
                    
                    
                break;
                }
            }
    }

    while(!select2){ //menu de seleção de cenário

            ALLEGRO_EVENT ev;
            al_wait_for_event(event_queue, &ev);

            if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE  ) {
                playing = 0;
                select2 = true;
                geralselect = false;
                
                break;
            }

            if(ev.type == ALLEGRO_EVENT_TIMER) {
                al_draw_bitmap(menu2,0,0,0);
                
                al_flip_display();
            }

            if(ev.type == ALLEGRO_EVENT_KEY_DOWN) {
               
                switch(ev.keyboard.keycode) {
                case ALLEGRO_KEY_1:
                    select2 = true;
                    geralselect = false;
                    c1 = true;
                    al_play_sample(ir, 2.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                break;
                    
                case ALLEGRO_KEY_2:
                    select2 = true;
                    geralselect = false;
                    c2 = true;
                    al_play_sample(ir, 2.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);     
                break;

                case ALLEGRO_KEY_3:
                    select2 = true;
                    geralselect = false;
                    c3 = true; 
                    al_play_sample(ir, 2.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);   
                break;

                case ALLEGRO_KEY_4:
                    select2 = true;
                    geralselect = false;
                    c4 = true;
                    al_play_sample(ir, 2.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL); 
                break;

                case ALLEGRO_KEY_5:
                    select2 = true;
                    geralselect = false;
                    c5 = true;
                    al_play_sample(ir, 2.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                break;

                case ALLEGRO_KEY_BACKSPACE:
                    select2 = true;
                    select = false;
                    playing = 0;
                    
                    
                break;
                }
            }
    }
}



al_set_audio_stream_playing(musica, false);

while(playing) {



            ALLEGRO_EVENT ev;
            al_wait_for_event(event_queue, &ev);

            if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE  ) {
                break;
            }

            if(ev.type == ALLEGRO_EVENT_KEY_DOWN) {
               
                scoreV = score;
                switch(ev.keyboard.keycode) {
                case ALLEGRO_KEY_Q:
                    flagQ = true;
                    for(i=0;i<5;i++){
                        score = checagem(nota,&nota[i],i,score,timer,largura_nota,altura_nota,erro,acerto,multiplicador,&quebra);
                    }
                    if(scoreV < score)
                        notas_acertadas++;    
                break;
                    
                case ALLEGRO_KEY_W:
                    flagW = true;
                    for(i=5;i<10;i++){
                        score = checagem(nota,&nota[i],i,score,timer,largura_nota,altura_nota,erro,acerto,multiplicador,&quebra);
                    }  
                    if(scoreV < score)
                        notas_acertadas++;       
                break;

                case ALLEGRO_KEY_E:
                    flagE = true;
                    for(i=10;i<15;i++){
                        score = checagem(nota,&nota[i],i,score,timer,largura_nota,altura_nota,erro,acerto,multiplicador,&quebra);
                    }
                    if(scoreV < score)
                        notas_acertadas++;
                break;

                case ALLEGRO_KEY_R:
                    flagR = true;
                    for(i=15;i<20;i++){
                        score = checagem(nota,&nota[i],i,score,timer,largura_nota,altura_nota,erro,acerto,multiplicador,&quebra);
                    }
                    if(scoreV < score)
                        notas_acertadas++;
                break;

                case ALLEGRO_KEY_I:
                    flagI = true;
                break;

                case ALLEGRO_KEY_SPACE:
                    flagSPACE = true;
                     for(i=20;i<25;i++){
                        score = checagem(nota,&nota[i],i,score,timer,largura_nota,altura_nota,erro,acerto,multiplicador,&quebra);
                    }
                    if(scoreV < score)
                        notas_acertadas++;
                break;

                case ALLEGRO_KEY_ESCAPE:
                    playing=0;

                break;  
                }
            }

            if(ev.type == ALLEGRO_EVENT_KEY_UP) {
                switch(ev.keyboard.keycode) {
                    
                case ALLEGRO_KEY_Q:
                    flagQ = false;
                break;
                    
                case ALLEGRO_KEY_W:
                    flagW = false;      
                break; 

                case ALLEGRO_KEY_E:
                    flagE = false;     
                break; 
            
                case ALLEGRO_KEY_R:
                    flagR = false;    
                break;

                case ALLEGRO_KEY_I:
                    flagI = false;    
                break;

                case ALLEGRO_KEY_SPACE:
                    flagSPACE = false;      
                break;  
                }
            }       


            if(ev.type == ALLEGRO_EVENT_TIMER) {

                if(c1)
                    cria_cenario(display,cenario,size_32);
                if(c2)
                    cria_cenario(display,cenario2,size_32);
                if(c3)
                    cria_cenario(display,cenario3,size_32);
                if(c4)
                    cria_cenario(display,cenario4,size_32);
                if(c5)
                    cria_cenario(display,cenario5,size_32);
               
                sprintf(my_score, "%d", score);
                al_draw_text(size_26, al_map_rgb(178, 192, 111),145, 401, 0, my_score);
                
               if (flagQ){
                    al_draw_bitmap(verde,255,516,0); 
                    if(scoreV < score)// nota dupla e tripla deixa isso meio bugado
                        al_draw_bitmap(fogo,265,435,0);  
                }
                if(flagW){
                    al_draw_bitmap(vermelho,333,516,0);
                    if(scoreV < score)
                        al_draw_bitmap(fogo,343,435,0);
                }  
                if(flagE){ 
                    al_draw_bitmap(amarelo,413,516,0);
                    if(scoreV < score)
                        al_draw_bitmap(fogo,423,435,0);
                }
                if(flagR){ 
                    al_draw_bitmap(azul,491,516,0);
                    if(scoreV < score)
                        al_draw_bitmap(fogo,501,435,0);
                }
                if(flagSPACE){ 
                    al_draw_bitmap(laranja,570,516,0);
                    if(scoreV < score)
                        al_draw_bitmap(fogo,580,435,0);
                }
                
        
                if(quebra)
                    notas_acertadas = 0;

                multiplicador = multiplicar(notas_acertadas);
                if(multiplicador == 2)
                    al_draw_bitmap(m2,142,422,0);
                if(multiplicador == 3)
                    al_draw_bitmap(m3,144,423,0);
                if(multiplicador == 4)
                    al_draw_bitmap(m4,144,422,0);

            


                al_draw_bitmap(medidor,167,492,0);
                sprintf(minhasnotas, "%d", notas_acertadas);
                    al_draw_text(size_26, al_map_rgb(255, 255, 255),200, 499, 0, minhasnotas);
                

                

                if(cheer>70 && cheer<100)
                    al_play_sample(plateia, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);

                cheer++;
                espera++;
                if(dificuldade == 0){
                    delay = 30+rand()%2500;
                    sortear_tc = rand()%13;
                }

                if(dificuldade == 1){
                    delay = 30+rand()%2000;
                    sortear_tc = rand()%14;
                }

                if(dificuldade == 2){
                    delay = 30+rand()%1000;
                    sortear_tc = rand()%15;

                }

                if (dificuldade == 3){
                    delay = 30+rand()%500; //espera 30 é o minimo pra n encavalar, independe do fps, 40 a parada fica doida
                    sortear_tc = rand()%17;
                }


                if (espera>(esperainicial+delay) && total_notas < MAX_MUSICA){ 
                    if (sortear_tc <=10 )
                        desenhar_notaS(nota);
                    if (sortear_tc >= 11 && sortear_tc <=13 )
                        desenhar_notaD(nota);
                    if (sortear_tc >= 14)
                        desenhar_notaT(nota);
                    total_notas++;
                    espera=0;
                    esperainicial = 0;
                } 
                 


                for (i = 0; i < MAXNOTAS; ++i){
                    if (nota[i].status ==1 ){
                        redraw = true;   //como eu movi o nota, preciso redesenhar ele 
                        if(redraw && al_is_event_queue_empty(event_queue)) {
                            redraw = false; //nao preciso redesenhar
                            desenhar_nota(&nota[i]);  //desenho o nota na nova posicao
                            nota[i].x += nota[i].dx;
                            nota[i].y += dy; 
                            nota[i].variacao += 0.2;
   
                        }
                    }
                }

               
                for ( i = 0; i < MAXNOTAS; ++i){
                    if (nota[i].y > altura_tela-60 ){ 
                        cria_nota(&nota[i],i,largura_nota,altura_nota);
                        if(!flagI){
                        score -=50;
                        }
                        al_play_sample(erro, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                        quebra = true;

                    }
                }
                al_flip_display();//dou um refresh na tela
            }

            auxfinal = 0;
            if(total_notas >= MAX_MUSICA){ 
                for (i = 0; i < MAXNOTAS; ++i){
                    if (nota[i].status == 0)
                        auxfinal ++;
                }
                if (auxfinal == 25){
                    fimdejogo = true; 
                    break;
                }
            }  
            

        }
if (fimdejogo){ 

    al_rest(3);
    char my_text[20];   
    char meu_texto[20];
    int record;
    float aux = 0.0;
    al_clear_to_color(al_map_rgb(230,240,250)); 
    FILE *arq;
    arq = fopen("record2.txt","r");
    fscanf(arq,"%d",&record);
    fclose(arq);
    if (score>record){
        al_play_sample(aplauso, 2.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
        al_draw_text(size_32, al_map_rgb(128,255,0), largura_tela/3, altura_tela/2-40, 0, "New Record!!");
        sprintf(meu_texto,"Past Record:%d ",record);
        al_draw_text(size_32, al_map_rgb(200, 0, 30), largura_tela/3, altura_tela/2+40, 0, meu_texto);
        arq = fopen("record2.txt","w");
        fprintf(arq,"%d",score);
        fclose(arq);
    }
    else{
        sprintf(meu_texto,"Record: %d",record);
        al_draw_text(size_32, al_map_rgb(200, 0, 30), largura_tela/3, altura_tela/2+40, 0, meu_texto);
    }
    
    sprintf(my_text, "Score: %d", score);
    al_draw_text(size_32, al_map_rgb(200, 0, 30), largura_tela/3, altura_tela/2, 0, my_text);

    //reinicializa a tela
    al_flip_display(); 
    playing = 0; 
    al_rest(4); 
    
   al_destroy_timer(timer);
   al_destroy_display(display);
   al_destroy_event_queue(event_queue);
}
   

return 0;
}
 


       