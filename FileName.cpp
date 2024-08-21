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
        cerr << "�� ������� ������� �����." << endl;
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

    // �������� �������� ���� ����� ������
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
            cout << "������ " << n << ": " << line << endl;
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
            std::cout << "������� ���������� � ������ " << lineNumber << ", ������� " << position + 1 << std::endl;
            c++;
        }
    }
    if (c <= 0)
    {
        cout << "���������� ���" << endl;
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
                cout << "������� ���������� � ������: " << line_number << ", �� �������: " << pos << "\n";
                pos += substring.length();
            }
        }
        file.close();
    }
    else {
        cout << "������ �������� �����";
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
    cout << "������� �������� �����" << endl;
    cin >> filename;
    if (fileExists(filename)) {
        cout << "���� ����������." << endl;
        string replacementText; 
        cout << "������� ������ s" << endl;
        cin >> replacementText;
        replaceEmptyLinesWithText(filename, replacementText);
        cout << "������� ����� ������" << endl;
        int n;
        cin >> n;
        string line = GetLineFromFile(filename, n);
        if (line.empty()) {
            cout << "������ � ������� " << n << " �� ����������." << endl;
        }
        else {
            cout << "������ " << n << ": " << line << endl;
        }
        string substring;
        cout << "������� ��������� ��� ������: " << endl;
        cin >> substring;

        findSubstringInFile(filename, substring);
        int uniqueCount = countUniqueWords(filename);
        cout << "���������� ���������� ���� � �����: " << uniqueCount << endl;
        return 0;
    }
    else {
        cout << "���� �� ����������." << endl;
        return 0;
    }

 

}