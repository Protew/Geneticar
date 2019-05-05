/*
 *  GLWorldViewer.cpp
 *  3DChallenge
 *
 *  Created by PRoTeW on 13/12/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "GLWorldViewer.h"
#include "GLWorldWidget.h"

b2Vec2* GLWorldViewer ::QTtoOpenGl( b2Vec2* coord )
{
	//TRANSFORMA COORD QT -> OpenGl
	float32 wx = coord->x;
	float32 vxmax = (float32) xview + width;
	float32 vxmin = (float32) xview;
	float32 wxmax = (float32) width;
	float32 wxmin = (float32) 0;
	//
	float32 wy = coord->y;
	float32 vymax = (float32) yview;
	float32 vymin = (float32) yview + height;
	float32 wymax = (float32) height;
	float32 wymin = (float32) 0;
	
	return new b2Vec2( ( ( vxmax - vxmin )/( wxmax - wxmin ) ) * ( wx - wxmin ) + vxmin, ( ( vymax - vymin )/( wymax - wymin ) ) * ( wy - wymin ) + vymin );
}
b2Vec2* GLWorldViewer :: OpenGltoQT( b2Vec2* coord )
{
	//TRANSFORMA OpenGl -> COORD QT
	float32 wx = coord->x;
	float32 vxmax = (float32) width;
	float32 vxmin = (float32) 0;
	float32 wxmax = (float32) xview + width;
	float32 wxmin = (float32) xview;
	//
	float32 wy = coord->y;
	float32 vymax = (float32) height;
	float32 vymin = (float32) 0;
	float32 wymax = (float32) yview;
	float32 wymin = (float32) yview + height;
	
	return new b2Vec2( ( ( vxmax - vxmin )/( wxmax - wxmin ) ) * ( wx - wxmin ) + vxmin, ( ( vymax - vymin )/( wymax - wymin ) ) * ( wy - wymin ) + vymin );
}
b2Vec2* GLWorldViewer ::OpenGltoBox2d( b2Vec2* coord ) 
{
	//TRANSFORMA COORD OpenGl -> BOX2D
	float32 wx = coord->x;
	float32 vxmax = (float32) width/2;
	float32 vxmin = (float32) 0;
	float32 wxmax = (float32) width;
	float32 wxmin = (float32) 0;
	//
	float32 wy = coord->y;
	float32 vymax = (float32) 0;
	float32 vymin = (float32) height/2;
	float32 wymax = (float32) 0;
	float32 wymin = (float32) height;
	
	return new b2Vec2( ( ( vxmax - vxmin )/( wxmax - wxmin ) ) * ( wx - wxmin ) + vxmin, ( ( vymax - vymin )/( wymax - wymin ) ) * ( wy - wymin ) + vymin );
}
b2Vec2* GLWorldViewer :: Box2dtoOpenGl( b2Vec2* coord ) 
{
	//TRANSFORMA COORD BOX2D -> OpenGl
	float32 wx = coord->x;
	float32 vxmax = (float32) width;
	float32 vxmin = (float32) 0;
	float32 wxmax = (float32) width/2;
	float32 wxmin = (float32) 0;
	//
	float32 wy = coord->y;
	float32 vymax = (float32) 0;
	float32 vymin = (float32) height;
	float32 wymax = (float32) 0;
	float32 wymin = (float32) height/2;
	
	return new b2Vec2( ( ( vxmax - vxmin )/( wxmax - wxmin ) ) * ( wx - wxmin ) + vxmin, ( ( vymax - vymin )/( wymax - wymin ) ) * ( wy - wymin ) + vymin );
}
GLWorldViewer :: GLWorldViewer( QWidget *parent, double W, double H ) 
: QGLWidget( parent )
{	
	width = W;
	height = H;
	//
	xview = yview = 0;
	//
	timeStep = 1.0f / 60.0f;
	velocityIterations = 6;
	positionIterations = 5;
	//
	main_vector = new b2Vec2( 0.0f, 0.0f );
	//
	gravity = new b2Vec2( 0.0f, -10.0f );
	world = new b2World( *gravity, true );
	//
	collision_detector = new CollisionDetect( world );
	world->SetContactListener( collision_detector );
	//
	timer = new QTimer;
	connect( timer, SIGNAL( timeout() ), this, SLOT( turn() ) );
	//
	individual_timer = new QTimer;
	connect( individual_timer, SIGNAL( timeout() ), this, SLOT( testIndividue() ) );
	//
	setFormat( QGLFormat( QGL::DoubleBuffer | QGL::DepthBuffer ) );
	setFixedSize( width, height );
	//
	population_type = SINGLE_POPULATION;
	selection_type = ALEATORY;
	population_size = 10;
	generators_size = 5;
	mutation_tax	= 10.0;
	ressurection_allowed = false;
	cross_mutation = true;
	//
	//IMPLEMENTAR NO TARGET FUNCTION SETTER
	//
	terrain_type = PLAIN;
	has_obstacles = false;
	initial_position = width;
	minimum_x_velocity = 1.0;
	maximum_test_interval = 1.5;
	wheels_kick_discounted = true;
	body_crash_discounted = true;
	loop_count_discounted = true;
	//
	start();
	setFocus();
}
void GLWorldViewer :: start( void )
{
	clock = 0;
	xview = yview = 0;
	//timer->start();
	create_population = true;
	past_historic.clear();
	actual_historic.clear();
	best_historic.clear();
	/*create_population = false;
	 actual_historic = loadHistoric( "/Users/PRoTeW/Desktop/best_cars.txt" );
	 orderHistoric();
	 best_historic = actual_historic;
	 population_size = best_historic.size();
	 std :: cout << "B SIZE " << best_historic.size() << std :: endl;
	 actual_historic.clear();*/
	generation = 0;
	individue_id = 0;
}
//SETS
void GLWorldViewer :: setPopulationType( QString type_name )
{
	if( type_name == "SINGLE" )
	{
		if( best_historic.size() )
		{
			int diff = abs( ( int ) ( actual_historic.size() - best_historic.size() ) );
			if( actual_historic.size() < best_historic.size() )
			{
				for ( int i = 0; i < diff; i++ ) {
					REGISTER * reg = new REGISTER;
					reg->register_id = individue_id;
					reg->x_distance = abs( x_final - x_initial );
					reg->time_spent = individual_clock;
					reg->score = 0;
					reg->specie = individue->getCromossome();
					actual_historic.push_back( reg );
				}
			}
			else if( actual_historic.size() > best_historic.size() )
			{
				std :: vector<REGISTER*> aux_historic = actual_historic;
				actual_historic.clear();
				for ( int i = 0; i < population_size; i++ ) {
					actual_historic.push_back( aux_historic[i] );
				}
			}
			for ( size_t rid = 0; rid < actual_historic.size(); rid++ )
				actual_historic = includeInOrder( actual_historic, best_historic[ rid ] );
		}
		population_type = SINGLE_POPULATION;
		( ( GLWorldWidget* ) parent() )->setBestHistoricText( "" );
		showActualHistoric();
	}
	if( type_name == "ACTUAL & BEST" )
		population_type = ACTUAL_BEST;
}
void GLWorldViewer :: setSelectionType( QString type_name )
{
	if( type_name == "ALEATORY" )
		selection_type = ALEATORY;
	if( type_name == "ROULETTE" )
		selection_type = ROULETTE;
	if( type_name == "TOURNEY" )
		selection_type = TOURNEY;
}
void GLWorldViewer :: setPopulationSize( int value )
{
	population_size = value;
}
void GLWorldViewer ::  setGeneratorsSize( int value )
{
	generators_size = value;
}
void GLWorldViewer :: setMutationTax( double value )
{
	mutation_tax = value;
}
void GLWorldViewer :: setAllowRessurectionState( int value )
{
	if( value )
		ressurection_allowed = true;
	else {
		ressurection_allowed = false;
	}
}
void GLWorldViewer :: setCrossMutation( int value )
{
	if( value )
		cross_mutation = true;
	else {
		cross_mutation = false;
	}
}
void GLWorldViewer :: setTerrainType( QString type_name )
{
	if( type_name == "PLAIN" )
		terrain_type = PLAIN;
	if( type_name == "IRREGULAR" )
		terrain_type = IRREGULAR;
	
	createTerrain();
}
void GLWorldViewer :: setHasObstacles( int value )
{
	has_obstacles = value;
}
void GLWorldViewer :: setInitialPosition( double value )
{
	initial_position = value * width;
}
void GLWorldViewer :: setMinXVelocity( double value )
{
	minimum_x_velocity = value;
}
void GLWorldViewer :: setMaxInterval( double value )
{
	maximum_test_interval = value;
}
void GLWorldViewer :: setWheelsKickDiscount( int value )
{
	wheels_kick_discounted = value;
}
void GLWorldViewer :: setCrashDiscount( int value )
{
	body_crash_discounted = value;
}
void GLWorldViewer :: setLoopDiscount( int value )
{
	loop_count_discounted = value;
}
void GLWorldViewer :: turn( void )
{	
	world->Step( timeStep, velocityIterations, positionIterations );
	world->ClearForces();
	
	if( individue )
	{
		xview = individue->getBody()->GetWorldCenter().x - width/2;
		yview = individue->getBody()->GetWorldCenter().y - height/2;
		//std :: cout << "height " << individue->getCarAngle() << std :: endl;
		projection();
	}
	updateGL();
}
bool GLWorldViewer :: stopCondition( void )
{
	if( generation >= 50 )
		return true; 
	for ( size_t bid_1 = 0; bid_1 < best_historic.size() - 1; bid_1++ )
		for ( size_t bid_2 = bid_1 + 1; bid_2 < best_historic.size(); bid_2++ )
			if( fabs( best_historic[ bid_1 ]->score - best_historic[ bid_2 ]->score ) > 0.01 )
				return false;
	return true;
}
void GLWorldViewer :: testIndividue( void )
{
	if( individue )
	{
		if( individue->getVelocity().x < minimum_x_velocity )
			time_stopped++;
		else
			time_stopped = 0;
		
		double wheels_discount = fabs( individue->getWheelCollisionCount() * 0.001 );
		double body_discount = fabs( individue->getBodyCollisionCount() * 0.01 );
		double loop_discount = fabs( ( individue->getCarAngle() / 6 ) * 0.05 );
		
		if ( wheels_discount + body_discount + loop_discount >= 1 )
			createIndividue();
		if( time_stopped > 1500 || individual_clock > ( maximum_test_interval * 60000 )  )
			createIndividue();
		
		if( individue->getCarCenter().x > 9.5 * width )
		{
			achieved = true;
			createIndividue();
		}
		//
		individual_clock++;
	}
}
std :: vector<REGISTER*> GLWorldViewer :: orderHistoric( std :: vector<REGISTER*> historic )
{
	std :: vector<REGISTER*> auxiliar_vector = historic;
	for ( size_t h1 = 0; h1 < auxiliar_vector.size() - 1; h1++ )
		for ( size_t h2 = h1; h2 < auxiliar_vector.size(); h2++ )
			if( auxiliar_vector[h1]->score < auxiliar_vector[h2]->score )
			{
				REGISTER * aux = auxiliar_vector[h1];
				auxiliar_vector[h1] = auxiliar_vector[h2];
				auxiliar_vector[h2] = aux;
			}
	return auxiliar_vector;
}
std :: vector<REGISTER*> GLWorldViewer :: includeInOrder( std :: vector<REGISTER*> where, REGISTER * who )
{
	std :: vector<REGISTER*> auxiliar_vector = where;
	bool found = false;
	int founded_id;
	for ( size_t best_id = 0; best_id < auxiliar_vector.size() && !found; best_id++ )
		if( who->score > auxiliar_vector[ best_id ]->score )
		{
			found = true;
			founded_id = ( int ) best_id;
		}
	if( found )
	{
		for ( int id = auxiliar_vector.size() - 1; id >= founded_id + 1; id-- )
			auxiliar_vector[ id ] = auxiliar_vector[ id - 1 ];
		auxiliar_vector[ founded_id ] = who;
	}
	return auxiliar_vector;
}
REGISTER * GLWorldViewer :: createRegister( void )
{
	REGISTER * reg = new REGISTER;
	reg->register_id = individue_id;
	reg->x_distance = abs( individue->getCarCenter().x - x_initial );
	reg->time_spent = individual_clock;
	//
	double wheels_discount = individue->getWheelCollisionCount() * 0.001;
	double body_discount = individue->getBodyCollisionCount() * 0.01;
	double loop_discount = fabs( ( individue->getCarAngle() / 6 ) * 0.05 );
	//
	//std :: cout << "W " << wheels_discount << "\nB " << body_discount << "\nL " << loop_discount << std :: endl;
	//
	// CALCULO DO ESCORE
	//
	reg->score = 1 + ( ( float32 ) reg->x_distance / reg->time_spent );
	//
	if( wheels_kick_discounted )
		reg->score -= wheels_discount;
	if( body_crash_discounted )
		reg->score -= body_discount;
	if( loop_count_discounted )
		reg->score -= loop_discount;
	
	if( reg->score < 0 )
		reg->score = 0;
	//
	reg->specie = individue->getCromossome();
	
	return reg;
}
void GLWorldViewer :: displayBestCar( std :: vector<REGISTER*> where )
{
	if( where.size() )
	{
		GeneticCar * aux = new GeneticCar( where[ 0 ]->register_id, this, new b2Vec2( 0, 0 ), 100, where[ 0 ]->specie, NULL );
		( ( GLWorldWidget * ) parent() )->setBestCar( aux );
		aux->Destroy();
	}
}
void GLWorldViewer :: addInSinglePopulation( void )
{
	//
	REGISTER * reg = createRegister();
	
	if( ( int ) actual_historic.size() >= population_size )
	{	
		create_population = false;
		actual_historic = includeInOrder( actual_historic, reg );
	}
	else {
		actual_historic.push_back( reg );
		actual_historic = orderHistoric( actual_historic );
	}
	//
	showActualHistoric();
	//
	//
	displayBestCar( actual_historic );
}
void GLWorldViewer :: addInActualBestPopulation( void )
{
	REGISTER * reg = createRegister();
	
	if( ( int ) actual_historic.size() >= population_size )
	{	
		generation++;
		create_population = false;
		//
		if( best_historic.size() )
		{
			int diff = abs( ( int ) ( actual_historic.size() - best_historic.size() ) );
			//
			if( best_historic.size() < actual_historic.size() )
			{
				for ( int i = 0; i < diff; i++ ) {
					reg = new REGISTER;
					reg->register_id = individue_id;
					reg->x_distance = abs( x_final - x_initial );
					reg->time_spent = individual_clock;
					reg->score = 0;
					reg->specie = individue->getCromossome();
					best_historic.push_back( reg );
				}
			}
			else if( best_historic.size() > actual_historic.size() )
			{
				std :: vector<REGISTER*> aux_historic = best_historic;
				best_historic.clear();
				for ( int i = 0; i < population_size; i++ ) {
					best_historic.push_back( aux_historic[i] );
				}
			}
			for ( size_t rid = 0; rid < actual_historic.size(); rid++ )
				best_historic = includeInOrder( best_historic, actual_historic[ rid ] );
		}
		else
			best_historic = actual_historic;
		actual_historic.clear();
		displayBestCar( best_historic );
	}
	
	actual_historic.push_back( reg );
	actual_historic = orderHistoric( actual_historic );
	//
	if( create_population )
		displayBestCar( actual_historic );
	//
	//
	showBestHistoric();
	showActualHistoric();
	//
}
int GLWorldViewer :: tourney( std :: vector<REGISTER*> contesters )
{
	//VETOR DE COMPETIDORES DO TORNEIO
	std :: vector<REGISTER*> players;
	//ENQUANTO O VETOR NAO ESTIVER COMPLETO...
	while( ( int )players.size() < generators_size )
	{ 
		//PEGA UM INDIVIDUO ALEATORIO ENTRE TODA A POPULACAO E INCLUI NO VETOR DE COMPETIDORES
		int aleatory = rand() % ( int ) contesters.size();
		bool found = false;
		for ( size_t pid = 0; pid < players.size() && !found; pid++ )
			if( players[ pid ]->register_id == contesters[ aleatory ]->register_id )
				found = true;
		if( !found )
			players.push_back( contesters[ aleatory ] );
	}
	//DEFINE O DE MELHOR PONTUACAO
	players = orderHistoric( players );
	for ( size_t pop_id = 0; pop_id < contesters.size(); pop_id++ )
		if( contesters[ pop_id ]->register_id == players[ 0 ]->register_id )
			return ( int ) pop_id;
	
	std :: cout << "TORNEIO ESCOLHEU NINGUEM" << std :: endl;
	return -1;
}
int GLWorldViewer :: roulette( std :: vector<REGISTER*> players )
{
	int sum = 0;
	//
	int actual_real_size = ( generators_size > ( int )players.size() ) ? ( int ) players.size() : generators_size;
	//
	for ( int pid = 0; pid < actual_real_size; pid++ )
		sum += ( players[ pid ]->score * 10000 );
	
	if( sum )
	{
		int aleatory = rand() % sum;
		
		int partial_sum = 0;
		for ( int pid = 0; pid < actual_real_size; pid++ )
		{
			if( aleatory >= partial_sum && aleatory < ( partial_sum + ( players[ pid ]->score * 10000 ) ) )
				return pid;
			partial_sum += players[ pid ]->score * 10000 ;
		}
	}
	else {
		std :: cout << "ROLETA LOUCA" << std :: endl;
		return rand() % players.size();
	}
	std :: cout << "ROLETA ESCOLHEU NINGUEM" << std :: endl;
	return -1;
}
void GLWorldViewer :: displayParent( std :: vector<REGISTER*> where, int reg_id, int flag )
{
	if( where.size() )
	{
		GeneticCar * aux = new GeneticCar( where[ reg_id ]->register_id, this, new b2Vec2( 0, 0 ), 100, where[ reg_id ]->specie, NULL );
		if( !flag )
			( ( GLWorldWidget * ) parent() )->setFirstParent( aux );
		else
			( ( GLWorldWidget * ) parent() )->setSecondParent( aux );
		aux->Destroy();
	}
}
void GLWorldViewer :: createIndividue( void )
{
	individual_timer->stop();
	//
	if( individue )
	{
		if( achieved )
		{
			if( population_type == SINGLE_POPULATION )
			{
				addInSinglePopulation();
			}
			else if( population_type == ACTUAL_BEST )
			{
				addInActualBestPopulation();
			}
		}
		individue->Destroy();
	}
	if( create_population )
	{
		individue = new GeneticCar( individue_id, this, new b2Vec2( initial_position, 3*height/4 ), 100, NULL, NULL );
	}
	else
	{
		int choosed_id_1, choosed_id_2;
		//ESCOLHE PARENTE A E DISPLAY PARENT A
		if( population_type == SINGLE_POPULATION )
		{
			if( selection_type == ROULETTE )
				choosed_id_1 = roulette( actual_historic );
			else if( selection_type == TOURNEY )
				choosed_id_1 = tourney( actual_historic );
			else if( selection_type == ALEATORY )
				choosed_id_1 = rand() % ( ( int ) actual_historic.size() );
		}
		if( population_type == ACTUAL_BEST )
		{
			if( selection_type == ROULETTE )
				choosed_id_1 = roulette( best_historic );
			else if( selection_type == TOURNEY )
				choosed_id_1 = tourney( best_historic );
			else if( selection_type == ALEATORY )
				choosed_id_1 = rand() % ( ( int ) best_historic.size() );
		}
		//TESTE DE MUTACAO
		int mutation = rand() % 10000;
		GeneticCar * mutant = NULL;
		//MUTACAO !!!
		if( mutation < mutation_tax * 100 )
		{
			mutant = new GeneticCar( -666, this, new b2Vec2( 0, 0 ), 100, NULL, NULL );
		}
		else {
			if( population_type == SINGLE_POPULATION )
			{
				if( selection_type == ROULETTE )
					choosed_id_2 = roulette( actual_historic );
				else if( selection_type == TOURNEY )
					choosed_id_2 = tourney( actual_historic );
				else if( selection_type == ALEATORY )
					choosed_id_2 = rand() % ( ( int ) actual_historic.size() );
			}
			else if( population_type == ACTUAL_BEST )
			{
				if( selection_type == ROULETTE )
					choosed_id_2 = roulette( best_historic );
				else if( selection_type == TOURNEY )
					choosed_id_2 = tourney( best_historic );
				else if( selection_type == ALEATORY )
					choosed_id_2 = rand() % ( ( int ) best_historic.size() );
			}
			//
			if( !ressurection_allowed )
				while ( choosed_id_1 == choosed_id_2 )
				{
					if( population_type == SINGLE_POPULATION )
					{
						if( selection_type == ROULETTE )
							choosed_id_2 = roulette( actual_historic );
						else if( selection_type == TOURNEY )
							choosed_id_2 = tourney( actual_historic );
						else if( selection_type == ALEATORY )
							choosed_id_2 = rand() % ( ( int ) actual_historic.size() );
					}
					else if( population_type == ACTUAL_BEST )
					{
						if( selection_type == ROULETTE )
							choosed_id_2 = roulette( best_historic );
						else if( selection_type == TOURNEY )
							choosed_id_2 = tourney( best_historic );
						else if( selection_type == ALEATORY )
							choosed_id_2 = rand() % ( ( int ) best_historic.size() );
					}
				}
		}
		//SE MUTANTE...
		if( mutant )
		{
			( ( GLWorldWidget * ) parent() )->setFirstParent( mutant );
			//
			if( population_type == SINGLE_POPULATION )
			{
				if( cross_mutation )
				{
					displayParent( actual_historic, choosed_id_1, 1 );
					individue = new GeneticCar( individue_id, this, new b2Vec2( initial_position, 3*height/4 ), 100, mutant->getCromossome(), actual_historic[ choosed_id_1 ]->specie );
				}
				else {
					( ( GLWorldWidget * ) parent() )->setSecondParent( NULL );
					individue = new GeneticCar( individue_id, this, new b2Vec2( initial_position, 3*height/4 ), 100, mutant->getCromossome(), NULL );
				}
				mutant->Destroy();
			}
			else if( population_type == ACTUAL_BEST )
			{
				if( cross_mutation )
				{
					displayParent( best_historic, choosed_id_1, 1 );
					individue = new GeneticCar( individue_id, this, new b2Vec2( initial_position, 3*height/4 ), 100, mutant->getCromossome(), best_historic[ choosed_id_1 ]->specie );
				}
				else {
					( ( GLWorldWidget * ) parent() )->setSecondParent( NULL );
					individue = new GeneticCar( individue_id, this, new b2Vec2( initial_position, 3*height/4 ), 100, mutant->getCromossome(), NULL );
				}
				mutant->Destroy();
			}
		}
		//SENÃO
		else
		{
			if( population_type == SINGLE_POPULATION )
			{
				displayParent( actual_historic, choosed_id_1, 0 );
				displayParent( actual_historic, choosed_id_2, 1 );
				individue = new GeneticCar( individue_id, this, new b2Vec2( initial_position, 3*height/4 ), 100, actual_historic[choosed_id_1]->specie, actual_historic[choosed_id_2]->specie );
			}
			else if( population_type == ACTUAL_BEST )
			{
				displayParent( best_historic, choosed_id_1, 0 );
				displayParent( best_historic, choosed_id_2, 1 );
				individue = new GeneticCar( individue_id, this, new b2Vec2( initial_position, 3*height/4 ), 100, best_historic[choosed_id_1]->specie, best_historic[choosed_id_2]->specie );
			}
		}
	}
	individue_id++;
	achieved = false;
	individual_clock = 0;
	time_stopped = 0;
	individual_timer->start();
	if( !timer->isActive() )
		timer->start();
	x_initial = individue->getCarCenter().x;
	//
}
void GLWorldViewer :: saveRegister( std :: string file_name, REGISTER* reg  )
{
	FILE * file = fopen( file_name.c_str(), "at" );
	if( file )
	{
		fwrite( &reg->register_id, 1, sizeof( int ), file );
		fwrite( &reg->x_distance, 1, sizeof( float32 ), file );
		fwrite( &reg->time_spent, 1, sizeof( long ), file );
		fwrite( &reg->score, 1, sizeof( float32 ), file );
		CROMOSSOME * centry = reg->specie;
		fwrite( &centry->number_of_wheels, 1, sizeof( int ), file );
		fwrite( &centry->max_ray, 1, sizeof( float32 ), file );
		for( int wid = 0; wid < centry->number_of_wheels; wid++ )
		{
			fwrite( &centry->wheeled_parts[wid], 1, sizeof( int ), file );
			fwrite( &centry->wheels_ray[wid], 1, sizeof( float32 ), file );
			fwrite( &centry->wheels_density[wid], 1, sizeof( float32 ), file );
			fwrite( &centry->wheels_restitution[wid], 1, sizeof( float32 ), file );
			fwrite( &centry->wheels_friction[wid], 1, sizeof( float32 ), file );
			fwrite( &centry->wheels_torque[wid], 1, sizeof( float32 ), file );
			fwrite( &centry->wheels_velocity[wid], 1, sizeof( float32 ), file );
		}
		for( int pid = 0; pid < 8; pid++ )
		{
			fwrite( &centry->parts_ray[pid], 1, sizeof( float32 ), file );
			fwrite( &centry->parts_angle[pid], 1, sizeof( float32 ), file );
			fwrite( &centry->parts_density[pid], 1, sizeof( float32 ), file );
			fwrite( &centry->parts_restitution[pid], 1, sizeof( float32 ), file );
			fwrite( &centry->parts_friction[pid], 1, sizeof( float32 ), file );
			fwrite( &centry->wheels_velocity[pid], 1, sizeof( float32 ), file );
		}
		fclose( file );
	}
	else {
		std :: cout << "REGISTER NOT SAVED !!!" << std :: endl;
	}
}
void GLWorldViewer :: saveHistoric( std :: string file_name, std :: vector<REGISTER*> historic  )
{
	for ( size_t hid = 0; hid < historic.size(); hid++ )
		saveRegister( file_name.c_str(), historic[ hid ] );
}
std :: vector<REGISTER*> GLWorldViewer :: loadHistoric( std :: string file_name )
{
	FILE * file = fopen( file_name.c_str(), "rt" );
	std :: vector<REGISTER*> load_historic;
	if( file )
	{
		while( !feof( file ) )
		{
			REGISTER * entry = new REGISTER;
			fread( &entry->register_id, 1, sizeof( int ), file );
			fread( &entry->x_distance, 1, sizeof( float32 ), file );
			fread( &entry->time_spent, 1, sizeof( long ), file );
			fread( &entry->score, 1, sizeof( float32 ), file );
			CROMOSSOME * centry = new CROMOSSOME;
			fread( &centry->number_of_wheels, 1, sizeof( int ), file );
			fread( &centry->max_ray, 1, sizeof( float32 ), file );
			for( int wid = 0; wid < centry->number_of_wheels; wid++ )
			{
				int part;
				fread( &part, 1, sizeof( int ), file );
				centry->wheeled_parts.push_back( part );
				float32 value;
				fread( &value, 1, sizeof( float32 ), file );
				centry->wheels_ray.push_back( value );
				fread( &value, 1, sizeof( float32 ), file );
				centry->wheels_density.push_back( value );
				fread( &value, 1, sizeof( float32 ), file );
				centry->wheels_restitution.push_back( value );
				fread( &value, 1, sizeof( float32 ), file );
				centry->wheels_friction.push_back( value );
				fread( &value, 1, sizeof( float32 ), file );
				centry->wheels_torque.push_back( value );
				fread( &value, 1, sizeof( float32 ), file );
				centry->wheels_velocity.push_back( value );
			}
			for( int pid = 0; pid < 8; pid++ )
			{
				fread( &centry->parts_ray[pid], 1, sizeof( float32 ), file );
				fread( &centry->parts_angle[pid], 1, sizeof( float32 ), file );
				fread( &centry->parts_density[pid], 1, sizeof( float32 ), file );
				fread( &centry->parts_restitution[pid], 1, sizeof( float32 ), file );
				fread( &centry->parts_friction[pid], 1, sizeof( float32 ), file );
				fread( &centry->wheels_velocity[pid], 1, sizeof( float32 ), file );
			}
			entry->specie = centry;
			load_historic.push_back( entry );
		}
		fclose( file );
	}
	else {
		std :: cout << "HISTORIC NOT LOADED !!!" << std :: endl;
	}
	return load_historic;
}
void GLWorldViewer :: startPauseTimer( void )
{
	if( timer->isActive() && individual_timer->isActive() )
	{
		individual_timer->stop();
		timer->stop();
	}
	else
	{
		individual_timer->start();
		timer->start();
	}
	
	/*if( individual_timer->isActive() )
	 individual_timer->stop();
	 else
	 individual_timer->start();*/
}
b2World* GLWorldViewer :: getWorld( void )
{
	return world;
}
QTimer* GLWorldViewer :: getTimer( void )
{
	return timer;
}
//SLOTS


//
//GETS
void GLWorldViewer :: stopSimulation( void )
{
	timer->stop();
}
void GLWorldViewer :: startSimulation( void )
{
	timer->start();
}
long GLWorldViewer :: getClock( void )
{
	return clock;
}
void GLWorldViewer :: initializeGL( void )
{
	//PRERROGATIVAS OpenGl
	
	glViewport( 0, 0, width, height );
	
	glMatrixMode ( GL_PROJECTION );
	glLoadIdentity ();
	
	gluOrtho2D( xview, xview + width, yview, yview + height );
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	glEnable(GL_DEPTH_TEST);                 
	glEnable(GL_NORMALIZE);
	//glEnable(GL_CULL_FACE);
	glEnable(GL_COLOR_MATERIAL);
	
	glShadeModel (GL_SMOOTH);
	
	individue = NULL;
	
	createTerrain();
}
void putObstacles( void )
{
	int number_of_obstacles = 50;
}
void GLWorldViewer :: createTerrain( void )
{
	for ( size_t bid = 0; bid < bases.size(); bid++ )
		bases[ bid ]->Destroy();
	bases.clear();
	switch( terrain_type )
	{
		case PLAIN:
			base = new GroundBlock( bases.size(), this, new b2Vec2( 0, height/4 ), new b2Vec2( 10 * width, height/4 ) );
			bases.push_back( base );
			break;
		case IRREGULAR:
			base_angle = 0;
			base = new GroundBlock( bases.size(), this, new b2Vec2( -4.5 * width, height/4 ), new b2Vec2( 2*width, height/100 ) );
			bases.push_back( base );
			for ( int i = 0; i < 80; i++ )
				addBase();
	}
}
void GLWorldViewer :: addBase( void )
{
	b2Vec2 *base_end = base->circlePoint( base_angle, new b2Vec2( base->getPosition().x, base->getPosition().y ), base->getDimension()->x / 2 );
	base_angle = ( float32 ) ( ( rand() % 91 - 45 ) * b2_pi ) / 180;
	b2Vec2 *base_position = base->circlePoint( base_angle, base_end, width/16 );
	base = new GroundBlock( bases.size(), this, base_position, new b2Vec2( width/8, height/100 ), base_angle );
	bases.push_back( base );
}
b2Vec2* circlePoint( float angle, b2Vec2 *center, float ray )
{
	return new b2Vec2( cos( angle ) * ray + center->x, sin( angle ) * ray + center->y );
}
void GLWorldViewer :: paintGL() 
{
	glClearColor ( 1, 1, 1, 1.0);
	glClear ( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	
	glEnable( GL_BLEND );
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
	glPushMatrix();
	//
	for ( size_t bid = 0; bid < bases.size(); bid++ )
		bases[ bid ]->draw();
	
	if( individue )
	{
		individue->draw();
	}
	
	glPopMatrix();
	glDisable( GL_BLEND );
}
void GLWorldViewer :: projection( void )
{
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	
	gluOrtho2D( xview, xview + width, yview, yview + height );
	
	glMatrixMode ( GL_MODELVIEW );
	glLoadIdentity ();
}
void GLWorldViewer :: showActualHistoric( void )
{
	char individue_resume[100];
	sprintf( individue_resume, "<b>ACTUAL GEN %d</b><br /><br />", generation );
	std :: string resume = individue_resume;
	for ( size_t hid = 0; hid < actual_historic.size(); hid++ )
	{
		sprintf( individue_resume, ( actual_historic[ hid ]->register_id == individue_id ) ? "%d - <b>[ %d ] %f</b><br />" : "%d - [ %d ] %f<br />", ( int ) ( hid + 1 ), actual_historic[hid]->register_id, actual_historic[hid]->score );
		resume += individue_resume;
	}
	( ( GLWorldWidget* ) parent() )->setActualHistoricText( resume );
}
void GLWorldViewer :: showBestHistoric( void )
{
	char individue_resume[100];
	sprintf( individue_resume, "<b>BEST</b><br /><br />" );
	std :: string resume = individue_resume;
	for ( size_t hid = 0; hid < best_historic.size(); hid++ )
	{
		sprintf( individue_resume, "%d - <b>[ %d ] %f</b><br />", ( int ) ( hid + 1 ), best_historic[hid]->register_id, best_historic[hid]->score );
		resume += individue_resume;
	}
	( ( GLWorldWidget* ) parent() )->setBestHistoricText( resume );
}
void GLWorldViewer :: keyPressEvent( QKeyEvent * event )
{
	switch( event->key() )
	{
			//ESC
		case 16777216:  
			exit(0);
			break;
		case 27:
			break;
		case 32: 
			createIndividue();
			break;
		case '-':
			break;
		case '=':
			break;
		case '1': 
			break;
		case '2': 
			break;
		case '3': 
			break;
		case '4': 
			break;
		case '5': 
			break;
		case '6': 
			break;
		case '7': 
			break;
		case '8': 
			break;
		case '9': 
			break;
		case '0': 
			break;
		case 'a':
		case 'A': 
			break;
		case 'b':
		case 'B': 
			addBase();
			break;
		case 'c':
		case 'C': 
			for ( population_it = population.begin(); population_it != population.end(); population_it++)
				( ( Object* ) *population_it )->Destroy();
			population.clear();
			break;
		case 'd':
		case 'D': 
			break;
		case 'e':
		case 'E': 
			break;
		case 'f':
		case 'F': 
			break;
		case 'g':
		case 'G':
			break;
		case 'h':
		case 'H':
			break;
		case 'i':
		case 'I':
			break;
		case 'j':
		case 'J':
			break;
		case 'k':
		case 'K':
			break;
		case 'l':
		case 'L':
			break;
		case 'm':
		case 'M':
			break;
		case 'n':
		case 'N':
			break;
		case 'o':
		case 'O':
			break;
		case 'p':
		case 'P':
			break;
		case 'q':
		case 'Q':
			break;
		case 'r':
		case 'R':
			break;
		case 's':
		case 'S':
			break;
		case 't':
		case 'T':
			break;
		case 'u':
		case 'U':
			break;
		case 'v':
		case 'V':
			break;
		case 'w':
		case 'W':
			break;
		case 'x':
		case 'X':
			break;
		case 'y':
		case 'Y':
			break;
		case 'z':
		case 'Z':
			break;
			//RIGHT
		case 16777236:
			xview += 10;
			break;
			//LEFT
		case 16777234:
			if( xview >= 10 )
				xview -= 10;
			else
				xview = 0;
			break;
			//UP
		case 16777235:
			yview += 10;
			break;
			//DOWN
		case 16777237:
			if( yview >= 10 )
				yview -= 10;
			else
				yview = 0;
			break;
	}
	projection();
	event->accept();
}
void GLWorldViewer :: mouseAction( QMouseEvent * event ) 
{
	event->accept();
}
void GLWorldViewer :: mousePressEvent( QMouseEvent * event ) 
{
	std :: cout << "( " << event->x() << ", " << event->y() << " )" << std :: endl;
} 
void GLWorldViewer :: mouseMoveEvent( QMouseEvent * event ) 
{
	event->accept();
} 
void GLWorldViewer :: mouseReleaseEvent( QMouseEvent * event )
{
	event->accept();
}
