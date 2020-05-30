#pragma once
#include <string>
#include <vector>
class kmp_compare
{
public:
	kmp_compare(std::string word) :pattern(word) 
	{
		next = std::vector<int>(pattern.size(), 0);
		getNextPos(pattern);
	};
	void getNextPos(std::string& st)
	{
		int k = -1, j = 0;
		next[0] = -1;
		for (;;)
		{
			if (j >= pattern.size())
				break;
			if (k == -1 || pattern[j] == pattern[k])
			{
				k++; j++;
				if (pattern[j] == pattern[k])
					next[j] = next[k];
				else
				{
					next[j] = k;
				}

			}
			else
			{
				k = next[k];
			}
		}
	}
	int compare(const char* str)
	{
		int num = strlen(str);
		int j = 0, i = 0;
		int res = -1;
		for (; ;) {
			if (j > pattern.size()-1 || i > num-1)
				break;

			if (pattern[j] == str[i] || j==-1) {
				i++;
				j++;
			}

			else
			{
				j = next[j];
			}


		}
		if (j >= pattern.size())
		{
			res = i - j;
		}

		return res;
	}
private:
	std::string pattern;
	std::vector<int> next;
};
