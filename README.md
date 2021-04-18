# Guitar-Hero-3

O jogo Guitar Hero funciona da seguinte maneira: na tela de jogo existem quatro retas, em cada reta iram descer notas de uma determinada cor (verde, vermelho, amarelo e azul)  até uma zona limite. O objetivo do jogo é conseguir a maior pontuação possível, para isso é necessário apertar a tecla correspondente a cada reta quando a nota dessa reta atingir a zona limite, caso isso aconteça sua pontuação aumentará e será emitido o som de um acorde de guitarra, caso contrário sua pontuação decrescerá e será emitido um BEEP grave. No final da música será exibido sua pontuação dessa partida e seu recorde de pontuação.

# Manual de Uso

Teclas:

• Q – Corresponde a primeira reta onde descerá as notas verdes.

• W – Corresponde a segunda reta onde descerá as notas vermelhas.

• E – Corresponde a terceira reta onde descerá as notas amarelas.

• R – Corresponde a quarta reta onde descerá as notas azuis.

• Barra de espaço  – Corresponde a quinta reta onde descerá as notas laranjas.

OBS: A dificuldade não altera a velocidade das notas e nem as cores das notas que irão ser utilizadas, ela modifica apenas a frequência em que as notas aparecem na tela.

Apagar – Encerra o jogo, caso esteja no meio da partida exibe a pontuação.
	 
# Detalhes da Implementação

Todas os notas do jogo são uma estrutura chamada Nota, que contem um float x e um y para determinar a posição na tela, um float dx para determinar a variação de posição, um float largura e altura que armazenam a dimensão da nota, um int para o status da nota (se está na tela ou não), um int para determinar o id que seria em qual reta ele está, e uma variável do tipo ALLEGRO_BITMAP para determinar a cor da nota. Como a velocidade de descida das notas é padrões, ela está declarada como variável global dy.

# Funções:

• cria_menu: Recebe como parâmetro uma variável do tipo ALLEGRO_DISPLAY e uma do tipo ALLEGRO_BITMAP  , desenha o menu de seleção de dificuldade.
    
• cria_cenario:  Recebe como parâmetro uma variável do tipo ALLEGRO_DISPLAY, uma do tipo ALLEGRO_BITMAP e outra do tipo ALLEGRO_FONT, desenha os cenários do jogo.
    
• cria_nota: Recebe como parâmetro o endereço i de um vetor de strings ,um número (no caso é o i) e largura e altura da nota padrão, preenche a string de 25 notas, 5 verdes, 	5 vermelhos, 5 amarelos , 5 azuis e 5 laranjas.
    
• desenhar_nota: Recebe o endereço da estrutura de uma nota e cria uma nota com os dados obtidos dessa estrutura. 
    
•  desenhar_notasS: Recebe o endereço da estrutura da nota e sorteia uma nota para ser criado, depois envia essa nota para a função desenhar_notas.
    
•  desenhar_notasD: Recebe o endereço da estrutura da nota e sorteia duas notas para serem criadas, depois envia essas notas para a função desenhar_nota.
    
• desenhar_notasT: Recebe o endereço da estrutura da nota e sorteia três notas para serem criadas, depois envia essas notas para a função desenhar_nota.
    
• checagem: Recebe o endereço da estrutura da nota, o endereço da sua nota, uma variável i, a pontuação do jogador, uma variável do tipo ALLEGRO_TIME, duas variáveis do tipo 	ALLEGRO_SAMPLE, as dimensões da nota, o multiplicador de pontuação e uma flag. Essa função checa se quando o jogador apertar uma das teclas existe alguma nota na área 		limite correspondente a essa tecla; caso isso aconteça sua pontuação aumentará e será emitido o som de um acorde de guitarra, caso contrário sua pontuação decrescerá e 	será emitido um BEEP grave e será zerado a sua pontuação de notas sequenciais. A função retorna a pontuação do jogador. 
    
• Multiplicador: Recebe o número de notas acertadas em sequência e a partir dele define qual será o multiplicador a ser utilizado(x1, x2, x3 ou x4).
      
# Outras funcionalidades que não foram separadas em funções incluem: 
      
• Sortear o tipo de nota (simples, dupla ou tripla).
    
• Impedir que as notas se sobreponham.
    
• Fazer as notas descerem.
    
• Escrever a pontuação e o recorde no final.
    
• Tocar a música de fundo.
    
• Fazer a movimentação das teclas do menu.
    
• Desenhar alguns menus.
    
• Fechar a tela principal quando todas as notas forem tocadas.
    
• Caso o recorde seja quebrado será emitido um som de aplausos.
