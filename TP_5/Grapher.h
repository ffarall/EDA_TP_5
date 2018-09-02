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

	/*init_has_failed*/
	//Devuelve si fallo la inicializacion del Grapher
	//Relacionado con inicializadores del display y componentes de Allegro.
	bool init_has_failed();
	void destroy();
	void update(Worm * wArray[], int wormCount);
private:
	ALLEGRO_DISPLAY * display;
	ALLEGRO_BITMAP  * background;
	ALLEGRO_BITMAP * walkingImages[N_WALKING_IMAGES];
	ALLEGRO_BITMAP * jumpingImages[N_JUMPING_IMAGES];

	bool initError;
	bool init_allegro(int xDisplay, int yDisplay);
	bool set_background();
	bool set_worm_images();

};

