/*
 *  CarInfoWidget.cpp
 *  GenetiCar_R4
 *
 *  Created by PRoTeW on 07/03/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "CarInfoWidget.h"


CarInfoWidget :: CarInfoWidget( QWidget * parent )
:QWidget( parent )
{
	initComponents();
	///setMinimumSize( 1200, 600 );
	//setFixedSize(sizeHint().width(), sizeHint().height());
}
//SETs
void CarInfoWidget :: setCar( GeneticCar * target )
{
	//IMAGE
	//
	car_viewer->setTarget( target );
	//
	//ID
	//
	if( target )
	{
		char temporary_str[10];
		//
		if( target->getId() == -666 )
			sprintf( temporary_str, "[MUTANTE]" );
		else
			sprintf( temporary_str, "[%d]", target->getId() );
		//
		lbl_car_id->setText( temporary_str );
	}
	else
		lbl_car_id->setText( "" );
}
void CarInfoWidget :: setDescription( QString * text )
{
	lbl_description->setText( *text );
}
void CarInfoWidget :: initComponents()
{
	car_description_layout = new QHBoxLayout;
	//
	main_layout		= new QVBoxLayout;
	//
	lbl_description = new QLabel( "TESTANDO" );
	car_description_layout->addWidget( lbl_description );
	//
	lbl_car_id = new QLabel;
	car_description_layout->addWidget( lbl_car_id );
	//
	car_viewer = new GLCarViewer( this, 200, 200 );
	main_layout->addLayout( car_description_layout );
	//
	main_layout->addWidget( car_viewer );
	//
	this->setLayout( main_layout );
}