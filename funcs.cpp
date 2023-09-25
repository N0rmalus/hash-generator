#include "libs.h"
#include "headers.h"

unordered_map<string, string> loadSavedData(const string& filename) {
    unordered_map<string, string> data;
    ifstream savedFile(filename);

    if (!savedFile) {
        cout << "Nepavyko atidaryti saved.dat failo." << endl;
        
        // return;
    }

    string binaryCode;
    string hexCode;

    while (savedFile >> binaryCode >> hexCode) {
        data[binaryCode] = hexCode;
    }

    savedFile.close();
    return data;
}

void processBinaryInput(bool fromFile) {
    ofstream write("saved.dat", std::ios::app);

    srand(static_cast<unsigned int>(time(nullptr)));
    string binaryRepresentation, randomBinaryRepresentation;
    string file, input;
    char symbol;

    if(fromFile) { // Skaityti iš failo
        do {
            cout << "Failu sarasas: "; system("ls *.dat");
            cout << "Pasirinkite faila: ";
            getline(cin, file);

            ifstream read(file);
            if(!read.is_open()) { 
                cout << "Klaida: tokio failo [" << file << "] nera." << endl;
            } else {
                while (read.get(symbol)) {
                    bitset<8> binary(symbol);
                    binaryRepresentation += binary.to_string();

                    int randomBit = rand() % 2;
                    randomBinaryRepresentation += to_string(randomBit);
                }

                read.close();

                break;
            }
        } while(true);
    } else { // Rašyti ranka
        cout << "Iveskite norima teksta: ";
        getline(cin, input);

        for(char c : input) {
            // Inputas paverčiamas į binarinį kodą, kuris bus saugomas saved.dat faile
            bitset<8> binary(c);
            binaryRepresentation += binary.to_string();

            // Inputo simboliai paverčiami į atsitiktinius bitus
            int randomBit = rand() % 2;
            randomBinaryRepresentation += to_string(randomBit);
        }
    }

    auto sHashavimas = std::chrono::high_resolution_clock::now();

    // Jei binarinis kodas yra ilgesnis, nei 256 simboliai - atitinkama dalis nukerpama
    if(randomBinaryRepresentation.length() > 256) {
        randomBinaryRepresentation = randomBinaryRepresentation.substr(0, 256);
    }

    // Jei binarinis kodas yra trumpesnis - pridedami bitai
    while(randomBinaryRepresentation.length() < 256) {
        int randomBit = rand() % 2;
        randomBinaryRepresentation += to_string(randomBit);
    }   

    // Binarinis kodas kovertuojamas į 64 simbolių ilgio hex kodą
    string hexadecimalRepresentation;
    for(size_t i = 0; i < randomBinaryRepresentation.length(); i += 4) {
        bitset<4> nibble(randomBinaryRepresentation.substr(i, 4));
        int nibbleValue = nibble.to_ulong();
        hexadecimalRepresentation += "0123456789abcdef"[nibbleValue];
    }

    // Ankščiau suhašinti inputai užkraunami
    unordered_map<string, string> savedData = loadSavedData("saved.dat");

    // Tikrinama, ar dabartinis į neatsitiktinį binarinį kodą paverstas inputas buvo jau anksčiau hašintas
    auto it = savedData.find(binaryRepresentation);
    if(it != savedData.end()) { // Dabartinis binarinis kodas sutampa su anksčiau suhašintu
        cout << "Isvestis*: " << it->second << endl;
    } else { // Danartinis binarinis kodas dar nebuvo įvestas - saugoma į saved.dat failą
        write << endl << endl << binaryRepresentation << " " << hexadecimalRepresentation;
        write.close();

        cout << "Isvestis: " << hexadecimalRepresentation << endl;
    }

    auto eHashavimas = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> dHashavimas = eHashavimas - sHashavimas;

    cout << endl << "Laikas: " << dHashavimas.count() << "s." << endl;
}
