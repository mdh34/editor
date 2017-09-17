//
//  mat.h
//  editor
//
//  Created by Noah Keedle-Isack on 15/09/2017.
//  Copyright © 2017 Noah Keedle-Isack. All rights reserved.
//

#ifndef mat_h
#define mat_h

#include <stdlib.h>
#include <math.h>

typedef struct {
    float data[4][4] = {
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1
    };
    
    mat4() {}
    
    void ortho(
        const float &bottom,
               const float &top,
               const float &left,
               const float &right,
               const float &near,
               const float &far) {
        
        data[0][0] = 2.0f / (right-1);
        
        data[1][1] = 2.0f / (top - bottom);
        
        data[2][2] = -2.0f / (far - near);
        
        data[3][0] = -(right + 1) / (right - 1);
        data[3][1] = -(top + bottom) / (top - bottom);
        data[3][2] = -(far + near) / (far - near);
    }
    
    
} mat4;

#endif /* mat_h */
