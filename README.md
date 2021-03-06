# BME280_PIC16F1619
これはBoschの温度、湿度、気圧センサBME280及びマイクロチップ・テクノロジーの温度センサMCP9804をPIC16F1619でコントロールするプログラムです。マイコンボードはPIC16F1619が標準で搭載されているCuriosityボードを使用しています。Curiosityボード上からI2C信号を取り出してBME280、MCP9804からデータを取り出してUartでデータを出力しています。   

![terminal_bme280_mcp9804](https://user-images.githubusercontent.com/2620156/36507565-71e6009a-179d-11e8-887d-ee3369d22b60.gif)

## 目的
BME280で取ったデータが正しいかどうか確かめるために作りました。またI2Cの２個使いの確認の為も兼ねています。

## 実験環境
次のように接続しています。  

![curiosity_bme280_mcp9804](https://user-images.githubusercontent.com/2620156/36507124-19f30a3c-179c-11e8-8254-2314a10bc3c0.png)

## MCCの設定
Microchip Code Configurator(MCC)で基本設定を行っています。MCCはEUSARTとTimer2を使用していてMSSPのライブラリは使用していません。使用していない理由は使いにくいのと無駄にメモリを使用していたためです。

| RAM size | ROM size|
|:----|----------|
|236 (23%)|5578 (68%)|

### PIN設定
下図のMCC設定画面を参照してください。  
![pin asign](https://user-images.githubusercontent.com/2620156/36339272-06efcbc2-1405-11e8-9d09-4a7464d4cbc9.png)

## BME280_driver
このフォルダー以下にBoschのサイトからダウンロードしたAPIをおいています。基本は変更していませんが、bme280_defs.hがXC8ではコンパイルが通らなかったのでキャスト変換マクロを変更しています。
```
#if !defined(UINT8_C) && !defined(INT8_C)
#define INT8_C(x)       (int8_t)(x)
#define UINT8_C(x)      (uint8_t)(x)
#endif
```

## 結果
- 0.3℃ぐらいの差があった。
- ２，３時間動作させて室内の温度があまり変化がない場合はほぼ同じでした。
- 立ち上げ後すぐは１℃弱の差がある。
