/*
 *  PolygonObject.cpp
 *  FirstBox2D
 *
 *  Created by PRoTeW on 10/05/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "PolygonObject.h"

PolygonObject :: PolygonObject( int ID, b2World * W, b2Fixture * F )
: Object( ID, W, new b2Vec2( 0, 0 ), new b2Vec2( 0, 0 ) )
{
	line = 0;
	
	body_def->type = b2_dynamicBody;
	body_def->position.Set( F->GetBody()->GetPosition().x, F->GetBody()->GetPosition().y );
	body_def->angle = F->GetBody()->GetAngle();
	body = world->CreateBody( body_def );
	
	count_vertexes = ( ( b2PolygonShape* ) F->GetShape() )->GetVertexCount();
	vertexes = ( b2Vec2* ) malloc( count_vertexes * sizeof( b2Vec2 ) );
	for ( int i = 0; i < count_vertexes; i++)
		vertexes[i] = ( ( b2PolygonShape* ) F->GetShape() )->GetVertex(i);
	
	fixture_definition->shape = F->GetShape();
	fixture_definition->density = F->GetDensity();
	fixture_definition->friction = F->GetFriction();
	fixture_definition->userData = F->GetUserData();
	fixture = body->CreateFixture( fixture_definition );
	createDisplayList();
}
PolygonObject :: PolygonObject( int ID, b2World * W, b2Vec2 * P, int32 L, int32 V )
: Object( ID, W, P, new b2Vec2( L, L ) )
{
	count_vertexes = V;
	line = L;
	
	body_def->type = b2_dynamicBody;
	body_def->position.Set( position->x, position->y );
	body = world->CreateBody( body_def );

	vertexes = ( b2Vec2* ) malloc( count_vertexes * sizeof( b2Vec2 ) );
	for ( int i = 0; i < count_vertexes; i++) {
		b2Vec2 * vertex = circlePoint( ( ( i * ( 360 / count_vertexes ) * b2_pi ) ) / 180, new b2Vec2( body->GetPosition().x, body->GetPosition().y ), line );
		vertexes[i].Set( vertex->x, vertex->y );
	}
	shape = new b2PolygonShape;
	shape->Set( vertexes, count_vertexes );
	
	fixture_definition->shape = shape;
	fixture_definition->density = 1.0f;
	fixture_definition->friction = 1.0f;
	fixture_definition->userData = new FixData;
	//((FixData*)fixture_definition->userData)->is_part = false;
	//((FixData*)fixture_definition->userData)->owner = this;
	//fixture = body->CreateFixture( &fixture_definition );
	createDisplayList();
}
PolygonObject :: PolygonObject( int ID, b2World * W, int32 CV, b2Vec2* V )
: Object( ID, W, new b2Vec2( 0, 0 ), 0 )
{
	count_vertexes = CV;
	line = 0;
	vertexes = V;
	
	body_def->type = b2_dynamicBody;
	b2Vec2 *center = new b2Vec2( 0, 0 );
	for ( int i = 0; i < count_vertexes; i++ ) {
		center->x += vertexes[i].x;
		center->y += vertexes[i].y;
	}
	center->x /= count_vertexes;
	center->y /= count_vertexes;
	body_def->position = *center;
	body = world->CreateBody( body_def );
	
	shape = new b2PolygonShape;
	shape->Set( vertexes, count_vertexes );
	
	fixture_definition->shape = shape;
	fixture_definition->density = 1.0f;
	fixture_definition->friction = 1.0f;
	fixture_definition->userData = new FixData;
	//((FixData*)fixture_definition->userData)->is_part = false;
	//((FixData*)fixture_definition->userData)->owner = this;
	//fixture = body->CreateFixture( &fixture_definition );
	createDisplayList();
}
PolygonObject :: PolygonObject( int ID, b2World * W, b2Vec2 * P, int32 CV, b2Vec2* V )
: Object( ID, W, P, 0 )
{
	count_vertexes = CV;
	line = 0;
	vertexes = V;
	
	body_def->type = b2_dynamicBody;
	body_def->position.Set( position->x, position->y );
	body = world->CreateBody( body_def );
	
	shape = new b2PolygonShape;
	shape->Set( vertexes, count_vertexes );
	
	fixture_definition->shape = shape;
	fixture_definition->density = 1.0f;
	fixture_definition->friction = 1.0f;
	fixture_definition->userData = new FixData;
	//((FixData*)fixture_definition->userData)->is_part = false;
	//((FixData*)fixture_definition->userData)->owner = this;
	//fixture = body->CreateFixture( &fixture_definition );
	createDisplayList();
}
void PolygonObject :: createDisplayList( void )
{
	//PEGA UM NUMERO DE LISTA DISPONÍVEL
	display_list = glGenLists( 1 );
	//INVOCA A LISTA
	glNewList( display_list, GL_COMPILE );
	//PREENCHE COM OS VÉRTICES
	fillDisplayList();
	//FIM DA CRIAÇÃO 
	glEndList();
}
int PolygonObject :: getCountVertex( void )
{
	return count_vertexes;
}
b2Vec2* PolygonObject :: getVertexes( void )
{
	return vertexes;
}
void PolygonObject :: fillDisplayList( void )
{
	glColor3f( 0, 0, 0 );
	glBegin( GL_LINE_LOOP );
	for ( int i = 0; i < count_vertexes; i++) {
		glVertex2f( vertexes[i].x, vertexes[i].y );
	}
	glEnd();
	glColor3f( 0.5, 0.5, 0.5 );
	glBegin( GL_POLYGON );
	for ( int i = 0; i < count_vertexes; i++) {
		glVertex2f( vertexes[i].x, vertexes[i].y );
	}
	glEnd();
}
void PolygonObject :: draw( void )
{
	glPushMatrix();
	glTranslatef( body->GetPosition().x, body->GetPosition().y, 0.0 );
	glRotatef( ( body->GetAngle() / b2_pi ) * 180, 0, 0, 1);
	
	glCallList( display_list );
	
	glPopMatrix(); 
}
PolygonObject :: ~PolygonObject( void ){}