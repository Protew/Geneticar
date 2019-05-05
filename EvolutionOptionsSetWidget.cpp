
/*
 *  EvolutionOptionsSetWidget.cpp
 *  PDBQuickViewer_04
 *
 *  Created by PRoTeW on 27/11/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "EvolutionOptionsSetWidget.h"
#include "GLWorldWidget.h"

#include <QApplication>

EvolutionOptionsSetWidget::EvolutionOptionsSetWidget( QWidget * parent )
:QGroupBox( parent )
{	
	this->setTitle( tr("EVOLUTION OPTIONS") );
	
	initWidgets();
	
	setFixedSize(sizeHint().width(), sizeHint().height());
}
void EvolutionOptionsSetWidget ::initWidgets( void )
{
	main_layout = new QVBoxLayout;
	//
	//POPULATION TYPE
	//
	pop_type_layout = new QHBoxLayout;
	lbl_population_type = new QLabel( "POPULATION TYPE");
	//
	cb_population_type = new QComboBox( this );
	cb_population_type->clear();
	cb_population_type->insertItems(0, QStringList()
                                      << QApplication::translate( "Form", "SINGLE", 0 )
                                      << QApplication::translate("Form", "ACTUAL & BEST", 0 )
									  );
	
	connect( cb_population_type, SIGNAL( currentIndexChanged( QString ) ), this, SLOT( populationTypeChanged( QString ) ) );
	
	pop_type_layout->addWidget( lbl_population_type );
	pop_type_layout->addWidget( cb_population_type );
	//
	//SELECTION TYPE
	//
	selection_type_layout = new QHBoxLayout;
	lbl_selection_type = new QLabel( "SELECTION TYPE");
	//
	cb_selection_type = new QComboBox( this );
	cb_selection_type->clear();
	cb_selection_type->insertItems(0, QStringList()
                                    << QApplication::translate("Form", "ALEATORY", 0 )
                                    << QApplication::translate("Form", "ROULETTE", 0 )
                                    << QApplication::translate("Form", "TOURNEY", 0 )
									);
	
	connect( cb_selection_type, SIGNAL( currentIndexChanged( QString ) ), this, SLOT( selectionTypeChanged( QString ) ) );
	
	selection_type_layout->addWidget( lbl_selection_type );
	selection_type_layout->addWidget( cb_selection_type );
	//
	// POPULATION SIZE
	//
	population_layout = new QHBoxLayout;
	lbl_population_size = new QLabel( "POPULATION SIZE");
	//
	sb_population_size = new QSpinBox( this );
	sb_population_size->setValue( 10 );
	sb_population_size->setSingleStep( 1 );
	sb_population_size->setMinimum( 2 );
	sb_population_size->setMaximum( 200 );
	
	connect( sb_population_size, SIGNAL( valueChanged( int ) ), this, SLOT( populationSizeChanged( int ) ) );
	
	population_layout->addWidget( lbl_population_size );
	population_layout->addWidget( sb_population_size );
	//
	// GENERATORS SIZE
	//
	generators_layout = new QHBoxLayout;
	lbl_generators_size = new QLabel( "GENERATORS SIZE");
	//
	sb_generators_size = new QSpinBox( this );
	sb_generators_size->setValue( 5 );
	sb_generators_size->setSingleStep( 1 );
	sb_generators_size->setMinimum( 2 );
	sb_generators_size->setMaximum( 10 );
	
	connect( sb_generators_size, SIGNAL( valueChanged( int ) ), this, SLOT( generatorsSizeChanged( int ) ) );
	
	generators_layout->addWidget( lbl_generators_size );
	generators_layout->addWidget( sb_generators_size );
	//
	// MUTATION TAX
	//
	mutation_layout = new QHBoxLayout;
	lbl_mutation_tax = new QLabel( "MUTATION TAX");
	//
	dsb_mutation_tax = new QDoubleSpinBox( this );
	dsb_mutation_tax->setValue( 10.00 );
	dsb_mutation_tax->setSingleStep( 0.01 );
	dsb_mutation_tax->setMinimum( 0.00 );
	dsb_mutation_tax->setMaximum( 100.00 );
	
	connect( dsb_mutation_tax, SIGNAL( valueChanged( double ) ), this, SLOT( mutationTaxChanged( double ) ) );
	
	mutation_layout->addWidget( lbl_mutation_tax );
	mutation_layout->addWidget( dsb_mutation_tax );
	//
	//ALLOW RESSURECTION
	//
	chb_allow_ressurection = new QCheckBox( "ALLOW RESSURECTION" );
	chb_allow_ressurection->setChecked( false );
	connect( chb_allow_ressurection, SIGNAL( stateChanged(int) ), this, SLOT( allowRessurectionStateChanged( int ) ) );
	//
	//CROSS MUTATION
	//
	chb_cross_mutation = new QCheckBox( "CROSS MUTATION" );
	chb_cross_mutation->setChecked( true );
	connect( chb_cross_mutation, SIGNAL( stateChanged(int) ), this, SLOT( crossMutationChanged( int ) ) );
	//
	main_layout->addLayout( pop_type_layout );
	main_layout->addLayout( selection_type_layout );
	main_layout->addLayout( population_layout );
	main_layout->addLayout( generators_layout );
	main_layout->addLayout( mutation_layout );
	main_layout->addWidget( chb_allow_ressurection );
	main_layout->addWidget( chb_cross_mutation );
	
	this->setLayout( main_layout );
	
}
void EvolutionOptionsSetWidget :: populationSizeChanged( int value )
{
	( ( GLWorldWidget * )nativeParentWidget() )->getWorldViewer()->setPopulationSize( value );
	sb_generators_size->setMaximum( value );
}
void EvolutionOptionsSetWidget :: generatorsSizeChanged( int value )
{
	( ( GLWorldWidget * )nativeParentWidget() )->getWorldViewer()->setGeneratorsSize( value );
	//std :: cout << value << std :: endl;
}
void EvolutionOptionsSetWidget :: mutationTaxChanged( double value )
{
	( ( GLWorldWidget * )nativeParentWidget() )->getWorldViewer()->setMutationTax( value );
}
void EvolutionOptionsSetWidget :: populationTypeChanged( QString option )
{
	( ( GLWorldWidget * )nativeParentWidget() )->getWorldViewer()->setPopulationType( option );
}
void EvolutionOptionsSetWidget :: selectionTypeChanged( QString option )
{
	( ( GLWorldWidget * )nativeParentWidget() )->getWorldViewer()->setSelectionType( option );
}
void EvolutionOptionsSetWidget :: allowRessurectionStateChanged( int value )
{
	( ( GLWorldWidget * )nativeParentWidget() )->getWorldViewer()->setAllowRessurectionState( value );
}
void EvolutionOptionsSetWidget :: crossMutationChanged( int value )
{
	( ( GLWorldWidget * )nativeParentWidget() )->getWorldViewer()->setCrossMutation( value );
	//std :: cout << value << std :: endl;
}
