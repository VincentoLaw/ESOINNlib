#include "neuron.h"
#include "connection.h"
#include "esoinn.h"
#include "cluster.h"

#include <iostream>
#include <fstream>
#include <QTime>
//#include "ESOINNLibSources/hasharray.h"


Esoinn::Esoinn(int dimensionSize, int maximalConnectionAge, int lambda, double c1, double c2, double (*distanceFunction)(double *,double *))//= &commonDistanceFunction
{
    this->dimensionSize = dimensionSize;
    neuronsList = new list<Neuron *>();
    connectionsList = new list<Connection *>();
    clustersList = new list<Cluster *>();
    this->maximalConnectionAge = maximalConnectionAge;
    this->lambda = lambda;
    this->c1 = c1;
    this->c2 = c2;
    this->LT = 0;
    //this->externalCalcDistance = distanceFunction;
}

Esoinn::Esoinn(int dimensionSize, int maximalConnectionAge, int lambda, double c1, double c2)//= &commonDistanceFunction
{
   	this->dimensionSize = dimensionSize;
    neuronsList = new list<Neuron *>();
    connectionsList = new list<Connection *>();
    clustersList = new list<Cluster *>();
    this->maximalConnectionAge = maximalConnectionAge;
    this->lambda = lambda;
    this->c1 = c1;
    this->c2 = c2;
    this->LT = 0;
}

Esoinn::~Esoinn()
{
    qDebug() << "D";
    for(list<Neuron *>::iterator it = neuronsList->begin(); it != neuronsList->end();) {
        removeNeuronFully(*it);
        it = neuronsList->erase(it);
    }
    qDebug() << "EEE";
    for(list<Connection *>::iterator it = connectionsList->begin(); it != connectionsList->end();) {
        if (*it)
            delete (*it);
        it = connectionsList->erase(it);
    }
    qDebug() << "FFF";
    for(list<Cluster *>::iterator it = clustersList->begin(); it != clustersList->end();) {
        delete(*it);
        it = clustersList->erase(it);
    }
    qDebug() << "GGG";
    //delete neuronsList;
    //delete connectionsList;
    //delete clustersList;
}
//C
Neuron* Esoinn::addNeuron(double *weights)
{
    Neuron* neuron = new Neuron(dimensionSize, weights);
    neuronsList->push_back(neuron);
    return neuron;
}
//C
Neuron* Esoinn::addNeuron(double * weights, double threshold)
{
    Neuron* neuron = new Neuron(dimensionSize, weights);
    neuronsList->push_back(neuron);
    neuron->similarityThreshold = threshold;
    return neuron;
}
//C
Neuron* Esoinn::addNeuron(Neuron *neuronToAdd)
{
	neuronsList->push_back(neuronToAdd);
	return neuronToAdd;
}
//NN + NC + NCl*NN + NNe*NNe
void Esoinn::removeNeuron(Neuron* neuronToRemove)
{
	
	for(list<Neuron*>::iterator it = neuronsList->begin(); it != neuronsList->end();)
	{
		if((*it) == neuronToRemove)
        {
			it = neuronsList->erase(it);
			break;
		}
		else ++it;
	}
	
	for(list<Connection*>::iterator it = connectionsList->begin(); it != connectionsList->end();)
	{
		if(((*it)->first == neuronToRemove) || ((*it)->second == neuronToRemove))
        {
			it = connectionsList->erase(it);
		}
		else ++it;
	}
	
	
	for(list<Cluster*>::iterator it = clustersList->begin(); it != clustersList->end(); ++it)
	{
		for(list<Neuron*>::iterator j = (*it)->neuronsList->begin(); j != (*it)->neuronsList->end();)
		{
			if((*j) == neuronToRemove)
            {
				j = (*it)->neuronsList->erase(j);
				break;
			}
			else ++j;
		}
	}
	
	if (neuronToRemove->neighboursList == NULL) 
		return;	
	
	for(list<Connection*>::iterator it = neuronToRemove->neighboursList->begin(); it != neuronToRemove->neighboursList->end(); ++it)
	{
		for(list<Connection*>::iterator j = (*it)->getNeighbourNeuron(neuronToRemove)->neighboursList->begin(); j != (*it)->getNeighbourNeuron(neuronToRemove)->neighboursList->end();)
		{
			if((*j) == (*it))
            {
				j = (*it)->getNeighbourNeuron(neuronToRemove)->neighboursList->erase(j);
			}
			else ++j;
		}
	}
	
}
//NN + NC + NCl*NN + NNe*NNe
void Esoinn::removeNeuron(list<Neuron*>::iterator &neuronToRemove)
{
    Neuron* buf = *neuronToRemove;
	neuronToRemove = neuronsList->erase(neuronToRemove);

	for(list<Connection*>::iterator it = connectionsList->begin(); it != connectionsList->end();)
	{
		if(((*it)->first == buf) || ((*it)->second == buf))
        {
			it = connectionsList->erase(it);
		}
		else ++it;
	}
	
	for(list<Cluster*>::iterator it = clustersList->begin(); it != clustersList->end(); ++it)
    {
        (*it)->neuronsList->remove(buf);
    }
	if (buf == NULL) return;
    if (buf->neighboursList == NULL) return;
	for(list<Connection*>::iterator it = buf->neighboursList->begin(); it != buf->neighboursList->end(); ++it)
	{
        Connection * con = *it;
        con->getNeighbourNeuron(buf)->neighboursList->remove(con);
    }
}
//C
Cluster* Esoinn::addCluster(Neuron* delegatorOfCluster)
{
    int ident = clustersList->size();
	clustersList->push_back(new Cluster(delegatorOfCluster, ++ident));
	return clustersList->back();
}
//C
Connection * Esoinn::addConnection(Neuron * first, Neuron * second)
{
	Connection * connection = new Connection(first, second);
	this->connectionsList->push_back(connection);
	first->neighboursList->push_back(connection);
	second->neighboursList->push_back(connection);
	return connection;
}
//NC + NNe*2
void Esoinn::removeConnection(list<Connection*>::iterator &edgeToRemove)
{
	Connection* edge = (*edgeToRemove); 
	edgeToRemove = connectionsList->erase(edgeToRemove);
	
	for(list<Connection*>::iterator j = edge->first->neighboursList->begin(); j != edge->first->neighboursList->end();)
	{
		if((*j) == edge)
        {
            j = edge->first->neighboursList->erase(j);
			break;
		}
		else ++j;
	}
	
	for(list<Connection*>::iterator j = edge->second->neighboursList->begin(); j != edge->second->neighboursList->end();)
	{
		if((*j) == edge)
        {
			j = edge->second->neighboursList->erase(j);
			break;
		}
		else ++j;
    }
}
//NC + NNe*2
void Esoinn::removeConnection(Connection *edge)
{
	for(list<Connection*>::iterator it = connectionsList->begin(); it != connectionsList->end();){
		if(edge == (*it))
        {
			it = connectionsList->erase(it);
			for(list<Connection*>::iterator j = edge->first->neighboursList->begin(); j != edge->first->neighboursList->end(); )
			{
				if((*j) == edge)
                {
					j = edge->first->neighboursList->erase(j);
					break;
				}
				else ++j;
			}
			
			for(list<Connection*>::iterator j = edge->second->neighboursList->begin(); j != edge->second->neighboursList->end();)
			{
				if((*j) == edge)
                {
					j = edge->second->neighboursList->erase(j);
					break;
				}
				else ++j;
			}
			break;
		}
		else ++it;
    }
}
//NC +NNe*2
void Esoinn::removeConnection(Neuron* first, Neuron* second)
{
	Connection *edge;
	for(list<Connection*>::iterator it = connectionsList->begin(); it != connectionsList->end();)
	{
		edge = (*it);
		if(((edge->first == first) && (edge->second == second)) || ((edge->first == second) && (edge->second == first)))
        {
			it = connectionsList->erase(it);		
			for(list<Connection*>::iterator j = edge->first->neighboursList->begin(); j != edge->first->neighboursList->end();)
			{
				if ((*j) == edge)
                {
					j = edge->first->neighboursList->erase(j);
					break;
				}
				else ++j;
			}
			for(list<Connection*>::iterator j = edge->second->neighboursList->begin(); j != edge->second->neighboursList->end();)
			{
				if((*j) == edge)
                {
					j = edge->second->neighboursList->erase(j);
					break;
				}
				else ++j;
			}
			break;
		}
		else ++it;
		
	}
}
//NC
Connection * Esoinn::getConnection(Neuron * first, Neuron * second)
{
	for (list<Connection*>::iterator it = connectionsList->begin(); it != connectionsList->end(); ++it)
	{
        if((((*it)->first == first) && ((*it)->second == second)) || (((*it)->first == second) && ((*it)->second == first)))
		{
            return (*it);
	    }
	}
	return NULL;
}

double Esoinn::calcEuclidNorm(double * vector1, double * vector2, int n)
{
	double res = 0.0;
	for(int i = 0; i < n; i++)
	{
        res += pow(vector1[i] - vector2[i], 2);
	}
	res = sqrt(res);
	return res;
}

double Esoinn::calcHemmingNorm(double * vector1, double * vector2, int n)
{
	double res = 0.0;
	for(int i = 0; i < n; ++i)
	{
		res += (int)vector1[i] != (int)vector2[i] ? 1 : 0;
	}
	return res;
}

double Esoinn::calcDistance(double * a, double * b)
{
    return calcEuclidNorm(a, b, dimensionSize);
}
//NNe
double Esoinn::calcMeanDistance(Neuron * neuron)
{
	double res = 0.0;
    //if (neuron->getId() == -1){
        /*double min = INF;
        for (list<Neuron*>::iterator it = neuronsList->begin(); it != neuronsList->end(); ++it){
            if ((*it) != neuron){
                double temp = calcDistance(neuron->weights, (*it)->weights);
                if (temp < min)
                    min = temp;
            }
        }
        return min;*/
    //    return res;
   // }
    Neuron * tmp;
    for (list<Connection*>::iterator it = neuron->neighboursList->begin(); it != neuron->neighboursList->end(); ++it)
	{
        tmp = (*it)->getNeighbourNeuron(neuron);
        res += calcDistance(neuron->weights, tmp->weights);
    }
    if (neuron->neighboursList->size() == 0)
        res = 0;
    else res /= neuron->neighboursList->size();
	return res;
}
//NNe
double Esoinn::calcPoint(Neuron * neuron)
{
	return 1.0 / pow(1 + calcMeanDistance(neuron), 2);
}
//NN
bool Esoinn::findWiner(double *inputVector, Neuron *&firstWinner, Neuron *&secondWinner)
{
    firstWinner = NULL, secondWinner = NULL;
    double dist, firstMinDist = INF, secondMinDist = INF;
    int neuronsCnt = neuronsList->size();
    if (neuronsCnt < 2)
        return false;
    for(list<Neuron*>::iterator it = neuronsList->begin(); it != neuronsList->end(); ++it)
	{
        dist = calcDistance((*it)->weights, inputVector);//error here

        if(dist < firstMinDist)
		{
			secondWinner = firstWinner;
            secondMinDist = firstMinDist;
            firstMinDist = dist;
            firstWinner = (*it);
        }
        else if (dist < secondMinDist)
		{
            secondMinDist = dist;
            secondWinner = (*it);
        }
    }
    return true;
}

//NN
double Esoinn::similarityThreshold(Neuron* neuron)
{
	double dist = 0.0;
    if(!neuron->neighboursList->size()) 
	{
        dist = INF;
        for(list<Neuron*>::iterator it = neuronsList->begin(); it != neuronsList->end(); ++it) 
		{
            if((*it) != neuron) 
			{
                double distCurrent = calcDistance(neuron->weights, (*it)->weights);
                dist = min(dist, distCurrent);
            }
        }
    } 
	else 
	{
        dist = -INF;
        for(list<Connection*>::iterator it = neuron->neighboursList->begin(); it != neuron->neighboursList->end(); ++it) 
		{
            double distCurrent = calcDistance(neuron->weights, (*it)->getNeighbourNeuron(neuron)->weights);
            dist =  max(dist, distCurrent);
        }
    }
    return dist;
}
//NN
bool Esoinn::isWithinThreshold(Neuron* firstWinner, Neuron* secondWinner, double* inputVector)
{
    if(calcDistance(inputVector, firstWinner->weights) > similarityThreshold(firstWinner)) 
	{
        return false;
    }
    if(calcDistance(inputVector, secondWinner->weights) > similarityThreshold(secondWinner)) 
	{
        return false;
    }
    return true;
}

//C
double Esoinn::densityThreshold(double mean, double max)
{
    double threshold;
    if(2.0 * mean >= max)
	{
    	threshold = 0.0;
	}
	else if(3.0 * mean >= max && max > 2.0 * mean)
	{  
		threshold = 0.5;
	}
	else threshold = 1.0;
    return threshold;
}
//NCN*4
bool Esoinn::needUniteClusters(Neuron *first, Neuron *second)
{	
    Cluster *A = first->getCluster();
	Cluster *B = second->getCluster();
	double meanA = A->calcMeanDensity();
	double meanB = B->calcMeanDensity();
    //if (meanA < 1e-10 || meanB < 1e-10) return false;
    //qDebug() << "B";
    double thresholdA = densityThreshold(meanA, A->findApex()->getDensity());
    double thresholdB = densityThreshold(meanB, B->findApex()->getDensity());
	double minAB = min(first->getDensity(), second->getDensity());
    //qDebug() << meanA << meanB << thresholdA << thresholdB << minAB;
    //if ((minAB > thresholdA * A->getApex()->getDensity() && minAB > thresholdB * B->getApex()->getDensity()) == true)
     //   qDebug() << "TRUE";
    return (minAB > thresholdA * A->getApex()->getDensity() && minAB > thresholdB * B->getApex()->getDensity());
}
//NCN*2
void Esoinn::uniteClusters(Neuron* a, Neuron* b)
{
    //int classId = min(a->getId(), b->getId());
     /*for(list<Neuron*>::iterator it = neuronsList->begin(); it != neuronsList->end(); ++it)
	 {
        if((*it)->getId() == a->getId() || (*it)->getId() == b->getId()) 
		{
            (*it)->setId(classId);
        }
    }*/
//qDebug() << a->getId() << b->getId();
    Cluster *A, *B;
    A = a->getCluster(), B = b->getCluster();
    if(A->getId() < B->getId())
    {
    	for(list<Neuron*>::iterator it = B->neuronsList->begin(); it != B->neuronsList->end(); ++it)
    	{
    		A->neuronsList->push_back((*it));
            (*it)->setArea(A);
    	}
        B->neuronsList->clear();
    }
    else
    {
    	for(list<Neuron*>::iterator it = A->neuronsList->begin(); it != A->neuronsList->end(); ++it)
    	{
            B->neuronsList->push_back((*it));
            (*it)->setArea(B);
    	}

        A->neuronsList->clear();
    }

}
//4*NCN
bool Esoinn::needAddConnection(Neuron *first, Neuron *second)
{
	if (first->getId() == -1 || second->getId() == -1) return true;
	if (first->getId() == second->getId()) return true;
	
    if (first->getId() != second->getId() && needUniteClusters(first, second)) return true;
	return false;
}
//NNe
void Esoinn::updateDensity(Neuron* winner)
{
    winner->point += calcPoint(winner);
    winner->incSignal();
    double density = winner->point / winner->allTimeWin;
    //qDebug() << winner->getDensity() << density;
    winner->setDensity(density);
    //qDebug() << winner->getDensity();
}
//NNe
void Esoinn::adaptWeights(Neuron *&winner, double* inputVector)
{
	double e1 = 1.0 / winner->getCountSignals();
    double e2 = 1.0 / (100 * winner->getCountSignals());
    for(int i = 0; i < winner->getDim(); i++)
	{
        //qDebug() << "BEFORE";
        //qDebug() << winner->weights[i];
        winner->weights[i] += e1 * (inputVector[i] - winner->weights[i]);
        //qDebug() << winner->weights[i];
    }
    for(list<Connection*>::iterator it = winner->neighboursList->begin(); it != winner->neighboursList->end(); ++it)
	{
        for(int i = 0; i < winner->getDim(); i++)
		{
            (*it)->getNeighbourNeuron(winner)->weights[i] += e2 * (inputVector[i] - (*it)->getNeighbourNeuron(winner)->weights[i]);
        }
    }
}
//NC*NC + NC*NNe*2
void Esoinn::removeOldConnections()
{
	for (list<Connection*>::iterator it = connectionsList->begin(); it != connectionsList->end();)
	{
        if ((*it)->getAge() > maximalConnectionAge)
		{
            removeConnection(it);
        }
        else ++it;
    }
}
//NNe*NNe?
void path(Neuron* top, Cluster *bag)
{
	top->setArea(bag);
	if(bag == NULL) return;
	if(bag->neuronsList == NULL) return;
	if(top != bag->getApex()) bag->neuronsList->push_back(top);
	for(list<Connection*>::iterator it = top->neighboursList->begin(); it != top->neighboursList->end(); ++it)
	{
		if((*it)->getNeighbourNeuron(top)->getId() == -1 && (*it)->getNeighbourNeuron(top)->getDensity() < top->getDensity())
		{
			path((*it)->getNeighbourNeuron(top), bag);
		}
	}
}
//C
bool cmp_density(Neuron *a, Neuron *b)
{
	return a->getDensity() > b->getDensity();
}
//NN*NN
void Esoinn::markClasses()
{
	list<Neuron*> vertexQueue;
	for(list<Neuron*>::iterator it = neuronsList->begin(); it != neuronsList->end(); ++it)
	{
        (*it)->setId(-1);
		vertexQueue.push_back(*it);
	}
	clustersList->clear();
	vertexQueue.sort(cmp_density);

	for(list<Neuron*>::iterator it = vertexQueue.begin(); it != vertexQueue.end(); ++it)
	{
		if((*it)->getId() == -1) path((*it), addCluster(*it));
	}
}
//NCN*2*NC + NCN*2*NCl
void Esoinn::separateToSubclasses()
{
	Neuron *a, *b;
    for(list<Connection*>::iterator it = connectionsList->begin(); it != connectionsList->end();)
	{
        bool need_iter_inc = true;
		a = (*it)->first, b = (*it)->second;
		if(a->getId() != b->getId())
		{
			if(needUniteClusters(a, b))
			{
				for(list<Cluster*>::iterator j = clustersList->begin(); j != clustersList->end();)
				{
					if((*j) == b->getCluster())
                    {
						j = clustersList->erase(j);
						break;
					}
					else ++j;
				}
                uniteClusters(a, b);

			}
            else
            {
                if (getConnection(a,b)){
                    removeConnection(it);
                    need_iter_inc = false;
                }
            }
		}
        if (need_iter_inc)
            it++;
	}
}
//NN+NN*(NN + NC + NCl*NN + NNe*NNe)
void Esoinn::removeNoise()
{
	double meanDensityA = 0.0;
    for (list<Neuron*>::iterator it = neuronsList->begin(); it != neuronsList->end(); ++it)
	{
        meanDensityA += (*it)->getDensity();
    }
	meanDensityA /= neuronsList->size();
    /*int win_cnt_temp = 0;
    for (list<Neuron*>::iterator it = neuronsList->begin(); it != neuronsList->end(); it++){
        if ((*it)->getCountSignals() > 0)
            win_cnt_temp++;
    }
    qDebug() << "WIN:" << win_cnt_temp << (this->LT % this->lambda);*/

    //meanDensityA /= 2;
    //qDebug() << "SIZEb: " << neuronsList->size();
	for(list<Neuron*>::iterator it = neuronsList->begin(); it != neuronsList->end();)
	{
		if ((*it) == NULL) return;
		if ((*it)->neighboursList == NULL) return;
		if(((*it)->neighboursList->size() == 2) && ((*it)->getDensity() < c1 * meanDensityA))
		{
            //qDebug() << (*it)->getCountSignals() << (*it)->getDensity();
            //qDebug() << c1 * meanDensityA << " " << (*it)->getDensity() << (*it)->getCountSignals();
            removeNeuron(it);
		}
        else if(((*it)->neighboursList->size() == 1) && ((*it)->getDensity() < c2 * meanDensityA))
		{

            //qDebug() << (*it)->getCountSignals() << (*it)->getDensity();
            //qDebug() << c2 * meanDensityA << " " << (*it)->getDensity()<< (*it)->getCountSignals();
            removeNeuron(it);
		}

        else if((*it)->neighboursList->size() == 0)
        {
            //qDebug() << (*it)->getCountSignals();
            removeNeuron(it);
		}
		else ++it;
	}

    /*win_cnt_temp = 0;
    for (list<Neuron*>::iterator it = neuronsList->begin(); it != neuronsList->end(); it++){
        if ((*it)->getCountSignals() > 0)
            win_cnt_temp++;
    }
    qDebug() << "WIN:" << win_cnt_temp << (this->LT % this->lambda);*/
    //qDebug() << "SIZEe: " << neuronsList->size();
}
//NN*NN   +   NCN*2*NC + NCN*2*NCl   +  NN+NN*(NN + NC + NCl*NN + NNe*NNe)
void Esoinn::updateClassLabels()
{
    markClasses();
    separateToSubclasses();
    removeNoise();
}

//TODO: implement this function
void Esoinn::inputSignal(double* inputVector){
/*-----------------1.Initialize-set-of-2-neurons-with-2-first-weights-taken-from-input*/
    Cluster* buf;
	if (neuronsList->size() < 2)//better count of all input signals
    {    
		Neuron* neuron = addNeuron(inputVector);
		//if(addCluster(neuron) == NULL)return;
		buf = addCluster(neuron);
		buf->setId(-1);
        neuron->setArea(buf);
        return;
    }

/*-----------------1.end--------------------------------------------------------------*/

/*-----------------2.Finding-first-and-second-winner-for-input-signal-----------------*/
    Neuron *firstWinner = NULL, *secondWinner = NULL;
    findWiner(inputVector, firstWinner, secondWinner);
/*-----------------2.end-------------------------------------------------------------*/
/*-----------------3.add-neuron-if-the-distance-between-inputVector-and-winner-or-secondWinner-is-greater-than-threshold-------*/
    if(!isWithinThreshold(firstWinner, secondWinner, inputVector))
    {
    	Neuron* neuron = addNeuron(inputVector);
    	buf = addCluster(neuron);
    	buf->setId(-1);
    	neuron->setArea(buf);
    	return;
    }
/*-----------------3.end--------------------------------------------------------------*/
/*-----------------4.increase-age-of-connection,-which-belongs-to-winner--------------*/
    for (list<Connection*>::iterator it = firstWinner->neighboursList->begin(); it != firstWinner->neighboursList->end(); ++it)
	{
        (*it)->incAge();
    }
/*----------------4.end.--------------------------------------------------------------*/

/*----------------5.To-create-connections-between-winner-and-secondWinner-if necessary*/
    Connection* edge = getConnection(firstWinner, secondWinner);
    if(needAddConnection(firstWinner, secondWinner))
	{
    	if(!edge)
		{
            addConnection(firstWinner, secondWinner);
            //Cluster::unite(winner->getCluster(), secondWinner->getCluster());
        }
        else edge->setAge(0);
    }
    else if (edge != NULL) 
        removeConnection(edge);
	/*-----------------5.end.----------------------------------------------------------*/

    /*-----------------6.Update the density of winner----------------------------------*/
    updateDensity(firstWinner);
    /*-----------------6.end.----------------------------------------------------------*/

    /*-----------------7.Increase-signals-of--neuron-winner----------------------------*/
    //firstWinner->incSignal();
    /*-----------------7.end.----------------------------------------------------------*/

    /*-----------------8.Adapt weight vectors of winner and it's neighbours------------*/
    //qDebug() << firstWinner->weights[0] << firstWinner->weights[1];
    adaptWeights(firstWinner, inputVector);
    //qDebug() << firstWinner->weights[0] << firstWinner->weights[1];
    /*-----------------8.end.-----------------------------------------------------------*/

    /*-----------------9.Find-old-edges-and-remove-them---------------------------------*/
    removeOldConnections();
    /*-----------------9.end.-----------------------------------------------------------*/

    /*---------------- 10.Separate-all-classes-on--subclasses---------------------------*/
    if(!(this->LT % this->lambda)) updateClassLabels();
	/*---------------- 10.end.----------------------------------------------------------*/
	/*-----------------11.-Delete-nodes-polluted-by-noise-------  ----------------------*/		
    this->LT++;
    /*-----------------11.end.----------------------------------------------------------*/

}

void Esoinn::writeStructureToFile(string fileName)
{
    std::ofstream out(fileName.c_str(),  std::ofstream::out);
    out << neuronsList->size() << "\n";
    for(NeuronIterator it = neuronsList->begin(); it != neuronsList->end(); ++it)
	{
        out << (*it)->weights[0] << " " << (*it)->weights[1] << " ";
        for(EdgeIterator it2 = (*it)->neighboursList->begin(); it2 != (*it)->neighboursList->end(); ++it2)
		{
            Neuron *n;
            /*if ((*it2)->first != (*it)) n = (*it2)->first;
            else n = (*it2)->second;
            */
            n = (*it2)->getNeighbourNeuron(*it);
			int cnt = 0;
            for(NeuronIterator it3 = neuronsList->begin(); it3 != neuronsList->end(); ++it3)
			{
                if (n == (*it3))
				{
                    out << cnt << " ";
                }
                cnt++;
            } 
        }
        out << "\n";
    }
}
double ** Esoinn::getStructure(){
    //std::ofstream out(fileName.c_str(),  std::ofstream::out);
    //std::ofstream ofs ("test.txt"
    double ** structure = new double * [neuronsList->size() + 1];
    structure[0] = new double[1];
    structure[0][0] = neuronsList->size();
    int i = 1;
    for(list<Neuron*>::iterator it = neuronsList->begin(); it != neuronsList->end(); ++it){
        structure[i] = new double[neuronsList->size() + 4];
        structure[i][0] = (*it)->weights[0];
        structure[i][1] = (*it)->weights[1];
        structure[i][2] = (*it)->getCountSignals();
        structure[i][3] = (*it)->getCluster()->getId();
        //cout << structure[i][0] << " " << structure[i][1] << " " << i << " " << neuronsList->size() << endl;
        if ((*it)->neighboursList->size() == 0){
            structure[i][4] = -1;
        }
        int j = 4;
        for(list<Connection*>::iterator it2 = (*it)->neighboursList->begin(); it2 != (*it)->neighboursList->end(); ++it2){
            Neuron * n;
            if ((*it2)->first != (*it))
                n = (*it2)->first;
            else n = (*it2)->second;
            int cnt = 0;
            for(list<Neuron*>::iterator it3 = neuronsList->begin(); it3 != neuronsList->end(); ++it3){
                //cout << n << " " << *it3 << endl;
                if (n == (*it3)){
                    structure[i][j] = cnt;
                    structure[i][j + 1] = -1;
                    j++;
                    break;
                }
                cnt++;
            }
        }
        i++;
    }
    //cout << "b" << structure[2][0];
    return structure;
}

void Esoinn::clearWinners(){
    for (list<Neuron*>::iterator it = neuronsList->begin(); it != neuronsList->end(); ++it)
    {
        (*it)->winInThisIter = false;
    }
}

void Esoinn::removeNeuronFully(Neuron * n){
    if (n->neighboursList->size() > 0){
        for(list<Connection *>::iterator it = n->neighboursList->begin(); it != n->neighboursList->end();) {
            qDebug() <<*it << (*it)->first;
            Connection * c = *it;
            qDebug() <<"N1";
            it = n->neighboursList->erase(it);
            qDebug() <<"N2" << c;
            if (c){
                qDebug() << c->getAge();
                Neuron * neigh = c->getNeighbourNeuron(n);
                neigh->neighboursList->remove(c);
                connectionsList->remove(c);
                delete c;
            }
            qDebug() <<"N3";
        }
    }
    n->getCluster()->removeNeuron(n);
    delete n;
}







