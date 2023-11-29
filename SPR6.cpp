#include <iostream>
#include <string>
#include <vector>
using namespace std;

//Leaf
class TelecommunicationalComponent {
protected:
    int throughput; // Пропускна здатність
    bool activityState; //Стан активності
public:
    TelecommunicationalComponent(int throughput, bool activityState)
        :throughput(throughput),activityState(activityState){}
    virtual void getInfo() = 0; 
    virtual ~TelecommunicationalComponent() {}

};

//Лінія зв язку
class TelecommunicationLine : public TelecommunicationalComponent {
private:
    int latency; //Латентність,тобто час,витрачений на відправку пакету та підтвердження його доставки
    string typeSignal; //Тип сигналу,аналоговий чи цифровий
public:
    TelecommunicationLine(int throughput, bool activityState, int latency, string typeSignal)
        :TelecommunicationalComponent(throughput, activityState), latency(latency), typeSignal(typeSignal) { }
    void getInfo() {
        cout<< "Tel.Line with characteristics: \nThoughput:" << throughput
            << "\n Activity state:" << activityState
            << "\n Latency:" << latency
            << "\n type of signal:" << typeSignal << endl;
    }
};

//Мережевий вузол(типу маршрутизатор чи комутатор)
class NetworkNode : public TelecommunicationalComponent {
private:
    int numberOfPorts;//Кількість портів
public:
    NetworkNode(int throughput, bool activityState, int numberOfPorts) 
        : TelecommunicationalComponent(throughput, activityState), numberOfPorts(numberOfPorts) { }
    void getInfo() {
        cout<< "Network node with characteristic: \nThoughput:" << throughput
            << "\n Activity state:" << activityState
            << "\n number of ports is:" << numberOfPorts << endl;
    }
};

//Мережевий рівень,об єднуючий вузли та лінії зв язку
class NetworkLevel {
private:
   vector<TelecommunicationalComponent*> components;
public:
    void addComponents(TelecommunicationalComponent* component) {
        components.push_back(component);
    }
    void getInfo() {
        cout << "In this network level had:" << endl;
        for (auto& component : components) {
            component->getInfo();
        }
    }
    ~NetworkLevel(){}
};

int main()
{
    NetworkLevel network;
    TelecommunicationLine* line = new TelecommunicationLine(150, true, 5, "Digital");
    NetworkNode* node = new NetworkNode(300, false, 8);
    network.addComponents(line); network.addComponents(node);

    network.getInfo();
    return 0;
}

