
#include <iostream>
#include <getopt.h>
#include <cstring>
#include <stdint.h>
#include <cstdlib>
#include "startoptions.h"
#include "auxil.h"

using namespace std;

#define OPT_STR    "f:"
//��ӡ�����ʹ�÷�ʽ��
void StartOptions::Usage(char* program) {
    cout << "Usage: " << program << "[-i] [-f filename]" << endl;//��ӡ�������ʹ�÷��������� program �ǳ�������ƣ�-i �� -f filename ��ʾ��ѡ�
    cout << "       " << "--no-console" << endl;//��ʾ --no-console ѡ���ѡ���������ָʾ�����Կ���̨ģʽ���С�
    cout << "       " << "--filename filename" << endl;//��ʾ --filename ѡ�������Ҫ����һ��������filename��������ָ�������ļ������ơ�
    cout << "       " << "--samplerate 2000000" << endl;//��ʾ --samplerate ѡ�������Ҫ����һ���������������ò����ʣ�ʾ����Ϊ 2000000 Hz��
    cout << "       " << "--carrierfrequency 0" << endl;//��ʾ --carrierfrequency ѡ�������Ҫ����һ�����������������ز�Ƶ�ʣ�ʾ����Ϊ 0 Hz��
    cout << "       " << "--skip 0" << endl;//��ʾ --skip ѡ�������Ҫ����һ������������ָ����������������ʾ����Ϊ 0��
    cout << "       " << "--fileformat 0" << endl;//��ʾ --fileformat ѡ�������Ҫ����һ�����������������ļ���ʽ��ʾ����Ϊ 0��
}//�������ͨ���ڽ��������в���ʱ���������������û�������Ҫ����ʱ���ã���ָ���û������ȷ��ʹ�ó���

//StartOptions ��� ParseOptions ��Ա������ʵ�֣������ڽ��������в���
void StartOptions::ParseOptions(int argc, char* argv[]) {
    int c; // ���ڴ洢 getopt_long ���ص�ֵ

    // ����ѭ�������ڳ�������������ѡ�ֱ��û�и���ѡ��
    while (1) {
        // ����һ����̬���飬�洢��ѡ�����Ϣ
        static struct option longOptions[] = {
            // ÿ��ѡ��������ơ��Ƿ��в�������־�Ͷ�Ӧ��ֵ
            {"no-console", no_argument, 0, '5'}, // ����������ѡ��
            {"filename", required_argument, 0, 'f'}, // ��Ҫ������ѡ��
            {"samplerate", required_argument, 0, '1'}, // ��Ҫ������ѡ��
            {"carrierfrequency", required_argument, 0, '2'}, // ��Ҫ������ѡ��
            {"skip", required_argument, 0, '3'}, // ��Ҫ������ѡ��
            {"fileformat", required_argument, 0, '4'}, // ��Ҫ������ѡ��
            {0, 0, 0, 0} // ѡ���б������־
        };

        int optionIndex = 0; // ���ڸ��ٵ�ǰ����ĳ�ѡ������

        // ������ѡ��Ͷ�ѡ�optarg �洢��ǰѡ��Ĳ���ֵ
        c = getopt_long(argc, argv, OPT_STR, longOptions, &optionIndex);
        // ���û�и���ѡ����������⣬�� getopt_long ���� -1
        if (c == -1) break;

        // ���ݵ�ǰѡ���ֵ��ִ����Ӧ�Ĳ���
        switch (c) {
        case '5': // ����� '--no-console' ѡ��
            console = false; // ���� console Ϊ false
            break;
        case 'f': // ����� '--filename' ѡ��
            fromFile = true; // ���� fromFile Ϊ true
            filename = optarg; // �洢����ֵ�� filename
            //cout << "from file: " << filename << endl; // ������Ϣ����ע��
            break;
        case '1': // ����� '--samplerate' ѡ��
            // ���������ʲ��������洢�� sampleRate ��
            sampleRate = ParseFreq(optarg);
            //cout << "sample rate: " << sampleRate << endl; // ������Ϣ����ע��
            break;
        case '2': // ����� '--carrierfrequency' ѡ��
            // �����ز�Ƶ�ʲ��������洢�� carrierFreq ��
            carrierFreq = ParseFreq(optarg);
            //cout << "carrier frequency: " << carrierFreq << endl; // ������Ϣ����ע��
            break;
        case '3': // ����� '--skip' ѡ��
            // �˴���δʵ�ֽ����߼�������ӡ����ֵ
            //cout << "skip: " << optarg << endl; // ������Ϣ����ע��
            break;
        case '4': // ����� '--fileformat' ѡ��
            // �˴���δʵ�ֽ����߼�������ӡ����ֵ
            //cout << "file format: " << optarg << endl; // ������Ϣ����ע��
            break;
        case '?': // ��� getopt_long ����δ֪ѡ������
            // getopt_long �Ѿ���ӡ�˴�����Ϣ
            error = true; // ���ô����־Ϊ true
            Usage(argv[0]); // ��ӡʹ��˵��
            return; // ���غ���
            break;
        default: // ��������޷�ʶ���ѡ��
            // ��ӡ������Ϣ�����˳�����
            cerr << "Error: option " << c
                << " not recognized. Argument: " << optarg << endl;
            error = true; // ���ô����־Ϊ true
            Usage(argv[0]); // ��ӡʹ��˵��
            return;
        }
    }

    // �˴��ĵ�����Ϣ��ע�͵��ˣ����ȡ��ע�ͣ�����ӡ console ��ֵ
    //cout << "console: " << console << endl;
}

StartOptions::StartOptions(int argc, char* argv[]) {
    InitDefaults();
    ParseOptions(argc, argv);
}

void StartOptions::InitDefaults() {
    error = false;
    console = true;
    fromFile = false;
    sampleRate = 2000000;
    carrierFreq = 0;
    skip = 0;
    fileFormat = 0;
    filename.clear();
}

int StartOptions::ParseFreq(char* arg) {
    double val = 0.0;
    string units;
    SplitArgument(arg, val, units);
    if (units.length() > 0){
        if (((auxil::strcmpi(units, string("MHz")) == 0) && (units.at(0) == 'M')) ||
                (units.compare("M") == 0))
            val *= 1000000.0;
        else if ((auxil::strcmpi(units, string("GHz")) == 0) ||
                (auxil::strcmpi(units, string("G")) == 0))
            val *= 1000000000.0;
        else if ((auxil::strcmpi(units, string("kHz")) == 0) ||
                (auxil::strcmpi(units, string("k")) == 0))
            val *= 1000.0;
        else
            return -1;
    }
    val += 0.5;
    return (int)val;
}

int StartOptions::SplitArgument(char* arg, double &val, string &units) {
    string str = arg;
    auxil::trimWhiteSpace(str);
    size_t split = str.find_first_not_of("1234567890.");
    string num;
    if (split >= str.length()){
        units.clear();
        num = str;
    } else {
        num = str.substr(0,split);
        str = str.substr(split, string::npos);
        auxil::trimWhiteSpace(str);
        units = str;
    }
    val = atof(num.c_str());
    return 0;
}
