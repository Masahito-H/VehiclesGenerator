/*
 * generating braitenberg vehicles
 * Braitenberg.cpp
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

#include "Braitenberg.h"

Braitenberg::Braitenberg(){
    vehicles = vector<Vehicle>();
    
    Vehicle::setR(150);
    Vehicle::setS(100);
    Vehicle::setRange(HALF_PI);
    
    regionCoordinate.set(0, 0);
    
    ///*++
    triPoints = vector<int>{15 * 30, 20 * 30, 25 * 30};
    triId = triPoints.size();
    triFrame = 0;
    triOffset = false;
    
    regionRandom = false;
    regionVisible = false;
    holding = false;
    regionCenter = false;
    triFlag = false; //++
}



void Braitenberg::updating(float straightSpeed, float turningForce, float agentRadious, float agentAngle, float regionRadious, float regionForce){
    if(regionRandom && !holding){
        if(((int)ofGetFrameNum()) % ((int)ofGetFrameRate() * 5) == 0){
            regionCoordinate.set(ofGetWidth() / 6 + ofRandomWidth() * 2 / 3, ofGetWidth() / 6 + ofRandomHeight() * 2 / 3);
            Vehicle::setRegionCoordinate(regionCoordinate.x, regionCoordinate.y);
        }
    }
    else if(regionCenter){
        regionCoordinate.set(ofGetWidth() / 2, ofGetHeight() / 2);
        Vehicle::setRegionCoordinate(regionCoordinate.x, regionCoordinate.y);
    }
    ///*++
    else if(triFlag){
        if((triFrame % triPoints[triId] == 0) && (triId < triPoints.size() - 1)){
            regionCoordinate.set(ofGetWidth() / 6 + ofRandomWidth() * 2 / 3, ofGetWidth() / 6 + ofRandomHeight() * 2 / 3);
            Vehicle::setRegionCoordinate(regionCoordinate.x, regionCoordinate.y);
            
            if(triOffset){
                triOffset = false;
            }
            else{
                triId++;
            }
            
            triFrame = 0;
        }
        else if((triId >= triPoints.size() - 1) && !csv.check()){
            triFlag = false;
        }
        
        triFrame++;
    }
    
    vector<Vehicle> past;
    copy(vehicles.begin(), vehicles.end(), back_inserter(past));
    
    for(int i = 0; i < vehicles.size(); i++){
        vehicles[i].updateParameters(straightSpeed, turningForce, agentRadious, agentAngle, regionRadious, regionForce);
        vehicles[i].solve(past);
        
        ofVec2f vec = vehicles[i].getPosition();
        if(csv.check()){
            csv.write("agent", i, vec.x, vec.y, csv.getFrame());
        }
    }
    
    if(csv.check()){
        ofVec2f co = Vehicle::getRegionCoordinate();
        csv.write("region", -1, co.x, co.y, csv.getFrame());
    }
    
    csv.brunch();
}

void Braitenberg::drawing(){
    if(regionVisible){
        ofSetColor(0, 255, 0);
        ofFill();
        ofDrawCircle(regionCoordinate.x, regionCoordinate.y, 5);
        
        ofSetColor(255);
    }
    
    for(int i = 0; i < vehicles.size(); i++){
        vehicles[i].drawing();
    }
}



void Braitenberg::addVehicle(Vehicle v){
    vehicles.push_back(v);
}



void Braitenberg::keyAction(int key){
    if(key == ' '){ //csv export.
        saveStart();
    }
    
    if(key == OF_KEY_TAB){ //all reset.
        Vehicle::setRegionControl(false);
        regionRandom = false;
        regionVisible = false;
        holding = false;
        regionCenter = false;
    }
    else if(key == 'g'){ //random mode.
        regionRandom = !regionRandom;
        Vehicle::setRegionControl(regionRandom);
        Vehicle::setRegionFlag(regionRandom);
        
        if(regionRandom){
            regionCenter = false;
            regionVisible = true;
        }
        else{
            regionVisible = false;
            holding = false;
        }
    }
    
    if(key == OF_KEY_SHIFT){ //visible.
        if(regionRandom || regionCenter || triFlag){ //++
            regionVisible = !regionVisible;
        }
    }
    
    if(regionRandom){ //manual trigger setting.
        if(key == 'h'){
            holding = !holding;
        }
        else if(key == 'f'){
            if(holding){
                regionCoordinate.set(ofGetWidth() / 6 + ofRandomWidth() * 2 / 3, ofGetHeight() / 6 + ofRandomHeight() * 2 / 3);
                Vehicle::setRegionCoordinate(regionCoordinate.x, regionCoordinate.y);
            }
        }
    }
    
    if(Vehicle::getRegionControl()){ //another mode.
        if(key == 'r'){
            Vehicle::setRegionFlag(!Vehicle::getRegionFlag());
        }
        
        if(key == 'c'){
            regionCenter = !regionCenter;
            regionRandom = regionCenter ? false : true;
        }
    }
}



void Braitenberg::saveStart(){
    ///*++
    regionRandom = false;
    holding = false;
    regionCenter = false;
    triFlag = true;
    
    ///*++
    std::random_shuffle(triPoints.begin(), triPoints.end());
    std::random_shuffle(triPoints.begin(), triPoints.end());
    triId = 0;
    triFrame = 0;
    triOffset = true;
    
    csv.writeStart(300);
}
