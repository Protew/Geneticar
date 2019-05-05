/*
 *  TargetOptionsSetWidget.cpp
 *  GenetiCar_R7
 *
 *  Created by PRoTeW on 09/03/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "TargetOptionsSetWidget.h"
#include "GLWorldWidget.h"

#include <QApplication>

TargetOptionsSetWidget::TargetOptionsSetWidget( QWidget * parent )
:QGroupBox( parent )
{	
	this->setTitle( tr("TARGET FUNCTION OPTIONS") );
	
	initWidgets();
	
	setFixedSize(sizeHint().width(), sizeHint().height());
}
void TargetOptionsSetWidget ::initWidgets( void )
{
	main_layout = new QVBoxLayout;
	//
	// TERRAIN TYPE
	//
	terrain_type_layout = new QHBoxLayout;
	lbl_terrain_type  = new QLabel( "TERRAIN TYPE");
	cb_terrain_type = new QComboBox( this );
	cb_terrain_type->clear();
	cb_terrain_type->insertItems(0, QStringList()
                                    << QApplication::translate("Form", "PLAIN", 0 )
                                    << QApplication::translate("Form", "IRREGULAR", 0 )
									);
	
	connect( cb_terrain_type, SIGNAL( currentIndexChanged( QString ) ), this, SLOT( terrainTypeChanged( QString ) ) );
	
	terrain_type_layout->addWidget( lbl_terrain_type );
	terrain_type_layout->addWidget( cb_terrain_type );
	//
	//
	//
	chb_has_obstacles = new QCheckBox( "HAS OBSTACLES" );
	chb_has_obstacles->setChecked( false );
	
	connect( chb_has_obstacles, SIGNAL( stateChanged(int) ), this, SLOT( hasObstaclesChanged( int ) ) );
	//
	//INITIAL POSITION
	//
	initial_position_layout = new QHBoxLayout;
	lbl_initial_position = new QLabel( "INITIAL POSITION");
	dsb_initial_position = new QDoubleSpinBox( this );
	dsb_initial_position->setValue( 0 );
	dsb_initial_position->setSingleStep( 0.1 );
	dsb_initial_position->setMinimum( -4.5 );
	dsb_initial_position->setMaximum( 4.5 );
	
	connect( dsb_initial_position, SIGNAL( valueChanged( double ) ), this, SLOT( initialPositionChanged( double ) ) );
	
	initial_position_layout->addWidget( lbl_initial_position );
	initial_position_layout->addWidget( dsb_initial_position );
	//
	//MINIMUM X VELOCITY
	//
	QHBoxLayout				*	minimum_x_velocity_layout;
	QLabel					*	lbl_minimum_x_velocity;
	QDoubleSpinBox			*	dsb_minimum_x_velocity;
	
	minimum_x_velocity_layout = new QHBoxLayout;
	lbl_minimum_x_velocity = new QLabel( "MIN X VELOCITY");
	dsb_minimum_x_velocity = new QDoubleSpinBox( this );
	dsb_minimum_x_velocity->setValue( 1 );
	dsb_minimum_x_velocity->setSingleStep( 0.1 );
	dsb_minimum_x_velocity->setMinimum( 0.5 );
	
	connect( dsb_minimum_x_velocity, SIGNAL( valueChanged( double ) ), this, SLOT( minXVelocityChanged( double ) ) );
	
	minimum_x_velocity_layout->addWidget( lbl_minimum_x_velocity );
	minimum_x_velocity_layout->addWidget( dsb_minimum_x_velocity );
	//
	//MAXIMUM TEST INTERVAL
	//
	maximum_test_interval_layout = new QHBoxLayout;
	lbl_maximum_test_interval = new QLabel( "MAX TEST INTERVAL");
	//
	dsb_maximum_test_interval = new QDoubleSpinBox( this );
	dsb_maximum_test_interval->setValue( 1.5 );
	dsb_maximum_test_interval->setSingleStep( 0.1 );
	dsb_maximum_test_interval->setMinimum( 0.1 );
	
	connect( dsb_maximum_test_interval, SIGNAL( valueChanged( double ) ), this, SLOT( maxTestIntervalChanged( double ) ) );

	maximum_test_interval_layout->addWidget( lbl_maximum_test_interval );
	maximum_test_interval_layout->addWidget( dsb_maximum_test_interval );
	
	//
	//WHEELS KICK DISCOUNT
	//
	chb_wheels_kick_discounted = new QCheckBox( "WHEELS KICK DISCOUNT" );
	chb_wheels_kick_discounted->setChecked( true );
	
	connect( chb_wheels_kick_discounted, SIGNAL( stateChanged(int) ), this, SLOT( wheelsKickDiscountChanged( int ) ) );
	//
	//BODY CRASH DISCOUNT
	//
	chb_body_crash_discounted = new QCheckBox( "BODY HIT DISCOUNT" );
	chb_body_crash_discounted->setChecked( true );
	
	connect( chb_body_crash_discounted, SIGNAL( stateChanged(int) ), this, SLOT( bodyCrashDiscountChanged( int ) ) );
	//
	//LOOP COUNT DISCOUNT
	//
	chb_loop_count_discounted = new QCheckBox( "LOOPS DISCOUNT" );
	chb_loop_count_discounted->setChecked( true );
	
	connect( chb_loop_count_discounted, SIGNAL( stateChanged(int) ), this, SLOT( loopCountDiscountChanged( int ) ) );

	main_layout->addLayout( terrain_type_layout );
	main_layout->addWidget( chb_has_obstacles );
	main_layout->addLayout( initial_position_layout );
	main_layout->addLayout( minimum_x_velocity_layout );
	main_layout->addLayout( maximum_test_interval_layout );
	main_layout->addWidget( chb_wheels_kick_discounted );
	main_layout->addWidget( chb_body_crash_discounted );
	main_layout->addWidget( chb_loop_count_discounted );
	
	this->setLayout( main_layout );
	
}
void TargetOptionsSetWidget :: terrainTypeChanged( QString option )
{
	( ( GLWorldWidget * )nativeParentWidget() )->getWorldViewer()->setTerrainType( option );
}
void TargetOptionsSetWidget :: hasObstaclesChanged( int value )
{
	( ( GLWorldWidget * )nativeParentWidget() )->getWorldViewer()->setHasObstacles( value );
}
void TargetOptionsSetWidget :: initialPositionChanged( double value )
{
	( ( GLWorldWidget * )nativeParentWidget() )->getWorldViewer()->setInitialPosition( value );
}
void TargetOptionsSetWidget :: minXVelocityChanged( double value )
{
	( ( GLWorldWidget * )nativeParentWidget() )->getWorldViewer()->setMinXVelocity( value );
}
void TargetOptionsSetWidget :: maxTestIntervalChanged( double value )
{
	( ( GLWorldWidget * )nativeParentWidget() )->getWorldViewer()->setMaxInterval( value );
}
void TargetOptionsSetWidget :: wheelsKickDiscountChanged( int value )
{
	( ( GLWorldWidget * )nativeParentWidget() )->getWorldViewer()->setWheelsKickDiscount( value );
}
void TargetOptionsSetWidget :: bodyCrashDiscountChanged( int value )
{
	( ( GLWorldWidget * )nativeParentWidget() )->getWorldViewer()->setCrashDiscount( value );
}
void TargetOptionsSetWidget :: loopCountDiscountChanged( int value )
{
	( ( GLWorldWidget * )nativeParentWidget() )->getWorldViewer()->setLoopDiscount( value );
}
