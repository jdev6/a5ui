#include <string.h>

#include "a5ui.h"

ALLEGRO_MOUSE_STATE a5ui_mstate;
int a5ui_lclick_released = 0;
ALLEGRO_FONT* a5ui_font = NULL;

#define mouse_collision(x2,y2,w2,h2) (\
	a5ui_mstate.x < x2+w2 &&\
	x2 < a5ui_mstate.x+1 &&\
	a5ui_mstate.y < y2+h2 &&\
	y2 < a5ui_mstate.y+1 \
)

#define RECT_ARGS float x, float y, int w, int h

void a5ui_frame(void) {
	a5ui_lclick_released = 0;
	al_get_mouse_state(&a5ui_mstate);
}

void a5ui_text_dimensions(char* text, int* w, int* h, int* lines) {
	//count new lines
	int nl = 0;
	for (int i = 0; text[i]; i++) nl += (text[i] == '\n');

	//get  MAX number of chars in text (check each line) (FOR width)
	char* text_copy = malloc(strlen(text)+1);
	char* line;
	strcpy(text_copy, text);
	line = strtok(text_copy, "\n");
	int width = 0;
	while (line) {
		int tmp = al_get_text_width(a5ui_font, line);
		if (tmp > width) width = tmp;
		line = strtok(NULL, "\n");
	}
	free(text_copy);	

	int bbh;
	bbh = al_get_font_line_height(a5ui_font);
	*w = *w ? *w : width+4;
	*h = *h ? *h : bbh*(nl+1)+4;
	if (lines) *lines = nl;
}


void a5ui_label(RECT_ARGS, char* text, ALLEGRO_COLOR color) {
	int lines = 0;
	a5ui_text_dimensions(text, &w, &h, &lines);

	al_draw_filled_rounded_rectangle(x,y,x+w,y+h,3,3,color);
	al_draw_multiline_text(a5ui_font, A5UI_TEXT_COLOR, x + 2, y + 2, w, 0, 0, text);
}

int a5ui_button(RECT_ARGS, char* text) {
	return a5ui_text_button(x,y,w,h,text, A5UI_COLOR, A5UI_HOVER_COLOR, A5UI_CLICK_COLOR);
}

int a5ui_text_button(RECT_ARGS, char* text, ALLEGRO_COLOR col, ALLEGRO_COLOR hover_col, ALLEGRO_COLOR click_col) {
	a5ui_text_dimensions(text, &w, &h, NULL);

	ALLEGRO_COLOR color = col;
	int hover = mouse_collision(x,y,w,h);

	if (hover) {
		color = a5ui_mstate.buttons & 1 ? click_col : hover_col;
	}

	a5ui_label(x,y,w,h, text, color);

	return hover ? (a5ui_lclick_released ? A5UI_BUTTON_CLICK : A5UI_BUTTON_HOVER) : 0;
}

int a5ui_bitmap_button(float x, float y, ALLEGRO_BITMAP* bmp, ALLEGRO_BITMAP* hover_bmp, ALLEGRO_BITMAP* click_bmp) {
	hover_bmp = hover_bmp ? hover_bmp : bmp;
	click_bmp = click_bmp ? click_bmp : bmp;
	int w = al_get_bitmap_width(bmp);
	int h = al_get_bitmap_height(bmp);
	
	ALLEGRO_BITMAP* bitmap = bmp;
	int hover = mouse_collision(x,y,w,h);
	
	if (mouse_collision(x,y,w,h)) {
		bitmap = a5ui_mstate.buttons & 1 ? click_bmp : hover_bmp;
	}

	al_draw_bitmap(bitmap, x,y, 0);

	return hover ? (a5ui_lclick_released ? A5UI_BUTTON_CLICK : A5UI_BUTTON_HOVER) : 0;
}
