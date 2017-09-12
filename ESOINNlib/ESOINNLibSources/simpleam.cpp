#include "simpleam.h"

/*AMConnection::AMConnection(){}

AMNeuron::AMNeuron(){
    connections = new list<AMConnection>();
}

SimpleAM::SimpleAM(){}

SimpleAM::SimpleAM(Esoinn * _senses, int senses_count)
{
    senses = new Esoinn*[senses_count];
    sensesCount = senses_count;
    neurons = new list<AMNeuron>*[senses_count];
    for (int i = 0; i < senses_count; i++){
        senses[i] = _senses[i];
        neurons[i] = new list<AMNeuron>();
    }
}

SimpleAM::~SimpleAM()
{

}

void SimpleAM::learn(double ** inputs){
    list<AMNeuron *> active_neurons = new list<AMNeuron *>();
    for (int i = 0; i < sensesCount; i++){
        senses[i].inputSignal(inputs[i]);
        //обновление списка нейронов apex-ов кластеров
        auto to_delete = new list<AMNeuron>();
        for (auto &it : neurons[i]){
            it->neuron = senses[i].getNeuronPatern(it->neuron);
            if (!(it->neuron))
                to_delete->push_back(it);
        }
        for (auto &it : to_delete)
            neurons[i].remove(it);
        //to_delete->clear();TODO:тут полное удаление нейрона

        //активация нейронов от входных данных
        vertex new_pattern = senses[i].getPattern(inputs[i]);
        AMNeuron * active_neuron = nullptr;
        for (auto &it : neurons[i]){
            if (it->neuron == new_pattern){
                active_neuron = *it;
            }
            else {
                *it->timesFromActive++;
            }
        }
        //в случае, если такой apex ещё не активировался, он добавляется в список apex-ов
        if (!active_neuron){
            AMNeuron * amn = new AMNeuron();
            amn->neuron = new_pattern;
            neurons[i].push_back(amn);
            active_neuron = amn;
        }
        active_neurons.push_back(active_neuron);
        if (active_neuron->timesActive == 0)
            active_neuron->timesFromActive = 1;
        active_neuron->timesActive++;
    }
    for(auto &n1 : active_neurons){
        for (auto &n2 : active_neurons){
            if (n1 != n2){
                bool con_exist = false;
                AMConnection amc = NULL;
                for (auto &c : (*n1)->connections)
                    if ((*c)->neuron1 == n2->neuron || (*c)->neuron2 == n2->neuron){
                        con_exist = true;
                        amc = *c;
                    }
                if (!con_exist){
                    auto con = new AMConnection();
                    con->neuron1 = *n1;
                    con->neuron2 = *n2;
                    (*n1)->connections.push_back(con);
                    (*n2)->connections.push_back(con);
                }
                else{
                    amc->weight = (amc->weight + (amc->neuron1->timesActive / amc->neuron1->timesFromActive
                                                  + amc->neuron2->timesActive / amc->neuron2->timesFromActive)/2)/2;
                }
            }
        }
    }
}

double ** SimpleAM::getAssotiation(double * input, int sense_id){
    vertex new_pattern = senses[sense_id].getPattern(input);
    if (new_pattern){
        AMNeuron * active_neuron = nullptr;
        for (auto &it : neurons[sense_id]){
            if (it->neuron == new_pattern){
                active_neuron = *it;
                break;
            }
        }
        if (active_neuron){
            double max_con = 0;
            AMNeuron * assot = nullptr;
            for(auto &cons : active_neuron->connections){
                if (max_con < cons->weight){
                    max_con = cons->weight;
                    assot = cons->neuron1 == active_neuron ? cons->neuron2 : cons->neuron1;
                }
            }
            double * result = new double[];
            for (int i = 0; i < ; i++)
                result[i] = assot->neuron->weights[i];
        }
    }
    else return NULL;
*/
    /*list<AMNeuron *> assotiations = new list<AMNeuron *>();
    for (int i = 0; i < sensesCount; i++){
        vertex new_pattern = senses[i].getPattern(inputs[i]);
        AMNeuron * active_neuron = nullptr;
        for (auto &it : neurons[i]){
            if (it->neuron == new_pattern){
                active_neuron = *it;
                break;
            }
        }
        double max_con = 0;
        AMNeuron * assot = nullptr;
        for(auto &cons : active_neuron->connections){
            if (max_con < cons->weight){
                max_con = cons->weight;
                assot = cons->neuron1 == active_neuron ? cons->neuron2 : cons->neuron1;
            }
        }
        if (assot)
            assotiations.push_back(assot);
    }
    for (auto &it : assotiations){

    }*/
/*}*/
