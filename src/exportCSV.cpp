/*
 * generating braitenberg vehicles
 * exportCSV.cpp
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

#include "exportCSV.h"

exportCSV::exportCSV(){
    variants = "object,no,x,y,frame";
    saving = false;
}


void exportCSV::write(string obj, int no, int x, int y, int frame){
    std::stringstream ss;
    
    ss << obj << ',' << no << ',' << x << ',' << y << ',' << frame;
    outputs.push_back(ss.str());
    
    cout << ss.str() << endl;
}

void exportCSV::download(){
    output.open("[output path]", ios::trunc); //set output path
    
    output << variants << std::endl;
    
    for(int i = 0; i < outputs.size(); i++){
        output << outputs[i] << std::endl;
    }
    
    output.close();
}

void exportCSV::reset(){
    outputs.clear();
}



void exportCSV::writeStart(int set){
    setFrame = set;
    startFrame = ofGetFrameNum();
    frame = 0;
    saving = true;
    
    cout << "write start" << endl;
}

void exportCSV::brunch(){
    if(saving){
        if(ofGetFrameNum() - startFrame <= setFrame){
            frame++;
        }
        else{
            download();
            reset();
            saving = false;
        }
    }
}

bool exportCSV::check(){
    return saving;
}

int exportCSV::getFrame(){
    return frame;
}
