/*
 * fonts.h
 *
 * Created: 19-01-2026 14:06:15
 *  Author: NIVYA
 */ 


#ifndef FONTS_H_
#define FONTS_H_

#include <stdint.h>
#include <string.h>

/* Font definition structure */
typedef struct {
	uint8_t FontWidth;      // Width of each character
	uint8_t FontHeight;     // Height of each character
	const uint16_t *data;   // Pointer to font data array
} FontDef_t;

/* String size structure */
typedef struct {
	uint16_t Length;        // String length in pixels
	uint16_t Height;        // String height in pixels
} FONTS_SIZE_t;

/* Available fonts */
extern FontDef_t Font_7x10;
extern FontDef_t Font_11x18;
extern FontDef_t Font_16x26;

/* Function prototypes */
char* FONTS_GetStringSize(char* str, FONTS_SIZE_t* SizeStruct, FontDef_t* Font);

#endif /* FONTS_H_ */