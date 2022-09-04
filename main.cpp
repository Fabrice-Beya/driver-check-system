//
// Created by Fabrice Beya on 2022/09/03.
//
#include <iostream>
#include <unordered_map>
#include <vector>
#include "Driver.h"
#include "CheckPoint.h"
#include "CheckEvent.h"
#include <fstream>

using namespace std;
/*
 * Check out point system at each checkpoint you can compute the following
 * - Add new checkpoints
 * - Perform driver check in
 * - Generate spreadsheet of total fees for driver
 * - Generate spreadsheet of to total fees for driver for last 24 hrs
 */

class CheckPointSystem {
public:
    // Keep track of all checks for a given driver
    unordered_map<int, vector<CheckEvent*>> checks;
    // Keep track of all the drivers which have passed through checks
    unordered_map<int, Driver*> driverLog;
    // Keep track of all valid checkpoints
    unordered_map<string, CheckPoint*> checkPoints;
    ofstream dailyFeesLog;

    CheckPointSystem() {
        checks = {};
        driverLog = {};
    }

    void AddCheckPoint(string name, double fee) {
        auto checkPoint = checkPoints[name];

        if (checkPoint == NULL) {
            checkPoint = new CheckPoint(name, fee);
        }

        checkPoints[name] = checkPoint;
    }

    int checkInDriver(int id, string checkPointName, int time) {

        auto checkPoint = checkPoints[checkPointName];

        if (checkPoint == NULL) {
            // Invalid checkpoint
            return -1;
        }

        // Check if driver exist else create a new driver and add it to the driver log
        auto driver = driverLog[id];
        if (driver == NULL) {
            driver = new Driver(id);
        }
        driverLog[id] = driver;

        // Create a new check point event and add it to the map
        CheckEvent *checkEvent = new CheckEvent(driver, checkPoint, time);
        checks[id].push_back(checkEvent);

    }

    /*
     * Create a new csv spreadsheet and use the driver log to fetch total driver fees
     */
    void generateTotalDriverFees() {
        dailyFeesLog.open("total_fees.csv");
        dailyFeesLog << "Driver Id, Total Fee" << "\n";

        for(auto driver: driverLog) {
            dailyFeesLog << driver.second->id << "," << driver.second->getTotalFees() << "\n";
        }

        dailyFeesLog.close();
    }
    /*
     * Create a new csv spreadsheet and use the driver log to fetch total daily driver fees
     */
    void generateDriverDailyFees() {
        dailyFeesLog.open("daily_fees.csv");
        dailyFeesLog << "Driver Id, Daily Fee" << "\n";

        for(auto driver: driverLog) {
            dailyFeesLog << driver.second->id << "," << driver.second->getTotalDailyFees() << "\n";
        }

        dailyFeesLog.close();
    }
};

int main () {
    // Create a new instance of the checkpoint system
    CheckPointSystem *checkPointSystem = new CheckPointSystem();

    // Add sum dummy checkpoints passing in a checkpoint name and fee
    checkPointSystem->AddCheckPoint("JHB", 2);
    checkPointSystem->AddCheckPoint("PTA", 5);
    checkPointSystem->AddCheckPoint("SWT", 1);

    // Perform some dummy checkin against a driver with registration number 0 within 24hr period
    checkPointSystem->checkInDriver(0, "JHB", 1);
    checkPointSystem->checkInDriver(0, "PTA", 3);
    checkPointSystem->checkInDriver(0, "SWT", 12);

    // Perform some dummy checkin against a driver with registration number 0 above a 24hr period
    checkPointSystem->checkInDriver(0, "JHB", 25);
    checkPointSystem->checkInDriver(0, "JHB", 29);

    // Generate driver total daily fees along with overall fees for all check ins
    checkPointSystem->generateDriverDailyFees();
    checkPointSystem->generateTotalDriverFees();
    return 0;
}
