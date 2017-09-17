//
//  vec3.h
//  editor
//
//  Created by Noah Keedle-Isack on 15/09/2017.
//  Copyright © 2017 Noah Keedle-Isack. All rights reserved.
//

#ifndef vec_h
#define vec_h

typdef struct {
    float x;
    float y;
    
    vec2() {
        this->x = 0;
        this->y = 0;
    }
    
    vec2(float x, float y) {
        this->x = x;
        this->y = y;
    }
} vec2;

typedef struct {
    float x;
    float y;
    float z;
    
    vec3() {
        this->x = 0;
        this->y = 0;
        this->z = 0;
    }
    
    vec3(float x, float y, float z) {
        this->x = x;
        this->y = y;
        this->z = z;
    }
} vec3;

typedef struct {
    float x;
    float y;
    float z;
    float w;
    
    vec4() {
        this->x = 0;
        this->y = 0;
        this->z = 0;
        this->w = 0;
    }
    
    vec4(float x, float y, float z, float w) {
        this->x = x;
        this->y = y;
        this->z = z;
        this->w = w;
    }
    
} vec4;

#endif
