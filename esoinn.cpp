#include "neuron.h"
#include "esoinn.h"

Esoinn::Esoinn(int dimensionSize, double learningRate, int maximalConnectionAge, int lambda, double (*distanceFunction)(double *,double *)){//= &commonDistanceFunction
    this->dimensionSize = dimensionSize;
    neuronsList = new std::list<Neuron>();
}

double Esoinn::calcEuclidNorm(double * vector1, double * vector2, int n){
	double res = 0.0;
	for(int i = 0; i < n; i++){
		res += pow(vector1[i] - vector2[i], 2);
	}
	res = pow(res, 0.5);
}

double Esoinn::calcMeanDistance(Neuron * neuron){
	double res = 0.0;
	Neuron * tmp;
	for(int i = 0; i < neuron->neighboursList->size(); i++){
		tmp = neuron->neighboursList[i].getNeighbourNeuron();
		res += calcEucludNorm(neuron->weights, tmp->weight, this->dimensionSize);
	}
	res /= neuron->neighboursList->size();
	
	return res;
}

double Esoinn::calcPoint(Neuron * neuron){
	return 1 / pow(1 + calcMeanDistance(neuron), 2);
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
/*-----------------5-end.----------------------------------------------------------*/

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
/*-----------------6.end.----------------------------------------------------------*/

/*-----------------7.Increase-signals-of--neuron-winner----------------------------*/
	a1->incSignal();
/*-----------------7-end.----------------------------------------------------------*/

/*-----------------8.Update the density of winner----------------------------------*/
	double point = calcPoint(a1);
	double density = point / a1->winerTimesCount;
	a1->setDensity(density);
/*-----------------8-end.----------------------------------------------------------*/

/*-----------------9.Find-old-edges-and-remove-them--------------------------------*/
	for(int i = 0; i < connectionsList.size(); i++){
		if (connectionsList[i]->age > this.maximalConnectionAge){
			connectionsList->remove(connectionList[i]);
		}
	}
/*-----------------9-end.----------------------------------------------------------*/
}



//This main function for testing. When we will make lib it will be removed.
int main(){
}
