#include "Grapher.h"
#include <allegro5/allegro_image.h>

Grapher::Grapher(int xDisplay, int yDisplay)
{
	display = NULL;
	background = NULL;
	initError = false;
	if (!init_allegro(xDisplay, yDisplay))
		initError = true;
}

bool Grapher::init_has_failed()
{
	return initError;
}

void Grapher::destroy()
{
	al_destroy_display(display);
	al_destroy_bitmap(background);
}

bool Grapher::set_background()
{
	background = al_load_bitmap(BACKGROUND_FILE);
	if (!background)
		return false;
	
	al_draw_bitmap(background, 0, 0, 0);

	al_flip_display();
	return true;

}

bool Grapher::init_allegro(int xDisplay, int yDisplay)
{
	if (!al_init())
		return false;
	
	display = al_create_display(xDisplay, yDisplay);

	if ((!display) || (!al_init_image_addon()))
		return false;
	
	if (!setmode)
		return false;

	return true;
	
}


