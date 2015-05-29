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
    this->maximalConnectionAge = maximalConnectionAge;
    this->lambda = lambda;
    this->c1 = c1;
    this->c2 = c2;
    this->LT = 0;
    clustersId = 0;
    //this->externalCalcDistance = distanceFunction;
}

Esoinn::Esoinn(int dimensionSize, int maximalConnectionAge, int lambda, double c1, double c2)//= &commonDistanceFunction
{
   	this->dimensionSize = dimensionSize;
    this->maximalConnectionAge = maximalConnectionAge;
    this->lambda = lambda;
    this->c1 = c1;
    this->c2 = c2;
    this->LT = 0;
    clustersId = 0;
}

Esoinn::Esoinn(string fileName){
    clustersId = 0;
    LT = 0;
    loadStateFromFile(fileName);
}


Esoinn::~Esoinn()
{
    for (auto &it: neuronsList)
        removeNeuron(it);
    neuronsList.clear();
    connectionsList.clear();
    clustersList.clear();
}

vertex Esoinn::addNeuron(double *weights)
{
    vertex neuron = vertex(new Neuron(dimensionSize, weights));
    //vertex neuron = make_shared<Neuron>(Neuron(dimensionSize, weights));
    //cout << neuron->weights[0]  << endl;
    neuronsList.push_back(neuron);
    return neuron;
}

vertex Esoinn::addNeuron(double * weights, double threshold)
{
    auto neuron = make_shared<Neuron>(Neuron(dimensionSize, weights));
    neuronsList.push_back(neuron);
    neuron->similarityThreshold = threshold;
    return neuron;
}

vertex Esoinn::addNeuron(vertex neuronToAdd)
{
    neuronsList.push_back(neuronToAdd);
	return neuronToAdd;
}

void Esoinn::removeNeuron(vertex neuronToRemove)
{
    //cout << "BEG " <<  neuronToRemove.use_count() << " ";
    for(auto it = connectionsList.begin(); it != connectionsList.end();)
	{
		if(((*it)->first == neuronToRemove) || ((*it)->second == neuronToRemove))
		{
            //cout << "A";
            vertex neigh = (*it)->getNeighbourNeuron(neuronToRemove);
            neigh->neighboursList.remove(*it);
            neuronToRemove->neighboursList.remove(*it);
            (*it)->first = nullptr;
            (*it)->second = nullptr;
            it = connectionsList.erase(it);
		}
		else ++it;
	}
	
    cluster buf;
    for(auto &it : clustersList)
	{
       int size1, size2;
       size1 = it->neuronsList.size();
       it->neuronsList.remove(neuronToRemove);
       size2 = it->neuronsList.size();
       if(abs(size2 - size1))
       {
            buf = it;
            if (it->getApex() == neuronToRemove)
            {

                it->setApex(nullptr);
                if(it->findApex())
                {
                    it->setId(it->getApex()->getId());
                }
                else
                {
                    it->setId(-1);
                }


            }
            break;
        }
  }
    if(!buf->neuronsList.size()) clustersList.remove(buf);
    neuronToRemove->neighboursList.clear();
    neuronToRemove->setCluster(nullptr);
    //cout << neuronToRemove.use_count() << endl;
}

cluster Esoinn::addCluster(vertex delegatorOfCluster)
{
    clustersList.push_back(make_shared<Cluster>(Cluster(delegatorOfCluster, ++clustersId)));
    return clustersList.back();
}

edge Esoinn::addConnection(vertex first, vertex second)
{
    auto connection = make_shared<Connection>(Connection(first, second));
    connectionsList.push_back(connection);
    first->neighboursList.push_back(connection);
    second->neighboursList.push_back(connection);
	return connection;
}

void Esoinn::removeConnection(edge d)
{
    d->first->neighboursList.remove(d);
    d->second->neighboursList.remove(d);
    d->first = nullptr;
    d->second = nullptr;
}

/*void Esoinn::removeConnection(vertex first, vertex second)
{
    edge d;
    for(auto it = connectionsList.begin(); it != connectionsList.end();)
	{
        d = (*it);
        if(((d->first == first) && (d->second == second)) || ((d->first == second) && (d->second == first)))
		{
            it = connectionsList.erase(it);
            for(auto j = d->first->neighboursList.begin(); j != d->first->neighboursList.end();)
			{
                if ((*j) == d)
				{
                    j = d->first->neighboursList.erase(j);
					break;
				}
				else ++j;
			}
            for(auto j = d->second->neighboursList.begin(); j != d->second->neighboursList.end();)
			{
                if((*j) == d)
				{
                    j = d->second->neighboursList.erase(j);
					break;
				}
				else ++j;
			}
			break;
		}
		else ++it;
		
	}
}*/

edge Esoinn::getConnection(vertex first, vertex second)
{
    for (auto &it : connectionsList)
	{
        if(((it->first == first) && (it->second == second)) || ((it->first == second) && (it->second == first)))
		{
            return it;
	    }
	}
    return nullptr;
}

double Esoinn::calcEuclidNorm(double * vector1, double * vector2, int n)
{
    auto res = 0.0;
    for(int i = 0; i < n; i++)
	{
        res += pow(vector1[i] - vector2[i], 2);
        //if (vector1[i] != 0)
        //    cout << "v1=" << vector1[i] << " ";
        //if (vector2[i] != 0)
        //    cout << "v2=" << vector2[i] << " ";
	}
    //if (res != 0)
    //    cout << "res1=" << res << endl;
	res = sqrt(res);
    //if (res != 0)
    //    cout << "res2=" << res << endl;
	return res;
}

double Esoinn::calcHemmingNorm(double * vector1, double * vector2, int n)
{
    auto res = 0.0;
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

double Esoinn::calcMeanDistance(vertex neuron)
{
    auto res = 0.0;
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
    vertex tmp;
    for (auto &it : neuron->neighboursList)
	{
        tmp = it->getNeighbourNeuron(neuron);
        res += calcDistance(neuron->weights, tmp->weights);
    }
    if (!neuron->neighboursList.size()) res = 0;
    else res /= neuron->neighboursList.size();
	return res;
}

double Esoinn::calcPoint(vertex neuron)
{
	return 1.0 / pow(1 + calcMeanDistance(neuron), 2);
}

bool Esoinn::findWiner(double *inputVector, vertex &firstWinner, vertex &secondWinner)
{
    firstWinner = nullptr, secondWinner = nullptr;
    double dist, firstMinDist = INF, secondMinDist = INF;
    int neuronsCnt = (int)neuronsList.size();
    if (neuronsCnt < 2) return false;
    for(auto &it : neuronsList)
	{
        dist = calcDistance(it->weights, inputVector);//error here

        if(dist < firstMinDist)
		{
			secondWinner = firstWinner;
            secondMinDist = firstMinDist;
            firstMinDist = dist;
            firstWinner = it;
        }
        else
        if (dist < secondMinDist)
		{
            secondMinDist = dist;
            secondWinner = it;
        }
    }
    return true;
}


double Esoinn::similarityThreshold(vertex neuron)
{
    auto dist = 0.0;
    if(!neuron->neighboursList.size())
	{
        dist = INF;
        for(auto &it : neuronsList)
		{
            if(it != neuron)
			{
                auto distCurrent = calcDistance(neuron->weights, it->weights);
                dist = min(dist, distCurrent);
            }
        }
    } 
	else 
	{
        dist = -INF;
        for(auto &it : neuron->neighboursList)
		{
            auto distCurrent = calcDistance(neuron->weights, it->getNeighbourNeuron(neuron)->weights);
            dist =  max(dist, distCurrent);
        }
    }
    return dist;
}

bool Esoinn::isWithinThreshold(vertex firstWinner, vertex secondWinner, double *inputVector)
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

bool Esoinn::needUniteClusters(vertex first, vertex second)
{	
    auto A = first->getCluster();
    auto B = second->getCluster();
    auto meanA = A->calcMeanDensity();
    auto meanB = B->calcMeanDensity();

    //qDebug() << "B";
    auto thresholdA = densityThreshold(meanA, A->findApex()->getDensity());
    auto thresholdB = densityThreshold(meanB, B->findApex()->getDensity());
    auto minAB = min(first->getDensity(), second->getDensity());
    //qDebug() << meanA << meanB << thresholdA << thresholdB << minAB;
    //if ((minAB > thresholdA * A->getApex()->getDensity() && minAB > thresholdB * B->getApex()->getDensity()) == true)
     //   qDebug() << "TRUE";
    return (minAB > thresholdA * A->getApex()->getDensity() && minAB > thresholdB * B->getApex()->getDensity());
}

void Esoinn::uniteClusters(vertex a, vertex b)
{
    auto A = a->getCluster();
    auto B = b->getCluster();

    for(auto &it : B->neuronsList)
    {
        A->neuronsList.push_back(it);
        it->setCluster(A);
        it->setId(A->getId());

    }
    B->neuronsList.clear();
    B->setApex(nullptr);
    clustersList.remove(B);

}

bool Esoinn::needAddConnection(vertex first, vertex second)
{
    if (!first->isClassified() || !second->isClassified()) return true;
    if (first->isClassified() && second->isClassified())
    {
        if (first->getId() == second->getId()) return true;
        if (first->getId() != second->getId() && needUniteClusters(first, second)) return true;
    }
	

	return false;
}

void Esoinn::updateDensity(vertex winner)
{
    winner->point += calcPoint(winner);//+= ?
    winner->incSignal();
    double density = winner->point / winner->allTimeWin;
    //qDebug() << winner->getDensity() << density;
    winner->setDensity(density);
    //qDebug() << winner->getDensity();
}

void Esoinn::adaptWeights(vertex &winner, double* inputVector)
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
    for(auto &it : winner->neighboursList)
	{
        for(int i = 0; i < winner->getDim(); i++)
		{
            it->getNeighbourNeuron(winner)->weights[i] += e2 * (inputVector[i] - it->getNeighbourNeuron(winner)->weights[i]);
        }
    }
}

void Esoinn::removeOldConnections()
{
    for (auto it = connectionsList.begin(); it != connectionsList.end();)
	{
        if ((*it)->getAge() > maximalConnectionAge)
		{
            removeConnection(*it);
            it = connectionsList.erase(it);
        }
        else ++it;
    }
}

void path(vertex top, cluster bag)
{
    top->setCluster(bag);
    top->setStatus(true);
    top->setId(bag->getId());
    if(top != bag->getApex()) bag->neuronsList.push_back(top);
    for(auto &it : top->neighboursList)
	{
        if(!it->getNeighbourNeuron(top)->isClassified() && it->getNeighbourNeuron(top)->getDensity() < top->getDensity())//?
		{
            path(it->getNeighbourNeuron(top), bag);
		}
	}
}

bool cmp_density(vertex a, vertex b)
{
	return a->getDensity() > b->getDensity();
}

void Esoinn::markClasses()
{
    list<vertex> vertexQueue;
    for(auto &it : neuronsList)
	{
        it->setStatus(false);
        it->setCluster(nullptr);
        it->setId(-1);
        vertexQueue.push_back(it);
	}
    for(auto &it : clustersList)
    {
        it->neuronsList.clear();
        it->setApex(nullptr);
    }
    clustersList.clear();
    //clustersId = 0;
	vertexQueue.sort(cmp_density);

    for(auto &it : vertexQueue)
	{
        if(!it->isClassified()) path(it, addCluster(it));
	}
}

void Esoinn::separateToSubclasses()
{
    vertex a, b;
    for(auto it = connectionsList.begin(); it != connectionsList.end();)
	{
        bool need_iter_inc = true;
		a = (*it)->first, b = (*it)->second;
		if(a->getId() != b->getId())
		{
            if (needUniteClusters(a, b))
            {
                uniteClusters(a, b);
            }
            else
            {
                if (getConnection(a, b)) // можно искать edge
                {
                    removeConnection(*it);
                    it = connectionsList.erase(it);
                    need_iter_inc = false;
                }
            }
		}
        if (need_iter_inc) it++;
	}
}

void Esoinn::removeNoise()
{
    auto meanDensityA = 0.0;
    for (auto &it : neuronsList) meanDensityA += it->getDensity();
    meanDensityA /= neuronsList.size();
    /*int win_cnt_temp = 0;
    for (list<Neuron*>::iterator it = neuronsList->begin(); it != neuronsList->end(); it++){
        if ((*it)->getCountSignals() > 0)
            win_cnt_temp++;
    }
    qDebug() << "WIN:" << win_cnt_temp << (this->LT % this->lambda);*/

    //meanDensityA /= 2;
    //qDebug() << "SIZEb: " << neuronsList->size();

    for(auto it = neuronsList.begin(); it != neuronsList.end();)
	{
        if(((*it)->neighboursList.size() == 2) && ((*it)->getDensity() < c1 * meanDensityA))
		{
            //qDebug() << (*it)->getCountSignals() << (*it)->getDensity();
            //qDebug() << c1 * meanDensityA << " " << (*it)->getDensity() << (*it)->getCountSignals();
            removeNeuron(*it);
            it = neuronsList.erase(it);
		}
        else if(((*it)->neighboursList.size() == 1) && ((*it)->getDensity() < c2 * meanDensityA))
		{

            //qDebug() << (*it)->getCountSignals() << (*it)->getDensity();
            //qDebug() << c2 * meanDensityA << " " << (*it)->getDensity()<< (*it)->getCountSignals();
            removeNeuron(*it);
            it = neuronsList.erase(it);
		}

        else if((*it)->neighboursList.size() == 0)
        {
            //qDebug() << (*it)->getCountSignals();
            removeNeuron(*it);
            it = neuronsList.erase(it);
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

void Esoinn::updateClassLabels()
{
    markClasses();

    separateToSubclasses();
    removeNoise();

    for(auto &it : clustersList)
    {
        if(!it->neuronsList.size()) qDebug() << "ho" << "\n";
    }
}

//TODO: implement this function
void Esoinn::inputSignal(double* inputVector)
{
/*-----------------1.Initialize-set-of-2-neurons-with-2-first-weights-taken-from-input*/
    if (neuronsList.size() < 2)//better count of all input signals
    {    
        addNeuron(inputVector);
        return;
    }
/*-----------------1.end--------------------------------------------------------------*/

/*-----------------2.Finding-first-and-second-winner-for-input-signal-----------------*/
    vertex firstWinner = nullptr;
    vertex secondWinner = nullptr;
    findWiner(inputVector, firstWinner, secondWinner);
/*-----------------2.end-------------------------------------------------------------*/
/*-----------------3.add-neuron-if-the-distance-between-inputVector-and-winner-or-secondWinner-is-greater-than-threshold-------*/
    if(!isWithinThreshold(firstWinner, secondWinner, inputVector))
    {
        addNeuron(inputVector);
    	return;
    }
/*-----------------3.end--------------------------------------------------------------*/
/*-----------------4.increase-age-of-connection,-which-belongs-to-winner--------------*/
    for (auto &it : firstWinner->neighboursList) it->incAge();

/*----------------4.end.--------------------------------------------------------------*/

/*----------------5.To-create-connections-between-winner-and-secondWinner-if necessary*/
    auto d = getConnection(firstWinner, secondWinner);
    if(needAddConnection(firstWinner, secondWinner))
	{
        if(!d)
		{
            addConnection(firstWinner, secondWinner);
        }
        else d->setAge(0);
    }
    else
    if (d)
    {
        removeConnection(d);
        connectionsList.remove(d);
    }
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
    if(!(this->LT % this->lambda))
    {
        updateClassLabels();

    }
	/*---------------- 10.end.----------------------------------------------------------*/
    /*-----------------11.-Delete-nodes-polluted-by-noise-------  ----------------------*/

    this->LT++;
    /*-----------------11.end.----------------------------------------------------------*/

}

 /*int* Esoinn::interpolation(int* pixels, int w1, int h1, int w2, int h2)
 {
    int* temp = new int[w2 * h2] ;
    // EDIT: added +1 to account for an early rounding problem
    int x_ratio = (int)((w1 << 16) / w2) + 1;
    int y_ratio = (int)((h1 << 16) / h2) + 1;

    int x2, y2;
    for (int i = 0; i < h2; ++i)
    {
        for (int j = 0; j < w2; ++j)
        {
            x2 = ((j * x_ratio) >> 16);
            y2 = ((i * y_ratio) >> 16);
            temp[(i * w2) + j] = pixels[(y2 * w1) + x2];
        }
    }
    return temp ;
}*/


void Esoinn::writeStructureToFile(string fileName)
{
    std::ofstream out(fileName.c_str(),  std::ofstream::out);
    out << neuronsList.size() << "\n";
    for(auto &it : neuronsList)
	{
        out << it->weights[0] << " " << it->weights[1] << " ";
        for(auto &it2 : it->neighboursList)
		{
            vertex n;
            /*if ((*it2)->first != (*it)) n = (*it2)->first;
            else n = (*it2)->second;
            */
            n = it2->getNeighbourNeuron(it);
            int cnt = 0;
            for(auto &it3 : neuronsList)
			{
                if (n == it3)
				{
                    out << cnt << " ";
                }
                cnt++;
            } 
        }
        out << "\n";
    }
}

string Esoinn::getCurrentParams(){
    return "Neurons count: " + to_string(neuronsList.size()) + ", Connections count: " + to_string(connectionsList.size()) + ", Clusters count: " + to_string(clustersList.size());
}

double ** Esoinn::getStructure()
{
    //std::ofstream out(fileName.c_str(),  std::ofstream::out);
    //std::ofstream ofs ("test.txt"
    double ** structure = new double * [neuronsList.size() + 1];
    structure[0] = new double[2];
    structure[0][0] = neuronsList.size();
    structure[0][1] = dimensionSize;
    int i = 1;
    for(auto &it : neuronsList)
    {
        structure[i] = new double[it->neighboursList.size() + 2 + dimensionSize];
        if (it->isClassified())
            structure[i][0] = it->getCluster()->getId();
        else structure[i][0] = -1;
        for (int k = 0; k < dimensionSize; k++)
            structure[i][k + 1] = it->weights[k];
        //cout << structure[i][0] << " " << structure[i][1] << " " << i << " " << neuronsList->size() << endl;
        if (!it->neighboursList.size()) structure[i][1 + dimensionSize] = -1;

        int j = 1 + dimensionSize;
        for(auto &it2 : it->neighboursList){
            vertex n;
            if (it2->first != it) n = it2->first;
            else n = it2->second;
            int cnt = 0;
            for(auto &it3 : neuronsList){
                //cout << n << " " << *it3 << endl;
                if (n == it3){
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
    return structure;
}

void Esoinn::clearWinners()
{
    for (auto &it : neuronsList) it->winInThisIter = false;
}

int Esoinn::getNeuronId(vertex neuron){
    int  neuron_ind = 0;
    for (auto &n : neuronsList){
        if (neuron == n)
            return neuron_ind;
        neuron_ind++;
    }
}

vertex Esoinn::getNeuronById(int id){
    int  neuron_ind = 0;
    for (auto &n : neuronsList)
    {
        if (neuron_ind == id) return n;
        neuron_ind++;
    }
}

void Esoinn::saveStateToFile(string fileName){
    ofstream file(fileName);
    file << dimensionSize << " " << maximalConnectionAge << " " << lambda << " " << c1 << " " << c2 << endl;
    file << neuronsList.size() << " " << connectionsList.size() << " " << clustersList.size() << endl;
    for(auto &it : neuronsList){
        for (int i = 0; i < dimensionSize; i++)
            file << it->weights[i] << " ";
        file << it->getNeuronData() << endl;
    }
    for (auto &it : connectionsList){
        file << it->getAge() << " " << getNeuronId(it->first) << " " << getNeuronId(it->second) << endl;
    }
    file << endl;
    for (auto &it : clustersList){
        file << it->getDensity() << " " << it->getId() << " " << getNeuronId(it->apex) << endl;
        file << it->neuronsList.size() << endl;
        for (auto &neuron : it->neuronsList)
            file << getNeuronId(neuron) << " ";
        file << endl;
    }
    file << endl;
}


void Esoinn::loadStateFromFile(string fileName){
    ifstream file(fileName);
    file >> dimensionSize >>  maximalConnectionAge >> lambda >> c1 >> c2;
    int neurons_list_size, connections_list_size, clusters_list_size;
    file >> neurons_list_size >> connections_list_size >> clusters_list_size;
    for(int i = 0; i < neurons_list_size; i++){
        double * w = new double[dimensionSize];
        for (int i = 0; i < dimensionSize; i++)
            file >> w[i];
        vertex n = addNeuron(w);
        double d1,d2,d3; int i1,i2,i3; bool b1;
        file >> d1 >> d2 >> b1 >> i1 >> d3 >> i2 >> i3;
        n->setNeuronData(d1, d2, b1, i1, d3 ,i2 ,i3);
    }
    for (int i = 0; i < connections_list_size; i++){
        int f_id, s_id, age;
        file >> age >> f_id >> s_id;
        vertex n1 = getNeuronById(f_id);
        vertex n2 = getNeuronById(s_id);
        auto con = addConnection(n1, n2);
        n1->neighboursList.push_back(con);
        n2->neighboursList.push_back(con);
        con->setAge(age);
    }
    for (int i = 0; i < clusters_list_size; i++){
        double dens;
        int id, neuronId, neuronsSize;
        file >> dens >> id >> neuronId >> neuronsSize;
        auto cl = addCluster(getNeuronById(neuronId));
        if (id == -1)
            id = clustersId++;
        cl->setId(id);
        cl->setDensity(dens);
        for (int j = 0; j < neuronsSize; j++){
            int n_id; file >> n_id;
            vertex neuron = getNeuronById(n_id);
            cl->neuronsList.push_back(neuron);
            neuron->setArea(cl);
        }
    }
}

bool comparator(cluster a, cluster b){
    return a->neuronsList.size() > b->neuronsList.size();
}

double ** Esoinn::getTopVectors(int cnt){
    vector<cluster> cl;
    for (auto &it: clustersList){
        cl.push_back(it);
    }
    sort(cl.begin(), cl.end(), comparator);
    double ** result = new double*[cnt];
    for (int i = 0; i < cnt; i++){
        result[i] = new double[27*27];
        if (cl[i]->apex != nullptr)
            for (int j = 0; j < 27*27; j++)
                result[i][j] = cl[i]->apex->weights[j];
        else result[i][0] = -1;
    }
    return result;
}

vertex Esoinn::getPattern(double * inputVector){
    vertex firstWinner = nullptr;
    vertex secondWinner = nullptr;
    findWiner(inputVector, firstWinner, secondWinner);
    if (firstWinner && firstWinner->getCluster())
        return firstWinner->getCluster()->getApex();
    else return nullptr;
}

vertex Esoinn::getNeuronPatern(vertex n){
    if (n->getCluster()){
        if (n->getCluster()->getApex() == n)
            return n;
        else return n->getCluster()->getApex();
    }
    else return nullptr;
}





