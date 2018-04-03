/*
 * lcd_drv.cpp
 *
 *  Created on: Apr 3, 2018
 *      Author: horia
 */
#include "lcd_drv.h"
#include <stdint.h>
#include <msp430.h>

//Change based on LCD Memory locations
#define POS_1 9   /* Digit A1 begins at S18 */
#define POS_2 5   /* Digit A2 begins at S10 */
#define POS_3 3   /* Digit A3 begins at S6  */
#define POS_4 18  /* Digit A4 begins at S36 */
#define POS_5 14  /* Digit A5 begins at S28 */
#define POS_7 7   /* Digit A6 begins at S14 */
#define LCD_C_CLOCKDIVIDER_1                                         (LCDDIV_0)
#define LCD_C_CLOCKPRESCALAR_16                                      (LCDPRE_4)
#define LCD_C_4_MUX                                           (LCDMX1 | LCDMX0)
#define LCD_C_LOW_POWER_WAVEFORMS                                       (LCDLP)
#define LCD_C_SEGMENTS_DISABLED                                           (0x0)
#define LCD_C_SEGMENTS_ENABLED                                         (LCDSON)
#define LCD_C_CLOCKSOURCE_ACLK                                            (0x0)
#define LCD_C_INTERNAL_REFERENCE_VOLTAGE                            (VLCDREF_0)
#define LCD_C_VLCD_GENERATED_INTERNALLY                                   (0x0)
#define LCD_C_V2V3V4_GENERATED_INTERNALLY_NOT_SWITCHED_TO_PINS            (0x0)
#define LCD_C_V5_VSS                                                      (0x0)
#define LCD_C_CHARGEPUMP_VOLTAGE_3_02V_OR_2_52VREF                      (VLCD3)

#define LCD_C_SEGMENT_LINE_0                                                (0)
#define LCD_C_SEGMENT_LINE_21                                              (21)
#define LCD_C_SEGMENT_LINE_26                                              (26)
#define LCD_C_SEGMENT_LINE_43                                              (43)
#define LCD_C_SYNCHRONIZATION_ENABLED                            (LCDCPCLKSYNC)

typedef struct
{
    uint16_t clockSource;
    uint16_t clockDivider;
    uint16_t clockPrescalar;
    uint16_t muxRate;
    uint16_t waveforms;
    uint16_t segments;
} LCD_C_initParam;

// LCD memory map for numeric digits
const char digit[10][2] = { { 0xFC, 0x28 }, /* "0" LCD segments a+b+c+d+e+f+k+q */
{ 0x60, 0x20 }, /* "1" */
{ 0xDB, 0x00 }, /* "2" */
{ 0xF3, 0x00 }, /* "3" */
{ 0x67, 0x00 }, /* "4" */
{ 0xB7, 0x00 }, /* "5" */
{ 0xBF, 0x00 }, /* "6" */
{ 0xE4, 0x00 }, /* "7" */
{ 0xFF, 0x00 }, /* "8" */
{ 0xF7, 0x00 } /* "9" */
};

// LCD memory map for uppercase letters
const char alphabetBig[26][2] = { { 0xEF, 0x00 }, /* "A" LCD segments a+b+c+e+f+g+m */
{ 0xF1, 0x50 }, /* "B" */
{ 0x9C, 0x00 }, /* "C" */
{ 0xF0, 0x50 }, /* "D" */
{ 0x9F, 0x00 }, /* "E" */
{ 0x8F, 0x00 }, /* "F" */
{ 0xBD, 0x00 }, /* "G" */
{ 0x6F, 0x00 }, /* "H" */
{ 0x90, 0x50 }, /* "I" */
{ 0x78, 0x00 }, /* "J" */
{ 0x0E, 0x22 }, /* "K" */
{ 0x1C, 0x00 }, /* "L" */
{ 0x6C, 0xA0 }, /* "M" */
{ 0x6C, 0x82 }, /* "N" */
{ 0xFC, 0x00 }, /* "O" */
{ 0xCF, 0x00 }, /* "P" */
{ 0xFC, 0x02 }, /* "Q" */
{ 0xCF, 0x02 }, /* "R" */
{ 0xB7, 0x00 }, /* "S" */
{ 0x80, 0x50 }, /* "T" */
{ 0x7C, 0x00 }, /* "U" */
{ 0x0C, 0x28 }, /* "V" */
{ 0x6C, 0x0A }, /* "W" */
{ 0x00, 0xAA }, /* "X" */
{ 0x00, 0xB0 }, /* "Y" */
{ 0x90, 0x28 } /* "Z" */
};

static void setLCDFunction(uint8_t index, uint16_t value)
{
    switch (index)
    {
        case 0:
            LCDCPCTL0 |= value;
            break;
        case 1:
            LCDCPCTL1 |= value;
            break;
        case 2:
            LCDCPCTL2 |= value;
            break;
        default:
            break;
    }
}

static void LCD_C_init(LCD_C_initParam *initParams)
{
    LCDCCTL0 &= ~LCDON;
    LCDCCTL0 &= ~(LCDMX0 | LCDMX1 | LCDMX2 | LCDSSEL | LCDLP | LCDSON
            | LCDDIV_31);

    LCDCCTL0 |= initParams->muxRate;
    LCDCCTL0 |= initParams->clockSource;
    LCDCCTL0 |= initParams->waveforms;
    LCDCCTL0 |= initParams->segments;
    LCDCCTL0 |= initParams->clockDivider;
    LCDCCTL0 |= initParams->clockPrescalar;
}

static void LCD_C_on(void)
{
    LCDCCTL0 |= LCDON;
}

static void LCD_C_clearMemory(void)
{
    LCDCMEMCTL |= LCDCLRM;
}

static void LCD_C_enableChargePump(void)
{
    LCDCCTL0 &= ~LCDON;
    LCDCVCTL |= LCDCPEN;
}

static void LCD_C_selectChargePumpReference(uint16_t reference)
{
    LCDCCTL0 &= ~LCDON;
    LCDCVCTL &= ~VLCDREF_3;

    LCDCVCTL |= reference;
}

static void LCD_C_setVLCDSource(uint16_t vlcdSource, uint16_t v2v3v4Source,
                                uint16_t v5Source)
{
    LCDCCTL0 &= ~LCDON;
    LCDCVCTL &= ~VLCDEXT;
    LCDCVCTL &= ~LCDREXT;
    LCDCVCTL &= ~LCDEXTBIAS;
    LCDCVCTL &= ~R03EXT;

    LCDCVCTL |= vlcdSource;
    LCDCVCTL |= v2v3v4Source;
    LCDCVCTL |= v5Source;
}

static void LCD_C_setVLCDVoltage(uint16_t voltage)
{
    LCDCCTL0 &= ~LCDON;
    LCDCVCTL &= ~VLCD_15;

    LCDCVCTL |= voltage;
}

static void LCD_C_setPinAsLCDFunctionEx(uint8_t startPin, uint8_t endPin)
{
    uint8_t startIdx = startPin >> 4;
    uint8_t endIdx = endPin >> 4;
    uint8_t startPos = startPin & 0xF;
    uint8_t endPos = endPin & 0xF;
    uint16_t val = 0;
    uint8_t i = 0;

    LCDCCTL0 &= ~LCDON;

    if (startIdx == endIdx)
    {
        val = (0xFFFF >> (15 - endPos)) & (0xFFFF << startPos);

        setLCDFunction(startIdx, val);
    }
    else
    {
        val = 0xFFFF >> (15 - endPos);
        setLCDFunction(endIdx, val);

        for( i = endIdx - 1; i > startIdx; i--)
        {
            setLCDFunction(i, 0xFFFF);
        }

        val = 0xFFFF << startPos;
        setLCDFunction(startIdx, val);
    }
}

static void LCD_C_configChargePump(uint16_t syncToClock,
                                   uint16_t functionControl)
{
    LCDCCPCTL &= ~(LCDCPCLKSYNC);
    LCDCCPCTL &= ~(LCDCPDIS7 | LCDCPDIS6 | LCDCPDIS5 | LCDCPDIS4 | LCDCPDIS3
            | LCDCPDIS2 | LCDCPDIS1 | LCDCPDIS0);

    LCDCCPCTL |= syncToClock | functionControl;
}

extern void Init_LCD()
{
    LCD_C_initParam initParams = { 0 };
    initParams.clockSource = LCD_C_CLOCKSOURCE_ACLK;
    initParams.clockDivider = LCD_C_CLOCKDIVIDER_1;
    initParams.clockPrescalar = LCD_C_CLOCKPRESCALAR_16;
    initParams.muxRate = LCD_C_4_MUX;
    initParams.waveforms = LCD_C_LOW_POWER_WAVEFORMS;
    initParams.segments = LCD_C_SEGMENTS_ENABLED;

    LCD_C_init(&initParams);
    // LCD Operation - VLCD generated internally, V2-V4 generated internally, v5 to ground

    LCD_C_setPinAsLCDFunctionEx(LCD_C_SEGMENT_LINE_0,
    LCD_C_SEGMENT_LINE_21);
    LCD_C_setPinAsLCDFunctionEx(LCD_C_SEGMENT_LINE_26,
    LCD_C_SEGMENT_LINE_43);

    LCD_C_setVLCDSource(LCD_C_VLCD_GENERATED_INTERNALLY,
    LCD_C_V2V3V4_GENERATED_INTERNALLY_NOT_SWITCHED_TO_PINS,
                        LCD_C_V5_VSS);

    // Set VLCD voltage to 3.20v
    LCD_C_setVLCDVoltage(LCD_C_CHARGEPUMP_VOLTAGE_3_02V_OR_2_52VREF);

    // Enable charge pump and select internal reference for it
    LCD_C_enableChargePump();
    LCD_C_selectChargePumpReference(LCD_C_INTERNAL_REFERENCE_VOLTAGE);

    LCD_C_configChargePump( LCD_C_SYNCHRONIZATION_ENABLED, 0);

    // Clear LCD memory
    LCD_C_clearMemory();

    //Turn LCD on
    LCD_C_on();
}

/*
 * Displays input character at given LCD digit/position
 * Only spaces, numeric digits, and uppercase letters are accepted characters
 */
void showChar(char c, unsigned position)
{
    if (c == ' ')
    {
        // Display space
        LCDMEM[position] = 0;
        LCDMEM[position + 1] = 0;
    }
    else if (c >= '0' && c <= '9')
    {
        // Display digit
        LCDMEM[position] = digit[c - 48][0];
        LCDMEM[position + 1] = digit[c - 48][1];
    }
    else if (c >= 'A' && c <= 'Z')
    {
        // Display alphabet
        LCDMEM[position] = alphabetBig[c - 65][0];
        LCDMEM[position + 1] = alphabetBig[c - 65][1];
    }
    else
    {
        // Turn all segments on if character is not a space, digit, or uppercase letter
        LCDMEM[position] = 0xFF;
        LCDMEM[position + 1] = 0xFF;
    }
}

/*
 * Clears memories to all 6 digits on the LCD
 */
void clearLCD()
{
    LCDMEM[POS_1] = LCDBMEM[POS_1] = 0;
    LCDMEM[POS_1 + 1] = LCDBMEM[POS_1 + 1] = 0;
    LCDMEM[POS_2] = LCDBMEM[POS_2] = 0;
    LCDMEM[POS_2 + 1] = LCDBMEM[POS_2 + 1] = 0;
    LCDMEM[POS_3] = LCDBMEM[POS_3] = 0;
    LCDMEM[POS_3 + 1] = LCDBMEM[POS_3 + 1] = 0;
    LCDMEM[POS_4] = LCDBMEM[POS_4] = 0;
    LCDMEM[POS_4 + 1] = LCDBMEM[POS_4 + 1] = 0;
    LCDMEM[POS_5] = LCDBMEM[POS_5] = 0;
    LCDMEM[POS_5 + 1] = LCDBMEM[POS_5 + 1] = 0;
    LCDMEM[POS_7] = LCDBMEM[POS_7] = 0;
    LCDMEM[POS_7 + 1] = LCDBMEM[POS_7 + 1] = 0;

    LCDM14 = LCDBM14 = 0x00;
    LCDM18 = LCDBM18 = 0x00;
    LCDM3 = LCDBM3 = 0x00;
}

