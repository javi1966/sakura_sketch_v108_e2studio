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

#ifndef	__H_RXDUINO_WIRE
#define	__H_RXDUINO_WIRE
/**************************************************************************//**
 * @file     wire.h
 * @brief    Arduino互換のWireライブラリ(I2C)を定義するヘッダファイル。<BR>
             詳細は TwoWire クラスの説明を参照。
 ******************************************************************************/

#include "rxduino.h"
#include "../tkdnhal/tkdn_i2c.h"

#define WIRE_LIBRARY_VERSION 0x01080000 // Version 1.08
#define WIRE_LIBRARY_TIME    1380466335 // 2013/09/29 23:52:15 

#ifdef __cplusplus
	extern "C" {
#endif

/*********************************************************************//**
 * @class   TwoWire
 * @brief   2線式シリアルインタフェース(Wire または I2Cと呼ばれる)を扱うためのライブラリ。<BR>
 *          このライブラリは tkdn_i2c.h で定義されたライブラリをC++でラッパしたものである。<BR>
 *          このライブラリを使うにはリンカオプションで -lwire を指定する。
 * @note    内蔵RIICモジュールを使うのではなく、GPIOを使って構築されている。<br>
 *          スレーブモードでの使用はできない。
 **********************************************************************/
class TwoWire {
private:
	i2c_info i2c; // 実体を持つ

public:
/*********************************************************************//**
 * @brief       ライブラリのバージョン情報を取得する
 * @param[out]  vi 拡張情報が必要ならばversion_info構造体へのポインタを与える。<BR>
 *              構造体の各フィールドがセットされて戻る。各フィールドは文字列へのポインタだが、<BR>
 *              static constな文字列を指すので、ユーザプログラムでfreeしてはならない。<BR>
 *              拡張情報が不要ならばNULLを指定してもよい
 * @return      バージョン番号を1バイトずつ詰めた16進数で返す
 *              例えば、バージョン1.00ならば、0x01000000を返す
 *              バージョン1.23ならば0x010203となる。
 *              メジャーバージョン.マイナーバージョン.サブバージョン.デバッグバージョン
 **********************************************************************/
	static unsigned long getVersion(version_info *vi);

/*********************************************************************//**
 * @brief       コンストラクタ。Wireクラスのオブジェクトを作成する。
 * @details     Arduinoと同じく、SDA=AN4番ピン(P44)、SCL=AN5番ピン(P45)に割り当てられる。RXduinoではピン番号は assignSdaScl() で変更できる。
 **********************************************************************/
	TwoWire();

/*********************************************************************//**
 * @brief       SDA,SCLピンの割り当て任意のピンに変更する
 * @param       sda_pin SDA(データ端子)のピンの番号。任意のピンが使用できる。
 * @param       scl_pin SCL(クロック端子)のピンの番号。任意のピンが使用できる。
 * @return      なし
 * @note      SDA端子はACKを受信する時に内蔵プルアップが有効になるので、外付けのプルアップ抵抗がなくてもそれなりに通信はできるが、より安定した高速動作のためにはプルアップ抵抗を外付けすることが望ましい
 **********************************************************************/
	void assignSdaScl(int sda_pin, int scl_pin);

/*********************************************************************//**
 * @brief       I2Cマスターとして初期化する
 * @return      なし
 **********************************************************************/
	void begin();

/*********************************************************************//**
 * @brief       I2Cスレーブとして初期化する
 * @warning     この機能は実装されていない
 * @return      なし
 * @todo      いずれI2Cスレーブモードを作る必要があるだろう
 **********************************************************************/
	void begin(int address);

/*********************************************************************//**
 * @brief     I2Cデバイスに対して受信シーケンスを発行し、データを読み出す
 * @details   読み出したデータ数は available() 関数で確認する。バッファ中のデータは read() 関数で読み出す。
 * @param     address ターゲットデバイスのアドレス(7bit)<BR>RD/WRを示すビットは含まず、0～0x7Fまでの純粋なアドレスを与えること。
 * @param     count 読み出したいデータのバイト数。範囲は0～260。260以上の値を指定した場合は260に切り捨てられる。
 * @return    実際に受信したバイト数。ターゲットデバイスがNACKを返した場合は、countで指定した値に満たなくても終了する。
 **********************************************************************/
	int requestFrom(unsigned char address, int count);

/*********************************************************************//**
 * @brief     受信バッファ内に溜まっているデータ数を調べる
 * @return    データ数(バイト単位)
 **********************************************************************/
	int available();


/*********************************************************************//**
 * @brief     受信バッファからデータを1バイト取り出す
 * @return    データがある場合は0～255を返す。データがない場合は-1を返す。
 **********************************************************************/
	int read();

/*********************************************************************//**
 * @brief     I2Cデバイスに対して送信を開始するための準備をする
 * @note      この関数は送信バッファを初期化するだけで、実際の動作は行わない。繰り返し呼ぶと、送信バッファが先頭に戻る。
 * @param     address ターゲットデバイスのアドレス(7bit)<BR>RD/WRを示すビットは含まず、0～0x7Fまでの純粋なアドレスを与えること。
 * @return    なし
 **********************************************************************/
	void beginTransmission(unsigned char address);

/*********************************************************************//**
 * @brief     送信バッファの末尾に1バイトのデータを追加する
 * @note      この関数は送信バッファにデータを溜めるだけで、実際の動作は行わない
 * @param     data 送信したいデータ
 * @return    成功したら1を返す。送信バッファ(260バイト)に空き容量が無ければ失敗して0を返す
 **********************************************************************/
	int write(unsigned char data);

/*********************************************************************//**
 * @brief     送信バッファの末尾に数値を追加する
 * @note      この関数は送信バッファにデータを溜めるだけで、実際の動作は行わない
 * @param     data 送信したいデータ
 * @return    成功したら送信したバイト数(バッファに溜めたバイト数)を返す。送信バッファ(260バイト)に空き容量が無ければ失敗して0を返す
 **********************************************************************/
	int write(int data);

/*********************************************************************//**
 * @brief     送信バッファの末尾に文字列送信を追加する
 * @note      この関数は送信バッファにデータを溜めるだけで、実際の動作は行わない
 * @param     str 送信したい文字列
 * @return    成功したら送信したバイト数(バッファに溜めたバイト数)を返す。送信バッファ(260バイト)に空き容量が無ければ失敗して0を返す
 **********************************************************************/
	int write(char *str);

/*********************************************************************//**
 * @brief     送信バッファの末尾にデータブロックを追加する
 * @note      この関数は送信バッファにデータを溜めるだけで、実際の動作は行わない
 * @param     data 送信したいデータ
 * @param     quantity 送信したいデータ数
 * @return    成功したら送信したバイト数(バッファに溜めたバイト数)を返す。送信バッファ(260バイト)に空き容量が無ければ失敗して0を返す
 **********************************************************************/
	int write(unsigned char *data,int quantity);

/*********************************************************************//**
 * @brief     ターゲットデバイスに対してI2Cの送信シーケンスを発行する
 * @details   I2Cの送信はこの関数を実行して初めて実際に行われる。<BR>
 *            送信されるターゲットアドレスは beginTransmission() 関数で指定したもの。
 *            送信データは write() 関数でバッファに格納されたもの。
 * @return    戻り値は以下のとおり
 *             - 0: 成功
 *             - 1: 送信バッファ溢れ
 *             - 2: スレーブアドレス送信時にNACKを受信
 *             - 3: データ送信時にNACKを受信
 *             - 4: その他のエラー
 **********************************************************************/
	unsigned char endTransmission();

/*********************************************************************//**
 * @brief     I2Cの周波数を変更する
 * @details   空ループで測っている。タイマを使ってキャリブレーションしているので、それなりに正確な値が出るはず。
 * @param[in] freq クロックの周波数をHz単位で指定する。有効な値は1～200000程度。基本的にソフトでやっているので400kHzは出ない。
 * @return    なし
 **********************************************************************/
	void setFrequency(int freq);


};

extern TwoWire Wire;

#ifdef __cplusplus
	}
#endif

#endif // __H_RXDUINO_TONE

