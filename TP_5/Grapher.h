#pragma once
#include <allegro5/allegro.h>

#define BACKGROUND_FILE	"Scenario.png"

class Grapher
{
public:
	Grapher(int xDisplay, int yDisplay);

	/*init_has_failed*/
	//Devuelve si fallo la inicializacion del Grapher
	//Relacionado con inicializadores del display y componentes de Allegro.
	bool init_has_failed();
	void destroy();
private:
	ALLEGRO_DISPLAY * display;
	ALLEGRO_BITMAP  * background;
	bool initError;
	bool init_allegro(int xDisplay, int yDisplay);
	bool set_background();
};

