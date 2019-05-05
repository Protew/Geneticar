/*
 *  CollisionDetect.h
 *  FirstBox2D_4
 *
 *  Created by PRoTeW on 16/05/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef COLLISIONDETECT_H
#define COLLISIONDETECT_H

#include "Box2D.h"
#include "b2Settings.h"
#include "b2WorldCallbacks.h"
#include <iostream>
#include <cstring>
#include <vector>

struct b2Vec2;
struct b2Transform;

class CollisionDetect : public b2ContactListener
{
	b2World *world;
	int counter;
	
public:
	CollisionDetect( b2World * );
	void BeginContact(b2Contact* contact);
};

#endif
