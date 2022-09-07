#include <E:\Git\c++\一键进入祖安\jsoncpp-src-0.5.0\include\json\json.h>
#include <iostream>
#include<fstream>
#include <string>
#include<locale> 
#include<codecvt>
#include <random>
using namespace std;

std::string utf8_to_gbk(const std::string& str)
{
    std::wstring_convert<std::codecvt_utf8<wchar_t> > conv;
    std::wstring tmp_wstr = conv.from_bytes(str);

    //GBK locale name in windows
    const char* GBK_LOCALE_NAME = ".936";
    std::wstring_convert<std::codecvt_byname<wchar_t, char, mbstate_t>> convert(new std::codecvt_byname<wchar_t, char, mbstate_t>(GBK_LOCALE_NAME));
    return convert.to_bytes(tmp_wstr);
}

string LineFeed(const std::string& str) {
    string change = utf8_to_gbk(str);
    int i = 0, j = 1;
    while (i<change.size()-1)
    {
        if (change[i] == '\\' && change[j] == 'n') {
            change[i] = ' ';
            change[j] = '\n';
        }
        ++i;
        ++j;
    }
    return change;
}

int main()
{
    Json::Reader reader;
    Json::Value root;
    Json::Value content;
    ifstream is;

    is.open("caihongpi.json", ios::binary);
    if (reader.parse(is, root)) {
        content = root.get("words", root);
        /*int a = content.size();
        cout << a<<endl;*/
        uniform_int_distribution<unsigned> u(0, 832);
        default_random_engine e;
        Json::FastWriter fw;
        /*while (true)
        {
            getchar();
            int a = u(e);
            cout << a << endl;
            cout << LineFeed(fw.write(content[a])) << endl;
        }*/
        for (int i = 0;i < 832;++i) {
            if (i == 16||i == 43) {
                continue;
            }
            try
            {
                cout << i << LineFeed(fw.write(content[i])) << endl;
            }
            catch (const std::exception&)
            {

            }
            
        }
        /*cout << utf8_to_gbk(fw.write(content[247])) << endl;
        cout << LineFeed(fw.write(content[784])) << endl;*/
    }

}