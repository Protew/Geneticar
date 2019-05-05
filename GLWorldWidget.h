/*
 *  GLWorldWidget.h
 *  3DChallenge
 *
 *  Created by PRoTeW on 15/12/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef GLWORLDWIDGET_H
#define GLWORLDWIDGET_H

#include <QPushButton>
#include <QLabel>

#include "GLWorldViewer.h"
#include "CarInfoWidget.h"
#include "EvolutionOptionsSetWidget.h"
#include "TargetOptionsSetWidget.h"

class GLWorldWidget : public QWidget
{
	Q_OBJECT
	
public:
	GLWorldWidget( QWidget* );
	void initComponents( void );
	//SETS
	void setActualHistoricText( std::string );
	void setBestHistoricText( std::string );

	void createObject( float32, float32 );
	void setFirstParent( GeneticCar * );
	void setSecondParent( GeneticCar * );
	void setBestCar( GeneticCar * );
	//GETs
	GLWorldViewer * getWorldViewer( void );
	//
	public slots:
	void changeButtonText( void );
	
private:
	
	//CARS VIEWER
	//
	//WORLD VIEWER
	GLWorldViewer	*	world_viewer;
	//CARS INFO VIEWERS
	CarInfoWidget	*	best_car_info;
	CarInfoWidget	*	first_parent_car_info;
	CarInfoWidget	*	second_parent_car_info;
	//
	//EVOLUTION OPTIONS SETTER
	//
	EvolutionOptionsSetWidget	* evolution_options_setter;
	//
	//TARGET OPTIONS SETTER
	//
	TargetOptionsSetWidget	* target_options_setter;
	//
	QPushButton		*	btn_start_pause;
	QPushButton		*	btn_skip_car;
	QLabel			*	lbl_actual_historic;
	QLabel			*	lbl_best_historic;
	
	//LAYOUTS
	QVBoxLayout		*	viewer_layout;
	QHBoxLayout		*	viewer_buttons_layout;
	QHBoxLayout		*	cars_display_layout;
	QVBoxLayout		*	control_layout;
	QVBoxLayout		*	car_info_layout;
	
	QHBoxLayout		*	main_layout;
};

#endif
