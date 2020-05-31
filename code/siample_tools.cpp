#include <string>
#include <vector>
#include <io.h>
#include <regex>
using namespace std;

/*******************************************************************************
��ȡ�ļ��м����ļ����������ļ�������·��
*******************************************************************************/
void getAllFiles(string path, string filter ,vector<string>& files) {
      //�ļ����
      long long hFile = 0;
      //�ļ���Ϣ
      struct _finddata_t fileinfo;  //�����õ��ļ���Ϣ��ȡ�ṹ
      string p; 

	  regex pattern(filter);
	  regex sub_pattern("^[0-9A-Za-z][^]*");
      if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(),&fileinfo)) != -1) {
          do {
              if ((fileinfo.attrib & _A_SUBDIR)) {  //�Ƚ��ļ������Ƿ����ļ���
                 if (strcmp(fileinfo.name,".") != 0 && strcmp(fileinfo.name,"..") != 0
					 && regex_match(fileinfo.name,sub_pattern)
					 ) {
                     //files.push_back(p.assign(path).append("\\").append(fileinfo.name));
                     getAllFiles(p.assign(path).append("\\").append(fileinfo.name),filter, files);
                 }
             } else {
				  string f_name_tmp = p.assign(path).append("\\").append(fileinfo.name);
				  if (regex_match(f_name_tmp, pattern)) {
					  files.push_back(f_name_tmp);
				  }
             }
         } while (_findnext(hFile, &fileinfo) == 0);  //Ѱ����һ�����ɹ�����0������-1
         _findclose(hFile);
     }
 }