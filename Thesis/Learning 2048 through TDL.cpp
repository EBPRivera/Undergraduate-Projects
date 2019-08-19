#include<iostream>
#include<ctime>
#include<cstdlib>
#include<cmath>
#include<fstream>

using namespace std;

#define grid_size 4

class state{
		
public:
	
	int grid[grid_size][grid_size];
	double r;
	
	void init_game_state();
	void add_random_tile();
	void print_state();

	state();

};

class Tuple{

public:

	double LUT[50625];
	int i[grid_size];
	int j[grid_size];

	Tuple();

};

bool is_terminal_state(state);
bool is_valid_move(int,state);
bool check_win(state);
state compute_afterstate(int, state);
state fill_space(int, state);
state merge_tiles(int, state);

class Game{
	
public:
	
	int score;
	state s;
	state s1;
	state s2;
	
	void make_move(int);
	void fill_space(int);
	void merge_tiles(int);

	Game();
	
};

class Agent{
	
public:

	int a;
	double alpha;
	double exploration_rate;
	bool learning_enabled;
	Tuple tuple[17];

	void construct_n_tuple_network();
	void play_game(Game*);
	int evaluate(state);
	void learn_evaluation(state,int,double,state,state);
	void update_LUT(state, double);

	double V(state);

	Agent();
	
};


int main(){ 
	int i, j, wins = 0;
	float win_rate = 0;
	int total_score = 0;
	int average_score;

	Agent agent;
	Game exec;
	fstream myfile;
	fstream myfile2;
	ofstream reset;
	
	srand(time(NULL));
	
	cout << "Executing" << endl;
	
	reset.open("score_data_001.txt", ios::trunc);
	reset.close();
	reset.open("win_rate_data_001.txt", ios::trunc);
	reset.close();
	
	for(i = 0; i < 500000; i++){
		
		agent.play_game(&exec);

		if((i+1) % 1000 == 0){
			
			agent.learning_enabled = false;
			
			for(j = 0; j < 1000; j++){
				
				agent.play_game(&exec);
				
				if(check_win(exec.s))
					wins++;
				
				total_score += exec.score;
				
			}
			
			win_rate = (float)wins/(float)1000;
			average_score = total_score/1000;

			myfile.open("score_data_001.txt", ios::app);
			myfile2.open("win_rate_data_001.txt", ios::app);

			myfile << "hold on;\nplot(" << i+1 << "," << average_score << ",'b.');\r\n";
			myfile2 << "hold on;\nplot(" << i+1 << "," << win_rate << ",'b.');\r\n";
				

			myfile.close();
			myfile2.close();
			
			cout << "Game " << i+1 << " | Wins: " << wins << " | Win Rate: " << win_rate << " | Average Score: " << average_score << endl;
			
			wins = 0;
			total_score = 0;
			agent.learning_enabled = true;
			
		}

	}
	
	return 0;
}//end class

bool is_terminal_state(state s){
	
	int i;
	
	for(i = 0; i < 4; i++)
		if(is_valid_move(i+1, s))
			return false;
	
	return true;
	
}//end method

bool is_valid_move(int a, state s){
	int i, j;
	
	switch(a){
		
		case 1: //up
			for(i = 1; i < grid_size; i++)
				for(j = 0; j < grid_size; j++)
					if(s.grid[i][j] != 0 && (s.grid[i][j] == s.grid[i-1][j] || s.grid[i-1][j] == 0))
						return true;
			break;
			
		case 2: //down
			for(i = 0; i < grid_size-1; i++)
				for(j = 0; j < grid_size; j++)
					if(s.grid[i][j] != 0 && (s.grid[i][j] == s.grid[i+1][j] || s.grid[i+1][j] == 0))
						return true;
			break;
			
		case 3: //left
			for(i = 0; i < grid_size; i++)
				for(j = 1; j < grid_size; j++)
					if(s.grid[i][j] != 0 && (s.grid[i][j] == s.grid[i][j-1] || s.grid[i][j-1] == 0))
						return true;
			break;
			
		case 4: //right
			for(i = 0; i < grid_size; i++)
				for(j = 0; j < grid_size-1; j++)
					if(s.grid[i][j] != 0 && (s.grid[i][j] == s.grid[i][j+1] || s.grid[i][j+1] == 0))
						return true;
			break;
	}
	return false;
	
}//end method

bool check_win(state s){

	int i, j;

	for(i = 0; i < grid_size; i++)
		for(j = 0; j < grid_size; j++)
			if(s.grid[i][j] >= 2048)
				return true;

	return false;

}

state compute_afterstate(int temp_a, state s){
	
	s = fill_space(temp_a, s);
	s = merge_tiles(temp_a, s);
	s = fill_space(temp_a, s);
	
	return s;

}

state fill_space(int a, state temp_state){
	switch(a)
	{
		case 1: //up
			for(int i=0;i<grid_size;i++)
				for(int j=0;j<grid_size;j++)
				{
					if(temp_state.grid[j][i] == 0)
					{
						for(int k=j+1;k<grid_size;k++)
							if(temp_state.grid[k][i] != 0)
							{

								temp_state.grid[j][i]=temp_state.grid[k][i];
								temp_state.grid[k][i]=0;
								break;
							}
					}

				}break;

		case 2: //down
			for(int i=0;i<grid_size;i++)
				for(int j=grid_size-1;j>=0;j--)
				{
					if(temp_state.grid[j][i] == 0)
					{
						for(int k=j-1;k>=0;k--)
							if(temp_state.grid[k][i] != 0)
							{
								temp_state.grid[j][i]=temp_state.grid[k][i];
								temp_state.grid[k][i]=0;
								break;
							}
					}

				}break;
		case 3: //left
			for(int i=0;i<grid_size;i++)
				for(int j=0;j<grid_size;j++)
				{
					if(temp_state.grid[i][j] == 0)
					{
						for(int k=j+1;k<grid_size;k++)
							if(temp_state.grid[i][k] != 0)
							{
								temp_state.grid[i][j]=temp_state.grid[i][k];
								temp_state.grid[i][k]=0;
								break;
							}
					}

				}break;


		case 4:	//right
			for(int i=0;i<grid_size;i++)
				for(int j=grid_size-1;j>=0;j--)
				{
					if(temp_state.grid[i][j] == 0)
					{
						for(int k=j-1;k>=0;k--)
							if(temp_state.grid[i][k] != 0)
							{
								temp_state.grid[i][j]=temp_state.grid[i][k];
								temp_state.grid[i][k]=0;
								break;
							}
					}

				}break; 

	}
	
	return temp_state;
	
}

state merge_tiles(int a, state temp_state){
	
	
	switch (a){
		case 1: //up
			for(int i=0;i<grid_size;i++){
				for(int j=0;j<grid_size-1;j++){
					if(temp_state.grid[j][i] != 0 && temp_state.grid[j][i]==temp_state.grid[j+1][i]){
						temp_state.grid[j][i]+=temp_state.grid[j+1][i];
						temp_state.grid[j+1][i]=0;
						temp_state.r += temp_state.grid[j][i];
					}
				}
			}
			break;
		case 2: //down
			for(int i=0;i<grid_size;i++){
				for(int j=grid_size-1;j>0;j--){
					if(temp_state.grid[j][i] != 0 && temp_state.grid[j][i]==temp_state.grid[j-1][i]){
						temp_state.grid[j][i]+=temp_state.grid[j-1][i];
						temp_state.grid[j-1][i]=0;
						temp_state.r += temp_state.grid[j][i];
					}
				}
			}
			break;
		case 3: //left
			for(int i=0;i<grid_size;i++){
				for(int j=0;j<grid_size-1;j++){
					if(temp_state.grid[i][j] != 0 && temp_state.grid[i][j]==temp_state.grid[i][j+1]){
						temp_state.grid[i][j]+=temp_state.grid[i][j+1];
						temp_state.grid[i][j+1]=0;
						temp_state.r += temp_state.grid[i][j];
					}
				}
			}
			break;
		case 4: //right
			for(int i=0;i<grid_size;i++){
				for(int j=grid_size-1;j>0;j--){
					if(temp_state.grid[i][j] != 0 && temp_state.grid[i][j]==temp_state.grid[i][j-1]){
						temp_state.grid[i][j]+=temp_state.grid[i][j-1];
						temp_state.grid[i][j-1]=0;
						temp_state.r += temp_state.grid[i][j];
					}
				}
			}
			break;
	}
	
	return temp_state;
	
}

Agent::Agent(){

	alpha = 0.001;
	exploration_rate = 0.001;
	learning_enabled = true;

	construct_n_tuple_network();

}

void Agent::construct_n_tuple_network(){

	int i, j;

	for(i = 0; i < 4; i++)
		for(j = 0; j < 4; j++){

			//Construction of vertical n-tuples
			tuple[i].i[j] = j;
			tuple[i].j[j] = i;

			//Construction of horizontal n-tuples
			tuple[4+i].i[j] = i;
			tuple[4+i].j[j] = j;

		}

	//Construction of square n-tuples
	for(i = 0; i < 3; i++)
		for(j = 0; j < 3; j++){
			tuple[8 + (3*i + j)].i[0] = i;
			tuple[8 + (3*i + j)].j[0] = j;

			tuple[8 + (3*i + j)].i[1] = i+1;
			tuple[8 + (3*i + j)].j[1] = j;

			tuple[8 + (3*i + j)].i[2] = i+1;
			tuple[8 + (3*i + j)].j[2] = j+1;

			tuple[8 + (3*i + j)].i[3] = i;
			tuple[8 + (3*i + j)].j[3] = j+1;
		}

}

void Agent::play_game(Game * game){ //Main Function
	
	double r;
	
	game->s.init_game_state();
	game->score = 0;
	
	
	while (!is_terminal_state(game->s)){
		
		r = (double) rand() / (RAND_MAX);
		
		if(r <= exploration_rate){
			while(true){
				a = rand() % 4 + 1;
				if(is_valid_move(a, game->s))
					break;
			}
		}else{
			a = evaluate(game->s);
		}

		game->make_move(a);
		
		if (learning_enabled){
			learn_evaluation(game->s, a, game->s1.r, game->s1, game->s2);
		}
		
		game->s = game->s2;
		game->score = game->score + game->s1.r;
		
	}


}

int Agent::evaluate(state s){

	int i, action;
	int count = 0;
	int rand_action[4];
	double temp_r[4];
	double max;
	bool assigned[4], first = true;
	state temp_state;

	for(i = 0; i < 4; i++){
		if(is_valid_move(i+1,s)){
			temp_state = compute_afterstate(i+1, s);
			temp_r[i] = temp_state.r + V(temp_state);
			
			assigned[i] = true;	
		}
		else assigned[i] = false;
	}

	for(i = 0; i < 4; i++)
		if(assigned[i]){
			if(first){
				first = false;
				max = temp_r[i];
				action = i+1;
				rand_action[0] = i+1;
			}
			else if(temp_r[i] > max){
				max = temp_r[i];
				action = i+1;
			}
			else if(temp_r[i] == max){
				rand_action[count] = i+1;
				count ++;
			}
		}
		
	if(count > 0)
		action = rand_action[rand() % (count + 1)];
		
	return action;

}

void Agent::learn_evaluation(state s,int a,double r,state s1,state s2){

	int a_next;
	double V_s;
	state temp_state;

	a_next = evaluate(s2);

	temp_state = compute_afterstate(a_next, s2);

	V_s = alpha*(temp_state.r + V(temp_state) - V(s1));
	update_LUT(s1, V_s);

}

double Agent::V(state s){

	double sum = 0;
	int i, j;
	int index;

	for(i = 0; i < 17; i++){

		index = 0;

		for(j = 0; j < 4; j++)
			if(s.grid[tuple[i].i[j]][tuple[i].j[j]] > 0)
				index += log2(s.grid[tuple[i].i[j]][tuple[i].j[j]]) * pow(15,j);

		sum += tuple[i].LUT[index];
	}

	return sum;

}

void Agent::update_LUT(state s, double V_s){

	int i, j;
	int index;

	for(i = 0; i < 17; i++){

		index = 0;

		for(j = 0; j < 4; j++)
			if(s.grid[tuple[i].i[j]][tuple[i].j[j]] > 0)
				index += log2(s.grid[tuple[i].i[j]][tuple[i].j[j]]) * pow(15,j);
			
		tuple[i].LUT[index] += V_s;
	}

}

Game::Game(){
	score = 0;
}

void Game::make_move(int a){
	
	s1 = s;
	
	s1 = compute_afterstate(a, s1);
	
	s2 = s1;
	s2.add_random_tile();
	s2.r = 0;
			
}

state::state(){
	r = 0;
}

void state::init_game_state(){ 
	int i, j;
	
	for(i = 0; i < grid_size; i++)
		for(j = 0; j < grid_size; j++)
				grid[i][j] = 0;
	
	add_random_tile();
	add_random_tile();
	
}

void state::add_random_tile(){
	
	int i, j, k;
	bool flag=false;
	k = rand() % 10;

	while (!flag){
	
		i = rand() % grid_size;
		j = rand() % grid_size;
		
		if (grid[i][j]==0){
			
			if(k < 1)
				grid[i][j] = 4;
			else
				grid[i][j] = 2;
			
			flag=true;
			
			return;
		}
	}

}

void state::print_state(){
	
	int i, j;
	
	cout << "\n";
	for(i = 0; i < grid_size;i++){
		for(j=0;j<grid_size;j++)
			cout << grid[i][j] << "\t";
		
		cout << "\n";
	}
	
}

Tuple::Tuple(){

	int i;

	for(i = 0; i < 50625; i++)
		LUT[i] = 0;

}

/*
	//Replace all functions, classes etc. with the same name for TDL
	
class Agent{
	
public:

	int a;
	int update_horizon;
	int t;
	double alpha;
	double lambda;
	double exploration_rate;
	bool learning_enabled;
	vector<state> state_trace;
	Tuple tuple[17];

	void construct_n_tuple_network();
	void play_game(Game*);
	int evaluate(state);
	void learn_evaluation(state, state);
	void update_LUT(state, double);

	double V(state);

	Agent();
	
};
	
Agent::Agent(){

	alpha = 0.01;
	lambda = 0.5;
	exploration_rate = 0.001;
	learning_enabled = true;
	update_horizon = ((int)(log(0.1)/log(lambda)) - 1);

	construct_n_tuple_network();
	
}
	
void Agent::play_game(Game * game){
	double r;
	
	state_trace.clear();
	t = 0;
	game->s.init_game_state();
	game->score = 0;
		
	while (!is_terminal_state(game->s)){
		r = (double) rand() / (RAND_MAX);
		
		if(r <= exploration_rate){
			while(true){
				a = rand() % 4 + 1;
				if(is_valid_move(a, game->s))
					break;
			}
		}else{
			a = evaluate(game->s);
		}

		game->make_move(a);
		
		if(learning_enabled){
			learn_evaluation(game->s1, game->s2);
		}
		
		if(state_trace.size() > update_horizon){
			state_trace.erase(state_trace.begin());
		}
		
		game->s = game->s2;
		game->score = game->score + game->s1.r;
		t++;
		
	}
}

void Agent::learn_evaluation(state s1, state s2){

	double delta;
	int a_next;
	int k = update_horizon;
	state temp_state;
	vector<state>::iterator it;
	
	a_next = evaluate(s2);
	temp_state = compute_afterstate(a_next, s2);
	state_trace.push_back(temp_state);
	delta = temp_state.r + V(temp_state) - V(s1);
	
	for(it = state_trace.end()-1; it >= state_trace.begin(); it--){
		update_LUT(*it, (alpha/17)*delta*pow(lambda,k));
		k--;
	}

}

*/

/*
	//For TEMPORAL COHERENCE LEARNING
	
class Agent{
	
public:

	int a;
	int update_horizon;
	int t;
	double beta;
	double lambda;
	double exploration_rate;
	bool learning_enabled;
	vector<state> state_trace;
	Tuple tuple[17];

	void construct_n_tuple_network();
	void play_game(Game*);
	int evaluate(state);
	void learn_evaluation(state, state);
	void update_LUT(state, double, int);

	double V(state);

	Agent();
	
};

class Tuple{

public:

	vector<double> LUT;
	int i[grid_size];
	int j[grid_size];
	double alpha;
	vector<double> V;
	vector<double> E;
	vector<double> A;

	Tuple();

};
	
Agent::Agent(){

	beta = 0.01;
	lambda = 0.5;
	exploration_rate = 0.001;
	learning_enabled = true;
	update_horizon = ((int)(log(0.1)/log(lambda)) - 1);

	construct_n_tuple_network();

}

void Agent::play_game(Game * game){
	double r;
	
	state_trace.clear();
	t = 0;
	game->s.init_game_state();
	game->score = 0;
		
	while (!is_terminal_state(game->s)){
		r = (double) rand() / (RAND_MAX);
		
		if(r <= exploration_rate){
			while(true){
				a = rand() % 4 + 1;
				if(is_valid_move(a, game->s))
					break;
			}
		}else{
			a = evaluate(game->s);
		}

		game->make_move(a);
		
		if(learning_enabled){
			learn_evaluation(game->s1, game->s2);
		}
		
		if(state_trace.size() > update_horizon){
			state_trace.erase(state_trace.begin());
		}
		
		game->s = game->s2;
		game->score = game->score + game->s1.r;
		t++;
		
	}
}

void Agent::learn_evaluation(state s1, state s2){

	double delta;
	int a_next;
	int k = update_horizon;
	state temp_state;
	vector<state>::iterator it;
	
	a_next = evaluate(s2);
	temp_state = compute_afterstate(a_next, s2);
	state_trace.push_back(temp_state);
	delta = temp_state.r + V(temp_state) - V(s1);
	
	for(it = state_trace.end()-1; it >= state_trace.begin(); it--){
		update_LUT(*it, delta, k);
		k--;
	}

}

void Agent::update_LUT(state s, double V_s, int k){

	int i, j;
	int index;

	for(i = 0; i < 17; i++){

		index = 0;

		for(j = 0; j < 4; j++)
			if(s.grid[tuple[i].i[j]][tuple[i].j[j]] > 0)
				index += log2(s.grid[tuple[i].i[j]][tuple[i].j[j]]) * pow(15,j);

		if(tuple[i].A[index] == 0){
			tuple[i].alpha = .01;
		}else{
			tuple[i].alpha = fabs(tuple[i].E[index])/tuple[i].A[index];
		}
		tuple[i].LUT[index] += beta*(tuple[i].alpha/17)*V_s*pow(lambda,k);
		tuple[i].E[index] += V_s;
		tuple[i].A[index] += fabs(V_s);

	}

}

Tuple::Tuple(){
	
	int i;

	for(i = 0; i < 50625; i++){
		LUT.push_back(0);
		V.push_back(0);
		E.push_back(0);
		A.push_back(0);
	}	
	
	alpha = .01;
}
*/

/*
	//For DELAYED TDL
	//*Replace the functions, classes etc. with the ones listed for TDL above.
	//Then replace and add the ones listed below
	
void Agent::play_game(Game * game){
	double r;
	
	state_trace.clear();
	delta_trace.clear();
	t = 0;
	game->s.init_game_state();
	game->score = 0;
		
	while (!is_terminal_state(game->s)){
		r = (double) rand() / (RAND_MAX);
		
		if(r <= exploration_rate){
			while(true){
				a = rand() % 4 + 1;
				if(is_valid_move(a, game->s))
					break;
			}
		}else{
			a = evaluate(game->s);
		}

		game->make_move(a);
		
		if(learning_enabled && !is_terminal_state(game->s2)){
			learn_evaluation(game->s1, game->s2);
		}
		
		if(state_trace.size() > update_horizon-1){
			state_trace.erase(state_trace.begin());
			delta_trace.erase(delta_trace.begin());
		}
		
		game->s = game->s2;
		game->score = game->score + game->s1.r;
		t++;		
	}
	finally();
}
	
void Agent::learn_evaluation(state s1, state s2){

	int a_next;
	state temp_state;
	
	a_next = evaluate(s2);
	temp_state = compute_afterstate(a_next, s2);
	state_trace.push_back(temp_state);
	delta_trace.push_back(temp_state.r + V(temp_state) - V(s1));
	
	if(t >= update_horizon){
		int i;
		int k;
		double final_delta = 0;
		
		k = delta_trace.size()-1;
		for(i = 0; i < delta_trace.size(); i++){
			final_delta += delta_trace.at(i) * pow(lambda,k);
			k--;
		}		
		update_LUT(state_trace.at(0),final_delta);
	}

}

void Agent::finally(){
	double final_delta;
	int k;
	
	while(!state_trace.empty()){
		final_delta = 0;
		for(k = 0; k < delta_trace.size(); k++){
			final_delta += delta_trace.at(k) * pow(lambda,k);
		}
		update_LUT(state_trace.at(0),final_delta);
		state_trace.erase(state_trace.begin());
		delta_trace.erase(delta_trace.begin());
	}
}
*/

/*
	//For DELAYED TEMPORAL COHERENCE LEARNING
	//*Replace the functions, classes etc. with the ones listed for TDL above.
	//Then replace and add the ones listed below
	
void Agent::play_game(Game * game){
	double r;
	
	state_trace.clear();
	delta_trace.clear();
	t = 0;
	game->s.init_game_state();
	game->score = 0;
		
	while (!is_terminal_state(game->s)){
		r = (double) rand() / (RAND_MAX);
		
		if(r <= exploration_rate){
			while(true){
				a = rand() % 4 + 1;
				if(is_valid_move(a, game->s))
					break;
			}
		}else{
			a = evaluate(game->s);
		}

		game->make_move(a);
		
		if(learning_enabled && !is_terminal_state(game->s2)){
			learn_evaluation(game->s1, game->s2);
		}
		
		if(state_trace.size() > update_horizon-1){
			state_trace.erase(state_trace.begin());
			delta_trace.erase(delta_trace.begin());
		}
		
		game->s = game->s2;
		game->score = game->score + game->s1.r;
		t++;		
	}
	finally();
}

void Agent::learn_evaluation(state s1, state s2){

	int a_next;
	state temp_state;
	
	a_next = evaluate(s2);
	temp_state = compute_afterstate(a_next, s2);
	state_trace.push_back(temp_state);
	delta_trace.push_back(temp_state.r + V(temp_state) - V(s1));
	
	if(t >= update_horizon){
		int i;
		int k;
		double final_delta = 0;
		
		k = delta_trace.size()-1;
		for(i = 0; i < delta_trace.size(); i++){
			final_delta += delta_trace.at(i) * pow(lambda,k);
			k--;
		}
		update_LUT(state_trace.at(0),final_delta);
	}

}

void Agent::finally(){
	double final_delta;
	int k;
	
	while(!state_trace.empty()){
		final_delta = 0;
		for(k = 0; k < delta_trace.size(); k++){
			final_delta += delta_trace.at(k) * pow(lambda,k);
		}
		update_LUT(state_trace.at(0),final_delta);
		state_trace.erase(state_trace.begin());
		delta_trace.erase(delta_trace.begin());
	}
}
*/