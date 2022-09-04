//
// Created by Fabrice Beya on 2022/09/04.
//

#ifndef GENERAL_CHECKPOINT_H
#define GENERAL_CHECKPOINT_H
#include <iostream>
using namespace std;

class CheckPoint {
public:
    string name;
    double fee;
    int totalChecks = 0;

    CheckPoint(string nameArg, double feeArg) {
        name = nameArg;
        fee = feeArg;
    }

    double getCheckPointFee(string checkPointName) {
        return fee;
    }
};

#endif //GENERAL_CHECKPOINT_H
