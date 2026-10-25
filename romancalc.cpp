#include <iostream>
#include <fstream>

int romanToArabic(const char* roman, int len);
void arabicToRoman(int number, char* result);

int main(int argc, char* argv[]) {
  char* inputFile = argv[1];
  char* outputFile = argv[2];

  std::ifstream in(inputFile);
  if (!in) {
    std::cout << "Failed to open input file!\n";
    return 0;
  }
  std::ofstream out(outputFile);
  if (!out) {
    std::cout << "Failed to open output file!\n";
    return 0;
  }

  in.seekg(0, std::ios::end);
  long fileSize = in.tellg();
  in.seekg(0, std::ios::beg);

  char file[1000];
  int j = 0;

  char RomanNumber[16];
  int k1 = 0;
  char roman[17];
  int arabicLine[200];
  int k2 = 0;
  int firstArabic = 0;

  while (!in.eof()) {
    char ch = (char)in.get();
    if (ch != '\n' && ch != '\0' && !in.eof()) {
      file[j++] = ch;
      out << ch;
    } else {
      file[j] = '\0';
      j = 0;
      int i = 0;
      firstArabic = 0;
      while (file[i] != '\0') {
        if (file[i] >= '0' && file[i] != ' ') {
          RomanNumber[k1++] = file[i];
          if (file[i + 1] == ' ' || file[i + 1] == '\0' ||
              file[i + 1] == '\n') {
            arabicLine[k2++] = romanToArabic(RomanNumber, k1);
            k1 = 0;
          }
        } else if (file[i] < 'A' && file[i] != ' ' && i != fileSize) {
          if (k2 > 0) {
            k2--;
          }
          firstArabic = arabicLine[k2];
          if (k2 > 0) {
            k2--;
          }
          int secondArabic = arabicLine[k2];

          switch (file[i]) {
            case '-':
              firstArabic = secondArabic - firstArabic;
              break;
            case '+':
              firstArabic = secondArabic + firstArabic;
              break;
            case '*':
              firstArabic = secondArabic * firstArabic;
              break;
            case '/':
              firstArabic = secondArabic / firstArabic;
              break;
          }
          arabicLine[k2++] = firstArabic;
        }
        i++;
      }
      if (!in.eof()) {
        if (firstArabic <= 0 || firstArabic > 3999) {
          out << " = ERR";
        } else {
          arabicToRoman(firstArabic, roman);
          out << " = " << roman;
        }
      } else {
        break;
      }
      out << '\n';
    }
  }
}

int romanToArabic(const char* roman, int len) {
  int result = 0;

  for (int i = 0; i < len; ++i) {
    switch (roman[i]) {
      case 'M':
        result += 1000;
        break;
      case 'D':
        result += 500;
        break;
      case 'C':
        if (i + 1 < len && (roman[i + 1] == 'M' || roman[i + 1] == 'D')) {
          result -= 100;
        } else {
          result += 100;
        }
        break;
      case 'L':
        result += 50;
        break;
      case 'X':
        if (i + 1 < len && (roman[i + 1] == 'C' || roman[i + 1] == 'L')) {
          result -= 10;
        } else {
          result += 10;
        }
        break;
      case 'V':
        result += 5;
        break;
      case 'I':
        if (i + 1 < len && (roman[i + 1] == 'V' || roman[i + 1] == 'X')) {
          result -= 1;
        } else {
          result += 1;
        }
        break;
      default:
        return 0;
    }
  }
  return result;
}

void arabicToRoman(int number, char* result) {
  int arabNumber[] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};

  const char* romanNumbers[] = {"M",  "CM", "D",  "CD", "C",  "XC", "L",
                                "XL", "X",  "IX", "V",  "IV", "I"};

  int index = 0;

  for (int i = 0; i < 13 && number > 0; ++i) {
    while (number >= arabNumber[i]) {
      for (int k = 0; romanNumbers[i][k] != 0; ++k) {
        result[index++] = romanNumbers[i][k];
      }
      number -= arabNumber[i];
    }
  }
  result[index] = '\0';
}