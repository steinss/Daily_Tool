#pragma once

#include <stdio.h>
#include <iostream>
#include <fstream>


struct IniInfo
{
	std::string  name;
	std::string  val;
	int          id;
	int          size;

};
namespace para_reader
{
	class IniReader
	{
	public:
		IniReader(const std::string& name);
		bool Connect();
		bool get_next_item(IniInfo& info);
		~IniReader();
	private:
		IniReader();
		void SearchItemHead(IniInfo& info);
		void SearchLine(IniInfo& info);
		void SearchVal(IniInfo& info);
		void UpdateLine();
		bool CheckItemHead();
		std::ifstream file_;
		std::string this_line_;
		enum ReaderState
		{
			S_IDLE = 0x10,
			S_SEARCH_HEAD = 0x20,
			S_SEARCH_PARA = 0x30,
			S_SEARCH_VAL = 0x40
		};
		ReaderState search_state_;
	};

}

