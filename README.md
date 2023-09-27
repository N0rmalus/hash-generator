# hash-generator

Paprasta simbolių hašinimo programa, kurioje gaunama išvestis yra 256 bitų arba 64 simbolių dešimtainis kodas.

### Šios programos pseudo kodas

```
function loadSavedData(filename)
    data = empty unordered map
    open the file specified by filename for reading as savedFile

    if savedFile is not found
        print an error message
        return an empty map

    while there are lines in savedFile
        read binaryCode and hexCode from the current line
        add binaryCode and hexCode to the data map

    close savedFile
    return data

function processBinaryInput(fromFile)
    open a file named "saved.dat" in append mode as write

    initialize the random number generator with the current time

    sHashavimas = current high-resolution time

    binaryRepresentation = ""
    randomBinaryRepresentation = ""

    if fromFile is true
        open a file named "input.txt" for reading as read

        if read is not found
            print an error message
            return

        while there are characters in read
            symbol = read the next character
            convert symbol to an 8-bit binary string
            append the binary string to binaryRepresentation

            generate a random bit and append it to randomBinaryRepresentation

        close read
    else
        prompt the user to input some text

        for every entered symbol 
            convert symbol to an 8-bit binary string 
            append the binary string to binaryRepresentation

            generate a random bit and append it to randomBinaryRepresentation

    if randomBinaryRepresentation is longer than 256 bits
        trim randomBinaryRepresentation to 256 bits

    while randomBinaryRepresentation is shorter than 256 bits
        generate a random bit and append it to randomBinaryRepresentation

    hexadecimalRepresentation = ""

    for each 4-bit nibble in randomBinaryRepresentation
        convert the nibble to an integer
        find the corresponding hexadecimal character and append it to hexadecimalRepresentation

    savedData = loadSavedData("saved.dat")

    if binaryRepresentation is found in savedData
        print "Output: " followed by the corresponding hexadecimal code
    else
        write a new line to the "saved.dat" file containing binaryRepresentation and hexadecimalRepresentation
        close write
        print "Output: " followed by hexadecimalRepresentation

function main()
    prompt the user to enter 'Y' to read from a file or 'N' to enter manually
    read the user's choice into fileRead

    if fileRead is 'Y' or 'y'
        call processBinaryInput with fromFile set to true
    else if fileRead is 'N' or 'n'
        call processBinaryInput with fromFile set to false
    else
        print "Invalid choice"
```

--

## Programos kompiliavimo laikas nuo input'o eilučių kiekio :)

|  Eilučių sk.      |  Laikas (s )  |
|-------------------|---------------|
|  **100**          |  0.133044s    |
|  **500**          |  0.051012s    |
|  **1 500**        |  0.164037s    |
|  **6 000**        |  0.670775s    |
|  **10 000**       |  1.013003s    |