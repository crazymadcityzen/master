#include <iostream>
#include <map>
#include <fstream>
#include <string>

#define SUCCESS 0
#define INCORRECT_INPUT -1

using namespace std;
class Dictionary
{
private:
    const string file_name = "./Dictionary/ItalianEnglish.txt";
    map<string, pair<string, string>> plot;
    int add()
    {
        pair<string, pair<string, string>> aux;
        getchar();
        cout << "Enter a word on Italian:" << endl;
        getline(cin, aux.first);
        cout << "Enter a gender of this word" << endl;
        getline(cin, aux.second.first);
        cout << "Enter an English translation for this word" << endl;
        getline(cin, aux.second.second);
        plot.insert(aux);
        return SUCCESS;
    }
    void print_all()
    {
        cout << "===========================================" << endl;
        for (auto begin = plot.begin(); begin != plot.end(); begin++)
            cout << begin->first << ' ' << begin->second.first << ' ' << begin->second.second << endl;
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
        pair<string, pair<string, string>> aux;
        while (getline(data_in, aux.first))
        {
            getline(data_in, aux.second.first);
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
