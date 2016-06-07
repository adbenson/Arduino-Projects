
#include <Charliplexing.h>
#include "WProgram.h"
#include "Letters.h"

#define MIN_LETTER 33
#define MAX_LETTER 126

#define SCR_TOP 0
#define SCR_LEFT 0
#define SCR_RIGHT 13
#define SCR_BOTTOM 8

namespace Letters {

Letter* letterSet;

Letter::Letter() {}

Letter::Letter(char chrIn, int ascIn, int* pixIn, int pixCntIn, int sizeIn) {
	character = chrIn;
	ascii = ascIn;
	pixels = pixIn;
	pixelCount = pixCntIn;
	size = sizeIn;
}

void init() {

letterSet = (Letter*)malloc(MAX_LETTER - MIN_LETTER * sizeof(Letter));

int ltr_bang[] = {0,0, 0,1, 0,2, 0,3, 0,4, 0,6};
int ltr_dblquote[] = {0,0, 2,0, 0,1, 2,1};
int ltr_hash[] = {1,0, 3,0, 0,1, 1,1, 2,1, 3,1, 4,1, 1,2, 3,2, 0,3, 1,3, 2,3, 3,365, 4,3, 1,4, 3,4};
int ltr_dollar[] = {2,0, 1,1, 2,1, 3,1, 4,1, 0,2, 2,2, 1,3, 2,3, 3,3, 2,4, 4,4, 0,5, 1,5, 2,5, 3,5};
int ltr_percent[] = {0,0, 1,0, 4,0, 0,1, 1,1, 3,1, 2,2, 2,3, 1,4, 3,4, 4,4, 0,5, 3,5, 4,5};
int ltr_amp[] = {1,0, 2,0, 0,1, 3,1, 1,2, 2,2, 1,3, 2,3, 4,3, 0,4, 3,4, 1,5, 2,5, 4,5};
int ltr_quote[] = {0,0, 0,1};
int ltr_lparen[] = {1,0, 0,1, 0,2, 0,3, 0,4, 1,5};
int ltr_rparen[] = {0,0, 1,1, 1,2, 1,3, 1,4, 0,5};
int ltr_asterisk[] = {0,0, 2,0, 1,1, 0,2, 2,2};
int ltr_plus[] = {1,1, 0,2, 1,2, 2,2, 1,3};
int ltr_comma[] = {0,5, 0,6};
int ltr_dash[] = {0,2, 1,2, 2,2};
int ltr_period[] = {0,5};
int ltr_slash[] = {3,0, 2,1, 2,2, 1,3, 1,4, 0,5};
int ltr_zero[] = {1,0, 2,0, 0,1, 3,1, 0,2, 3,2, 0,3, 3,3, 0,4, 3,4, 1,5, 2,5};
int ltr_one[] = {1,0, 0,1, 1,1, 1,2, 1,3, 1,4, 0,5, 1,5, 2,5};
int ltr_two[] = {1,0, 2,0, 0,1, 3,1, 3,2, 2,3, 1,4, 0,5, 1,5, 2,5, 3,5};
int ltr_three[] = {1,0, 2,0, 0,1, 3,1, 2,2, 3,3, 0,4, 3,4, 1,5, 2,5};
int ltr_four[] = {0,0, 3,0, 0,1, 3,1, 0,2, 1,2, 2,2, 3,2, 3,3, 3,4, 3,5};
int ltr_five[] = {0,0, 1,0, 2,0, 3,0, 0,1, 0,2, 1,2, 2,2, 3,3, 0,4, 3,4, 1,5, 2,5};
int ltr_six[] = {1,0, 2,0, 3,0, 0,1, 0,2, 1,2, 2,2, 0,3, 3,3, 0,4, 3,4, 1,5, 2,5};
int ltr_seven[] = {0,0, 1,0, 2,0, 3,0, 3,1, 2,2, 1,3, 1,4, 1,5};
int ltr_eight[] = {1,0, 2,0, 0,1, 3,1, 1,2, 2,2, 0,3, 3,3, 0,4, 3,4, 1,5, 2,5};
int ltr_nine[] = {1,0, 2,0, 0,1, 3,1, 0,2, 3,2, 1,3, 2,3, 3,3, 3,4, 1,5, 2,5};
int ltr_colon[] = {0,1, 0,4};
int ltr_semicolon[] = {0,1, 0,4, 0,5};
int ltr_lthan[] = {2,0, 1,1, 0,2, 1,3, 2,4};
int ltr_equal[] = {0,1, 1,1, 2,1, 0,3, 1,3, 2,3};
int ltr_gthan[] = {0,0, 1,1, 2,2, 1,3, 0,4};
int ltr_question[] = {1,0, 2,0, 0,1, 3,1, 3,2, 1,3, 2,3, 1,5};
int ltr_at[] = {1,0, 2,0, 3,0, 0,1, 4,1, 1,2, 2,2, 4,2, 0,3, 2,3, 4,3, 0,4, 4,4, 1,5, 2,5, 3,5};
int ltr_A[] = {1,0, 2,0, 0,1, 3,1, 0,2, 1,2, 2,2, 3,2, 0,3, 3,3, 0,4, 3,4, 0,5, 3,5};
int ltr_B[] = {0,0, 1,0, 2,0, 0,1, 3,1, 0,2, 1,2, 2,2, 0,3, 3,3, 0,4, 3,4, 0,5, 1,5, 2,5};
int ltr_C[] = {1,0, 2,0, 0,1, 3,1, 0,2, 0,3, 0,4, 3,4, 1,5, 2,5};
int ltr_D[] = {0,0, 1,0, 2,0, 0,1, 3,1, 0,2, 3,2, 0,3, 3,3, 0,4, 3,4, 0,5, 1,5, 2,5};
int ltr_E[] = {0,0, 1,0, 2,0, 3,0, 0,1, 0,2, 1,2, 2,2, 0,3, 0,4, 0,5, 1,5, 2,5, 3,5};
int ltr_F[] = {0,0, 1,0, 2,0, 3,0, 0,1, 0,2, 1,2, 2,2, 0,3, 0,4, 0,5};
int ltr_G[] = {1,0, 2,0, 0,1, 3,1, 0,2, 0,3, 2,3, 3,3, 0,4, 3,4, 1,5, 2,5};
int ltr_H[] = {0,0, 3,0, 0,1, 3,1, 0,2, 1,2, 2,2, 3,2, 0,3, 3,3, 0,4, 3,4, 0,5, 3,5};
int ltr_I[] = {0,0, 1,0, 2,0, 1,1, 1,2, 1,3, 1,4, 0,5, 1,5, 2,5};
int ltr_J[] = {1,0, 2,0, 3,0, 2,1, 2,2, 2,3, 0,4, 2,4, 1,5};
int ltr_K[] = {0,0, 3,0, 0,1, 2,1, 0,2, 1,2, 0,3, 2,3, 0,4, 3,4, 0,5, 3,5};
int ltr_L[] = {0,0, 0,1, 0,2, 0,3, 0,4, 0,5, 1,5, 2,5, 3,5};
int ltr_M[] = {0,0, 4,0, 0,1, 1,1, 3,1, 4,1, 0,2, 2,2, 4,2, 0,3, 4,3, 0,4, 4,4, 0,5, 4,5};
int ltr_N[] = {0,0, 4,0, 0,1, 1,1, 4,1, 0,2, 2,2, 4,2, 0,3, 2,3, 4,3, 0,4, 3,4, 4,4, 0,5, 4,5};
int ltr_O[] = {1,0, 2,0, 3,0, 0,1, 4,1, 0,2, 4,2, 0,3, 4,3, 0,4, 4,4, 1,5, 2,5, 3,5};
int ltr_P[] = {0,0, 1,0, 2,0, 0,1, 3,1, 0,2, 1,2, 2,2, 0,3, 0,4, 0,5};
int ltr_Q[] = {1,0, 2,0, 0,1, 3,1, 0,2, 3,2, 0,3, 3,3, 0,4, 2,4, 3,4, 1,5, 2,5, 3,5};
int ltr_R[] = {0,0, 1,0, 2,0, 0,1, 3,1, 0,2, 1,2, 2,2, 0,3, 3,3, 0,4, 3,4, 0,5, 3,5};
int ltr_S[] = {1,0, 2,0, 0,1, 3,1, 1,2, 2,3, 0,4, 3,4, 1,5, 2,5};
int ltr_T[] = {0,0, 1,0, 2,0, 1,1, 1,2, 1,3, 1,4, 1,5};
int ltr_U[] = {0,0, 3,0, 0,1, 3,1, 0,2, 3,2, 0,3, 3,3, 0,4, 3,4, 1,5, 2,5};
int ltr_V[] = {0,0, 4,0, 0,1, 4,1, 1,2, 3,2, 1,3, 3,3, 2,4, 2,5};
int ltr_W[] = {0,0, 4,0, 0,1, 4,1, 0,2, 4,2, 0,3, 4,3, 0,4, 2,4, 4,4, 1,5, 3,5};
int ltr_X[] = {0,0, 4,0, 1,1, 3,1, 2,2, 2,3, 1,4, 3,4, 0,5, 4,5};
int ltr_Y[] = {0,0, 4,0, 1,1, 3,1, 2,2, 2,3, 2,4, 2,5};
int ltr_Z[] = {0,0, 1,0, 2,0, 3,0, 3,1, 2,2, 1,3, 0,4, 0,5, 1,5, 2,5, 3,5};
int ltr_lsqbrace[] = {0,0, 1,0, 0,1, 0,2, 0,3, 0,4, 0,5, 1,5};
int ltr_backslash[] = {0,0, 1,1, 1,2, 2,3, 2,4, 3,5};
int ltr_rsqbrace[] = {0,0, 1,0, 1,1, 1,2, 1,3, 1,4, 0,5, 1,5};
int ltr_carat[] = {1,0, 0,1, 2,1};
int ltr_underscr[] = {0,5, 1,5, 2,5};
int ltr_accent[] = {0,0, 1,1};
int ltr_a[] = {1,1, 2,1, 3,2, 1,3, 2,3, 3,3, 0,4, 3,4, 1,5, 2,5, 3,5};
int ltr_b[] = {0,0, 0,1, 0,2, 1,2, 2,2, 0,3, 3,3, 0,4, 3,4, 0,5, 1,5, 2,5};
int ltr_c[] = {1,2, 2,2, 3,2, 0,3, 0,4, 1,5, 2,5, 3,5};
int ltr_d[] = {3,0, 3,1, 1,2, 2,2, 3,2, 0,3, 3,3, 0,4, 3,4, 1,5, 2,5, 3,5};
int ltr_e[] = {1,2, 2,2, 0,3, 1,3, 2,3, 3,3, 0,4, 1,5, 2,5, 3,5};
int ltr_f[] = {2,0, 1,1, 0,2, 1,2, 2,2, 1,3, 1,4, 1,5};
int ltr_g[] = {1,2, 2,2, 0,3, 3,3, 1,4, 2,4, 3,4, 3,5, 0,6, 1,6, 2,6};
int ltr_h[] = {0,0, 0,1, 0,2, 1,2, 2,2, 0,3, 3,3, 0,4, 3,4, 0,5, 3,5};
int ltr_i[] = {0,1, 0,3, 0,4, 0,5};
int ltr_j[] = {2,1, 2,3, 2,4, 2,5, 0,6, 1,6};
int ltr_k[] = {0,0, 0,1, 0,2, 2,2, 0,3, 1,3, 0,4, 2,4, 0,5, 3,5};
int ltr_l[] = {0,0, 0,1, 0,2, 0,3, 0,4, 0,5, 1,5};
int ltr_m[] = {1,2, 3,2, 0,3, 2,3, 4,3, 0,4, 4,4, 0,5, 4,5};
int ltr_n[] = {1,2, 0,3, 2,3, 0,4, 2,4, 0,5, 2,5};
int ltr_o[] = {1,2, 0,3, 2,3, 0,4, 2,4, 1,5};
int ltr_p[] = {0,2, 1,2, 2,2, 0,3, 3,3, 0,4, 1,4, 2,4, 0,5, 0,6};
int ltr_q[] = {1,2, 2,2, 0,3, 3,3, 1,4, 2,4, 3,4, 3,5, 3,6, 4,6};
int ltr_r[] = {1,2, 2,2, 0,3, 0,4, 0,5};
int ltr_s[] = {1,1, 2,1, 0,2, 1,3, 2,4, 0,5, 1,5};
int ltr_t[] = {1,0, 1,1, 0,2, 1,2, 2,2, 1,3, 1,4, 1,5};
int ltr_u[] = {0,2, 3,2, 0,3, 3,3, 0,4, 3,4, 1,5, 2,5};
int ltr_v[] = {0,2, 2,2, 0,3, 2,3, 0,4, 2,4, 1,5};
int ltr_w[] = {0,2, 4,2, 0,3, 4,3, 0,4, 2,4, 4,4, 1,5, 3,5};
int ltr_x[] = {0,2, 2,2, 1,3, 1,4, 0,5, 2,5};
int ltr_y[] = {0,2, 2,2, 0,3, 2,3, 1,4, 2,4, 2,5, 0,6, 1,6};
int ltr_z[] = {0,1, 1,1, 2,1, 2,2, 1,3, 0,4, 0,5, 1,5, 2,5};
int ltr_lcrlbrace[] = {2,0, 1,1, 0,2, 1,2, 1,3, 1,4, 2,5};
int ltr_pipe[] = {0,0, 0,1, 0,2, 0,3, 0,5, 0,6, 0,7, 0,8};
int ltr_rcurlbrace[] = {0,0, 1,1, 1,2, 2,2, 1,3, 1,4, 0,5};
int ltr_tilde[] = {1,1, 3,1, 0,2, 2,2};

letterSet[-1] = new Letter(' ', 32, ltr_space,  0, 3); 
letterSet[0] = new Letter('!', 33, ltr_bang,  6, 1); 
letterSet[1] = new Letter('"', 34, ltr_dblquote,  4, 3); 
letterSet[2] = new Letter('#', 35, ltr_hash, 16, 5); 
letterSet[3] = new Letter('$', 36, ltr_dollar, 16, 5); 
letterSet[4] = new Letter('%', 37, ltr_percent, 14, 5); 
letterSet[5] = new Letter('&', 38, ltr_amp, 14, 5); 
letterSet[6] = new Letter('\'', 39, ltr_quote,  2, 1); 
letterSet[7] = new Letter('(', 40, ltr_lparen,  6, 2); 
letterSet[8] = new Letter(')', 41, ltr_rparen,  6, 2); 
letterSet[9] = new Letter('*', 42, ltr_asterisk,  5, 3); 
letterSet[10] = new Letter('+', 43, ltr_plus,  5, 3); 
letterSet[11] = new Letter(',', 44, ltr_comma,  2, 1); 
letterSet[12] = new Letter('-', 45, ltr_dash,  3, 3); 
letterSet[13] = new Letter('.', 46, ltr_period,  1, 1); 
letterSet[14] = new Letter('/', 47, ltr_slash,  6, 4); 
letterSet[15] = new Letter('0', 48, ltr_zero, 12, 4); 
letterSet[16] = new Letter('1', 49, ltr_one,  9, 3); 
letterSet[17] = new Letter('2', 50, ltr_two, 11, 4); 
letterSet[18] = new Letter('3', 51, ltr_three, 10, 4); 
letterSet[19] = new Letter('4', 52, ltr_four, 11, 4); 
letterSet[20] = new Letter('5', 53, ltr_five, 13, 4); 
letterSet[21] = new Letter('6', 54, ltr_six, 13, 4); 
letterSet[22] = new Letter('7', 55, ltr_seven,  9, 4); 
letterSet[23] = new Letter('8', 56, ltr_eight, 12, 4); 
letterSet[24] = new Letter('9', 57, ltr_nine, 12, 4); 
letterSet[25] = new Letter(':', 58, ltr_colon,  2, 1); 
letterSet[26] = new Letter(';', 59, ltr_semicolon,  3, 1); 
letterSet[27] = new Letter('<', 60, ltr_lthan,  5, 3); 
letterSet[28] = new Letter('=', 61, ltr_equal,  6, 3); 
letterSet[29] = new Letter('>', 62, ltr_gthan,  5, 3); 
letterSet[30] = new Letter('?', 63, ltr_question,  8, 4); 
letterSet[31] = new Letter('@', 64, ltr_at, 16, 5); 
letterSet[32] = new Letter('A', 65, ltr_A, 14, 4); 
letterSet[33] = new Letter('B', 66, ltr_B, 15, 4); 
letterSet[34] = new Letter('C', 67, ltr_C, 10, 4); 
letterSet[35] = new Letter('D', 68, ltr_D, 14, 4); 
letterSet[36] = new Letter('E', 69, ltr_E, 14, 4); 
letterSet[37] = new Letter('F', 70, ltr_F, 11, 4); 
letterSet[38] = new Letter('G', 71, ltr_G, 12, 4); 
letterSet[39] = new Letter('H', 72, ltr_H, 14, 4); 
letterSet[40] = new Letter('I', 73, ltr_I, 10, 3); 
letterSet[41] = new Letter('J', 74, ltr_J,  9, 4); 
letterSet[42] = new Letter('K', 75, ltr_K, 12, 4); 
letterSet[43] = new Letter('L', 76, ltr_L,  9, 4); 
letterSet[44] = new Letter('M', 77, ltr_M, 15, 5); 
letterSet[45] = new Letter('N', 78, ltr_N, 16, 5); 
letterSet[46] = new Letter('O', 79, ltr_O, 14, 5); 
letterSet[47] = new Letter('P', 80, ltr_P, 11, 4); 
letterSet[48] = new Letter('Q', 81, ltr_Q, 14, 4); 
letterSet[49] = new Letter('R', 82, ltr_R, 14, 4); 
letterSet[50] = new Letter('S', 83, ltr_S, 10, 4); 
letterSet[51] = new Letter('T', 84, ltr_T,  8, 3); 
letterSet[52] = new Letter('U', 85, ltr_U, 12, 4); 
letterSet[53] = new Letter('V', 86, ltr_V, 10, 5); 
letterSet[54] = new Letter('W', 87, ltr_W, 13, 5); 
letterSet[55] = new Letter('X', 88, ltr_X, 10, 5); 
letterSet[56] = new Letter('Y', 89, ltr_Y,  8, 5); 
letterSet[57] = new Letter('Z', 90, ltr_Z, 12, 4); 
letterSet[58] = new Letter('[', 91, ltr_lsqbrace,  8, 2); 
letterSet[59] = new Letter('\\', 92, ltr_backslash,  6, 4); 
letterSet[60] = new Letter(']', 93, ltr_rsqbrace,  8, 2); 
letterSet[61] = new Letter('^', 94, ltr_carat,  3, 3); 
letterSet[62] = new Letter('_', 95, ltr_underscr,  3, 3); 
letterSet[63] = new Letter('`', 96, ltr_accent,  2, 2); 
letterSet[64] = new Letter('a', 97, ltr_a, 11, 4); 
letterSet[65] = new Letter('b', 98, ltr_b, 12, 4); 
letterSet[66] = new Letter('c', 99, ltr_c,  8, 4); 
letterSet[67] = new Letter('d', 100, ltr_d, 12, 4); 
letterSet[68] = new Letter('e', 101, ltr_e, 10, 4); 
letterSet[69] = new Letter('f', 102, ltr_f,  8, 3); 
letterSet[70] = new Letter('g', 103, ltr_g, 11, 4); 
letterSet[71] = new Letter('h', 104, ltr_h, 11, 4); 
letterSet[72] = new Letter('i', 105, ltr_i,  4, 1); 
letterSet[73] = new Letter('j', 106, ltr_j,  6, 3); 
letterSet[74] = new Letter('k', 107, ltr_k, 10, 4); 
letterSet[75] = new Letter('l', 108, ltr_l,  7, 2); 
letterSet[76] = new Letter('m', 109, ltr_m,  9, 5); 
letterSet[77] = new Letter('n', 110, ltr_n,  7, 3); 
letterSet[78] = new Letter('o', 111, ltr_o,  6, 3); 
letterSet[79] = new Letter('p', 112, ltr_p, 10, 4); 
letterSet[80] = new Letter('q', 113, ltr_q, 10, 5); 
letterSet[81] = new Letter('r', 114, ltr_r,  5, 3); 
letterSet[82] = new Letter('s', 115, ltr_s,  7, 3); 
letterSet[83] = new Letter('t', 116, ltr_t,  8, 3); 
letterSet[84] = new Letter('u', 117, ltr_u,  8, 4); 
letterSet[85] = new Letter('v', 118, ltr_v,  7, 3); 
letterSet[86] = new Letter('w', 119, ltr_w,  9, 5); 
letterSet[87] = new Letter('x', 120, ltr_x,  6, 3); 
letterSet[88] = new Letter('y', 121, ltr_y,  9, 3); 
letterSet[89] = new Letter('z', 122, ltr_z,  9, 3); 
letterSet[90] = new Letter('{', 123, ltr_lcrlbrace,  7, 3); 
letterSet[91] = new Letter('|', 124, ltr_pipe,  8, 1); 
letterSet[92] = new Letter('}', 125, ltr_rcurlbrace,  7, 3); 
letterSet[93] = new Letter('~', 126, ltr_tilde,  4, 4); 

//}; //end letterSet[]
} //end init()

void test() {

	// Letter X = letterSet['N' - MIN_LETTER];
	// int x, y, value;
	// x = y = value = 1;
	
	//Serial.begin(9600);
	// Serial.print("Printing: '");
	// Serial.print(X.character);
	// Serial.print("' - ");
	// Serial.print(X.pixelCount);
	// Serial.println(" pixels.");

	// for (int pixel=0; pixel<X.pixelCount; pixel++) {
		// int i = pixel*2;
		// int xOffset = x + X.pixels[i];
		// int yOffset = y + X.pixels[i+1];
		// Serial.print(pixel);
		// Serial.print(": ");
		// Serial.print("(");
		// Serial.print(i);
		// Serial.print(")");
		// Serial.print(X.pixels[i]);
		// Serial.print(", ");
		// Serial.println(X.pixels[i+1]);
		// LedSign::Set(xOffset, yOffset, value);
	// }

delay(6000);
}

int draw(char letter, int x, int y, int value) {
	if (letter == ' ')
		return 3;
		
	if (letter < MIN_LETTER || letter > MAX_LETTER)
		return 0;

	Letter toDraw = letterSet[letter - MIN_LETTER];

	for (int pixel=0; pixel<toDraw.pixelCount; pixel++) {
		int i = pixel*2;
		int xOffset = x + toDraw.pixels[i];
		int yOffset = y + toDraw.pixels[i+1];
		if (xOffset >= SCR_LEFT && xOffset <= SCR_RIGHT && yOffset >= SCR_TOP && yOffset <= SCR_BOTTOM)
			LedSign::Set(xOffset, yOffset, value);
	}

	return toDraw.size;
}

int messageWidth(char* message) {
	int msgWidth = 0; 

	for (int i=0; message[i] != '\0'; i++) {
		msgWidth += message[i];
	}
  
	return msgWidth;
}

}//end Letters namespace

