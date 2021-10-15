    #include <iostream>
    #include <thread>
    #include <condition_variable>
    #include <mutex>
    #include <chrono>
    #include <vector>
    #include <memory>
    
    using namespace std;

	// В классе Птенцов задем сколько еды каждый из них потребляет за один прием пиши и промежуток сна
    class Chick
	{
	public:
		float needFood = 1;
		chrono::milliseconds needSleep = chrono::milliseconds(rand() % 10000);
	};

	// В классе Мамы задаем количество приносимой ей еды (емкость миски)
    class Mother
    {
    public:
		float capacityFood = 6;
    };

	// В классе Миски в цикле реализуем потребление пиши птенцами
    class Bowl
    {
		mutex eatMutex_;
		condition_variable emptyBowl_;
		condition_variable fillBowl_;

		float food_ = 0.0f;
    public:
		// Потребление еды Птенцами
		void eat(std::shared_ptr<Chick>& chick)
		{
			unique_lock<mutex> lock(eatMutex_);
			while (food_ <= 0)
			{
				emptyBowl_.notify_all();
				fillBowl_.wait(lock);
			}
			cout << "ЕДА! ЕДА! ЕДА! ЕДА! ЕДА! ЕДА!" << endl;
			food_ -= chick->needFood;
		}

		// Наполнение миски Мамой
		void fillBowl(std::shared_ptr<Mother>& mother)
		{
			unique_lock<mutex> lock(eatMutex_);
			food_ += mother->capacityFood;
			cout << "Апхрыть-фу!,садитесь жрать личинусы"  << endl;
			fillBowl_.notify_all();
			emptyBowl_.wait(lock);
		}
    };

	// Проверка миски Мамой
    void motherThread(shared_ptr<Mother> mother, shared_ptr<Bowl> bowl)
    {
		while (true)
		{
			bowl->fillBowl(mother);
		}
    }

	// Проверка миски Птенцами
    void chicksThread(shared_ptr<Chick> chick, shared_ptr<Bowl> bowl)
    {
		while (true)
		{
			bowl->eat(chick);
			this_thread::sleep_for(chick->needSleep);
		}
    }

    int main()
    {
		// Задаем кол-во птенцов (от 2, *2=1)
		unsigned int chicksCount = 3;
		shared_ptr<Mother> mother { make_shared<Mother>() };
		shared_ptr<Bowl> bowl { make_shared<Bowl>() };

		thread mTh(&motherThread, mother, bowl);
		vector<thread> chicksThreads_;
		while (--chicksCount)
		{
			chicksThreads_.emplace_back(&chicksThread, make_shared<Chick>(), bowl);
		}

		mTh.join();

		return 0;
    }

