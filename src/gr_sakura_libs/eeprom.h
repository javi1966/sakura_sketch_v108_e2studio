/*******************************************************************************
* GR-SAKURA LIBRARY LICENSE.  LIMITATION and DISCLAIMER of WARRANTY
*
* This software is supplied by Tokushu Denshi Kairo Inc. and is only intended 
* for use with Gadget Renesas projects. No other uses are authorized.
* This software is owned by Tokuden and is protected under all applicable laws,
* including copyright laws. Disclosure or redistribution to others this headder
* file and related library file alone is not allowed.
* You can redistribute the executable object file (only SREC or BIN file) which
* is generated as a result of compilation and link your program.
* Of cource the limitation of this library license does not effect to your code.
* THIS SOFTWARE IS PROVIDED "AS IS" AND TOKUDEN MAKES NO WARRANTIES REGARDING
* THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT
* LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE
* AND NON-INFRINGEMENT. ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED.
* Tokuden reserves the right, without notice, to make changes to this software
* and to discontinue the availability of this software. By using this software,
* you agree to the additional terms and conditions found by accessing the
* http://rx.tokudenkairo.co.jp/
* (C) Copyright 2011-2012 Tokushu Denshi Kairo Inc.
*******************************************************************************/

#ifndef	__H_RXDUINO_EEPROM
#define	__H_RXDUINO_EEPROM
/**************************************************************************//**
 * @file     eeprom.h
 * @brief    Arduino互換のEEPROMライブラリを定義するヘッダファイル。<BR>
             詳細は EEPROM クラスの説明を参照。
 * @details  RXマイコンに内蔵されたE2データフラッシュをEEPROMのように扱うためのライブラリ。<BR>
 *           ライブラリを使用するには、リンカオプションで -leeprom を指定する。
 ******************************************************************************/
#include "rxduino.h"

#ifdef __cplusplus
	extern "C" {
#endif

/*********************************************************************//**
 *  @class   EEPROM
 *  @brief   内蔵E2データフラッシュでEEPROMをエミュレートするクラス
 *  @note    実体は tkdn_dflash.h をC++でカプセル化するものである。
 *  @note    V1.08から、このクラスを使うためにEEPROM EEPROMの宣言をしなくてもよくなった
 *  @todo    現在はRX63N専用。RX62Nでも使えるようにしたい。
 **********************************************************************/
class EEPROM
{
public:
/*********************************************************************//**
 * @brief    EEPROMの内容を1バイト読み出す
 * @param    addr 範囲は0～0x7fff
 * @note     EEPROMは内蔵E2データフラッシュでエミュレートしている
 * @return   読み出したデータ
 **********************************************************************/
	unsigned char read(unsigned long addr);

/*********************************************************************//**
 * @brief    EEPROMに1バイト書き込む
 * @param    addr 範囲は0～0x7fff
 * @param    data 書き込むデータ
 * @note     EEPROMは内蔵E2データフラッシュでエミュレートしている。<BR>
 *           書き換え可能回数は推定50000回。<BR>
 *           内部で消去を行うので、明示的な消去関数はない。
 * @return   失敗すると-1を返す。成功すると1を返す
 **********************************************************************/
	int write(unsigned long addr,unsigned char data);
};

extern EEPROM EEPROM;

#ifdef __cplusplus
	}
#endif

#endif // __H_RXDUINO_EEPROM

