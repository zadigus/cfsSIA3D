#ifndef SINGLETON_HPP
#define SINGLETON_HPP

template<class T> class Singleton
{
	public:
		static T& getInstance();
		virtual ~Singleton() { };

	protected:
		Singleton() { };
};

template<class T> T& Singleton<T>::getInstance()
{
	static T instance;
	return instance;
}

#endif