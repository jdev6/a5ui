#ifndef A5UI_H
#define A5UI_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>

//DEFAULT colors
#define A5UI_COLOR al_map_rgb(66,66,66)
#define A5UI_HOVER_COLOR al_map_rgb(50,153,187)
#define A5UI_CLICK_COLOR al_map_rgb(255,153,0)
#define A5UI_TEXT_COLOR al_map_rgb(188,188,188)

enum a5ui_button_state {
	A5UI_BUTTON_HOVER = 1,
	A5UI_BUTTON_CLICK = 2
};

//set whghen event of MOUSE key up  is button 1
int a5ui_lclick_released;

//set at INIT
ALLEGRO_FONT* a5ui_font;

//call EVERY frame before. processing events
void a5ui_frame(void);

//juts text label
void a5ui_label(float x, float y, int w, int h, char* text, ALLEGRO_COLOR color);

//button
int a5ui_button(float x, float y, int w, int h, char* text);

//BUTTON with colors options
int a5ui_text_button(float x, float y, int w, int h, char* text, ALLEGRO_COLOR col, ALLEGRO_COLOR hover_col, ALLEGRO_COLOR click_col);

//IMAGe button
int a5ui_bitmap_button(float x, float y, ALLEGRO_BITMAP* bmp, ALLEGRO_BITMAP* hover_bmp, ALLEGRO_BITMAP* click_bmp);

#endif
