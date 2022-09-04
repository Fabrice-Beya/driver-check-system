//
// Created by Fabrice Beya on 2022/09/04.
//

#ifndef GENERAL_CHECKEVENT_H
#define GENERAL_CHECKEVENT_H

#include "CheckPoint.h"
#include <vector>
#include "Driver.h"

using namespace std;

class CheckEvent {
public:
    int id;
    Driver *driver;
    CheckPoint *checkPoint;
    double checkPointTime;

    // Create a new check in event and update the driver fees
    CheckEvent(Driver *driverArg, CheckPoint *checkpointArg, double checkPointTimeArg) {
        driver = driverArg;
        checkPoint = checkpointArg;
        checkPointTime = checkPointTimeArg;

        driver->updateFees(checkpointArg, checkpointArg->fee, checkPointTimeArg);
    }
};

#endif //GENERAL_CHECKEVENT_H
