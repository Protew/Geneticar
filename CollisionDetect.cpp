/*
 *  CollisionDetect.cpp
 *  FirstBox2D_4
 *
 *  Created by PRoTeW on 16/05/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "CollisionDetect.h"
#include "GroundBlock.h"
#include <typeinfo>
#include <cmath>
//#include <QSound>

CollisionDetect :: CollisionDetect( b2World* W )
{
	counter = 0;
	world = W;
    //crash = new QSound( "Pop.aiff" );
	
}
void CollisionDetect :: BeginContact( b2Contact* contact )
{
	FixData *data_a = ((FixData*)contact->GetFixtureA()->GetUserData() );
	FixData *data_b = ((FixData*)contact->GetFixtureB()->GetUserData() );
	
	if( data_a && data_b )
	{
		if( data_a->object_type == WHEEL && data_b->object_type == GROUND )
		{
			data_a->wheel_collision_count++;
			//std :: cout << ++counter << "RODA NO CHAO" << std :: endl;
		}
		if( data_b->object_type == WHEEL && data_a->object_type == GROUND )
		{
			data_b->wheel_collision_count++;
			//std :: cout << ++counter << "CHAO NA RODA" << std :: endl;
		}
		if( data_a->object_type == BODY && data_b->object_type == GROUND )
		{
			data_a->body_collision_count++;
			//std :: cout << ++counter << "CORPO NO CHAO" << std :: endl;
		}
		if( data_b->object_type == BODY && data_a->object_type == GROUND )
		{
			data_b->body_collision_count++;
			//std :: cout << ++counter << "CHAO NO CORPO" << std :: endl;
		}
	}
}
