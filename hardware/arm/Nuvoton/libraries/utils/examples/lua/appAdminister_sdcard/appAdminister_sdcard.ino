/* addAdminister.ino stm32 vdisk/mcu administer
    ---------------------------------------------------------------------------------------
   1 selected: one of  in HAL_Conf.h file option: USE_SDIOSDCARD/USE_SPISDCARD/USE_SPIFLASH
   2 from the menu option selected:  Startup adr: flash(WhitRamboo xxkRAM used only) to build the project.
   ---------------------------------------------------------------------------------------
   cmd usage:
   type help or h or ? for Display list of commands.
   ---------------------------------------------------------------------------------------
   tested for F103xE/F407xE  by huaweiwx@sina.com 2017.10
   ---------------------------------------------------------------------------------------
*/

#if  USE_SPISDCARD > 0
# include <SD.h>
#elif  USE_SDIOSDCARD > 0
# include <STM32SD.h>
#elif  SPIFLASHDISK_SIZE
# include <SpiFlashDisk.h>
#endif

#include <cmdline.h>
char cmdline[256];
int ptr;

#include <lua.h>
#include <utils.h>
#include <LED.h>

void setup() {
  Serial.begin(115200);
  Led.Init();

  //for  use SerialUSB if selected from menu
#if (MENU_USB_SERIAL || MENU_USB_IAD)
  while (!Serial.available()) {
    Led.flash(10, 990, 1);
  }
#endif

  delay(1000);
  Serial.println(F("\n****************************************"));
  Serial.println(F("*        STM32 vdos demo v18.0         *"));
  Serial.println(F("*  Type help Display list of commands  *"));
  Serial.println(F("****************************************\n"));
#if  USE_SPISDCARD > 0
  Serial <<  "use spi sdcard disk\n\n";
#elif  USE_SDIOSDCARD > 0
  Serial <<  "use sdio sdcard disk\n\n";
#else
  Serial <<  "unused sdcard or serial flash as disk\n\n";
#endif

  Serial.print(F(">"));
  ptr = 0;
}

boolean stringComplete = false;  // whether the string is complete
void loop() {
  int nStatus;
  if (stringComplete) {
    if (cmdline[0] > ' ') {
      nStatus = CmdLineProcess(cmdline);
      if (nStatus == CMDLINE_BAD_CMD)
      {
        Serial.println(F("Bad cmd!"));
      }
      else if (nStatus == CMDLINE_TOO_MANY_ARGS)
      {
        Serial.println(F("Too many args!"));
      }
      else if (nStatus != 0)
      {
        Serial.print(F("Cmd rtn err_code"));
        Serial.println(nStatus);
      }
    }
    ptr = 0;
    stringComplete = false;
    Serial.print(F("\r\n>"));
  }
#if defined(STM32GENERIC)
  serialEvent();
#endif
  Led.flash(10, 90, 1);
}

void serialEvent() {
  while (Serial.available()) {
    char inChar = (char)Serial.read();
    cmdline[ptr++] = inChar;
    cmdline[ptr] = '\0';
    if ((inChar == '\n') || (inChar == '\r')) {
      stringComplete = true;
    }
  }
}

//*****************************************************************************
// This function implements the "help" command.  It prints a simple list of the
// available commands with a brief description.
//*****************************************************************************
void print_port(char* str, uint16_t val) {
  Serial <<  str << " : ";
  for (uint8_t i = 15; i > 0; i--) {
    if (val & (1 << i)) break;
    Serial << "0";
  }
  Serial << _BIN(val) << "(0x" << _HEX(val) << ")\n";
}

int Cmd_help(int argc, char *argv[])
{
  if (argc == 2) { //  ?[ pin/P/A/B/C/D]
    char* pstr = argv[1];
    if (isdigit(pstr[0])) {
      uint8_t pin = atoi(argv[1]);
      Serial << stm32PinName(pin) << "(" << argv[1] << "): " << digitalRead(pin) << "\n";
      return 0;
    }
    if (pstr[0] == 'P') {
      uint8_t pin = UTIL_Str2PortPin(argv[1]);
      if (pin == 0xff) {
        Serial << "err: pinName" << argv[1] << "\n";
        return 0;
      } else {
        Serial << argv[1] << "(" << pin << ") : " << digitalRead(pin) << "\n";
        return 0;
      }
    }
    if (pstr[0] == 'A') {
      print_port((char*)"GPIOA->IDR  ", GPIOA->IDR);
#if defined(STM32F1)
      print_port((char*)"      ->CRH  ", GPIOA->CRH & 0xffff);
      print_port((char*)"      ->CRL  ", GPIOA->CRL & 0xffff);
#else
      print_port((char*)"      ->MODER", GPIOA->MODER);
#endif
      return 0;
    }
    if (pstr[0] == 'B') {
      print_port((char*)"GPIOB->IDR  ", GPIOB->IDR);
#if defined(STM32F1)
      print_port((char*)"      ->CRH  ", GPIOB->CRH & 0xffff);
      print_port((char*)"      ->CRL  ", GPIOB->CRL & 0xffff);
#else
      print_port((char*)"      ->MODER", GPIOB->MODER);
#endif
      return 0;
    }
    if (pstr[0] == 'C') {
      print_port((char*)"GPIOC->IDR  ", GPIOC->IDR);
#if defined(STM32F1)
      print_port((char*)"      ->CRH  ", GPIOC->CRH & 0xffff);
      print_port((char*)"      ->CRL  ", GPIOC->CRL & 0xffff);
#else
      print_port((char*)"      ->MODER", GPIOC->MODER);
#endif
      return 0;
    }
#ifdef GPIOD
    if (pstr[0] == 'D') {
      print_port((char*)"GPIOD->IDR  ", GPIOD->IDR);
#if defined(STM32F1)
      print_port((char*)"      ->CRH  ", GPIOD->CRH & 0xffff);
      print_port((char*)"      ->CRL  ", GPIOD->CRL & 0xffff);
#else
      print_port((char*)"      ->MODER", GPIOD->MODER);
#endif
      return 0;
    }
#endif
#ifdef GPIOE
    if (pstr[0] == 'E') {
      print_port((char*)"GPIOE->IDR  ", GPIOE->IDR);
#if defined(STM32F1)
      print_port((char*)"      ->CRH  ", GPIOE->CRH & 0xffff);
      print_port((char*)"      ->CRL  ", GPIOE->CRL & 0xffff);
#else
      print_port((char*)"      ->MODER", GPIOE->MODER);
#endif
      return 0;
    }
#endif
#ifdef GPIOF
    if (pstr[0] == 'F') {
      print_port((char*)"GPIOF->IDR  ", GPIOF->IDR);
#if defined(STM32F1)
      print_port((char*)"      ->CRH  ", GPIOF->CRH & 0xffff);
      print_port((char*)"      ->CRL  ", GPIOF->CRL & 0xffff);
#else
      print_port((char*)"      ->MODER", GPIOF->MODER);
#endif
      return 0;
    }
#endif
#ifdef GPIOG
    if (pstr[0] == 'G') {
      print_port((char*)"GPIOG->IDR  ", GPIOG->IDR);
#if defined(STM32F1)
      print_port((char*)"      ->CRH  ", GPIOG->CRH & 0xffff);
      print_port((char*)"      ->CRL  ", GPIOG->CRL & 0xffff);
#else
      print_port((char*)"      ->MODER", GPIOG->MODER);
#endif
      return 0;
    }
#endif
#ifdef GPIOH
    if (pstr[0] == 'H') {
      print_port((char*)"GPIOH->IDR  ", GPIOH->IDR);
#if defined(STM32F1)
      print_port((char*)"      ->CRH  ", GPIOH->CRH & 0xffff);
      print_port((char*)"      ->CRL  ", GPIOH->CRL & 0xffff);
#else
      print_port((char*)"      ->MODER", GPIOH->MODER);
#endif
      return 0;
    }
#endif
#ifdef GPIOH
    if (pstr[0] == 'H') {
      print_port((char*)"GPIOH->IDR  ", GPIOH->IDR);
#if defined(STM32F1)
      print_port((char*)"      ->CRH  ", GPIOH->CRH & 0xffff);
      print_port((char*)"      ->CRL  ", GPIOH->CRL & 0xffff);
#else
      print_port((char*)"      ->MODER", GPIOH->MODER);
#endif
      return 0;
    }
#endif
    Serial << argc << "  " <<  argv[1] << " ??\n";
  }

  tCmdLineEntry *pEntry;
  pEntry = &g_sCmdTable[0];
  Serial.println(F("\r\nAvailable commands:\r\n------------------\n"));
  while (pEntry->pcCmd)
  {
    Serial.print( pEntry->pcCmd);
    Serial.println(pEntry->pcHelp);
    pEntry++;
  }

  Serial << "\nPIN list:";
  for (uint8_t i = 0; i < sizeof(variant_pin_list) / sizeof(variant_pin_list[0]); i++)
    Serial << stm32PinName(i) << "("  << i  << "), ";

  uint8_t leds[] = {LEDS_LIST};
  Serial << "\nLED list:\n";
  for (uint8_t i = 0; i < sizeof(leds) / sizeof(leds[0]); i++)
    Serial << "LED" << i << "_BUILTIN(" <<  stm32PinName(leds[i]) << "), ";

#ifdef KEYS_LIST
  uint8_t keys[] = {KEYS_LIST};
  Serial << "\nKEYS list:";
  for (uint8_t i = 0; i < sizeof(keys) / sizeof(keys[0]); i++)
    Serial << "BUILTIN" << i << "(" << stm32PinName(keys[i]) << "), ";
#endif

#ifdef MOSI
  Serial << "\nSPI pins:";
  Serial << "MOSI(" <<  stm32PinName(MOSI);
  Serial << "), MISO(" <<  stm32PinName(MISO);
  Serial << "), SCK(" <<  stm32PinName(SCK);
  Serial << "), SS(" <<  stm32PinName(SS) << "),";
#endif

#ifdef SDA
  Serial << "\nI2C pins:";
  Serial << "SDA:" <<  stm32PinName(SDA);
  Serial << ",SCL:" <<  stm32PinName(SCL);
#endif

#ifdef DBGMCU
  Serial << "\nMCU_IDCODE:" << _HEX(HAL_GetDEVID());
#endif

#ifdef OB_BASE
  uint32_t UID[3];
#if defined(STM32F0)||defined(STM32F3)
  UID[0] = HAL_GetUIDw0();
  UID[1] = HAL_GetUIDw1();
  UID[2] = HAL_GetUIDw2();
#else
  HAL_GetUID(UID);
#endif
  Serial << "\nUSERID:" << _HEX(UID[0]) << " " << _HEX(UID[1]) << " " <<  _HEX(UID[2]);
#endif
  return (0);
}

int Cmd_dir(int argc, char *argv[])  //exp: dir/ls
{
  UNUSED(argc);  /*unused argc, move warnign*/
  UNUSED(argv);  /*unused argc, move warnign*/
  volatile uint32_t useradr;

#if USE_FILESYSTEM > 0
  Serial << "ls files:\n";
  vdos_listFiles();
#endif

  Serial << "\ncodes on slot:\n";
  for (int i = 0; i < (appCodeSegAddr[0] + 1); i++) {
    if (i > 0)
      useradr = FLASH_BASE + appCodeSegAddr[i] * 1024;
    else {
      useradr = USER_CODE_RAM;
    }
    Serial << i << "# addr:0x";
    if (useradr < 0x10000000) Serial << "0";
    Serial << _HEX(useradr);
    if (UTIL_checkUserCode(useradr))
      Serial << " is app.\n";
    else
      Serial << " is free.\n";
  }
  return (0);
}

void show_addr(uint32_t addr, uint8_t* data, uint8_t num = 16, uint8_t asc = 1);
void show_addr(uint32_t addr, uint8_t* data, uint8_t num, uint8_t asc) {
  Serial << ((addr < 0x10) ? "000" : ((addr < 0x100) ? "00" : ((addr < 0x1000) ? "0" : ""))) << _HEX(addr) << " :";
  for (uint8_t i = 0; i < num; i++) {
    if (data[i] < 0x10) Serial << "0";
    Serial << _HEX(data[i]) << " ";
  }
  if (asc) {
    Serial << "    ";
    for (uint8_t i = 0; i < num; i++)
      Serial.write((isprint (data[i])) ? data[i] : '.');
  }
}

int Cmd_dispmen (int argc, char *argv[]) {
  static uint32_t addr = 0;
  uint8_t data[16];
  if (argc == 2) {
    char *pstr = argv[1];
    addr = UTIL_getNum(pstr) & 0xfffffff0;
  }
  for (uint8_t i = 0; i < 16; i++) {
    volatile uint8_t *mem = (uint8_t*) (addr);
    for (uint8_t j = 0; j < 16; j++) {
      data[j] = mem[j];
    }
    show_addr(addr, data);
    Serial << "\n ";
    addr += 0x10;
  }
  return (0);
}

#if ( USE_FILESYSTEM > 0)
#if defined(STM32F4)||(FLASH_BANK1_END >  0x0801FFFFU)  //for hight density  xC/D/E
//exp: load mydemo.bin
int Cmd_load(int argc, char *argv[]) {
  volatile uint8_t* prog_ram =  (uint8_t *) USER_CODE_RAM;
  for (uint8_t i = 0; i < argc; i++)
  {
    Serial.print(argv[i]);
    Serial.print(F("  "));
  };
  Serial.println();

  File f = vdos_openfile(argv[1], FILE_READ);

  if (!f) {
    Serial << "file: " << argv[1] << "no found!\n";
    return 0;
  }

  uint32_t fsize = f.size();
  if ( fsize > MAX_PROG_RAM) {
    Serial << "file " << argv[1] << "too larger to fit in ram!\n";
    return 0;
  }

  uint16_t i = 0;
  uint8_t t = 1;
  char c;
  while (t) {
    if (f.available()) {
      c = f.read();
    } else {
      c =  0;
      t = 0;
    }
    prog_ram[i++] = (uint8_t) c;
  }
  f.close();

  if (UTIL_checkUserCode(USER_CODE_RAM))
  {
    Serial << "load ok! reset run it\n";
  } else {
    Serial << "file: " << argv[1] << "is unavailed!\n";
  }
  return 0;
}
#endif
#endif


//exp: typr test.txt

#if USE_FILESYSTEM > 0
int Cmd_type(int argc, char *argv[])
{
  if (!(argc == 2)) return 0;
  //  SD.cacheClear();
  File f = vdos_openfile(argv[1], FILE_READ);
  if (!f) {
    Serial << "file: " << argv[1] << "no found!\n";
    return 0;
  }
  char c;
  while (f.available()) {
    c = f.read();
    if (isprint(c) || (c == '\r') || (c == '\n')) Serial.write(c);
    else Serial.write('.');
  }
  f.close();
  return 0;
}
#endif

//exp:go 1/2/...
int Cmd_go(int argc, char *argv[])
{
  if (!(argc == 2)) return 0;
  volatile uint32_t useradr;
  Serial << "go " << argv[1] << "\n";
  int i = atoi(argv[1]);
  if (i < (appCodeSegAddr[0] + 1)) {
    if (i == 0) {
      useradr =  USER_CODE_RAM;
    } else {
      useradr = FLASH_BASE + appCodeSegAddr[i] * 1024;
    }

    if (UTIL_checkUserCode(useradr))
    {
      Serial << "check ok and goto " << _HEX(useradr) << ".....\n" << _endl;
#if (MENU_USB_SERIAL||MENU_USB_MASS_STORAGE||MENU_USB_IAD)
      USBDeviceFS.end();
#endif
      delay(1000); /*wait  serial complated */

      //    Serial1.end();  /*if open close it*/
      //    Serial2.end();  /*if open close it*/
      //    UTIL_jumpToUser(useradr);
      start_application(useradr);
    } else {
      Serial << "slot: " << argv[1] << " is unavailed!\n";
    }
  }
  return 0;
}

/*---------------------arduino func----------------------------*/
static uint8_t getpin(char* str) {
  uint8_t pin = 0xff;
  if (str[0] == 'P')    pin = UTIL_Str2PortPin(str);
  else if (UTIL_isHexStr(str)) pin = UTIL_hexNum(str);
  else if (isdigit(str[0]))  pin = atoi(str);
  return pin;
}


tCmdLineEntry g_sCmdTable[] =
{
  { "help",   Cmd_help,      " : Display list of commands & get mcu info..."} ,
  { "?",      Cmd_help,   "    : alias for help"} ,

  //debug
  { "d",      Cmd_dispmen,   "    : disp memory([addr])"} ,

  //vdisk function
  { "dir",    Cmd_dir,      "  : list vdisk files"} ,
  { "ls",     Cmd_dir,      "   : alias for dir"} ,

#if USE_FILESYSTEM > 0
  { "type",   Cmd_type,      " : type a txt file(filename)"} ,
#if defined(STM32F4)||(FLASH_BANK1_END >  0x0801FFFFU)  //for hight density  xC/D/E
  { "load",   Cmd_load,      " : chech bin file and load it if available"} ,
#endif
#endif

  //go flash addr
  { "go",     Cmd_go,      "   : goto n slot addr running(slot#)"},
  { "lua",    Cmd_lua,     "   : lua shell"},

  {  0, 0, 0 }
};
