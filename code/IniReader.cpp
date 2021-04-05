#include "IniReader.h"
#include <string>

namespace para_reader
{
	bool _separator_char(char c)
	{
		return c == ' ' || c == '\n' || c == '\r' || c == '\t';
	}

	std::string string_del_space(const std::string& str, bool del_tail = true)
	{
		std::string ret;
		int start = 0;
		int end = str.length() - 1;
		for (; start < str.length();)
		{
			char c = str.at(start);
			if (!_separator_char(c))
			{
				break;
			}
			start++;
		}
		if (del_tail)
		{
			for (; end >= 0;)
			{
				char c = str.at(end);
				if (!_separator_char(c))
				{
					break;
				}
				end--;
			}
		}

		if (end >= start)
		{
			ret = str.substr(start, end - start+1);
		}
		return ret;
	}


	std::string& str_replace_all(std::string& str, std::string old_value, std::string new_value)
	{
		for (;;)
		{
			std::string::size_type pos(0);
			if ((pos = str.find(old_value)) != std::string::npos)
				str.replace(pos, old_value.length(), new_value);
			else
			{
				break;
			}
		}
		return str;

	}


	bool IniReader::Connect()
	{
		return search_state_ > S_IDLE;
	}

	bool IniReader::get_next_item(IniInfo& info)
	{
		info.name.clear();
		for (;;)
		{
			switch (search_state_)
			{
			case IniReader::S_SEARCH_HEAD:
				SearchItemHead(info);
				break;
			case IniReader::S_SEARCH_PARA:
				SearchLine(info);
				break;
			case IniReader::S_SEARCH_VAL:
				SearchVal(info);
				break;
			default:
				search_state_ = S_IDLE;
				break;
			}
			if (search_state_ < S_SEARCH_HEAD)
			{
				break;
			}
			if (CheckItemHead()&& search_state_ > S_SEARCH_HEAD )
			{
				search_state_ = S_SEARCH_HEAD;
				break;
			}
		}
		if (file_.eof())
		{
			search_state_ = S_IDLE;
			file_.close();
		}
		if (!info.val.empty())
		{
			str_replace_all(info.val, "\n", " ");
			str_replace_all(info.val, "\r", " ");
			str_replace_all(info.val, "\t", " ");
		}
		return !info.name.empty();
	}

	void IniReader::SearchItemHead(IniInfo& info)
	{
		bool st = false;
		st = CheckItemHead();
		if (st)
		{
			info.name = this_line_.substr(1, this_line_.length() - 2);
			search_state_ = S_SEARCH_PARA;
		}
		UpdateLine();
	}
	void IniReader::SearchLine(IniInfo& info)
	{
		int pos = -1;
		pos = this_line_.find("=");
		if (pos > 0 && pos < this_line_.length() - 1)
		{
			std::string shead, stail;
			shead = this_line_.substr(0, pos);
			stail = this_line_.substr(pos + 1, this_line_.length() - pos - 1);
			shead = string_del_space(shead);
			stail = string_del_space(stail);
			if ("val" == shead)
			{
				if (stail.at(0) == '<')
				{
					search_state_ = S_SEARCH_VAL;
					info.val = stail.substr(1, stail.length() - 1);
					info.val += std::string(" ");
				}
				else
				{
					info.val = stail;
				}
			}
		}
		UpdateLine();


	}
	void  IniReader::SearchVal(IniInfo& info)
	{
		int pos = -1;

		std::string line = string_del_space(this_line_);
		if (line.length() > 0)
		{
			line = line + std::string(" ");
			pos = line.find('>');
			if (pos > 0)
			{
				search_state_ = S_SEARCH_PARA;
				if (info.val.length() < 512)
				{
					info.val += line.substr(0, pos);
				}
			}
			else
			{
				if (info.val.length() < 512)
				{
					info.val += line;
				}

			}
		}


		UpdateLine();
	}
	void IniReader::UpdateLine()
	{
		char buffer[256];
		for (;;)
		{
			if (std::getline(file_, this_line_))
			{
				if (this_line_.length() <= 256)
				{
					break;
				}
			}
			else
			{
				search_state_ = S_IDLE;
				break;
			}
		}
		//if (file_.eof())
		//{
		//	search_state_ = S_IDLE;
		//}

	}


	bool IniReader::CheckItemHead()
	{
		if (this_line_.empty())
		{
			return false;
		}
		bool st = this_line_.front() == '[' && this_line_.back() == ']';
		return st;
	}

	IniReader::IniReader()
		:search_state_(S_IDLE)
	{}

	IniReader::IniReader(const std::string& name)
		: search_state_(S_IDLE)
	{
		file_.open(name);
		if (file_.is_open())
		{
			search_state_ = S_SEARCH_HEAD;
		}
	}
	IniReader::~IniReader()
	{
		if (file_.is_open())
		{
			file_.close();
		}
	}
}

