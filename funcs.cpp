#include "libs.h"

string readBinaryFromFile(string& input) { // Inputas skaitomas iš failo
    string binaryRepresentation;
    string file;
    char symbol;

    do {
        cout << "Failu sarasas: ";
        system("ls *.dat");
        cout << "Pasirinkite faila: ";
        getline(cin, file);

        ifstream read(file);
        if (!read.is_open()) {
            cout << "Klaida: tokio failo [" << file << "] nera." << endl;
        } else {
            while (read.get(symbol)) {
                // Simbolis konvertuojamas į dvejetainį
                bitset<8> binary(symbol);
                binaryRepresentation += binary.to_string();
            }
            read.close();
            input = binaryRepresentation;

            break;
        }
    } while (true);

    return binaryRepresentation;
}

string convertTextToBinary(string& input) { // Inputas įvedamas ranka
    string binaryRepresentation;
    string textInput;

    cout << "Iveskite norima teksta: ";
    getline(cin, textInput);
    input = textInput;

    for (char c : input) {
        // Simbolis konvertuojamas į dvejetainį
        bitset<8> binary(c);
        binaryRepresentation += binary.to_string();
    }

    return binaryRepresentation;
}

string padBinaryRepresentationShort(string binaryRepresentation, int targetLength) {
    while (binaryRepresentation.length() < targetLength) {
        // Pridėti randominius simbolius
        char padChar = 'a' + (binaryRepresentation.length() % targetLength);
        binaryRepresentation += bitset<8>(padChar).to_string();
    }
    return binaryRepresentation;
}
string padBinaryRepresentationLong(string binaryRepresentation, int targetLength) {
    for(int i = 0; i < targetLength / 8; i++) {
        // Pridėti randominius simbolius
        char padChar = 'a' + (binaryRepresentation.length() % targetLength);
        binaryRepresentation += std::bitset<8>(padChar).to_string();
    }
    return binaryRepresentation;
}

string generateHexadecimalRepresentation(string binaryRepresentation, const string& input) {
    // Dabartinio laiko ir inputo kombinacija kaip sydas mt19937 generatoriui
    random_device rd;
    mt19937 mt(rd());
    for(char c : input)
        mt.seed(mt() ^ static_cast<unsigned int>(c));

    // Indeksų kiekis nustatomas pagal dvejetainio kodo ilgį
    int indexAmount = binaryRepresentation.length() / 8;
    vector<int> indexes(indexAmount);
    for (int i = 0; i < indexAmount; i++) {
        indexes[i] = i;
    }

    // Indeksai mašomi pagal mt19937 atsitiktinių skaičių generatorių
    shuffle(indexes.begin(), indexes.end(), mt);

    // Dvejetainiai konteineriai pertvarkomi pagal išmaišytus indeksus
    vector<bitset<8>> rearrangedBinaryArray(indexAmount);
    for (int i = 0; i < indexAmount; i++) {
        rearrangedBinaryArray[indexes[i]] = bitset<8>(binaryRepresentation.substr(i * 8, 8));
    }

    // Pertvarkytas dvejetainis kodas konvertuoajamas į hex
    stringstream hexStream;
    for (const auto &binaryByte : rearrangedBinaryArray) {
        hexStream << setw(2) << setfill('0') << hex << static_cast<int>(binaryByte.to_ulong());
    }

    // Hex kodas nukerpamas iki 64 simbolių
    return hexStream.str().substr(0, 64);
}

void processBinaryInput(bool fromFile) {
    // srand(static_cast<unsigned int>(time(nullptr)));

    std::chrono::high_resolution_clock::time_point sHashing, eHashing;
    std::chrono::duration<double> tHashing;

    string binaryRepresentation;
    string input;

    if (fromFile) { // Skaitoma iš failo
        binaryRepresentation = readBinaryFromFile(input);
    } else { // Įvedimas ranka
        binaryRepresentation = convertTextToBinary(input);
    }

    sHashing = std::chrono::high_resolution_clock::now();
    if (binaryRepresentation.length() < 256) { // Dvejetainis kodas trumpesnis, nei 256 simboliai
        binaryRepresentation += "1"; // Pridedamas vienetas į galą
        binaryRepresentation = padBinaryRepresentationShort(binaryRepresentation, 256);
    } else { // Dvejetainis kodas ilgesnis, nei 256 simboliai
        binaryRepresentation = padBinaryRepresentationLong(binaryRepresentation, 512);
    }
    eHashing = std::chrono::high_resolution_clock::now();
    tHashing = eHashing - sHashing;

    string hexadecimalRepresentation = generateHexadecimalRepresentation(binaryRepresentation, input);

    cout << endl << "Isvestis: " << hexadecimalRepresentation << endl;
    // cout << "Laikas: " << tHashing.count() << "s." << endl;
}
