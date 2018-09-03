#include "Grapher.h"
#include <allegro5/allegro_image.h>
#include <string> 
#include "Vector.h"

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
	ALLEGRO_BITMAP * bit;
	for (int i = 0; i < wormCount; i++)
	{
		bit = get_bitmap(wArray[i]->get_currentState(), wArray[i]->get_frameCounter());
		al_draw_bitmap(bit, wArray[i]->get_pos().get_x(), wArray[i]->get_pos().get_y(), (wArray[i]->get_orientation()) ? ALLEGRO_FLIP_HORIZONTAL : NO_ROTATION);
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
	std::string wFile = "wwalking\\wwalk-F";
	std::string jFile = "wjump\\wjump-F";
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

ALLEGRO_BITMAP * Grapher::get_bitmap(wormState_n currentState, uint frameCounter)
{
	switch (currentState)
	{
		case START_JUMPING:
			if ((frameCounter >= 6) && (frameCounter <= 8))
			{
				return jumpingImages[frameCounter - 5 - 1]; //El -1 es porque la foto 1 se encuentra en la posicion 0 del arreglo.
			}
			else
			{
				return walkingImages[0];
			}
			break;
		case IDLE:
			return walkingImages[0];
			break;
		case START_MOVING:
			if ((frameCounter >= 6) && (frameCounter <= 8))
			{
				return walkingImages[frameCounter - 2 - 1];
			}
			else 
			{
				return walkingImages[0];
			}
			break;
		case MOVING:
		case STOP_MOVING:
			if ((frameCounter >= 1) && (frameCounter <= 8))
			{
				return walkingImages[frameCounter + 3 - 1];
			}
			else if ((frameCounter >= 1 + 14) && (frameCounter <= 8 + 14))
			{
				return walkingImages[frameCounter - 14 + 3 - 1];
			}
			else if ((frameCounter >= 1 + 14 * 2) && (frameCounter <= 8 + 14 * 2))
			{
				return walkingImages[frameCounter - 14*2 + 3 - 1];
			}
			else if ((frameCounter >= 1 + 14 * 3) && (frameCounter <= 8 + 14 * 3))
			{
				return walkingImages[frameCounter - 14 * 3 + 3 - 1];
			}
			else if ((frameCounter >= 9) && (frameCounter <= 13))
			{
				return walkingImages[frameCounter + 2 - 1];
			}
			else if ((frameCounter >= 9 + 14) && (frameCounter <= 13 + 14))
			{
				return walkingImages[frameCounter -14 + 2 - 1];
			}
			else if ((frameCounter >= 9 + 14 * 2) && (frameCounter <= 13 + 14 * 2))
			{
				return walkingImages[frameCounter - 14*2 + 2 - 1];
			}
			else if ((frameCounter >= 9 + 14 * 3) && (frameCounter <= 13 + 14 * 3))
			{
				return walkingImages[frameCounter - 14 * 3 + 2 - 1];
			}
			else if ((frameCounter % 14) == 0)
			{
				return walkingImages[3];
			}
		
			break;
		
		case JUMPING:
			return jumpingImages[3];
			break;
		case LANDING:
			return jumpingImages[frameCounter + 4 - 1];
			break;
	}
	return nullptr;
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


