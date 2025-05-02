#include <iostream>
#include <vector>
#include <string>
using namespace std;

class HardwareComponent {
protected:
	string name;
public:
	HardwareComponent(string n) : name(n) {}
	virtual ~HardwareComponent() {}
	virtual void getSpecs() = 0;
	virtual float getPowerConsumption() = 0;
	string getName() {
		return name;
	}
};

class Overclockable {
public:
    virtual void overclock(float percentage) = 0;
};

class CPU : public HardwareComponent, public Overclockable {
private:
	int cores;
	float clockSpeed;
public:
	CPU(string n, int c, float cs) : HardwareComponent(n), cores(c), clockSpeed(cs)
	{}
	void getSpecs() override {
		cout << "CPU Specs - Cores: " << cores << ", Clock Speed: " << clockSpeed
		     << " GHz\n";
	}
	float getPowerConsumption() override {
		return cores * clockSpeed * 10;
	}
    void overclock(float percentage) override {
        clockSpeed *= percentage;
    }
};
class RAM : public HardwareComponent {
private:
	int size;
	string type;
public:
	RAM(string n, int s, string t) : HardwareComponent(n), size(s), type(t) {}
	void getSpecs() override {
		cout << "RAM Specs - Size: " << size << " GB, Type: " << type << "\n";
	}
	float getPowerConsumption() override {
		return size * 0.5;
	}
};
class GPU : public HardwareComponent, public Overclockable {
private:
	int vram;
	float clockSpeed;
public:
	GPU(string n, int v, float cs) : HardwareComponent(n), vram(v), clockSpeed(cs)
	{}
	void getSpecs() override {
		cout << "GPU Specs - VRAM: " << vram << " GB, Clock Speed: " << clockSpeed
		     << " GHz\n";
	}
	float getPowerConsumption() override {
		return vram * clockSpeed * 15;
	}
    void overclock(float percentage) override {
        clockSpeed *= percentage;
    }
};

int main()
{
    vector<HardwareComponent *> components;

    CPU *myCPU = new CPU("Intel i9", 12, 3.8);
    GPU *myGPU = new GPU("NVIDIA RTX 3080", 10, 1.7);

    components.push_back(myCPU);
    components.push_back(myGPU);

    cout << "Before Overclocking:\n";
    for (HardwareComponent *c : components)
    {
        cout << "Component: " << c->getName() << "\n";
        c->getSpecs();
        cout << "Power Consumption: " << c->getPowerConsumption() << "W\n\n";
    }

    myCPU->overclock(1.5);
    myGPU->overclock(1.25);

    cout << "\nAfter Overclocking:\n";
    for (HardwareComponent *c : components)
    {
        cout << "Component: " << c->getName() << "\n";
        c->getSpecs();
        cout << "Power Consumption: " << c->getPowerConsumption() << "W\n\n";
    }

    for (HardwareComponent *c : components)
    {
        delete c;
    }

    return 0;
}
