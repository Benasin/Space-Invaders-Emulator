#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "cpu8080.h"

//#define FOR_CPUDIAG 0

unsigned char cycles8080[] = {
	4, 10, 7, 5, 5, 5, 7, 4, 4, 10, 7, 5, 5, 5, 7, 4, //0x00..0x0f
	4, 10, 7, 5, 5, 5, 7, 4, 4, 10, 7, 5, 5, 5, 7, 4, //0x10..0x1f
	4, 10, 16, 5, 5, 5, 7, 4, 4, 10, 16, 5, 5, 5, 7, 4, //etc
	4, 10, 13, 5, 10, 10, 10, 4, 4, 10, 13, 5, 5, 5, 7, 4,
	
	5, 5, 5, 5, 5, 5, 7, 5, 5, 5, 5, 5, 5, 5, 7, 5, //0x40..0x4f
	5, 5, 5, 5, 5, 5, 7, 5, 5, 5, 5, 5, 5, 5, 7, 5,
	5, 5, 5, 5, 5, 5, 7, 5, 5, 5, 5, 5, 5, 5, 7, 5,
	7, 7, 7, 7, 7, 7, 7, 7, 5, 5, 5, 5, 5, 5, 7, 5,
	
	4, 4, 4, 4, 4, 4, 7, 4, 4, 4, 4, 4, 4, 4, 7, 4, //0x80..8x4f
	4, 4, 4, 4, 4, 4, 7, 4, 4, 4, 4, 4, 4, 4, 7, 4,
	4, 4, 4, 4, 4, 4, 7, 4, 4, 4, 4, 4, 4, 4, 7, 4,
	4, 4, 4, 4, 4, 4, 7, 4, 4, 4, 4, 4, 4, 4, 7, 4,
	
	11, 10, 10, 10, 17, 11, 7, 11, 11, 10, 10, 10, 10, 17, 7, 11, //0xc0..0xcf
	11, 10, 10, 10, 17, 11, 7, 11, 11, 10, 10, 10, 10, 17, 7, 11, 
	11, 10, 10, 18, 17, 11, 7, 11, 11, 5, 10, 5, 17, 17, 7, 11, 
	11, 10, 10, 4, 17, 11, 7, 11, 11, 5, 10, 4, 17, 17, 7, 11, 
};


void Disassemble8080(unsigned char* codebuffer, int pc) {
	unsigned char* code = &codebuffer[pc];
	printf("%04x ", pc);
	switch(*code) {
		case 0x00: printf("NOP"); break;
		case 0x01: printf("LXI B, #$%02x%02x",code[2],code[1]); break;
		case 0x02: printf("STAX B"); break;
		case 0x03: printf("INX B"); break;
		case 0x04: printf("INR B"); break;
		case 0x05: printf("DCR B"); break;
		case 0x06: printf("MVI B, #$%02x", code[1]); break;
		case 0x07: printf("RLC"); break;
		case 0x09: printf("DAD B"); break;
		case 0x0A: printf("LDAX B"); break;
		case 0x0B: printf("DCR B"); break;
		case 0x0C: printf("INR C"); break;
		case 0x0D: printf("DCR C"); break;
		case 0x0E: printf("MVI C, #$%02x", code[1]); break;
		case 0x0F: printf("RRC"); break;
		case 0x11: printf("LXI D, #$%02x%02x",code[2],code[1]); break;
		case 0x12: printf("STAX D"); break;
		case 0x13: printf("INX D"); break;
		case 0x14: printf("INR D"); break;
		case 0x15: printf("DCR D"); break;
		case 0x16: printf("MVI D, #$%02x", code[1]); break;
		case 0x17: printf("RAL"); break;
		case 0x19: printf("DAD D"); break;
		case 0x1A: printf("LDAX D"); break;
		case 0x1B: printf("DCX D"); break;
		case 0x1C: printf("INR E"); break;
		case 0x1D: printf("DCR E"); break;
		case 0x1E: printf("MVI E, #$%02x", code[1]); break;
		case 0x1F: printf("RAR"); break;
		case 0x21: printf("LXI H, #$%02x%02x",code[2],code[1]); break;
		case 0x22: printf("SHLD $%02x%02x",code[2],code[1]); break;
		case 0x23: printf("INX H"); break;
		case 0x24: printf("INR H"); break;
		case 0x25: printf("DCR H"); break;
		case 0x26: printf("MVI H, #$%02x", code[1]); break;
		case 0x27: printf("DAA"); break;
		case 0x29: printf("DAD H"); break;
		case 0x2A: printf("LHLD $%02x%02x",code[2],code[1]); break;
		case 0x2B: printf("DCX H"); break;
		case 0x2C: printf("INR L"); break;
		case 0x2D: printf("DCR L"); break;
		case 0x2E: printf("MVI L, #$%02x", code[1]); break;
		case 0x2F: printf("CMA"); break;
		case 0x31: printf("LXI SP, #$%02x%02x",code[2],code[1]); break;
		case 0x32: printf("STA $%02x%02x",code[2],code[1]); break;
		case 0x33: printf("INX SP"); break;
		case 0x34: printf("INR M"); break;
		case 0x35: printf("DCR M"); break;
		case 0x36: printf("MVI M, #$%02x", code[1]); break;
		case 0x37: printf("STC"); break;
		case 0x39: printf("DAD SP"); break;
		case 0x3A: printf("LDA $%02x%02x",code[2],code[1]); break;
		case 0x3B: printf("DCX SP"); break;
		case 0x3C: printf("INR A"); break;
		case 0x3D: printf("DCR A"); break;
		case 0x3E: printf("MVI A, #$%02x", code[1]); break;
		case 0x3F: printf("CMC"); break;
		case 0x40: printf("MOV B,B"); break;
		case 0x41: printf("MOV B,C"); break;
		case 0x42: printf("MOV B,D"); break;
		case 0x43: printf("MOV B,E"); break;
		case 0x44: printf("MOV B,H"); break;
		case 0x45: printf("MOV B,L"); break;
		case 0x46: printf("MOV B,M"); break;
		case 0x47: printf("MOV B,A"); break;
		case 0x48: printf("MOV C,B"); break;
		case 0x49: printf("MOV C,C"); break;
		case 0x4A: printf("MOV C,D"); break;
		case 0x4B: printf("MOV C,E"); break;
		case 0x4C: printf("MOV C,H"); break;
		case 0x4D: printf("MOV C,L"); break;
		case 0x4E: printf("MOV C,M"); break;
		case 0x4F: printf("MOV C,A"); break;
		case 0x50: printf("MOV D,B"); break;
		case 0x51: printf("MOV D,C"); break;
		case 0x52: printf("MOV D,D"); break;
		case 0x53: printf("MOV D,E"); break;
		case 0x54: printf("MOV D,H"); break;
		case 0x55: printf("MOV D,L"); break;
		case 0x56: printf("MOV D,M"); break;
		case 0x57: printf("MOV D,A"); break;
		case 0x58: printf("MOV E,B"); break;
		case 0x59: printf("MOV E,C"); break;
		case 0x5A: printf("MOV E,D"); break;
		case 0x5B: printf("MOV E,E"); break;
		case 0x5C: printf("MOV E,H"); break;
		case 0x5D: printf("MOV E,L"); break;
		case 0x5E: printf("MOV E,M"); break;
		case 0x5F: printf("MOV E,A"); break;
		case 0x60: printf("MOV H,B"); break;
		case 0x61: printf("MOV H,C"); break;
		case 0x62: printf("MOV H,D"); break;
		case 0x63: printf("MOV H,E"); break;
		case 0x64: printf("MOV H,H"); break;
		case 0x65: printf("MOV H,L"); break;
		case 0x66: printf("MOV H,M"); break;
		case 0x67: printf("MOV H,A"); break;
		case 0x68: printf("MOV L,B"); break;
		case 0x69: printf("MOV L,C"); break;
		case 0x6A: printf("MOV L,D"); break;
		case 0x6B: printf("MOV L,E"); break;
		case 0x6C: printf("MOV L,H"); break;
		case 0x6D: printf("MOV L,L"); break;
		case 0x6E: printf("MOV L,M"); break;
		case 0x6F: printf("MOV L,A"); break;
		case 0x70: printf("MOV M,B"); break;
		case 0x71: printf("MOV M,C"); break;
		case 0x72: printf("MOV M,D"); break;
		case 0x73: printf("MOV M,E"); break;
		case 0x74: printf("MOV M,H"); break;
		case 0x75: printf("MOV M,L"); break;
		case 0x76: printf("HLT"); break;
		case 0x77: printf("MOV M,A"); break;
		case 0x78: printf("MOV A,B"); break;
		case 0x79: printf("MOV A,C"); break;
		case 0x7A: printf("MOV A,D"); break;
		case 0x7B: printf("MOV A,E"); break;
		case 0x7C: printf("MOV A,H"); break;
		case 0x7D: printf("MOV A,L"); break;
		case 0x7E: printf("MOV A,M"); break;
		case 0x7F: printf("MOV A,A"); break;
		case 0x80: printf("ADD B"); break;
		case 0x81: printf("ADD C"); break;
		case 0x82: printf("ADD D"); break;
		case 0x83: printf("ADD E"); break;
		case 0x84: printf("ADD H"); break;
		case 0x85: printf("ADD L"); break;
		case 0x86: printf("ADD M"); break;
		case 0x87: printf("ADD A"); break;
		case 0x88: printf("ADC B"); break;
		case 0x89: printf("ADC C"); break;
		case 0x8A: printf("ADC D"); break;
		case 0x8B: printf("ADC E"); break;
		case 0x8C: printf("ADC H"); break;
		case 0x8D: printf("ADC L"); break;
		case 0x8E: printf("ADC M"); break;
		case 0x8F: printf("ADC A"); break;
		case 0x90: printf("SUB B"); break;
		case 0x91: printf("SUB C"); break;
		case 0x92: printf("SUB D"); break;
		case 0x93: printf("SUB E"); break;
		case 0x94: printf("SUB H"); break;
		case 0x95: printf("SUB L"); break;
		case 0x96: printf("SUB M"); break;
		case 0x97: printf("SUB A"); break;
		case 0x98: printf("SBB B"); break;
		case 0x99: printf("SBB C"); break;
		case 0x9A: printf("SBB D"); break;
		case 0x9B: printf("SBB E"); break;
		case 0x9C: printf("SBB H"); break;
		case 0x9D: printf("SBB L"); break;
		case 0x9E: printf("SBB M"); break;
		case 0x9F: printf("SBB A"); break;
		case 0xA0: printf("ANA B"); break;
		case 0xA1: printf("ANA C"); break;
		case 0xA2: printf("ANA D"); break;
		case 0xA3: printf("ANA E"); break;
		case 0xA4: printf("ANA H"); break;
		case 0xA5: printf("ANA L"); break;
		case 0xA6: printf("ANA M"); break;
		case 0xA7: printf("ANA A"); break;
		case 0xA8: printf("XRA B"); break;
		case 0xA9: printf("XRA C"); break;
		case 0xAA: printf("XRA D"); break;
		case 0xAB: printf("XRA E"); break;
		case 0xAC: printf("XRA H"); break;
		case 0xAD: printf("XRA L"); break;
		case 0xAE: printf("XRA M"); break;
		case 0xAF: printf("XRA A"); break;
		case 0xB0: printf("ORA B"); break;
		case 0xB1: printf("ORA C"); break;
		case 0xB2: printf("ORA D"); break;
		case 0xB3: printf("ORA E"); break;
		case 0xB4: printf("ORA H"); break;
		case 0xB5: printf("ORA L"); break;
		case 0xB6: printf("ORA M"); break;
		case 0xB7: printf("ORA A"); break;
		case 0xB8: printf("CMP B"); break;
		case 0xB9: printf("CMP C"); break;
		case 0xBA: printf("CMP D"); break;
		case 0xBB: printf("CMP E"); break;
		case 0xBC: printf("CMP H"); break;
		case 0xBD: printf("CMP L"); break;
		case 0xBE: printf("CMP M"); break;
		case 0xBF: printf("CMP A"); break;
		case 0xC0: printf("RNZ"); break;
		case 0xC1: printf("POP B"); break;
		case 0xC2: printf("JNZ $%02x%02x",code[2],code[1]); break;
		case 0xC3: printf("JMP $%02x%02x",code[2],code[1]); break;
		case 0xC4: printf("CNZ $%02x%02x",code[2],code[1]); break;
		case 0xC5: printf("PUSH B"); break;
		case 0xC6: printf("ADI #$%02x",code[1]); break;
		case 0xC7: printf("RST 0"); break;
		case 0xC8: printf("RZ"); break;
		case 0xC9: printf("RET"); break;
		case 0xCA: printf("JZ $%02x%02x",code[2],code[1]); break;
		case 0xCC: printf("CZ $%02x%02x",code[2],code[1]); break;
		case 0xCD: printf("CALL $%02x%02x",code[2],code[1]); break;
		case 0xCE: printf("ACI #$%02x",code[1]); break;
		case 0xCF: printf("RST 1"); break;
		case 0xD0: printf("RNC"); break;
		case 0xD1: printf("POP D"); break;
		case 0xD2: printf("JNC $%02x%02x",code[2],code[1]); break;
		case 0xD3: printf("OUT #$%02x",code[1]); break;
		case 0xD4: printf("CNC $%02x%02x",code[2],code[1]); break;
		case 0xD5: printf("PUSH D"); break;
		case 0xD6: printf("SUI #$%02x",code[1]); break;
		case 0xD7: printf("RST 2"); break;
		case 0xD8: printf("RC"); break;
		case 0xDA: printf("JC $%02x%02x",code[2],code[1]); break;
		case 0xDB: printf("IN #$%02x",code[1]); break;
		case 0xDC: printf("CC $%02x%02x",code[2],code[1]); break;
		case 0xDE: printf("SBI #$%02x",code[1]); break;
		case 0xDF: printf("RST 3"); break;
		case 0xE0: printf("RPO"); break;
		case 0xE1: printf("POP H"); break;
		case 0xE2: printf("JPO $%02x%02x",code[2],code[1]); break;
		case 0xE3: printf("XTHL"); break;
		case 0xE4: printf("CPO $%02x%02x",code[2],code[1]); break;
		case 0xE5: printf("PUSH H"); break;
		case 0xE6: printf("ANI #$%02x",code[1]); break;
		case 0xE7: printf("RST 4"); break;
		case 0xE8: printf("RPE"); break;
		case 0xE9: printf("PCHL"); break;
		case 0xEA: printf("JPE $%02x%02x",code[2],code[1]); break;
		case 0xEB: printf("XCHG"); break;
		case 0xEC: printf("CPE $%02x%02x",code[2],code[1]); break;
		case 0xEE: printf("XRI #$%02x",code[1]); break;
		case 0xEF: printf("RST 5"); break;
		case 0xF0: printf("RP"); break;
		case 0xF1: printf("POP PSW"); break;
		case 0xF2: printf("JP $%02x%02x",code[2],code[1]); break;
		case 0xF3: printf("DI"); break;
		case 0xF4: printf("CP $%02x%02x",code[2],code[1]); break;
		case 0xF5: printf("PUSH PSW"); break;
		case 0xF6: printf("ORI #$%02x",code[1]); break;
		case 0xF7: printf("RST 6"); break;
		case 0xF8: printf("RM"); break;
		case 0xF9: printf("SPHL"); break;
		case 0xFA: printf("JM $%02x%02x",code[2],code[1]); break;
		case 0xFB: printf("EI"); break;
		case 0xFC: printf("CM $%02x%02x",code[2],code[1]); break;
		case 0xFE: printf("CPI #$%02x",code[1]); break;
		case 0xFF: printf("RST 7"); break;
	}
	printf("\n");
}
void UnimplementedInstruction(State8080* state) {
	printf("Error: Unimplemented instruction\n");
	state->pc--;
	unsigned char* code = &state->memory[state->pc];
	printf("OPCODE = %02x\n", *code); 
	exit(1);
}

int Parity(uint8_t value) {
	int bits_on = 0;
	value = (value & ((1<<8)-1));
	for(int i = 0; i < 8; i++) {
		if(value & 0x1) 
			bits_on++;
		value = value >> 1;	
	}
	return (0 == (bits_on & 0x1));
}

int Emulate8080(State8080* state) {
	unsigned char* code = &state->memory[state->pc];
	//Disassemble8080(state->memory, state->pc);
	state->pc += 1;

	switch(*code) {
		case 0x00: break; //NOP
        case 0x01: //LXI B, D16
			state->b = code[2];
			state->c = code[1];
			state->pc += 2;
			break;
        case 0x02: //STAX B 
			{
				uint16_t offset = (state->b << 8) | state->c;
				state->memory[offset] = state->a;
			}
			break;
        case 0x03: //INX B 
			{
				state->c++;
				if(state->c == 0) {
					state->b++;
				}
			}
			break;
        case 0x04: //INR B 
			{
				uint8_t answer = state->b + 1;
				state->cc.z = (answer == 0);
				state->cc.s = ((answer & 0x80) == 0x80);
				state->cc.p = Parity(answer);
				state->b = answer;
			}
			break;
        case 0x05: //DCR B 
			{
				uint8_t answer = state->b - 1;
				state->cc.z = (answer == 0);
				state->cc.s = ((answer & 0x80) == 0x80);
				state->cc.p = Parity(answer);
				state->b = answer;
			}
			break;
        case 0x06: state->b = code[1]; state->pc += 1; break; //MVI B, D8
        case 0x07: //RLC 
			{
				uint8_t x = state->a;
				state->a = (x << 1) | ((x & 0x80) >> 7);
				state->cc.cy = (0x80 == (x & 0x80)); 
			}
			break;
        case 0x09: //DAD B
			{
				uint32_t hl = (state->h << 8) | state->l;
				uint32_t bc = (state->b << 8) | state->c;
				uint32_t answer = hl + bc;
				state->h = (answer & 0xFF00) >> 8;
				state->l = (answer & 0xFF);
				if(answer > 0xFFFF) {
					state->cc.cy = 1;
				} else {
					state->cc.cy = 0;
				}
			}
			break;
        case 0x0A: //LDAX B
			{
				uint16_t offset = (state->b << 8) | state->c;
				state->a = state->memory[offset];
			}
			break;
        case 0x0B: //DCX B
			{
				state->c -= 1;
				if(state->c == 0xFF)
					state->b -= 1;
			}
			break;
        case 0x0C: //INR C
			{
				uint8_t answer = state->c + 1;
				state->cc.z = (answer == 0);
				state->cc.s = ((answer & 0x80) == 0x80);
				state->cc.p = Parity(answer);
				state->c = answer;
			}
			break;
        case 0x0D: //DCR C
			{
				uint8_t answer = state->c - 1;
				state->cc.z = (answer == 0);
				state->cc.s = ((answer & 0x80) == 0x80);
				state->cc.p = Parity(answer);
				state->c = answer;
			}
			break;
        case 0x0E: state->c = code[1]; state->pc +=1; break; //MVI C,D8
        case 0x0F: //RRC
			{
				uint8_t x = state->a;
				state->a = ((x & 1) << 7) | (x >> 1);
				state->cc.cy = (1 == (x & 1));
			}
			break;
        case 0x11: //LXI D, D16
			{
				state->d = code[2];
				state->e = code[1];
				state->pc += 2;
			}
			break;
        case 0x12: //STAX D
			{
				uint16_t offset = (state->d << 8) | state->e;
				state->memory[offset] = state->a;
			} 
			break;
        case 0x13: //INX D 
			{
				uint16_t de = (state->d << 8) | state->e;
				uint16_t answer = de + 1;
				state->d = (answer & 0xFF00) >> 8;
				state->e = answer & 0xFF;
			}
			break;
        case 0x14: //INR D 
			{
				uint8_t answer = state->d + 1;
				state->cc.z = (answer == 0);
				state->cc.s = ((answer & 0x80) == 0x80);
				state->cc.p = Parity(answer);
				state->d = answer;
			}
			break;
        case 0x15: //DCR D 
			{
				uint8_t answer = state->d - 1;
				state->cc.z = (answer == 0);
				state->cc.s = ((answer & 0x80) == 0x80);
				state->cc.p = Parity(answer);
				state->d = answer;
			}
			break;
        case 0x16: //MVI D,D8 
			{
				state->d = code[1];
				state->pc++;
			}
			break;
        case 0x17: //RAL
			{
				uint8_t x = state->a;
				state->a = (x << 1) | (state->cc.cy & 0x1);
				state->cc.cy = (0x80 == (0x80 & x));
			}
			break;
        case 0x19: //DAD D
			{
				uint32_t hl = (state->h << 8) | state->l;
				uint32_t de = (state->d << 8) | state->e;
				uint32_t answer = hl + de;
				state->h = (answer & 0xFF00) >> 8;
				state->l = answer & 0xFF;
				if(answer > 0xFFFF) {
					state->cc.cy = 1;
				} else {
					state->cc.cy = 0;
				}
			}
			break;
        case 0x1A: //LDAX D 
			{
				uint16_t offset= (state->d << 8) | state->e;
				state->a = state->memory[offset]; 
			}
			break;
        case 0x1B: //DCX D
			{
				state->e -= 1;
				if(state->e == 0xFF)
					state->d -= 1;
			}
			break;
        case 0x1C: //INR E
			{
				uint8_t answer = state->e + 1;
				state->cc.z = (answer == 0);
				state->cc.s = ((answer & 0x80) == 0x80);
				state->cc.p = Parity(answer);
				state->e = answer;
			}
			break;
        case 0x1D: //DCR E
			{
				uint8_t answer = state->e - 1;
				state->cc.z = (answer == 0);
				state->cc.s = ((answer & 0x80) == 0x80);
				state->cc.p = Parity(answer);
				state->e = answer;
			}
			break;
        case 0x1E: // MVI E, D8
			{
				state->e = code[1];
				state->pc += 1;
			}
			break;
        case 0x1F: // RAR 
			{
				uint8_t x = state->a;
				state->a = ((state->cc.cy & 0x1) << 7) | (x >> 1);
				state->cc.cy = (1 == (x & 1));
			} 
			break;
        case 0x21: // LXI H, D16 
			{
				state->h = code[2];
				state->l = code[1];
				state->pc += 2;
			}
			break;
        case 0x22: //SHLD adr
			{
				uint16_t offset = (code[2] << 8) | code[1];
				state->memory[offset] =  state->l;
				state->memory[offset+1] =  state->h;
				state->pc += 2;
			}
			break;
        case 0x23: //INX H 
			{
				state->l++;
				if(state->l == 0) {
					state->h++;
				}
			}
			break;
        case 0x24: //INR H
			{
				uint8_t answer = state->h + 1;
				state->cc.z = (answer == 0);
				state->cc.s = ((answer & 0x80) == 0x80);
				state->cc.p = Parity(answer);
				state->h = answer;
			}
			break;
        case 0x25: //DCR H
			{
				uint8_t answer = state->h - 1;
				state->cc.z = (answer == 0);
				state->cc.s = ((answer & 0x80) == 0x80);
				state->cc.p = Parity(answer);
				state->h = answer;
			}
			break;
        case 0x26: state->h = code[1]; state->pc += 1; break; //MVI H,D8
        case 0x27: //DAA 
			{
				if ((state->a & 0xf) > 9)    
            		state->a += 6;    
        		if ((state->a & 0xf0) > 0x90) {    
            		uint16_t answer = (uint16_t) state->a + 0x60;    
					state->cc.z = ((answer & 0xFF) == 0);
					state->cc.s = (0x80 == (answer & 0x80));
					state->cc.p = Parity(answer & 0xFF);
					state->cc.cy = (answer > 0xFF);
            		state->a = answer & 0xFF;    
        		}    
			}
       		break;    
        case 0x29: //DAD H 
			{
				uint32_t hl = (state->h << 8) | state->l;
				uint32_t answer = hl + hl;
				state->h = (answer & 0xFF00) >> 8;
				state->l = answer & 0xFF;
				state->cc.cy = (answer > 0xFFFF);
			}
			break;
        case 0x2A: // LHLD adr
			{
				uint16_t offset = (code[2] << 8) | code[1];
				state->l = state->memory[offset];
				state->h = state->memory[offset+1];
				state->pc += 2;
			}
			break;
        case 0x2B: //DCX H 
			{
				state->l -= 1;
				if(state->l == 0xFF)
					state->h -= 1;
			}
			break;
        case 0x2C: //INR L 
			{
				uint8_t answer = state->l + 1;
				state->cc.z = (answer == 0);
				state->cc.s = ((answer & 0x80) == 0x80);
				state->cc.p = Parity(answer);
				state->l = answer;
			}
			break;
        case 0x2D: //DCR L
			{
				uint8_t answer = state->l - 1;
				state->cc.z = (answer == 0);
				state->cc.s = ((answer & 0x80) == 0x80);
				state->cc.p = Parity(answer);
				state->l = answer;
			}
			break;
        case 0x2E: //MVI L, D8 
			{
				state->l = code[1];
				state->pc += 1;
			}
			break;
        case 0x2F: //CMA
			{
				state->a = ~(state->a); 
			}
			break;
        case 0x31: //LXI SP, D16 
			{
				state->sp = (code[2] << 8) | code[1];
				state->pc += 2;
			}
			break;
        case 0x32: //STA adr 
			{
				uint16_t offset = (code[2] << 8) | code[1];
				state->memory[offset] = state->a;
				state->pc += 2;
			}
			break;
        case 0x33: //INX SP
			{
				state->sp += 1;
			}
			break;
        case 0x34: //INR M
			{
				uint16_t offset = (state->h << 8) | state->l;
				uint8_t res = state->memory[offset] + 1; 
				state->cc.z = (res == 0);
				state->cc.s = ((0x80 & res) == 0x80);
				state->cc.p = Parity(res);
				state->memory[offset] = res;
			}
			break;
        case 0x35: //DCR M 
			{
				uint16_t offset = (state->h << 8) | state->l;
				uint8_t res = state->memory[offset] - 1; 
				state->cc.z = (res == 0);
				state->cc.s = ((0x80 & res) == 0x80);
				state->cc.p = Parity(res);
				state->memory[offset] = res;
			}
			break;
        case 0x36: //MVI M,D8 
			{
				uint16_t offset = (state->h << 8) | state->l;
				state->memory[offset] = code[1];
				state->pc += 1;
			}
			break;
        case 0x37:  state->cc.cy = 1; break; //STC
        case 0x39: //DAD SP
			{
				uint32_t answer = ((state->h << 8) | state->l) + state->sp;
				state->h = (answer & 0xFF00) >> 8;
				state->l = answer & 0xFF;
				state->cc.cy = (answer > 0xFFFF);
			}
			break;
        case 0x3A: //LDA adr
			{
				uint16_t offset = (code[2] << 8) | code[1];
				state->a = state->memory[offset];
				state->pc += 2;
			}
			break;
        case 0x3B: //DCX SP 
			{
				state->sp -= 1;
			}
			break;
        case 0x3C: // INR A
			{
				uint8_t answer = state->a + 1;
				state->cc.z = (answer == 0);
				state->cc.s = ((answer & 0x80) == 0x80);
				state->cc.p = Parity(answer);
				state->a = answer;
			}
			break;
        case 0x3D: // DCR A
			{
				uint8_t answer = state->a - 1;
				state->cc.z = (answer == 0);
				state->cc.s = ((answer & 0x80) == 0x80);
				state->cc.p = Parity(answer);
				state->a = answer;
			}
			break;
        case 0x3E: state->a = code[1]; state->pc++; break;// MVI A,D8
        case 0x3F: state->cc.cy = 0; break;//CMC
        case 0x40: state->b = state->b; break;// MOV B,B
        case 0x41: state->b = state->c; break;// MOV B,C
        case 0x42: state->b = state->d; break;// MOV B,D
        case 0x43: state->b = state->e; break;// MOV B,E
        case 0x44: state->b = state->h; break;// MOV B,H
        case 0x45: state->b = state->l; break;// MOV B,L
        case 0x46: //MOV B,M
			{
				uint16_t offset = (state->h << 8) | state->l;
				state->b = state->memory[offset];
			}
			break;
        case 0x47: state->b = state->a; break;// MOV B,A
        case 0x48: state->c = state->b; break;// MOV C,B
        case 0x49: state->c = state->c; break;// MOV C,C
        case 0x4A: state->c = state->d; break;// MOV C,D
        case 0x4B: state->c = state->e; break;// MOV C,E
        case 0x4C: state->c = state->h; break;// MOV C,H
        case 0x4D: state->c = state->l; break;// MOV C,L
        case 0x4E: //MOV C,M
			{
				uint16_t offset = (state->h << 8) | state->l;
				state->c = state->memory[offset];
			}
			break;
        case 0x4F: state->c = state->a; break;// MOV C,A
        case 0x50: state->d = state->b; break;// MOV D,B
        case 0x51: state->d = state->c; break;// MOV D,C
        case 0x52: state->d = state->d; break;// MOV D,D
        case 0x53: state->d = state->e; break;// MOV D,E
        case 0x54: state->d = state->h; break;// MOV D,H
        case 0x55: state->d = state->l; break;// MOV D,L
        case 0x56: //MOV D,M
			{
				uint16_t offset = (state->h << 8) | state->l;
				state->d = state->memory[offset]; 
			}
			break;
        case 0x57: state->d = state->a; break;// MOV D,A
        case 0x58: state->e = state->b; break;// MOV E,B
        case 0x59: state->e = state->c; break;// MOV E,C
        case 0x5A: state->e = state->d; break;// MOV E,D
        case 0x5B: state->e = state->e; break;// MOV E,E
        case 0x5C: state->e = state->h; break;// MOV E,H
        case 0x5D: state->e = state->l; break;// MOV E,L
        case 0x5E: //MOV E,M
			{
				uint16_t offset = (state->h << 8) | state->l;
				state->e = state->memory[offset]; 
			}
			break;
        case 0x5F: state->e = state->a; break;// MOV E,A
        case 0x60: state->h = state->b; break;// MOV H,B
        case 0x61: state->h = state->c; break;// MOV H,C
        case 0x62: state->h = state->d; break;// MOV H,D
        case 0x63: state->h = state->e; break;// MOV H,E
        case 0x64: state->h = state->h; break;// MOV H,H
        case 0x65: state->h = state->l; break;// MOV H,L
        case 0x66: //MOV H,M
			{
				uint16_t offset = (state->h << 8) | state->l;
				state->h = state->memory[offset]; 
			}
			break;
        case 0x67: state->h = state->a; break;// MOV H,A
        case 0x68: state->l = state->b; break;// MOV L,B
        case 0x69: state->l = state->c; break;// MOV L,C
        case 0x6A: state->l = state->d; break;// MOV L,D
        case 0x6B: state->l = state->e; break;// MOV L,E
        case 0x6C: state->l = state->h; break;// MOV L,H
        case 0x6D: state->l = state->l; break;// MOV L,L
        case 0x6E: // MOV L,M
			{
				uint16_t offset = (state->h << 8) | state->l;
				state->l = state->memory[offset];
			}
		   	break;
        case 0x6F: state->l = state->a; break;//MOV L,A
        case 0x70: //MOV M,B
			{
				uint16_t offset = (state->h << 8) | state->l;
				state->memory[offset] = state->b;
			}
			break;
        case 0x71: //MOV M,C
			{
				uint16_t offset = (state->h << 8) | state->l;
				state->memory[offset] = state->c;
			}
			break;
        case 0x72: //MOV M,D
			{
				uint16_t offset = (state->h << 8) | state->l;
				state->memory[offset] = state->d;
			}
			break;
        case 0x73: //MOV M,E
			{
				uint16_t offset = (state->h << 8) | state->l;
				state->memory[offset] = state->e;
			}
			break;
        case 0x74: //MOV M,H
			{
				uint16_t offset = (state->h << 8) | state->l;
				state->memory[offset] = state->h;
			}
			break;
        case 0x75: //MOV M,L
			{
				uint16_t offset = (state->h << 8) | state->l;
				state->memory[offset] = state->l;
			}
			break;
        case 0x76: break; //HLT
        case 0x77: //MOV M,A
			{
				uint16_t offset = (state->h << 8) | state->l;
				state->memory[offset] = state->a;
			}
			break;
        case 0x78: state->a = state->b; break;// MOV A,B
        case 0x79: state->a = state->c; break;// MOV A,C
        case 0x7A: state->a = state->d; break;// MOV A,D
        case 0x7B: state->a = state->e; break;// MOV A,E
        case 0x7C: state->a = state->h; break;// MOV A,H
        case 0x7D: state->a = state->l; break;// MOV A,L
        case 0x7E: //MOV A,M
			{
				uint16_t offset = (state->h << 8) | state->l;
				state->a = state->memory[offset];
		    }
			break;
        case 0x7F: state->a = state->a; break;// MOV A,A
        case 0x80: // ADD B
			{
				// Convert 8 bits to 16 bits numbers for making carry operation simpler
				uint16_t answer = (uint16_t)state->a + (uint16_t)state->b;
				// If answer equal 0 set zero flag	
				if((answer & 0xFF) == 0) {
					state->cc.z = 1;
				} else {
					state->cc.z = 0;
				}
				// If 7th bit is on set the sign flag
				if(answer & 0x80) {
					state->cc.s = 1;
				} else {
					state->cc.s = 0;
				} 
				// If answer is bigger than 8 bits number set carry flag
				if(answer > 0xFF) {
					state->cc.cy = 1;
				} else {
					state->cc.cy = 0;
				}
				state->cc.p = Parity(answer & 0xFF);

				state->a = answer & 0xFF;
			}
			break;
        case 0x81: //ADD C
			{
				uint16_t answer = (uint16_t)state->a + (uint16_t)state->c;
				state->cc.z = ((answer & 0xFF) == 0);
				state->cc.s = (0x80 == (answer & 0x80));
				state->cc.p = Parity(answer & 0xFF);
				state->cc.cy = (answer > 0xFF);
				state->a = answer & 0xFF;
			}
			break;
        case 0x82: //ADD D 
			{
				uint16_t answer = (uint16_t)state->a + (uint16_t)state->d;
				state->cc.z = ((answer & 0xFF) == 0);
				state->cc.s = (0x80 == (answer & 0x80));
				state->cc.p = Parity(answer & 0xFF);
				state->cc.cy = (answer > 0xFF);
				state->a = answer & 0xFF;
			}
			break;
        case 0x83: //ADD E 
			{
				uint16_t answer = (uint16_t)state->a + (uint16_t)state->e;
				state->cc.z = ((answer & 0xFF) == 0);
				state->cc.s = (0x80 == (answer & 0x80));
				state->cc.p = Parity(answer & 0xFF);
				state->cc.cy = (answer > 0xFF);
				state->a = answer & 0xFF;
			}
			break;
        case 0x84: //ADD H 
			{
				uint16_t answer = (uint16_t)state->a + (uint16_t)state->h;
				state->cc.z = ((answer & 0xFF) == 0);
				state->cc.s = (0x80 == (answer & 0x80));
				state->cc.p = Parity(answer & 0xFF);
				state->cc.cy = (answer > 0xFF);
				state->a = answer & 0xFF;
			}
			break;
        case 0x85: //ADD L
			{
				uint16_t answer = (uint16_t)state->a + (uint16_t)state->l;
				state->cc.z = ((answer & 0xFF) == 0);
				state->cc.s = (0x80 == (answer & 0x80));
				state->cc.p = Parity(answer & 0xFF);
				state->cc.cy = (answer > 0xFF);
				state->a = answer & 0xFF;
			}
			break;
        case 0x86: //ADD M
			{
				uint16_t offset = (state->h << 8) | state->l;
				uint16_t answer = (uint16_t)state->a + state->memory[offset];
				state->cc.z = ((answer & 0xFF) == 0);
				state->cc.s = (0x80 == (answer & 0x80));
				state->cc.p = Parity(answer & 0xFF);
				state->cc.cy = (answer > 0xFF);
				state->a = answer & 0xFF;
			}
			break;
		case 0x87: //ADD A
			{
				uint16_t answer = (uint16_t)state->a + (uint16_t)state->a;
				state->cc.z = ((answer & 0xFF) == 0);
				state->cc.s = (0x80 == (answer & 0x80));
				state->cc.p = Parity(answer & 0xFF);
				state->cc.cy = (answer > 0xFF);
				state->a = answer & 0xFF;
			}
			break;
        case 0x88: //ADC B
			{
				uint16_t answer = (uint16_t)state->a + (uint16_t)state->b + state->cc.cy;
				state->cc.z = ((answer & 0xFF) == 0);
				state->cc.s = (0x80 == (answer & 0x80));
				state->cc.p = Parity(answer & 0xFF);
				state->cc.cy = (answer > 0xFF);
				state->a = answer & 0xFF;
			}
			break;
        case 0x89: //ADC C 
			{
				uint16_t answer = (uint16_t)state->a + (uint16_t)state->c + state->cc.cy;
				state->cc.z = ((answer & 0xFF) == 0);
				state->cc.s = (0x80 == (answer & 0x80));
				state->cc.p = Parity(answer & 0xFF);
				state->cc.cy = (answer > 0xFF);
				state->a = answer & 0xFF;
			}
			break;
        case 0x8A: //ADC D 
			{
				uint16_t answer = (uint16_t)state->a + (uint16_t)state->d + state->cc.cy;
				state->cc.z = ((answer & 0xFF) == 0);
				state->cc.s = (0x80 == (answer & 0x80));
				state->cc.p = Parity(answer & 0xFF);
				state->cc.cy = (answer > 0xFF);
				state->a = answer & 0xFF;
			}
			break;
        case 0x8B: //ADC E 
			{
				uint16_t answer = (uint16_t)state->a + (uint16_t)state->e + state->cc.cy;
				state->cc.z = ((answer & 0xFF) == 0);
				state->cc.s = (0x80 == (answer & 0x80));
				state->cc.p = Parity(answer & 0xFF);
				state->cc.cy = (answer > 0xFF);
				state->a = answer & 0xFF;
			}
			break;
        case 0x8C: //ADC H 
			{
				uint16_t answer = (uint16_t)state->a + (uint16_t)state->h + state->cc.cy;
				state->cc.z = ((answer & 0xFF) == 0);
				state->cc.s = (0x80 == (answer & 0x80));
				state->cc.p = Parity(answer & 0xFF);
				state->cc.cy = (answer > 0xFF);
				state->a = answer & 0xFF;
			}
			break;
        case 0x8D: //ADC L 
			{
				uint16_t answer = (uint16_t)state->a + (uint16_t)state->l + state->cc.cy;
				state->cc.z = ((answer & 0xFF) == 0);
				state->cc.s = (0x80 == (answer & 0x80));
				state->cc.p = Parity(answer & 0xFF);
				state->cc.cy = (answer > 0xFF);
				state->a = answer & 0xFF;
			}
			break;
        case 0x8E: //ADC M 
			{
				uint16_t offset = (state->h << 8) | state->l;
				uint16_t answer = (uint16_t)state->a + state->memory[offset] + state->cc.cy;
				state->cc.z = ((answer & 0xFF) == 0);
				state->cc.s = (0x80 == (answer & 0x80));
				state->cc.p = Parity(answer & 0xFF);
				state->cc.cy = (answer > 0xFF);
				state->a = answer & 0xFF;
			}
			break;
        case 0x8F: //ADC A 
			{
				uint16_t answer = (uint16_t)state->a + (uint16_t)state->a + state->cc.cy;
				state->cc.z = ((answer & 0xFF) == 0);
				state->cc.s = (0x80 == (answer & 0x80));
				state->cc.p = Parity(answer & 0xFF);
				state->cc.cy = (answer > 0xFF);
				state->a = answer & 0xFF;
			}
			break;
        case 0x90: //SUB B
			{
				uint16_t answer = (uint16_t)state->a - (uint16_t)state->b;
				state->cc.z = ((answer & 0xFF) == 0);
				state->cc.s = (0x80 == (answer & 0x80));
				state->cc.p = Parity(answer & 0xFF);
				state->cc.cy = (answer > 0xFF);
				state->a = answer & 0xFF;
			}
			break;
        case 0x91: //SUB C
			{
				uint16_t answer = (uint16_t)state->a - (uint16_t)state->c;
				state->cc.z = ((answer & 0xFF) == 0);
				state->cc.s = (0x80 == (answer & 0x80));
				state->cc.p = Parity(answer & 0xFF);
				state->cc.cy = (answer > 0xFF);
				state->a = answer & 0xFF;
			}
			break;
        case 0x92: //SUB D
			{
				uint16_t answer = (uint16_t)state->a - (uint16_t)state->d;
				state->cc.z = ((answer & 0xFF) == 0);
				state->cc.s = (0x80 == (answer & 0x80));
				state->cc.p = Parity(answer & 0xFF);
				state->cc.cy = (answer > 0xFF);
				state->a = answer & 0xFF;
			}
			break;
        case 0x93: //SUB E
			{
				uint16_t answer = (uint16_t)state->a - (uint16_t)state->e;
				state->cc.z = ((answer & 0xFF) == 0);
				state->cc.s = (0x80 == (answer & 0x80));
				state->cc.p = Parity(answer & 0xFF);
				state->cc.cy = (answer > 0xFF);
				state->a = answer & 0xFF;
			}
			break;
        case 0x94: //SUB H
			{
				uint16_t answer = (uint16_t)state->a - (uint16_t)state->h;
				state->cc.z = ((answer & 0xFF) == 0);
				state->cc.s = (0x80 == (answer & 0x80));
				state->cc.p = Parity(answer & 0xFF);
				state->cc.cy = (answer > 0xFF);
				state->a = answer & 0xFF;
			}
			break;
        case 0x95: //SUB L
			{
				uint16_t answer = (uint16_t)state->a - (uint16_t)state->l;
				state->cc.z = ((answer & 0xFF) == 0);
				state->cc.s = (0x80 == (answer & 0x80));
				state->cc.p = Parity(answer & 0xFF);
				state->cc.cy = (answer > 0xFF);
				state->a = answer & 0xFF;
			}
			break;
        case 0x96: //SUB M 
			{
			uint16_t offset = (state->h << 8) | state->l;
				uint16_t answer = (uint16_t)state->a - state->memory[offset];
				state->cc.z = ((answer & 0xFF) == 0);
				state->cc.s = (0x80 == (answer & 0x80));
				state->cc.p = Parity(answer & 0xFF);
				state->cc.cy = (answer > 0xFF);
				state->a = answer & 0xFF;
			}	 
			break;
        case 0x97: //SUB A
			{
				uint16_t answer = (uint16_t)state->a - (uint16_t)state->a;
				state->cc.z = ((answer & 0xFF) == 0);
				state->cc.s = (0x80 == (answer & 0x80));
				state->cc.p = Parity(answer & 0xFF);
				state->cc.cy = (answer > 0xFF);
				state->a = answer & 0xFF;
			}
			break;
        case 0x98: //SBB B
			{
				uint16_t answer = (uint16_t)state->a - (uint16_t)state->b - state->cc.cy;
				state->cc.z = ((answer & 0xFF) == 0);
				state->cc.s = (0x80 == (answer & 0x80));
				state->cc.p = Parity(answer & 0xFF);
				state->cc.cy = (answer > 0xFF);
				state->a = answer & 0xFF;
			}
			break;
        case 0x99: //SBB C 
			{
				uint16_t answer = (uint16_t)state->a - (uint16_t)state->c - state->cc.cy;
				state->cc.z = ((answer & 0xFF) == 0);
				state->cc.s = (0x80 == (answer & 0x80));
				state->cc.p = Parity(answer & 0xFF);
				state->cc.cy = (answer > 0xFF);
				state->a = answer & 0xFF;
			}
			break;
        case 0x9A: //SBB D
			{
				uint16_t answer = (uint16_t)state->a - (uint16_t)state->d - state->cc.cy;
				state->cc.z = ((answer & 0xFF) == 0);
				state->cc.s = (0x80 == (answer & 0x80));
				state->cc.p = Parity(answer & 0xFF);
				state->cc.cy = (answer > 0xFF);
				state->a = answer & 0xFF;
			}
			break;
        case 0x9B: //SBB E
			{
				uint16_t answer = (uint16_t)state->a - (uint16_t)state->e - state->cc.cy;
				state->cc.z = ((answer & 0xFF) == 0);
				state->cc.s = (0x80 == (answer & 0x80));
				state->cc.p = Parity(answer & 0xFF);
				state->cc.cy = (answer > 0xFF);
				state->a = answer & 0xFF;
			}
			break;
        case 0x9C: //SBB H
			{
				uint16_t answer = (uint16_t)state->a - (uint16_t)state->h - state->cc.cy;
				state->cc.z = ((answer & 0xFF) == 0);
				state->cc.s = (0x80 == (answer & 0x80));
				state->cc.p = Parity(answer & 0xFF);
				state->cc.cy = (answer > 0xFF);
				state->a = answer & 0xFF;
			}
			break;
        case 0x9D: //SBB L 
			{
				uint16_t answer = (uint16_t)state->a - (uint16_t)state->l - state->cc.cy;
				state->cc.z = ((answer & 0xFF) == 0);
				state->cc.s = (0x80 == (answer & 0x80));
				state->cc.p = Parity(answer & 0xFF);
				state->cc.cy = (answer > 0xFF);
				state->a = answer & 0xFF;
			}
			break;
        case 0x9E: //SBB M 
			{
				uint16_t offset = (state->h << 8) | state->l;
				uint16_t answer = (uint16_t)state->a - state->memory[offset] - state->cc.cy;
				state->cc.z = ((answer & 0xFF) == 0);
				state->cc.s = (0x80 == (answer & 0x80));
				state->cc.p = Parity(answer & 0xFF);
				state->cc.cy = (answer > 0xFF);
				state->a = answer & 0xFF;
			}
			break;
        case 0x9F:  
			{
				uint16_t answer = (uint16_t)state->a - (uint16_t)state->a - state->cc.cy;
				state->cc.z = ((answer & 0xFF) == 0);
				state->cc.s = (0x80 == (answer & 0x80));
				state->cc.p = Parity(answer & 0xFF);
				state->cc.cy = (answer > 0xFF);
				state->a = answer & 0xFF;
			}
			break;
        case 0xA0: //ANA B
			{
				state->a &= state->b;
				state->cc.z = (state->a & 0xFF) == 0;
				state->cc.s = ((state->a & 0x80) == 0x80);
				state->cc.p = Parity(state->a & 0xFF);
				state->cc.cy = 0;
			}
			break;
        case 0xA1: //ANA C 
			{
				state->a &= state->c;
				state->cc.z = (state->a & 0xFF) == 0;
				state->cc.s = ((state->a & 0x80) == 0x80);
				state->cc.p = Parity(state->a & 0xFF);
				state->cc.cy = 0;
			}
			break;
        case 0xA2: //ANA D
			{
				state->a &= state->d;
				state->cc.z = (state->a & 0xFF) == 0;
				state->cc.s = ((state->a & 0x80) == 0x80);
				state->cc.p = Parity(state->a & 0xFF);
				state->cc.cy = 0;
			}
			break;
        case 0xA3: //ANA E 
			{
				state->a &= state->e;
				state->cc.z = (state->a & 0xFF) == 0;
				state->cc.s = ((state->a & 0x80) == 0x80);
				state->cc.p = Parity(state->a & 0xFF);
				state->cc.cy = 0;
			}
			break;
        case 0xA4: //ANA H
			{
				state->a &= state->h;
				state->cc.z = (state->a & 0xFF) == 0;
				state->cc.s = ((state->a & 0x80) == 0x80);
				state->cc.p = Parity(state->a & 0xFF);
				state->cc.cy = 0;
			}
			break;
        case 0xA5: //ANA L
			{
				state->a &= state->l;
				state->cc.z = (state->a & 0xFF) == 0;
				state->cc.s = ((state->a & 0x80) == 0x80);
				state->cc.p = Parity(state->a & 0xFF);
				state->cc.cy = 0;
			}
			break;
        case 0xA6: //ANA M
			{
				int16_t offset = (state->h << 8) | state->l;
				state->a &= state->memory[offset];
				state->cc.z = (state->a & 0xFF) == 0;
				state->cc.s = ((state->a & 0x80) == 0x80);
				state->cc.p = Parity(state->a & 0xFF);
				state->cc.cy = 0;
			}
			break;
        case 0xA7: //ANA A 
			{
				state->a &= state->a;
				state->cc.z = (state->a & 0xFF) == 0;
				state->cc.s = ((state->a & 0x80) == 0x80);
				state->cc.p = Parity(state->a & 0xFF);
				state->cc.cy = 0;
			}
			break;
        case 0xA8: //XRA B 
			{
				state->a = state->a ^ state->b;
				state->cc.z = (state->a & 0xFF) == 0;
				state->cc.s = ((state->a & 0x80) == 0x80);
				state->cc.p = Parity(state->a & 0xFF);
				state->cc.cy = 0;
			}
			break;
        case 0xA9: //XRA C
			{
				state->a = state->a ^ state->c;
				state->cc.z = (state->a & 0xFF) == 0;
				state->cc.s = ((state->a & 0x80) == 0x80);
				state->cc.p = Parity(state->a & 0xFF);
				state->cc.cy = 0;
			}
			break;
        case 0xAA: //XRA D
			{
				state->a = state->a ^ state->d;
				state->cc.z = (state->a & 0xFF) == 0;
				state->cc.s = ((state->a & 0x80) == 0x80);
				state->cc.p = Parity(state->a & 0xFF);
				state->cc.cy = 0;
			}
			break;
        case 0xAB: //XRA E
			{
				state->a = state->a ^ state->e;
				state->cc.z = (state->a & 0xFF) == 0;
				state->cc.s = ((state->a & 0x80) == 0x80);
				state->cc.p = Parity(state->a & 0xFF);
				state->cc.cy = 0;
			}
			break;
        case 0xAC: //XRA H
			{
				state->a = state->a ^ state->h;
				state->cc.z = (state->a & 0xFF) == 0;
				state->cc.s = ((state->a & 0x80) == 0x80);
				state->cc.p = Parity(state->a & 0xFF);
				state->cc.cy = 0;
			}
			break;
        case 0xAD: //XRA L
			{
				state->a = state->a ^ state->l;
				state->cc.z = (state->a & 0xFF) == 0;
				state->cc.s = ((state->a & 0x80) == 0x80);
				state->cc.p = Parity(state->a & 0xFF);
				state->cc.cy = 0;
			}
			break;
        case 0xAE: //XRA M 
			{
				uint16_t offset = (state->h << 8) | state->l;
				state->a = state->a ^ state->memory[offset];
				state->cc.z = (state->a & 0xFF) == 0;
				state->cc.s = ((state->a & 0x80) == 0x80);
				state->cc.p = Parity(state->a & 0xFF);
				state->cc.cy = 0;
			}
			break;
        case 0xAF: //XRA A 
			{
				state->a = state->a ^ state->a;
				state->cc.z = (state->a & 0xFF) == 0;
				state->cc.s = ((state->a & 0x80) == 0x80);
				state->cc.p = Parity(state->a & 0xFF);
				state->cc.cy = 0;
			}
			break;
        case 0xB0: //ORA B 
			{
				state->a = state->a | state->b;
				state->cc.z = state->a == 0;
				state->cc.s = ((state->a & 0x80) == 0x80);
				state->cc.p = Parity(state->a & 0xFF);
				state->cc.cy = 0;
			}
			break;
        case 0xB1: //ORA C
			{
				state->a = state->a | state->c;
				state->cc.z = state->a == 0;
				state->cc.s = ((state->a & 0x80) == 0x80);
				state->cc.p = Parity(state->a & 0xFF);
				state->cc.cy = 0;
			}
			break;
        case 0xB2: //ORA D
			{
				state->a = state->a | state->d;
				state->cc.z = state->a == 0;
				state->cc.s = ((state->a & 0x80) == 0x80);
				state->cc.p = Parity(state->a & 0xFF);
				state->cc.cy = 0;
			}
			break;
        case 0xB3: //ORA E
			{
				state->a = state->a | state->e;
				state->cc.z = state->a == 0;
				state->cc.s = ((state->a & 0x80) == 0x80);
				state->cc.p = Parity(state->a & 0xFF);
				state->cc.cy = 0;
			}
			break;
        case 0xB4: //ORA H
			{
				state->a = state->a | state->h;
				state->cc.z = state->a == 0;
				state->cc.s = ((state->a & 0x80) == 0x80);
				state->cc.p = Parity(state->a & 0xFF);
				state->cc.cy = 0;
			}
			break;
        case 0xB5: //ORA L
			{
				state->a = state->a | state->l;
				state->cc.z = state->a == 0;
				state->cc.s = ((state->a & 0x80) == 0x80);
				state->cc.p = Parity(state->a & 0xFF);
				state->cc.cy = 0;
			}
			break;
        case 0xB6: //ORA M 
			{
				uint16_t offset = (state->h << 8) | state->l;
				state->a = state->a | state->memory[offset]; 
				state->cc.z = state->a == 0;
				state->cc.s = ((state->a & 0x80) == 0x80);
				state->cc.p = Parity(state->a & 0xFF);
				state->cc.cy = 0;
			}
			break;
        case 0xB7: //ORA A
			{
				state->a = state->a | state->a;
				state->cc.z = state->a == 0;
				state->cc.s = ((state->a & 0x80) == 0x80);
				state->cc.p = Parity(state->a & 0xFF);
				state->cc.cy = 0;
			}
			break;
        case 0xB8: //CMP B 
			{
				uint16_t answer = (uint16_t)state->a - (uint16_t)state->b;
				state->cc.z = (answer == 0);
				state->cc.s = ((answer & 0x80) == 0x80);
				state->cc.p = Parity(answer & 0xFF);
				state->cc.cy = (answer > 0xFF);
			}
			break;
        case 0xB9: //CMP C
			{
				uint16_t answer = (uint16_t)state->a - (uint16_t)state->c;
				state->cc.z = (answer == 0);
				state->cc.s = ((answer & 0x80) == 0x80);
				state->cc.p = Parity(answer & 0xFF);
				state->cc.cy = (answer > 0xFF);
			}
			break;
        case 0xBA: //CMP D
			{
				uint16_t answer = (uint16_t)state->a - (uint16_t)state->d;
				state->cc.z = (answer == 0);
				state->cc.s = ((answer & 0x80) == 0x80);
				state->cc.p = Parity(answer & 0xFF);
				state->cc.cy = (answer > 0xFF);
			}
			break;
        case 0xBB: //CMP E
			{
				uint16_t answer = (uint16_t)state->a - (uint16_t)state->e;
				state->cc.z = (answer == 0);
				state->cc.s = ((answer & 0x80) == 0x80);
				state->cc.p = Parity(answer & 0xFF);
				state->cc.cy = (answer > 0xFF);
			}
			break;
        case 0xBC: //CMP H
			{
				uint16_t answer = (uint16_t)state->a - (uint16_t)state->h;
				state->cc.z = (answer == 0);
				state->cc.s = ((answer & 0x80) == 0x80);
				state->cc.p = Parity(answer & 0xFF);
				state->cc.cy = (answer > 0xFF);
			}
			break;
        case 0xBD: //CMP L
			{
				uint16_t answer = (uint16_t)state->a - (uint16_t)state->l;
				state->cc.z = (answer == 0);
				state->cc.s = ((answer & 0x80) == 0x80);
				state->cc.p = Parity(answer & 0xFF);
				state->cc.cy = (answer > 0xFF);
			}
			break;
        case 0xBE: //CMP M
			{
				uint16_t offset = (state->h << 8) | state->l;
				uint16_t answer = (uint16_t)state->a - (uint16_t)state->memory[offset];
				state->cc.z = (answer == 0);
				state->cc.s = ((answer & 0x80) == 0x80);
				state->cc.p = Parity(answer & 0xFF);
				state->cc.cy = (answer > 0xFF);
			}
			break;
        case 0xBF: //CMP A
			{
				uint16_t answer = (uint16_t)state->a - (uint16_t)state->a;
				state->cc.z = (answer == 0);
				state->cc.s = ((answer & 0x80) == 0x80);
				state->cc.p = Parity(answer & 0xFF);
				state->cc.cy = (answer > 0xFF);
			}
			break;
        case 0xC0: //RNZ 
			{
				if(state->cc.z == 0) {
					state->pc = (state->memory[state->sp+1] << 8) | (state->memory[state->sp]);
					state->sp += 2;
				}
			}
			break;
        case 0xC1: //POP B 
			{
				state->c = state->memory[state->sp];
				state->b = state->memory[state->sp+1];
				state->sp += 2;
			}
			break;
        case 0xC2:  // JNZ addr 
			{
				if(state->cc.z == 0) 
					state->pc = (code[2] << 8) | code[1];
				else
					state->pc += 2;
			}
			break;
        case 0xC3:  state->pc = (code[2] << 8) | code[1]; break; //JMP adr
        case 0xC4: //CNZ adr 
			{
				if(state->cc.z == 0) {
					uint16_t ret = state->pc + 2;
					state->sp -= 2;
					state->memory[state->sp+1] = (ret >> 8) & 0xFF;
					state->memory[state->sp] = ret & 0xFF;
					state->pc = (code[2] << 8) | code[1];
				} else {
					state->pc += 2;
				}
			}
			break;
        case 0xC5: //PUSH B 
			{
				state->memory[state->sp-2] = state->c;
				state->memory[state->sp-1] = state->b;
				state->sp -= 2;
			}
			break;
        case 0xC6: //ADI D8 
			{
				uint16_t answer = state->a + code[1];
				state->cc.z = ((answer & 0xFF) == 0);
				state->cc.s = ((answer & 0x80) == 0x80);
				state->cc.p = Parity(answer & 0xFF);
				state->cc.cy = (answer > 0xFF);
				state->a = answer;
				state->pc += 1;
			}
			break;
        case 0xC7: //RST 0 Potential bug
			{
				uint16_t ret = state->pc;
				state->sp -= 2;
				state->memory[state->sp+1] = (ret >> 8) & 0xFF;
				state->memory[state->sp] = ret & 0xFF;
				state->pc = 0x0000; 
			}
			break;
        case 0xC8: //RZ 
			{
				if(state->cc.z) {
					state->pc = (state->memory[state->sp+1] << 8) | (state->memory[state->sp]);
					state->sp += 2;
				}
			}
			break;
        case 0xC9: //RET 
			{
				state->pc = (state->memory[state->sp+1] << 8) | (state->memory[state->sp]);
				state->sp += 2;
			}
			break;
        case 0xCA: //JZ adr 
			{
				if(state->cc.z == 1) {
					state->pc = (code[2] << 8) | code[1];
				} else {
					state->pc += 2;
				}
			}
			break;
        case 0xCC: //CZ adr 
			{
				if(state->cc.z) {
					uint16_t ret = state->pc + 2;
					state->sp -= 2;
					state->memory[state->sp+1] = (ret >> 8) & 0xFF;
					state->memory[state->sp] = ret & 0xFF;
					state->pc = (code[2] << 8) | code[1];
				} else {
					state->pc += 2;
				}
			}
			break;
        case 0xCD: //CALL adr 
			#ifdef FOR_CPUDIAG    
            if (5 ==  ((code[2] << 8) | code[1]))    
            {    
                if (state->c == 9)    
                {    
                    uint16_t offset = (state->d<<8) | (state->e);    
                    char *str = &state->memory[offset+3];  //skip the prefix bytes    
                    while (*str != '$')    
                        printf("%c", *str++);    
                    printf("\n");    
                }    
                else if (state->c == 2)    
                {    
                    //saw this in the inspected code, never saw it called    
                    printf ("print char routine called\n");    
                }    
            }    
            else if (0 ==  ((code[2] << 8) | code[1]))    
            {    
                exit(0);    
            }    
            else    
   			#endif 
			{
				uint16_t ret = state->pc + 2;
				state->sp -= 2;
				state->memory[state->sp+1] = (ret >> 8) & 0xFF;
				state->memory[state->sp] = ret & 0xFF;
				state->pc = (code[2] << 8) | code[1]; 
			}
			break;
        case 0xCE: //ACI D8 
			{
				uint16_t answer = (uint16_t)state->a + (uint16_t)code[1] + state->cc.cy;
				state->cc.z = ((answer & 0xFF) == 0);
				state->cc.s = (0x80 == (answer & 0x80));
				state->cc.p = Parity(answer & 0xFF);
				state->cc.cy = (answer > 0xFF);
				state->a = answer & 0xFF;
				state->pc++;
			}
			break;
        case 0xCF: //RST 1
			{
				uint16_t ret = state->pc;
				state->sp -= 2;
				state->memory[state->sp+1] = (ret >> 8) & 0xFF;
				state->memory[state->sp] = ret & 0xFF;
				state->pc = 0x0008; 
			}
			break;
        case 0xD0: //RNC 
			{
				if(state->cc.cy == 0) {
					state->pc = (state->memory[state->sp+1] << 8) | (state->memory[state->sp]);
					state->sp += 2;
				}
			}
			break;
        case 0xD1: //POP D 
			{
				state->e = state->memory[state->sp];
				state->d = state->memory[state->sp+1];
				state->sp += 2;
			}
			break;
        case 0xD2: //JNC adr
			{
				if(state->cc.cy == 0) {
					state->pc = (code[2] << 8) | code[1];
				} else {
					state->pc += 2;
				} 
			}
			break;
        case 0xD3: //OUT D8
			state->pc += 1;
			break;
        case 0xD4: //CNC adr  
			{
				if(state->cc.cy == 0) {
					uint16_t ret = state->pc + 2;
					state->sp -= 2;
					state->memory[state->sp+1] = (ret >> 8) & 0xFF;
					state->memory[state->sp] = ret & 0xFF;
					state->pc = (code[2] << 8) | code[1];
				} else {
					state->pc += 2;
				}
			}
			break;
        case 0xD5: //PUSH D  
			{
				state->memory[state->sp-2] = state->e;
				state->memory[state->sp-1] = state->d;
				state->sp -= 2;
			}
			break;
        case 0xD6: //SUI D8
			{
				uint8_t answer = (uint16_t)state->a - (uint16_t)code[1];
				state->cc.z = ((answer & 0xFF) == 0);
				state->cc.s = (0x80 == (answer & 0x80));
				state->cc.p = Parity(answer & 0xFF);
				state->cc.cy = (state->a < code[1]);
				state->a = answer;
				state->pc++;
			}		
			break;
        case 0xD7: //RST 2 
			{
				uint16_t ret = state->pc;
				state->sp -= 2;
				state->memory[state->sp+1] = (ret >> 8) & 0xFF;
				state->memory[state->sp] = ret & 0xFF;
				state->pc = 0x0010; 
			}
		 	break;
        case 0xD8: //RC 
			{
				if(state->cc.cy) {
					state->pc = (state->memory[state->sp+1] << 8) | (state->memory[state->sp]);
					state->sp += 2;
				}
			}
			break;
        case 0xDA: //JC adr 
			{
				if(state->cc.cy) {
					state->pc = (code[2] << 8) | code[1];
				} else {
					state->pc += 2;
				}
			}
			break;
        case 0xDB: //IN D8 
			state->pc++;
			break;
        case 0xDC: //CC adr 
			{
				if(state->cc.cy) {
					uint16_t ret = state->pc + 2;
					state->sp -= 2;
					state->memory[state->sp+1] = (ret >> 8) & 0xFF;
					state->memory[state->sp] = ret & 0xFF;
					state->pc = (code[2] << 8) | code[1]; 
				} else {
					state->pc += 2;
				}
			}
			break;
        case 0xDE: //SBI D8
			{
				uint16_t answer = (uint16_t)state->a - (uint16_t)code[1] - state->cc.cy;
				state->cc.z = ((answer & 0xFF) == 0);
				state->cc.s = (0x80 == (answer & 0x80));
				state->cc.p = Parity(answer & 0xFF);
				state->cc.cy = (answer > 0xFF);
				state->a = answer & 0xFF;
				state->pc++;
			}
			break;
        case 0xDF: //RST 3
			{
				uint16_t ret = state->pc;
				state->sp -= 2;
				state->memory[state->sp+1] = (ret >> 8) & 0xFF;
				state->memory[state->sp] = ret & 0xFF;
				state->pc = 0x0018; 
			}
			break;
        case 0xE0: //RPO
			{
				if(state->cc.p == 0) {
					state->pc = (state->memory[state->sp+1] << 8) | state->memory[state->sp];
					state->sp += 2;
				}
			}
			break;
        case 0xE1: //POP H 
			{
				state->l = state->memory[state->sp];
				state->h = state->memory[state->sp+1];
				state->sp += 2;
			}
 			break;
        case 0xE2: //JPO adr
			{
				if(state->cc.p == 0) {
					state->pc = (code[2] << 8) | code[1];
				} else {
					state->pc += 2;
				}
			}
			break;
        case 0xE3: //XTHL 
			{
				uint8_t tmp = state->l;
				state->l = state->memory[state->sp];
				state->memory[state->sp] = tmp;
				tmp 	 = state->h;
				state->h = state->memory[state->sp+1];
				state->memory[state->sp+1]= tmp;
			}
			break;
        case 0xE4: //CPO adr
			{
				if(state->cc.p == 0) {
					uint16_t ret = state->pc + 2;
					state->sp -= 2;
					state->memory[state->sp+1] = (ret >> 8) & 0xFF;
					state->memory[state->sp] = ret & 0xFF;
					state->pc = (code[2] << 8) | code[1];
				} else {
					state->pc += 2;
				}
			}
			break;
        case 0xE5: //PUSH H 
			{
				state->memory[state->sp-2] = state->l;
				state->memory[state->sp-1] = state->h;
				state->sp -= 2;
			}
			break;
        case 0xE6: //ANI D8 
			{
				state->a = state->a & code[1];
				state->cc.z = (state->a == 0);
				state->cc.s = ((state->a & 0x80) == 0x80);
				state->cc.p = Parity(state->a);
				state->cc.cy = 0;
				state->pc += 1;
			}
			break;
        case 0xE7: //RST 4
			{
				uint16_t ret = state->pc;
				state->sp -= 2;
				state->memory[state->sp+1] = (ret >> 8) & 0xFF;
				state->memory[state->sp] = ret & 0xFF;
				state->pc = 0x0020; 
			}
			break;
        case 0xE8: //RPE
			{
				if(state->cc.p) {
					state->pc = (state->memory[state->sp+1] << 8) | state->memory[state->sp];
					state->sp += 2;
				}
			}
			break;
        case 0xE9: //PCHL 
			{
				state->pc = (state->h << 8) | state->l;
			}
			break;
        case 0xEA: //JPE adr 
			{
				if(state->cc.p) {
					state->pc = (code[2] << 8) | code[1];
				} else {
					state->pc += 2;
				}
			}
		 	break;
        case 0xEB: //XCHG 
			{
				uint8_t tmp = state->h;
				state->h = state->d;
				state->d = tmp;
				tmp 	 = state->l;
				state->l = state->e;
				state->e = tmp;
			}
			break;
        case 0xEC: //CPE adr
			{
				if(state->cc.p) {
					uint16_t ret = state->pc + 2;
					state->sp -= 2;
					state->memory[state->sp+1] = (ret >> 8) & 0xFF;
					state->memory[state->sp] = ret & 0xFF;
					state->pc = (code[2] << 8) | code[1];
				} else {
					state->pc += 2;
				}
			}
		 	break;
        case 0xEE: //XRI D8
			{
				state->a = state->a ^ code[1];
				state->cc.z = (state->a == 0);
				state->cc.s = ((state->a & 0x80) == 0x80);
				state->cc.p = Parity(state->a);
				state->cc.cy = 0;
				state->pc += 1;
			}
		 	break;
        case 0xEF: //RST 5
			{
				uint16_t ret = state->pc;
				state->sp -= 2;
				state->memory[state->sp+1] = (ret >> 8) & 0xFF;
				state->memory[state->sp] = ret & 0xFF;
				state->pc = 0x0028; 
			}
			break;
        case 0xF0: //RP
			{
				if(state->cc.s == 0) {
					state->pc = (state->memory[state->sp+1] << 8) | state->memory[state->sp];
					state->sp += 2;
				}
			}
			break;
        case 0xF1: //POP PSW 
			{ 
				state->a = state->memory[state->sp+1];
				state->cc.z = (0x01 == (state->memory[state->sp] & 0x01));
				state->cc.s = (0x02 == (state->memory[state->sp] & 0x02));
				state->cc.p = (0x04 == (state->memory[state->sp] & 0x04));
				state->cc.cy = (0x08 == (state->memory[state->sp] & 0x08));
				state->cc.ac = (0x10 == (state->memory[state->sp] & 0x10));
				state->sp += 2;
			}
			break;
        case 0xF2: //JP adr 
			{
				if(state->cc.s == 0) {
					state->pc = (code[2] << 8) | code[1];
				} else {
					state->pc += 2;
				}
			}
			break;
        case 0xF3: //DI
			state->int_enable = 0;
			break;
        case 0xF4: //CP adr 
			{
				if(state->cc.s == 0) {
					uint16_t ret = state->pc + 2;
					state->sp -= 2;
					state->memory[state->sp+1] = (ret >> 8) & 0xFF;
					state->memory[state->sp] = ret & 0xFF;
					state->pc = (code[2] << 8) | code[1];
				} else {
					state->pc += 2;
				}
			}
			break;
        case 0xF5: //PUSH PSW 
			{
			state->memory[state->sp-1] = state->a;
			uint8_t flags = state->cc.z << 0 
						  | state->cc.s << 1
						  | state->cc.p << 2
						  | state->cc.cy<< 3
						  | state->cc.ac<< 4;
			state->memory[state->sp-2] = flags;
			state->sp -= 2;
			}
			break;
        case 0xF6: //ORI D8 
			{
				state->a = state->a | code[1];
				state->cc.z = (state->a == 0);
				state->cc.s = ((state->a & 0x80) == 0x80);
				state->cc.p = Parity(state->a);
				state->cc.cy = 0;
				state->pc += 1;
			}
			break;
        case 0xF7: //RST 6
			{
				uint16_t ret = state->pc;
				state->sp -= 2;
				state->memory[state->sp+1] = (ret >> 8) & 0xFF;
				state->memory[state->sp] = ret & 0xFF;
				state->pc = 0x0030; 
			}
			break;
        case 0xF8: //RM 
			{
				if(state->cc.s) {
					state->pc = (state->memory[state->sp+1] << 8) | state->memory[state->sp];
					state->sp += 2;
				}
			}
			break;
        case 0xF9: //SPHL 
			{
				state->sp = (state->h << 8) | state->l;
			}
			break;
        case 0xFA: //JM addr 
			{
				if(state->cc.s) {
					state->pc = (code[2] << 8) | code[1];
				} else {
					state->pc += 2;
				}
			}
			break;
        case 0xFB: //EI 
			{
				state->int_enable = 1;
			}
			break;
        case 0xFC: //CM adr
			{
				if(state->cc.s) {
					uint16_t ret = state->pc + 2;
					state->sp -= 2;
					state->memory[state->sp+1] = (ret >> 8) & 0xFF;
					state->memory[state->sp] = ret & 0xFF;
					state->pc = (code[2] << 8) | code[1];
				} else {
					state->pc += 2;
				}
			}
			break;
        case 0xFE: //CPI D8 
			{
				uint8_t answer = state->a - code[1];
				state->cc.z = (answer == 0);
				state->cc.s = ((answer & 0x80) == 0x80); 
				state->cc.p = Parity(answer);
				state->cc.cy = (state->a < code[1]);
				state->pc++;
			}
			break;
        case 0xFF: //RST 7
			{
				uint16_t ret = state->pc;
				state->sp -= 2;
				state->memory[state->sp+1] = (ret >> 8) & 0xFF;
				state->memory[state->sp] = ret & 0xFF;
				state->pc = 0x0038; 
			}
			break;
	}       
	/*
		printf("\tC=%d,P=%d,S=%d,Z=%d\n", state->cc.cy, state->cc.p, state->cc.s, state->cc.z);    
       	printf("\tA $%02x B $%02x C $%02x D $%02x E $%02x H $%02x L $%02x SP %04x I = %d\n", 
		  state->a, state->b, state->c, state->d,    
          state->e, state->h, state->l, state->sp, state->int_enable);
		printf("Top of the stack 0x%02x%02x\n", state->memory[state->sp+1], state->memory[state->sp]);
	*/
}

void LoadROM(char* file, State8080* state, uint16_t offset) {
	FILE *f = fopen(file, "rb");
	if(f == NULL) {
		printf("Can't open file\n");
		exit(1);
	}

	fseek(f, 0L, SEEK_END);
	int fsize = ftell(f);
	fseek(f, 0L, SEEK_SET);

	state->memory = malloc(0x10000);

	uint8_t *buffer = &state->memory[offset];
	fread(buffer, fsize, 1, f);
	fclose(f);
} 

//TEST CODE
/*
int main(int argc, char* argv[]) {
	State8080* state = calloc(1, sizeof(State8080));
	LoadROM(argv[1], state, 0x100);

    //Fix the first instruction to be JMP 0x100    
    state->memory[0]=0xc3;    
    state->memory[1]=0;    
    state->memory[2]=0x01;    

    //Fix the stack pointer from 0x6ad to 0x7ad    
    // this 0x06 byte 112 in the code, which is    
    // byte 112 + 0x100 = 368 in memory    
    state->memory[368] = 0x7;    

    //Skip DAA test    
    state->memory[0x59c] = 0xc3; //JMP    
    state->memory[0x59d] = 0xc2;    
    state->memory[0x59e] = 0x05;    

	while(1) {
		Emulate8080(state);
	}
}
*/
