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

#ifndef	__H_RXDUINO_STEPPER
#define	__H_RXDUINO_STEPPER
/**************************************************************************//**
 * @file     Stepper.h
 * @brief    Stepperクラスを使うためのライブラリを使用するためのヘッダファイル<BR>
             詳細は Stepper クラスの説明を参照。
 ******************************************************************************/
#include "rxduino.h"

#ifdef __cplusplus
	extern "C" {
#endif

/*********************************************************************//**
 *  @class   Stepper
 *  @brief   ステッピングモータを制御するクラス
 *  @details  ライブラリを使用するには、リンカオプションで -lstepper を指定する。
 **********************************************************************/
class Stepper{
public:

/*********************************************************************//**
 *  @brief   接続するモータの種類
 *  @note    このenum型を使用するには、myStepper(steps,3,4,5,6,Stepper::NORMAL4)などのようにデータメンバを指定する必要がある.指定なしの場合NORMAL4が選択される
 **********************************************************************/
	typedef enum
	{
		NORMAL4,	//!< 4極ステッピングモータ．デフォルトはこの設定になる
		PIN34DIR,	//!< 2極ステッピングモータ(モータ極性端子は2極,方向端子2極)  
		NORMAL2,	//!< 2極ステッピングモータ
	} STEPPER_TYPE;

/*********************************************************************//**
 *  @brief   4本線ステッピングモータ用のコンストラクタ
 *  @details Stepperクラスのコンストラクタ。4極ステッピングモータや、2極で論理反転回路があるモータなどで使う
 *  @param[in] steps 1回転あたりのステップ数
 *  @param[in] pin_1  モータに接続するピンの番号
 *  @param[in] pin_2  モータに接続するピンの番号
 *  @param[in] pin_3  モータに接続するピンの番号,または極性反転用ピンの番号
 *  @param[in] pin_4  モータに接続するピンの番号,または極性反転用ピンの番号
 *  @param[in] type  接続するモータの種類
 *                    - NORMAL4  : 中点タップのコイルタイプで使う (MERCURY MOTOR社のST-42BYG020などの型)
 *                    - PIN34DIR : pin_3とpin_4は、モータドライバの極性反転端子に接続する
 *  @note    このenum型を使用するには、myStepper(steps,3,4,5,6,Stepper::NORMAL4)などのようにデータメンバを指定する必要がある.指定なしの場合NORMAL4が選択される
 **********************************************************************/
	Stepper(int steps, int pin_1, int pin_2, int pin_3, int pin_4, STEPPER_TYPE type = NORMAL4);

/*********************************************************************//**
 *  @brief   2本線ステッピングモータ用のコンストラクタ
 *  @details Stepperクラスのコンストラクタ。2極で正負の信号を流すステッピングモータで使う。
 *  @param[in] steps 1回転あたりのステップ数
 *  @param[in] pin_1  モータに接続するピンの番号
 *  @param[in] pin_2  モータに接続するピンの番号
 **********************************************************************/
	Stepper(int steps, int pin_1, int pin_2);

/*********************************************************************//**
 *  @brief   1分間あたり何回転するかを決める
 *  @param[in] rpms 回転速度[rpm]
 *  @return  なし
 **********************************************************************/
	void setSpeed(int rpms);

/*********************************************************************//**
 *  @brief   モーターを回転させる
 *  @param[in] steps モータが回転する量をステップ数により指定する。<BR>
 *             負の数を入力すると逆回転する。
 *  @note    この関数はモータが停止するまで制御を返さない
 *  @return  なし
 **********************************************************************/
	void step(int steps);

/*********************************************************************//**
 *  @brief   モータ停止時に各ピンをどの状態にするかを指定する
 *  @details  - 0:Lowレベル
 *            - 1:Highレベル
 *            - それ以外:変更しない(デフォルト)
 *  @note    このメンバ変数を設定すると、モータ停止時にコイルに流れる電流をとめることができ、
 *           消費電力を低減できる。しかし、モータの位置が動いてしまうため、正しい位置にならない。
 **********************************************************************/
	int  pin_safe_state;

/*********************************************************************//**
 *  @brief   モータの現在の回転速度を取得する。
 *  @return  現在の回転速度。単位はrpm。
 **********************************************************************/
	int  getRpms(void);

/*********************************************************************//**
 *  @brief   モータの現在の回転位置を取得する。
 *  @return  現在の回転位置。単位はステップ数。
 **********************************************************************/
	int  getPosition(void);

private:
	void setMotorCycles(int cycles);		// モータを実際に回転させる関数

	int clock_wise;							// 回転方向(0:反時計回り,1:時計回り)
	int rpms;
	STEPPER_TYPE type;

	unsigned int delay_motor_cycles;		// それぞれのステップの時間間隔
	int max_steps;							// 1周するときのトータルステップ数
	int position;							// モータが現在どのステップにいるか
	int pin_counter;						//　モータドライブに使うピン数(2 or 4)

	// モータ制御に使うピン
	int pin_1;
	int pin_2;
	int pin_3;
	int pin_4;

	int delay_last_time;					// 前回の時間のタイムスタンプ記憶用
};

#ifdef __cplusplus
	}
#endif

#endif // __H_RXDUINO_TONE

