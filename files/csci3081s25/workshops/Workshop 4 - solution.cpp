#include <iostream>
#include <map>
#include <string>

// object classes

class ISandwich {
    public:
        virtual void printName() = 0;
        virtual std::string getName() = 0;
};

class IBLT : public ISandwich {
    public:
        virtual void printName() = 0;
        virtual std::string getName() = 0;
};

class ITuna : public ISandwich  {
    public:
        virtual void printName() = 0;
        virtual std::string getName() = 0;
};

class IPBJ : public ISandwich  {
    public:
        virtual void printName() = 0;
        virtual std::string getName() = 0;
};

class JJBLT : public IBLT {
    public:
    void printName() override {
        std::cout << "BLT from JJ\n";
    }
    std::string getName() override {
        return "JJBLT";
    }
};

class JJTuna : public ITuna {
    public:
    void printName() override {
        std::cout << "Tuna from JJ\n";
    }
    std::string getName() override {
        return "JJTuna";
    }   
};

class JJPBJ : public IPBJ {
    public:
    void printName() override {
        std::cout << "PBJ from JJ\n";
    }
    std::string getName() override {
        return "JJPBJ";
    }  
};

class SubwayBLT : public IBLT {
    public:
    void printName() override {
        std::cout << "BLT from Subway\n";
    }
    std::string getName() override {
        return "SubwayBLT";
    }  
};

class SubwayTuna : public ITuna {
    public:
    void printName() override {
        std::cout << "Tuna from Subway\n";
    }
    std::string getName() override {
        return "SubwayTuna";
    }  
};

class SubwayPBJ : public IPBJ {
    public:
    void printName() override {
        std::cout << "PBJ from Subway\n";
    }
    std::string getName() override {
        return "SubwayPBJ";
    }  
};

class PotbellyBLT : public IBLT {
    public:
    void printName() override {
        std::cout << "BLT from Potbelly\n";
    }
    std::string getName() override {
        return "PotbellyBLT";
    }  
};

class PotbellyTuna : public ITuna {
    public:
    void printName() override {
        std::cout << "Tuna from Potbelly\n";
    }
    std::string getName() override {
        return "PotbellyTuna";
    }  
};

class PotbellyPBJ : public IPBJ {
    public:
    void printName() override {
        std::cout << "PBJ from Potbelly\n";
    }
    std::string getName() override {
        return "PotbellyPBJ";
    }  
};

// abstract factory

class SandwichFactory {
    public:
        virtual IBLT* createBLT() = 0;
        virtual ITuna* createTuna() = 0;
        virtual IPBJ* createPBJ() = 0;
        virtual ~SandwichFactory() {}
};

class JJFactory : public SandwichFactory {
   public:
        IBLT* createBLT() override {
            return new JJBLT();
        }
        ITuna* createTuna() override {
            return new JJTuna();
        }
        IPBJ* createPBJ() override {
            return new JJPBJ();
        }
};

class SubwayFactory : public SandwichFactory {
   public:
        IBLT* createBLT() override {
            return new SubwayBLT();
        }
        ITuna* createTuna() override {
            return new SubwayTuna();
        }
        IPBJ* createPBJ() override {
            return new SubwayPBJ();
        }
};

class PotbellyFactory : public SandwichFactory {
   public:
        IBLT* createBLT() override {
            return new PotbellyBLT();
        }
        ITuna* createTuna() override {
            return new PotbellyTuna();
        }
        IPBJ* createPBJ() override {
            return new PotbellyPBJ();
        }
};

// singleton

class SandwichLogger {
    private:
        std::map<std::string, int> sales;
        SandwichLogger() {}
        static SandwichLogger* instance;
    public:
        ~SandwichLogger() { 
            showSales();
            delete instance;
        }
        SandwichLogger(SandwichLogger &other) = delete;
        void operator=(const SandwichLogger &other) = delete;
        static SandwichLogger* getInstance() {
            if (!instance) {
                static SandwichLogger instance;
                return &instance;
            }
            return instance;
        }
        void logSandwich(const std::string& sandwichName) {
            sales[sandwichName]++;
        }
        void showSales() const {
            std::cout << "\nSales:\n";
            for (const auto& pair : sales) {
                std::cout << pair.first << ": " << pair.second << "\n";
            }
        }
};

SandwichLogger* SandwichLogger::instance = nullptr;

// facade

class SandwichStore {
    public:
        void run() {
            
            SandwichLogger* logger = SandwichLogger::getInstance();
            
            std::cout << "Choose a store: (1) JJ, (2) Subway, (3) Potbelly, (0) Exit: ";
            int choice1;
            std::cin >> choice1;

            if (choice1 == 0) {
                return;
            }
            
            SandwichFactory* factory = nullptr;
            switch (choice1)
            {
            case 1:
                factory = new JJFactory();
                break;
            case 2:
                factory = new SubwayFactory();
                break;
            case 3:
                factory = new PotbellyFactory();
                break;
            default:
                std::cout << "Invalid choice!\n";
            }
            
            while (true) {
                std::cout << "Choose a sandwich: (1) BLT, (2) Tuna, (3) PBJ, (0) Exit: ";
                int choice2;
                std::cin >> choice2;
                if (choice2 == 0) {
                    break;
                }
                switch (choice2)
                    {
                    case 1:
                        factory->createBLT()->printName();
                        SandwichLogger::getInstance()->logSandwich(factory->createBLT()->getName());
                        break;
                    case 2:
                        factory->createTuna()->printName();
                        SandwichLogger::getInstance()->logSandwich(factory->createTuna()->getName());
                        break;
                    case 3:
                        factory->createPBJ()->printName();
                        SandwichLogger::getInstance()->logSandwich(factory->createPBJ()->getName());
                        break;
                    default:
                        std::cout << "Invalid choice!\n";
                        continue;
                    }
            }
            delete factory;
            
        }
};

int main() {
    SandwichStore* ss = new SandwichStore();
    ss->run();
    delete ss;

    return 0;
}