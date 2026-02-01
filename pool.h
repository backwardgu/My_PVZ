#pragma once
#include<vector>
template<class T>
class object_pool
{
public:
	int capcity;
	std::vector<T>pool;
	std::vector<int>using_list;
	std::vector<int>free_list;
	object_pool(int N = 50)
	{
		initiat(N);
	}
	void initiat(int N)
	{
		capcity = N;
		for (int i = 0; i < N; i++)
		{
			free_list.push_back(i);
		}
		pool.resize(N);
	}
	void free(int id)
	{
		for (int &it : using_list)
		{
			if (it == id)
			{
				std::swap(it, using_list.back());
				free_list.push_back(id);
				using_list.pop_back();
				return;
			}
		}
	}
	int get()
	{
		if (free_list.empty())return -1;
		int id = free_list.back();
		using_list.push_back(id);
		free_list.pop_back();
		return id;
	}
	void update()
	{
		for (int id : using_list)
		{
			pool[id].update();
		}
	}
	void draw()
	{
		for (int id : using_list)
		{
			pool[id].draw();
		}
	}
	template<typename Func>
	void for_each_activate(Func F)
	{
		for (int id : using_list)
		{
			F(pool[id]);
		}
	}
	T& operator[](int id)
	{
		return pool[id];
	}
};

