#include <string>
#include <vector>
#include <io.h>
#include <regex>
using namespace std;

/*******************************************************************************
获取文件夹及子文件夹下所有文件名绝对路径
*******************************************************************************/
void getAllFiles(string path, string filter ,vector<string>& files) {
      //文件句柄
      long long hFile = 0;
      //文件信息
      struct _finddata_t fileinfo;  //很少用的文件信息读取结构
      string p; 

	  regex pattern(filter);
	  regex sub_pattern("^[0-9A-Za-z][^]*");
      if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(),&fileinfo)) != -1) {
          do {
              if ((fileinfo.attrib & _A_SUBDIR)) {  //比较文件类型是否是文件夹
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
         } while (_findnext(hFile, &fileinfo) == 0);  //寻找下一个，成功返回0，否则-1
         _findclose(hFile);
     }
 }