//
//  OverlapTester.cpp
//  floppycock
//
//  Created by Stephen Gowen on 2/11/14.
//  Copyright (c) 2014 Techne Games. All rights reserved.
//

#include "pch.h"
#include "OverlapTester.h"
#include "Rectangle.h"
#include "Vector2D.h"

bool OverlapTester::doRectanglesOverlap(Rectangle &r1, Rectangle &r2)
{
    if (r1.getAngle() > 0)
    {
        float halfWidth = r1.getWidth() / 2;
        float halfHeight = r1.getHeight() / 2;
        
        float rad = DEGREES_TO_RADIANS(r1.getAngle());
        float cos = cosf(rad);
        float sin = sinf(rad);
        
        float x1 = -halfWidth * cos - (-halfHeight) * sin;
        float y1 = -halfWidth * sin + (-halfHeight) * cos;
        
        float x2 = halfWidth * cos - (-halfHeight) * sin;
        float y2 = halfWidth * sin + (-halfHeight) * cos;
        
        float x3 = halfWidth * cos - halfHeight * sin;
        float y3 = halfWidth * sin + halfHeight * cos;
        
        float x4 = -halfWidth * cos - halfHeight * sin;
        float y4 = -halfWidth * sin + halfHeight * cos;
        
        float x = r1.getLowerLeft().getX() + r1.getWidth() / 2;
        float y = r1.getLowerLeft().getY() + r1.getHeight() / 2;
        
        x1 += x;
        y1 += y;
        
        x2 += x;
        y2 += y;
        
        x3 += x;
        y3 += y;
        
        x4 += x;
        y4 += y;
        
        return isPointInRectangle(Vector2D(x1, y1), r2) || isPointInRectangle(Vector2D(x2, y2), r2) || isPointInRectangle(Vector2D(x3, y3), r2) || isPointInRectangle(Vector2D(x4, y4), r2);
    }
    else
    {
        return (r1.getLowerLeft().getX() < r2.getLowerLeft().getX() + r2.getWidth() && r1.getLowerLeft().getX() + r1.getWidth() > r2.getLowerLeft().getX() && r1.getLowerLeft().getY() < r2.getLowerLeft().getY() + r2.getHeight() && r1.getLowerLeft().getY() + r1.getHeight() > r2.getLowerLeft().getY());
    }
}

bool OverlapTester::isPointInRectangle(const Vector2D &p, Rectangle &r)
{
	return r.getLowerLeft().getX() <= p.getX() && r.getLowerLeft().getX() + r.getWidth() >= p.getX() && r.getLowerLeft().getY() <= p.getY() && r.getLowerLeft().getY() + r.getHeight() >= p.getY();
}

// Private Methods

OverlapTester::OverlapTester()
{
	// Hide Constructor
}