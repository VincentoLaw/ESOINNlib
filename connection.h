
class Neuron;
//Also can be called as edge
class Connection {

	private:

		int age;
        int id;
        int count;

	public:

		Connection(Neuron * first, Neuron * second);
		~Connection();
		Neuron * first, * second;
        //increasing age of connection by n
        void incAge();
        Neuron * getNeighbourNeuron(Neuron* node);
        void setAge(int age);
        int getId();
        int getAge();
		void remove();
};
