/*
 *  GLWorldViewer.h
 *  3DChallenge
 *
 *  Created by PRoTeW on 13/12/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef GLWORLDVIEWER_H
#define GLWORLDVIEWER_H

#include <QtGui> 
#include <QTimer>
#include <QKeyEvent>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <iostream>

#include "GroundBlock.h"
#include "GeneticCar.h"
#include "CollisionDetect.h"

class GLWorldViewer : public QGLWidget {
	
	Q_OBJECT
	
private: 
	//PHYSICS
	//
	b2Vec2	* gravity;
	b2World * world;
	b2Vec2	* main_vector;
	float32 timeStep;
	int32 velocityIterations;
	int32 positionIterations;
	//
	float32 xview;
	float32 yview;
	//
	long clock;
	QTimer * timer;
	//
	int individue_id;
	long individual_clock;
	long time_stopped;
	QTimer * individual_timer;
	bool achieved;
	
	double width;
	double height;
	//
	CollisionDetect * collision_detector;
	//
	//OBJECTS
	GeneticCar  * individue;
	GroundBlock * base;
	float32 base_angle;
	std :: vector<GroundBlock*> bases;
	std :: list<Object*>::iterator population_it;
	std :: list<Object*> population;
	//
	//SIMULATION INFO
	//
	int generation;
	//
	// EVOLUTION
	//
	POPULATION_TYPE population_type;
	SELECTION_TYPE selection_type;
	int population_size;
	int generators_size;
	double mutation_tax;
	bool ressurection_allowed;
	bool cross_mutation;
	//
	// TARGET
	//
	TERRAIN_TYPE terrain_type;
	bool has_obstacles;
	double minimum_x_velocity;
	double maximum_test_interval;
	double initial_position;
	bool wheels_kick_discounted;
	bool body_crash_discounted;
	bool loop_count_discounted;
	//
	bool create_population;
	float32 x_initial, x_final;
	std :: vector<REGISTER*> past_historic;
	std :: vector<REGISTER*> actual_historic;
	std :: vector<REGISTER*> best_historic;
	//
	public slots:
	void createIndividue( void );
	void turn( void );
	void testIndividue( void );
	void startPauseTimer( void );

public: 
	GLWorldViewer( QWidget *, double, double );
	//
	//SETs
	void setPopulationType( QString );
	void setSelectionType( QString );
	void setPopulationSize( int );
	void setGeneratorsSize( int );
	void setMutationTax( double );
	void setAllowRessurectionState( int );
	void setCrossMutation( int );
	//
	void setTerrainType( QString );
	void setInitialPosition( double );
	void setMinXVelocity( double );
	void setMaxInterval( double );
	void setWheelsKickDiscount( int );
	void setCrashDiscount( int );
	void setLoopDiscount( int );
	void setHasObstacles( int );
	//
	void projection( void );
	void drawTemporary( void );
	void createTerrain( void );
	void createObject( b2Vec2* );
	Object* objectHited( b2Vec2 );
	//
	void displayBestCar( std :: vector<REGISTER*> );
	void displayParent( std :: vector<REGISTER*>, int, int );
	//
	//HANDLE HISTORICS
	//
	REGISTER * createRegister( void );
	//void addRegister( void );
	void saveRegister( std :: string, REGISTER* );
	void saveHistoric( std :: string, std :: vector<REGISTER*> );
	std :: vector<REGISTER*> loadHistoric( std :: string );
	//
	std :: vector<REGISTER*> orderHistoric( std :: vector<REGISTER*> );
	std :: vector<REGISTER*> includeInOrder( std :: vector<REGISTER*>, REGISTER * );
	//
	int roulette( std :: vector<REGISTER*> );
	int tourney( std :: vector<REGISTER*> );
	void addInSinglePopulation( void );
	void addInActualBestPopulation( void );
	//
	void showActualHistoric( void );
	void showBestHistoric( void );
	//
	void showCarInfo( CROMOSSOME * );
	//
	b2Vec2* QTtoOpenGl( b2Vec2* );
	b2Vec2* OpenGltoQT( b2Vec2* );
	b2Vec2* OpenGltoBox2d( b2Vec2* );
	b2Vec2* Box2dtoOpenGl( b2Vec2* );
	void mousePress( int, int, int ); 
	void mouseMotion( int, int );
	void createSpecieImages( void );
	void initClock( void );
	QTimer* getTimer( void );
	long getClock( void );
	b2World * getWorld( void );
	void stopSimulation( void );
	void startSimulation( void );
	//
	void start( void );
	bool stopCondition( void );
	//
	void addBase( void );
	//
	void mouseAction( QMouseEvent * );
	
protected: 
	void initializeGL( void ); 
	//void resizeGL( int, int ); 
	void paintGL( void ); 
	void keyPressEvent( QKeyEvent * );
	void mousePressEvent( QMouseEvent * ); 
	void mouseMoveEvent( QMouseEvent * ); 
	void mouseReleaseEvent( QMouseEvent * );
	//void mouseDoubleClickEvent(QMouseEvent *);
	void initComponents( void );
};

#endif
