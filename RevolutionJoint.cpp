/*
 *  RevolutionJoint.cpp
 *  FirstBox2D_2
 *
 *  Created by PRoTeW on 11/05/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "RevolutionJoint.h"

RevolutionJoint :: RevolutionJoint( b2World * W, Object *BA, Object *BB, b2Vec2 * FP )
{
	world = W;
	torque = 0;
	speed = 0;
	
	body_a = BA->getBody();
	body_b = BB->getBody();
	
	joint_def.Initialize( body_a, body_b, *FP );
	joint_def.collideConnected = false;
	//joint_def.lowerAngle = 0 * b2_pi; // -90 degrees
	//joint_def.upperAngle = 2 * b2_pi; // 45 degrees
	joint_def.enableLimit = true;
	
	//joint_def.enableMotor = true;
	//joint_def.maxMotorTorque = torque;;
	//joint_def.motorSpeed = speed;
	
	joint = ( b2RevoluteJoint* ) world->CreateJoint( &joint_def );
}
RevolutionJoint :: RevolutionJoint( b2World * W, Object *BA, Object *BB, float32 T, float32 S )
{
	world = W;
	torque = T;
	speed = S;
	
	body_a = BA->getBody();
	body_b = BB->getBody();
	
	joint_def.Initialize( body_a, body_b, body_b->GetWorldCenter());
	joint_def.collideConnected = false;
	//joint_def.lowerAngle = 0 * b2_pi; // -90 degrees
	//joint_def.upperAngle = 2 * b2_pi; // 45 degrees
	//joint_def.enableLimit = true;
	
	joint_def.enableMotor = true;
	joint_def.maxMotorTorque = torque;;
	joint_def.motorSpeed = speed;
	
	joint = ( b2RevoluteJoint* ) world->CreateJoint( &joint_def );
}
RevolutionJoint :: RevolutionJoint( b2World * W, Object *BA, Object *BB, float32 T, float32 S, b2Vec2 *FP )
{
	world = W;
	torque = T;
	speed = S;
	
	body_a = BA->getBody();
	body_b = BB->getBody();
	
	joint_def.Initialize( body_a, body_b, *FP );
	joint_def.collideConnected = false;
	//joint_def.lowerAngle = 0 * b2_pi; // -90 degrees
	//joint_def.upperAngle = 2 * b2_pi; // 45 degrees
	//joint_def.enableLimit = true;
	
	joint_def.enableMotor = true;
	joint_def.maxMotorTorque = torque;;
	joint_def.motorSpeed = speed;
	
	joint = ( b2RevoluteJoint* ) world->CreateJoint( &joint_def );
}
RevolutionJoint :: RevolutionJoint( b2World * W, Object *BA, Object *BB, float32 T, float32 S, float32 LA, float32 UA, b2Vec2 *FP )
{
	world = W;
	torque = T;
	speed = S;
	
	body_a = BA->getBody();
	body_b = BB->getBody();
	
	joint_def.Initialize( body_a, body_b, *FP );
	joint_def.collideConnected = false;
	joint_def.lowerAngle = LA; // -90 degrees
	joint_def.upperAngle = UA; // 45 degrees
	joint_def.enableLimit = true;
	
	joint_def.enableMotor = true;
	joint_def.maxMotorTorque = torque;;
	joint_def.motorSpeed = speed;
	
	joint = ( b2RevoluteJoint* ) world->CreateJoint( &joint_def );
}
//SETS
void RevolutionJoint :: accelerate( float32 speed )
{
	joint->SetMotorSpeed( joint->GetMotorSpeed() + speed );
}
//GETS
b2World* RevolutionJoint :: getWorld( void )
{
	return world;
}
b2Body* RevolutionJoint :: getBodyA( void )
{
	return body_a;
}
b2Body* RevolutionJoint :: getBodyB( void )
{
	return body_b;
}
void RevolutionJoint :: Destroy( void )
{
	world->DestroyJoint( joint );
}
void RevolutionJoint :: draw( void )
{
	glColor3f( 0, 1, 0 );
	glBegin( GL_LINES );
	glVertex2f( joint->GetAnchorA().x, joint->GetAnchorA().y );
	glVertex2f( joint->GetAnchorB().x, joint->GetAnchorB().y );
	glEnd();
}
RevolutionJoint :: ~RevolutionJoint( void ){}