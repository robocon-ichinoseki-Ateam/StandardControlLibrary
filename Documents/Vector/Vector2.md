# Vector2

## 値を設定する
```C++
//初期化
Vector2 v(2.0, 3.0);

// 代入
v.set(2.0, 3.0);

//成分ごとに代入
v.x = 2.0;
v.y = 3.0;
```

## 成分を取得する
```C++
double a = v.x;
double b = v.y;
```

# 関数
## ベクトルの大きさを取得する
```C++
double c = v.getMagnitude();
```

## ベクトルを正規化にする
```C++
v.normalize();
```

## 正規化されたベクトルを取得する
```C++
Vector2 vb = v.getNormalized();
```

## ベクトルをangle分回転させる
```C++
v.rotate(angle);
```

## angle分回転させたベクトルを取得する
```C++
Vector2 vc = v.getRotated(angle);
```

# static関数
## 二つのベクトルの内積を求める
```C++
Vectro2 a, b;
double dot= Vector2::getDot(a, b);
```

## 二つのベクトルの成す角度を求める
```C++
Vectro2 a, b;
double angle = Vector2::getAngle(a, b);
```

## 二つのベクトルの距離
```C++
Vectro2 a, b;
double distance= Vector2::getDistance(a, b);

// distance = (b - a).getMagnitude();
```

## 二つのベクトルをtで線形補完する
```C++
Vectro2 a, b;
double t; // 0 ~ 1
double angle = Vector2::leap(a, b, t);
```