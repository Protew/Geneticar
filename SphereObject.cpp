/*
 *  SphereObject.cpp
 *  FirstBox2D_1
 *
 *  Created by PRoTeW on 11/05/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "SphereObject.h"

SphereObject :: SphereObject( int ID, b2World * W, b2Vec2 * P, float32 R, float32 D, float32 F, float32 REST )
: Object( ID, W, P, new b2Vec2( R, R ) )
{	
	ray = R;
	body_def = new b2BodyDef;
	body_def->type = b2_dynamicBody;
	//body_def->linearDamping = 10.0f;
	//body_def->angularDamping = 10.0f;
	//body_def->allowSleep = true;
	body_def->position.Set( position->x, position->y );
	body = world->CreateBody( body_def );
	
	circle_shape = new b2CircleShape;
	circle_shape->m_p.Set( body->GetPosition().x, body->GetPosition().y );
	circle_shape->m_radius = ray;
	
	fixture_definition = new b2FixtureDef;
	fixture_definition->shape = circle_shape;
	fixture_definition->density = D;
	fixture_definition->friction = F;
	fixture_definition->restitution = REST;
	fixture_definition->filter.groupIndex = -8;
	FixData * fix_data			= new FixData;
	fix_data->object_type		= WHEEL;
	fix_data->wheel_collision_count = 0;
	fix_data->body_collision_count  = 0;
	fixture_definition->userData = fix_data;
	fixture = body->CreateFixture( fixture_definition );
	createDisplayList();
}
void SphereObject :: fillDisplayList( void )
{
	//RAY
	b2Vec2 * vertex = circlePoint( ( 90 * b2_pi ) / 180, new b2Vec2( body->GetPosition().x, body->GetPosition().y ), ray );
	glColor4f( 0, 0, 0, 1 );
	glBegin( GL_LINES );
	glVertex2f( body->GetPosition().x, body->GetPosition().y );
	glVertex2f( vertex->x, vertex->y );
	glEnd();
	
	//PERIMETER
	glColor4f( 0, 0, 0, 1 );
	glBegin( GL_LINE_LOOP );
	for ( int i = 0; i < 359; i++) {
		float32 base_angle = ( i * b2_pi ) / 180;
		vertex = circlePoint( base_angle, new b2Vec2( body->GetPosition().x, body->GetPosition().y ), ray );
		glVertex2f( vertex->x, vertex->y );
	}
	glEnd();
		
	//INSIDE
	glColor4f( 0, 1, 0, 1 );
	glBegin( GL_POLYGON );
	for ( int i = 0; i < 359; i++) {
		float32 base_angle = ( i * b2_pi ) / 180;
		vertex = circlePoint( base_angle, new b2Vec2( body->GetPosition().x, body->GetPosition().y ), ray );
		glVertex2f( vertex->x, vertex->y );
	}
	glEnd();
}
void SphereObject :: createDisplayList( void )
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
void SphereObject :: draw( void )
{
	glPushMatrix();
	glTranslatef( body->GetPosition().x, body->GetPosition().y, 0.0 );
	glRotatef( ( body->GetAngle() / b2_pi ) * 180, 0, 0, 1 );

	glCallList( display_list );
	
	glPopMatrix(); 
}
void SphereObject :: drawCommands( void )
{
	glPushMatrix();
	glTranslatef( body->GetPosition().x, body->GetPosition().y, 0.0 );
	glRotatef( ( body->GetAngle() / b2_pi ) * 180, 0, 0, 1 );
	
	fillDisplayList();
	
	glPopMatrix(); 
}
SphereObject :: ~SphereObject( void ){}