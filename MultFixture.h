/*
 *  MultFixture.h
 *  MultFixture_1
 *
 *  Created by PRoTeW on 30/09/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

/*
 *  MultFixture.h
 *  FirstBox2D_4
 *
 *  Created by PRoTeW on 15/05/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef MULTFIXTURE_H
#define MULTFIXTURE_H

#include "SphereObject.h"
#include "RevolutionJoint.h"

struct CROMOSSOME {
	int number_of_wheels;
	float32 max_ray;
	std::vector<int> wheeled_parts;
	float32 parts_ray[8];
	float32 parts_angle[8];
	float32 parts_density[8];
	float32 parts_restitution[8];
	float32 parts_friction[8];
	std::vector<float32> wheels_ray;
	std::vector<float32> wheels_density;
	std::vector<float32> wheels_restitution;
	std::vector<float32> wheels_friction;
	std::vector<float32> wheels_torque;
	std::vector<float32> wheels_velocity;
};

class MultFixture : public Object {
	GLuint display_list;
	b2Vec2 *vertexes;
	b2PolygonShape * shape;
	CROMOSSOME * cromossome;
	float32 ray_max;
	int32 count_vertexes;
	std :: list<b2Fixture*> :: iterator iter;
	std :: list<b2Fixture*> fixtures;
	//
	QGLWidget * canvas;
public:
	MultFixture( int, QGLWidget *, b2Vec2 *, float32, CROMOSSOME *, CROMOSSOME * );
	int containsAtId( b2Fixture * );
	b2Vec2 getCenter( void );
	double getAngle( void );
	std::list<b2Fixture*> getFixtures( void );
	void findFreeFixtures( void );
	CROMOSSOME * getCromossome( void );
	void createDisplayList( void );
	void fillDisplayList( void );
	void crash( void );
	void draw( void );
	void drawCommands( void );
	~MultFixture( void );
};

#endif