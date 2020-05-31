#include <string>
#include <vector>
#include <io.h>
using namespace std;

/*******************************************************************************
��ȡ�ļ��м����ļ����������ļ�������·��
*******************************************************************************/
void getAllFiles(string path, string filter ,vector<string>& files) {
      //�ļ����
      long hFile = 0;
      //�ļ���Ϣ
      struct _finddata_t fileinfo;  //�����õ��ļ���Ϣ��ȡ�ṹ
      string p; 

      if ((hFile = _findfirst(p.assign(path).append("\\").append(filter).c_str(),&fileinfo)) != -1) {
          do {
              if ((fileinfo.attrib & _A_SUBDIR)) {  //�Ƚ��ļ������Ƿ����ļ���
                 if (strcmp(fileinfo.name,".") != 0 && strcmp(fileinfo.name,"..") != 0) {
                     //files.push_back(p.assign(path).append("\\").append(fileinfo.name));
                     getAllFiles(p.assign(path).append("\\").append(fileinfo.name),filter, files);
                 }
             } else {
                 files.push_back(p.assign(path).append("\\").append(fileinfo.name));
             }
         } while (_findnext(hFile, &fileinfo) == 0);  //Ѱ����һ�����ɹ�����0������-1
         _findclose(hFile);
     }
 }