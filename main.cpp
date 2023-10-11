#include "libs.h"

void processBinaryInput(bool fromFile);
void readAndConvertBinaryFromFile();

int main() {
    string fileRead, choice;

    do {
        cout << "-----------------------------------------------------------------------" << endl;
        cout << "Iejima skaityti is failo? (Y/N): ";
        getline(cin, fileRead);

        if(fileRead == "Y" || fileRead == "y") {
            do {
                cout << "-----------------------------------------------------------------------" << endl;
                cout << "Pasirinkite:" << endl; 
                cout << "1. Bandyti programa" << endl;
                cout << "2. Eksperimentuoti programos funkcionaluma" << endl;
                cout << "> ";
                getline(cin, choice);

                if(choice == "1") {
                    processBinaryInput(true);

                    break;
                } if(choice == "2") {
                    readAndConvertBinaryFromFile();

                    break;
                } else {
                    cout << "Tokio pasirinkimo [" << choice << "] nera." << endl;
        
                    continue;
                }
            } while(true);
            


            break;
        } else if(fileRead == "N" || fileRead == "n") {
            processBinaryInput(false);

            break;
        } else {
            cout << "Tokio pasirinkimo [" << fileRead << "] nera." << endl;
        
            continue;
        }
    } while(true);
    
    return 0;
}
