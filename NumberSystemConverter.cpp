#include <iostream>
#include <vector>
#include <string>
#include <math.h>

void CreateHeaderText(std::string text);
void CreateDividerText();
void CreateErrorText(std::string text);
bool GetBoolUserInput(std::string text);


std::vector<char> HexValues = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
void convertBinaryToDecimal(std::string input);
void convertDecimalToBinary(int input);
void convertDecimalToHex(int input);
void convertHexToDecimal(std::string input);
void binarySpacingConvert(std::string &input);
int getHexIndex(char hexValue);

int main() {
    //Introduction text
    std::cout << "\n\n";
    CreateHeaderText("=-= Convert To Binary, Decimal, and Hex =-=");
    std::cout << "\n\n";

    //Do while loop and variable declaration
    bool isRunning = true;
    int convertType;
    std::string stringInput;
    int intInput;
    do {
        //Get conversion type from the user.
        std::cout << "Select the conversion type.\n    1. Convert binary to decimal\n    2. Convert decimal to binary\n    3. Convert decimal to hex\n    4. Convert hex to decimal\n";
        std::cin >> convertType;

        switch (convertType){
            case 1:
                //Get string for converting binary to decimal
                std::cout << "Input the value to convert: ";
                std::getline (std::cin,stringInput);
                std::getline (std::cin,stringInput);
                convertBinaryToDecimal(stringInput);
                break;

            case 2:
                //Get int to convert decimal to binary
                std::cout << "Input the value to convert: ";
                std::cin >> intInput;
                convertDecimalToBinary(intInput);
                break;

            case 3:
                //Get int to convert decimal to hex
                std::cout << "Input the value to convert: ";
                std::cin >> intInput;
                convertDecimalToHex(intInput);
                break;

            case 4:
                //Get string for converting hex to decimal
                std::cout << "Input the value to convert: ";
                std::getline (std::cin,stringInput);
                std::getline (std::cin,stringInput);
                convertHexToDecimal(stringInput);
                break;

            default:
                //If unsupported input, show error
                CreateErrorText("Unrecognized input, try again.");
                break;
        }
        std::cout << "\n";
        //Ask user if they want to use tool again
        if(!(GetBoolUserInput("Would you like to use this again? Y/N\n"))) {
            isRunning = false;
        }
    } while (isRunning);
}

void convertBinaryToDecimal(std::string input) {
    int sizeOf = input.size();
    int bitValue;
    unsigned long long decimalValue = 0;
    //Get max size of bits
    for (int i = 1; i <= sizeOf; i++){
        //If not defined, set bitValue to 1
        if(!bitValue) {
            bitValue = 1;
            //Skip to next loop iteration
            continue;
        }
        //Set bitValue to double the current value
        bitValue *= 2;
    }
    
    //For each letter in the input
    for (char letter : input)
    {
        //If letter is 1, bitValue is added to decimalValue
        if(letter == '1') {
            decimalValue = decimalValue + bitValue;
        }
        //bitValue is halved to represent the correct number
        bitValue = bitValue / 2;
    }
    //Display decimalValue
    std::cout << "Converted binary to decimal: " << decimalValue << "\n";
}

void convertDecimalToBinary(int input) {
    int bitValue = 1;
    //While bitValue is less than input
    while (bitValue < input) {
        //If double bitValue is less than input, bitValue = bitValue * 2
        if((bitValue * 2) < input) {
            bitValue *= 2;
        } else {
            //If input is less than double bitValue, exit loop
            break;
        }
    }

    //Declare binaryOutput return value
    std::string binaryOutput = "";
    //While bitValue is greater than or equal to 1
    while (bitValue >= 1) {
        //If input - bitValue is greater than or equal to 0 output 1
        if((input - bitValue) >= 0) {
            binaryOutput += "1";
            input = input - bitValue;
            //Subtract bitValue from input as its not included anymore
        } else {
            //Otherwise, output 0
            binaryOutput += "0";
        }
        //Halve bitValue
        bitValue = bitValue / 2;
    }
    //Add spacing conventions
    binarySpacingConvert(binaryOutput);
    //Display result
    std::cout << "Converted binary to decimal: " << binaryOutput << "\n";
}

void convertDecimalToHex(int input) {
    //Get remainder and whole number from division of input
    std::string hexOutput = "";
    int remainder = input % 16;
    int wholeNum = input / 16;
    //First remainder always gets added to the hex as first value
    hexOutput = HexValues[remainder] + hexOutput;
    
    //While wholeNum is greater than 15, so that we never get a result without a whole number
    while (wholeNum > 15) {
        //Get remainder and whole number of the wholeNum divided by 16.
        remainder = wholeNum % 16;
        //Add remainder to the front of the output string
        hexOutput = HexValues[remainder] + hexOutput;
        wholeNum = wholeNum / 16;
    }
    //Add the wholeNum to the front of the output string
    hexOutput = HexValues[wholeNum] + hexOutput;

    //Display output string
    std::cout << "Converted decimal to hex: " << hexOutput << "\n";
}

void convertHexToDecimal(std::string input) {
    //Make string all upper to comply with hexValues chars that are all upper.
    for (auto &c: input) c = toupper(c);

    //Max hex value is 16 to the power of the last index of the input.
    int maxHexValue = std::pow(16,input.size() - 1);
    int decimalOutput = 0;
    char hexValue;
    int index;

    //From 0 to input size get hex char
    for (int i = 0; i < input.size(); i++) {
        hexValue = input[i];
        //Get index from hexValues for char
        index = getHexIndex(hexValue);
        //Decimal value is the index * maxHexValue added to previous decimal value
        decimalOutput = decimalOutput + (index*maxHexValue);
        //Reduce maxHexValue by dividing by 16
        maxHexValue = maxHexValue / 16;
    }

    //Display result
    std::cout << "Converted hex to decimal: " << decimalOutput << "\n";
}

void binarySpacingConvert(std::string &input) {
    //Passing by reference to alter the string used as input
    //While the size of input has a remainder when divided by 4 add a 0 to the front
    while (input.size() % 4 != 0){
        input.insert(0,"0");
    }

    //For each time that input can be divided by 4 add a space at the 4th positions
    for (int i = 0; i < ((input.size() / 4) - 1); i++){
        input.insert((i+1)*4+(1*i)," ");
    }
}

int getHexIndex(char hexValue) {
    //If no return, default is -1, used for checking for result.
    int returnValue = -1;
    //From 0 to HexValues size, check if the value at the index is equal to the input, if it is, update the return value.
    for (int i = 0; i < HexValues.size(); i++) {
        if(HexValues[i] == hexValue) {
            returnValue = i;
            //Exit loop to prevent looping extra times
            break;
        }
    }
    return returnValue;
}

//Unrelated to program

void CreateHeaderText(std::string text) {
    for (int i = 0; i < text.size(); i++) {
        std::cout << "=";
    }
    std::cout << "\n" << text << "\n";
    for (int i = 0; i < text.size(); i++) {
        std::cout << "=";
    }
    std::cout << "\n";
}

void CreateDividerText() {
    for (int i = 0; i < 20; i++) {
        std::cout << "=";
    }
    std::cout << "\n";
}

void CreateErrorText(std::string text) {
    std::string errorText = "[ERROR] : ";
    errorText += text;
    CreateHeaderText(errorText);
}

bool GetBoolUserInput(std::string text) {
    char input;
    while (toupper(input) != 'Y' && toupper(input) != 'N') {
        std::cout << text;
        std::cin >> input;
    }
    if(toupper(input) == 'Y') {
        return true;
    } else {
        return false;
    }
}

