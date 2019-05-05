/*
 *  GeneticCar.h
 *  FirstBox2D_5
 *
 *  Created by PRoTeW on 17/05/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef GENETICCAR_H
#define GENETICCAR_H

#include "MultFixture.h"
#include "SphereObject.h"

struct REGISTER {
	int register_id;
	float32 x_distance;
	long time_spent;
	float32 score;
	CROMOSSOME * specie;
};

class GeneticCar : public Object {
	QGLWidget * canvas;
	float32	ray_max;
	MultFixture * main_body;
	std :: list<b2Fixture*> :: iterator iter;
	std::list<b2Fixture*> fixtures;
	std :: vector<SphereObject*> wheels;
public:
	GeneticCar( int, QWidget *, b2Vec2 *, float32, CROMOSSOME*, CROMOSSOME* );
	CROMOSSOME * getCromossome( void );
	//
	//INFO
	//
	b2Vec2 getVelocity( void );
	//
	//GETS
	int getWheelCollisionCount( void );
	int getBodyCollisionCount( void );
	b2Vec2 getCarCenter( void );
	double getCarAngle( void );
	float32 getMass( void );
	MultFixture * getMainBody( void );
	void draw( void );
	void drawCommands( void );
	void Destroy( void );
	~GeneticCar( void );
};

#endif