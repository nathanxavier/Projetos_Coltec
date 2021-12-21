#pragma once

#include "BasicLinearAlgebra.h"
#include <chrono>

void predict(float accel);
void updateBaro(float altitude);
void updateGPS(float altitude);


float getKalmanPosition();
float getKalmanVelocity();
float getKalmanGravity();
float getKalmanBias();

