#include "Grapher.h"
#include <allegro5/allegro_image.h>
#include <string> 

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

void Grapher::update(Worm * wArray[], int wormCount)
{
	al_clear_to_color(al_map_rgb(0, 0, 0));
	al_draw_bitmap(background, 0, 0, 0);
	
	for (int i = 0; i < wormCount; i++)
	{
		if (wArray[i]->get_currentState() == MOVING)
		{
			al_draw_bitmap(walkingImages[wArray[i]->get_frameCounter()], wArray[i]->get_pos.get_x(), wArray[i]->get_pos.get_y(), (wArray[i]->get_orientation) ? ALLEGRO_FLIP_HORIZONTAL : NO_ROTATION);
		}
		else if (wArray[i]->get_currentState() == JUMP)
		{
			al_draw_bitmap(jumpingImages[wArray[i]->get_frameCounter()], wArray[i]->get_pos.get_x(), wArray[i]->get_pos.get_y(), (wArray[i]->get_orientation) ? ALLEGRO_FLIP_HORIZONTAL : NO_ROTATION);
		}
	}
	al_flip_display();
	
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

bool Grapher::set_worm_images()
{
	std::string wFile = "wwalk-F";
	std::string jFile = "wjump-F";
	std::string png = ".png";
	std::string currentPhoto;

	for (int i = 1; i <= N_WALKING_IMAGES; i++)
	{
		currentPhoto =  wFile + std::to_string(i) + png;
		walkingImages[i-1] = al_load_bitmap(currentPhoto.c_str());
		if (!walkingImages[i - 1])
			return false;
	}
	for (int j = 1; j <= N_JUMPING_IMAGES; j++)
	{
		currentPhoto = jFile + std::to_string(j) + png;
		jumpingImages[j - 1] = al_load_bitmap(currentPhoto.c_str());
		if (!jumpingImages[j - 1])
			return false;
	}

	return true;
}

bool Grapher::init_allegro(int xDisplay, int yDisplay)
{
	if (!al_init())
		return false;
	
	display = al_create_display(xDisplay, yDisplay);

	if ((!display) || (!al_init_image_addon()))
		return false;
	
	if ((!set_background()) || (!set_worm_images()))
		return false;

	return true;
	
}


