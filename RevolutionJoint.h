/*
 *  RevolutionJoint.h
 *  FirstBox2D_2
 *
 *  Created by PRoTeW on 11/05/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef REVOLUTIONJOINT_H
#define REVOLUTIONJOINT_H

#include "Object.h"

class RevolutionJoint {
protected:
	b2World				*world;
	float32				torque;
	float32				speed;
	
	b2RevoluteJointDef	joint_def;
	b2RevoluteJoint		*joint;
	
	b2Body				*body_a;
	b2Body				*body_b;
	
	b2Vec2				contact_point;
	
public:
	RevolutionJoint( b2World *, Object *, Object *, b2Vec2 * );
	RevolutionJoint( b2World *, Object *, Object *, float32, float32 );
	RevolutionJoint( b2World *, Object *, Object *, float32, float32, b2Vec2 * );
	RevolutionJoint( b2World * W, Object *BA, Object *BB, float32 T, float32 S, float32 LA, float32 UA, b2Vec2 *FP );
	void Destroy( void );
	//
	virtual void draw( void );
	virtual ~RevolutionJoint( void );
	
	//GETS
	b2World*	getWorld( void );
	
	b2Body*		getBodyA( void );
	b2Body*		getBodyB( void );
	//SETS
	void accelerate( float32 );
};

#endif