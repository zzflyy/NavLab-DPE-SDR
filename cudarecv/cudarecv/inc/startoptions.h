
#ifndef INC__STARTOPTIONS_H_
#define INC__STARTOPTIONS_H_

#include <string>

//using namespace std;

class StartOptions {

    public:

        StartOptions(int argc, char* argv[]);

        bool console;                   /**< console mode *///ָʾ�����Ƿ��Կ���̨ģʽ����
        bool fromFile;                  /**< samples from file *///ָʾ���������Ƿ������ļ���
        unsigned int sampleRate;        /**< in Hz *///�����ʣ���λ�Ǻ��ȣ�Hz����
        unsigned int carrierFreq;       /**< in Hz *///�ز�Ƶ�ʣ���λ�Ǻ��ȣ�Hz����
        unsigned long skip;             /**< in number of samples *///��������������
        unsigned char fileFormat;//�ļ���ʽ��
        std::string filename;//�ļ�����

        bool error;//ָʾ�Ƿ�������

    private:

        /** \brief Initializes all options to defaults. *///��ʼ������ѡ��ΪĬ��ֵ��
        void InitDefaults(void);

        /** \brief Parses all of argv[] into options. *///���������в���������Ա������
        void ParseOptions(int argc, char* argv[]);

        /** \brief Prints usage instructions. *///��ӡʹ��˵����ͨ���������в�������ʱ���á�
        void Usage(char* program);

        /** \brief Parses frequency string into integer.
         *
         *  Parses possible strings such as 12.3GHz into integer of value Hz.
         *  Possible units are GHz, MHz, kHz.
         *  return frequency in Hz. -1 on error.
         *///����Ƶ���ַ������� "12.3GHz"��Ϊ��������ֵ���ڳ���ʱ���� -1��
        int ParseFreq(char* arg);

        /** \brief Splits an input string into its value and units. *///�������ַ����ָ�Ϊ��ֵ�͵�λ�����ؽ���״̬��
        int SplitArgument(char* arg, double &val, std::string &units);

};

#endif
