#include "purge.h"
#include "Security.h"
#include <vector>
using namespace std;

int main() {
    vector<Security*> portfolio;
    portfolio.push_back(new Metal);
    portfolio.push_back(new Investment);
    portfolio.push_back(new Bond);
    portfolio.push_back(new Stock);
    for(vector<Security*>::iterator it = portfolio.begin(); it != portfolio.end(); it++) {
        Investment *cm = dynamic_cast<Investment*>(*it);
        if(cm)
            cm->special();
        else
            cout << "not a Investment" << endl;
    }
    cout << "cast from intermediate pointer: " << endl;
    Security *sp = new Metal;
    Investment *cp = dynamic_cast<Investment*>(sp);
    if(cp)
        cout << "it is an Investment" << endl;
}

