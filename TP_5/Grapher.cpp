#include "Grapher.h"
#include <allegro5/allegro_image.h>
#include <string> 
#include "Vector.h"

Grapher::Grapher(int xDisplay, int yDisplay)
{
	display = NULL;
	background = NULL;
	initError = false;
	if (!init_allegro(xDisplay, yDisplay))	//Chequea error
		initError = true;
}

Grapher::~Grapher()
{
	if(display)
		al_destroy_display(display);	//Si existe display, lo destruye.
	if(background)
		al_destroy_bitmap(background);	//Si existe background lo destruye
}

bool Grapher::init_has_failed()
{
	return initError;
}


void Grapher::update(Worm * wArray[], int wormCount)
{
	al_clear_to_color(al_map_rgb(0, 0, 0));	//Limpia pantalla
	al_draw_bitmap(background, 0, 0, 0);	//Dibuja fondo
	ALLEGRO_BITMAP * bit;
	for (int i = 0; i < wormCount; i++)		//Se dibuja cada Worm
	{
		bit = get_bitmap(wArray[i]->get_currentState(), wArray[i]->get_frameCounter());		//Se obtiene la imagen correspondiente para cada Worm.
		al_draw_bitmap			//Se muestra el Worm en el display
			(bit, 
			wArray[i]->get_pos().get_x(), wArray[i]->get_pos().get_y(), 
			(wArray[i]->get_orientation()) ? ALLEGRO_FLIP_HORIZONTAL : NO_ROTATION);	//Se rota o no la imagen dependiendo de la orientacion del Worm.
	}
	al_flip_display();
}

bool Grapher::set_background()
{
	background = al_load_bitmap(BACKGROUND_FILE);	//Se carga el fondo
	if (!background)								//Chequea error
		return false;
	
	al_draw_bitmap(background, 0, 0, 0);			//Se muestra el fondo

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
		currentPhoto =  wFile + std::to_string(i) + png;				//Se forma el path correspondiente a cada imagen.
		walkingImages[i-1] = al_load_bitmap(currentPhoto.c_str());		//Se carga cada imagen
		if (!walkingImages[i - 1])										//Chequea error
			return false;
	}
	for (int j = 1; j <= N_JUMPING_IMAGES; j++)
	{
		currentPhoto = jFile + std::to_string(j) + png;					//Se forma el path correspondiente a cada imagen.
		jumpingImages[j - 1] = al_load_bitmap(currentPhoto.c_str());	//Se carga cada imagen
		if (!jumpingImages[j - 1])										//Chequea error
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
				return walkingImages[frameCounter - 3];
			}
			else 
			{
				return walkingImages[0];
			}
			break;
		case MOVING:
		case STOP_MOVING:
			if (((frameCounter - 8) % 14) == 0)
			{
				/*Para el ultimo frame de cada ciclo se debera mostrar la imagen 4, almacenada en la posicion 3 del array.*/
				return walkingImages[3];
			}
			else 
			{
				for (int i = 0; i < 3; i++) //3: cantidad de repeticiones.
				{
					/*	Del frame 9 al 16 la imagen que se debe mostrar es "5" menos. P. ej. para el 9 se debe mostrar la imagen 4.
					*	Esta imagen se encuentra almacenada en el array en la posicion 3.
					*	Por esta razon se restan 6 y no 5.
					*	Como esta secuencia se debe repetir 3 veces, lo mismo sucedera para los frames entre 23 y 30 y entre 37 y 44.
					*	La unica diferencia sera que se debera restar [5 + (14 o 28) + 1] al indicador de posicion del array.
					*/
					if ((frameCounter >= (9 + 14*i)) && (frameCounter <= (16 +14*i)))
					{
						
						return walkingImages[frameCounter - 6 -14*i];
					}

					/*	Del frame 17 al 21 la imagen que se debe mostrar es "6" menos. P. ej. para el 17 se debe mostrar la imagen 13.
					*	Esta imagen se encuentra almacenada en el array en la posicion 12.
					*	Por esta razon se restan 7 y no 6.
					*	Como esta secuencia se debe repetir 3 veces, lo mismo sucedera para los frames entre 31 y 35 y entre 45 y 49.
					*	La unica diferencia sera que se debera restar [6 + (14 o 28) + 1] al indicador de posicion del array.
					*/
					else if ((frameCounter >= (17+14*i)) && (frameCounter <= (21+14*i)))
					{
						
						return walkingImages[frameCounter - 7 -14*i];
					}
				}
			}
			
			
			break;
		
		case JUMPING:
			return jumpingImages[3];
			break;
		case LANDING:
			return jumpingImages[frameCounter + 3];
			break;
	}
	return nullptr;
}

bool Grapher::init_allegro(int xDisplay, int yDisplay)
{
	if (!al_init())										//Chequea error
		return false;
	
	display = al_create_display(xDisplay, yDisplay);	//Crea display

	if ((!display) || (!al_init_image_addon()))			//Chequea error
		return false;
	
	if ((!set_background()) || (!set_worm_images()))	//Chequea error
		return false;

	return true;
	
}


