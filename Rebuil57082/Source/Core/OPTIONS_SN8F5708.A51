$NOMOD51
;------------------------------------------------------------------------------
;
;  Copyright (c) 2015 SONiX Technology Co., Ltd.
;  Version 2.1 - SN8F5708, SN8F5707, SN8F5705, SN8F57081, SN8F57082, SN8F57084, SN8F57085, SN8F57086, SN8F57087
;	 Version 2.2 - Add code option address for MP5
;    Version 2.3 - Repair an error, omission, etc.
;  *** <<< Use Configuration Wizard in Context Menu >>> ***
;------------------------------------------------------------------------------
;
;  This preference, such as watchdog, external reset pin, and clock source, is preloaded 
;  during the microcontroller's power-on. It is strongly recommanded to use configuration 
;  wizard to set these parameters up appropriately.
;
;------------------------------------------------------------------------------
ROM_SIZE		EQU		0x4000
;
;   <o> Program Memory Security <0x01=> Disable <0x00=> Enable
    SECURITY_SET    EQU     0x01	;	{0x3FFF}
;   <i> The debug interface cannot read program memory if this security option is enable.
;   <i> Erase Full Chip can be proformmed to erase original code/data and unlock security.
;
;   <o.1..3> CPU Clock Source <0x07=> IHRC 32 MHz <0x03=> IHRC 32 MHz with RTC <0x01=> X'tal 12 MHz <0x00=> X'tal 4 MHz <0x02=> External Clock
    CLOCKSRC_SET    EQU     0x0E	;	{0x3FFF}
;   <i> IHRC 32 MHz: on-chip internal clock with or without Timer 0 real time clock.
;   <i> X'tal 12 MHz: off-chip crystal between 4 MHz and 16 MHz.
;   <i> X'tal 4 MHz: off-chip crystal between 1 MHz and 4 MHz.
;   <i> External Clock: external clock input from XIN pin.
;
;   <o> Noise Filter <0x01=> Disable <0x00=> Enable
    NOISEFILT_SET   EQU     0x01	;	{0x3FFC}
;
;   <h> Reset Sources
;       <o.1..2> VDD Voltage (Low Voltage Detection) <0x00=> LVD_Max <0x01=> LVD_H <0x02=> LVD_M <0x03=> LVD_L
        LVDMODE_SET     EQU     0x06	;	{0x3FFC}
;       <i> LVD_Max: 3.3 V or below triggers reset.
;       <i> LVD_H: 2.4 V or below triggers reset with LVD33 indicator.
;       <i> LVD_M: 1.8 V or below triggers reset with LVD24 indicator.
;       <i> LVD_L: 1.8 V or below triggers reset.
;
;       <o.4..5> External Reset / GPIO Shared Pin <0x00=> Reset with De-bounce <0x02=> Reset without De-bounce <0x03=> GPIO
        RESETPIN_SET    EQU     0x30	;	{0x3FFC}
;       <i> Reset with De-bounce: Triggers reset if this pin is pulled low over 4 ms.
;       <i> Reset without De-bounce: Triggers reset immediately if this pin is pulled low.
;       <i> GPIO: The shared pin is reserved for general purpose input/output.
;       <i> The de-bounce period is based on Internal Low R-C Clock which has a gentle inaccuracy.
;
;       <o.4..7> Watchdog Reset <0x00=> Always <0x05=> Enable <0x0A=> Disable
        WATCHDOG_SET    EQU     0xA0	;	{0x3FFF}
;       <i> Always: Trun on watchdog function including Normal, IDLE, and SLEEP mode.
;       <i> Enable: Turn on watchdog function only in Normal mode.
;       <i> Disable: Turn off watchdog function.
;
;       <o.6..7> Watchdog Overflow Period <0x00=> 64 ms <0x01=> 128 ms <0x02=> 256 ms <0x03=> 512 ms
        WATCHCLK_SET    EQU     0xC0	;	{0x3FFC}
;       <i> The watchdog overflow period is based on Internal Low R-C Clock which has a gentle inaccuracy.
;   </h>


    CSEG    AT      0x3FF6
    DB      0xFF
    DB      0xFF
    DB      0xFF
    DB      0xFF
    DB      0xFF
    DB      0xFF
    DB      WATCHCLK_SET + RESETPIN_SET + LVDMODE_SET + NOISEFILT_SET
    DB      0x5A
    DB      0xA5
    DB      WATCHDOG_SET + CLOCKSRC_SET + SECURITY_SET
    END
