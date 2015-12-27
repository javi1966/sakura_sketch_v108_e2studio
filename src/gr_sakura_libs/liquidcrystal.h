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
// キャラクタ液晶のライブラリ
// (C)Copyright 2011 特殊電子回路

#ifndef	__H_RXDUINO_LIQUIDCRYSTAL
#define	__H_RXDUINO_LIQUIDCRYSTAL

/**************************************************************************//**
 * @file     liquidcrystal.h
 * @brief    Arduino互換のLiquidCrystalライブラリを定義するヘッダファイル。<BR>
             詳細は LiquidCrystal クラスの説明を参照。
 ******************************************************************************/

/*********************************************************************//**
 * @class   LiquidCrystal
 * @details 標準的なキャラクタLCDを扱うためのライブラリ。<BR>
 *          ライブラリを使用するには、リンカオプションで -lliquidcrystal を指定する。
 * @brief   標準的なキャラクタLCDを扱うためのクラス
 * @todo    createCharの仕様がArduinoと違うらしい。
 **********************************************************************/
class LiquidCrystal {
private:
	char pinnum[11];
	void init();
	unsigned char cols;
	unsigned char rows;

	unsigned char col;
	unsigned char row;
	unsigned char entry_mode;
	unsigned char display_mode;
	unsigned char cursol_mode;
	unsigned char mode4bit;

	void send_control(unsigned char val);
	void send_data(unsigned char data);

	size_t print_number(unsigned long val,int base);

public:
	int writeDelay; //!< // １文字書き込み後の遅延時間。us単位。(デフォルト0)

/*********************************************************************//**
 * @brief    データ線4bit、RS、ENABLEありで使うためのオブジェクトを生成する
 * @param    rs LCDのRSピンに接続するピン番号
 * @param    enable LCDのENABLEピンに接続するピン番号
 * @param    d4 LCDのデータ線D4に接続するピン番号
 * @param    d5 LCDのデータ線D5に接続するピン番号
 * @param    d6 LCDのデータ線D6に接続するピン番号
 * @param    d7 LCDのデータ線D7に接続するピン番号
 **********************************************************************/
	LiquidCrystal(int rs, int enable, int d4, int d5, int d6, int d7);

/*********************************************************************//**
 * @brief    データ線4bit、RS、RW、ENABLEありで使うためのオブジェクトを生成する
 * @param    rs LCDのRSピンに接続するピン番号
 * @param    rw LCDのRWピンに接続するピン番号
 * @param    enable LCDのENABLEピンに接続するピン番号
 * @param    d4 LCDのデータ線D4に接続するピン番号
 * @param    d5 LCDのデータ線D5に接続するピン番号
 * @param    d6 LCDのデータ線D6に接続するピン番号
 * @param    d7 LCDのデータ線D7に接続するピン番号
 **********************************************************************/
	LiquidCrystal(int rs, int rw, int enable, int d4, int d5, int d6, int d7);

/*********************************************************************//**
 * @brief    データ線8bit、RS、ENABLEありで使うためのオブジェクトを生成する
 * @param    rs LCDのRSピンに接続するピン番号
 * @param    enable LCDのENABLEピンに接続するピン番号
 * @param    d0 LCDのデータ線D0に接続するピン番号
 * @param    d1 LCDのデータ線D1に接続するピン番号
 * @param    d2 LCDのデータ線D2に接続するピン番号
 * @param    d3 LCDのデータ線D3に接続するピン番号
 * @param    d4 LCDのデータ線D4に接続するピン番号
 * @param    d5 LCDのデータ線D5に接続するピン番号
 * @param    d6 LCDのデータ線D6に接続するピン番号
 * @param    d7 LCDのデータ線D7に接続するピン番号
 **********************************************************************/
	LiquidCrystal(int rs, int enable, int d0, int d1, int d2, int d3, int d4, int d5, int d6, int d7);

/*********************************************************************//**
 * @brief    データ線8bit、RS、RW、ENABLEありで使うためのオブジェクトを生成する
 * @param    rs LCDのRSピンに接続するピン番号
 * @param    rw LCDのRWピンに接続するピン番号
 * @param    enable LCDのENABLEピンに接続するピン番号
 * @param    d0 LCDのデータ線D0に接続するピン番号
 * @param    d1 LCDのデータ線D1に接続するピン番号
 * @param    d2 LCDのデータ線D2に接続するピン番号
 * @param    d3 LCDのデータ線D3に接続するピン番号
 * @param    d4 LCDのデータ線D4に接続するピン番号
 * @param    d5 LCDのデータ線D5に接続するピン番号
 * @param    d6 LCDのデータ線D6に接続するピン番号
 * @param    d7 LCDのデータ線D7に接続するピン番号
 **********************************************************************/
	LiquidCrystal(int rs, int rw, int enable, int d0, int d1, int d2, int d3, int d4, int d5, int d6, int d7);

/*********************************************************************//**
 * @brief    LCDの桁数と行数を指定する
 * @param    cols 桁数
 * @param    rows 行数
 * @return   なし
 **********************************************************************/
	void begin(int cols,int rows);

/*********************************************************************//**
 * @brief    LCDの表示をクリアする
 * @return   なし
 **********************************************************************/
	void clear(void);

/*********************************************************************//**
 * @brief    LCDのカーソルをホームポジションに戻す
 * @return   なし
 **********************************************************************/
	void home(void) ;

/*********************************************************************//**
 * @brief    LCDのカーソルを移動する
 * @param    col 桁 (0が左端)
 * @param    row 行 (0が1行目)
 * @return   なし
 **********************************************************************/
	void setCursor(unsigned char col,unsigned char row) ;

/*********************************************************************//**
 * @brief    LCDに1文字出力する
 * @param    data 表示したい文字コード
 * @return   出力したバイト数
 **********************************************************************/
	size_t write(unsigned char data);

/*********************************************************************//**
 * @brief    LCDに文字列を出力する
 * @param    str 表示したい文字列
 * @return   実際に出力したバイト数
 **********************************************************************/
	size_t print(const char str[]);

/*********************************************************************//**
 * @brief    LCDに文字を出力する
 * @param    c 出力したい文字コード
 * @return   実際に出力したバイト数
 **********************************************************************/
	size_t print(char c);

/*********************************************************************//**
 * @brief    LCDに値(数字)を出力する
 * @param    c 出力したい値
 * @param print_type 基数
 *        - 2:  二進数
 *        - 8:  8進数
 *        - 10: 10進数 (デフォルト)
 *        - 16: 16進数
 * @return 実際に出力したバイト数
 **********************************************************************/
	size_t print(unsigned char c, int print_type=DEC);

/*********************************************************************//**
 * @brief    LCDに値(数字)を出力する
 * @param    val 出力したい値
 * @param print_type 基数
 *        - 2:  二進数
 *        - 8:  8進数
 *        - 10: 10進数 (デフォルト)
 *        - 16: 16進数
 * @return 実際に出力したバイト数
 **********************************************************************/
	size_t print(int val, int print_type=DEC);

/*********************************************************************//**
 * @brief    LCDに値(数字)を出力する
 * @param    val 出力したい値
 * @param print_type 基数
 *        - 2:  二進数
 *        - 8:  8進数
 *        - 10: 10進数 (デフォルト)
 *        - 16: 16進数
 * @return 実際に出力したバイト数
 **********************************************************************/
	size_t print(unsigned int val, int print_type=DEC);

/*********************************************************************//**
 * @brief    LCDに値(数字)を出力する
 * @param    val 出力したい値
 * @param print_type 基数
 *        - 2:  二進数
 *        - 8:  8進数
 *        - 10: 10進数 (デフォルト)
 *        - 16: 16進数
 * @return 実際に出力したバイト数
 **********************************************************************/
	size_t print(long val, int print_type=DEC);

/*********************************************************************//**
 * @brief    LCDに値(数字)を出力する
 * @param    val 出力したい値
 * @param print_type 基数
 *        - 2:  二進数
 *        - 8:  8進数
 *        - 10: 10進数 (デフォルト)
 *        - 16: 16進数
 * @return 実際に出力したバイト数
 **********************************************************************/
	size_t print(unsigned long val, int print_type=DEC);

/*********************************************************************//**
 * @brief    LCDに浮動小数点数を出力する
 * @param    val 出力したい値
 * @param fpdigit 小数点以下何桁まで表示するか
 * @return 実際に出力したバイト数
 **********************************************************************/
	size_t print(double val, int fpdigit=2);

/*********************************************************************//**
 * @brief    カーソルを表示します
 * @return   なし
 **********************************************************************/
	void cursor();

/*********************************************************************//**
 * @brief    カーソルを消します
 * @return   なし
 **********************************************************************/
	void noCursor();

/*********************************************************************//**
 * @brief    カーソルを点滅させます
 * @return   なし
 **********************************************************************/
	void blink();

/*********************************************************************//**
 * @brief    カーソルの点滅をやめます
 * @return   なし
 **********************************************************************/
	void noBlink();

/*********************************************************************//**
 * @brief    画面を表示します
 * @return   なし
 **********************************************************************/
	void display();

/*********************************************************************//**
 * @brief    画面の表示を消します
 * @return   なし
 **********************************************************************/
	void noDisplay();

/*********************************************************************//**
 * @brief    表示中の文字とカーソルを左に1個スクロールします
 * @return   なし
 **********************************************************************/
	void scrollDisplayLeft();

/*********************************************************************//**
 * @brief    表示中の文字とカーソルを右に1個スクロールします
 * @return   なし
 **********************************************************************/
	void scrollDisplayRight();

/*********************************************************************//**
 * @brief    自動スクロールを有効にします
 * @return   なし
 **********************************************************************/
	void autoscroll();

/*********************************************************************//**
 * @brief    自動スクロールを無効にします
 * @return   なし
 **********************************************************************/
	void noAutoscroll();

/*********************************************************************//**
 * @brief    左から右に文字を出力していきます
 * @return   なし
 **********************************************************************/
	void leftToRight();

/*********************************************************************//**
 * @brief    右から左に文字を出力していきます
 * @return   なし
 **********************************************************************/
	void rightToLeft();

/*********************************************************************//**
 * @brief    カスタムキャラクタを作成します
 * @param    location 作成するキャラクタの番号
 *            - 0 - カスタムキャラクタ0 
 *            - 1 - カスタムキャラクタ1 
 *            - 2 - カスタムキャラクタ2 
 *            - 3 - カスタムキャラクタ3 
 *            - 4 - カスタムキャラクタ4 
 *            - 5 - カスタムキャラクタ5 
 *            - 6 - カスタムキャラクタ6 
 *            - 7 - カスタムキャラクタ7 
 *           上記以外の値を入れたときには何もしない
 * @param    charmap[] 作成するキャラクタのビットマップが入った配列
 * @note     この関数の仕様はV1.00でArduinoライブラリに準拠した。
 * @return   なし
 **********************************************************************/
	void createChar(unsigned char location,const unsigned char charmap[]);
};

#endif // __H_RXDUINO_LIQUIDCRYSTAL
