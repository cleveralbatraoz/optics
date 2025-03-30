#pragma once

struct SingleParaxialCharacteristic {
    double front = 0.0;
    double back = 0.0;
};

struct ParaxialCharacteristics {
    SingleParaxialCharacteristic f;
    SingleParaxialCharacteristic sf;
    SingleParaxialCharacteristic sh;
};
