/*
 * generating braitenberg vehicles
 * ALife.cpp
 *
 * The MIT License (MIT)
 *
 * Copyright (c) 2019 Masahito H.
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

#include "ALife.h"

ALife::ALife(){
    ofSetVerticalSync(true);
    ofBackground(50);
    braitenberg = Braitenberg();
    for(int i = 0; i < 800; i++){
        braitenberg.addVehicle(Vehicle(ofRandomWidth(), ofRandomHeight()));
    }
    
    gui.setup();
    gui.add(straightSpeed.setup("straight speed", 100, 0, 100));
    gui.add(turningForce.setup("turning force", 15, 0, 30));
    gui.add(agentRadious.setup("agent radius", 10, 0, 500));
    gui.add(agentAngle.setup("agent angle", HALF_PI / 2, 0, PI));
    gui.add(regionRadious.setup("region radius", 300, 0, 500));
    gui.add(regionForce.setup("region force", 27.5, 0, 100));
}



void ALife::updating(){
    braitenberg.updating(straightSpeed, turningForce, agentRadious, agentAngle, regionRadious, regionForce);
}

void ALife::drawing(){
    braitenberg.drawing();
    
    gui.draw();
}

void ALife::mouseAction(int x, int y){
    
}

void ALife::keyAction(int key){
    braitenberg.keyAction(key);
}
