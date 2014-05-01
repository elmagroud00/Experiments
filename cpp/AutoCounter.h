#ifndef AUTOCONTER_H
#define AUTOCONTER_H

#include <iostream>
#include <set>
#include <string>

class AutoCounter {
    static int count;
    int id;
    class CleanupCheck {
        std::set<AutoCounter*>trace;
    public:
        void add(AutoCounter *ap) {
            trace.insert(ap);
        }
        void remove(AutoCounter *ap) {
            if(trace.erase(ap) == 1)
                std::cout << "Attemp to delete AutoCounter" << std::endl;
            else
                std::cout << "Attmp to delte AutoCounter twice" << std::endl;
        }
        ~CleanupCheck() {
            std::cout << "~CleanupCheck()" << std::endl;
            if(trace.size() == 0)
                std::cout << "All AutoCounter objects  cleaned up" << std::endl;
            else
            {
                std::cout << "There are " << trace.size() << "not cleanup" << std::endl;
                for(std::set<AutoCounter*>::iterator it = trace.begin(); it!= trace.end(); it++) 
                    std::cout << (*it)->id << std::endl;
            }
        }
    };
    static CleanupCheck verifier;
    AutoCounter() : id(count++) {
        verifier.add(this); //register itself
        std::cout << "created[" << id << "]" << std::endl;
    }
    AutoCounter(const AutoCounter&);
    void operator=(const AutoCounter&);
public:
    /* You can only create objects with this */
    static AutoCounter *create() {
        return new AutoCounter();
    }
    ~AutoCounter() {
        std::cout << "destroying[" << id << "]" << std::endl;
        verifier.remove(this);
    }
    friend std::ostream &operator<<(std::ostream &os, const AutoCounter &ac) {
        return os << "AutoCounter " << ac.id;
    }
    friend std::ostream &operator<<(std::ostream &os, const AutoCounter *ac) {
        return os << "AutoCounter " << ac->id;
    }
};

#endif // AUTOCONTER_H ///:~

















