/*
 * generating braitenberg vehicles
 * Vehicle.cpp
 *
 * The MIT License (MIT)
 *
 * Copyright (c) 2019 Masahito H.
 *
 * referrence: Braitenberg Vehicles simulation (Vehicles : Built with Processing and Processing.js - GitHub Pages)
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

#include "Vehicle.h"

const int Vehicle::RATE;
int Vehicle::radial;
int Vehicle::constSpeed;
float Vehicle::range;
float Vehicle::left;
float Vehicle::right;

ofVec2f Vehicle::regionCoordinate;
bool Vehicle::regionControl;
bool Vehicle::regionFlag;

Vehicle::Vehicle(float x, float y){
    TAU = TWO_PI;
    position = ofPoint(x, y);
    velocity = ofVec2f(constSpeed, constSpeed).normalize() * constSpeed;
    acceleration = ofVec2f(0, 0);
    rVehicle = 1;
    
    F = 300;
    angle = ofRandomf() * TWO_PI;
}



void Vehicle::drawing(){
    ofDrawCircle(position.x, position.y, rVehicle);
}

void Vehicle::updateParameters(float straightSpeed, float turningForce, float agentRadious, float agentAngle, float regionRadious, float regionForce){
    this -> straightSpeed = straightSpeed;
    this -> turningForce = turningForce;
    this -> agentRadious = agentRadious;
    this -> agentAngle = agentAngle;
    this -> regionRadious = regionRadious;
    this -> regionForce = regionForce;
}

void Vehicle::solve(vector<Vehicle> vec){
    Vehicle* leftV;
    Vehicle* rightV;
    float vDistL = FLT_MAX;
    float vDistR = FLT_MAX;
    
    for(Vehicle vehicle: vec){
        float dist = position.distance(vehicle.getPosition());
        
        if(agentAngle > 0 && agentAngle < left){
            if(dist < vDistL && dist != 0){
                vDistL = dist;
                leftV = &vehicle;
            }
        }
        else if(agentAngle <= 0 && agentAngle > right){
            if(dist < vDistR && dist != 0){
                vDistR = dist;
                rightV = &vehicle;
            }
        }
    }
    
    float dt = 1.0 / RATE;
    ofVec2f n = velocity;
    n.normalize();
    if(vDistL < agentRadious || vDistR < agentRadious){
        
        float a1 = 0;
        float a2 = 0;
        if(vDistL < agentRadious && vDistR >= agentRadious){
            a1 = fmod((TAU - angleBetweenPoints(position, leftV -> getPosition())), TAU);
        }
        else if(vDistL >= agentRadious && vDistR < agentRadious){
            a2 = fmod((TAU - angleBetweenPoints(position, rightV -> getPosition())), TAU);
        }
        else if(vDistL < agentRadious && vDistR < agentRadious){
            a1 = fmod((TAU - angleBetweenPoints(position, leftV -> getPosition())), TAU);
            a2 = fmod((TAU - angleBetweenPoints(position, rightV -> getPosition())), TAU);
        }
        
        float l = cos(a1 + a2 - angle - left) / 2 + .5;
        float r = cos(a1 + a2 - angle - right) / 2 + .5;
        
        float vl = l * F;
        float vr = r * F;
        
        float da = (vr - vl) / (2 * cos(range) * agentRadious);
        //float s = 1 - min(vDistL, vDistR) / agentRadious;
        
        angle = fmod(angle + da * dt, TAU);
        
        int sign = signFunction(da);
        
        acceleration.set(straightSpeed * turningForce * (-n.y) * -sign, straightSpeed * turningForce * n.x * -sign);
    }
    else{
        velocity.normalize() *= straightSpeed;
        acceleration.set(0, 0);
    }
    
    ///*
    if(Vehicle::regionControl && Vehicle::regionFlag){
        acceleration = region(acceleration);
    }
    //*/
    
    velocity += (acceleration * dt);
    position += (velocity * dt);
    borders();
    
    //////
    /*
    ofPoint v = ofPoint(0, 0);
    float a = fmod((TAU - angleBetweenPoints(position, v)), TAU);
    
    float l = cos(a - angle - left) / 2 + .5;
    float r = cos(a - angle - right) / 2 + .5;
    
    float vl = l * F;
    float vr = r * F;
    
    float dt = 1.0 / RATE;
    float da = (vr - vl) / (2 * w);
    float s = (vr + vl) / 2; //
    
    angle = fmod(angle + da * dt, TAU); //
    
    float dx = s * cos(-angle); //
    float dy = s * sin(-angle); //
    */

}


void Vehicle::borders(){
    if(position.x < -rVehicle) position.x = ofGetWidth() + rVehicle;
    if(position.y < -rVehicle) position.y = ofGetHeight() + rVehicle;
    if(position.x > ofGetWidth() + rVehicle) position.x = -rVehicle;
    if(position.y > ofGetHeight() + rVehicle) position.y = -rVehicle;
}


float Vehicle::angleBetweenPoints(ofPoint a, ofPoint b){
    ofPoint d = b - a;
    return atan2(d.y, d.x);
}

void Vehicle::setPosition(int x, int y){
    position.set(x, y);
}

ofPoint Vehicle::getPosition(){
    return position;
}



void Vehicle::setR(int r){
    radial = r;
}

void Vehicle::setS(int s){
    constSpeed = s;
}

void Vehicle::setRange(float r){
    range = r;
    left = r;
    right = -r;
}



void Vehicle::setRegionControl(bool b){
    regionControl = b;
}

bool Vehicle::getRegionControl(){
    return regionControl;
}

void Vehicle::setRegionCoordinate(int x, int y){
    regionCoordinate.set(x, y);
}

ofVec2f Vehicle::getRegionCoordinate(){
    return regionCoordinate;
}

void Vehicle::setRegionFlag(bool b){
    regionFlag = b;
}

bool Vehicle::getRegionFlag(){
    return regionFlag;
}

ofVec2f Vehicle::region(ofVec2f vec){
    float dist = position.distance(regionCoordinate);
    
    float dt = 1.0 / RATE;
    ofVec2f n = velocity;
    n.normalize();
    if(dist < regionRadious){
        float a = fmod((TAU - angleBetweenPoints(position, regionCoordinate)), TAU);
        
        float l = cos(a - angle - left) / 2 + .5;
        float r = cos(a - angle - right) / 2 + .5;
        
        float vl = r * F;
        float vr = l * F;
        
        float da = (vr - vl) / (2 * cos(range) * regionRadious);
        float s = 1 - dist / regionRadious;
        
        angle = fmod(angle + da * dt, TAU);
        int sign = signFunction(da);
        
        return ofVec2f(straightSpeed * regionForce * (-n.y) * sign * s, straightSpeed * regionForce * n.x * sign * s);
    }
    else{
        return vec;
    }
}



int Vehicle::signFunction(float da){
    if(da > 0){
        return 1;
    }
    else if(da == 0){
        return 0;
    }
    else if(da < 0){
        return -1;
    }
}
