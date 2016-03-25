#include <stdio.h>
#include <string>
#include <Windows.h>
using namespace std;

#pragma once
class CheckList
{
	private:
		int amount;
		COORD coord;
		string * options;
		HANDLE h;
	public:
		CheckList(string opts[], int optAmount);
		CheckList(string opts[], int optAmount, COORD crd);

		int getAmount();
		int addOption(string opt);
		void display(COORD crd);
		void display();

		~CheckList();
};

