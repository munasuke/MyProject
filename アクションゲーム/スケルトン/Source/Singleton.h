#pragma once

// ｼﾝｸﾞﾙﾄﾝのﾃﾝﾌﾟﾚｰﾄ化
namespace osaru
{
	template <class T>
	class Singleton
	{
	public:
		using InstanceType = T;
		virtual ~Singleton() {};
		static void Create(void)
		{
			if (s_instance == nullptr)
			{
				///インスタンスされてないならインスタンスする
				s_instance = new InstanceType();
			}
		}
		static void Destroy(void)
		{
			if (s_instance != nullptr)
			{
				delete s_instance;
			}
			s_instance = nullptr;	///関数を抜けるときに必ずNULLにする
		}
#ifndef GET_PTR
		static InstanceType *GetInstance(void)
		{
			return s_instance;
		}
#else
		static InstanceType &GetInstance(void)
		{
			return *s_instance;
		}
#endif
		static InstanceType *GetInstancePtr(void)
		{
			return s_instance;
		}
		static InstanceType &GetInstanceRef(void)
		{
			return *s_instance;
		}
		///作成済みかどうか
		static bool isCreate()
		{
			return (s_instance != nullptr);
		}
		///削除済みかどうか
		static bool isDestroy()
		{
			return (s_instance == nullptr);
		}

	private:
	protected:
		Singleton() {};
		static InstanceType *s_instance;
	};

	template <typename T> T*Singleton<T>::s_instance = nullptr;
}
