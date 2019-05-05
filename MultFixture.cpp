/*
 *  MultFixture.cpp
 *  MultFixture_1
 *
 *  Created by PRoTeW on 30/09/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "MultFixture.h"
#include "GLWorldViewer.h"

bool contains( std::vector<int> v, int t )
{
	for ( size_t pid = 0; pid < v.size(); pid++)
		if( v[pid] == t )
			return true;
	return false;
}
int getAllAnglesSum( int actual, CROMOSSOME * crome )
{
	int sum = 0;
	for ( int cid = 0; cid < actual; cid++)
		sum += crome->parts_angle[cid];
	return sum;
}
float32 maximumRayOf( int actual, CROMOSSOME * crome )
{
	float32 maximum = crome->parts_ray[0];
	for ( int cid = 1; cid < actual; cid++)
		if( crome->parts_ray[cid] > maximum )
			maximum = crome->parts_ray[cid];
	return maximum;
}
float32 minimumRayOf( int actual, CROMOSSOME * crome )
{
	float32 minimum = crome->parts_ray[0];
	for ( int cid = 1; cid < actual; cid++)
		if( crome->parts_ray[cid] < minimum )
			minimum = crome->parts_ray[cid];
	return minimum;
}
CROMOSSOME * crossOver( CROMOSSOME * A, CROMOSSOME * B )
{
	CROMOSSOME * result = new CROMOSSOME;
	//
    result->max_ray = ( rand() % (int) ( abs( A->max_ray - B->max_ray ) + 1 ) ) + ( A->max_ray < B->max_ray ) ? A->max_ray : B->max_ray;
	//
	int choose_a = rand() % 2;
	result->number_of_wheels = ( choose_a ) ? A->number_of_wheels : B->number_of_wheels;
	int cid;
	//PARTES
	for ( cid = 0; cid < 8; cid++)
	{
		choose_a = rand() % 2;
		result->parts_ray[cid]			= ( choose_a ) ? A->parts_ray[cid]			: B->parts_ray[cid];
		choose_a = rand() % 2;
		result->parts_angle[cid]		= ( choose_a ) ? A->parts_angle[cid]		: B->parts_angle[cid];
		choose_a = rand() % 2;
		result->parts_density[cid]		= ( choose_a ) ? A->parts_density[cid]		: B->parts_density[cid];
		choose_a = rand() % 2;
		result->parts_restitution[cid]	= ( choose_a ) ? A->parts_restitution[cid]	: B->parts_restitution[cid];
		choose_a = rand() % 2;
		result->parts_friction[cid]		= ( choose_a ) ? A->parts_friction[cid]		: B->parts_friction[cid];
	}
	//AJEITANDO OS ANGULOS
	//
	int angles_sum = getAllAnglesSum( 8, result );
	while( angles_sum > 360 )
	{
		for ( cid = 0; cid < 8; cid++)
		{
			if( angles_sum > 360 && result->parts_angle[cid] > 1  )
				result->parts_angle[cid] -= 1;
			angles_sum = getAllAnglesSum( 8, result );
		}
	}
	while( angles_sum < 360 )
	{
		for ( cid = 0; cid < 8; cid++)
		{
			if( angles_sum < 360 && result->parts_angle[cid] < 360 )
				result->parts_angle[cid] += 1;
			angles_sum = getAllAnglesSum( 8, result );
		}
	}
	//
	//RODAS
	//
	//ENCONTRA AS PARTES COM RODAS COMUNS EM A E B
	for ( int wa = 0; wa < A->number_of_wheels; wa++)
		for ( int wb = 0; wb < B->number_of_wheels; wb++)
		{
			if( A->wheeled_parts[ wa ] == B->wheeled_parts[ wb ] && !contains( result->wheeled_parts, A->wheeled_parts[ wa ] ) )
				result->wheeled_parts.push_back( A->wheeled_parts[ wa ] );
		}
	//COMPLETA SE PRECISAR...
	int wid = 0;
	while( ( int ) result->wheeled_parts.size() < result->number_of_wheels )
	{
		if( ( int ) result->wheeled_parts.size() < A->number_of_wheels && ( int ) result->wheeled_parts.size() < B->number_of_wheels )
		{
			choose_a = rand() % 2;
			if( choose_a && !contains( result->wheeled_parts, A->wheeled_parts[ wid ] ) )
				result->wheeled_parts.push_back( A->wheeled_parts[ wid ] );
			else if( !choose_a && !contains( result->wheeled_parts, B->wheeled_parts[ wid ] ) )
				result->wheeled_parts.push_back( B->wheeled_parts[ wid ] );
		}
		else if( wid < A->number_of_wheels && !contains( result->wheeled_parts, A->wheeled_parts[ wid ] ) )
		{
			result->wheeled_parts.push_back( A->wheeled_parts[ wid ] );
		}
		else if( wid < B->number_of_wheels && !contains( result->wheeled_parts, B->wheeled_parts[ wid ] ) )
		{
			result->wheeled_parts.push_back( B->wheeled_parts[ wid ] );
		}
		if( wid >= ( ( A->wheeled_parts.size() > B->wheeled_parts.size() ) ? ( int ) A->wheeled_parts.size() : ( int ) B->wheeled_parts.size() ) )
			wid = 0;
		else
			wid++;
	}
	//DEFINE AS CARACTERISTICAS DAS RODAS
	for ( cid = 0; cid < result->number_of_wheels; cid++)
	{
		//
		choose_a = rand() % 2;
		if( choose_a )
		{
			int wheel_of_a = rand() % A->number_of_wheels;
			result->wheels_ray.push_back( A->wheels_ray[wheel_of_a] );
			result->wheels_density.push_back( A->wheels_density[wheel_of_a] );
			result->wheels_restitution.push_back( A->wheels_restitution[wheel_of_a] );
			result->wheels_friction.push_back( A->wheels_friction[wheel_of_a] );
			result->wheels_torque.push_back( A->wheels_torque[wheel_of_a] );
			result->wheels_velocity.push_back( A->wheels_velocity[wheel_of_a] );
		}
		else {
			int wheel_of_b = rand() % B->number_of_wheels;
			result->wheels_ray.push_back( B->wheels_ray[wheel_of_b] );
			result->wheels_density.push_back( B->wheels_density[wheel_of_b] );
			result->wheels_restitution.push_back( B->wheels_restitution[wheel_of_b] );
			result->wheels_friction.push_back( B->wheels_friction[wheel_of_b] );
			result->wheels_torque.push_back( B->wheels_torque[wheel_of_b] );
			result->wheels_velocity.push_back( B->wheels_velocity[wheel_of_b] );
		}
	}
	return result;	
}
CROMOSSOME * spontaniousGenerating( void )
{
	CROMOSSOME * adam = new CROMOSSOME;
	adam->max_ray				= ( rand() % 101 ) + 50;	// 50 a 150
	adam->number_of_wheels		= ( rand() % 5 ) + 2;		// 2 a 6
	int cid;
	//PARTES
	for ( cid = 0; cid < 8; cid++)
	{
		adam->parts_ray[cid] = rand() % ( int ) adam->max_ray + 1;	// 1 a max_ray
		//
		adam->parts_angle[cid] = ( rand() % 71 ) + 10;				// 10 a 80
		//
		adam->parts_density[cid] =		( float )( ( rand() % 10 ) + 1 ) / 10.0f;	// 0.1 a 1.0
		adam->parts_restitution[cid] =	( float )( ( rand() % 11 ) ) / 10.0f;		// 0.0 a 1.0
		adam->parts_friction[cid] =		( float )( ( rand() % 11 ) ) / 10.0f;		// 0.0 a 1.0
	}
	//AJEITANDO OS ANGULOS ( SOMA DEVE DAR 360 )
	//
	int angles_sum = getAllAnglesSum( 8, adam );
	while( angles_sum > 360 )
	{
		for ( cid = 0; cid < 8; cid++)
		{
			if( angles_sum > 360 && adam->parts_angle[cid] > 1  )
				adam->parts_angle[cid] -= 1;
			angles_sum = getAllAnglesSum( 8, adam );
		}
	}
	while( angles_sum < 360 )
	{
		for ( cid = 0; cid < 8; cid++)
		{
			if( angles_sum < 360 && adam->parts_angle[cid] < 353 )
				adam->parts_angle[cid] += 1;
			angles_sum = getAllAnglesSum( 8, adam );
		}
	}
	//
	//RODAS
	for ( cid = 0; cid < adam->number_of_wheels; cid++)
	{
		int rand_part = ( rand() % 8 ) + 1;
		while ( contains( adam->wheeled_parts, rand_part ) )
			rand_part = ( rand() % 8 ) + 1;
		adam->wheeled_parts.push_back( rand_part );
		//
		adam->wheels_ray.push_back( ( float32 )( ( rand() % ( int ) maximumRayOf( 8, adam ) ) / 2 ) + ( float32 )( minimumRayOf( 8, adam ) / 2 ) );
		adam->wheels_density.push_back( ( float32 )( ( rand() % 10 ) + 1 ) / 10 );	// 0.1 a 1.0
		adam->wheels_restitution.push_back( ( float32 )( ( rand() % 11 ) ) / 10 );	// 0.0 a 1.0
		adam->wheels_friction.push_back( ( float32 )( ( rand() % 11 ) ) / 10 );		// 0.0 a 1.0
		adam->wheels_velocity.push_back( -1 * ( ( rand() % 2001 ) + 100 ) );		// 100 a 2100
		adam->wheels_torque.push_back( ( ( rand() % ( adam->number_of_wheels * 10001 ) ) + ( -1 * adam->wheels_velocity[ cid ] + 1 ) ) ); // speed + 1 a 10001
	}
	return adam;
}
MultFixture :: MultFixture( int ID, QGLWidget * QGLW, b2Vec2 * P, float32 M, CROMOSSOME * A, CROMOSSOME * B )
: Object( ID, ( ( GLWorldViewer* ) QGLW )->getWorld(), P, new b2Vec2( M, M ) )
{
	ray_max = M;
	count_vertexes = 8;
	canvas = QGLW;
	//
	srand( time( NULL ) );
	//
	if( A && B )
		cromossome = crossOver( A, B );
	else if( A )
		cromossome = A;
	else if( B )
		cromossome = B;
	else
		cromossome = spontaniousGenerating();
	//
	body_def = new b2BodyDef;
	body_def->type = b2_dynamicBody;
	body_def->position.Set( position->x, position->y );
	body = world->CreateBody( body_def );
	//
	vertexes = ( b2Vec2* ) malloc( 3 * sizeof( b2Vec2 ) );
	//CENTRO
	vertexes[0].Set( position->x, position->y );
	//PRIMEIRO
	b2Vec2 * first = circlePoint( 0, new b2Vec2( position->x, position->y ), cromossome->parts_ray[0] );
	b2Vec2 * vertex = first;
	vertexes[1].Set( vertex->x, vertex->y );
	std::vector<b2Vec2*> axis;
	for ( int wheel_count = 0, i = 1; i < count_vertexes; i++) {
		
		vertex = circlePoint( ( ( getAllAnglesSum( i, cromossome ) ) * b2_pi ) / 180, new b2Vec2( position->x, position->y ), cromossome->parts_ray[i] );
		vertexes[2].Set( vertex->x, vertex->y );
		shape = new b2PolygonShape;
		shape->Set( vertexes, 3 );
		fixture_definition = new b2FixtureDef;
		fixture_definition->shape			= shape;
		fixture_definition->density			= cromossome->parts_density[i];
		fixture_definition->restitution		= cromossome->parts_restitution[i];
		fixture_definition->friction		= cromossome->parts_friction[i];
		fixture_definition->filter.groupIndex = -7;
		FixData * fix_data			= new FixData;
		fix_data->object_type		= BODY;
		fix_data->wheel_collision_count = 0;
		fix_data->body_collision_count  = 0;
		if ( contains( cromossome->wheeled_parts, i ) )
		{	
			fix_data->wheeled			= true;
			fix_data->wheel_ray			= cromossome->wheels_ray[wheel_count];
			fix_data->wheel_density		= cromossome->wheels_density[wheel_count];
			fix_data->wheel_restitution	= cromossome->wheels_restitution[wheel_count];
			fix_data->wheel_friction	= cromossome->wheels_friction[wheel_count];
			fix_data->wheel_torque		= cromossome->wheels_torque[wheel_count];
			fix_data->wheel_velocity	= cromossome->wheels_velocity[wheel_count];
			wheel_count++;
		}
		else
			fix_data->wheeled			= false;
		//
		fixture_definition->userData = fix_data;
		fixture = body->CreateFixture( fixture_definition );
		fixtures.push_back( fixture );
		vertexes[1].Set( vertexes[2].x, vertexes[2].y );
	}
	vertexes[2].Set( first->x, first->y );
	shape = new b2PolygonShape;
	shape->Set( vertexes, 3 );
	
	fixture_definition->shape		= shape;
	fixture_definition->density		= cromossome->parts_density[0];
	fixture_definition->restitution = cromossome->parts_restitution[0];
	fixture_definition->friction	= cromossome->parts_friction[0];
	fixture_definition->filter.groupIndex = -7;
	//
	FixData * fix_data			= new FixData;
	fix_data->object_type		= BODY;
	fix_data->wheel_collision_count = 0;
	fix_data->body_collision_count  = 0;
	if ( contains( cromossome->wheeled_parts, 8 ) )
	{	
		fix_data->wheeled			= true;
		fix_data->wheel_ray			= cromossome->wheels_ray[ cromossome->wheeled_parts.size()-1 ];
		fix_data->wheel_density		= cromossome->wheels_density[ cromossome->wheeled_parts.size()-1 ];
		fix_data->wheel_restitution	= cromossome->wheels_restitution[ cromossome->wheeled_parts.size()-1 ];
		fix_data->wheel_friction	= cromossome->wheels_friction[ cromossome->wheeled_parts.size()-1 ];
		fix_data->wheel_torque		= cromossome->wheels_torque[ cromossome->wheeled_parts.size()-1 ];
		fix_data->wheel_velocity	= cromossome->wheels_velocity[ cromossome->wheeled_parts.size()-1 ];
	}
	else
		fix_data->wheeled			= false;
	fixture_definition->userData = fix_data;
	//
	fixtures.push_back( body->CreateFixture( fixture_definition ) );
	createDisplayList();
}
b2Vec2 MultFixture ::  getCenter( void )
{
	return body->GetWorldCenter();
}
double MultFixture ::  getAngle( void )
{
	return body->GetAngle();
}
CROMOSSOME * MultFixture :: getCromossome( void )
{
	return cromossome;
}
std::list<b2Fixture*> MultFixture :: getFixtures( void )
{
	return fixtures;
}
void MultFixture :: createDisplayList( void )
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
void MultFixture :: fillDisplayList( void )
{
	for ( iter = fixtures.begin(); iter != fixtures.end(); iter++) {
		glColor3f( 0, 0, 0 );
		glBegin( GL_LINE_LOOP );
		for ( int fvid = 0; fvid < 3; fvid++ )
			glVertex2f( (( b2PolygonShape*) ( ( b2Fixture*) *iter )->GetShape() )->GetVertex( fvid ).x, (( b2PolygonShape*) ( ( b2Fixture*) *iter )->GetShape())->GetVertex( fvid ).y );
		glEnd();
		glColor4f( 0, 0, 0, ( ( b2Fixture*) *iter )->GetDensity() );
		glBegin( GL_POLYGON );
		for ( int fvid = 0; fvid < 3; fvid++ )
			glVertex2f( (( b2PolygonShape*) ( ( b2Fixture*) *iter )->GetShape())->GetVertex( fvid ).x, (( b2PolygonShape*) ( ( b2Fixture*) *iter )->GetShape())->GetVertex( fvid ).y );
		glEnd();
	}
}
void MultFixture :: draw( void )
{
	glPushMatrix();
	glTranslatef( body->GetPosition().x, body->GetPosition().y, 0.0 );
	glRotatef( ( body->GetAngle() / b2_pi ) * 180, 0, 0, 1);
	
	glCallList( display_list );
	
	glPopMatrix(); 
}
void MultFixture :: drawCommands( void )
{
	fillDisplayList(); 
}
MultFixture :: ~MultFixture( void ){}
