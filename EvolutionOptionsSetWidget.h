/*
 *  EvolutionOptionsSetWidget.h
 *  GenetiCar_R4
 *
 *  Created by PRoTeW on 07/03/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */


#ifndef EVOLUTIONOPTIONSSETWIDGET_H
#define EVOLUTIONOPTIONSSETWIDGET_H

#include <QtGui> 

#include <QGroupBox>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QComboBox>
#include <QCheckBox>

class EvolutionOptionsSetWidget : public QGroupBox
{
    Q_OBJECT
	
public:
	EvolutionOptionsSetWidget( QWidget * parent = 0 );
	void initWidgets( void );
	
	public slots:
	void populationSizeChanged( int );
	void generatorsSizeChanged( int );
	void mutationTaxChanged( double );
	void populationTypeChanged( QString );
	void selectionTypeChanged( QString );
	void allowRessurectionStateChanged( int );
	void crossMutationChanged( int );
	
private:

	QHBoxLayout			*	population_layout;
	QLabel				*	lbl_population_size;
	QSpinBox			*	sb_population_size;
	
	QHBoxLayout			*	generators_layout;
	QLabel				*	lbl_generators_size;
	QSpinBox			*	sb_generators_size;
	
	QCheckBox			*	chb_allow_ressurection;
	QCheckBox			*	chb_cross_mutation;
	//
	QHBoxLayout			*	mutation_layout;
	QLabel				*	lbl_mutation_tax;
	QDoubleSpinBox		*	dsb_mutation_tax;
	//
	QHBoxLayout			*	pop_type_layout;
	QLabel				*	lbl_population_type;
	QComboBox			*	cb_population_type;
	//
	QHBoxLayout			*	selection_type_layout;
	QLabel				*	lbl_selection_type;
	QComboBox			*	cb_selection_type;
	//
	QVBoxLayout			*	main_layout;
};

#endif
