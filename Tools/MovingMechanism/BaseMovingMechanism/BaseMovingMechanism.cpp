#include "BaseMovingMechanism.h"


BaseMovingMechanism::BaseMovingMechanism(mechanismConfig_t config, thresholdParam_t thresholdParam, int wheelNum) :
    _config(config), _thresholdParam(thresholdParam), _wheelNum(wheelNum)
{
    
}

void BaseMovingMechanism::calculateBase(double velocityVector[3], double outputRate[])
{
    // 出力のレートを格納するバッファ変数  [-300.0 - 300.0]
    double bufOutputRate[4] = {0};
    
    // 理論出力レート値が実際の範囲越えを起こしたかを格納するフラグ変数
    bool isOverflowOfOutputRate = false;

    // 最大値を格納 [0-_thresholdParam.maxOutput]
    double MaxAbsOutputRate = 0;
    
    
    // 閾値未満切り捨て、ガード処理
    for(int element = 0; element < 3; element++)
    {
        if(abs(velocityVector[element]) < _thresholdParam.minInput)
            velocityVector[element] = 0;
        if(abs(velocityVector[element]) > _thresholdParam.maxInput)
            velocityVector[element] = _thresholdParam.maxInput;
    }
    
    // 線形変換
    for(int motorNum = 0; motorNum < _wheelNum; motorNum++)
    {
        for (int element = 0; element < 3; element++) {
            bufOutputRate[motorNum] += _rateMatrix[motorNum][element] * velocityVector[element];
        }
        
        // 絶対値の最大値を格納
        MaxAbsOutputRate = (abs(bufOutputRate[motorNum]) > MaxAbsOutputRate) ? abs(bufOutputRate[motorNum]) : MaxAbsOutputRate;

        // いずれかのモータが出力倍率を超過していればフラグを立てる
        if (abs(bufOutputRate[motorNum]) > _thresholdParam.maxOutput) {
            isOverflowOfOutputRate = true;
        }
    }
    
    // 出力値の最終調整
    // 1つでもモータが出力倍率を超過しているか？
    if (isOverflowOfOutputRate == true) {
        // 超過している
        // 出力値を再調整しつつ出力用の配列に書きこむ
        for (int motorNum = 0; motorNum < _wheelNum; motorNum++) {
            outputRate[motorNum] = constrain((bufOutputRate[motorNum] * (_thresholdParam.maxOutput / MaxAbsOutputRate)), -_thresholdParam.maxOutput, _thresholdParam.maxOutput) * MaxAbsOutputRate / _thresholdParam.maxOutput;
        }
    } else {
        // 超過が存在しない
        // すべて出力範囲内で収まっているためそのまま書き込む
        for (int motorNum = 0; motorNum < _wheelNum; motorNum++) {
            outputRate[motorNum] = bufOutputRate[motorNum] * MaxAbsOutputRate / _thresholdParam.maxOutput;
        }
    }
}