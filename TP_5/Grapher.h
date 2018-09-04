#pragma once
#include <allegro5/allegro.h>
#include "Worm.h"

#define BACKGROUND_FILE	"Scenario.png"
#define N_WALKING_IMAGES	15
#define N_JUMPING_IMAGES	10
#define NO_ROTATION			0


class Grapher
{
public:
	Grapher(int xDisplay, int yDisplay);
	~Grapher();

	/*init_has_failed*/
	//Devuelve si fallo la inicializacion del Grapher
	//Relacionado con inicializadores del display y componentes de Allegro.
	bool init_has_failed();
	/*update*/
	//Actualiza el display con las posiciones actuales de los Worms.
	void update(Worm * wArray[], int wormCount);

private:
	ALLEGRO_DISPLAY * display;							//Display
	ALLEGRO_BITMAP  * background;						//Imagen de fondo
	ALLEGRO_BITMAP * walkingImages[N_WALKING_IMAGES];	//Arreglo de imagenes de caminata para el worm.
	ALLEGRO_BITMAP * jumpingImages[N_JUMPING_IMAGES];	//Arreglo de imagenes de salto para el worm.

	bool initError;

	/*init_allegro*/
	//Inicializa Allegro y un display con las proporciones indicadas.
	//Si falla devuelve false.
	bool init_allegro(int xDisplay, int yDisplay);

	/*set_background*/
	//Carga la imagen para el fondo y la muestra en el display.
	//Si falla devuelve false
	bool set_background();

	/*set_worm_images*/
	//Llena los array de bitmaps para caminar y saltar con las imagenes correspondientes.
	//Si falla devuelve false.
	bool set_worm_images();

	/*get_bitmap*/
	//Devuelve la imagen a mostrar de un Worm dependiendo de su estado y su contador de frames.
	ALLEGRO_BITMAP * get_bitmap(wormState_n currentState, uint frameCounter);

};

