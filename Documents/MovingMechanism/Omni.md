# Omniライブラリ

## 初期設定
```C++
mechanismConfig_t _config = 
{
    .theta = PI / 6, // x軸と番号0のホイールがなす角度
    .radius  = 0.4, // 機体半径
    .option = OMNI_3WHEEL // or 'OMNI_4WHEEL'
};

thresholdParam_t _param = 
{
    .minInput = 0.1,
    .maxInput = 2.7,
    .minOutput = 0.05,
    .maxOutput = 2.7
};

Omni omni(_config, _param);
```

`mechanismConfig_t ` マシンの大きさについての設定 単位[rad], [m]
`thresholdParam_t  ` マシンの速度についての設定(絶対値) 単位[m/s]

## 計算
```C++
double velocity[3];
omni.calculate(velocity);
```
または
```C++
double vx, vy, vtheta;
omni.calculate(vx, vy, vtheta);
```

内部で入力の値の絶対値を`thresholdParam_t`の`.minInput`から`.maxInput`でガード処理した後に移動機構ごとの計算をする。その後計算結果を`.minOutput`から`.maxOutput`でガード処理する

## ホイール速度の取得
```C++
double v[4];
for(int wheel; wheel < 3; wheel++)
{
    v[wheel] = omni.getWheelVelocity(wheel);
}
```

引数にホイール番号(右斜め前から反時計回りに0~2)を指定する