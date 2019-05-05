/*
 *  GeneticCar.cpp
 *  GeneticCar_1
 *
 *  Created by PRoTeW on 30/09/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "GeneticCar.h"
#include "GLWorldViewer.h"

GeneticCar :: GeneticCar( int ID, QWidget * QGLW, b2Vec2 * P, float32 M, CROMOSSOME * A, CROMOSSOME * B )
: Object( ID, ( (GLWorldViewer*) QGLW )->getWorld(), P, new b2Vec2( M, M ) )
{
	ray_max = M;
	canvas = ( GLWorldViewer * )QGLW;
	canvas->makeCurrent();
	//
	main_body = new MultFixture( 0, canvas, position, ray_max, A, B );
	fixture = main_body->getFixture();
	body = main_body->getBody();
	
	fixtures = main_body->getFixtures();
	for ( iter = fixtures.begin(); iter != fixtures.end(); iter++) {
		FixData * data = (( FixData* )( ( b2Fixture* )*iter )->GetUserData() );
		if( data->wheeled )
		{
			b2Vec2 wheel_axis = (( b2PolygonShape*) ( ( b2Fixture*) *iter )->GetShape() )->GetVertex( 1 );
			wheels.push_back( new SphereObject( 0, world,  new b2Vec2( ( wheel_axis.x + main_body->getPosition().x ) / 2, ( wheel_axis.y + main_body->getPosition().y ) / 2 ), data->wheel_ray, data->wheel_density, data->wheel_friction, data->wheel_restitution ) );
			new RevolutionJoint( world, main_body, wheels[ wheels.size() - 1 ], data->wheel_torque, data->wheel_velocity );
		}
	}
}
int GeneticCar :: getWheelCollisionCount( void )
{
	int sum = 0;
	for ( size_t wid = 0; wid < wheels.size(); wid++ )
		sum += ( ( FixData * ) wheels[wid]->getFixture()->GetUserData() )->wheel_collision_count;
	return sum;
}
int GeneticCar :: getBodyCollisionCount( void )
{
	int sum = 0;
	for ( iter = fixtures.begin(); iter != fixtures.end(); iter++) {
		FixData * data = (( FixData* )( ( b2Fixture* )*iter )->GetUserData() );
		sum += data->body_collision_count;
	}
	return sum;
}
b2Vec2 GeneticCar :: getCarCenter( void )
{
	return main_body->getCenter();
}
double GeneticCar :: getCarAngle( void )
{
	return main_body->getAngle();
}
CROMOSSOME * GeneticCar :: getCromossome( void )
{
	return main_body->getCromossome();
}
float32 GeneticCar :: getMass( void )
{
	float32 total_mass = main_body->getBody()->GetMass();
	for ( size_t wid = 0; wid < wheels.size(); wid++ )
		total_mass += wheels[wid]->getBody()->GetMass();
	return total_mass;
}
MultFixture * GeneticCar :: getMainBody( void )
{
	return main_body;
}
b2Vec2 GeneticCar :: getVelocity( void )
{
	return body->GetLinearVelocity();
}
void GeneticCar :: draw( void )
{
	main_body->draw();
	
	for ( size_t wid = 0; wid < wheels.size(); wid++ )
		wheels[wid]->draw();
}
void GeneticCar :: drawCommands( void )
{
	main_body->drawCommands();
	
	for ( size_t wid = 0; wid < wheels.size(); wid++ )
		wheels[wid]->drawCommands();
}
void GeneticCar :: Destroy( void )
{
	main_body->Destroy();
	for ( size_t wid = 0; wid < wheels.size(); wid++ )
		wheels[wid]->Destroy();
}
GeneticCar :: ~GeneticCar( void ){}