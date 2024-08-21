#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <iostream>
using namespace std;

void replaceEmptyLinesWithText(const string& filePath, const string& replacementText) {
    ifstream inputFile(filePath);
    ofstream outputFile("output.txt"); 

    if (!inputFile || !outputFile) {
        cerr << "Не удалось открыть файлы." << endl;
        return;
    }

    string line;
    while (getline(inputFile, line)) {
        if (line.empty()) {
            outputFile << replacementText << endl;
        }
        else {
            outputFile << line << endl;
        }
    }

    inputFile.close();
    outputFile.close();

    // Заменяем исходный файл новым файлом
    remove(filePath.c_str());
    rename("output.txt", filePath.c_str());
}
bool fileExists(const string& filename) {
    ifstream file(filename);
    return file.good();
}
/*void printNthLine(const string& filename, int n) {
    ifstream file(filename);
    string line;
    int lineNumber = 0;

    while (getline(file, line)) {
        lineNumber++;
        if (lineNumber == n) {
            cout << "Строка " << n << ": " << line << endl;
            break; 
        }
    }

    file.close();
}*/

/*void findSubstringInFile(const string& filename, const string& substring) {
    ifstream file(filename);
    string line;
    int lineNumber = 0;
    int c = 0;
    while (getline(file, line)) {
        lineNumber++;
        size_t position = line.find(substring);
        if (position != string::npos) {
            std::cout << "Найдено совпадение в строке " << lineNumber << ", позиция " << position + 1 << std::endl;
            c++;
        }
    }
    if (c <= 0)
    {
        cout << "Совпадений нет" << endl;
    }
    file.close();

}*/
void findSubstringInFile(const string& filename, const string& substring) {
    ifstream file(filename);
    string line;
    int line_number = 0;

    if (file.is_open()) {
        while (getline(file, line)) {
            line_number++;
            size_t pos = 0;

            while ((pos = line.find(substring, pos)) != string::npos) {
                cout << "Найдено совпадение в строке: " << line_number << ", на позиции: " << pos << "\n";
                pos += substring.length();
            }
        }
        file.close();
    }
    else {
        cout << "Ошибка открытия файла";
    }
}
string GetLineFromFile(const string& filename, int n) {
    ifstream file(filename);
    string line;

    for (int i = 1; i < n; i++) {
        if (!getline(file, line)) {
            return "";
        }
    }

    getline(file, line);

    return line;
}
int countUniqueWords(const string& filename) {
    ifstream file(filename);
    string word;
    map<string, int> wordCount;

    while (file >> word) {
        
        transform(word.begin(), word.end(), word.begin(), ::tolower);
        word.erase(remove_if(word.begin(), word.end(), ::ispunct), word.end());

        
        wordCount[word]++;
    }

    int uniqueCount = 0;
    for (const auto& pair : wordCount) {
        if (pair.second == 1) {
            uniqueCount++;
        }
    }

    return uniqueCount;
}
int main() {
    setlocale(LC_ALL, "rus");
    string filename;
    cout << "Введите название файла" << endl;
    cin >> filename;
    if (fileExists(filename)) {
        cout << "Файл существует." << endl;
        string replacementText; 
        cout << "Введите строку s" << endl;
        cin >> replacementText;
        replaceEmptyLinesWithText(filename, replacementText);
        cout << "Введите номер строки" << endl;
        int n;
        cin >> n;
        string line = GetLineFromFile(filename, n);
        if (line.empty()) {
            cout << "Строки с номером " << n << " не существует." << endl;
        }
        else {
            cout << "Строка " << n << ": " << line << endl;
        }
        string substring;
        cout << "Введите подстроку для поиска: " << endl;
        cin >> substring;

        findSubstringInFile(filename, substring);
        int uniqueCount = countUniqueWords(filename);
        cout << "Количество уникальных слов в файле: " << uniqueCount << endl;
        return 0;
    }
    else {
        cout << "Файл не существует." << endl;
        return 0;
    }

 

}