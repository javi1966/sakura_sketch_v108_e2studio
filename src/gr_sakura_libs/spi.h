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

#ifndef	__H_RXDUINO_SPI
#define	__H_RXDUINO_SPI
/**************************************************************************//**
 * @file    spi.h
 * @brief   Arduino互換のSPIライブラリを定義するヘッダファイル。<BR>
            詳細は CSPI クラスの説明を参照。
 * @details このライブラリを使用するとSPIという名前のグローバルインスタンスが生成される。<BR>
 *          ライブラリを使用するには、リンカオプションで -lspi を指定する。
 ******************************************************************************/
#include "rxduino.h"

#ifdef __cplusplus
	extern "C" {
#endif

//------------------------------------------------------------------
// SPIポート
//------------------------------------------------------------------
//typedef enum {SPI_PORT_NONE, SPI_PORT_CS0_DUINO, SPI_PORT_CS1_MARY1, SPI_PORT_CS2_MARY2, SPI_PORT_CS3_ROM, SPI_PORT_SDMMC} SPI_PORT;
//typedef enum {LSBFIRST, MSBFIRST} SPI_BIT_ORDER;
//typedef enum {SPI_CLOCK_DIV2,  SPI_CLOCK_DIV4,  SPI_CLOCK_DIV8, SPI_CLOCK_DIV16,
//              SPI_CLOCK_DIV32, SPI_CLOCK_DIV64, SPI_CLOCK_DIV128 } SPI_CLK_DIVIDER;
//typedef enum {SPI_MODE0 , SPI_MODE1 , SPI_MODE2 , SPI_MODE3 } SPI_DATA_MODE;

#define LSBFIRST SPI_LSBFIRST //!< @brief enum型の定数 LSBを先に送出する
#define MSBFIRST SPI_MSBFIRST //!< @brief enum型の定数 MSBを先に送出する

/*********************************************************************//**
 *  @class   CSPI
 *  @brief   Arduino互換のSPIクラス RXマイコン内蔵のRSPIモジュールを使いやすくする
 *  @note    実体は tkdn_spi.h をC++でカプセル化するものである。
 *  @warning このクラスのインスタンスはライブラリをインポートすると自動的に生成され、グローバルインスタンスSPIが使用できるようになる。<BR>
 *           ユーザアプリケーションでコンストラクタを呼び出してインスタンスを生成したり、<BR>
 *           デフォルトで存在するインスタンスをデストラクトしてはならない。
 **********************************************************************/
class CSPI {
private:
	int bitOrder;
	SPI_CLK_DIVIDER divider;
	SPI_DATA_MODE dataMode;

public:
	CSPI(SPI_PORT port);
	~CSPI();

/*********************************************************************//**
 * @brief		ポート番号を変える場合はここを変える
 **********************************************************************/
	SPI_PORT port; 

/*********************************************************************//**
 * @brief    内蔵SPIモジュールを初期化し、使用できるようにする。
 * @note     使用されるピンはボードごとにあらかじめ決められている。
 * @note     SPIの各種関数はこの関数を呼び出した後で呼び出さないと効果を持たない。
 * @warning  SDMMC ライブラリと一緒に使うときには、SDMMC::begin() よりも先に呼び出さなければならない
 * @return   なし
 **********************************************************************/
	void begin(void) ;

/*********************************************************************//**
 * @brief    SPIをクローズし、割り当てられたピンを汎用I/Oポートに戻す
 * @return   なし
 **********************************************************************/
	void end(void) ;

/*********************************************************************//**
 * @brief    送受信するビット長の指定
 * @param    bitLength 1回の transfer() で送受信するデータのビット長。
 *           設定可能な値は8～16,20,24,32。これ以外の値を設定したときの動作は保証されない。
 * @note     この関数を呼び出す前はデフォルトで8bitになっている。
 * @return   なし
 **********************************************************************/
	void setBitLength(int bitLength);

/*********************************************************************//**
 * @brief    送受信するビットオーダーを指定する
 * @param    bitOrder 設定可能な値
 *            - MSBFIRST : MSB(ビット番号の大きい方)から先に送る
 *            - LSBFIRST : LSB(ビット番号の小さい方)から先に送る
 * @note     この関数を呼び出す前はデフォルトでMSBFIRSTになっている。
 * @return   なし
 **********************************************************************/
	void setBitOrder(int bitOrder) ;

/*********************************************************************//**
 * @brief    SPIクロックの速度(PCLKに対する分周比)の設定
 * @param    divider 次の値のいずれかを指定する
 *            - SPI_CLOCK_DIV2   : PCLK/2   (24MHz)
 *            - SPI_CLOCK_DIV4   : PCLK/4   (12MHz)
 *            - SPI_CLOCK_DIV8   : PCLK/8   (6MHz)
 *            - SPI_CLOCK_DIV16  : PCLK/16  (3MHz)
 *            - SPI_CLOCK_DIV32  : PCLK/32  (1.5MHz)
 *            - SPI_CLOCK_DIV64  : PCLK/64  (750kHz)
 *            - SPI_CLOCK_DIV128 : PCLK/128 (375kHz)
 *            これ以外の値を指定しないこと
 * @note      デフォルトの分周比は不明
 * @return   なし
 **********************************************************************/
	void setClockDivider(SPI_CLK_DIVIDER divider);

/*********************************************************************//**
 * @brief    SPIのデータモードを指定する
 * @param    mode データモード
 *            - SPI_MODE0 アイドル時のクロックがL、立ち上がりでサンプリング(基本)
 *            - SPI_MODE1 アイドル時のクロックがL、立ち下がりでサンプリング
 *            - SPI_MODE2 アイドル時のクロックがH、立ち上がりでサンプリング
 *            - SPI_MODE3 アイドル時のクロックがH、立ち下がりでサンプリング
 * @note     デフォルトのモードは0
 * @warning  モード2とモード3に設定したときには、SDMMCが使えなくなる
 * @return   なし
 **********************************************************************/
	void setDataMode(SPI_DATA_MODE mode);

/*********************************************************************//**
 * @brief    SPIのデータを送受信する
 * @param    txdata 8～32bitのデータ。リトルエンディアン。実際に送信される長さは setBitLength() で指定する。
 * @note     Arduinoでは8bitまでだったが、RXduinoでは32bitまで対応している
 * @return   受信したデータ
 **********************************************************************/
	unsigned long transfer(unsigned long txdata) ;
};

extern CSPI SPI;

#ifdef __cplusplus
	}
#endif

#endif // __H_RXDUINO_SPI

