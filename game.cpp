// standard headers
#include <stdio.h>

// allegro headers
#ifndef __ALLEGRO_INCLUDED__
#define __ALLEGRO_INCLUDED__

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h> // include the header with the image addon
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_native_dialog.h> // use allegro_dialog-5.0 in compile

#endif

// my headers
#include "hero.hpp"

const float FPS = 30;

int main(void) {
	ALLEGRO_DISPLAY *Screen = NULL;
	ALLEGRO_EVENT_QUEUE *EventQueue = NULL;
	ALLEGRO_EVENT Event;
	ALLEGRO_BITMAP *Image = NULL, /*Start Simon's Code */*ExitUpState = NULL, *ExitOverState = NULL/* End Simon's Code */; // object that holds the graphic. initialize it empty
	ALLEGRO_TIMER *Timer = NULL;

	// Start Simon's Code
	bool Exit = false, OverButton = false, keyDownDown = false, keyDownUp = false, keyDownLeft = false, keyDownRight = false;
	const int ButtonX = 10, ButtonY = 540, ButtonWidth = 100, ButtonHeight = 50;

	//Error checking
	if (!al_init()) {
		al_show_native_message_box(NULL, "Error!", "Allegro has failed to initialize.", 0, 0, ALLEGRO_MESSAGEBOX_ERROR);
		return -1;
	}
	if (!al_init_image_addon()) {
		al_show_native_message_box(NULL, "Error!", "Allegro image addon has failed to initialize!", 0, 0, ALLEGRO_MESSAGEBOX_ERROR);
		return -1;
	}

	Screen = al_create_display(800, 600);

	if (Screen == NULL) {
		al_show_native_message_box(Screen, "Error!", "Failed to create the display.", 0, 0, ALLEGRO_MESSAGEBOX_ERROR);
		return -1;
	}

	EventQueue = al_create_event_queue();

	if (EventQueue == NULL) {
		al_show_native_message_box(Screen, "Error!", "Failed to create the event queue.", 0, 0, ALLEGRO_MESSAGEBOX_ERROR);
		return -1;
	}

	if (!al_install_mouse()) {
		al_show_native_message_box(NULL, "Error!", "Failed to install mouse!", 0, 0, ALLEGRO_MESSAGEBOX_ERROR);
		return -1;
	}
	if (!al_install_keyboard()) {
		al_show_native_message_box(NULL, "Error!", "Failed to install keyboard!", 0, 0, ALLEGRO_MESSAGEBOX_ERROR);
	}

	// Removed: al_init();
	// Removed: al_install_keyboard();
	al_init_image_addon(); // this must be called after al_init to load images
	al_init_primitives_addon();

	// Removed: Screen = al_create_display(800,600);
	// Removed: EventQueue = al_create_event_queue();
	Timer = al_create_timer(1.0 / FPS);

	al_register_event_source(EventQueue, al_get_display_event_source(Screen));
	al_register_event_source(EventQueue, al_get_keyboard_event_source());
	al_register_event_source(EventQueue, al_get_timer_event_source(Timer));	
	// Added:
	al_register_event_source(EventQueue, al_get_mouse_event_source());

	ExitUpState = al_load_bitmap("chars/ExitUp.png");
	if (ExitUpState == NULL) {
		al_show_native_message_box(Screen, "Error!", "Failed to load -ExitUp.png-", 0, 0, ALLEGRO_MESSAGEBOX_ERROR);
		return -1;
	}

	ExitOverState = al_load_bitmap("chars/ExitOver.png");
	if (ExitOverState == NULL) {
		al_show_native_message_box(Screen, "Error!", "Failed to load -ExitOver.png-", 0, 0, ALLEGRO_MESSAGEBOX_ERROR);
		return -1;
	}
	// </Simon's Code>

	Hero hero1(400,300);
	hero1.loadSprite("chars/hero.png");
	
	// Removed: applies transform; scales 400%
	// Removed: ALLEGRO_TRANSFORM transform;
	// Removed: al_identity_transform(&transform);
	// Removed: al_scale_transform(&transform, 4, 4);
	// Removed: al_use_transform(&transform);

	hero1.draw();
	//al_flip_display();
	al_start_timer(Timer);

	// Moved: bool exit = false;
	while (!Exit) {
		if (OverButton == true) {
			al_draw_bitmap(ExitOverState, ButtonX, ButtonY, 0);
		}
		else {
			al_draw_bitmap(ExitUpState, ButtonX, ButtonY, 0);
		}

		al_flip_display();

		al_wait_for_event(EventQueue, &Event);

		if (Event.type == ALLEGRO_EVENT_MOUSE_AXES) {
			if ((Event.mouse.x >= ButtonX) && (Event.mouse.x <= ButtonX+ButtonWidth) && (Event.mouse.y >= ButtonY) && (Event.mouse.y <= ButtonY+ButtonHeight)) {
				OverButton = true;
			}
			else {
				OverButton = false;
			}
		}

		if (Event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			Exit = true;
		}

		if (Event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
			if (OverButton == true) {
				Exit = true;
			}
		}
		if (Event.type == ALLEGRO_EVENT_KEY_DOWN) {
			if (Event.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
				Exit = true;
			}
			if (Event.keyboard.keycode == ALLEGRO_KEY_DOWN) {
				keyDownDown = true;
			}
			else if (Event.keyboard.keycode == ALLEGRO_KEY_RIGHT) {
				keyDownRight = true;
			}
			else if (Event.keyboard.keycode == ALLEGRO_KEY_UP) {
				keyDownUp = true;
			}
			else if (Event.keyboard.keycode == ALLEGRO_KEY_LEFT) {
				keyDownLeft = true;
			}
		}
		if (Event.type == ALLEGRO_EVENT_KEY_UP) {
			if (keyDownDown == true) {
				keyDownDown = false;
			}
			else if (keyDownUp == true) {
				keyDownUp = false;
			}
			else if (keyDownLeft == true) {
				keyDownLeft = false;
			}
			else if (keyDownRight == true) {
				keyDownRight = false;
			}
		}
		if (keyDownDown == true) {
			hero1.setMotionDown();
			hero1.draw();
		}
		else if (keyDownUp == true) {
			hero1.setMotionUp();
			hero1.draw();
		}
		else if (keyDownRight == true) {
			hero1.setMotionRight();
			hero1.draw();
		}
		else if (keyDownLeft == true) {
			hero1.setMotionLeft();
			hero1.draw();
		}
		else {
			hero1.stopMotion();
		}
	}

	// <Simon's Code>>
	al_destroy_bitmap(ExitUpState);
	al_destroy_bitmap(ExitOverState);
	al_destroy_event_queue(EventQueue);
	al_destroy_display(Screen);
	// </Simon's Code>

	return 0;
}
