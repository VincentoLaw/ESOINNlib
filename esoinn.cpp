#include "neuron.h"``
#include "esoinn.h"

Esoinn::Esoinn(int dimensionSize, double learningRate, int maximalConnectionAge, int lambda, double (*distanceFunction)(double *,double *)){//= &commonDistanceFunction
    this->dimensionSize = dimensionSize;
    neuronsList = new std::list<Neuron>();
}

//TODO: implement this function
void Esoinn::inputSignal(double * inputVector){

/*-----------------5.increase-age-of-connection,-which-belongs-to-a1-winner-------*/
	Neuron *a1 = new Neuron(this->dimensionSize);
	Neuron *a2 = new Neuron(this->dimensionSize);
	
	a1 = findFirstWiner(inputVector);
	a2 = findSecondWiner(intputVector, a1);
	
	for(int i = 0; i < a1->neighboursList.size(); i++){
			a1->neighboursList[i]->increaseAge();
	}
/*-----------------end-of-5.-------------------------------------------------------*/

/*-----------------6.To-create-connections-between-a1-and-a2-if necessary----------*/
	bool exist = connectionExist(a1, a2);
	bool key = keytoConnect(a1, a2)
	if(key){
		if(!exist){
			addConnection(a1, a2);
			int n = getConnectionCount();
			connectionsList[n - 1]->setAge(0);
		}
		else{
			setConnectionAge(a1, a2);
		}
	}
	else{
		if(exist) removeConnection(a1, a2);
	}
/*-----------------end-of-6--------------------------------------------------------*/

/*-----------------7.Increase-signals-of--neuron-winner----------------------------*/
	a1->incSignal();
/*-----------------end-of-7--------------------------------------------------------*/

/*-----------------8.Update the density of winner----------------------------------*/
	double point = calcPoint(a1);
	
/*-----------------end-of-8--------------------------------------------------------*/
}



//This main function for testing. When we will make lib it will be removed.
int main(){
}
