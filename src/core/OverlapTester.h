//
//  OverlapTester.h
//  floppycock
//
//  Created by Stephen Gowen on 2/11/14.
//  Copyright (c) 2014 Techne Games. All rights reserved.
//

#ifndef __floppycock__OverlapTester__
#define __floppycock__OverlapTester__

class Vector2D;
class Rectangle;

class OverlapTester
{
public:
    static bool doRectanglesOverlap(Rectangle &r1, Rectangle &r2);
    
	static bool isPointInRectangle(const Vector2D &p, Rectangle &r);

private:
    // Hide the Constructor
    OverlapTester();
};

#endif /* defined(__floppycock__OverlapTester__) */