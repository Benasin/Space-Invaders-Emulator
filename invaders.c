#include <SDL2/SDL.h>
#include <stdio.h>
#include <time.h>
#include "cpu8080.h"

#define TIC (1000.0 / 60.0)

const int SCREEN_WIDTH = 224;
const int SCREEN_HEIGHT = 256;

SDL_Window* window = NULL;
SDL_Surface* window_surface = NULL;
SDL_Surface* surface_buffer = NULL;

void drawPixel(uint32_t color, int x, int y) {
	uint32_t* pixel = (uint32_t*) surface_buffer->pixels + x + y * SCREEN_WIDTH; 
	*pixel = color;
}

void update_screen(State8080* state) {
	for(int i = 0; i < SCREEN_WIDTH; i++) {
		for(int j = 31; j >= 0; j--) {
			uint8_t x = state->memory[0x2400+i*32+j];
			for(int k = 0; k < 8; k++) {
				if((x << k) & 0x80) {
					drawPixel(0xFFFFFF, i, (31 - j)*8 + k);
				} else {
					drawPixel(0x000000, i, (31 - j)*8 + k);
				}
			}
		}
	}
	SDL_BlitScaled(surface_buffer, NULL, window_surface, NULL); 
	if(SDL_UpdateWindowSurface(window)) 
		puts(SDL_GetError());
}

void Emulate_Controller(State8080* state) {
	SDL_Event e;
	while(SDL_PollEvent(&e) != 0) {
		if(e.type == SDL_QUIT){
			exit(0);
		} else if(e.type == SDL_KEYDOWN) {
			switch(e.key.keysym.sym) {
				case 'c':
					state->p1_input_port |= 0x1; //Insert coin
					break;
				case '1':
					state->p1_input_port |= 0x4; //Play player 1
					break;
				case '2':
					state->p1_input_port |= 0x2; //Play player 2
					break;
				case 'v':
					state->p1_input_port |= 0x10;//Shoot player 1
					break;
				case 'z':
					state->p1_input_port |= 0x20;//Move left p1
					break;
				case 'x':
					state->p1_input_port |= 0x40;//Move right p1
					break;
				case '.':
					state->p2_input_port |= 0x10;//Shoot p2
					break;
				case 'n':
					state->p2_input_port |= 0x20;//Move left p2
					break;
				case 'm':
					state->p2_input_port |= 0x40;//Move right p2
					break;
			}
		} else if(e.type == SDL_KEYUP) {
			switch(e.key.keysym.sym) {
				case 'c':
					state->p1_input_port &= 0;
					break;
				case '1':
					state->p1_input_port &= ~(0x4);
					break;
				case '2':
					state->p1_input_port &= ~(0x2);
					break;
				case 'v':
					state->p1_input_port &= ~(0x10);
					break;
				case 'z':
					state->p1_input_port &= ~(0x20);
					break;
				case 'x':
					state->p1_input_port &= ~(0x40);
					break;
				case '.':
					state->p2_input_port &= ~(0x10);
					break;
				case 'n':
					state->p2_input_port &= ~(0x20);
					break;
				case 'm':
					state->p2_input_port &= ~(0x40);
					break;
			}	
		}
	}
}

int init_screen() {
	if(SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL could not initialize! %s\n", SDL_GetError());
		return -1;
	} else {
		//Create window
		window = SDL_CreateWindow("Space invaders", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 2*SCREEN_WIDTH, 2*SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if(window == NULL) {
			printf("Window could not be created! %s\n", SDL_GetError());
			return -1;
		} else {
			window_surface = SDL_GetWindowSurface(window);
			surface_buffer = SDL_CreateRGBSurface(0, SCREEN_WIDTH, SCREEN_HEIGHT, 32, 0, 0, 0, 0);
			return 0;
		}
	}
}

void Push_Address(State8080* state, uint16_t addr) {
	state->memory[state->sp - 1] = (addr & 0xFF00) >> 8;
	state->memory[state->sp - 2] = (addr & 0xFF);
	state->sp -= 2;
}

void Generate_Interrupt(State8080* state, uint16_t addr) {
	Push_Address(state, state->pc);
	state->pc = addr; 
	state->int_enable = 0;
}

void Emulate_Shift_Register(State8080* state) {
	unsigned char* code = &state->memory[state->pc];
	static uint16_t shift_register;
	static int shift_offset;
	
	if(*code == 0xDB) { //IN D8
		switch(code[1]){
			case 0:
				state->a = 0xf;
				break;
			case 1: //Read input player 1
				state->a = state->p1_input_port;
				break;
			case 2: //Read input player 2
				state->a = state->p2_input_port;
				break;
			case 3: //Shift and return result
				state->a = (shift_register >> (8 - shift_offset)) & 0xFF;
				break;
		}
	} else if(*code == 0xD3) { //OUT D8
		switch(code[1]){
			case 2: //Set the offset
				shift_offset = state->a;
				break;
			case 4: //Set value for shift register
				shift_register = (state->a << 8) | (shift_register >> 8);
				break;
		}
	}
}

void CPU_run(State8080* state, long cycles) {
	int i = 0;
	while(i < cycles) {
		i += cycles8080[state->memory[state->pc]];
		Emulate_Shift_Register(state);	
		Emulate8080(state);	
	}
}

int main(int argc, char* argv[]) {
	State8080* state = calloc(1,sizeof(State8080));
	
	LoadROM(argv[1], state, 0x0000);

	if(init_screen() < 0) {
		exit(1);
	}

	uint32_t last_tic = SDL_GetTicks();
	while(1) {

		if((SDL_GetTicks() - last_tic) >= TIC) {
			last_tic = SDL_GetTicks();	

			CPU_run(state, (2000 * TIC)/2);

			if(state->int_enable) {
				Generate_Interrupt(state, 0x0008);
			}

			CPU_run(state, (2000 * TIC)/2);
			update_screen(state);
			Emulate_Controller(state);

			if(state->int_enable) {
				Generate_Interrupt(state, 0x0010);
			}
		}
	}
	return 0;
}
