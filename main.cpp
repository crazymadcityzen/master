#include <iostream>
#include <map>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>

#define TAB_LEN 4

#define SUCCESS 0
#define INCORRECT_INPUT -1

using namespace std;
class Dictionary
{
private:
    const string basic_directory = "./Dictionary/";
    string cur_file = "";
    const string filenames = "./Dictionary/filenames.txt";
    vector<string> languages;
    map<string, pair<string, string>> plot;
    size_t max_base_word_len, max_gend_size;
    int is_correct_gender(string gender)
    {
        int result = gender.compare("m") && gender.compare("M");
        result &= gender.compare("F") && gender.compare("f") && gender.compare("-");
        return result;
    }
    int add_language()
    {
        string from, to;
        flag:
        cout << "`````````````````````````````````````````" << endl;
        cout << "Enter a language you want to learn words from" << endl;
        getline(cin, from);
        if (from.compare("") == 0)
        {
            cout << "Empty input. Try again" << endl;
            goto flag;
        }
        cout << "Enter a language you want to describe these words on" << endl;
        getline(cin, to);
        for (size_t i = 0; i != languages.size(); i++)
            if (languages[i].compare(from + to) == 0 || to.compare("") == 0)
            {
                char aux;
                cout << "Already have this pair of languages or empty input. Enter 'E' to return to main menu or anything else to try again" << endl;
                cin >> aux;
                if (aux == 'E')
                    return INCORRECT_INPUT;
                goto flag;
            }
        languages.push_back(from + to);
        cout << "`````````````````````````````````````````" << endl;
        return SUCCESS;
    }
    void change_language()
    {
        flag:
        cout << "Choose on of the languages below by entering an appropriate number" << endl;
        for (size_t i = 0; i != languages.size(); i++)
            cout << i + 1 << " - " << languages[i] << endl;
        size_t au;
        cin >> au;
        if (au < 0 || au > languages.size())
        {
            cout << "Try again. Incorrect dial" << endl;
            goto flag;
        }

        ofstream data_out(basic_directory + cur_file + ".txt", ifstream::out);
        for (auto begin = plot.begin(); begin != plot.end(); begin++)
            data_out << begin->first << endl << begin->second.first << endl << begin->second.second << endl;
        data_out.close();
        plot.clear();

        cur_file = languages[au - 1];

        ifstream data_in(basic_directory + cur_file + ".txt", ifstream::in);
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
    int add()
    {
        pair<string, pair<string, string>> aux;
        getchar();
        cout << "Enter a word on the language u learn words on:" << endl;
        getline(cin, aux.first);
        if (aux.first.length() > max_base_word_len)
            max_base_word_len = aux.first.length();
        flag:

        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << "Enter a gender of this word" << endl;
        getline(cin, aux.second.first);
        if (is_correct_gender(aux.second.first))
        {
            cout << "Incorrect gender. Must be M, F or M/F" << endl;
            goto flag;
        }
        if (aux.second.first.length() > max_gend_size)
            max_gend_size = aux.second.first.length();
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << "Enter a translation for this word on the picked language" << endl;
        getline(cin, aux.second.second);
        plot.insert(aux);
        return SUCCESS;
    }
    void print_all()
    {
        cout << "===========================================" << endl;
        size_t amount_of_spaces = 0;
        for (auto begin = plot.begin(); begin != plot.end(); begin++)
        {
            cout << begin->first;
            amount_of_spaces = (max_base_word_len + 1) - begin->first.length();
            for (size_t i = 0; i < amount_of_spaces; i++)
                cout << ' ';

            for (size_t i = 0; i != begin->second.first.length(); i++)
                cout << char(toupper(begin->second.first[i]));
            amount_of_spaces = (max_gend_size + 1) - begin->second.first.length();
            for (size_t i = 0; i < amount_of_spaces; i++)
                cout << ' ';
            cout << begin->second.second << endl;
        }
        cout << "===========================================" << endl;
    }
    void delete_all()
    {
        plot.clear();
        max_gend_size = 0;
        max_base_word_len = 0;
    }
public:
    Dictionary()
    {
        flag_1:
        ifstream file_in(filenames, ifstream::in);
        if (!file_in.is_open())
        {
            ofstream file_out(filenames, ifstream::out);
            file_out.close();
            goto flag_1;
        }
        string aux_str = "";
        while (getline(file_in, aux_str))
            languages.push_back(aux_str);
        while (languages.size() == 0)
            add_language();
        cur_file = languages[0];

        flag:
        ifstream data_in(basic_directory + cur_file + ".txt", ifstream::in);
        if (!data_in.is_open())
        {
            ofstream data_out(basic_directory + cur_file + ".txt", ifstream::out);
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
        file_in.close();
        data_in.close();
    }
    int Menu()
    {
        flag:
        cout << "Current system of languages is " << cur_file << endl;
        cout << "______________________________" << endl;
        cout << "1 - Add word\n2 - See all words\n3 - Delete all words\n4 - Add language\n" <<
                "5 - Switch language\n6 - Exit\n";
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
                getchar();
                add_language();
                break;
            case 5:
                change_language();
                break;
            case 6:
                return SUCCESS;
                break;
            default:
                cout << "Try again" << endl;
                break;
        }
        cout << "+++++++++++++++++++++++++++++++++++++++++++" << endl;
        goto flag;
        return SUCCESS;
    }
    ~Dictionary()
    {
        ofstream data_out(basic_directory + cur_file + ".txt", ifstream::out);
        for (auto begin = plot.begin(); begin != plot.end(); begin++)
            data_out << begin->first << endl << begin->second.first << endl << begin->second.second << endl;
        data_out.close();
        ofstream file_out(filenames, ifstream::out);
        for (size_t i = 0; i != languages.size(); i++)
            if (languages[i].compare(cur_file) == 0)
            {
               string aux = languages[i];
               languages[i] = languages[0];
               languages[0] = aux;
               break;
            }
        for (size_t i = 0; i != languages.size(); i++)
            file_out << languages[i] << '\n';
        file_out.close();
    }
};
int main()
{
    Dictionary example;
    example.Menu();
    return SUCCESS;
}
