# hash-generator

Paprasta simbolių hašinimo programa, kurioje gaunama išvestis yra 256 bitų arba 64 simbolių dešimtainis kodas.

## v0.2 (naujausia)
Nuo šiol įvestis ir išvestis yra nebesaugoma **saved.dat** ir hašinta įvestis yra labiau apsaugota.

### Programos pseudo kodas

```
Main program:
    Initialize fileRead as a string

    Do:
        Display user prompt for file input
        Read fileRead from user

        If fileRead indicates reading from a file Then
            Call processBinaryInput with file input mode
            Break
        Else If fileRead indicates manual input Then
            Call processBinaryInput with manual input mode
            Break
        Else
            Display error message for invalid input
            Continue
        End If
    While true

ProcessBinaryInput(inputMode):
    Initialize binaryRepresentation as a string
    Initialize input as a string

    If inputMode is file input Then
        binaryRepresentation = Call readBinaryFromFile with input argument
    Else If inputMode is manual input Then
        binaryRepresentation = Call convertTextToBinary with input argument
    End If

    If length of binaryRepresentation is less than a threshold Then
        binaryRepresentation = Call padBinaryRepresentationShort with binaryRepresentation and target length
    Else
        binaryRepresentation = Call padBinaryRepresentationLong with binaryRepresentation and target length
    End If

    hexadecimalRepresentation = Call generateHexadecimalRepresentation with binaryRepresentation and input as arguments

    Display the result

ReadBinaryFromFile(input):
    Initialize binaryRepresentation as a string
    Initialize file as a string
    Initialize symbol as a character

    Do:
        Display available file list
        Read user-selected file

        If the file exists Then
            Read the file content character by character
            Convert each character to binary and append to binaryRepresentation
            Close the file

            Set input to include file information and content
            Exit loop
        Else
            Display file not found error
        End If
    While true

    Return binaryRepresentation

ConvertTextToBinary(input):
    Initialize binaryRepresentation as a string
    Initialize textInput as a string

    Display user prompt for text input
    Read user input as text

    For each character c in text Do
        Convert c to binary and append to binaryRepresentation
    End For

    Set input to include text input

    Return binaryRepresentation

PadBinaryRepresentationShort(binaryRepresentation, targetLength):
    While length of binaryRepresentation is less than targetLength Do
        Calculate a pad character based on the current length
        Convert the pad character to binary and append to binaryRepresentation
    End While

    Return binaryRepresentation

PadBinaryRepresentationLong(binaryRepresentation, targetLength):
    Initialize padChar as a character

    For each position in binaryRepresentation until reaching the target length Do
        Calculate a pad character based on the current length
        Convert the pad character to binary and append to binaryRepresentation
    End For

    Return binaryRepresentation

GenerateHexadecimalRepresentation(binaryRepresentation, input):
    Initialize hexadecimalRepresentation as a string

    Initialize a random number generator with a seed based on input data
    Create a list of indexes and shuffle them
    Rearrange binary data based on shuffled indexes
    Convert rearranged binary data to hexadecimal representation
    Limit hexadecimalRepresentation to a fixed length

    Return hexadecimalRepresentation
```

|  Įvedimas (input)    |  Išvedimas                                                         |  Laikas (s)  |
|----------------------|--------------------------------------------------------------------|--------------|
|  lietuva             |  5d216c5505796119296d767d74090d015965cd6171256975651d752d15511169  |  0s          |
|  Lietuva             |  512d7d75756d61657974cd71257669550d65155d11056929591d194c09016121  |  0s          |
|                      |  0d3d2d796929610171555939517505250919355d494d65452141151db17d116d  |  0s          |
|  "Konstitucija.txt"  |  6e6e744cc46f6a79b36e7373736c61696f6e756969626b6b6f6f5673692c7269  |  0.000024s   |
|  "2500.txt"          |  3d266954683722476b7e720a6d2c5e3c3c47622577626b3d4e6c384f37454367  |  0.001031s   |
|  "240000.txt"        |  345a5650524c7862666577376e435464724c343542774a584f78316b506b6857  |  0.000999s   |
|  "li2000.txt"        |  7565724f6f63736375732065746e61616173206974747473737320747470656d  |  0.003508s   |

---

### Išvada
- Programos skaitymas iš failo su daug eilučių ( > 2000 ) yra lėtas
- Hašinimo išvestis yra konstantinio ilgio (256 bitų, 64 simbolių ilgio)
- Funckija yra deterministinė, t.y., ta pati įvestis - ta pati išvestis

---

**main.cpp** - pagrindinis programos failas.

**funcs.cpp** - papildoma programos dalis, kurioje laikomi funkcijų aprašymai.

**libs.h** - failas, kuriame saugomos visos bibliotekos ir jų pagrindinės funkcijos, kurios yra reikalingos šiai programai veikti.