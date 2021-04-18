
ALLEGRO_VERSION=5.0.10
MINGW_VERSION=4.7.0
FOLDER=E:

FOLDER_NAME=\allegro-$(ALLEGRO_VERSION)-mingw-$(MINGW_VERSION)
PATH_ALLEGRO=$(FOLDER)$(FOLDER_NAME)
LIB_ALLEGRO=\lib\liballegro-$(ALLEGRO_VERSION)-monolith-mt.a
INCLUDE_ALLEGRO=\include

all:  guitar_hero.exe teste.exe guitar_hero2.exe teste2.exe 

teste.exe: teste.o
	gcc -o teste.exe teste.o $(PATH_ALLEGRO)$(LIB_ALLEGRO)

teste.o: teste.c
	gcc -I $(PATH_ALLEGRO)$(INCLUDE_ALLEGRO) -c teste.c

teste2.exe: teste2.o
	gcc -o teste2.exe teste2.o $(PATH_ALLEGRO)$(LIB_ALLEGRO)

teste2.o: teste2.c
	gcc -I $(PATH_ALLEGRO)$(INCLUDE_ALLEGRO) -c teste2.c
	
guitar_hero.exe: guitar_hero.o
	gcc -o guitar_hero.exe guitar_hero.o $(PATH_ALLEGRO)$(LIB_ALLEGRO)

guitar_hero.o: guitar_hero.c
	gcc -I $(PATH_ALLEGRO)$(INCLUDE_ALLEGRO) -c guitar_hero.c		

guitar_hero2.exe: guitar_hero2.o
	gcc -o guitar_hero2.exe guitar_hero2.o $(PATH_ALLEGRO)$(LIB_ALLEGRO)

guitar_hero2.o: guitar_hero2.c
	gcc -I $(PATH_ALLEGRO)$(INCLUDE_ALLEGRO) -c guitar_hero2.c	


 
clean:
	
	del teste.o
	del teste.exe
	del guitar_hero.o
	del guitar_hero.exe
	del teste2.o
	del teste2.exe
	del guitar_hero2.o
	del guitar_hero2.exe


