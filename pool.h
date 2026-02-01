#pragma once
#include<vector>
template<class T>
class object_pool
{
public:
	int capcity;
	std::vector<T>pool;

	//双队列遍历池
	std::vector<int>using_list;
	std::vector<int>free_list;
	
	
	//默认构造100的容量
	object_pool(int N = 100)
	{
		initiat(N);
		capcity = 100;
	}

	//传参初始化
	void initiat(int N)
	{
		if (N <= capcity)
			return;
		for (int i = capcity; i < N; i++)
		{
			free_list.push_back(i);
		}
		pool.resize(N);
		capcity = N;
	}

	//释放指定对象
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

	//释放所有没有在被使用的对象
	void free()
	{
		for (int i = 0;i<using_list.size();)
		{
			if (pool[using_list[i]].is_using == false)
			{
				free_list.push_back(using_list[i]);
				std::swap(using_list[i], using_list.back());
				using_list.pop_back();
			}
			else
			{
				i++;
			}
		}
	}

	int get()	//获取一个可用id
	{
		if (free_list.empty())return -1;
		int id = free_list.back();
		using_list.push_back(id);
		free_list.pop_back();
		return id;
	}

	void update()	//update池中所有正在被启用的对象
	{
		for (int id : using_list)
		{
			pool[id].update();
		}
	}

	void draw()		//绘制所以正在被激活的对象
	{
		for (int id : using_list)
		{
			pool[id].draw();
		}
	}

	template<typename Func>		//快捷调用函数，但并没有实际用上
	void for_each_activate(Func F)
	{
		for (int id : using_list)
		{
			F(pool[id]);
		}
	}

	T& operator[](int id)		//模仿数组，直接返回对象
	{
		return pool[id];
	}
};

