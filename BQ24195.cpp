
/*
There are 11 registers that allow the user to control and monitor all the parameters
of the BQ24195. The functions are grouped by the registers they belong to.
----------------------------------------------------------
REGISTER NAME                           ADDRESS     TYPE
----------------------------------------------------------
INPUT_SOURCE_REGISTER                   0x00        R/W
POWERON_CONFIG_REGISTER                 0x01        R/W
CHARGE_CURRENT_CONTROL_REGISTER         0x02        R/W
PRECHARGE_CURRENT_CONTROL_REGISTER      0x03        R/W
CHARGE_VOLTAGE_CONTROL_REGISTER         0x04        R/W
CHARGE_TIMER_CONTROL_REGISTER           0x05        R/W
THERMAL_REG_CONTROL_REGISTER            0x06        R/W
MISC_CONTROL_REGISTER                   0x07        R/W
SYSTEM_STATUS_REGISTER                  0x08        R
FAULT_REGISTER                          0x09        R
BQ24195_VERSION_REGISTER                0x0A        R
----------------------------------------------------------
The I2C address of BQ24195 is 0x6B
*/

#include "BQ24195.h"

BQ24195::BQ24195(TWIClass* _twi) :
    twi(_twi)
{
}

BQ24195::~BQ24195()
{
	twi = NULL;
}

/*******************************************************************************
 * Function Name  : begin
 * Description    : Initializes the I2C for the BQ24195 module
 * Input          : NONE
 * Return         : 0 Error, 1 Success
 *******************************************************************************/
bool BQ24195::begin()
{
    twi->begin();
    return 1;
}

/*
//-----------------------------------------------------------------------------
// Input source control register
//-----------------------------------------------------------------------------
REG00
BIT
7 : 0:Enable Buck regulator 1:disable buck regulator (powered only from a LiPo)
--- input volatge limit. this is used to determine if USB source is overloaded
6 : VINDPM[3] 640mV | offset is 3.88V, Range is 3.88 to 5.08
5 : VINDPM[2] 320mV | enabling bits 3 to 6 adds the volatges to 3.88 base value
4 : VINDPM[1] 160mV | Default is 4.36 (0110)
3 : VINDPM[0] 80mV  |
--- input current limit
2 : INLIM[2]  000: 100mA, 001: 150mA, 010: 500mA,   | Default: 100mA when OTG pin is LOW and
1 : INLIM[1]  011: 900mA, 100: 1.2A,   101: 1.5A    | 500mA when OTG pin is HIGH
0 : INLIM[0]  110: 2.0A,  111: 3.0A                 | when charging port detected, 1.5A
//-----------------------------------------------------------------------------
*/

/*******************************************************************************
 * Function Name  : setInputVoltageLimit
 * Description    : set the minimum acceptable input voltage
 * Input          : 3880mV to 5080mV in the increments of 80mV
                    3880
                    3960
                    4040
                    4120
                    4200
                    4280
                    4360
                    4440
                    4520
                    4600
                    4680
                    4760
                    4840
                    4920
                    5000
                    5080
 * Return         : 0 Error, 1 Success
 *******************************************************************************/
// There is prolly a better way to do this. TODO: Optimize
bool BQ24195::setInputVoltageLimit(uint16_t voltage) {
	
    uint8_t DATA = readRegister(INPUT_SOURCE_REGISTER);
    uint8_t mask = DATA & 0b10000111;

    switch(voltage) {

        case 3880:
        writeRegister(INPUT_SOURCE_REGISTER, (mask | 0b00000000));
        break;

        case 3960:
        writeRegister(INPUT_SOURCE_REGISTER, (mask | 0b00001000));
        break;

        case 4040:
        writeRegister(INPUT_SOURCE_REGISTER, (mask | 0b00010000));
        break;

        case 4120:
        writeRegister(INPUT_SOURCE_REGISTER, (mask | 0b00011000));
        break;

        case 4200:
        writeRegister(INPUT_SOURCE_REGISTER, (mask | 0b00100000));
        break;

        case 4280:
        writeRegister(INPUT_SOURCE_REGISTER, (mask | 0b00101000));
        break;

        case 4360:
        writeRegister(INPUT_SOURCE_REGISTER, (mask | 0b00110000));
        break;

        case 4440:
        writeRegister(INPUT_SOURCE_REGISTER, (mask | 0b00111000));
        break;

        case 4520:
        writeRegister(INPUT_SOURCE_REGISTER, (mask | 0b01000000));
        break;

        case 4600:
        writeRegister(INPUT_SOURCE_REGISTER, (mask | 0b01001000));
        break;

        case 4680:
        writeRegister(INPUT_SOURCE_REGISTER, (mask | 0b01010000));
        break;

        case 4760:
        writeRegister(INPUT_SOURCE_REGISTER, (mask | 0b01011000));
        break;

        case 4840:
        writeRegister(INPUT_SOURCE_REGISTER, (mask | 0b01100000));
        break;

        case 4920:
        writeRegister(INPUT_SOURCE_REGISTER, (mask | 0b01101000));
        break;

        case 5000:
        writeRegister(INPUT_SOURCE_REGISTER, (mask | 0b01110000));
        break;

        case 5080:
        writeRegister(INPUT_SOURCE_REGISTER, (mask | 0b01111000));
        break;

        default:
        return 0; // return error since the value passed didn't match
    }

    return 1; // value was written successfully
}

/*******************************************************************************
 * Function Name  :
 * Description    :
 * Input          :
 * Return         :
 *******************************************************************************/
uint8_t BQ24195::getInputVoltageLimit(void) {

    //TODO
    return 1;

}

/*******************************************************************************
 * Function Name  : setInputCurrentLimit
 * Description    : Sets the input current limit for the BQ24195
 * Input          : 100,150,500,900,1200,1500,2000,3000 (mAmp)
 * Return         : 0 Error, 1 Success
 *******************************************************************************/
bool BQ24195::setInputCurrentLimit(uint16_t current) {

    uint8_t DATA = readRegister(INPUT_SOURCE_REGISTER);
    uint8_t mask = DATA & 0b11111000;

    switch (current) {

        case 100:
        writeRegister(INPUT_SOURCE_REGISTER, (mask | 0b00000000));
        break;

        case 150:
        writeRegister(INPUT_SOURCE_REGISTER, (mask | 0b00000001));
        break;

        case 500:
        writeRegister(INPUT_SOURCE_REGISTER, (mask | 0b00000010));
        break;

        case 900:
        writeRegister(INPUT_SOURCE_REGISTER, (mask | 0b00000011));
        break;

        case 1200:
        writeRegister(INPUT_SOURCE_REGISTER, (mask | 0b00000100));
        break;

        case 1500:
        writeRegister(INPUT_SOURCE_REGISTER, (mask | 0b00000101));
        break;

        case 2000:
        writeRegister(INPUT_SOURCE_REGISTER, (mask | 0b00000110));
        break;

        case 3000:
        writeRegister(INPUT_SOURCE_REGISTER, (mask | 0b00000111));
        break;

        default:
        return 0; // return error since the value passed didn't match
    }

    return 1; // value was written successfully
}

/*******************************************************************************
 * Function Name  :
 * Description    :
 * Input          :
 * Return         :
 *******************************************************************************/
uint16_t BQ24195::getInputCurrentLimit(void) {
    static const uint16_t mapping[] = {
        100,
        150,
        500,
        900,
        1200,
        1500,
        2000,
        3000
    };
    uint8_t raw = readInputSourceRegister();
    raw &= 0x03;
    return mapping[raw];
}

/*******************************************************************************
 * Function Name  : readInputSourceRegister
 * Description    :
 * Input          : NONE
 * Return         :
 *******************************************************************************/
uint8_t BQ24195::readInputSourceRegister(void) {

    return readRegister(INPUT_SOURCE_REGISTER);
}

/*******************************************************************************
 * Function Name  : enableBuck
 * Description    :
 * Input          : NONE
 * Return         :
 *******************************************************************************/
bool BQ24195::enableBuck(void) {
    uint8_t DATA = readRegister(INPUT_SOURCE_REGISTER);
    writeRegister(INPUT_SOURCE_REGISTER, (DATA & 0b01111111));
    return 1;
}

/*******************************************************************************
 * Function Name  : disableBuck
 * Description    :
 * Input          : NONE
 * Return         :
 *******************************************************************************/
bool BQ24195::disableBuck(void) {
    uint8_t DATA = readRegister(INPUT_SOURCE_REGISTER);
    writeRegister(INPUT_SOURCE_REGISTER, (DATA | 0b10000000));
    return 1;
}


/*
//-----------------------------------------------------------------------------
// Power ON configuration register
//-----------------------------------------------------------------------------
REG01
BIT
7: 0: keep current settings 1:reset register to default
6: 0: normal 1: reset I2C watchdog timer
--- charger config
5: CHG_CONFIG[1]    | 00: Disable charging, 01: Charge battery(default)
4: CHG_CONFIG[0]    | 10/11: OTG
--- minimum system voltage limit. this is the minimum output feeding the gsm module
3: SYS_MIN[2] 0.4V  | offset is 3.0V, Range 3.0V to 3.7V
2: SYS_MIN[1] 0.2V  | enabling bits 1 to 3 adds the volatges to 3.0 base value
1: SYS_MIN[0] 0.1V  | default is 3.5V (101)
0: Reserved
*/


/*******************************************************************************
 * Function Name  : readPowerONRegister
 * Description    :
 * Input          :
 * Return         :
 *******************************************************************************/
uint8_t BQ24195::readPowerONRegister(void) {

    return readRegister(POWERON_CONFIG_REGISTER);

}

/*******************************************************************************
 * Function Name  : enableCharging
 * Description    :
 * Input          :
 * Return         :
 *******************************************************************************/
bool BQ24195::enableCharging() {
    uint8_t DATA = readRegister(POWERON_CONFIG_REGISTER);
    DATA = DATA & 0b11001111;
    DATA = DATA | 0b00010000;
    writeRegister(POWERON_CONFIG_REGISTER, DATA);
    return 1;
}

/*******************************************************************************
 * Function Name  : disableCharging
 * Description    :
 * Input          :
 * Return         :
*******************************************************************************/
bool BQ24195::disableCharging() {
    uint8_t DATA = readRegister(POWERON_CONFIG_REGISTER);
    writeRegister(POWERON_CONFIG_REGISTER, (DATA & 0b11001111));
    return 1;
}

/*******************************************************************************
 * Function Name  : disableOTG
 * Description    :
 * Input          :
 * Return         :
*******************************************************************************/
bool BQ24195::disableOTG(void) {
    uint8_t DATA = readRegister(POWERON_CONFIG_REGISTER);
    DATA = DATA & 0b11001111;
    DATA = DATA | 0b00010000;
    writeRegister(POWERON_CONFIG_REGISTER, DATA);
    return 1;
}

/*******************************************************************************
 * Function Name  : enableOTG
 * Description    :
 * Input          :
 * Return         :
*******************************************************************************/
bool BQ24195::enableOTG(void) {
    uint8_t DATA = readRegister(POWERON_CONFIG_REGISTER);
    DATA = DATA & 0b11001111;
    DATA = DATA | 0b00100000;
    writeRegister(POWERON_CONFIG_REGISTER, DATA);
    return 1;
}

/*******************************************************************************
 * Function Name  : resetWatchdog
 * Description    :
 * Input          :
 * Return         :
*******************************************************************************/
bool BQ24195::resetWatchdog() {
    uint8_t DATA = readRegister(POWERON_CONFIG_REGISTER);
    writeRegister(POWERON_CONFIG_REGISTER, (DATA | 0b01000000));
    return 1;
}

/*******************************************************************************
 * Function Name  : setMinimumSystemVoltage
 * Description    : Set the minimum acceptable voltage to feed the GSM module
 * Input          : 3000,3100,3200,3300,3400,3500,3600,3700 (mV)
 * Return         : 0 Error, 1 Success
*******************************************************************************/
bool BQ24195::setMinimumSystemVoltage(uint16_t voltage) {
	
    uint8_t DATA = readRegister(POWERON_CONFIG_REGISTER);
    uint8_t mask = DATA & 0b11110000;

    switch (voltage) {

        case 3000:
        writeRegister(POWERON_CONFIG_REGISTER, (mask | 0b00000001));
        break;

        case 3100:
        writeRegister(POWERON_CONFIG_REGISTER, (mask | 0b00000011));
        break;

        case 3200:
        writeRegister(POWERON_CONFIG_REGISTER, (mask | 0b00000101));
        break;

        case 3300:
        writeRegister(POWERON_CONFIG_REGISTER, (mask | 0b00000111));
        break;

        case 3400:
        writeRegister(POWERON_CONFIG_REGISTER, (mask | 0b00001001));
        break;

        case 3500:
        writeRegister(POWERON_CONFIG_REGISTER, (mask | 0b00001011));
        break;

        case 3600:
        writeRegister(POWERON_CONFIG_REGISTER, (mask | 0b00001101));
        break;

        case 3700:
        writeRegister(POWERON_CONFIG_REGISTER, (mask | 0b00001111));
        break;

        default:
        return 0; // return error since the value passed didn't match
    }

    return 1; // value was written successfully


}

/*******************************************************************************
 * Function Name  : getMinimumSystemVoltage
 * Description    : Returns the set minimum system voltage
 * Input          : NONE
 * Return         : The set system voltage in millivolts or 0 if ERROR
*******************************************************************************/
uint16_t BQ24195::getMinimumSystemVoltage() {

    uint8_t DATA = readRegister(POWERON_CONFIG_REGISTER);
    uint8_t sysvoltage = DATA & 0b00001110;

    switch (sysvoltage) {

        case 0:
        return 3000;

        case 2:
        return 3100;

        case 4:
        return 3200;

        case 6:
        return 3300;

        case 8:
        return 3400;

        case 10:
        return 3500;

        case 12:
        return 3600;

        case 14:
        return 3700;

        default:
        return 0; // return error since the value didn't match
    }

}

/*
//-----------------------------------------------------------------------------
// Charge current control register
//-----------------------------------------------------------------------------
REG02
BIT
7: ICHG[5] 2048mA   | offset is 512mA
6: ICHG[4] 1024mA   | Range: 512 to 4544mA (BQ24195)
5: ICHG[3] 512mA    | Range: 512 to 2496mA (BQ24195L)
4: ICHG[2] 256mA    | Default: 2048mA (011000) = 512mA+1024mA+512mA
3: ICHG[1] 128mA    | enabling bits 2 to 7 adds the current to 512mA base value
2: ICHG[0] 64mA     |
1: Reserved (should always be 0)
0: FORCE_20PCT (fill this description)
*/

/*******************************************************************************
 * Function Name  : getChargeCurrent
 * Description    : It currently just returns the contents of the register
 * Input          :
 * Return         :
 *******************************************************************************/
//TO DO: Return more meaningful value
uint8_t BQ24195::getChargeCurrent(void) {

    return readRegister(CHARGE_CURRENT_CONTROL_REGISTER);
}

/*******************************************************************************
 * Function Name  : setChargeCurrent
 * Description    : The total charge current is the 512mA + the combination of the
                    current that the following bits represent
                    bit7 = 2048mA
                    bit6 = 1024mA
                    bit5 = 512mA
                    bit4 = 256mA
                    bit3 = 128mA
                    bit2 = 64mA
 * Input          : six boolean values
                    For example,
                    setChargeCurrent(0,0,1,1,1,0) will set the charge current to
                    512mA + [0+0+512mA+256mA+128mA+0] = 1408mA
 * Return         : 0 Error, 1 Success
 *******************************************************************************/
bool BQ24195::setChargeCurrent(bool bit7, bool bit6, bool bit5, bool bit4, bool bit3, bool bit2) {
    uint8_t current = 0;
    if (bit7) current = current | 0b10000000;
    if (bit6) current = current | 0b01000000;
    if (bit5) current = current | 0b00100000;
    if (bit4) current = current | 0b00010000;
    if (bit3) current = current | 0b00001000;
    if (bit2) current = current | 0b00000100;

    uint8_t DATA = readRegister(CHARGE_CURRENT_CONTROL_REGISTER);
    uint8_t mask = DATA & 0b00000001;
    writeRegister(CHARGE_CURRENT_CONTROL_REGISTER, current | mask);
    return 1;
}

/*
//-----------------------------------------------------------------------------
// Charge voltage control register
//-----------------------------------------------------------------------------
REG04
BIT
7: VREG[5] 512mV    | Charge Voltage Limit
6: VREG[4] 256mV    | offset is 3.504V
5: VREG[3] 128mV    | Range: 3.504 V to 4.400 V (111000)
4: VREG[2] 64mV     | Default: 4.208 V (101100) = 3.504V+512mV+128mV+64mV
3: VREG[1] 32mV     | enabling bits 2 to 7 adds the voltage to 3.504V base value
2: VREG[0] 16mV     |
1: BATLOWV          | Battery Precharge to Fast Charge Threshold
                    | 0 – 2.8 V, 1 – 3.0 V (default)
0: VRECHG           | Battery Recharge Threshold (below battery regulation voltage)
                    | 0 – 100 mV (default), 1 – 300 mV
*/

/*******************************************************************************
 * Function Name  : getChargeVoltage
 * Description    : It currently just returns the contents of the register
 * Input          :
 * Return         :
 *******************************************************************************/

uint8_t BQ24195::getChargeVoltage(void) {

    return readRegister(CHARGE_VOLTAGE_CONTROL_REGISTER);
}

uint16_t BQ24195::getChargeVoltageValue() {
    uint8_t raw = getChargeVoltage();
    unsigned baseVoltage = 16;
    unsigned v = 3504;
    for (unsigned i = 0; i < 6; i++) {
        uint8_t b = (raw >> (i + 2)) & 0x01;
        v += ((unsigned)b) * baseVoltage;
        baseVoltage *= 2;
    }
    return v;
}

/*******************************************************************************
 * Function Name  : setChargeVoltage
 * Description    : The total charge voltage is the 3.504V + the combination of the
                    voltage that the following bits represent
                    bit7 = 512mV
                    bit6 = 256mV
                    bit5 = 128mV
                    bit4 = 64mV
                    bit3 = 32mV
                    bit2 = 16mV
 * Input          : desired voltage (4208 or 4112 are the only options currently)
                    4208 is the default
                    4112 is a safer termination voltage if exposing the
                    battery to temperatures above 45°C
 * Return         : 0 Error, 1 Success
 *******************************************************************************/
bool BQ24195::setChargeVoltage(uint16_t voltage) {
    uint8_t DATA = readRegister(CHARGE_VOLTAGE_CONTROL_REGISTER);
    uint8_t mask = DATA & 0b000000011;

    switch (voltage) {

        case 4112:
        writeRegister(CHARGE_VOLTAGE_CONTROL_REGISTER, (mask | 0b10011000));
        break;

        case 4208:
        writeRegister(CHARGE_VOLTAGE_CONTROL_REGISTER, (mask | 0b10110000));
        break;

        default:
        return 0; // return error since the value passed didn't match
    }

    return 1; // value was written successfully
}

/*
//-----------------------------------------------------------------------------
//Charge Termination/Timer Control Register
//-----------------------------------------------------------------------------
REG05
BIT
--- Charging Termination Enable
7: EN_TERM      0:Disable
                1:Enable
                Default: Enable Termination (1)
--- Termination Indicator Threshold
6: TERM_STAT    0:Match ITERM,
                1:STAT pin high before actual termination when charge current below 800 mA
                Default Match ITERM (0)
--- I2C Watchdog Timer Setting
5: WATCHDOG[1]  | 00: disable timer, 01: 40seconds
4: WATCHDOG[0]  | 10: 80 seconds, 11: 160 seconds. Default: 40s(01)
--- Charging Safety Timer Enable
3: EN_TIMER     0:Disable
                1:Enable
                Default:Enable(1)
--- Fast Charge Timer Setting
2: CHG_TIMER[1] | 00: 5hrs, 01: 8hrs, 10: 12hrs, 11: 20hrs
1: CHG_TIMER[0] | Default: 8hrs(01)
0: Reserved
*/


/*******************************************************************************
 * Function Name  :
 * Description    :
 * Input          :
 * Return         :
 *******************************************************************************/
uint8_t BQ24195::readChargeTermRegister(void) {

    return readRegister(CHARGE_TIMER_CONTROL_REGISTER);

}

/*******************************************************************************
 * Function Name  :
 * Description    :
 * Input          :
 * Return         :
 *******************************************************************************/
bool BQ24195::disableWatchdog(void) {
    uint8_t DATA = readRegister(CHARGE_TIMER_CONTROL_REGISTER);
    writeRegister(CHARGE_TIMER_CONTROL_REGISTER, (DATA & 0b11001110));
    return 1;
}

bool BQ24195::setWatchdog(uint8_t time) {
    uint8_t DATA = readRegister(CHARGE_TIMER_CONTROL_REGISTER);
    time &= 0b11;
    writeRegister(CHARGE_TIMER_CONTROL_REGISTER, (DATA & 0b11001110) | (time << 4));
    return 1;
}

/*
//-----------------------------------------------------------------------------
//Misc Operation Control Register
//-----------------------------------------------------------------------------
REG07
BIT
--- Force DPDM detection
7: DPDM_EN  0: Not in D+/D– detection,
            1: Force D+/D– detection.
            Default: (0)
--- Safety Timer Setting during Input DPM and Thermal Regulation
6: TMR2X_EN 0: Safety timer not slowed by 2X during input DPM or thermal regulation
            1: Safety timer slowed by 2X during input DPM or thermal regulation
            Default: (1)
--- Force BATFET Off (this essentially disconnects the battery from the system)
5: BATFET_Disable   0: Allow Q4 turn on
                    1: Turn off Q4
                    Default: (0)
4: 0 – Reserved. Must write "0"
3: 1 – Reserved. Must write "1"
2: 0 – Reserved. Must write "0"
1: INT_MASK[1]      0: No INT during CHRG_FAULT
                    1: INT onCHRG_FAULT
                    Default(1)
0: INT_MASK[0]      0: No INT during BAT_FAULT
                    1: INT on BAT_FAULT
                    Default(1)
*/

/*******************************************************************************
 * Function Name  : disableDPDM
 * Description    :
 * Input          :
 * Return         :
 *******************************************************************************/
bool BQ24195::disableDPDM() {
    uint8_t DATA = readRegister(MISC_CONTROL_REGISTER);
    writeRegister(MISC_CONTROL_REGISTER, (DATA & 0b01111111));
    return 1;
}

/*******************************************************************************
 * Function Name  : enableDPDM
 * Description    :
 * Input          :
 * Return         :
*******************************************************************************/
bool BQ24195::enableDPDM() {
    uint8_t DATA = readRegister(MISC_CONTROL_REGISTER);
    writeRegister(MISC_CONTROL_REGISTER, (DATA | 0b10000000));
    return 1;
}

/*******************************************************************************
 * Function Name  : enableBATFET
 * Description    :
 * Input          :
 * Return         :
*******************************************************************************/
bool BQ24195::enableBATFET(void) {
    uint8_t DATA = readRegister(MISC_CONTROL_REGISTER);
    writeRegister(MISC_CONTROL_REGISTER, (DATA & 0b11011111));
    return 1;

}

/*******************************************************************************
 * Function Name  : disableBATFET
 * Description    : Force BATFET Off
                    (this essentially disconnects the battery from the system)
 * Input          :
 * Return         :
*******************************************************************************/
bool BQ24195::disableBATFET(void) {
    uint8_t DATA = readRegister(MISC_CONTROL_REGISTER);
    writeRegister(MISC_CONTROL_REGISTER, (DATA | 0b00100000));
    return 1;
}

/*******************************************************************************
 * Function Name  :
 * Description    :
 * Input          :
 * Return         :
*******************************************************************************/
uint8_t BQ24195::readOpControlRegister(void) {

    return readRegister(MISC_CONTROL_REGISTER);

}

uint16_t BQ24195::getRechargeThreshold() {
    return ((readRegister(CHARGE_VOLTAGE_CONTROL_REGISTER) & 0x01) == 0 ? 100 : 300);
}

bool BQ24195::setRechargeThreshold(uint16_t voltage) {
    switch (voltage) {
        case 300:
            writeRegister(CHARGE_VOLTAGE_CONTROL_REGISTER, readRegister(CHARGE_VOLTAGE_CONTROL_REGISTER) | 0x01);
            break;
        case 100:
        default:
            writeRegister(CHARGE_VOLTAGE_CONTROL_REGISTER, readRegister(CHARGE_VOLTAGE_CONTROL_REGISTER) & 0xfe);
            break;
    }

    return true;
}

/*
//-----------------------------------------------------------------------------
//System Status Register
//-----------------------------------------------------------------------------
//NOTE: This is a read-only register
REG08
BIT
--- VBUS status
7: VBUS_STAT[1] | 00: Unknown (no input, or DPDM detection incomplete), 01: USB host
6: VBUS_STAT[0] | 10: Adapter port, 11: OTG
--- Charging status
5: CHRG_STAT[1] | 00: Not Charging,  01: Pre-charge (<VBATLOWV)
4: CHRG_STAT[0] | 10: Fast Charging, 11: Charge termination done
3: DPM_STAT     0: Not DPM
                1: VINDPM or IINDPM
2: PG_STAT      0: Power NO Good :(
                1: Power Good :)
1: THERM_STAT   0: Normal
                1: In Thermal Regulation (HOT)
0: VSYS_STAT    0: Not in VSYSMIN regulation (BAT > VSYSMIN)
                1: In VSYSMIN regulation (BAT < VSYSMIN)
*/

/*******************************************************************************
 * Function Name  :
 * Description    :
 * Input          :
 * Return         :
 *******************************************************************************/
bool BQ24195::isPowerGood(void) {

    uint8_t DATA = 0;
    DATA = readRegister(SYSTEM_STATUS_REGISTER);
    if(DATA & 0b00000100) return 1;
    else return 0;
}

/*******************************************************************************
 * Function Name  :
 * Description    :
 * Input          :
 * Return         :
 *******************************************************************************/
bool BQ24195::isHot(void) {

    uint8_t DATA = 0;
    DATA = readRegister(SYSTEM_STATUS_REGISTER);
    if(DATA & 0b00000010) return 1;
    else return 0;
}

/*******************************************************************************
 * Function Name  :
 * Description    :
 * Input          :
 * Return         :
 *******************************************************************************/
uint8_t BQ24195::getSystemStatus() {

    uint8_t DATA = 0;
    DATA = readRegister(SYSTEM_STATUS_REGISTER);
    return DATA;
}

/*
//-----------------------------------------------------------------------------
//Fault Register
//-----------------------------------------------------------------------------
//NOTE: This is a read-only register
REG09
BIT
7: WATCHDOG_FAULT   0: Normal
                    1: watchdog timer expired
6: Reserved
--- Charge fault status
5: CHRG_FAULT[1]    | 00: Normal, 01: Input fault (VBUS OVP or VBAT < VBUS < 3.8 V)
4: CHRG_FAULT[0]    | 10: Thermal shutdown, 11: charge safetly timer expiration
--- Battery fault status
3: BAT_FAULT        0: Normal
                    1: BATOVP battery over threshold
--- NTC thermistor fault status
2: NTC_FAULT[2]     | 000: Normal
1: NTC_FAULT[1]     | 101: Cold
0: NTC_FAULT[0]     | 110: Hot
*/

/*******************************************************************************
 * Function Name  :
 * Description    :
 * Input          :
 * Return         :
 *******************************************************************************/
uint8_t BQ24195::getFault() {

    uint8_t DATA = 0;
    DATA = readRegister(FAULT_REGISTER);
    return DATA;

}

/*
//-----------------------------------------------------------------------------
//Vender / Part / Revision Status Register
//-----------------------------------------------------------------------------
//NOTE: This is a read-only register
REG0A  (reset = 00100011, or 0x23)
BIT
7: Reserved
6: Reserved
--- Device configuration
5: PN[2]        1
4: PN[1]        0
3: PN[0]        0
2: TS_PROFILE   0
1: DEV_REG[0]   1
0: DEV_REG[0]   1
*/

/*******************************************************************************
 * Function Name  : getVersion
 * Description    : Return the version number of the chip
                    Value at reset: 00100011, 0x23
 * Input          : NONE
 * Return         : version number
 *******************************************************************************/
// Return the version number of the chip
// Value at reset: 00100011, 0x23
uint8_t BQ24195::getVersion() {
    uint8_t DATA = 0;
    DATA = readRegister(BQ24195_VERSION_REGISTER);
    return DATA;
}



/*******************************************************************************
 * Function Name  :
 * Description    :
 * Input          :
 * Return         :
 *******************************************************************************/
uint8_t BQ24195::readRegister(uint8_t startAddress) {
    uint8_t DATA = 0;
    twi->beginTransmission(BQ24195_ADDRESS);
    twi->write(startAddress);
    twi->endTransmission(true);
    twi->requestFrom(BQ24195_ADDRESS, 1);
    DATA = twi->read();
    return DATA;
}


/*******************************************************************************
 * Function Name  :
 * Description    :
 * Input          :
 * Return         :
 *******************************************************************************/
void BQ24195::writeRegister(uint8_t address, uint8_t DATA) {
    twi->beginTransmission(BQ24195_ADDRESS);
    twi->write(address);
    twi->write(DATA);
    twi->endTransmission(true);
}
