/*
 * generating braitenberg vehicles
 * Vehicle.h
 *
 * The MIT License (MIT)
 *
 * Copyright (c) 2019 Masahito H.
 *
 * referrence: Braitenberg Vehicles simulation
 * (Vehicles : Built with Processing and Processing.js - GitHub Pages)
 * Copyright (c) 2013 Steve Battle
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef Vehicle_h
#define Vehicle_h

#include "ofMain.h"
#include <climits>

class Vehicle{
public:
    Vehicle(float x, float y);
    
    static void setR(int r);
    static void setS(int s);
    static void setRange(float r);
    
    static void setRegionControl(bool b);
    static bool getRegionControl();
    static void setRegionCoordinate(int x, int y);
    static ofVec2f getRegionCoordinate();
    static void setRegionFlag(bool b);
    static bool getRegionFlag();
    ofVec2f region(ofVec2f vec);
    
    void drawing();
    void updateParameters(float straightSpeed, float turningForce, float agentRadious, float agentAngle, float regionRadious, float regionForce);
    void solve(vector<Vehicle> vec);
    
    void borders();
    
    float angleBetweenPoints(ofPoint a, ofPoint b);
    void setPosition(int x, int y);
    ofPoint getPosition();
    
private:
    static const int RATE = 60;
    static int radial;
    static int constSpeed;
    static float range;
    static float left;
    static float right;
    
    static ofVec2f regionCoordinate;
    static bool regionControl;
    static bool regionFlag;
    
    ofPoint position;
    ofVec2f velocity, acceleration;
    float angle, TAU;
    int rVehicle;
    
    int F;
    
    float straightSpeed;
    float turningForce;
    float agentRadious;
    float agentAngle;
    float regionRadious;
    float regionForce;
    
    int signFunction(float da);
};

#endif /* Vehicle_h */
