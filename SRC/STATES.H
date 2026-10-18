#ifndef STATES_H
#define STATES_H

#define INITIAL_CELL_COUNT  21
#define NEIGHBOR_COUNT      8

static const int initial_states[INITIAL_CELL_COUNT][2] = {
    {9, 182},
    {18, 182},
    {27, 182},
    {18, 173},
    {27, 173},
    {36, 173},
    {104, 50},
    {104, 59},
    {104, 68},
    {113, 77},
    {122, 86},
    {131, 86},
    {113, 41},
    {122, 32},
    {131, 32},
    {302, 41},
    {293, 41},
    {284, 41},
    {293, 50},
    {284, 50},
    {275, 50},
};

 static const int neighbor_states[NEIGHBOR_COUNT][2] = {
    {9, 0},
    {-9, 0},
    {-9, -9},
    {0, -9},
    {0, 9},
    {9, -9},
    {9, 9},
    {-9, 9},
}; 

#endif