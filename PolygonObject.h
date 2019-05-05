/*
 *  PolygonObject.h
 *  FirstBox2D
 *
 *  Created by PRoTeW on 10/05/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef POLYGONOBJECT_H
#define POLYGONOBJECT_H

#include "Object.h"

class PolygonObject : public Object {
	GLuint display_list;
	b2Vec2 *vertexes;
	int32 count_vertexes;
	int32 line;
	
	b2PolygonShape * shape;
public:
	PolygonObject( int, b2World *, b2Fixture * );
	PolygonObject( int, b2World *, b2Vec2 *, int32, int32 );
	PolygonObject( int, b2World *, int32, b2Vec2* );
	PolygonObject( int, b2World *, b2Vec2 *, int32, b2Vec2* );
	int getCountVertex( void );
	b2Vec2* getVertexes( void );
	void createDisplayList( void );
	void fillDisplayList( void );
	void draw( void );
	~PolygonObject( void );
};

#endif