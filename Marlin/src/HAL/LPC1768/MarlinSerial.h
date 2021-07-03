/**
 * Marlin 3D Printer Firmware
 * Copyright (c) 2020 MarlinFirmware [https://github.com/MarlinFirmware/Marlin]
 *
 * Based on Sprinter and grbl.
 * Copyright (c) 2011 Camiel Gubbels / Erik van der Zalm
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 */
#pragma once

#include <HardwareSerial.h>
#include <WString.h>

#include "../../inc/MarlinConfigPre.h"
#if ENABLED(EMERGENCY_PARSER)
  #include "../../feature/e_parser.h"
#endif
#include "../../core/serial_hook.h"

#ifndef SERIAL_PORT
  #define SERIAL_PORT 0
#endif
#ifndef RX_BUFFER_SIZE
  #define RX_BUFFER_SIZE 128
#endif
#ifndef TX_BUFFER_SIZE
  #define TX_BUFFER_SIZE 32
#endif

class MarlinSerial : public HardwareSerial<RX_BUFFER_SIZE, TX_BUFFER_SIZE> {
public:
  MarlinSerial(LPC_UART_TypeDef *UARTx) : HardwareSerial<RX_BUFFER_SIZE, TX_BUFFER_SIZE>(UARTx) { }

  void end() {}

  #if ENABLED(EMERGENCY_PARSER)
    bool recv_callback(const char c) override {
      emergency_parser.update(static_cast<Serial0Type<MarlinSerial> *>(this)->emergency_state, c);
      return true; // do not discard character
    }
  #endif
};
#define IDLE        0
#define WORKING     1
#define PAUSING     2
#define PAUSE      3
#define REPRINTING  4
#define REPRINTED   5
#define RESUMING    6
#define STOP        7
typedef Serial0Type<MarlinSerial> MSerialT;
extern MSerialT MSerial;
extern MSerialT MSerial1;
extern MSerialT MSerial2;
extern MSerialT MSerial3;
void change_button(int adress_high,int adress_low,int var);
void jump_to(int adress);
void get_serial1_commands(void);
void print_thr_count_page(int file_count,int page_flage);
void print_thr_adress_string(int high_adress,int low_adress,char *src);
void buf_clear(int high_adress,int low_adress,int num);
void printer_state_deal();
void pause_resume();
void change_en();
void change_zh_CN();
void change_zh_TW();
void change_ru();
void change_fr();
void change_es();
void change_de();
void change_jp();