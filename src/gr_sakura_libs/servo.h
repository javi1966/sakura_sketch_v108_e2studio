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

#ifndef	__H_RXDUINO_SERVO
#define	__H_RXDUINO_SERVO
/**************************************************************************//**
 * @file     servo.h
 * @brief    サーボモータライブラリを使用するためのヘッダファイル<BR>
             詳細は Servo クラスの説明を参照。
 * @details 一般的に、サーボモータと呼ばれる部品は、電源、GNDのほかに「制御入力」と呼ばれる信号を持ち、
 *          この信号に与えられたパルスの幅に応じた角度で静止します。<BR>
 *          このライブラリはRX62N/RX63Nの内蔵MTUを6個使い、20チャネルのサーボを同時に制御できます。<BR><BR>
 *          ごく一般的なサーボモータではパルスの周期は20msで、与えるパルスの幅が544usの場合に角度は0°となり、
 *          パルスの幅が2400usの場合に角度は180°となります。角度とパルス幅の関係は自由に設定でき、
 *          パルス幅が長ければながいほど回転角度が大きくなります。<BR>
 *          このライブラリは tkdn_servo.h で用意されたライブラリをC++で使いやすくラッパしたものです。
 *          使用するには、リンカオプションで -lservo を指定してください。<BR>
 ******************************************************************************/
#include "rxduino.h"
#include "../tkdnhal/tkdn_servo.h"

#ifdef __cplusplus
	extern "C" {
#endif

/*********************************************************************//**
 *  @class   Servo
 *  @brief   サーボモータを制御するクラス
 **********************************************************************/
class Servo 
{
private:
	servo_t servo;
	bool _attached;
public:

	Servo(); 
	~Servo();

/*********************************************************************//**
 * @brief     サーボライブラリを初期化し、出力を任意のピンに割り当てる
 * @param pin ピン番号
 * @note 最大20個のチャネルを割り当てられる
 * @return なし
 **********************************************************************/
	void attach(int pin);

/*********************************************************************//**
 * @brief     サーボライブラリを初期化し、出力を任意のピンに割り当てる
 * @param pin ピン番号
 * @param min サーボの角度が0度のときのパルス幅(マイクロ秒)。デフォルトは544
 * @param max サーボの角度が180度のときのパルス幅(マイクロ秒)。デフォルトは2400
 * @note 最大20個のチャネルを割り当てられる
 * @return なし
 **********************************************************************/
	void attach(int pin,int min,int max);

/*********************************************************************//**
 * @brief     サーボの角度をセットし、シャフトをその方向に向ける。<BR>
 * @details   この関数を呼び出すと、指定された回転角になるような幅のパルスが、<BR>
 *            attach() 関数で指定したピンから出力される。
 * @param     angle 静止させたい角度 (0-180の範囲)
 * @return なし
 **********************************************************************/
	void write(int angle);

/*********************************************************************//**
 * @brief     サーボモータに与える出力をマイクロ秒単位で角度を指定する。
 * @details   サーボモータに与えられるパルスは20ms周期で、1周期中のHighの時間を直接指定する。
 * @note      実質的にPWM出力である。連続回転タイプのサーボでは、回転のスピードが設定することができる。
 * @param     us 出力したいパルスの幅をus単位で指定する。範囲は1～19999。<BR>
 *            0を指定すると出力はOFFになる。
 * @return なし
 **********************************************************************/
	void writeMicroseconds(int us);

/*********************************************************************//**
 * @brief     最後に設定された角度を読み出す
 * @note      writeMicroseconds() で与えた値は読みとれない
 * @return    us マイクロ秒単位
 **********************************************************************/
	int read(void);

/*********************************************************************//**
 * @brief     ピンにサーボが割り当てられているかを確認する
 * @return    
 *             - true : 割り当てられている
 *             - false : 割り当てはない
 **********************************************************************/
	bool attached(void);

/*********************************************************************//**
 * @brief     サーボの動作を止め、割り込みを禁止する
 * @details   目的のチャネルのサーボ動作を停止し、割り込みを禁止する。<BR>
 *            指定されたピンのみ停止し、他のピンの動作には影響を与えない
 * @return    なし
 **********************************************************************/
	void detach(void);
};

#ifdef __cplusplus
	}
#endif

#endif // __H_RXDUINO_TONE

