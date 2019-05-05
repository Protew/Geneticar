/*
 *  GLWorldWidget.cpp
 *  3DChallenge
 *
 *  Created by PRoTeW on 13/12/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "GLWorldWidget.h"

GLWorldWidget :: GLWorldWidget( QWidget * parent )
:QWidget( parent )
{
	initComponents();
	///setMinimumSize( 1200, 600 );
	//setFixedSize(sizeHint().width(), sizeHint().height());
}
void GLWorldWidget :: setActualHistoricText( std::string text )
{
	//char str_clock_display[100];
	//sprintf( str_clock_display, "[%f, %f]", velocity.x, velocity.y );
	lbl_actual_historic->setText( text.c_str() );
}
void GLWorldWidget :: setBestHistoricText( std::string text )
{
	//char str_clock_display[100];
	//sprintf( str_clock_display, "[%f, %f]", velocity.x, velocity.y );
	lbl_best_historic->setText( text.c_str() );
}
void GLWorldWidget :: setFirstParent( GeneticCar * first )
{
	first_parent_car_info->setCar( first ); 
}
void GLWorldWidget :: setSecondParent( GeneticCar * second )
{
	second_parent_car_info->setCar( second ); 
}
void GLWorldWidget :: setBestCar( GeneticCar * best )
{
	best_car_info->setCar( best ); 
}
//GETS
GLWorldViewer * GLWorldWidget :: getWorldViewer( void )
{
	return world_viewer;
}
//SLOTS
void GLWorldWidget :: changeButtonText( void )
{
	if( btn_start_pause->text() == "START" )
		btn_start_pause->setText( "STOP" );
	else
		btn_start_pause->setText( "START" );
}
void GLWorldWidget :: initComponents()
{
	//
	//VIEWER LAYOUT
	viewer_layout	= new QVBoxLayout;
	//
	//CONTROL LAYOUT
	control_layout	= new QVBoxLayout;
	//
	//CARS DISPLAY LAYOUT
	cars_display_layout = new QHBoxLayout;
	//
	//VIEWER INFO LAYOUT
	car_info_layout	= new QVBoxLayout;
	//
	//VIEWER BUTTONS LAYOUT
	viewer_buttons_layout = new QHBoxLayout;
	//
	//HISTORIC INFO
	//
	lbl_actual_historic = new QLabel;
	car_info_layout->addWidget( lbl_actual_historic );
	lbl_best_historic = new QLabel;
	car_info_layout->addWidget( lbl_best_historic );
	//BEST CAR INFO
	best_car_info = new CarInfoWidget( this );
	best_car_info->setDescription( new QString( "BEST CAR" ) );
	cars_display_layout->addWidget( best_car_info );
	//BEST CAR INFO
	first_parent_car_info = new CarInfoWidget( this );
	first_parent_car_info->setDescription( new QString( "FIRST PARENT" ) );
	cars_display_layout->addWidget( first_parent_car_info );
	//BEST CAR INFO
	second_parent_car_info = new CarInfoWidget( this );
	second_parent_car_info->setDescription( new QString( "SECOND PARENT" ) );
	cars_display_layout->addWidget( second_parent_car_info );
	//WORLD VIEWER
	world_viewer	= new GLWorldViewer( this, 700, 400 );
	//CAR INFO
	//
	evolution_options_setter = new EvolutionOptionsSetWidget( this );
	control_layout->addWidget( evolution_options_setter );
	//
	target_options_setter = new TargetOptionsSetWidget( this );
	control_layout->addWidget( target_options_setter );
	//BTN CREATE CAR
	btn_skip_car	= new QPushButton( "CREATE CAR" );
	connect( btn_skip_car, SIGNAL( clicked() ), world_viewer, SLOT( createIndividue() ) );
	viewer_buttons_layout->addWidget( btn_skip_car );
	//
	//BTN START
	btn_start_pause	= new QPushButton( "START" );
	connect( btn_start_pause, SIGNAL( clicked() ), world_viewer, SLOT( startPauseTimer() ) );
	connect( btn_start_pause, SIGNAL( clicked() ), this, SLOT( changeButtonText() ) );
	viewer_buttons_layout->addWidget( btn_start_pause );
	//
	//
	viewer_layout->addLayout( cars_display_layout );
	viewer_layout->addWidget( world_viewer );
	viewer_layout->addLayout( viewer_buttons_layout );
	main_layout		= new QHBoxLayout;
	main_layout->addLayout( control_layout );
	main_layout->addLayout( viewer_layout );
	main_layout->addLayout( car_info_layout );
	this->setLayout( main_layout );
}