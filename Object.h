/*
 *  Object.h
 *  FirstBox2D
 *
 *  Created by PRoTeW on 10/05/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef OBJECT_H
#define OBJECT_H

#include <QGLWidget>

#include "Box2D/Box2D.h"

enum OBJECT_TYPE{ NONE = 0, WHEEL = 1, BODY = 2, GROUND = 3 };
enum TERRAIN_TYPE{ PLAIN = 0, IRREGULAR = 1 };
enum POPULATION_TYPE{ SINGLE_POPULATION = 0, ACTUAL_BEST = 1 };
enum SELECTION_TYPE{ ALEATORY = 0, ROULETTE = 1, TOURNEY = 2 };

class Object {
protected:
	
	int object_id;
	
	float32 angle;
	
	b2World				*world;
	b2Vec2				*position;
	b2Vec2				*dimension;
	
	float32				density;
	float32				friction;
	
	b2BodyDef			*body_def;
	b2Body				*body;
	b2FixtureDef		*fixture_definition;
	
	b2Fixture			*fixture;
	
public:
	Object( int, b2World *, b2Vec2 *, b2Vec2 * );
	b2Vec2* circlePoint( float, b2Vec2 *, float );
	//
	virtual void draw( void );
	virtual void Destroy( void );
	virtual ~Object( void );
	
	//GETS
	int getId( void );
	b2World*	getWorld( void );
	b2Vec2		getPosition( void );
	b2Vec2*		getDimension( void );
	
	b2BodyDef*			GetBodyDef( void );
	b2Body*				getBody( void );
	b2Fixture*			getFixture( void );
	//SETS
	void setDensity( float32 );
	void setFriction( float32 );
	//GETS
	void setId( int );
};

class FixData {
public:
	bool wheeled;
	float32 wheel_ray;
	float32 wheel_density;
	float32 wheel_restitution;
	float32 wheel_friction;
	float32 wheel_torque;
	float32 wheel_velocity;
	int wheel_collision_count;
	int body_collision_count;
	OBJECT_TYPE object_type;
};

#endif
