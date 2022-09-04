//
// Created by Fabrice Beya on 2022/09/04.
//

#ifndef GENERAL_DRIVER_H
#define GENERAL_DRIVER_H
#include <vector>
#include <iostream>
#include "CheckPoint.h"

using namespace std;

class DriverCheck {
public:
    CheckPoint *checkPoint;
    double time;

    DriverCheck(CheckPoint *checkPointArg, double timeArg) {
        checkPoint = checkPointArg;
        time = timeArg;
    }
};

class Driver {
public:
    int id;
    vector<DriverCheck*> checks;
    vector<DriverCheck*> lastDayChecks;
    double totalFees;
    double totalDailyFees;

    Driver(int idArg) {
        id = idArg;
        checks = {};
        totalFees = 0;
        totalDailyFees = 0;
    }
    void updateFees(CheckPoint *checkPoint, double feeArg, double time) {
        totalFees += feeArg;
        DriverCheck *newCheck = new DriverCheck(checkPoint, feeArg);
        checks.push_back(newCheck);
        // Check if the new check is within a 24hr period and add it to the last day checks
        if (24 - time > 0) {
            lastDayChecks.push_back(newCheck);
        }

        // Computer total daily fees
        computeDailyFees();
    }

    /*
     * A Pruning task which needs to run each day to ensure that the last day checks are updated
     */
    void computeLastDayChecks() {
        vector<DriverCheck*> tmp = {};

        for(auto check: checks) {
            if (24.00 - check->time > 0) {
                tmp.push_back(check);
            }
        }

        lastDayChecks = tmp;
    }

    /*
     * Return total driver fees
     */
    double getTotalFees() {
        return totalFees;
    }

    /*
     * Return total daily driver fees
     */
    double getTotalDailyFees() {
        return totalDailyFees;
    }

    /*
     * Compute the total daily fees for the day using list of last day check
     */
    void computeDailyFees() {
        double tmp = 0;
        for(auto check: lastDayChecks) {
            tmp += check->checkPoint->fee;
        }

        totalDailyFees = tmp;
    }
};

#endif //GENERAL_DRIVER_H
