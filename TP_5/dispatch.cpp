

void dispatch(eventType ev, ...) // worm pointer
{
	switch (ev)
	{
	case POSSIBLE_WORM_MOVE:
	{
		for (int i = 0; i < worm.get_count(); i++)
		{
			wArray[i]->start_moving(keyUnichar);
		}
	} break;
	case REFRESH:
		for (int i = 0; i < worm.get_count(); i++)
		{
			wArray[i]->update(); // increment frameCount of worm.
			grapher.update();
		}
	default:
		break;
	}
}