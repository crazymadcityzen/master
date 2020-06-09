#include <iostream>
#include <map>
#include <fstream>
#include <string>
#include <cmath>

#define TAB_LEN 4

#define SUCCESS 0
#define INCORRECT_INPUT -1

using namespace std;
class Dictionary
{
private:
    const string file_name = "./Dictionary/ItalianEnglish.txt";
    map<string, pair<string, string>> plot;
    size_t max_base_word_len, max_gend_size;
    int add()
    {
        pair<string, pair<string, string>> aux;
        getchar();
        cout << "Enter a word on Italian:" << endl;
        getline(cin, aux.first);
        if (aux.first.length() > max_base_word_len)
            max_base_word_len = aux.first.length();
        cout << "Enter a gender of this word" << endl;
        getline(cin, aux.second.first);
        if (aux.second.first.length() > max_gend_size)
            max_gend_size = aux.second.first.length();
        cout << "Enter an English translation for this word" << endl;
        getline(cin, aux.second.second);
        plot.insert(aux);
        return SUCCESS;
    }
    void print_all()
    {
        cout << "===========================================" << endl;
        size_t current_length = 0, amount_of_spaces = 0;
        for (auto begin = plot.begin(); begin != plot.end(); begin++)
        {
            cout << begin->first;
            current_length = begin->first.length();
            amount_of_spaces = (max_base_word_len + 1) - current_length;
            for (size_t i = 0; i < amount_of_spaces; i++)
                cout << ' ';
            cout << begin->second.first;
            current_length = begin->second.first.length();
            amount_of_spaces = (max_gend_size + 1) - current_length;
            for (size_t i = 0; i < amount_of_spaces; i++)
                cout << ' ';
            cout << begin->second.second << endl;
        }
        cout << "===========================================" << endl;
    }
    void delete_all()
    {
        plot.clear();
    }
public:
    Dictionary()
    {
        flag:
        ifstream data_in(file_name, ifstream::in);
        if (!data_in.is_open())
        {
            ofstream data_out(file_name, ifstream::out);
            data_out.close();
            goto flag;
        }
        max_base_word_len = 0, max_gend_size = 0;
        pair<string, pair<string, string>> aux;
        while (getline(data_in, aux.first))
        {
            if (aux.first.length() > max_base_word_len)
                max_base_word_len = aux.first.length();
            getline(data_in, aux.second.first);
            if (aux.second.first.length() > max_gend_size)
                max_gend_size = aux.second.first.length();
            getline(data_in, aux.second.second);
            plot.insert(aux);
        }
        data_in.close();
    }
    int Menu()
    {
        flag:
        cout << "1 - Add\n2 - See all\n3 - Delete all\n4 - Exit\n";
        int key;
        cin >> key;
        switch(key)
        {
            case 1:
                add();
                break;
            case 2:
                print_all();
                break;
            case 3:
                delete_all();
                break;
            case 4:
                return SUCCESS;
                break;
            default:
                cout << "Try again" << endl;
                break;
        }
        goto flag;
        return SUCCESS;
    }
    ~Dictionary()
    {
        ofstream data_out(file_name, ifstream::out);
        for (auto begin = plot.begin(); begin != plot.end(); begin++)
            data_out << begin->first << endl << begin->second.first << endl << begin->second.second << endl;
        data_out.close();
    }
};
int main()
{
    Dictionary example;
    example.Menu();
    return SUCCESS;
}
