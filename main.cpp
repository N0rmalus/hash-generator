#include "libs.h"
#include "headers.h"

int main() {
    string fileRead;

    do {
        cout << "-----------------------------------------------------------------------" << endl;
        cout << "Iejima skaityti is failo? (Y/N): ";
        getline(cin, fileRead);

        if (fileRead == "Y" || fileRead == "y") {
            processBinaryInput(true);

            break;
        } else if (fileRead == "N" || fileRead == "n") {
            processBinaryInput(false);

            break;
        } else {
            cout << "Tokio pasirinkimo [" << fileRead << "] nera." << endl;

            continue;
        }
    } while (true);
    
    return 0;
}
