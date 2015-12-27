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

#ifndef	__H_RXDUINO_USBHOST
#define	__H_RXDUINO_USBHOST
/**************************************************************************//**
 * @file     usbhost.h
 * @brief    独自仕様のUSBホストライブラリ
 ******************************************************************************/

#include "rxduino.h"
#include "../tkdnhal/tkusbhost.h"

#define USBHOST_LIBRARY_VERSION 0x01080000 // Version 1.08

#ifdef __cplusplus
	extern "C" {
#endif

class USBHost;

/*********************************************************************//**
 * @class   EndPoint
 * @brief   USBのエンドポイントを抽象化して扱うためのクラス。USBホストライブラリの一部。
 * @brief   このライブラリは tkusbhost.h で定義されたライブラリをC++でラッパしたものである。<BR>
 *          このライブラリを使うにはリンカオプションで -lusbhost を指定する。
 **********************************************************************/
class EndPoint {
	int ep;
	USBHost *parent;
	int timeout;

public:
/*********************************************************************//**
 * @brief       リード・ライトでタイムアウトする時間を設定
 * @param[in]   milliseconds タイムアウトするまでの時間。ms単位で指定する。<BR>-1を指定すると無限に待つ。
 * @return      なし
 **********************************************************************/
	void setTimeout(int milliseconds);

/*********************************************************************//**
 * @brief       コントロール・リード転送を実行する
 * @param[in]   reqt bmRequestTypeフィールド
 * @param[in]   req bRequestフィールド
 * @param[in]   val wValueフィールド
 * @param[in]   index wIndexフィールド
 * @param[out]  buf 読み出されたデータが格納されるバッファ
 * @param[in]   len 読み出したい長さ
 * @note        例えば、GET_DESCRIPTORを発行するには、reqt=0x80,req=0x06とする。
 * @return      実際に読み出したバイト数を返す。失敗またはパラメータ異常の場合は-1を返す
 **********************************************************************/
	int read(unsigned char reqt,unsigned char req,unsigned short val,unsigned short index,unsigned char *buf,int len);

/*********************************************************************//**
 * @brief       バルク転送でエンドポイントからデータを読み出す
 * @param[out]  buf 読み出されたデータが格納されるバッファ
 * @param[in]   len 読み出したい長さ
 * @return      実際に読み出したバイト数を返す。失敗またはパラメータ異常の場合は-1を返す
 **********************************************************************/
	int read(unsigned char *buf,int len);

/*********************************************************************//**
 * @brief       コントロール・ライト転送を実行する
 * @param[in]   reqt bmRequestTypeフィールド
 * @param[in]   req bRequestフィールド
 * @param[in]   val wValueフィールド
 * @param[in]   index wIndexフィールド
 * @param[out]  buf 送信したいデータが格納されるバッファ
 * @param[in]   len 送信したい長さ
 * @return      実際に送信されたバイト数を返す。失敗またはパラメータ異常の場合は-1を返す
 **********************************************************************/
	int write(unsigned char reqt,unsigned char req,unsigned short val,unsigned short index,unsigned char *buf,int len);

/*********************************************************************//**
 * @brief       エンドポイントにデータを送信する
 * @param[out]  buf 送信したいデータが格納されるバッファ
 * @param[in]   len 送信したい長さ
 * @return      実際に送信されたバイト数を返す。失敗またはパラメータ異常の場合は-1を返す
 **********************************************************************/
	int write(unsigned char *buf,int len);

	// 以下の関数やメンバ変数には、ユーザは操作しないこと
	EndPoint(); // 空のEndPointを作る
	EndPoint(const EndPoint &obj) {ep = obj.ep;parent = obj.parent;timeout = obj.timeout;} ; // コピーコンストラクタ
	EndPoint(USBHost *parent,int ep) {this->parent = parent;this->ep = ep;timeout = 100;};
	operator int() {if(!parent || (ep < 0)) return 0; return 1;}
	operator bool() {if(!parent || (ep < 0)) return false; return true;}
};

/*********************************************************************//**
 * @class   USBHost
 * @brief   USBホストライブラリ<BR>
 *          このライブラリは tkusbhost.h で定義されたライブラリをC++でラッパしたものである。<BR>
 *          データの送受信は EndPoint クラスを使う。<BR>
 *          このライブラリを使うにはリンカオプションで -lusbhost を指定する。
 **********************************************************************/
class USBHost {
private:
	bool init;

public:
/*********************************************************************
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
//	static unsigned long getVersion(version_info *vi);

/*********************************************************************//**
 * @brief       コンストラクタ。USBHostクラスのオブジェクトを作成する。
 **********************************************************************/
	USBHost();

	~USBHost();

/*********************************************************************//**
 * @brief       初期化して、ターゲットからの接続を待つ
 * @details     2回以上呼び出した場合は、初期化はスキップして、接続待ちのみを行う。
 * @param       timeout タイムアウトまでの時間をms単位で指定する
 * @param       GPIOPullDown trueならば、P22,P25のプルダウンを行う。最初の呼び出しのときのみ効果がある。
 * @return      成功したらtrue、失敗したらfalse
 **********************************************************************/
	bool begin(int timeout,bool GPIOPullDown = false);

/*********************************************************************//**
 * @brief       ターゲットに接続したかどうかを調べる
 * @return      接続していればtrueを返す。接続していなければfalseを返す
 **********************************************************************/
	bool connected();

/*********************************************************************//**
 * @brief       ターゲットと切断する
 * @return      なし
 **********************************************************************/
	void stop();

/*********************************************************************//**
 * @brief       ターゲットのベンダIDを調べる
 * @return      ベンダID
 **********************************************************************/
	unsigned short getVendor();

/*********************************************************************//**
 * @brief       ターゲットのベンダIDとベンダ名を調べる
 * @param[out]  string ベンダIDの名前が格納される文字列バッファ。NULLを指定すると省略
 * @param[in]   buflen 文字列バッファの長さ
 * @return      ベンダID
 **********************************************************************/
	unsigned short getVendor(char *string,int buflen);

/*********************************************************************//**
 * @brief       ターゲットのプロダクトIDを調べる
 * @return      プロダクトID
 **********************************************************************/
	unsigned short getProduct();

/*********************************************************************//**
 * @brief       ターゲットのプロダクトIDとプロダクト名を調べる
 * @param[out]  string プロダクトIDの名前が格納される文字列バッファ。NULLを指定すると省略
 * @param[in]   buflen 文字列バッファの長さ
 * @return      プロダクトID
 **********************************************************************/
	unsigned short getProduct(char *string,int buflen);

/*********************************************************************//**
 * @brief       エンドポイントのオブジェクトを得る
 * @param       ep 取得したいエンドポイントの番号
 * @return      なし
 **********************************************************************/
	EndPoint getEndPoint(int ep);
};

#ifdef __cplusplus
	}
#endif

#endif // __H_RXDUINO_TONE

