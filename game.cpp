// standard headers
#include <stdio.h>

// allegro headers
#ifndef __ALLEGRO_INCLUDED__
#define __ALLEGRO_INCLUDED__

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h> // include the header with the image addon
#include <allegro5/allegro_primitives.h>

#endif

// my headers
#include "hero.hpp"

const float FPS = 30;

int main(void) {
	ALLEGRO_DISPLAY *Screen = NULL;
	ALLEGRO_EVENT_QUEUE *EventQueue = NULL;
	ALLEGRO_EVENT Event;
	ALLEGRO_BITMAP *Image = NULL; // object that holds the graphic. initialize it empty
	ALLEGRO_TIMER *Timer = NULL;
	

	al_init();
	al_install_keyboard();
	al_init_image_addon(); // this must be called after al_init to load images
	al_init_primitives_addon();

	Screen = al_create_display(800,600);
	EventQueue = al_create_event_queue();
	Timer = al_create_timer(1.0 / FPS);

	al_register_event_source(EventQueue, al_get_display_event_source(Screen));
	al_register_event_source(EventQueue, al_get_keyboard_event_source());
	al_register_event_source(EventQueue, al_get_timer_event_source(Timer));	

	Hero hero1(100,100);
	hero1.loadSprite("chars/hero.png");
	
	// applies transform; scales 400%
	ALLEGRO_TRANSFORM transform;
	al_identity_transform(&transform);
	al_scale_transform(&transform, 4, 4);
	al_use_transform(&transform);

	hero1.draw();
	al_flip_display();
	al_start_timer(Timer);

	bool exit = false;
	while (!exit) {
		al_wait_for_event(EventQueue, &Event);

		if (Event.type == ALLEGRO_EVENT_TIMER) {
			hero1.draw();
			
			al_flip_display();
		}

		else if(Event.type == ALLEGRO_EVENT_KEY_DOWN) {
			switch(Event.keyboard.keycode) {
				case ALLEGRO_KEY_ESCAPE:
					exit = true;
					break;
				case ALLEGRO_KEY_LEFT:
					hero1.setMotionLeft();
					break;
				case ALLEGRO_KEY_RIGHT:
					hero1.setMotionRight();
					break;
				case ALLEGRO_KEY_UP:
					hero1.setMotionUp();
					break;
				case ALLEGRO_KEY_DOWN:
					hero1.setMotionDown();
					break;
				case ALLEGRO_KEY_SPACE:
					hero1.stopMotion();
					break;
			}

			hero1.draw();
		}		
	}

	return 0;
}
